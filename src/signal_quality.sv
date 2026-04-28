`timescale 1ns/1ps

module signal_quality #(
    parameter integer MOTION_W = 16,
    parameter integer CNT_W = 16
) (
    input  logic                     clk_i,
    input  logic                     rst_i,
    input  logic                     en_i,

    input  logic                     epoch_end_i,

    input  logic                     beat_event_i,
    input  logic [7:0]               beat_quality_i,
    input  logic                     double_beat_i,
    input  logic                     missed_beat_i,

    input  logic                     fifo_overflow_i,
    input  logic                     fifo_i2c_error_i,

    input  logic                     motion_valid_i,
    input  logic [MOTION_W-1:0]      motion_intensity_i,

    input  logic [7:0]               cfg_beat_q_min_i,
    input  logic [7:0]               cfg_min_valid_fraction_i,
    input  logic [7:0]               cfg_max_double_i,
    input  logic [7:0]               cfg_max_missed_i,
    input  logic [MOTION_W-1:0]      cfg_motion_hi_th_i,
    input  logic [CNT_W-1:0]         cfg_max_motion_hi_i,

    output logic  [7:0]               invalid_reason_o,
    output logic                      ml_update_gate_o
);

    logic [CNT_W-1:0] beat_cnt_r, good_beat_cnt_r;
    logic [7:0]       double_cnt_r, missed_cnt_r;
    logic [CNT_W-1:0] motion_hi_cnt_r;
    logic             overflow_seen_r, i2c_err_seen_r;

    always @(posedge clk_i) begin
        logic [15:0] frac_num_v;
        logic [7:0]  frac_v;
        logic        no_beats_v, low_frac_v, double_bad_v, missed_bad_v, motion_bad_v;
        if (rst_i) begin
            beat_cnt_r <= '0;
            good_beat_cnt_r <= '0;
            double_cnt_r <= 8'd0;
            missed_cnt_r <= 8'd0;
            motion_hi_cnt_r <= '0;
            overflow_seen_r <= 1'b0;
            i2c_err_seen_r <= 1'b0;

            invalid_reason_o <= 8'd0;
            ml_update_gate_o <= 1'b0;
        end else if (en_i) begin
            if (beat_event_i) begin
                beat_cnt_r <= beat_cnt_r + 1'b1;
                if (beat_quality_i >= cfg_beat_q_min_i) begin
                    good_beat_cnt_r <= good_beat_cnt_r + 1'b1;
                end
            end
            if (double_beat_i && (double_cnt_r != 8'hFF)) double_cnt_r <= double_cnt_r + 1'b1;
            if (missed_beat_i && (missed_cnt_r != 8'hFF)) missed_cnt_r <= missed_cnt_r + 1'b1;
            if (motion_valid_i && (motion_intensity_i > cfg_motion_hi_th_i)) motion_hi_cnt_r <= motion_hi_cnt_r + 1'b1;
            if (fifo_overflow_i) overflow_seen_r <= 1'b1;
            if (fifo_i2c_error_i) i2c_err_seen_r <= 1'b1;

            if (epoch_end_i) begin
                if (beat_cnt_r != {CNT_W{1'b0}}) begin
                    frac_num_v = good_beat_cnt_r * 8'd255;
                    frac_v = frac_num_v / beat_cnt_r;
                end else begin
                    frac_v = 8'd0;
                end
                no_beats_v = (beat_cnt_r == {CNT_W{1'b0}});
                low_frac_v = (frac_v < cfg_min_valid_fraction_i);
                double_bad_v = (double_cnt_r > cfg_max_double_i);
                missed_bad_v = (missed_cnt_r > cfg_max_missed_i);
                motion_bad_v = (motion_hi_cnt_r > cfg_max_motion_hi_i);

                invalid_reason_o[0] <= overflow_seen_r;
                invalid_reason_o[1] <= i2c_err_seen_r;
                invalid_reason_o[2] <= no_beats_v;
                invalid_reason_o[3] <= low_frac_v;
                invalid_reason_o[4] <= double_bad_v;
                invalid_reason_o[5] <= missed_bad_v;
                invalid_reason_o[6] <= motion_bad_v;
                invalid_reason_o[7] <= 1'b0;

                ml_update_gate_o <= !(overflow_seen_r || i2c_err_seen_r || no_beats_v || low_frac_v ||
                                      double_bad_v || missed_bad_v || motion_bad_v);

                beat_cnt_r <= '0;
                good_beat_cnt_r <= '0;
                double_cnt_r <= 8'd0;
                missed_cnt_r <= 8'd0;
                motion_hi_cnt_r <= '0;
                overflow_seen_r <= 1'b0;
                i2c_err_seen_r <= 1'b0;
            end
        end
    end

endmodule


