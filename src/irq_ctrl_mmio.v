`timescale 1ns/1ps

// IRQ controller MMIO block with pending/mask/wake management.
// Supports CPU MMIO access plus optional host sideband proxy access.
// Provides IRQ lines and wake pulse generation for SoC power control.

module irq_ctrl_mmio #(
    parameter BASE_ADDR = 32'h0300_5000
)(
    input  wire        clk,
    input  wire        resetn,

    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,
    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    // Host-I2C sideband access (byte offset based, same register map)
    input  wire        host_req_i,
    input  wire        host_we_i,
    input  wire [7:0]  host_off_i,
    input  wire [31:0] host_wdata_i,
    output reg         host_ready_o,
    output reg  [31:0] host_rdata_o,

    input  wire [31:0] irq_src_i,      // raw source bits
    output wire [31:0] irq_o,          // routed to CPU
    output wire        wake_req_o      // pulse on wake-enabled pending rise
);

    localparam OFF_PENDING  = 32'h00;  // RO/W1C
    localparam OFF_MASK     = 32'h04;  // RW (1=enabled)
    localparam OFF_WAKE_EN  = 32'h08;  // RW (1=can wake)
    localparam OFF_ACTIVE   = 32'h0C;  // RO one-hot active claim
    localparam OFF_RAW      = 32'h10;  // RO synchronized raw source
    localparam OFF_CLAIM    = 32'h14;  // RO encoded id (1..32, 0=none)
    localparam OFF_COMPLETE = 32'h18;  // WO encoded id (1..32)

    wire        sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);
    wire [31:0] off = mem_addr - BASE_ADDR;
    wire        wr  = sel && (mem_wstrb != 4'b0000);
    wire        host_do = host_req_i && !sel; // prioritize CPU MMIO when both collide

    reg [31:0] src_d;
    reg [31:0] pending;
    reg [31:0] mask;
    reg [31:0] wake_en;
    reg [31:0] active;
    reg [31:0] wake_pending_d;

    wire [31:0] src_rise      = irq_src_i & ~src_d;
    wire [31:0] pending_armed = pending & wake_en;
    wire [31:0] wake_rise     = pending_armed & ~wake_pending_d;

    assign irq_o      = pending & mask;
    assign wake_req_o = |wake_rise;

    function automatic [31:0] encode_claim;
        input [31:0] bits;
        integer i;
        begin
            encode_claim = 32'd0;
            for (i = 0; i < 32; i = i + 1) begin
                if (bits[i] && (encode_claim == 0))
                    encode_claim = i + 1;
            end
        end
    endfunction

    wire [31:0] claim_id = encode_claim(pending & mask);

    always @(posedge clk) begin
        if (!resetn) begin
            mem_ready       <= 1'b0;
            mem_rdata       <= 32'h0;
            host_ready_o    <= 1'b0;
            host_rdata_o    <= 32'h0;
            src_d           <= 32'h0;
            pending         <= 32'h0;
            mask            <= 32'h0000_0000;
            wake_en         <= 32'h0000_0007;
            active          <= 32'h0;
            wake_pending_d  <= 32'h0;
        end else begin
            mem_ready      <= 1'b0;
            host_ready_o   <= 1'b0;
            src_d          <= irq_src_i;
            pending        <= pending | src_rise;
            wake_pending_d <= pending_armed;

            if (sel) begin
                mem_ready <= 1'b1;
                case (off)
                    OFF_PENDING: mem_rdata <= pending;
                    OFF_MASK:    mem_rdata <= mask;
                    OFF_WAKE_EN: mem_rdata <= wake_en;
                    OFF_ACTIVE:  mem_rdata <= active;
                    OFF_RAW:     mem_rdata <= irq_src_i;
                    OFF_CLAIM:   mem_rdata <= claim_id;
                    default:     mem_rdata <= 32'h0;
                endcase
            end

            if (wr) begin
                case (off)
                    OFF_PENDING: begin
                        pending <= pending & ~mem_wdata; // W1C
                    end
                    OFF_MASK: begin
                        mask <= mem_wdata;
                    end
                    OFF_WAKE_EN: begin
                        wake_en <= mem_wdata;
                    end
                    OFF_CLAIM: begin
                        if (claim_id != 0)
                            active <= 32'h1 << (claim_id - 1);
                    end
                    OFF_COMPLETE: begin
                        if ((mem_wdata >= 1) && (mem_wdata <= 32))
                            active[mem_wdata - 1] <= 1'b0;
                    end
                    default: begin end
                endcase
            end

            // Host sideband access to the same register map.
            if (host_do) begin
                host_ready_o <= 1'b1;

                case (host_off_i)
                    OFF_PENDING[7:0]: host_rdata_o <= pending;
                    OFF_MASK[7:0]:    host_rdata_o <= mask;
                    OFF_WAKE_EN[7:0]: host_rdata_o <= wake_en;
                    OFF_ACTIVE[7:0]:  host_rdata_o <= active;
                    OFF_RAW[7:0]:     host_rdata_o <= irq_src_i;
                    OFF_CLAIM[7:0]:   host_rdata_o <= claim_id;
                    default:          host_rdata_o <= 32'h0;
                endcase

                if (host_we_i) begin
                    case (host_off_i)
                        OFF_PENDING[7:0]: begin
                            pending <= pending & ~host_wdata_i; // W1C
                        end
                        OFF_MASK[7:0]: begin
                            mask <= host_wdata_i;
                        end
                        OFF_WAKE_EN[7:0]: begin
                            wake_en <= host_wdata_i;
                        end
                        OFF_CLAIM[7:0]: begin
                            if (claim_id != 0)
                                active <= 32'h1 << (claim_id - 1);
                        end
                        OFF_COMPLETE[7:0]: begin
                            if ((host_wdata_i >= 1) && (host_wdata_i <= 32))
                                active[host_wdata_i - 1] <= 1'b0;
                        end
                        default: begin end
                    endcase
                end
            end
        end
    end

endmodule
