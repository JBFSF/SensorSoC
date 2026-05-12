`timescale 1ns/1ps
`default_nettype none

// Standalone testbench for the synthesis path of i2c_master.sv.
// Compiled WITHOUT -DSIM so the real bit-banging I2C state machine runs.
//
// Test: 1-byte read from the accelerometer (addr=0x19, reg=0x27).
// A simple I2C slave BFM monitors scl/sda, ACKs the address and register,
// and drives back 0xA5. The test checks that accel_rsp_data arrives
// correctly and no error flag is set.
//
// Compile and run:
//   iverilog -g2012 -o tb_i2c_master_rtl.vvp \
//            cocotb/sim/tb/tb_i2c_master_rtl.sv src/i2c_master.sv
//   vvp tb_i2c_master_rtl.vvp

module tb_i2c_master_rtl;

    // CLK/I2C ratio: QUARTER = 1000/(4*100) = 2 cycles, HALF = 4 cycles.
    // Each I2C bit period = 2*HALF = 8 system clocks — fast for simulation.
    localparam integer CLK_HZ     = 1000;
    localparam integer I2C_CLK_HZ = 100;

    localparam [6:0] ACCEL_ADDR = 7'h19;
    localparam [7:0] ACCEL_REG  = 8'h27;
    localparam [7:0] SLAVE_DATA = 8'hA5;

    logic clk    = 1'b0;
    logic resetn = 1'b0;
    always #1 clk = ~clk;

    // Accel command
    logic accel_cmd_valid = 1'b0;
    wire  accel_cmd_ready;
    wire  accel_rsp_valid;
    wire  [7:0] accel_rsp_data;
    wire  accel_rsp_last;
    wire  accel_rsp_done;
    wire  accel_rsp_err;

    // Physical I2C bus. SDA is open-drain: driven low by either master
    // (via sda_oe) or the slave BFM (via slave_sda_lo). Pulled high otherwise.
    wire scl;
    wire sda_oe;
    logic slave_sda_lo = 1'b0;
    wire sda = (sda_oe | slave_sda_lo) ? 1'b0 : 1'b1;

    i2c_master #(
        .CLK_HZ    (CLK_HZ),
        .I2C_CLK_HZ(I2C_CLK_HZ)
    ) u_dut (
        .clk              (clk),
        .resetn           (resetn),
        .en_i             (1'b1),

        .accel_cmd_valid_i(accel_cmd_valid),
        .accel_cmd_ready_o(accel_cmd_ready),
        .accel_cmd_addr_i (ACCEL_ADDR),
        .accel_cmd_reg_i  (ACCEL_REG),
        .accel_cmd_len_i  (8'd1),
        .accel_cmd_write_i(1'b0),
        .accel_cmd_wdata_i(8'h00),
        .accel_rsp_valid_o(accel_rsp_valid),
        .accel_rsp_data_o (accel_rsp_data),
        .accel_rsp_last_o (accel_rsp_last),
        .accel_rsp_done_o (accel_rsp_done),
        .accel_rsp_err_o  (accel_rsp_err),
        .accel_rsp_ready_i(1'b1),

        .ppg_cmd_valid_i  (1'b0),
        .ppg_cmd_ready_o  (),
        .ppg_cmd_addr_i   (7'h0),
        .ppg_cmd_reg_i    (8'h0),
        .ppg_cmd_len_i    (8'd0),
        .ppg_cmd_write_i  (1'b0),
        .ppg_cmd_wdata_i  (8'h0),
        .ppg_rsp_valid_o  (),
        .ppg_rsp_data_o   (),
        .ppg_rsp_last_o   (),
        .ppg_rsp_done_o   (),
        .ppg_rsp_err_o    (),
        .ppg_rsp_ready_i  (1'b1),

        .scl_o  (scl),
        .sda_i  (sda),
        .sda_oe (sda_oe),

        // Synthesis path holds these outputs idle; tie inputs to inactive values.
        .sim_req   (),
        .sim_addr  (),
        .sim_reg   (),
        .sim_len   (),
        .sim_write (),
        .sim_wdata (),
        .sim_ack   (1'b0),
        .sim_rdata (8'h00),
        .sim_rvalid(1'b0),
        .sim_rlast (1'b0),
        .sim_err   (1'b1)
    );

    
    // I2C slave BFM tasks
    

    // Receive 8 bits MSB-first by sampling SDA on each SCL rising edge.
    task automatic recv_byte(output logic [7:0] b);
        integer i;
        b = 8'h00;
        for (i = 7; i >= 0; i = i - 1) begin
            @(posedge scl);
            b[i] = sda;
        end
    endtask

    // Drive ACK: pull SDA low for one SCL high period after the 8th bit.
    task automatic send_ack;
        @(negedge scl);         // SCL falls after 8th bit
        slave_sda_lo = 1'b1;   // ACK: pull SDA low
        @(posedge scl);         // SCL rises: master samples ACK
        @(negedge scl);         // SCL falls: release
        slave_sda_lo = 1'b0;
    endtask

    // Drive one data byte MSB-first. Called while SCL is already low
    // (right after send_ack returns, which leaves SCL low).
    task automatic send_byte(input [7:0] b);
        integer i;
        for (i = 7; i >= 0; i = i - 1) begin
            slave_sda_lo = ~b[i];  // low=0, released=1 (open-drain)
            @(posedge scl);        // master samples on SCL rising edge
            @(negedge scl);        // SCL falls, advance to next bit
        end
        slave_sda_lo = 1'b0;       // release SDA for master NACK
    endtask

    // Detect a START or repeated START: SDA falls while SCL=1.
    task automatic wait_start;
        logic found;
        found = 1'b0;
        while (!found) begin
            @(negedge sda);
            if (scl == 1'b1) found = 1'b1;
        end
    endtask

    
    // Slave BFM process
    

    logic [7:0] rx;

    initial begin
        // START condition
        wait_start();
        $display("[SLAVE] START detected");

        // Receive address + W (should be {ACCEL_ADDR, 1'b0} = 0x32)
        recv_byte(rx);
        if (rx !== {ACCEL_ADDR, 1'b0})
            $display("[SLAVE] WARNING addr+W: got 0x%02h, expected 0x%02h",
                     rx, {ACCEL_ADDR, 1'b0});
        else
            $display("[SLAVE] addr+W 0x%02h OK", rx);
        send_ack();

        // Receive register address (should be ACCEL_REG = 0x27)
        recv_byte(rx);
        if (rx !== ACCEL_REG)
            $display("[SLAVE] WARNING reg: got 0x%02h, expected 0x%02h", rx, ACCEL_REG);
        else
            $display("[SLAVE] reg 0x%02h OK", rx);
        send_ack();

        // Repeated START
        wait_start();
        $display("[SLAVE] rSTART detected");

        // Receive address + R (should be {ACCEL_ADDR, 1'b1} = 0x33)
        recv_byte(rx);
        if (rx !== {ACCEL_ADDR, 1'b1})
            $display("[SLAVE] WARNING addr+R: got 0x%02h, expected 0x%02h",
                     rx, {ACCEL_ADDR, 1'b1});
        else
            $display("[SLAVE] addr+R 0x%02h OK", rx);
        send_ack();

        // Drive data byte; master will NACK (it only expects 1 byte)
        $display("[SLAVE] driving data 0x%02h", SLAVE_DATA);
        send_byte(SLAVE_DATA);

        // STOP: SDA rises while SCL=1
        begin
            logic found_stop;
            found_stop = 1'b0;
            while (!found_stop) begin
                @(posedge sda);
                if (scl == 1'b1) found_stop = 1'b1;
            end
            $display("[SLAVE] STOP detected");
        end
    end

    
    // Test stimulus and result check
    

    logic [7:0] captured_data = 8'hXX;
    integer     timeout;

    initial begin
        $dumpfile("tb_i2c_master_rtl.vcd");
        $dumpvars(0, tb_i2c_master_rtl);

        // Release reset
        resetn = 1'b0;
        repeat(4) @(posedge clk);
        resetn = 1'b1;
        repeat(4) @(posedge clk);

        // Hold accel_cmd_valid high until the master pulses accel_cmd_ready.
        // The SM latches the command in ST_REQ (one cycle after ST_ARB).
        accel_cmd_valid = 1'b1;
        @(posedge clk);
        while (!accel_cmd_ready) @(posedge clk);
        accel_cmd_valid = 1'b0;
        $display("[TB]   command accepted");

        // Capture data when the master outputs the last valid byte.
        timeout = 0;
        while (!(accel_rsp_valid && accel_rsp_last)) begin
            @(posedge clk);
            if (++timeout > 10000) begin
                $display("FAIL: timeout waiting for rsp_valid+rsp_last");
                $finish;
            end
        end
        captured_data = accel_rsp_data;

        // Wait for done (STOP condition reached in state machine).
        timeout = 0;
        while (!accel_rsp_done) begin
            @(posedge clk);
            if (++timeout > 500) begin
                $display("FAIL: timeout waiting for rsp_done after data");
                $finish;
            end
        end

        // Verdict
        if (accel_rsp_err) begin
            $display("FAIL: accel_rsp_err asserted");
            $finish;
        end
        if (captured_data !== SLAVE_DATA) begin
            $display("FAIL: expected data=0x%02h, got 0x%02h", SLAVE_DATA, captured_data);
            $finish;
        end

        $display("PASS: data=0x%02h, no errors", captured_data);
        $finish;
    end

    // Hard safety timeout
    initial begin
        #500_000;
        $display("FATAL: global simulation timeout — check state machine");
        $finish;
    end

endmodule
