`timescale 1ns/1ps
//
// weight_flash_axi.v
//
// On reset, issues one SPI READ transaction to load CACHE_WORDS×32-bit words
// from the dedicated weight flash into four gf180mcu SRAM macros (one per
// byte lane), then asserts weight_boot_done. After that, taketwo's AXI read
// bursts are served from the SRAMs. One extra wait state is inserted per burst
// beat to absorb the SRAM's synchronous 1-cycle read latency.
//
// Feature inputs at X_OFFSET: CPU-writable; taketwo reads via AXI (register).
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

    // Asserts once boot-load from SPI flash is complete and SRAM is valid
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

    // Supply rails for SRAM macros when power pins are not exposed as ports
    `ifndef USE_POWER_PINS
    supply1 VDD;
    supply0 VSS;
    `endif

    // Write channel: accept-and-discard so taketwo never stalls on writes
    assign saxi_awready = 1'b1;
    assign saxi_wready  = 1'b1;
    assign saxi_bid     = 1'b0;
    assign saxi_bresp   = 2'b00;
    assign saxi_bvalid  = 1'b1;

    reg [0:0] rid_r;
    assign saxi_rid = rid_r;

    // -----------------------------------------------------------------------
    // Weight SRAM — 4 × gf180mcu_fd_ip_sram__sram512x8m8wm1 (one per byte lane)
    // Together: 32-bit wide, 512 words deep. CACHE_WORDS (208) locations used.
    // Written sequentially during SPI boot; read by taketwo AXI bursts after.
    // -----------------------------------------------------------------------
    reg        sram_cen;      // chip enable, active low
    reg        sram_gwen;     // global write enable, active low (0=write, 1=read)
    reg  [8:0] sram_addr;     // word address (0 to CACHE_WORDS-1)
    reg [31:0] sram_wdata;    // write data

    wire [7:0] sram_q_b0, sram_q_b1, sram_q_b2, sram_q_b3;
    wire [31:0] sram_rdata = {sram_q_b3, sram_q_b2, sram_q_b1, sram_q_b0};

    gf180mcu_fd_ip_sram__sram512x8m8wm1 u_wsram_b0 (
        .CLK(clk), .CEN(sram_cen), .GWEN(sram_gwen),
        .WEN(8'h00), .A(sram_addr), .D(sram_wdata[7:0]),
        .Q(sram_q_b0), .VDD(VDD), .VSS(VSS)
    );
    gf180mcu_fd_ip_sram__sram512x8m8wm1 u_wsram_b1 (
        .CLK(clk), .CEN(sram_cen), .GWEN(sram_gwen),
        .WEN(8'h00), .A(sram_addr), .D(sram_wdata[15:8]),
        .Q(sram_q_b1), .VDD(VDD), .VSS(VSS)
    );
    gf180mcu_fd_ip_sram__sram512x8m8wm1 u_wsram_b2 (
        .CLK(clk), .CEN(sram_cen), .GWEN(sram_gwen),
        .WEN(8'h00), .A(sram_addr), .D(sram_wdata[23:16]),
        .Q(sram_q_b2), .VDD(VDD), .VSS(VSS)
    );
    gf180mcu_fd_ip_sram__sram512x8m8wm1 u_wsram_b3 (
        .CLK(clk), .CEN(sram_cen), .GWEN(sram_gwen),
        .WEN(8'h00), .A(sram_addr), .D(sram_wdata[31:24]),
        .Q(sram_q_b3), .VDD(VDD), .VSS(VSS)
    );

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

    // Register read data for AXI bursts hitting feat/logit range (no SRAM)
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
    //   ST_BOOT_HDR  : clock out {0x03, FLASH_BASE[23:0]} — 32 bits
    //   ST_BOOT_DATA : clock in CACHE_WORDS×32-bit words → SRAM
    //   ST_IDLE      : wait for taketwo AXI AR
    //   ST_READ_WAIT : one-cycle SRAM read latency before asserting rvalid
    //   ST_BURST     : hold rvalid; on rready, issue next SRAM read or finish
    // -----------------------------------------------------------------------
    localparam [2:0] ST_BOOT_HDR  = 3'd0;
    localparam [2:0] ST_BOOT_DATA = 3'd1;
    localparam [2:0] ST_IDLE      = 3'd2;
    localparam [2:0] ST_READ_WAIT = 3'd3;
    localparam [2:0] ST_BURST     = 3'd4;

    reg [2:0]  state;
    reg [7:0]  cache_word_cnt;
    reg [7:0]  beats_left;
    reg [31:0] burst_addr;
    reg [4:0]  bit_cnt;
    reg [7:0]  div_cnt;
    reg [31:0] tx_sr;
    reg [31:0] rx_sr;
    reg        last_word_captured;
    reg        burst_is_var;   // current burst reads from VAR/SRAM region

    wire phase_done = (div_cnt == CLK_DIV - 8'h1);

    // Combinatorial address helpers for AXI read path
    wire [31:0] ar_off      = saxi_araddr - BASE_ADDR;
    wire        ar_is_var   = (ar_off >= VAR_OFFSET) &&
                              (ar_off < VAR_OFFSET + CACHE_WORDS * 4);
    wire [8:0]  sram_idx_ar = (ar_off - VAR_OFFSET) >> 2;

    wire [31:0] burst_next_addr = burst_addr + 32'd4;
    wire [31:0] burst_next_off  = burst_next_addr - BASE_ADDR;
    wire [8:0]  sram_idx_next   = (burst_next_off - VAR_OFFSET) >> 2;

    always @(posedge clk) begin
        if (!resetn) begin
            state            <= ST_BOOT_HDR;
            spi_cs_n         <= 1'b0;
            spi_clk          <= 1'b0;
            spi_mosi         <= 1'b0;
            tx_sr            <= {8'h03, FLASH_BASE};
            bit_cnt          <= 5'd31;
            div_cnt          <= 8'h0;
            rx_sr            <= 32'h0;
            cache_word_cnt   <= 8'h0;
            weight_boot_done <= 1'b0;
            saxi_arready     <= 1'b0;
            saxi_rvalid      <= 1'b0;
            saxi_rdata       <= 32'h0;
            saxi_rresp       <= 2'b00;
            saxi_rlast       <= 1'b0;
            rid_r            <= 1'b0;
            beats_left       <= 8'h0;
            burst_addr       <= 32'h0;
            burst_is_var     <= 1'b0;
            feat_reg_0       <= 32'h0;
            feat_reg_1       <= 32'h0;
            logit_reg_0      <= 32'h0;
            logit_reg_1      <= 32'h0;
            axi_wr_addr_r    <= 32'h0;
            axi_wr_active_r  <= 1'b0;
            mem_ready        <= 1'b0;
            last_word_captured <= 1'b0;
            sram_cen         <= 1'b1;
            sram_gwen        <= 1'b1;
            sram_addr        <= 9'h0;
            sram_wdata       <= 32'h0;
        end else begin
            saxi_arready <= 1'b0;
            mem_ready    <= 1'b0;
            sram_cen     <= 1'b1;   // default: SRAM idle; states assert when needed

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
            // CPU MMIO write — feature registers only
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
                end
            end

            case (state)

                // -----------------------------------------------------------
                // ST_BOOT_HDR: clock out {0x03, FLASH_BASE} MSB-first.
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
                // ST_BOOT_DATA: clock in CACHE_WORDS×32-bit words into SRAM.
                // Rising edge: sample MISO, write complete word to SRAM.
                // Falling edge after last word: deassert CS, assert boot_done.
                // -----------------------------------------------------------
                ST_BOOT_DATA: begin
                    if (phase_done) begin
                        div_cnt <= 8'h0;
                        spi_clk <= ~spi_clk;
                        if (!spi_clk) begin
                            // Rising edge: sample MISO
                            if (last_word_captured) begin
                                // guard — should not normally fire
                            end else if (bit_cnt == 5'd0) begin
                                // Complete 32-bit word received — write to SRAM.
                                // sram_cen default is 1'b1 above; override here.
                                sram_cen   <= 1'b0;
                                sram_gwen  <= 1'b0;
                                sram_addr  <= cache_word_cnt[8:0];
                                sram_wdata <= {rx_sr[30:0], spi_miso};
                                if (cache_word_cnt == CACHE_WORDS - 1) begin
                                    last_word_captured <= 1'b1;
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
                            // Falling edge: deassert CS after last word completes
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
                // If VAR region: issue SRAM read and wait one cycle (ST_READ_WAIT).
                // If feat/logit register region: respond immediately (ST_BURST).
                // -----------------------------------------------------------
                ST_IDLE: begin
                    if (saxi_arvalid) begin
                        saxi_arready <= 1'b1;
                        beats_left   <= saxi_arlen;
                        rid_r        <= saxi_arid;
                        burst_addr   <= saxi_araddr;
                        saxi_rresp   <= 2'b00;
                        saxi_rlast   <= (saxi_arlen == 8'h0);
                        burst_is_var <= ar_is_var;

                        if (ar_is_var) begin
                            // Issue SRAM read; data ready next cycle in ST_READ_WAIT
                            sram_cen  <= 1'b0;
                            sram_gwen <= 1'b1;
                            sram_addr <= sram_idx_ar;
                            state     <= ST_READ_WAIT;
                        end else begin
                            // Register read — respond immediately
                            saxi_rdata  <= reg_rdata(ar_off);
                            saxi_rvalid <= 1'b1;
                            state       <= ST_BURST;
                        end
                    end
                end

                // -----------------------------------------------------------
                // ST_READ_WAIT: one-cycle bubble for SRAM read latency.
                // sram_rdata is valid this cycle; latch and assert rvalid.
                // -----------------------------------------------------------
                ST_READ_WAIT: begin
                    saxi_rdata  <= sram_rdata;
                    saxi_rvalid <= 1'b1;
                    state       <= ST_BURST;
                end

                // -----------------------------------------------------------
                // ST_BURST: rvalid is high. On rready, either finish or issue
                // the next SRAM read (going back to ST_READ_WAIT) / reg read.
                // -----------------------------------------------------------
                ST_BURST: begin
                    if (saxi_rvalid && saxi_rready) begin
                        if (beats_left == 8'h0) begin
                            saxi_rvalid <= 1'b0;
                            saxi_rlast  <= 1'b0;
                            state       <= ST_IDLE;
                        end else begin
                            beats_left <= beats_left - 8'h1;
                            burst_addr <= burst_next_addr;
                            saxi_rlast <= (beats_left == 8'h1);

                            if (burst_is_var) begin
                                // Issue SRAM read for next beat; drop rvalid for 1 cycle
                                sram_cen    <= 1'b0;
                                sram_gwen   <= 1'b1;
                                sram_addr   <= sram_idx_next;
                                saxi_rvalid <= 1'b0;
                                state       <= ST_READ_WAIT;
                            end else begin
                                // Register path: next data available immediately
                                saxi_rdata <= reg_rdata(burst_next_off);
                            end
                        end
                    end
                end

                default: state <= ST_IDLE;
            endcase
        end
    end

endmodule
