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

  chip_top u_chip (
    .VDD(VDD),
    .VSS(VSS),
    .clk_PAD(clk_PAD),
    .rst_n_PAD(rst_n_PAD),
    .input_PAD(input_PAD),
    .bidir_PAD(bidir_PAD),
    .analog_PAD(analog_PAD)
  );
endmodule
