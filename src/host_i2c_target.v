`timescale 1ns/1ps

// host-side I2C target (7-bit slave address) for register access.
// Converts I2C byte transactions into wr/rd register bus signals.
// Used in simulation to exercise host control and status paths.

module host_i2c_target #(
    parameter [6:0] SLAVE_ADDR = 7'h42
) (
    input  wire       clk,
    input  wire       resetn,

    input  wire       i2c_scl_i,
    inout  wire       i2c_sda_io,

    output reg        wr_en_o,
    output reg  [7:0] wr_addr_o,
    output reg  [7:0] wr_data_o,

    output reg  [7:0] rd_addr_o,
    input  wire [7:0] rd_data_i,

    output reg        proto_err_o
);
    localparam [2:0] ST_IDLE     = 3'd0;
    localparam [2:0] ST_ADDR_RX  = 3'd1;
    localparam [2:0] ST_ADDR_ACK = 3'd2;
    localparam [2:0] ST_WR_RX    = 3'd3;
    localparam [2:0] ST_WR_ACK   = 3'd4;
    localparam [2:0] ST_RD_TX    = 3'd5;
    localparam [2:0] ST_RD_ACK   = 3'd6;

    reg [2:0] state;
    reg [2:0] bit_cnt;
    reg [7:0] shift;

    reg rw_mode;
    reg ptr_set;
    reg expect_ptr;
    reg ack_seen_high;
    reg [7:0] reg_ptr;

    reg sda_drive_low;
    wire sda_in = i2c_sda_io;
    assign i2c_sda_io = sda_drive_low ? 1'b0 : 1'bz;

    reg scl_sync, scl_prev;
    reg sda_sync, sda_prev;

    wire scl_rise = !scl_prev && scl_sync;
    wire scl_fall = scl_prev && !scl_sync;
    wire start_cond = (sda_prev == 1'b1) && (sda_sync == 1'b0) && (scl_sync == 1'b1) && !sda_drive_low;
    wire stop_cond  = (sda_prev == 1'b0) && (sda_sync == 1'b1) && (scl_sync == 1'b1) && !sda_drive_low;

    reg [7:0] rx_byte;
    reg [6:0] addr7;

    always @(posedge clk) begin
        if (!resetn) begin
            scl_sync      <= 1'b1;
            scl_prev      <= 1'b1;
            sda_sync      <= 1'b1;
            sda_prev      <= 1'b1;

            state         <= ST_IDLE;
            bit_cnt       <= 3'd7;
            shift         <= 8'h00;
            rx_byte       <= 8'h00;
            addr7         <= 7'h00;
            rw_mode       <= 1'b0;

            reg_ptr       <= 8'h00;
            ptr_set       <= 1'b0;
            expect_ptr    <= 1'b1;
            ack_seen_high <= 1'b0;
            rd_addr_o     <= 8'h00;

            sda_drive_low <= 1'b0;

            wr_en_o       <= 1'b0;
            wr_addr_o     <= 8'h00;
            wr_data_o     <= 8'h00;
            proto_err_o   <= 1'b0;
        end else begin
            wr_en_o     <= 1'b0;
            proto_err_o <= 1'b0;

            scl_prev <= scl_sync;
            sda_prev <= sda_sync;
            scl_sync <= i2c_scl_i;
            sda_sync <= sda_in;

            if (start_cond) begin
                state         <= ST_ADDR_RX;
                bit_cnt       <= 3'd7;
                sda_drive_low <= 1'b0;
            end else if (stop_cond) begin
                state         <= ST_IDLE;
                sda_drive_low <= 1'b0;
            end else begin
                case (state)
                    ST_IDLE: begin
                        sda_drive_low <= 1'b0;
                    end

                    ST_ADDR_RX: begin
                        if (scl_rise) begin
                            shift[bit_cnt] <= sda_sync;
                            if (bit_cnt == 3'd0) begin
                                rx_byte <= {shift[7:1], sda_sync};
                                addr7   <= shift[7:1];
                                rw_mode <= sda_sync;

                                if (shift[7:1] == SLAVE_ADDR) begin
                                    if (sda_sync && ptr_set)
                                        rd_addr_o <= reg_ptr;
                                    state         <= ST_ADDR_ACK;
                                    sda_drive_low <= 1'b1;
                                    ack_seen_high <= 1'b0;
                                end else begin
                                    state         <= ST_IDLE;
                                    sda_drive_low <= 1'b0;
                                end
                                bit_cnt <= 3'd7;
                            end else begin
                                bit_cnt <= bit_cnt - 3'd1;
                            end
                        end
                    end

                    ST_ADDR_ACK: begin
                        if (scl_rise)
                            ack_seen_high <= 1'b1;

                        if (ack_seen_high && scl_fall) begin
                            if (rw_mode) begin
                                if (!ptr_set) begin
                                    proto_err_o <= 1'b1;
                                    reg_ptr   <= 8'h00;
                                    rd_addr_o <= 8'h00;
                                    ptr_set   <= 1'b1;
                                end
                                state   <= ST_RD_TX;
                                bit_cnt <= 3'd7;
                                sda_drive_low <= ~rd_data_i[7];
                            end else begin
                                sda_drive_low <= 1'b0;
                                state   <= ST_WR_RX;
                                bit_cnt <= 3'd7;
                                expect_ptr <= 1'b1;
                            end
                        end
                    end

                    ST_WR_RX: begin
                        if (scl_rise) begin
                            shift[bit_cnt] <= sda_sync;
                            if (bit_cnt == 3'd0) begin
                                rx_byte <= {shift[7:1], sda_sync};
                                if (expect_ptr) begin
                                    reg_ptr <= {shift[7:1], sda_sync};
                                    ptr_set <= 1'b1;
                                    expect_ptr <= 1'b0;
                                end else begin
                                    wr_en_o   <= 1'b1;
                                    wr_addr_o <= reg_ptr;
                                    wr_data_o <= {shift[7:1], sda_sync};
                                    reg_ptr   <= reg_ptr + 8'd1;
                                end
                                state         <= ST_WR_ACK;
                                sda_drive_low <= 1'b1;
                                ack_seen_high <= 1'b0;
                                bit_cnt       <= 3'd7;
                            end else begin
                                bit_cnt <= bit_cnt - 3'd1;
                            end
                        end
                    end

                    ST_WR_ACK: begin
                        if (scl_rise)
                            ack_seen_high <= 1'b1;

                        if (ack_seen_high && scl_fall) begin
                            sda_drive_low <= 1'b0;
                            state         <= ST_WR_RX;
                        end
                    end

                    ST_RD_TX: begin
                        if (scl_fall) begin
                            sda_drive_low <= ~rd_data_i[bit_cnt];
                        end
                        if (scl_rise) begin
                            if (bit_cnt == 3'd0) begin
                                state <= ST_RD_ACK;
                            end else begin
                                bit_cnt <= bit_cnt - 3'd1;
                            end
                        end
                    end

                    ST_RD_ACK: begin
                        if (scl_fall) begin
                            // Release SDA only after the final data bit is sampled.
                            sda_drive_low <= 1'b0;
                        end
                        if (scl_rise) begin
                            if (!sda_sync) begin
                                reg_ptr   <= reg_ptr + 8'd1;
                                rd_addr_o <= reg_ptr + 8'd1;
                                bit_cnt   <= 3'd7;
                                state     <= ST_RD_TX;
                            end else begin
                                state <= ST_IDLE;
                            end
                        end
                    end

                    default: begin
                        state         <= ST_IDLE;
                        sda_drive_low <= 1'b0;
                    end
                endcase
            end
        end
    end
endmodule
