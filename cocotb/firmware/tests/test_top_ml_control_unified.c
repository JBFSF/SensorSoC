#include <stdint.h>

// Short unified-top ML-control regression.
// This firmware bypasses the sensor pipeline and SPI loader entirely:
//   CPU writes a direct test vector into WRAM,
//   programs the global WRAM base,
//   enables/clears the completion IRQ,
//   starts inference,
//   waits for BUSY to rise and fall,
//   and records whether the output region was mutated.
// The hard pass/fail criteria here are the control-plane checks; output
// mutation is reported diagnostically so this stays a stable short regression.

#define ML_BASE       0x03003000u
#define WEIGHT_BASE   0x03006000u
#define TEST_BASE     0x0300F000u

#define TEST_STATUS   (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE     (*(volatile uint32_t*)(TEST_BASE + 0x04u))

#define ML_REG(off)   (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off) (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define TEST_PASS 0xCAFEBABEu
#define TEST_FAIL 0xDEADBEEFu

#define X_BASE        64u
#define OUT0_SENTINEL 0xA5A55A5Au
#define OUT1_SENTINEL 0x5A5AA5A5u

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static int wait_busy_value(uint32_t target, uint32_t timeout) {
    while (timeout--) {
        if ((ML_REG(0x14u) & 1u) == target) return 1;
    }
    return 0;
}

int main(void) {
    uint32_t out0_before;
    uint32_t out1_before;
    uint32_t out0_after;
    uint32_t out1_after;
    uint32_t saw_busy;
    uint32_t outputs_mutated;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;

    // Point taketwo at the shared WRAM used in unified top tests.
    // This is the minimum base-address programming that is stable across the
    // current unified-top regressions.
    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xEC00u);

    // Direct test vector: x0=motion, x1=time, x2=delta_hr, x3=rmssd.
    WRAM_I16(X_BASE + 0u) = (int16_t)0x0100;
    WRAM_I16(X_BASE + 2u) = (int16_t)0x0200;
    WRAM_I16(X_BASE + 4u) = (int16_t)0x0040;
    WRAM_I16(X_BASE + 6u) = (int16_t)0x0080;

    if (WRAM_I16(X_BASE + 0u) != (int16_t)0x0100) fail(0xEC10u);
    if (WRAM_I16(X_BASE + 2u) != (int16_t)0x0200) fail(0xEC11u);
    if (WRAM_I16(X_BASE + 4u) != (int16_t)0x0040) fail(0xEC12u);
    if (WRAM_I16(X_BASE + 6u) != (int16_t)0x0080) fail(0xEC13u);

    WRAM_U32(5504u + 0u) = OUT0_SENTINEL;
    WRAM_U32(5504u + 4u) = OUT1_SENTINEL;
    out0_before = WRAM_U32(5504u + 0u);
    out1_before = WRAM_U32(5504u + 4u);

    // Enable the completion IRQ and clear any stale status before kicking ML.
    ML_REG(0x28u) = 1u;
    if ((ML_REG(0x28u) & 1u) == 0u) fail(0xEC20u);
    ML_REG(0x2Cu) = 1u;

    // Kick inference and prove that BUSY goes high and later returns low.
    ML_REG(0x10u) = 1u;

    saw_busy = wait_busy_value(1u, 200000u);
    if (!saw_busy) fail(0xEC21u);
    if (!wait_busy_value(0u, 2000000u)) fail(0xEC22u);

    ML_REG(0x10u) = 0u;
    ML_REG(0x2Cu) = 1u;

    out0_after = WRAM_U32(5504u + 0u);
    out1_after = WRAM_U32(5504u + 4u);
    outputs_mutated = (out0_after != out0_before) || (out1_after != out1_before);

    // Compact bench-visible summary:
    // [31:24] saw_busy
    // [23:16] output mutated (diagnostic; not a hard failure in this short control test)
    // [15:0]  low halfword of output word 0
    TEST_CODE =
        ((saw_busy & 0xFFu) << 24) |
        ((outputs_mutated & 0xFFu) << 16) |
        (out0_after & 0xFFFFu);
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
