`timescale 1ns/1ps
//
// i2c_slave_lis2dw12_raw.sv
//
// Simulation-only raw I2C slave for the LIS2DW12 accelerometer.
// Monitors SCL/SDA at pad level — works in GL sim where the chip's
// internal sim_* functional bus is not present.
//
// Transactions handled (matches accel_reader.sv usage):
//   Write any register : ACK silently (init writes to CTRL1=0x20, RANGE=0x23)
//   Read  from 0x28   : burst 6 bytes XL,XH,YL,YH,ZL,ZH from CSV
//   Read  other reg   : returns 0x00 per byte
//
// CSV path set at runtime:
//   +DATA_DIR=sim/data   (default when invoked from cocotb/)

module i2c_slave_lis2dw12_raw #(
    parameter [6:0] I2C_ADDR = 7'h19,
    parameter [7:0] REG_DATA = 8'h28
)(
    input  wire clk,
    input  wire resetn,
    input  wire scl_i,     // SCL from chip I2C master (pad-level)
    input  wire sda_i,     // SDA bus (open-drain combined; 0 = low on bus)
    output reg  sda_o      // slave SDA drive: 1=release(high-Z), 0=pull-low
);

    // ----------------------------------------------------------------
    // Edge / condition detection
    // ----------------------------------------------------------------
    reg scl_d, sda_d;
    always @(posedge clk or negedge resetn)
        if (!resetn) begin scl_d <= 1'b1; sda_d <= 1'b1; end
        else         begin scl_d <= scl_i; sda_d <= sda_i; end

    wire scl_rise   =  scl_i & ~scl_d;
    wire scl_fall   = ~scl_i &  scl_d;
    // START: SDA falls while SCL has been stable-high for >= 1 cycle
    wire start_cond =  scl_i &  scl_d &  sda_d & ~sda_i;
    // STOP:  SDA rises while SCL has been stable-high for >= 1 cycle
    wire stop_cond  =  scl_i &  scl_d & ~sda_d &  sda_i;

    // ----------------------------------------------------------------
    // State machine
    // ----------------------------------------------------------------
    localparam [3:0]
        S_IDLE    = 4'd0,
        S_RX_ADDR = 4'd1,   // receive 8 bits: 7-bit addr + R/W
        S_ACK     = 4'd2,   // drive ACK after address byte
        S_RX_REG  = 4'd3,   // receive 8-bit register pointer
        S_ACK_REG = 4'd4,   // drive ACK after register pointer
        S_WAIT    = 4'd5,   // after reg ACK: wait for rSTART or write bytes
        S_ACK_WD  = 4'd6,   // drive ACK for a received write-data byte
        S_TX      = 4'd7,   // drive data byte (MSB first)
        S_MACK    = 4'd8;   // wait for master ACK/NACK

    reg [3:0] state;
    reg [3:0] bit_cnt;   // counts SCL transitions within a byte (0..7)
    reg [7:0] rx_buf;    // shift register for incoming bits (MSB first)
    reg [7:0] reg_addr;  // latched register pointer
    reg [7:0] tx_byte;   // current byte being driven on SDA
    reg [2:0] byte_idx;  // byte position within a multi-byte response
    reg       ack_r;     // latched master ACK/NACK sample

    // ----------------------------------------------------------------
    // Sample data from CSV
    // ----------------------------------------------------------------
    reg [15:0] ax16, ay16, az16;
    int  fd, r_cnt;
    int  raw_ax, raw_ay, raw_az;
    string data_dir, csv_file;

    initial begin
        sda_o = 1'b1;
        if (!$value$plusargs("DATA_DIR=%s", data_dir))
            data_dir = "sim/data";
        csv_file = {data_dir, "/accel_digital.csv"};
        fd = $fopen(csv_file, "r");
        if (fd == 0) $fatal(1, "i2c_slave_lis2dw12_raw: cannot open %s", csv_file);
        $display("i2c_slave_lis2dw12_raw: opened %s", csv_file);
        ax16 = 16'd0; ay16 = 16'd0; az16 = 16'd0;
    end

    // Blocking assignments so the caller sees updated values immediately.
    task automatic read_next_sample;
        r_cnt = $fscanf(fd, "%d,%d,%d\n", raw_ax, raw_ay, raw_az);
        if (r_cnt != 3) begin
            $display("i2c_slave_lis2dw12_raw: EOF — rewinding");
            $rewind(fd);
            r_cnt = $fscanf(fd, "%d,%d,%d\n", raw_ax, raw_ay, raw_az);
        end
        ax16 = {raw_ax[13:0], 2'b00};
        ay16 = {raw_ay[13:0], 2'b00};
        az16 = {raw_az[13:0], 2'b00};
    endtask

    function automatic [7:0] data_byte;
        input [2:0] idx;
        case (idx)
            3'd0: data_byte = ax16[7:0];
            3'd1: data_byte = ax16[15:8];
            3'd2: data_byte = ay16[7:0];
            3'd3: data_byte = ay16[15:8];
            3'd4: data_byte = az16[7:0];
            3'd5: data_byte = az16[15:8];
            default: data_byte = 8'h00;
        endcase
    endfunction

    // ----------------------------------------------------------------
    // Combinational/sequential logic
    // ----------------------------------------------------------------
    always @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            state    <= S_IDLE;
            sda_o    <= 1'b1;
            bit_cnt  <= 4'd0;
            rx_buf   <= 8'h00;
            reg_addr <= 8'h00;
            tx_byte  <= 8'hFF;
            byte_idx <= 3'd0;
            ack_r    <= 1'b1;
        end else begin
            sda_o <= 1'b1;   // default: release SDA (high-Z via pull-up)

            // START and STOP take priority over per-state logic
            if (start_cond) begin
                state   <= S_RX_ADDR;
                bit_cnt <= 4'd0;
                rx_buf  <= 8'h00;
            end else if (stop_cond) begin
                state <= S_IDLE;
            end else begin
                case (state)
                    // ------------------------------------------------
                    S_IDLE: ;   // nothing — wait for start_cond above

                    // ------------------------------------------------
                    // Receive 7-bit I2C address + R/W bit (8 bits, MSB first)
                    // After 7 rises: rx_buf[6:0] = addr, next sda_i = R/W
                    S_RX_ADDR: begin
                        if (scl_rise) begin
                            rx_buf <= {rx_buf[6:0], sda_i};
                            if (bit_cnt == 4'd7) begin
                                // rx_buf_old[6:0] = ADDR[6:0] (see timing analysis)
                                if (rx_buf[6:0] == I2C_ADDR)
                                    state <= S_ACK;
                                else
                                    state <= S_IDLE;   // not our address
                                bit_cnt <= 4'd0;
                            end else begin
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    // ------------------------------------------------
                    // Drive ACK (SDA=0) for one SCL cycle after address
                    S_ACK: begin
                        sda_o <= 1'b0;
                        if (scl_fall) begin
                            // rx_buf[0] = R/W bit (shifted in on 8th SCL rise)
                            if (rx_buf[0]) begin
                                // Read request: load first data byte
                                if (reg_addr == REG_DATA)
                                    read_next_sample;
                                tx_byte  <= (reg_addr == REG_DATA) ? data_byte(3'd0) : 8'h00;
                                byte_idx <= 3'd0;
                                bit_cnt  <= 4'd0;
                                state    <= S_TX;
                            end else begin
                                // Write: receive register pointer next
                                rx_buf  <= 8'h00;
                                bit_cnt <= 4'd0;
                                state   <= S_RX_REG;
                            end
                        end
                    end

                    // ------------------------------------------------
                    // Receive 8-bit register pointer (MSB first)
                    S_RX_REG: begin
                        if (scl_rise) begin
                            rx_buf <= {rx_buf[6:0], sda_i};
                            if (bit_cnt == 4'd7) begin
                                // Assemble full byte: {old_rx_buf[6:0], sda_i}
                                reg_addr <= {rx_buf[6:0], sda_i};
                                bit_cnt  <= 4'd0;
                                state    <= S_ACK_REG;
                            end else begin
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    // ------------------------------------------------
                    // Drive ACK after register pointer
                    S_ACK_REG: begin
                        sda_o <= 1'b0;
                        if (scl_fall) begin
                            rx_buf  <= 8'h00;
                            bit_cnt <= 4'd0;
                            state   <= S_WAIT;
                        end
                    end

                    // ------------------------------------------------
                    // After register ACK: wait for repeated-START (→ S_RX_ADDR
                    // via global handler) or absorb write-data bytes
                    S_WAIT: begin
                        if (scl_rise) begin
                            rx_buf <= {rx_buf[6:0], sda_i};
                            if (bit_cnt == 4'd7) begin
                                // Write-data byte received (don't care about value)
                                bit_cnt <= 4'd0;
                                state   <= S_ACK_WD;
                            end else begin
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    // ------------------------------------------------
                    S_ACK_WD: begin
                        sda_o <= 1'b0;
                        if (scl_fall) begin
                            rx_buf  <= 8'h00;
                            bit_cnt <= 4'd0;
                            state   <= S_WAIT;   // wait for next byte or STOP
                        end
                    end

                    // ------------------------------------------------
                    // Drive data byte on SDA, MSB first.
                    // Shift on SCL fall so the next bit is ready before the
                    // following SCL rise.
                    S_TX: begin
                        sda_o <= tx_byte[7];
                        if (scl_fall) begin
                            if (bit_cnt == 4'd7) begin
                                // 8 bits sent; release SDA, wait for master ACK
                                state   <= S_MACK;
                                bit_cnt <= 4'd0;
                            end else begin
                                tx_byte <= {tx_byte[6:0], 1'b0};   // shift left
                                bit_cnt <= bit_cnt + 4'd1;
                            end
                        end
                    end

                    // ------------------------------------------------
                    // Wait for master ACK/NACK.
                    // Sample on SCL rise; decide on SCL fall to avoid counting
                    // the ACK SCL fall as a data SCL fall in S_TX.
                    S_MACK: begin
                        // sda_o = 1 (default): released so master can drive ACK
                        if (scl_rise)
                            ack_r <= sda_i;   // 0=ACK (send more), 1=NACK (done)
                        if (scl_fall) begin
                            if (!ack_r) begin
                                // ACK: advance to next byte
                                byte_idx <= byte_idx + 3'd1;
                                tx_byte  <= (reg_addr == REG_DATA) ?
                                            data_byte(byte_idx + 3'd1) : 8'h00;
                                bit_cnt  <= 4'd0;
                                state    <= S_TX;
                            end else begin
                                // NACK: master is done reading
                                state <= S_IDLE;
                            end
                        end
                    end

                    default: state <= S_IDLE;
                endcase
            end
        end
    end

endmodule
