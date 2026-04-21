`timescale 1ns/1ps

//------------------------------------------------------------------------------
// sim_top_unified_env.sv
//
// Shared cocotb wrapper for the unified top.sv environment.
//
// Purpose
// -------
// This wrapper is the common simulation shell for cocotb tests that target the
// unified SensorSoC top-level RTL:
//
//   - src/top.sv
//
// Instead of creating one-off SystemVerilog wrappers per cocotb test, this
// module centralizes the common environment:
//
//   1) unified top.sv instantiation
//   2) simulated accelerometer model
//   3) simulated PPG model
//   4) simulated SPI flash model
//   5) shared debug mirrors for cocotb assertions
//
// This lets Python tests focus on:
//
//   - reset and initialization checks
//   - host-I2C behavior
//   - repeated production-loop smoke checks
//   - future test-force wake/IRQ injection
//
// rather than duplicating environment setup in several SV wrappers.
//
// Why this exists alongside the long SV benches
// ---------------------------------------------
// The repo still keeps plain SystemVerilog end-to-end benches for the heaviest
// firmware-driven regressions. This shared wrapper supports a hybrid strategy:
//
//   - cocotb for narrow and medium-sized checks
//   - long SV benches for full integrated production-style runs
//
// Exposed signals
// ---------------
// Besides the normal top-level DUT ports, this wrapper exports a curated set of
// "debug tap" mirrors from inside top.sv so cocotb can observe system state
// without rebuilding custom wrappers:
//
//   - PicoRV32 debug outputs
//   - feature-latch state
//   - IRQ controller state
//   - power-control wake bookkeeping
//   - test mailbox mirrors
//
// The goal is to expose enough observability for bring-up and verification
// without turning the wrapper into a second implementation of the SoC.
//------------------------------------------------------------------------------

module sim_top_unified_env;

  logic clk = 1'b0;
  logic reset = 1'b1;

  // Test-only force hooks exposed so cocotb can inject wake/IRQ events
  // without rewriting the DUT or creating scenario-specific wrappers.
  logic test_force_irq  = 1'b0;
  logic test_force_wake = 1'b0;
  logic [2:0] test_irq_src = 3'b000;

  // Host-I2C drive controls. Cocotb can bit-bang transactions by driving SCL
  // directly and pulling SDA low when needed. Idle state is released/high.
  logic host_scl_drv = 1'b1;
  logic host_sda_drv_low = 1'b0;

  // Sensor-model simulation bus driven by top.sv's i2c_master.
  wire        sim_req;
  wire [6:0]  sim_addr;
  wire [7:0]  sim_reg;
  wire [7:0]  sim_len;
  wire        sim_write;
  wire [7:0]  sim_wdata;
  wire        sim_ack;
  wire [7:0]  sim_rdata;
  wire        sim_rvalid;
  wire        sim_rlast;
  wire        sim_err;

  wire        accel_sim_ack;
  wire [7:0]  accel_sim_rdata;
  wire        accel_sim_rvalid;
  wire        accel_sim_rlast;
  wire        accel_sim_err;

  wire        ppg_sim_ack;
  wire [7:0]  ppg_sim_rdata;
  wire        ppg_sim_rvalid;
  wire        ppg_sim_rlast;
  wire        ppg_sim_err;

  // Host-facing IO kept in the wrapper so multiple cocotb tests can share the
  // same top-level environment without rebuilding separate benches.
  wire        spi_clk;
  wire        spi_mosi;
  wire        spi_miso;
  wire        spi_cs_n;
  wire        boot_spi_clk;
  wire        boot_spi_mosi;
  wire        boot_spi_miso;
  wire        boot_spi_cs_n;
  wire        host_i2c_scl;
  tri1        host_i2c_sda;

  // Directly exposed DUT outputs from top.sv.
  wire                      feat_valid;
  wire signed [15:0]        time_feat;
  wire signed [15:0]        motion_feat;
  wire signed [15:0]        delta_hr_feat;
  wire signed [15:0]        mssd_feat;
  wire                      ml_update_gate;
  wire [7:0]                invalid_reason;
  wire                      epoch_end;
  wire                      alarm;
  wire [2:0]                irq_eoi;
  wire                      boot_done;
  wire                      pico_trap;
  wire                      pico_cpu_clk_en;
  wire                      pico_mem_valid;
  wire                      pico_mem_instr;
  wire                      pico_mem_ready;
  wire [3:0]                pico_mem_wstrb;
  wire [31:0]               pico_mem_addr;
  wire [31:0]               pico_mem_wdata;
  wire [31:0]               pico_irq;
  wire                      pico_sleeping;
  wire                      host_i2c_irq_event;
  wire                      ml_irq;
  wire                      timer_event;

  // Frequently-used mirrors from inside unified top.sv. These are intentionally
  // shallow "debug taps" for cocotb and avoid rewriting scenario-specific SV.
  wire                      feat_latched_valid;
  wire signed [15:0]        feat_latched_time;
  wire signed [15:0]        feat_latched_motion;
  wire signed [15:0]        feat_latched_delta_hr;
  wire signed [15:0]        feat_latched_mssd;
  wire                      feat_latched_gate;
  wire [7:0]                feat_latched_invalid_reason;
  wire [31:0]               irq_pending;
  wire [31:0]               irq_mask;
  wire [31:0]               irq_wake_en;
  wire [31:0]               irq_claim_id;
  wire [31:0]               pwr_wake_status;
  wire [31:0]               pwr_wake_reason;
  wire                      sleep_req;
  wire [31:0]               ml_score_hw;
  wire [31:0]               test_status;
  wire [31:0]               test_code;
  wire [15:0]               host_irq_count;
  wire [15:0]               host_conf_abs;
  wire [15:0]               host_logit0_proxy;
  wire [7:0]                host_conf_stat_mirror;

  localparam [6:0] ACC_ADDR = 7'h19;
  localparam [6:0] PPG_ADDR = 7'h64;

  assign sim_ack    = (sim_addr == ACC_ADDR) ? accel_sim_ack    :
                      (sim_addr == PPG_ADDR) ? ppg_sim_ack      : 1'b0;
  assign sim_rdata  = (sim_addr == ACC_ADDR) ? accel_sim_rdata  :
                      (sim_addr == PPG_ADDR) ? ppg_sim_rdata    : 8'h00;
  assign sim_rvalid = (sim_addr == ACC_ADDR) ? accel_sim_rvalid :
                      (sim_addr == PPG_ADDR) ? ppg_sim_rvalid   : 1'b0;
  assign sim_rlast  = (sim_addr == ACC_ADDR) ? accel_sim_rlast  :
                      (sim_addr == PPG_ADDR) ? ppg_sim_rlast    : 1'b0;
  assign sim_err    = (sim_addr == ACC_ADDR) ? accel_sim_err    :
                      (sim_addr == PPG_ADDR) ? ppg_sim_err      : 1'b1;

  // Host-I2C is idle-high by default in this shared wrapper. Tests that need
  // active host-I2C transactions can later drive additional wrapper-level hooks
  // or extend this environment with bit-banged helpers from cocotb.
  assign host_i2c_scl = host_scl_drv;
  assign host_i2c_sda = host_sda_drv_low ? 1'b0 : 1'bz;

  // Unified SoC + sensor pipeline under test.
  //
  // The default parameters match the current production-like simulation flow:
  // firmware boots from simple_sram, weights are loaded from the flash model,
  // and the sensor side runs with short simulation-friendly periods.
  top #(
    .MEM_WORDS(8192),
    .BOOT_WORDS(512),
    .FIRMWARE_HEX("firmware/build/prod_main/firmware.hex"),
    .WEIGHT_INIT_HEX(""),
    .CLK_HZ(1000),
    .GT_CLK_HZ(1000),
    .GT_EPOCH_HZ(100),
    .GT_EPOCH_COUNT_MAX(16),
    .ACC_POLL_PERIOD_TICKS(8),
    .PPG_POLL_PERIOD_TICKS(2),
    .PPG_WATERMARK(8),
    .PPG_MAX_BURST_SAMPLES(32),
    .CFG_REFRACT_MS(250),
    .CFG_RR_MIN_MS(300),
    .CFG_RR_MAX_MS(2000),
    .CFG_Q_MIN_ACCEPT(0),
    .CFG_BEAT_Q_MIN(0),
    .CFG_MIN_VALID_FRAC(0),
    .CFG_MAX_DOUBLE(8'd4),
    .CFG_MAX_MISSED(8'd3),
    .CFG_MOTION_HI_TH(16'hFFFF),
    .CFG_MAX_MOTION_HI(16'hFFFF),
    .MSSD_MIN_RR_COUNT(1)
  ) u_dut (
    .clk_i(clk),
    .reset_i(reset),
    .i2c_scl_i(host_i2c_scl),
    .i2c_sda_io(host_i2c_sda),
    .i2c_sda_i(host_i2c_sda),
    .i2c_sda_drive_low_o(),
    .sim_req_o(sim_req),
    .sim_addr_o(sim_addr),
    .sim_reg_o(sim_reg),
    .sim_len_o(sim_len),
    .sim_write_o(sim_write),
    .sim_wdata_o(sim_wdata),
    .sim_ack_i(sim_ack),
    .sim_rdata_i(sim_rdata),
    .sim_rvalid_i(sim_rvalid),
    .sim_rlast_i(sim_rlast),
    .sim_err_i(sim_err),
    .feat_valid_o(feat_valid),
    .time_feat_o(time_feat),
    .motion_feat_o(motion_feat),
    .delta_hr_feat_o(delta_hr_feat),
    .mssd_feat_o(mssd_feat),
    .ml_update_gate_o(ml_update_gate),
    .invalid_reason_o(invalid_reason),
    .spi_clk_o(spi_clk),
    .spi_mosi_o(spi_mosi),
    .spi_miso_i(spi_miso),
    .spi_cs_n_o(spi_cs_n),
    .boot_spi_clk_o(boot_spi_clk),
    .boot_spi_mosi_o(boot_spi_mosi),
    .boot_spi_miso_i(boot_spi_miso),
    .boot_spi_cs_n_o(boot_spi_cs_n),
    .epoch_end_o(epoch_end),
    .alarm_o(alarm),
    .test_force_irq_i(test_force_irq),
    .test_force_wake_i(test_force_wake),
    .test_irq_src_i(test_irq_src),
    .irq_eoi_o(irq_eoi),
    .boot_done_o(boot_done),
    .pico_trap_o(pico_trap),
    .pico_cpu_clk_en_o(pico_cpu_clk_en),
    .pico_mem_valid_o(pico_mem_valid),
    .pico_mem_instr_o(pico_mem_instr),
    .pico_mem_ready_o(pico_mem_ready),
    .pico_mem_wstrb_o(pico_mem_wstrb),
    .pico_mem_addr_o(pico_mem_addr),
    .pico_mem_wdata_o(pico_mem_wdata),
    .pico_irq_o(pico_irq),
    .pico_sleeping_o(pico_sleeping),
    .host_i2c_irq_event_o(host_i2c_irq_event),
    .ml_irq_o(ml_irq),
    .timer_event_o(timer_event)
  );

  // Accelerometer model backing the top.sv simulated I2C path.
  i2c_slave_lis2dw12 #(
    .I2C_ADDR(ACC_ADDR)
  ) u_accel_slave (
    .clk(clk),
    .resetn(~reset),
    .sim_req(sim_req),
    .sim_addr(sim_addr),
    .sim_reg(sim_reg),
    .sim_len(sim_len),
    .sim_ack(accel_sim_ack),
    .sim_rdata(accel_sim_rdata),
    .sim_rvalid(accel_sim_rvalid),
    .sim_rlast(accel_sim_rlast),
    .sim_err(accel_sim_err)
  );

  // PPG model backing the top.sv simulated I2C path.
  i2c_slave_adpd144ri #(
    .I2C_ADDR(PPG_ADDR)
  ) u_ppg_slave (
    .clk(clk),
    .resetn(~reset),
    .sim_req(sim_req),
    .sim_addr(sim_addr),
    .sim_reg(sim_reg),
    .sim_len(sim_len),
    .sim_write(sim_write),
    .sim_wdata(sim_wdata),
    .sim_ack(ppg_sim_ack),
    .sim_rdata(ppg_sim_rdata),
    .sim_rvalid(ppg_sim_rvalid),
    .sim_rlast(ppg_sim_rlast),
    .sim_err(ppg_sim_err)
  );

  // Simulated SPI flash used by firmware boot/load flows. The parameter image
  // is the same generated taketwo payload used by the other unified-top tests.
  spi_flash_model #(
    .FLASH_WORDS(208),
    .FLASH_INIT_HEX("firmware/build/generated/taketwo_params.hex")
  ) u_flash (
    .spi_clk(spi_clk),
    .spi_cs_n(spi_cs_n),
    .spi_mosi(spi_mosi),
    .spi_miso(spi_miso)
  );

  spi_flash_model #(
    .FLASH_WORDS(512),
    .FLASH_INIT_HEX("firmware/build/prod_main/firmware.hex")
  ) u_boot_flash (
    .spi_clk(boot_spi_clk),
    .spi_cs_n(boot_spi_cs_n),
    .spi_mosi(boot_spi_mosi),
    .spi_miso(boot_spi_miso)
  );

  // Internal mirrors used by cocotb tests. These keep the Python layer simple
  // and make reset/init / repeated-loop checks much easier to express.
  assign feat_latched_valid          = u_dut.feat_latched_valid_r;
  assign feat_latched_time           = u_dut.feat_time_latched_r;
  assign feat_latched_motion         = u_dut.feat_motion_latched_r;
  assign feat_latched_delta_hr       = u_dut.feat_delta_hr_latched_r;
  assign feat_latched_mssd           = u_dut.feat_mssd_latched_r;
  assign feat_latched_gate           = u_dut.feat_gate_latched_r;
  assign feat_latched_invalid_reason = u_dut.feat_invalid_reason_latched_r;
  assign irq_pending                 = u_dut.u_irqc.pending;
  assign irq_mask                    = u_dut.u_irqc.mask;
  assign irq_wake_en                 = u_dut.u_irqc.wake_en;
  assign irq_claim_id                = u_dut.u_irqc.claim_id;
  assign pwr_wake_status             = u_dut.u_pwr.wake_status;
  assign pwr_wake_reason             = u_dut.u_pwr.wake_reason;
  assign sleep_req                   = u_dut.sleep_req;
  assign ml_score_hw                 = u_dut.ml_score_hw;
  assign test_status                 = u_dut.test_status;
  assign test_code                   = u_dut.test_code;
  assign host_irq_count              = u_dut.u_host_i2c_bridge_regs.irq_count;
  assign host_conf_abs               = u_dut.u_host_i2c_bridge_regs.score_conf;
  assign host_logit0_proxy           = u_dut.u_host_i2c_bridge_regs.score_proxy0;
  assign host_conf_stat_mirror       = {4'b0,
                                        u_dut.u_host_i2c_bridge_regs.conf_armed,
                                        u_dut.u_host_i2c_bridge_regs.conf_thr_irq_fired_sticky,
                                        u_dut.u_host_i2c_bridge_regs.conf_cross_seen_sticky,
                                        u_dut.u_host_i2c_bridge_regs.above_thr_live};

  // Shared waveform dump for cocotb runs using this wrapper. Tests may ignore
  // it during normal passes, but it is invaluable when a new cocotb regression
  // fails during bring-up.
  initial begin
    $dumpfile("top_unified_env.vcd");
    $dumpvars(0, sim_top_unified_env);
  end

endmodule
