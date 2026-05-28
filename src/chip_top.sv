// SPDX-FileCopyrightText: © 2025 Project Template Contributors
// SPDX-License-Identifier: Apache-2.0

`default_nettype none

`include "slot_defines.svh"

module chip_top #(
    // Power/ground pads for core and I/O
    parameter NUM_DVDD_PADS = `NUM_DVDD_PADS,
    parameter NUM_DVSS_PADS = `NUM_DVSS_PADS,

    // Signal pads
    parameter NUM_INPUT_PADS  = `NUM_INPUT_PADS,
    parameter NUM_BIDIR_PADS  = `NUM_BIDIR_PADS,
    parameter NUM_ANALOG_PADS = `NUM_ANALOG_PADS,

    // Simulation / timing overrides forwarded to chip_core -> top
    parameter FIRMWARE_HEX          = "",
    parameter WEIGHT_INIT_HEX       = "",
    parameter integer CLK_HZ                = 10_000_000,
    parameter integer GT_CLK_HZ             = 10_000_000,
    parameter integer GT_EPOCH_HZ           = 100,
    parameter integer GT_EPOCH_COUNT_MAX    = 1000,
    parameter integer ACC_POLL_PERIOD_TICKS = 50_000,
    parameter integer PPG_POLL_PERIOD_TICKS = 100,
    parameter integer PPG_WATERMARK         = 8,
    parameter integer PPG_MAX_BURST_SAMPLES = 32,
    parameter [15:0]  CFG_MOTION_HI_TH      = 16'd2000,
    parameter [15:0]  CFG_MAX_MOTION_HI     = 16'd3
    parameter integer TIMER_RELOAD_DEFAULT  = 5_000_000
    )(
    `ifdef USE_POWER_PINS
    inout  wire VDD,
    inout  wire VSS,
    `endif

    inout  wire clk_PAD,
    inout  wire rst_n_PAD,
    
    inout  wire [NUM_INPUT_PADS-1:0] input_PAD,
    inout  wire [NUM_BIDIR_PADS-1:0] bidir_PAD,

    inout  wire [NUM_ANALOG_PADS-1:0] analog_PAD

    `ifdef SIM
    ,
    output wire         sim_req_o,
    output wire [6:0]   sim_addr_o,
    output wire [7:0]   sim_reg_o,
    output wire [7:0]   sim_len_o,
    output wire         sim_write_o,
    output wire [7:0]   sim_wdata_o,
    input  wire         sim_ack_i,
    input  wire [7:0]   sim_rdata_i,
    input  wire         sim_rvalid_i,
    input  wire         sim_rlast_i,
    input  wire         sim_err_i
    `endif
);

    wire clk_PAD2CORE;
    wire rst_n_PAD2CORE;
    
    wire [NUM_INPUT_PADS-1:0] input_PAD2CORE;
    wire [NUM_INPUT_PADS-1:0] input_CORE2PAD_PU;
    wire [NUM_INPUT_PADS-1:0] input_CORE2PAD_PD;

    wire [NUM_BIDIR_PADS-1:0] bidir_PAD2CORE;
    wire [NUM_BIDIR_PADS-1:0] bidir_CORE2PAD;
    wire [NUM_BIDIR_PADS-1:0] bidir_CORE2PAD_OE;
    wire [NUM_BIDIR_PADS-1:0] bidir_CORE2PAD_CS;
    wire [NUM_BIDIR_PADS-1:0] bidir_CORE2PAD_SL;
    wire [NUM_BIDIR_PADS-1:0] bidir_CORE2PAD_IE;
    wire [NUM_BIDIR_PADS-1:0] bidir_CORE2PAD_PU;
    wire [NUM_BIDIR_PADS-1:0] bidir_CORE2PAD_PD;

    // Power/ground pad instances
    generate
    for (genvar i=0; i<NUM_DVDD_PADS; i++) begin : dvdd_pads
        (* keep *)
        gf180mcu_ws_io__dvdd pad (
            `ifdef USE_POWER_PINS
            .DVDD   (VDD),
            .DVSS   (VSS),
            .VSS    (VSS)
            `endif
        );
    end
    
    for (genvar i=0; i<NUM_DVSS_PADS; i++) begin : dvss_pads
        (* keep *)
        gf180mcu_ws_io__dvss pad (
            `ifdef USE_POWER_PINS
            .DVDD   (VDD),
            .DVSS   (VSS),
            .VDD    (VDD)
            `endif
        );
    end
    endgenerate

    // Signal IO pad instances

    // Schmitt trigger
    gf180mcu_fd_io__in_s clk_pad (
        `ifdef USE_POWER_PINS
        .DVDD   (VDD),
        .DVSS   (VSS),
        .VDD    (VDD),
        .VSS    (VSS),
        `endif
    
        .Y      (clk_PAD2CORE),
        .PAD    (clk_PAD),
        
        .PU     (1'b0),
        .PD     (1'b0)
    );
    
    // Normal input
    gf180mcu_fd_io__in_c rst_n_pad (
        `ifdef USE_POWER_PINS
        .DVDD   (VDD),
        .DVSS   (VSS),
        .VDD    (VDD),
        .VSS    (VSS),
        `endif
    
        .Y      (rst_n_PAD2CORE),
        .PAD    (rst_n_PAD),
        
        .PU     (1'b0),
        .PD     (1'b0)
    );

    generate
    for (genvar i=0; i<NUM_INPUT_PADS; i++) begin : inputs
        (* keep *)
        gf180mcu_fd_io__in_c pad (
            `ifdef USE_POWER_PINS
            .DVDD   (VDD),
            .DVSS   (VSS),
            .VDD    (VDD),
            .VSS    (VSS),
            `endif
        
            .Y      (input_PAD2CORE[i]),
            .PAD    (input_PAD[i]),
            
            .PU     (input_CORE2PAD_PU[i]),
            .PD     (input_CORE2PAD_PD[i])
        );
    end
    endgenerate

    generate
    for (genvar i=0; i<NUM_BIDIR_PADS; i++) begin : bidir
        (* keep *)
        gf180mcu_fd_io__bi_24t pad (
            `ifdef USE_POWER_PINS
            .DVDD   (VDD),
            .DVSS   (VSS),
            .VDD    (VDD),
            .VSS    (VSS),
            `endif
        
            .A      (bidir_CORE2PAD[i]),
            .OE     (bidir_CORE2PAD_OE[i]),
            .Y      (bidir_PAD2CORE[i]),
            .PAD    (bidir_PAD[i]),
            
            .CS     (bidir_CORE2PAD_CS[i]),
            .SL     (bidir_CORE2PAD_SL[i]),
            .IE     (bidir_CORE2PAD_IE[i]),

            .PU     (bidir_CORE2PAD_PU[i]),
            .PD     (bidir_CORE2PAD_PD[i])
        );
    end
    endgenerate

    generate
    for (genvar i=0; i<NUM_ANALOG_PADS; i++) begin : analog
        (* keep *)
        gf180mcu_fd_io__asig_5p0 pad (
            `ifdef USE_POWER_PINS
            .DVDD   (VDD),
            .DVSS   (VSS),
            .VDD    (VDD),
            .VSS    (VSS),
            `endif
            .ASIG5V (analog_PAD[i])
        );
    end
    endgenerate

    // Core design

    chip_core #(
        .NUM_INPUT_PADS         (NUM_INPUT_PADS),
        .NUM_BIDIR_PADS         (NUM_BIDIR_PADS),
        .NUM_ANALOG_PADS        (NUM_ANALOG_PADS),
        .DEBUG_STIM_EN          (0),
        .FIRMWARE_HEX           (FIRMWARE_HEX),
        .WEIGHT_INIT_HEX        (WEIGHT_INIT_HEX),
        .CLK_HZ                 (CLK_HZ),
        .GT_CLK_HZ              (GT_CLK_HZ),
        .GT_EPOCH_HZ            (GT_EPOCH_HZ),
        .GT_EPOCH_COUNT_MAX     (GT_EPOCH_COUNT_MAX),
        .ACC_POLL_PERIOD_TICKS  (ACC_POLL_PERIOD_TICKS),
        .PPG_POLL_PERIOD_TICKS  (PPG_POLL_PERIOD_TICKS),
        .PPG_WATERMARK          (PPG_WATERMARK),
        .PPG_MAX_BURST_SAMPLES  (PPG_MAX_BURST_SAMPLES),
        .CFG_MOTION_HI_TH       (CFG_MOTION_HI_TH),
        .CFG_MAX_MOTION_HI      (CFG_MAX_MOTION_HI)
        .TIMER_RELOAD_DEFAULT   (TIMER_RELOAD_DEFAULT)
    ) i_chip_core (
        `ifdef USE_POWER_PINS
        .VDD        (VDD),
        .VSS        (VSS),
        `endif

        .clk        (clk_PAD2CORE),
        .rst_n      (rst_n_PAD2CORE),

        .input_in   (input_PAD2CORE),
        .input_pu   (input_CORE2PAD_PU),
        .input_pd   (input_CORE2PAD_PD),

        .bidir_in   (bidir_PAD2CORE),
        .bidir_out  (bidir_CORE2PAD),
        .bidir_oe   (bidir_CORE2PAD_OE),
        .bidir_cs   (bidir_CORE2PAD_CS),
        .bidir_sl   (bidir_CORE2PAD_SL),
        .bidir_ie   (bidir_CORE2PAD_IE),
        .bidir_pu   (bidir_CORE2PAD_PU),
        .bidir_pd   (bidir_CORE2PAD_PD),

        `ifdef SIM
            .sim_req_o    (sim_req_o),
            .sim_addr_o   (sim_addr_o),
            .sim_reg_o    (sim_reg_o),
            .sim_len_o    (sim_len_o),
            .sim_write_o  (sim_write_o),
            .sim_wdata_o  (sim_wdata_o),
            .sim_ack_i    (sim_ack_i),
            .sim_rdata_i  (sim_rdata_i),
            .sim_rvalid_i (sim_rvalid_i),
            .sim_rlast_i  (sim_rlast_i),
            .sim_err_i    (sim_err_i),
        `endif

        .debug_stim_override_en_i (1'b0),
        .debug_stim_mssd_i        (16'h0000),
        .debug_stim_delta_hr_i    (16'h0000),
        .debug_stim_time_i        (16'h0000),
        .debug_stim_motion_i      (16'h0000),

        .analog     (analog_PAD)
    );
    
    // Chip ID - do not remove, necessary for tapeout
    (* keep *)
    gf180mcu_ws_ip__id chip_id ();
    
    // wafer.space logo - can be removed
    (* keep *)
    gf180mcu_ws_ip__logo wafer_space_logo ();

endmodule

`default_nettype wire
