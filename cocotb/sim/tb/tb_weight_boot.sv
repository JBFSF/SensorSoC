`timescale 1ns/1ps
//
// tb_weight_boot.sv
//
// Verifies the two-stage hardware weight-boot path:
//
//   Stage 1 — SPI flash -> weight_ram_axi
//     u_weight_boot_ctrl (spi_boot_ctrl) reads WEIGHT_WORDS 32-bit words
//     from SPI flash and writes them into weight_ram_axi via the CPU MMIO
//     port.  weight_boot_done_o asserts when all words are loaded.
//
//   Stage 2 — weight_ram_axi -> taketwo internal SRAMs
//     Once weight_boot_done, we drive taketwo's AXI-Lite slave directly
//     from the testbench (bypassing the CPU/bridge) to:
//       a. Set _maxi_global_base_addr = WEIGHT_BASE (0x0300_6000).
//       b. Assert the start trigger (_saxi_register_4 = 1).
//     taketwo's AXI4 master then reads from weight_ram_axi and loads
//     the data into the internal gf180mcu_fd_ip_sram__sram512x8m8wm1
//     arrays.
//
// Stage 1 checks:
//   1. weight SPI CS was asserted at least once.
//   2. Enough SPI bits were clocked (8 cmd + 24 addr + WEIGHT_WORDS*32 data).
//   3. weight_ram_axi.mem[0..3] match weight_flash.mem[0..3].
//
// Stage 2 checks:
//   4. taketwo issued at least one AXI read within the WEIGHT_BASE range.
//   5. taketwo issued >= WEIGHT_WORDS AXI read beats (full load attempted).
//
// Run via: make sim-weight-boot
//

module tb_weight_boot;

localparam int unsigned WEIGHT_WORDS = 16;
localparam int unsigned TB_TIMEOUT   = 20_000;
localparam int unsigned S2_TIMEOUT   = 200_000; // beat-wait limit
// Minimum SPI bits: 8 (cmd) + 24 (addr) + WEIGHT_WORDS*32 (data)
localparam int unsigned MIN_SPI_BITS = 8 + 24 + WEIGHT_WORDS * 32;
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


// Weight flash model — first 16 words of taketwo_params.hex

spi_flash_model #(
    .FLASH_WORDS    (WEIGHT_WORDS),
    .FLASH_INIT_HEX ("firmware/build/generated/taketwo_params.hex")
) u_weight_flash (
    .spi_clk  (weight_spi_clk),
    .spi_cs_n (weight_spi_cs_n),
    .spi_mosi (weight_spi_mosi),
    .spi_miso (weight_spi_miso)
);


// Stage 1

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

// Stage 2
// wram_* wires in dut connect taketwo_wrap.maxi_* to weight_ram_axi.saxi_*

integer wram_read_beats;   // count of rvalid && rready beats
reg     wram_araddr_ok;    // went high when araddr was in WEIGHT_BASE range

always @(posedge clk) begin
    if (reset) begin
        wram_read_beats <= 0;
        wram_araddr_ok  <= 1'b0;
    end else begin
        if (dut.wram_rvalid && dut.wram_rready)
            wram_read_beats <= wram_read_beats + 1;
        if (dut.wram_arvalid && dut.wram_arready)
            if (dut.wram_araddr >= WEIGHT_BASE &&
                dut.wram_araddr <  WEIGHT_BASE + 32'h4000)  // 16KB weight_ram_axi window
                wram_araddr_ok <= 1'b1;
    end
end


// AXI-Lite write task — drives taketwo's saxi_* via dut.ml_saxi_* wires.
// Uses force/release to bypass the ml_axil_bridge_mmio (which is idle
// when the CPU has no firmware).  taketwo's saxi slave is registered:
//   AW handshake fires 1 clock after awvalid (registered prev_awvalid).
//   W  handshake fires when FSM reaches state 3 (~2 clocks after AW).
//   B  handshake fires 1 clock after W completes.

task axil_write_taketwo;
    input [31:0] offset;   // byte offset within taketwo's register space
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

        // Wait for AW handshake (awready fires 1 clock after awvalid is seen)
        @(posedge clk);
        t = 0;
        while (!dut.ml_saxi_awready && t < 20) begin
            @(posedge clk); t = t + 1;
        end
        @(posedge clk);   // let writevalid propagate through NBA

        // Wait for W handshake (wready is combinatorial from FSM==3)
        t = 0;
        while (!dut.ml_saxi_wready && t < 20) begin
            @(posedge clk); t = t + 1;
        end
        @(posedge clk);   // W data written to register; bvalid scheduled

        // Wait for B channel (write response)
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
    $display("     WEIGHT_WORDS=%0d  flash=firmware/build/generated/taketwo_params.hex",
             WEIGHT_WORDS);

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released — weight boot controller running", $time);

    // stage 1 (waiting for weight_boot_done)

    while (cycles < TB_TIMEOUT) begin
        @(posedge clk);
        cycles = cycles + 1;

        if (weight_boot_done) begin
            $display("[cyc %0d] weight_boot_done asserted — verifying weight_ram contents",
                     cycles);

            // Extra cycle for final write to commit.
            @(posedge clk);

            // --- Check 1: SPI CS asserted ---
            if (spi_cs_asserts == 0) begin
                $display("FAIL: weight SPI CS never asserted");
                failures = failures + 1;
            end

            // --- Check 2: Enough SPI bits clocked ---
            if (spi_bit_count < MIN_SPI_BITS) begin
                $display("FAIL: too few weight SPI bits: %0d (expected >= %0d)",
                         spi_bit_count, MIN_SPI_BITS);
                failures = failures + 1;
            end

            // --- Check 3: weight_ram_axi contents match flash ---
            if (dut.u_weight_ram.mem[0] !== u_weight_flash.mem[0]) begin
                $display("FAIL: wram[0]=0x%08x != flash[0]=0x%08x",
                         dut.u_weight_ram.mem[0], u_weight_flash.mem[0]);
                failures = failures + 1;
            end
            if (dut.u_weight_ram.mem[1] !== u_weight_flash.mem[1]) begin
                $display("FAIL: wram[1]=0x%08x != flash[1]=0x%08x",
                         dut.u_weight_ram.mem[1], u_weight_flash.mem[1]);
                failures = failures + 1;
            end
            if (dut.u_weight_ram.mem[2] !== u_weight_flash.mem[2]) begin
                $display("FAIL: wram[2]=0x%08x != flash[2]=0x%08x",
                         dut.u_weight_ram.mem[2], u_weight_flash.mem[2]);
                failures = failures + 1;
            end
            if (dut.u_weight_ram.mem[3] !== u_weight_flash.mem[3]) begin
                $display("FAIL: wram[3]=0x%08x != flash[3]=0x%08x",
                         dut.u_weight_ram.mem[3], u_weight_flash.mem[3]);
                failures = failures + 1;
            end

            if (failures > 0) begin
                $display("FAIL: Stage 1 — %0d check(s) failed, aborting", failures);
                $fatal(1);
            end

            $display("PASS: Stage 1 (SPI→weight_ram_axi)");
            $display("  spi_cs=%0d  spi_bits=%0d", spi_cs_asserts, spi_bit_count);
            $display("  wram[0..3] = %08x %08x %08x %08x",
                         dut.u_weight_ram.mem[0], dut.u_weight_ram.mem[1],
                         dut.u_weight_ram.mem[2], dut.u_weight_ram.mem[3]);
            $display("  flash[0..3]= %08x %08x %08x %08x",
                         u_weight_flash.mem[0], u_weight_flash.mem[1],
                         u_weight_flash.mem[2], u_weight_flash.mem[3]);
            // stage 2 (trigger taketwo to read from weight_ram_axi)
            // top_fsm starts in SLEEP (ml_en=0).  Force ml_en=1 so taketwo's
            // AXI master signals are not gated.  Then drive taketwo's saxi
            // slave directly to set the base address and fire the start trigger.
            $display("[cyc %0d] Stage 2 start — enabling ML domain", cycles);
            force dut.ml_en = 1'b1;
            repeat (2) @(posedge clk);

            // 2a. Set _maxi_global_base_addr = WEIGHT_BASE (reg 32, offset 0x80)
            $display("[cyc %0d] Stage 2: writing maxi_global_base_addr = 0x%08x",
                     cycles, WEIGHT_BASE);
            axil_write_taketwo(32'h80, WEIGHT_BASE);

            // 2b. Assert start trigger (reg 4, offset 0x10) to launch inference
            $display("[cyc %0d] Stage 2: writing start trigger (reg4 = 1)", cycles);
            axil_write_taketwo(32'h10, 32'h1);
            $display("[cyc %0d] Stage 2: taketwo triggered — watching AXI master",
                     cycles);

            // Wait for taketwo to issue >= WEIGHT_WORDS read beats from weight_ram_axi
            tw = 0;
            while (wram_read_beats < WEIGHT_WORDS && tw < S2_TIMEOUT) begin
                @(posedge clk);
                cycles = cycles + 1;
                tw     = tw + 1;
            end
            @(posedge clk);   // let last beat settle

            release dut.ml_en;

            // --- Check 4: AXI read address was within WEIGHT_BASE range ---
            if (!wram_araddr_ok) begin
                $display("FAIL: taketwo never issued AXI read at WEIGHT_BASE range [0x%08x..0x%08x)",
                         WEIGHT_BASE, WEIGHT_BASE + 32'h4000);
                failures = failures + 1;
            end

            // --- Check 5: enough AXI read beats ---
            if (wram_read_beats < WEIGHT_WORDS) begin
                $display("FAIL: taketwo only issued %0d AXI read beats (expected >= %0d)",
                         wram_read_beats, WEIGHT_WORDS);
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_weight_boot — all %0d checks passed", 5);
                $display("  Stage 1: spi_cs=%0d  spi_bits=%0d", spi_cs_asserts, spi_bit_count);
                $display("  Stage 2: wram_araddr_ok=%0d  wram_read_beats=%0d",
                         wram_araddr_ok, wram_read_beats);

                $finish;
            end else begin
                $display("FAIL: tb_weight_boot — %0d check(s) failed", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout — weight_boot_done never asserted after %0d cycles", TB_TIMEOUT);
    $display("  spi_cs=%0d  spi_bits=%0d", spi_cs_asserts, spi_bit_count);
    $fatal(1);
end


// VCD dump

initial begin
    $dumpfile("sim/build/weight_boot.vcd");
    $dumpvars(0, tb_weight_boot);
end

endmodule
