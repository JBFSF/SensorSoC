`timescale 1ns/1ps

module logit_to_confidence_tb;

  logic clk_i;
  logic rst_ni;
  logic en_i;
  logic sample_valid_i;

  logic signed [15:0] log0;
  logic signed [15:0] log1;

  logic [7:0] confidence_o;
  logic [7:0] inst_confidence_o;

  // DUT
  logit_to_confidence dut (
    .clk_i(clk_i),
    .rst_ni(rst_ni),
    .en_i(en_i),
    .sample_valid_i(sample_valid_i),
    .log0(log0),
    .log1(log1),
    .confidence_o(confidence_o),
    .inst_confidence_o(inst_confidence_o)
  );

  // clock generation (100 MHz)
  initial clk_i = 0;
  always #5 clk_i = ~clk_i;

  // send one logit sample
  task send_sample(input signed [15:0] l0, input signed [15:0] l1);
  begin
    @(posedge clk_i);
    log0 <= l0;
    log1 <= l1;
    sample_valid_i <= 1;

    @(posedge clk_i);
    sample_valid_i <= 0;
  end
  endtask

  initial begin

    // VCD dump
    $dumpfile("logit_to_confidence.vcd");
    $dumpvars(0, logit_to_confidence_tb);

    // init
    log0 = 0;
    log1 = 0;
    sample_valid_i = 0;
    en_i = 0;
    rst_ni = 0;

    // reset
    repeat (5) @(posedge clk_i);
    rst_ni = 1;

    repeat (5) @(posedge clk_i);

    // enable wake confidence tracking
    en_i = 1;

    $display("---- TEST 1: log1 < log0 (should trend toward sleep) ----");

    repeat (20) begin
      send_sample(16'sd200, 16'sd20);
      @(posedge clk_i);
      $display("conf=%0d inst=%0d", confidence_o, inst_confidence_o);
    end

    $display("---- TEST 2: log1 > log0 (should trend toward wake) ----");

    repeat (20) begin
      send_sample(16'sd20, 16'sd200);
      @(posedge clk_i);
      $display("conf=%0d inst=%0d", confidence_o, inst_confidence_o);
    end

    $display("---- TEST 3: equal logits (should stabilize) ----");

    repeat (20) begin
      send_sample(16'sd100, 16'sd100);
      @(posedge clk_i);
      $display("conf=%0d inst=%0d", confidence_o, inst_confidence_o);
    end

    $finish;
  end

endmodule