`timescale 1ns/1ps

module ppg_fifo_reader #(
    parameter [6:0]  I2C_ADDR = 7'h64,
    parameter [7:0]  REG_STATUS = 8'h00,
    parameter [7:0]  REG_FIFO_THRESH = 8'h06,
    parameter [7:0]  REG_FIFO_ACCESS_ENA = 8'h5F,
    parameter [7:0]  REG_FIFO_ACCESS = 8'h60,
    parameter integer SAMPLE_W = 16,
    parameter integer STATUS_BYTES = 2,
    parameter integer COUNT_W = 8,
    parameter integer WATERMARK = 8,
    parameter integer MAX_BURST_SAMPLES = 32,
    parameter integer PACKET_BYTES = 2,
    parameter integer POLL_PERIOD = 1_000_000,
    parameter integer TIMESTAMP_PER_SAMPLE = 1,
    parameter integer SAMPLE_PERIOD_TICKS = 10
)(
    input  logic                  clk_i,
    input  logic                  rst_i,
    input  logic                  en_i,

    input  logic [31:0]           t_now,

    // i2c command interface
    output logic                   i2c_cmd_valid,
    input  logic                  i2c_cmd_ready,
    output logic  [6:0]            i2c_cmd_addr,
    output logic  [7:0]            i2c_cmd_reg,
    output logic  [7:0]            i2c_cmd_len,
    output logic                   i2c_cmd_write,
    output logic  [7:0]            i2c_cmd_wdata,

    // i2c response interface
    input  logic                  i2c_rsp_valid,
    input  logic [7:0]            i2c_rsp_data,
    input  logic                  i2c_rsp_last,
    input  logic                  i2c_rsp_err,
    output logic                   i2c_rsp_ready,

    // output samples
    output logic  [SAMPLE_W-1:0]   ppg_sample,
    output logic                   ppg_sample_valid,
    output logic  [31:0]           ppg_sample_time,

    output logic                   fifo_overflow_flag,
    output logic                   fifo_empty_flag,
    output logic                   i2c_error_flag
);

    localparam integer STATUS_W = 16;
    localparam integer THRESH_W = 16;
    localparam integer SAMPLE_BYTES = (SAMPLE_W + 7) / 8;
    localparam integer PACKET_BYTES_EFF = (PACKET_BYTES <= 0) ? 1 : PACKET_BYTES;
    localparam integer MAX_BURST_BYTES = MAX_BURST_SAMPLES * SAMPLE_BYTES;
    localparam [7:0] FIFO_EN_BITVAL = 8'h01;

    typedef enum logic [3:0] {
        ST_POLL = 4'd0,
        ST_STATUS_CMD = 4'd1,
        ST_STATUS_RECV = 4'd2,
        ST_THRESH_CMD = 4'd3,
        ST_THRESH_RECV = 4'd4,
        ST_DECIDE = 4'd5,
        ST_ENA1_CMD = 4'd6,
        ST_ENA2_CMD = 4'd7,
        ST_DATA_CMD = 4'd8,
        ST_DATA_RECV = 4'd9,
        ST_DIS_CMD = 4'd10
    } state_t;

    state_t state_r;

    logic [31:0] poll_cnt_r;
    logic [STATUS_W-1:0] status_shift_r;
    logic [$clog2(STATUS_BYTES+1)-1:0] status_byte_idx_r;
    logic [THRESH_W-1:0] thresh_shift_r;
    logic [$clog2(3)-1:0] thresh_byte_idx_r;

    logic [SAMPLE_W-1:0] sample_shift_r;
    logic [$clog2(SAMPLE_BYTES+1)-1:0] sample_byte_idx_r;

    logic [15:0] bytes_left_r;
    logic [15:0] read_bytes_r;
    logic [15:0] samples_left_r;
    logic [31:0] burst_time_r;
    logic [31:0] sample_time_next_r;
    logic [31:0] last_sample_time_r;

    logic poll_hit;

    logic overflow_w;
    logic [7:0] fifo_bytes_avail_w;
    logic [5:0] fifo_thresh_words_w;
    logic [5:0] fifo_thresh_words_eff_w;
    logic [15:0] fifo_thresh_bytes_w;
    logic fifo_empty_w;

    logic [15:0] fifo_bytes_avail_ext_w;
    logic [15:0] read_bytes_pre_w;
    logic [15:0] read_bytes_pkt_w;
    logic [15:0] read_samples_w;
    logic should_read_w;

    assign poll_hit = (poll_cnt_r == (POLL_PERIOD - 1));
    assign overflow_w = status_shift_r[7];
    assign fifo_bytes_avail_w = status_shift_r[15:8];
    assign fifo_thresh_words_w = thresh_shift_r[13:8];
    assign fifo_thresh_words_eff_w = (fifo_thresh_words_w != 6'd0) ?
                                     fifo_thresh_words_w :
                                     ((WATERMARK > 63) ? 6'd63 : WATERMARK[5:0]);
    assign fifo_thresh_bytes_w = {9'd0, fifo_thresh_words_eff_w, 1'b0};
    assign fifo_empty_w = (fifo_bytes_avail_w == 8'd0);
    assign fifo_bytes_avail_ext_w = {8'd0, fifo_bytes_avail_w};
    assign read_bytes_pre_w =
        (fifo_bytes_avail_ext_w > MAX_BURST_BYTES[15:0]) ? MAX_BURST_BYTES[15:0] : fifo_bytes_avail_ext_w;
    assign read_bytes_pkt_w = (read_bytes_pre_w / PACKET_BYTES_EFF) * PACKET_BYTES_EFF;
    assign read_samples_w = read_bytes_pkt_w / SAMPLE_BYTES;
    assign should_read_w = (fifo_bytes_avail_ext_w >= fifo_thresh_bytes_w) &&
                           (read_bytes_pkt_w >= PACKET_BYTES_EFF);

    always @(posedge clk_i) begin
        if (rst_i) begin
            state_r <= ST_POLL;
            poll_cnt_r <= 32'd0;

            i2c_cmd_valid <= 1'b0;
            i2c_cmd_addr <= I2C_ADDR;
            i2c_cmd_reg <= 8'h00;
            i2c_cmd_len <= 8'd0;
            i2c_cmd_write <= 1'b0;
            i2c_cmd_wdata <= 8'd0;

            i2c_rsp_ready <= 1'b0;

            status_shift_r <= {STATUS_W{1'b0}};
            status_byte_idx_r <= '0;
            thresh_shift_r <= {THRESH_W{1'b0}};
            thresh_byte_idx_r <= '0;

            sample_shift_r <= {SAMPLE_W{1'b0}};
            sample_byte_idx_r <= '0;
            bytes_left_r <= 16'd0;
            read_bytes_r <= 16'd0;
            samples_left_r <= 16'd0;
            burst_time_r <= 32'd0;
            sample_time_next_r <= 32'd0;
            last_sample_time_r <= 32'd0;

            ppg_sample <= {SAMPLE_W{1'b0}};
            ppg_sample_valid <= 1'b0;
            ppg_sample_time <= 32'd0;

            fifo_overflow_flag <= 1'b0;
            fifo_empty_flag <= 1'b0;
            i2c_error_flag <= 1'b0;
        end else if (en_i) begin
            ppg_sample_valid <= 1'b0;
            i2c_cmd_valid <= 1'b0;
            i2c_cmd_write <= 1'b0;
            i2c_cmd_wdata <= 8'd0;
            i2c_rsp_ready <= 1'b0;

            case (state_r)
                ST_POLL: begin
                    if (poll_hit) begin
                        poll_cnt_r <= 32'd0;
                        state_r <= ST_STATUS_CMD;
                    end else begin
                        poll_cnt_r <= poll_cnt_r + 32'd1;
                    end
                end

                ST_STATUS_CMD: begin
                    i2c_cmd_valid <= 1'b1;
                    i2c_cmd_addr <= I2C_ADDR;
                    i2c_cmd_reg <= REG_STATUS;
                    i2c_cmd_len <= 8'd2;
                    if (i2c_cmd_ready) begin
                        status_shift_r <= {STATUS_W{1'b0}};
                        status_byte_idx_r <= '0;
                        state_r <= ST_STATUS_RECV;
                    end
                end

                ST_STATUS_RECV: begin
                    i2c_rsp_ready <= 1'b1;
                    if (i2c_rsp_valid) begin
                        if (i2c_rsp_err) begin
                            i2c_error_flag <= 1'b1;
                            state_r <= ST_POLL;
                        end else begin
                            begin
                                logic [STATUS_W-1:0] status_next;
                                status_next = status_shift_r | ({{(STATUS_W-8){1'b0}}, i2c_rsp_data} << (status_byte_idx_r * 8));
                                status_shift_r <= status_next;
                                status_byte_idx_r <= status_byte_idx_r + 1'b1;
                                if ((status_byte_idx_r == (STATUS_BYTES-1)) || i2c_rsp_last) begin
                                    fifo_overflow_flag <= fifo_overflow_flag | status_next[7];
                                    fifo_empty_flag <= (status_next[15:8] == 8'd0);
                                    state_r <= ST_THRESH_CMD;
                                end
                            end
                        end
                    end
                end

                ST_THRESH_CMD: begin
                    i2c_cmd_valid <= 1'b1;
                    i2c_cmd_addr <= I2C_ADDR;
                    i2c_cmd_reg <= REG_FIFO_THRESH;
                    i2c_cmd_len <= 8'd2;
                    if (i2c_cmd_ready) begin
                        thresh_shift_r <= {THRESH_W{1'b0}};
                        thresh_byte_idx_r <= '0;
                        state_r <= ST_THRESH_RECV;
                    end
                end

                ST_THRESH_RECV: begin
                    i2c_rsp_ready <= 1'b1;
                    if (i2c_rsp_valid) begin
                        if (i2c_rsp_err) begin
                            i2c_error_flag <= 1'b1;
                            state_r <= ST_POLL;
                        end else begin
                            begin
                                logic [THRESH_W-1:0] thresh_next;
                                thresh_next = thresh_shift_r | ({{(THRESH_W-8){1'b0}}, i2c_rsp_data} << (thresh_byte_idx_r * 8));
                                thresh_shift_r <= thresh_next;
                                thresh_byte_idx_r <= thresh_byte_idx_r + 1'b1;
                                if ((thresh_byte_idx_r == 2-1) || i2c_rsp_last) begin
                                    state_r <= ST_DECIDE;
                                end
                            end
                        end
                    end
                end

                ST_DECIDE: begin
                    if (should_read_w) begin
                        logic [31:0] backfill_v;
                        logic [31:0] start_time_v;
                        logic [31:0] min_start_v;
                        read_bytes_r <= read_bytes_pkt_w;
                        bytes_left_r <= read_bytes_pkt_w;
                        samples_left_r <= read_samples_w;
                        sample_shift_r <= {SAMPLE_W{1'b0}};
                        sample_byte_idx_r <= '0;
                        if (TIMESTAMP_PER_SAMPLE == 0) begin
                            burst_time_r <= t_now;
                        end else begin
                            if (read_samples_w > 16'd1) begin
                                backfill_v = (read_samples_w - 16'd1) * SAMPLE_PERIOD_TICKS[31:0];
                            end else begin
                                backfill_v = 32'd0;
                            end
                            start_time_v = (t_now > backfill_v) ? (t_now - backfill_v) : 32'd0;
                            if (last_sample_time_r != 32'd0) begin
                                min_start_v = last_sample_time_r + SAMPLE_PERIOD_TICKS[31:0];
                                if (start_time_v < min_start_v) begin
                                    start_time_v = min_start_v;
                                end
                            end
                            sample_time_next_r <= start_time_v;
                        end
                        state_r <= ST_ENA1_CMD;
                    end else begin
                        state_r <= ST_POLL;
                    end
                end

                ST_ENA1_CMD: begin
                    i2c_cmd_valid <= 1'b1;
                    i2c_cmd_addr <= I2C_ADDR;
                    i2c_cmd_reg <= REG_FIFO_ACCESS_ENA;
                    i2c_cmd_len <= 8'd1;
                    i2c_cmd_write <= 1'b1;
                    i2c_cmd_wdata <= FIFO_EN_BITVAL;
                    if (i2c_cmd_ready) begin
                        state_r <= ST_ENA2_CMD;
                    end
                end

                ST_ENA2_CMD: begin
                    i2c_cmd_valid <= 1'b1;
                    i2c_cmd_addr <= I2C_ADDR;
                    i2c_cmd_reg <= REG_FIFO_ACCESS_ENA;
                    i2c_cmd_len <= 8'd1;
                    i2c_cmd_write <= 1'b1;
                    i2c_cmd_wdata <= FIFO_EN_BITVAL;
                    if (i2c_cmd_ready) begin
                        state_r <= ST_DATA_CMD;
                    end
                end

                ST_DATA_CMD: begin
                    i2c_cmd_valid <= 1'b1;
                    i2c_cmd_addr <= I2C_ADDR;
                    i2c_cmd_reg <= REG_FIFO_ACCESS;
                    i2c_cmd_len <= read_bytes_r[7:0];
                    if (i2c_cmd_ready) begin
                        state_r <= ST_DATA_RECV;
                    end
                end

                ST_DATA_RECV: begin
                    i2c_rsp_ready <= 1'b1;
                    if (i2c_rsp_valid) begin
                        if (i2c_rsp_err) begin
                            i2c_error_flag <= 1'b1;
                            state_r <= ST_DIS_CMD;
                        end else begin
                            sample_shift_r <= sample_shift_r | ({{(SAMPLE_W-8){1'b0}}, i2c_rsp_data} << (sample_byte_idx_r * 8));
                            sample_byte_idx_r <= sample_byte_idx_r + 1'b1;

                            if ((sample_byte_idx_r == (SAMPLE_BYTES-1)) || i2c_rsp_last) begin
                                ppg_sample <= sample_shift_r | ({{(SAMPLE_W-8){1'b0}}, i2c_rsp_data} << (sample_byte_idx_r * 8));
                                ppg_sample_valid <= 1'b1;
                                if (TIMESTAMP_PER_SAMPLE != 0) begin
                                    ppg_sample_time <= sample_time_next_r;
                                    last_sample_time_r <= sample_time_next_r;
                                    sample_time_next_r <= sample_time_next_r + SAMPLE_PERIOD_TICKS[31:0];
                                end else begin
                                    ppg_sample_time <= burst_time_r;
                                    last_sample_time_r <= burst_time_r;
                                end

                                sample_shift_r <= {SAMPLE_W{1'b0}};
                                sample_byte_idx_r <= '0;

                                if (samples_left_r > 0) samples_left_r <= samples_left_r - 1'b1;
                            end

                            if (bytes_left_r > 0) bytes_left_r <= bytes_left_r - 1'b1;
                            if ((bytes_left_r == 16'd1) || i2c_rsp_last) begin
                                state_r <= ST_DIS_CMD;
                            end
                        end
                    end
                end

                ST_DIS_CMD: begin
                    i2c_cmd_valid <= 1'b1;
                    i2c_cmd_addr <= I2C_ADDR;
                    i2c_cmd_reg <= REG_FIFO_ACCESS_ENA;
                    i2c_cmd_len <= 8'd1;
                    i2c_cmd_write <= 1'b1;
                    i2c_cmd_wdata <= 8'h00;
                    if (i2c_cmd_ready) begin
                        state_r <= ST_POLL;
                        bytes_left_r <= 16'd0;
                        read_bytes_r <= 16'd0;
                        samples_left_r <= 16'd0;
                        sample_shift_r <= {SAMPLE_W{1'b0}};
                        sample_byte_idx_r <= '0;
                        sample_time_next_r <= 32'd0;
                    end
                end

                default: state_r <= ST_POLL;
            endcase
        end
    end

endmodule
