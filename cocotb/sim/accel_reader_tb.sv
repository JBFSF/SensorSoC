`timescale 1ns/1ps

module accel_reader_tb;

  logic clk = 0;
  logic rst_i = 1;

  logic        cfg_enable;
  logic        cfg_init_en;
  logic [31:0] cfg_poll_period_ticks;
  logic [7:0]  cfg_ctrl1_data;
  logic [7:0]  cfg_range_data;

  logic        i2c_cmd_valid;
  logic        i2c_cmd_ready;
  logic [6:0]  i2c_cmd_addr;
  logic [7:0]  i2c_cmd_reg;
  logic [7:0]  i2c_cmd_len;
  logic        i2c_cmd_write;
  logic [7:0]  i2c_cmd_wdata;

  logic        i2c_rsp_valid;
  logic [7:0]  i2c_rsp_data;
  logic        i2c_rsp_done;
  logic        i2c_rsp_error;

  wire signed [15:0] ax;
  wire signed [15:0] ay;
  wire signed [15:0] az;
  wire               accel_valid;
  wire               init_done;
  wire               i2c_error;
  wire               timeout;
  wire               nack_seen;

  accel_reader #(
    .I2C_ADDR(7'h19),
    .REG_CTRL1(8'h20),
    .REG_RANGE(8'h23),
    .REG_OUT_X_L(8'h28),
    .READ_LEN(6),
    .RSP_TIMEOUT_TICKS(25)
  ) dut (
    .clk(clk),
    .rst_i(rst_i),
    .cfg_enable_i(cfg_enable),
    .cfg_init_en_i(cfg_init_en),
    .cfg_poll_period_ticks_i(cfg_poll_period_ticks),
    .cfg_ctrl1_data_i(cfg_ctrl1_data),
    .cfg_range_data_i(cfg_range_data),
    .i2c_cmd_valid_o(i2c_cmd_valid),
    .i2c_cmd_ready_i(i2c_cmd_ready),
    .i2c_cmd_addr_o(i2c_cmd_addr),
    .i2c_cmd_reg_o(i2c_cmd_reg),
    .i2c_cmd_len_o(i2c_cmd_len),
    .i2c_cmd_write_o(i2c_cmd_write),
    .i2c_cmd_wdata_o(i2c_cmd_wdata),
    .i2c_rsp_valid_i(i2c_rsp_valid),
    .i2c_rsp_data_i(i2c_rsp_data),
    .i2c_rsp_done_i(i2c_rsp_done),
    .i2c_rsp_error_i(i2c_rsp_error),
    .ax_o(ax),
    .ay_o(ay),
    .az_o(az),
    .accel_valid_o(accel_valid),
    .init_done_o(init_done),
    .i2c_error_o(i2c_error),
    .timeout_o(timeout),
    .nack_seen_o(nack_seen)
  );

  always #10 clk = ~clk;

  assign i2c_cmd_ready = 1'b1;

  task automatic wait_cmd_check(
      input [7:0] reg_addr,
      input [7:0] exp_len,
      input bit exp_write,
      input [7:0] exp_wdata,
      input int timeout_cycles
  );
    int cycles;
    begin
      cycles = 0;
      while (!(i2c_cmd_valid && i2c_cmd_ready && (i2c_cmd_reg == reg_addr) && (i2c_cmd_write == exp_write))) begin
        @(posedge clk);
        cycles++;
        if (cycles > timeout_cycles) $fatal(1, "timeout waiting for cmd reg=0x%02x write=%0d", reg_addr, exp_write);
      end
      if (i2c_cmd_addr !== 7'h19) $fatal(1, "addr mismatch got=0x%02x", i2c_cmd_addr);
      if (i2c_cmd_len !== exp_len) $fatal(1, "len mismatch reg=0x%02x got=%0d exp=%0d", reg_addr, i2c_cmd_len, exp_len);
      if (exp_write && (i2c_cmd_wdata !== exp_wdata)) begin
        $fatal(1, "wdata mismatch reg=0x%02x got=0x%02x exp=0x%02x", reg_addr, i2c_cmd_wdata, exp_wdata);
      end
    end
  endtask

  task automatic rsp_done(input bit err);
    begin
      @(negedge clk);
      i2c_rsp_valid = 1'b0;
      i2c_rsp_data = 8'h00;
      i2c_rsp_error = err;
      i2c_rsp_done = 1'b1;
      @(posedge clk);
      @(negedge clk);
      i2c_rsp_done = 1'b0;
      i2c_rsp_error = 1'b0;
    end
  endtask

  task automatic rsp_read_byte(input [7:0] data, input bit done, input bit err);
    begin
      @(negedge clk);
      i2c_rsp_valid = 1'b1;
      i2c_rsp_data = data;
      i2c_rsp_error = err;
      i2c_rsp_done = done;
      @(posedge clk);
      @(negedge clk);
      i2c_rsp_valid = 1'b0;
      i2c_rsp_done = 1'b0;
      i2c_rsp_error = 1'b0;
    end
  endtask

  int sample_count;
  logic signed [15:0] ax_last, ay_last, az_last;
  always @(posedge clk) begin
    if (rst_i) begin
      sample_count <= 0;
      ax_last <= '0;
      ay_last <= '0;
      az_last <= '0;
    end else if (accel_valid) begin
      sample_count <= sample_count + 1;
      ax_last <= ax;
      ay_last <= ay;
      az_last <= az;
    end
  end

  initial begin
    i2c_rsp_valid = 0;
    i2c_rsp_data = 0;
    i2c_rsp_done = 0;
    i2c_rsp_error = 0;

    cfg_enable = 1'b1;
    cfg_init_en = 1'b1;
    cfg_poll_period_ticks = 32'd8;
    cfg_ctrl1_data = 8'h57;
    cfg_range_data = 8'h10;

    rst_i = 1'b1;
    repeat (5) @(posedge clk);
    rst_i = 1'b0;

    // 1) Init sequencing writes ODR/range config.
    wait_cmd_check(8'h20, 8'd1, 1'b1, 8'h57, 80);
    rsp_done(1'b0);
    wait_cmd_check(8'h23, 8'd1, 1'b1, 8'h10, 80);
    rsp_done(1'b0);
    repeat (2) @(posedge clk);
    if (!init_done) $fatal(1, "init_done not asserted after init writes");

    // 2) First periodic burst read and xyz assembly.
    wait_cmd_check(8'h28, 8'd6, 1'b0, 8'h00, 120);
    // x = -1000 (0xFC18), y = 291 (0x0123), z = -2 (0xFFFE)
    rsp_read_byte(8'h18, 1'b0, 1'b0);
    rsp_read_byte(8'hFC, 1'b0, 1'b0);
    rsp_read_byte(8'h23, 1'b0, 1'b0);
    rsp_read_byte(8'h01, 1'b0, 1'b0);
    rsp_read_byte(8'hFE, 1'b0, 1'b0);
    rsp_read_byte(8'hFF, 1'b1, 1'b0);
    repeat (2) @(posedge clk);
    if (sample_count < 1) $fatal(1, "no accel_valid after first read");
    if (ax_last !== -16'sd1000) $fatal(1, "ax mismatch got=%0d exp=-1000", ax_last);
    if (ay_last !== 16'sd291) $fatal(1, "ay mismatch got=%0d exp=291", ay_last);
    if (az_last !== -16'sd2) $fatal(1, "az mismatch got=%0d exp=-2", az_last);

    // 3) Poll scheduler issues another read after interval.
    wait_cmd_check(8'h28, 8'd6, 1'b0, 8'h00, 120);
    rsp_read_byte(8'h00, 1'b0, 1'b0);
    rsp_read_byte(8'h00, 1'b0, 1'b0);
    rsp_read_byte(8'h00, 1'b0, 1'b0);
    rsp_read_byte(8'h00, 1'b0, 1'b0);
    rsp_read_byte(8'h00, 1'b0, 1'b0);
    rsp_read_byte(8'h00, 1'b1, 1'b0);

    // 4) Error on read should set nack + i2c_error.
    wait_cmd_check(8'h28, 8'd6, 1'b0, 8'h00, 120);
    rsp_read_byte(8'hAA, 1'b1, 1'b1);
    repeat (3) @(posedge clk);
    if (!i2c_error) $fatal(1, "i2c_error not asserted on rsp_error");
    if (!nack_seen) $fatal(1, "nack_seen not asserted on rsp_error");

    // 5) Timeout when no response arrives.
    wait_cmd_check(8'h28, 8'd6, 1'b0, 8'h00, 120);
    repeat (40) @(posedge clk); // > RSP_TIMEOUT_TICKS
    if (!timeout) $fatal(1, "timeout flag not asserted");

    $display("PASS");
    $finish;
  end

  initial begin
    $dumpfile("accel_reader_tb.vcd");
    $dumpvars(0, accel_reader_tb);
  end

endmodule
