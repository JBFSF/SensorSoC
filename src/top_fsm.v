/* TOP FSM that controls sleep for different sections, controllable via outside debug
    NORMAL operation:
    1. IDLE,      wait for reset to be released
    2. SLEEP,     cpu/feat/ml all off, wake on irqc_wake_req or any wake_sources rising edge
    3. FEAT_ONLY, feat enabled, waits for first feature vector to be ready
    4. ALL,       feat + ML + CPU all on; waits for ML inference to complete
    5. CPU_FEAT,  feat + CPU on, goes back to just feats on when CPU is done
*/
module top_fsm
(
    input         resetn_i,
    input         clk_i,

    input   [3:0] test_mode_i,
    //add input start? 

    // Pipeline done signals
    input         feat_valid_i,    // one-cycle strobe: feature vector ready (FEAT_ONLY -> ALL)
    input         ml_irq_i,        // ML inference complete (ALL -> CPU_FEAT)

    // CPU sleep/wake inputs
    input  [31:0] wake_sources_i,  // this includes watchdog
    input         sleep_req_i,     // CPU requests sleep (from pwrctrl MMIO)
    input         mem_valid_i,     // CPU memory-access valid (for idle detection)
    input         irqc_wake_req_i, // interrupt controller forces wake

    output        feat_en_o,
    output        ml_en_o,
    output        cpu_en_o,
    output        sleeping_o
);

    localparam IDLE      = 3'd0;
    localparam SLEEP     = 3'd1;
    localparam FEAT_ONLY = 3'd2;
    localparam ALL       = 3'd3;
    localparam CPU_FEAT  = 3'd4;
    localparam FEAT_ML   = 3'd5;
    localparam CPU_ONLY  = 3'd6;

    reg [2:0] state_d, state_q, state_debug_q;

    // Rising-edge detection on wake sources
    reg  [31:0] wake_sources_d_r;
    wire [31:0] wake_rise_w  = wake_sources_i & ~wake_sources_d_r;
    wire        wake_event_w = |wake_rise_w;

    // Rising-edge detection on sleep request
    reg  sleep_req_d_r;
    wire sleep_req_rise_w = sleep_req_i & ~sleep_req_d_r;

    // CPU idle tracking: set once CPU is active but not doing a memory access
    reg  cpu_idle_seen_r;
    reg  cpu_clk_en_r;

    // Safe to sleep: CPU asked, was seen idle, and no wake event racing in
    wire can_sleep_w = sleep_req_i && cpu_idle_seen_r && !(irqc_wake_req_i || wake_event_w);

    always @(posedge clk_i) begin
        if (!resetn_i)
            state_q <= IDLE;
        else
            state_q <= state_d;
    end

    always @(*) begin
        state_d = state_q;

        case (state_q)
            IDLE:     state_d = SLEEP;
            SLEEP:    if (irqc_wake_req_i || wake_event_w) state_d = FEAT_ONLY;
            FEAT_ONLY:if (feat_valid_i)                    state_d = ALL;
            ALL:      if (ml_irq_i)                        state_d = CPU_FEAT;
            CPU_FEAT: if (can_sleep_w)                     state_d = FEAT_ONLY;
        endcase

        case (test_mode_i)
            4'b0001, 4'b0010, 4'b0011, 4'b0100: state_d = FEAT_ONLY; //just feat_pl
            4'b0110, 4'b1100, 4'b1101: state_d = FEAT_ML; //feat and ML
            4'b0111, 4'b1000, 4'b1001, 4'b1010, 4'b1011: state_d = CPU_ONLY; //just cpu?
            4'b0101: state_d = ALL; //all 
        endcase
    end


    // Output enables (combinational from state)
    assign feat_en_o  = (state_q == FEAT_ONLY) || (state_q == ALL) || (state_q == CPU_FEAT) || (state_q == FEAT_ML);
    assign ml_en_o    = (state_q == ALL) || (state_q == FEAT_ML);
    assign cpu_en_o   = cpu_clk_en_r;
    assign sleeping_o = (state_q == SLEEP);

    always @(posedge clk_i) begin
        if (!resetn_i) begin
            wake_sources_d_r <= 32'h0;
            sleep_req_d_r    <= 1'b0;
            cpu_clk_en_r     <= 1'b0;
            cpu_idle_seen_r  <= 1'b0;
        end else begin
            wake_sources_d_r <= wake_sources_i;
            sleep_req_d_r    <= sleep_req_i;

            // Idle tracking: reset on new sleep req, accumulate when CPU active but bus idle
            if (cpu_clk_en_r && sleep_req_rise_w)
                cpu_idle_seen_r <= 1'b0;
            else if (cpu_clk_en_r)
                cpu_idle_seen_r <= cpu_idle_seen_r | (~mem_valid_i);

            // cpu_clk_en_r follows states where CPU should be active
            cpu_clk_en_r <= (state_d == ALL) || (state_d == CPU_FEAT) || (state_d == CPU_ONLY);
            // clear idle tracking when CPU powers on or system enters sleep
            if (state_d == SLEEP ||
                    ((state_d == ALL || state_d == CPU_FEAT || state_d == CPU_ONLY) && !cpu_clk_en_r))
                cpu_idle_seen_r <= 1'b0;
        end
    end

endmodule
