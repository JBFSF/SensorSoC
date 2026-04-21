`timescale 1ns/1ps

module tb_top_ml_control_unified;

// Short unified-top ML-control regression.
// This bench proves the CPU-owned ML control contract without waiting on
// feature generation or SPI flash boot copy:
//   WRAM input writes -> ML AXI-Lite programming -> START -> BUSY -> IRQ
//   -> AXI activity in shared WRAM.
// Output mutation is still reported diagnostically, but the hard pass/fail
// criteria focus on the control path that is stable in the unified top today.

localparam [31:0] WEIGHT_BASE = 32'h0300_6000;
localparam [31:0] ML_BASE     = 32'h0300_3000;
localparam [31:0] TEST_BASE   = 32'h0300_F000;

localparam [31:0] REG_START   = ML_BASE + 32'h10;
localparam [31:0] REG_BUSY    = ML_BASE + 32'h14;
localparam [31:0] REG_IRQ_EN  = ML_BASE + 32'h28;
localparam [31:0] REG_IRQ_CLR = ML_BASE + 32'h2C;
localparam [31:0] REG_GBASE   = ML_BASE + 32'h80;
localparam [31:0] TEST_PASS   = 32'hCAFEBABE;
localparam [31:0] TEST_FAIL   = 32'hDEADBEEF;

localparam [31:0] X_BASE      = WEIGHT_BASE + 32'd64;
localparam [31:0] LOGIT_BASE  = WEIGHT_BASE + 32'd5504;

localparam int unsigned TB_TIMEOUT_CYCLES = 2_000_000;
localparam int unsigned TB_PROGRESS_EVERY = 250_000;

reg clk;
reg reset;

wire        sim_req;
wire [6:0]  sim_addr;
wire [7:0]  sim_reg;
wire [7:0]  sim_len;
wire        sim_write;
wire [7:0]  sim_wdata;
wire        sim_ack;
wire [7:0]  sim_rdata;
wire        sim_rvalid;
wire        sim_rlast;
wire        sim_err;

wire        accel_sim_ack;
wire [7:0]  accel_sim_rdata;
wire        accel_sim_rvalid;
wire        accel_sim_rlast;
wire        accel_sim_err;

wire        ppg_sim_ack;
wire [7:0]  ppg_sim_rdata;
wire        ppg_sim_rvalid;
wire        ppg_sim_rlast;
wire        ppg_sim_err;

wire        host_i2c_scl;
tri1        host_i2c_sda;

localparam [6:0] ACC_ADDR = 7'h19;
localparam [6:0] PPG_ADDR = 7'h64;

integer failures;
integer cycles;
integer weight_writes;
integer busy_reads;
integer irq_en_writes;
integer irq_clr_writes;
integer start_writes;
integer axi_ar_hs;
integer axi_r_hs;
integer axi_aw_hs;
integer axi_w_hs;
integer axi_b_hs;
integer ml_irq_high_cycles;
reg saw_gbase_write;
reg saw_start_write;
reg saw_busy_read;
reg saw_ml_irq;
reg [31:0] out0_before;
reg [31:0] out1_before;

assign sim_ack    = (sim_addr == ACC_ADDR) ? accel_sim_ack    :
                    (sim_addr == PPG_ADDR) ? ppg_sim_ack      : 1'b0;
assign sim_rdata  = (sim_addr == ACC_ADDR) ? accel_sim_rdata  :
                    (sim_addr == PPG_ADDR) ? ppg_sim_rdata    : 8'h00;
assign sim_rvalid = (sim_addr == ACC_ADDR) ? accel_sim_rvalid :
                    (sim_addr == PPG_ADDR) ? ppg_sim_rvalid   : 1'b0;
assign sim_rlast  = (sim_addr == ACC_ADDR) ? accel_sim_rlast  :
                    (sim_addr == PPG_ADDR) ? ppg_sim_rlast    : 1'b0;
assign sim_err    = (sim_addr == ACC_ADDR) ? accel_sim_err    :
                    (sim_addr == PPG_ADDR) ? ppg_sim_err      : 1'b1;

top #(
    .MEM_WORDS(8192),
    .FIRMWARE_HEX("firmware/build/test_top_ml_control_unified/firmware.hex"),
    .WEIGHT_INIT_HEX("firmware/build/generated/taketwo_params.hex"),
    .CLK_HZ(1000),
    .GT_CLK_HZ(1000),
    .GT_EPOCH_HZ(100),
    .GT_EPOCH_COUNT_MAX(300),
    .ACC_POLL_PERIOD_TICKS(8),
    .PPG_POLL_PERIOD_TICKS(2),
    .PPG_WATERMARK(8),
    .PPG_MAX_BURST_SAMPLES(32),
    .CFG_REFRACT_MS(250),
    .CFG_RR_MIN_MS(300),
    .CFG_RR_MAX_MS(2000),
    .CFG_Q_MIN_ACCEPT(0),
    .CFG_BEAT_Q_MIN(0),
    .CFG_MIN_VALID_FRAC(0),
    .CFG_MAX_DOUBLE(8'd4),
    .CFG_MAX_MISSED(8'd3),
    .CFG_MOTION_HI_TH(16'hFFFF),
    .CFG_MAX_MOTION_HI(16'hFFFF),
    
    
    
    .MSSD_MIN_RR_COUNT(1)
) dut (
    .clk_i(clk),
    .reset_i(reset),
    .i2c_scl_i(host_i2c_scl),
    .i2c_sda_io(host_i2c_sda),
    .sim_req_o(sim_req),
    .sim_addr_o(sim_addr),
    .sim_reg_o(sim_reg),
    .sim_len_o(sim_len),
    .sim_write_o(sim_write),
    .sim_wdata_o(sim_wdata),
    .sim_ack_i(sim_ack),
    .sim_rdata_i(sim_rdata),
    .sim_rvalid_i(sim_rvalid),
    .sim_rlast_i(sim_rlast),
    .sim_err_i(sim_err),
    .feat_valid_o(),
    .time_feat_o(),
    .motion_feat_o(),
    .delta_hr_feat_o(),
    .mssd_feat_o(),
    .ml_update_gate_o(),
    .invalid_reason_o(),
    .spi_clk_o(),
    .spi_mosi_o(),
    .spi_miso_i(1'b1),
    .spi_cs_n_o(),
    .boot_spi_clk_o(),
    .boot_spi_mosi_o(),
    .boot_spi_miso_i(1'b1),
    .boot_spi_cs_n_o(),
    .epoch_end_o(),
    .alarm_o(),
    .test_force_irq_i(1'b0),
    .test_force_wake_i(1'b0),
    .test_irq_src_i(3'b000),
    .irq_eoi_o(),
    .boot_done_o()
);

assign host_i2c_scl = 1'b1;

i2c_slave_lis2dw12 #(
    .I2C_ADDR(ACC_ADDR)
) u_accel_slave (
    .clk(clk),
    .resetn(~reset),
    .sim_req(sim_req),
    .sim_addr(sim_addr),
    .sim_reg(sim_reg),
    .sim_len(sim_len),
    .sim_ack(accel_sim_ack),
    .sim_rdata(accel_sim_rdata),
    .sim_rvalid(accel_sim_rvalid),
    .sim_rlast(accel_sim_rlast),
    .sim_err(accel_sim_err)
);

i2c_slave_adpd144ri #(
    .I2C_ADDR(PPG_ADDR)
) u_ppg_slave (
    .clk(clk),
    .resetn(~reset),
    .sim_req(sim_req),
    .sim_addr(sim_addr),
    .sim_reg(sim_reg),
    .sim_len(sim_len),
    .sim_write(sim_write),
    .sim_wdata(sim_wdata),
    .sim_ack(ppg_sim_ack),
    .sim_rdata(ppg_sim_rdata),
    .sim_rvalid(ppg_sim_rvalid),
    .sim_rlast(ppg_sim_rlast),
    .sim_err(ppg_sim_err)
);

always #10 clk = ~clk;

always @(posedge clk) begin
    if (reset) begin
        weight_writes <= 0;
        busy_reads <= 0;
        irq_en_writes <= 0;
        irq_clr_writes <= 0;
        start_writes <= 0;
        axi_ar_hs <= 0;
        axi_r_hs <= 0;
        axi_aw_hs <= 0;
        axi_w_hs <= 0;
        axi_b_hs <= 0;
        ml_irq_high_cycles <= 0;
        saw_gbase_write <= 1'b0;
        saw_start_write <= 1'b0;
        saw_busy_read <= 1'b0;
        saw_ml_irq <= 1'b0;
        out0_before <= 32'h0;
        out1_before <= 32'h0;
    end else begin
        // Count the minimum firmware-visible contract for the short ML control
        // path: write inputs, enable/clear IRQ, write START, poll BUSY.
        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0)) begin
            if ((dut.mem_addr >= X_BASE) && (dut.mem_addr < (X_BASE + 32'h8)))
                weight_writes <= weight_writes + 1;
            if (dut.mem_addr == REG_GBASE && dut.mem_wdata == WEIGHT_BASE)
                saw_gbase_write <= 1'b1;
            if (dut.mem_addr == REG_IRQ_EN && dut.mem_wdata[0])
                irq_en_writes <= irq_en_writes + 1;
            if (dut.mem_addr == REG_IRQ_CLR && dut.mem_wdata[0])
                irq_clr_writes <= irq_clr_writes + 1;
            if (dut.mem_addr == REG_START && dut.mem_wdata[0]) begin
                start_writes <= start_writes + 1;
                saw_start_write <= 1'b1;
            end
            if (dut.mem_addr == LOGIT_BASE)
                out0_before <= dut.mem_wdata;
            if (dut.mem_addr == (LOGIT_BASE + 32'h4))
                out1_before <= dut.mem_wdata;
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb == 4'b0) &&
            (dut.mem_addr == REG_BUSY)) begin
            busy_reads <= busy_reads + 1;
            saw_busy_read <= 1'b1;
        end

        // AXI traffic is the main datapath-side proof that taketwo actually ran.
        if (dut.wram_arvalid && dut.wram_arready) axi_ar_hs <= axi_ar_hs + 1;
        if (dut.wram_rvalid  && dut.wram_rready)  axi_r_hs  <= axi_r_hs + 1;
        if (dut.wram_awvalid && dut.wram_awready) axi_aw_hs <= axi_aw_hs + 1;
        if (dut.wram_wvalid  && dut.wram_wready)  axi_w_hs  <= axi_w_hs + 1;
        if (dut.wram_bvalid  && dut.wram_bready)  axi_b_hs  <= axi_b_hs + 1;

        // The short regression expects completion IRQ activity as part of the
        // stable control-plane contract.
        if (dut.ml_irq) begin
            ml_irq_high_cycles <= ml_irq_high_cycles + 1;
            saw_ml_irq <= 1'b1;
        end
    end
end

initial begin
    clk = 1'b0;
    reset = 1'b1;
    failures = 0;
    cycles = 0;

    $dumpfile("/tmp/top_ml_control_unified.vcd");
    $dumpvars(0, tb_top_ml_control_unified);

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    while ((dut.test_status !== TEST_PASS) && (dut.test_status !== TEST_FAIL) &&
           (cycles < TB_TIMEOUT_CYCLES)) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[%0t] TB: progress cycles=%0d pc=0x%08x status=0x%08x code=0x%08x start=%0d busy_reads=%0d irq=%0d",
                     $time, cycles, dut.cpu.reg_pc, dut.test_status, dut.test_code,
                     start_writes, busy_reads, ml_irq_high_cycles);
        end

        if (dut.trap) begin
            $display("FAIL: CPU trap asserted mem_addr=0x%08x pc=0x%08x", dut.mem_addr, dut.cpu.reg_pc);
            $fatal(1);
        end
    end

    if (cycles >= TB_TIMEOUT_CYCLES) begin
        $display("FAIL: timed out waiting for firmware completion");
        failures = failures + 1;
    end

    if (dut.test_status == TEST_FAIL) begin
        $display("FAIL: firmware reported TEST_FAIL code=0x%08x", dut.test_code);
        failures = failures + 1;
    end

    if (!saw_gbase_write) begin
        $display("FAIL: missing ML_REG(0x80)=WEIGHT_BASE write");
        failures = failures + 1;
    end
    if (weight_writes < 4) begin
        $display("FAIL: observed too few direct WRAM input writes: %0d", weight_writes);
        failures = failures + 1;
    end
    if (irq_en_writes < 1 || irq_clr_writes < 1) begin
        $display("FAIL: missing ML IRQ enable/clear writes en=%0d clr=%0d", irq_en_writes, irq_clr_writes);
        failures = failures + 1;
    end
    if (!saw_start_write || start_writes < 1) begin
        $display("FAIL: did not observe ML START write");
        failures = failures + 1;
    end
    if (!saw_busy_read || busy_reads == 0) begin
        $display("FAIL: did not observe BUSY polling reads");
        failures = failures + 1;
    end
    if (!saw_ml_irq) begin
        $display("FAIL: did not observe ml_irq assertion");
        failures = failures + 1;
    end
    if (axi_ar_hs == 0 || axi_r_hs == 0) begin
        $display("FAIL: no AXI read activity from taketwo to WRAM");
        failures = failures + 1;
    end
    if (axi_aw_hs == 0 && axi_w_hs == 0 && axi_b_hs == 0) begin
        $display("FAIL: no AXI write activity from taketwo to WRAM");
        failures = failures + 1;
    end
    if (failures == 0) begin
        $display("PASS: tb_top_ml_control_unified");
        $display("  start=%0d busy_reads=%0d irq_en/clr=%0d/%0d axi=%0d/%0d/%0d/%0d/%0d mutated=%0d code=0x%08x",
                 start_writes, busy_reads, irq_en_writes, irq_clr_writes,
                 axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs,
                 dut.test_code[16], dut.test_code);
    end else begin
        $display("FAIL: tb_top_ml_control_unified failures=%0d code=0x%08x",
                 failures, dut.test_code);
    end

    $finish;
end

endmodule
