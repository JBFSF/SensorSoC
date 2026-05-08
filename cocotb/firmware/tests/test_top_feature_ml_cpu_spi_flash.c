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

#define ML_REG(off)      (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off)    (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off)    (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define VAR_BASE         128u
#define X_BASE           64u
#define LOGIT_BASE       5504u

#define TEST_PASS 0xCAFEBABEu
#define TEST_FAIL 0xDEADBEEFu

#define OUT0_SENTINEL 0xA5A55A5Au
#define OUT1_SENTINEL 0x5A5AA5A5u

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static int wait_feature_valid(uint32_t timeout, uint32_t *status_out) {
    while (timeout--) {
        uint32_t status = FEATURE_STATUS;
        if ((status & FEATURE_VALID_MASK) != 0u) {
            *status_out = status;
            return 1;
        }
    }
    return 0;
}

static int wait_busy_value(uint32_t target, uint32_t timeout) {
    while (timeout--) {
        if ((ML_REG(0x14u) & 1u) == target) return 1;
    }
    return 0;
}

static uint16_t abs_i16(int16_t x) {
    return (x < 0) ? (uint16_t)(-x) : (uint16_t)x;
}

void main(void) {
    uint32_t feature_status;
    int16_t time_feat;
    int16_t motion_feat;
    int16_t delta_hr_feat;
    int16_t rmssd_feat;
    uint32_t out0_after;
    uint32_t out1_after;
    uint32_t saw_busy;
    int16_t log0;
    int16_t log1;
    uint16_t conf;
    uint32_t predicted_class;
    uint32_t outputs_mutated;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;
    ML_SCORE = 0u;

    /* Weights are pre-loaded into weight_flash_axi's on-chip cache at reset
     * via the dedicated weight SPI flash — no CPU involvement needed. */

    if (!wait_feature_valid(5000000u, &feature_status)) fail(0xF200u);

    time_feat     = (int16_t)(FEATURE_TIME & 0xFFFFu);
    motion_feat   = (int16_t)(FEATURE_MOTION & 0xFFFFu);
    delta_hr_feat = (int16_t)(FEATURE_DHR & 0xFFFFu);
    rmssd_feat    = (int16_t)(FEATURE_RMSSD & 0xFFFFu);

    FEATURE_STATUS = 1u;

    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xF201u);

    ML_REG(0x88u) = LOGIT_BASE;
    if (ML_REG(0x88u) != LOGIT_BASE) fail(0xF20Au);

    ML_REG(0x8Cu) = X_BASE;
    if (ML_REG(0x8Cu) != X_BASE) fail(0xF20Bu);
    ML_REG(0x90u) = VAR_BASE;
    if (ML_REG(0x90u) != VAR_BASE) fail(0xF20Cu);

    WRAM_I16(X_BASE + 0u) = motion_feat;
    WRAM_I16(X_BASE + 2u) = time_feat;
    WRAM_I16(X_BASE + 4u) = delta_hr_feat;
    WRAM_I16(X_BASE + 6u) = rmssd_feat;

    if (WRAM_I16(X_BASE + 0u) != motion_feat) fail(0xF202u);
    if (WRAM_I16(X_BASE + 2u) != time_feat) fail(0xF203u);
    if (WRAM_I16(X_BASE + 4u) != delta_hr_feat) fail(0xF204u);
    if (WRAM_I16(X_BASE + 6u) != rmssd_feat) fail(0xF205u);

    WRAM_U32(LOGIT_BASE + 0u) = OUT0_SENTINEL;
    WRAM_U32(LOGIT_BASE + 4u) = OUT1_SENTINEL;

    ML_REG(0x28u) = 1u;
    ML_REG(0x2Cu) = 1u;
    ML_REG(0x10u) = 1u;

    saw_busy = wait_busy_value(1u, 200000u);
    if (!saw_busy) fail(0xF206u);
    if (!wait_busy_value(0u, 2000000u)) fail(0xF207u);
    ML_REG(0x10u) = 0u;

    out0_after = WRAM_U32(LOGIT_BASE + 0u);
    out1_after = WRAM_U32(LOGIT_BASE + 4u);
    outputs_mutated = (out0_after != OUT0_SENTINEL) || (out1_after != OUT1_SENTINEL);
    if (!outputs_mutated) fail(0xF208u);

    log0 = (int16_t)(out0_after & 0xFFFFu);
    log1 = (int16_t)((out0_after >> 16) & 0xFFFFu);
    conf = abs_i16((int16_t)(log0 - log1));
    predicted_class = (log1 > log0) ? 1u : 0u;

    ML_SCORE = conf;
    TEST_CODE =
        ((predicted_class & 1u) << 31) |
        ((outputs_mutated & 1u) << 30) |
        ((saw_busy & 1u) << 29) |
        (conf & 0xFFFFu);
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
