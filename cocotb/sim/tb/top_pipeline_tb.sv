`timescale 1ns/1ps

module top_pipeline_tb;

  logic clk = 1'b0;
  logic reset = 1'b1;

  // top <-> functional sensor bus
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

  // top outputs
  wire                      feat_valid;
  wire signed [15:0]        time_feat;
  wire signed [15:0]        motion_feat;
  wire signed [15:0]        delta_hr_feat;
  wire signed [15:0]        rmssd_feat;
  wire                      ml_update_gate;
  wire [7:0]                invalid_reason;
  wire                      epoch_end;
  wire                      alarm;

  // accel slave wires
  wire        accel_sim_ack;
  wire [7:0]  accel_sim_rdata;
  wire        accel_sim_rvalid;
  wire        accel_sim_rlast;
  wire        accel_sim_err;

  // ppg slave wires
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
    .alarm_o(alarm)
  );

  assign host_i2c_scl = 1'b1;

  i2c_slave_lis2dw12 #(
    .I2C_ADDR(ACC_ADDR),
    .CSV_FILE("../data/accel_digital.csv")
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
    .I2C_ADDR(PPG_ADDR),
    .CSV_FILE("../data/ppg_digital.csv")
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

  always #5 clk = ~clk;

  integer cyc_cnt;
  integer epoch_cnt;
  integer feat_cnt;
  integer accel_cnt;
  integer ppg_cnt;
  integer beat_cnt;
  integer rr_valid_cnt;
  integer rmssd_valid_cnt;
  integer axi_aw_cnt;
  integer axi_w_cnt;
  integer axi_b_cnt;
  integer axi_feat_write_cnt;
  integer last_sec_cycle;
  integer last_epoch_cycle;

  bit saw_first_ppg;
  logic [31:0] last_ppg_time;
  logic [15:0] prev_seconds;
  bit prev_feat_valid;

  bit saw_time_feat;
  logic signed [15:0] time_feat_min;
  logic signed [15:0] time_feat_max;
  integer signed time_feat_span;

  bit axi_expect_active;
  logic [31:0] axi_expected_w0;
  logic [31:0] axi_expected_w1;
  logic [31:0] axi_seen_w0;
  logic [31:0] axi_seen_w1;
  bit axi_seen_first_word;
  bit axi_seen_second_word;

  task automatic check_no_x16(input logic signed [15:0] v, input [255:0] name);
    begin
      if (^v === 1'bx) $fatal(1, "%0s contains X", name);
    end
  endtask

  always @(posedge clk) begin
    logic [31:0] dt;

    cyc_cnt <= cyc_cnt + 1;

    if (!reset && dut.accel_valid_w) accel_cnt <= accel_cnt + 1;
    if (!reset && dut.beat_pulse_w) beat_cnt <= beat_cnt + 1;
    if (!reset && dut.rr_valid_w) rr_valid_cnt <= rr_valid_cnt + 1;
    if (!reset && dut.rmssd_valid_w) rmssd_valid_cnt <= rmssd_valid_cnt + 1;

    if (!reset && dut.ppg_sample_valid_w) begin
      ppg_cnt <= ppg_cnt + 1;
      if (!saw_first_ppg) begin
        saw_first_ppg <= 1'b1;
      end else begin
        if (dut.ppg_sample_time_w <= last_ppg_time) begin
          $fatal(1, "ppg_sample_time must increase (last=%0d now=%0d)",
                 last_ppg_time, dut.ppg_sample_time_w);
        end
        dt = dut.ppg_sample_time_w - last_ppg_time;
        if ((dt < 1) || (dt > 512)) begin
          $fatal(1, "ppg_sample_time step out of expected range [1..512], got %0d", dt);
        end
      end
      last_ppg_time <= dut.ppg_sample_time_w;
    end

    if (!reset && (dut.seconds_w != prev_seconds)) begin
      if ((prev_seconds != 16'd0) && (last_sec_cycle != 0)) begin
        if ((cyc_cnt - last_sec_cycle) != 1000) begin
          $fatal(1, "time_in_night_seconds period mismatch: got %0d exp 1000", (cyc_cnt - last_sec_cycle));
        end
      end
      last_sec_cycle <= cyc_cnt;
    end

    if (!reset && epoch_end) begin
      epoch_cnt <= epoch_cnt + 1;
      if (last_epoch_cycle != 0) begin
        if ((cyc_cnt - last_epoch_cycle) != 3000) begin
          $fatal(1, "epoch_end period mismatch: got %0d exp 3000", (cyc_cnt - last_epoch_cycle));
        end
      end
      last_epoch_cycle <= cyc_cnt;
    end

    if (!reset && feat_valid && !ml_update_gate) begin
      $fatal(1, "feat_valid asserted while ml_update_gate is low");
    end
    if (!reset && feat_valid && prev_feat_valid) begin
      $fatal(1, "feat_valid must be single-cycle pulse");
    end

    if (!reset && feat_valid) begin
      feat_cnt <= feat_cnt + 1;
      check_no_x16(time_feat, "time_feat");
      check_no_x16(motion_feat, "motion_feat");
      check_no_x16(delta_hr_feat, "delta_hr_feat");
      check_no_x16(rmssd_feat, "rmssd_feat");

      if (dut.axi_busy_w) begin
        $fatal(1, "feat_valid asserted while axi_interface is still busy");
      end

      axi_expect_active <= 1'b1;
      axi_expected_w0 <= {time_feat[15:0], motion_feat[15:0]};
      axi_expected_w1 <= {rmssd_feat[15:0], delta_hr_feat[15:0]};
      axi_seen_first_word <= 1'b0;
      axi_seen_second_word <= 1'b0;

      if (!saw_time_feat) begin
        saw_time_feat <= 1'b1;
        time_feat_min <= time_feat;
        time_feat_max <= time_feat;
      end else begin
        if (time_feat < time_feat_min) time_feat_min <= time_feat;
        if (time_feat > time_feat_max) time_feat_max <= time_feat;
      end
    end

    if (!reset && dut.maxi_awvalid_w && dut.maxi_awready_w) begin
      axi_aw_cnt <= axi_aw_cnt + 1;
      if (dut.maxi_awaddr_w != 32'h0000_0000 && dut.maxi_awaddr_w != 32'h0000_0004) begin
        $fatal(1, "unexpected AXI write address 0x%08x", dut.maxi_awaddr_w);
      end
    end

    if (!reset && dut.maxi_wvalid_w && dut.maxi_wready_w) begin
      axi_w_cnt <= axi_w_cnt + 1;
      if (!axi_expect_active) begin
        $fatal(1, "AXI write data observed without a preceding feat_valid");
      end

      if (!axi_seen_first_word) begin
        axi_seen_w0 <= dut.maxi_wdata_w;
        axi_seen_first_word <= 1'b1;
        if (dut.maxi_wdata_w !== axi_expected_w0) begin
          $fatal(1, "AXI word0 mismatch exp=0x%08x got=0x%08x",
                 axi_expected_w0, dut.maxi_wdata_w);
        end
      end else if (!axi_seen_second_word) begin
        axi_seen_w1 <= dut.maxi_wdata_w;
        axi_seen_second_word <= 1'b1;
        if (dut.maxi_wdata_w !== axi_expected_w1) begin
          $fatal(1, "AXI word1 mismatch exp=0x%08x got=0x%08x",
                 axi_expected_w1, dut.maxi_wdata_w);
        end
      end else begin
        $fatal(1, "saw more than two AXI data beats for one feature vector");
      end
    end

    if (!reset && dut.maxi_bvalid_w && dut.maxi_bready_w) begin
      axi_b_cnt <= axi_b_cnt + 1;
    end

    if (!reset && dut.axi_done_w) begin
      axi_feat_write_cnt <= axi_feat_write_cnt + 1;
      axi_expect_active <= 1'b0;
    end

    prev_seconds <= dut.seconds_w;
    prev_feat_valid <= feat_valid;
  end

  initial begin
    cyc_cnt = 0;
    epoch_cnt = 0;
    feat_cnt = 0;
    accel_cnt = 0;
    ppg_cnt = 0;
    beat_cnt = 0;
    rr_valid_cnt = 0;
    rmssd_valid_cnt = 0;
    axi_aw_cnt = 0;
    axi_w_cnt = 0;
    axi_b_cnt = 0;
    axi_feat_write_cnt = 0;
    last_sec_cycle = 0;
    last_epoch_cycle = 0;
    saw_first_ppg = 1'b0;
    last_ppg_time = 32'd0;
    prev_seconds = 16'd0;
    prev_feat_valid = 1'b0;
    saw_time_feat = 1'b0;
    time_feat_min = 16'sd0;
    time_feat_max = 16'sd0;
    time_feat_span = 0;
    axi_expect_active = 1'b0;
    axi_expected_w0 = 32'd0;
    axi_expected_w1 = 32'd0;
    axi_seen_w0 = 32'd0;
    axi_seen_w1 = 32'd0;
    axi_seen_first_word = 1'b0;
    axi_seen_second_word = 1'b0;

    force dut.maxi_awready_w = 1'b1;
    force dut.maxi_wready_w  = 1'b1;
    force dut.maxi_bvalid_w  = 1'b1;
    force dut.maxi_bresp_w   = 2'b00;

    repeat (20) @(posedge clk);
    reset = 1'b0;

    wait (epoch_cnt >= 20);

    if (accel_cnt < 20) $fatal(1, "too few accel samples: %0d", accel_cnt);
    if (ppg_cnt < 200) $fatal(1, "too few ppg samples: %0d", ppg_cnt);
    if (beat_cnt == 0) $fatal(1, "no beats detected");
    if (rr_valid_cnt == 0) $fatal(1, "no valid RR intervals");
    if (rmssd_valid_cnt == 0) $fatal(1, "rmssd_valid never asserted");
    if (feat_cnt == 0) $fatal(1, "feat_valid never asserted");
    if (axi_feat_write_cnt == 0) $fatal(1, "axi_interface never completed a feature write");
    if (axi_feat_write_cnt != feat_cnt) begin
      $fatal(1, "axi feature write count mismatch: feat=%0d axi=%0d", feat_cnt, axi_feat_write_cnt);
    end
    if (axi_aw_cnt != (2 * feat_cnt)) begin
      $fatal(1, "axi address beat count mismatch: aw=%0d expected=%0d", axi_aw_cnt, (2 * feat_cnt));
    end
    if (axi_w_cnt != (2 * feat_cnt)) begin
      $fatal(1, "axi data beat count mismatch: w=%0d expected=%0d", axi_w_cnt, (2 * feat_cnt));
    end

    if (!saw_time_feat) $fatal(1, "time feature never captured on feat_valid");
    time_feat_span = $signed({{16{time_feat_max[15]}}, time_feat_max}) -
                     $signed({{16{time_feat_min[15]}}, time_feat_min});
    if (time_feat_span < 2000) begin
      $fatal(1, "time_feat did not move enough: min=%0d max=%0d", time_feat_min, time_feat_max);
    end

    $display("PASS: epochs=%0d accel=%0d ppg=%0d beats=%0d rr=%0d rmssd_valid=%0d feat=%0d axi_feat_writes=%0d invalid_reason=0x%02x",
             epoch_cnt, accel_cnt, ppg_cnt, beat_cnt, rr_valid_cnt, rmssd_valid_cnt, feat_cnt, axi_feat_write_cnt, invalid_reason);
    $finish;
  end

  initial begin
    $dumpfile("top_pipeline_tb.vcd");
    $dumpvars(0, top_pipeline_tb);
  end

  initial begin
    repeat (300000) @(posedge clk);
    $fatal(1, "timeout");
  end

endmodule
