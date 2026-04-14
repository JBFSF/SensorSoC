`timescale 1ns/1ps

module tb_top_spi_init_unified;

// Short unified-top SPI initialization regression.
// The goal is to isolate the flash boot-copy plumbing:
//   CPU firmware -> spi_master_mmio -> spi_flash_model -> weight_ram_axi
// without waiting on the sensor feature path or ML execution.

localparam [31:0] SPI_BASE    = 32'h0300_A000;
localparam [31:0] WEIGHT_BASE = 32'h0300_6000;
localparam [31:0] TEST_BASE   = 32'h0300_F000;

localparam [31:0] SPI_CS_ADDR      = SPI_BASE + 32'h00;
localparam [31:0] SPI_STATUS_ADDR  = SPI_BASE + 32'h04;
localparam [31:0] SPI_DATA_ADDR    = SPI_BASE + 32'h08;
localparam [31:0] SPI_DIV_ADDR     = SPI_BASE + 32'h0C;
localparam [31:0] TEST_STATUS_ADDR = TEST_BASE + 32'h00;
localparam [31:0] TEST_CODE_ADDR   = TEST_BASE + 32'h04;

localparam [31:0] TEST_PASS = 32'hCAFEBABE;
localparam [31:0] TEST_FAIL = 32'hDEADBEEF;

localparam integer FLASH_WORDS = 208;
localparam integer BOOT_WORDS = 8;
localparam [31:0] BOOT_BASE = 32'd128;
localparam integer BOOT_INDEX = BOOT_BASE >> 2;
localparam integer MIN_SPI_BITS = 8 * (4 + BOOT_WORDS * 4);
localparam integer TB_TIMEOUT_CYCLES = 300000;
localparam integer TB_PROGRESS_EVERY = 50000;

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
wire        spi_miso;
wire        spi_cs_n;
wire        host_i2c_scl;
tri1        host_i2c_sda;

localparam [6:0] ACC_ADDR = 7'h19;
localparam [6:0] PPG_ADDR = 7'h64;

integer failures;
integer cycles;
integer spi_cs_asserts;
integer spi_bit_count;
integer spi_data_writes;
integer spi_status_reads;
integer spi_div_writes;
integer wram_boot_writes;
reg prev_spi_cs_n;
reg prev_spi_clk;

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
    .FIRMWARE_HEX("firmware/build/test_top_spi_init_unified/firmware.hex"),
    .WEIGHT_INIT_HEX(""),
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
    .COS_PERIOD_SECONDS(32'd16),
    .COS_LUT_BITS(3'd6),
    .COS_SCALE_Q15(16'h7FFF),
    .RMSSD_MIN_RR_COUNT(1)
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
    .spi_miso_i(spi_miso),
    .spi_cs_n_o(spi_cs_n),
    .feat_valid_o(),
    .time_feat_o(),
    .motion_feat_o(),
    .delta_hr_feat_o(),
    .rmssd_feat_o(),
    .ml_update_gate_o(),
    .invalid_reason_o(),
    .epoch_end_o(),
    .alarm_o(),
    .test_force_irq_i(1'b0),
    .test_force_wake_i(1'b0)
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

spi_flash_model #(
    .FLASH_WORDS(FLASH_WORDS),
    .FLASH_INIT_HEX("firmware/build/generated/taketwo_params.hex")
) u_flash (
    .spi_clk(spi_clk),
    .spi_cs_n(spi_cs_n),
    .spi_mosi(spi_mosi),
    .spi_miso(spi_miso)
);

always #10 clk = ~clk;

always @(posedge clk) begin
    if (reset) begin
        spi_cs_asserts <= 0;
        spi_bit_count <= 0;
        spi_data_writes <= 0;
        spi_status_reads <= 0;
        spi_div_writes <= 0;
        wram_boot_writes <= 0;
        prev_spi_cs_n <= 1'b1;
        prev_spi_clk <= 1'b0;
    end else begin
        if (prev_spi_cs_n && !spi_cs_n)
            spi_cs_asserts <= spi_cs_asserts + 1;
        prev_spi_cs_n <= spi_cs_n;

        if (!prev_spi_clk && spi_clk && !spi_cs_n)
            spi_bit_count <= spi_bit_count + 1;
        prev_spi_clk <= spi_clk;

        if (dut.mmio_sel && dut.mem_valid) begin
            if (dut.mem_addr == SPI_STATUS_ADDR && (dut.mem_wstrb == 4'b0))
                spi_status_reads <= spi_status_reads + 1;
            if ((dut.mem_addr == SPI_DIV_ADDR) && (dut.mem_wstrb != 4'b0))
                spi_div_writes <= spi_div_writes + 1;
            if ((dut.mem_addr == SPI_DATA_ADDR) && (dut.mem_wstrb != 4'b0))
                spi_data_writes <= spi_data_writes + 1;
            if ((dut.mem_addr >= (WEIGHT_BASE + BOOT_BASE)) &&
                (dut.mem_addr <  (WEIGHT_BASE + BOOT_BASE + (BOOT_WORDS * 4))) &&
                (dut.mem_wstrb != 4'b0))
                wram_boot_writes <= wram_boot_writes + 1;
        end
    end
end

initial begin : run_test
    integer i;
    reg [31:0] expected_word;

    clk = 1'b0;
    reset = 1'b1;
    failures = 0;
    cycles = 0;

    $dumpfile("/tmp/top_spi_init_unified.vcd");
    $dumpvars(0, tb_top_spi_init_unified);

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    while ((dut.test_status !== TEST_PASS) && (dut.test_status !== TEST_FAIL) &&
           (cycles < TB_TIMEOUT_CYCLES)) begin
        @(posedge clk);
        cycles = cycles + 1;
        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[%0t] TB: progress cycles=%0d pc=0x%08x spi_cs_n=%0b bit_count=%0d status=0x%08x code=0x%08x",
                     $time, cycles, dut.cpu.reg_pc, spi_cs_n, spi_bit_count,
                     dut.test_status, dut.test_code);
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

    if (spi_div_writes < 1) begin
        $display("FAIL: observed no SPI divider write");
        failures = failures + 1;
    end
    if (spi_cs_asserts < 1) begin
        $display("FAIL: observed no SPI CS assertion");
        failures = failures + 1;
    end
    if (spi_data_writes < (4 + (BOOT_WORDS * 4))) begin
        $display("FAIL: observed too few SPI data writes: %0d", spi_data_writes);
        failures = failures + 1;
    end
    if (spi_status_reads < BOOT_WORDS) begin
        $display("FAIL: observed too few SPI status reads: %0d", spi_status_reads);
        failures = failures + 1;
    end
    if (spi_bit_count < MIN_SPI_BITS) begin
        $display("FAIL: observed too few SPI clock bits: %0d", spi_bit_count);
        failures = failures + 1;
    end
    if (wram_boot_writes < BOOT_WORDS) begin
        $display("FAIL: observed too few WRAM boot writes: %0d", wram_boot_writes);
        failures = failures + 1;
    end

    for (i = 0; i < BOOT_WORDS; i = i + 1) begin
        expected_word = u_flash.mem[i];
        if (dut.u_weight_ram.mem[BOOT_INDEX + i] !== expected_word) begin
            $display("FAIL: WRAM boot word %0d mismatch got=0x%08x exp=0x%08x",
                     i, dut.u_weight_ram.mem[BOOT_INDEX + i], expected_word);
            failures = failures + 1;
        end
    end

    if (failures == 0) begin
        $display("PASS: tb_top_spi_init_unified cs=%0d bits=%0d data=%0d status_reads=%0d wram_writes=%0d code=0x%08x",
                 spi_cs_asserts, spi_bit_count, spi_data_writes,
                 spi_status_reads, wram_boot_writes, dut.test_code);
    end else begin
        $display("FAIL: tb_top_spi_init_unified failures=%0d code=0x%08x",
                 failures, dut.test_code);
    end

    $finish;
end

endmodule
