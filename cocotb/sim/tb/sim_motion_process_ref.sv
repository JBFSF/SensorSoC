`timescale 1ns/1ps

module sim_motion_process_ref;

  logic clk = 1'b0;
  logic rst_i = 1'b0;
  logic sample_valid = 1'b0;
  logic signed [15:0] ax = '0;
  logic signed [15:0] ay = '0;
  logic signed [15:0] az = '0;
  logic epoch_end = 1'b0;

  wire epoch_done;
  wire [47:0] motion_energy_epoch;

  motion_process #(
    .AX_W(16)
  ) dut (
    .clk(clk),
    .rst_i(rst_i),
    .sample_valid_i(sample_valid),
    .ax_i(ax),
    .ay_i(ay),
    .az_i(az),
    .epoch_end_i(epoch_end),
    .epoch_done_o(epoch_done),
    .motion_energy_epoch_o(motion_energy_epoch)
  );

endmodule
