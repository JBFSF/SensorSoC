`timescale 1ns/1ps
//
// tb_top_spi_weights.sv
//
// Dedicated weight-SPI inference smoke test.
//
// Firmware must not use spi_master_mmio for weights. It writes only the
// CPU-visible feature registers, starts taketwo, and reads back the captured
// logit register. The bench verifies that the dedicated weight_spi_* port was
// used for parameter fetches and that the CPU SPI bus stayed idle.
//
// Verifies:
//   - Weight SPI CS was asserted
//   - Enough SPI bits were clocked for the canonical NNGen parameter image
//   - Firmware reports PASS
//   - TEST_CODE/logit output match the canonical packed logits
//
// No sensor pipeline, no ML inference.
//
// Run via: make sim-top-spi-weights
//

module tb_top_spi_weights;

localparam int unsigned WEIGHT_WORDS   = 1296;
localparam int unsigned TB_TIMEOUT     = 5_000_000;
localparam int unsigned TB_PROGRESS    = 1_000_000;
localparam int unsigned MIN_AXI_BEATS  = 134;
localparam int unsigned MIN_SPI_BITS   = MIN_AXI_BEATS * 32;
localparam logic [31:0] EXPECTED_LOGIT_WORD = 32'h3585_F96A;

// ----------------------------------------------------------------
// Clock and reset
// ----------------------------------------------------------------
reg clk   = 1'b0;
reg reset = 1'b1;

always #30 clk = ~clk;  // 16.7 MHz, above gf180 SRAM timing minimum

// ----------------------------------------------------------------
// CPU SPI wires — monitored only; no flash model is connected here
// ----------------------------------------------------------------
wire cpu_spi_clk;
wire cpu_spi_mosi;
wire cpu_spi_cs_n;

// ----------------------------------------------------------------
// Shared flash SPI wires (spi_boot_ctrl at boot, weight_flash_axi after)
// ----------------------------------------------------------------
wire flash_spi_clk;
wire flash_spi_mosi;
wire flash_spi_miso;
wire flash_spi_cs_n;

wire signed [15:0] logit0;
wire signed [15:0] logit1;
wire boot_done;

// ----------------------------------------------------------------
// DUT — top.sv
// ----------------------------------------------------------------
top #(
    .MEM_WORDS              (1024),
    .FIRMWARE_HEX           (""),
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
    .i2c_scl_o          (),
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
    // CPU SPI — monitored only; firmware must leave it idle
    .spi_clk_o          (cpu_spi_clk),
    .spi_mosi_o         (cpu_spi_mosi),
    .spi_miso_i         (1'b1),
    .spi_cs_n_o         (cpu_spi_cs_n),
    // Shared flash SPI — connected to combined flash model
    .start_i            (1'b1),
    .test_mode_i        (4'b0101),
    .flash_spi_clk_o    (flash_spi_clk),
    .flash_spi_mosi_o   (flash_spi_mosi),
    .flash_spi_miso_i   (flash_spi_miso),
    .flash_spi_cs_n_o   (flash_spi_cs_n),
    .epoch_end_o        (),
    .alarm_o            (),
    .logit0             (logit0),
    .logit1             (logit1),
    .boot_done_o        (boot_done),
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
    .ml_irq_o           (),
    .timer_event_o      ()
);

wire trap;

// ----------------------------------------------------------------
// Combined flash model — firmware at offset 0, weights at offset 0x001000
// ----------------------------------------------------------------
spi_flash_model #(
    .FLASH_WORDS    (2368),
    .FLASH_INIT_HEX ("firmware/build/generated/combined_flash_test_top_spi_boot_weights.hex")
) u_combined_flash (
    .spi_clk  (flash_spi_clk),
    .spi_cs_n (flash_spi_cs_n),
    .spi_mosi (flash_spi_mosi),
    .spi_miso (flash_spi_miso)
);

// ----------------------------------------------------------------
// SPI activity monitors
// ----------------------------------------------------------------
integer spi_cs_asserts;
integer spi_bit_count;
integer cpu_spi_cs_asserts;
integer cpu_spi_bit_count;
integer axi_ar_hs;
integer axi_r_hs;
integer axi_aw_hs;
integer axi_w_hs;
integer axi_b_hs;
reg     prev_spi_cs_n;
reg     prev_spi_clk;
reg     prev_cpu_spi_cs_n;
reg     prev_cpu_spi_clk;
reg [31:0] sampled_logit_word;

always @(posedge clk) begin
    if (reset) begin
        spi_cs_asserts <= 0;
        spi_bit_count  <= 0;
        cpu_spi_cs_asserts <= 0;
        cpu_spi_bit_count  <= 0;
        axi_ar_hs <= 0;
        axi_r_hs  <= 0;
        axi_aw_hs <= 0;
        axi_w_hs  <= 0;
        axi_b_hs  <= 0;
        prev_spi_cs_n  <= 1'b1;
        prev_spi_clk   <= 1'b0;
        prev_cpu_spi_cs_n <= 1'b1;
        prev_cpu_spi_clk  <= 1'b0;
    end else begin
        if (boot_done && prev_spi_cs_n && !flash_spi_cs_n)
            spi_cs_asserts <= spi_cs_asserts + 1;
        prev_spi_cs_n <= flash_spi_cs_n;

        if (boot_done && !prev_spi_clk && flash_spi_clk && !flash_spi_cs_n)
            spi_bit_count <= spi_bit_count + 1;
        prev_spi_clk <= flash_spi_clk;

        if (prev_cpu_spi_cs_n && !cpu_spi_cs_n)
            cpu_spi_cs_asserts <= cpu_spi_cs_asserts + 1;
        prev_cpu_spi_cs_n <= cpu_spi_cs_n;

        if (!prev_cpu_spi_clk && cpu_spi_clk && !cpu_spi_cs_n)
            cpu_spi_bit_count <= cpu_spi_bit_count + 1;
        prev_cpu_spi_clk <= cpu_spi_clk;

        if (dut.wram_arvalid && dut.wram_arready) axi_ar_hs <= axi_ar_hs + 1;
        if (dut.wram_rvalid  && dut.wram_rready)  axi_r_hs  <= axi_r_hs + 1;
        if (dut.wram_awvalid && dut.wram_awready) axi_aw_hs <= axi_aw_hs + 1;
        if (dut.wram_wvalid  && dut.wram_wready) begin
            axi_w_hs <= axi_w_hs + 1;
            $display("[%0t] AXI W awaddr=0x%08x wdata=0x%08x wlast=%0b",
                     $time, dut.wram_awaddr, dut.wram_wdata, dut.wram_wlast);
        end
        if (dut.wram_bvalid  && dut.wram_bready)  axi_b_hs  <= axi_b_hs + 1;
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
            $display("[cyc %0d] status=0x%08x code=0x%08x weight_spi_cs=%0d spi_bits=%0d cpu_spi_cs=%0d cpu_spi_bits=%0d axi=%0d/%0d/%0d/%0d/%0d",
                     cycles, dut.test_status, dut.test_code,
                     spi_cs_asserts, spi_bit_count,
                     cpu_spi_cs_asserts, cpu_spi_bit_count,
                     axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);

        if (trap) begin
            $display("FAIL: CPU trap");
            $fatal(1);
        end

        if (dut.test_status == 32'hDEAD_BEEF) begin
            $display("FAIL: firmware FAIL code=0x%08x", dut.test_code);
            $display("  weight_spi_cs=%0d weight_spi_bits=%0d cpu_spi_cs=%0d cpu_spi_bits=%0d axi=%0d/%0d/%0d/%0d/%0d logit_word=0x%08x",
                     spi_cs_asserts, spi_bit_count,
                     cpu_spi_cs_asserts, cpu_spi_bit_count,
                     axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs,
                     {logit1[15:0], logit0[15:0]});
            $fatal(1);
        end

        if (dut.test_status == 32'hCAFE_BABE) begin
            sampled_logit_word = {logit1[15:0], logit0[15:0]};

            if (spi_cs_asserts == 0) begin
                $display("FAIL: weight SPI CS never asserted");
                failures = failures + 1;
            end

            if (spi_bit_count < MIN_SPI_BITS) begin
                $display("FAIL: too few weight SPI bits: %0d (expected >= %0d)",
                         spi_bit_count, MIN_SPI_BITS);
                failures = failures + 1;
            end

            if (cpu_spi_cs_asserts != 0 || cpu_spi_bit_count != 0) begin
                $display("FAIL: CPU SPI bus was used cs=%0d bits=%0d",
                         cpu_spi_cs_asserts, cpu_spi_bit_count);
                failures = failures + 1;
            end

            if (axi_ar_hs == 0 || axi_r_hs < MIN_AXI_BEATS) begin
                $display("FAIL: too little AXI read activity ar=%0d r=%0d expected_r>=%0d",
                         axi_ar_hs, axi_r_hs, MIN_AXI_BEATS);
                failures = failures + 1;
            end

            if ((axi_aw_hs == 0) && (axi_w_hs == 0) && (axi_b_hs == 0)) begin
                $display("FAIL: no AXI write/logit activity from taketwo");
                failures = failures + 1;
            end

            if (dut.test_code !== EXPECTED_LOGIT_WORD) begin
                $display("FAIL: TEST_CODE=0x%08x expected logit word=0x%08x",
                         dut.test_code, EXPECTED_LOGIT_WORD);
                failures = failures + 1;
            end

            if (sampled_logit_word !== EXPECTED_LOGIT_WORD) begin
                $display("FAIL: visible logits=0x%08x expected=0x%08x",
                         sampled_logit_word, EXPECTED_LOGIT_WORD);
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_top_spi_weights");
                $display("  weight_spi_cs=%0d weight_spi_bits=%0d axi=%0d/%0d/%0d/%0d/%0d",
                         spi_cs_asserts, spi_bit_count,
                         axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
                $display("  logit_word=0x%08x", sampled_logit_word);
                $finish;
            end else begin
                $display("FAIL: tb_top_spi_weights failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT);
    $display("  status=0x%08x weight_spi_cs=%0d weight_spi_bits=%0d cpu_spi_cs=%0d cpu_spi_bits=%0d axi=%0d/%0d/%0d/%0d/%0d",
             dut.test_status, spi_cs_asserts, spi_bit_count,
             cpu_spi_cs_asserts, cpu_spi_bit_count,
             axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
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
