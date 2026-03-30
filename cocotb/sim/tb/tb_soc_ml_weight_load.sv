`timescale 1ns/1ps

module tb_soc_ml_weight_load #(
    parameter string FW = "firmware/build/test_ml_weights/firmware.hex"
);

localparam [31:0] WEIGHT_BASE = 32'h0300_6000;
localparam [31:0] WEIGHT_END  = 32'h0300_A000;
localparam [31:0] ML_BASE     = 32'h0300_3000;
localparam [31:0] REG_START   = ML_BASE + 32'h10;
localparam [31:0] REG_BUSY    = ML_BASE + 32'h14;
localparam [31:0] REG_GBASE   = ML_BASE + 32'h80;

localparam int unsigned TB_TIMEOUT_CYCLES = 8_000_000;
localparam int unsigned TB_PROGRESS_EVERY = 1_000_000;

reg clk;
reg resetn;
wire [7:0] gpio_out;
wire cpu_clk_o;
wire cpu_awake_o;
wire i2c_sda;
assign i2c_sda = 1'bz;

integer failures;
integer cycles;
integer weight_mmio_writes;
integer busy_reads;
integer axi_ar_hs;
integer axi_r_hs;
integer axi_aw_hs;
integer axi_w_hs;
integer axi_b_hs;
integer irq_high_cycles;
reg saw_global_base_write;
reg saw_start_write;
reg saw_busy_read;

soc_top #(
    .MEM_WORDS    (8192),
    .FIRMWARE_HEX (FW)
) dut (
    .clk        (clk),
    .resetn     (resetn),
    .i2c_scl_i  (1'b1),
    .i2c_sda_io (i2c_sda),
    .gpio_out   (gpio_out),
    .cpu_clk_o  (cpu_clk_o),
    .cpu_awake_o(cpu_awake_o)
);

always #10 clk = ~clk;  // 50MHz

always @(posedge clk) begin
    if (!resetn) begin
        weight_mmio_writes <= 0;
        busy_reads <= 0;
        axi_ar_hs <= 0;
        axi_r_hs <= 0;
        axi_aw_hs <= 0;
        axi_w_hs <= 0;
        axi_b_hs <= 0;
        irq_high_cycles <= 0;
        saw_global_base_write <= 1'b0;
        saw_start_write <= 1'b0;
        saw_busy_read <= 1'b0;
    end else begin
        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0)) begin
            if ((dut.mem_addr >= WEIGHT_BASE) && (dut.mem_addr < WEIGHT_END))
                weight_mmio_writes <= weight_mmio_writes + 1;
            if (dut.mem_addr == REG_GBASE && dut.mem_wdata == WEIGHT_BASE)
                saw_global_base_write <= 1'b1;
            if (dut.mem_addr == REG_START && dut.mem_wdata[0])
                saw_start_write <= 1'b1;
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb == 4'b0) && dut.mem_addr == REG_BUSY) begin
            busy_reads <= busy_reads + 1;
            saw_busy_read <= 1'b1;
        end

        if (dut.wram_arvalid && dut.wram_arready) axi_ar_hs <= axi_ar_hs + 1;
        if (dut.wram_rvalid  && dut.wram_rready)  axi_r_hs  <= axi_r_hs + 1;
        if (dut.wram_awvalid && dut.wram_awready) axi_aw_hs <= axi_aw_hs + 1;
        if (dut.wram_wvalid  && dut.wram_wready)  axi_w_hs  <= axi_w_hs + 1;
        if (dut.wram_bvalid  && dut.wram_bready)  axi_b_hs  <= axi_b_hs + 1;

        if (dut.ml_irq) irq_high_cycles <= irq_high_cycles + 1;
    end
end

initial begin
    clk = 1'b0;
    resetn = 1'b0;
    failures = 0;
    cycles = 0;

    $display("[TB] start FW=%s", FW);

    repeat (10) @(posedge clk);
    resetn = 1'b1;
    $display("[%0t] Reset released", $time);

    while (cycles < TB_TIMEOUT_CYCLES) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[cyc %0d] alive status=0x%08x code=0x%08x writes=%0d ar=%0d aw=%0d irq_hi=%0d",
                     cycles, dut.test_status, dut.test_code,
                     weight_mmio_writes, axi_ar_hs, axi_aw_hs, irq_high_cycles);
        end

        if (dut.trap) begin
            $display("FAIL: CPU trap asserted mem_addr=0x%08x pc=0x%08x", dut.mem_addr, dut.cpu.reg_pc);
            $fatal(1);
        end

        if (dut.test_status == 32'hDEAD_BEEF) begin
            $display("FAIL: firmware reported FAIL code=0x%08x", dut.test_code);
            $fatal(1);
        end

        if (dut.test_status == 32'hCAFE_BABE) begin
            if (weight_mmio_writes < 16) begin
                $display("FAIL: too few CPU writes to WEIGHT_BASE: %0d", weight_mmio_writes);
                failures = failures + 1;
            end
            if (!saw_global_base_write) begin
                $display("FAIL: did not observe ML_REG(0x80)=WEIGHT_BASE write");
                failures = failures + 1;
            end
            if (!saw_start_write) begin
                $display("FAIL: did not observe ML START write");
                failures = failures + 1;
            end
            if (!saw_busy_read || busy_reads == 0) begin
                $display("FAIL: did not observe BUSY polling reads");
                failures = failures + 1;
            end
            if (axi_ar_hs == 0 || axi_r_hs == 0) begin
                $display("FAIL: no AXI read activity from taketwo to weight RAM");
                failures = failures + 1;
            end
            if ((axi_aw_hs == 0) && (axi_w_hs == 0) && (axi_b_hs == 0)) begin
                $display("FAIL: no AXI write activity from taketwo to weight RAM");
                failures = failures + 1;
            end
            if (irq_high_cycles > 200000) begin
                $display("FAIL: ml_irq stuck/high too long (%0d cycles)", irq_high_cycles);
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_soc_ml_weight_load");
                $display("  writes=%0d busy_reads=%0d axi(ar/r/aw/w/b)=%0d/%0d/%0d/%0d/%0d code=0x%08x",
                         weight_mmio_writes, busy_reads,
                         axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs,
                         dut.test_code);
                $finish;
            end else begin
                $display("FAIL: tb_soc_ml_weight_load failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT_CYCLES);
    $display("  status=0x%08x code=0x%08x writes=%0d busy_reads=%0d axi=%0d/%0d/%0d/%0d/%0d",
             dut.test_status, dut.test_code, weight_mmio_writes, busy_reads,
             axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
    $fatal(1);
end

initial begin
    $dumpfile("/tmp/ml_weight_load_soc.vcd");
    $dumpvars(0, tb_soc_ml_weight_load);
end

endmodule
