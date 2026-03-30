`timescale 1ns/1ps
module sim_test_mmio;
  reg clk = 0;
  reg resetn = 0;

  reg        mem_valid;
  reg [31:0] mem_addr;
  reg [31:0] mem_wdata;
  reg [3:0]  mem_wstrb;

  wire       mem_ready;
  wire [31:0] mem_rdata;
  wire [31:0] status_o, code_o;

  test_mmio #(.BASE_ADDR(32'h0300_F000)) dut (
    .clk(clk),
    .resetn(resetn),
    .mem_valid(mem_valid),
    .mem_addr(mem_addr),
    .mem_wdata(mem_wdata),
    .mem_wstrb(mem_wstrb),
    .cfg_target_wake_sec_i(32'h0),
    .cfg_window_sec_i(32'h0),
    .cfg_step_sec_i(16'h0),
    .cfg_motion_hi_th_i(16'h0),
    .cfg_motion_hi_count_i(8'h0),
    .cfg_policy_i(8'h0),
    .cfg_conf_thr_i(16'h0),
    .mem_ready(mem_ready),
    .mem_rdata(mem_rdata),
    .status_o(status_o),
    .code_o(code_o)
  );

  // cocotb will drive clk/reset from Python, so no always block needed
endmodule
