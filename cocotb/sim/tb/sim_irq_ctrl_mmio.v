`timescale 1ns/1ps

module sim_irq_ctrl_mmio;
  reg clk = 0;
  reg resetn = 0;

  reg        mem_valid;
  reg [31:0] mem_addr;
  reg [31:0] mem_wdata;
  reg [3:0]  mem_wstrb;
  wire       mem_ready;
  wire [31:0] mem_rdata;

  reg        host_req_i;
  reg        host_we_i;
  reg [7:0]  host_off_i;
  reg [31:0] host_wdata_i;
  wire       host_ready_o;
  wire [31:0] host_rdata_o;

  reg [31:0] irq_src_i;
  wire [31:0] irq_o;
  wire        wake_req_o;

  irq_ctrl_mmio #(.BASE_ADDR(32'h0300_5000)) dut (
    .clk(clk),
    .resetn(resetn),
    .mem_valid(mem_valid),
    .mem_addr(mem_addr),
    .mem_wdata(mem_wdata),
    .mem_wstrb(mem_wstrb),
    .mem_ready(mem_ready),
    .mem_rdata(mem_rdata),
    .host_req_i(host_req_i),
    .host_we_i(host_we_i),
    .host_off_i(host_off_i),
    .host_wdata_i(host_wdata_i),
    .host_ready_o(host_ready_o),
    .host_rdata_o(host_rdata_o),
    .irq_src_i(irq_src_i),
    .irq_o(irq_o),
    .wake_req_o(wake_req_o)
  );
endmodule
