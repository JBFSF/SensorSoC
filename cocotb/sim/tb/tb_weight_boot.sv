`timescale 1ns/1ps
//
// tb_weight_boot.sv
//
// Verifies the weight_flash_axi path: taketwo reads ML weights directly
// from the dedicated SPI flash at inference time (no boot-time SRAM load).
//
// weight_boot_done_o is permanently 1'b1 — no boot stage needed.
//
// Checks:
//   1. taketwo issued at least one AXI read within the WEIGHT_BASE range.
//   2. taketwo issued >= MIN_AXI_BEATS AXI read beats (one full inference pass).
//   3. weight SPI CS was asserted (flash was accessed during inference).
//   4. >= MIN_SPI_BITS SPI clock edges seen (at least all weight data bits).
//
// Run via: make sim-weight-boot
//

module tb_weight_boot;

// Actual AXI read beats for one complete inference pass:
//   layer0: 32 filter + 8 bias + 1 scale + 2 input_act = 43
//   layer1: 64 filter + 4 bias + 1 scale + 8 input_act = 77
//   layer2:  8 filter + 1 bias + 1 scale + 4 input_act = 14  => total 134
localparam int unsigned MIN_AXI_BEATS = 134;
// Minimum SPI data bits = 134 words × 32 bits (command/addr overhead per burst on top)
localparam int unsigned MIN_SPI_BITS  = 134 * 32;
localparam int unsigned S2_TIMEOUT    = 200_000;
localparam int unsigned WEIGHT_WORDS  = 208;
// AXI base addresses (MUST match top.sv parameters)
localparam logic [31:0] WEIGHT_BASE = 32'h0300_6000;

// Clock and reset

reg clk   = 1'b0;
reg reset = 1'b1;

always #10 clk = ~clk;  // 50 MHz


// DUT I/O

wire weight_spi_clk;
wire weight_spi_mosi;
wire weight_spi_miso;
wire weight_spi_cs_n;
wire weight_boot_done;


// DUT — top.sv

top #(
    .MEM_WORDS             (1024),
    .BOOT_WORDS            (1),       // 1 dummy word → firmware boot_done fires fast
    .FIRMWARE_HEX          (""),
    .WEIGHT_INIT_HEX       (""),
    .CLK_HZ                (1000),
    .GT_CLK_HZ             (1000),
    .GT_EPOCH_HZ           (100),
    .GT_EPOCH_COUNT_MAX    (300),
    .ACC_POLL_PERIOD_TICKS (8),
    .PPG_POLL_PERIOD_TICKS (2),
    .PPG_WATERMARK         (8),
    .PPG_MAX_BURST_SAMPLES (32),
    .CFG_REFRACT_MS        (250),
    .CFG_RR_MIN_MS         (300),
    .CFG_RR_MAX_MS         (2000),
    .CFG_Q_MIN_ACCEPT      (0),
    .CFG_BEAT_Q_MIN        (0),
    .CFG_MIN_VALID_FRAC    (0),
    .CFG_MAX_DOUBLE        (8'd4),
    .CFG_MAX_MISSED        (8'd3),
    .CFG_MOTION_HI_TH      (16'hFFFF),
    .CFG_MAX_MOTION_HI     (16'hFFFF),
    .MSSD_MIN_RR_COUNT     (1)
) dut (
    .clk_i                 (clk),
    .reset_i               (reset),
    .i2c_scl_i             (1'b1),
    .i2c_sda_io            (),
    .i2c_sda_i             (1'b1),
    .i2c_sda_drive_low_o   (),
    // Feature outputs — unused
    .feat_valid_o          (),
    .time_feat_o           (),
    .motion_feat_o         (),
    .delta_hr_feat_o       (),
    .mssd_feat_o           (),
    .ml_update_gate_o      (),
    .invalid_reason_o      (),
    // Weight SPI — connected to weight flash model
    .weight_spi_clk_o      (weight_spi_clk),
    .weight_spi_mosi_o     (weight_spi_mosi),
    .weight_spi_miso_i     (weight_spi_miso),
    .weight_spi_cs_n_o     (weight_spi_cs_n),
    .weight_boot_done_o    (weight_boot_done),
    // CPU-driven SPI master — not used
    .spi_clk_o             (),
    .spi_mosi_o            (),
    .spi_miso_i            (1'b1),
    .spi_cs_n_o            (),
    // Firmware boot SPI — MISO tied high: one 0xFFFFFFFF word, boot_done fires fast
    .boot_spi_clk_o        (),
    .boot_spi_mosi_o       (),
    .boot_spi_miso_i       (1'b1),
    .boot_spi_cs_n_o       (),
    // Misc
    .epoch_end_o           (),
    .alarm_o               (),
    .logit0                (),
    .logit1                (),
    .test_mode_i           (4'b0),
    .test_force_irq_i      (1'b0),
    .test_force_wake_i     (1'b0),
    .test_irq_src_i        (3'b000),
    .irq_eoi_o             (),
    .boot_done_o           (),
    .pico_trap_o           (),
    .pico_cpu_clk_en_o     (),
    .pico_mem_valid_o      (),
    .pico_mem_instr_o      (),
    .pico_mem_ready_o      (),
    .pico_mem_wstrb_o      (),
    .pico_mem_addr_o       (),
    .pico_mem_wdata_o      (),
    .pico_irq_o            (),
    .pico_sleeping_o       (),
    .host_i2c_irq_event_o  (),
    .ml_irq_o              (),
    .timer_event_o         ()
);


// Weight flash model

spi_flash_model #(
    .FLASH_WORDS    (WEIGHT_WORDS),
    .FLASH_INIT_HEX ("firmware/build/generated/taketwo_params.hex")
) u_weight_flash (
    .spi_clk  (weight_spi_clk),
    .spi_cs_n (weight_spi_cs_n),
    .spi_mosi (weight_spi_mosi),
    .spi_miso (weight_spi_miso)
);


// SPI activity monitor (inference-time flash reads)

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
        if (prev_spi_cs_n && !weight_spi_cs_n)
            spi_cs_asserts <= spi_cs_asserts + 1;
        prev_spi_cs_n <= weight_spi_cs_n;

        if (!prev_spi_clk && weight_spi_clk && !weight_spi_cs_n)
            spi_bit_count <= spi_bit_count + 1;
        prev_spi_clk <= weight_spi_clk;
    end
end

// AXI read beat monitor (wram_* wires connect taketwo maxi → weight_flash_axi saxi)

integer wram_read_beats;
reg     wram_araddr_ok;

always @(posedge clk) begin
    if (reset) begin
        wram_read_beats <= 0;
        wram_araddr_ok  <= 1'b0;
    end else begin
        if (dut.wram_rvalid && dut.wram_rready)
            wram_read_beats <= wram_read_beats + 1;
        if (dut.wram_arvalid && dut.wram_arready)
            if (dut.wram_araddr >= WEIGHT_BASE &&
                dut.wram_araddr <  WEIGHT_BASE + 32'h4000)
                wram_araddr_ok <= 1'b1;
    end
end


// AXI-Lite write task — drives taketwo's saxi_* via dut.ml_saxi_* wires.

task axil_write_taketwo;
    input [31:0] offset;
    input [31:0] data;
    integer t;
    begin
        force dut.ml_saxi_awaddr  = offset;
        force dut.ml_saxi_awprot  = 3'b000;
        force dut.ml_saxi_awvalid = 1'b1;
        force dut.ml_saxi_wdata   = data;
        force dut.ml_saxi_wstrb   = 4'hF;
        force dut.ml_saxi_wvalid  = 1'b1;
        force dut.ml_saxi_bready  = 1'b1;

        @(posedge clk);
        t = 0;
        while (!dut.ml_saxi_awready && t < 20) begin
            @(posedge clk); t = t + 1;
        end
        @(posedge clk);

        t = 0;
        while (!dut.ml_saxi_wready && t < 20) begin
            @(posedge clk); t = t + 1;
        end
        @(posedge clk);

        t = 0;
        while (!dut.ml_saxi_bvalid && t < 20) begin
            @(posedge clk); t = t + 1;
        end

        release dut.ml_saxi_awvalid;
        release dut.ml_saxi_awaddr;
        release dut.ml_saxi_awprot;
        release dut.ml_saxi_wvalid;
        release dut.ml_saxi_wdata;
        release dut.ml_saxi_wstrb;
        release dut.ml_saxi_bready;
        @(posedge clk);
    end
endtask

// Main test sequence

integer cycles;
integer failures;
integer tw;

initial begin
    cycles   = 0;
    failures = 0;

    $display("[TB] tb_weight_boot start");
    $display("     weight_boot_done_o is tied 1 — flash bridge active at inference time");

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    // weight_boot_done is permanently 1'b1 — skip straight to Stage 2.
    repeat (20) @(posedge clk);
    cycles = 20;

    if (!weight_boot_done) begin
        $display("FAIL: weight_boot_done not asserted after reset (should be tied 1)");
        $fatal(1);
    end

    // Stage 2: trigger taketwo to run one inference pass via weight_flash_axi.
    $display("[cyc %0d] Stage 2 start — enabling ML domain", cycles);
    force dut.ml_en = 1'b1;
    repeat (2) @(posedge clk);

    // Set _maxi_global_base_addr = WEIGHT_BASE (reg 32, offset 0x80)
    $display("[cyc %0d] Stage 2: writing maxi_global_base_addr = 0x%08x",
             cycles, WEIGHT_BASE);
    axil_write_taketwo(32'h80, WEIGHT_BASE);

    // Assert start trigger (reg 4, offset 0x10) to launch inference
    $display("[cyc %0d] Stage 2: writing start trigger (reg4 = 1)", cycles);
    axil_write_taketwo(32'h10, 32'h1);
    $display("[cyc %0d] Stage 2: taketwo triggered — watching AXI master + SPI",
             cycles);

    // Wait for taketwo to issue >= MIN_AXI_BEATS read beats
    tw = 0;
    while (wram_read_beats < MIN_AXI_BEATS && tw < S2_TIMEOUT) begin
        @(posedge clk);
        cycles = cycles + 1;
        tw     = tw + 1;
    end
    @(posedge clk);

    release dut.ml_en;

    // --- Check 1: AXI read address was within WEIGHT_BASE range ---
    if (!wram_araddr_ok) begin
        $display("FAIL: taketwo never issued AXI read at WEIGHT_BASE range [0x%08x..0x%08x)",
                 WEIGHT_BASE, WEIGHT_BASE + 32'h4000);
        failures = failures + 1;
    end

    // --- Check 2: enough AXI read beats (one complete inference pass) ---
    if (wram_read_beats < MIN_AXI_BEATS) begin
        $display("FAIL: taketwo only issued %0d AXI read beats (expected >= %0d)",
                 wram_read_beats, MIN_AXI_BEATS);
        failures = failures + 1;
    end

    // --- Check 3: SPI CS was asserted (flash was accessed during inference) ---
    if (spi_cs_asserts == 0) begin
        $display("FAIL: weight SPI CS never asserted during inference");
        failures = failures + 1;
    end

    // --- Check 4: enough SPI bits clocked (at least 134 words × 32 bits) ---
    if (spi_bit_count < MIN_SPI_BITS) begin
        $display("FAIL: too few SPI clock edges: %0d (expected >= %0d)",
                 spi_bit_count, MIN_SPI_BITS);
        failures = failures + 1;
    end

    if (failures == 0) begin
        $display("PASS: tb_weight_boot — all 4 checks passed");
        $display("  Stage 2: wram_araddr_ok=%0d  wram_read_beats=%0d",
                 wram_araddr_ok, wram_read_beats);
        $display("  SPI:     cs_asserts=%0d  spi_bits=%0d",
                 spi_cs_asserts, spi_bit_count);
        $finish;
    end else begin
        $display("FAIL: tb_weight_boot — %0d check(s) failed", failures);
        $fatal(1);
    end
end


// VCD dump

initial begin
    $dumpfile("sim/build/weight_boot.vcd");
    $dumpvars(0, tb_weight_boot);
end

endmodule
