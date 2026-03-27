`timescale 1ns/1ps

module cos_lut_timer_tb;

  logic clk = 0;
  logic rst_i = 1;

  logic        cfg_enable;
  logic [31:0] seconds_in_night;
  logic        seconds_valid;
  logic [31:0] cfg_period_seconds;
  logic [2:0]  cfg_lut_bits;
  logic [15:0] cfg_scale_q15;

  wire signed [15:0] cos_time_feat;

  cos_lut_timer dut (
    .clk_i(clk),
    .rst_i(rst_i),
    .cfg_enable_i(cfg_enable),
    .seconds_in_night_i(seconds_in_night),
    .seconds_valid_i(seconds_valid),
    .cfg_period_seconds_i(cfg_period_seconds),
    .cfg_lut_bits_i(cfg_lut_bits),
    .cfg_scale_q15_i(cfg_scale_q15),
    .cos_time_feat_o(cos_time_feat)
  );

  always #10 clk = ~clk;

  task automatic tick_seconds(input [31:0] sec);
    begin
      @(negedge clk);
      seconds_in_night = sec;
      seconds_valid = 1'b1;
      @(posedge clk);
      @(negedge clk);
      seconds_valid = 1'b0;
    end
  endtask

  initial begin
    cfg_enable = 1'b1;
    seconds_in_night = 32'd0;
    seconds_valid = 1'b0;
    cfg_period_seconds = 32'd24; // easy quarter-point checks
    cfg_lut_bits = 3'd6;
    cfg_scale_q15 = 16'd32767;

    rst_i = 1'b1;
    repeat (5) @(posedge clk);
    rst_i = 1'b0;

    // Cos quarter points
    tick_seconds(32'd0);
    if (cos_time_feat < 16'sd32000) $fatal(1, "cos(0) too low got=%0d", cos_time_feat);

    tick_seconds(32'd6);
    if ((cos_time_feat > 16'sd1500) || (cos_time_feat < -16'sd1500)) $fatal(1, "cos(pi/2) not near 0 got=%0d", cos_time_feat);

    tick_seconds(32'd12);
    if (cos_time_feat > -16'sd30000) $fatal(1, "cos(pi) too high got=%0d", cos_time_feat);

    tick_seconds(32'd18);
    if ((cos_time_feat > 16'sd1500) || (cos_time_feat < -16'sd1500)) $fatal(1, "cos(3pi/2) not near 0 got=%0d", cos_time_feat);

    // Scaling check: half scale should roughly halve amplitude.
    cfg_scale_q15 = 16'd16384;
    tick_seconds(32'd0);
    if ((cos_time_feat < 16'sd15000) || (cos_time_feat > 16'sd17000)) $fatal(1, "half-scale cos(0) mismatch got=%0d", cos_time_feat);

    // LUT size quantization check (coarser LUT): values at close seconds should match after quantization.
    cfg_scale_q15 = 16'd32767;
    cfg_lut_bits = 3'd4;
    tick_seconds(32'd0);
    begin
      logic signed [15:0] c1;
      c1 = cos_time_feat;
      tick_seconds(32'd1);
      if (cos_time_feat !== c1) $fatal(1, "coarse LUT quantization expected same value for adjacent secs");
    end

    // Disable behavior
    cfg_enable = 1'b0;
    tick_seconds(32'd5);
    if (cos_time_feat !== 16'sd0) $fatal(1, "disabled cos output expected 0 got=%0d", cos_time_feat);

    $display("PASS");
    $finish;
  end

  initial begin
    $dumpfile("cos_lut_timer_tb.vcd");
    $dumpvars(0, cos_lut_timer_tb);
  end

endmodule
