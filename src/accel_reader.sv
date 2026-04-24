`timescale 1ns/1ps

module accel_reader #(
    parameter [6:0]  I2C_ADDR = 7'h19,
    parameter [7:0]  REG_CTRL1 = 8'h20,
    parameter [7:0]  REG_RANGE = 8'h23,
    parameter [7:0]  REG_OUT_X_L = 8'h28,
    parameter integer READ_LEN = 6,
    parameter integer RSP_TIMEOUT_TICKS = 5000
) (
    input  logic                  clk,
    input  logic                  rst_i,
    input  logic                  en_i,

    input  logic                  cfg_enable_i,
    input  logic                  cfg_init_en_i,
    input  logic [31:0]           cfg_poll_period_ticks_i,
    input  logic [7:0]            cfg_ctrl1_data_i,
    input  logic [7:0]            cfg_range_data_i,

    // I2C command interface
    output logic                   i2c_cmd_valid_o,
    input  logic                  i2c_cmd_ready_i,
    output logic  [6:0]            i2c_cmd_addr_o,
    output logic  [7:0]            i2c_cmd_reg_o,
    output logic  [7:0]            i2c_cmd_len_o,
    output logic                   i2c_cmd_write_o,
    output logic  [7:0]            i2c_cmd_wdata_o,

    // I2C response interface
    input  logic                  i2c_rsp_valid_i,
    input  logic [7:0]            i2c_rsp_data_i,
    input  logic                  i2c_rsp_done_i,
    input  logic                  i2c_rsp_error_i,

    // Output samples
    output logic  signed [15:0]    ax_o,
    output logic  signed [15:0]    ay_o,
    output logic  signed [15:0]    az_o,
    output logic                   accel_valid_o,

    output logic                   init_done_o,
    output logic                   i2c_error_o,
    output logic                   timeout_o,
    output logic                   nack_seen_o
);

    typedef enum logic [2:0] {
        ST_IDLE       = 3'd0,
        ST_INIT1_CMD  = 3'd1,
        ST_INIT1_WAIT = 3'd2,
        ST_INIT2_CMD  = 3'd3,
        ST_INIT2_WAIT = 3'd4,
        ST_READ_CMD   = 3'd5,
        ST_READ_WAIT  = 3'd6
    } state_t;

    localparam integer READ_BUF_W = READ_LEN * 8;
    localparam integer READ_IDX_W = $clog2(READ_LEN + 1);

    state_t state_r;
    logic [31:0] poll_cnt_r;
    logic [31:0] timeout_cnt_r;
    logic [READ_BUF_W-1:0] read_buf_r;
    logic [READ_IDX_W-1:0] read_idx_r;

    logic [31:0] poll_period_eff_w;
    logic poll_hit_w;

    logic [31:0] timeout_eff_w;
    logic timeout_hit_w;

    assign poll_period_eff_w = (cfg_poll_period_ticks_i == 32'd0) ? 32'd1 : cfg_poll_period_ticks_i;
    assign poll_hit_w = (poll_cnt_r == (poll_period_eff_w - 32'd1));
    assign timeout_eff_w = (RSP_TIMEOUT_TICKS <= 0) ? 32'd1 : RSP_TIMEOUT_TICKS[31:0];
    assign timeout_hit_w = (timeout_cnt_r >= (timeout_eff_w - 32'd1));

    always @(posedge clk) begin
        logic [READ_BUF_W-1:0] read_buf_next_v;
        logic [READ_IDX_W-1:0] read_idx_next_v;

        if (rst_i) begin
            state_r <= ST_IDLE;
            poll_cnt_r <= 32'd0;
            timeout_cnt_r <= 32'd0;
            read_buf_r <= {READ_BUF_W{1'b0}};
            read_idx_r <= '0;

            i2c_cmd_valid_o <= 1'b0;
            i2c_cmd_addr_o <= I2C_ADDR;
            i2c_cmd_reg_o <= 8'h00;
            i2c_cmd_len_o <= 8'd0;
            i2c_cmd_write_o <= 1'b0;
            i2c_cmd_wdata_o <= 8'd0;

            ax_o <= 16'sd0;
            ay_o <= 16'sd0;
            az_o <= 16'sd0;
            accel_valid_o <= 1'b0;

            init_done_o <= 1'b0;
            i2c_error_o <= 1'b0;
            timeout_o <= 1'b0;
            nack_seen_o <= 1'b0;
        end else if (en_i) begin
            i2c_cmd_valid_o <= 1'b0;
            i2c_cmd_write_o <= 1'b0;
            i2c_cmd_wdata_o <= 8'd0;
            accel_valid_o <= 1'b0;

            if (!cfg_enable_i) begin
                state_r <= ST_IDLE;
                poll_cnt_r <= 32'd0;
                timeout_cnt_r <= 32'd0;
                read_idx_r <= '0;
            end else begin
                case (state_r)
                    ST_IDLE: begin
                        timeout_cnt_r <= 32'd0;
                        read_idx_r <= '0;
                        if (!init_done_o) begin
                            if (cfg_init_en_i) begin
                                state_r <= ST_INIT1_CMD;
                            end else begin
                                init_done_o <= 1'b1;
                            end
                        end else begin
                            if (poll_hit_w) begin
                                poll_cnt_r <= 32'd0;
                                state_r <= ST_READ_CMD;
                            end else begin
                                poll_cnt_r <= poll_cnt_r + 32'd1;
                            end
                        end
                    end

                    ST_INIT1_CMD: begin
                        i2c_cmd_valid_o <= 1'b1;
                        i2c_cmd_addr_o <= I2C_ADDR;
                        i2c_cmd_reg_o <= REG_CTRL1;
                        i2c_cmd_len_o <= 8'd1;
                        i2c_cmd_write_o <= 1'b1;
                        i2c_cmd_wdata_o <= cfg_ctrl1_data_i;
                        if (i2c_cmd_ready_i) begin
                            timeout_cnt_r <= 32'd0;
                            state_r <= ST_INIT1_WAIT;
                        end
                    end

                    ST_INIT1_WAIT: begin
                        if (i2c_rsp_done_i) begin
                            if (i2c_rsp_error_i) begin
                                i2c_error_o <= 1'b1;
                                nack_seen_o <= 1'b1;
                                state_r <= ST_IDLE;
                            end else begin
                                state_r <= ST_INIT2_CMD;
                            end
                        end else if (timeout_hit_w) begin
                            timeout_o <= 1'b1;
                            i2c_error_o <= 1'b1;
                            state_r <= ST_IDLE;
                        end else begin
                            timeout_cnt_r <= timeout_cnt_r + 32'd1;
                        end
                    end

                    ST_INIT2_CMD: begin
                        i2c_cmd_valid_o <= 1'b1;
                        i2c_cmd_addr_o <= I2C_ADDR;
                        i2c_cmd_reg_o <= REG_RANGE;
                        i2c_cmd_len_o <= 8'd1;
                        i2c_cmd_write_o <= 1'b1;
                        i2c_cmd_wdata_o <= cfg_range_data_i;
                        if (i2c_cmd_ready_i) begin
                            timeout_cnt_r <= 32'd0;
                            state_r <= ST_INIT2_WAIT;
                        end
                    end

                    ST_INIT2_WAIT: begin
                        if (i2c_rsp_done_i) begin
                            if (i2c_rsp_error_i) begin
                                i2c_error_o <= 1'b1;
                                nack_seen_o <= 1'b1;
                            end else begin
                                init_done_o <= 1'b1;
                            end
                            state_r <= ST_IDLE;
                        end else if (timeout_hit_w) begin
                            timeout_o <= 1'b1;
                            i2c_error_o <= 1'b1;
                            state_r <= ST_IDLE;
                        end else begin
                            timeout_cnt_r <= timeout_cnt_r + 32'd1;
                        end
                    end

                    ST_READ_CMD: begin
                        i2c_cmd_valid_o <= 1'b1;
                        i2c_cmd_addr_o <= I2C_ADDR;
                        i2c_cmd_reg_o <= REG_OUT_X_L;
                        i2c_cmd_len_o <= READ_LEN[7:0];
                        if (i2c_cmd_ready_i) begin
                            read_buf_r <= {READ_BUF_W{1'b0}};
                            read_idx_r <= '0;
                            timeout_cnt_r <= 32'd0;
                            state_r <= ST_READ_WAIT;
                        end
                    end

                    ST_READ_WAIT: begin
                        read_buf_next_v = read_buf_r;
                        read_idx_next_v = read_idx_r;

                        if (i2c_rsp_valid_i && (read_idx_next_v < READ_LEN[READ_IDX_W-1:0])) begin
                            read_buf_next_v[(read_idx_next_v * 8) +: 8] = i2c_rsp_data_i;
                            read_idx_next_v = read_idx_next_v + 1'b1;
                        end

                        read_buf_r <= read_buf_next_v;
                        read_idx_r <= read_idx_next_v;

                        if (i2c_rsp_done_i) begin
                            if (i2c_rsp_error_i) begin
                                i2c_error_o <= 1'b1;
                                nack_seen_o <= 1'b1;
                            end else if (read_idx_next_v == READ_LEN[READ_IDX_W-1:0]) begin
                                ax_o <= $signed(read_buf_next_v[15:0]);
                                ay_o <= $signed(read_buf_next_v[31:16]);
                                az_o <= $signed(read_buf_next_v[47:32]);
                                accel_valid_o <= 1'b1;
                            end else begin
                                i2c_error_o <= 1'b1;
                            end
                            state_r <= ST_IDLE;
                            timeout_cnt_r <= 32'd0;
                        end else if (timeout_hit_w) begin
                            timeout_o <= 1'b1;
                            i2c_error_o <= 1'b1;
                            state_r <= ST_IDLE;
                        end else begin
                            timeout_cnt_r <= timeout_cnt_r + 32'd1;
                        end
                    end

                    default: state_r <= ST_IDLE;
                endcase
            end
        end
    end

endmodule


