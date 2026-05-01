#include <stdint.h>

// Unified-top golden-vector ML regression with explicit SPI-flash weight load.
//
// Purpose:
//   - reuse the proven flash-backed parameter path from the unified top
//   - write the canonical_v1 quantized input vector from golden_vectors.py
//   - kick ML through the normal CPU-owned control registers
//   - let the SV bench compare the final logits numerically
//
// Flow:
//   1. boot on PicoRV32 inside top.sv
//   2. program taketwo's GBASE / LOGIT_BASE / X_BASE / VAR_BASE registers
//   3. write the fixed int16 feature vector into the CPU-visible feature window
//   4. start inference and poll BUSY until it returns low
//   5. leave the final output word in the CPU-visible logit window for the bench
//      to check
//
// Canonical vector (canonical_v1 in golden_vectors.py):
//   x_float = [0.5, -0.25, 0.1, -1.0]
//   x_int   = [256, -128, 51, -512] with X_SCALE = 512

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

#define X_BASE       64u
#define VAR_BASE     128u
#define LOGIT_BASE   5504u

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
    uint32_t out_word;
    uint32_t out_word_1;
    uint32_t saw_busy;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;

    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xEE00u);
    ML_REG(0x88u) = LOGIT_BASE;
    if (ML_REG(0x88u) != LOGIT_BASE) fail(0xEE01u);
    ML_REG(0x8Cu) = X_BASE;
    if (ML_REG(0x8Cu) != X_BASE) fail(0xEE02u);
    ML_REG(0x90u) = VAR_BASE;
    if (ML_REG(0x90u) != VAR_BASE) fail(0xEE03u);

    WRAM_I16(X_BASE + 0u) = (int16_t)256;
    WRAM_I16(X_BASE + 2u) = (int16_t)-128;
    WRAM_I16(X_BASE + 4u) = (int16_t)51;
    WRAM_I16(X_BASE + 6u) = (int16_t)-512;

    if (WRAM_I16(X_BASE + 0u) != (int16_t)256) fail(0xEE10u);
    if (WRAM_I16(X_BASE + 2u) != (int16_t)-128) fail(0xEE11u);
    if (WRAM_I16(X_BASE + 4u) != (int16_t)51) fail(0xEE12u);
    if (WRAM_I16(X_BASE + 6u) != (int16_t)-512) fail(0xEE13u);

    ML_REG(0x28u) = 1u;
    if ((ML_REG(0x28u) & 1u) == 0u) fail(0xEE20u);
    ML_REG(0x2Cu) = 1u;

    ML_REG(0x10u) = 1u;
    saw_busy = wait_busy_value(1u, 200000u);
    if (!saw_busy) fail(0xEE21u);
    if (!wait_busy_value(0u, 2000000u)) fail(0xEE22u);
    ML_REG(0x10u) = 0u;
    ML_REG(0x2Cu) = 1u;

    out_word = WRAM_U32(LOGIT_BASE);
    out_word_1 = WRAM_U32(LOGIT_BASE + 4u);

    // Compact bench-visible summary:
    // [31:24] saw_busy
    // [23:0]  low 24 bits of the final output word
    TEST_CODE =
        ((saw_busy & 0xFFu) << 24) |
        (out_word & 0x00FFFFFFu);
    (void)out_word_1;
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
