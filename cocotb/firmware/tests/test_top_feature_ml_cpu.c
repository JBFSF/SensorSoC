#include <stdint.h>

// Unified-top integration test:
//   1. Wait for the sensor pipeline to publish a latched feature vector.
//   2. Read that vector through the feature MMIO bank.
//   3. Copy the four features into taketwo's shared input buffer.
//   4. Start ML through the CPU-owned AXI-Lite control path.
//   5. Report success/failure through test_mmio for the SV bench.

#define FEATURE_BASE  0x03004000u
#define ML_BASE       0x03003000u
#define WEIGHT_BASE   0x03006000u
#define TEST_STATUS   (*(volatile uint32_t*)0x0300F000u)
#define TEST_CODE     (*(volatile uint32_t*)0x0300F004u)

#define FEATURE_STATUS (*(volatile uint32_t*)(FEATURE_BASE + 0x00u))
#define FEATURE_TIME   (*(volatile uint32_t*)(FEATURE_BASE + 0x04u))
#define FEATURE_MOTION (*(volatile uint32_t*)(FEATURE_BASE + 0x08u))
#define FEATURE_DHR    (*(volatile uint32_t*)(FEATURE_BASE + 0x0Cu))
#define FEATURE_RMSSD  (*(volatile uint32_t*)(FEATURE_BASE + 0x10u))

#define FEATURE_VALID_MASK (1u << 0)

#define ML_REG(off)      (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off)    (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off)    (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define TEST_PASS 0xCAFEBABEu
#define TEST_FAIL 0xDEADBEEFu

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

void main(void) {
    uint32_t feature_status;
    int16_t time_feat;
    int16_t motion_feat;
    int16_t delta_hr_feat;
    int16_t rmssd_feat;
    uint32_t out0_before, out1_before;
    uint32_t out0_after, out1_after;
    uint32_t saw_busy;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;

    if (!wait_feature_valid(5000000u, &feature_status)) fail(0xF100u);

    time_feat     = (int16_t)(FEATURE_TIME & 0xFFFFu);
    motion_feat   = (int16_t)(FEATURE_MOTION & 0xFFFFu);
    delta_hr_feat = (int16_t)(FEATURE_DHR & 0xFFFFu);
    rmssd_feat    = (int16_t)(FEATURE_RMSSD & 0xFFFFu);

    // Clear the sticky feature-valid bit once firmware has consumed the
    // current epoch's feature vector.
    FEATURE_STATUS = 1u;

    // Point taketwo's AXI master at the shared weight/activation RAM.
    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xF101u);

    // Shared input-buffer layout for this test:
    //   x0=motion, x1=time, x2=delta_hr, x3=rmssd
    WRAM_I16(64u + 0u) = motion_feat;
    WRAM_I16(64u + 2u) = time_feat;
    WRAM_I16(64u + 4u) = delta_hr_feat;
    WRAM_I16(64u + 6u) = rmssd_feat;

    if (WRAM_I16(64u + 0u) != motion_feat) fail(0xF102u);
    if (WRAM_I16(64u + 2u) != time_feat) fail(0xF103u);
    if (WRAM_I16(64u + 4u) != delta_hr_feat) fail(0xF104u);
    if (WRAM_I16(64u + 6u) != rmssd_feat) fail(0xF105u);

    // Prime the output region so the bench can see whether taketwo touches it.
    WRAM_U32(5504u + 0u) = 0xA5A5A5A5u;
    WRAM_U32(5504u + 4u) = 0x5A5A5A5Au;
    out0_before = WRAM_U32(5504u + 0u);
    out1_before = WRAM_U32(5504u + 4u);

    // Enable/clear completion IRQ state, then kick inference.
    ML_REG(0x28u) = 1u;
    ML_REG(0x2Cu) = 1u;
    ML_REG(0x10u) = 1u;

    saw_busy = wait_busy_value(1u, 200000u);
    if (!saw_busy) fail(0xF106u);
    if (!wait_busy_value(0u, 2000000u)) fail(0xF107u);
    ML_REG(0x10u) = 0u;

    out0_after = WRAM_U32(5504u + 0u);
    out1_after = WRAM_U32(5504u + 4u);

    // Encode a compact summary for bench-side visibility:
    //   [31:24] feature status low byte seen by firmware
    //   [16]    output mutation observed
    //   [15:0]  low halfword of output word 0
    TEST_CODE =
        ((feature_status & 0xFFu) << 24) |
        ((out0_after != out0_before ? 1u : 0u) << 16) |
        (out0_after & 0xFFFFu);
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
