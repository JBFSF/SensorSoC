`timescale 1ns/1ps

// i2c_slave_adpd144ri.sv
//
// Simulation-only I2C slave model for the ADPD144RI PPG sensor.
// Connects to i2c_master.sv via the sim_* functional bus.
// Reads ppg_digital.csv and responds as a real ADPD144RI would.
//
// Register behavior:
//   0x00 STATUS        : 2 bytes — FIFO byte count (0 or WATERMARK_SAMPLES*2)
//   0x06 FIFO_THRESH   : 2 bytes — threshold=WATERMARK_SAMPLES words
//   0x5F FIFO_ACCESS_ENA: write accepted, no response
//   0x60 FIFO_ACCESS   : streams one 16-bit PPG sample (red channel) per word
//
// Rate control: FIFO is only "full" (WATERMARK_SAMPLES samples ready) every
// WATERMARK_SAMPLES * SAMPLE_PERIOD_CLKS clock cycles, matching the real
// sensor's sample rate. This ensures the beat-detection filter sees samples
// at the correct effective rate rather than as a continuous flood.
//
// CSV format: red_counts,ir_counts unsigned integers per row (14-bit)
//
// CSV path is set at runtime via plusarg:
//   vvp sim.out +DATA_DIR=cocotb/sim/data   (from repo root)
//   vvp sim.out +DATA_DIR=sim/data          (from cocotb/)
//   vvp sim.out                             (uses default: sim/data)

module i2c_slave_adpd144ri #(
    parameter [6:0]  I2C_ADDR          = 7'h64,
    parameter [7:0]  REG_STATUS        = 8'h00,
    parameter [7:0]  REG_FIFO_THRESH   = 8'h06,
    parameter [7:0]  REG_FIFO_ENA      = 8'h5F,
    parameter [7:0]  REG_FIFO_ACCESS   = 8'h60,
    // Cycles between consecutive samples at the simulation clock rate.
    // Default 10 matches 100 Hz sensor at CLK_HZ=1000 (1 cycle = 1 ms).
    parameter integer SAMPLE_PERIOD_CLKS = 10,
    // Number of samples that must accumulate before the FIFO is reported full.
    parameter integer WATERMARK_SAMPLES   = 8
)(
    input  wire        clk,
    input  wire        resetn,

    // Functional sim bus — driven by i2c_master
    input  wire        sim_req,
    input  wire [6:0]  sim_addr,
    input  wire [7:0]  sim_reg,
    input  wire [7:0]  sim_len,
    input  wire        sim_write,
    input  wire [7:0]  sim_wdata,
    output reg         sim_ack,
    output reg  [7:0]  sim_rdata,
    output reg         sim_rvalid,
    output reg         sim_rlast,
    output reg         sim_err
);

    // Number of clock cycles needed to fill WATERMARK_SAMPLES samples
    localparam integer FILL_CLKS       = WATERMARK_SAMPLES * SAMPLE_PERIOD_CLKS;
    // FIFO threshold register value: WATERMARK_SAMPLES words (2 bytes each)
    localparam [7:0]   THRESH_WORDS_BYTE = WATERMARK_SAMPLES;
    // FIFO bytes available when full: WATERMARK_SAMPLES * 2 bytes (capped at 255)
    localparam [7:0]   FIFO_BYTES_FULL   = (WATERMARK_SAMPLES * 2 > 255) ? 8'hFF
                                            : WATERMARK_SAMPLES * 2;

    int    fd;
    int    r;
    int    raw_red, raw_ir;
    reg [15:0] red16, ir16;
    string data_dir;
    string csv_file;

    typedef enum logic [2:0] {
        RSP_IDLE    = 3'd0,
        RSP_STATUS  = 3'd1,
        RSP_THRESH  = 3'd2,
        RSP_FIFO    = 3'd3,
        RSP_WRITE   = 3'd4
    } rsp_state_t;

    rsp_state_t rsp_state;
    reg [1:0]  byte_cnt;
    reg [7:0]  bytes_left;

    // Fill counter: counts up each cycle; FIFO is "ready" when it reaches FILL_CLKS.
    // Reset to 0 after each FIFO burst read so the next batch accumulates fresh.
    integer fill_cnt_r;
    wire    fifo_ready_w = (fill_cnt_r >= FILL_CLKS);

    initial begin
        if (!$value$plusargs("DATA_DIR=%s", data_dir))
            data_dir = "sim/data";          // default: invoke from cocotb/
        csv_file = {data_dir, "/ppg_digital.csv"};

        fd = $fopen(csv_file, "r");
        if (fd == 0) begin
            $display("ERROR: i2c_slave_adpd144ri: cannot open %s", csv_file);
            $fatal(1);
        end
        $display("i2c_slave_adpd144ri: opened %s", csv_file);
        red16 = 16'h0;
        ir16  = 16'h0;
    end

    task read_next_sample;
        r = $fscanf(fd, "%d,%d\n", raw_red, raw_ir);
        if (r == 2) begin
            red16 = {2'b00, raw_red[13:0]};
            ir16  = {2'b00, raw_ir[13:0]};
        end else begin
            red16 = 16'h0; ir16 = 16'h0;
            $display("i2c_slave_adpd144ri: EOF at time %0t", $time);
        end
    endtask

    always @(posedge clk) begin
        if (!resetn) begin
            sim_ack    <= 1'b0;
            sim_rdata  <= 8'h00;
            sim_rvalid <= 1'b0;
            sim_rlast  <= 1'b0;
            sim_err    <= 1'b0;
            rsp_state  <= RSP_IDLE;
            byte_cnt   <= 2'd0;
            bytes_left <= 8'd0;
            fill_cnt_r <= 0;
        end else begin
            sim_ack    <= 1'b0;
            sim_rvalid <= 1'b0;
            sim_rlast  <= 1'b0;
            sim_err    <= 1'b0;

            // Advance fill counter until it saturates at FILL_CLKS
            if (fill_cnt_r < FILL_CLKS)
                fill_cnt_r <= fill_cnt_r + 1;

            case (rsp_state)
                RSP_IDLE: begin
                    if (sim_req && (sim_addr == I2C_ADDR)) begin
                        sim_ack <= 1'b1;
                        byte_cnt <= 2'd0;
                        if (sim_write) begin
                            rsp_state <= RSP_WRITE;
                        end else if (sim_reg == REG_STATUS) begin
                            rsp_state <= RSP_STATUS;
                        end else if (sim_reg == REG_FIFO_THRESH) begin
                            rsp_state <= RSP_THRESH;
                        end else if (sim_reg == REG_FIFO_ACCESS) begin
                            read_next_sample;
                            bytes_left <= sim_len;
                            rsp_state  <= RSP_FIFO;
                        end else begin
                            sim_rdata  <= 8'h00;
                            sim_rvalid <= 1'b1;
                            sim_rlast  <= 1'b1;
                        end
                    end
                end

                RSP_WRITE: begin
                    rsp_state <= RSP_IDLE;
                end

                RSP_STATUS: begin
                    sim_rvalid <= 1'b1;
                    if (byte_cnt == 2'd0) begin
                        // byte 0: bit 7 = overflow (always 0), bits[6:0] = reserved
                        sim_rdata <= 8'h00;
                        byte_cnt  <= 2'd1;
                    end else begin
                        // byte 1: FIFO bytes available — only report data when fill
                        // counter has accumulated a full watermark batch of samples
                        sim_rdata <= fifo_ready_w ? FIFO_BYTES_FULL : 8'h00;
                        sim_rlast <= 1'b1;
                        byte_cnt  <= 2'd0;
                        rsp_state <= RSP_IDLE;
                    end
                end

                RSP_THRESH: begin
                    sim_rvalid <= 1'b1;
                    if (byte_cnt == 2'd0) begin
                        sim_rdata <= 8'h00;
                        byte_cnt  <= 2'd1;
                    end else begin
                        // byte 1 bits[13:8]: FIFO threshold in words (samples)
                        sim_rdata <= THRESH_WORDS_BYTE;
                        sim_rlast <= 1'b1;
                        byte_cnt  <= 2'd0;
                        rsp_state <= RSP_IDLE;
                    end
                end

                RSP_FIFO: begin
                    sim_rvalid <= 1'b1;
                    case (byte_cnt)
                        2'd0: sim_rdata <= red16[7:0];
                        2'd1: sim_rdata <= red16[15:8];
                        default: sim_rdata <= 8'h00;
                    endcase

                    if (bytes_left <= 8'd1) begin
                        sim_rlast  <= 1'b1;
                        rsp_state  <= RSP_IDLE;
                        byte_cnt   <= 2'd0;
                        // Reset fill counter so next batch must wait for FILL_CLKS cycles
                        fill_cnt_r <= 0;
                    end else begin
                        byte_cnt   <= byte_cnt + 1'b1;
                        bytes_left <= bytes_left - 1;
                        if (byte_cnt == 2'd1) begin
                            read_next_sample;
                            byte_cnt <= 2'd0;
                        end
                    end
                end

                default: rsp_state <= RSP_IDLE;
            endcase
        end
    end

endmodule
