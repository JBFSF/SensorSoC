`timescale 1ns/1ps

// Cocotb wrapper for simple_sram.
// All signals are driven/sampled by the Python test (simple_sram_tb.py).
// No clock generator or test logic here.

module tb_simple_sram;

  reg        CLK    = 1'b0;
  reg        resetn = 1'b0;
  reg        valid  = 1'b0;
  wire       ready;
  reg  [3:0] wstrb  = 4'b0;
  reg [31:0] addr   = 32'h0;
  reg [31:0] wdata  = 32'h0;
  wire[31:0] rdata;

  simple_sram #(
    .WORDS(1024)
  ) dut (
    .clk   (CLK),
    .resetn(resetn),
    .valid (valid),
    .ready (ready),
    .wstrb (wstrb),
    .addr  (addr),
    .wdata (wdata),
    .rdata (rdata)
  );

  initial begin
      $dumpfile("sim/waves/tb_simple_sram.vcd");
      $dumpvars(0, tb_simple_sram);
  end
endmodule
