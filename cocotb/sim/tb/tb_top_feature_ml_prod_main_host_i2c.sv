`timescale 1ns/1ps

module tb_top_feature_ml_prod_main_host_i2c;

localparam [31:0] FEATURE_BASE = 32'h0300_4000;
localparam [31:0] WEIGHT_BASE  = 32'h0300_6000;
localparam [31:0] ML_BASE      = 32'h0300_3000;
localparam [31:0] REG_START    = ML_BASE + 32'h10;
localparam [31:0] REG_BUSY     = ML_BASE + 32'h14;
localparam [31:0] REG_GBASE    = ML_BASE + 32'h80;
localparam [31:0] REG_XBASE    = ML_BASE + 32'h8C;
localparam [31:0] REG_VAR_BASE = ML_BASE + 32'h90;
localparam [31:0] IRQC_BASE    = 32'h0300_5000;
localparam [31:0] TEST_FAIL    = 32'hDEAD_BEEF;
localparam [31:0] X_BASE       = WEIGHT_BASE + 32'd64;
localparam [31:0] VAR_BASE     = WEIGHT_BASE + 32'd128;
localparam [31:0] LOGIT_BASE   = WEIGHT_BASE + 32'd5504;

localparam [31:0] FEAT_STATUS  = FEATURE_BASE + 32'h00;
localparam [31:0] FEAT_TIME    = FEATURE_BASE + 32'h04;
localparam [31:0] FEAT_MOTION  = FEATURE_BASE + 32'h08;
localparam [31:0] FEAT_DHR     = FEATURE_BASE + 32'h0C;
localparam [31:0] FEAT_RMSSD   = FEATURE_BASE + 32'h10;

localparam [31:0] IRQC_MASK_ADDR    = IRQC_BASE + 32'h04;
localparam [31:0] IRQC_WAKE_EN_ADDR = IRQC_BASE + 32'h08;
localparam [31:0] IRQC_CLAIM_ADDR   = IRQC_BASE + 32'h14;
localparam [31:0] IRQC_COMPLETE_ADDR = IRQC_BASE + 32'h18;

localparam int unsigned FLASH_WORDS = 208;
localparam int unsigned TB_TIMEOUT_CYCLES = 20_000_000;
localparam int unsigned TB_PROGRESS_EVERY = 1_000_000;
localparam int unsigned MIN_SPI_BITS = 8 * (4 + FLASH_WORDS * 4);
localparam int unsigned MIN_ML_IRQ_COMPLETES = 4;

localparam [7:0] HOST_WHOAMI      = 8'h00;
localparam [7:0] HOST_VERSION     = 8'h01;
localparam [7:0] HOST_IRQ_COUNT_L = 8'h05;
localparam [7:0] HOST_IRQ_COUNT_H = 8'h06;
localparam [7:0] HOST_CONF_THR_L  = 8'h30;
localparam [7:0] HOST_CONF_THR_H  = 8'h31;
localparam [7:0] HOST_CONF_CTRL   = 8'h32;
localparam [7:0] HOST_CONF_STAT   = 8'h33;
localparam [7:0] HOST_LOGIT0_L    = 8'h34;
localparam [7:0] HOST_LOGIT0_H    = 8'h35;
localparam [7:0] HOST_CONF_ABS_L  = 8'h38;
localparam [7:0] HOST_CONF_ABS_H  = 8'h39;

reg clk;
reg reset;
reg scl_drv;
reg sda_drv_low;
tri1 host_i2c_sda;

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
integer first_ar_captures;
integer spi_cs_asserts;
integer spi_bit_count;
integer boot_writes_seen;
integer sleep_writes;
integer spi_data_writes;
integer spi_status_reads;
integer sleep_edges;
integer wake_edges;
integer test_code_writes;
integer ml_score_writes;
integer irq_claim_reads;
integer irq_claim_writes;
integer irq_complete_writes;
integer irq_pending_ml_clears;
integer ml_irq_clr_writes;
reg saw_feature_latch;
reg signed [15:0] first_time_feat;
reg signed [15:0] first_motion_feat;
reg signed [15:0] first_delta_hr_feat;
reg signed [15:0] first_rmssd_feat;
reg saw_global_base_write;
reg saw_start_write;
reg saw_busy_read;
reg saw_ml_irq_pending;
reg saw_host_irq_event;
reg saw_mask_ml_only;
reg saw_wake_ml_only;
reg saw_ml_claim;
reg saw_ml_complete;
reg saw_nonzero_score;
reg prev_spi_cs_n;
reg prev_spi_clk;
reg [31:0] boot_word0;
reg [31:0] boot_word1;
reg [31:0] boot_word2;
reg [31:0] boot_word3;
reg [31:0] first_feature_word0;
reg [31:0] first_feature_word1;
reg saw_first_feature_word0;
reg saw_first_feature_word1;
reg saw_xbase_write;
reg saw_var_base_write;

reg host_cfg_done;
reg host_observed_score;
reg [7:0] host_whoami;
reg [7:0] host_version;
reg [7:0] host_conf_stat;
reg [7:0] host_irq_count_lo;
reg [7:0] host_irq_count_hi;
reg [7:0] host_logit0_l;
reg [7:0] host_logit0_h;
reg [7:0] host_conf_abs_l;
reg [7:0] host_conf_abs_h;

reg [31:0] expected_conf;
reg expected_class;
reg [31:0] raw_logit_word;
reg [31:0] sampled_logit_word;
reg signed [15:0] log0_s;
reg signed [15:0] log1_s;
reg signed [15:0] diff_s;
reg [15:0] host_conf_abs;
reg [15:0] host_logit0;
reg [15:0] host_irq_count;
reg [15:0] expected_host_conf_abs;
reg [15:0] expected_host_logit0;
reg printed_spi_start;
reg printed_feature_latch;
reg printed_ml_start;
reg printed_first_score;
reg printed_first_weight_write;
reg printed_first_test_code_write;
reg printed_first_ml_score_write;
reg printed_first_postwake_logits;
reg printed_stall_snapshot;
reg printed_spi_internal_snapshot;
reg boot_done;
reg printed_boot_done;
reg printed_sensor_stream_enable;
reg saw_preboot_feature_read;
reg prev_cpu_clk_en;
reg prev_ml_irq_pending;
reg printed_first_irqc_snapshot;
reg printed_first_coherent_score;
reg printed_multi_irq_checkpoint;
reg host_irq_rearm_done;
reg [31:0] iter_feature_word0;
reg [31:0] iter_feature_word1;
reg signed [15:0] iter_time_feat;
reg signed [15:0] iter_motion_feat;
reg signed [15:0] iter_delta_hr_feat;
reg signed [15:0] iter_rmssd_feat;
reg iter_tracking;
reg iter_has_word0;
reg iter_has_word1;

assign host_i2c_sda = sda_drv_low ? 1'b0 : 1'bz;

assign sim_ack    = boot_done ? ((sim_addr == ACC_ADDR) ? accel_sim_ack    :
                                 (sim_addr == PPG_ADDR) ? ppg_sim_ack      : 1'b0) : 1'b0;
assign sim_rdata  = boot_done ? ((sim_addr == ACC_ADDR) ? accel_sim_rdata  :
                                 (sim_addr == PPG_ADDR) ? ppg_sim_rdata    : 8'h00) : 8'h00;
assign sim_rvalid = boot_done ? ((sim_addr == ACC_ADDR) ? accel_sim_rvalid :
                                 (sim_addr == PPG_ADDR) ? ppg_sim_rvalid   : 1'b0) : 1'b0;
assign sim_rlast  = boot_done ? ((sim_addr == ACC_ADDR) ? accel_sim_rlast  :
                                 (sim_addr == PPG_ADDR) ? ppg_sim_rlast    : 1'b0) : 1'b0;
assign sim_err    = boot_done ? ((sim_addr == ACC_ADDR) ? accel_sim_err    :
                                 (sim_addr == PPG_ADDR) ? ppg_sim_err      : 1'b1) : 1'b0;

top #(
    .MEM_WORDS(8192),
    .FIRMWARE_HEX("firmware/build/prod_main/firmware.hex"),
    .WEIGHT_INIT_HEX(""),
    .CLK_HZ(1000),
    .GT_CLK_HZ(1000),
    .GT_EPOCH_HZ(100),
    .GT_EPOCH_COUNT_MAX(16),
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
    .i2c_scl_i(scl_drv),
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
        first_ar_captures <= 0;
        spi_cs_asserts <= 0;
        spi_bit_count <= 0;
        boot_writes_seen <= 0;
        sleep_writes <= 0;
        spi_data_writes <= 0;
        spi_status_reads <= 0;
        sleep_edges <= 0;
        wake_edges <= 0;
        test_code_writes <= 0;
        ml_score_writes <= 0;
        irq_claim_reads <= 0;
        irq_claim_writes <= 0;
        irq_complete_writes <= 0;
        irq_pending_ml_clears <= 0;
        ml_irq_clr_writes <= 0;
        saw_feature_latch <= 1'b0;
        first_time_feat <= '0;
        first_motion_feat <= '0;
        first_delta_hr_feat <= '0;
        first_rmssd_feat <= '0;
        saw_global_base_write <= 1'b0;
        saw_start_write <= 1'b0;
        saw_busy_read <= 1'b0;
        saw_ml_irq_pending <= 1'b0;
        saw_host_irq_event <= 1'b0;
        saw_mask_ml_only <= 1'b0;
        saw_wake_ml_only <= 1'b0;
        saw_ml_claim <= 1'b0;
        saw_ml_complete <= 1'b0;
        saw_nonzero_score <= 1'b0;
        prev_spi_cs_n <= 1'b1;
        prev_spi_clk <= 1'b0;
        boot_word0 <= 32'h0;
        boot_word1 <= 32'h0;
        boot_word2 <= 32'h0;
        boot_word3 <= 32'h0;
        first_feature_word0 <= 32'h0;
        first_feature_word1 <= 32'h0;
        saw_first_feature_word0 <= 1'b0;
        saw_first_feature_word1 <= 1'b0;
        saw_xbase_write <= 1'b0;
        saw_var_base_write <= 1'b0;
        sampled_logit_word <= 32'h0;
        iter_feature_word0 <= 32'h0;
        iter_feature_word1 <= 32'h0;
        iter_time_feat <= '0;
        iter_motion_feat <= '0;
        iter_delta_hr_feat <= '0;
        iter_rmssd_feat <= '0;
        iter_tracking <= 1'b0;
        iter_has_word0 <= 1'b0;
        iter_has_word1 <= 1'b0;
        printed_spi_start <= 1'b0;
        printed_feature_latch <= 1'b0;
        printed_ml_start <= 1'b0;
        printed_first_score <= 1'b0;
        printed_first_weight_write <= 1'b0;
        printed_first_test_code_write <= 1'b0;
        printed_first_ml_score_write <= 1'b0;
        printed_first_postwake_logits <= 1'b0;
        printed_stall_snapshot <= 1'b0;
        printed_spi_internal_snapshot <= 1'b0;
        boot_done <= 1'b0;
        printed_boot_done <= 1'b0;
        printed_sensor_stream_enable <= 1'b0;
        saw_preboot_feature_read <= 1'b0;
        printed_first_irqc_snapshot <= 1'b0;
        prev_cpu_clk_en <= 1'b1;
        prev_ml_irq_pending <= 1'b0;
    end else begin
        if (!boot_done &&
            (spi_bit_count >= MIN_SPI_BITS) &&
            (boot_writes_seen >= 4) &&
            (dut.u_weight_ram.mem[32] === u_flash.mem[0]) &&
            (dut.u_weight_ram.mem[33] === u_flash.mem[1]) &&
            (dut.u_weight_ram.mem[34] === u_flash.mem[2]) &&
            (dut.u_weight_ram.mem[35] === u_flash.mem[3])) begin
            boot_done <= 1'b1;
            if (!printed_boot_done) begin
                printed_boot_done <= 1'b1;
                $display("[%0t] TB: boot complete spi_bits=%0d boot_writes=%0d wram[32..35]=%08x %08x %08x %08x",
                         $time, spi_bit_count, boot_writes_seen,
                         dut.u_weight_ram.mem[32], dut.u_weight_ram.mem[33],
                         dut.u_weight_ram.mem[34], dut.u_weight_ram.mem[35]);
            end
            if (!printed_sensor_stream_enable) begin
                printed_sensor_stream_enable <= 1'b1;
                $display("[%0t] TB: sensor streaming enabled after observed weight boot", $time);
            end
        end

        if (prev_spi_cs_n && !spi_cs_n) begin
            spi_cs_asserts <= spi_cs_asserts + 1;
            if (!printed_spi_start) begin
                printed_spi_start <= 1'b1;
                $display("[%0t] TB: first SPI CS assert", $time);
            end
        end
        prev_spi_cs_n <= spi_cs_n;
        if (!prev_spi_clk && spi_clk && !spi_cs_n)
            spi_bit_count <= spi_bit_count + 1;
        prev_spi_clk <= spi_clk;

        if (!saw_feature_latch && dut.feat_latched_valid_r) begin
            saw_feature_latch <= 1'b1;
            if (!printed_feature_latch) begin
                printed_feature_latch <= 1'b1;
                $display("[%0t] TB: first feature latch valid time=%0d motion=%0d dhr=%0d rmssd=%0d",
                         $time, $signed(dut.feat_time_latched_r), $signed(dut.feat_motion_latched_r),
                         $signed(dut.feat_delta_hr_latched_r), $signed(dut.feat_rmssd_latched_r));
            end
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0) &&
            (dut.mem_addr == FEAT_STATUS) && dut.mem_wdata[0]) begin
            first_time_feat <= dut.feat_time_latched_r;
            first_motion_feat <= dut.feat_motion_latched_r;
            first_delta_hr_feat <= dut.feat_delta_hr_latched_r;
            first_rmssd_feat <= dut.feat_rmssd_latched_r;
            iter_time_feat <= dut.feat_time_latched_r;
            iter_motion_feat <= dut.feat_motion_latched_r;
            iter_delta_hr_feat <= dut.feat_delta_hr_latched_r;
            iter_rmssd_feat <= dut.feat_rmssd_latched_r;
            iter_feature_word0 <= 32'h0;
            iter_feature_word1 <= 32'h0;
            iter_has_word0 <= 1'b0;
            iter_has_word1 <= 1'b0;
            iter_tracking <= 1'b1;
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb == 4'b0)) begin
            case (dut.mem_addr)
                FEAT_STATUS: begin
                    feature_status_reads <= feature_status_reads + 1;
                    if (!boot_done) saw_preboot_feature_read <= 1'b1;
                end
                FEAT_TIME: begin
                    feature_time_reads <= feature_time_reads + 1;
                    if (!boot_done) saw_preboot_feature_read <= 1'b1;
                end
                FEAT_MOTION: begin
                    feature_motion_reads <= feature_motion_reads + 1;
                    if (!boot_done) saw_preboot_feature_read <= 1'b1;
                end
                FEAT_DHR: begin
                    feature_dhr_reads <= feature_dhr_reads + 1;
                    if (!boot_done) saw_preboot_feature_read <= 1'b1;
                end
                FEAT_RMSSD: begin
                    feature_rmssd_reads <= feature_rmssd_reads + 1;
                    if (!boot_done) saw_preboot_feature_read <= 1'b1;
                end
                32'h0300A004: spi_status_reads <= spi_status_reads + 1;
                IRQC_CLAIM_ADDR: begin
                    irq_claim_reads <= irq_claim_reads + 1;
                    if (dut.u_irqc.claim_id == 32'h0000_0002)
                        saw_ml_claim <= 1'b1;
                end
                REG_BUSY: begin
                    busy_reads <= busy_reads + 1;
                    saw_busy_read <= 1'b1;
                end
            endcase
        end

        if (dut.mmio_sel && dut.mem_valid && (dut.mem_wstrb != 4'b0)) begin
            if (dut.mem_addr == 32'h0300A008)
                spi_data_writes <= spi_data_writes + 1;
            if (dut.mem_addr == IRQC_COMPLETE_ADDR) begin
                irq_complete_writes <= irq_complete_writes + 1;
                if (dut.mem_wdata == 32'h0000_0002)
                    saw_ml_complete <= 1'b1;
            end
            if ((dut.mem_addr == 32'h0300_5000) && (dut.mem_wdata == 32'h0000_0002))
                irq_pending_ml_clears <= irq_pending_ml_clears + 1;
            if ((dut.mem_addr == (ML_BASE + 32'h2C)) && dut.mem_wdata[0])
                ml_irq_clr_writes <= ml_irq_clr_writes + 1;
            if (dut.mem_addr == IRQC_CLAIM_ADDR || dut.mem_addr == IRQC_COMPLETE_ADDR) begin
                $display("[%0t] TB: raw IRQC bus pc=0x%08x valid=%0b ready=%0b addr=0x%08x wstrb=0x%0x wdata=0x%08x rdata=0x%08x",
                         $time, dut.cpu.reg_pc, dut.mem_valid, dut.mem_ready, dut.mem_addr,
                         dut.mem_wstrb, dut.mem_wdata, dut.mem_rdata);
            end
            if (dut.mem_addr == 32'h0300F004) begin
                test_code_writes <= test_code_writes + 1;
                if (!printed_first_test_code_write) begin
                    printed_first_test_code_write <= 1'b1;
                    $display("[%0t] TB: first TEST_CODE write data=0x%08x pc=0x%08x",
                             $time, dut.mem_wdata, dut.cpu.reg_pc);
                end
            end
            if (dut.mem_addr == 32'h0300F020) begin
                ml_score_writes <= ml_score_writes + 1;
                if (!printed_first_ml_score_write) begin
                    printed_first_ml_score_write <= 1'b1;
                    $display("[%0t] TB: first ML_SCORE write data=0x%08x pc=0x%08x",
                             $time, dut.mem_wdata, dut.cpu.reg_pc);
                end
                if ((dut.mem_wdata != 32'h0) && !saw_nonzero_score) begin
                    saw_nonzero_score <= 1'b1;
                    $display("[%0t] TB: first nonzero ML_SCORE data=0x%08x code=0x%08x",
                             $time, dut.mem_wdata, dut.test_code);
                end
            end
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
            if (!saw_first_feature_word0 && (dut.mem_addr == X_BASE)) begin
                saw_first_feature_word0 <= 1'b1;
                first_feature_word0 <= dut.mem_wdata;
            end
            if (!saw_first_feature_word1 && (dut.mem_addr == (X_BASE + 32'h4))) begin
                saw_first_feature_word1 <= 1'b1;
                first_feature_word1 <= dut.mem_wdata;
            end
            if (iter_tracking && (dut.mem_addr == X_BASE)) begin
                if (dut.mem_wstrb[0]) iter_feature_word0[7:0]   <= dut.mem_wdata[7:0];
                if (dut.mem_wstrb[1]) iter_feature_word0[15:8]  <= dut.mem_wdata[15:8];
                if (dut.mem_wstrb[2]) iter_feature_word0[23:16] <= dut.mem_wdata[23:16];
                if (dut.mem_wstrb[3]) iter_feature_word0[31:24] <= dut.mem_wdata[31:24];
                iter_has_word0 <= 1'b1;
            end
            if (iter_tracking && (dut.mem_addr == (X_BASE + 32'h4))) begin
                if (dut.mem_wstrb[0]) iter_feature_word1[7:0]   <= dut.mem_wdata[7:0];
                if (dut.mem_wstrb[1]) iter_feature_word1[15:8]  <= dut.mem_wdata[15:8];
                if (dut.mem_wstrb[2]) iter_feature_word1[23:16] <= dut.mem_wdata[23:16];
                if (dut.mem_wstrb[3]) iter_feature_word1[31:24] <= dut.mem_wdata[31:24];
                iter_has_word1 <= 1'b1;
            end
            if (!printed_first_weight_write &&
                (dut.mem_addr >= VAR_BASE) && (dut.mem_addr < VAR_BASE + 32'h10)) begin
                printed_first_weight_write <= 1'b1;
                $display("[%0t] TB: first CPU WRAM write addr=0x%08x data=0x%08x ready=%0b pc=0x%08x",
                         $time, dut.mem_addr, dut.mem_wdata, dut.mem_ready, dut.cpu.reg_pc);
            end
            if ((dut.mem_addr == FEAT_STATUS) && dut.mem_wdata[0])
                feature_clear_writes <= feature_clear_writes + 1;
            if (dut.mem_addr == REG_GBASE && dut.mem_wdata == WEIGHT_BASE)
                saw_global_base_write <= 1'b1;
            if (dut.mem_addr == REG_XBASE && dut.mem_wdata == 32'd64)
                saw_xbase_write <= 1'b1;
            if (dut.mem_addr == REG_VAR_BASE && dut.mem_wdata == 32'd128)
                saw_var_base_write <= 1'b1;
            if (dut.mem_addr == REG_START && dut.mem_wdata[0]) begin
                saw_start_write <= 1'b1;
                if (!printed_ml_start) begin
                    printed_ml_start <= 1'b1;
                    $display("[%0t] TB: first ML start write", $time);
                end
            end
            if (dut.mem_addr == 32'h0300_1000 && dut.mem_wdata[0])
                sleep_writes <= sleep_writes + 1;
            if (dut.mem_addr == IRQC_MASK_ADDR && dut.mem_wdata == 32'h0000_0002)
                saw_mask_ml_only <= 1'b1;
            if (dut.mem_addr == IRQC_WAKE_EN_ADDR && dut.mem_wdata == 32'h0000_0002)
                saw_wake_ml_only <= 1'b1;
        end

        if (dut.u_irqc.pending[1]) saw_ml_irq_pending <= 1'b1;
        if (dut.host_i2c_irq_event) saw_host_irq_event <= 1'b1;

        if (prev_cpu_clk_en && !dut.cpu_clk_en) begin
            sleep_edges <= sleep_edges + 1;
            $display("[%0t] TB: CPU -> SLEEP (%0d) pc=0x%08x sleep_req=%0b ml_pending=%0b wake_reason=0x%08x",
                     $time, sleep_edges + 1, dut.cpu.reg_pc, dut.sleep_req,
                     dut.u_irqc.pending[1], dut.u_pwr.wake_reason);
        end
        if (!prev_cpu_clk_en && dut.cpu_clk_en) begin
            wake_edges <= wake_edges + 1;
            $display("[%0t] TB: CPU -> WAKE (%0d) pc=0x%08x ml_pending=%0b wake_reason=0x%08x",
                     $time, wake_edges + 1, dut.cpu.reg_pc, dut.u_irqc.pending[1],
                     dut.u_pwr.wake_reason);
        end
        if (!prev_ml_irq_pending && dut.u_irqc.pending[1]) begin
            $display("[%0t] TB: ML IRQ pending rise wake_reason=0x%08x",
                     $time, dut.u_pwr.wake_reason);
            if (!printed_first_irqc_snapshot) begin
                printed_first_irqc_snapshot <= 1'b1;
                $display("[%0t] TB: IRQC snapshot pending=0x%08x mask=0x%08x wake_en=0x%08x claim_id=0x%08x active=0x%08x irq=0x%08x test_code=0x%08x",
                         $time, dut.u_irqc.pending, dut.u_irqc.mask, dut.u_irqc.wake_en,
                         dut.u_irqc.claim_id, dut.u_irqc.active, dut.irq, dut.test_code);
            end
        end
        prev_cpu_clk_en <= dut.cpu_clk_en;
        prev_ml_irq_pending <= dut.u_irqc.pending[1];

        if (!printed_first_postwake_logits && (irq_claim_reads > 0 || wake_edges > 0)) begin
            if ((dut.u_weight_ram.mem[1376] !== 32'hA5A55A5A) ||
                (dut.u_weight_ram.mem[1377] !== 32'h5A5AA5A5)) begin
                printed_first_postwake_logits <= 1'b1;
                $display("[%0t] TB: first post-irq logits word0=0x%08x word1=0x%08x",
                         $time, dut.u_weight_ram.mem[1376], dut.u_weight_ram.mem[1377]);
            end
        end

        if (dut.wram_arvalid && dut.wram_arready) axi_ar_hs <= axi_ar_hs + 1;
        if (dut.wram_arvalid && dut.wram_arready && (first_ar_captures < 8)) begin
            first_ar_captures <= first_ar_captures + 1;
            $display("[%0t] TB: ML AR[%0d] addr=0x%08x (x_base=0x%08x var_base=0x%08x out_base=0x%08x)",
                     $time, first_ar_captures, dut.wram_araddr, X_BASE, VAR_BASE, LOGIT_BASE);
        end
        if (dut.wram_rvalid  && dut.wram_rready)  axi_r_hs  <= axi_r_hs + 1;
        if (dut.wram_awvalid && dut.wram_awready) axi_aw_hs <= axi_aw_hs + 1;
        if (dut.wram_wvalid  && dut.wram_wready)  axi_w_hs  <= axi_w_hs + 1;
        if (dut.wram_bvalid  && dut.wram_bready)  axi_b_hs  <= axi_b_hs + 1;
    end
end

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

task i2c_read_byte;
    output [7:0] byte_out;
    input ack_from_master;
    integer i;
    reg bitv;
begin
    byte_out = 8'h00;
    for (i = 7; i >= 0; i = i - 1) begin
        i2c_read_bit(bitv);
        byte_out[i] = bitv;
    end
    i2c_write_bit(ack_from_master);
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

task i2c_read_reg;
    input [7:0] reg_addr;
    output [7:0] reg_data;
    reg ack;
begin
    i2c_start();
    i2c_write_byte(8'h84, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host write address before read");
        failures = failures + 1;
    end
    i2c_write_byte(reg_addr, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host register pointer before read");
        failures = failures + 1;
    end
    i2c_start();
    i2c_write_byte(8'h85, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host read address");
        failures = failures + 1;
    end
    i2c_read_byte(reg_data, 1'b1);
    i2c_stop();
end
endtask

task i2c_read_reg16_stable;
    input [7:0] reg_addr_lo;
    input [7:0] reg_addr_hi;
    output [15:0] reg_data;
    reg [7:0] lo0, hi0, lo1, hi1;
begin
    i2c_read_reg(reg_addr_lo, lo0);
    i2c_read_reg(reg_addr_hi, hi0);
    i2c_read_reg(reg_addr_lo, lo1);
    i2c_read_reg(reg_addr_hi, hi1);

    if ((lo0 == lo1) && (hi0 == hi1))
        reg_data = {hi0, lo0};
    else
        reg_data = {hi1, lo1};
end
endtask

initial begin
    clk = 1'b0;
    reset = 1'b1;
    scl_drv = 1'b1;
    sda_drv_low = 1'b0;
    failures = 0;
    cycles = 0;
    host_cfg_done = 1'b0;
    host_observed_score = 1'b0;
    expected_conf = 32'h0;
    expected_class = 1'b0;
    printed_first_coherent_score = 1'b0;
    printed_multi_irq_checkpoint = 1'b0;
    host_irq_rearm_done = 1'b0;

    $display("[TB] start FW=firmware/build/prod_main/firmware.hex FLASH=firmware/build/generated/taketwo_params.hex + host I2C");

    repeat (10) @(posedge clk);
    reset = 1'b0;
    $display("[%0t] Reset released", $time);

    i2c_write_reg(HOST_CONF_THR_L, 8'h01);
    i2c_write_reg(HOST_CONF_THR_H, 8'h00);
    i2c_write_reg(HOST_CONF_CTRL, 8'h03);
    host_cfg_done = 1'b1;
    $display("[%0t] Programmed host confidence threshold bridge", $time);
end

initial begin
    while (cycles < TB_TIMEOUT_CYCLES) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[cyc %0d] status=0x%08x code=0x%08x score=0x%08x boot_done=%0d feature_reads=%0d/%0d/%0d/%0d/%0d spi_cs=%0d spi_bits=%0d host_event=%0d axi=%0d/%0d/%0d/%0d/%0d",
                     cycles, dut.test_status, dut.test_code, dut.ml_score_hw,
                     boot_done,
                     feature_status_reads, feature_time_reads, feature_motion_reads,
                     feature_dhr_reads, feature_rmssd_reads,
                     spi_cs_asserts, spi_bit_count, saw_host_irq_event,
                     axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
        end

        if (!printed_stall_snapshot && (cycles >= 10000) && (spi_bit_count == 64) &&
            (feature_status_reads == 0) && (weight_feature_writes == 0)) begin
            printed_stall_snapshot = 1'b1;
            $display("[%0t] TB: stall snapshot pc=0x%08x mem_valid=%0b mem_ready=%0b mem_addr=0x%08x mem_wstrb=0x%0x mem_wdata=0x%08x spi_status=0x%08x spi_cs_n=%0b cpu_clk_en=%0b sleeping=%0b sleep_req=%0b spi_data_writes=%0d spi_status_reads=%0d",
                     $time, dut.cpu.reg_pc, dut.mem_valid, dut.mem_ready, dut.mem_addr,
                     dut.mem_wstrb, dut.mem_wdata, dut.spi_rdata, spi_cs_n,
                     dut.cpu_clk_en, dut.sleeping_r, dut.sleep_req, spi_data_writes, spi_status_reads);
        end
        if (!printed_spi_internal_snapshot && printed_stall_snapshot) begin
            printed_spi_internal_snapshot = 1'b1;
            $display("[%0t] TB: spi internals busy=%0b clk=%0b cs_n=%0b div=%0d div_cnt=%0d phase=%0b bit_cnt=%0d tx_shift=0x%02x rx_shift=0x%02x rx_data=0x%02x",
                     $time, dut.u_spi.busy, dut.u_spi.spi_clk_o, dut.u_spi.spi_cs_n_o,
                     dut.u_spi.divider_reg, dut.u_spi.div_cnt, dut.u_spi.sck_phase,
                     dut.u_spi.bit_cnt, dut.u_spi.tx_shift, dut.u_spi.rx_shift, dut.u_spi.rx_data);
        end

        if (!printed_first_score &&
            (dut.ml_score_hw != 32'h0) &&
            (dut.test_code[15:0] == dut.ml_score_hw[15:0]) &&
            (dut.u_weight_ram.mem[1376] !== 32'hA5A55A5A)) begin
            printed_first_score = 1'b1;
            $display("[%0t] TB: first true output score=0x%08x code=0x%08x logit_word=0x%08x class=%0d",
                     $time, dut.ml_score_hw, dut.test_code, dut.u_weight_ram.mem[1376], dut.test_code[31]);
        end

        if (dut.trap) begin
            $display("FAIL: CPU trap asserted mem_addr=0x%08x pc=0x%08x", dut.mem_addr, dut.cpu.reg_pc);
            $fatal(1);
        end

        if (saw_preboot_feature_read) begin
            $display("FAIL: observed feature MMIO read before boot_done");
            $display("  boot_done=%0d spi_bits=%0d boot_writes=%0d feature_reads=%0d/%0d/%0d/%0d/%0d",
                     boot_done, spi_bit_count, boot_writes_seen,
                     feature_status_reads, feature_time_reads, feature_motion_reads,
                     feature_dhr_reads, feature_rmssd_reads);
            $fatal(1);
        end

        if (dut.test_status == TEST_FAIL) begin
            $display("FAIL: firmware reported FAIL code=0x%08x", dut.test_code);
            $display("  spi_cs=%0d spi_bits=%0d boot_writes=%0d captured=%08x %08x %08x %08x wram[32..35]=%08x %08x %08x %08x flash[0..3]=%08x %08x %08x %08x out=%08x %08x",
                     spi_cs_asserts, spi_bit_count, boot_writes_seen,
                     boot_word0, boot_word1, boot_word2, boot_word3,
                     dut.u_weight_ram.mem[32], dut.u_weight_ram.mem[33],
                     dut.u_weight_ram.mem[34], dut.u_weight_ram.mem[35],
                     u_flash.mem[0], u_flash.mem[1], u_flash.mem[2], u_flash.mem[3],
                     dut.u_weight_ram.mem[1376], dut.u_weight_ram.mem[1377]);
            $fatal(1);
        end

        if ((irq_claim_reads >= 4) && (ml_score_writes <= 1) && (dut.test_status != TEST_FAIL)) begin
            $display("FAIL: serviced ML IRQ %0d times without any non-init ML_SCORE write", irq_claim_reads);
            $display("  code=0x%08x score=0x%08x out=%08x %08x test_code_writes=%0d claim_writes=%0d complete_writes=%0d",
                     dut.test_code, dut.ml_score_hw, dut.u_weight_ram.mem[1376],
                     dut.u_weight_ram.mem[1377], test_code_writes, irq_claim_writes, irq_complete_writes);
            $fatal(1);
        end

        if (host_cfg_done && !host_observed_score &&
            saw_start_write && (ml_score_writes > 1) &&
            (dut.test_code[15:0] == dut.ml_score_hw[15:0]) &&
            (dut.ml_score_hw >= 32'h0000_0001) &&
            (dut.u_weight_ram.mem[1376] !== 32'hA5A55A5A)) begin
            host_observed_score = 1'b1;
            printed_first_coherent_score = 1'b1;
            iter_tracking = 1'b0;
            $display("[%0t] TB: first coherent host-visible score score=0x%08x code=0x%08x irq_complete_writes=%0d host_irq_event=%0d",
                     $time, dut.ml_score_hw, dut.test_code, irq_complete_writes, saw_host_irq_event);
        end

        if (host_observed_score && !host_irq_rearm_done) begin
            host_irq_rearm_done = 1'b1;
            i2c_write_reg(HOST_CONF_THR_L, 8'hFF);
            i2c_write_reg(HOST_CONF_THR_H, 8'hFF);
            i2c_write_reg(HOST_CONF_THR_L, 8'h01);
            i2c_write_reg(HOST_CONF_THR_H, 8'h00);
            i2c_write_reg(HOST_CONF_THR_L, 8'hFF);
            i2c_write_reg(HOST_CONF_THR_H, 8'hFF);
            i2c_write_reg(HOST_CONF_THR_L, 8'h01);
            i2c_write_reg(HOST_CONF_THR_H, 8'h00);
            i2c_write_reg(HOST_CONF_THR_L, 8'hFF);
            i2c_write_reg(HOST_CONF_THR_H, 8'hFF);
            i2c_write_reg(HOST_CONF_THR_L, 8'h01);
            i2c_write_reg(HOST_CONF_THR_H, 8'h00);
            $display("[%0t] TB: re-armed host confidence threshold for repeated IRQ generation", $time);
        end

        if (host_observed_score && !printed_multi_irq_checkpoint &&
            (dut.u_host_i2c_bridge_regs.irq_count >= MIN_ML_IRQ_COMPLETES)) begin
            printed_multi_irq_checkpoint = 1'b1;
            $display("[%0t] TB: reached %0d ML IRQ completes score=0x%08x code=0x%08x claims=%0d completes=%0d ml_score_writes=%0d",
                     $time, MIN_ML_IRQ_COMPLETES, dut.ml_score_hw, dut.test_code,
                     irq_claim_reads, irq_complete_writes, ml_score_writes);
        end

        if (host_observed_score &&
            host_irq_rearm_done &&
            (dut.u_host_i2c_bridge_regs.irq_count >= MIN_ML_IRQ_COMPLETES) &&
            (dut.test_code[15:0] == dut.ml_score_hw[15:0]) &&
            (dut.ml_score_hw >= 32'h0000_0001)) begin
            i2c_read_reg(HOST_WHOAMI, host_whoami);
            i2c_read_reg(HOST_VERSION, host_version);
            i2c_read_reg(HOST_CONF_STAT, host_conf_stat);
            i2c_read_reg(HOST_IRQ_COUNT_L, host_irq_count_lo);
            i2c_read_reg(HOST_IRQ_COUNT_H, host_irq_count_hi);
            i2c_read_reg16_stable(HOST_CONF_ABS_L, HOST_CONF_ABS_H, host_conf_abs);
            expected_host_conf_abs = dut.u_host_i2c_bridge_regs.score_conf;
            i2c_read_reg16_stable(HOST_LOGIT0_L, HOST_LOGIT0_H, host_logit0);
            expected_host_logit0 = dut.u_host_i2c_bridge_regs.score_proxy0;


            sampled_logit_word = dut.u_weight_ram.mem[1376];
            raw_logit_word = sampled_logit_word;
            log0_s = $signed(sampled_logit_word[15:0]);
            log1_s = $signed(sampled_logit_word[31:16]);
            diff_s = log0_s - log1_s;
            expected_conf = dut.ml_score_hw;
            expected_class = dut.test_code[31];
            host_irq_count = {host_irq_count_hi, host_irq_count_lo};

            $display("[%0t] TB: host readback conf_abs=0x%04x conf_stat=0x%02x irq_count=%0d logit0_proxy=0x%04x",
                     $time, host_conf_abs, host_conf_stat, host_irq_count, host_logit0);

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
            if (!iter_has_word0 || (iter_feature_word0 !== {iter_time_feat[15:0], iter_motion_feat[15:0]})) begin
                $display("FAIL: weight RAM word0 mismatch expected={time,motion}=0x%04x_%04x got=0x%08x",
                         iter_time_feat[15:0], iter_motion_feat[15:0], iter_feature_word0);
                failures = failures + 1;
            end
            if (!iter_has_word1 || (iter_feature_word1 !== {iter_rmssd_feat[15:0], iter_delta_hr_feat[15:0]})) begin
                $display("FAIL: weight RAM word1 mismatch expected={rmssd,dhr}=0x%04x_%04x got=0x%08x",
                         iter_rmssd_feat[15:0], iter_delta_hr_feat[15:0], iter_feature_word1);
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
            if (!boot_done) begin
                $display("FAIL: never observed bench boot_done before result check");
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
            if (!saw_xbase_write) begin
                $display("FAIL: did not observe ML_REG(0x8C)=64 write");
                failures = failures + 1;
            end
            if (!saw_var_base_write) begin
                $display("FAIL: did not observe ML_REG(0x90)=128 write");
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
            if (!saw_ml_irq_pending) begin
                $display("FAIL: did not observe ML IRQ pending");
                failures = failures + 1;
            end
            if (!saw_mask_ml_only) begin
                $display("FAIL: did not observe IRQC_MASK programmed to ML-only");
                failures = failures + 1;
            end
            if (!saw_wake_ml_only) begin
                $display("FAIL: did not observe IRQC_WAKE_EN programmed to ML-only");
                failures = failures + 1;
            end
            if (irq_claim_reads == 0) begin
                $display("FAIL: did not observe IRQC_CLAIM reads");
                failures = failures + 1;
            end
            if (!saw_ml_claim) begin
                $display("FAIL: did not observe IRQC_CLAIM returning source 2");
                failures = failures + 1;
            end
            if (irq_pending_ml_clears == 0) begin
                $display("FAIL: did not observe ML pending W1C");
                failures = failures + 1;
            end
            if (!saw_ml_complete) begin
                $display("FAIL: did not observe ML complete write");
                failures = failures + 1;
            end
            if (ml_irq_clr_writes == 0) begin
                $display("FAIL: did not observe ML IRQ clear write");
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
            if (host_whoami !== 8'hA5) begin
                $display("FAIL: host WHOAMI mismatch got=0x%02x", host_whoami);
                failures = failures + 1;
            end
            if (host_version !== 8'h01) begin
                $display("FAIL: host VERSION mismatch got=0x%02x", host_version);
                failures = failures + 1;
            end
            if (!saw_host_irq_event) begin
                $display("FAIL: never observed host_i2c_irq_event pulse");
                failures = failures + 1;
            end
            if (host_irq_count < MIN_ML_IRQ_COMPLETES) begin
                $display("FAIL: host IRQ count too small expected>=%0d got=%0d", MIN_ML_IRQ_COMPLETES, host_irq_count);
                failures = failures + 1;
            end
            if (!host_conf_stat[0]) begin
                $display("FAIL: host CONF_STAT live-above-threshold bit not set");
                failures = failures + 1;
            end
            if (!host_conf_stat[1]) begin
                $display("FAIL: host CONF_STAT cross-sticky bit not set");
                failures = failures + 1;
            end
            if (!host_conf_stat[2]) begin
                $display("FAIL: host CONF_STAT fired-sticky bit not set");
                failures = failures + 1;
            end
            if (host_conf_abs == 16'h0000) begin
                $display("FAIL: host CONF_ABS is zero at aggregate checkpoint");
                failures = failures + 1;
            end
            if (host_logit0 == 16'h0000) begin
                $display("FAIL: host LOGIT0 proxy is zero at aggregate checkpoint");
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_top_feature_ml_prod_main_host_i2c");
                $display("  score=0x%08x class=%0d spi_cs=%0d spi_bits=%0d host_irq_count=%0d conf_stat=0x%02x axi=%0d/%0d/%0d/%0d/%0d code=0x%08x",
                         dut.ml_score_hw, dut.test_code[31], spi_cs_asserts, spi_bit_count,
                         host_irq_count, host_conf_stat,
                         axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs, dut.test_code);
                $display("  claims=%0d completes=%0d ml_score_writes=%0d feature_reads=%0d/%0d/%0d/%0d/%0d feature_clears=%0d weight_writes=%0d",
                         irq_claim_reads, irq_complete_writes, ml_score_writes,
                         feature_status_reads, feature_time_reads, feature_motion_reads,
                         feature_dhr_reads, feature_rmssd_reads,
                         feature_clear_writes, weight_feature_writes);
                $finish;
            end else begin
                $display("FAIL: tb_top_feature_ml_prod_main_host_i2c failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT_CYCLES);
    $display("  status=0x%08x code=0x%08x score=0x%08x spi_bits=%0d host_event=%0d axi=%0d/%0d/%0d/%0d/%0d",
             dut.test_status, dut.test_code, dut.ml_score_hw, spi_bit_count, saw_host_irq_event,
             axi_ar_hs, axi_r_hs, axi_aw_hs, axi_w_hs, axi_b_hs);
    $fatal(1);
end

initial begin
    $dumpfile("/tmp/top_feature_ml_prod_main_host_i2c.vcd");
    $dumpvars(0, tb_top_feature_ml_prod_main_host_i2c);
end

endmodule
