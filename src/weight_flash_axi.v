`timescale 1ns/1ps
//
// weight_flash_axi.v
//
// Translates taketwo's AXI4 weight read bursts directly into SPI READ
// transactions on the dedicated weight flash — no intermediate SRAM.
// Weights are fetched on demand each inference. The flash stays permanently
// connected (soldered), so there is no power reason to cache them first.
//
// On each AXI AR to the VAR region: assert CS, clock out READ cmd + flash
// address (32 SPI bits), then stream 32-bit words into AXI R beats one at
// a time, pausing the SPI clock between beats while waiting for rready.
// After the last beat, deassert CS and return to IDLE.
//
// Feature inputs at X_OFFSET: CPU-writable registers read by taketwo via AXI.
// Logit outputs at LOGIT_OFFSET: captured from taketwo AXI writes.
// SPI Mode 0 (CPOL=0, CPHA=0), MSB-first.

module weight_flash_axi #(
    parameter [31:0]  BASE_ADDR    = 32'h0300_6000,
    parameter [7:0]   CLK_DIV     = 8'd2,
    parameter [23:0]  FLASH_BASE  = 24'h00_0000,
    parameter [31:0]  X_OFFSET    = 32'h40,
    parameter [31:0]  LOGIT_OFFSET = 32'd5504,
    parameter [31:0]  VAR_OFFSET   = 32'h80,
    parameter integer CACHE_WORDS  = 208
)(
    `ifdef USE_POWER_PINS
    inout  wire        VDD,
    inout  wire        VSS,
    `endif
    input  wire        clk,
    input  wire        resetn,

    // CPU MMIO port — write feature registers; read feature and logit registers
    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,
    output reg         mem_ready,
    output wire [31:0] mem_rdata,

    // SPI flash — driven on demand during each inference weight fetch
    output reg         spi_cs_n,
    output reg         spi_clk,
    output reg         spi_mosi,
    input  wire        spi_miso,

    // AXI4 slave — write channel (accept-and-discard; taketwo activation writes)
    input  wire [0:0]  saxi_awid,
    input  wire [31:0] saxi_awaddr,
    input  wire [7:0]  saxi_awlen,
    input  wire [2:0]  saxi_awsize,
    input  wire [1:0]  saxi_awburst,
    input  wire [0:0]  saxi_awlock,
    input  wire [3:0]  saxi_awcache,
    input  wire [2:0]  saxi_awprot,
    input  wire [3:0]  saxi_awqos,
    input  wire [1:0]  saxi_awuser,
    input  wire        saxi_awvalid,
    output wire        saxi_awready,

    input  wire [31:0] saxi_wdata,
    input  wire [3:0]  saxi_wstrb,
    input  wire        saxi_wlast,
    input  wire        saxi_wvalid,
    output wire        saxi_wready,

    output wire [0:0]  saxi_bid,
    output wire [1:0]  saxi_bresp,
    output wire        saxi_bvalid,
    input  wire        saxi_bready,

    // AXI4 slave — read channel
    input  wire [0:0]  saxi_arid,
    input  wire [31:0] saxi_araddr,
    input  wire [7:0]  saxi_arlen,
    input  wire [2:0]  saxi_arsize,
    input  wire [1:0]  saxi_arburst,
    input  wire [0:0]  saxi_arlock,
    input  wire [3:0]  saxi_arcache,
    input  wire [2:0]  saxi_arprot,
    input  wire [3:0]  saxi_arqos,
    input  wire [1:0]  saxi_aruser,
    input  wire        saxi_arvalid,
    output reg         saxi_arready,

    output wire [0:0]  saxi_rid,
    output reg  [31:0] saxi_rdata,
    output reg  [1:0]  saxi_rresp,
    output reg         saxi_rlast,
    output reg         saxi_rvalid,
    input  wire        saxi_rready
);

    // Write channel: accept-and-discard so taketwo never stalls on writes
    assign saxi_awready = 1'b1;
    assign saxi_wready  = 1'b1;
    assign saxi_bid     = 1'b0;
    assign saxi_bresp   = 2'b00;
    assign saxi_bvalid  = 1'b1;

    reg [0:0] rid_r;
    assign saxi_rid = rid_r;

    // Feature registers — CPU writes before each inference, taketwo reads via AXI
    reg [31:0] feat_reg_0;   // BASE_ADDR + X_OFFSET
    reg [31:0] feat_reg_1;   // BASE_ADDR + X_OFFSET + 4

    // Logit registers — taketwo AXI writes after inference, CPU reads back
    reg [31:0] logit_reg_0;  // BASE_ADDR + LOGIT_OFFSET
    reg [31:0] logit_reg_1;  // BASE_ADDR + LOGIT_OFFSET + 4

    // AXI write address tracking (for logit capture)
    reg [31:0] axi_wr_addr_r;
    reg        axi_wr_active_r;
    wire [31:0] eff_waddr = saxi_awvalid ? saxi_awaddr : axi_wr_addr_r;
    wire [31:0] eff_woff  = eff_waddr - BASE_ADDR;

    // CPU address decode
    wire [31:0] cpu_off = mem_addr - BASE_ADDR;
    wire        cpu_sel = mem_valid && (cpu_off[31:14] == 18'h0);

    assign mem_rdata = (cpu_off == X_OFFSET)            ? feat_reg_0  :
                       (cpu_off == X_OFFSET + 32'h4)     ? feat_reg_1  :
                       (cpu_off == LOGIT_OFFSET)         ? logit_reg_0 :
                       (cpu_off == LOGIT_OFFSET + 32'h4) ? logit_reg_1 :
                       32'h0;

    // Register read for non-VAR AXI bursts (feat/logit range)
    function [31:0] reg_rdata;
        input [31:0] off;
        begin
            if      (off == X_OFFSET)             reg_rdata = feat_reg_0;
            else if (off == X_OFFSET + 32'h4)     reg_rdata = feat_reg_1;
            else if (off == LOGIT_OFFSET)         reg_rdata = logit_reg_0;
            else if (off == LOGIT_OFFSET + 32'h4) reg_rdata = logit_reg_1;
            else                                   reg_rdata = 32'h0;
        end
    endfunction

    // -----------------------------------------------------------------------
    // State machine
    //   ST_IDLE     : wait for taketwo AXI AR
    //   ST_SPI_HDR  : clock out {0x03, flash_addr} — 32 SPI bits (command+address)
    //   ST_SPI_DATA : stream 32-bit words from flash; assert rvalid per word;
    //                 pause SPI between beats while waiting for rready
    //   ST_BURST    : register-region burst (feat/logit regs, no SPI needed)
    // -----------------------------------------------------------------------
    localparam [1:0] ST_IDLE     = 2'd0;
    localparam [1:0] ST_SPI_HDR  = 2'd1;
    localparam [1:0] ST_SPI_DATA = 2'd2;
    localparam [1:0] ST_BURST    = 2'd3;

    reg [1:0]  state;
    reg [7:0]  beats_left;
    reg [31:0] burst_next_addr;
    reg [4:0]  bit_cnt;
    reg [7:0]  div_cnt;
    reg [31:0] tx_sr;
    reg [31:0] rx_sr;

    wire phase_done = (div_cnt == CLK_DIV - 8'h1);

    // AXI address helpers
    wire [31:0] ar_off       = saxi_araddr - BASE_ADDR;
    wire        ar_is_var    = (ar_off >= VAR_OFFSET);
    // Flash byte address for this burst (24-bit, wraps harmlessly for out-of-range)
    wire [23:0] ar_flash_addr = FLASH_BASE + ar_off[23:0] - VAR_OFFSET[23:0];

    wire [31:0] burst_next_off = burst_next_addr - BASE_ADDR;

    always @(posedge clk) begin
        if (!resetn) begin
            state           <= ST_IDLE;
            spi_cs_n        <= 1'b1;
            spi_clk         <= 1'b0;
            spi_mosi        <= 1'b0;
            tx_sr           <= 32'h0;
            bit_cnt         <= 5'd0;
            div_cnt         <= 8'h0;
            rx_sr           <= 32'h0;
            saxi_arready    <= 1'b0;
            saxi_rvalid     <= 1'b0;
            saxi_rdata      <= 32'h0;
            saxi_rresp      <= 2'b00;
            saxi_rlast      <= 1'b0;
            rid_r           <= 1'b0;
            beats_left      <= 8'h0;
            burst_next_addr <= 32'h0;
            feat_reg_0      <= 32'h0;
            feat_reg_1      <= 32'h0;
            logit_reg_0     <= 32'h0;
            logit_reg_1     <= 32'h0;
            axi_wr_addr_r   <= 32'h0;
            axi_wr_active_r <= 1'b0;
            mem_ready       <= 1'b0;
        end else begin
            saxi_arready <= 1'b0;
            mem_ready    <= 1'b0;

            // -----------------------------------------------------------
            // AXI write snooping — capture taketwo logit outputs into regs
            // -----------------------------------------------------------
            if (saxi_awvalid && !saxi_wvalid) begin
                axi_wr_addr_r   <= saxi_awaddr;
                axi_wr_active_r <= 1'b1;
            end else if (saxi_wvalid && (saxi_awvalid || axi_wr_active_r)) begin
                if (saxi_wlast)
                    axi_wr_active_r <= 1'b0;
                else begin
                    axi_wr_addr_r   <= eff_waddr + 32'd4;
                    axi_wr_active_r <= 1'b1;
                end
            end
            if (saxi_wvalid && (saxi_awvalid || axi_wr_active_r)) begin
                if (eff_woff == LOGIT_OFFSET)
                    logit_reg_0 <= saxi_wdata;
                if (eff_woff == LOGIT_OFFSET + 32'h4)
                    logit_reg_1 <= saxi_wdata;
            end

            // -----------------------------------------------------------
            // CPU MMIO write — feature registers only
            // -----------------------------------------------------------
            if (cpu_sel && !mem_ready) begin
                mem_ready <= 1'b1;
                if (mem_wstrb != 4'h0) begin
                    if (cpu_off == X_OFFSET) begin
                        if (mem_wstrb[0]) feat_reg_0[ 7: 0] <= mem_wdata[ 7: 0];
                        if (mem_wstrb[1]) feat_reg_0[15: 8] <= mem_wdata[15: 8];
                        if (mem_wstrb[2]) feat_reg_0[23:16] <= mem_wdata[23:16];
                        if (mem_wstrb[3]) feat_reg_0[31:24] <= mem_wdata[31:24];
                    end
                    if (cpu_off == X_OFFSET + 32'h4) begin
                        if (mem_wstrb[0]) feat_reg_1[ 7: 0] <= mem_wdata[ 7: 0];
                        if (mem_wstrb[1]) feat_reg_1[15: 8] <= mem_wdata[15: 8];
                        if (mem_wstrb[2]) feat_reg_1[23:16] <= mem_wdata[23:16];
                        if (mem_wstrb[3]) feat_reg_1[31:24] <= mem_wdata[31:24];
                    end
                end
            end

            case (state)

                // -----------------------------------------------------------
                // ST_IDLE: wait for taketwo AXI AR.
                // VAR region → start SPI READ transaction.
                // Register region → serve from regs immediately.
                // -----------------------------------------------------------
                ST_IDLE: begin
                    if (saxi_arvalid) begin
                        saxi_arready    <= 1'b1;
                        beats_left      <= saxi_arlen;
                        rid_r           <= saxi_arid;
                        saxi_rresp      <= 2'b00;
                        saxi_rlast      <= (saxi_arlen == 8'h0);
                        burst_next_addr <= saxi_araddr + 32'd4;

                        if (ar_is_var) begin
                            // Initiate SPI READ: cmd 0x03 + 24-bit flash address
                            spi_cs_n <= 1'b0;
                            spi_clk  <= 1'b0;
                            spi_mosi <= 1'b0;  // MSB of 0x03 is 0
                            tx_sr    <= {8'h03, ar_flash_addr};
                            bit_cnt  <= 5'd31;
                            div_cnt  <= 8'h0;
                            state    <= ST_SPI_HDR;
                        end else begin
                            saxi_rdata  <= reg_rdata(ar_off);
                            saxi_rvalid <= 1'b1;
                            state       <= ST_BURST;
                        end
                    end
                end

                // -----------------------------------------------------------
                // ST_SPI_HDR: clock out {0x03, flash_addr} MSB-first (32 bits).
                // Same SPI Mode 0 clocking as the former boot path.
                // -----------------------------------------------------------
                ST_SPI_HDR: begin
                    if (phase_done) begin
                        div_cnt <= 8'h0;
                        spi_clk <= ~spi_clk;
                        if (spi_clk) begin  // falling edge: shift out next bit
                            if (bit_cnt == 5'd0) begin
                                // Header done — start receiving weight data
                                spi_mosi <= 1'b0;
                                rx_sr    <= 32'h0;
                                bit_cnt  <= 5'd31;
                                state    <= ST_SPI_DATA;
                            end else begin
                                tx_sr    <= {tx_sr[30:0], 1'b0};
                                spi_mosi <= tx_sr[30];
                                bit_cnt  <= bit_cnt - 5'd1;
                            end
                        end
                    end else begin
                        div_cnt <= div_cnt + 8'h1;
                    end
                end

                // -----------------------------------------------------------
                // ST_SPI_DATA: receive 32-bit words from flash, one per AXI beat.
                // SPI clock advances only when rvalid is NOT asserted (i.e., not
                // stalled waiting for rready). On rready, either start next word
                // or close the SPI transaction and return to IDLE.
                // -----------------------------------------------------------
                ST_SPI_DATA: begin
                    if (saxi_rvalid && saxi_rready) begin
                        // Beat accepted by taketwo
                        saxi_rvalid <= 1'b0;
                        if (beats_left == 8'h0) begin
                            // Last beat — close SPI transaction
                            spi_cs_n <= 1'b1;
                            spi_clk  <= 1'b0;
                            state    <= ST_IDLE;
                        end else begin
                            beats_left      <= beats_left - 8'h1;
                            burst_next_addr <= burst_next_addr + 32'd4;
                            saxi_rlast      <= (beats_left == 8'h1);
                            rx_sr           <= 32'h0;
                            bit_cnt         <= 5'd31;
                            // spi_clk is high (just completed a rising edge);
                            // div_cnt is 0; SPI will continue clocking naturally
                        end
                    end else if (!saxi_rvalid) begin
                        // Advance SPI clock
                        if (phase_done) begin
                            div_cnt <= 8'h0;
                            spi_clk <= ~spi_clk;
                            if (!spi_clk) begin  // going high = rising edge: sample MISO
                                if (bit_cnt == 5'd0) begin
                                    // 32nd bit received — word complete
                                    saxi_rdata  <= {rx_sr[30:0], spi_miso};
                                    saxi_rvalid <= 1'b1;
                                end else begin
                                    rx_sr   <= {rx_sr[30:0], spi_miso};
                                    bit_cnt <= bit_cnt - 5'd1;
                                end
                            end
                            // falling edge: MOSI don't-care (receiving only)
                        end else begin
                            div_cnt <= div_cnt + 8'h1;
                        end
                    end
                    // else: rvalid && !rready — SPI paused, waiting for handshake
                end

                // -----------------------------------------------------------
                // ST_BURST: register-region burst (no SPI).
                // Serves feat_reg / logit_reg immediately each beat.
                // -----------------------------------------------------------
                ST_BURST: begin
                    if (saxi_rvalid && saxi_rready) begin
                        if (beats_left == 8'h0) begin
                            saxi_rvalid <= 1'b0;
                            saxi_rlast  <= 1'b0;
                            state       <= ST_IDLE;
                        end else begin
                            beats_left      <= beats_left - 8'h1;
                            burst_next_addr <= burst_next_addr + 32'd4;
                            saxi_rlast      <= (beats_left == 8'h1);
                            saxi_rdata      <= reg_rdata(burst_next_off);
                        end
                    end
                end

                default: state <= ST_IDLE;
            endcase
        end
    end

endmodule
