`timescale 1ns/1ps

module sim_top_sensor_pipeline;

  logic clk = 1'b0;
  logic reset = 1'b1;

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

  wire                      feat_valid_o;
  wire signed [15:0]        time_feat_o;
  wire signed [15:0]        motion_feat_o;
  wire signed [15:0]        delta_hr_feat_o;
  wire signed [15:0]        mssd_feat_o;
  wire                      ml_update_gate_o;
  wire [7:0]                invalid_reason_o;
  wire                      epoch_end_o;
  wire                      alarm;

  wire signed [15:0]        ax_w;
  wire signed [15:0]        ay_w;
  wire signed [15:0]        az_w;
  wire                      accel_valid_w;
  wire [15:0]               motion_inst_mag_w;
  wire                      motion_epoch_w;
  wire [47:0]               motion_energy_w;
  wire [15:0]               ppg_sample_w;
  wire                      ppg_sample_valid_w;
  wire [31:0]               ppg_sample_time_w;
  wire                      beat_pulse_w;
  wire                      rr_valid_w;
  wire                      rr_accepted_w;
  wire [31:0]               rr_interval_w;
  wire signed [16:0]        delta_hr_w;
  wire [7:0]                beat_quality_w;
  wire                      double_beat_w;
  wire                      missed_beat_w;
  wire                      ppg_invalid_w;
  wire [15:0]               mssd_w;
  wire                      mssd_valid_w;
  wire                      fifo_overflow_event_w;
  wire                      ppg_i2c_err_event_w;
  wire [15:0]               seconds_w;
  wire                      epoch_end_w;
  wire                      epoch_end_d;

  localparam [6:0] ACC_ADDR = 7'h19;
  localparam [6:0] PPG_ADDR = 7'h64;

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
  ) u_dut (
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
    .feat_valid_o(feat_valid_o),
    .time_feat_o(time_feat_o),
    .motion_feat_o(motion_feat_o),
    .delta_hr_feat_o(delta_hr_feat_o),
    .mssd_feat_o(mssd_feat_o),
    .ml_update_gate_o(ml_update_gate_o),
    .invalid_reason_o(invalid_reason_o),
    .epoch_end_o(epoch_end_o),
    .alarm_o(alarm),
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

  assign ax_w = u_dut.ax_w;
  assign ay_w = u_dut.ay_w;
  assign az_w = u_dut.az_w;
  assign accel_valid_w = u_dut.accel_valid_w;
  assign motion_inst_mag_w = u_dut.motion_inst_mag_w;
  assign motion_epoch_w = u_dut.motion_epoch_w;
  assign motion_energy_w = u_dut.motion_energy_w;
  assign ppg_sample_w = u_dut.ppg_sample_w;
  assign ppg_sample_valid_w = u_dut.ppg_sample_valid_w;
  assign ppg_sample_time_w = u_dut.ppg_sample_time_w;
  assign beat_pulse_w = u_dut.beat_pulse_w;
  assign rr_valid_w = u_dut.rr_valid_w;
  assign rr_accepted_w = u_dut.rr_accepted_w;
  assign rr_interval_w = u_dut.rr_interval_w;
  assign delta_hr_w = u_dut.delta_hr_w;
  assign beat_quality_w = u_dut.beat_quality_w;
  assign double_beat_w = u_dut.double_beat_w;
  assign missed_beat_w = u_dut.missed_beat_w;
  assign ppg_invalid_w = u_dut.ppg_invalid_w;
  assign mssd_w = u_dut.mssd_w[15:0];
  assign mssd_valid_w = u_dut.mssd_valid_w;
  assign fifo_overflow_event_w = u_dut.fifo_overflow_event_w;
  assign ppg_i2c_err_event_w = u_dut.ppg_i2c_err_event_w;
  assign seconds_w = u_dut.seconds_w;
  assign epoch_end_w = u_dut.epoch_end_w;
  assign epoch_end_d = u_dut.epoch_end_d;

  initial begin
    $dumpfile("top_sensor_pipeline.vcd");
    $dumpvars(0, u_dut);
  end

endmodule
