/*
 * test_top_spi_boot_weights.c
 *
 * Dedicated weight-SPI ML smoke test.
 *
 * The legacy version manually drove spi_master_mmio, copied bytes into the
 * weight window, and then read those addresses back.  That is no longer the
 * architecture: weight_flash_axi fetches weights directly from the shared
 * flash bus during taketwo AXI reads.
 *
 * This firmware writes the canonical input vector, starts taketwo through the
 * normal ML control registers, and numerically checks the packed output word.
 * The SystemVerilog bench separately verifies that flash_spi_* toggled and
 * spi_master_mmio stayed idle.
 */

#include <stdint.h>

#define WEIGHT_BASE  0x03006000u
#define ML_BASE      0x03003000u
#define TEST_BASE    0x0300F000u

#define TEST_STATUS  (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE    (*(volatile uint32_t*)(TEST_BASE + 0x04u))

#define ML_REG(off)  (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off) (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define X_BASE       64u
#define VAR_BASE     128u
#define TMP_BASE     5312u
#define LOGIT_BASE   5504u

#define EXPECTED_LOGIT_WORD 0x3585F96Au

#define TEST_PASS    0xCAFEBABEu
#define TEST_FAIL    0xDEADBEEFu

static void fail(uint32_t code) {
    TEST_CODE   = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static int wait_busy_value(uint32_t target, uint32_t timeout) {
    while (timeout--) {
        if ((ML_REG(0x14u) & 1u) == target) return 1;
    }
    return 0;
}

void main(void) {
    uint32_t out_word;
    uint32_t saw_busy;

    TEST_STATUS = 0u;
    TEST_CODE   = 0u;

    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xB000u);
    ML_REG(0x84u) = TMP_BASE;
    if (ML_REG(0x84u) != TMP_BASE) fail(0xB004u);
    ML_REG(0x88u) = LOGIT_BASE;
    if (ML_REG(0x88u) != LOGIT_BASE) fail(0xB001u);
    ML_REG(0x8Cu) = X_BASE;
    if (ML_REG(0x8Cu) != X_BASE) fail(0xB002u);
    ML_REG(0x90u) = VAR_BASE;
    if (ML_REG(0x90u) != VAR_BASE) fail(0xB003u);

    /* canonical_v1 from sim/tb/golden_vectors.py */
    WRAM_I16(X_BASE + 0u) = (int16_t)256;
    WRAM_I16(X_BASE + 2u) = (int16_t)-128;
    WRAM_I16(X_BASE + 4u) = (int16_t)51;
    WRAM_I16(X_BASE + 6u) = (int16_t)-512;

    if (WRAM_I16(X_BASE + 0u) != (int16_t)256) fail(0xB010u);
    if (WRAM_I16(X_BASE + 2u) != (int16_t)-128) fail(0xB011u);
    if (WRAM_I16(X_BASE + 4u) != (int16_t)51) fail(0xB012u);
    if (WRAM_I16(X_BASE + 6u) != (int16_t)-512) fail(0xB013u);

    ML_REG(0x28u) = 1u;
    ML_REG(0x2Cu) = 1u;
    ML_REG(0x10u) = 1u;

    saw_busy = wait_busy_value(1u, 200000u);
    if (!saw_busy) fail(0xB020u);
    if (!wait_busy_value(0u, 2000000u)) fail(0xB021u);
    ML_REG(0x10u) = 0u;
    ML_REG(0x2Cu) = 1u;

    out_word = WRAM_U32(LOGIT_BASE);
    if (out_word != EXPECTED_LOGIT_WORD) fail(0xB100u | (out_word & 0xFFu));

    TEST_CODE   = out_word;
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
