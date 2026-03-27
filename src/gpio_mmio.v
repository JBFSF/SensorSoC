// gpio_mmio.v
`timescale 1ns/1ps

module gpio_mmio #(
    parameter BASE_ADDR = 32'h0300_0000
)(
    input  wire        clk,
    input  wire        resetn,

    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,

    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    output reg  [7:0]  gpio_out   // 8 GPIOs (good for iCEBreaker LEDs)
);

    wire sel = mem_valid && (mem_addr[31:0] == BASE_ADDR);

    always @(posedge clk) begin
        if (!resetn) begin
            gpio_out  <= 8'h00;
            mem_ready <= 1'b0;
            mem_rdata <= 32'h0;
        end else begin
            mem_ready <= 1'b0;

            if (sel) begin
                // complete transaction in 1 cycle
                mem_ready <= 1'b1;

                // READ returns current GPIO state
                mem_rdata <= {24'h0, gpio_out};

                // WRITE updates GPIO register (honor byte strobes)
                if (mem_wstrb[0]) gpio_out <= mem_wdata[7:0];
            end
        end
    end

endmodule
