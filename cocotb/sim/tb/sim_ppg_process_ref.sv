`timescale 1ns/1ps

module sim_ppg_process_ref;

  logic clk = 1'b0;
  logic rst_i = 1'b0;
  logic [15:0] ppg_sample = '0;
  logic ppg_valid = 1'b0;
  logic [31:0] ppg_sample_time = '0;
  logic cfg_enable = 1'b1;
  logic cfg_bypass = 1'b0;
  logic cfg_signed = 1'b0;
  logic [11:0] cfg_lp_beta = '0;
  logic [11:0] cfg_base_alpha = '0;
  logic [23:0] cfg_env_decay = '0;
  logic cfg_abs_en = 1'b1;
  logic [11:0] cfg_thr_k = '0;
  logic [23:0] cfg_thr_min = '0;
  logic [31:0] cfg_refrac_ticks = '0;
  logic [31:0] cfg_rr_min_ticks = '0;
  logic [31:0] cfg_rr_max_ticks = '0;
  logic [7:0] cfg_q_amp_w = '0;
  logic [7:0] cfg_q_slope_w = '0;
  logic [7:0] cfg_q_refrac_penalty = '0;
  logic [7:0] cfg_q_min_accept = '0;

  wire beat_pulse;
  wire rr_valid;
  wire rr_accepted;
  wire [31:0] rr_interval;
  wire signed [16:0] delta_hr_bpm;
  wire [7:0] beat_quality;
  wire double_beat;
  wire missed_beat;
  wire ppg_invalid;

  ppg_process dut (
    .clk_i(clk),
    .rst_i(rst_i),
    .ppg_sample_i(ppg_sample),
    .ppg_valid_i(ppg_valid),
    .ppg_sample_time_i(ppg_sample_time),
    .cfg_enable_i(cfg_enable),
    .cfg_bypass_i(cfg_bypass),
    .cfg_signed_i(cfg_signed),
    .cfg_lp_beta_i(cfg_lp_beta),
    .cfg_base_alpha_i(cfg_base_alpha),
    .cfg_env_decay_i(cfg_env_decay),
    .cfg_abs_en_i(cfg_abs_en),
    .cfg_thr_k_i(cfg_thr_k),
    .cfg_thr_min_i(cfg_thr_min),
    .cfg_refrac_ticks_i(cfg_refrac_ticks),
    .cfg_rr_min_ticks_i(cfg_rr_min_ticks),
    .cfg_rr_max_ticks_i(cfg_rr_max_ticks),
    .cfg_q_amp_w_i(cfg_q_amp_w),
    .cfg_q_slope_w_i(cfg_q_slope_w),
    .cfg_q_refrac_penalty_i(cfg_q_refrac_penalty),
    .cfg_q_min_accept_i(cfg_q_min_accept),
    .beat_pulse_o(beat_pulse),
    .rr_valid_o(rr_valid),
    .rr_accepted_o(rr_accepted),
    .rr_interval_o(rr_interval),
    .delta_hr_bpm_o(delta_hr_bpm),
    .beat_quality_o(beat_quality),
    .double_beat_o(double_beat),
    .missed_beat_o(missed_beat),
    .ppg_invalid_o(ppg_invalid)
  );

endmodule
