`timescale 1ns/1ps

// i2c_master.sv
//
// I2C master for wristwatch sleep tracker SoC.
// Arbitrates between accel_reader (client 0) and ppg_fifo_reader (client 1)
// and executes register-read and register-write transactions.
//
// Two compile-time implementations selected by ifdef SIM:
//
//   SIM defined   : functional simulation bus (sim_req/sim_ack/sim_rdata).
//                   Fast zero-latency model used by cocotb testbenches.
//                   scl_o is held high and sda_oe held low (bus idle).
//
//   else (synthesis) : real I2C master at I2C_CLK_HZ (default 100 kHz).
//                   Drives scl_o (push-pull SCL) and sda_oe (open-drain SDA).
//                   sim_* outputs are held idle.
//
// Read transaction:
//   START, addr+W, ACK, reg, ACK, rSTART, addr+R, ACK,
//   [data, ACK] x (N-1), data, NACK, STOP
//
// Write transaction:
//   START, addr+W, ACK, reg, ACK, data, ACK, STOP

module i2c_master #(
    parameter integer CLK_HZ     = 10_000_000,
    parameter integer I2C_CLK_HZ = 100_000
) (
    input  wire        clk,
    input  wire        resetn,
    input  wire        en_i,

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

    // Physical I2C bus used in synthesis. SCL is push-pull (master always
    // drives it). SDA is open-drain: sda_oe=1 drives SDA low, sda_oe=0
    // releases SDA so the external pull-up makes it high.
    output reg         scl_o,
    input  wire        sda_i,
    output reg         sda_oe,

    // Functional simulation bus used in SIM. Ignored in synthesis.
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

    // System clocks per I2C quarter-period (25 at 10 MHz / 100 kHz).
    // HALF is used for data bits; QUARTER is used for START/STOP/rSTART phases.
    localparam integer QUARTER = CLK_HZ / (4 * I2C_CLK_HZ);
    localparam integer HALF    = QUARTER * 2;
    localparam integer TIMER_W = $clog2(HALF > 1 ? HALF : 2);

    // Transaction phase codes used in the synthesis path to track which byte
    // is currently being sent or received within a transaction.
    localparam [2:0] PHASE_ADDR_W = 3'd0;
    localparam [2:0] PHASE_REG    = 3'd1;
    localparam [2:0] PHASE_ADDR_R = 3'd2;
    localparam [2:0] PHASE_RX     = 3'd3;
    localparam [2:0] PHASE_TX     = 3'd4;

    // State encoding covers both SIM and synthesis paths. States unreachable
    // in a given path are caught by the default branch of the case statement.
    typedef enum logic [4:0] {
        ST_IDLE         = 5'd0,
        ST_ARB          = 5'd1,
        ST_REQ          = 5'd2,
        ST_SIM_WAIT_ACK = 5'd3,
        ST_SIM_DATA     = 5'd4,
        ST_SIM_DONE     = 5'd5,
        ST_S1           = 5'd6,  // bus idle guard before START
        ST_S2           = 5'd7,  // SDA falls while SCL=1 (START condition)
        ST_S3           = 5'd8,  // SCL falls, hold SDA low after START
        ST_BIT_LO       = 5'd9,  // SCL=0, SDA holds the bit to transmit
        ST_BIT_HI       = 5'd10, // SCL=1, hold SDA (slave samples here)
        ST_ACK_LO       = 5'd11, // SCL=0, SDA released for slave to drive ACK
        ST_ACK_HI       = 5'd12, // SCL=1, master samples SDA for ACK or NACK
        ST_RS1          = 5'd13, // SCL=0, release SDA before raising SCL
        ST_RS2          = 5'd14, // SCL=1, SDA=1 (setup for repeated START)
        ST_RS3          = 5'd15, // SDA falls while SCL=1 (repeated START)
        ST_RS4          = 5'd16, // SCL falls, hold SDA low after repeated START
        ST_RX_LO        = 5'd17, // SCL=0, SDA released so slave drives it
        ST_RX_HI        = 5'd18, // SCL=1, master samples SDA
        ST_RACK_LO      = 5'd19, // SCL=0, master drives ACK or NACK
        ST_RACK_HI      = 5'd20, // SCL=1, hold ACK or NACK
        ST_P1           = 5'd21, // SCL=0, SDA=0 (setup for STOP)
        ST_P2           = 5'd22, // SCL=1, SDA still low
        ST_P3           = 5'd23  // SDA rises while SCL=1 (STOP condition)
    } state_t;

    state_t              state_r;
    reg [TIMER_W-1:0]    timer_r;

    reg        active_client;
    reg        last_grant;

    reg [6:0]  cmd_addr_r;
    reg [7:0]  cmd_reg_r;
    reg [7:0]  cmd_len_r;
    reg        cmd_write_r;
    reg [7:0]  cmd_wdata_r;
    reg [7:0]  byte_cnt_r;

    // Synthesis-path working registers
    reg [2:0]  byte_phase_r;
    reg [2:0]  bit_cnt_r;
    reg [7:0]  sr_r; // TX/RX shift register, MSB transmitted and received first

    wire accel_req = accel_cmd_valid_i;
    wire ppg_req   = ppg_cmd_valid_i;

    // True when the byte currently being received is the last one.
    // Evaluated using byte_cnt_r before the end-of-byte increment.
    wire rx_last_w = (byte_cnt_r == cmd_len_r - 8'h01);

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
            byte_phase_r      <= 3'h0;
            bit_cnt_r         <= 3'h0;
            sr_r              <= 8'h00;
            timer_r           <= '0;
            scl_o             <= 1'b1;
            sda_oe            <= 1'b0;
        end else if (en_i) begin

            // Clear one-cycle pulse outputs at the start of every cycle
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

// `ifdef SIM
//             // SIM PATH: functional bus, no real I2C timing
//             sim_req <= 1'b0;
//             scl_o   <= 1'b1;
//             sda_oe  <= 1'b0;

//             case (state_r)

//                 ST_IDLE: begin
//                     if (accel_req || ppg_req)
//                         state_r <= ST_ARB;
//                 end

//                 ST_ARB: begin
//                     if (accel_req && ppg_req) begin
//                         active_client <= ~last_grant;
//                         last_grant    <= ~last_grant;
//                     end else if (accel_req) begin
//                         active_client <= 1'b0;
//                         last_grant    <= 1'b0;
//                     end else begin
//                         active_client <= 1'b1;
//                         last_grant    <= 1'b1;
//                     end
//                     state_r <= ST_REQ;
//                 end

//                 ST_REQ: begin
//                     if (active_client == 1'b0) begin
//                         accel_cmd_ready_o <= 1'b1;
//                         cmd_addr_r  <= accel_cmd_addr_i;
//                         cmd_reg_r   <= accel_cmd_reg_i;
//                         cmd_len_r   <= accel_cmd_len_i;
//                         cmd_write_r <= accel_cmd_write_i;
//                         cmd_wdata_r <= accel_cmd_wdata_i;
//                     end else begin
//                         ppg_cmd_ready_o <= 1'b1;
//                         cmd_addr_r  <= ppg_cmd_addr_i;
//                         cmd_reg_r   <= ppg_cmd_reg_i;
//                         cmd_len_r   <= ppg_cmd_len_i;
//                         cmd_write_r <= ppg_cmd_write_i;
//                         cmd_wdata_r <= ppg_cmd_wdata_i;
//                     end
//                     byte_cnt_r <= 8'h00;
//                     state_r    <= ST_SIM_WAIT_ACK;
//                 end

//                 ST_SIM_WAIT_ACK: begin
//                     sim_req   <= 1'b1;
//                     sim_addr  <= cmd_addr_r;
//                     sim_reg   <= cmd_reg_r;
//                     sim_len   <= cmd_len_r;
//                     sim_write <= cmd_write_r;
//                     sim_wdata <= cmd_wdata_r;

//                     if (sim_err) begin
//                         if (active_client == 1'b0) begin
//                             accel_rsp_err_o  <= 1'b1;
//                             accel_rsp_done_o <= 1'b1;
//                         end else begin
//                             ppg_rsp_err_o  <= 1'b1;
//                             ppg_rsp_done_o <= 1'b1;
//                         end
//                         state_r <= ST_SIM_DONE;
//                     end else if (sim_ack) begin
//                         sim_req <= 1'b0;
//                         if (cmd_write_r) begin
//                             if (active_client == 1'b0)
//                                 accel_rsp_done_o <= 1'b1;
//                             else
//                                 ppg_rsp_done_o <= 1'b1;
//                             state_r <= ST_SIM_DONE;
//                         end else begin
//                             state_r <= ST_SIM_DATA;
//                         end
//                     end
//                 end

//                 ST_SIM_DATA: begin
//                     if (sim_err) begin
//                         if (active_client == 1'b0) begin
//                             accel_rsp_err_o  <= 1'b1;
//                             accel_rsp_done_o <= 1'b1;
//                         end else begin
//                             ppg_rsp_err_o  <= 1'b1;
//                             ppg_rsp_done_o <= 1'b1;
//                         end
//                         state_r <= ST_SIM_DONE;
//                     end else if (sim_rvalid) begin
//                         byte_cnt_r <= byte_cnt_r + 8'h01;
//                         if (active_client == 1'b0) begin
//                             accel_rsp_valid_o <= 1'b1;
//                             accel_rsp_data_o  <= sim_rdata;
//                             accel_rsp_last_o  <= sim_rlast;
//                             if (sim_rlast) begin
//                                 accel_rsp_done_o <= 1'b1;
//                                 state_r <= ST_SIM_DONE;
//                             end
//                         end else begin
//                             ppg_rsp_valid_o <= 1'b1;
//                             ppg_rsp_data_o  <= sim_rdata;
//                             ppg_rsp_last_o  <= sim_rlast;
//                             if (sim_rlast) begin
//                                 ppg_rsp_done_o <= 1'b1;
//                                 state_r <= ST_SIM_DONE;
//                             end
//                         end
//                     end
//                 end

//                 ST_SIM_DONE: begin
//                     state_r <= ST_IDLE;
//                 end

//                 default: state_r <= ST_IDLE;
//             endcase

// `else
        // SYNTHESIS PATH: real I2C bus master
        sim_req   <= 1'b0;
        sim_addr  <= 7'h00;
        sim_reg   <= 8'h00;
        sim_len   <= 8'h00;
        sim_write <= 1'b0;
        sim_wdata <= 8'h00;

        // Timer counts down each cycle; state transitions load a new value
        // which shadows the decrement on the same clock edge
        if (timer_r != '0)
            timer_r <= timer_r - 1'b1;

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
                state_r <= ST_S1;
                scl_o   <= 1'b1;
                sda_oe  <= 1'b0;
                timer_r <= QUARTER - 1;
            end

            ST_S1: begin
                if (timer_r == '0) begin
                    state_r <= ST_S2;
                    sda_oe  <= 1'b1; // SDA falls while SCL=1: START condition
                    timer_r <= QUARTER - 1;
                end
            end

            ST_S2: begin
                if (timer_r == '0) begin
                    state_r <= ST_S3;
                    scl_o   <= 1'b0; // SCL falls, hold SDA low
                    timer_r <= QUARTER - 1;
                end
            end

            ST_S3: begin
                if (timer_r == '0) begin
                    // Load addr+W into the shift register and begin the first
                    // TX bit. sda_oe is driven from cmd_addr_r[6] directly
                    // (combinatorial) because sr_r is not readable until the
                    // next clock edge.
                    sr_r         <= {cmd_addr_r, 1'b0};
                    bit_cnt_r    <= 3'd7;
                    byte_phase_r <= PHASE_ADDR_W;
                    state_r      <= ST_BIT_LO;
                    sda_oe       <= ~cmd_addr_r[6];
                    timer_r      <= HALF - 1;
                end
            end

            ST_BIT_LO: begin
                if (timer_r == '0) begin
                    state_r <= ST_BIT_HI;
                    scl_o   <= 1'b1; // SCL rises; slave samples SDA during this phase
                    timer_r <= HALF - 1;
                end
            end

            ST_BIT_HI: begin
                if (timer_r == '0) begin
                    if (bit_cnt_r != 3'd0) begin
                        // Shift register left; the next bit to drive is old sr[6]
                        // which becomes the new sr[7] after the shift
                        sr_r      <= {sr_r[6:0], 1'b0};
                        bit_cnt_r <= bit_cnt_r - 1'b1;
                        state_r   <= ST_BIT_LO;
                        scl_o     <= 1'b0;
                        sda_oe    <= ~sr_r[6];
                        timer_r   <= HALF - 1;
                    end else begin
                        // All 8 bits sent; release SDA so the slave can drive ACK
                        state_r <= ST_ACK_LO;
                        scl_o   <= 1'b0;
                        sda_oe  <= 1'b0;
                        timer_r <= HALF - 1;
                    end
                end
            end

            ST_ACK_LO: begin
                if (timer_r == '0) begin
                    state_r <= ST_ACK_HI;
                    scl_o   <= 1'b1; // SCL rises; master will sample SDA next
                    timer_r <= HALF - 1;
                end
            end

            ST_ACK_HI: begin
                if (timer_r == '0) begin
                    if (sda_i) begin
                        // NACK: abort the transaction, issue STOP, report error
                        if (active_client == 1'b0) begin
                            accel_rsp_err_o  <= 1'b1;
                            accel_rsp_done_o <= 1'b1;
                        end else begin
                            ppg_rsp_err_o  <= 1'b1;
                            ppg_rsp_done_o <= 1'b1;
                        end
                        state_r <= ST_P1;
                        scl_o   <= 1'b0;
                        sda_oe  <= 1'b1; // drive SDA low to set up STOP
                        timer_r <= QUARTER - 1;
                    end else begin
                        // ACK received; next step depends on the transaction phase
                        case (byte_phase_r)

                            PHASE_ADDR_W: begin
                                // Address+W was ACK'd; send register address byte next
                                sr_r         <= cmd_reg_r;
                                bit_cnt_r    <= 3'd7;
                                byte_phase_r <= PHASE_REG;
                                state_r      <= ST_BIT_LO;
                                scl_o        <= 1'b0;
                                sda_oe       <= ~cmd_reg_r[7];
                                timer_r      <= HALF - 1;
                            end

                            PHASE_REG: begin
                                if (cmd_write_r) begin
                                    // Write transaction: send the data byte next
                                    sr_r         <= cmd_wdata_r;
                                    bit_cnt_r    <= 3'd7;
                                    byte_phase_r <= PHASE_TX;
                                    state_r      <= ST_BIT_LO;
                                    scl_o        <= 1'b0;
                                    sda_oe       <= ~cmd_wdata_r[7];
                                    timer_r      <= HALF - 1;
                                end else begin
                                    // Read transaction: generate repeated START next
                                    byte_phase_r <= PHASE_ADDR_R;
                                    state_r      <= ST_RS1;
                                    scl_o        <= 1'b0;
                                    sda_oe       <= 1'b0;
                                    timer_r      <= QUARTER - 1;
                                end
                            end

                            PHASE_ADDR_R: begin
                                // addr+R was ACK'd; begin receiving data bytes
                                byte_cnt_r   <= 8'h00;
                                bit_cnt_r    <= 3'd7;
                                byte_phase_r <= PHASE_RX;
                                state_r      <= ST_RX_LO;
                                scl_o        <= 1'b0;
                                sda_oe       <= 1'b0;
                                timer_r      <= HALF - 1;
                            end

                            PHASE_TX: begin
                                // Write data was ACK'd; transaction is complete
                                if (active_client == 1'b0)
                                    accel_rsp_done_o <= 1'b1;
                                else
                                    ppg_rsp_done_o <= 1'b1;
                                state_r <= ST_P1;
                                scl_o   <= 1'b0;
                                sda_oe  <= 1'b1;
                                timer_r <= QUARTER - 1;
                            end

                            default: begin
                                state_r <= ST_P1;
                                scl_o   <= 1'b0;
                                sda_oe  <= 1'b1;
                                timer_r <= QUARTER - 1;
                            end

                        endcase
                    end
                end
            end

            ST_RS1: begin
                if (timer_r == '0) begin
                    // Release SDA high before raising SCL for repeated START
                    state_r <= ST_RS2;
                    scl_o   <= 1'b1;
                    sda_oe  <= 1'b0;
                    timer_r <= QUARTER - 1;
                end
            end

            ST_RS2: begin
                if (timer_r == '0) begin
                    // SCL=1, SDA=1; now pull SDA low to create repeated START
                    state_r <= ST_RS3;
                    sda_oe  <= 1'b1;
                    timer_r <= QUARTER - 1;
                end
            end

            ST_RS3: begin
                if (timer_r == '0) begin
                    state_r <= ST_RS4;
                    scl_o   <= 1'b0; // SCL falls after repeated START
                    timer_r <= QUARTER - 1;
                end
            end

            ST_RS4: begin
                if (timer_r == '0) begin
                    // byte_phase_r is already PHASE_ADDR_R from ST_ACK_HI
                    sr_r      <= {cmd_addr_r, 1'b1};
                    bit_cnt_r <= 3'd7;
                    state_r   <= ST_BIT_LO;
                    scl_o     <= 1'b0;
                    sda_oe    <= ~cmd_addr_r[6];
                    timer_r   <= HALF - 1;
                end
            end

            ST_RX_LO: begin
                if (timer_r == '0) begin
                    state_r <= ST_RX_HI;
                    scl_o   <= 1'b1; // SCL rises; master samples SDA this phase
                    timer_r <= HALF - 1;
                end
            end

            ST_RX_HI: begin
                if (timer_r == '0) begin
                    sr_r <= {sr_r[6:0], sda_i}; // shift received bit into LSB
                    if (bit_cnt_r != 3'd0) begin
                        bit_cnt_r <= bit_cnt_r - 1'b1;
                        state_r   <= ST_RX_LO;
                        scl_o     <= 1'b0;
                        timer_r   <= HALF - 1;
                    end else begin
                        // Full byte received; output response data and
                        // set ACK (more bytes coming) or NACK (last byte)
                        byte_cnt_r <= byte_cnt_r + 8'h01;
                        bit_cnt_r  <= 3'd7;
                        if (active_client == 1'b0) begin
                            accel_rsp_valid_o <= 1'b1;
                            accel_rsp_data_o  <= {sr_r[6:0], sda_i};
                            accel_rsp_last_o  <= rx_last_w;
                            accel_rsp_done_o  <= rx_last_w;
                        end else begin
                            ppg_rsp_valid_o <= 1'b1;
                            ppg_rsp_data_o  <= {sr_r[6:0], sda_i};
                            ppg_rsp_last_o  <= rx_last_w;
                            ppg_rsp_done_o  <= rx_last_w;
                        end
                        state_r <= ST_RACK_LO;
                        scl_o   <= 1'b0;
                        sda_oe  <= ~rx_last_w; // drive low=ACK; release=NACK on last byte
                        timer_r <= HALF - 1;
                    end
                end
            end

            ST_RACK_LO: begin
                if (timer_r == '0) begin
                    state_r <= ST_RACK_HI;
                    scl_o   <= 1'b1;
                    timer_r <= HALF - 1;
                end
            end

            ST_RACK_HI: begin
                if (timer_r == '0) begin
                    if (byte_cnt_r < cmd_len_r) begin
                        state_r <= ST_RX_LO;
                        scl_o   <= 1'b0;
                        sda_oe  <= 1'b0;
                        timer_r <= HALF - 1;
                    end else begin
                        // All bytes received; issue STOP
                        state_r <= ST_P1;
                        scl_o   <= 1'b0;
                        sda_oe  <= 1'b1;
                        timer_r <= QUARTER - 1;
                    end
                end
            end

            ST_P1: begin
                if (timer_r == '0) begin
                    state_r <= ST_P2;
                    scl_o   <= 1'b1; // SCL rises; SDA is still low
                    timer_r <= QUARTER - 1;
                end
            end

            ST_P2: begin
                if (timer_r == '0) begin
                    state_r <= ST_P3;
                    sda_oe  <= 1'b0; // SDA rises while SCL=1: STOP condition
                    timer_r <= QUARTER - 1;
                end
            end

            ST_P3: begin
                if (timer_r == '0) begin
                    state_r <= ST_IDLE;
                end
            end

            default: state_r <= ST_IDLE;

        endcase
// `endif

        end
    end

endmodule
