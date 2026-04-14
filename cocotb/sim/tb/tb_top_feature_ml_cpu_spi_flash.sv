`timescale 1ns/1ps

module tb_top_feature_ml_cpu_spi_flash;

localparam [31:0] FEATURE_BASE = 32'h0300_4000;
localparam [31:0] WEIGHT_BASE  = 32'h0300_6000;
localparam [31:0] ML_BASE      = 32'h0300_3000;
localparam [31:0] REG_START    = ML_BASE + 32'h10;
localparam [31:0] REG_BUSY     = ML_BASE + 32'h14;
localparam [31:0] REG_GBASE    = ML_BASE + 32'h80;
localparam [31:0] X_BASE       = WEIGHT_BASE + 32'd64;
localparam [31:0] VAR_BASE     = WEIGHT_BASE + 32'd128;
localparam [31:0] LOGIT_BASE   = WEIGHT_BASE + 32'd5504;

localparam [31:0] FEAT_STATUS  = FEATURE_BASE + 32'h00;
localparam [31:0] FEAT_TIME    = FEATURE_BASE + 32'h04;
localparam [31:0] FEAT_MOTION  = FEATURE_BASE + 32'h08;
localparam [31:0] FEAT_DHR     = FEATURE_BASE + 32'h0C;
localparam [31:0] FEAT_RMSSD   = FEATURE_BASE + 32'h10;

localparam int unsigned FLASH_WORDS = 208;
localparam int unsigned TB_TIMEOUT_CYCLES = 10_000_000;
localparam int unsigned TB_PROGRESS_EVERY = 1_000_000;
localparam int unsigned MIN_SPI_BITS = 8 * (4 + FLASH_WORDS * 4);

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
integer feature_status_reads;
integer feature_time_reads;
integer feature_motion_reads;
integer feature_dhr_reads;
integer feature_rmssd_reads;
integer feature_clear_writes;
integer weight_feature_writes;
integer busy_reads;
integer axi_ar_hs;
integer axi_r_hs;
integer axi_aw_hs;
integer axi_w_hs;
integer axi_b_hs;
integer spi_cs_asserts;
integer spi_bit_count;
integer boot_writes_seen;
reg saw_feature_latch;
reg signed [15:0] first_time_feat;
reg signed [15:0] first_motion_feat;
reg signed [15:0] first_delta_hr_feat;
reg signed [15:0] first_rmssd_feat;
reg saw_global_base_write;
reg saw_start_write;
reg saw_busy_read;
reg prev_spi_cs_n;
reg prev_spi_clk;
reg [31:0] boot_word0;
reg [31:0] boot_word1;
reg [31:0] boot_word2;
reg [31:0] boot_word3;

reg [31:0] expected_conf;
reg expected_class;
reg [31:0] raw_logit_word;
reg [31:0] sampled_logit_word;
reg signed [15:0] log0_s;
reg signed [15:0] log1_s;
reg signed [15:0] diff_s;
reg [31:0] feature_word0_snap;
reg [31:0] feature_word1_snap;
reg saw_feature_word0_snap;
reg saw_feature_word1_snap;

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
    .FIRMWARE_HEX("firmware/build/test_top_feature_ml_cpu_spi_flash/firmware.hex"),
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
    .feat_valid_o(),
    .time_feat_o(),
    .motion_feat_o(),
    .delta_hr_feat_o(),
    .rmssd_feat_o(),
    .ml_update_gate_o(),
    .invalid_reason_o(),
    .spi_clk_o(spi_clk),
    .spi_mosi_o(spi_mosi),
    .spi_miso_i(spi_miso),
    .spi_cs_n_o(spi_cs_n),
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
        feature_status_reads <= 0;
        feature_time_reads <= 0;
        feature_motion_reads <= 0;
        feature_dhr_reads <= 0;
        feature_rmssd_reads <= 0;
        feature_clear_writes <= 0;
        weight_feature_writes <= 0;
        busy_reads <= 0;
        axi_ar_hs <= 0;
        axi_r_hs <= 0;
        axi_aw_hs <= 0;
        axi_w_hs <= 0;
        axi_b_hs <= 0;
        spi_cs_asserts <= 0;
        spi_bit_count <= 0;
        boot_writes_seen <= 0;
        saw_feature_latch <= 1'b0;
        first_time_feat <= '0;
        first_motion_feat <= '0;
        first_delta_hr_feat <= '0;
        first_rmssd_feat <= '0;
        saw_global_base_write <= 1'b0;
        saw_start_write <= 1'b0;
        saw_busy_read <= 1'b0;
        prev_spi_cs_n <= 1'b1;
        prev_spi_clk <= 1'b0;
        boot_word0 <= 32'h0;
        boot_word1 <= 32'h0;
        boot_word2 <= 32'h0;
        boot_word3 <= 32'h0;
        sampled_logit_word <= 32'h0;
        feature_word0_snap <= 32'h0;
        feature_word1_snap <= 32'h0;
        saw_feature_word0_snap <= 1'b0;
        saw_feature_word1_snap <= 1'b0;
    end else begin
        if (prev_spi_cs_n && !spi_cs_n)
            spi_cs_asserts <= spi_cs_asserts + 1;
        prev_spi_cs_n <= spi_cs_n;
        if (!prev_spi_clk && spi_clk && !spi_cs_n)
            spi_bit_count <= spi_bit_count + 1;
        prev_spi_clk <= spi_clk;

        if (!saw_feature_latch && dut.feat_latched_valid_r)
            saw_feature_latch <= 1'b1;

        // Capture feature values at the moment the firmware clears the valid bit,
        // which is after the firmware has read all features, so these match what
        // the firmware wrote into WRAM.
        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0) &&
            (dut.mem_addr == FEAT_STATUS) && dut.mem_wdata[0]) begin
            first_time_feat <= dut.feat_time_latched_r;
            first_motion_feat <= dut.feat_motion_latched_r;
            first_delta_hr_feat <= dut.feat_delta_hr_latched_r;
            first_rmssd_feat <= dut.feat_rmssd_latched_r;
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb == 4'b0)) begin
            case (dut.mem_addr)
                FEAT_STATUS: feature_status_reads <= feature_status_reads + 1;
                FEAT_TIME:   feature_time_reads   <= feature_time_reads + 1;
                FEAT_MOTION: feature_motion_reads <= feature_motion_reads + 1;
                FEAT_DHR:    feature_dhr_reads    <= feature_dhr_reads + 1;
                FEAT_RMSSD:  feature_rmssd_reads  <= feature_rmssd_reads + 1;
                REG_BUSY: begin
                    busy_reads <= busy_reads + 1;
                    saw_busy_read <= 1'b1;
                end
            endcase
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0)) begin
            if ((dut.mem_addr >= VAR_BASE) && (dut.mem_addr < VAR_BASE + 32'h10) && (boot_writes_seen < 4)) begin
                case (dut.mem_addr - VAR_BASE)
                    32'h00: boot_word0 <= dut.mem_wdata;
                    32'h04: boot_word1 <= dut.mem_wdata;
                    32'h08: boot_word2 <= dut.mem_wdata;
                    32'h0C: boot_word3 <= dut.mem_wdata;
                    default: ;
                endcase
                boot_writes_seen <= boot_writes_seen + 1;
            end
            if ((dut.mem_addr >= X_BASE) && (dut.mem_addr < X_BASE + 32'h8))
                weight_feature_writes <= weight_feature_writes + 1;
            if (dut.mem_addr == X_BASE) begin
                if (dut.mem_wstrb[0]) feature_word0_snap[7:0]   <= dut.mem_wdata[7:0];
                if (dut.mem_wstrb[1]) feature_word0_snap[15:8]  <= dut.mem_wdata[15:8];
                if (dut.mem_wstrb[2]) feature_word0_snap[23:16] <= dut.mem_wdata[23:16];
                if (dut.mem_wstrb[3]) feature_word0_snap[31:24] <= dut.mem_wdata[31:24];
                saw_feature_word0_snap <= 1'b1;
            end
            if (dut.mem_addr == (X_BASE + 32'h4)) begin
                if (dut.mem_wstrb[0]) feature_word1_snap[7:0]   <= dut.mem_wdata[7:0];
                if (dut.mem_wstrb[1]) feature_word1_snap[15:8]  <= dut.mem_wdata[15:8];
                if (dut.mem_wstrb[2]) feature_word1_snap[23:16] <= dut.mem_wdata[23:16];
                if (dut.mem_wstrb[3]) feature_word1_snap[31:24] <= dut.mem_wdata[31:24];
                saw_feature_word1_snap <= 1'b1;
            end
            if ((dut.mem_addr == FEAT_STATUS) && dut.mem_wdata[0])
                feature_clear_writes <= feature_clear_writes + 1;
            if (dut.mem_addr == REG_GBASE && dut.mem_wdata == WEIGHT_BASE)
                saw_global_base_write <= 1'b1;
            if (dut.mem_addr == REG_START && dut.mem_wdata[0])
                saw_start_write <= 1'b1;
        end

        if (dut.wram_arvalid && dut.wram_arready) axi_ar_hs <= axi_ar_hs + 1;
        if (dut.wram_rvalid  && dut.wram_rready)  axi_r_hs  <= axi_r_hs + 1;
        if (dut.wram_awvalid && dut.wram_awready) axi_aw_hs <= axi_aw_hs + 1;
        if (dut.wram_wvalid  && dut.wram_wready)  axi_w_hs  <= axi_w_hs + 1;
        if (dut.wram_bvalid  && dut.wram_bready)  axi_b_hs  <= axi_b_hs + 1;
    end
end

initial begin
    clk = 1'b0;
    reset = 1'b1;
    failures = 0;
    cycles = 0;
    expected_conf = 32'h0;
    expected_class = 1'b0;

    $display("[TB] start FW=firmware/build/test_top_feature_ml_cpu_spi_flash/firmware.hex FLASH=firmware/build/generated/taketwo_params.hex");

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    while (cycles < TB_TIMEOUT_CYCLES) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[cyc %0d] status=0x%08x code=0x%08x score=0x%08x feature_reads=%0d/%0d/%0d/%0d/%0d spi_cs=%0d spi_bits=%0d axi=%0d/%0d/%0d/%0d/%0d",
                     cycles, dut.test_status, dut.test_code, dut.ml_score_hw,
                     feature_status_reads, feature_time_reads, feature_motion_reads,
                     feature_dhr_reads, feature_rmssd_reads,
                     spi_cs_asserts, spi_bit_count,
                     axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
        end

        if (dut.trap) begin
            $display("FAIL: CPU trap asserted mem_addr=0x%08x pc=0x%08x", dut.mem_addr, dut.cpu.reg_pc);
            $fatal(1);
        end

        if (dut.test_status == 32'hDEAD_BEEF) begin
            $display("FAIL: firmware reported FAIL code=0x%08x", dut.test_code);
            $display("  spi_cs=%0d spi_bits=%0d boot_writes=%0d captured=%08x %08x %08x %08x wram[0..3]=%08x %08x %08x %08x flash[0..3]=%08x %08x %08x %08x out=%08x %08x",
                     spi_cs_asserts, spi_bit_count, boot_writes_seen,
                     boot_word0, boot_word1, boot_word2, boot_word3,
                     dut.u_weight_ram.mem[0], dut.u_weight_ram.mem[1],
                     dut.u_weight_ram.mem[2], dut.u_weight_ram.mem[3],
                     u_flash.mem[0], u_flash.mem[1], u_flash.mem[2], u_flash.mem[3],
                     dut.u_weight_ram.mem[1376], dut.u_weight_ram.mem[1377]);
            $fatal(1);
        end

        if (dut.test_status == 32'hCAFE_BABE) begin
            sampled_logit_word = dut.u_weight_ram.mem[1376];
            raw_logit_word = sampled_logit_word;
            log0_s = $signed(sampled_logit_word[15:0]);
            log1_s = $signed(sampled_logit_word[31:16]);
            diff_s = log0_s - log1_s;
            expected_conf = diff_s[15] ? {16'h0, $unsigned(-diff_s)} : {16'h0, $unsigned(diff_s)};
            expected_class = (log1_s > log0_s);

            if (!saw_feature_latch) begin
                $display("FAIL: never observed feature MMIO latch go valid");
                failures = failures + 1;
            end
            if (feature_status_reads == 0 || feature_time_reads == 0 || feature_motion_reads == 0 ||
                feature_dhr_reads == 0 || feature_rmssd_reads == 0) begin
                $display("FAIL: CPU did not read full feature MMIO bank");
                failures = failures + 1;
            end
            if (feature_clear_writes == 0) begin
                $display("FAIL: CPU did not clear FEATURE_STATUS valid bit");
                failures = failures + 1;
            end
            if (weight_feature_writes < 4) begin
                $display("FAIL: too few CPU writes into feature input buffer: %0d", weight_feature_writes);
                failures = failures + 1;
            end
            if (!saw_feature_word0_snap || (feature_word0_snap !== {first_time_feat[15:0], first_motion_feat[15:0]})) begin
                $display("FAIL: weight RAM word0 mismatch expected={time,motion}=0x%04x_%04x got=0x%08x",
                         first_time_feat[15:0], first_motion_feat[15:0], feature_word0_snap);
                failures = failures + 1;
            end
            if (!saw_feature_word1_snap || (feature_word1_snap !== {first_rmssd_feat[15:0], first_delta_hr_feat[15:0]})) begin
                $display("FAIL: weight RAM word1 mismatch expected={rmssd,dhr}=0x%04x_%04x got=0x%08x",
                         first_rmssd_feat[15:0], first_delta_hr_feat[15:0], feature_word1_snap);
                failures = failures + 1;
            end
            if (spi_cs_asserts == 0) begin
                $display("FAIL: firmware never asserted SPI CS");
                failures = failures + 1;
            end
            if (spi_bit_count < MIN_SPI_BITS) begin
                $display("FAIL: too few SPI bit clocks observed: %0d", spi_bit_count);
                failures = failures + 1;
            end
            if (dut.u_weight_ram.mem[32] !== u_flash.mem[0] ||
                dut.u_weight_ram.mem[33] !== u_flash.mem[1] ||
                dut.u_weight_ram.mem[34] !== u_flash.mem[2] ||
                dut.u_weight_ram.mem[35] !== u_flash.mem[3]) begin
                $display("FAIL: WRAM leading words do not match SPI flash image");
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
                $display("FAIL: did not observe ML BUSY polling");
                failures = failures + 1;
            end
            if (axi_ar_hs == 0 || axi_r_hs == 0) begin
                $display("FAIL: no AXI read activity from taketwo");
                failures = failures + 1;
            end
            if ((axi_aw_hs == 0) && (axi_w_hs == 0) && (axi_b_hs == 0)) begin
                $display("FAIL: no AXI write activity from taketwo");
                failures = failures + 1;
            end
            if ((dut.u_weight_ram.mem[1376] === 32'hA5A55A5A) && (dut.u_weight_ram.mem[1377] === 32'h5A5AA5A5)) begin
                $display("FAIL: logit output region kept sentinel values");
                failures = failures + 1;
            end
            if (!dut.test_code[30]) begin
                $display("FAIL: firmware did not report output mutation in TEST_CODE");
                failures = failures + 1;
            end
            if (!dut.test_code[29]) begin
                $display("FAIL: firmware did not report BUSY high observation in TEST_CODE");
                failures = failures + 1;
            end
            if (dut.ml_score_hw !== expected_conf) begin
                $display("FAIL: firmware score mismatch expected=0x%08x got=0x%08x", expected_conf, dut.ml_score_hw);
                failures = failures + 1;
            end
            if (dut.test_code[15:0] !== expected_conf[15:0]) begin
                $display("FAIL: TEST_CODE confidence mismatch expected=0x%04x got=0x%04x",
                         expected_conf[15:0], dut.test_code[15:0]);
                failures = failures + 1;
            end
            if (dut.test_code[31] !== expected_class) begin
                $display("FAIL: predicted class mismatch expected=%0d got=%0d", expected_class, dut.test_code[31]);
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_top_feature_ml_cpu_spi_flash");
                $display("  score=0x%08x class=%0d spi_cs=%0d spi_bits=%0d axi=%0d/%0d/%0d/%0d/%0d code=0x%08x",
                         dut.ml_score_hw, dut.test_code[31], spi_cs_asserts, spi_bit_count,
                         axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs, dut.test_code);
                $finish;
            end else begin
                $display("FAIL: tb_top_feature_ml_cpu_spi_flash failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT_CYCLES);
    $display("  status=0x%08x code=0x%08x score=0x%08x spi_bits=%0d axi=%0d/%0d/%0d/%0d/%0d",
             dut.test_status, dut.test_code, dut.ml_score_hw, spi_bit_count,
             axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
    $fatal(1);
end

initial begin
    $dumpfile("sim/build/top_feature_ml_cpu_spi_flash.vcd");
    $dumpvars(0, tb_top_feature_ml_cpu_spi_flash);
end

endmodule
