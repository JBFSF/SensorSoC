`timescale 1ns/1ps

module sim_chip_top_gl_sensor_bridge_env;
  localparam integer SENSOR_SCL_PAD = 23;
  localparam integer SENSOR_SDA_PAD = 24;
  localparam integer HOST_SDA_PAD   = 6;

  logic        clk_drv = 1'b0;
  logic        rst_n_drv = 1'b0;
  logic [11:0] input_drv = 12'h000;
  wire         clk_PAD;
  wire         rst_n_PAD;
  wire  [11:0] input_PAD;
  logic [39:0] bidir_drv = 40'h0;
  logic [39:0] bidir_oe = 40'h0;
  wire  [39:0] bidir_PAD;
  wire  [39:0] bidir_sample;
  wire         sensor_scl_sample;
  wire         sensor_sda_sample;
  logic        sensor_sda_drive_low = 1'b0;
  logic        accel_sda_o = 1'b1;
  logic        ppg_sda_o = 1'b1;
  logic        accel_scl_o = 1'b1;
  logic        ppg_scl_o = 1'b1;
  wire  [1:0]  analog_PAD;

  wire VDD = 1'b1;
  wire VSS = 1'b0;

  assign bidir_sample = bidir_PAD;
  assign sensor_scl_sample = bidir_PAD[SENSOR_SCL_PAD];
  assign sensor_sda_sample = bidir_PAD[SENSOR_SDA_PAD];
  assign clk_PAD = clk_drv;
  assign rst_n_PAD = rst_n_drv;
  assign input_PAD = input_drv;

  genvar i;
  generate
    for (i = 0; i < 40; i = i + 1) begin : tb_bidir_drive
      if (i == SENSOR_SDA_PAD) begin : sensor_sda_drive
        assign bidir_PAD[i] = (sensor_sda_drive_low || !accel_sda_o || !ppg_sda_o) ? 1'b0 :
                              (bidir_oe[i] ? bidir_drv[i] : 1'bz);
      end else begin : external_drive
        assign bidir_PAD[i] = bidir_oe[i] ? bidir_drv[i] : 1'bz;
      end
    end
  endgenerate

  pullup host_sda_pullup (bidir_PAD[HOST_SDA_PAD]);
  pullup sensor_sda_pullup (bidir_PAD[SENSOR_SDA_PAD]);

  // Alarm output exposed so chip_top_tb.py can poll dut.alarm_o directly.
  wire alarm_o;
  assign alarm_o = bidir_PAD[0];

  // ----------------------------------------------------------------
  // Verilog I2C slaves — raw SCL/SDA protocol, no Python overhead.
  // These replace the Python cocotbext-i2c slaves for GL simulation.
  // They monitor bidir_PAD[SENSOR_SCL_PAD] for SCL and drive
  // accel_sda_o / ppg_sda_o (combined in the bidir_PAD assignment
  // above) to pull SDA low when sending ACK or data.
  // ----------------------------------------------------------------

  wire clk_intern = clk_drv;    // system clock (same as chip drives internally)
  wire rst_n_intern = rst_n_drv;

  i2c_slave_lis2dw12_raw #(
      .I2C_ADDR (7'h19)
  ) u_accel_slave (
      .clk     (clk_intern),
      .resetn  (rst_n_intern),
      .scl_i   (bidir_PAD[SENSOR_SCL_PAD]),
      .sda_i   (bidir_PAD[SENSOR_SDA_PAD]),
      .sda_o   (accel_sda_o)
  );

  i2c_slave_adpd144ri_raw #(
      .I2C_ADDR  (7'h64),
      .WATERMARK (8)
  ) u_ppg_slave (
      .clk     (clk_intern),
      .resetn  (rst_n_intern),
      .scl_i   (bidir_PAD[SENSOR_SCL_PAD]),
      .sda_i   (bidir_PAD[SENSOR_SDA_PAD]),
      .sda_o   (ppg_sda_o)
  );

  chip_top
  `ifndef FUNCTIONAL
  // Parameter overrides only apply in RTL mode. In GL the netlist
  // already has parameters baked from synthesis.
  #(
    .CLK_HZ                 (1_000_000),    // 1 MHz (vs real 10MHz) — 10x faster sim
    .I2C_CLK_HZ             (100_000),      // QUARTER = 1M/(4*100k) = 2 → 8 sys-clk per I2C bit (near minimum)
    .GT_CLK_HZ              (1_000_000),
    .GT_EPOCH_HZ            (100),
    .GT_EPOCH_COUNT_MAX     (100),          // 1 sec / epoch_end — fast features for sim
    .ACC_POLL_PERIOD_TICKS  (5_000),        // 5ms intervals (matches real-chip ratio)
    .PPG_POLL_PERIOD_TICKS  (10),
    .PPG_WATERMARK          (8),
    .PPG_MAX_BURST_SAMPLES  (32),
    .CFG_MOTION_HI_TH       (16'hFFFF),
    .CFG_MAX_MOTION_HI      (16'hFFFF),
    .TIMER_RELOAD_DEFAULT   (100)
  )
  `endif
  u_chip (
    `ifdef USE_POWER_PINS
    .VDD(VDD),
    .VSS(VSS),
    `endif
    .clk_PAD(clk_PAD),
    .rst_n_PAD(rst_n_PAD),
    .input_PAD(input_PAD),
    .bidir_PAD(bidir_PAD),
    .analog_PAD(analog_PAD)
  );

  // Shared SPI flash: words [0:1023] firmware, [1024:3071] ML weights.
  localparam integer FLASH_WORDS = 3072;
  localparam integer WEIGHT_FLASH_OFFSET_WORDS = 1024;

  spi_flash_model #(
      .FLASH_WORDS    (FLASH_WORDS),
      .FLASH_INIT_HEX ("")
  ) u_boot_flash (
      .spi_clk  (bidir_PAD[1]),
      .spi_cs_n (bidir_PAD[3]),
      .spi_mosi (bidir_PAD[2]),
      .spi_miso (bidir_PAD[4])
  );

  string fw_hex, wt_hex;
  initial begin
      if (!$value$plusargs("FIRMWARE_HEX=%s", fw_hex))
          $fatal(1, "sim_chip_top_gl_sensor_bridge_env: no FIRMWARE_HEX — pass +FIRMWARE_HEX=<abs_path>");
      $readmemh(fw_hex, u_boot_flash.mem, 0, WEIGHT_FLASH_OFFSET_WORDS - 1);
      $display("sim_chip_top_gl_sensor_bridge_env: boot flash loaded from %s", fw_hex);

      if (!$value$plusargs("WEIGHT_HEX=%s", wt_hex))
          $fatal(1, "sim_chip_top_gl_sensor_bridge_env: no WEIGHT_HEX — pass +WEIGHT_HEX=<abs_path>");
      $readmemh(wt_hex, u_boot_flash.mem, WEIGHT_FLASH_OFFSET_WORDS, FLASH_WORDS - 1);
      $display("sim_chip_top_gl_sensor_bridge_env: weights loaded at word offset %0d from %s",
               WEIGHT_FLASH_OFFSET_WORDS, wt_hex);
  end

endmodule
