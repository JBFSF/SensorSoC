`timescale 1ns/1ps

module ppg_process #(
    parameter integer SAMPLE_W = 16,
    parameter integer T_W = 32,
    parameter integer X_W = 24,
    parameter integer ENV_W = 24,
    parameter integer COEFF_W = 12,
    parameter integer COEFF_FRAC = 10,
    parameter integer QUALITY_MARGIN_SHIFT = 4,

    // Optional compile-time configuration mode for area reduction.
    parameter integer STATIC_CFG = 0,
    parameter         STATIC_ENABLE = 1'b1,
    parameter         STATIC_BYPASS = 1'b0,
    parameter         STATIC_SIGNED = 1'b0,
    parameter [COEFF_W-1:0] STATIC_LP_BETA = 12'd128,
    parameter [COEFF_W-1:0] STATIC_BASE_ALPHA = 12'd16,
    parameter [ENV_W-1:0]   STATIC_ENV_DECAY = 24'd8,
    parameter         STATIC_ABS_EN = 1'b1,
    parameter [COEFF_W-1:0] STATIC_THR_K = 12'd512,
    parameter [ENV_W-1:0]   STATIC_THR_MIN = 24'd32,
    parameter [T_W-1:0]     STATIC_REFRACT_TICKS = 32'd250,
    parameter [T_W-1:0]     STATIC_RR_MIN_TICKS = 32'd300,
    parameter [T_W-1:0]     STATIC_RR_MAX_TICKS = 32'd2000,
    parameter [7:0]   STATIC_Q_AMP_W = 8'd4,
    parameter [7:0]   STATIC_Q_SLOPE_W = 8'd2,
    parameter [7:0]   STATIC_Q_REFRAC_PENALTY = 8'd24,
    parameter [7:0]   STATIC_Q_MIN_ACCEPT = 8'd10
) (
    input  logic                         clk_i,
    input  logic                         rst_i,

    input  logic [SAMPLE_W-1:0]          ppg_sample_i,
    input  logic                         ppg_valid_i,
    input  logic [T_W-1:0]               ppg_sample_time_i,

    input  logic                         cfg_enable_i,
    input  logic                         cfg_bypass_i,
    input  logic                         cfg_signed_i,         // 0: unsigned sample, 1: signed sample

    input  logic [COEFF_W-1:0]           cfg_lp_beta_i,
    input  logic [COEFF_W-1:0]           cfg_base_alpha_i,
    input  logic [ENV_W-1:0]             cfg_env_decay_i,
    input  logic                         cfg_abs_en_i,

    input  logic [COEFF_W-1:0]           cfg_thr_k_i,
    input  logic [ENV_W-1:0]             cfg_thr_min_i,

    input  logic [T_W-1:0]               cfg_refrac_ticks_i,
    input  logic [T_W-1:0]               cfg_rr_min_ticks_i,
    input  logic [T_W-1:0]               cfg_rr_max_ticks_i,

    input  logic [7:0]                   cfg_q_amp_w_i,
    input  logic [7:0]                   cfg_q_slope_w_i,
    input  logic [7:0]                   cfg_q_refrac_penalty_i,
    input  logic [7:0]                   cfg_q_min_accept_i,

    output logic                          beat_pulse_o,
    output logic                          rr_valid_o,
    output logic                          rr_accepted_o,
    output logic  [T_W-1:0]               rr_interval_o,
    output logic  signed [16:0]           delta_hr_bpm_o,

    output logic  [7:0]                   beat_quality_o,
    output logic                          double_beat_o,
    output logic                          missed_beat_o,
    output logic                          ppg_invalid_o
);

    localparam [COEFF_W-1:0] COEFF_ONE = ({{(COEFF_W-1){1'b0}}, 1'b1} << COEFF_FRAC);

    logic  signed [X_W-1:0] x_lp_r, x_base_r, x_hp_r;
    logic  [ENV_W-1:0]      env_r, thr_r;

    logic  signed [X_W-1:0] xhp_d2_r, xhp_d1_r;
    logic  [ENV_W-1:0]      thr_d1_r;
    logic  [T_W-1:0]        t_d1_r;

    logic  [T_W-1:0] last_beat_time_r;
    logic            have_last_beat_r;
    logic  [15:0]    prev_hr_bpm_r;
    logic            have_prev_hr_r;
    logic            have_init_r;

    function automatic signed [X_W-1:0] sample_to_signed;
        input [SAMPLE_W-1:0] s;
        input                sample_is_signed;
        begin
            if (sample_is_signed) begin
                sample_to_signed = {{(X_W-SAMPLE_W){s[SAMPLE_W-1]}}, s};
            end else begin
                sample_to_signed = $signed({{(X_W-SAMPLE_W){1'b0}}, s});
            end
        end
    endfunction

    function automatic [X_W-1:0] abs_x;
        input signed [X_W-1:0] v;
        begin
            abs_x = v[X_W-1] ? (~v + {{(X_W-1){1'b0}}, 1'b1}) : v;
        end
    endfunction

    logic [T_W-1:0] t_now_w;
    logic [T_W-1:0] elapsed_since_last_w;
    logic in_refrac_w;

    logic                   cfg_enable_w;
    logic                   cfg_bypass_w;
    logic                   cfg_signed_w;
    logic [COEFF_W-1:0]     cfg_lp_beta_w;
    logic [COEFF_W-1:0]     cfg_base_alpha_w;
    logic [ENV_W-1:0]       cfg_env_decay_w;
    logic                   cfg_abs_en_w;
    logic [COEFF_W-1:0]     cfg_thr_k_w;
    logic [ENV_W-1:0]       cfg_thr_min_w;
    logic [T_W-1:0]         cfg_refrac_ticks_w;
    logic [T_W-1:0]         cfg_rr_min_ticks_w;
    logic [T_W-1:0]         cfg_rr_max_ticks_w;
    logic [7:0]             cfg_q_amp_w_w;
    logic [7:0]             cfg_q_slope_w_w;
    logic [7:0]             cfg_q_refrac_penalty_w;
    logic [7:0]             cfg_q_min_accept_w;

    assign cfg_enable_w           = STATIC_CFG ? STATIC_ENABLE : cfg_enable_i;
    assign cfg_bypass_w           = STATIC_CFG ? STATIC_BYPASS : cfg_bypass_i;
    assign cfg_signed_w           = STATIC_CFG ? STATIC_SIGNED : cfg_signed_i;
    assign cfg_lp_beta_w          = STATIC_CFG ? STATIC_LP_BETA : cfg_lp_beta_i;
    assign cfg_base_alpha_w       = STATIC_CFG ? STATIC_BASE_ALPHA : cfg_base_alpha_i;
    assign cfg_env_decay_w        = STATIC_CFG ? STATIC_ENV_DECAY : cfg_env_decay_i;
    assign cfg_abs_en_w           = STATIC_CFG ? STATIC_ABS_EN : cfg_abs_en_i;
    assign cfg_thr_k_w            = STATIC_CFG ? STATIC_THR_K : cfg_thr_k_i;
    assign cfg_thr_min_w          = STATIC_CFG ? STATIC_THR_MIN : cfg_thr_min_i;
    assign cfg_refrac_ticks_w     = STATIC_CFG ? STATIC_REFRACT_TICKS : cfg_refrac_ticks_i;
    assign cfg_rr_min_ticks_w     = STATIC_CFG ? STATIC_RR_MIN_TICKS : cfg_rr_min_ticks_i;
    assign cfg_rr_max_ticks_w     = STATIC_CFG ? STATIC_RR_MAX_TICKS : cfg_rr_max_ticks_i;
    assign cfg_q_amp_w_w          = STATIC_CFG ? STATIC_Q_AMP_W : cfg_q_amp_w_i;
    assign cfg_q_slope_w_w        = STATIC_CFG ? STATIC_Q_SLOPE_W : cfg_q_slope_w_i;
    assign cfg_q_refrac_penalty_w = STATIC_CFG ? STATIC_Q_REFRAC_PENALTY : cfg_q_refrac_penalty_i;
    assign cfg_q_min_accept_w     = STATIC_CFG ? STATIC_Q_MIN_ACCEPT : cfg_q_min_accept_i;

    assign t_now_w = ppg_sample_time_i;
    assign elapsed_since_last_w = t_now_w - last_beat_time_r;
    assign in_refrac_w = have_last_beat_r && (elapsed_since_last_w < cfg_refrac_ticks_w);

    always @(posedge clk_i) begin
        logic signed [X_W-1:0] x_raw_v;
        logic signed [X_W-1:0] lp_err_v;
        logic signed [X_W+COEFF_W-1:0] lp_mul_v;
        logic signed [X_W-1:0] lp_step_v;
        logic signed [X_W-1:0] x_lp_next_v;

        logic signed [X_W-1:0] base_err_v;
        logic signed [X_W+COEFF_W-1:0] base_mul_v;
        logic signed [X_W-1:0] base_step_v;
        logic signed [X_W-1:0] x_base_next_v;

        logic signed [X_W-1:0] x_hp_next_v;
        logic [X_W-1:0] x_mag_v;

        logic [ENV_W-1:0] env_decay_v;
        logic [ENV_W-1:0] env_next_v;

        logic [ENV_W+COEFF_W-1:0] thr_mul_v;
        logic [ENV_W-1:0] thr_scaled_v;
        logic [ENV_W-1:0] thr_next_v;

        logic localmax_candidate_v;

        logic [X_W-1:0] peak_abs_v;
        logic signed [X_W-1:0] slope_signed_v;
        logic [X_W-1:0] slope_mag_v;
        logic [X_W-1:0] amp_margin_v;
        logic [X_W-1:0] slope_margin_v;
        logic [31:0] amp_term_v;
        logic [31:0] slope_term_v;
        logic [31:0] quality_raw_v;
        logic [31:0] quality_minus_pen_v;
        logic [7:0]  quality_v;
        logic [7:0]  penalty_v;
        logic        quality_ok_v;

        logic [T_W-1:0] beat_time_v;
        logic [T_W-1:0] rr_v;
        logic [15:0]    hr_bpm_new_v;
        logic signed [16:0] delta_hr_v;
        logic           accept_v;
        logic           reject_short_rr_v;
        logic           flag_missed_v;
        logic           rr_should_pulse_v;

        if (rst_i) begin
            beat_pulse_o      <= 1'b0;
            rr_valid_o        <= 1'b0;
            rr_accepted_o     <= 1'b0;
            rr_interval_o     <= {T_W{1'b0}};
            delta_hr_bpm_o    <= 17'sd0;

            beat_quality_o    <= 8'd0;
            double_beat_o     <= 1'b0;
            missed_beat_o     <= 1'b0;
            ppg_invalid_o     <= 1'b0;

            x_lp_r            <= '0;
            x_base_r          <= '0;
            x_hp_r            <= '0;
            env_r             <= '0;
            thr_r             <= '0;
            xhp_d2_r          <= '0;
            xhp_d1_r          <= '0;
            thr_d1_r          <= '0;
            t_d1_r            <= '0;


            last_beat_time_r  <= {T_W{1'b0}};
            have_last_beat_r  <= 1'b0;
            prev_hr_bpm_r     <= 16'd0;
            have_prev_hr_r    <= 1'b0;
            have_init_r       <= 1'b0;
        end else begin
            beat_pulse_o   <= 1'b0;
            rr_valid_o     <= 1'b0;
            rr_accepted_o <= 1'b0;
            double_beat_o  <= 1'b0;
            missed_beat_o  <= 1'b0;

            if (!cfg_enable_w || cfg_bypass_w) begin
                ppg_invalid_o <= 1'b0;
                have_init_r <= 1'b0;
            end else if (have_last_beat_r && (elapsed_since_last_w > cfg_rr_max_ticks_w)) begin
                ppg_invalid_o <= 1'b1;
            end

            if (ppg_valid_i) begin
                x_raw_v = sample_to_signed(ppg_sample_i, cfg_signed_w);
                if (!have_init_r) begin
                    // Seed filters to first sample to avoid large startup transients
                    // that can keep threshold too high for a long time.
                    x_lp_r <= x_raw_v;
                    x_base_r <= x_raw_v;
                    x_hp_r <= '0;
                    env_r <= '0;
                    thr_r <= cfg_thr_min_w;
                    xhp_d2_r <= '0;
                    xhp_d1_r <= '0;
                    thr_d1_r <= cfg_thr_min_w;
                    t_d1_r <= t_now_w;
                    beat_quality_o <= 8'd0;
                    have_init_r <= 1'b1;
                end else begin

                lp_err_v = x_raw_v - x_lp_r;
                if (cfg_lp_beta_w == {COEFF_W{1'b0}}) begin
                    x_lp_next_v = x_lp_r;
                end else if (cfg_lp_beta_w >= COEFF_ONE) begin
                    x_lp_next_v = x_raw_v;
                end else begin
                    lp_mul_v = lp_err_v * $signed({1'b0, cfg_lp_beta_w});
                    lp_step_v = lp_mul_v >>> COEFF_FRAC;
                    x_lp_next_v = x_lp_r + lp_step_v;
                end

                base_err_v = x_lp_next_v - x_base_r;
                if (cfg_base_alpha_w == {COEFF_W{1'b0}}) begin
                    x_base_next_v = x_base_r;
                end else if (cfg_base_alpha_w >= COEFF_ONE) begin
                    x_base_next_v = x_lp_next_v;
                end else begin
                    base_mul_v = base_err_v * $signed({1'b0, cfg_base_alpha_w});
                    base_step_v = base_mul_v >>> COEFF_FRAC;
                    x_base_next_v = x_base_r + base_step_v;
                end

                x_hp_next_v = x_lp_next_v - x_base_next_v;
                x_mag_v = cfg_abs_en_w ? abs_x(x_hp_next_v) : (x_hp_next_v[X_W-1] ? {X_W{1'b0}} : x_hp_next_v[X_W-1:0]);

                env_decay_v = (env_r > cfg_env_decay_w) ? (env_r - cfg_env_decay_w) : {ENV_W{1'b0}};
                env_next_v  = (x_mag_v[ENV_W-1:0] > env_decay_v) ? x_mag_v[ENV_W-1:0] : env_decay_v;

                thr_mul_v = env_next_v * cfg_thr_k_w;
                thr_scaled_v = thr_mul_v >>> COEFF_FRAC;
                thr_next_v = (thr_scaled_v > cfg_thr_min_w) ? thr_scaled_v : cfg_thr_min_w;

                localmax_candidate_v = (xhp_d1_r > xhp_d2_r) &&
                                       (xhp_d1_r > x_hp_next_v) &&
                                       (!xhp_d1_r[X_W-1]) &&
                                       (xhp_d1_r[X_W-1:0] > thr_d1_r);

                peak_abs_v = abs_x(xhp_d1_r);
                slope_signed_v = xhp_d1_r - xhp_d2_r;
                beat_time_v = t_d1_r;

                slope_mag_v = slope_signed_v[X_W-1] ? {X_W{1'b0}} : slope_signed_v[X_W-1:0];
                amp_margin_v = (peak_abs_v > thr_d1_r) ? (peak_abs_v - thr_d1_r) : {X_W{1'b0}};
                slope_margin_v = slope_mag_v;

                amp_term_v = cfg_q_amp_w_w * (amp_margin_v >> QUALITY_MARGIN_SHIFT);
                slope_term_v = cfg_q_slope_w_w * (slope_margin_v >> QUALITY_MARGIN_SHIFT);
                quality_raw_v = amp_term_v + slope_term_v;

                penalty_v = ((have_last_beat_r) &&
                             (elapsed_since_last_w < (cfg_refrac_ticks_w + (cfg_refrac_ticks_w >> 2)))) ?
                             cfg_q_refrac_penalty_w : 8'd0;

                quality_minus_pen_v = (quality_raw_v > penalty_v) ? (quality_raw_v - penalty_v) : 32'd0;
                quality_v = (quality_minus_pen_v > 32'd255) ? 8'd255 : quality_minus_pen_v[7:0];
                quality_ok_v = (quality_v >= cfg_q_min_accept_w);

                accept_v = 1'b0;
                reject_short_rr_v = 1'b0;
                flag_missed_v = 1'b0;
                rr_should_pulse_v = 1'b0;
                rr_v = beat_time_v - last_beat_time_r;
                hr_bpm_new_v = prev_hr_bpm_r;
                delta_hr_v = 17'sd0;

                if (cfg_enable_w && !cfg_bypass_w && localmax_candidate_v && !in_refrac_w && quality_ok_v) begin
                    if (!have_last_beat_r) begin
                        accept_v = 1'b1;
                    end else if (rr_v < cfg_rr_min_ticks_w) begin
                        reject_short_rr_v = 1'b1;
                    end else begin
                        accept_v = 1'b1;
                        rr_should_pulse_v = 1'b1;
                        if (rr_v > cfg_rr_max_ticks_w) begin
                            flag_missed_v = 1'b1;
                        end
                    end
                end

                if (localmax_candidate_v && !in_refrac_w) begin
                    beat_quality_o <= quality_v;
                end

                if (reject_short_rr_v) begin
                    double_beat_o <= 1'b1;
                end

                if (accept_v) begin
                    beat_pulse_o <= 1'b1;
                    last_beat_time_r <= beat_time_v;
                    have_last_beat_r <= 1'b1;
                    ppg_invalid_o <= 1'b0;
                end

                if (rr_should_pulse_v) begin
                    rr_valid_o <= 1'b1;
                    rr_accepted_o <= !reject_short_rr_v && (rr_v <= cfg_rr_max_ticks_w);
                    rr_interval_o <= rr_v;
                    if (rr_v != {T_W{1'b0}}) begin
                        hr_bpm_new_v = 16'(32'd60000 / rr_v);
                        if (have_prev_hr_r) begin
                            delta_hr_v = $signed({1'b0, hr_bpm_new_v}) - $signed({1'b0, prev_hr_bpm_r});
                        end else begin
                            delta_hr_v = 17'sd0;
                        end
                        delta_hr_bpm_o <= delta_hr_v;
                        prev_hr_bpm_r <= hr_bpm_new_v;
                        have_prev_hr_r <= 1'b1;
                    end
                end

                if (flag_missed_v) begin
                    missed_beat_o <= 1'b1;
                end

                x_lp_r <= x_lp_next_v;
                x_base_r <= x_base_next_v;
                x_hp_r <= x_hp_next_v;
                env_r <= env_next_v;
                thr_r <= thr_next_v;

                xhp_d2_r <= xhp_d1_r;
                xhp_d1_r <= x_hp_next_v;
                thr_d1_r <= thr_next_v;
                t_d1_r <= t_now_w;
                end

            end
        end
    end

endmodule
