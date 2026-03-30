// wrapper for cocotb (cpu_to_ml_tb.py)
`timescale 1ns/1ps
module sim_cpu_to_ml;

  reg clk = 0;
  reg resetn = 0;

  // Fake CPU MMIO signals (driven by cocotb)
  reg         mem_valid;
  reg  [31:0] mem_addr;
  reg  [31:0] mem_wdata;
  reg  [3:0]  mem_wstrb;
  wire        mem_ready;
  wire [31:0] mem_rdata;

  wire        ml_irq;

  // clock
  always #5 clk = ~clk;  // 100MHz

  // DUT
  cpu_to_ml #(.ML_BASE(32'h0300_4000)) dut (
    .clk(clk),
    .resetn(resetn),

    .mem_valid(mem_valid),
    .mem_addr(mem_addr),
    .mem_wdata(mem_wdata),
    .mem_wstrb(mem_wstrb),
    .mem_ready(mem_ready),
    .mem_rdata(mem_rdata),

    .ml_irq(ml_irq)
  );

  initial begin
    // init signals (cocotb will override too, but this avoids Xs)
    mem_valid = 0;
    mem_addr  = 0;
    mem_wdata = 0;
    mem_wstrb = 0;

    // reset pulse
    #100;
    resetn = 1;
  end

endmodule