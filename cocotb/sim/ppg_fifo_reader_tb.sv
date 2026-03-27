`timescale 1ns/1ps

module ppg_fifo_reader_tb;

  localparam int SAMPLE_W = 16;
  localparam int STATUS_BYTES = 2;
  localparam int COUNT_W = 8;
  localparam int WATERMARK = 4;
  localparam int MAX_BURST = 8;
  localparam int PACKET_BYTES = 4;

  localparam byte REG_STATUS = 8'h00;
  localparam byte REG_FIFO_THRESH = 8'h06;
  localparam byte REG_FIFO_ACCESS_ENA = 8'h5F;
  localparam byte REG_FIFO_ACCESS = 8'h60;

  logic clk = 0;
  logic rst_i = 1;

  logic [31:0] t_now;

  logic        i2c_cmd_valid;
  logic        i2c_cmd_ready;
  logic [6:0]  i2c_cmd_addr;
  logic [7:0]  i2c_cmd_reg;
  logic [7:0]  i2c_cmd_len;
  logic        i2c_cmd_write;
  logic [7:0]  i2c_cmd_wdata;

  logic        i2c_rsp_valid;
  logic [7:0]  i2c_rsp_data;
  logic        i2c_rsp_last;
  logic        i2c_rsp_err;
  logic        i2c_rsp_ready;

  wire [SAMPLE_W-1:0] ppg_sample;
  wire                ppg_sample_valid;
  wire [31:0]         ppg_sample_time;

  wire fifo_overflow_flag;
  wire fifo_empty_flag;
  wire i2c_error_flag;

  ppg_fifo_reader #(
    .I2C_ADDR(7'h64),
    .REG_STATUS(REG_STATUS),
    .REG_FIFO_THRESH(REG_FIFO_THRESH),
    .REG_FIFO_ACCESS_ENA(REG_FIFO_ACCESS_ENA),
    .REG_FIFO_ACCESS(REG_FIFO_ACCESS),
    .SAMPLE_W(SAMPLE_W),
    .STATUS_BYTES(STATUS_BYTES),
    .COUNT_W(COUNT_W),
    .WATERMARK(WATERMARK),
    .MAX_BURST_SAMPLES(MAX_BURST),
    .PACKET_BYTES(PACKET_BYTES),
    .POLL_PERIOD(20),
    .TIMESTAMP_PER_SAMPLE(1)
  ) dut (
    .clk_i(clk),
    .rst_i(rst_i),

    .t_now(t_now),

    .i2c_cmd_valid(i2c_cmd_valid),
    .i2c_cmd_ready(i2c_cmd_ready),
    .i2c_cmd_addr(i2c_cmd_addr),
    .i2c_cmd_reg(i2c_cmd_reg),
    .i2c_cmd_len(i2c_cmd_len),
    .i2c_cmd_write(i2c_cmd_write),
    .i2c_cmd_wdata(i2c_cmd_wdata),

    .i2c_rsp_valid(i2c_rsp_valid),
    .i2c_rsp_data(i2c_rsp_data),
    .i2c_rsp_last(i2c_rsp_last),
    .i2c_rsp_err(i2c_rsp_err),
    .i2c_rsp_ready(i2c_rsp_ready),

    .ppg_sample(ppg_sample),
    .ppg_sample_valid(ppg_sample_valid),
    .ppg_sample_time(ppg_sample_time),

    .fifo_overflow_flag(fifo_overflow_flag),
    .fifo_empty_flag(fifo_empty_flag),
    .i2c_error_flag(i2c_error_flag)
  );

  always #10 clk = ~clk;

  always @(posedge clk) begin
    if (rst_i) t_now <= 32'd0;
    else t_now <= t_now + 1;
  end

  // Simple i2c response queue
  byte rsp_q[$];
  bit  rsp_err_q[$];
  bit  rsp_last_q[$];

  task automatic q_push(input byte b, input bit err, input bit last);
    rsp_q.push_back(b);
    rsp_err_q.push_back(err);
    rsp_last_q.push_back(last);
  endtask

  task automatic q_clear();
    rsp_q.delete();
    rsp_err_q.delete();
    rsp_last_q.delete();
  endtask

  assign i2c_cmd_ready = 1'b1;

  always @(posedge clk) begin
    i2c_rsp_valid <= 1'b0;
    if (i2c_rsp_ready && (rsp_q.size() != 0)) begin
      i2c_rsp_valid <= 1'b1;
      i2c_rsp_data <= rsp_q.pop_front();
      i2c_rsp_err  <= rsp_err_q.pop_front();
      i2c_rsp_last <= rsp_last_q.pop_front();
    end
  end

  int sample_count;
  logic [SAMPLE_W-1:0] exp_samples[$];
  logic [SAMPLE_W-1:0] got_samples[$];

  always @(posedge clk) begin
    if (rst_i) sample_count <= 0;
    else if (ppg_sample_valid) sample_count <= sample_count + 1;
  end

  always @(posedge clk) begin
    if (rst_i) begin
      got_samples.delete();
    end else if (ppg_sample_valid) begin
      got_samples.push_back(ppg_sample);
      if (!((ppg_sample_time == t_now) || (ppg_sample_time == (t_now - 1)))) begin
        $fatal(1, "timestamp mismatch: got=%0d exp=%0d or %0d", ppg_sample_time, t_now, (t_now - 1));
      end
    end
  end

  task automatic wait_polls(input int n);
    repeat (n) @(posedge clk);
  endtask

  task automatic wait_cmd_check(
      input byte reg_addr,
      input byte exp_len,
      input bit exp_write,
      input byte exp_wdata,
      input int timeout
  );
    int cycles;
    begin
      cycles = 0;
      while (!(i2c_cmd_valid && i2c_cmd_ready && (i2c_cmd_reg == reg_addr) && (i2c_cmd_write == exp_write))) begin
        @(posedge clk);
        cycles++;
        if (cycles > timeout) $fatal(1, "timeout waiting cmd reg=0x%02x write=%0d", reg_addr, exp_write);
      end
      if (i2c_cmd_addr !== 7'h64) $fatal(1, "cmd addr mismatch: got=0x%02x", i2c_cmd_addr);
      if (i2c_cmd_len !== exp_len) $fatal(1, "cmd len mismatch reg=0x%02x got=%0d exp=%0d", reg_addr, i2c_cmd_len, exp_len);
      if (exp_write && (i2c_cmd_wdata !== exp_wdata)) begin
        $fatal(1, "cmd wdata mismatch reg=0x%02x got=0x%02x exp=0x%02x", reg_addr, i2c_cmd_wdata, exp_wdata);
      end
    end
  endtask

  task automatic assert_no_cmd(input byte reg_addr, input int cycles);
    begin
      repeat (cycles) begin
        @(posedge clk);
        if (i2c_cmd_valid && i2c_cmd_ready && (i2c_cmd_reg == reg_addr)) begin
          $fatal(1, "unexpected cmd reg=0x%02x", reg_addr);
        end
      end
    end
  endtask

  task automatic expect_samples(input int n, input int timeout);
    int cycles;
    begin
      cycles = 0;
      while (got_samples.size() < n) begin
        @(posedge clk);
        cycles++;
        if (cycles > timeout) $fatal(1, "timeout waiting for %0d samples (got %0d)", n, got_samples.size());
      end
    end
  endtask

  task automatic clear_expected();
    exp_samples.delete();
    got_samples.delete();
  endtask

  task automatic check_expected();
    if (got_samples.size() != exp_samples.size()) begin
      $fatal(1, "sample count mismatch got=%0d exp=%0d", got_samples.size(), exp_samples.size());
    end
    for (int i = 0; i < exp_samples.size(); i++) begin
      if (got_samples[i] !== exp_samples[i]) begin
        $fatal(1, "sample[%0d] mismatch got=0x%0x exp=0x%0x", i, got_samples[i], exp_samples[i]);
      end
    end
  endtask

  task automatic push_status(input byte fifo_bytes_avail, input bit overflow, input bit rsp_err_once);
    begin
      wait_cmd_check(REG_STATUS, 8'd2, 1'b0, 8'h00, 200);
      q_clear();
      if (rsp_err_once) begin
        q_push(8'h00, 1'b1, 1'b1);
      end else begin
        q_push({overflow, 7'd0}, 1'b0, 1'b0);
        q_push(fifo_bytes_avail, 1'b0, 1'b1);
      end
    end
  endtask

  task automatic push_thresh(input byte thresh_words, input bit rsp_err_once);
    begin
      wait_cmd_check(REG_FIFO_THRESH, 8'd2, 1'b0, 8'h00, 200);
      q_clear();
      if (rsp_err_once) begin
        q_push(8'h00, 1'b1, 1'b1);
      end else begin
        q_push(8'h00, 1'b0, 1'b0);
        q_push({2'b00, thresh_words[5:0]}, 1'b0, 1'b1); // reg[13:8]
      end
    end
  endtask

  initial begin
    i2c_rsp_valid = 0;
    i2c_rsp_data = 0;
    i2c_rsp_err = 0;
    i2c_rsp_last = 0;

    rst_i = 1;
    wait_polls(5);
    rst_i = 0;

    // 1) fifo empty: bytes avail = 0, threshold = 4 words (=8 bytes), no read
    clear_expected();
    push_status(8'd0, 1'b0, 1'b0);
    push_thresh(8'd4, 1'b0);
    wait_polls(10);
    if (!fifo_empty_flag) $fatal(1, "empty: fifo_empty_flag not set");
    if (sample_count != 0) $fatal(1, "empty: unexpected samples %0d", sample_count);
    assert_no_cmd(REG_FIFO_ACCESS, 10);

    // 2) below threshold: avail=6 bytes (<8), no read
    clear_expected();
    push_status(8'd6, 1'b0, 1'b0);
    push_thresh(8'd4, 1'b0);
    wait_polls(10);
    if (fifo_empty_flag) $fatal(1, "below threshold: fifo_empty_flag should be clear");
    assert_no_cmd(REG_FIFO_ACCESS, 10);

    // 3) threshold hit: avail=8 bytes
    clear_expected();
    push_status(8'd8, 1'b0, 1'b0);
    push_thresh(8'd4, 1'b0);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS, 8'd8, 1'b0, 8'h00, 200);
    q_clear();
    // 4 samples: 0x0011, 0x2233, 0x4455, 0x6677
    q_push(8'h11, 1'b0, 1'b0); q_push(8'h00, 1'b0, 1'b0);
    q_push(8'h33, 1'b0, 1'b0); q_push(8'h22, 1'b0, 1'b0);
    q_push(8'h55, 1'b0, 1'b0); q_push(8'h44, 1'b0, 1'b0);
    q_push(8'h77, 1'b0, 1'b0); q_push(8'h66, 1'b0, 1'b1);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h00, 200);
    exp_samples.push_back(16'h0011);
    exp_samples.push_back(16'h2233);
    exp_samples.push_back(16'h4455);
    exp_samples.push_back(16'h6677);
    expect_samples(4, 300);
    check_expected();

    // 4) packet integrity: avail=14 bytes, packet=4 -> read 12 bytes (6 samples)
    clear_expected();
    push_status(8'd14, 1'b0, 1'b0);
    push_thresh(8'd4, 1'b0);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS, 8'd12, 1'b0, 8'h00, 200);
    q_clear();
    for (int i = 0; i < 6; i++) begin
      q_push(byte'(i[7:0]), 1'b0, 1'b0);
      q_push(8'h00, 1'b0, (i == 5));
      exp_samples.push_back({8'h00, byte'(i[7:0])});
    end
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h00, 200);
    expect_samples(6, 400);
    check_expected();

    // 5) max burst clamp: avail=40 bytes -> read only 16 bytes (MAX_BURST*2)
    clear_expected();
    push_status(8'd40, 1'b0, 1'b0);
    push_thresh(8'd4, 1'b0);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS, 8'd16, 1'b0, 8'h00, 200);
    q_clear();
    for (int i = 0; i < MAX_BURST; i++) begin
      q_push(byte'(8'h80 + i[7:0]), 1'b0, 1'b0);
      q_push(8'h00, 1'b0, (i == (MAX_BURST-1)));
      exp_samples.push_back({8'h00, byte'(8'h80 + i[7:0])});
    end
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h00, 200);
    expect_samples(MAX_BURST, 500);
    check_expected();

    // 6) i2c error on status read
    push_status(8'd0, 1'b0, 1'b1);
    wait_polls(10);
    if (!i2c_error_flag) $fatal(1, "status read error: i2c_error_flag not set");

    // 7) i2c error on threshold read
    push_status(8'd8, 1'b0, 1'b0);
    push_thresh(8'd0, 1'b1);
    wait_polls(10);
    if (!i2c_error_flag) $fatal(1, "threshold read error: i2c_error_flag not set");

    // 8) i2c error on data read still disables FIFO access
    clear_expected();
    push_status(8'd8, 1'b0, 1'b0);
    push_thresh(8'd4, 1'b0);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h01, 200);
    wait_cmd_check(REG_FIFO_ACCESS, 8'd8, 1'b0, 8'h00, 200);
    q_clear();
    q_push(8'hAA, 1'b1, 1'b1);
    wait_cmd_check(REG_FIFO_ACCESS_ENA, 8'd1, 1'b1, 8'h00, 200);
    wait_polls(20);
    if (got_samples.size() != 0) $fatal(1, "data error: unexpected samples");

    // 9) overflow bit is sticky
    push_status(8'd0, 1'b1, 1'b0);
    push_thresh(8'd4, 1'b0);
    wait_polls(10);
    if (!fifo_overflow_flag) $fatal(1, "overflow: flag not set");

    $display("PASS");
    $finish;
  end

  initial begin
    $dumpfile("ppg_fifo_reader_tb.vcd");
    $dumpvars(0, ppg_fifo_reader_tb);
  end

endmodule
