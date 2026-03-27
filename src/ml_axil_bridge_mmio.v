`timescale 1ns/1ps

module ml_axil_bridge_mmio #(
    parameter BASE_ADDR = 32'h0300_4000
)(
    input  wire        clk,
    input  wire        resetn,

    // PicoRV32 MMIO side
    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,

    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    // Optional: if you still want to generate a wake/event from ML
    output reg         event_o,
    output reg  [31:0] score_o,

    // AXI-Lite master side -> connect to taketwo's saxi_*
    output reg  [31:0] saxi_awaddr,
    output reg  [2:0]  saxi_awprot,
    output reg         saxi_awvalid,
    input  wire        saxi_awready,

    output reg  [31:0] saxi_wdata,
    output reg  [3:0]  saxi_wstrb,
    output reg         saxi_wvalid,
    input  wire        saxi_wready,

    input  wire [1:0]  saxi_bresp,
    input  wire        saxi_bvalid,
    output reg         saxi_bready,

    output reg  [31:0] saxi_araddr,
    output reg  [2:0]  saxi_arprot,
    output reg         saxi_arvalid,
    input  wire        saxi_arready,

    input  wire [31:0] saxi_rdata,
    input  wire [1:0]  saxi_rresp,
    input  wire        saxi_rvalid,
    output reg         saxi_rready
);

    // Decode: this block responds to the whole 4KB page of BASE_ADDR
    wire sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);

    // Most AXI-Lite slave IP expects offsets starting at 0x0.
    // So map CPU addr 0x0300_3000 + off  -> AXI addr = off
    wire [31:0] axil_addr = mem_addr - BASE_ADDR;


    // Simple 1-request-at-a-time FSM
    localparam ST_IDLE   = 3'd0;
    localparam ST_W_AW_W = 3'd1;
    localparam ST_W_B    = 3'd2;
    localparam ST_R_AR   = 3'd3;
    localparam ST_R_R    = 3'd4;
    localparam ST_RESP   = 3'd5;

    reg [2:0]  state;

    // latched request
    reg [31:0] req_addr;
    reg [31:0] req_wdata;
    reg [3:0]  req_wstrb;
    reg        req_is_write;

    // handshake bookkeeping
    reg aw_done, w_done, ar_done;

    // optional: simple "event" example (can delete later)
    // Here we can pulse event_o when a write to some status reg happens,
    // or can replace this with taketwo irq wiring later.
    always @(posedge clk) begin
        if (!resetn) begin
            event_o <= 1'b0;
            score_o <= 32'h0;
        end else begin
            // default: no event
            event_o <= 1'b0;

            // example: if CPU writes to ML reg 0x10 (START) then pulse event
            // (totally optional)
            if (state == ST_IDLE && sel && (mem_wstrb != 4'b0000) && (axil_addr[11:0] == 12'h010)) begin
                event_o <= 1'b1;
                score_o <= score_o + 1;
            end
        end
    end


    // Main FSM
    always @(posedge clk) begin
        if (!resetn) begin
            state <= ST_IDLE;

            mem_ready <= 1'b0;
            mem_rdata <= 32'h0;

            // AXI-Lite defaults
            saxi_awaddr  <= 32'h0;
            saxi_awprot  <= 3'b000;
            saxi_awvalid <= 1'b0;

            saxi_wdata   <= 32'h0;
            saxi_wstrb   <= 4'h0;
            saxi_wvalid  <= 1'b0;

            saxi_bready  <= 1'b0;

            saxi_araddr  <= 32'h0;
            saxi_arprot  <= 3'b000;
            saxi_arvalid <= 1'b0;

            saxi_rready  <= 1'b0;

            // bookkeeping
            aw_done <= 1'b0;
            w_done  <= 1'b0;
            ar_done <= 1'b0;

            req_addr     <= 32'h0;
            req_wdata    <= 32'h0;
            req_wstrb    <= 4'h0;
            req_is_write <= 1'b0;

        end else begin
            // defaults each cycle
            mem_ready <= 1'b0;

            // keep valids unless handshake completes
            // (deassert in logic below)

            case (state)
                // IDLE: latch CPU request
                ST_IDLE: begin
                    // clear any leftover AXI signals
                    saxi_awvalid <= 1'b0;
                    saxi_wvalid  <= 1'b0;
                    saxi_bready  <= 1'b0;
                    saxi_arvalid <= 1'b0;
                    saxi_rready  <= 1'b0;

                    aw_done <= 1'b0;
                    w_done  <= 1'b0;
                    ar_done <= 1'b0;

                    if (sel) begin
                        req_addr  <= axil_addr;
                        req_wdata <= mem_wdata;
                        req_wstrb <= mem_wstrb;
                        req_is_write <= (mem_wstrb != 4'b0000);

                        if (mem_wstrb != 4'b0000) begin
                            // start WRITE
                            saxi_awaddr  <= axil_addr;
                            saxi_awprot  <= 3'b000;
                            saxi_awvalid <= 1'b1;

                            saxi_wdata   <= mem_wdata;
                            saxi_wstrb   <= mem_wstrb;
                            saxi_wvalid  <= 1'b1;

                            state <= ST_W_AW_W;
                        end else begin
                            // start READ
                            saxi_araddr  <= axil_addr;
                            saxi_arprot  <= 3'b000;
                            saxi_arvalid <= 1'b1;

                            state <= ST_R_AR;
                        end
                    end
                end

                // WRITE: send AW + W
                ST_W_AW_W: begin
                    // AW handshake
                    if (saxi_awvalid && saxi_awready) begin
                        saxi_awvalid <= 1'b0;
                        aw_done <= 1'b1;
                    end

                    // W handshake
                    if (saxi_wvalid && saxi_wready) begin
                        saxi_wvalid <= 1'b0;
                        w_done <= 1'b1;
                    end

                    // once both have handshaked, wait for B
                    if ((aw_done || (saxi_awvalid && saxi_awready)) &&
                        (w_done  || (saxi_wvalid  && saxi_wready ))) begin
                        saxi_bready <= 1'b1;
                        state <= ST_W_B;
                    end
                end

                // WRITE: wait for B
                ST_W_B: begin
                    if (saxi_bvalid) begin
                        // could check saxi_bresp here
                        saxi_bready <= 1'b0;

                        // respond to CPU (write has no rdata meaning)
                        mem_rdata <= 32'h0;
                        mem_ready <= 1'b1;

                        state <= ST_RESP;
                    end else begin
                        saxi_bready <= 1'b1;
                    end
                end

                // READ: send AR
                ST_R_AR: begin
                    if (saxi_arvalid && saxi_arready) begin
                        saxi_arvalid <= 1'b0;
                        saxi_rready  <= 1'b1;
                        state <= ST_R_R;
                    end
                end

                // READ: wait for R
                ST_R_R: begin
                    if (saxi_rvalid) begin
                        // could check saxi_rresp here
                        mem_rdata <= saxi_rdata;

                        saxi_rready <= 1'b0;

                        mem_ready <= 1'b1;
                        state <= ST_RESP;
                    end else begin
                        saxi_rready <= 1'b1;
                    end
                end

                // RESP: ensure CPU deasserts mem_valid before accepting another
                // (prevents double-issuing if mem_valid stays high)
                ST_RESP: begin
                    if (!sel) begin
                        state <= ST_IDLE;
                    end
                end

                default: state <= ST_IDLE;
            endcase
        end
    end

endmodule