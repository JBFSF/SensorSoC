`timescale 1ns/1ps

module rmssd_engine #(
    parameter integer RR_W = 32,
    parameter integer ACC_W = 64,
    parameter integer CNT_W = 16,
    parameter integer MIN_RR_COUNT = 1
) (
    input  logic                         clk_i,
    input  logic                         rst_i,

    input  logic [RR_W-1:0]              rr_interval_i,
    input  logic                         rr_valid_i,
    input  logic                         rr_accepted_i,
    input  logic                         epoch_end_i,

    output logic  [RR_W-1:0]              rmssd_epoch_o,
    output logic                          rmssd_valid_o,
    output logic  [CNT_W-1:0]             rr_diff_count_o
);

    logic [RR_W-1:0] prev_rr_r;
    logic            have_prev_rr_r;
    logic [ACC_W-1:0] sum_sq_r;
    logic [CNT_W-1:0] diff_cnt_r;

    function automatic [RR_W-1:0] isqrt_u64;
        input [63:0] x;
        logic [63:0] op;
        logic [63:0] res;
        logic [63:0] one;
        integer i;
        begin
            op  = x;
            res = 64'd0;
            one = 64'h4000_0000_0000_0000; // highest power-of-four <= 2^64

            for (i = 0; i < 32; i = i + 1) begin
                if (one > op) one = one >> 2;
            end

            for (i = 0; i < 32; i = i + 1) begin
                if (one == 64'd0) begin
                    // no-op
                end else if (op >= (res + one)) begin
                    op  = op - (res + one);
                    res = (res >> 1) + one;
                    one = one >> 2;
                end else begin
                    res = res >> 1;
                    one = one >> 2;
                end
            end
            isqrt_u64 = res[RR_W-1:0];
        end
    endfunction

    always @(posedge clk_i) begin
        logic signed [RR_W:0] diff_v;
        logic [ACC_W-1:0] diff_sq_v;
        logic [ACC_W-1:0] mean_sq_v;
        logic [RR_W-1:0] rmssd_v;
        if (rst_i) begin
            prev_rr_r <= {RR_W{1'b0}};
            have_prev_rr_r <= 1'b0;
            sum_sq_r <= {ACC_W{1'b0}};
            diff_cnt_r <= {CNT_W{1'b0}};

            rmssd_epoch_o <= {RR_W{1'b0}};
            rmssd_valid_o <= 1'b0;
            rr_diff_count_o <= {CNT_W{1'b0}};
        end else begin
            rmssd_valid_o <= 1'b0;

            if (rr_valid_i && rr_accepted_i) begin
                if (have_prev_rr_r) begin
                    diff_v = $signed({1'b0, rr_interval_i}) - $signed({1'b0, prev_rr_r});
                    diff_sq_v = diff_v * diff_v;
                    sum_sq_r <= sum_sq_r + diff_sq_v;
                    diff_cnt_r <= diff_cnt_r + 1'b1;
                end
                prev_rr_r <= rr_interval_i;
                have_prev_rr_r <= 1'b1;
            end

            if (epoch_end_i) begin
                rr_diff_count_o <= diff_cnt_r;
                if (diff_cnt_r >= MIN_RR_COUNT[CNT_W-1:0]) begin
                    mean_sq_v = sum_sq_r / diff_cnt_r;
                    rmssd_v = isqrt_u64(mean_sq_v[63:0]);
                    rmssd_epoch_o <= rmssd_v;
                    rmssd_valid_o <= 1'b1;
                end else begin
                    rmssd_epoch_o <= {RR_W{1'b0}};
                end

                sum_sq_r <= {ACC_W{1'b0}};
                diff_cnt_r <= {CNT_W{1'b0}};
                have_prev_rr_r <= 1'b0;
            end
        end
    end

endmodule


