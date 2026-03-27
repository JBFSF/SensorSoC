`timescale 1ns/1ps

module cos_lut_timer #(
    parameter integer LUT_BITS_MAX = 6
) (
    input  logic                   clk_i,
    input  logic                   rst_i,

    input  logic                   cfg_enable_i,
    input  logic [31:0]            seconds_in_night_i,
    input  logic                   seconds_valid_i,
    input  logic [31:0]            cfg_period_seconds_i,
    input  logic [2:0]             cfg_lut_bits_i,   // 4..6 supported
    input  logic [15:0]            cfg_scale_q15_i,  // 1.0 -> 32767

    output logic  signed [15:0]     cos_time_feat_o
);

    function automatic signed [15:0] cos_lut64;
        input [5:0] idx;
        begin
            case (idx)
                6'd0: cos_lut64 = 16'sd32767; 6'd1: cos_lut64 = 16'sd32609; 6'd2: cos_lut64 = 16'sd32137; 6'd3: cos_lut64 = 16'sd31356;
                6'd4: cos_lut64 = 16'sd30273; 6'd5: cos_lut64 = 16'sd28898; 6'd6: cos_lut64 = 16'sd27245; 6'd7: cos_lut64 = 16'sd25329;
                6'd8: cos_lut64 = 16'sd23170; 6'd9: cos_lut64 = 16'sd20787; 6'd10: cos_lut64 = 16'sd18204; 6'd11: cos_lut64 = 16'sd15446;
                6'd12: cos_lut64 = 16'sd12539; 6'd13: cos_lut64 = 16'sd9512; 6'd14: cos_lut64 = 16'sd6393; 6'd15: cos_lut64 = 16'sd3212;
                6'd16: cos_lut64 = 16'sd0; 6'd17: cos_lut64 = -16'sd3212; 6'd18: cos_lut64 = -16'sd6393; 6'd19: cos_lut64 = -16'sd9512;
                6'd20: cos_lut64 = -16'sd12539; 6'd21: cos_lut64 = -16'sd15446; 6'd22: cos_lut64 = -16'sd18204; 6'd23: cos_lut64 = -16'sd20787;
                6'd24: cos_lut64 = -16'sd23170; 6'd25: cos_lut64 = -16'sd25329; 6'd26: cos_lut64 = -16'sd27245; 6'd27: cos_lut64 = -16'sd28898;
                6'd28: cos_lut64 = -16'sd30273; 6'd29: cos_lut64 = -16'sd31356; 6'd30: cos_lut64 = -16'sd32137; 6'd31: cos_lut64 = -16'sd32609;
                6'd32: cos_lut64 = -16'sd32767; 6'd33: cos_lut64 = -16'sd32609; 6'd34: cos_lut64 = -16'sd32137; 6'd35: cos_lut64 = -16'sd31356;
                6'd36: cos_lut64 = -16'sd30273; 6'd37: cos_lut64 = -16'sd28898; 6'd38: cos_lut64 = -16'sd27245; 6'd39: cos_lut64 = -16'sd25329;
                6'd40: cos_lut64 = -16'sd23170; 6'd41: cos_lut64 = -16'sd20787; 6'd42: cos_lut64 = -16'sd18204; 6'd43: cos_lut64 = -16'sd15446;
                6'd44: cos_lut64 = -16'sd12539; 6'd45: cos_lut64 = -16'sd9512; 6'd46: cos_lut64 = -16'sd6393; 6'd47: cos_lut64 = -16'sd3212;
                6'd48: cos_lut64 = 16'sd0; 6'd49: cos_lut64 = 16'sd3212; 6'd50: cos_lut64 = 16'sd6393; 6'd51: cos_lut64 = 16'sd9512;
                6'd52: cos_lut64 = 16'sd12539; 6'd53: cos_lut64 = 16'sd15446; 6'd54: cos_lut64 = 16'sd18204; 6'd55: cos_lut64 = 16'sd20787;
                6'd56: cos_lut64 = 16'sd23170; 6'd57: cos_lut64 = 16'sd25329; 6'd58: cos_lut64 = 16'sd27245; 6'd59: cos_lut64 = 16'sd28898;
                6'd60: cos_lut64 = 16'sd30273; 6'd61: cos_lut64 = 16'sd31356; 6'd62: cos_lut64 = 16'sd32137; 6'd63: cos_lut64 = 16'sd32609;
            endcase
        end
    endfunction

    always @(posedge clk_i) begin
        logic [31:0] period_eff_v;
        logic [31:0] sec_mod_v;
        logic [5:0]  idx64_v, idx64_q_v;
        logic [2:0]  lut_bits_eff_v;
        logic [2:0]  drop_bits_v;
        logic signed [15:0] cos_raw_v;
        logic signed [31:0] cos_scaled_v;
        if (rst_i) begin
            cos_time_feat_o <= 16'sd0;
        end else if (seconds_valid_i) begin
            if (!cfg_enable_i) begin
                cos_time_feat_o <= 16'sd0;
            end else begin
                period_eff_v = (cfg_period_seconds_i == 32'd0) ? 32'd1 : cfg_period_seconds_i;
                sec_mod_v = seconds_in_night_i % period_eff_v;
                idx64_v = (sec_mod_v * 32'd64) / period_eff_v;

                lut_bits_eff_v = (cfg_lut_bits_i < 3'd4) ? 3'd4 : ((cfg_lut_bits_i > LUT_BITS_MAX[2:0]) ? LUT_BITS_MAX[2:0] : cfg_lut_bits_i);
                drop_bits_v = LUT_BITS_MAX[2:0] - lut_bits_eff_v;
                idx64_q_v = (idx64_v >> drop_bits_v) << drop_bits_v;

                cos_raw_v = cos_lut64(idx64_q_v);

                cos_scaled_v = (cos_raw_v * $signed({1'b0, cfg_scale_q15_i})) >>> 15;
                cos_time_feat_o <= cos_scaled_v[15:0];
            end
        end
    end

endmodule


