`timescale 1ns/1ps

// Host I2C register bridge with event + IRQC proxy controls.
// Exposes an 8-bit host register map and threshold-triggered IRQ events.
// Designed for simulation bring-up and SoC integration testing.

module host_i2c_bridge_regs (
    input  wire        clk,
    input  wire        resetn,

    input  wire        wr_en_i,
    input  wire [7:0]  wr_addr_i,
    input  wire [7:0]  wr_data_i,

    input  wire [7:0]  rd_addr_i,
    output reg  [7:0]  rd_data_o,

    input  wire        proto_err_i,
    input  wire [31:0] ml_score_i,
    output reg         event_o,
    output wire [31:0] cfg_target_wake_sec_o,
    output wire [31:0] cfg_window_sec_o,
    output wire [15:0] cfg_step_sec_o,
    output wire [15:0] cfg_motion_hi_th_o,
    output wire [7:0]  cfg_motion_hi_count_o,
    output wire [7:0]  cfg_policy_o,
    output wire [15:0] cfg_conf_thr_o,

    // Proxy command path to irq_ctrl_mmio sideband interface
    output reg         irqc_req_o,
    output reg         irqc_we_o,
    output reg  [7:0]  irqc_off_o,
    output reg  [31:0] irqc_wdata_o,
    input  wire        irqc_ready_i,
    input  wire [31:0] irqc_rdata_i
);
    localparam [7:0] REG_WHOAMI      = 8'h00;
    localparam [7:0] REG_VERSION     = 8'h01;
    localparam [7:0] REG_STATUS      = 8'h02;
    localparam [7:0] REG_CTRL        = 8'h03;
    localparam [7:0] REG_IRQ_KICK    = 8'h04;
    localparam [7:0] REG_IRQ_COUNT_L = 8'h05;
    localparam [7:0] REG_IRQ_COUNT_H = 8'h06;
    localparam [7:0] REG_WAKE_TS0    = 8'h10;
    localparam [7:0] REG_WAKE_TS1    = 8'h11;
    localparam [7:0] REG_WAKE_TS2    = 8'h12;
    localparam [7:0] REG_WAKE_TS3    = 8'h13;
    localparam [7:0] REG_WAKE_WIN_L  = 8'h14;
    localparam [7:0] REG_WAKE_WIN_H  = 8'h15;
    localparam [7:0] REG_STEP_SEC_L  = 8'h16;
    localparam [7:0] REG_STEP_SEC_H  = 8'h17;
    localparam [7:0] REG_MOTION_TH_L = 8'h18;
    localparam [7:0] REG_MOTION_TH_H = 8'h19;
    localparam [7:0] REG_MOTION_CNT  = 8'h1A;
    localparam [7:0] REG_WAKE_POLICY = 8'h1B; // bit0=deadline_override

    localparam [7:0] REG_IRQC_OFF    = 8'h20;
    localparam [7:0] REG_IRQC_W0     = 8'h21;
    localparam [7:0] REG_IRQC_W1     = 8'h22;
    localparam [7:0] REG_IRQC_W2     = 8'h23;
    localparam [7:0] REG_IRQC_W3     = 8'h24;
    localparam [7:0] REG_IRQC_CMD    = 8'h25; // bit0=GO, bit1=WE
    localparam [7:0] REG_IRQC_STAT   = 8'h26; // bit0=DONE, bit1=ERR (W1C)
    localparam [7:0] REG_IRQC_R0     = 8'h28;
    localparam [7:0] REG_IRQC_R1     = 8'h29;
    localparam [7:0] REG_IRQC_R2     = 8'h2A;
    localparam [7:0] REG_IRQC_R3     = 8'h2B;

    localparam [7:0] REG_CONF_THR_L  = 8'h30;
    localparam [7:0] REG_CONF_THR_H  = 8'h31;
    localparam [7:0] REG_CONF_CTRL   = 8'h32; // bit0=en, bit1=irq_en, bit2=clear sticky
    localparam [7:0] REG_CONF_STAT   = 8'h33; // bit0 live, bit1 cross_sticky, bit2 fired_sticky, bit3 armed
    localparam [7:0] REG_LOGIT0_L    = 8'h34;
    localparam [7:0] REG_LOGIT0_H    = 8'h35;
    localparam [7:0] REG_LOGIT1_L    = 8'h36;
    localparam [7:0] REG_LOGIT1_H    = 8'h37;
    localparam [7:0] REG_CONF_ABS_L  = 8'h38;
    localparam [7:0] REG_CONF_ABS_H  = 8'h39;

    // STATUS bits
    localparam integer ST_IRQ_KICK_SEEN = 0;
    localparam integer ST_I2C_RX_ERROR  = 1;
    localparam integer ST_I2C_PROTO_ERR = 2;

    reg        irq_bridge_en;
    reg [7:0]  status;
    reg [15:0] irq_count;

    reg [7:0]  irqc_off;
    reg [31:0] irqc_wdata;
    reg [31:0] irqc_rdata_latched;
    reg [1:0]  irqc_stat; // bit0 done, bit1 err
    reg        irqc_busy;
    reg        irqc_req_we_pending;
    reg [7:0]  irqc_req_off_pending;
    reg [31:0] irqc_req_wdata_pending;

    reg [15:0] conf_thr;
    reg        conf_en;
    reg        conf_irq_en;
    reg        conf_armed;
    reg        conf_cross_seen_sticky;
    reg        conf_thr_irq_fired_sticky;
    reg [31:0] cfg_target_wake_sec;
    reg [31:0] cfg_window_sec;
    reg [15:0] cfg_step_sec;
    reg [15:0] cfg_motion_hi_th;
    reg [7:0]  cfg_motion_hi_count;
    reg [7:0]  cfg_policy;

    // Firmware writes the final confidence score into ml_score_i. The host
    // register bridge exposes that score directly for thresholding and readback.
    wire [15:0] score_conf = ml_score_i[15:0];
    wire [15:0] score_proxy0 = score_conf;
    wire [15:0] score_proxy1 = 16'h0000;
    wire        above_thr_live = (score_conf >= conf_thr);

    wire in_cfg_window    = (wr_addr_i >= 8'h10) && (wr_addr_i <= 8'h1B);
    wire in_irqc_window   = (wr_addr_i >= 8'h20) && (wr_addr_i <= 8'h2B);
    assign cfg_target_wake_sec_o = cfg_target_wake_sec;
    assign cfg_window_sec_o = cfg_window_sec;
    assign cfg_step_sec_o = cfg_step_sec;
    assign cfg_motion_hi_th_o = cfg_motion_hi_th;
    assign cfg_motion_hi_count_o = cfg_motion_hi_count;
    assign cfg_policy_o = cfg_policy;
    assign cfg_conf_thr_o = conf_thr;

    reg manual_kick_pulse;
    reg threshold_pulse;
    always @(posedge clk) begin
        

        if (!resetn) begin
            irq_bridge_en      <= 1'b1;
            status             <= 8'h00;
            irq_count          <= 16'h0000;
            event_o            <= 1'b0;

            irqc_req_o         <= 1'b0;
            irqc_we_o          <= 1'b0;
            irqc_off_o         <= 8'h00;
            irqc_wdata_o       <= 32'h0;
            irqc_off           <= 8'h00;
            irqc_wdata         <= 32'h0;
            irqc_rdata_latched <= 32'h0;
            irqc_stat          <= 2'b00;
            irqc_busy          <= 1'b0;
            irqc_req_we_pending <= 1'b0;
            irqc_req_off_pending <= 8'h00;
            irqc_req_wdata_pending <= 32'h0;

            conf_thr <= 16'h0400;
            conf_en  <= 1'b0;
            conf_irq_en <= 1'b0;
            conf_armed <= 1'b1;
            conf_cross_seen_sticky <= 1'b0;
            conf_thr_irq_fired_sticky <= 1'b0;
            cfg_target_wake_sec <= 32'd1800;
            cfg_window_sec <= 32'd1800;
            cfg_step_sec <= 16'd300;
            cfg_motion_hi_th <= 16'd800;
            cfg_motion_hi_count <= 8'd2;
            cfg_policy <= 8'h01;
        end else begin
            manual_kick_pulse = 1'b0;
            threshold_pulse   = 1'b0;

            event_o    <= 1'b0;
            irqc_req_o <= 1'b0;

            if (proto_err_i)
                status[ST_I2C_PROTO_ERR] <= 1'b1;

            // crossing-only threshold IRQ behavior with auto re-arm below threshold
            if (!above_thr_live)
                conf_armed <= 1'b1;

            if (conf_en && conf_irq_en && conf_armed && above_thr_live) begin
                threshold_pulse = 1'b1;
                conf_cross_seen_sticky <= 1'b1;
                conf_thr_irq_fired_sticky <= 1'b1;
                conf_armed <= 1'b0;
            end

            if (wr_en_i) begin
                case (wr_addr_i)
                    REG_STATUS: begin
                        status <= status & ~wr_data_i; // W1C
                    end
                    REG_CTRL: begin
                        irq_bridge_en <= wr_data_i[0];
                    end
                    REG_IRQ_KICK: begin
                        if (wr_data_i[0] && irq_bridge_en) begin
                            manual_kick_pulse = 1'b1;
                            status[ST_IRQ_KICK_SEEN] <= 1'b1;
                        end
                    end
                    REG_WAKE_TS0: cfg_target_wake_sec[7:0] <= wr_data_i;
                    REG_WAKE_TS1: cfg_target_wake_sec[15:8] <= wr_data_i;
                    REG_WAKE_TS2: cfg_target_wake_sec[23:16] <= wr_data_i;
                    REG_WAKE_TS3: cfg_target_wake_sec[31:24] <= wr_data_i;
                    REG_WAKE_WIN_L: cfg_window_sec[7:0] <= wr_data_i;
                    REG_WAKE_WIN_H: cfg_window_sec[15:8] <= wr_data_i;
                    REG_STEP_SEC_L: cfg_step_sec[7:0] <= wr_data_i;
                    REG_STEP_SEC_H: cfg_step_sec[15:8] <= wr_data_i;
                    REG_MOTION_TH_L: cfg_motion_hi_th[7:0] <= wr_data_i;
                    REG_MOTION_TH_H: cfg_motion_hi_th[15:8] <= wr_data_i;
                    REG_MOTION_CNT: cfg_motion_hi_count <= wr_data_i;
                    REG_WAKE_POLICY: cfg_policy <= wr_data_i;

                    REG_IRQC_OFF: irqc_off <= wr_data_i;
                    REG_IRQC_W0:  irqc_wdata[7:0] <= wr_data_i;
                    REG_IRQC_W1:  irqc_wdata[15:8] <= wr_data_i;
                    REG_IRQC_W2:  irqc_wdata[23:16] <= wr_data_i;
                    REG_IRQC_W3:  irqc_wdata[31:24] <= wr_data_i;

                    REG_IRQC_CMD: begin
                        if (wr_data_i[0]) begin
                            if (!irqc_busy) begin
                                irqc_busy <= 1'b1;
                                irqc_req_we_pending <= wr_data_i[1];
                                irqc_req_off_pending <= irqc_off;
                                irqc_req_wdata_pending <= irqc_wdata;
                                irqc_stat <= 2'b00;
                            end else begin
                                irqc_stat[1] <= 1'b1; // busy/error
                            end
                        end
                    end

                    REG_IRQC_STAT: begin
                        irqc_stat <= irqc_stat & ~wr_data_i[1:0]; // W1C
                    end

                    REG_CONF_THR_L: conf_thr[7:0] <= wr_data_i;
                    REG_CONF_THR_H: conf_thr[15:8] <= wr_data_i;
                    REG_CONF_CTRL: begin
                        conf_en <= wr_data_i[0];
                        conf_irq_en <= wr_data_i[1];
                        if (wr_data_i[2]) begin
                            conf_cross_seen_sticky <= 1'b0;
                            conf_thr_irq_fired_sticky <= 1'b0;
                        end
                    end
                    REG_CONF_STAT: begin
                        if (wr_data_i[1]) conf_cross_seen_sticky <= 1'b0;
                        if (wr_data_i[2]) conf_thr_irq_fired_sticky <= 1'b0;
                    end

                    default: begin
                        if (!in_cfg_window && !in_irqc_window)
                            status[ST_I2C_RX_ERROR] <= 1'b1;
                    end
                endcase
            end

            // Drive sideband request until the IRQ controller responds.
            if (irqc_busy) begin
                irqc_req_o   <= 1'b1;
                irqc_we_o    <= irqc_req_we_pending;
                irqc_off_o   <= irqc_req_off_pending;
                irqc_wdata_o <= irqc_req_wdata_pending;
                if (irqc_ready_i) begin
                    irqc_rdata_latched <= irqc_rdata_i;
                    irqc_stat[0] <= 1'b1; // done
                    irqc_stat[1] <= 1'b0;
                    irqc_busy <= 1'b0;
                end
            end

            event_o <= manual_kick_pulse | threshold_pulse;
            if (manual_kick_pulse | threshold_pulse)
                irq_count <= irq_count + 16'd1;
        end
    end

    always @* begin
        case (rd_addr_i)
            REG_WHOAMI:      rd_data_o = 8'hA5;
            REG_VERSION:     rd_data_o = 8'h01;
            REG_STATUS:      rd_data_o = status;
            REG_CTRL:        rd_data_o = {7'b0, irq_bridge_en};
            REG_IRQ_KICK:    rd_data_o = 8'h00;
            REG_IRQ_COUNT_L: rd_data_o = irq_count[7:0];
            REG_IRQ_COUNT_H: rd_data_o = irq_count[15:8];
            REG_WAKE_TS0:    rd_data_o = cfg_target_wake_sec[7:0];
            REG_WAKE_TS1:    rd_data_o = cfg_target_wake_sec[15:8];
            REG_WAKE_TS2:    rd_data_o = cfg_target_wake_sec[23:16];
            REG_WAKE_TS3:    rd_data_o = cfg_target_wake_sec[31:24];
            REG_WAKE_WIN_L:  rd_data_o = cfg_window_sec[7:0];
            REG_WAKE_WIN_H:  rd_data_o = cfg_window_sec[15:8];
            REG_STEP_SEC_L:  rd_data_o = cfg_step_sec[7:0];
            REG_STEP_SEC_H:  rd_data_o = cfg_step_sec[15:8];
            REG_MOTION_TH_L: rd_data_o = cfg_motion_hi_th[7:0];
            REG_MOTION_TH_H: rd_data_o = cfg_motion_hi_th[15:8];
            REG_MOTION_CNT:  rd_data_o = cfg_motion_hi_count;
            REG_WAKE_POLICY: rd_data_o = cfg_policy;

            REG_IRQC_OFF:    rd_data_o = irqc_off;
            REG_IRQC_W0:     rd_data_o = irqc_wdata[7:0];
            REG_IRQC_W1:     rd_data_o = irqc_wdata[15:8];
            REG_IRQC_W2:     rd_data_o = irqc_wdata[23:16];
            REG_IRQC_W3:     rd_data_o = irqc_wdata[31:24];
            REG_IRQC_CMD:    rd_data_o = {6'b0, irqc_we_o, 1'b0};
            REG_IRQC_STAT:   rd_data_o = {6'b0, irqc_stat};
            REG_IRQC_R0:     rd_data_o = irqc_rdata_latched[7:0];
            REG_IRQC_R1:     rd_data_o = irqc_rdata_latched[15:8];
            REG_IRQC_R2:     rd_data_o = irqc_rdata_latched[23:16];
            REG_IRQC_R3:     rd_data_o = irqc_rdata_latched[31:24];

            REG_CONF_THR_L:  rd_data_o = conf_thr[7:0];
            REG_CONF_THR_H:  rd_data_o = conf_thr[15:8];
            REG_CONF_CTRL:   rd_data_o = {5'b0, 1'b0, conf_irq_en, conf_en};
            REG_CONF_STAT:   rd_data_o = {4'b0, conf_armed, conf_thr_irq_fired_sticky, conf_cross_seen_sticky, above_thr_live};
            REG_LOGIT0_L:    rd_data_o = score_proxy0[7:0];
            REG_LOGIT0_H:    rd_data_o = score_proxy0[15:8];
            REG_LOGIT1_L:    rd_data_o = score_proxy1[7:0];
            REG_LOGIT1_H:    rd_data_o = score_proxy1[15:8];
            REG_CONF_ABS_L:  rd_data_o = score_conf[7:0];
            REG_CONF_ABS_H:  rd_data_o = score_conf[15:8];

            default:         rd_data_o = 8'h00;
        endcase
    end
endmodule
