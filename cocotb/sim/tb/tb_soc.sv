`timescale 1ns/1ps

module tb_soc #(
  parameter string FW               = "firmware/build/test_sleepwake/firmware.hex",
  parameter string WEIGHT_INIT_HEX  = "",
  parameter int    CHECK_SLEEP_WAKE = 1
);

  initial begin
    $display("[TB] Firmware file (parameter) = %s", FW);
  end

  // Optional: page constants for runtime filtering (NOT hierarchical)
  localparam logic [31:12] TIMER_PAGE = 20'h03002;
  localparam logic [31:12] PWR_PAGE   = 20'h03001;
  localparam logic [31:12] TEST_PAGE  = 20'h0300F;

  logic clk = 0;
  logic resetn = 0;

  wire [7:0] gpio_out;
  wire cpu_clk_o, cpu_awake_o;

  // DUT
  wire i2c_sda;
  assign i2c_sda = 1'bz;

  soc_top #(
    .MEM_WORDS(1024),
    .FIRMWARE_HEX(FW),
    .WEIGHT_INIT_HEX(WEIGHT_INIT_HEX)
  ) dut (
    .clk(clk),
    .resetn(resetn),
    .i2c_scl_i(1'b1),
    .i2c_sda_io(i2c_sda),
    .gpio_out(gpio_out),
    .cpu_clk_o(cpu_clk_o),
    .cpu_awake_o(cpu_awake_o)
  );

  // 50 MHz clock
  always #10 clk = ~clk;

  // reset
  initial begin
    resetn = 0;
    repeat (10) @(posedge clk);
    resetn = 1;
  end

  // ------------------------------------------------------------
  // TAP internal DUT signals into TB wires (Icarus-safe pattern)
  // ------------------------------------------------------------
  // NOTE: These are *continuous assigns*, not params/generate.
  wire        tap_trap      = dut.trap;

  wire        tap_mem_valid = dut.mem_valid;
  wire [31:0] tap_mem_addr  = dut.mem_addr;
  wire [31:0] tap_mem_wdata = dut.mem_wdata;
  wire [3:0]  tap_mem_wstrb = dut.mem_wstrb;
  wire        tap_mmio_sel  = dut.mmio_sel;

  wire [31:0] tap_test_status = dut.test_status;
  wire [31:0] tap_test_code   = dut.test_code;

  // ----------------------------
  // Sleep/Wake observation flags
  // ----------------------------
  bit saw_sleep = 0;
  bit saw_wake  = 0;

  initial begin
    wait(resetn == 1);
    forever begin
      @(posedge clk);

      if (!cpu_awake_o)
        saw_sleep = 1;

      if (saw_sleep && cpu_awake_o)
        saw_wake = 1;
    end
  end

  // timeout watchdog
  longint unsigned cycles;
  initial begin
    cycles = 0;
    wait(resetn == 1);
    while (cycles < 20_000_000) begin
      @(posedge clk);
      cycles++;
    end
    $fatal(1, "TIMEOUT: test did not finish");
  end

  // PASS/FAIL monitor
  initial begin
    wait(resetn == 1);

    forever begin
      @(posedge clk);

      if (tap_test_status == 32'hCAFE_BABE) begin
        if (CHECK_SLEEP_WAKE && (!saw_sleep || !saw_wake)) begin
          $display("FAIL: Firmware reported PASS but did not observe cpu_awake_o 1->0->1");
          $display("  saw_sleep=%0d saw_wake=%0d", saw_sleep, saw_wake);
          $fatal(1, "Sleep/Wake not observed");
        end

        $display("PASS%s", CHECK_SLEEP_WAKE ? " (sleep/wake observed)" : "");
        $finish;
      end

      if (tap_test_status == 32'hDEAD_BEEF) begin
        $display("FAIL, code=0x%08x", tap_test_code);
        $fatal(1, "Firmware reported FAIL");
      end
    end
  end

  // Optional wave dump
  initial begin
    $dumpfile("soc.vcd");
    $dumpvars(0, tb_soc);
  end

  // Trap monitor
  initial begin
    wait(resetn == 1);
    forever begin
      @(posedge clk);
      if (tap_trap) begin
        $display("TRAP asserted at time %0t", $time);
        $fatal(1, "CPU trapped (likely bad code / bad link address / illegal instruction)");
      end
    end
  end

  // MMIO write monitor (runtime compare only; NO generate/const expr)
  initial begin
    wait(resetn == 1);
    forever begin
      @(posedge clk);

      if (tap_mmio_sel && tap_mem_valid && (tap_mem_wstrb != 4'b0000)) begin
        $display("MMIO WRITE addr=%08x data=%08x wstrb=%b time=%0t",
                 tap_mem_addr, tap_mem_wdata, tap_mem_wstrb, $time);

        // Example: only print for a specific 4KB page:
        // if (tap_mem_addr[31:12] == TIMER_PAGE) begin
        //   $display("  (timer page write)");
        // end
      end
    end
  end

  // Print when firmware writes PASS/FAIL
  logic [31:0] last_status;
  initial begin
    last_status = 32'h0;
    wait(resetn == 1);
    forever begin
      @(posedge clk);
      if (tap_test_status != last_status) begin
        $display("test_status changed: %08x -> %08x @ %0t",
                 last_status, tap_test_status, $time);
        last_status = tap_test_status;
      end
    end
  end

endmodule
