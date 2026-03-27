`timescale 1ns/1ps

// weight_ram_axi.v
// 16KB weight/activation RAM with two access ports:
//   - CPU MMIO port  (PicoRV32 native bus, priority when AXI is idle)
//   - AXI4 slave port (connected to taketwo_wrap maxi_* for burst r/w)
//
// AXI4 FSM:
//   IDLE → RD_DATA (AR burst, serve beats, RLAST) → IDLE
//   IDLE → WR_DATA (AW+W burst, accept beats)    → WR_RESP → IDLE
//
// CPU takes priority in IDLE; AXI holds the RAM during active bursts.

module weight_ram_axi #(
    parameter integer WORDS           = 2048,          // 16 KB (4096 x 32-bit) CHANGE THIS TO 8KB, 6 IF POSSIBLE
    parameter [31:0]  BASE_ADDR       = 32'h0300_6000,
    parameter         WEIGHT_INIT_HEX = ""
)(
    input  wire        clk,
    input  wire        resetn,

    // ----------------------------------------------------------------
    // CPU MMIO port (PicoRV32 native bus)
    // ----------------------------------------------------------------
    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,
    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    // ----------------------------------------------------------------
    // AXI4 slave port (taketwo_wrap maxi_* connects here)
    // ----------------------------------------------------------------
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
    output reg         saxi_awready,

    input  wire [31:0] saxi_wdata,
    input  wire [3:0]  saxi_wstrb,
    input  wire        saxi_wlast,
    input  wire        saxi_wvalid,
    output reg         saxi_wready,

    output reg  [0:0]  saxi_bid,
    output reg  [1:0]  saxi_bresp,
    output reg         saxi_bvalid,
    input  wire        saxi_bready,

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

    output reg  [0:0]  saxi_rid,
    output reg  [31:0] saxi_rdata,
    output reg  [1:0]  saxi_rresp,
    output reg         saxi_rlast,
    output reg         saxi_rvalid,
    input  wire        saxi_rready
);

    // ----------------------------------------------------------------
    // RAM storage
    // ----------------------------------------------------------------
    reg [31:0] mem [0:WORDS-1];
    integer ii;
    initial begin
        if (WEIGHT_INIT_HEX != "") begin
            $readmemh(WEIGHT_INIT_HEX, mem);
        end else begin
            for (ii = 0; ii < WORDS; ii = ii + 1)
                mem[ii] = 32'h0;
        end
    end

    // ----------------------------------------------------------------
    // CPU address decode
    //   cpu_off[31:14]==0 → within 16KB window (WORDS=4096 → 4*4096=16384=0x4000)
    // ----------------------------------------------------------------
    wire [31:0] cpu_off  = mem_addr - BASE_ADDR;
    wire        cpu_sel  = mem_valid && (cpu_off[31:14] == 18'h0);
    wire [11:0] cpu_widx = cpu_off[13:2];

    // ----------------------------------------------------------------
    // AXI4 FSM
    // ----------------------------------------------------------------
    localparam ST_IDLE    = 2'd0;
    localparam ST_RD_DATA = 2'd1;
    localparam ST_WR_DATA = 2'd2;
    localparam ST_WR_RESP = 2'd3;

    reg [1:0]  state;
    reg [31:0] burst_addr;   // current AXI byte address
    reg [7:0]  beats_left;   // remaining beats (0 = last beat in this txn)
    reg [0:0]  txn_id;

    wire axi_busy = (state != ST_IDLE);

    // AXI word index (combinatorial from registered burst_addr)
    wire [11:0] axi_widx = (burst_addr - BASE_ADDR) >> 2;

    // ----------------------------------------------------------------
    // Combined FSM — single always block owns all RAM access
    // ----------------------------------------------------------------
    always @(posedge clk) begin
        if (!resetn) begin
            state        <= ST_IDLE;
            mem_ready    <= 1'b0;
            mem_rdata    <= 32'h0;
            saxi_awready <= 1'b0;
            saxi_wready  <= 1'b0;
            saxi_bid     <= 1'b0;
            saxi_bresp   <= 2'b00;
            saxi_bvalid  <= 1'b0;
            saxi_arready <= 1'b0;
            saxi_rid     <= 1'b0;
            saxi_rdata   <= 32'h0;
            saxi_rresp   <= 2'b00;
            saxi_rlast   <= 1'b0;
            saxi_rvalid  <= 1'b0;
            burst_addr   <= 32'h0;
            beats_left   <= 8'h0;
            txn_id       <= 1'b0;
        end else begin
            // Single-cycle handshake signals default to deasserted
            mem_ready    <= 1'b0;
            saxi_awready <= 1'b0;
            saxi_arready <= 1'b0;

            case (state)

                // ----------------------------------------------------
                // IDLE: CPU has priority; start AXI only when CPU idle
                // ----------------------------------------------------
                ST_IDLE: begin
                    if (cpu_sel && !mem_ready) begin
                        // CPU access (read or write); mem_ready was 0 last
                        // cycle so this fires exactly once per CPU request.
                        mem_rdata <= mem[cpu_widx];
                        if (mem_wstrb[0]) mem[cpu_widx][ 7: 0] <= mem_wdata[ 7: 0];
                        if (mem_wstrb[1]) mem[cpu_widx][15: 8] <= mem_wdata[15: 8];
                        if (mem_wstrb[2]) mem[cpu_widx][23:16] <= mem_wdata[23:16];
                        if (mem_wstrb[3]) mem[cpu_widx][31:24] <= mem_wdata[31:24];
                        mem_ready <= 1'b1;
                        // Remain in IDLE so AXI can proceed next cycle.

                    end else if (saxi_arvalid) begin
                        // AXI READ: accept AR channel, prefetch first word
                        saxi_arready <= 1'b1;
                        burst_addr   <= saxi_araddr;
                        beats_left   <= saxi_arlen;
                        txn_id       <= saxi_arid;
                        saxi_rid     <= saxi_arid;
                        saxi_rresp   <= 2'b00;
                        saxi_rlast   <= (saxi_arlen == 8'h0);
                        // Prefetch: data will be in saxi_rdata one cycle later
                        saxi_rdata   <= mem[(saxi_araddr - BASE_ADDR) >> 2];
                        state        <= ST_RD_DATA;

                    end else if (saxi_awvalid) begin
                        // AXI WRITE: accept AW channel
                        saxi_awready <= 1'b1;
                        burst_addr   <= saxi_awaddr;
                        beats_left   <= saxi_awlen;
                        txn_id       <= saxi_awid;
                        state        <= ST_WR_DATA;
                    end
                end

                // ----------------------------------------------------
                // RD_DATA: stream read beats to AXI master
                // ----------------------------------------------------
                ST_RD_DATA: begin
                    saxi_rvalid <= 1'b1;

                    if (saxi_rvalid && saxi_rready) begin
                        if (beats_left == 8'h0) begin
                            // Last beat accepted — return to IDLE
                            saxi_rvalid <= 1'b0;
                            saxi_rlast  <= 1'b0;
                            state       <= ST_IDLE;
                        end else begin
                            // Advance burst: prefetch next word
                            beats_left <= beats_left - 8'h1;
                            burst_addr <= burst_addr + 32'd4;
                            saxi_rdata <= mem[(burst_addr + 32'd4 - BASE_ADDR) >> 2];
                            saxi_rlast <= (beats_left == 8'h1); // next is last
                        end
                    end
                end

                // ----------------------------------------------------
                // WR_DATA: accept write data beats from AXI master
                // ----------------------------------------------------
                ST_WR_DATA: begin
                    saxi_wready <= 1'b1;

                    if (saxi_wvalid) begin
                        if (saxi_wstrb[0]) mem[axi_widx][ 7: 0] <= saxi_wdata[ 7: 0];
                        if (saxi_wstrb[1]) mem[axi_widx][15: 8] <= saxi_wdata[15: 8];
                        if (saxi_wstrb[2]) mem[axi_widx][23:16] <= saxi_wdata[23:16];
                        if (saxi_wstrb[3]) mem[axi_widx][31:24] <= saxi_wdata[31:24];

                        if (saxi_wlast) begin
                            saxi_wready <= 1'b0;
                            state       <= ST_WR_RESP;
                        end else begin
                            burst_addr <= burst_addr + 32'd4;
                        end
                    end
                end

                // ----------------------------------------------------
                // WR_RESP: issue write response
                // ----------------------------------------------------
                ST_WR_RESP: begin
                    saxi_bvalid <= 1'b1;
                    saxi_bresp  <= 2'b00;
                    saxi_bid    <= txn_id;

                    if (saxi_bvalid && saxi_bready) begin
                        saxi_bvalid <= 1'b0;
                        state       <= ST_IDLE;
                    end
                end

                default: state <= ST_IDLE;
            endcase
        end
    end

endmodule
