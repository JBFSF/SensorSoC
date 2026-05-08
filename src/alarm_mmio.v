//------------------------------------------------------------------------------
// Single-pin output MMIO peripheral for connecting CPU to alarm
//------------------------------------------------------------------------------
// Memory Map (BASE_ADDR = 0x0300_3000), alarm at bit 0

module alarm_mmio #(
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

    output reg         alarm_o
);

    localparam OFF_CTRL = 32'h0;

    wire        sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);
    wire [31:0] off = mem_addr - BASE_ADDR;

    always @(posedge clk) begin
        if (!resetn) begin
            alarm_o   <= 1'b0;
            mem_ready <= 1'b0;
            mem_rdata <= 32'h0;
        end else begin
            mem_ready <= 1'b0;

            if (sel) begin
                mem_ready <= 1'b1;

                case (off)
                    OFF_CTRL: mem_rdata <= {31'b0, alarm_o};
                    default:  mem_rdata <= 32'h0;
                endcase

                if (mem_wstrb[0]) begin
                    case (off)
                        OFF_CTRL: alarm_o <= mem_wdata[0];
                        default: begin end
                    endcase
                end
            end
        end
    end

endmodule
