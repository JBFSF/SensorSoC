/* TOP FSM that controls sleep for different sections, controllable via outside debug
    NORMAL operation:
    1. IDLE,      wait for reset to be released
    2. CPU_INIT,  CPU on only; firmware initialises ML/IRQC/timer then requests sleep
    3. SLEEP,     cpu/feat/ml all off, wake on interrupt controller request (timer)
    4. FEAT_ONLY, feat enabled, waits for first feature vector to be ready
    5. ALL,       feat + ML + CPU all on; waits for ML inference to complete
    6. CPU_FEAT,  feat + CPU on; firmware reads logits, applies policy, requests sleep
    7. ALARM,     alarm is active, wait for user acknowledgment
*/
module top_fsm
(
    input         resetn_i,
    input         clk_i,

    input   [3:0] test_mode_i,
    input         start_i,
    input         boot_done_i,
    // Pipeline done signals
    input         feat_valid_i,    // one-cycle strobe: feature vector ready (FEAT_ONLY -> ALL)
    input         ml_irq_i,        // ML inference complete (ALL -> CPU_FEAT)

    // CPU sleep/wake inputs
    input         sleep_req_i,     // CPU requests sleep (from pwrctrl MMIO)
    input         mem_valid_i,     // CPU memory-access valid (for idle detection)
    input         irqc_wake_req_i, // interrupt controller forces wake
    input         cpu_alarm_i,     // if the cpu says the alarm should be on

    output        watchdog_o,      // enable the watchdog after we've started
    output        feat_en_o,
    output        ml_en_o,
    output        cpu_en_o,
    output        sleeping_o,
    output        init_o,          // if the cpu initalization was done
    output        alarm_o
);

    localparam BOOT      = 4'd0;
    localparam IDLE      = 4'd1;
    localparam SLEEP     = 4'd2;
    localparam FEAT_ONLY = 4'd3;
    localparam ALL       = 4'd4;
    localparam CPU_FEAT  = 4'd5;
    localparam FEAT_ML   = 4'd6;
    localparam CPU_ONLY  = 4'd7;
    localparam ALARM     = 4'd8;
    localparam CPU_INIT  = 4'd9;   // CPU-only init: firmware sets up timer/IRQC then sleeps

    reg [3:0] state_d, state_q, state_debug_q;

    // Rising-edge detection on sleep request
    reg  sleep_req_d_r;
    wire sleep_req_rise_w = sleep_req_i & ~sleep_req_d_r;

    // CPU idle tracking: set once CPU is active but not doing a memory access
    reg  cpu_idle_seen_r;
    reg  cpu_clk_en_r;

    // Safe to sleep: CPU asked, was seen idle, and no wake event racing in
    wire can_sleep_w = sleep_req_i && cpu_idle_seen_r && !irqc_wake_req_i;

    always @(posedge clk_i) begin
        if (!resetn_i)
            state_q <= BOOT;
        else
            state_q <= state_d;
    end

    always @(*) begin
        state_d = state_q;

        case (state_q)
            BOOT:     if (boot_done_i) state_d = IDLE;
            IDLE:     if (start_i)     state_d = CPU_INIT;
            CPU_INIT: if (can_sleep_w) state_d = SLEEP;
            SLEEP:    if (irqc_wake_req_i) state_d = FEAT_ONLY;
            FEAT_ONLY:if (feat_valid_i)    state_d = ALL;
            ALL:      if (ml_irq_i)        state_d = CPU_FEAT;
            CPU_FEAT: begin
                if (cpu_alarm_i)       state_d = ALARM;
                else if (feat_valid_i) state_d = ALL;
                else if (can_sleep_w)  state_d = FEAT_ONLY;
            end
            ALARM:    if (start_i)     state_d = SLEEP;
        endcase

        case (test_mode_i)
            4'b0001, 4'b0010, 4'b0011, 4'b0100: state_d = FEAT_ONLY; //just feat_pl
            4'b0110: state_d = FEAT_ML; //feat and ML
            // 01001 is an observer mode for live sleep/IRQ state; do not
            // override the FSM or it cannot expose sleeping_o=1.
            4'b0111, 4'b1000, 4'b1010, 4'b1011: state_d = CPU_ONLY; //just cpu?
            4'b0101, 4'b1100, 4'b1101: state_d = ALL; //all
        endcase
    end


    // Output enables (combinational from state)
    assign feat_en_o  = (state_q == FEAT_ONLY) || (state_q == ALL) || (state_q == CPU_FEAT) || (state_q == FEAT_ML);
    assign ml_en_o    = (state_q == ALL) || (state_q == FEAT_ML) || (state_q == BOOT) || (state_q == CPU_INIT) || (state_q == CPU_FEAT);
    assign cpu_en_o   = cpu_clk_en_r;
    assign sleeping_o = (state_q == SLEEP);
    assign watchdog_o = (state_q == FEAT_ONLY) || (state_q == ALL) || (state_q == CPU_FEAT) || (state_q == FEAT_ML) || (state_q == SLEEP);
    assign init_o     = (state_q != BOOT);
    assign alarm_o    = (state_q == ALARM);

    always @(posedge clk_i) begin
        if (!resetn_i) begin
            sleep_req_d_r    <= 1'b0;
            cpu_clk_en_r     <= 1'b0;
            cpu_idle_seen_r  <= 1'b0;
        end else begin
            sleep_req_d_r    <= sleep_req_i;

            // Idle tracking: reset on new sleep req, accumulate when CPU active but bus idle
            if (cpu_clk_en_r && sleep_req_rise_w)
                cpu_idle_seen_r <= 1'b0;
            else if (cpu_clk_en_r)
                cpu_idle_seen_r <= cpu_idle_seen_r | (~mem_valid_i);

            // cpu_clk_en_r follows states where CPU should be active
            cpu_clk_en_r <= (state_d == ALL) || (state_d == CPU_FEAT) ||
                            (state_d == CPU_ONLY) || (state_d == CPU_INIT);
            // clear idle tracking when CPU powers on or system enters sleep
            if (state_d == SLEEP ||
                    ((state_d == ALL || state_d == CPU_FEAT ||
                      state_d == CPU_ONLY || state_d == CPU_INIT) && !cpu_clk_en_r))
                cpu_idle_seen_r <= 1'b0;
        end
    end

endmodule
