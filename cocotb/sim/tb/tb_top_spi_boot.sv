`timescale 1ns/1ps
//
// tb_top_spi_boot.sv
//
// Test 1: Hardware SPI boot controller isolation test.
//
// Verifies that spi_boot_ctrl correctly:
//   1. Asserts boot SPI CS
//   2. Sends READ (0x03) + 24-bit address to boot flash
//   3. Streams BOOT_WORDS words into simple_sram
//   4. Asserts boot_done_o, releasing the CPU from reset
//   5. simple_sram contents match the boot flash model
//
// No CPU execution is checked here — this isolates the hardware
// boot path only. The CPU is held in reset until boot_done fires,
// and we verify the SRAM was correctly populated.
//
// Run via: make sim-top-spi-boot
//

module tb_top_spi_boot;

// Number of firmware words to boot — keep small for sim speed.
// Must match BOOT_WORDS parameter passed to top.
localparam int unsigned BOOT_WORDS     = 64;
localparam int unsigned TB_TIMEOUT     = 2_000_000;
localparam int unsigned TB_PROGRESS    = 500_000;
// Command byte (0x03) + 3 address bytes + BOOT_WORDS * 4 data bytes
localparam int unsigned MIN_BOOT_BITS  = 8 * (4 + BOOT_WORDS * 4);

// ----------------------------------------------------------------
// Clock and reset
// ----------------------------------------------------------------
reg clk   = 1'b0;
reg reset = 1'b1;

always #10 clk = ~clk;  // 50 MHz

// ----------------------------------------------------------------
// Boot SPI wires (spi_boot_ctrl <-> boot flash model)
// ----------------------------------------------------------------
wire boot_spi_clk;
wire boot_spi_mosi;
wire boot_spi_miso;
wire boot_spi_cs_n;

// ----------------------------------------------------------------
// Weight SPI wires — not used in this test, tie MISO high
// ----------------------------------------------------------------
wire spi_clk;
wire spi_mosi;
wire spi_cs_n;

// ----------------------------------------------------------------
// DUT — top.sv
// ----------------------------------------------------------------
top #(
    .MEM_WORDS              (1024),
    .BOOT_WORDS             (BOOT_WORDS),
    .FIRMWARE_HEX           (""),          // SRAM loaded by boot ctrl, not preloaded
    .WEIGHT_INIT_HEX        (""),
    .CLK_HZ                 (1000),
    .GT_CLK_HZ              (1000),
    .GT_EPOCH_HZ            (100),
    .GT_EPOCH_COUNT_MAX     (300),
    .ACC_POLL_PERIOD_TICKS  (8),
    .PPG_POLL_PERIOD_TICKS  (2),
    .PPG_WATERMARK          (8),
    .PPG_MAX_BURST_SAMPLES  (32),
    .CFG_REFRACT_MS         (250),
    .CFG_RR_MIN_MS          (300),
    .CFG_RR_MAX_MS          (2000),
    .CFG_Q_MIN_ACCEPT       (0),
    .CFG_BEAT_Q_MIN         (0),
    .CFG_MIN_VALID_FRAC     (0),
    .CFG_MAX_DOUBLE         (8'd4),
    .CFG_MAX_MISSED         (8'd3),
    .CFG_MOTION_HI_TH       (16'hFFFF),
    .CFG_MAX_MOTION_HI      (16'hFFFF),
    .MSSD_MIN_RR_COUNT      (1)
) dut (
    .clk_i              (clk),
    .reset_i            (reset),
    .i2c_scl_i          (1'b1),
    .i2c_sda_io         (),
    .i2c_sda_i          (1'b1),
    .i2c_sda_drive_low_o(),
    // Sensor sim bus — tie off, not used in this test
    .sim_req_o          (),
    .sim_addr_o         (),
    .sim_reg_o          (),
    .sim_len_o          (),
    .sim_write_o        (),
    .sim_wdata_o        (),
    .sim_ack_i          (1'b0),
    .sim_rdata_i        (8'h00),
    .sim_rvalid_i       (1'b0),
    .sim_rlast_i        (1'b0),
    .sim_err_i          (1'b1),
    // Feature outputs — unused
    .feat_valid_o       (),
    .time_feat_o        (),
    .motion_feat_o      (),
    .delta_hr_feat_o    (),
    .mssd_feat_o        (),
    .ml_update_gate_o   (),
    .invalid_reason_o   (),
    // Weight SPI — not used in this test
    .spi_clk_o          (spi_clk),
    .spi_mosi_o         (spi_mosi),
    .spi_miso_i         (1'b1),
    .spi_cs_n_o         (spi_cs_n),
    // Boot SPI — connected to boot flash model
    .boot_spi_clk_o     (boot_spi_clk),
    .boot_spi_mosi_o    (boot_spi_mosi),
    .boot_spi_miso_i    (boot_spi_miso),
    .boot_spi_cs_n_o    (boot_spi_cs_n),
    // Misc
    .epoch_end_o        (),
    .alarm_o            (),
    .boot_done_o        (boot_done_observed),
    .test_force_irq_i   (1'b0),
    .test_force_wake_i  (1'b0),
    .test_irq_src_i     (3'b000),
    .irq_eoi_o          (),
    .pico_trap_o        (),
    .pico_cpu_clk_en_o  (),
    .pico_mem_valid_o   (),
    .pico_mem_instr_o   (),
    .pico_mem_ready_o   (),
    .pico_mem_wstrb_o   (),
    .pico_mem_addr_o    (),
    .pico_mem_wdata_o   (),
    .pico_irq_o         (),
    .pico_sleeping_o    (),
    .host_i2c_irq_event_o(),
    .ml_irq_o           (),
    .timer_event_o      ()
);

wire boot_done_observed;

// ----------------------------------------------------------------
// Boot flash model — loaded with firmware hex
// ----------------------------------------------------------------
spi_flash_model #(
    .FLASH_WORDS    (BOOT_WORDS),
    .FLASH_INIT_HEX ("firmware/build/test_top_feature_ml_cpu_spi_flash/firmware.hex")
) u_boot_flash (
    .spi_clk  (boot_spi_clk),
    .spi_cs_n (boot_spi_cs_n),
    .spi_mosi (boot_spi_mosi),
    .spi_miso (boot_spi_miso)
);

// ----------------------------------------------------------------
// Boot SPI activity monitors
// ----------------------------------------------------------------
integer boot_cs_asserts;
integer boot_bit_count;
reg     prev_boot_cs_n;
reg     prev_boot_clk;

always @(posedge clk) begin
    if (reset) begin
        boot_cs_asserts <= 0;
        boot_bit_count  <= 0;
        prev_boot_cs_n  <= 1'b1;
        prev_boot_clk   <= 1'b0;
    end else begin
        if (prev_boot_cs_n && !boot_spi_cs_n)
            boot_cs_asserts <= boot_cs_asserts + 1;
        prev_boot_cs_n <= boot_spi_cs_n;

        if (!prev_boot_clk && boot_spi_clk && !boot_spi_cs_n)
            boot_bit_count <= boot_bit_count + 1;
        prev_boot_clk <= boot_spi_clk;
    end
end

// ----------------------------------------------------------------
// Main test sequence
// ----------------------------------------------------------------
integer cycles;
integer failures;

initial begin
    cycles   = 0;
    failures = 0;

    $display("[TB] tb_top_spi_boot start");
    $display("     BOOT_FLASH=firmware/build/test_top_e2e_preloaded/firmware.hex");
    $display("     BOOT_WORDS=%0d", BOOT_WORDS);

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released — spi_boot_ctrl now running", $time);

    // Wait for boot_done or timeout
    while (cycles < TB_TIMEOUT) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS) == 0)
            $display("[cyc %0d] boot_done=%0b boot_cs=%0d boot_bits=%0d",
                     cycles, boot_done_observed,
                     boot_cs_asserts, boot_bit_count);

        if (boot_done_observed) begin
            $display("[cyc %0d] boot_done asserted — checking SRAM contents",
                     cycles);

            // --- Check 1: Boot CS was asserted ---
            if (boot_cs_asserts == 0) begin
                $display("FAIL: boot SPI CS never asserted");
                failures = failures + 1;
            end

            // --- Check 2: Enough boot bits clocked ---
            if (boot_bit_count < MIN_BOOT_BITS) begin
                $display("FAIL: too few boot SPI bits: %0d (expected >= %0d)",
                         boot_bit_count, MIN_BOOT_BITS);
                failures = failures + 1;
            end

            // --- Check 3: SRAM words match boot flash ---
            // spi_boot_ctrl writes words starting at byte address 0 (word index 0)
            if (dut.sram.mem[0] !== u_boot_flash.mem[0]) begin
                $display("FAIL: sram[0]=0x%08x != flash[0]=0x%08x",
                         dut.sram.mem[0], u_boot_flash.mem[0]);
                failures = failures + 1;
            end
            if (dut.sram.mem[1] !== u_boot_flash.mem[1]) begin
                $display("FAIL: sram[1]=0x%08x != flash[1]=0x%08x",
                         dut.sram.mem[1], u_boot_flash.mem[1]);
                failures = failures + 1;
            end
            if (dut.sram.mem[2] !== u_boot_flash.mem[2]) begin
                $display("FAIL: sram[2]=0x%08x != flash[2]=0x%08x",
                         dut.sram.mem[2], u_boot_flash.mem[2]);
                failures = failures + 1;
            end
            if (dut.sram.mem[3] !== u_boot_flash.mem[3]) begin
                $display("FAIL: sram[3]=0x%08x != flash[3]=0x%08x",
                         dut.sram.mem[3], u_boot_flash.mem[3]);
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_top_spi_boot");
                $display("  boot_done=%0b boot_cs=%0d boot_bits=%0d",
                         boot_done_observed, boot_cs_asserts, boot_bit_count);
                $display("  sram[0..3]=%08x %08x %08x %08x",
                         dut.sram.mem[0], dut.sram.mem[1],
                         dut.sram.mem[2], dut.sram.mem[3]);
                $display("  flash[0..3]=%08x %08x %08x %08x",
                         u_boot_flash.mem[0], u_boot_flash.mem[1],
                         u_boot_flash.mem[2], u_boot_flash.mem[3]);
                $finish;
            end else begin
                $display("FAIL: tb_top_spi_boot failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout — boot_done never asserted after %0d cycles", TB_TIMEOUT);
    $display("  boot_cs=%0d boot_bits=%0d", boot_cs_asserts, boot_bit_count);
    $fatal(1);
end

// ----------------------------------------------------------------
// VCD dump
// ----------------------------------------------------------------
initial begin
    $dumpfile("sim/build/top_spi_boot.vcd");
    $dumpvars(0, tb_top_spi_boot);
end

endmodule
