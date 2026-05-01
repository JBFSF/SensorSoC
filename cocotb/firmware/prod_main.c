#include <stdint.h>

#define FEATURE_BASE  0x03004000u
#define ML_BASE       0x03003000u
#define WEIGHT_BASE   0x03006000u
#define TEST_BASE     0x0300F000u

#define TEST_STATUS   (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE     (*(volatile uint32_t*)(TEST_BASE + 0x04u))
#define ML_SCORE      (*(volatile uint32_t*)(TEST_BASE + 0x20u))

#define FEATURE_STATUS (*(volatile uint32_t*)(FEATURE_BASE + 0x00u))
#define FEATURE_TIME   (*(volatile uint32_t*)(FEATURE_BASE + 0x04u))
#define FEATURE_MOTION (*(volatile uint32_t*)(FEATURE_BASE + 0x08u))
#define FEATURE_DHR    (*(volatile uint32_t*)(FEATURE_BASE + 0x0Cu))
#define FEATURE_RMSSD  (*(volatile uint32_t*)(FEATURE_BASE + 0x10u))

#define FEATURE_VALID_MASK (1u << 0)

#define PWR_CTRL         (*(volatile uint32_t*)0x03001000u)
#define PWR_WAKE_STATUS  (*(volatile uint32_t*)0x03001004u)
#define PWR_WAKE_REASON  (*(volatile uint32_t*)0x03001008u)

#define ML_REG(off)      (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off)    (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off)    (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define IRQC_PENDING     (*(volatile uint32_t*)0x03005000u)
#define IRQC_MASK        (*(volatile uint32_t*)0x03005004u)
#define IRQC_WAKE_EN     (*(volatile uint32_t*)0x03005008u)
#define IRQC_CLAIM       (*(volatile uint32_t*)0x03005014u)
#define IRQC_COMPLETE    (*(volatile uint32_t*)0x03005018u)

#define IRQ_ML_BIT       (1u << 1)

#define VAR_BASE         128u
#define X_BASE           64u
#define LOGIT_BASE       5504u

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
                                    /* Disable the ML IRQ in the controller immediately so that
                                     irq_o drops before we clear pending/complete.  This prevents
                                     PicoRV32 from re-vectoring the moment retirq fires, even if
                                     taketwo's done signal stays asserted for a few extra cycles. */
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
    __asm__ volatile (".word 0x0600000b" ::: "memory");
}

static inline uint32_t cpu_waitirq(void) {
    uint32_t pending;
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
    int16_t log0;
    int16_t log1;
    uint16_t conf;
    uint32_t predicted_class;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;
    ML_SCORE = 0u;
    g_ml_done_flag = 0u;
    g_irq_claims = 0u;
    g_irq_bad_claims = 0u;

    PWR_CTRL = 0u;
    PWR_WAKE_STATUS = 0xFFFFFFFFu;
    IRQC_PENDING = 0xFFFFFFFFu;

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
        do {
            feature_status = FEATURE_STATUS;
        } while ((feature_status & FEATURE_VALID_MASK) == 0u);

        time_feat = (int16_t)(FEATURE_TIME & 0xFFFFu);
        motion_feat = (int16_t)(FEATURE_MOTION & 0xFFFFu);
        delta_hr_feat = (int16_t)(FEATURE_DHR & 0xFFFFu);
        rmssd_feat = (int16_t)(FEATURE_RMSSD & 0xFFFFu);

        FEATURE_STATUS = 1u;

        WRAM_I16(X_BASE + 0u) = motion_feat;
        WRAM_I16(X_BASE + 2u) = time_feat;
        WRAM_I16(X_BASE + 4u) = delta_hr_feat;
        WRAM_I16(X_BASE + 6u) = rmssd_feat;

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

        out0_after = WRAM_U32(LOGIT_BASE + 0u);
        out1_after = WRAM_U32(LOGIT_BASE + 4u);

        if (g_irq_bad_claims != 0u) fail(0xF806u);

        logits_word = out0_after;
        log0 = (int16_t)(logits_word & 0xFFFFu);
        log1 = (int16_t)((logits_word >> 16) & 0xFFFFu);
        conf = abs_i16((int16_t)(log0 - log1));
        predicted_class = (log1 > log0) ? 1u : 0u;

        ML_SCORE = conf;
        TEST_CODE = (predicted_class << 31) | conf;

        ML_REG(0x10u) = 0u;
        ML_REG(0x2Cu) = 1u;
        IRQC_PENDING = IRQ_ML_BIT;   /* clear any stale pending */
        IRQC_MASK = IRQ_ML_BIT;      /* re-arm for next iteration */
    }
}
