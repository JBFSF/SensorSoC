`timescale 1ns/1ps

module ppg_process_tb;

  localparam int SAMPLE_W = 16;
  localparam int T_W = 32;
  localparam int COEFF_W = 12;
  localparam int COEFF_FRAC = 10;
  localparam int COEFF_ONE = (1 << COEFF_FRAC);

  logic clk = 0;
  logic rst_i = 1;

  logic [SAMPLE_W-1:0] ppg_sample;
  logic                ppg_valid;
  logic [T_W-1:0]      ppg_sample_time;
  logic [T_W-1:0]      sim_time;

  logic                cfg_enable;
  logic                cfg_bypass;
  logic                cfg_signed;
  logic [COEFF_W-1:0]  cfg_lp_beta;
  logic [COEFF_W-1:0]  cfg_base_alpha;
  logic [23:0]         cfg_env_decay;
  logic                cfg_abs_en;
  logic [COEFF_W-1:0]  cfg_thr_k;
  logic [23:0]         cfg_thr_min;
  logic [T_W-1:0]      cfg_refrac_ticks;
  logic [T_W-1:0]      cfg_rr_min_ticks;
  logic [T_W-1:0]      cfg_rr_max_ticks;
  logic [7:0]          cfg_q_amp_w;
  logic [7:0]          cfg_q_slope_w;
  logic [7:0]          cfg_q_refrac_penalty;
  logic [7:0]          cfg_q_min_accept;

  wire                 beat_pulse;
  wire                 rr_valid;
  wire                 rr_accepted;
  wire [T_W-1:0]       rr_interval;
  wire signed [16:0]   delta_hr_bpm;
  wire [7:0]           beat_quality;
  wire                 double_beat;
  wire                 missed_beat;
  wire                 ppg_invalid;

  ppg_process #(
    .SAMPLE_W(SAMPLE_W),
    .T_W(T_W),
    .COEFF_W(COEFF_W),
    .COEFF_FRAC(COEFF_FRAC)
  ) dut (
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

  always #10 clk = ~clk;

  always @(posedge clk) begin
    if (rst_i) sim_time <= 0;
    else sim_time <= sim_time + 1;
  end

  task automatic step_sample(input int s);
    begin
      @(negedge clk);
      ppg_sample <= s[SAMPLE_W-1:0];
      ppg_sample_time <= sim_time;
      ppg_valid <= 1'b1;
      @(posedge clk);
      @(negedge clk);
      ppg_valid <= 1'b0;
    end
  endtask

  task automatic idle_cycles(input int n);
    begin
      repeat (n) step_sample(0);
    end
  endtask

  task automatic emit_peak(input int amp);
    begin
      step_sample(0);
      step_sample(amp/3);
      step_sample((2*amp)/3);
      step_sample(amp);
      step_sample((2*amp)/3);
      step_sample(amp/3);
      step_sample(0);
    end
  endtask

  task automatic reset_dut();
    begin
      rst_i <= 1'b1;
      repeat (5) @(posedge clk);
      rst_i <= 1'b0;
      repeat (2) @(posedge clk);
    end
  endtask

  int beat_count;
  int rr_count;
  int dbl_count;
  int miss_count;
  reg [T_W-1:0] last_rr;
  reg signed [16:0] last_delta_hr;

  always @(posedge clk) begin
    if (rst_i) begin
      beat_count <= 0;
      rr_count <= 0;
      dbl_count <= 0;
      miss_count <= 0;
      last_rr <= 0;
      last_delta_hr <= 0;
    end else begin
      if (beat_pulse) beat_count <= beat_count + 1;
      if (rr_valid) begin
        rr_count <= rr_count + 1;
        last_rr <= rr_interval;
        last_delta_hr <= delta_hr_bpm;
      end
      if (double_beat) dbl_count <= dbl_count + 1;
      if (missed_beat) miss_count <= miss_count + 1;
    end
  end

  task automatic apply_default_cfg();
    begin
      cfg_enable            = 1'b1;
      cfg_bypass            = 1'b0;
      cfg_signed            = 1'b0;
      cfg_lp_beta           = COEFF_ONE;
      cfg_base_alpha        = 0;
      cfg_env_decay         = 24'd2;
      cfg_abs_en            = 1'b1;
      cfg_thr_k             = (COEFF_ONE/2); // 0.5 * envelope
      cfg_thr_min           = 24'd40;
      cfg_refrac_ticks      = 32'd250;
      cfg_rr_min_ticks      = 32'd300;
      cfg_rr_max_ticks      = 32'd2000;
      cfg_q_amp_w           = 8'd4;
      cfg_q_slope_w         = 8'd2;
      cfg_q_refrac_penalty  = 8'd8;
      cfg_q_min_accept      = 8'd5;
    end
  endtask

  initial begin
    ppg_sample = 0;
    ppg_valid = 0;
    ppg_sample_time = 0;
    sim_time = 0;
    apply_default_cfg();

    // 1) First beat after reset: beat pulse, no RR.
    apply_default_cfg();
    reset_dut();
    beat_count = 0;
    rr_count = 0;
    emit_peak(600);
    idle_cycles(20);
    if (beat_count < 1) $fatal(1, "first beat not detected");
    if (rr_count != 0) $fatal(1, "rr_valid should stay low on first beat");

    // 2) RR interval update on second beat.
    apply_default_cfg();
    reset_dut();
    beat_count = 0;
    rr_count = 0;
    emit_peak(600);
    idle_cycles(950);
    emit_peak(600);
    idle_cycles(20);
    if (rr_count < 1) $fatal(1, "rr_valid not asserted on subsequent beat");
    if ((last_rr < cfg_rr_min_ticks) || (last_rr > cfg_rr_max_ticks))
      $fatal(1, "rr interval out of configured bounds: %0d", last_rr);

    // 3) Refractory / min-RR reject: very close next beat => double_beat flag.
    apply_default_cfg();
    cfg_refrac_ticks = 32'd50;
    reset_dut();
    dbl_count = 0;
    emit_peak(600);
    idle_cycles(120);
    emit_peak(600);
    idle_cycles(20);
    if (dbl_count < 1) $fatal(1, "double beat was not flagged");

    // 4) Missed beat flag: RR > rr_max accepted with missed_beat.
    apply_default_cfg();
    cfg_rr_max_ticks = 32'd500;
    reset_dut();
    miss_count = 0;
    emit_peak(600);
    idle_cycles(800);
    emit_peak(600);
    idle_cycles(20);
    if (miss_count < 1) $fatal(1, "missed beat flag not asserted");

    // 5) Quality threshold rejects low-quality candidates.
    apply_default_cfg();
    cfg_q_amp_w = 8'd0;
    cfg_q_slope_w = 8'd0;
    cfg_q_min_accept = 8'd1;
    reset_dut();
    beat_count = 0;
    idle_cycles(50);
    emit_peak(700);
    idle_cycles(50);
    if (beat_count != 0) $fatal(1, "quality gating failed: beat should be rejected");

    // Restore quality acceptance and force one accepted beat.
    cfg_q_amp_w = 8'd4;
    cfg_q_slope_w = 8'd2;
    cfg_q_min_accept = 8'd5;
    emit_peak(700);
    idle_cycles(10);
    if (beat_count == 0) $fatal(1, "quality restore failed: beat not accepted");

    // 6) Invalid flag after prolonged no-beat timeout.
    apply_default_cfg();
    reset_dut();
    emit_peak(700);
    idle_cycles(20);
    idle_cycles(2100);
    if (!ppg_invalid) $fatal(1, "ppg_invalid not asserted after timeout");

    // 7) Bypass mode should suppress beats.
    apply_default_cfg();
    cfg_bypass = 1'b1;
    reset_dut();
    beat_count = 0;
    emit_peak(800);
    idle_cycles(20);
    if (beat_count != 0) $fatal(1, "bypass mode still produced beats");

    // 8) Delta HR output: first RR delta=0, then positive and negative deltas.
    apply_default_cfg();
    cfg_rr_min_ticks = 32'd150;
    cfg_rr_max_ticks = 32'd2500;
    reset_dut();
    rr_count = 0;
    emit_peak(700);
    idle_cycles(900);
    emit_peak(700); // first RR
    idle_cycles(20);
    if (rr_count < 1) $fatal(1, "delta-hr: missing first rr");
    if (last_delta_hr !== 17'sd0) $fatal(1, "delta-hr: first rr delta must be 0, got %0d", last_delta_hr);

    idle_cycles(450);
    emit_peak(700); // shorter RR => HR up
    idle_cycles(20);
    if (rr_count < 2) $fatal(1, "delta-hr: missing second rr");
    if (last_delta_hr <= 0) $fatal(1, "delta-hr: expected positive delta, got %0d", last_delta_hr);

    idle_cycles(1300);
    emit_peak(700); // longer RR => HR down
    idle_cycles(20);
    if (rr_count < 3) $fatal(1, "delta-hr: missing third rr");
    if (last_delta_hr >= 0) $fatal(1, "delta-hr: expected negative delta, got %0d", last_delta_hr);

    $display("PASS");
    $finish;
  end

  initial begin
    $dumpfile("ppg_process_tb.vcd");
    $dumpvars(0, ppg_process_tb);
  end

endmodule
