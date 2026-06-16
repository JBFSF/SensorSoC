`timescale 1ns/1ps
//
// i2c_slave_adpd144ri_raw.sv
//
// Simulation-only raw I2C slave for the ADPD144RI PPG sensor.
// Monitors SCL/SDA at pad level — works in GL sim where the chip's
// internal sim_* functional bus is not present.
//
// Transactions handled (matches ppg_fifo_reader.sv usage):
//   Read  STATUS (0x00)        : 2 bytes → {0x00, FIFO_BYTES_AVAIL}
//   Read  FIFO_THRESH (0x06)   : 2 bytes → {0x00, WATERMARK}
//   Write FIFO_ACCESS_ENA(0x5F): ACK, ignore
//   Read  FIFO_ACCESS (0x60)   : stream N bytes (2 bytes/sample) from CSV
//   Write any other reg        : ACK, ignore
//   Read  any other reg        : returns 0x00
//
// FIFO fill simulation: report FIFO full immediately (FIFO_BYTES_AVAIL =
// WATERMARK*2) on every STATUS poll.  This maximises simulation throughput
// at the cost of artificially high PPG sample rate; fine for GL pipeline
// verification because we only care that the pipeline completes, not that
// the feature values are biologically realistic.

module i2c_slave_adpd144ri_raw #(
    parameter [6:0] I2C_ADDR         = 7'h64,
    parameter [7:0] REG_STATUS       = 8'h00,
    parameter [7:0] REG_FIFO_THRESH  = 8'h06,
    parameter [7:0] REG_FIFO_ACCESS  = 8'h60,
    parameter integer WATERMARK      = 8    // samples per burst (must match chip param)
)(
    input  wire clk,
    input  wire resetn,
    input  wire scl_i,
    input  wire sda_i,
    output reg  sda_o
);

    // FIFO bytes reported as available each time STATUS is polled.
    // 2 bytes per sample (16-bit red channel).
    localparam [7:0] FIFO_BYTES_AVAIL = WATERMARK * 2;

    // ----------------------------------------------------------------
    // Edge / condition detection (identical to lis2dw12_raw)
    // ----------------------------------------------------------------
    reg scl_d, sda_d;
    always @(posedge clk or negedge resetn)
        if (!resetn) begin scl_d <= 1'b1; sda_d <= 1'b1; end
        else         begin scl_d <= scl_i; sda_d <= sda_i; end

    wire scl_rise   =  scl_i & ~scl_d;
    wire scl_fall   = ~scl_i &  scl_d;
    wire start_cond =  scl_i &  scl_d &  sda_d & ~sda_i;
    wire stop_cond  =  scl_i &  scl_d & ~sda_d &  sda_i;

    // ----------------------------------------------------------------
    // State machine (same encoding as lis2dw12_raw for consistency)
    // ----------------------------------------------------------------
    localparam [3:0]
        S_IDLE    = 4'd0,
        S_RX_ADDR = 4'd1,
        S_ACK     = 4'd2,
        S_RX_REG  = 4'd3,
        S_ACK_REG = 4'd4,
        S_WAIT    = 4'd5,
        S_ACK_WD  = 4'd6,
        S_TX      = 4'd7,
        S_MACK    = 4'd8;

    reg [3:0] state;
    reg [3:0] bit_cnt;
    reg [7:0] rx_buf;
    reg [7:0] reg_addr;
    reg [7:0] tx_byte;
    reg [7:0] byte_idx;   // byte index within current read response (0..255)
    reg       ack_r;

    // ----------------------------------------------------------------
    // Sample data from CSV
    // ----------------------------------------------------------------
    reg [15:0] red16;
    int  fd, r_cnt;
    int  raw_red, raw_ir;
    string data_dir, csv_file;

    initial begin
        sda_o = 1'b1;
        if (!$value$plusargs("DATA_DIR=%s", data_dir))
            data_dir = "sim/data";
        csv_file = {data_dir, "/ppg_digital.csv"};
        fd = $fopen(csv_file, "r");
        if (fd == 0) $fatal(1, "i2c_slave_adpd144ri_raw: cannot open %s", csv_file);
        $display("i2c_slave_adpd144ri_raw: opened %s", csv_file);
        red16 = 16'd0;
    end

    task automatic read_next_sample;
        r_cnt = $fscanf(fd, "%d,%d\n", raw_red, raw_ir);
        if (r_cnt != 2) begin
            $display("i2c_slave_adpd144ri_raw: EOF — rewinding");
            $rewind(fd);
            r_cnt = $fscanf(fd, "%d,%d\n", raw_red, raw_ir);
        end
        red16 = {2'b00, raw_red[13:0]};
    endtask

    // Return the correct byte for the given read register and byte index.
    // STATUS: 2 bytes {0x00, FIFO_BYTES_AVAIL}
    // FIFO_THRESH: 2 bytes {0x00, WATERMARK[7:0]}
    // FIFO_ACCESS: alternating low/high bytes of red16 samples
    function automatic [7:0] resp_byte;
        input [7:0] reg_a;
        input [7:0] bidx;
        if (reg_a == 8'h00) begin
            // STATUS: byte0=flags(0x00), byte1=fifo_bytes_avail
            resp_byte = (bidx[0] == 1'b0) ? 8'h00 : FIFO_BYTES_AVAIL;
        end else if (reg_a == 8'h06) begin
            // FIFO_THRESH: byte0=0x00, byte1=watermark_words
            resp_byte = (bidx[0] == 1'b0) ? 8'h00 : WATERMARK[7:0];
        end else if (reg_a == 8'h60) begin
            // FIFO_ACCESS: 2 bytes per sample, little-endian
            resp_byte = (bidx[0] == 1'b0) ? red16[7:0] : red16[15:8];
        end else begin
            resp_byte = 8'h00;
        end
    endfunction

    // ----------------------------------------------------------------
    // Main state machine
    // ----------------------------------------------------------------
    always @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            state    <= S_IDLE;
            sda_o    <= 1'b1;
            bit_cnt  <= 4'd0;
            rx_buf   <= 8'h00;
            reg_addr <= 8'h00;
            tx_byte  <= 8'hFF;
            byte_idx <= 8'd0;
            ack_r    <= 1'b1;
            red16    <= 16'd0;
        end else begin
            sda_o <= 1'b1;   // default: release SDA

            if (start_cond) begin
                state   <= S_RX_ADDR;
                bit_cnt <= 4'd0;
                rx_buf  <= 8'h00;
            end else if (stop_cond) begin
                state <= S_IDLE;
            end else begin
                case (state)
                    S_IDLE: ;

                    S_RX_ADDR: begin
                        if (scl_rise) begin
                            rx_buf <= {rx_buf[6:0], sda_i};
                            if (bit_cnt == 4'd7) begin
                                if (rx_buf[6:0] == I2C_ADDR)
                                    state <= S_ACK;
                                else
                                    state <= S_IDLE;
                                bit_cnt <= 4'd0;
                            end else begin
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    S_ACK: begin
                        sda_o <= 1'b0;
                        if (scl_fall) begin
                            if (rx_buf[0]) begin
                                // Read: load first response byte
                                if (reg_addr == REG_FIFO_ACCESS)
                                    read_next_sample;
                                tx_byte  <= resp_byte(reg_addr, 8'd0);
                                byte_idx <= 8'd0;
                                bit_cnt  <= 4'd0;
                                state    <= S_TX;
                            end else begin
                                rx_buf  <= 8'h00;
                                bit_cnt <= 4'd0;
                                state   <= S_RX_REG;
                            end
                        end
                    end

                    S_RX_REG: begin
                        if (scl_rise) begin
                            rx_buf <= {rx_buf[6:0], sda_i};
                            if (bit_cnt == 4'd7) begin
                                reg_addr <= {rx_buf[6:0], sda_i};
                                bit_cnt  <= 4'd0;
                                state    <= S_ACK_REG;
                            end else begin
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    S_ACK_REG: begin
                        sda_o <= 1'b0;
                        if (scl_fall) begin
                            rx_buf  <= 8'h00;
                            bit_cnt <= 4'd0;
                            state   <= S_WAIT;
                        end
                    end

                    S_WAIT: begin
                        if (scl_rise) begin
                            rx_buf <= {rx_buf[6:0], sda_i};
                            if (bit_cnt == 4'd7) begin
                                bit_cnt <= 4'd0;
                                state   <= S_ACK_WD;
                            end else begin
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    S_ACK_WD: begin
                        sda_o <= 1'b0;
                        if (scl_fall) begin
                            rx_buf  <= 8'h00;
                            bit_cnt <= 4'd0;
                            state   <= S_WAIT;
                        end
                    end

                    S_TX: begin
                        sda_o <= tx_byte[7];
                        if (scl_fall) begin
                            if (bit_cnt == 4'd7) begin
                                state   <= S_MACK;
                                bit_cnt <= 4'd0;
                            end else begin
                                tx_byte <= {tx_byte[6:0], 1'b0};
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    S_MACK: begin
                        if (scl_rise)
                            ack_r <= sda_i;
                        if (scl_fall) begin
                            if (!ack_r) begin
                                // ACK: send next byte.  For FIFO_ACCESS, read a
                                // new CSV sample at the start of each 2-byte word.
                                byte_idx <= byte_idx + 8'd1;
                                if (reg_addr == REG_FIFO_ACCESS &&
                                    byte_idx[0] == 1'b1) begin
                                    // Just finished the high byte; load next sample
                                    // so it's ready for the next low-byte request.
                                    read_next_sample;
                                end
                                tx_byte <= resp_byte(reg_addr, byte_idx + 8'd1);
                                bit_cnt <= 4'd0;
                                state   <= S_TX;
                            end else begin
                                state <= S_IDLE;
                            end
                        end
                    end

                    default: state <= S_IDLE;
                endcase
            end
        end
    end

endmodule
