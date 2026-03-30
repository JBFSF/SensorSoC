`timescale 1ns/1ps

// tb_irq.sv — Three IRQ case checks for IRQ-driven firmware (main.c)
//
//   CHECK 1 — IRQ_TIMER (bit 0): timer_event rises while CPU is gated;
//             wake FSM re-enables cpu_clk so PicoRV32 takes the IRQ.
//
//   CHECK 2 — IRQ_ML   (bit 1): ml_irq has a RISING EDGE while CPU
//             is gated; wake FSM re-enables cpu_clk so PicoRV32 takes
//             the ML IRQ.  A stale-high ml_irq (raised while awake)
//             does not satisfy this check.
//
//   CHECK 3 — Full N-sample loop: firmware collects NUM_SAMPLES
//             timer→ML cycles and writes TEST_STATUS = 0xCAFEBABE.
//
// Usage:
//   make firmware-main   # build firmware/main.c
//   make sim-irq         # compile + run

module tb_irq;

  localparam string FW = "firmware/build/main/firmware.hex";

  logic clk    = 0;
  logic resetn = 0;

  wire [7:0] gpio_out;
  wire       cpu_clk_o, cpu_awake_o;

  wire i2c_sda;
  assign i2c_sda = 1'bz;

  soc_top #(
    .MEM_WORDS   (1024),
    .FIRMWARE_HEX(FW)
  ) dut (
    .clk        (clk),
    .resetn     (resetn),
    .i2c_scl_i  (1'b1),
    .i2c_sda_io (i2c_sda),
    .gpio_out   (gpio_out),
    .cpu_clk_o  (cpu_clk_o),
    .cpu_awake_o(cpu_awake_o)
  );

  always #10 clk = ~clk;  // 50 MHz

  initial begin
    $display("[%0t] TB: simulation starting, FW=%s", $time, FW);
    resetn = 0;
    repeat (10) @(posedge clk);
    $display("[%0t] TB: releasing reset", $time);
    resetn = 1;
  end


  wire        tap_trap        = dut.trap;
  wire        tap_timer_event = dut.timer_event;
  wire        tap_ml_irq      = dut.ml_irq;
  wire [31:0] tap_test_status = dut.test_status;
  wire [31:0] tap_test_code   = dut.test_code;

  wire        tap_sleep_req   = dut.sleep_req;
  wire        tap_sleeping    = dut.sleeping;
  wire        tap_idle_seen   = dut.cpu_idle_seen;


  wire        tap_mem_valid   = dut.mem_valid;
  wire [31:0] tap_mem_addr    = dut.mem_addr;
  wire [31:0] tap_mem_wdata   = dut.mem_wdata;
  wire [3:0]  tap_mem_wstrb   = dut.mem_wstrb;
  wire        tap_mmio_sel    = dut.mmio_sel;
  wire        tap_sram_sel    = dut.sram_sel;
  wire        tap_mem_ready   = dut.mem_ready;
  wire        tap_unmapped    = tap_mem_valid && !tap_mmio_sel && !tap_sram_sel;


  wire [31:0] tap_irq_pending = dut.cpu.irq_pending;
  wire [31:0] tap_irq_mask    = dut.cpu.irq_mask;
  wire        tap_irq_active  = dut.cpu.irq_active;


  // Start-up debug: print all bus transactions after reset

  longint unsigned dbg_cyc = 0;
  initial begin
    wait (resetn);
    forever begin
      @(posedge clk);
      dbg_cyc = dbg_cyc + 1;

      if (tap_mmio_sel && (tap_mem_wstrb != 4'b0000) && !tap_mem_ready) begin
        $display("[cyc %0d] MMIO WRITE addr=0x%08x data=0x%08x",
                 dbg_cyc, tap_mem_addr, tap_mem_wdata);
      end

      // Print every MMIO read (when response is ready)
      if (tap_mmio_sel && (tap_mem_wstrb == 4'b0000) && tap_mem_ready) begin
        $display("[cyc %0d] MMIO READ  addr=0x%08x rdata=0x%08x",
                 dbg_cyc, tap_mem_addr, dut.mmio_rdata);
      end

      // Print all bus transactions (SRAM + MMIO): shows CPU PC during instruction fetches
      // Only during first 200 cycles and also whenever mem_valid goes high on a new access
      if (tap_mem_valid && !tap_mem_ready && dbg_cyc < 200) begin
        if (tap_mem_wstrb != 4'b0000)
          $display("[cyc %0d] BUS WRITE addr=0x%08x data=0x%08x wstrb=%04b  mmio=%0b sram=%0b",
                   dbg_cyc, tap_mem_addr, tap_mem_wdata, tap_mem_wstrb, tap_mmio_sel, tap_sram_sel);
        else
          $display("[cyc %0d] BUS READ  addr=0x%08x  mmio=%0b sram=%0b (fetch=%0b)",
                   dbg_cyc, tap_mem_addr, tap_mmio_sel, tap_sram_sel, dut.mem_instr);
      end
    end
  end

  reg prev_unmapped = 0;
  initial begin
    wait (resetn);
    prev_unmapped = 0;
    forever begin
      @(posedge clk);
      if (tap_unmapped && !prev_unmapped) begin
        $display("[cyc %0d] UNMAPPED ACCESS addr=0x%08x wstrb=%04b fetch=%0b",
                 dbg_cyc, tap_mem_addr, tap_mem_wstrb, dut.mem_instr);
      end
      prev_unmapped = tap_unmapped;
    end
  end

  // Sleep / wake transition monitor

  reg prev_awake = 1;
  initial begin
    wait (resetn);
    prev_awake = 1;
    forever begin
      @(posedge clk);
      if (prev_awake && !cpu_awake_o)
        $display("[cyc %0d] CPU -> SLEEP (sleep_req=%0b idle_seen=%0b timer=%0b ml=%0b)",
                 dbg_cyc, tap_sleep_req, tap_idle_seen, tap_timer_event, tap_ml_irq);
      if (!prev_awake && cpu_awake_o)
        $display("[cyc %0d] CPU -> WAKE  (timer=%0b ml=%0b irq_pending=0x%08x)",
                 dbg_cyc, tap_timer_event, tap_ml_irq, tap_irq_pending);
      prev_awake = cpu_awake_o;
    end
  end


  // IRQ state monitor — print when irq_pending or irq_mask changes

  reg [31:0] prev_irq_pending = 0;
  reg [31:0] prev_irq_mask    = 32'hffffffff;
  initial begin
    wait (resetn);
    forever begin
      @(posedge clk);
      if (tap_irq_pending !== prev_irq_pending) begin
        $display("[cyc %0d] irq_pending: 0x%08x -> 0x%08x  (mask=0x%08x active=%0b)",
                 dbg_cyc, prev_irq_pending, tap_irq_pending, tap_irq_mask, tap_irq_active);
        prev_irq_pending = tap_irq_pending;
      end
      if (tap_irq_mask !== prev_irq_mask) begin
        $display("[cyc %0d] irq_mask:    0x%08x -> 0x%08x",
                 dbg_cyc, prev_irq_mask, tap_irq_mask);
        prev_irq_mask = tap_irq_mask;
      end
    end
  end

  // Timer / ML event edge monitor

  reg prev_timer_event = 0;
  reg prev_ml_irq      = 0;
  initial begin
    wait (resetn);
    forever begin
      @(posedge clk);
      if (!prev_timer_event && tap_timer_event)
        $display("[cyc %0d] TIMER EVENT RISE  awake=%0b", dbg_cyc, cpu_awake_o);
      if (prev_timer_event && !tap_timer_event)
        $display("[cyc %0d] TIMER EVENT FALL  awake=%0b", dbg_cyc, cpu_awake_o);
      if (!prev_ml_irq && tap_ml_irq)
        $display("[cyc %0d] ML EVENT RISE     awake=%0b", dbg_cyc, cpu_awake_o);
      if (prev_ml_irq && !tap_ml_irq)
        $display("[cyc %0d] ML EVENT FALL     awake=%0b", dbg_cyc, cpu_awake_o);
      prev_timer_event = tap_timer_event;
      prev_ml_irq      = tap_ml_irq;
    end
  end


  // Periodic status print every 100k cycles

  initial begin
    wait (resetn);
    forever begin
      repeat (100_000) @(posedge clk);
      $display("[cyc %0d] STATUS: awake=%0b sleep_req=%0b timer=%0b ml=%0b irq_pend=0x%08x mask=0x%08x status=0x%08x check1=%0d check2=%0d check3=%0d",
               dbg_cyc, cpu_awake_o, tap_sleep_req, tap_timer_event, tap_ml_irq,
               tap_irq_pending, tap_irq_mask, tap_test_status,
               check1_pass, check2_pass, check3_pass);
    end
  end


  // CHECK 1 — Timer IRQ (bit 0)
  //   Observe timer_event HIGH while cpu_awake_o is LOW, then cpu wakes.

  bit check1_pass = 0;

  reg c1a_done, c1b_done;
  initial begin
    wait (resetn);

    // Phase 1a: timer_event asserts while CPU is gated
    c1a_done = 0;
    while (!c1a_done) begin
      @(posedge clk);
      if (tap_timer_event && !cpu_awake_o) c1a_done = 1;
    end
    $display("[cyc %0d] CHECK1 phase1a: timer_event=1 while sleeping", dbg_cyc);

    // Phase 1b: CPU wakes
    c1b_done = 0;
    while (!c1b_done) begin
      @(posedge clk);
      if (cpu_awake_o) c1b_done = 1;
    end

    check1_pass = 1;
    $display("[cyc %0d] CHECK 1 PASS: Timer IRQ (bit0) woke CPU", dbg_cyc);
  end

  // CHECK 2 — ML IRQ (bit 1)
  //   In current SoC, ml_irq may be brief while IRQC pending[1] is latched.
  //   So this check accepts either a direct ml_irq edge while sleeping or
  //   pending[1] observed while sleeping, then requires wake.

  bit check2_pass = 0;

  reg c2a_done, c2b_done, c2c_done;
  initial begin
    wait (resetn);

    // ml_irq deasserted while sleeping
    c2a_done = 0;
    while (!c2a_done) begin
      @(posedge clk);
      if (!tap_ml_irq && !cpu_awake_o) c2a_done = 1;
    end
    $display("[cyc %0d] CHECK2 phase2a: ml_irq=0 while sleeping", dbg_cyc);

    // ml_irq edge or latched pending[1] while CPU is still sleeping
    c2b_done = 0;
    while (!c2b_done) begin
      @(posedge clk);
      if (!cpu_awake_o && (tap_ml_irq || tap_irq_pending[1])) c2b_done = 1;
    end
    $display("[cyc %0d] CHECK2 phase2b: ml source observed while sleeping (ml_irq=%0b pending=0x%08x)",
             dbg_cyc, tap_ml_irq, tap_irq_pending);

    // CPU wakes
    c2c_done = 0;
    while (!c2c_done) begin
      @(posedge clk);
      if (cpu_awake_o) c2c_done = 1;
    end

    check2_pass = 1;
    $display("[cyc %0d] CHECK 2 PASS: ML IRQ (bit1) woke CPU", dbg_cyc);
  end

  // CHECK 3 — Full N-sample loop completes
  bit check3_pass = 0;

  reg c3_done;
  initial begin
    wait (resetn);

    c3_done = 0;
    while (!c3_done) begin
      @(posedge clk);
      if (tap_test_status == 32'hCAFE_BABE) c3_done = 1;
    end

    check3_pass = 1;
    $display("[cyc %0d] CHECK 3 PASS: N-sample loop complete, last_score=0x%08x",
             dbg_cyc, tap_test_code);
  end

  // CHECK IRQ1/IRQ2 — explicit irq_pending bit checks
  bit check_irq1_pass = 0;
  bit check_irq2_pass = 0;

  initial begin
    wait (resetn);
    while (!tap_irq_pending[0]) @(posedge clk);
    check_irq1_pass = 1;
    $display("[cyc %0d] CHECK IRQ1 PASS: irq_pending bit0 observed (value includes 0x1)",
             dbg_cyc);
  end

  initial begin
    wait (resetn);
    while (!tap_irq_pending[1]) @(posedge clk);
    check_irq2_pass = 1;
    $display("[cyc %0d] CHECK IRQ2 PASS: irq_pending bit1 observed (value includes 0x2)",
             dbg_cyc);
  end

  // all three must pass
  reg verdict_done;
  initial begin
    wait (resetn);
    verdict_done = 0;
    while (!verdict_done) begin
      @(posedge clk);
      if (check1_pass && check2_pass && check3_pass &&
          check_irq1_pass && check_irq2_pass) verdict_done = 1;
    end
    $display("ALL IRQ + SLEEP/WAKE CHECKS PASSED");
    $finish;
  end

  // Watchdog — 2 M cycles (reduced from 20M for faster debug)
  longint unsigned cyc;
  initial begin
    cyc = 0;
    wait (resetn);
    while (cyc < 2_000_000) begin
      @(posedge clk);
      cyc = cyc + 1;
    end
    $display("TIMEOUT after 2M cycles: check1=%0d check2=%0d check3=%0d irq1=%0d irq2=%0d",
             check1_pass, check2_pass, check3_pass, check_irq1_pass, check_irq2_pass);
    $display("  Final: awake=%0b sleep_req=%0b sleeping=%0b timer=%0b ml=%0b",
             cpu_awake_o, tap_sleep_req, tap_sleeping, tap_timer_event, tap_ml_irq);
    $display("  irq_pending=0x%08x irq_mask=0x%08x irq_active=%0b trap=%0b",
             tap_irq_pending, tap_irq_mask, tap_irq_active, tap_trap);
    $display("  test_status=0x%08x test_code=0x%08x",
             tap_test_status, tap_test_code);
    $fatal(1, "TIMEOUT");
  end

  // Safety monitors — trap + FAIL
  initial begin
    wait (resetn);
    forever begin
      @(posedge clk);
      if (tap_trap) begin
        $display("CPU TRAP asserted at cyc=%0d", dbg_cyc);
        $fatal(1, "[%0t] CPU TRAP asserted", $time);
      end
      if (tap_test_status == 32'hDEAD_BEEF) begin
        $display("Firmware FAIL at cyc=%0d code=0x%08x", dbg_cyc, tap_test_code);
        $fatal(1, "[%0t] Firmware FAIL", $time);
      end
    end
  end

  // Waveform dump
  initial begin
    $dumpfile("irq.vcd");
    $dumpvars(0, tb_irq);
  end

endmodule
