`timescale 1ns/1ps

module mssd_engine #(
    parameter integer RR_W = 16,
    parameter integer ACC_W = 40,
    parameter integer CNT_W = 16,
    parameter integer MIN_RR_COUNT = 1,
    parameter integer MAX_DIFF_COUNT = 64
) (
    input  logic                         clk_i,
    input  logic                         rst_i,
    input  logic                         en_i,

    input  logic [RR_W-1:0]              rr_interval_i,
    input  logic                         rr_valid_i,
    input  logic                         rr_accepted_i,
    input  logic                         epoch_end_i,

    output logic [RR_W-1:0]              mssd_epoch_o,
    output logic                         mssd_valid_o,
    output logic [CNT_W-1:0]             rr_diff_count_o
);

    logic [RR_W-1:0]  prev_rr_r;
    logic             have_prev_rr_r;
    logic [ACC_W-1:0] sum_sq_r;
    logic [CNT_W-1:0] diff_cnt_r;

    always @(posedge clk_i) begin
        logic signed [RR_W:0] diff_v;
        logic [ACC_W-1:0]     diff_sq_v;
        logic [15:0]          sum_sq_clip_v;

        if (rst_i) begin
            prev_rr_r       <= {RR_W{1'b0}};
            have_prev_rr_r  <= 1'b0;
            sum_sq_r        <= {ACC_W{1'b0}};
            diff_cnt_r      <= {CNT_W{1'b0}};

            mssd_epoch_o   <= {RR_W{1'b0}};
            mssd_valid_o   <= 1'b0;
            rr_diff_count_o <= {CNT_W{1'b0}};
        end else if (en_i) begin
            mssd_valid_o <= 1'b0;

            if (rr_valid_i && rr_accepted_i) begin
                if (have_prev_rr_r) begin
                    diff_v    = $signed({1'b0, rr_interval_i}) - $signed({1'b0, prev_rr_r});
                    diff_sq_v = diff_v * diff_v;
                    sum_sq_r  <= sum_sq_r + diff_sq_v;

                    if (diff_cnt_r < MAX_DIFF_COUNT[CNT_W-1:0])
                        diff_cnt_r <= diff_cnt_r + 1'b1;
                end

                prev_rr_r      <= rr_interval_i;
                have_prev_rr_r <= 1'b1;
            end

            if (epoch_end_i) begin
                rr_diff_count_o <= diff_cnt_r;

                if (diff_cnt_r >= MIN_RR_COUNT[CNT_W-1:0]) begin
                    if (|sum_sq_r[ACC_W-1:16])
                        sum_sq_clip_v = 16'hFFFF;
                    else
                        sum_sq_clip_v = sum_sq_r[15:0];

                    mssd_epoch_o <= sum_sq_clip_v;
                    mssd_valid_o <= 1'b1;
                end else begin
                    mssd_epoch_o <= {RR_W{1'b0}};
                end

                sum_sq_r       <= {ACC_W{1'b0}};
                diff_cnt_r     <= {CNT_W{1'b0}};
                have_prev_rr_r <= 1'b0;
            end
        end
    end

endmodule
