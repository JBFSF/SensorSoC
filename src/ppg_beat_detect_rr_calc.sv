`timescale 1ns/1ps

module ppg_beat_detect_rr_calc #(
    parameter integer SAMPLE_W = 16,
    parameter integer T_W = 32,
    parameter integer X_W = 24,
    parameter integer ENV_W = 24,
    parameter integer COEFF_W = 12,
    parameter integer COEFF_FRAC = 10,
    parameter integer QUALITY_MARGIN_SHIFT = 4
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
    input  logic                         cfg_peak_mode_i,      // 0: local-max, 1: rising-edge

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

    assign t_now_w = ppg_sample_time_i;
    assign elapsed_since_last_w = t_now_w - last_beat_time_r;
    assign in_refrac_w = have_last_beat_r && (elapsed_since_last_w < cfg_refrac_ticks_i);

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
        logic rise_candidate_v;
        logic candidate_v;

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

            if (!cfg_enable_i || cfg_bypass_i) begin
                ppg_invalid_o <= 1'b0;
                have_init_r <= 1'b0;
            end else if (have_last_beat_r && (elapsed_since_last_w > cfg_rr_max_ticks_i)) begin
                ppg_invalid_o <= 1'b1;
            end

            if (ppg_valid_i) begin
                x_raw_v = sample_to_signed(ppg_sample_i, cfg_signed_i);
                if (!have_init_r) begin
                    // Seed filters to first sample to avoid large startup transients
                    // that can keep threshold too high for a long time.
                    x_lp_r <= x_raw_v;
                    x_base_r <= x_raw_v;
                    x_hp_r <= '0;
                    env_r <= '0;
                    thr_r <= cfg_thr_min_i;
                    xhp_d2_r <= '0;
                    xhp_d1_r <= '0;
                    thr_d1_r <= cfg_thr_min_i;
                    t_d1_r <= t_now_w;
                    beat_quality_o <= 8'd0;
                    have_init_r <= 1'b1;
                end else begin

                lp_err_v = x_raw_v - x_lp_r;
                if (cfg_lp_beta_i == {COEFF_W{1'b0}}) begin
                    x_lp_next_v = x_lp_r;
                end else if (cfg_lp_beta_i >= COEFF_ONE) begin
                    x_lp_next_v = x_raw_v;
                end else begin
                    lp_mul_v = lp_err_v * $signed({1'b0, cfg_lp_beta_i});
                    lp_step_v = lp_mul_v >>> COEFF_FRAC;
                    x_lp_next_v = x_lp_r + lp_step_v;
                end

                base_err_v = x_lp_next_v - x_base_r;
                if (cfg_base_alpha_i == {COEFF_W{1'b0}}) begin
                    x_base_next_v = x_base_r;
                end else if (cfg_base_alpha_i >= COEFF_ONE) begin
                    x_base_next_v = x_lp_next_v;
                end else begin
                    base_mul_v = base_err_v * $signed({1'b0, cfg_base_alpha_i});
                    base_step_v = base_mul_v >>> COEFF_FRAC;
                    x_base_next_v = x_base_r + base_step_v;
                end

                x_hp_next_v = x_lp_next_v - x_base_next_v;
                x_mag_v = cfg_abs_en_i ? abs_x(x_hp_next_v) : (x_hp_next_v[X_W-1] ? {X_W{1'b0}} : x_hp_next_v[X_W-1:0]);

                env_decay_v = (env_r > cfg_env_decay_i) ? (env_r - cfg_env_decay_i) : {ENV_W{1'b0}};
                env_next_v  = (x_mag_v[ENV_W-1:0] > env_decay_v) ? x_mag_v[ENV_W-1:0] : env_decay_v;

                thr_mul_v = env_next_v * cfg_thr_k_i;
                thr_scaled_v = thr_mul_v >>> COEFF_FRAC;
                thr_next_v = (thr_scaled_v > cfg_thr_min_i) ? thr_scaled_v : cfg_thr_min_i;

                localmax_candidate_v = (xhp_d1_r > xhp_d2_r) &&
                                       (xhp_d1_r > x_hp_next_v) &&
                                       (!xhp_d1_r[X_W-1]) &&
                                       (xhp_d1_r[X_W-1:0] > thr_d1_r);

                rise_candidate_v = (!xhp_d1_r[X_W-1]) &&
                                   (xhp_d1_r[X_W-1:0] <= thr_d1_r) &&
                                   (!x_hp_next_v[X_W-1]) &&
                                   (x_hp_next_v[X_W-1:0] > thr_next_v);

                candidate_v = cfg_peak_mode_i ? rise_candidate_v : localmax_candidate_v;

                if (cfg_peak_mode_i) begin
                    peak_abs_v = x_mag_v;
                    slope_signed_v = x_hp_next_v - xhp_d1_r;
                    beat_time_v = t_now_w;
                end else begin
                    peak_abs_v = abs_x(xhp_d1_r);
                    slope_signed_v = xhp_d1_r - xhp_d2_r;
                    beat_time_v = t_d1_r;
                end

                slope_mag_v = slope_signed_v[X_W-1] ? {X_W{1'b0}} : slope_signed_v[X_W-1:0];
                amp_margin_v = (peak_abs_v > thr_d1_r) ? (peak_abs_v - thr_d1_r) : {X_W{1'b0}};
                slope_margin_v = slope_mag_v;

                amp_term_v = cfg_q_amp_w_i * (amp_margin_v >> QUALITY_MARGIN_SHIFT);
                slope_term_v = cfg_q_slope_w_i * (slope_margin_v >> QUALITY_MARGIN_SHIFT);
                quality_raw_v = amp_term_v + slope_term_v;

                penalty_v = ((have_last_beat_r) &&
                             (elapsed_since_last_w < (cfg_refrac_ticks_i + (cfg_refrac_ticks_i >> 2)))) ?
                             cfg_q_refrac_penalty_i : 8'd0;

                quality_minus_pen_v = (quality_raw_v > penalty_v) ? (quality_raw_v - penalty_v) : 32'd0;
                quality_v = (quality_minus_pen_v > 32'd255) ? 8'd255 : quality_minus_pen_v[7:0];
                quality_ok_v = (quality_v >= cfg_q_min_accept_i);

                accept_v = 1'b0;
                reject_short_rr_v = 1'b0;
                flag_missed_v = 1'b0;
                rr_should_pulse_v = 1'b0;
                rr_v = beat_time_v - last_beat_time_r;
                hr_bpm_new_v = prev_hr_bpm_r;
                delta_hr_v = 17'sd0;

                if (cfg_enable_i && !cfg_bypass_i && candidate_v && !in_refrac_w && quality_ok_v) begin
                    if (!have_last_beat_r) begin
                        accept_v = 1'b1;
                    end else if (rr_v < cfg_rr_min_ticks_i) begin
                        reject_short_rr_v = 1'b1;
                    end else begin
                        accept_v = 1'b1;
                        rr_should_pulse_v = 1'b1;
                        if (rr_v > cfg_rr_max_ticks_i) begin
                            flag_missed_v = 1'b1;
                        end
                    end
                end

                if (candidate_v && !in_refrac_w) begin
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
                    rr_accepted_o <= !reject_short_rr_v && (rr_v <= cfg_rr_max_ticks_i);
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
