`timescale 1ns/1ps

// i2c_master.sv
//
// Functional I2C master for wristwatch sleep tracker SoC.
//
// Accepts commands from accel_reader and ppg_fifo_reader via a shared
// command/response bus. Arbitrates between the two clients and executes
// I2C transactions against the simulation slave models.
//
// Command interface (driven by accel_reader / ppg_fifo_reader):
//   i2c_cmd_valid  -- client asserts to request a transaction
//   i2c_cmd_ready  -- master asserts when ready to accept
//   i2c_cmd_addr   -- 7-bit device address
//   i2c_cmd_reg    -- register/subaddress byte
//   i2c_cmd_len    -- number of bytes to read (or 1 for write)
//   i2c_cmd_write  -- 1=write, 0=read
//   i2c_cmd_wdata  -- write data byte (single byte writes only)
//
// Response interface (driven by master back to clients):
//   i2c_rsp_valid  -- one byte of response data is ready
//   i2c_rsp_data   -- response byte
//   i2c_rsp_last   -- this is the last byte (same cycle as final rsp_valid)
//   i2c_rsp_done   -- transaction complete
//   i2c_rsp_err    -- transaction failed (NACK from slave)
//   i2c_rsp_ready  -- client ready to accept response (flow control)
//
// Functional simulation bus (connects to i2c_slave_lis2dw12 / i2c_slave_adpd144ri):
//   sim_req/ack/rdata/rvalid/rlast/err
//
// Arbitration: round-robin between accel and PPG clients.

module i2c_master (
    input  wire        clk,
    input  wire        resetn,


    // Client 0: accel_reader

    input  wire        accel_cmd_valid_i,
    output reg         accel_cmd_ready_o,
    input  wire [6:0]  accel_cmd_addr_i,
    input  wire [7:0]  accel_cmd_reg_i,
    input  wire [7:0]  accel_cmd_len_i,
    input  wire        accel_cmd_write_i,
    input  wire [7:0]  accel_cmd_wdata_i,

    output reg         accel_rsp_valid_o,
    output reg  [7:0]  accel_rsp_data_o,
    output reg         accel_rsp_last_o,
    output reg         accel_rsp_done_o,
    output reg         accel_rsp_err_o,
    input  wire        accel_rsp_ready_i,


    // Client 1: ppg_fifo_reader

    input  wire        ppg_cmd_valid_i,
    output reg         ppg_cmd_ready_o,
    input  wire [6:0]  ppg_cmd_addr_i,
    input  wire [7:0]  ppg_cmd_reg_i,
    input  wire [7:0]  ppg_cmd_len_i,
    input  wire        ppg_cmd_write_i,
    input  wire [7:0]  ppg_cmd_wdata_i,

    output reg         ppg_rsp_valid_o,
    output reg  [7:0]  ppg_rsp_data_o,
    output reg         ppg_rsp_last_o,
    output reg         ppg_rsp_done_o,
    output reg         ppg_rsp_err_o,
    input  wire        ppg_rsp_ready_i,


    // Functional simulation bus

    output reg         sim_req,
    output reg  [6:0]  sim_addr,
    output reg  [7:0]  sim_reg,
    output reg  [7:0]  sim_len,
    output reg         sim_write,
    output reg  [7:0]  sim_wdata,
    input  wire        sim_ack,
    input  wire [7:0]  sim_rdata,
    input  wire        sim_rvalid,
    input  wire        sim_rlast,
    input  wire        sim_err
);

    typedef enum logic [2:0] {
        ST_IDLE     = 3'd0,
        ST_ARB      = 3'd1,
        ST_REQ      = 3'd2,
        ST_WAIT_ACK = 3'd3,
        ST_DATA     = 3'd4,
        ST_DONE     = 3'd5
    } state_t;

    state_t state_r;

    reg        active_client;
    reg        last_grant;

    reg [6:0]  cmd_addr_r;
    reg [7:0]  cmd_reg_r;
    reg [7:0]  cmd_len_r;
    reg        cmd_write_r;
    reg [7:0]  cmd_wdata_r;
    reg [7:0]  byte_cnt_r;

    wire accel_req = accel_cmd_valid_i;
    wire ppg_req   = ppg_cmd_valid_i;

    always @(posedge clk) begin
        if (!resetn) begin
            state_r           <= ST_IDLE;
            active_client     <= 1'b0;
            last_grant        <= 1'b1;
            accel_cmd_ready_o <= 1'b0;
            accel_rsp_valid_o <= 1'b0;
            accel_rsp_data_o  <= 8'h00;
            accel_rsp_last_o  <= 1'b0;
            accel_rsp_done_o  <= 1'b0;
            accel_rsp_err_o   <= 1'b0;
            ppg_cmd_ready_o   <= 1'b0;
            ppg_rsp_valid_o   <= 1'b0;
            ppg_rsp_data_o    <= 8'h00;
            ppg_rsp_last_o    <= 1'b0;
            ppg_rsp_done_o    <= 1'b0;
            ppg_rsp_err_o     <= 1'b0;
            sim_req           <= 1'b0;
            sim_addr          <= 7'h00;
            sim_reg           <= 8'h00;
            sim_len           <= 8'h00;
            sim_write         <= 1'b0;
            sim_wdata         <= 8'h00;
            cmd_addr_r        <= 7'h00;
            cmd_reg_r         <= 8'h00;
            cmd_len_r         <= 8'h00;
            cmd_write_r       <= 1'b0;
            cmd_wdata_r       <= 8'h00;
            byte_cnt_r        <= 8'h00;
        end else begin
            accel_cmd_ready_o <= 1'b0;
            accel_rsp_valid_o <= 1'b0;
            accel_rsp_last_o  <= 1'b0;
            accel_rsp_done_o  <= 1'b0;
            accel_rsp_err_o   <= 1'b0;
            ppg_cmd_ready_o   <= 1'b0;
            ppg_rsp_valid_o   <= 1'b0;
            ppg_rsp_last_o    <= 1'b0;
            ppg_rsp_done_o    <= 1'b0;
            ppg_rsp_err_o     <= 1'b0;
            sim_req           <= 1'b0;

            case (state_r)

                ST_IDLE: begin
                    if (accel_req || ppg_req)
                        state_r <= ST_ARB;
                end

                ST_ARB: begin
                    if (accel_req && ppg_req) begin
                        active_client <= ~last_grant;
                        last_grant    <= ~last_grant;
                    end else if (accel_req) begin
                        active_client <= 1'b0;
                        last_grant    <= 1'b0;
                    end else begin
                        active_client <= 1'b1;
                        last_grant    <= 1'b1;
                    end
                    state_r <= ST_REQ;
                end

                ST_REQ: begin
                    if (active_client == 1'b0) begin
                        accel_cmd_ready_o <= 1'b1;
                        cmd_addr_r  <= accel_cmd_addr_i;
                        cmd_reg_r   <= accel_cmd_reg_i;
                        cmd_len_r   <= accel_cmd_len_i;
                        cmd_write_r <= accel_cmd_write_i;
                        cmd_wdata_r <= accel_cmd_wdata_i;
                    end else begin
                        ppg_cmd_ready_o <= 1'b1;
                        cmd_addr_r  <= ppg_cmd_addr_i;
                        cmd_reg_r   <= ppg_cmd_reg_i;
                        cmd_len_r   <= ppg_cmd_len_i;
                        cmd_write_r <= ppg_cmd_write_i;
                        cmd_wdata_r <= ppg_cmd_wdata_i;
                    end
                    byte_cnt_r <= 8'h00;
                    state_r    <= ST_WAIT_ACK;
                end

                ST_WAIT_ACK: begin
                    sim_req   <= 1'b1;
                    sim_addr  <= cmd_addr_r;
                    sim_reg   <= cmd_reg_r;
                    sim_len   <= cmd_len_r;
                    sim_write <= cmd_write_r;
                    sim_wdata <= cmd_wdata_r;

                    if (sim_err) begin
                        if (active_client == 1'b0) begin
                            accel_rsp_err_o  <= 1'b1;
                            accel_rsp_done_o <= 1'b1;
                        end else begin
                            ppg_rsp_err_o  <= 1'b1;
                            ppg_rsp_done_o <= 1'b1;
                        end
                        state_r <= ST_DONE;
                    end else if (sim_ack) begin
                        sim_req <= 1'b0;
                        if (cmd_write_r) begin
                            // Write — no response bytes, signal done immediately
                            if (active_client == 1'b0)
                                accel_rsp_done_o <= 1'b1;
                            else
                                ppg_rsp_done_o <= 1'b1;
                            state_r <= ST_DONE;
                        end else begin
                            state_r <= ST_DATA;
                        end
                    end
                end

                ST_DATA: begin
                    if (sim_err) begin
                        if (active_client == 1'b0) begin
                            accel_rsp_err_o  <= 1'b1;
                            accel_rsp_done_o <= 1'b1;
                        end else begin
                            ppg_rsp_err_o  <= 1'b1;
                            ppg_rsp_done_o <= 1'b1;
                        end
                        state_r <= ST_DONE;
                    end else if (sim_rvalid) begin
                        byte_cnt_r <= byte_cnt_r + 1;

                        if (active_client == 1'b0) begin
                            accel_rsp_valid_o <= 1'b1;
                            accel_rsp_data_o  <= sim_rdata;
                            accel_rsp_last_o  <= sim_rlast;
                            if (sim_rlast) begin
                                accel_rsp_done_o <= 1'b1;
                                state_r <= ST_DONE;
                            end
                        end else begin
                            ppg_rsp_valid_o <= 1'b1;
                            ppg_rsp_data_o  <= sim_rdata;
                            ppg_rsp_last_o  <= sim_rlast;
                            if (sim_rlast) begin
                                ppg_rsp_done_o <= 1'b1;
                                state_r <= ST_DONE;
                            end
                        end
                    end
                end

                ST_DONE: begin
                    state_r <= ST_IDLE;
                end

                default: state_r <= ST_IDLE;
            endcase
        end
    end

endmodule

