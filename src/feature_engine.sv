module feature_engine (
    input  wire                     clk_i,
    input  wire                     rst_i,
    input  wire                     en_i,

    // enable on epoch end at top level
    input  wire                     enable_i,

    // Time feature inputs
    input  wire                     seconds_valid_i,
    input  wire [15:0]              time_value_i,

    // motion
    input wire                     motion_valid_i,
    input wire [15:0]              motion_energy_epoch_i,

    // delta hr
    input wire                     delta_hr_valid_i,
    input wire signed [15:0]       delta_hr_i,

    // mssd
    input wire                     mssd_valid_i,
    input wire signed [15:0]       mssd_i,

    // valid
    output reg                      feat_valid_o,
    output reg signed [15:0]        time_feat_o,
    output reg signed [15:0]        motion_feat_o,
    output reg signed [15:0]        delta_hr_feat_o,
    output reg signed [15:0]        mssd_feat_o,
    
    // ML gate from signal quality
    input  wire                     ml_update_gate_i
);
    always @(posedge clk_i) begin
        if(rst_i) begin
            feat_valid_o <= 1'b0;
            time_feat_o <= 16'sd0;
            motion_feat_o <= 16'sd0;
            delta_hr_feat_o <= 16'sd0;
            mssd_feat_o <= 16'sd0;
        end else if (en_i) begin
            feat_valid_o <= 1'b0;

            // capture latest features when their valid strobes fire
            if (seconds_valid_i) time_feat_o <= $signed(time_value_i);
            if (motion_valid_i)  motion_feat_o <= motion_energy_epoch_i;
            if (delta_hr_valid_i) delta_hr_feat_o <= delta_hr_i;
            if (mssd_valid_i)   mssd_feat_o <= mssd_i;

            // epoch strobe: emit a clean valid pulse using the last captured values
            if (enable_i && ml_update_gate_i) feat_valid_o <= 1'b1;
        end
    end

endmodule
