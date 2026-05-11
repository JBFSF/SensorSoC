// SPDX-FileCopyrightText: © 2025 XXX Authors
// SPDX-License-Identifier: Apache-2.0

    // Current pinout:
    // input_in[4:0] : test mode selector
    // input_in[10]  : clear sticky feature-valid status when SENSOR_SIM_PAD_BRIDGE is defined
    // input_in[11]  : sensor sim-bus pad bridge enable when SENSOR_SIM_PAD_BRIDGE is defined
    // bidir[0]      : alarm output
    // bidir[1]      : SPI flash clock output
    // bidir[2]      : SPI flash MOSI output
    // bidir[3]      : SPI flash CS_n output
    // bidir[4]      : SPI flash MISO input
    // bidir[5]      : I2C SCL input
    // bidir[6]      : I2C SDA open drain
    // bidir[22:7]   : 16-bit debug bus for test mode outputs
    // bidir[37]     : force Pico IRQ input, only used by test modes = 01010 / 11010
    // bidir[38]     : force wake source input, only used by test modes = 01011 / 11011
    // bidir[39]     : external test clock, used by the 1xxxx test-mode bank
    //
    // SENSOR_SIM_PAD_BRIDGE mode, enabled by input_in[11], repurposes bidir pads:
    // bidir[7:0]    : sim_wdata from chip on writes, sim_rdata from TB on reads
    // bidir[8]      : sim_req output from chip
    // bidir[9]      : sim_write output from chip
    // bidir[16:10]  : sim_addr output from chip
    // bidir[24:17]  : sim_reg output from chip
    // bidir[32:25]  : sim_len output from chip
    // bidir[33]     : sim_ack input to chip
    // bidir[34]     : sim_rvalid input to chip
    // bidir[35]     : sim_rlast input to chip
    // bidir[36]     : sim_err input to chip
    //
    // When SENSOR_SIM_PAD_BRIDGE is defined and input_in[11] is low:
    // bidir[33]     : sticky feature-valid-seen status, cleared by input_in[10]
    // bidir[34]     : live feat_valid pulse
    // bidir[35]     : live epoch_end pulse
    // bidir[36]     : live ml_update_gate status
    //
    // Test mode map:
    //   00000 : normal mode, PLL clock, debug bus disabled
    //   00001 : MSSD feature
    //   00010 : delta HR feature
    //   00011 : time feature
    //   00100 : motion feature
    //   00101 : pipeline smoke-test summary
    //   00110 : ML update gate / invalid-reason summary
    //   00111 : Pico core state and low address bits
    //   01000 : Pico MMIO write summary
    //   01001 : Pico sleep / IRQ summary
    //   01010 : force Pico IRQ view
    //   01011 : force wake-source view
    //   01100 : logit0
    //   01101 : logit1
    //   01110 : not used yet
    //   01111 : reserved
    //   10000 : normal mode, external clock, debug bus disabled
    //   1xxxx : same debug-bus mapping as 0xxxx, but clocked from bidir[39]

`default_nettype none

`ifdef SIM
`define CHIP_CORE_HAS_SENSOR_SIM_BUS
`endif
`ifdef SENSOR_SIM_PAD_BRIDGE
`define CHIP_CORE_HAS_SENSOR_SIM_BUS
`endif

module chip_core #(
    parameter NUM_INPUT_PADS = 12,
    parameter NUM_BIDIR_PADS = 40,
    parameter NUM_ANALOG_PADS = 2,
    parameter DEBUG_STIM_EN = 0,
    parameter CLK_HZ =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        1000,
    `else
        10_000_000,
    `endif
    parameter GT_CLK_HZ =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        1000,
    `else
        10_000_000,
    `endif
    parameter GT_EPOCH_HZ = 100,
    parameter GT_EPOCH_COUNT_MAX =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        300,
    `else
        1000,
    `endif
    parameter ACC_POLL_PERIOD_TICKS =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        8,
    `else
        50_000,
    `endif
    parameter PPG_POLL_PERIOD_TICKS =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        2,
    `else
        100,
    `endif
    parameter PPG_WATERMARK = 8,
    parameter PPG_MAX_BURST_SAMPLES = 32,
    parameter CFG_REFRACT_MS = 32'd250,
    parameter CFG_RR_MIN_MS = 32'd300,
    parameter CFG_RR_MAX_MS = 32'd2000,
    parameter CFG_Q_MIN_ACCEPT =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        8'd0,
    `else
        8'd10,
    `endif
    parameter CFG_BEAT_Q_MIN =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        8'd0,
    `else
        8'd16,
    `endif
    parameter CFG_MIN_VALID_FRAC =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        8'd0,
    `else
        8'd96,
    `endif
    parameter CFG_MAX_DOUBLE = 8'd4,
    parameter CFG_MAX_MISSED = 8'd3,
    parameter CFG_MOTION_HI_TH =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        16'hFFFF,
    `else
        16'd2000,
    `endif
    parameter CFG_MAX_MOTION_HI =
    `ifdef SENSOR_SIM_PAD_BRIDGE
        16'hFFFF,
    `else
        16'd3,
    `endif
    parameter MSSD_MIN_RR_COUNT = 1
)(
    `ifdef USE_POWER_PINS
    inout  wire VDD,
    inout  wire VSS,
    `endif

    input  wire clk,       // clock
    input  wire rst_n,     // reset (active low)

    input  wire [NUM_INPUT_PADS-1:0] input_in,   // Input value
    output wire [NUM_INPUT_PADS-1:0] input_pu,   // Pull-up
    output wire [NUM_INPUT_PADS-1:0] input_pd,   // Pull-down

    input  wire [NUM_BIDIR_PADS-1:0] bidir_in,   // Input value
    output wire [NUM_BIDIR_PADS-1:0] bidir_out,  // Output value
    output wire [NUM_BIDIR_PADS-1:0] bidir_oe,   // Output enable
    output wire [NUM_BIDIR_PADS-1:0] bidir_cs,   // Input type (0=CMOS Buffer, 1=Schmitt Trigger)
    output wire [NUM_BIDIR_PADS-1:0] bidir_sl,   // Slew rate (0=fast, 1=slow)
    output wire [NUM_BIDIR_PADS-1:0] bidir_ie,   // Input enable
    output wire [NUM_BIDIR_PADS-1:0] bidir_pu,   // Pull-up
    output wire [NUM_BIDIR_PADS-1:0] bidir_pd,   // Pull-down

    output wire       sim_req_o,
    output wire [6:0] sim_addr_o,
    output wire [7:0] sim_reg_o,
    output wire [7:0] sim_len_o,
    output wire       sim_write_o,
    output wire [7:0] sim_wdata_o,
    input  wire       sim_ack_i,
    input  wire [7:0] sim_rdata_i,
    input  wire       sim_rvalid_i,
    input  wire       sim_rlast_i,
    input  wire       sim_err_i,

    input  wire        debug_stim_override_en_i,
    input  wire [15:0] debug_stim_mssd_i,
    input  wire [15:0] debug_stim_delta_hr_i,
    input  wire [15:0] debug_stim_time_i,
    input  wire [15:0] debug_stim_motion_i,

    inout  wire [NUM_ANALOG_PADS-1:0] analog     // Analog
);


    localparam int DEBUG_BUS_LO        = 7;
    localparam int DEBUG_BUS_HI        = 22;
    localparam int TEST_FORCE_IRQ_PAD  = 37;
    localparam int TEST_FORCE_WAKE_PAD = 38;
    localparam int TEST_CLK_PAD        = 39;
    localparam int SENSOR_STATUS_CLEAR_PAD = 10;
    localparam int SENSOR_BRIDGE_EN_PAD = 11;
    localparam int SENSOR_DATA_LO      = 0;
    localparam int SENSOR_DATA_HI      = 7;
    localparam int SENSOR_REQ_PAD      = 8;
    localparam int SENSOR_WRITE_PAD    = 9;
    localparam int SENSOR_ADDR_LO      = 10;
    localparam int SENSOR_ADDR_HI      = 16;
    localparam int SENSOR_REG_LO       = 17;
    localparam int SENSOR_REG_HI       = 24;
    localparam int SENSOR_LEN_LO       = 25;
    localparam int SENSOR_LEN_HI       = 32;
    localparam int SENSOR_ACK_PAD      = 33;
    localparam int SENSOR_RVALID_PAD   = 34;
    localparam int SENSOR_RLAST_PAD    = 35;
    localparam int SENSOR_ERR_PAD      = 36;
    localparam int SENSOR_STATUS_FEAT_SEEN_PAD = 33;
    localparam int SENSOR_STATUS_FEAT_VALID_PAD = 34;
    localparam int SENSOR_STATUS_EPOCH_END_PAD = 35;
    localparam int SENSOR_STATUS_ML_GATE_PAD = 36;

    logic [4:0] test_mode_w;
    logic       core_clk_w;

    logic [NUM_BIDIR_PADS-1:0] bidir_out_w;
    logic [NUM_BIDIR_PADS-1:0] bidir_oe_w;

    logic [15:0] debug_bus_w;

    logic feat_valid_w;
    logic signed [15:0] time_feat_w;
    logic signed [15:0] motion_feat_w;
    logic signed [15:0] delta_hr_feat_w;
    logic signed [15:0] mssd_feat_w;
    logic signed [15:0] time_feat_top_w;
    logic signed [15:0] motion_feat_top_w;
    logic signed [15:0] delta_hr_feat_top_w;
    logic signed [15:0] mssd_feat_top_w;

    logic ml_update_gate_w;
    logic [7:0] invalid_reason_w;

    logic spi_clk_w;
    logic spi_mosi_w;
    logic spi_cs_n_w;
    logic i2c_sda_drive_low_w;

    logic epoch_end_w;
    logic alarm_w;

    logic [15:0] logit0_w;
    logic [15:0] logit1_w;

    logic        pico_trap_w;
    logic        pico_cpu_clk_en_w;
    logic        pico_mem_valid_w;
    logic        pico_mem_instr_w;
    logic        pico_mem_ready_w;
    logic [3:0]  pico_mem_wstrb_w;
    logic [31:0] pico_mem_addr_w;
    logic [31:0] pico_mem_wdata_w;
    logic [31:0] pico_irq_w;
    logic        pico_sleeping_w;
    logic        test_force_irq_w;
    logic        test_force_wake_w;
    logic        host_i2c_irq_event_w;
    logic        ml_irq_w;
    logic        timer_event_w;

    logic       sim_req_w;
    logic [6:0] sim_addr_w;
    logic [7:0] sim_reg_w;
    logic [7:0] sim_len_w;
    logic       sim_write_w;
    logic [7:0] sim_wdata_w;
    logic       sensor_bridge_en_w;
    logic       sensor_sim_ack_w;
    logic [7:0] sensor_sim_rdata_w;
    logic       sensor_sim_rvalid_w;
    logic       sensor_sim_rlast_w;
    logic       sensor_sim_err_w;
    logic       sensor_status_clear_w;
    logic       sensor_feature_valid_seen_q;

    assign sim_req_o   = sim_req_w;
    assign sim_addr_o  = sim_addr_w;
    assign sim_reg_o   = sim_reg_w;
    assign sim_len_o   = sim_len_w;
    assign sim_write_o = sim_write_w;
    assign sim_wdata_o = sim_wdata_w;

    `ifndef CHIP_CORE_HAS_SENSOR_SIM_BUS
        assign sim_req_w   = 1'b0;
        assign sim_addr_w  = 7'b0;
        assign sim_reg_w   = 8'b0;
        assign sim_len_w   = 8'b0;
        assign sim_write_w = 1'b0;
        assign sim_wdata_w = 8'b0;
    `endif


    assign input_pu = '0;
    assign input_pd = '0;

    assign bidir_out = bidir_out_w;
    assign bidir_oe = bidir_oe_w;
    assign bidir_cs = '0;
    assign bidir_sl = '0;
    assign bidir_ie = ~bidir_oe_w;
    assign bidir_pu = '0;
    assign bidir_pd = '0;

    assign test_mode_w = input_in[4:0];
    assign test_force_irq_w = bidir_in[TEST_FORCE_IRQ_PAD];
    assign test_force_wake_w = bidir_in[TEST_FORCE_WAKE_PAD];
    `ifdef SENSOR_SIM_PAD_BRIDGE
        assign sensor_bridge_en_w = input_in[SENSOR_BRIDGE_EN_PAD];
        assign sensor_status_clear_w = input_in[SENSOR_STATUS_CLEAR_PAD];
    `else
        assign sensor_bridge_en_w = 1'b0;
        assign sensor_status_clear_w = 1'b0;
    `endif
    assign sensor_sim_ack_w = sensor_bridge_en_w ? bidir_in[SENSOR_ACK_PAD] : sim_ack_i;
    assign sensor_sim_rdata_w = sensor_bridge_en_w ? bidir_in[SENSOR_DATA_HI:SENSOR_DATA_LO] : sim_rdata_i;
    assign sensor_sim_rvalid_w = sensor_bridge_en_w ? bidir_in[SENSOR_RVALID_PAD] : sim_rvalid_i;
    assign sensor_sim_rlast_w = sensor_bridge_en_w ? bidir_in[SENSOR_RLAST_PAD] : sim_rlast_i;
    assign sensor_sim_err_w = sensor_bridge_en_w ? bidir_in[SENSOR_ERR_PAD] : sim_err_i;

    // Upper-half test modes run from the external test clock.
    assign core_clk_w = test_mode_w[4] ? bidir_in[TEST_CLK_PAD] : clk;

    assign time_feat_w = (DEBUG_STIM_EN && debug_stim_override_en_i) ? $signed(debug_stim_time_i) : time_feat_top_w;
    assign motion_feat_w = (DEBUG_STIM_EN && debug_stim_override_en_i) ? $signed(debug_stim_motion_i) : motion_feat_top_w;
    assign delta_hr_feat_w = (DEBUG_STIM_EN && debug_stim_override_en_i) ? $signed(debug_stim_delta_hr_i) : delta_hr_feat_top_w;
    assign mssd_feat_w = (DEBUG_STIM_EN && debug_stim_override_en_i) ? $signed(debug_stim_mssd_i) : mssd_feat_top_w;

    `ifdef SENSOR_SIM_PAD_BRIDGE
        always_ff @(posedge core_clk_w or negedge rst_n) begin
            if (!rst_n) begin
                sensor_feature_valid_seen_q <= 1'b0;
            end else if (sensor_status_clear_w) begin
                sensor_feature_valid_seen_q <= 1'b0;
            end else if (feat_valid_w) begin
                sensor_feature_valid_seen_q <= 1'b1;
            end
        end
    `else
        assign sensor_feature_valid_seen_q = 1'b0;
    `endif

    always_comb begin
        debug_bus_w = '0;
        unique case (test_mode_w)
            5'b00000: begin
                //normal mode, pll clock
                debug_bus_w = '0;
            end

            5'b00001: begin
                // view processed MSSD
                //these busses are not cut off, just writing [15:0 to be explicit]
                debug_bus_w = mssd_feat_w[15:0];
            end

            5'b00010: begin
                // view processed deltaHR
                debug_bus_w = delta_hr_feat_w[15:0];

            end
            5'b00011: begin
                // view processed time feature
                debug_bus_w = time_feat_w[15:0];
            end

            5'b00100: begin
                // view processed motion feature
                debug_bus_w = motion_feat_w[15:0];
            end
            5'b00101: begin
                // smoke test, to see that important signals are there, and updating
                debug_bus_w = {|mssd_feat_w, |delta_hr_feat_w, |time_feat_w, |motion_feat_w, feat_valid_w, |logit0_w, |logit1_w, ml_update_gate_w, epoch_end_w, alarm_w, 6'b000000};
            end

            5'b00110: begin 
                // view ML update gating
                // this was made by chatgpt I'm not too sure what these signals do
                debug_bus_w = {ml_update_gate_w, epoch_end_w, invalid_reason_w[7:0], 6'b0};
            end
            5'b00111: begin
                // observe pico state (ie fetch, read, write, stalled, trapped),
                // with the low 7 address bits for quick activity checks
                debug_bus_w = {pico_trap_w, pico_cpu_clk_en_w, pico_mem_valid_w,
                pico_mem_instr_w, pico_mem_ready_w, pico_mem_wstrb_w, pico_mem_addr_w[6:0]};
            end

            5'b01000: begin
                // observe pico MMIO writes with the low byte of the address and
                // low nibble of write data, plus a few key qualifiers
                debug_bus_w = {
                    pico_mem_valid_w && (pico_mem_wstrb_w != 4'b0000),
                    pico_trap_w,
                    |pico_mem_wstrb_w,
                    pico_mem_wstrb_w == 4'hF,
                    pico_mem_addr_w[7:0],
                    pico_mem_wdata_w[3:0]
                };
            end

            5'b01001: begin
                // observe pico sleep/irq with summary flags
                debug_bus_w = {pico_trap_w, pico_sleeping_w, pico_cpu_clk_en_w, |pico_irq_w, 12'b0};
            end

            5'b01010: begin 
                // force pico IRQ and watch memory activity
                debug_bus_w = {
                    test_force_irq_w, pico_trap_w, pico_cpu_clk_en_w, pico_mem_instr_w, pico_mem_valid_w, pico_mem_ready_w, pico_mem_addr_w[9:0]};
            end
            5'b01011: begin 
                // force pico wake and expose the wake/IRQ sources directly
                debug_bus_w = {test_force_wake_w, host_i2c_irq_event_w, ml_irq_w, timer_event_w, 12'b0};
            end


            // reserved test modes for future debug views
            5'b01100: begin 
                debug_bus_w = logit0_w[15:0];
            end
            5'b01101: begin 
                debug_bus_w = logit1_w[15:0];
            end

            5'b01110: begin 
                //not yet used
                debug_bus_w = '0;
            end
            5'b01111: begin
                //not yet used 
                debug_bus_w = '0;
            end

            5'b10000: begin
                // normal mode, with external clock
                debug_bus_w = '0;
            end

            5'b10001: begin
                // view processed MSSD
                //these busses are not cut off, just writing [15:0 to be explicit]
                debug_bus_w = mssd_feat_w[15:0];
            end

            5'b10010: begin
                // view processed deltaHR
                debug_bus_w = delta_hr_feat_w[15:0];

            end
            5'b10011: begin
                // view processed time feature
                debug_bus_w = time_feat_w[15:0];
            end

            5'b10100: begin
                // view processed motion feature
                debug_bus_w = motion_feat_w[15:0];
            end
            5'b10101: begin
                //  // smoke test, to see that important signals are there, and updating
                debug_bus_w = {|mssd_feat_w, |delta_hr_feat_w, |time_feat_w, |motion_feat_w, feat_valid_w, |logit0_w, |logit1_w, ml_update_gate_w, epoch_end_w, alarm_w, 6'b000000};
            end

            5'b10110: begin 
                // view ML update gating
                // this was made by chatgpt I'm not too sure what these signals do
                debug_bus_w = {ml_update_gate_w, epoch_end_w, invalid_reason_w[7:0], 6'b0};
            end
            5'b10111: begin
                // observe pico state (ie fetch, read, write, stalled, trapped),
                // with the low 7 address bits for quick activity checks
                debug_bus_w = {pico_trap_w, pico_cpu_clk_en_w, pico_mem_valid_w,
                pico_mem_instr_w, pico_mem_ready_w, pico_mem_wstrb_w, pico_mem_addr_w[6:0]};
            end

            5'b11000: begin
                // observe pico MMIO writes with the low byte of the address and
                // low nibble of write data, plus a few key qualifiers
                debug_bus_w = {
                    pico_mem_valid_w && (pico_mem_wstrb_w != 4'b0000),
                    pico_trap_w,
                    |pico_mem_wstrb_w,
                    pico_mem_wstrb_w == 4'hF,
                    pico_mem_addr_w[7:0],
                    pico_mem_wdata_w[3:0]
                };
            end
            
            5'b11001: begin
                // observe pico sleep/irq with summary flags
                debug_bus_w = {pico_trap_w, pico_sleeping_w, pico_cpu_clk_en_w, |pico_irq_w, 12'b0};
            end

            5'b11010: begin 
                // force pico IRQ and watch memory activity
                debug_bus_w = {
                    test_force_irq_w, pico_trap_w, pico_cpu_clk_en_w, pico_mem_instr_w, pico_mem_valid_w, pico_mem_ready_w, pico_mem_addr_w[9:0]};
            end
            5'b11011: begin 
                // force pico wake and expose the wake/IRQ sources directly
                debug_bus_w = {test_force_wake_w, host_i2c_irq_event_w, ml_irq_w, timer_event_w, 12'b0};
            end


            // reserved test modes for future debug views
            5'b11100: begin 
                debug_bus_w = logit0_w[15:0];
            end
            5'b11101: begin 
                debug_bus_w = logit1_w[15:0];
            end

            5'b11110: begin 
                //not yet used
                debug_bus_w = '0;
            end

            5'b11111: begin
                //not yet used 
                debug_bus_w = '0;
            end
            default: begin
                debug_bus_w = '0; 
            end
        endcase
    end

    always_comb begin
        bidir_out_w = '0;
        bidir_oe_w  = '0;

        bidir_out_w[0] = alarm_w;
        bidir_out_w[1] = spi_clk_w;
        bidir_out_w[2] = spi_mosi_w;
        bidir_out_w[3] = spi_cs_n_w;
        bidir_out_w[6] = 1'b0;

        bidir_oe_w[0] = 1'b1;
        bidir_oe_w[1] = 1'b1;
        bidir_oe_w[2] = 1'b1;
        bidir_oe_w[3] = 1'b1;
        bidir_oe_w[6] = i2c_sda_drive_low_w;

        if (test_mode_w[3:0] != 4'b0000) begin
            bidir_out_w[DEBUG_BUS_HI:DEBUG_BUS_LO] = debug_bus_w;
            bidir_oe_w[DEBUG_BUS_HI:DEBUG_BUS_LO] = '1;
        end

        `ifdef SENSOR_SIM_PAD_BRIDGE
        if (!sensor_bridge_en_w) begin
            bidir_out_w[SENSOR_STATUS_FEAT_SEEN_PAD] = sensor_feature_valid_seen_q;
            bidir_out_w[SENSOR_STATUS_FEAT_VALID_PAD] = feat_valid_w;
            bidir_out_w[SENSOR_STATUS_EPOCH_END_PAD] = epoch_end_w;
            bidir_out_w[SENSOR_STATUS_ML_GATE_PAD] = ml_update_gate_w;
            bidir_oe_w[SENSOR_STATUS_FEAT_SEEN_PAD] = 1'b1;
            bidir_oe_w[SENSOR_STATUS_FEAT_VALID_PAD] = 1'b1;
            bidir_oe_w[SENSOR_STATUS_EPOCH_END_PAD] = 1'b1;
            bidir_oe_w[SENSOR_STATUS_ML_GATE_PAD] = 1'b1;
        end
        `endif

        if (sensor_bridge_en_w) begin
            bidir_out_w[SENSOR_DATA_HI:SENSOR_DATA_LO] = sim_wdata_w;
            bidir_out_w[SENSOR_REQ_PAD] = sim_req_w;
            bidir_out_w[SENSOR_WRITE_PAD] = sim_write_w;
            bidir_out_w[SENSOR_ADDR_HI:SENSOR_ADDR_LO] = sim_addr_w;
            bidir_out_w[SENSOR_REG_HI:SENSOR_REG_LO] = sim_reg_w;
            bidir_out_w[SENSOR_LEN_HI:SENSOR_LEN_LO] = sim_len_w;

            bidir_oe_w[SENSOR_DATA_HI:SENSOR_DATA_LO] = {8{sim_req_w && sim_write_w}};
            bidir_oe_w[SENSOR_REQ_PAD] = 1'b1;
            bidir_oe_w[SENSOR_WRITE_PAD] = 1'b1;
            bidir_oe_w[SENSOR_ADDR_HI:SENSOR_ADDR_LO] = '1;
            bidir_oe_w[SENSOR_REG_HI:SENSOR_REG_LO] = '1;
            bidir_oe_w[SENSOR_LEN_HI:SENSOR_LEN_LO] = '1;
            bidir_oe_w[SENSOR_ACK_PAD] = 1'b0;
            bidir_oe_w[SENSOR_RVALID_PAD] = 1'b0;
            bidir_oe_w[SENSOR_RLAST_PAD] = 1'b0;
            bidir_oe_w[SENSOR_ERR_PAD] = 1'b0;
        end
    end

    top #(
        .CLK_HZ(CLK_HZ),
        .GT_CLK_HZ(GT_CLK_HZ),
        .GT_EPOCH_HZ(GT_EPOCH_HZ),
        .GT_EPOCH_COUNT_MAX(GT_EPOCH_COUNT_MAX),
        .ACC_POLL_PERIOD_TICKS(ACC_POLL_PERIOD_TICKS),
        .PPG_POLL_PERIOD_TICKS(PPG_POLL_PERIOD_TICKS),
        .PPG_WATERMARK(PPG_WATERMARK),
        .PPG_MAX_BURST_SAMPLES(PPG_MAX_BURST_SAMPLES),
        .CFG_REFRACT_MS(CFG_REFRACT_MS),
        .CFG_RR_MIN_MS(CFG_RR_MIN_MS),
        .CFG_RR_MAX_MS(CFG_RR_MAX_MS),
        .CFG_Q_MIN_ACCEPT(CFG_Q_MIN_ACCEPT),
        .CFG_BEAT_Q_MIN(CFG_BEAT_Q_MIN),
        .CFG_MIN_VALID_FRAC(CFG_MIN_VALID_FRAC),
        .CFG_MAX_DOUBLE(CFG_MAX_DOUBLE),
        .CFG_MAX_MISSED(CFG_MAX_MISSED),
        .CFG_MOTION_HI_TH(CFG_MOTION_HI_TH),
        .CFG_MAX_MOTION_HI(CFG_MAX_MOTION_HI),
        .MSSD_MIN_RR_COUNT(MSSD_MIN_RR_COUNT)
    ) u_top (
        `ifdef USE_POWER_PINS
        .VDD                   (VDD),
        .VSS                   (VSS),
        `endif
        .clk_i                 (core_clk_w),
        .reset_i               (~rst_n),

        .i2c_scl_i             (bidir_in[5]),
        .i2c_sda_io            (),
        .i2c_sda_i             (bidir_in[6]),
        .i2c_sda_drive_low_o   (i2c_sda_drive_low_w),

        `ifdef CHIP_CORE_HAS_SENSOR_SIM_BUS
            .sim_req_o    (sim_req_w),
            .sim_addr_o   (sim_addr_w),
            .sim_reg_o    (sim_reg_w),
            .sim_len_o    (sim_len_w),
            .sim_write_o  (sim_write_w),
            .sim_wdata_o  (sim_wdata_w),
            .sim_ack_i    (sensor_sim_ack_w),
            .sim_rdata_i  (sensor_sim_rdata_w),
            .sim_rvalid_i (sensor_sim_rvalid_w),
            .sim_rlast_i  (sensor_sim_rlast_w),
            .sim_err_i    (sensor_sim_err_w),
        `endif
        .feat_valid_o          (feat_valid_w),
        .time_feat_o           (time_feat_top_w),
        .motion_feat_o         (motion_feat_top_w),
        .delta_hr_feat_o       (delta_hr_feat_top_w),
        .mssd_feat_o           (mssd_feat_top_w),

        .ml_update_gate_o      (ml_update_gate_w),
        .invalid_reason_o      (invalid_reason_w),

        .spi_clk_o             (spi_clk_w),
        .spi_mosi_o            (spi_mosi_w),
        .spi_miso_i            (bidir_in[4]),
        .spi_cs_n_o            (spi_cs_n_w),
        .boot_spi_clk_o        (),
        .boot_spi_mosi_o       (),
        .boot_spi_miso_i       (1'b1),
        .boot_spi_cs_n_o       (),

        .epoch_end_o           (epoch_end_w),
        .alarm_o               (alarm_w),

        .logit0                (logit0_w),
        .logit1                (logit1_w),
        .test_mode_i           (test_mode_w[3:0]),
        
        .test_force_irq_i      (test_force_irq_w),
        .test_force_wake_i     (test_force_wake_w),
        .test_irq_src_i        (3'b000),
        .irq_eoi_o             (),
        .boot_done_o           (),
        .pico_trap_o           (pico_trap_w),
        .pico_cpu_clk_en_o     (pico_cpu_clk_en_w),
        .pico_mem_valid_o      (pico_mem_valid_w),
        .pico_mem_instr_o      (pico_mem_instr_w),
        .pico_mem_ready_o      (pico_mem_ready_w),
        .pico_mem_wstrb_o      (pico_mem_wstrb_w),
        .pico_mem_addr_o       (pico_mem_addr_w),
        .pico_mem_wdata_o      (pico_mem_wdata_w),
        .pico_irq_o            (pico_irq_w),
        .pico_sleeping_o       (pico_sleeping_w),
        .host_i2c_irq_event_o  (host_i2c_irq_event_w),
        .ml_irq_o              (ml_irq_w),
        .timer_event_o         (timer_event_w)

    );

    //analog pads unused

    logic unused_analog;
    assign unused_analog = &analog;

endmodule
