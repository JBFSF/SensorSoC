`timescale 1ns/1ps

module signal_quality_tb;

  logic clk = 0;
  logic rst_i = 1;

  logic        epoch_end;
  logic        beat_event;
  logic [7:0]  beat_quality;
  logic        double_beat;
  logic        missed_beat;
  logic        fifo_overflow;
  logic        fifo_i2c_error;
  logic        motion_valid;
  logic [15:0] motion_intensity;

  logic [7:0]  cfg_beat_q_min;
  logic [7:0]  cfg_min_valid_fraction;
  logic [7:0]  cfg_max_double;
  logic [7:0]  cfg_max_missed;
  logic [15:0] cfg_motion_hi_th;
  logic [15:0] cfg_max_motion_hi;

  wire [7:0]   invalid_reason;
  wire         ml_update_gate;

  signal_quality dut (
    .clk_i(clk),
    .rst_i(rst_i),
    .epoch_end_i(epoch_end),
    .beat_event_i(beat_event),
    .beat_quality_i(beat_quality),
    .double_beat_i(double_beat),
    .missed_beat_i(missed_beat),
    .fifo_overflow_i(fifo_overflow),
    .fifo_i2c_error_i(fifo_i2c_error),
    .motion_valid_i(motion_valid),
    .motion_intensity_i(motion_intensity),
    .cfg_beat_q_min_i(cfg_beat_q_min),
    .cfg_min_valid_fraction_i(cfg_min_valid_fraction),
    .cfg_max_double_i(cfg_max_double),
    .cfg_max_missed_i(cfg_max_missed),
    .cfg_motion_hi_th_i(cfg_motion_hi_th),
    .cfg_max_motion_hi_i(cfg_max_motion_hi),
    .invalid_reason_o(invalid_reason),
    .ml_update_gate_o(ml_update_gate)
  );

  always #10 clk = ~clk;

  task automatic send_beat(input [7:0] q);
    begin
      @(negedge clk);
      beat_quality = q;
      beat_event = 1'b1;
      @(posedge clk);
      @(negedge clk);
      beat_event = 1'b0;
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

  task automatic pulse_double();
    begin
      @(negedge clk);
      double_beat = 1'b1;
      @(posedge clk);
      @(negedge clk);
      double_beat = 1'b0;
    end
  endtask

  task automatic pulse_missed();
    begin
      @(negedge clk);
      missed_beat = 1'b1;
      @(posedge clk);
      @(negedge clk);
      missed_beat = 1'b0;
    end
  endtask

  task automatic send_motion(input [15:0] m);
    begin
      @(negedge clk);
      motion_valid = 1'b1;
      motion_intensity = m;
      @(posedge clk);
      @(negedge clk);
      motion_valid = 1'b0;
    end
  endtask

  initial begin
    epoch_end = 0;
    beat_event = 0;
    beat_quality = 0;
    double_beat = 0;
    missed_beat = 0;
    fifo_overflow = 0;
    fifo_i2c_error = 0;
    motion_valid = 0;
    motion_intensity = 0;

    cfg_beat_q_min = 8'd120;
    cfg_min_valid_fraction = 8'd180;
    cfg_max_double = 8'd2;
    cfg_max_missed = 8'd2;
    cfg_motion_hi_th = 16'd500;
    cfg_max_motion_hi = 16'd3;

    rst_i = 1;
    repeat (5) @(posedge clk);
    rst_i = 0;

    // Epoch 1: good quality + low motion => valid
    send_beat(8'd200);
    send_beat(8'd190);
    send_beat(8'd180);
    send_motion(16'd100);
    send_motion(16'd120);
    pulse_epoch_end();
    repeat (1) @(posedge clk);
    if (!ml_update_gate) $fatal(1, "epoch1 ml update gate expected 1");
    if (invalid_reason != 8'h00) $fatal(1, "epoch1 invalid_reason expected 0 got=0x%02x", invalid_reason);

    // Epoch 2: low quality + errors + high motion + double/missed excess => invalid
    send_beat(8'd80);
    send_beat(8'd90);
    send_beat(8'd70);
    repeat (4) pulse_double();
    repeat (4) pulse_missed();
    repeat (5) send_motion(16'd700);
    fifo_overflow = 1'b1;
    fifo_i2c_error = 1'b1;
    pulse_epoch_end();
    repeat (1) @(posedge clk);
    if (ml_update_gate) $fatal(1, "epoch2 ml update gate expected 0");
    if (!invalid_reason[0]) $fatal(1, "epoch2 overflow reason bit missing");
    if (!invalid_reason[1]) $fatal(1, "epoch2 i2c reason bit missing");
    if (!invalid_reason[3]) $fatal(1, "epoch2 low quality reason bit missing");
    if (!invalid_reason[4]) $fatal(1, "epoch2 double reason bit missing");
    if (!invalid_reason[5]) $fatal(1, "epoch2 missed reason bit missing");
    if (!invalid_reason[6]) $fatal(1, "epoch2 motion reason bit missing");

    // Epoch 3: no beats => invalid no_beats bit
    fifo_overflow = 1'b0;
    fifo_i2c_error = 1'b0;
    send_motion(16'd100);
    pulse_epoch_end();
    repeat (1) @(posedge clk);
    if (ml_update_gate) $fatal(1, "epoch3 ml update gate expected 0");
    if (!invalid_reason[2]) $fatal(1, "epoch3 no_beats reason bit missing");

    $display("PASS");
    $finish;
  end

  initial begin
    $dumpfile("signal_quality_tb.vcd");
    $dumpvars(0, signal_quality_tb);
  end

endmodule
