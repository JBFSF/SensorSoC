`timescale 1ns/1ps

module mssd_engine_tb;

  logic clk = 0;
  logic rst_i = 1;

  logic [15:0] rr_interval;
  logic        rr_valid;
  logic        rr_accepted;
  logic        epoch_end;

  wire [15:0]  mssd_epoch;
  wire         mssd_valid;
  wire [15:0]  rr_diff_count;

  logic mssd_seen;
  logic [15:0] cap_mssd_epoch;
  logic [15:0] cap_rr_diff_count;

  mssd_engine #(
    .MIN_RR_COUNT(2)
  ) dut (
    .clk_i(clk),
    .rst_i(rst_i),
    .rr_interval_i(rr_interval),
    .rr_valid_i(rr_valid),
    .rr_accepted_i(rr_accepted),
    .epoch_end_i(epoch_end),
    .mssd_epoch_o(mssd_epoch),
    .mssd_valid_o(mssd_valid),
    .rr_diff_count_o(rr_diff_count)
  );

  always #10 clk = ~clk;

  always @(posedge clk) begin
    if (rst_i) begin
      mssd_seen <= 1'b0;
      cap_mssd_epoch <= '0;
      cap_rr_diff_count <= '0;
    end else if (mssd_valid) begin
      mssd_seen <= 1'b1;
      cap_mssd_epoch <= mssd_epoch;
      cap_rr_diff_count <= rr_diff_count;
    end
  end

  task automatic send_rr(input [15:0] rr, input bit accepted);
    begin
      @(negedge clk);
      rr_interval = rr;
      rr_accepted = accepted;
      rr_valid = 1'b1;
      @(posedge clk);
      @(negedge clk);
      rr_valid = 1'b0;
      rr_accepted = 1'b0;
    end
  endtask

  task automatic pulse_epoch_end();
    begin
      @(negedge clk);
      epoch_end = 1'b1;
      @(posedge clk);
      @(negedge clk);
      epoch_end = 1'b0;
    end
  endtask

  initial begin
    rr_interval = 0;
    rr_valid = 0;
    rr_accepted = 0;
    epoch_end = 0;

    rst_i = 1;
    repeat (5) @(posedge clk);
    rst_i = 0;

    // Epoch 1: accepted RR = [1000,1100,900,1000]
    // diffs = [100,-200,100] => squares = [10000,40000,10000]
    // RTL outputs the clipped sum-of-squares accumulator => 60000
    send_rr(16'd1000, 1'b1);
    send_rr(16'd1100, 1'b1);
    send_rr(16'd900, 1'b1);
    send_rr(16'd1000, 1'b1);
    mssd_seen = 1'b0;
    pulse_epoch_end();
    repeat (2) @(posedge clk);
    if (!mssd_seen) $fatal(1, "mssd_valid not asserted at epoch_end");
    if (cap_mssd_epoch != 16'd60000) $fatal(1, "mssd mismatch: got=%0d exp=60000", cap_mssd_epoch);
    if (cap_rr_diff_count != 16'd3) $fatal(1, "rr_diff_count mismatch got=%0d exp=3", cap_rr_diff_count);

    // Epoch 2: include rejected beat; mssd must ignore it (gate by rr_accepted)
    send_rr(16'd1000, 1'b1);
    send_rr(16'd700, 1'b0);   // rejected, must be ignored
    send_rr(16'd1200, 1'b1);  // diff from 1000 -> 200
    send_rr(16'd1000, 1'b1);  // diff -> -200
    mssd_seen = 1'b0;
    pulse_epoch_end();
    repeat (2) @(posedge clk);
    if (!mssd_seen) $fatal(1, "epoch2 mssd_valid not asserted");
    if (cap_mssd_epoch != 16'hFFFF) $fatal(1, "epoch2 mssd mismatch got=%0d exp=65535", cap_mssd_epoch);
    if (cap_rr_diff_count != 16'd2) $fatal(1, "epoch2 rr_diff_count mismatch got=%0d exp=2", cap_rr_diff_count);

    // Epoch 3: insufficient diffs => mssd_valid should not assert
    send_rr(16'd1000, 1'b1);
    send_rr(16'd1100, 1'b1); // only 1 diff
    mssd_seen = 1'b0;
    pulse_epoch_end();
    repeat (2) @(posedge clk);
    if (mssd_seen) $fatal(1, "epoch3 mssd_valid asserted with insufficient diffs");

    $display("PASS");
    $finish;
  end

  initial begin
    $dumpfile("mssd_engine_tb.vcd");
    $dumpvars(0, mssd_engine_tb);
  end

endmodule
