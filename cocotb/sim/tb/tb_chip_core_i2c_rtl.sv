`timescale 1ns/1ps
`default_nettype none

// Level 2 pad-routing testbench for the synthesis path of chip_core.sv.
// Compiled WITHOUT -DSIM — the real I2C bit-banging state machine runs.
//
// Goal: prove that bidir[23] carries SCL (push-pull) and bidir[24] carries
// SDA (open-drain) for the sensor I2C bus all the way through chip_core.
//
// How it works:
//   - input_in[3:0] = 4'b0001 forces top_fsm into FEAT_ONLY → feat_en = 1.
//   - accel_reader immediately issues two init writes (CTRL1, RANGE), then polls.
//   - An I2C slave BFM monitors bidir_out[23]/bidir_oe[24]/bidir_in[24],
//     ACKs the init writes, and drives back 6 data bytes for the first poll read.
//   - PASS when: SCL toggles on bidir_out[23], ACK round-trips work via bidir[24],
//     and the slave BFM sees the correct I2C addresses throughout.
//
// Compile (from cocotb/):
//   iverilog -g2012 -I ../src -s tb_chip_core_i2c_rtl -o sim/build/tb_chip_core_i2c_rtl.vvp \
//       sim/tb/tb_chip_core_i2c_rtl.sv \
//       ../src/chip_core.sv \
//       ../src/top.sv ../src/top_fsm.v ../src/i2c_master.sv \
//       ../src/accel_reader.sv ../src/motion_process.sv \
//       ../src/ppg_fifo_reader.sv ../src/ppg_process.sv \
//       ../src/mssd_engine.sv ../src/signal_quality.sv \
//       ../src/feature_engine.sv ../src/globaltimer.sv \
//       ../src/simple_sram.v ../src/spi_boot_ctrl.v \
//       ../ip/picorv32.v \
//       ../src/test_mmio.v ../src/timer_mmio.v \
//       ../src/ml_axil_bridge_mmio.v ../src/weight_flash_axi.v \
//       ../src/irq_ctrl_mmio.v ../src/alarm_mmio.v \
//       ../src/taketwo_wrap.v ../src/taketwo.v \
//       ../src/pwrctrl_mmio.v \
//       ../src/gf180mcu_fd_ip_sram__sram512x8m8wm1.v
//   vvp sim/build/tb_chip_core_i2c_rtl.vvp

module tb_chip_core_i2c_rtl;

    // CLK_HZ=1_000_000 → QUARTER=2, HALF=4 → one I2C bit = 8 system clocks.
    localparam integer TB_CLK_HZ     = 1_000_000;
    // Short poll period so the first accel read happens quickly after init.
    localparam integer TB_POLL_TICKS = 50;
    // PPG poll period kept large so PPG never fires during this accel-focused test.
    localparam integer TB_PPG_POLL_TICKS = 500_000;

    // Pad indices — must match chip_core.sv localparams.
    localparam integer SENSOR_SCL_PAD = 23;
    localparam integer SENSOR_SDA_PAD = 24;

    // Expected I2C traffic (from top.sv accel_reader instantiation):
    //   addr=0x19, CTRL1 reg=0x20 data=0x57, RANGE reg=0x23 data=0x00
    //   poll: reg=0x28, 6 bytes
    localparam [6:0] ACCEL_ADDR  = 7'h19;
    localparam [7:0] REG_CTRL1   = 8'h20;
    localparam [7:0] REG_RANGE   = 8'h23;
    localparam [7:0] REG_OUT_X_L = 8'h28;

    // ----------------------------------------------------------------
    // Clock / reset
    // ----------------------------------------------------------------
    logic clk   = 1'b0;
    logic rst_n = 1'b0;
    always #1 clk = ~clk;

    // ----------------------------------------------------------------
    // DUT wires
    // ----------------------------------------------------------------
    wire [39:0] bidir_out;
    wire [39:0] bidir_oe;
    wire [39:0] bidir_cs;
    wire [39:0] bidir_sl;
    wire [39:0] bidir_ie;
    wire [39:0] bidir_pu;
    wire [39:0] bidir_pd;
    wire [11:0] input_pu;
    wire [11:0] input_pd;
    wire [1:0]  analog;

    // input_in[4:0] = 5'b0_0001:
    //   [4]=0 → core_clk = clk (not bidir[39])
    //   [3:0]=4'b0001 → test_mode_i → top_fsm FEAT_ONLY → feat_en=1
    logic [11:0] input_in = 12'b0000_0000_0001;

    // ----------------------------------------------------------------
    // I2C physical bus model
    // ----------------------------------------------------------------

    // SCL is a push-pull output from the chip.
    wire scl = bidir_out[SENSOR_SCL_PAD];

    // SDA is open-drain. Chip drives low via bidir_oe[SENSOR_SDA_PAD].
    // Slave BFM drives low via slave_sda_lo.
    // Physical SDA = 0 when either side drives low, else pulled high.
    logic slave_sda_lo = 1'b0;
    wire  sda = (bidir_oe[SENSOR_SDA_PAD] | slave_sda_lo) ? 1'b0 : 1'b1;

    // Feed physical SDA back into chip bidir_in[SENSOR_SDA_PAD].
    // All other pads: pulled high except IRQ/wake force pads (held 0).
    logic [39:0] bidir_in;
    always_comb begin
        bidir_in        = {40{1'b1}};     // default: all pulled high
        bidir_in[SENSOR_SDA_PAD] = sda;  // open-drain SDA feedback
        bidir_in[37]    = 1'b0;           // TEST_FORCE_IRQ_PAD: inactive
        bidir_in[38]    = 1'b0;           // TEST_FORCE_WAKE_PAD: inactive
    end

    // ----------------------------------------------------------------
    // DUT instantiation
    // ----------------------------------------------------------------
    chip_core #(
        .CLK_HZ               (TB_CLK_HZ),
        .ACC_POLL_PERIOD_TICKS (TB_POLL_TICKS),
        .PPG_POLL_PERIOD_TICKS (TB_PPG_POLL_TICKS)
    ) u_dut (
        .clk      (clk),
        .rst_n    (rst_n),
        .input_in (input_in),
        .input_pu (input_pu),
        .input_pd (input_pd),
        .bidir_in (bidir_in),
        .bidir_out(bidir_out),
        .bidir_oe (bidir_oe),
        .bidir_cs (bidir_cs),
        .bidir_sl (bidir_sl),
        .bidir_ie (bidir_ie),
        .bidir_pu (bidir_pu),
        .bidir_pd (bidir_pd),
        .debug_stim_override_en_i(1'b0),
        .debug_stim_mssd_i       (16'h0),
        .debug_stim_delta_hr_i   (16'h0),
        .debug_stim_time_i       (16'h0),
        .debug_stim_motion_i     (16'h0),
        .analog   (analog)
    );

    // ----------------------------------------------------------------
    // I2C slave BFM tasks
    // ----------------------------------------------------------------

    // Sample 8 bits MSB-first on each SCL rising edge.
    task automatic recv_byte(output logic [7:0] b);
        integer i;
        b = 8'h00;
        for (i = 7; i >= 0; i = i - 1) begin
            @(posedge scl);
            b[i] = sda;
        end
    endtask

    // Drive ACK: pull SDA low for one SCL high period after the 8th bit.
    task automatic send_ack;
        @(negedge scl);
        slave_sda_lo = 1'b1;
        @(posedge scl);
        @(negedge scl);
        slave_sda_lo = 1'b0;
    endtask

    // Drive one data byte MSB-first. Called while SCL is low.
    task automatic send_byte(input [7:0] b);
        integer i;
        for (i = 7; i >= 0; i = i - 1) begin
            slave_sda_lo = ~b[i];  // low=0, released=1 (open-drain)
            @(posedge scl);
            @(negedge scl);
        end
        slave_sda_lo = 1'b0;  // release SDA for master NACK
    endtask

    // Detect START or repeated START: SDA falls while SCL=1.
    task automatic wait_start;
        logic found;
        found = 1'b0;
        while (!found) begin
            @(negedge sda);
            if (scl == 1'b1) found = 1'b1;
        end
    endtask

    // ----------------------------------------------------------------
    // Slave BFM process
    //   Handles: init write 1 (CTRL1), init write 2 (RANGE),
    //            first poll read (6 bytes).
    // ----------------------------------------------------------------
    logic [7:0] rx;
    integer     bfm_errors = 0;
    logic       bfm_done   = 1'b0;

    task automatic check_rx(input [7:0] got, input [7:0] exp, input string tag);
        if (got !== exp) begin
            $display("[SLAVE] WARN %0s: got 0x%02h, expected 0x%02h", tag, got, exp);
            bfm_errors = bfm_errors + 1;
        end else begin
            $display("[SLAVE] %0s 0x%02h OK", tag, got);
        end
    endtask

    initial begin
        // ---------- Init Write 1: CTRL1 ----------
        wait_start();
        $display("[SLAVE] START (init write 1)");
        recv_byte(rx); check_rx(rx, {ACCEL_ADDR, 1'b0}, "addr+W");
        send_ack();
        recv_byte(rx); check_rx(rx, REG_CTRL1, "reg CTRL1");
        send_ack();
        recv_byte(rx); $display("[SLAVE] CTRL1 data=0x%02h", rx);
        send_ack();
        // Master sends STOP; next wait_start waits for the following transaction.

        // ---------- Init Write 2: RANGE ----------
        wait_start();
        $display("[SLAVE] START (init write 2)");
        recv_byte(rx); check_rx(rx, {ACCEL_ADDR, 1'b0}, "addr+W");
        send_ack();
        recv_byte(rx); check_rx(rx, REG_RANGE, "reg RANGE");
        send_ack();
        recv_byte(rx); $display("[SLAVE] RANGE data=0x%02h", rx);
        send_ack();

        // ---------- Poll Read: 6 XYZ bytes ----------
        wait_start();
        $display("[SLAVE] START (poll read)");
        recv_byte(rx); check_rx(rx, {ACCEL_ADDR, 1'b0}, "addr+W");
        send_ack();
        recv_byte(rx); check_rx(rx, REG_OUT_X_L, "reg OUT_X_L");
        send_ack();

        wait_start();
        $display("[SLAVE] rSTART");
        recv_byte(rx); check_rx(rx, {ACCEL_ADDR, 1'b1}, "addr+R");
        send_ack();

        // Drive 6 bytes (X_L, X_H, Y_L, Y_H, Z_L, Z_H).
        // Master ACKs first 5, NACKs 6th — slave ignores the NACK.
        send_byte(8'hA1);
        send_byte(8'hA2);
        send_byte(8'hA3);
        send_byte(8'hA4);
        send_byte(8'hA5);
        send_byte(8'hA6);
        $display("[SLAVE] 6 data bytes sent");

        bfm_done = 1'b1;
    end

    // ----------------------------------------------------------------
    // Main stimulus and verdict
    // ----------------------------------------------------------------
    integer timeout;
    logic   scl_last;
    integer scl_toggles;

    initial begin
        $dumpfile("tb_chip_core_i2c_rtl.vcd");
        $dumpvars(0, tb_chip_core_i2c_rtl);

        rst_n = 1'b0;
        repeat(8) @(posedge clk);
        rst_n = 1'b1;
        $display("[TB] Reset released — test_mode=0x01 → feat_en=1");

        // ---- Check 1: SCL appears on bidir_out[SENSOR_SCL_PAD] ----
        scl_last    = bidir_out[SENSOR_SCL_PAD];
        scl_toggles = 0;
        timeout = 0;
        while (scl_toggles < 4) begin
            @(posedge clk);
            if (bidir_oe[SENSOR_SCL_PAD] && bidir_out[SENSOR_SCL_PAD] !== scl_last) begin
                scl_last = bidir_out[SENSOR_SCL_PAD];
                scl_toggles = scl_toggles + 1;
            end
            if (++timeout > 100_000) begin
                $display("FAIL: timeout waiting for SCL on bidir_out[%0d]", SENSOR_SCL_PAD);
                $finish;
            end
        end
        if (!bidir_oe[SENSOR_SCL_PAD]) begin
            $display("FAIL: bidir_oe[%0d] not asserted — SCL OE routing broken", SENSOR_SCL_PAD);
            $finish;
        end
        $display("[TB] SCL toggling on bidir_out[%0d], bidir_oe[%0d]=1 — SCL pad routing OK",
                 SENSOR_SCL_PAD, SENSOR_SCL_PAD);

        // ---- Wait for slave BFM to complete all 3 transactions ----
        timeout = 0;
        while (!bfm_done) begin
            @(posedge clk);
            if (++timeout > 500_000) begin
                $display("FAIL: timeout waiting for slave BFM to complete");
                $finish;
            end
        end

        // ---- Verdict ----
        if (bfm_errors > 0) begin
            $display("FAIL: %0d I2C address/register mismatch(es) in slave BFM", bfm_errors);
            $finish;
        end
        $display("PASS: bidir[%0d] SCL routing OK, bidir[%0d] SDA open-drain OK, all I2C transactions ACK'd",
                 SENSOR_SCL_PAD, SENSOR_SDA_PAD);
        $finish;
    end

    // Hard safety timeout
    initial begin
        #20_000_000;
        $display("FATAL: global simulation timeout");
        $finish;
    end

endmodule
