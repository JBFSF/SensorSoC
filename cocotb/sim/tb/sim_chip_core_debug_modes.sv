`timescale 1ns/1ps

`default_nettype none

module sim_chip_core_debug_modes;

  localparam int NUM_INPUT_PADS = 12;
  localparam int NUM_BIDIR_PADS = 40;
  localparam int NUM_ANALOG_PADS = 2;
  localparam int DEBUG_BUS_LO = 7;
  localparam int DEBUG_BUS_HI = 22;

  logic clk = 1'b0;
  logic rst_n = 1'b0;
  logic [3:0] mode_sel = 4'b0000;

  logic        stim_override_en = 1'b0;
  logic [15:0] stim_mssd = 16'h0000;
  logic [15:0] stim_delta_hr = 16'h0000;
  logic [15:0] stim_time = 16'h0000;
  logic [15:0] stim_motion = 16'h0000;

  logic [NUM_INPUT_PADS-1:0] input_in;
  wire [NUM_BIDIR_PADS-1:0] bidir_in;
  wire [NUM_ANALOG_PADS-1:0] analog;

  logic [NUM_INPUT_PADS-1:0] input_pu;
  logic [NUM_INPUT_PADS-1:0] input_pd;
  logic [NUM_BIDIR_PADS-1:0] bidir_out;
  logic [NUM_BIDIR_PADS-1:0] bidir_oe;
  logic [NUM_BIDIR_PADS-1:0] bidir_cs;
  logic [NUM_BIDIR_PADS-1:0] bidir_sl;
  logic [NUM_BIDIR_PADS-1:0] bidir_ie;
  logic [NUM_BIDIR_PADS-1:0] bidir_pu;
  logic [NUM_BIDIR_PADS-1:0] bidir_pd;

  logic [15:0] debug_bus;
  logic [15:0] debug_oe;

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

  wire signed [15:0] ax_w;
  wire signed [15:0] ay_w;
  wire signed [15:0] az_w;
  wire               accel_valid_w;
  wire [15:0]        motion_inst_mag_w;
  wire               motion_epoch_w;
  wire [47:0]        motion_energy_w;
  wire [15:0]        ppg_sample_w;
  wire               ppg_sample_valid_w;
  wire [31:0]        ppg_sample_time_w;
  wire               beat_pulse_w;
  wire               rr_valid_w;
  wire               rr_accepted_w;
  wire [31:0]        rr_interval_w;
  wire signed [16:0] delta_hr_w;
  wire [7:0]         beat_quality_w;
  wire               double_beat_w;
  wire               missed_beat_w;
  wire               ppg_invalid_w;
  wire [15:0]        mssd_w;
  wire               mssd_valid_w;
  wire               fifo_overflow_event_w;
  wire               ppg_i2c_err_event_w;
  wire [15:0]        seconds_w;
  wire               epoch_end_w;
  wire               epoch_end_d;
  wire               feat_valid_o;
  wire signed [15:0] time_feat_o;
  wire signed [15:0] motion_feat_o;
  wire signed [15:0] delta_hr_feat_o;
  wire signed [15:0] mssd_feat_o;
  wire               ml_update_gate_o;
  wire [7:0]         invalid_reason_o;

  localparam [6:0] ACC_ADDR = 7'h19;
  localparam [6:0] PPG_ADDR = 7'h64;

  assign analog = 'z;
  assign bidir_in = {{(NUM_BIDIR_PADS-7){1'b0}}, 2'b11, 5'b00000};
  assign input_in = {{(NUM_INPUT_PADS-4){1'b0}}, mode_sel};
  assign debug_bus = bidir_out[DEBUG_BUS_HI:DEBUG_BUS_LO];
  assign debug_oe = bidir_oe[DEBUG_BUS_HI:DEBUG_BUS_LO];

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

  chip_core #(
    .NUM_INPUT_PADS(NUM_INPUT_PADS),
    .NUM_BIDIR_PADS(NUM_BIDIR_PADS),
    .NUM_ANALOG_PADS(NUM_ANALOG_PADS),
    .DEBUG_STIM_EN(1),
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
    .MSSD_MIN_RR_COUNT(1)
  ) u_chip_core (
    .clk(clk),
    .rst_n(rst_n),
    .input_in(input_in),
    .input_pu(input_pu),
    .input_pd(input_pd),
    .bidir_in(bidir_in),
    .bidir_out(bidir_out),
    .bidir_oe(bidir_oe),
    .bidir_cs(bidir_cs),
    .bidir_sl(bidir_sl),
    .bidir_ie(bidir_ie),
    .bidir_pu(bidir_pu),
    .bidir_pd(bidir_pd),
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
    .debug_stim_override_en_i(stim_override_en),
    .debug_stim_mssd_i(stim_mssd),
    .debug_stim_delta_hr_i(stim_delta_hr),
    .debug_stim_time_i(stim_time),
    .debug_stim_motion_i(stim_motion),
    .analog(analog)
  );

  i2c_slave_lis2dw12 #(
    .I2C_ADDR(ACC_ADDR)
  ) u_accel_slave (
    .clk(clk),
    .resetn(rst_n),
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
    .resetn(rst_n),
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

  assign ax_w = u_chip_core.u_top.ax_w;
  assign ay_w = u_chip_core.u_top.ay_w;
  assign az_w = u_chip_core.u_top.az_w;
  assign accel_valid_w = u_chip_core.u_top.accel_valid_w;
  assign motion_inst_mag_w = u_chip_core.u_top.motion_inst_mag_w;
  assign motion_epoch_w = u_chip_core.u_top.motion_epoch_w;
  assign motion_energy_w = u_chip_core.u_top.motion_energy_w;
  assign ppg_sample_w = u_chip_core.u_top.ppg_sample_w;
  assign ppg_sample_valid_w = u_chip_core.u_top.ppg_sample_valid_w;
  assign ppg_sample_time_w = u_chip_core.u_top.ppg_sample_time_w;
  assign beat_pulse_w = u_chip_core.u_top.beat_pulse_w;
  assign rr_valid_w = u_chip_core.u_top.rr_valid_w;
  assign rr_accepted_w = u_chip_core.u_top.rr_accepted_w;
  assign rr_interval_w = u_chip_core.u_top.rr_interval_w;
  assign delta_hr_w = u_chip_core.u_top.delta_hr_w;
  assign beat_quality_w = u_chip_core.u_top.beat_quality_w;
  assign double_beat_w = u_chip_core.u_top.double_beat_w;
  assign missed_beat_w = u_chip_core.u_top.missed_beat_w;
  assign ppg_invalid_w = u_chip_core.u_top.ppg_invalid_w;
  assign mssd_w = u_chip_core.u_top.mssd_w[15:0];
  assign mssd_valid_w = u_chip_core.u_top.mssd_valid_w;
  assign fifo_overflow_event_w = u_chip_core.u_top.fifo_overflow_event_w;
  assign ppg_i2c_err_event_w = u_chip_core.u_top.ppg_i2c_err_event_w;
  assign seconds_w = u_chip_core.u_top.seconds_w;
  assign epoch_end_w = u_chip_core.u_top.epoch_end_w;
  assign epoch_end_d = u_chip_core.u_top.epoch_end_d;
  assign feat_valid_o = u_chip_core.u_top.feat_valid_o;
  assign time_feat_o = u_chip_core.u_top.time_feat_o;
  assign motion_feat_o = u_chip_core.u_top.motion_feat_o;
  assign delta_hr_feat_o = u_chip_core.u_top.delta_hr_feat_o;
  assign mssd_feat_o = u_chip_core.u_top.mssd_feat_o;
  assign ml_update_gate_o = u_chip_core.u_top.ml_update_gate_o;
  assign invalid_reason_o = u_chip_core.u_top.invalid_reason_o;

  initial begin
    $dumpfile("chip_core_debug_modes.vcd");
    $dumpvars(0, sim_chip_core_debug_modes);
  end

endmodule
