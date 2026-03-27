#include <stdint.h>

#define ML_BASE     0x03003000u
#define WEIGHT_BASE 0x03006000u
#define TEST_STATUS (*(volatile uint32_t*)0x0300F000u)
#define TEST_CODE   (*(volatile uint32_t*)0x0300F004u)

// taketwo AXI-Lite registers (via ml_axil_bridge_mmio)
#define ML_REG(off)   (*(volatile uint32_t*)(ML_BASE     + (off)))
// Weight RAM (CPU MMIO)
#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off) (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define TEST_PASS 0xCAFEBABEu
#define TEST_FAIL 0xDEADBEEFu

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static int wait_busy_value(uint32_t target, uint32_t timeout) {
    while (timeout--) {
        if ((ML_REG(0x14) & 1u) == target) return 1;
    }
    return 0;
}

void main(void) {
    uint32_t i;
    uint32_t out0_before, out1_before;
    uint32_t out0_after, out1_after;
    uint32_t saw_busy;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;

    // 1) CPU writes a known pattern/weights into weight SRAM via MMIO.
    for (i = 0; i < 256u; i++) {
        WRAM_U32(i * 4u) = 0xA5000000u ^ (i * 0x01010101u);
    }
    if (WRAM_U32(0u) != (0xA5000000u ^ 0x00000000u)) fail(0xE001u);
    if (WRAM_U32(31u * 4u) != (0xA5000000u ^ (31u * 0x01010101u))) fail(0xE002u);
    if (WRAM_U32(255u * 4u) != (0xA5000000u ^ (255u * 0x01010101u))) fail(0xE003u);

    // 1. Program global_base_addr (taketwo reg 32, AXI-Lite offset 0x80)
    ML_REG(0x80) = WEIGHT_BASE;
    if (ML_REG(0x80) != WEIGHT_BASE) fail(0xE010u);

    // 2. Write one test input vector (x_base = 64 bytes from WEIGHT_BASE)
    //    x_float = [0.5, -0.25, 0.1, -1.0], scaled by Q3.13 = 8192
    WRAM_I16(64 + 0) = (int16_t)  4096;   // movement  = 0.5
    WRAM_I16(64 + 2) = (int16_t) -2048;   // cosine    = -0.25
    WRAM_I16(64 + 4) = (int16_t)   819;   // delta_hr  = 0.1
    WRAM_I16(64 + 6) = (int16_t) -8192;   // hr_rmssd  = -1.0

    // Prime output region with a known value to prove mutation.
    WRAM_U32(5504 + 0) = 0xA5A5A5A5u;
    WRAM_U32(5504 + 4) = 0x5A5A5A5Au;
    out0_before = WRAM_U32(5504 + 0);
    out1_before = WRAM_U32(5504 + 4);

    // 3. Start inference (reg at offset 0x10, write 1 then 0)
    ML_REG(0x10) = 1;
    saw_busy = wait_busy_value(1u, 200000u);
    if (!saw_busy) fail(0xE020u);

    // 4. Poll busy flag (reg at offset 0x14)
    if (!wait_busy_value(0u, 2000000u)) fail(0xE021u);
    ML_REG(0x10) = 0;

    // 5) Read output region and confirm mutation happened.
    out0_after = WRAM_U32(5504 + 0);
    out1_after = WRAM_U32(5504 + 4);
    if (out0_after == out0_before && out1_after == out1_before) fail(0xE030u);

    // encode summary for TB visibility
    TEST_CODE = ((saw_busy & 0xFFu) << 24) |
                ((out0_after != out0_before ? 1u : 0u) << 16) |
                (out0_after & 0xFFFFu);
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
