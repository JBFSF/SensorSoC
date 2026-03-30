`timescale 1ns/1ps

module sim_host_i2c_bridge_regs;
  reg clk = 0;
  reg resetn = 0;

  reg        wr_en_i;
  reg [7:0]  wr_addr_i;
  reg [7:0]  wr_data_i;
  reg [7:0]  rd_addr_i;
  wire [7:0] rd_data_o;

  reg        proto_err_i;
  reg [31:0] ml_score_i;
  wire       event_o;

  wire [31:0] cfg_target_wake_sec_o;
  wire [31:0] cfg_window_sec_o;
  wire [15:0] cfg_step_sec_o;
  wire [15:0] cfg_motion_hi_th_o;
  wire [7:0]  cfg_motion_hi_count_o;
  wire [7:0]  cfg_policy_o;
  wire [15:0] cfg_conf_thr_o;

  wire        irqc_req_o;
  wire        irqc_we_o;
  wire [7:0]  irqc_off_o;
  wire [31:0] irqc_wdata_o;
  reg         irqc_ready_i;
  reg [31:0]  irqc_rdata_i;

  host_i2c_bridge_regs dut (
    .clk(clk),
    .resetn(resetn),
    .wr_en_i(wr_en_i),
    .wr_addr_i(wr_addr_i),
    .wr_data_i(wr_data_i),
    .rd_addr_i(rd_addr_i),
    .rd_data_o(rd_data_o),
    .proto_err_i(proto_err_i),
    .ml_score_i(ml_score_i),
    .event_o(event_o),
    .cfg_target_wake_sec_o(cfg_target_wake_sec_o),
    .cfg_window_sec_o(cfg_window_sec_o),
    .cfg_step_sec_o(cfg_step_sec_o),
    .cfg_motion_hi_th_o(cfg_motion_hi_th_o),
    .cfg_motion_hi_count_o(cfg_motion_hi_count_o),
    .cfg_policy_o(cfg_policy_o),
    .cfg_conf_thr_o(cfg_conf_thr_o),
    .irqc_req_o(irqc_req_o),
    .irqc_we_o(irqc_we_o),
    .irqc_off_o(irqc_off_o),
    .irqc_wdata_o(irqc_wdata_o),
    .irqc_ready_i(irqc_ready_i),
    .irqc_rdata_i(irqc_rdata_i)
  );
endmodule
