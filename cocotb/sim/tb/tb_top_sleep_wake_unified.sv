`timescale 1ns/1ps

module tb_top_sleep_wake_unified;

// Dedicated unified-top sleep/wake regression.
// Repeated timer + ML + host-I2C wake verification.
// Each firmware iteration performs:
//   timer wake, then ML IRQ wake.
//   then host-I2C wake through the always-on host bridge.
// The bench checks that the same mechanisms stay coherent across multiple
// cycles rather than only the first one.

localparam [31:0] TIMER_BASE = 32'h0300_2000;
localparam [31:0] PWR_BASE   = 32'h0300_1000;
localparam [31:0] IRQC_BASE  = 32'h0300_5000;
localparam [31:0] TEST_BASE  = 32'h0300_F000;

localparam [31:0] T_CTRL        = TIMER_BASE + 32'h00;
localparam [31:0] T_RELOAD      = TIMER_BASE + 32'h04;
localparam [31:0] T_COUNT       = TIMER_BASE + 32'h08;
localparam [31:0] T_EVENT       = TIMER_BASE + 32'h0C;
localparam [31:0] P_CTRL        = PWR_BASE + 32'h00;
localparam [31:0] P_WAKE_STATUS = PWR_BASE + 32'h04;
localparam [31:0] P_WAKE_REASON = PWR_BASE + 32'h08;
localparam [31:0] IRQC_PENDING  = IRQC_BASE + 32'h00;
localparam [31:0] IRQC_MASK     = IRQC_BASE + 32'h04;
localparam [31:0] IRQC_WAKE_EN  = IRQC_BASE + 32'h08;
localparam [31:0] IRQC_CLAIM    = IRQC_BASE + 32'h14;
localparam [31:0] IRQC_COMPLETE = IRQC_BASE + 32'h18;
localparam [31:0] TEST_STATUS   = TEST_BASE + 32'h00;
localparam [31:0] TEST_CODE     = TEST_BASE + 32'h04;
localparam [31:0] ML_BASE       = 32'h0300_3000;
localparam [31:0] REG_START     = ML_BASE + 32'h10;
localparam [31:0] REG_IRQ_CLR   = ML_BASE + 32'h2C;

localparam [31:0] TEST_PASS     = 32'hCAFEBABE;
localparam [31:0] TEST_FAIL     = 32'hDEADBEEF;
localparam [31:0] IRQ_TIMER_BIT = 32'h0000_0001;
localparam [31:0] IRQ_ML_BIT    = 32'h0000_0002;
localparam [31:0] IRQ_HOST_BIT  = 32'h0000_0004;
localparam integer EXPECTED_ITERS = 2;

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

wire        spi_clk;
wire        spi_mosi;
wire        spi_cs_n;
wire        host_i2c_scl;
tri1        host_i2c_sda;
reg         scl_drv;
reg         sda_drv_low;

localparam [6:0] ACC_ADDR = 7'h19;
localparam [6:0] PPG_ADDR = 7'h64;

wire feat_valid;
wire signed [15:0] time_feat;
wire signed [15:0] motion_feat;
wire signed [15:0] delta_hr_feat;
wire signed [15:0] mssd_feat;
wire ml_update_gate;
wire [7:0] invalid_reason;
wire epoch_end;
wire alarm;

// Bench summary counters. These are intentionally phase-oriented so a failing
// run can quickly answer "did timer wake happen?", "did ML pending rise?",
// and "did firmware actually service the IRQ path?".
integer failures;
integer cycles;
integer sleep_edges;
integer wake_edges;
integer sleep_writes;
integer wake_status_clears;
integer irq_pending_clears;
integer timer_event_clears;
integer irqc_wake_en_writes;
integer timer_event_rises;
integer ml_sleep_edges;
integer ml_wake_edges;
integer ml_pending_rises;
integer host_sleep_edges;
integer host_wake_edges;
integer host_pending_rises;
integer host_event_pulses;
integer irq_claim_reads;
integer irq_complete_writes;
integer ml_irq_clr_writes;
integer ml_start_writes;
reg prev_cpu_clk_en;
reg prev_timer_event;
reg prev_timer_pending;
reg prev_ml_pending;
reg prev_host_pending;
reg saw_timer_reason_bit;
reg saw_ml_reason_bit;
reg saw_host_reason_bit;
reg issued_host_kick;

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
    .FIRMWARE_HEX("firmware/build/test_top_sleep_wake_unified/firmware.hex"),
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
    .i2c_sda_i(host_i2c_sda),
    .i2c_sda_drive_low_o(),
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
    .spi_clk_o(spi_clk),
    .spi_mosi_o(spi_mosi),
    .spi_miso_i(1'b1),
    .spi_cs_n_o(spi_cs_n),
    .boot_spi_clk_o(),
    .boot_spi_mosi_o(),
    .boot_spi_miso_i(1'b1),
    .boot_spi_cs_n_o(),
    .feat_valid_o(feat_valid),
    .time_feat_o(time_feat),
    .motion_feat_o(motion_feat),
    .delta_hr_feat_o(delta_hr_feat),
    .mssd_feat_o(mssd_feat),
    .ml_update_gate_o(ml_update_gate),
    .invalid_reason_o(invalid_reason),
    .epoch_end_o(epoch_end),
    .alarm_o(alarm),
    .test_force_irq_i(1'b0),
    .test_force_wake_i(1'b0),
    .test_irq_src_i(3'b000),
    .irq_eoi_o(),
    .boot_done_o()
);

assign host_i2c_scl = scl_drv;
assign host_i2c_sda = sda_drv_low ? 1'b0 : 1'bz;

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

task i2c_tick;
begin
    #120;
end
endtask

task i2c_start;
begin
    sda_drv_low = 1'b0;
    scl_drv     = 1'b1;
    i2c_tick();
    sda_drv_low = 1'b1;
    i2c_tick();
    scl_drv     = 1'b0;
    i2c_tick();
end
endtask

task i2c_stop;
begin
    sda_drv_low = 1'b1;
    scl_drv     = 1'b0;
    i2c_tick();
    scl_drv     = 1'b1;
    i2c_tick();
    sda_drv_low = 1'b0;
    i2c_tick();
end
endtask

task i2c_write_bit;
    input bitval;
begin
    scl_drv     = 1'b0;
    sda_drv_low = bitval ? 1'b0 : 1'b1;
    i2c_tick();
    scl_drv     = 1'b1;
    i2c_tick();
    scl_drv     = 1'b0;
    i2c_tick();
end
endtask

task i2c_read_bit;
    output bitval;
begin
    scl_drv     = 1'b0;
    sda_drv_low = 1'b0;
    i2c_tick();
    scl_drv     = 1'b1;
    i2c_tick();
    bitval      = host_i2c_sda;
    scl_drv     = 1'b0;
    i2c_tick();
end
endtask

task i2c_write_byte;
    input [7:0] byte_in;
    output ack;
    integer i;
    reg bitv;
begin
    for (i = 7; i >= 0; i = i - 1) i2c_write_bit(byte_in[i]);
    i2c_read_bit(bitv);
    ack = ~bitv;
end
endtask

task i2c_write_reg;
    input [7:0] reg_addr;
    input [7:0] reg_data;
    reg ack;
begin
    i2c_start();
    i2c_write_byte(8'h84, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host write address");
        failures = failures + 1;
    end
    i2c_write_byte(reg_addr, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host register pointer");
        failures = failures + 1;
    end
    i2c_write_byte(reg_data, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host register data");
        failures = failures + 1;
    end
    i2c_stop();
end
endtask

always @(posedge clk) begin
    if (reset) begin
        scl_drv <= 1'b1;
        sda_drv_low <= 1'b0;
        sleep_edges <= 0;
        wake_edges <= 0;
        sleep_writes <= 0;
        wake_status_clears <= 0;
        irq_pending_clears <= 0;
        timer_event_clears <= 0;
        irqc_wake_en_writes <= 0;
        timer_event_rises <= 0;
        ml_sleep_edges <= 0;
        ml_wake_edges <= 0;
        ml_pending_rises <= 0;
        host_sleep_edges <= 0;
        host_wake_edges <= 0;
        host_pending_rises <= 0;
        host_event_pulses <= 0;
        irq_claim_reads <= 0;
        irq_complete_writes <= 0;
        ml_irq_clr_writes <= 0;
        ml_start_writes <= 0;
        prev_cpu_clk_en <= 1'b1;
        prev_timer_event <= 1'b0;
        prev_timer_pending <= 1'b0;
        prev_ml_pending <= 1'b0;
        prev_host_pending <= 1'b0;
        saw_timer_reason_bit <= 1'b0;
        saw_ml_reason_bit <= 1'b0;
        saw_host_reason_bit <= 1'b0;
        issued_host_kick <= 1'b0;
    end else begin
        // Count the specific MMIO accesses that prove firmware is exercising
        // the intended power-control and IRQ-controller contract.
        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0)) begin
            if ((dut.mem_addr == P_CTRL) && dut.mem_wdata[0])
                sleep_writes <= sleep_writes + 1;
            if ((dut.mem_addr == P_WAKE_STATUS) && (dut.mem_wdata & IRQ_TIMER_BIT))
                wake_status_clears <= wake_status_clears + 1;
            if ((dut.mem_addr == IRQC_PENDING) && (dut.mem_wdata & IRQ_TIMER_BIT))
                irq_pending_clears <= irq_pending_clears + 1;
            if ((dut.mem_addr == T_EVENT) && dut.mem_wdata[0])
                timer_event_clears <= timer_event_clears + 1;
            if ((dut.mem_addr == IRQC_WAKE_EN) && (dut.mem_wdata & IRQ_TIMER_BIT))
                irqc_wake_en_writes <= irqc_wake_en_writes + 1;
            if (dut.mem_addr == IRQC_COMPLETE)
                irq_complete_writes <= irq_complete_writes + 1;
            if ((dut.mem_addr == REG_IRQ_CLR) && dut.mem_wdata[0])
                ml_irq_clr_writes <= ml_irq_clr_writes + 1;
            if ((dut.mem_addr == REG_START) && dut.mem_wdata[0])
                ml_start_writes <= ml_start_writes + 1;
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb == 4'b0)) begin
            if (dut.mem_addr == IRQC_CLAIM)
                irq_claim_reads <= irq_claim_reads + 1;
        end

        // Track wake bookkeeping after it settles, rather than trusting only
        // the exact edge cycle, because wake_reason can lag the wake edge by
        // one cycle depending on snapshot timing.
        if (!prev_timer_event && dut.timer_event)
            timer_event_rises <= timer_event_rises + 1;

        if (dut.u_pwr.wake_reason[0] || dut.u_pwr.wake_status[0])
            saw_timer_reason_bit <= 1'b1;
        if (dut.u_pwr.wake_reason[1] || dut.u_pwr.wake_status[1])
            saw_ml_reason_bit <= 1'b1;
        if (dut.u_pwr.wake_reason[2] || dut.u_pwr.wake_status[2])
            saw_host_reason_bit <= 1'b1;
        if (dut.host_i2c_irq_event)
            host_event_pulses <= host_event_pulses + 1;

        if (prev_cpu_clk_en && !dut.cpu_clk_en) begin
            sleep_edges <= sleep_edges + 1;
            $display("[%0t] TB: CPU -> SLEEP (%0d) pc=0x%08x sleep_req=%0b wake_status=0x%08x",
                     $time, sleep_edges + 1, dut.cpu.reg_pc, dut.sleep_req, dut.u_pwr.wake_status);
            if (dut.sleep_req && dut.u_irqc.wake_en[2]) begin
                host_sleep_edges <= host_sleep_edges + 1;
                issued_host_kick <= 1'b0;
            end
        end

        if (!prev_cpu_clk_en && dut.cpu_clk_en) begin
            wake_edges <= wake_edges + 1;
            $display("[%0t] TB: CPU -> WAKE (%0d) pc=0x%08x wake_reason=0x%08x pending=0x%08x",
                     $time, wake_edges + 1, dut.cpu.reg_pc, dut.u_pwr.wake_reason, dut.u_irqc.pending);
            if (dut.u_pwr.wake_status[1] || dut.u_pwr.wake_reason[1] || dut.u_irqc.pending[1])
                ml_wake_edges <= ml_wake_edges + 1;
            if (dut.u_pwr.wake_status[2] || dut.u_pwr.wake_reason[2] || dut.u_irqc.pending[2])
                host_wake_edges <= host_wake_edges + 1;
        end

        if (!prev_timer_pending && dut.u_irqc.pending[0]) begin
            $display("[%0t] TB: timer pending rise wake_status=0x%08x wake_reason=0x%08x",
                     $time, dut.u_pwr.wake_status, dut.u_pwr.wake_reason);
        end
        if (!prev_ml_pending && dut.u_irqc.pending[1]) begin
            ml_pending_rises <= ml_pending_rises + 1;
            $display("[%0t] TB: ML pending rise wake_status=0x%08x wake_reason=0x%08x active=0x%08x claim=0x%08x",
                     $time, dut.u_pwr.wake_status, dut.u_pwr.wake_reason, dut.u_irqc.active, dut.u_irqc.claim_id);
        end
        if (!prev_host_pending && dut.u_irqc.pending[2]) begin
            host_pending_rises <= host_pending_rises + 1;
            $display("[%0t] TB: HOST pending rise wake_status=0x%08x wake_reason=0x%08x",
                     $time, dut.u_pwr.wake_status, dut.u_pwr.wake_reason);
        end
        if (prev_cpu_clk_en && !dut.cpu_clk_en && dut.sleep_req && dut.u_irqc.wake_en[1])
            ml_sleep_edges <= ml_sleep_edges + 1;

        prev_cpu_clk_en <= dut.cpu_clk_en;
        prev_timer_event <= dut.timer_event;
        prev_timer_pending <= dut.u_irqc.pending[0];
        prev_ml_pending <= dut.u_irqc.pending[1];
        prev_host_pending <= dut.u_irqc.pending[2];
    end
end

initial begin
    clk = 1'b0;
    reset = 1'b1;
    scl_drv = 1'b1;
    sda_drv_low = 1'b0;
    failures = 0;
    cycles = 0;

    $dumpfile("/tmp/top_sleep_wake_unified.vcd");
    $dumpvars(0, tb_top_sleep_wake_unified);

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    // Wait for firmware to report PASS/FAIL through test_mmio, while also
    // printing periodic progress snapshots if the run is taking a while.
    while ((dut.test_status !== TEST_PASS) && (dut.test_status !== TEST_FAIL) &&
           (cycles < TB_TIMEOUT_CYCLES)) begin
        @(posedge clk);
        cycles = cycles + 1;
        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[%0t] TB: progress cycles=%0d pc=0x%08x cpu_clk_en=%0b sleeping=%0b sleep_req=%0b wake_status=0x%08x wake_reason=0x%08x pending=0x%08x",
                     $time, cycles, dut.cpu.reg_pc, dut.cpu_clk_en, dut.sleeping_r, dut.sleep_req,
                     dut.u_pwr.wake_status, dut.u_pwr.wake_reason, dut.u_irqc.pending);
        end

        if (!reset && dut.cpu_clk_en == 1'b0 && dut.sleep_req && dut.u_irqc.wake_en[2] && !issued_host_kick) begin
            issued_host_kick = 1'b1;
            i2c_write_reg(8'h04, 8'h01);
            $display("[%0t] TB: issued host-I2C wake kick while CPU asleep", $time);
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

    if (sleep_edges < (2 * EXPECTED_ITERS)) begin
        $display("FAIL: observed too few CPU sleep edges: %0d", sleep_edges);
        failures = failures + 1;
    end
    if (wake_edges < (2 * EXPECTED_ITERS)) begin
        $display("FAIL: observed too few CPU wake edges: %0d", wake_edges);
        failures = failures + 1;
    end
    if (sleep_writes < (2 * EXPECTED_ITERS)) begin
        $display("FAIL: observed too few P_CTRL sleep writes: %0d", sleep_writes);
        failures = failures + 1;
    end
    if (irqc_wake_en_writes < EXPECTED_ITERS) begin
        $display("FAIL: observed too few timer IRQC_WAKE_EN writes: %0d", irqc_wake_en_writes);
        failures = failures + 1;
    end
    if (timer_event_rises < EXPECTED_ITERS) begin
        $display("FAIL: observed too few timer_event rises: %0d", timer_event_rises);
        failures = failures + 1;
    end
    if (!saw_timer_reason_bit) begin
        $display("FAIL: never observed timer bit in wake_reason/wake_status");
        failures = failures + 1;
    end
    if (wake_status_clears < EXPECTED_ITERS) begin
        $display("FAIL: observed too few timer wake_status clears: %0d", wake_status_clears);
        failures = failures + 1;
    end
    if (irq_pending_clears < EXPECTED_ITERS) begin
        $display("FAIL: observed too few timer pending clears: %0d", irq_pending_clears);
        failures = failures + 1;
    end
    if (timer_event_clears < EXPECTED_ITERS) begin
        $display("FAIL: observed too few timer event clears: %0d", timer_event_clears);
        failures = failures + 1;
    end
    if (ml_sleep_edges < EXPECTED_ITERS) begin
        $display("FAIL: observed too few ML-armed sleep edges: %0d", ml_sleep_edges);
        failures = failures + 1;
    end
    if (ml_wake_edges < EXPECTED_ITERS) begin
        $display("FAIL: observed too few ML-attributed wake edges: %0d", ml_wake_edges);
        failures = failures + 1;
    end
    if (ml_pending_rises < EXPECTED_ITERS) begin
        $display("FAIL: observed too few ML pending rises: %0d", ml_pending_rises);
        failures = failures + 1;
    end
    if (host_sleep_edges < EXPECTED_ITERS) begin
        $display("FAIL: observed too few host-armed sleep edges: %0d", host_sleep_edges);
        failures = failures + 1;
    end
    if (host_wake_edges < EXPECTED_ITERS) begin
        $display("FAIL: observed too few host-attributed wake edges: %0d", host_wake_edges);
        failures = failures + 1;
    end
    if (host_pending_rises < EXPECTED_ITERS) begin
        $display("FAIL: observed too few host pending rises: %0d", host_pending_rises);
        failures = failures + 1;
    end
    if (host_event_pulses < EXPECTED_ITERS) begin
        $display("FAIL: observed too few host_i2c_irq_event pulses: %0d", host_event_pulses);
        failures = failures + 1;
    end
    if (irq_claim_reads < EXPECTED_ITERS) begin
        $display("FAIL: observed too few IRQC_CLAIM reads: %0d", irq_claim_reads);
        failures = failures + 1;
    end
    if (irq_complete_writes < EXPECTED_ITERS) begin
        $display("FAIL: observed too few IRQC_COMPLETE writes: %0d", irq_complete_writes);
        failures = failures + 1;
    end
    if (ml_irq_clr_writes < EXPECTED_ITERS) begin
        $display("FAIL: observed too few ML IRQ clear writes: %0d", ml_irq_clr_writes);
        failures = failures + 1;
    end
    if (ml_start_writes < EXPECTED_ITERS) begin
        $display("FAIL: observed too few ML start writes: %0d", ml_start_writes);
        failures = failures + 1;
    end
    if (!saw_ml_reason_bit) begin
        $display("FAIL: never observed ML bit in wake_reason/wake_status");
        failures = failures + 1;
    end
    if (!saw_host_reason_bit) begin
        $display("FAIL: never observed HOST bit in wake_reason/wake_status");
        failures = failures + 1;
    end
    if (dut.u_irqc.pending[0]) begin
        $display("FAIL: timer pending bit still set at end of test");
        failures = failures + 1;
    end
    if (dut.u_pwr.wake_status[0]) begin
        $display("FAIL: pwr wake_status timer bit still set at end of test");
        failures = failures + 1;
    end
    if (dut.u_irqc.pending[1]) begin
        $display("FAIL: ML pending bit still set at end of test");
        failures = failures + 1;
    end
    if (dut.u_irqc.pending[2]) begin
        $display("FAIL: HOST pending bit still set at end of test");
        failures = failures + 1;
    end
    if (dut.u_pwr.wake_status[1]) begin
        $display("FAIL: pwr wake_status ML bit still set at end of test");
        failures = failures + 1;
    end
    if (dut.u_pwr.wake_status[2]) begin
        $display("FAIL: pwr wake_status HOST bit still set at end of test");
        failures = failures + 1;
    end

    if (failures == 0) begin
        $display("PASS: tb_top_sleep_wake_unified sleep_edges=%0d wake_edges=%0d timer_event_rises=%0d ml=%0d/%0d/%0d host=%0d/%0d/%0d evt=%0d claims=%0d/%0d mlclr=%0d code=0x%08x",
                 sleep_edges, wake_edges, timer_event_rises,
                 ml_sleep_edges, ml_wake_edges, ml_pending_rises,
                 host_sleep_edges, host_wake_edges, host_pending_rises, host_event_pulses,
                 irq_claim_reads, irq_complete_writes, ml_irq_clr_writes,
                 dut.test_code);
    end else begin
        $display("FAIL: tb_top_sleep_wake_unified failures=%0d code=0x%08x",
                 failures, dut.test_code);
    end

    $finish;
end

endmodule
