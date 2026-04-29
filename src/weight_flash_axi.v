`timescale 1ns/1ps
//
// weight_flash_axi.v
//
// Bridges taketwo's AXI4 master reads directly to a dedicated SPI flash.
// Each AXI AR burst becomes one SPI READ transaction (0x03 + 24-bit addr +
// N×4 bytes data).  taketwo reads ML weights from flash on every inference.
// No intermediate SRAM — zero extra silicon area beyond combinational logic.
//
// SPI Mode 0 (CPOL=0, CPHA=0), MSB-first.  One CS# pulse per AXI burst.
// Per-burst latency: (8 + 24 + 32*(arlen+1)) × 2 × CLK_DIV system clocks.
//
// Write channel: accepted and discarded.  taketwo writes intermediate
// activations here; they need to complete without stalling the master.

module weight_flash_axi #(
    parameter [31:0] BASE_ADDR  = 32'h0300_6000,
    parameter [7:0]  CLK_DIV   = 8'd2,
    parameter [23:0] FLASH_BASE = 24'h00_0000
)(
    input  wire        clk,
    input  wire        resetn,

    // Dedicated SPI flash (ML weights only)
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

    // -----------------------------------------------------------------------
    // SPI read state machine
    //   ST_IDLE : wait for AXI AR
    //   ST_HDR  : shift out {0x03, 24-bit flash addr} = 32 bits MSB-first
    //   ST_DATA : shift in 32 bits per AXI beat from MISO
    //             SPI clock is paused while rvalid=1 (back-pressure)
    // -----------------------------------------------------------------------
    localparam [1:0] ST_IDLE = 2'd0;
    localparam [1:0] ST_HDR  = 2'd1;
    localparam [1:0] ST_DATA = 2'd2;

    reg [1:0]  state;
    reg [7:0]  beats_left;   // AXI beats remaining after the current one
    reg [4:0]  bit_cnt;      // bits remaining to clock in current phase (31..0)
    reg [7:0]  div_cnt;      // SPI clock half-period counter (0..CLK_DIV-1)
    reg [31:0] tx_sr;        // transmit shift register (HDR phase, MSB-first)
    reg [31:0] rx_sr;        // receive shift register  (DATA phase, MSB-first)

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
        end else begin
            saxi_arready <= 1'b0;

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
                        // Header: {READ cmd 0x03, 24-bit flash byte address}
                        // Flash addr = FLASH_BASE + (araddr - BASE_ADDR)
                        tx_sr    <= {8'h03, FLASH_BASE + saxi_araddr[23:0]
                                                       - BASE_ADDR[23:0]};
                        bit_cnt  <= 5'd31;
                        spi_cs_n <= 1'b0;
                        // MOSI = MSB of header = bit 7 of 0x03 = 0
                        spi_mosi <= 1'b0;
                        state    <= ST_HDR;
                    end
                end

                // -----------------------------------------------------------
                // ST_HDR: clock out 32-bit header (CMD + ADDR) MSB-first.
                // Flash samples MOSI on rising edge; we update on falling edge.
                // spi_clk OLD value identifies edge type (NB assignment delay).
                // -----------------------------------------------------------
                ST_HDR: begin
                    if (phase_done) begin
                        div_cnt <= 8'h0;
                        spi_clk <= ~spi_clk;
                        if (spi_clk) begin
                            // Falling edge: load next MOSI bit
                            if (bit_cnt == 5'd0) begin
                                // All 32 header bits sent — start DATA phase
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
                        // Rising edge: flash samples MOSI, nothing to do here
                    end else begin
                        div_cnt <= div_cnt + 8'h1;
                    end
                end

                // -----------------------------------------------------------
                // ST_DATA: clock in 32 bits from MISO per AXI beat.
                // MISO is sampled on rising edge (spi_clk OLD=0 → new=1).
                // SPI clock is frozen while rvalid=1 waiting for rready.
                // -----------------------------------------------------------
                ST_DATA: begin
                    if (saxi_rvalid && !saxi_rready) begin
                        // Back-pressure: hold SPI clock until master accepts
                    end else begin
                        if (saxi_rvalid && saxi_rready) begin
                            // Beat accepted
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
                                    // Rising edge: sample MISO into rx_sr
                                    if (bit_cnt == 5'd0) begin
                                        // 32 bits complete — present AXI beat
                                        saxi_rdata  <= {rx_sr[30:0], spi_miso};
                                        saxi_rvalid <= 1'b1;
                                        saxi_rresp  <= 2'b00;
                                        saxi_rlast  <= (beats_left == 8'h0);
                                    end else begin
                                        rx_sr   <= {rx_sr[30:0], spi_miso};
                                        bit_cnt <= bit_cnt - 5'd1;
                                    end
                                end
                                // Falling edge: MOSI stays 0 (read-only phase)
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
