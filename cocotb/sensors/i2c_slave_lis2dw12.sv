`timescale 1ns/1ps

// i2c_slave_lis2dw12.sv
//
// Simulation-only I2C slave model for the LIS2DW12 accelerometer.
// Connects to i2c_master.sv via the sim_* functional bus.
// Reads accel_digital.csv and responds as a real LIS2DW12 would.
//
// Register behavior:
//   0x27 STATUS : always returns 0x01 (DRDY=1)
//   0x28 DATA   : returns 6 bytes XL,XH,YL,YH,ZL,ZH (left-justified 16-bit)
//
// CSV format: ax,ay,az signed integers per row (14-bit values)
//
// CSV path is set at runtime via plusarg:
//   vvp sim.out +DATA_DIR=cocotb/sim/data   (from repo root)
//   vvp sim.out +DATA_DIR=sim/data          (from cocotb/)
//   vvp sim.out                             (uses default: sim/data)

module i2c_slave_lis2dw12 #(
    parameter [6:0]  I2C_ADDR   = 7'h18,
    parameter [7:0]  REG_STATUS = 8'h27,
    parameter [7:0]  REG_DATA   = 8'h28
)(
    input  wire        clk,
    input  wire        resetn,

    // Functional sim bus — driven by i2c_master
    input  wire        sim_req,
    input  wire [6:0]  sim_addr,
    input  wire [7:0]  sim_reg,
    input  wire [7:0]  sim_len,
    output reg         sim_ack,
    output reg  [7:0]  sim_rdata,
    output reg         sim_rvalid,
    output reg         sim_rlast,
    output reg         sim_err
);

    int    fd;
    int    r;
    int    raw_ax, raw_ay, raw_az;
    reg [15:0] ax16, ay16, az16;
    string data_dir;
    string csv_file;

    typedef enum logic [1:0] {
        RSP_IDLE   = 2'd0,
        RSP_STATUS = 2'd1,
        RSP_DATA   = 2'd2
    } rsp_state_t;

    rsp_state_t rsp_state;
    reg [2:0] byte_cnt;

    initial begin
        if (!$value$plusargs("DATA_DIR=%s", data_dir))
            data_dir = "sim/data";          // default: invoke from cocotb/
        csv_file = {data_dir, "/accel_digital.csv"};

        fd = $fopen(csv_file, "r");
        if (fd == 0) begin
            $display("ERROR: i2c_slave_lis2dw12: cannot open %s", csv_file);
            $fatal(1);
        end
        $display("i2c_slave_lis2dw12: opened %s", csv_file);
    end

    task read_next_sample;
        r = $fscanf(fd, "%d,%d,%d\n", raw_ax, raw_ay, raw_az);
        if (r == 3) begin
            ax16 = {raw_ax[13:0], 2'b00};
            ay16 = {raw_ay[13:0], 2'b00};
            az16 = {raw_az[13:0], 2'b00};
        end else begin
            ax16 = 16'h0; ay16 = 16'h0; az16 = 16'h0;
            $display("i2c_slave_lis2dw12: EOF at time %0t", $time);
        end
    endtask

    always @(posedge clk) begin
        if (!resetn) begin
            sim_ack    <= 1'b0;
            sim_rdata  <= 8'h00;
            sim_rvalid <= 1'b0;
            sim_rlast  <= 1'b0;
            sim_err    <= 1'b0;
            rsp_state  <= RSP_IDLE;
            byte_cnt   <= '0;
        end else begin
            sim_ack    <= 1'b0;
            sim_rvalid <= 1'b0;
            sim_rlast  <= 1'b0;
            sim_err    <= 1'b0;

            case (rsp_state)
                RSP_IDLE: begin
                    if (sim_req && (sim_addr == I2C_ADDR)) begin
                        sim_ack <= 1'b1;
                        if (sim_reg == REG_STATUS) begin
                            rsp_state <= RSP_STATUS;
                        end else if (sim_reg == REG_DATA) begin
                            read_next_sample;
                            byte_cnt  <= 3'd0;
                            rsp_state <= RSP_DATA;
                        end else begin
                            sim_rdata  <= 8'h00;
                            sim_rvalid <= 1'b1;
                            sim_rlast  <= 1'b1;
                        end
                    end
                end

                RSP_STATUS: begin
                    sim_rdata  <= 8'h01;   // DRDY=1
                    sim_rvalid <= 1'b1;
                    sim_rlast  <= 1'b1;
                    rsp_state  <= RSP_IDLE;
                end

                RSP_DATA: begin
                    sim_rvalid <= 1'b1;
                    case (byte_cnt)
                        3'd0: sim_rdata <= ax16[7:0];
                        3'd1: sim_rdata <= ax16[15:8];
                        3'd2: sim_rdata <= ay16[7:0];
                        3'd3: sim_rdata <= ay16[15:8];
                        3'd4: sim_rdata <= az16[7:0];
                        3'd5: sim_rdata <= az16[15:8];
                        default: sim_rdata <= 8'h00;
                    endcase
                    if (byte_cnt == 3'd5) begin
                        sim_rlast <= 1'b1;
                        rsp_state <= RSP_IDLE;
                    end
                    byte_cnt <= byte_cnt + 1;
                end

                default: rsp_state <= RSP_IDLE;
            endcase
        end
    end

endmodule
