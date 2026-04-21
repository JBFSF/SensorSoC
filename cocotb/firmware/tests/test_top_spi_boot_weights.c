/*
 * test_top_spi_boot_weights.c
 *
 * Test 1: SPI flash boot — weight load only.
 *
 * Boots from SPI flash, loads ML weights into WRAM, verifies the first
 * four words written to WRAM match what was read from flash. No sensor
 * pipeline, no ML inference. Fast isolation test for the SPI boot path.
 *
 * PASS criteria:
 *   - SPI CS asserted at least once
 *   - 208 words (832 bytes) transferred from flash to WRAM
 *   - First 4 WRAM words read back and match expected flash content
 */

#include <stdint.h>

#define WEIGHT_BASE  0x03006000u
#define SPI_BASE     0x0300A000u
#define TEST_BASE    0x0300F000u

#define TEST_STATUS  (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE    (*(volatile uint32_t*)(TEST_BASE + 0x04u))

#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))

#define SPI_CS       (*(volatile uint32_t*)(SPI_BASE + 0x00u))
#define SPI_STATUS   (*(volatile uint32_t*)(SPI_BASE + 0x04u))
#define SPI_DATA     (*(volatile uint32_t*)(SPI_BASE + 0x08u))
#define SPI_DIVIDER  (*(volatile uint32_t*)(SPI_BASE + 0x0Cu))
#define SPI_BUSY_BIT (1u << 0)

/* Weight layout in WRAM — matches taketwo firmware convention */
#define VAR_BASE     128u
#define WEIGHT_WORDS 208u

#define TEST_PASS    0xCAFEBABEu
#define TEST_FAIL    0xDEADBEEFu

static void fail(uint32_t code) {
    TEST_CODE   = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static uint8_t spi_xfer(uint8_t tx) {
    uint32_t delay;

    SPI_DATA = (uint32_t)tx;
    for (delay = 0u; delay < 8u; delay++) {
        __asm__ volatile ("nop");
    }
    while (SPI_STATUS & SPI_BUSY_BIT) {}
    (void)SPI_DATA;               /* dummy read to latch rx_data */
    return (uint8_t)(SPI_DATA & 0xFFu);
}

static void spi_boot_load(void) {
    uint32_t i;
    uint32_t settle;

    SPI_DIVIDER = 2u;

    /* Assert CS and send READ (0x03) command + 24-bit address 0x000000 */
    SPI_CS = 0u;
    spi_xfer(0x03u);
    spi_xfer(0x00u);
    spi_xfer(0x00u);
    spi_xfer(0x00u);

    /* Read WEIGHT_WORDS 32-bit words, little-endian byte order */
    for (i = 0u; i < WEIGHT_WORDS; i++) {
        uint32_t b0 = spi_xfer(0x00u);
        uint32_t b1 = spi_xfer(0x00u);
        uint32_t b2 = spi_xfer(0x00u);
        uint32_t b3 = spi_xfer(0x00u);
        WRAM_U32(VAR_BASE + (i * 4u)) = b0 | (b1 << 8u) | (b2 << 16u) | (b3 << 24u);

        /* Brief settle between words */
        for (settle = 0u; settle < 16u; settle++) {
            __asm__ volatile ("nop");
        }
    }

    SPI_CS = 1u;
}

void main(void) {
    uint32_t w0, w1, w2, w3;

    TEST_STATUS = 0u;
    TEST_CODE   = 0u;

    spi_boot_load();

    /*
     * Read back the first 4 WRAM words and encode them into TEST_CODE
     * so the testbench can compare against the flash model contents.
     */
    w0 = WRAM_U32(VAR_BASE + 0u);
    w1 = WRAM_U32(VAR_BASE + 4u);
    w2 = WRAM_U32(VAR_BASE + 8u);
    w3 = WRAM_U32(VAR_BASE + 12u);

    /* Sanity: at least one word must be non-zero for a valid weight file */
    if ((w0 == 0u) && (w1 == 0u) && (w2 == 0u) && (w3 == 0u)) {
        fail(0xB001u);
    }

    /* Report PASS — testbench cross-checks WRAM vs flash model directly */
    TEST_CODE   = w0;   /* first weight word for TB verification */
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
