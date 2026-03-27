`timescale 1ns/1ps

module ml_stub_mmio #(
    parameter BASE_ADDR = 32'h0300_3000
)(
    input  wire        clk,
    input  wire        resetn,

    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,

    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    output reg         event_o,
    output reg  [31:0] score_o
);

    localparam OFF_CTRL  = 32'h0;  // bit0 trigger_event, bit1 auto_mode
    localparam OFF_SCORE = 32'h4;  // RO
    localparam OFF_EVENT = 32'h8;  // W1C bit0

    wire sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);
    wire [31:0] off = mem_addr - BASE_ADDR;

    reg auto_mode;
    reg [31:0] auto_cnt;

    always @(posedge clk) begin
        if (!resetn) begin
            event_o  <= 1'b0;
            score_o  <= 32'h0;
            auto_mode <= 1'b0;
            auto_cnt <= 32'd2_000_000;
        end else begin
            // Optional periodic “ML result ready”
            if (auto_mode) begin
                if (auto_cnt != 0) auto_cnt <= auto_cnt - 1;
                else begin
                    auto_cnt <= 32'd2_000_000;
                    score_o  <= score_o + 1;
                    event_o  <= 1'b1;
                end
            end
        end
    end

    // MMIO
    always @(posedge clk) begin
        if (!resetn) begin
            mem_ready <= 1'b0;
            mem_rdata <= 32'h0;
        end else begin
            mem_ready <= 1'b0;

            if (sel) begin
                mem_ready <= 1'b1;

                case (off)
                    OFF_CTRL:  mem_rdata <= {30'b0, auto_mode, 1'b0};
                    OFF_SCORE: mem_rdata <= score_o;
                    OFF_EVENT: mem_rdata <= {31'b0, event_o};
                    default:   mem_rdata <= 32'h0;
                endcase

                if (mem_wstrb != 4'b0000) begin
                    case (off)
                        OFF_CTRL: begin
                            if (mem_wstrb[0]) begin
                                if (mem_wdata[0]) begin
                                    score_o <= score_o + 32'd10;
                                    event_o <= 1'b1;
                                end
                                auto_mode <= mem_wdata[1];
                            end
                        end
                        OFF_EVENT: begin
                            if (mem_wdata[0]) event_o <= 1'b0; // W1C
                        end
                        default: begin end
                    endcase
                end
            end
        end
    end

endmodule