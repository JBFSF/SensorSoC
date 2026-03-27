module feature_engine (
    input  wire                     clk_i,
    input  wire                     rst_i,

    // enable on epoch end at top level
    input  wire                     enable_i,

    // Time feature inputs
    input  wire                     seconds_valid_i,
    input  wire [15:0]              cos_time_feat_i,

    // motion
    input wire                     motion_valid_i,
    input wire [15:0]              motion_energy_epoch_i,

    // delta hr
    input wire                     delta_hr_valid_i,
    input wire signed [15:0]       delta_hr_i,

    // rmssd
    input wire                     rmssd_valid_i,
    input wire signed [15:0]       rmssd_i,

    // valid
    output reg                      feat_valid_o,
    output reg signed [15:0]        time_feat_o,
    output reg signed [15:0]        motion_feat_o,
    output reg signed [15:0]        delta_hr_feat_o,
    output reg signed [15:0]        rmssd_feat_o,
    
    // ML gate from signal quality
    input  wire                     ml_update_gate_i
);
    always @(posedge clk_i) begin
        if(rst_i) begin
            feat_valid_o <= 1'b0;
            time_feat_o <= 16'sd0;
            motion_feat_o <= 16'sd0;
            delta_hr_feat_o <= 16'sd0;
            rmssd_feat_o <= 16'sd0;
        end else begin
            feat_valid_o <= 1'b0;

            // capture latest features when their valid strobes fire
            if (seconds_valid_i) time_feat_o <= cos_time_feat_i;
            if (motion_valid_i)  motion_feat_o <= motion_energy_epoch_i;
            if (delta_hr_valid_i) delta_hr_feat_o <= delta_hr_i;
            if (rmssd_valid_i)   rmssd_feat_o <= rmssd_i;

            // epoch strobe: emit a clean valid pulse using the last captured values
            if (enable_i && ml_update_gate_i) feat_valid_o <= 1'b1;
        end
    end

endmodule
