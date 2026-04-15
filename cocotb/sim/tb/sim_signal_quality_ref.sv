`timescale 1ns/1ps

module sim_signal_quality_ref;

  logic clk = 1'b0;
  logic rst_i = 1'b0;
  logic epoch_end = 1'b0;
  logic beat_event = 1'b0;
  logic [7:0] beat_quality = '0;
  logic double_beat = 1'b0;
  logic missed_beat = 1'b0;
  logic fifo_overflow = 1'b0;
  logic fifo_i2c_error = 1'b0;
  logic motion_valid = 1'b0;
  logic [15:0] motion_intensity = '0;
  logic [7:0] cfg_beat_q_min = '0;
  logic [7:0] cfg_min_valid_fraction = '0;
  logic [7:0] cfg_max_double = '0;
  logic [7:0] cfg_max_missed = '0;
  logic [15:0] cfg_motion_hi_th = '0;
  logic [15:0] cfg_max_motion_hi = '0;

  wire [7:0] invalid_reason;
  wire ml_update_gate;

  signal_quality dut (
    .clk_i(clk),
    .rst_i(rst_i),
    .epoch_end_i(epoch_end),
    .beat_event_i(beat_event),
    .beat_quality_i(beat_quality),
    .double_beat_i(double_beat),
    .missed_beat_i(missed_beat),
    .fifo_overflow_i(fifo_overflow),
    .fifo_i2c_error_i(fifo_i2c_error),
    .motion_valid_i(motion_valid),
    .motion_intensity_i(motion_intensity),
    .cfg_beat_q_min_i(cfg_beat_q_min),
    .cfg_min_valid_fraction_i(cfg_min_valid_fraction),
    .cfg_max_double_i(cfg_max_double),
    .cfg_max_missed_i(cfg_max_missed),
    .cfg_motion_hi_th_i(cfg_motion_hi_th),
    .cfg_max_motion_hi_i(cfg_max_motion_hi),
    .invalid_reason_o(invalid_reason),
    .ml_update_gate_o(ml_update_gate)
  );

endmodule
