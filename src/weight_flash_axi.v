`timescale 1ns/1ps
//
// weight_flash_axi.v
//
// On reset, issues one SPI READ transaction to load CACHE_WORDS×32-bit words
// from the dedicated weight flash into an on-chip cache array, then asserts
// weight_boot_done. After that, taketwo's AXI read bursts are served from
// the cache with no SPI latency per inference.
//
// Feature inputs at X_OFFSET: CPU-writable; taketwo reads via AXI.
// Logit outputs at LOGIT_OFFSET: captured from taketwo AXI writes; CPU-readable.
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
    input  wire        clk,
    input  wire        resetn,

    // CPU MMIO port — write feature registers; read feature and logit registers
    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,
    output reg         mem_ready,
    output wire [31:0] mem_rdata,

    // Asserts once boot-load from SPI flash is complete and cache is valid
    output reg         weight_boot_done,

    // SPI flash — driven during boot-load; held idle afterwards
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

    // -----------------------------------------------------------------------
    // On-chip weight cache — loaded once from SPI flash at boot
    // -----------------------------------------------------------------------
    reg [31:0] weight_cache [0:CACHE_WORDS-1];

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

    // -----------------------------------------------------------------------
    // AXI read data lookup — serves taketwo burst reads from cache or feat regs
    // -----------------------------------------------------------------------
    function [31:0] cache_lookup;
        input [31:0] byte_addr;
        reg [31:0] off, cidx;
        begin
            off  = byte_addr - BASE_ADDR;
            cidx = (off >= VAR_OFFSET) ? ((off - VAR_OFFSET) >> 2) : 32'h0;
            if (off == X_OFFSET)
                cache_lookup = feat_reg_0;
            else if (off == X_OFFSET + 32'h4)
                cache_lookup = feat_reg_1;
            else if ((off >= VAR_OFFSET) && (off < VAR_OFFSET + CACHE_WORDS * 4))
                cache_lookup = weight_cache[cidx];
            else
                cache_lookup = 32'h0;
        end
    endfunction

    // -----------------------------------------------------------------------
    // State machine
    //   ST_BOOT_HDR  : clock out {0x03, FLASH_BASE[23:0]} — 32 bits
    //   ST_BOOT_DATA : clock in CACHE_WORDS×32-bit words → weight_cache[]
    //   ST_IDLE      : wait for taketwo AXI AR
    //   ST_BURST     : stream cache beats back to taketwo
    // -----------------------------------------------------------------------
    localparam [1:0] ST_BOOT_HDR  = 2'd0;
    localparam [1:0] ST_BOOT_DATA = 2'd1;
    localparam [1:0] ST_IDLE      = 2'd2;
    localparam [1:0] ST_BURST     = 2'd3;

    reg [1:0]  state;
    reg [7:0]  cache_word_cnt;
    reg [7:0]  beats_left;
    reg [31:0] burst_addr;
    reg [4:0]  bit_cnt;
    reg [7:0]  div_cnt;
    reg [31:0] tx_sr;
    reg [31:0] rx_sr;
    reg        last_word_captured;

    wire phase_done = (div_cnt == CLK_DIV - 8'h1);

    integer reset_k;

    always @(posedge clk) begin
        if (!resetn) begin
            state           <= ST_BOOT_HDR;
            // Begin SPI READ immediately: assert CS, put CMD on MOSI, start clocking
            spi_cs_n        <= 1'b0;
            spi_clk         <= 1'b0;
            spi_mosi        <= 1'b0;
            tx_sr           <= {8'h03, FLASH_BASE};
            bit_cnt         <= 5'd31;
            div_cnt         <= 8'h0;
            rx_sr           <= 32'h0;
            cache_word_cnt  <= 8'h0;
            weight_boot_done <= 1'b0;
            saxi_arready    <= 1'b0;
            saxi_rvalid     <= 1'b0;
            saxi_rdata      <= 32'h0;
            saxi_rresp      <= 2'b00;
            saxi_rlast      <= 1'b0;
            rid_r           <= 1'b0;
            beats_left      <= 8'h0;
            burst_addr      <= 32'h0;
            feat_reg_0      <= 32'h0;
            feat_reg_1      <= 32'h0;
            logit_reg_0     <= 32'h0;
            logit_reg_1     <= 32'h0;
            axi_wr_addr_r   <= 32'h0;
            axi_wr_active_r  <= 1'b0;
            mem_ready        <= 1'b0;
            last_word_captured <= 1'b0;
            for (reset_k = 0; reset_k < CACHE_WORDS; reset_k = reset_k + 1)
                weight_cache[reset_k] <= 32'h0;
        end else begin
            saxi_arready <= 1'b0;
            mem_ready    <= 1'b0;

            // ---------------------------------------------------------------
            // AXI write snooping — capture taketwo logit outputs into regs
            // ---------------------------------------------------------------
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

            // ---------------------------------------------------------------
            // CPU MMIO write — feature registers only (logit/weight are read-only
            // from CPU perspective; they're filled by taketwo AXI / boot load)
            // ---------------------------------------------------------------
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
                    // All other CPU writes (logit sentinels, etc.) are silently accepted
                end
            end

            case (state)

                // -----------------------------------------------------------
                // ST_BOOT_HDR: clock out {0x03, FLASH_BASE} MSB-first.
                // Action on falling edge (spi_clk was 1 → going 0).
                // -----------------------------------------------------------
                ST_BOOT_HDR: begin
                    if (phase_done) begin
                        div_cnt <= 8'h0;
                        spi_clk <= ~spi_clk;
                        if (spi_clk) begin
                            if (bit_cnt == 5'd0) begin
                                spi_mosi <= 1'b0;
                                rx_sr    <= 32'h0;
                                bit_cnt  <= 5'd31;
                                state    <= ST_BOOT_DATA;
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
                // ST_BOOT_DATA: clock in CACHE_WORDS×32-bit words.
                // Capture on rising edge (spi_clk was 0 → going 1).
                // Deassert CS on the falling edge after the last word is
                // captured so the final clock pulse completes fully (6688
                // total rising edges: 32 header + 208×32 data).
                // -----------------------------------------------------------
                ST_BOOT_DATA: begin
                    if (phase_done) begin
                        div_cnt <= 8'h0;
                        spi_clk <= ~spi_clk;
                        if (!spi_clk) begin
                            // Rising edge: sample MISO
                            if (last_word_captured) begin
                                // extra half-cycle guard — should not normally fire
                            end else if (bit_cnt == 5'd0) begin
                                weight_cache[cache_word_cnt] <= {rx_sr[30:0], spi_miso};
                                if (cache_word_cnt == CACHE_WORDS - 1) begin
                                    last_word_captured <= 1'b1;  // let clock complete high
                                end else begin
                                    cache_word_cnt <= cache_word_cnt + 8'h1;
                                    rx_sr          <= 32'h0;
                                    bit_cnt        <= 5'd31;
                                end
                            end else begin
                                rx_sr   <= {rx_sr[30:0], spi_miso};
                                bit_cnt <= bit_cnt - 5'd1;
                            end
                        end else begin
                            // Falling edge: deassert CS after last word
                            if (last_word_captured) begin
                                last_word_captured <= 1'b0;
                                spi_cs_n           <= 1'b1;
                                spi_clk            <= 1'b0;
                                weight_boot_done   <= 1'b1;
                                state              <= ST_IDLE;
                            end
                        end
                    end else begin
                        div_cnt <= div_cnt + 8'h1;
                    end
                end

                // -----------------------------------------------------------
                // ST_IDLE: boot done; wait for taketwo AXI AR.
                // -----------------------------------------------------------
                ST_IDLE: begin
                    if (saxi_arvalid) begin
                        saxi_arready <= 1'b1;
                        beats_left   <= saxi_arlen;
                        rid_r        <= saxi_arid;
                        burst_addr   <= saxi_araddr;
                        saxi_rresp   <= 2'b00;
                        saxi_rdata   <= cache_lookup(saxi_araddr);
                        saxi_rlast   <= (saxi_arlen == 8'h0);
                        saxi_rvalid  <= 1'b1;
                        state        <= ST_BURST;
                    end
                end

                // -----------------------------------------------------------
                // ST_BURST: stream cache beats; pre-load rdata for next beat
                // the cycle the current beat is accepted, keeping rvalid high.
                // -----------------------------------------------------------
                ST_BURST: begin
                    if (saxi_rvalid && saxi_rready) begin
                        if (beats_left == 8'h0) begin
                            saxi_rvalid <= 1'b0;
                            saxi_rlast  <= 1'b0;
                            state       <= ST_IDLE;
                        end else begin
                            beats_left <= beats_left - 8'h1;
                            burst_addr <= burst_addr + 32'd4;
                            saxi_rdata <= cache_lookup(burst_addr + 32'd4);
                            saxi_rlast <= (beats_left == 8'h1);
                        end
                    end
                end

                default: state <= ST_IDLE;
            endcase
        end
    end

endmodule
