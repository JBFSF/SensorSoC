`timescale 1ns/1ps

module tb_top_feature_ml_cpu;

// Unified-top end-to-end verification bench.
// This test keeps the real sensor models in the loop and checks the intended
// CPU-owned path:
//   feature MMIO -> CPU reads -> shared ML RAM writes -> ML AXI-Lite start.

localparam [31:0] FEATURE_BASE = 32'h0300_4000;
localparam [31:0] WEIGHT_BASE  = 32'h0300_6000;
localparam [31:0] ML_BASE      = 32'h0300_3000;
localparam [31:0] REG_START    = ML_BASE + 32'h10;
localparam [31:0] REG_BUSY     = ML_BASE + 32'h14;
localparam [31:0] REG_GBASE    = ML_BASE + 32'h80;

localparam [31:0] FEAT_STATUS  = FEATURE_BASE + 32'h00;
localparam [31:0] FEAT_TIME    = FEATURE_BASE + 32'h04;
localparam [31:0] FEAT_MOTION  = FEATURE_BASE + 32'h08;
localparam [31:0] FEAT_DHR     = FEATURE_BASE + 32'h0C;
localparam [31:0] FEAT_RMSSD   = FEATURE_BASE + 32'h10;

localparam int unsigned TB_TIMEOUT_CYCLES = 8_000_000;
localparam int unsigned TB_PROGRESS_EVERY = 1_000_000;

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

localparam [6:0] ACC_ADDR = 7'h19;
localparam [6:0] PPG_ADDR = 7'h64;

wire                      feat_valid;
wire signed [15:0]        time_feat;
wire signed [15:0]        motion_feat;
wire signed [15:0]        delta_hr_feat;
wire signed [15:0]        rmssd_feat;
wire                      ml_update_gate;
wire [7:0]                invalid_reason;
wire                      epoch_end;
wire                      alarm;

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
reg saw_feature_latch;
reg signed [15:0] first_time_feat;
reg signed [15:0] first_motion_feat;
reg signed [15:0] first_delta_hr_feat;
reg signed [15:0] first_rmssd_feat;
reg saw_global_base_write;
reg saw_start_write;
reg saw_busy_read;

// Route the top-level functional I2C simulation bus to the correct model
// based on the addressed sensor.
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
    .FIRMWARE_HEX("firmware/build/test_top_feature_ml_cpu/firmware.hex"),
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
    .spi_miso_i(1'b1),
    .spi_cs_n_o(spi_cs_n),
    .feat_valid_o(feat_valid),
    .time_feat_o(time_feat),
    .motion_feat_o(motion_feat),
    .delta_hr_feat_o(delta_hr_feat),
    .rmssd_feat_o(rmssd_feat),
    .ml_update_gate_o(ml_update_gate),
    .invalid_reason_o(invalid_reason),
    .epoch_end_o(epoch_end),
    .alarm_o(alarm),
    .test_force_irq_i(1'b0),
    .test_force_wake_i(1'b0)
);

assign host_i2c_scl = 1'b1;

// Simulation-only accelerometer model.
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

// Simulation-only PPG model.
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
        saw_feature_latch <= 1'b0;
        first_time_feat <= '0;
        first_motion_feat <= '0;
        first_delta_hr_feat <= '0;
        first_rmssd_feat <= '0;
        saw_global_base_write <= 1'b0;
        saw_start_write <= 1'b0;
        saw_busy_read <= 1'b0;
    end else begin
        // Snapshot the first published feature vector so we can compare it
        // against what firmware later writes into the shared ML input buffer.
        if (!saw_feature_latch && dut.feat_latched_valid_r) begin
            saw_feature_latch <= 1'b1;
            first_time_feat <= dut.feat_time_latched_r;
            first_motion_feat <= dut.feat_motion_latched_r;
            first_delta_hr_feat <= dut.feat_delta_hr_latched_r;
            first_rmssd_feat <= dut.feat_rmssd_latched_r;
        end

        // Count CPU reads from the feature MMIO bank and ML busy polling.
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

        // Count CPU writes that move features into the shared input buffer and
        // kick the ML control registers.
        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0)) begin
            if ((dut.mem_addr >= WEIGHT_BASE + 32'h40) && (dut.mem_addr < WEIGHT_BASE + 32'h48))
                weight_feature_writes <= weight_feature_writes + 1;
            if ((dut.mem_addr == FEAT_STATUS) && dut.mem_wdata[0])
                feature_clear_writes <= feature_clear_writes + 1;
            if (dut.mem_addr == REG_GBASE && dut.mem_wdata == WEIGHT_BASE)
                saw_global_base_write <= 1'b1;
            if (dut.mem_addr == REG_START && dut.mem_wdata[0])
                saw_start_write <= 1'b1;
        end

        // Observe taketwo AXI traffic into shared RAM so the bench can prove
        // the accelerator is actually running after the CPU starts it.
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

    $display("[TB] start FW=firmware/build/test_top_feature_ml_cpu/firmware.hex WEIGHTS=firmware/build/generated/taketwo_params.hex");

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    while (cycles < TB_TIMEOUT_CYCLES) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[cyc %0d] alive status=0x%08x code=0x%08x feature_reads=%0d/%0d/%0d/%0d/%0d feature_writes=%0d axi=%0d/%0d/%0d/%0d/%0d",
                     cycles, dut.test_status, dut.test_code,
                     feature_status_reads, feature_time_reads, feature_motion_reads,
                     feature_dhr_reads, feature_rmssd_reads, weight_feature_writes,
                     axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
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
            // The shared input buffer should match the feature vector that was
            // published through the MMIO-visible latch bank.
            if (dut.u_weight_ram.mem[16] !== {first_time_feat[15:0], first_motion_feat[15:0]}) begin
                $display("FAIL: weight RAM word0 mismatch expected={time,motion}=0x%04x_%04x got=0x%08x",
                         first_time_feat[15:0], first_motion_feat[15:0], dut.u_weight_ram.mem[16]);
                failures = failures + 1;
            end
            if (dut.u_weight_ram.mem[17] !== {first_rmssd_feat[15:0], first_delta_hr_feat[15:0]}) begin
                $display("FAIL: weight RAM word1 mismatch expected={rmssd,dhr}=0x%04x_%04x got=0x%08x",
                         first_rmssd_feat[15:0], first_delta_hr_feat[15:0], dut.u_weight_ram.mem[17]);
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

            if (failures == 0) begin
                $display("PASS: tb_top_feature_ml_cpu");
                $display("  feature_reads=%0d/%0d/%0d/%0d/%0d clear=%0d wbuf_writes=%0d axi=%0d/%0d/%0d/%0d/%0d code=0x%08x",
                         feature_status_reads, feature_time_reads, feature_motion_reads,
                         feature_dhr_reads, feature_rmssd_reads, feature_clear_writes,
                         weight_feature_writes, axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs,
                         dut.test_code);
                $finish;
            end else begin
                $display("FAIL: tb_top_feature_ml_cpu failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT_CYCLES);
    $display("  status=0x%08x code=0x%08x feature_reads=%0d/%0d/%0d/%0d/%0d wbuf_writes=%0d axi=%0d/%0d/%0d/%0d/%0d",
             dut.test_status, dut.test_code,
             feature_status_reads, feature_time_reads, feature_motion_reads,
             feature_dhr_reads, feature_rmssd_reads, weight_feature_writes,
             axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
    $fatal(1);
end

initial begin
    $dumpfile("/tmp/top_feature_ml_cpu.vcd");
    $dumpvars(0, tb_top_feature_ml_cpu);
end

endmodule
