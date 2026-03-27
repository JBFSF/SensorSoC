// Reset controller for Sleep SoC (always-on domain)
// Goals:
//  - Centralize reset generation (glitch-free, timed reset pulses)
//  - Support multiple reset sources:
//      * external POR(Power-on-Reset) reset pin (active-low)         -> ext_resetn
//      * watchdog timeout request (pulse or level)                   -> wdt_reset_req
//      * software-requested CPU reset (pulse/level)                  -> sw_cpu_reset_req
//      * software-requested global/AON reset                         -> sw_aon_reset_req
//  - Produce two reset outputs:
//      * aon_resetn : resets always-on blocks (rare)
//      * cpu_resetn : resets CPU domain (CPU + SRAM + optional state)
//
// Notes:
//  - Runs on always-on clk.
//  - External reset: async assert, sync deassert (2-FF).
//  - Requests are latched and then "serviced" by issuing a reset pulse of HOLD_CYCLES.
//  - IMPORTANT FIX: use *_next when deciding to start a reset so 1-cycle pulses
//    are not missed due to nonblocking assignment timing.

`timescale 1ns/1ps

module reset_ctrl #(
    parameter integer HOLD_CYCLES    = 32,  // how long to hold reset active (in clk cycles)
    parameter         WDT_GLOBAL     = 1'b0 // 0: watchdog resets CPU only, 1: watchdog triggers global reset
)(
    input  wire        clk,             // always-on clock
    input  wire        ext_resetn,        // external reset pin, active-low (POR)
    input  wire        wdt_reset_req,     // watchdog timeout request (pulse or level)
    input  wire        sw_cpu_reset_req,  // SW request CPU reset (pulse or level)
    input  wire        sw_aon_reset_req,  // SW request global/AON reset (pulse or level)

    output wire        aon_resetn,        // active-low reset for always-on domain
    output wire        cpu_resetn,        // active-low reset for CPU domain
    output reg  [2:0]  reset_cause,       // latched "last reset cause"
    output wire        reset_in_progress
);

    // Reset cause encoding
    localparam [2:0] CAUSE_POR     = 3'd0;
    localparam [2:0] CAUSE_WDT     = 3'd1;
    localparam [2:0] CAUSE_SW_CPU  = 3'd2;
    localparam [2:0] CAUSE_SW_AON  = 3'd3;

    // -----------------------------
    // External reset synchronizer
    // async assert, sync deassert
    // -----------------------------
    reg [1:0] ext_sync;
    always @(posedge clk or negedge ext_resetn) begin
        if (!ext_resetn)
            ext_sync <= 2'b00;
        else
            ext_sync <= {ext_sync[0], 1'b1};
    end

    // treat as POR/reset-active until synchronized high for 2 cycles
    wire por_active = (ext_sync != 2'b11);

    // -----------------------------
    // Pending request latches
    // -----------------------------
    reg pend_wdt, pend_sw_cpu, pend_sw_aon;

    // *_next includes the current-cycle request pulse
    wire pend_wdt_next    = pend_wdt    | wdt_reset_req;
    wire pend_sw_cpu_next = pend_sw_cpu | sw_cpu_reset_req;
    wire pend_sw_aon_next = pend_sw_aon | sw_aon_reset_req;

    // -----------------------------
    // Reset hold counters
    // -----------------------------
    reg [$clog2(HOLD_CYCLES+1)-1:0] cpu_cnt;
    reg [$clog2(HOLD_CYCLES+1)-1:0] aon_cnt;

    // Reset is active if POR active, or counters nonzero.
    // Note: cpu_reset also asserted during AON reset.
    wire cpu_reset_active = por_active || (cpu_cnt != 0) || (aon_cnt != 0);
    wire aon_reset_active = por_active || (aon_cnt != 0);

    assign cpu_resetn = ~cpu_reset_active;
    assign aon_resetn = ~aon_reset_active;
    assign reset_in_progress = cpu_reset_active || aon_reset_active;

    // -----------------------------
    // Main control logic
    // Priority when starting a new reset pulse:
    //   1) POR (implicit)
    //   2) WDT
    //   3) SW AON (global)
    //   4) SW CPU
    // -----------------------------
    always @(posedge clk or negedge ext_resetn) begin
        if (!ext_resetn) begin
            // Immediate assert behavior for external reset
            pend_wdt    <= 1'b0;
            pend_sw_cpu <= 1'b0;
            pend_sw_aon <= 1'b0;

            cpu_cnt     <= '0;
            aon_cnt     <= '0;

            reset_cause <= CAUSE_POR;
        end else begin
            // 1) Latch any new requests (even while busy)
            pend_wdt    <= pend_wdt_next;
            pend_sw_cpu <= pend_sw_cpu_next;
            pend_sw_aon <= pend_sw_aon_next;

            // 2) If POR is active, hold everything in reset and clear counters.
            if (por_active) begin
                reset_cause <= CAUSE_POR;
                cpu_cnt     <= '0;
                aon_cnt     <= '0;
            end else begin
                // 3) Decrement counters if currently resetting
                if (cpu_cnt != 0)
                    cpu_cnt <= cpu_cnt - 1'b1;

                if (aon_cnt != 0)
                    aon_cnt <= aon_cnt - 1'b1;

                // 4) If idle (no timed reset active), service any pending request.
                // IMPORTANT FIX: use *_next so 1-cycle pulses aren't missed.
                if ((cpu_cnt == 0) && (aon_cnt == 0)) begin
                    if (pend_wdt_next) begin
                        reset_cause <= CAUSE_WDT;

                        cpu_cnt <= $unsigned(HOLD_CYCLES);

                        if (WDT_GLOBAL)
                            aon_cnt <= $unsigned(HOLD_CYCLES);

                        pend_wdt <= 1'b0; // consume
                    end
                    else if (pend_sw_aon_next) begin
                        reset_cause <= CAUSE_SW_AON;

                        aon_cnt <= $unsigned(HOLD_CYCLES);
                        cpu_cnt <= $unsigned(HOLD_CYCLES);

                        pend_sw_aon <= 1'b0; // consume
                    end
                    else if (pend_sw_cpu_next) begin
                        reset_cause <= CAUSE_SW_CPU;

                        cpu_cnt <= $unsigned(HOLD_CYCLES);

                        pend_sw_cpu <= 1'b0; // consume
                    end
                end
            end
        end
    end

endmodule