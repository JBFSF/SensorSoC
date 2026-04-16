#include <stdint.h>

// Unified-top golden-vector ML regression with explicit SPI-flash weight load.
//
// Purpose:
//   - reuse the proven flash-backed parameter path from the unified top
//   - write the canonical writeverilog.py-aligned input vector
//   - kick ML through the normal CPU-owned control registers
//   - let the SV bench compare the final logits numerically
//
// Flow:
//   1. boot on PicoRV32 inside top.sv
//   2. use spi_master_mmio to read the packed parameter image from the flash model
//   3. copy those parameter words into WRAM at VAR_BASE
//   4. program taketwo's GBASE / LOGIT_BASE / X_BASE / VAR_BASE registers
//   5. write the fixed int16 feature vector into WRAM at X_BASE
//   6. start inference and poll BUSY until it returns low
//   7. leave the final output word in WRAM for the bench to check
//
// Canonical vector:
//   x_float = [0.5, -0.25, 0.1, -1.0]
//   x_int   = [256, -128, 51, -512] with X_SCALE = 512

#define ML_BASE       0x03003000u
#define WEIGHT_BASE   0x03006000u
#define SPI_BASE      0x0300A000u
#define TEST_BASE     0x0300F000u

#define TEST_STATUS   (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE     (*(volatile uint32_t*)(TEST_BASE + 0x04u))

#define ML_REG(off)   (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off) (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define SPI_CS        (*(volatile uint32_t*)(SPI_BASE + 0x00u))
#define SPI_STATUS    (*(volatile uint32_t*)(SPI_BASE + 0x04u))
#define SPI_DATA      (*(volatile uint32_t*)(SPI_BASE + 0x08u))
#define SPI_DIVIDER   (*(volatile uint32_t*)(SPI_BASE + 0x0Cu))
#define SPI_BUSY_BIT  (1u << 0)

#define TEST_PASS 0xCAFEBABEu
#define TEST_FAIL 0xDEADBEEFu

#define WEIGHT_WORDS 208u
#define X_BASE       64u
#define VAR_BASE     128u
#define LOGIT_BASE   5504u

#define OUT0_SENTINEL 0xA5A55A5Au

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

static uint8_t spi_xfer(uint8_t tx) {
    uint32_t delay;
    uint32_t rx_word;

    SPI_DATA = (uint32_t)tx;
    for (delay = 0u; delay < 8u; delay++) {
        __asm__ volatile ("nop");
    }
    while (SPI_STATUS & SPI_BUSY_BIT) {}
    rx_word = SPI_DATA;
    rx_word = SPI_DATA;
    return (uint8_t)(rx_word & 0xFFu);
}

static void spi_boot_load(void) {
    uint32_t i;
    uint32_t settle;

    // Issue a standard SPI flash READ (0x03) from byte address 0x000000,
    // then stream WEIGHT_WORDS 32-bit words into the ML parameter window.
    SPI_DIVIDER = 2u;
    SPI_CS = 0u;
    spi_xfer(0x03u);
    spi_xfer(0x00u);
    spi_xfer(0x00u);
    spi_xfer(0x00u);

    for (i = 0u; i < WEIGHT_WORDS; i++) {
        uint32_t b0 = spi_xfer(0x00u);
        uint32_t b1 = spi_xfer(0x00u);
        uint32_t b2 = spi_xfer(0x00u);
        uint32_t b3 = spi_xfer(0x00u);
        WRAM_U32(VAR_BASE + (i * 4u)) = b0 | (b1 << 8u) | (b2 << 16u) | (b3 << 24u);
        (void)SPI_STATUS;
        for (settle = 0u; settle < 16u; settle++) {
            __asm__ volatile ("nop");
        }
    }

    SPI_CS = 1u;
}

int main(void) {
    uint32_t out_word;
    uint32_t saw_busy;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;

    // Stage the ML parameter image in WRAM before programming the accelerator.
    spi_boot_load();

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

    // Prime the output location so the bench can distinguish "no write" from
    // "wrong logits" when debugging failures.
    WRAM_U32(LOGIT_BASE + 0u) = OUT0_SENTINEL;

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

    // Compact bench-visible summary:
    // [31:24] saw_busy
    // [23:0]  low 24 bits of the final output word
    TEST_CODE =
        ((saw_busy & 0xFFu) << 24) |
        (out_word & 0x00FFFFFFu);
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
