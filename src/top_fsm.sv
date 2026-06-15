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
module top_fsm (
    input  logic        resetn_i,
    input  logic        clk_i,

    input  logic [3:0]  test_mode_i,
    input  logic        start_i,
    input  logic        boot_done_i,
    // Pipeline done signals
    input  logic        feat_valid_i,    // one-cycle strobe: feature vector ready (FEAT_ONLY -> ALL)
    input  logic        ml_irq_i,        // ML inference complete (ALL -> CPU_FEAT)

    // CPU sleep/wake inputs
    input  logic        sleep_req_i,     // CPU requests sleep (from pwrctrl MMIO)
    input  logic        irqc_wake_req_i, // interrupt controller forces wake
    input  logic        cpu_alarm_i,     // if the cpu says the alarm should be on

    output logic        watchdog_o,      // enable the watchdog after we've started
    output logic        feat_en_o,
    output logic        ml_en_o,
    output logic        cpu_en_o,
    output logic        sleeping_o,
    output logic        init_o,          // if the cpu initalization was done
    output logic        alarm_o
);

    typedef enum logic [3:0] {
        BOOT      = 4'd0,
        IDLE      = 4'd1,
        SLEEP     = 4'd2,
        FEAT_ONLY = 4'd3,
        ALL       = 4'd4,
        CPU_FEAT  = 4'd5,
        FEAT_ML   = 4'd6,
        CPU_ONLY  = 4'd7,
        ALARM     = 4'd8,
        CPU_INIT  = 4'd9
    } state_t;

    (* fsm_encoding = "none" *) state_t state_d, state_q;

    logic cpu_clk_en_r;
    logic cpu_clk_en_next;

    logic can_sleep_w;
    assign can_sleep_w = sleep_req_i && !irqc_wake_req_i;

    always_ff @(posedge clk_i) begin
        if (!resetn_i)
            state_q <= BOOT;
        else
            state_q <= state_d;
    end

    always_comb begin
        state_d = state_q;

        // Do NOT use `unique case` here: Yosys exploits the "unique" guarantee
        // to treat unvisited state encodings as don't-cares, which causes it to
        // prune irqc_wake_req_i / cpu_alarm_i / ml_irq_i / feat_valid_i as
        // "unreachable" and eliminate the IDLE and FEAT_ONLY DFFs entirely.
        // Plain `case` is sufficient; the FSM is still one-hot after synthesis.
        case (state_q)
            BOOT:      if (boot_done_i)     state_d = IDLE;
            IDLE:      if (start_i)         state_d = CPU_INIT;
            CPU_INIT:  if (can_sleep_w)     state_d = SLEEP;
            SLEEP:     if (irqc_wake_req_i) state_d = FEAT_ONLY;
            FEAT_ONLY: if (feat_valid_i)    state_d = ALL;
            ALL:       if (ml_irq_i)        state_d = CPU_FEAT;
            CPU_FEAT: begin
                if (cpu_alarm_i)       state_d = ALARM;
                else if (feat_valid_i) state_d = ALL;
                else if (can_sleep_w)  state_d = FEAT_ONLY;
            end
            ALARM:     if (start_i)         state_d = IDLE;
            // DFT-only states: hold until test_mode override takes effect below
            default:   state_d = state_q;
        endcase

        case (test_mode_i)
            4'b0001, 4'b0010, 4'b0011, 4'b0100: state_d = FEAT_ONLY;
            4'b0110:                             state_d = FEAT_ML;
            // 01001 is an observer mode for live sleep/IRQ state; do not
            // override the FSM or it cannot expose sleeping_o=1.
            4'b0111, 4'b1000, 4'b1010, 4'b1011: state_d = CPU_ONLY;
            4'b0101, 4'b1100, 4'b1101:           state_d = ALL;
            default: ; // 4'b0000 and other unlisted modes: no override
        endcase
    end

    assign cpu_clk_en_next = (state_d == ALL) || (state_d == CPU_FEAT) ||
                             (state_d == CPU_ONLY) || (state_d == CPU_INIT);

    always_ff @(posedge clk_i) begin
        if (!resetn_i) cpu_clk_en_r <= 1'b0;
        else           cpu_clk_en_r <= cpu_clk_en_next;
    end

    // Output enables (combinational from state)
    assign feat_en_o  = (state_q == FEAT_ONLY) || (state_q == ALL) || (state_q == CPU_FEAT) || (state_q == FEAT_ML);
    assign ml_en_o    = (state_q == ALL) || (state_q == FEAT_ML) || (state_q == BOOT) || (state_q == CPU_INIT) || (state_q == CPU_FEAT);
    assign cpu_en_o   = cpu_clk_en_r;
    assign sleeping_o = (state_q == SLEEP);
    assign watchdog_o = (state_q == FEAT_ONLY) || (state_q == ALL) || (state_q == CPU_FEAT) || (state_q == FEAT_ML) || (state_q == SLEEP);
    assign init_o     = (state_q != BOOT);
    assign alarm_o    = (state_q == ALARM);

endmodule
