`timescale 1ns/1ps

module motion_process #(
    parameter integer AX_W = 14,
    parameter integer MAG_W = (AX_W + 2),
    parameter integer DYN_W = (MAG_W + 1),
    parameter integer ENERGY_W = 48
)(
    input  logic                     clk,
    input  logic                     rst_i,
    input  logic                     en_i,

    // Sample capture
    input  logic                     sample_valid_i,
    input  logic signed [AX_W-1:0]    ax_i,
    input  logic signed [AX_W-1:0]    ay_i,
    input  logic signed [AX_W-1:0]    az_i,

    // Epoch control (external)
    input  logic                     epoch_end_i,

    // Per epoch outputs (latched on epoch end)
    output logic                      epoch_done_o,
    output logic  [ENERGY_W-1:0]      motion_energy_epoch_o
);

    logic sample_fire;

    // absolute value per axis
    function automatic [AX_W-1:0] abs_s;
        input signed [AX_W-1:0] v;
        begin
            abs_s = v[AX_W-1] ? (~v + {{(AX_W-1){1'b0}}, 1'b1}) : v;
        end
    endfunction

    logic signed [AX_W-1:0] ax_s;
    logic signed [AX_W-1:0] ay_s;
    logic signed [AX_W-1:0] az_s;

    logic [AX_W-1:0] abs_ax;
    logic [AX_W-1:0] abs_ay;
    logic [AX_W-1:0] abs_az;

    // magnitude = |ax| + |ay| + |az|
    logic [MAG_W-1:0] mag1_w;

    // energy increment
    logic [ENERGY_W-1:0] mag_ext;
    logic [ENERGY_W-1:0] energy_add_w;

    logic [ENERGY_W-1:0] motion_energy_accum_r;
    logic [ENERGY_W-1:0] epoch_energy_w;

    assign sample_fire = sample_valid_i;
    assign ax_s = sample_fire ? ax_i : {AX_W{1'b0}};
    assign ay_s = sample_fire ? ay_i : {AX_W{1'b0}};
    assign az_s = sample_fire ? az_i : {AX_W{1'b0}};
    assign abs_ax = abs_s(ax_s);
    assign abs_ay = abs_s(ay_s);
    assign abs_az = abs_s(az_s);
    assign mag1_w = {{(MAG_W-AX_W){1'b0}}, abs_ax}
                  + {{(MAG_W-AX_W){1'b0}}, abs_ay}
                  + {{(MAG_W-AX_W){1'b0}}, abs_az};
    assign mag_ext = {{(ENERGY_W-MAG_W){1'b0}}, mag1_w};
    assign energy_add_w = mag_ext;
    assign epoch_energy_w = motion_energy_accum_r + (sample_fire ? energy_add_w : {ENERGY_W{1'b0}});

    always @(posedge clk) begin
        if (rst_i) begin
            motion_energy_accum_r <= {ENERGY_W{1'b0}};
            motion_energy_epoch_o <= {ENERGY_W{1'b0}};
            epoch_done_o          <= 1'b0;
        end else if (en_i) begin
            epoch_done_o <= 1'b0;

            if (sample_fire) begin
                motion_energy_accum_r <= motion_energy_accum_r + energy_add_w;
            end

            if (epoch_end_i) begin
                motion_energy_epoch_o <= epoch_energy_w;
                epoch_done_o          <= 1'b1;
                motion_energy_accum_r <= {ENERGY_W{1'b0}};
            end
        end
    end

endmodule


