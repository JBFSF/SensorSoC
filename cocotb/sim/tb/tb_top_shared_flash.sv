`timescale 1ns/1ps
//
// tb_top_shared_flash.sv
//
// Focused proof that a single SPI flash chip can serve both the firmware boot
// controller and the ML weight reader on the same physical bus.
//
// Flash layout (combined_flash_test_top_spi_boot_weights.hex):
//   Words   0 – 1023  (byte 0x000000 – 0x000FFF) : firmware
//   Words 1024 – 2319 (byte 0x001000 – 0x002400) : ML weights
//
// The bench monitors the single flash_spi_* bus in two temporal phases,
// gated by boot_done, and validates:
//   Phase 1 (boot_done == 0):  spi_boot_ctrl drives; CS asserted, bits clocked.
//   Phase 2 (boot_done == 1):  weight_flash_axi drives; CS asserted during inference.
//   Always:                    CPU spi_master_mmio never asserts CS.
//   End state:                 firmware PASS + logit == golden + SRAM[0] == flash[0].
//
// Run via: make sim-top-shared-flash
//

module tb_top_shared_flash;

localparam int unsigned FLASH_WORDS         = 2368;
localparam int unsigned TB_TIMEOUT          = 5_000_000;
localparam int unsigned TB_PROGRESS         = 1_000_000;
localparam int unsigned MIN_BOOT_SPI_BITS   = 32;
localparam int unsigned MIN_AXI_BEATS       = 134;
localparam int unsigned MIN_WEIGHT_SPI_BITS = MIN_AXI_BEATS * 32;
localparam logic [31:0] EXPECTED_LOGIT_WORD = 32'h3585_F96A;
localparam logic [31:0] TEST_PASS           = 32'hCAFE_BABE;
localparam logic [31:0] TEST_FAIL           = 32'hDEAD_BEEF;

// ----------------------------------------------------------------
// Clock and reset
// ----------------------------------------------------------------
reg clk   = 1'b0;
reg reset = 1'b1;
always #30 clk = ~clk;

// ----------------------------------------------------------------
// DUT wires
// ----------------------------------------------------------------
wire        flash_spi_clk;
wire        flash_spi_mosi;
wire        flash_spi_miso;
wire        flash_spi_cs_n;

wire        cpu_spi_clk;
wire        cpu_spi_mosi;
wire        cpu_spi_cs_n;

wire        boot_done;
wire        trap;
wire signed [15:0] logit0;
wire signed [15:0] logit1;

// ----------------------------------------------------------------
// DUT — top.sv with shared flash
// ----------------------------------------------------------------
top #(
    .MEM_WORDS              (1024),
    .FIRMWARE_HEX           (""),
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
    .i2c_scl_o          (),
    .i2c_sda_io         (),
    .i2c_sda_i          (1'b1),
    .i2c_sda_drive_low_o(),
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
    .feat_valid_o       (),
    .time_feat_o        (),
    .motion_feat_o      (),
    .delta_hr_feat_o    (),
    .mssd_feat_o        (),
    .ml_update_gate_o   (),
    .invalid_reason_o   (),
    // CPU SPI — monitored; must stay idle
    .spi_clk_o          (cpu_spi_clk),
    .spi_mosi_o         (cpu_spi_mosi),
    .spi_miso_i         (1'b1),
    .spi_cs_n_o         (cpu_spi_cs_n),
    // Single shared flash bus
    .flash_spi_clk_o    (flash_spi_clk),
    .flash_spi_mosi_o   (flash_spi_mosi),
    .flash_spi_miso_i   (flash_spi_miso),
    .flash_spi_cs_n_o   (flash_spi_cs_n),
    .start_i            (1'b1),
    .test_mode_i        (4'b0101),
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

// ----------------------------------------------------------------
// Single combined flash model
// Firmware at words 0–1023, weights at words 1024–2319.
// ----------------------------------------------------------------
spi_flash_model #(
    .FLASH_WORDS    (FLASH_WORDS),
    .FLASH_INIT_HEX ("firmware/build/generated/combined_flash_test_top_spi_boot_weights.hex")
) u_combined_flash (
    .spi_clk (flash_spi_clk),
    .spi_cs_n(flash_spi_cs_n),
    .spi_mosi(flash_spi_mosi),
    .spi_miso(flash_spi_miso)
);

// ----------------------------------------------------------------
// SPI activity monitors — gated by boot_done to distinguish phases
// ----------------------------------------------------------------
integer boot_cs_asserts;
integer boot_spi_bits;
integer weight_cs_asserts;
integer weight_spi_bits;
integer cpu_cs_asserts;
integer cpu_spi_bits;
integer axi_ar_hs;
integer axi_r_hs;
integer axi_aw_hs;
integer axi_w_hs;
integer axi_b_hs;
reg prev_flash_cs_n;
reg prev_flash_clk;
reg prev_cpu_cs_n;
reg prev_cpu_clk;

always @(posedge clk) begin
    if (reset) begin
        boot_cs_asserts   <= 0;
        boot_spi_bits     <= 0;
        weight_cs_asserts <= 0;
        weight_spi_bits   <= 0;
        cpu_cs_asserts    <= 0;
        cpu_spi_bits      <= 0;
        axi_ar_hs         <= 0;
        axi_r_hs          <= 0;
        axi_aw_hs         <= 0;
        axi_w_hs          <= 0;
        axi_b_hs          <= 0;
        prev_flash_cs_n   <= 1'b1;
        prev_flash_clk    <= 1'b0;
        prev_cpu_cs_n     <= 1'b1;
        prev_cpu_clk      <= 1'b0;
    end else begin
        // Boot phase: spi_boot_ctrl (before boot_done)
        if (!boot_done) begin
            if (prev_flash_cs_n && !flash_spi_cs_n)
                boot_cs_asserts <= boot_cs_asserts + 1;
            if (!prev_flash_clk && flash_spi_clk && !flash_spi_cs_n)
                boot_spi_bits <= boot_spi_bits + 1;
        end
        // Weight phase: weight_flash_axi (after boot_done)
        if (boot_done) begin
            if (prev_flash_cs_n && !flash_spi_cs_n)
                weight_cs_asserts <= weight_cs_asserts + 1;
            if (!prev_flash_clk && flash_spi_clk && !flash_spi_cs_n)
                weight_spi_bits <= weight_spi_bits + 1;
        end
        prev_flash_cs_n <= flash_spi_cs_n;
        prev_flash_clk  <= flash_spi_clk;

        // CPU SPI — must stay idle throughout
        if (prev_cpu_cs_n && !cpu_spi_cs_n)
            cpu_cs_asserts <= cpu_cs_asserts + 1;
        if (!prev_cpu_clk && cpu_spi_clk && !cpu_spi_cs_n)
            cpu_spi_bits <= cpu_spi_bits + 1;
        prev_cpu_cs_n <= cpu_spi_cs_n;
        prev_cpu_clk  <= cpu_spi_clk;

        // AXI read/write handshake counts
        if (dut.wram_arvalid && dut.wram_arready) axi_ar_hs <= axi_ar_hs + 1;
        if (dut.wram_rvalid  && dut.wram_rready)  axi_r_hs  <= axi_r_hs  + 1;
        if (dut.wram_awvalid && dut.wram_awready) axi_aw_hs <= axi_aw_hs + 1;
        if (dut.wram_wvalid  && dut.wram_wready)  axi_w_hs  <= axi_w_hs  + 1;
        if (dut.wram_bvalid  && dut.wram_bready)  axi_b_hs  <= axi_b_hs  + 1;
    end
end

// ----------------------------------------------------------------
// Main test
// ----------------------------------------------------------------
integer cycles;
integer failures;
reg [31:0] sampled_logit_word;

initial begin
    cycles   = 0;
    failures = 0;

    $display("[TB] tb_top_shared_flash start");
    $display("     FLASH=firmware/build/generated/combined_flash_test_top_spi_boot_weights.hex");
    $display("     fw words 0-1023  (0x000000-0x000FFF)");
    $display("     wt words 1024-2319 (0x001000-0x0023FC)");

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    while (cycles < TB_TIMEOUT) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS) == 0)
            $display("[cyc %0d] boot_done=%0b status=0x%08x boot_cs=%0d boot_bits=%0d wt_cs=%0d wt_bits=%0d cpu_cs=%0d axi=%0d/%0d",
                     cycles, boot_done, dut.test_status,
                     boot_cs_asserts, boot_spi_bits,
                     weight_cs_asserts, weight_spi_bits,
                     cpu_cs_asserts, axi_ar_hs, axi_r_hs);

        if (trap) begin
            $display("FAIL: CPU trap");
            $fatal(1);
        end

        if (dut.test_status == TEST_FAIL) begin
            sampled_logit_word = {logit1[15:0], logit0[15:0]};
            $display("FAIL: firmware code=0x%08x visible_logits=0x%08x weight_logit_regs=0x%08x_0x%08x",
                     dut.test_code, sampled_logit_word,
                     dut.u_weight_ram.logit_reg_1, dut.u_weight_ram.logit_reg_0);
            $display("FAIL: firmware FAIL code=0x%08x", dut.test_code);
            $fatal(1);
        end

        if (dut.test_status == TEST_PASS) begin
            sampled_logit_word = {logit1[15:0], logit0[15:0]};

            // --- Boot phase checks ---
            if (boot_cs_asserts < 1) begin
                $display("FAIL: boot SPI CS never asserted");
                failures = failures + 1;
            end
            if (boot_spi_bits < MIN_BOOT_SPI_BITS) begin
                $display("FAIL: too few boot SPI bits: %0d (expected >= %0d)",
                         boot_spi_bits, MIN_BOOT_SPI_BITS);
                failures = failures + 1;
            end

            // --- Weight phase checks ---
            if (weight_cs_asserts < 1) begin
                $display("FAIL: weight SPI CS never asserted after boot_done");
                failures = failures + 1;
            end
            if (weight_spi_bits < MIN_WEIGHT_SPI_BITS) begin
                $display("FAIL: too few weight SPI bits: %0d (expected >= %0d)",
                         weight_spi_bits, MIN_WEIGHT_SPI_BITS);
                failures = failures + 1;
            end

            // --- CPU SPI must be idle ---
            if (cpu_cs_asserts != 0 || cpu_spi_bits != 0) begin
                $display("FAIL: CPU SPI bus was used cs=%0d bits=%0d",
                         cpu_cs_asserts, cpu_spi_bits);
                failures = failures + 1;
            end

            // --- AXI activity ---
            if (axi_ar_hs == 0 || axi_r_hs < MIN_AXI_BEATS) begin
                $display("FAIL: insufficient AXI read activity ar=%0d r=%0d (expected_r>=%0d)",
                         axi_ar_hs, axi_r_hs, MIN_AXI_BEATS);
                failures = failures + 1;
            end

            // --- Logit golden comparison ---
            if (dut.test_code !== EXPECTED_LOGIT_WORD) begin
                $display("FAIL: firmware TEST_CODE=0x%08x expected=0x%08x",
                         dut.test_code, EXPECTED_LOGIT_WORD);
                failures = failures + 1;
            end
            if (sampled_logit_word !== EXPECTED_LOGIT_WORD) begin
                $display("FAIL: visible logits=0x%08x expected=0x%08x",
                         sampled_logit_word, EXPECTED_LOGIT_WORD);
                failures = failures + 1;
            end

            // --- Ideal reference: flash model memory comparison ---
            if (dut.sram.mem[0] !== u_combined_flash.mem[0]) begin
                $display("FAIL: SRAM[0]=0x%08x != flash[0]=0x%08x (boot load mismatch)",
                         dut.sram.mem[0], u_combined_flash.mem[0]);
                failures = failures + 1;
            end
            if (u_combined_flash.mem[1024] === 32'h0) begin
                $display("FAIL: flash[1024] (first weight word) is zero — params missing?");
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_top_shared_flash");
                $display("  boot_cs=%0d boot_bits=%0d | weight_cs=%0d weight_bits=%0d | cpu_cs=%0d",
                         boot_cs_asserts, boot_spi_bits,
                         weight_cs_asserts, weight_spi_bits, cpu_cs_asserts);
                $display("  axi ar=%0d r=%0d aw=%0d w=%0d b=%0d",
                         axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
                $display("  logit_word=0x%08x (matches golden 0x%08x)",
                         sampled_logit_word, EXPECTED_LOGIT_WORD);
                $display("  flash[0]=0x%08x == SRAM[0]=0x%08x",
                         u_combined_flash.mem[0], dut.sram.mem[0]);
                $finish;
            end else begin
                $display("FAIL: tb_top_shared_flash failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT);
    $display("  boot_done=%0b status=0x%08x boot_cs=%0d boot_bits=%0d wt_cs=%0d wt_bits=%0d cpu_cs=%0d axi=%0d/%0d",
             boot_done, dut.test_status,
             boot_cs_asserts, boot_spi_bits,
             weight_cs_asserts, weight_spi_bits,
             cpu_cs_asserts, axi_ar_hs, axi_r_hs);
    $fatal(1);
end

initial begin
    $dumpfile("tb_top_shared_flash.vcd");
    $dumpvars(0, tb_top_shared_flash);
end

endmodule
