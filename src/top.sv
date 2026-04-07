`timescale 1ns/1ps

`include "taketwo_feature_bridge.sv"

module top #(
    parameter int unsigned MEM_WORDS = 1024,
    parameter string       FIRMWARE_HEX = "",
    parameter string       WEIGHT_INIT_HEX = "",

    parameter logic [31:0] PWR_BASE    = 32'h0300_1000,
    parameter logic [31:0] TIMER_BASE  = 32'h0300_2000,
    parameter logic [31:0] ML_BASE     = 32'h0300_3000,
    parameter logic [31:0] FEATURE_BASE= 32'h0300_4000,
    parameter logic [31:0] IRQC_BASE   = 32'h0300_5000,
    parameter logic [31:0] WEIGHT_BASE = 32'h0300_6000,
    parameter logic [31:0] SPI_BASE    = 32'h0300_A000,
    parameter logic [31:0] TEST_BASE   = 32'h0300_F000,

    parameter int unsigned CLK_HZ = 10_000_000,
    parameter int unsigned GT_CLK_HZ = 10_000_000,
    parameter int unsigned GT_EPOCH_HZ = 100,
    parameter int unsigned GT_EPOCH_COUNT_MAX = 1000,

    parameter int unsigned ACC_POLL_PERIOD_TICKS = 50_000,
    parameter int unsigned PPG_POLL_PERIOD_TICKS = 100,
    parameter int unsigned PPG_WATERMARK = 8,
    parameter int unsigned PPG_MAX_BURST_SAMPLES = 32,

    parameter logic [31:0] CFG_REFRACT_MS = 32'd250,
    parameter logic [31:0] CFG_RR_MIN_MS = 32'd300,
    parameter logic [31:0] CFG_RR_MAX_MS = 32'd2000,

    parameter logic [7:0] CFG_Q_MIN_ACCEPT = 8'd10,

    parameter logic [7:0] CFG_BEAT_Q_MIN = 8'd16,
    parameter logic [7:0] CFG_MIN_VALID_FRAC = 8'd96,
    parameter logic [7:0] CFG_MAX_DOUBLE = 8'd4,
    parameter logic [7:0] CFG_MAX_MISSED = 8'd3,
    parameter logic [15:0] CFG_MOTION_HI_TH = 16'd2000,
    parameter logic [15:0] CFG_MAX_MOTION_HI = 16'd3,
    parameter logic [31:0] COS_PERIOD_SECONDS = 32'd86400,
    parameter logic [2:0]  COS_LUT_BITS = 3'd6,
    parameter logic [15:0] COS_SCALE_Q15 = 16'h7FFF,

    parameter int unsigned RMSSD_MIN_RR_COUNT = 1
) (
    input  logic clk_i,
    input  logic reset_i,
    input  logic i2c_scl_i,
    inout  wire  i2c_sda_io,

    // Functional simulation bus to sensor models (through i2c_master).
    output logic        sim_req_o,     // request strobe from i2c_master into simulated sensor bus
    output logic [6:0]  sim_addr_o,    // 7-bit I2C address for the active simulated sensor transaction
    output logic [7:0]  sim_reg_o,     // I2C register address for the active simulated sensor transaction
    output logic [7:0]  sim_len_o,     // number of bytes to read/write for the active simulated sensor transaction
    output logic        sim_write_o,   // 1: write transaction, 0: read transaction
    output logic [7:0]  sim_wdata_o,   // write data byte for the active simulated sensor transaction
    input  logic        sim_ack_i,     // simulated sensor acknowledges/accepts the requested transaction
    input  logic [7:0]  sim_rdata_i,   // read data byte returned by simulated sensor
    input  logic        sim_rvalid_i,  // read data valid strobe from simulated sensor
    input  logic        sim_rlast_i,   // marks last read byte of the transaction from simulated sensor
    input  logic        sim_err_i,     // error indicator from simulated sensor (e.g., NACK/invalid access)

    // Pipeline outputs toward ML
    output logic                      feat_valid_o,     // one-cycle strobe: feature vector is ready for ML consumption
    output logic signed [15:0]        time_feat_o,      // time-of-night feature (cosine LUT output)
    output logic signed [15:0]        motion_feat_o,    // motion feature (per-epoch motion energy)
    output logic signed [15:0]        delta_hr_feat_o,  // delta heart-rate feature derived from RR intervals
    output logic signed [15:0]        rmssd_feat_o,     // HRV feature (RMSSD) for the epoch

    // Signal quality outputs
    output logic                      ml_update_gate_o,  // gate: only update ML when signal-quality checks pass
    output logic [7:0]                invalid_reason_o,  // reason code when ML update is gated off

    // SPI flash interface used by the simulation boot stub.
    output logic                      spi_clk_o,
    output logic                      spi_mosi_o,
    input  logic                      spi_miso_i,
    output logic                      spi_cs_n_o,

    // Epoch pulse for TB orchestration
    output logic                      epoch_end_o,      // epoch boundary pulse (from globaltimer)

    output logic                      alarm_o           // placeholder alarm output (unused in current RTL)
);

    localparam logic [11:0] CFG_LP_BETA_Q10      = 12'd128;
    localparam logic [11:0] CFG_BASE_ALPHA_Q10   = 12'd16;
    localparam logic [23:0] CFG_ENV_DECAY        = 24'd8;
    localparam logic [11:0] CFG_THR_K_Q10        = 12'd512;
    localparam logic [23:0] CFG_THR_MIN          = 24'd32;
    localparam logic [7:0]  CFG_Q_AMP_W          = 8'd4;
    localparam logic [7:0]  CFG_Q_SLOPE_W        = 8'd2;
    localparam logic [7:0]  CFG_Q_REFRAC_PENALTY = 8'd24;

    localparam int unsigned MS_DIV = (CLK_HZ >= 1000) ? (CLK_HZ / 1000) : 1;
    localparam int unsigned MS_DIV_W = (MS_DIV <= 1) ? 1 : $clog2(MS_DIV);

    logic [MS_DIV_W-1:0] ms_div_q;        // clock divider counter for generating a 1ms timebase
    logic [31:0]         time_ms_w;       // millisecond timestamp used by PPG FIFO reader (t_now)

    logic [15:0] seconds_w;              // time-in-night counter from globaltimer (seconds)
    logic epoch_end_w;                   // raw epoch-end pulse from globaltimer
    logic signed [15:0] cos_time_w;      // cosine time feature generated from seconds_w

    logic signed [15:0] ax_w;            // accelerometer X axis sample (signed)
    logic signed [15:0] ay_w;            // accelerometer Y axis sample (signed)
    logic signed [15:0] az_w;            // accelerometer Z axis sample (signed)
    logic accel_valid_w;                 // strobe: new accel sample triple (ax/ay/az) is valid
    logic accel_error_w;                 // sticky flag: accel_reader saw an I2C error
    logic [15:0] motion_inst_mag_w;      // per-sample motion magnitude proxy (|ax|+|ay|+|az|) for signal quality

    logic motion_epoch_w;                // strobe: motion_process completed an epoch accumulation
    logic [47:0] motion_energy_w;        // per-epoch motion energy accumulator output

    logic [15:0] ppg_sample_w;           // raw PPG sample from FIFO reader
    logic ppg_sample_valid_w;            // strobe: ppg_sample_w and ppg_sample_time_w are valid
    logic [31:0] ppg_sample_time_w;      // timestamp (ms) associated with the PPG sample
    logic fifo_overflow_w;               // sticky flag: PPG FIFO overflow detected
    logic fifo_empty_w;                  // status flag: PPG FIFO empty detected during polling
    logic ppg_i2c_err_w;                 // sticky flag: PPG FIFO reader saw an I2C error

    logic beat_pulse_w;                  // one-cycle beat event pulse from beat detector
    logic rr_valid_w;                    // strobe: rr_interval_w is valid
    logic rr_accepted_w;                 // indicates rr_interval_w passed plausibility checks
    logic [31:0] rr_interval_w;          // RR interval (tick domain = ms in this top) between accepted beats
    logic signed [16:0] delta_hr_w;      // delta heart-rate estimate (bpm delta) from beat detector
    logic [7:0] beat_quality_w;          // beat-quality score used by signal_quality gating
    logic double_beat_w;                 // beat detector flagged a double-beat condition
    logic missed_beat_w;                 // beat detector flagged a missed-beat condition
    logic ppg_invalid_w;                 // beat detector flagged invalid PPG stream (unused by top currently)

    logic [31:0] rmssd_w;                // RMSSD value computed for the epoch
    logic rmssd_valid_w;                 // strobe: rmssd_w is valid for this epoch

    logic epoch_end_d;                   // delayed epoch_end_w used to align feature emission timing
    logic fifo_overflow_d;               // previous fifo_overflow_w (for edge detection)
    logic ppg_i2c_err_d;                 // previous ppg_i2c_err_w (for edge detection)
    logic fifo_overflow_event_w;         // one-cycle pulse when FIFO overflow first becomes asserted
    logic ppg_i2c_err_event_w;           // one-cycle pulse when PPG I2C error first becomes asserted

    logic       acc_i2c_cmd_valid_w;     // accel_reader -> i2c_master: command valid
    logic       acc_i2c_cmd_ready_w;     // i2c_master -> accel_reader: command accepted/ready
    logic [6:0] acc_i2c_cmd_addr_w;      // accel_reader -> i2c_master: target 7-bit I2C address
    logic [7:0] acc_i2c_cmd_reg_w;       // accel_reader -> i2c_master: register address
    logic [7:0] acc_i2c_cmd_len_w;       // accel_reader -> i2c_master: read/write length (bytes)
    logic       acc_i2c_cmd_write_w;     // accel_reader -> i2c_master: write enable (1=write, 0=read)
    logic [7:0] acc_i2c_cmd_wdata_w;     // accel_reader -> i2c_master: write data byte
    logic       acc_i2c_rsp_valid_w;     // i2c_master -> accel_reader: response data valid
    logic [7:0] acc_i2c_rsp_data_w;      // i2c_master -> accel_reader: response data byte
    logic       acc_i2c_rsp_done_w;      // i2c_master -> accel_reader: transaction complete
    logic       acc_i2c_rsp_error_w;     // i2c_master -> accel_reader: transaction error (e.g., NACK)

    logic       ppg_i2c_cmd_valid_w;     // ppg_fifo_reader -> i2c_master: command valid
    logic       ppg_i2c_cmd_ready_w;     // i2c_master -> ppg_fifo_reader: command accepted/ready
    logic [6:0] ppg_i2c_cmd_addr_w;      // ppg_fifo_reader -> i2c_master: target 7-bit I2C address
    logic [7:0] ppg_i2c_cmd_reg_w;       // ppg_fifo_reader -> i2c_master: register address
    logic [7:0] ppg_i2c_cmd_len_w;       // ppg_fifo_reader -> i2c_master: read/write length (bytes)
    logic       ppg_i2c_cmd_write_w;     // ppg_fifo_reader -> i2c_master: write enable (1=write, 0=read)
    logic [7:0] ppg_i2c_cmd_wdata_w;     // ppg_fifo_reader -> i2c_master: write data byte
    logic       ppg_i2c_rsp_valid_w;     // i2c_master -> ppg_fifo_reader: response data valid
    logic [7:0] ppg_i2c_rsp_data_w;      // i2c_master -> ppg_fifo_reader: response data byte
    logic       ppg_i2c_rsp_last_w;      // i2c_master -> ppg_fifo_reader: marks last byte of response
    logic       ppg_i2c_rsp_done_w;      // i2c_master -> ppg_fifo_reader: transaction complete
    logic       ppg_i2c_rsp_err_w;       // i2c_master -> ppg_fifo_reader: transaction error (e.g., NACK)
    logic       ppg_i2c_rsp_ready_w;     // ppg_fifo_reader -> i2c_master: ready to accept response stream

    // ---------------------------------------------------------------------
    // Unified SoC/CPU/ML path
    // ---------------------------------------------------------------------
    // `top.sv` is now the single simulation top. The sensor pipeline above
    // produces epoch features, while the logic below provides the CPU-owned
    // SoC path that reads those features, writes them into shared ML memory,
    // and starts the taketwo accelerator.
    reg cpu_clk_en;
    reg cpu_clk_en_lat;
    wire cpu_clk;

    wire        mem_valid;
    wire        mem_instr;
    wire        mem_ready;
    wire [31:0] mem_addr;
    wire [31:0] mem_wdata;
    wire [3:0]  mem_wstrb;
    wire [31:0] mem_rdata;
    wire        trap;
    wire [31:0] irq;

    localparam logic [31:0] STACKADDR      = 4 * MEM_WORDS;
    localparam logic [31:0] PROGADDR_RESET = 32'h0000_0000;
    localparam logic [31:0] PROGADDR_IRQ   = 32'h0000_0010;

    wire bus_valid;
    wire sram_sel;
    wire mmio_sel;
    wire invalid_sel;
    wire pwr_sel;
    wire timer_sel;
    wire ml_sel;
    wire weight_sel;
    wire irqc_sel;
    wire spi_sel;
    wire test_sel;
    wire [31:0] weight_off_sel;

    wire        sram_ready;
    wire [31:0] sram_rdata;

    wire        timer_ready;
    wire [31:0] timer_rdata;
    wire        timer_event;

    wire        pwr_ready;
    wire [31:0] pwr_rdata;
    wire        sleep_req;

    wire        feat_mmio_ready;
    logic [31:0] feat_mmio_rdata;

    wire        ml_ready;
    wire [31:0] ml_rdata;
    wire        ml_irq;

    wire        weight_ready;
    wire [31:0] weight_rdata;

    wire        irqc_ready;
    wire [31:0] irqc_rdata;
    wire        spi_ready;
    wire [31:0] spi_rdata;
    wire        irqc_wake_req;

    wire        test_ready;
    wire [31:0] test_rdata;
    wire [31:0] test_status;
    wire [31:0] test_code;
    wire [31:0] ml_score_hw;

    wire [31:0] ml_saxi_awaddr;
    wire [2:0]  ml_saxi_awprot;
    wire        ml_saxi_awvalid;
    wire        ml_saxi_awready;
    wire [31:0] ml_saxi_wdata;
    wire [3:0]  ml_saxi_wstrb;
    wire        ml_saxi_wvalid;
    wire        ml_saxi_wready;
    wire [1:0]  ml_saxi_bresp;
    wire        ml_saxi_bvalid;
    wire        ml_saxi_bready;
    wire [31:0] ml_saxi_araddr;
    wire [2:0]  ml_saxi_arprot;
    wire        ml_saxi_arvalid;
    wire        ml_saxi_arready;
    wire [31:0] ml_saxi_rdata;
    wire [1:0]  ml_saxi_rresp;
    wire        ml_saxi_rvalid;
    wire        ml_saxi_rready;

    wire [0:0]  wram_awid;
    wire [31:0] wram_awaddr;
    wire [7:0]  wram_awlen;
    wire [2:0]  wram_awsize;
    wire [1:0]  wram_awburst;
    wire [0:0]  wram_awlock;
    wire [3:0]  wram_awcache;
    wire [2:0]  wram_awprot;
    wire [3:0]  wram_awqos;
    wire [1:0]  wram_awuser;
    wire        wram_awvalid;
    wire        wram_awready;
    wire [31:0] wram_wdata;
    wire [3:0]  wram_wstrb;
    wire        wram_wlast;
    wire        wram_wvalid;
    wire        wram_wready;
    wire [0:0]  wram_bid;
    wire [1:0]  wram_bresp;
    wire        wram_bvalid;
    wire        wram_bready;
    wire [0:0]  wram_arid;
    wire [31:0] wram_araddr;
    wire [7:0]  wram_arlen;
    wire [2:0]  wram_arsize;
    wire [1:0]  wram_arburst;
    wire [0:0]  wram_arlock;
    wire [3:0]  wram_arcache;
    wire [2:0]  wram_arprot;
    wire [3:0]  wram_arqos;
    wire [1:0]  wram_aruser;
    wire        wram_arvalid;
    wire        wram_arready;
    wire [0:0]  wram_rid;
    wire [31:0] wram_rdata;
    wire [1:0]  wram_rresp;
    wire        wram_rlast;
    wire        wram_rvalid;
    wire        wram_rready;

    logic       feat_latched_valid_r;
    logic signed [15:0] feat_time_latched_r;
    logic signed [15:0] feat_motion_latched_r;
    logic signed [15:0] feat_delta_hr_latched_r;
    logic signed [15:0] feat_rmssd_latched_r;
    logic       feat_gate_latched_r;
    logic [7:0] feat_invalid_reason_latched_r;
    logic       feat_valid_d;

    // Lightweight feature register bank exposed to firmware. This is the
    // current handoff point between the sensor pipeline and the CPU-owned ML
    // path; firmware reads these latched values and copies them into WEIGHT_BASE.
    wire        feat_sel = mmio_sel && (mem_addr[31:12] == FEATURE_BASE[31:12]);
    wire [31:0] feat_off = mem_addr - FEATURE_BASE;
    wire        feat_wr  = feat_sel && (mem_wstrb != 4'b0000);

    wire [31:0] irq_sources;
    wire [31:0] wake_sources;
    wire        host_i2c_wr_en;
    wire [7:0]  host_i2c_wr_addr;
    wire [7:0]  host_i2c_wr_data;
    wire [7:0]  host_i2c_rd_addr;
    wire [7:0]  host_i2c_rd_data;
    wire        host_i2c_proto_err;
    wire        host_i2c_irq_event;
    wire        host_i2c_irqc_req;
    wire        host_i2c_irqc_we;
    wire [7:0]  host_i2c_irqc_off;
    wire [31:0] host_i2c_irqc_wdata;
    wire        host_i2c_irqc_ready;
    wire [31:0] host_i2c_irqc_rdata;
    wire [31:0] host_cfg_target_wake_sec;
    wire [31:0] host_cfg_window_sec;
    wire [15:0] host_cfg_step_sec;
    wire [15:0] host_cfg_motion_hi_th;
    wire [7:0]  host_cfg_motion_hi_count;
    wire [7:0]  host_cfg_policy;
    wire [15:0] host_cfg_conf_thr;

    always_ff @(posedge clk_i) begin
        if (reset_i) begin
            ms_div_q  <= '0;
            time_ms_w <= 32'd0;
            epoch_end_d <= 1'b0;
            fifo_overflow_d <= 1'b0;
            ppg_i2c_err_d <= 1'b0;
        end else begin
            if (ms_div_q == MS_DIV-1) begin
                ms_div_q  <= '0;
                time_ms_w <= time_ms_w + 32'd1;
            end else begin
                ms_div_q <= ms_div_q + 1'b1;
            end
            epoch_end_d <= epoch_end_w;
            fifo_overflow_d <= fifo_overflow_w;
            ppg_i2c_err_d <= ppg_i2c_err_w;
        end
    end

    // Convert sticky FIFO flags into edge events so one old error does not
    // permanently hold ML gating low across all future epochs.
    assign fifo_overflow_event_w = fifo_overflow_w & ~fifo_overflow_d;
    assign ppg_i2c_err_event_w = ppg_i2c_err_w & ~ppg_i2c_err_d;

    always @(negedge clk_i or posedge reset_i) begin
        if (reset_i)
            cpu_clk_en_lat <= 1'b1;
        else
            cpu_clk_en_lat <= cpu_clk_en;
    end

    assign cpu_clk = clk_i & cpu_clk_en_lat;

    // PicoRV32 remains the owner of ML orchestration in the unified top.
    picorv32 #(
        .STACKADDR(STACKADDR),
        .PROGADDR_RESET(PROGADDR_RESET),
        .PROGADDR_IRQ(PROGADDR_IRQ),
        .BARREL_SHIFTER(1),
        .COMPRESSED_ISA(1),
        .ENABLE_COUNTERS(1),
        .ENABLE_MUL(1),
        .ENABLE_DIV(1),
        .ENABLE_FAST_MUL(0),
        .ENABLE_IRQ(1),
        .ENABLE_IRQ_QREGS(1)
    ) cpu (
        .clk       (cpu_clk),
        .resetn    (~reset_i),
        .mem_valid (mem_valid),
        .mem_instr (mem_instr),
        .mem_ready (mem_ready),
        .mem_addr  (mem_addr),
        .mem_wdata (mem_wdata),
        .mem_wstrb (mem_wstrb),
        .mem_rdata (mem_rdata),
        .irq       (irq),
        .trap      (trap)
    );

    assign bus_valid  = mem_valid && cpu_clk_en_lat;
    assign sram_sel   = bus_valid && (mem_addr < 4 * MEM_WORDS);
    assign mmio_sel   = bus_valid && (mem_addr[31:24] == 8'h03);
    assign invalid_sel = bus_valid && !sram_sel && !mmio_sel;
    assign weight_off_sel = mem_addr - WEIGHT_BASE;
    assign pwr_sel    = mmio_sel && (mem_addr[31:12] == PWR_BASE[31:12]);
    assign timer_sel  = mmio_sel && (mem_addr[31:12] == TIMER_BASE[31:12]);
    assign ml_sel     = mmio_sel && (mem_addr[31:12] == ML_BASE[31:12]);
    assign weight_sel = mmio_sel && (weight_off_sel[31:14] == 18'h0);
    assign irqc_sel   = mmio_sel && (mem_addr[31:12] == IRQC_BASE[31:12]);
    assign spi_sel    = mmio_sel && (mem_addr[31:12] == SPI_BASE[31:12]);
    assign test_sel   = mmio_sel && (mem_addr[31:12] == TEST_BASE[31:12]);

    // Temporary CPU memory backing store for simulation. This is the block
    // planned to be replaced by macro-backed SRAM plus a flash boot path later.
    simple_sram #(
        .WORDS(MEM_WORDS),
        .INIT_HEX(FIRMWARE_HEX)
    ) sram (
        .clk   (cpu_clk),
        .resetn(~reset_i),
        .valid (sram_sel),
        .ready (sram_ready),
        .wstrb (mem_wstrb),
        .addr  (mem_addr),
        .wdata (mem_wdata),
        .rdata (sram_rdata)
    );

    globaltimer #(
        .clk_speed_hz(GT_CLK_HZ),
        .epoch_hz(GT_EPOCH_HZ),
        .epoch_count_max(GT_EPOCH_COUNT_MAX)
    ) u_globaltimer (
        .clk_i(clk_i),
        .rst_i(reset_i),
        .en_i(1'b1),                        // enables the globaltimer (always on in this top)
        .time_in_night_seconds_o(seconds_w), // seconds counter used for time feature generation
        .epoch_end_o(epoch_end_w),           // epoch boundary pulse used to latch per-epoch features
        .epoch_index_o()                    // unused: epoch counter/index
    );

    cos_lut_timer u_cos (
        .clk_i(clk_i),
        .rst_i(reset_i),
        .cfg_enable_i(1'b1),                         // enables time feature output (always on in this top)
        .seconds_in_night_i({16'h0000, seconds_w}),  // seconds input (zero-extended to 32-bit)
        .seconds_valid_i(1'b1),                      // seconds input is always considered valid here
        .cfg_period_seconds_i(COS_PERIOD_SECONDS),   // cosine period (seconds) for time-of-night embedding
        .cfg_lut_bits_i(COS_LUT_BITS),               // LUT resolution control (quantize index)
        .cfg_scale_q15_i(COS_SCALE_Q15),             // output scaling in Q15
        .cos_time_feat_o(cos_time_w)                 // signed cosine feature to feature_engine
    );

    i2c_master u_i2c_master (
        .clk(clk_i),
        .resetn(~reset_i),
        .accel_cmd_valid_i(acc_i2c_cmd_valid_w),   // accel_reader command valid -> I2C master
        .accel_cmd_ready_o(acc_i2c_cmd_ready_w),   // I2C master ready/accept -> accel_reader
        .accel_cmd_addr_i(acc_i2c_cmd_addr_w),     // accel target 7-bit I2C address
        .accel_cmd_reg_i(acc_i2c_cmd_reg_w),       // accel register address
        .accel_cmd_len_i(acc_i2c_cmd_len_w),       // accel transfer length (bytes)
        .accel_cmd_write_i(acc_i2c_cmd_write_w),   // accel command direction (write/read)
        .accel_cmd_wdata_i(acc_i2c_cmd_wdata_w),   // accel write data byte
        .accel_rsp_valid_o(acc_i2c_rsp_valid_w),   // accel response data valid
        .accel_rsp_data_o(acc_i2c_rsp_data_w),     // accel response data byte
        .accel_rsp_last_o(),                       // unused: last byte marker for accel stream
        .accel_rsp_done_o(acc_i2c_rsp_done_w),     // accel transaction done
        .accel_rsp_err_o(acc_i2c_rsp_error_w),     // accel transaction error
        .accel_rsp_ready_i(1'b1),                  // accel_reader always ready (uses done handshake)
        .ppg_cmd_valid_i(ppg_i2c_cmd_valid_w),     // ppg_fifo_reader command valid -> I2C master
        .ppg_cmd_ready_o(ppg_i2c_cmd_ready_w),     // I2C master ready/accept -> ppg_fifo_reader
        .ppg_cmd_addr_i(ppg_i2c_cmd_addr_w),       // PPG target 7-bit I2C address
        .ppg_cmd_reg_i(ppg_i2c_cmd_reg_w),         // PPG register address
        .ppg_cmd_len_i(ppg_i2c_cmd_len_w),         // PPG transfer length (bytes)
        .ppg_cmd_write_i(ppg_i2c_cmd_write_w),     // PPG command direction (write/read)
        .ppg_cmd_wdata_i(ppg_i2c_cmd_wdata_w),     // PPG write data byte
        .ppg_rsp_valid_o(ppg_i2c_rsp_valid_w),     // PPG response data valid
        .ppg_rsp_data_o(ppg_i2c_rsp_data_w),       // PPG response data byte
        .ppg_rsp_last_o(ppg_i2c_rsp_last_w),       // PPG response last-byte marker
        .ppg_rsp_done_o(ppg_i2c_rsp_done_w),       // PPG transaction done
        .ppg_rsp_err_o(ppg_i2c_rsp_err_w),         // PPG transaction error
        .ppg_rsp_ready_i(ppg_i2c_rsp_ready_w),     // backpressure from ppg_fifo_reader during bursts
        .sim_req(sim_req_o),                       // drive sim sensor-bus request (to TB sensor models)
        .sim_addr(sim_addr_o),                     // drive sim sensor-bus device address
        .sim_reg(sim_reg_o),                       // drive sim sensor-bus register address
        .sim_len(sim_len_o),                       // drive sim sensor-bus transfer length
        .sim_write(sim_write_o),                   // drive sim sensor-bus direction
        .sim_wdata(sim_wdata_o),                   // drive sim sensor-bus write data
        .sim_ack(sim_ack_i),                       // receive sim sensor-bus ack from model
        .sim_rdata(sim_rdata_i),                   // receive sim sensor-bus read data from model
        .sim_rvalid(sim_rvalid_i),                 // receive sim sensor-bus read valid strobe
        .sim_rlast(sim_rlast_i),                   // receive sim sensor-bus last-byte marker
        .sim_err(sim_err_i)                        // receive sim sensor-bus error indication
    );

    accel_reader u_accel_reader (
        .clk(clk_i),
        .rst_i(reset_i),
        .cfg_enable_i(1'b1),                     // enables accel polling/reads (always on in this top)
        .cfg_init_en_i(1'b1),                    // enables accel init writes before polling
        .cfg_poll_period_ticks_i(ACC_POLL_PERIOD_TICKS), // poll interval in clk ticks
        .cfg_ctrl1_data_i(8'h57),                // accel CTRL1 init value (ODR/enable axes)
        .cfg_range_data_i(8'h00),                // accel range config init value
        .i2c_cmd_valid_o(acc_i2c_cmd_valid_w),   // command stream to i2c_master (accel)
        .i2c_cmd_ready_i(acc_i2c_cmd_ready_w),   // ready/accept from i2c_master (accel)
        .i2c_cmd_addr_o(acc_i2c_cmd_addr_w),     // I2C address for accel
        .i2c_cmd_reg_o(acc_i2c_cmd_reg_w),       // register address for accel access
        .i2c_cmd_len_o(acc_i2c_cmd_len_w),       // byte length for accel access
        .i2c_cmd_write_o(acc_i2c_cmd_write_w),   // direction for accel access
        .i2c_cmd_wdata_o(acc_i2c_cmd_wdata_w),   // write byte for accel init/config
        .i2c_rsp_valid_i(acc_i2c_rsp_valid_w),   // response byte valid from i2c_master (accel)
        .i2c_rsp_data_i(acc_i2c_rsp_data_w),     // response byte from i2c_master (accel)
        .i2c_rsp_done_i(acc_i2c_rsp_done_w),     // accel transaction completion strobe
        .i2c_rsp_error_i(acc_i2c_rsp_error_w),   // accel transaction error indicator
        .ax_o(ax_w),                             // accel X sample output
        .ay_o(ay_w),                             // accel Y sample output
        .az_o(az_w),                             // accel Z sample output
        .accel_valid_o(accel_valid_w),           // strobe: accel samples are valid
        .init_done_o(),                          // unused: accel init completion
        .i2c_error_o(accel_error_w),             // sticky I2C error flag for accel path
        .timeout_o(),                            // unused: timeout flag
        .nack_seen_o()                           // unused: NACK-seen flag
    );

    motion_process #(
        .AX_W(16)
    ) u_motion_process (
        .clk(clk_i),
        .rst_i(reset_i),
        .sample_valid_i(accel_valid_w),     // drive motion accumulation with each valid accel sample
        // accel_valid_o already indicates a completed good read.
        .sample_ok_i(1'b1),                 // treat all valid samples as OK (no separate quality bit)
        .ax_i(ax_w),                        // accel X input for motion energy
        .ay_i(ay_w),                        // accel Y input for motion energy
        .az_i(az_w),                        // accel Z input for motion energy
        .epoch_end_i(epoch_end_w),          // epoch boundary: latch and clear accumulators
        .epoch_done_o(motion_epoch_w),      // strobe: epoch motion energy is ready
        .motion_energy_epoch_o(motion_energy_w) // per-epoch motion energy output
    );

    // Per-sample motion magnitude for signal-quality high-motion counting.
    assign motion_inst_mag_w =
        (ax_w[15] ? (~ax_w + 16'd1) : ax_w) +
        (ay_w[15] ? (~ay_w + 16'd1) : ay_w) +
        (az_w[15] ? (~az_w + 16'd1) : az_w);

    ppg_fifo_reader #(
        .POLL_PERIOD(PPG_POLL_PERIOD_TICKS),
        .WATERMARK(PPG_WATERMARK),
        .MAX_BURST_SAMPLES(PPG_MAX_BURST_SAMPLES)
    ) u_ppg_fifo_reader (
        .clk_i(clk_i),
        .rst_i(reset_i),
        .t_now(time_ms_w),                      // current timebase (ms) used to timestamp samples
        .i2c_cmd_valid(ppg_i2c_cmd_valid_w),    // command stream to i2c_master (PPG)
        .i2c_cmd_ready(ppg_i2c_cmd_ready_w),    // ready/accept from i2c_master (PPG)
        .i2c_cmd_addr(ppg_i2c_cmd_addr_w),      // I2C address for PPG sensor
        .i2c_cmd_reg(ppg_i2c_cmd_reg_w),        // register address for PPG access (status/FIFO)
        .i2c_cmd_len(ppg_i2c_cmd_len_w),        // number of bytes to read/write on PPG I2C transaction
        .i2c_cmd_write(ppg_i2c_cmd_write_w),    // direction for PPG I2C transaction
        .i2c_cmd_wdata(ppg_i2c_cmd_wdata_w),    // write byte for PPG I2C transaction (when applicable)
        .i2c_rsp_valid(ppg_i2c_rsp_valid_w),    // response byte valid from i2c_master (PPG)
        .i2c_rsp_data(ppg_i2c_rsp_data_w),      // response byte data from i2c_master (PPG)
        .i2c_rsp_last(ppg_i2c_rsp_last_w),      // indicates last response byte of the read burst
        .i2c_rsp_err(ppg_i2c_rsp_err_w),        // transaction error indication from i2c_master
        .i2c_rsp_ready(ppg_i2c_rsp_ready_w),    // backpressure to i2c_master while consuming response bytes
        .ppg_sample(ppg_sample_w),              // unpacked PPG sample stream
        .ppg_sample_valid(ppg_sample_valid_w),  // strobe: PPG sample valid
        .ppg_sample_time(ppg_sample_time_w),    // timestamp associated with each PPG sample
        .fifo_overflow_flag(fifo_overflow_w),   // sticky FIFO overflow flag
        .fifo_empty_flag(fifo_empty_w),         // FIFO empty status flag
        .i2c_error_flag(ppg_i2c_err_w)          // sticky I2C error flag on PPG path
    );

    ppg_process u_beat_detect (
        .clk_i(clk_i),
        .rst_i(reset_i),
        .ppg_sample_i(ppg_sample_w),            // raw PPG sample stream input
        .ppg_valid_i(ppg_sample_valid_w),       // strobe: PPG sample input valid
        .ppg_sample_time_i(ppg_sample_time_w),  // timestamp for RR interval computation
        .cfg_enable_i(1'b1),                    // enables beat detection (always on)
        .cfg_bypass_i(1'b0),                    // do not bypass filtering/logic
        .cfg_signed_i(1'b0),                    // PPG samples treated as unsigned
        .cfg_lp_beta_i(CFG_LP_BETA_Q10),        // low-pass filter coefficient
        .cfg_base_alpha_i(CFG_BASE_ALPHA_Q10),  // baseline EWMA coefficient
        .cfg_env_decay_i(CFG_ENV_DECAY),        // envelope decay parameter
        .cfg_abs_en_i(1'b1),                    // absolute-value enable for signal conditioning
        .cfg_thr_k_i(CFG_THR_K_Q10),            // adaptive threshold gain
        .cfg_thr_min_i(CFG_THR_MIN),            // minimum detection threshold clamp
        .cfg_refrac_ticks_i(CFG_REFRACT_MS),    // refractory time between beats (ms)
        .cfg_rr_min_ticks_i(CFG_RR_MIN_MS),     // minimum plausible RR interval (ms)
        .cfg_rr_max_ticks_i(CFG_RR_MAX_MS),     // maximum plausible RR interval (ms)
        .cfg_q_amp_w_i(CFG_Q_AMP_W),            // beat-quality amplitude weight
        .cfg_q_slope_w_i(CFG_Q_SLOPE_W),        // beat-quality slope weight
        .cfg_q_refrac_penalty_i(CFG_Q_REFRAC_PENALTY), // penalty weight for refractory violations
        .cfg_q_min_accept_i(CFG_Q_MIN_ACCEPT),  // minimum quality to accept RR intervals
        .beat_pulse_o(beat_pulse_w),            // beat event output
        .rr_valid_o(rr_valid_w),                // RR interval valid strobe
        .rr_accepted_o(rr_accepted_w),          // RR interval accepted indicator
        .rr_interval_o(rr_interval_w),          // RR interval output (ms ticks)
        .delta_hr_bpm_o(delta_hr_w),            // delta HR output (bpm delta)
        .beat_quality_o(beat_quality_w),        // beat-quality score output
        .double_beat_o(double_beat_w),          // double-beat flag output
        .missed_beat_o(missed_beat_w),          // missed-beat flag output
        .ppg_invalid_o(ppg_invalid_w)           // invalid PPG indicator output
    );

    rmssd_engine #(
        .MIN_RR_COUNT(RMSSD_MIN_RR_COUNT)
    ) u_rmssd (
        .clk_i(clk_i),
        .rst_i(reset_i),
        .rr_interval_i(rr_interval_w[15:0]),  // RR interval input for HRV calculation
        .rr_valid_i(rr_valid_w),        // strobe: RR interval input valid
        .rr_accepted_i(rr_accepted_w),  // only include accepted RR intervals
        .epoch_end_i(epoch_end_w),      // epoch boundary: finalize RMSSD and reset accumulators
        .rmssd_epoch_o(rmssd_w[15:0]),        // RMSSD result for epoch
        .rmssd_valid_o(rmssd_valid_w),  // strobe: RMSSD output valid
        .rr_diff_count_o()              // unused: number of RR diffs included
    );

    signal_quality u_signal_quality (
        .clk_i(clk_i),
        .rst_i(reset_i),
        .epoch_end_i(epoch_end_w),              // epoch boundary: evaluate signal quality for that epoch
        .beat_event_i(beat_pulse_w),            // beat events counted for valid fraction and anomalies
        .beat_quality_i(beat_quality_w),        // beat-quality score for "good beat" counting
        .double_beat_i(double_beat_w),          // double-beat anomaly indicator
        .missed_beat_i(missed_beat_w),          // missed-beat anomaly indicator
        .fifo_overflow_i(fifo_overflow_event_w), // overflow event (edge) for this epoch
        .fifo_i2c_error_i(ppg_i2c_err_event_w),  // I2C error event (edge) for this epoch
        .motion_valid_i(accel_valid_w),         // strobe: motion sample valid (used to count motion-hi samples)
        .motion_intensity_i(motion_inst_mag_w), // motion intensity proxy for high-motion detection
        .cfg_beat_q_min_i(CFG_BEAT_Q_MIN),      // minimum beat-quality to count as good
        .cfg_min_valid_fraction_i(CFG_MIN_VALID_FRAC), // minimum % of good beats required
        .cfg_max_double_i(CFG_MAX_DOUBLE),      // max allowed double-beat count per epoch
        .cfg_max_missed_i(CFG_MAX_MISSED),      // max allowed missed-beat count per epoch
        .cfg_motion_hi_th_i(CFG_MOTION_HI_TH),  // motion intensity threshold for "high motion"
        .cfg_max_motion_hi_i(CFG_MAX_MOTION_HI), // max allowed "high motion" sample count per epoch
        .invalid_reason_o(invalid_reason_o),    // outputs reason code if invalid
        .ml_update_gate_o(ml_update_gate_o)     // outputs gate controlling ML update at epoch end
    );

    feature_engine u_feature_engine (
        .clk_i(clk_i),
        .rst_i(reset_i),
        .enable_i(epoch_end_d),                 // epoch strobe (delayed) to emit a consolidated feature vector
        .seconds_valid_i(1'b1),                 // time feature treated as always valid here
        .cos_time_feat_i(cos_time_w),           // cosine time feature input
        .motion_valid_i(motion_epoch_w),        // strobe: motion epoch energy is ready
        .motion_energy_epoch_i(motion_energy_w[15:0]), // motion energy (truncated to 16-bit feature)
        .delta_hr_valid_i(rr_valid_w),          // strobe: delta HR feature should update
        .delta_hr_i(delta_hr_w[15:0]),          // delta HR (truncated to 16-bit feature)
        .rmssd_valid_i(rmssd_valid_w),          // strobe: RMSSD feature should update
        .rmssd_i(rmssd_w[15:0]),                // RMSSD (truncated to 16-bit feature)
        .feat_valid_o(feat_valid_o),            // output strobe: features are ready
        .time_feat_o(time_feat_o),              // output time feature to ML
        .motion_feat_o(motion_feat_o),          // output motion feature to ML
        .delta_hr_feat_o(delta_hr_feat_o),      // output delta HR feature to ML
        .rmssd_feat_o(rmssd_feat_o),            // output RMSSD feature to ML
        .ml_update_gate_i(ml_update_gate_o)     // gate emission/update when signal quality is poor
    );

    // Latch the most recent valid feature vector so firmware can consume it
    // through MMIO without racing a one-cycle `feat_valid_o` pulse.
    always_ff @(posedge clk_i) begin
        if (reset_i) begin
            feat_valid_d                 <= 1'b0;
            feat_latched_valid_r          <= 1'b0;
            feat_time_latched_r           <= '0;
            feat_motion_latched_r         <= '0;
            feat_delta_hr_latched_r       <= '0;
            feat_rmssd_latched_r          <= '0;
            feat_gate_latched_r           <= 1'b0;
            feat_invalid_reason_latched_r <= 8'h00;
        end else begin
            // `feat_valid_o` is produced by feature_engine in its own
            // clocked block, so capture a delayed copy here before using it
            // to load the sticky MMIO-visible feature bank.
            feat_valid_d <= feat_valid_o;

            if (feat_valid_o || feat_valid_d) begin
                feat_latched_valid_r          <= 1'b1;
                feat_time_latched_r           <= time_feat_o;
                feat_motion_latched_r         <= motion_feat_o;
                feat_delta_hr_latched_r       <= delta_hr_feat_o;
                feat_rmssd_latched_r          <= rmssd_feat_o;
                feat_gate_latched_r           <= ml_update_gate_o;
                feat_invalid_reason_latched_r <= invalid_reason_o;
            end

            if (feat_wr && (feat_off == 32'h0) && mem_wdata[0])
                feat_latched_valid_r <= 1'b0;
        end
    end

    // Feature MMIO register map:
    //   +0x00 status / clear-valid control
    //   +0x04 time feature
    //   +0x08 motion feature
    //   +0x0C delta-HR feature
    //   +0x10 RMSSD feature
    always @(*) begin
        case (feat_off)
            32'h00: feat_mmio_rdata = {14'd0, feat_gate_latched_r, 8'd0, feat_invalid_reason_latched_r, feat_latched_valid_r};
            32'h04: feat_mmio_rdata = {{16{feat_time_latched_r[15]}}, feat_time_latched_r};
            32'h08: feat_mmio_rdata = {{16{feat_motion_latched_r[15]}}, feat_motion_latched_r};
            32'h0C: feat_mmio_rdata = {{16{feat_delta_hr_latched_r[15]}}, feat_delta_hr_latched_r};
            32'h10: feat_mmio_rdata = {{16{feat_rmssd_latched_r[15]}}, feat_rmssd_latched_r};
            default: feat_mmio_rdata = 32'h0000_0000;
        endcase
    end

    assign feat_mmio_ready = feat_sel;

    // Always-on watchdog timer used by firmware for wake/scheduling.
    timer_mmio #(.BASE_ADDR(TIMER_BASE)) u_timer (
        .clk      (clk_i),
        .resetn   (~reset_i),
        .mem_valid(mmio_sel),
        .mem_addr (mem_addr),
        .mem_wdata(mem_wdata),
        .mem_wstrb(mem_wstrb),
        .mem_ready(timer_ready),
        .mem_rdata(),
        .event_o  (timer_event),
        .rdata_o  (timer_rdata)
    );

    // CPU MMIO -> AXI-Lite bridge into the taketwo control/status port.
    ml_axil_bridge_mmio #(.BASE_ADDR(ML_BASE)) u_ml (
        .clk         (clk_i),
        .resetn      (~reset_i),
        .mem_valid   (mmio_sel),
        .mem_addr    (mem_addr),
        .mem_wdata   (mem_wdata),
        .mem_wstrb   (mem_wstrb),
        .mem_ready   (ml_ready),
        .mem_rdata   (ml_rdata),
        .event_o     (),
        .score_o     (),
        .saxi_awaddr (ml_saxi_awaddr),
        .saxi_awprot (ml_saxi_awprot),
        .saxi_awvalid(ml_saxi_awvalid),
        .saxi_awready(ml_saxi_awready),
        .saxi_wdata  (ml_saxi_wdata),
        .saxi_wstrb  (ml_saxi_wstrb),
        .saxi_wvalid (ml_saxi_wvalid),
        .saxi_wready (ml_saxi_wready),
        .saxi_bresp  (ml_saxi_bresp),
        .saxi_bvalid (ml_saxi_bvalid),
        .saxi_bready (ml_saxi_bready),
        .saxi_araddr (ml_saxi_araddr),
        .saxi_arprot (ml_saxi_arprot),
        .saxi_arvalid(ml_saxi_arvalid),
        .saxi_arready(ml_saxi_arready),
        .saxi_rdata  (ml_saxi_rdata),
        .saxi_rresp  (ml_saxi_rresp),
        .saxi_rvalid (ml_saxi_rvalid),
        .saxi_rready (ml_saxi_rready)
    );

    // ML accelerator instance. Firmware talks to it through u_ml above,
    // and the core reads/writes its working set through weight_ram_axi below.
    taketwo_wrap u_taketwo_wrap (
        .CLK   (clk_i),
        .RESETN(~reset_i),
        .irq   (ml_irq),
        .maxi_awid   (wram_awid),
        .maxi_awaddr (wram_awaddr),
        .maxi_awlen  (wram_awlen),
        .maxi_awsize (wram_awsize),
        .maxi_awburst(wram_awburst),
        .maxi_awlock (wram_awlock),
        .maxi_awcache(wram_awcache),
        .maxi_awprot (wram_awprot),
        .maxi_awqos  (wram_awqos),
        .maxi_awuser (wram_awuser),
        .maxi_awvalid(wram_awvalid),
        .maxi_awready(wram_awready),
        .maxi_wdata  (wram_wdata),
        .maxi_wstrb  (wram_wstrb),
        .maxi_wlast  (wram_wlast),
        .maxi_wvalid (wram_wvalid),
        .maxi_wready (wram_wready),
        .maxi_bid    (wram_bid),
        .maxi_bresp  (wram_bresp),
        .maxi_bvalid (wram_bvalid),
        .maxi_bready (wram_bready),
        .maxi_arid   (wram_arid),
        .maxi_araddr (wram_araddr),
        .maxi_arlen  (wram_arlen),
        .maxi_arsize (wram_arsize),
        .maxi_arburst(wram_arburst),
        .maxi_arlock (wram_arlock),
        .maxi_arcache(wram_arcache),
        .maxi_arprot (wram_arprot),
        .maxi_arqos  (wram_arqos),
        .maxi_aruser (wram_aruser),
        .maxi_arvalid(wram_arvalid),
        .maxi_arready(wram_arready),
        .maxi_rid    (wram_rid),
        .maxi_rdata  (wram_rdata),
        .maxi_rresp  (wram_rresp),
        .maxi_rlast  (wram_rlast),
        .maxi_rvalid (wram_rvalid),
        .maxi_rready (wram_rready),
        .saxi_awaddr (ml_saxi_awaddr),
        .saxi_awprot (ml_saxi_awprot),
        .saxi_awvalid(ml_saxi_awvalid),
        .saxi_awready(ml_saxi_awready),
        .saxi_wdata  (ml_saxi_wdata),
        .saxi_wstrb  (ml_saxi_wstrb),
        .saxi_wvalid (ml_saxi_wvalid),
        .saxi_wready (ml_saxi_wready),
        .saxi_bresp  (ml_saxi_bresp),
        .saxi_bvalid (ml_saxi_bvalid),
        .saxi_bready (ml_saxi_bready),
        .saxi_araddr (ml_saxi_araddr),
        .saxi_arprot (ml_saxi_arprot),
        .saxi_arvalid(ml_saxi_arvalid),
        .saxi_arready(ml_saxi_arready),
        .saxi_rdata  (ml_saxi_rdata),
        .saxi_rresp  (ml_saxi_rresp),
        .saxi_rvalid (ml_saxi_rvalid),
        .saxi_rready (ml_saxi_rready)
    );

    // Shared ML memory. Firmware writes inputs/weights through MMIO, while
    // taketwo accesses the same storage through its AXI master interface.
    weight_ram_axi #(
        .WORDS          (4096),
        .BASE_ADDR      (WEIGHT_BASE),
        .WEIGHT_INIT_HEX(WEIGHT_INIT_HEX)
    ) u_weight_ram (
        .clk         (clk_i),
        .resetn      (~reset_i),
        .mem_valid   (mmio_sel),
        .mem_addr    (mem_addr),
        .mem_wdata   (mem_wdata),
        .mem_wstrb   (mem_wstrb),
        .mem_ready   (weight_ready),
        .mem_rdata   (weight_rdata),
        .saxi_awid   (wram_awid),
        .saxi_awaddr (wram_awaddr),
        .saxi_awlen  (wram_awlen),
        .saxi_awsize (wram_awsize),
        .saxi_awburst(wram_awburst),
        .saxi_awlock (wram_awlock),
        .saxi_awcache(wram_awcache),
        .saxi_awprot (wram_awprot),
        .saxi_awqos  (wram_awqos),
        .saxi_awuser (wram_awuser),
        .saxi_awvalid(wram_awvalid),
        .saxi_awready(wram_awready),
        .saxi_wdata  (wram_wdata),
        .saxi_wstrb  (wram_wstrb),
        .saxi_wlast  (wram_wlast),
        .saxi_wvalid (wram_wvalid),
        .saxi_wready (wram_wready),
        .saxi_bid    (wram_bid),
        .saxi_bresp  (wram_bresp),
        .saxi_bvalid (wram_bvalid),
        .saxi_bready (wram_bready),
        .saxi_arid   (wram_arid),
        .saxi_araddr (wram_araddr),
        .saxi_arlen  (wram_arlen),
        .saxi_arsize (wram_arsize),
        .saxi_arburst(wram_arburst),
        .saxi_arlock (wram_arlock),
        .saxi_arcache(wram_arcache),
        .saxi_arprot (wram_arprot),
        .saxi_arqos  (wram_arqos),
        .saxi_aruser (wram_aruser),
        .saxi_arvalid(wram_arvalid),
        .saxi_arready(wram_arready),
        .saxi_rid    (wram_rid),
        .saxi_rdata  (wram_rdata),
        .saxi_rresp  (wram_rresp),
        .saxi_rlast  (wram_rlast),
        .saxi_rvalid (wram_rvalid),
        .saxi_rready (wram_rready)
    );

    // CPU-driven SPI master used by the simulation boot stub to stream
    // taketwo weights from external flash into shared WRAM.
    spi_master_mmio #(.BASE_ADDR(SPI_BASE)) u_spi (
        .clk       (clk_i),
        .resetn    (~reset_i),
        .mem_valid (mmio_sel),
        .mem_addr  (mem_addr),
        .mem_wdata (mem_wdata),
        .mem_wstrb (mem_wstrb),
        .mem_ready (spi_ready),
        .mem_rdata (spi_rdata),
        .spi_clk_o (spi_clk_o),
        .spi_mosi_o(spi_mosi_o),
        .spi_miso_i(spi_miso_i),
        .spi_cs_n_o(spi_cs_n_o)
    );

    // Off-chip host I2C target bridge in the always-on domain. This mirrors
    // soc_top so the unified top can participate in end-to-end host config and
    // score visibility tests without changing production firmware.
    host_i2c_target #(
        .SLAVE_ADDR(7'h42)
    ) u_host_i2c_target (
        .clk        (clk_i),
        .resetn     (~reset_i),
        .i2c_scl_i  (i2c_scl_i),
        .i2c_sda_io (i2c_sda_io),
        .wr_en_o    (host_i2c_wr_en),
        .wr_addr_o  (host_i2c_wr_addr),
        .wr_data_o  (host_i2c_wr_data),
        .rd_addr_o  (host_i2c_rd_addr),
        .rd_data_i  (host_i2c_rd_data),
        .proto_err_o(host_i2c_proto_err)
    );

    host_i2c_bridge_regs u_host_i2c_bridge_regs (
        .clk                  (clk_i),
        .resetn               (~reset_i),
        .wr_en_i              (host_i2c_wr_en),
        .wr_addr_i            (host_i2c_wr_addr),
        .wr_data_i            (host_i2c_wr_data),
        .rd_addr_i            (host_i2c_rd_addr),
        .rd_data_o            (host_i2c_rd_data),
        .proto_err_i          (host_i2c_proto_err),
        .ml_score_i           (ml_score_hw),
        .event_o              (host_i2c_irq_event),
        .cfg_target_wake_sec_o(host_cfg_target_wake_sec),
        .cfg_window_sec_o     (host_cfg_window_sec),
        .cfg_step_sec_o       (host_cfg_step_sec),
        .cfg_motion_hi_th_o   (host_cfg_motion_hi_th),
        .cfg_motion_hi_count_o(host_cfg_motion_hi_count),
        .cfg_policy_o         (host_cfg_policy),
        .cfg_conf_thr_o       (host_cfg_conf_thr),
        .irqc_req_o           (host_i2c_irqc_req),
        .irqc_we_o            (host_i2c_irqc_we),
        .irqc_off_o           (host_i2c_irqc_off),
        .irqc_wdata_o         (host_i2c_irqc_wdata),
        .irqc_ready_i         (host_i2c_irqc_ready),
        .irqc_rdata_i         (host_i2c_irqc_rdata)
    );

    assign irq_sources = {29'b0, host_i2c_irq_event, ml_irq, timer_event};
    assign wake_sources = irq_sources;

    // Minimal interrupt controller used for CPU-visible pending bits and wake.
    irq_ctrl_mmio #(.BASE_ADDR(IRQC_BASE)) u_irqc (
        .clk        (clk_i),
        .resetn     (~reset_i),
        .mem_valid  (mmio_sel),
        .mem_addr   (mem_addr),
        .mem_wdata  (mem_wdata),
        .mem_wstrb  (mem_wstrb),
        .mem_ready  (irqc_ready),
        .mem_rdata  (irqc_rdata),
        .host_req_i (host_i2c_irqc_req),
        .host_we_i  (host_i2c_irqc_we),
        .host_off_i (host_i2c_irqc_off),
        .host_wdata_i(host_i2c_irqc_wdata),
        .host_ready_o(host_i2c_irqc_ready),
        .host_rdata_o(host_i2c_irqc_rdata),
        .irq_src_i  (irq_sources),
        .irq_o      (irq),
        .wake_req_o (irqc_wake_req)
    );

    // Power/sleep control block.
    pwrctrl_mmio #(.BASE_ADDR(PWR_BASE)) u_pwr (
        .clk        (clk_i),
        .resetn     (~reset_i),
        .mem_valid  (mmio_sel),
        .mem_addr   (mem_addr),
        .mem_wdata  (mem_wdata),
        .mem_wstrb  (mem_wstrb),
        .mem_ready  (pwr_ready),
        .mem_rdata  (pwr_rdata),
        .sleep_req_o(sleep_req),
        .wake_src_i (wake_sources),
        .cpu_awake_i(cpu_clk_en_lat)
    );

    // Simulation/debug mailbox for firmware-driven status and result reporting.
    test_mmio #(.BASE_ADDR(TEST_BASE)) u_test (
        .clk(clk_i),
        .resetn(~reset_i),
        .mem_valid(mmio_sel),
        .mem_addr(mem_addr),
        .mem_wdata(mem_wdata),
        .mem_wstrb(mem_wstrb),
        .cfg_target_wake_sec_i(host_cfg_target_wake_sec),
        .cfg_window_sec_i(host_cfg_window_sec),
        .cfg_step_sec_i(host_cfg_step_sec),
        .cfg_motion_hi_th_i(host_cfg_motion_hi_th),
        .cfg_motion_hi_count_i(host_cfg_motion_hi_count),
        .cfg_policy_i(host_cfg_policy),
        .cfg_conf_thr_i(host_cfg_conf_thr),
        .mem_ready(test_ready),
        .mem_rdata(test_rdata),
        .status_o(test_status),
        .code_o(test_code),
        .score_o(ml_score_hw)
    );

    // MMIO response mux
    wire mmio_ready =
        (pwr_sel && pwr_ready) |
        (timer_sel && timer_ready) |
        (ml_sel && ml_ready) |
        (weight_sel && weight_ready) |
        (irqc_sel && irqc_ready) |
        (spi_sel && spi_ready) |
        (test_sel && test_ready) |
        feat_mmio_ready;
    wire [31:0] mmio_rdata =
        (pwr_sel && pwr_ready)        ? pwr_rdata      :
        (timer_sel && timer_ready)    ? timer_rdata    :
        (ml_sel && ml_ready)          ? ml_rdata       :
        (weight_sel && weight_ready)  ? weight_rdata   :
        (irqc_sel && irqc_ready)      ? irqc_rdata     :
        (spi_sel && spi_ready)        ? spi_rdata      :
        (test_sel && test_ready)      ? test_rdata     :
        feat_mmio_ready? feat_mmio_rdata:
        32'h0000_0000;

    assign mem_ready = sram_ready | mmio_ready | invalid_sel;
    assign mem_rdata = sram_ready ? sram_rdata :
                       mmio_ready ? mmio_rdata :
                       32'h0000_0000;

    // Sleep/wake control copied from soc_top.
    reg sleeping_r;
    reg cpu_idle_seen_r;
    reg sleep_req_d_r;
    reg [31:0] wake_sources_d_r;
    wire [31:0] wake_rise_w = wake_sources & ~wake_sources_d_r;
    wire        wake_event_w = |wake_rise_w;
    wire        sleep_req_rise_w = sleep_req & ~sleep_req_d_r;

    always_ff @(posedge clk_i) begin
        if (reset_i)
            wake_sources_d_r <= 32'h0;
        else
            wake_sources_d_r <= wake_sources;
    end

    always_ff @(posedge clk_i) begin
        if (reset_i) begin
            cpu_clk_en    <= 1'b1;
            sleeping_r    <= 1'b0;
            cpu_idle_seen_r <= 1'b0;
            sleep_req_d_r <= 1'b0;
        end else begin
            sleep_req_d_r <= sleep_req;

            if (cpu_clk_en && sleep_req_rise_w)
                cpu_idle_seen_r <= 1'b0;
            else if (cpu_clk_en)
                cpu_idle_seen_r <= cpu_idle_seen_r | (~mem_valid);

            if (sleeping_r) begin
                if (irqc_wake_req || wake_event_w) begin
                    cpu_clk_en      <= 1'b1;
                    sleeping_r      <= 1'b0;
                    cpu_idle_seen_r <= 1'b0;
                end
            end else begin
                if (sleep_req && cpu_idle_seen_r && !(irqc_wake_req || wake_event_w)) begin
                    cpu_clk_en      <= 1'b0;
                    sleeping_r      <= 1'b1;
                    cpu_idle_seen_r <= 1'b0;
                end
            end
        end
    end

    // ---------------------------------------------------------------------
    // Legacy local bridge path kept commented out temporarily during merge.
    // ---------------------------------------------------------------------
    /*
    // axi wires 
    logic [31:0] axi_x_addr_w;       // destination address for feature writes (placeholder)
    logic        axi_done_w;         // one-cycle pulse when writes complete
    logic        axi_busy_w;         // high while writes are in progress

    logic [31:0] maxi_awaddr_w;
    logic [7:0]  maxi_awlen_w;
    logic [2:0]  maxi_awsize_w;
    logic [1:0]  maxi_awburst_w;
    logic        maxi_awlock_w;
    logic [3:0]  maxi_awcache_w;
    logic [2:0]  maxi_awprot_w;
    logic [3:0]  maxi_awqos_w;
    logic [1:0]  maxi_awuser_w;
    logic        maxi_awvalid_w;
    logic        maxi_awready_w;

    logic [31:0] maxi_wdata_w;
    logic [3:0]  maxi_wstrb_w;
    logic        maxi_wlast_w;
    logic        maxi_wvalid_w;
    logic        maxi_wready_w;

    logic [1:0]  maxi_bresp_w;
    logic        maxi_bvalid_w;
    logic        maxi_bready_w;

    logic        taketwo_irq_w;
    logic [31:0] tk_maxi_awaddr_w;
    logic [7:0]  tk_maxi_awlen_w;
    logic [2:0]  tk_maxi_awsize_w;
    logic [1:0]  tk_maxi_awburst_w;
    logic        tk_maxi_awlock_w;
    logic [3:0]  tk_maxi_awcache_w;
    logic [2:0]  tk_maxi_awprot_w;
    logic [3:0]  tk_maxi_awqos_w;
    logic [1:0]  tk_maxi_awuser_w;
    logic        tk_maxi_awvalid_w;
    logic        tk_maxi_awready_w;

    logic [31:0] tk_maxi_wdata_w;
    logic [3:0]  tk_maxi_wstrb_w;
    logic        tk_maxi_wlast_w;
    logic        tk_maxi_wvalid_w;
    logic        tk_maxi_wready_w;

    logic [1:0]  tk_maxi_bresp_w;
    logic        tk_maxi_bvalid_w;
    logic        tk_maxi_bready_w;

    logic [31:0] tk_maxi_araddr_w;
    logic [7:0]  tk_maxi_arlen_w;
    logic [2:0]  tk_maxi_arsize_w;
    logic [1:0]  tk_maxi_arburst_w;
    logic        tk_maxi_arlock_w;
    logic [3:0]  tk_maxi_arcache_w;
    logic [2:0]  tk_maxi_arprot_w;
    logic [3:0]  tk_maxi_arqos_w;
    logic [1:0]  tk_maxi_aruser_w;
    logic        tk_maxi_arvalid_w;
    logic        tk_maxi_arready_w;
    logic [31:0] tk_maxi_rdata_w;
    logic [1:0]  tk_maxi_rresp_w;
    logic        tk_maxi_rlast_w;
    logic        tk_maxi_rvalid_w;
    logic        tk_maxi_rready_w;

    logic [31:0] tk_saxi_awaddr_w;
    logic [3:0]  tk_saxi_awcache_w;
    logic [2:0]  tk_saxi_awprot_w;
    logic        tk_saxi_awvalid_w;
    wire         tk_saxi_awready_w;
    logic [31:0] tk_saxi_wdata_w;
    logic [3:0]  tk_saxi_wstrb_w;
    logic        tk_saxi_wvalid_w;
    wire         tk_saxi_wready_w;
    wire [1:0]   tk_saxi_bresp_w;
    wire         tk_saxi_bvalid_w;
    logic        tk_saxi_bready_w;
    logic [31:0] tk_saxi_araddr_w;
    logic [3:0]  tk_saxi_arcache_w;
    logic [2:0]  tk_saxi_arprot_w;
    logic        tk_saxi_arvalid_w;
    wire         tk_saxi_arready_w;
    wire [31:0]  tk_saxi_rdata_w;
    wire [1:0]   tk_saxi_rresp_w;
    wire         tk_saxi_rvalid_w;
    logic        tk_saxi_rready_w;

    logic [31:0] tk_shared_mem [16:17];
    taketwo_feature_bridge u_taketwo_feature_bridge (
        .clk_i            (clk_i),
        .reset_i          (reset_i),
        .axi_x_addr_o     (axi_x_addr_w),
        .maxi_awready_o   (maxi_awready_w),
        .maxi_wready_o    (maxi_wready_w),
        .maxi_bresp_o     (maxi_bresp_w),
        .maxi_bvalid_o    (maxi_bvalid_w),
        .maxi_awvalid_i   (maxi_awvalid_w),
        .maxi_awaddr_i    (maxi_awaddr_w),
        .maxi_wvalid_i    (maxi_wvalid_w),
        .maxi_wdata_i     (maxi_wdata_w),
        .maxi_wstrb_i     (maxi_wstrb_w),
        .maxi_bready_i    (maxi_bready_w),
        .tk_maxi_awready_o(tk_maxi_awready_w),
        .tk_maxi_wready_o (tk_maxi_wready_w),
        .tk_maxi_bresp_o  (tk_maxi_bresp_w),
        .tk_maxi_bvalid_o (tk_maxi_bvalid_w),
        .tk_maxi_awvalid_i(tk_maxi_awvalid_w),
        .tk_maxi_awaddr_i (tk_maxi_awaddr_w),
        .tk_maxi_awlen_i  (tk_maxi_awlen_w),
        .tk_maxi_awsize_i (tk_maxi_awsize_w),
        .tk_maxi_awburst_i(tk_maxi_awburst_w),
        .tk_maxi_wvalid_i (tk_maxi_wvalid_w),
        .tk_maxi_wdata_i  (tk_maxi_wdata_w),
        .tk_maxi_wstrb_i  (tk_maxi_wstrb_w),
        .tk_maxi_wlast_i  (tk_maxi_wlast_w),
        .tk_maxi_bready_i (tk_maxi_bready_w),
        .tk_maxi_arready_o(tk_maxi_arready_w),
        .tk_maxi_rdata_o  (tk_maxi_rdata_w),
        .tk_maxi_rresp_o  (tk_maxi_rresp_w),
        .tk_maxi_rlast_o  (tk_maxi_rlast_w),
        .tk_maxi_rvalid_o (tk_maxi_rvalid_w),
        .tk_maxi_arvalid_i(tk_maxi_arvalid_w),
        .tk_maxi_araddr_i (tk_maxi_araddr_w),
        .tk_maxi_arlen_i  (tk_maxi_arlen_w),
        .tk_maxi_arsize_i (tk_maxi_arsize_w),
        .tk_maxi_arburst_i(tk_maxi_arburst_w),
        .tk_maxi_rready_i (tk_maxi_rready_w),
        .tk_saxi_awcache_o(tk_saxi_awcache_w),
        .tk_saxi_awprot_o (tk_saxi_awprot_w),
        .tk_saxi_awvalid_o(tk_saxi_awvalid_w),
        .tk_saxi_awready_i(tk_saxi_awready_w),
        .tk_saxi_awaddr_o (tk_saxi_awaddr_w),
        .tk_saxi_wdata_o  (tk_saxi_wdata_w),
        .tk_saxi_wstrb_o  (tk_saxi_wstrb_w),
        .tk_saxi_wvalid_o (tk_saxi_wvalid_w),
        .tk_saxi_wready_i (tk_saxi_wready_w),
        .tk_saxi_bresp_i  (tk_saxi_bresp_w),
        .tk_saxi_bvalid_i (tk_saxi_bvalid_w),
        .tk_saxi_bready_o (tk_saxi_bready_w),
        .tk_saxi_arcache_o(tk_saxi_arcache_w),
        .tk_saxi_arprot_o (tk_saxi_arprot_w),
        .tk_saxi_arvalid_o(tk_saxi_arvalid_w),
        .tk_saxi_araddr_o (tk_saxi_araddr_w),
        .tk_saxi_arready_i(tk_saxi_arready_w),
        .tk_saxi_rdata_i  (tk_saxi_rdata_w),
        .tk_saxi_rresp_i  (tk_saxi_rresp_w),
        .tk_saxi_rvalid_i (tk_saxi_rvalid_w),
        .tk_saxi_rready_o (tk_saxi_rready_w),
        .axi_done_i       (axi_done_w),
        .feature_word0_o  (tk_shared_mem[16]),
        .feature_word1_o  (tk_shared_mem[17])
    );

    axi_interface u_axi_interface (
        .CLK         (clk_i),
        .RESETN      (~reset_i),

        .start       (feat_valid_o),
        .x_addr      (axi_x_addr_w),

        .x0          (motion_feat_o),       // movement
        .x1          (time_feat_o),         // cosine time feature
        .x2          (delta_hr_feat_o),     // delta HR
        .x3          (rmssd_feat_o),        // RMSSD

        .done        (axi_done_w),
        .busy        (axi_busy_w),

        .maxi_awaddr (maxi_awaddr_w),
        .maxi_awlen  (maxi_awlen_w),
        .maxi_awsize (maxi_awsize_w),
        .maxi_awburst(maxi_awburst_w),
        .maxi_awlock (maxi_awlock_w),
        .maxi_awcache(maxi_awcache_w),
        .maxi_awprot (maxi_awprot_w),
        .maxi_awqos  (maxi_awqos_w),
        .maxi_awuser (maxi_awuser_w),
        .maxi_awvalid(maxi_awvalid_w),
        .maxi_awready(maxi_awready_w),

        // AXI4 write data channel.
        .maxi_wdata  (maxi_wdata_w),
        .maxi_wstrb  (maxi_wstrb_w),
        .maxi_wlast  (maxi_wlast_w),
        .maxi_wvalid (maxi_wvalid_w),
        .maxi_wready (maxi_wready_w),

        // AXI4 write response channel.
        .maxi_bresp  (maxi_bresp_w),
        .maxi_bvalid (maxi_bvalid_w),
        .maxi_bready (maxi_bready_w)
    );

    taketwo u_taketwo (
        .CLK         (clk_i),
        .RESETN      (~reset_i),
        .irq         (taketwo_irq_w),
        .maxi_awaddr (tk_maxi_awaddr_w),
        .maxi_awlen  (tk_maxi_awlen_w),
        .maxi_awsize (tk_maxi_awsize_w),
        .maxi_awburst(tk_maxi_awburst_w),
        .maxi_awlock (tk_maxi_awlock_w),
        .maxi_awcache(tk_maxi_awcache_w),
        .maxi_awprot (tk_maxi_awprot_w),
        .maxi_awqos  (tk_maxi_awqos_w),
        .maxi_awuser (tk_maxi_awuser_w),
        .maxi_awvalid(tk_maxi_awvalid_w),
        .maxi_awready(tk_maxi_awready_w),
        .maxi_wdata  (tk_maxi_wdata_w),
        .maxi_wstrb  (tk_maxi_wstrb_w),
        .maxi_wlast  (tk_maxi_wlast_w),
        .maxi_wvalid (tk_maxi_wvalid_w),
        .maxi_wready (tk_maxi_wready_w),
        .maxi_bresp  (tk_maxi_bresp_w),
        .maxi_bvalid (tk_maxi_bvalid_w),
        .maxi_bready (tk_maxi_bready_w),
        .maxi_araddr (tk_maxi_araddr_w),
        .maxi_arlen  (tk_maxi_arlen_w),
        .maxi_arsize (tk_maxi_arsize_w),
        .maxi_arburst(tk_maxi_arburst_w),
        .maxi_arlock (tk_maxi_arlock_w),
        .maxi_arcache(tk_maxi_arcache_w),
        .maxi_arprot (tk_maxi_arprot_w),
        .maxi_arqos  (tk_maxi_arqos_w),
        .maxi_aruser (tk_maxi_aruser_w),
        .maxi_arvalid(tk_maxi_arvalid_w),
        .maxi_arready(tk_maxi_arready_w),
        .maxi_rdata  (tk_maxi_rdata_w),
        .maxi_rresp  (tk_maxi_rresp_w),
        .maxi_rlast  (tk_maxi_rlast_w),
        .maxi_rvalid (tk_maxi_rvalid_w),
        .maxi_rready (tk_maxi_rready_w),
        .saxi_awaddr (tk_saxi_awaddr_w),
        .saxi_awcache(tk_saxi_awcache_w),
        .saxi_awprot (tk_saxi_awprot_w),
        .saxi_awvalid(tk_saxi_awvalid_w),
        .saxi_awready(tk_saxi_awready_w),
        .saxi_wdata  (tk_saxi_wdata_w),
        .saxi_wstrb  (tk_saxi_wstrb_w),
        .saxi_wvalid (tk_saxi_wvalid_w),
        .saxi_wready (tk_saxi_wready_w),
        .saxi_bresp  (tk_saxi_bresp_w),
        .saxi_bvalid (tk_saxi_bvalid_w),
        .saxi_bready (tk_saxi_bready_w),
        .saxi_araddr (tk_saxi_araddr_w),
        .saxi_arcache(tk_saxi_arcache_w),
        .saxi_arprot (tk_saxi_arprot_w),
        .saxi_arvalid(tk_saxi_arvalid_w),
        .saxi_arready(tk_saxi_arready_w),
        .saxi_rdata  (tk_saxi_rdata_w),
        .saxi_rresp  (tk_saxi_rresp_w),
        .saxi_rvalid (tk_saxi_rvalid_w),
        .saxi_rready (tk_saxi_rready_w)
    );
    */

    assign epoch_end_o = epoch_end_w;
    assign alarm_o = 1'b0;

endmodule
