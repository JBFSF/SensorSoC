`timescale 1ns/1ps

module motion_preprocess_tb;

  localparam int AX_W = 14;

  logic clk = 0;
  logic rst_i = 1;

  // sample interface
  logic sample_valid;
  logic sample_ok;
  logic signed [AX_W-1:0] ax, ay, az;

  // epoch control
  logic epoch_end;

  // outputs
  wire  epoch_done;
  wire [47:0] motion_energy_epoch;

  logic epoch_done_seen;
  always @(posedge clk) begin
    if (rst_i) epoch_done_seen <= 1'b0;
    else if (epoch_done) epoch_done_seen <= 1'b1;
  end

  motion_preprocess dut (
    .clk(clk),
    .rst_i(rst_i),

    .sample_valid_i(sample_valid),
    .sample_ok_i(sample_ok),
    .ax_i(ax),
    .ay_i(ay),
    .az_i(az),
    .epoch_end_i(epoch_end),

    .epoch_done_o(epoch_done),
    .motion_energy_epoch_o(motion_energy_epoch)
  );

  // 50 MHz
  always #10 clk = ~clk;

  task automatic send_sample(input int sax, input int say, input int saz, input bit ok);
    begin
      @(negedge clk);
      ax = sax;
      ay = say;
      az = saz;
      sample_ok = ok;
      sample_valid = 1'b1;
      @(posedge clk);
      @(negedge clk);
      sample_valid = 1'b0;
      sample_ok = 1'b0;
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

  task automatic do_reset();
    begin
      rst_i = 1;
      repeat (5) @(posedge clk);
      rst_i = 0;
      repeat (2) @(posedge clk);
    end
  endtask

  initial begin
    sample_valid = 0;
    sample_ok    = 0;
    ax = '0; ay = '0; az = '0;
    epoch_end = 1'b0;

    do_reset();

    // test 1: accumulation with sample_ok gating
    epoch_done_seen = 1'b0;
    send_sample(3, -4, 5, 1'b1);  // mag=12
    send_sample(1, 2, 3, 1'b1);   // mag=6
    send_sample(10, 0, 0, 1'b0);  // ignored
    pulse_epoch_end();
    repeat (2) @(posedge clk);
    if (!epoch_done_seen) $fatal(1, "epoch_done not asserted");
    if (motion_energy_epoch !== 48'd18) $fatal(1, "energy mismatch: got=%0d exp=18", motion_energy_epoch);

    // test 2: second accumulation window
    do_reset();
    epoch_done_seen = 1'b0;
    send_sample(2, 0, 0, 1'b1);   // mag=2
    send_sample(3, 0, 0, 1'b1);   // mag=3
    pulse_epoch_end();
    repeat (2) @(posedge clk);
    if (!epoch_done_seen) $fatal(1, "epoch_done not asserted");
    if (motion_energy_epoch !== 48'd5) $fatal(1, "energy mismatch: got=%0d exp=5", motion_energy_epoch);

    // test 3: epoch_done is a clean strobe
    do_reset();
    send_sample(1, 0, 0, 1'b1);
    if (epoch_done) $fatal(1, "epoch_done asserted without pulse");
    epoch_done_seen = 1'b0;
    pulse_epoch_end();
    repeat (2) @(posedge clk);
    if (!epoch_done_seen) $fatal(1, "epoch_done missing after pulse");
    repeat (2) @(posedge clk);
    if (epoch_done) $fatal(1, "epoch_done not deasserted");

    $display("PASS");
    $finish;
  end

  initial begin
    $dumpfile("motion_preprocess_tb.vcd");
    $dumpvars(0, motion_preprocess_tb);
  end

endmodule
