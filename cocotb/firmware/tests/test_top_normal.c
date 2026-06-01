#include <stdint.h>

#define FEATURE_BASE  0x03004000u
#define ML_BASE       0x03003000u
#define WEIGHT_BASE   0x03006000u
#define TEST_BASE     0x0300F000u
#define TIMER_BASE    0x03002000u

#define TEST_STATUS   (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE     (*(volatile uint32_t*)(TEST_BASE + 0x04u))
#define ML_SCORE      (*(volatile uint32_t*)(TEST_BASE + 0x20u))

#define FEATURE_STATUS (*(volatile uint32_t*)(FEATURE_BASE + 0x00u))
#define FEATURE_TIME   (*(volatile uint32_t*)(FEATURE_BASE + 0x04u))
#define FEATURE_MOTION (*(volatile uint32_t*)(FEATURE_BASE + 0x08u))
#define FEATURE_DHR    (*(volatile uint32_t*)(FEATURE_BASE + 0x0Cu))
#define FEATURE_RMSSD  (*(volatile uint32_t*)(FEATURE_BASE + 0x10u))

#define FEATURE_VALID_MASK (1u << 0)

#define ML_REG(off)   (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off) (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define VAR_BASE    128u
#define X_BASE       64u
#define LOGIT_BASE 5504u

#define ALARM_BASE    0x03000000u
#define ALARM_CTRL    (*(volatile uint32_t*)(ALARM_BASE + 0x00u))

#define PWR_CTRL         (*(volatile uint32_t*)0x03001000u)
#define PWR_WAKE_STATUS  (*(volatile uint32_t*)0x03001004u)

#define TIMER_CTRL       (*(volatile uint32_t*)(TIMER_BASE + 0x00u))
#define TIMER_RELOAD     (*(volatile uint32_t*)(TIMER_BASE + 0x04u))
#define TIMER_COUNT      (*(volatile uint32_t*)(TIMER_BASE + 0x08u))

#define IRQC_PENDING     (*(volatile uint32_t*)0x03005000u)
#define IRQC_MASK        (*(volatile uint32_t*)0x03005004u)
#define IRQC_WAKE_EN     (*(volatile uint32_t*)0x03005008u)
#define IRQC_CLAIM       (*(volatile uint32_t*)0x03005014u)
#define IRQC_COMPLETE    (*(volatile uint32_t*)0x03005018u)

#define IRQ_TIMER_BIT    (1u << 0)
#define IRQ_ML_BIT       (1u << 1)

/* Matches TIMER_RELOAD_DEFAULT in the sim wrapper (chip_top_sim_wrap.sv). */
#define EPOCH_TIMER_CYCLES 1000u

#define TEST_PASS 0xCAFEBABEu
#define TEST_FAIL 0xDEADBEEFu

#define OUT0_SENTINEL 0xA5A55A5Au

#define N_LOGITS 10

#define WAKE_CLASS        0u
#define WAKE_STREAK_REQ   2u

static void fail(uint32_t code) {
    TEST_CODE   = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static inline void cpu_irq_unmask_all(void) {
    __asm__ volatile (".word 0x0600000b" ::: "memory");
}

static inline uint32_t cpu_waitirq(void) {
    uint32_t pending;
    __asm__ volatile (".word 0x0800000b" : "=r"(pending) :: "memory");
    return pending;
}

static volatile uint32_t g_ml_done_flag;

static void service_irqs(void) {
    uint32_t guard = 16u;
    while (guard--) {
        uint32_t claim = IRQC_CLAIM;
        if (claim == 0u || claim > 32u) break;
        uint32_t bit = 1u << (claim - 1u);

        if (bit & IRQ_ML_BIT) {
            /* Drop the controller mask before completing so irq_o falls
             * before retirq. taketwo's done signal may remain briefly. */
            IRQC_MASK = 0u;
            ML_REG(0x2Cu) = 1u;    /* ap_continue — release taketwo done */
            g_ml_done_flag = 1u;
        }

        IRQC_PENDING = bit;
        IRQC_COMPLETE = claim;
    }
}

void irq_handler(void) {
    service_irqs();
}

static int wait_feature_valid(uint32_t timeout, uint32_t *status_out) {
    while (timeout--) {
        uint32_t s = FEATURE_STATUS;
        if (s & FEATURE_VALID_MASK) { *status_out = s; return 1; }
    }
    return 0;
}

static int wait_busy_value(uint32_t target, uint32_t timeout) {
    while (timeout--) {
        if ((ML_REG(0x14u) & 1u) == target) return 1;
    }
    return 0;
}

void main(void) {
    int i;
    uint32_t feature_status;
    int16_t  time_feat, motion_feat, delta_hr_feat, rmssd_feat;
    uint32_t out0_after;
    int16_t  log0, log1;
    uint16_t conf;
    uint32_t predicted_class;
    uint32_t wake_streak;

    TEST_STATUS = 0u;
    TEST_CODE   = 0u;
    ML_SCORE    = 0u;
    ALARM_CTRL  = 0u;
    log0 = 0; log1 = 0; predicted_class = 0u; wake_streak = 0u;

    /* Signal CPU_INIT done: program epoch timer, enable IRQ wake, then sleep.
     * FSM: CPU_INIT -> SLEEP -> FEAT_ONLY -> ALL; CPU resumes with features ready. */
    PWR_CTRL     = 0u;
    PWR_WAKE_STATUS = 0xFFFFFFFFu;
    IRQC_PENDING = 0xFFFFFFFFu;
    TIMER_RELOAD = EPOCH_TIMER_CYCLES;
    TIMER_COUNT  = EPOCH_TIMER_CYCLES;
    TIMER_CTRL   = 0x3u;           /* enable=1, periodic=1 */
    IRQC_WAKE_EN = IRQ_TIMER_BIT;
    cpu_irq_unmask_all();
    IRQC_MASK    = IRQ_TIMER_BIT;
    PWR_CTRL     = 1u;             /* sleep_req -> can_sleep_w -> CPU_INIT done */
    (void)cpu_waitirq();
    service_irqs();

    /* One-time ML register setup */
    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xF201u);
    ML_REG(0x88u) = LOGIT_BASE;
    if (ML_REG(0x88u) != LOGIT_BASE) fail(0xF20Au);
    ML_REG(0x8Cu) = X_BASE;
    if (ML_REG(0x8Cu) != X_BASE) fail(0xF20Bu);
    ML_REG(0x90u) = VAR_BASE;
    if (ML_REG(0x90u) != VAR_BASE) fail(0xF20Cu);
    ML_REG(0x28u) = 1u;
    ML_REG(0x2Cu) = 1u;

    /* Production loop: continuously read features, run inference, drive alarm.
     * No exit condition — the chip runs forever responding to live sensor data.
     * ALARM_CTRL is held high while the wake streak threshold is met and
     * automatically de-asserts when a non-wake prediction breaks the streak. */
    i = 0;
    for (;;) {
        /* Wait for the feature engine to produce a new valid epoch */
        if (!wait_feature_valid(5000000u, &feature_status)) fail(0xF210u | ((uint32_t)i & 0xFFu));

        /* Latch features then consume (clear valid so next epoch can be produced) */
        time_feat     = (int16_t)(FEATURE_TIME   & 0xFFFFu);
        motion_feat   = (int16_t)(FEATURE_MOTION & 0xFFFFu);
        delta_hr_feat = (int16_t)(FEATURE_DHR    & 0xFFFFu);
        rmssd_feat    = (int16_t)(FEATURE_RMSSD  & 0xFFFFu);
        FEATURE_STATUS = 1u;

        /* Write feature vector into X buffer */
        WRAM_I16(X_BASE + 0u) = motion_feat;
        WRAM_I16(X_BASE + 2u) = time_feat;
        WRAM_I16(X_BASE + 4u) = delta_hr_feat;
        WRAM_I16(X_BASE + 6u) = rmssd_feat;

        /* Poison output so we can detect mutation */
        WRAM_U32(LOGIT_BASE + 0u) = OUT0_SENTINEL;

        /* Re-program taketwo's output objaddr (reg 33 at offset 0x84) each
         * inference. Otherwise internal pointer state drifts across inferences
         * and the final logit write lands outside LOGIT_OFFSET, so
         * weight_flash_axi never captures it into logit_reg_0. */
        ML_REG(0x84u) = 0u;

        /* Re-arm taketwo per inference: ap_continue then auto_restart.
         * Without ap_continue each iteration, taketwo's internal SRAM write
         * pointer (sink_26 inside ram_w16_l512_id1_*) ratchets forward but
         * the AXI write-back source pointer stays at the first-inference
         * location, so logit_reg_0 only ever sees the first inference's value. */
        ML_REG(0x2Cu) = 1u;   /* ap_continue */
        ML_REG(0x28u) = 1u;   /* auto_restart */

        /* Arm ML IRQ: clear any stale pending bit, enable the mask, then START.
         * Going through the IRQ path (instead of polling BUSY and clearing
         * START quickly) keeps ml_irq asserted long enough for top_fsm to
         * observe it and transition ALL -> CPU_FEAT. */
        g_ml_done_flag = 0u;
        IRQC_PENDING = IRQ_ML_BIT;
        IRQC_MASK = IRQ_ML_BIT;
        ML_REG(0x10u) = 1u;

        while (g_ml_done_flag == 0u) {
            (void)cpu_waitirq();
            service_irqs();
        }
        ML_REG(0x10u) = 0u;

        /* Read output and verify mutation */
        out0_after = WRAM_U32(LOGIT_BASE + 0u);
        if (out0_after == OUT0_SENTINEL) fail(0xF240u | (uint32_t)i);

        log0 = (int16_t)(out0_after & 0xFFFFu);
        log1 = (int16_t)((out0_after >> 16) & 0xFFFFu);
        conf = (log1 > log0) ? (uint16_t)(log1 - log0) : (uint16_t)(log0 - log1);
        predicted_class = (log1 > log0) ? 1u : 0u;

        /* Wake-streak alarm policy.
         * Class == WAKE_CLASS → tick streak; assert alarm at threshold.
         * Any other class → reset streak AND de-assert alarm so the FSM can
         * leave ALARM (via start_i) and cycle back through inference. */
        if (predicted_class == WAKE_CLASS) {
            if (wake_streak < 0xFFFFFFFFu) wake_streak++;
            if (wake_streak >= WAKE_STREAK_REQ) ALARM_CTRL = 1u;
        } else {
            wake_streak = 0u;
            ALARM_CTRL  = 0u;
        }

        ML_SCORE = conf;

        /* Signal testbench: packed logits in TEST_CODE, iteration number in TEST_STATUS */
        TEST_CODE   = ((predicted_class & 1u) << 31) |
                      ((uint32_t)(uint16_t)log1 << 16) |
                      ((uint32_t)(uint16_t)log0);
        TEST_STATUS = (uint32_t)(i + 1);
        i++;

        /* Re-arm sleep_req every iteration. pwrctrl_mmio auto-clears
         * sleep_req_o on wake, so we must rewrite it for the FSM to
         * accept the CPU_INIT -> SLEEP (and CPU_FEAT -> FEAT_ONLY)
         * transitions. Required for the post-alarm loopback path:
         *   ALARM -(start_i)-> IDLE -(start_i)-> CPU_INIT
         *   CPU_INIT -(can_sleep_w)-> SLEEP -(timer)-> ... */
        PWR_CTRL = 1u;
    }
}
