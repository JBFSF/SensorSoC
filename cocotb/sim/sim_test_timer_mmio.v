`timescale 1ns/1ps

module sim_test_timer_mmio;
  reg clk = 0;
  reg resetn = 0;

  reg        mem_valid;
  reg [31:0] mem_addr;
  reg [31:0] mem_wdata;
  reg [3:0]  mem_wstrb;

  wire       mem_ready;
  wire [31:0] mem_rdata;

  wire       event_o;
  wire [31:0] rdata_o;

  // 50 MHz clock (matches your other sims)
  always #10 clk = ~clk;

  timer_mmio #(.BASE_ADDR(32'h0300_2000)) dut (
    .clk(clk),
    .resetn(resetn),
    .mem_valid(mem_valid),
    .mem_addr(mem_addr),
    .mem_wdata(mem_wdata),
    .mem_wstrb(mem_wstrb),
    .mem_ready(mem_ready),
    .mem_rdata(mem_rdata),
    .event_o(event_o),
    .rdata_o(rdata_o)
  );
endmodule
