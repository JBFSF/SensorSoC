`timescale 1ns/1ps

module top #(
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

    logic motion_epoch_w;                // strobe: motion_preprocess completed an epoch accumulation
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

    motion_preprocess #(
        .AX_W(16)
    ) u_motion_preprocess (
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

    ppg_beat_detect_rr_calc u_beat_detect (
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
        .cfg_peak_mode_i(1'b0),                 // detection mode select (0=local max)
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
        .rr_interval_i(rr_interval_w),  // RR interval input for HRV calculation
        .rr_valid_i(rr_valid_w),        // strobe: RR interval input valid
        .rr_accepted_i(rr_accepted_w),  // only include accepted RR intervals
        .epoch_end_i(epoch_end_w),      // epoch boundary: finalize RMSSD and reset accumulators
        .rmssd_epoch_o(rmssd_w),        // RMSSD result for epoch
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

    assign epoch_end_o = epoch_end_w;
    assign alarm_o = 1'b0;

endmodule
