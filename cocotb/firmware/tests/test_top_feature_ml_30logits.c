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

#define ML_REG(off)   (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off) (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define VAR_BASE    128u
#define X_BASE       64u
#define LOGIT_BASE 5504u

#define ALARM_BASE    0x03000000u
#define ALARM_CTRL    (*(volatile uint32_t*)(ALARM_BASE + 0x00u))

#define TEST_PASS 0xCAFEBABEu
#define TEST_FAIL 0xDEADBEEFu

#define OUT0_SENTINEL 0xA5A55A5Au

#define N_LOGITS 10

#define WAKE_CLASS        1u
#define WAKE_STREAK_REQ   1u

static void fail(uint32_t code) {
    TEST_CODE   = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
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

    for (i = 0; i < N_LOGITS; i++) {
        /* Wait for the feature engine to produce a new valid epoch */
        if (!wait_feature_valid(5000000u, &feature_status)) fail(0xF210u | (uint32_t)i);

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

        /* Start inference, wait BUSY 0->1->0, clear START */
        ML_REG(0x10u) = 1u;
        if (!wait_busy_value(1u, 200000u))  fail(0xF220u | (uint32_t)i);
        if (!wait_busy_value(0u, 2000000u)) fail(0xF230u | (uint32_t)i);
        ML_REG(0x10u) = 0u;

        /* Read output and verify mutation */
        out0_after = WRAM_U32(LOGIT_BASE + 0u);
        if (out0_after == OUT0_SENTINEL) fail(0xF240u | (uint32_t)i);

        log0 = (int16_t)(out0_after & 0xFFFFu);
        log1 = (int16_t)((out0_after >> 16) & 0xFFFFu);
        conf = (log1 > log0) ? (uint16_t)(log1 - log0) : (uint16_t)(log0 - log1);
        predicted_class = (log1 > log0) ? 1u : 0u;

        /* Streak: 5 consecutive wake predictions trips the alarm */
        if (predicted_class == WAKE_CLASS)
            wake_streak++;
        else
            wake_streak = 0u;

        if (wake_streak >= WAKE_STREAK_REQ)
            ALARM_CTRL = 1u;

        ML_SCORE = conf;

        /* Signal testbench: packed logits in TEST_CODE, iteration number in TEST_STATUS */
        TEST_CODE   = ((predicted_class & 1u) << 31) |
                      ((uint32_t)(uint16_t)log1 << 16) |
                      ((uint32_t)(uint16_t)log0);
        TEST_STATUS = (uint32_t)(i + 1);
    }

    /* Final: write last logit info + PASS */
    ML_SCORE  = (uint32_t)(log1 > log0 ? (log1 - log0) : (log0 - log1));
    TEST_CODE = ((predicted_class & 1u) << 31) |
                ((uint32_t)(uint16_t)log1 << 16) |
                ((uint32_t)(uint16_t)log0);
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
