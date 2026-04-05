`timescale 1ns/1ps

module sim_top_feature_mmio_unified;

  logic clk = 1'b0;
  logic reset = 1'b1;

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

  wire                      feat_valid;
  wire signed [15:0]        time_feat;
  wire signed [15:0]        motion_feat;
  wire signed [15:0]        delta_hr_feat;
  wire signed [15:0]        rmssd_feat;
  wire                      ml_update_gate;
  wire [7:0]                invalid_reason;
  wire                      epoch_end;
  wire                      alarm;

  // Expose the new SoC-visible feature latch state from the unified top.
  wire                      feat_latched_valid;
  wire signed [15:0]        feat_latched_time;
  wire signed [15:0]        feat_latched_motion;
  wire signed [15:0]        feat_latched_delta_hr;
  wire signed [15:0]        feat_latched_rmssd;
  wire                      feat_latched_gate;
  wire [7:0]                feat_latched_invalid_reason;
  wire [31:0]               feat_status_mirror;

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

  top #(
    .CLK_HZ(1000),
    .GT_CLK_HZ(1000),
    .GT_EPOCH_HZ(100),
    .GT_EPOCH_COUNT_MAX(300),
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
    .COS_PERIOD_SECONDS(32'd16),
    .COS_LUT_BITS(3'd6),
    .COS_SCALE_Q15(16'h7FFF),
    .RMSSD_MIN_RR_COUNT(1)
  ) u_dut (
    .clk_i(clk),
    .reset_i(reset),
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
    .rmssd_feat_o(rmssd_feat),
    .ml_update_gate_o(ml_update_gate),
    .invalid_reason_o(invalid_reason),
    .epoch_end_o(epoch_end),
    .alarm_o(alarm)
  );

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

  assign feat_latched_valid          = u_dut.feat_latched_valid_r;
  assign feat_latched_time           = u_dut.feat_time_latched_r;
  assign feat_latched_motion         = u_dut.feat_motion_latched_r;
  assign feat_latched_delta_hr       = u_dut.feat_delta_hr_latched_r;
  assign feat_latched_rmssd          = u_dut.feat_rmssd_latched_r;
  assign feat_latched_gate           = u_dut.feat_gate_latched_r;
  assign feat_latched_invalid_reason = u_dut.feat_invalid_reason_latched_r;
  assign feat_status_mirror          = {14'd0, u_dut.feat_gate_latched_r, 8'd0,
                                        u_dut.feat_invalid_reason_latched_r, u_dut.feat_latched_valid_r};

  initial begin
    $dumpfile("top_feature_mmio_unified.vcd");
    $dumpvars(0, clk, reset);
    $dumpvars(0, feat_valid, time_feat, motion_feat, delta_hr_feat, rmssd_feat);
    $dumpvars(0, ml_update_gate, invalid_reason, epoch_end, alarm);
    $dumpvars(0, feat_latched_valid, feat_latched_time, feat_latched_motion);
    $dumpvars(0, feat_latched_delta_hr, feat_latched_rmssd);
    $dumpvars(0, feat_latched_gate, feat_latched_invalid_reason, feat_status_mirror);
    $dumpvars(0, u_dut);
  end

endmodule
