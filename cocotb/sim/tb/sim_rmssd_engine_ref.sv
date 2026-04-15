`timescale 1ns/1ps

module sim_rmssd_engine_ref;

  logic clk = 1'b0;
  logic rst_i = 1'b0;
  logic [15:0] rr_interval = '0;
  logic rr_valid = 1'b0;
  logic rr_accepted = 1'b0;
  logic epoch_end = 1'b0;

  wire [15:0] rmssd_epoch;
  wire rmssd_valid;
  wire [15:0] rr_diff_count;

  rmssd_engine #(
    .MIN_RR_COUNT(2)
  ) dut (
    .clk_i(clk),
    .rst_i(rst_i),
    .rr_interval_i(rr_interval),
    .rr_valid_i(rr_valid),
    .rr_accepted_i(rr_accepted),
    .epoch_end_i(epoch_end),
    .rmssd_epoch_o(rmssd_epoch),
    .rmssd_valid_o(rmssd_valid),
    .rr_diff_count_o(rr_diff_count)
  );

endmodule
