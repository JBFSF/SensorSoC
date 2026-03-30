`timescale 1ns/1ps

module tb_reset_ctrl;

  localparam int HOLD = 8;

  reg  clk;
  reg  ext_resetn;
  reg  wdt_reset_req;
  reg  sw_cpu_reset_req;
  reg  sw_aon_reset_req;

  wire aon_resetn;
  wire cpu_resetn;
  wire [2:0] reset_cause;
  wire reset_in_progress;

  // DUT
  reset_ctrl #(
    .HOLD_CYCLES(HOLD),
    .WDT_GLOBAL(1'b0)
  ) dut (
    .clk(clk),
    .ext_resetn(ext_resetn),
    .wdt_reset_req(wdt_reset_req),
    .sw_cpu_reset_req(sw_cpu_reset_req),
    .sw_aon_reset_req(sw_aon_reset_req),
    .aon_resetn(aon_resetn),
    .cpu_resetn(cpu_resetn),
    .reset_cause(reset_cause),
    .reset_in_progress(reset_in_progress)
  );

  // -------------------------
  // Clock + cycle counter
  // -------------------------
  initial clk = 1'b0;
  always #5 clk = ~clk;

  int cycle = 0;
  always @(posedge clk) begin
    cycle <= cycle + 1;
  end

  // -------------------------
  // VCD
  // -------------------------
  initial begin
    $dumpfile("reset_ctrl.vcd");
    $dumpvars(0, tb_reset_ctrl);
  end

  // -------------------------
  // Pretty decode for cause
  // -------------------------
  function automatic string cause_str(input [2:0] c);
    case (c)
      3'd0: cause_str = "POR";
      3'd1: cause_str = "WDT";
      3'd2: cause_str = "SW_CPU";
      3'd3: cause_str = "SW_AON";
      default: cause_str = "UNK";
    endcase
  endfunction

  // -------------------------
  // Edge logging (only on changes)
  // -------------------------
  reg cpu_resetn_d = 1'b1;
  reg aon_resetn_d = 1'b1;

  always @(posedge clk) begin
    cpu_resetn_d <= cpu_resetn;
    aon_resetn_d <= aon_resetn;

    if (cpu_resetn_d !== cpu_resetn) begin
      if (cpu_resetn === 1'b0)
        $display("** CPU RESET ASSERT  t=%0t cyc=%0d cause=%0d (%s) cpu_cnt=%0d aon_cnt=%0d",
                 $time, cycle, reset_cause, cause_str(reset_cause), dut.cpu_cnt, dut.aon_cnt);
      else if (cpu_resetn === 1'b1)
        $display("** CPU RESET RELEASE t=%0t cyc=%0d cause=%0d (%s) cpu_cnt=%0d aon_cnt=%0d",
                 $time, cycle, reset_cause, cause_str(reset_cause), dut.cpu_cnt, dut.aon_cnt);
      else
        $display("** CPU RESET X/Z     t=%0t cyc=%0d cpu_resetn=%b", $time, cycle, cpu_resetn);
    end

    if (aon_resetn_d !== aon_resetn) begin
      if (aon_resetn === 1'b0)
        $display("** AON RESET ASSERT  t=%0t cyc=%0d cause=%0d (%s) cpu_cnt=%0d aon_cnt=%0d",
                 $time, cycle, reset_cause, cause_str(reset_cause), dut.cpu_cnt, dut.aon_cnt);
      else if (aon_resetn === 1'b1)
        $display("** AON RESET RELEASE t=%0t cyc=%0d cause=%0d (%s) cpu_cnt=%0d aon_cnt=%0d",
                 $time, cycle, reset_cause, cause_str(reset_cause), dut.cpu_cnt, dut.aon_cnt);
      else
        $display("** AON RESET X/Z     t=%0t cyc=%0d aon_resetn=%b", $time, cycle, aon_resetn);
    end
  end

  // -------------------------
  // Icarus-friendly pulse tasks
  // -------------------------
  task automatic pulse_wdt();
    begin
      $display(">> PULSE WDT      at t=%0t cyc=%0d", $time, cycle);
      wdt_reset_req = 1'b1;
      @(posedge clk);
      wdt_reset_req = 1'b0;
      $display("<< END   WDT      at t=%0t cyc=%0d", $time, cycle);
    end
  endtask

  task automatic pulse_sw_cpu();
    begin
      $display(">> PULSE SW_CPU   at t=%0t cyc=%0d", $time, cycle);
      sw_cpu_reset_req = 1'b1;
      @(posedge clk);
      sw_cpu_reset_req = 1'b0;
      $display("<< END   SW_CPU   at t=%0t cyc=%0d", $time, cycle);
    end
  endtask

  task automatic pulse_sw_aon();
    begin
      $display(">> PULSE SW_AON   at t=%0t cyc=%0d", $time, cycle);
      sw_aon_reset_req = 1'b1;
      @(posedge clk);
      sw_aon_reset_req = 1'b0;
      $display("<< END   SW_AON   at t=%0t cyc=%0d", $time, cycle);
    end
  endtask

  // -------------------------
  // Assertions helpers
  // -------------------------
  task automatic expect_high(input string name, input logic sig);
    if (sig !== 1'b1) begin
      $display("FAIL: %s expected HIGH at t=%0t cyc=%0d (got %b)", name, $time, cycle, sig);
      $fatal(1);
    end
  endtask

  task automatic expect_low(input string name, input logic sig);
    if (sig !== 1'b0) begin
      $display("FAIL: %s expected LOW at t=%0t cyc=%0d (got %b)", name, $time, cycle, sig);
      $fatal(1);
    end
  endtask

  // -------------------------
  // Icarus-safe reset pulse checkers
  // (IMPORTANT: wait on the REAL nets, not a task argument)
  // -------------------------
  task automatic expect_cpu_reset_pulse(input string name, input int expected_low_cycles);
    int start_cyc;
    begin
      $display(".. waiting for %s ASSERT (negedge) at t=%0t cyc=%0d", name, $time, cycle);
      @(negedge cpu_resetn);
      start_cyc = cycle;
      $display(".. %s asserted at t=%0t cyc=%0d", name, $time, cycle);

      $display(".. waiting for %s RELEASE (posedge) at t=%0t cyc=%0d", name, $time, cycle);
      @(posedge cpu_resetn);
      $display(".. %s released at t=%0t cyc=%0d", name, $time, cycle);

      if ((cycle - start_cyc) != expected_low_cycles) begin
        $display("FAIL: %s low cycles=%0d expected=%0d", name, (cycle - start_cyc), expected_low_cycles);
        $fatal(1);
      end else begin
        $display("PASS: %s low cycles=%0d", name, expected_low_cycles);
      end
    end
  endtask

  task automatic expect_aon_reset_pulse(input string name, input int expected_low_cycles);
    int start_cyc;
    begin
      $display(".. waiting for %s ASSERT (negedge) at t=%0t cyc=%0d", name, $time, cycle);
      @(negedge aon_resetn);
      start_cyc = cycle;
      $display(".. %s asserted at t=%0t cyc=%0d", name, $time, cycle);

      $display(".. waiting for %s RELEASE (posedge) at t=%0t cyc=%0d", name, $time, cycle);
      @(posedge aon_resetn);
      $display(".. %s released at t=%0t cyc=%0d", name, $time, cycle);

      if ((cycle - start_cyc) != expected_low_cycles) begin
        $display("FAIL: %s low cycles=%0d expected=%0d", name, (cycle - start_cyc), expected_low_cycles);
        $fatal(1);
      end else begin
        $display("PASS: %s low cycles=%0d", name, expected_low_cycles);
      end
    end
  endtask

  // -------------------------
  // Main test
  // -------------------------
  initial begin
    $display("TB starting...");

    // init
    ext_resetn       = 1'b1;
    wdt_reset_req    = 1'b0;
    sw_cpu_reset_req = 1'b0;
    sw_aon_reset_req = 1'b0;

    // TEST 1: POR async assert + sync deassert
    $display("\n==================================================");
    $display("TEST 1: POR async assert + sync deassert");
    $display("t=%0t", $time);
    $display("==================================================");
    #2;
    $display(">> ext_resetn ASSERT (drive low) at t=%0t", $time);
    ext_resetn = 1'b0;
    #1;
    expect_low("cpu_resetn (POR assert)", cpu_resetn);
    expect_low("aon_resetn (POR assert)", aon_resetn);

    $display(">> ext_resetn DEASSERT (drive high) at t=%0t", $time);
    ext_resetn = 1'b1;

    @(posedge clk); expect_low ("cpu_resetn (POR sync stage1)", cpu_resetn);
    @(posedge clk); expect_low ("cpu_resetn (POR sync stage2)", cpu_resetn);
    @(posedge clk); expect_high("cpu_resetn (POR released)",    cpu_resetn);
                   expect_high("aon_resetn (POR released)",    aon_resetn);

    // TEST 2: SW_CPU reset (CPU only)
    $display("\n==================================================");
    $display("TEST 2: SW_CPU reset (CPU only)");
    $display("t=%0t", $time);
    $display("==================================================");

    pulse_sw_cpu();

    fork
      begin
        expect_cpu_reset_pulse("cpu_resetn (SW_CPU)", HOLD);
      end
      begin
        int i;
        for (i = 0; i < HOLD+3; i++) begin
          @(posedge clk);
          if (aon_resetn !== 1'b1) begin
            $display("FAIL: aon_resetn went low during SW_CPU reset at t=%0t cyc=%0d", $time, cycle);
            $fatal(1);
          end
        end
        $display(".. aon_resetn stayed HIGH throughout SW_CPU window");
      end
    join

    // TEST 3: SW_AON reset (global)
    $display("\n==================================================");
    $display("TEST 3: SW_AON reset (global)");
    $display("t=%0t", $time);
    $display("==================================================");

    pulse_sw_aon();

    fork
      begin
        expect_cpu_reset_pulse("cpu_resetn (SW_AON)", HOLD);
      end
      begin
        expect_aon_reset_pulse("aon_resetn (SW_AON)", HOLD);
      end
    join

    // TEST 4: WDT reset (CPU only here)
    $display("\n==================================================");
    $display("TEST 4: WDT reset (CPU only)");
    $display("t=%0t", $time);
    $display("==================================================");

    pulse_wdt();
    expect_cpu_reset_pulse("cpu_resetn (WDT)", HOLD);
    expect_high("aon_resetn (WDT CPU-only)", aon_resetn);

    // TEST 5: request latching while busy
    $display("\n==================================================");
    $display("TEST 5: Latched request while busy");
    $display("==================================================");

    pulse_sw_aon();
    @(posedge clk);
    pulse_sw_cpu();

    // Wait global reset finishes
    @(posedge aon_resetn);
    $display(".. global reset finished, expecting queued CPU reset next");

    expect_cpu_reset_pulse("cpu_resetn (latched SW_CPU after busy)", HOLD);

    $display("\nALL RESET_CTRL TESTS PASSED");
    $finish;
  end

  // Timeout
  initial begin
    #200000; // 200us
    $display("TIMEOUT: testbench stuck at t=%0t  cyc=%0d", $time, cycle);
    $display("  ext_resetn=%b por_active=%b pend_cpu=%b pend_aon=%b pend_wdt=%b cpu_cnt=%0d aon_cnt=%0d cpu_resetn=%b aon_resetn=%b cause=%s",
             ext_resetn, dut.por_active, dut.pend_sw_cpu, dut.pend_sw_aon, dut.pend_wdt,
             dut.cpu_cnt, dut.aon_cnt, cpu_resetn, aon_resetn, cause_str(reset_cause));
    $fatal(1);
  end

endmodule