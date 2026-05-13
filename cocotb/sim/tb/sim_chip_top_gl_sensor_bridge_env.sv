`timescale 1ns/1ps

module sim_chip_top_gl_sensor_bridge_env;
  localparam [6:0] ACC_ADDR = 7'h19;
  localparam [6:0] PPG_ADDR = 7'h64;

  logic        clk_drv = 1'b0;
  logic        rst_n_drv = 1'b0;
  logic [11:0] input_drv = 12'h000;
  wire         clk_PAD;
  wire         rst_n_PAD;
  wire  [11:0] input_PAD;
  logic [39:0] bidir_drv = 40'h0;
  logic [39:0] bidir_oe = 40'h0;
  wire  [39:0] bidir_PAD;
  wire  [39:0] bidir_sample;
  wire  [1:0]  analog_PAD;

  wire VDD = 1'b1;
  wire VSS = 1'b0;

  wire sensor_bridge_en = input_drv[11];

  wire       sim_req = bidir_PAD[8];
  wire       sim_write = bidir_PAD[9];
  wire [6:0] sim_addr = bidir_PAD[16:10];
  wire [7:0] sim_reg = bidir_PAD[24:17];
  wire [7:0] sim_len = bidir_PAD[32:25];
  wire [7:0] sim_wdata = bidir_PAD[7:0];
  wire       sensor_req = sensor_bridge_en ? sim_req : 1'b0;
  wire       sensor_write = sensor_bridge_en ? sim_write : 1'b0;
  wire [6:0] sensor_addr = sensor_bridge_en ? sim_addr : 7'h00;
  wire [7:0] sensor_reg = sensor_bridge_en ? sim_reg : 8'h00;
  wire [7:0] sensor_len = sensor_bridge_en ? sim_len : 8'h00;
  wire [7:0] sensor_wdata = sensor_bridge_en ? sim_wdata : 8'h00;

  wire       accel_sim_ack;
  wire [7:0] accel_sim_rdata;
  wire       accel_sim_rvalid;
  wire       accel_sim_rlast;
  wire       accel_sim_err;

  wire       ppg_sim_ack;
  wire [7:0] ppg_sim_rdata;
  wire       ppg_sim_rvalid;
  wire       ppg_sim_rlast;
  wire       ppg_sim_err;

  wire sensor_sim_ack = (sensor_addr == ACC_ADDR) ? accel_sim_ack :
                        (sensor_addr == PPG_ADDR) ? ppg_sim_ack : 1'b0;
  wire [7:0] sensor_sim_rdata = (sensor_addr == ACC_ADDR) ? accel_sim_rdata :
                                (sensor_addr == PPG_ADDR) ? ppg_sim_rdata : 8'h00;
  wire sensor_sim_rvalid = (sensor_addr == ACC_ADDR) ? accel_sim_rvalid :
                           (sensor_addr == PPG_ADDR) ? ppg_sim_rvalid : 1'b0;
  wire sensor_sim_rlast = (sensor_addr == ACC_ADDR) ? accel_sim_rlast :
                          (sensor_addr == PPG_ADDR) ? ppg_sim_rlast : 1'b0;
  wire sensor_sim_err = (sensor_addr == ACC_ADDR) ? accel_sim_err :
                        (sensor_addr == PPG_ADDR) ? ppg_sim_err : 1'b1;

  logic       sensor_sim_ack_pad_q;
  logic       sensor_sim_rvalid_pad_q;
  logic [7:0] sensor_sim_rdata_pad_q;
  logic       sensor_sim_rlast_pad_q;
  logic       sensor_sim_err_pad_q;

  // Sensor models update on the rising edge, like the GL netlist. Retiming the
  // pad response on the falling edge makes the external pads stable before the
  // chip samples them on the next rising edge.
  always_ff @(negedge clk_PAD or negedge rst_n_PAD) begin
    if (!rst_n_PAD) begin
      sensor_sim_ack_pad_q <= 1'b0;
      sensor_sim_rvalid_pad_q <= 1'b0;
      sensor_sim_rdata_pad_q <= 8'h00;
      sensor_sim_rlast_pad_q <= 1'b0;
      sensor_sim_err_pad_q <= 1'b0;
    end else if (!sensor_bridge_en) begin
      sensor_sim_ack_pad_q <= 1'b0;
      sensor_sim_rvalid_pad_q <= 1'b0;
      sensor_sim_rdata_pad_q <= 8'h00;
      sensor_sim_rlast_pad_q <= 1'b0;
      sensor_sim_err_pad_q <= 1'b0;
    end else begin
      sensor_sim_ack_pad_q <= sensor_sim_ack;
      sensor_sim_rvalid_pad_q <= sensor_sim_rvalid;
      sensor_sim_rdata_pad_q <= sensor_sim_rdata;
      sensor_sim_rlast_pad_q <= sensor_sim_rlast;
      sensor_sim_err_pad_q <= sensor_sim_err;
    end
  end

  assign bidir_sample = bidir_PAD;
  assign clk_PAD = clk_drv;
  assign rst_n_PAD = rst_n_drv;
  assign input_PAD = input_drv;

  genvar i;
  generate
    for (i = 0; i < 40; i = i + 1) begin : tb_bidir_drive
      if (i < 8) begin : sensor_data_drive
        assign bidir_PAD[i] = sensor_bridge_en ? (sensor_sim_rvalid_pad_q ? sensor_sim_rdata_pad_q[i] : 1'bz) :
                              (bidir_oe[i] ? bidir_drv[i] : 1'bz);
      end else if (i == 33) begin : sensor_ack_drive
        assign bidir_PAD[i] = sensor_bridge_en ? sensor_sim_ack_pad_q :
                              (bidir_oe[i] ? bidir_drv[i] : 1'bz);
      end else if (i == 34) begin : sensor_rvalid_drive
        assign bidir_PAD[i] = sensor_bridge_en ? sensor_sim_rvalid_pad_q :
                              (bidir_oe[i] ? bidir_drv[i] : 1'bz);
      end else if (i == 35) begin : sensor_rlast_drive
        assign bidir_PAD[i] = sensor_bridge_en ? sensor_sim_rlast_pad_q :
                              (bidir_oe[i] ? bidir_drv[i] : 1'bz);
      end else if (i == 36) begin : sensor_err_drive
        assign bidir_PAD[i] = sensor_bridge_en ? sensor_sim_err_pad_q :
                              (bidir_oe[i] ? bidir_drv[i] : 1'bz);
      end else begin : external_drive
        assign bidir_PAD[i] = bidir_oe[i] ? bidir_drv[i] : 1'bz;
      end
    end
  endgenerate

  pullup host_sda_pullup (bidir_PAD[6]);

  i2c_slave_lis2dw12 #(
    .I2C_ADDR(ACC_ADDR)
  ) u_accel_slave (
    .clk(clk_PAD),
    .resetn(rst_n_PAD),
    .sim_req(sensor_req),
    .sim_addr(sensor_addr),
    .sim_reg(sensor_reg),
    .sim_len(sensor_len),
    .sim_ack(accel_sim_ack),
    .sim_rdata(accel_sim_rdata),
    .sim_rvalid(accel_sim_rvalid),
    .sim_rlast(accel_sim_rlast),
    .sim_err(accel_sim_err)
  );

  i2c_slave_adpd144ri #(
    .I2C_ADDR(PPG_ADDR)
  ) u_ppg_slave (
    .clk(clk_PAD),
    .resetn(rst_n_PAD),
    .sim_req(sensor_req),
    .sim_addr(sensor_addr),
    .sim_reg(sensor_reg),
    .sim_len(sensor_len),
    .sim_write(sensor_write),
    .sim_wdata(sensor_wdata),
    .sim_ack(ppg_sim_ack),
    .sim_rdata(ppg_sim_rdata),
    .sim_rvalid(ppg_sim_rvalid),
    .sim_rlast(ppg_sim_rlast),
    .sim_err(ppg_sim_err)
  );

  chip_top u_chip (
    .VDD(VDD),
    .VSS(VSS),
    .clk_PAD(clk_PAD),
    .rst_n_PAD(rst_n_PAD),
    .input_PAD(input_PAD),
    .bidir_PAD(bidir_PAD),
    .analog_PAD(analog_PAD)
  );
endmodule
