`timescale 1ns/1ps

module sim_mssd_engine_ref;

  logic clk = 1'b0;
  logic rst_i = 1'b0;
  logic [15:0] rr_interval = '0;
  logic rr_valid = 1'b0;
  logic rr_accepted = 1'b0;
  logic epoch_end = 1'b0;

  wire [15:0] mssd_epoch;
  wire mssd_valid;
  wire [15:0] rr_diff_count;

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

endmodule
