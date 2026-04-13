`timescale 1ns/1ps

// tb_sensor_pipeline.sv
//
// Testbench for the full sensor pipeline. Two simulated I2C slaves
// (LIS2DW12 accelerometer and ADPD144RI PPG sensor) feed data through
// a shared I2C master into their respective readers. The accel path
// continues into motion_process for epoch energy computation.
//
// Pass criteria:
//   - At least 1 accel sample received (accel_valid_o asserted)
//   - At least 1 PPG sample received (ppg_sample_valid asserted)
//   - At least 1 motion epoch completed (epoch_done_o asserted)
//
// Run from SensorSoC/cocotb/:
//   iverilog -g2012 -o sim/sim_sensor \
//     ../src/i2c_master.sv \
//     ../src/accel_reader.sv \
//     ../src/ppg_fifo_reader.sv \
//     ../src/motion_process.sv \
//     ../src/globaltimer.sv \
//     sensors/i2c_slave_lis2dw12.sv \
//     sensors/i2c_slave_adpd144ri.sv \
//     sim/tb/tb_sensor_pipeline.sv
//
//   vvp sim/sim_sensor
//
// Or from SensorSoC/ (repo root):
//   iverilog -g2012 -o cocotb/sim/sim_sensor \
//     src/i2c_master.sv \
//     src/accel_reader.sv \
//     src/ppg_fifo_reader.sv \
//     src/motion_process.sv \
//     src/globaltimer.sv \
//     cocotb/sensors/i2c_slave_lis2dw12.sv \
//     cocotb/sensors/i2c_slave_adpd144ri.sv \
//     cocotb/sim/tb/tb_sensor_pipeline.sv
//
//   vvp cocotb/sim/sim_sensor +DATA_DIR=cocotb/sim/data

module tb_sensor_pipeline;


    // Clock and reset

    logic clk    = 0;
    logic resetn = 0;

    always #10 clk = ~clk;   // 50 MHz

    initial begin
        resetn = 0;
        repeat (10) @(posedge clk);
        resetn = 1;
    end


    // Shared functional sim bus (i2c_master <-> slaves)

    wire        sim_req;
    wire [6:0]  sim_addr;
    wire [7:0]  sim_reg;
    wire [7:0]  sim_len;
    wire        sim_write;
    wire [7:0]  sim_wdata;

    wire        accel_sim_ack,   ppg_sim_ack;
    wire [7:0]  accel_sim_rdata, ppg_sim_rdata;
    wire        accel_sim_rvalid,ppg_sim_rvalid;
    wire        accel_sim_rlast, ppg_sim_rlast;
    wire        accel_sim_err,   ppg_sim_err;

    // Mux slave responses to master based on address
    wire sim_ack    = (sim_addr == 7'h18) ? accel_sim_ack    : ppg_sim_ack;
    wire [7:0] sim_rdata = (sim_addr == 7'h18) ? accel_sim_rdata : ppg_sim_rdata;
    wire sim_rvalid = (sim_addr == 7'h18) ? accel_sim_rvalid : ppg_sim_rvalid;
    wire sim_rlast  = (sim_addr == 7'h18) ? accel_sim_rlast  : ppg_sim_rlast;
    wire sim_err    = (sim_addr == 7'h18) ? accel_sim_err    : ppg_sim_err;


    // I2C slave models

    i2c_slave_lis2dw12 u_accel_slave (
        .clk        (clk),
        .resetn     (resetn),
        .sim_req    (sim_req),
        .sim_addr   (sim_addr),
        .sim_reg    (sim_reg),
        .sim_len    (sim_len),
        .sim_ack    (accel_sim_ack),
        .sim_rdata  (accel_sim_rdata),
        .sim_rvalid (accel_sim_rvalid),
        .sim_rlast  (accel_sim_rlast),
        .sim_err    (accel_sim_err)
    );

    i2c_slave_adpd144ri u_ppg_slave (
        .clk        (clk),
        .resetn     (resetn),
        .sim_req    (sim_req),
        .sim_addr   (sim_addr),
        .sim_reg    (sim_reg),
        .sim_len    (sim_len),
        .sim_write  (sim_write),
        .sim_wdata  (sim_wdata),
        .sim_ack    (ppg_sim_ack),
        .sim_rdata  (ppg_sim_rdata),
        .sim_rvalid (ppg_sim_rvalid),
        .sim_rlast  (ppg_sim_rlast),
        .sim_err    (ppg_sim_err)
    );


    // I2C master <-> accel_reader wires

    wire        accel_cmd_valid, accel_cmd_ready;
    wire [6:0]  accel_cmd_addr;
    wire [7:0]  accel_cmd_reg, accel_cmd_len, accel_cmd_wdata;
    wire        accel_cmd_write;
    wire        accel_rsp_valid, accel_rsp_last, accel_rsp_done, accel_rsp_err;
    wire [7:0]  accel_rsp_data;


    // I2C master <-> ppg_fifo_reader wires

    wire        ppg_cmd_valid, ppg_cmd_ready;
    wire [6:0]  ppg_cmd_addr;
    wire [7:0]  ppg_cmd_reg, ppg_cmd_len, ppg_cmd_wdata;
    wire        ppg_cmd_write;
    wire        ppg_rsp_valid, ppg_rsp_last, ppg_rsp_done, ppg_rsp_err;
    wire [7:0]  ppg_rsp_data;
    wire        ppg_rsp_ready;


    // I2C master

    i2c_master u_i2c_master (
        .clk                (clk),
        .resetn     (resetn),

        .accel_cmd_valid_i  (accel_cmd_valid),
        .accel_cmd_ready_o  (accel_cmd_ready),
        .accel_cmd_addr_i   (accel_cmd_addr),
        .accel_cmd_reg_i    (accel_cmd_reg),
        .accel_cmd_len_i    (accel_cmd_len),
        .accel_cmd_write_i  (accel_cmd_write),
        .accel_cmd_wdata_i  (accel_cmd_wdata),
        .accel_rsp_valid_o  (accel_rsp_valid),
        .accel_rsp_data_o   (accel_rsp_data),
        .accel_rsp_last_o   (accel_rsp_last),
        .accel_rsp_done_o   (accel_rsp_done),
        .accel_rsp_err_o    (accel_rsp_err),
        .accel_rsp_ready_i  (1'b1),

        .ppg_cmd_valid_i    (ppg_cmd_valid),
        .ppg_cmd_ready_o    (ppg_cmd_ready),
        .ppg_cmd_addr_i     (ppg_cmd_addr),
        .ppg_cmd_reg_i      (ppg_cmd_reg),
        .ppg_cmd_len_i      (ppg_cmd_len),
        .ppg_cmd_write_i    (ppg_cmd_write),
        .ppg_cmd_wdata_i    (ppg_cmd_wdata),
        .ppg_rsp_valid_o    (ppg_rsp_valid),
        .ppg_rsp_data_o     (ppg_rsp_data),
        .ppg_rsp_last_o     (ppg_rsp_last),
        .ppg_rsp_done_o     (ppg_rsp_done),
        .ppg_rsp_err_o      (ppg_rsp_err),
        .ppg_rsp_ready_i    (ppg_rsp_ready),

        .sim_req            (sim_req),
        .sim_addr           (sim_addr),
        .sim_reg            (sim_reg),
        .sim_len            (sim_len),
        .sim_write          (sim_write),
        .sim_wdata          (sim_wdata),
        .sim_ack            (sim_ack),
        .sim_rdata          (sim_rdata),
        .sim_rvalid         (sim_rvalid),
        .sim_rlast          (sim_rlast),
        .sim_err            (sim_err)
    );


    // Global timer

    wire [15:0] time_in_night_seconds;
    wire        epoch_end_global;
    wire [9:0]  epoch_index;

    globaltimer #(
        .clk_speed_hz   (50_000_000),
        .epoch_hz       (25),
        .epoch_count_max(1000)
    ) u_globaltimer (
        .clk_i                  (clk),
        .rst_i                  (~resetn),
        .en_i                   (1'b1),
        .time_in_night_seconds_o(time_in_night_seconds),
        .epoch_end_o            (epoch_end_global),
        .epoch_index_o          (epoch_index)
    );

    // t_now for accel_reader and ppg_fifo_reader
    reg [31:0] t_now;
    always @(posedge clk) begin
        if (!resetn) t_now <= 32'd0;
        else         t_now <= t_now + 1;
    end


    // Accel reader

    wire signed [15:0] ax_o, ay_o, az_o;
    wire               accel_valid_o;
    wire               accel_init_done;

    accel_reader #(
        .I2C_ADDR           (7'h18),
        .RSP_TIMEOUT_TICKS  (10000)
    ) u_accel_reader (
        .clk                    (clk),
        .rst_i                  (~resetn),
        .cfg_enable_i           (1'b1),
        .cfg_init_en_i          (1'b0),
        .cfg_poll_period_ticks_i(32'd200_000),
        .cfg_ctrl1_data_i       (8'h00),
        .cfg_range_data_i       (8'h00),

        .i2c_cmd_valid_o        (accel_cmd_valid),
        .i2c_cmd_ready_i        (accel_cmd_ready),
        .i2c_cmd_addr_o         (accel_cmd_addr),
        .i2c_cmd_reg_o          (accel_cmd_reg),
        .i2c_cmd_len_o          (accel_cmd_len),
        .i2c_cmd_write_o        (accel_cmd_write),
        .i2c_cmd_wdata_o        (accel_cmd_wdata),
        .i2c_rsp_valid_i        (accel_rsp_valid),
        .i2c_rsp_data_i         (accel_rsp_data),
        .i2c_rsp_done_i         (accel_rsp_done),
        .i2c_rsp_error_i        (accel_rsp_err),
        .ax_o                   (ax_o),
        .ay_o                   (ay_o),
        .az_o                   (az_o),
        .accel_valid_o          (accel_valid_o),

        .init_done_o            (accel_init_done),
        .i2c_error_o            (),
        .timeout_o              (),
        .nack_seen_o            ()
    );


    // Epoch scheduler (25 samples per epoch)

    reg [4:0]  epoch_sample_cnt;
    reg        epoch_end;

    always @(posedge clk) begin
        if (!resetn) begin
            epoch_sample_cnt <= 5'd0;
            epoch_end        <= 1'b0;
        end else begin
            epoch_end <= 1'b0;
            if (accel_valid_o) begin
                if (epoch_sample_cnt == 5'd24) begin
                    epoch_sample_cnt <= 5'd0;
                    epoch_end        <= 1'b1;
                end else begin
                    epoch_sample_cnt <= epoch_sample_cnt + 1;
                end
            end
        end
    end


    // Motion preprocessor

    wire        epoch_done;
    wire [47:0] motion_energy_epoch;

    motion_process u_motion (
        .clk                   (clk),
        .rst_i                 (~resetn),
        .sample_valid_i        (accel_valid_o),
        .ax_i                  (ax_o[13:0]),
        .ay_i                  (ay_o[13:0]),
        .az_i                  (az_o[13:0]),
        .epoch_end_i           (epoch_end),
        .epoch_done_o          (epoch_done),
        .motion_energy_epoch_o (motion_energy_epoch)
    );


    // PPG FIFO reader

    wire [15:0] ppg_sample;
    wire        ppg_sample_valid;
    wire [31:0] ppg_sample_time;

    ppg_fifo_reader #(
        .POLL_PERIOD    (50_000)
    ) u_ppg_reader (
        .clk_i          (clk),
        .rst_i          (~resetn),
        .t_now          (t_now),
        .i2c_cmd_valid  (ppg_cmd_valid),
        .i2c_cmd_ready  (ppg_cmd_ready),
        .i2c_cmd_addr   (ppg_cmd_addr),
        .i2c_cmd_reg    (ppg_cmd_reg),
        .i2c_cmd_len    (ppg_cmd_len),
        .i2c_cmd_write  (ppg_cmd_write),
        .i2c_cmd_wdata  (ppg_cmd_wdata),
        .i2c_rsp_valid  (ppg_rsp_valid),
        .i2c_rsp_data   (ppg_rsp_data),
        .i2c_rsp_last   (ppg_rsp_last),
        .i2c_rsp_err    (ppg_rsp_err),
        .i2c_rsp_ready  (ppg_rsp_ready),
        .ppg_sample         (ppg_sample),
        .ppg_sample_valid   (ppg_sample_valid),
        .ppg_sample_time    (ppg_sample_time),
        .fifo_overflow_flag (),
        .fifo_empty_flag    (),
        .i2c_error_flag     ()
    );


    // Wave dump

    initial begin
        $dumpfile("sensor_pipeline.vcd");
        $dumpvars(0, tb_sensor_pipeline);
    end


    // Monitors

    initial begin
        wait(resetn == 1);
        forever begin
            @(posedge clk);
            if (accel_valid_o)
                $display("ACCEL: ax=%0d ay=%0d az=%0d @ %0t",
                         ax_o, ay_o, az_o, $time);
            if (ppg_sample_valid)
                $display("PPG:   sample=%0d t=%0d @ %0t",
                         ppg_sample, ppg_sample_time, $time);
            if (epoch_done)
                $display("EPOCH: energy=%0d @ %0t",
                         motion_energy_epoch, $time);
        end
    end


    // PASS/FAIL — wait for at least 3 accel samples, 3 PPG samples,
    // and 1 epoch, then declare PASS

    int accel_count = 0;
    int ppg_count   = 0;
    int epoch_count = 0;

    initial begin
        wait(resetn == 1);
        forever @(posedge clk) begin
            if (accel_valid_o)    accel_count++;
            if (ppg_sample_valid) ppg_count++;
            if (epoch_done)       epoch_count++;

            if (accel_count >= 3 && ppg_count >= 3 && epoch_count >= 1) begin
                $display("PASS: accel=%0d ppg=%0d epochs=%0d",
                         accel_count, ppg_count, epoch_count);
                $finish;
            end
        end
    end

    // Timeout watchdog — 500M cycles (~10s sim time)
    initial begin
        wait(resetn == 1);
        repeat (500_000_000) @(posedge clk);
        $fatal(1, "TIMEOUT: sensor pipeline did not produce expected samples");
    end

endmodule
