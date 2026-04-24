// SPDX-FileCopyrightText: © 2025 XXX Authors
// SPDX-License-Identifier: Apache-2.0

`default_nettype none

module chip_core #(
    parameter NUM_INPUT_PADS = 12,
    parameter NUM_BIDIR_PADS = 40,
    parameter NUM_ANALOG_PADS = 2
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

    inout  wire [NUM_ANALOG_PADS-1:0] analog     // Analog
);

    // Current pinout:
    // input_in[3:0] : test mode selector
    // bidir[0]      : alarm output
    // bidir[1]      : SPI flash clock output
    // bidir[2]      : SPI flash MOSI output
    // bidir[3]      : SPI flash CS_n output
    // bidir[4]      : SPI flash MISO input
    // bidir[5]      : I2C SCL input
    // bidir[6]      : I2C SDA open drain
    // bidir[22:7]   : 16-bit debug bus for test mode outputs
    // bidir[37]     : force Pico IRQ input, only used by test mode = 1010
    // bidir[38]     : force wake source input, only used by test mode = 1011
    // bidir[39]     : external test clock, only for test mode = 0101

    localparam int DEBUG_BUS_LO        = 7;
    localparam int DEBUG_BUS_HI        = 22;
    localparam int TEST_FORCE_IRQ_PAD  = 37;
    localparam int TEST_FORCE_WAKE_PAD = 38;
    localparam int TEST_CLK_PAD        = 39;

    logic [3:0] test_mode_w;
    logic       core_clk_w;

    logic [NUM_BIDIR_PADS-1:0] bidir_out_w;
    logic [NUM_BIDIR_PADS-1:0] bidir_oe_w;

    logic [15:0] debug_bus_w;

    logic sim_req_w;
    logic [6:0] sim_addr_w;
    logic [7:0] sim_reg_w;
    logic [7:0] sim_len_w;
    logic sim_write_w;
    logic [7:0] sim_wdata_w;

    logic feat_valid_w;
    logic signed [15:0] time_feat_w;
    logic signed [15:0] motion_feat_w;
    logic signed [15:0] delta_hr_feat_w;
    logic signed [15:0] rmssd_feat_w;

    logic ml_update_gate_w;
    logic [7:0] invalid_reason_w;

    logic spi_clk_w;
    logic spi_mosi_w;
    logic spi_cs_n_w;
    logic i2c_sda_drive_low_w;

    logic epoch_end_w;
    logic alarm_w;

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

    assign input_pu = '0;
    assign input_pd = '0;

    assign bidir_out = bidir_out_w;
    assign bidir_oe = bidir_oe_w;
    assign bidir_cs = '0;
    assign bidir_sl = '0;
    assign bidir_ie = ~bidir_oe_w;
    assign bidir_pu = '0;
    assign bidir_pd = '0;

    assign test_mode_w = input_in[3:0];
    assign test_force_irq_w = bidir_in[TEST_FORCE_IRQ_PAD];
    assign test_force_wake_w = bidir_in[TEST_FORCE_WAKE_PAD];

    // Use the external test clock only in the dedicated clock-test mode.
    assign core_clk_w = (test_mode_w == 4'b0101) ? bidir_in[TEST_CLK_PAD] : clk;

    always_comb begin
        debug_bus_w = '0;
        unique case (test_mode_w)
            4'b0000: begin
                debug_bus_w = '0;
            end

            4'b0001: begin
                // view processed RMSSD
                //these busses are not cut off, just writing [15:0 to be explicit]
                debug_bus_w = rmssd_feat_w[15:0];
            end

            4'b0010: begin
                // view processed deltaHR
                debug_bus_w = delta_hr_feat_w[15:0];

            end
            4'b0011: begin
                // view processed time feature
                debug_bus_w = time_feat_w[15:0];
            end

            4'b0100: begin
                // view processed motion feature
                debug_bus_w = motion_feat_w[15:0];
            end
            4'b0101: begin
                // external clock test mode. we do the muxing above,
                // may want to assign other signals here or put the internal clock as an output?
                debug_bus_w = '0;
            end

            4'b0110: begin 
                // view ML update gating
                debug_bus_w = {ml_update_gate_w, epoch_end_w, invalid_reason_w[7:0], 6'b0};
            end
            4'b0111: begin
                // observe pico state (ie fetch, read, write, stalled, trapped),
                // with the low 7 address bits for quick activity checks
                debug_bus_w = {pico_trap_w, pico_cpu_clk_en_w, pico_mem_valid_w,
                pico_mem_instr_w, pico_mem_ready_w, pico_mem_wstrb_w, pico_mem_addr_w[6:0]};
            end

            4'b1000: begin
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

            4'b1001: begin
                // observe pico sleep/irq with summary flags
                debug_bus_w = {pico_trap_w, pico_sleeping_w, pico_cpu_clk_en_w, |pico_irq_w, 12'b0};
            end

            4'b1010: begin 
                // force pico IRQ and watch memory activity
                debug_bus_w = {
                    test_force_irq_w, pico_trap_w, pico_cpu_clk_en_w, pico_mem_instr_w, pico_mem_valid_w, pico_mem_ready_w, pico_mem_addr_w[9:0]};
            end
            4'b1011: begin 
                // force pico wake and expose the wake/IRQ sources directly
                debug_bus_w = {test_force_wake_w, host_i2c_irq_event_w, ml_irq_w, timer_event_w, 12'b0};
            end


            // reserved test modes for future debug views
            4'b1100: begin 
                debug_bus_w = '0;
            end
            4'b1101: begin 
                debug_bus_w = '0;
            end
            4'b1110: begin 
                debug_bus_w = '0;
            end
            4'b1111: begin 

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

        if (test_mode_w != 4'b0000) begin
            bidir_out_w[DEBUG_BUS_HI:DEBUG_BUS_LO] = debug_bus_w;
            bidir_oe_w[DEBUG_BUS_HI:DEBUG_BUS_LO] = '1;
        end
    end

    top u_top (
        .clk_i                 (core_clk_w),
        .reset_i               (~rst_n),

        .i2c_scl_i             (bidir_in[5]),
        .i2c_sda_io            (),
        .i2c_sda_i             (bidir_in[6]),
        .i2c_sda_drive_low_o   (i2c_sda_drive_low_w),

        .sim_req_o             (),
        .sim_addr_o            (),
        .sim_reg_o             (),
        .sim_len_o             (),
        .sim_write_o           (),
        .sim_wdata_o           (),
        .sim_ack_i             (1'b0),
        .sim_rdata_i           (8'h00),
        .sim_rvalid_i          (1'b0),
        .sim_rlast_i           (1'b0),
        .sim_err_i             (1'b0),

        .feat_valid_o          (feat_valid_w),
        .time_feat_o           (time_feat_w),
        .motion_feat_o         (motion_feat_w),
        .delta_hr_feat_o       (delta_hr_feat_w),
        .mssd_feat_o          (rmssd_feat_w),

        .ml_update_gate_o      (ml_update_gate_w),
        .invalid_reason_o      (invalid_reason_w),

        .spi_clk_o             (spi_clk_w),
        .spi_mosi_o            (spi_mosi_w),
        .spi_miso_i            (bidir_in[4]),
        .spi_cs_n_o            (spi_cs_n_w),

        .epoch_end_o           (epoch_end_w),
        .alarm_o               (alarm_w),
        
        .test_force_irq_i      (test_force_irq_w),
        .test_force_wake_i     (test_force_wake_w),
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

`default_nettype wire
