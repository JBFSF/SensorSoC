`timescale 1ns/1ps

// Cocotb wrapper for top_fsm.
// All signals driven/sampled by test_top_fsm.py.

module tb_top_fsm;

    reg        clk_i           = 1'b0;
    reg        resetn_i        = 1'b0;
    reg  [3:0] test_mode_i     = 4'b0000;

    reg        start_i         = 1'b0;
    reg        boot_done_i     = 1'b0;
    reg        feat_valid_i    = 1'b0;
    reg        ml_irq_i        = 1'b0;

    reg        sleep_req_i     = 1'b0;
    reg        mem_valid_i     = 1'b0;
    reg        irqc_wake_req_i = 1'b0;
    reg        cpu_alarm_i     = 1'b0;

    wire       watchdog_o;
    wire       feat_en_o;
    wire       ml_en_o;
    wire       cpu_en_o;
    wire       sleeping_o;
    wire       alarm_o;

    top_fsm dut (
        .clk_i           (clk_i),
        .resetn_i        (resetn_i),
        .test_mode_i     (test_mode_i),
        .start_i         (start_i),
        .boot_done_i     (boot_done_i),
        .feat_valid_i    (feat_valid_i),
        .ml_irq_i        (ml_irq_i),
        .sleep_req_i     (sleep_req_i),
        .mem_valid_i     (mem_valid_i),
        .irqc_wake_req_i (irqc_wake_req_i),
        .cpu_alarm_i     (cpu_alarm_i),
        .watchdog_o      (watchdog_o),
        .feat_en_o       (feat_en_o),
        .ml_en_o         (ml_en_o),
        .cpu_en_o        (cpu_en_o),
        .sleeping_o      (sleeping_o),
        .alarm_o         (alarm_o)
    );

    initial begin
        $dumpfile("sim/waves/tb_top_fsm.vcd");
        $dumpvars(0, tb_top_fsm);
    end

endmodule
