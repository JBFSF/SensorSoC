#include <stdint.h>

/*
 * Production-style firmware for the unified top.sv path.
 *
 * This is intentionally a forever loop, not a self-ending test program. The
 * firmware waits for latched sensor features, copies them into the
 * weight_flash_axi feature input registers, starts taketwo, waits for the ML
 * completion IRQ, reads back captured logits, and applies the wake/alarm
 * policy. TEST_STATUS is only used for fatal failures; normal progress is
 * reported through TEST_CODE and ML_SCORE for simulation/debug visibility.
 */

/* Top-level MMIO bases. Keep these aligned with top.sv parameters. */
#define FEATURE_BASE  0x03004000u
#define ML_BASE       0x03003000u
#define WEIGHT_BASE   0x03006000u
#define ALARM_BASE    0x03000000u
#define TEST_BASE     0x0300F000u

/* Simulation/debug mailbox. Hardware behavior should not depend on these. */
#define TEST_STATUS   (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE     (*(volatile uint32_t*)(TEST_BASE + 0x04u))
#define ML_SCORE      (*(volatile uint32_t*)(TEST_BASE + 0x20u))

/* Feature MMIO exposes the latest latched feature vector from top.sv. */
#define FEATURE_STATUS (*(volatile uint32_t*)(FEATURE_BASE + 0x00u))
#define FEATURE_TIME   (*(volatile uint32_t*)(FEATURE_BASE + 0x04u))
#define FEATURE_MOTION (*(volatile uint32_t*)(FEATURE_BASE + 0x08u))
#define FEATURE_DHR    (*(volatile uint32_t*)(FEATURE_BASE + 0x0Cu))
#define FEATURE_RMSSD  (*(volatile uint32_t*)(FEATURE_BASE + 0x10u))

#define FEATURE_VALID_MASK (1u << 0)

#define PWR_CTRL         (*(volatile uint32_t*)0x03001000u)
#define PWR_WAKE_STATUS  (*(volatile uint32_t*)0x03001004u)
#define PWR_WAKE_REASON  (*(volatile uint32_t*)0x03001008u)

/*
 * weight_flash_axi owns the WEIGHT_BASE page in the current architecture.
 *
 * Despite the historical "WRAM" naming in older docs/tests, this page is now a
 * small register interface plus an SPI-backed AXI bridge:
 *   - CPU writes features at X_BASE into feature registers.
 *   - taketwo reads model weights from external SPI flash via AXI.
 *   - taketwo writes logits, which weight_flash_axi captures for CPU reads.
 */
#define ML_REG(off)      (*(volatile uint32_t*)(ML_BASE + (off)))
#define WFLASH_U32(off)  (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WFLASH_I16(off)  (*(volatile int16_t*) (WEIGHT_BASE + (off)))
#define ALARM_CTRL       (*(volatile uint32_t*)(ALARM_BASE + 0x00u))

/* IRQ controller registers. Claim values are one-based IDs for pending bits. */
#define IRQC_PENDING     (*(volatile uint32_t*)0x03005000u)
#define IRQC_MASK        (*(volatile uint32_t*)0x03005004u)
#define IRQC_WAKE_EN     (*(volatile uint32_t*)0x03005008u)
#define IRQC_CLAIM       (*(volatile uint32_t*)0x03005014u)
#define IRQC_COMPLETE    (*(volatile uint32_t*)0x03005018u)

#define IRQ_ML_BIT       (1u << 1)

#define VAR_BASE         128u
#define X_BASE           64u
#define LOGIT_BASE       5504u

/*
 * Wake policy:
 *   - Start the observation clock from the first feature timestamp seen after
 *     firmware starts.
 *   - During the wake window, class 1 is treated as light sleep / wake OK.
 *   - Five consecutive class-1 results assert alarm_mmio bit 0.
 *
 * PROD_MAIN_FAST_WAKE_WINDOW is a temporary simulation acceleration hook for
 * chip-top/top-level normal-mode runs. It keeps the production policy shape
 * intact, but moves the wake window close to startup so sim does not need to
 * run for hours of firmware time before the alarm path can be observed.
 */
#ifdef PROD_MAIN_FAST_WAKE_WINDOW
#define WAKE_WINDOW_START_SEC  5u
#define WAKE_WINDOW_END_SEC    15u
#define LIGHT_SLEEP_CLASS      1u
#define LIGHT_SLEEP_STREAK_REQ 5u
#else
#define WAKE_WINDOW_START_SEC  (7u * 60u * 60u)
#define WAKE_WINDOW_END_SEC    (8u * 60u * 60u)
#define LIGHT_SLEEP_CLASS      1u
#define LIGHT_SLEEP_STREAK_REQ 5u
#endif

#define TEST_FAIL        0xDEADBEEFu

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static volatile uint32_t g_ml_done_flag;
static volatile uint32_t g_irq_claims;
static volatile uint32_t g_irq_bad_claims;

static void service_irqs(void) {
    uint32_t guard = 16u;

    /*
     * Drain all currently claimable IRQs. The guard protects firmware from an
     * accidental live-lock if a source keeps reappearing faster than we can
     * clear it.
     */
    while (guard--) {
        uint32_t claim = IRQC_CLAIM;
        uint32_t bit;

        if (claim == 0u) break;
        if (claim > 32u) {
            g_irq_bad_claims++;
            break;
        }

        bit = 1u << (claim - 1u);
        g_irq_claims++;

        if (bit & IRQ_ML_BIT) {
            /*
             * Drop the controller mask before completing the IRQ so irq_o
             * falls before retirq. taketwo's done signal can remain asserted
             * briefly, so this avoids immediate re-entry.
             */
            IRQC_MASK = 0u;
            ML_REG(0x2Cu) = 1u;   /* ap_continue — release taketwo done */
            g_ml_done_flag = 1u;
        }

        IRQC_PENDING = bit;       /* W1C */
        IRQC_COMPLETE = claim;
    }
}

void irq_handler(void) {
    service_irqs();
}

static inline void cpu_irq_unmask_all(void) {
    /* PicoRV32 custom maskirq instruction: unmask all CPU IRQ bits. */
    __asm__ volatile (".word 0x0600000b" ::: "memory");
}

static inline uint32_t cpu_waitirq(void) {
    uint32_t pending;

    /* PicoRV32 custom waitirq instruction: sleep until an IRQ is observed. */
    __asm__ volatile (".word 0x0800000b" : "=r"(pending) :: "memory");
    return pending;
}

static uint16_t abs_i16(int16_t x) {
    return (x < 0) ? (uint16_t)(-x) : (uint16_t)x;
}

int main(void) {
    uint32_t feature_status;
    uint32_t out0_after;
    uint32_t out1_after;
    int16_t time_feat;
    int16_t motion_feat;
    int16_t delta_hr_feat;
    int16_t rmssd_feat;
    uint32_t logits_word;
    uint32_t start_time_sec;
    uint32_t elapsed_sec;
    uint32_t have_start_time;
    int16_t log0;
    int16_t log1;
    uint16_t conf;
    uint32_t predicted_class;
    uint32_t light_sleep_streak;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;
    ML_SCORE = 0u;
    ALARM_CTRL = 0u;
    g_ml_done_flag = 0u;
    g_irq_claims = 0u;
    g_irq_bad_claims = 0u;
    start_time_sec = 0u;
    elapsed_sec = 0u;
    have_start_time = 0u;
    light_sleep_streak = 0u;

    PWR_CTRL = 0u;
    PWR_WAKE_STATUS = 0xFFFFFFFFu;
    IRQC_PENDING = 0xFFFFFFFFu;

    /*
     * Program taketwo's address registers for the weight_flash_axi layout.
     * GBASE is an absolute MMIO base; the other three are byte offsets from
     * that base.
     */
    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xF801u);

    ML_REG(0x88u) = LOGIT_BASE;
    if (ML_REG(0x88u) != LOGIT_BASE) fail(0xF802u);

    ML_REG(0x8Cu) = X_BASE;
    if (ML_REG(0x8Cu) != X_BASE) fail(0xF807u);

    ML_REG(0x90u) = VAR_BASE;
    if (ML_REG(0x90u) != VAR_BASE) fail(0xF808u);

    ML_REG(0x28u) = 1u;
    ML_REG(0x2Cu) = 1u;
    if ((ML_REG(0x28u) & 1u) == 0u) fail(0xF803u);

    IRQC_MASK = IRQ_ML_BIT;
    IRQC_WAKE_EN = IRQ_ML_BIT;
    cpu_irq_unmask_all();

    for (;;) {
        /* Wait until top.sv has latched a complete feature vector. */
        do {
            feature_status = FEATURE_STATUS;
        } while ((feature_status & FEATURE_VALID_MASK) == 0u);

        time_feat = (int16_t)(FEATURE_TIME & 0xFFFFu);
        motion_feat = (int16_t)(FEATURE_MOTION & 0xFFFFu);
        delta_hr_feat = (int16_t)(FEATURE_DHR & 0xFFFFu);
        rmssd_feat = (int16_t)(FEATURE_RMSSD & 0xFFFFu);

        FEATURE_STATUS = 1u;

        /*
         * FEATURE_TIME is the current time-in-night feature. Track elapsed
         * seconds relative to the first feature observed after start.
         */
        if (!have_start_time) {
            start_time_sec = (uint16_t)time_feat;
            have_start_time = 1u;
        }
        elapsed_sec = (uint16_t)((uint16_t)time_feat - (uint16_t)start_time_sec);

        /*
         * Pack four int16 features into weight_flash_axi's CPU-visible feature
         * registers. taketwo reads these through AXI before fetching weights.
         */
        WFLASH_I16(X_BASE + 0u) = motion_feat;
        WFLASH_I16(X_BASE + 2u) = time_feat;
        WFLASH_I16(X_BASE + 4u) = delta_hr_feat;
        WFLASH_I16(X_BASE + 6u) = rmssd_feat;

        /* Start one ML inference and wait for the completion IRQ. */
        g_ml_done_flag = 0u;
        IRQC_PENDING = IRQ_ML_BIT;
        ML_REG(0x2Cu) = 1u;
        ML_REG(0x28u) = 1u;
        ML_REG(0x10u) = 1u;

        while (g_ml_done_flag == 0u) {
            (void)cpu_waitirq();
            service_irqs();
        }

        while ((ML_REG(0x14u) & 1u) != 0u) {}

        /*
         * Read logits captured by weight_flash_axi. The first output word packs
         * logit0 in bits [15:0] and logit1 in bits [31:16].
         */
        out0_after = WFLASH_U32(LOGIT_BASE + 0u);
        out1_after = WFLASH_U32(LOGIT_BASE + 4u);

        if (g_irq_bad_claims != 0u) fail(0xF806u);

        logits_word = out0_after;
        log0 = (int16_t)(logits_word & 0xFFFFu);
        log1 = (int16_t)((logits_word >> 16) & 0xFFFFu);
        conf = abs_i16((int16_t)(log0 - log1));
        predicted_class = (log1 > log0) ? 1u : 0u;

        ML_SCORE = conf;
        TEST_CODE = (predicted_class << 31) | conf;

        /*
         * Alarm policy. A single light-sleep classification is not enough; the
         * user must be in the wake window and produce five consecutive class-1
         * results. Any class-0 result or out-of-window result resets the streak.
         */
        if ((elapsed_sec >= WAKE_WINDOW_START_SEC) &&
            (elapsed_sec <= WAKE_WINDOW_END_SEC) &&
            (predicted_class == LIGHT_SLEEP_CLASS)) {
            if (light_sleep_streak < LIGHT_SLEEP_STREAK_REQ)
                light_sleep_streak++;
        } else {
            light_sleep_streak = 0u;
        }

        if (light_sleep_streak >= LIGHT_SLEEP_STREAK_REQ) {
            ALARM_CTRL = 1u;
            TEST_CODE = (predicted_class << 31) |
                        (1u << 30) |
                        ((light_sleep_streak & 0xFFu) << 16) |
                        conf;
        }

        /* Re-arm taketwo and the IRQ controller for the next feature epoch. */
        ML_REG(0x10u) = 0u;
        ML_REG(0x2Cu) = 1u;
        IRQC_PENDING = IRQ_ML_BIT;   /* clear any stale pending */
        IRQC_MASK = IRQ_ML_BIT;      /* re-arm for next iteration */
    }
}
