`timescale 1ns/1ps
//
// weight_flash_axi.v
//
// Bridges taketwo's AXI4 master reads to a dedicated SPI flash for weights.
// Two CPU-writable feature registers at X_OFFSET and X_OFFSET+4 allow live
// sensor values to be injected before each inference — taketwo AXI reads at
// those addresses are served from the registers (no SPI transaction needed).
// All other AXI reads hit the SPI flash.
//
// SPI Mode 0 (CPOL=0, CPHA=0), MSB-first.  One CS# pulse per AXI burst.
// Per-burst latency: (8 + 24 + 32*(arlen+1)) × 2 × CLK_DIV system clocks.
//
// CPU MMIO port: write feature registers; reads return 0.
// Write channel: accepted and discarded (taketwo activation writes).

module weight_flash_axi #(
    parameter [31:0] BASE_ADDR  = 32'h0300_6000,
    parameter [7:0]  CLK_DIV   = 8'd2,
    parameter [23:0] FLASH_BASE = 24'h00_0000,
    parameter [31:0] X_OFFSET     = 32'h40,   // byte offset of input feature words within BASE_ADDR
    parameter [31:0] LOGIT_OFFSET = 32'd5504  // byte offset of output logit words within BASE_ADDR
)(
    input  wire        clk,
    input  wire        resetn,

    // CPU MMIO port — write feature registers; reads return 0
    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,
    output reg         mem_ready,
    output wire [31:0] mem_rdata,

    // Dedicated SPI flash (ML weights)
    output reg         spi_cs_n,
    output reg         spi_clk,
    output reg         spi_mosi,
    input  wire        spi_miso,

    // AXI4 slave — write channel (accept-and-discard)
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

    // Write channel: accept-and-discard so taketwo never stalls on writes.
    assign saxi_awready = 1'b1;
    assign saxi_wready  = 1'b1;
    assign saxi_bid     = 1'b0;
    assign saxi_bresp   = 2'b00;
    assign saxi_bvalid  = 1'b1;

    reg [0:0] rid_r;
    assign saxi_rid = rid_r;

    // Feature registers — CPU writes before inference, taketwo reads via AXI
    reg [31:0] feat_reg_0;   // at BASE_ADDR + X_OFFSET
    reg [31:0] feat_reg_1;   // at BASE_ADDR + X_OFFSET + 4

    // Logit registers — taketwo AXI writes after inference, CPU reads back
    reg [31:0] logit_reg_0;  // at BASE_ADDR + LOGIT_OFFSET
    reg [31:0] logit_reg_1;  // at BASE_ADDR + LOGIT_OFFSET + 4

    // AXI write address tracking (for logit capture)
    reg [31:0] axi_wr_addr_r;
    reg        axi_wr_active_r;
    wire [31:0] eff_waddr = saxi_awvalid ? saxi_awaddr : axi_wr_addr_r;
    wire [31:0] eff_woff  = eff_waddr - BASE_ADDR;

    // CPU address decode
    wire [31:0] cpu_off = mem_addr - BASE_ADDR;
    wire        cpu_sel = mem_valid && (cpu_off[31:14] == 18'h0);

    assign mem_rdata = (cpu_off == X_OFFSET)                  ? feat_reg_0  :
                       (cpu_off == X_OFFSET + 32'h4)           ? feat_reg_1  :
                       (cpu_off == LOGIT_OFFSET)               ? logit_reg_0 :
                       (cpu_off == LOGIT_OFFSET + 32'h4)       ? logit_reg_1 :
                       32'h0;

    // AXI address offset and feature-range detection (combinational)
    wire [31:0] ar_off     = saxi_araddr - BASE_ADDR;
    wire        ar_is_feat = (ar_off >= X_OFFSET) && (ar_off < X_OFFSET + 32'h8);
    wire [31:0] ar_rdata_w = (ar_off == X_OFFSET)         ? feat_reg_0 :
                             (ar_off == X_OFFSET + 32'h4)  ? feat_reg_1 : 32'h0;

    // Next-beat address for ST_REG burst advancement
    reg [31:0] burst_addr;
    wire [31:0] next_addr    = burst_addr + 32'd4;
    wire [31:0] next_off     = next_addr - BASE_ADDR;
    wire [31:0] next_rdata_w = (next_off == X_OFFSET)         ? feat_reg_0 :
                               (next_off == X_OFFSET + 32'h4)  ? feat_reg_1 : 32'h0;

    // -----------------------------------------------------------------------
    // SPI read state machine
    //   ST_IDLE : wait for AXI AR
    //   ST_REG  : serve feature register beats (no SPI)
    //   ST_HDR  : shift out {0x03, 24-bit flash addr} = 32 bits MSB-first
    //   ST_DATA : shift in 32 bits per AXI beat from MISO
    //             SPI clock is paused while rvalid=1 (back-pressure)
    // -----------------------------------------------------------------------
    localparam [1:0] ST_IDLE = 2'd0;
    localparam [1:0] ST_HDR  = 2'd1;
    localparam [1:0] ST_DATA = 2'd2;
    localparam [1:0] ST_REG  = 2'd3;

    reg [1:0]  state;
    reg [7:0]  beats_left;
    reg [4:0]  bit_cnt;
    reg [7:0]  div_cnt;
    reg [31:0] tx_sr;
    reg [31:0] rx_sr;

    wire phase_done = (div_cnt == CLK_DIV - 8'h1);

    always @(posedge clk) begin
        if (!resetn) begin
            state        <= ST_IDLE;
            spi_cs_n     <= 1'b1;
            spi_clk      <= 1'b0;
            spi_mosi     <= 1'b0;
            saxi_arready <= 1'b0;
            saxi_rvalid  <= 1'b0;
            saxi_rdata   <= 32'h0;
            saxi_rresp   <= 2'b00;
            saxi_rlast   <= 1'b0;
            rid_r        <= 1'b0;
            div_cnt      <= 8'h0;
            bit_cnt      <= 5'h0;
            beats_left   <= 8'h0;
            tx_sr        <= 32'h0;
            rx_sr        <= 32'h0;
            burst_addr   <= 32'h0;
            feat_reg_0      <= 32'h0;
            feat_reg_1      <= 32'h0;
            logit_reg_0     <= 32'h0;
            logit_reg_1     <= 32'h0;
            axi_wr_addr_r   <= 32'h0;
            axi_wr_active_r <= 1'b0;
            mem_ready    <= 1'b0;
        end else begin
            saxi_arready <= 1'b0;
            mem_ready    <= 1'b0;

            // AXI write snooping — capture taketwo logit outputs into registers
            // Track write address across burst beats (INCR burst assumed)
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

            // CPU feature register write — single-cycle handshake
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
                ST_IDLE: begin
                    spi_cs_n <= 1'b1;
                    spi_clk  <= 1'b0;
                    div_cnt  <= 8'h0;
                    if (saxi_arvalid) begin
                        saxi_arready <= 1'b1;
                        beats_left   <= saxi_arlen;
                        rid_r        <= saxi_arid;
                        burst_addr   <= saxi_araddr;
                        saxi_rresp   <= 2'b00;
                        if (ar_is_feat) begin
                            // Feature range: serve from registers, skip SPI
                            saxi_rdata  <= ar_rdata_w;
                            saxi_rlast  <= (saxi_arlen == 8'h0);
                            saxi_rvalid <= 1'b1;
                            state       <= ST_REG;
                        end else begin
                            // Flash range: issue SPI READ transaction
                            tx_sr    <= {8'h03, FLASH_BASE + saxi_araddr[23:0]
                                                           - BASE_ADDR[23:0]};
                            bit_cnt  <= 5'd31;
                            spi_cs_n <= 1'b0;
                            spi_mosi <= 1'b0;
                            state    <= ST_HDR;
                        end
                    end
                end

                // -----------------------------------------------------------
                // ST_REG: stream feature register beats to AXI master.
                // Mirrors the ST_RD_DATA pattern from weight_ram_axi.
                // -----------------------------------------------------------
                ST_REG: begin
                    if (saxi_rvalid && saxi_rready) begin
                        if (beats_left == 8'h0) begin
                            saxi_rvalid <= 1'b0;
                            saxi_rlast  <= 1'b0;
                            state       <= ST_IDLE;
                        end else begin
                            beats_left <= beats_left - 8'h1;
                            burst_addr <= next_addr;
                            saxi_rdata <= next_rdata_w;
                            saxi_rlast <= (beats_left == 8'h1);
                        end
                    end
                end

                // -----------------------------------------------------------
                // ST_HDR: clock out 32-bit header (CMD + ADDR) MSB-first.
                // -----------------------------------------------------------
                ST_HDR: begin
                    if (phase_done) begin
                        div_cnt <= 8'h0;
                        spi_clk <= ~spi_clk;
                        if (spi_clk) begin
                            if (bit_cnt == 5'd0) begin
                                spi_mosi <= 1'b0;
                                rx_sr    <= 32'h0;
                                bit_cnt  <= 5'd31;
                                state    <= ST_DATA;
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
                // ST_DATA: clock in 32 bits from MISO per AXI beat.
                // SPI clock is frozen while rvalid=1 waiting for rready.
                // -----------------------------------------------------------
                ST_DATA: begin
                    if (saxi_rvalid && !saxi_rready) begin
                        // Back-pressure: hold SPI clock until master accepts
                    end else begin
                        if (saxi_rvalid && saxi_rready) begin
                            saxi_rvalid <= 1'b0;
                            saxi_rlast  <= 1'b0;
                            if (beats_left == 8'h0) begin
                                spi_cs_n <= 1'b1;
                                spi_clk  <= 1'b0;
                                state    <= ST_IDLE;
                            end else begin
                                beats_left <= beats_left - 8'h1;
                                rx_sr      <= 32'h0;
                                bit_cnt    <= 5'd31;
                            end
                        end

                        if (!saxi_rvalid) begin
                            if (phase_done) begin
                                div_cnt <= 8'h0;
                                spi_clk <= ~spi_clk;
                                if (!spi_clk) begin
                                    if (bit_cnt == 5'd0) begin
                                        saxi_rdata  <= {rx_sr[30:0], spi_miso};
                                        saxi_rvalid <= 1'b1;
                                        saxi_rresp  <= 2'b00;
                                        saxi_rlast  <= (beats_left == 8'h0);
                                    end else begin
                                        rx_sr   <= {rx_sr[30:0], spi_miso};
                                        bit_cnt <= bit_cnt - 5'd1;
                                    end
                                end
                            end else begin
                                div_cnt <= div_cnt + 8'h1;
                            end
                        end
                    end
                end

                default: state <= ST_IDLE;
            endcase
        end
    end

endmodule
