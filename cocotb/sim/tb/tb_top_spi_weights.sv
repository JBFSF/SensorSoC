`timescale 1ns/1ps
//
// tb_top_spi_weights.sv
//
// Legacy CPU-driven SPI weight-loading smoke test.
//
// The new architecture's primary weight-load proof is:
//   make sim-weight-boot
//
// That path verifies hardware weight boot completion directly. This older
// bench is kept as a firmware-side SPI smoke test only. It should not assume
// a large, directly visible WRAM parameter image anymore.
//
// Verifies:
//   - Weight SPI CS was asserted
//   - Enough SPI bits were clocked for 208 weight words
//   - Firmware reports PASS
//   - TEST_CODE mirrors the first staged parameter word
//
// No sensor pipeline, no ML inference.
//
// Run via: make sim-top-spi-weights
//

module tb_top_spi_weights;

localparam int unsigned WEIGHT_WORDS   = 208;
localparam int unsigned TB_TIMEOUT     = 5_000_000;
localparam int unsigned TB_PROGRESS    = 1_000_000;
localparam int unsigned MIN_SPI_BITS   = 8 * (4 + WEIGHT_WORDS * 4);

// ----------------------------------------------------------------
// Clock and reset
// ----------------------------------------------------------------
reg clk   = 1'b0;
reg reset = 1'b1;

always #10 clk = ~clk;  // 50 MHz

// ----------------------------------------------------------------
// Weight SPI wires (spi_master_mmio <-> weight flash model)
// ----------------------------------------------------------------
wire spi_clk;
wire spi_mosi;
wire spi_miso;
wire spi_cs_n;

// ----------------------------------------------------------------
// Boot SPI wires — not used, tie MISO high
// ----------------------------------------------------------------
wire boot_spi_clk;
wire boot_spi_mosi;
wire boot_spi_cs_n;

// ----------------------------------------------------------------
// DUT — top.sv
// ----------------------------------------------------------------
top #(
    .MEM_WORDS              (8192),
    .BOOT_WORDS             (1),           // fires immediately, CPU starts from FIRMWARE_HEX
    .FIRMWARE_HEX           ("firmware/build/test_top_spi_boot_weights/firmware.hex"),
    .WEIGHT_INIT_HEX        (""),          // weights come from SPI flash, not preloaded
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
    // Sensor sim bus — not used
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
    // Weight SPI — connected to weight flash model
    .spi_clk_o          (spi_clk),
    .spi_mosi_o         (spi_mosi),
    .spi_miso_i         (spi_miso),
    .spi_cs_n_o         (spi_cs_n),
    // Boot SPI — not used, tie MISO high
    .boot_spi_clk_o     (boot_spi_clk),
    .boot_spi_mosi_o    (boot_spi_mosi),
    .boot_spi_miso_i    (1'b1),
    .boot_spi_cs_n_o    (boot_spi_cs_n),
    .epoch_end_o        (),
    .alarm_o            (),
    .boot_done_o        (),
    .weight_boot_done_o (),
    .test_force_irq_i   (1'b0),
    .test_force_wake_i  (1'b0),
    .test_irq_src_i     (3'b000),
    .irq_eoi_o          (),
    .pico_trap_o        (trap),
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

wire trap;

// ----------------------------------------------------------------
// Weight flash model — loaded with ML weight hex
// ----------------------------------------------------------------
spi_flash_model #(
    .FLASH_WORDS    (WEIGHT_WORDS),
    .FLASH_INIT_HEX ("firmware/build/generated/taketwo_params.hex")
) u_weight_flash (
    .spi_clk  (spi_clk),
    .spi_cs_n (spi_cs_n),
    .spi_mosi (spi_mosi),
    .spi_miso (spi_miso)
);

// ----------------------------------------------------------------
// SPI activity monitors
// ----------------------------------------------------------------
integer spi_cs_asserts;
integer spi_bit_count;
reg     prev_spi_cs_n;
reg     prev_spi_clk;

always @(posedge clk) begin
    if (reset) begin
        spi_cs_asserts <= 0;
        spi_bit_count  <= 0;
        prev_spi_cs_n  <= 1'b1;
        prev_spi_clk   <= 1'b0;
    end else begin
        if (prev_spi_cs_n && !spi_cs_n)
            spi_cs_asserts <= spi_cs_asserts + 1;
        prev_spi_cs_n <= spi_cs_n;

        if (!prev_spi_clk && spi_clk && !spi_cs_n)
            spi_bit_count <= spi_bit_count + 1;
        prev_spi_clk <= spi_clk;
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

    $display("[TB] tb_top_spi_weights start");
    $display("     FW=firmware/build/test_top_spi_boot_weights/firmware.hex");
    $display("     WEIGHT_FLASH=firmware/build/generated/taketwo_params.hex");

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    while (cycles < TB_TIMEOUT) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS) == 0)
            $display("[cyc %0d] status=0x%08x code=0x%08x spi_cs=%0d spi_bits=%0d",
                     cycles, dut.test_status, dut.test_code,
                     spi_cs_asserts, spi_bit_count);

        if (trap) begin
            $display("FAIL: CPU trap");
            $fatal(1);
        end

        if (dut.test_status == 32'hDEAD_BEEF) begin
            $display("FAIL: firmware FAIL code=0x%08x", dut.test_code);
            $display("  spi_cs=%0d spi_bits=%0d", spi_cs_asserts, spi_bit_count);
            $fatal(1);
        end

        if (dut.test_status == 32'hCAFE_BABE) begin

            // --- Check 1: Weight SPI CS was asserted ---
            if (spi_cs_asserts == 0) begin
                $display("FAIL: weight SPI CS never asserted");
                failures = failures + 1;
            end

            // --- Check 2: Enough SPI bits clocked ---
            if (spi_bit_count < MIN_SPI_BITS) begin
                $display("FAIL: too few SPI bits: %0d (expected >= %0d)",
                         spi_bit_count, MIN_SPI_BITS);
                failures = failures + 1;
            end

            // --- Check 3: TEST_CODE == first flashed weight word ---
            if (dut.test_code !== u_weight_flash.mem[0]) begin
                $display("FAIL: TEST_CODE=0x%08x != flash[0]=0x%08x",
                         dut.test_code, u_weight_flash.mem[0]);
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_top_spi_weights");
                $display("  spi_cs=%0d spi_bits=%0d",
                         spi_cs_asserts, spi_bit_count);
                $display("  test_code(first weight)=0x%08x flash[0]=0x%08x",
                         dut.test_code, u_weight_flash.mem[0]);
                $finish;
            end else begin
                $display("FAIL: tb_top_spi_weights failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT);
    $display("  status=0x%08x spi_cs=%0d spi_bits=%0d",
             dut.test_status, spi_cs_asserts, spi_bit_count);
    $fatal(1);
end

// ----------------------------------------------------------------
// VCD dump
// ----------------------------------------------------------------
initial begin
    $dumpfile("sim/build/top_spi_weights.vcd");
    $dumpvars(0, tb_top_spi_weights);
end

endmodule
