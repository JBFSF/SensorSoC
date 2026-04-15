#include <stdint.h>

// Short unified-top SPI initialization regression.
// This firmware only proves the SPI MMIO boot-copy path:
//   CPU -> spi_master_mmio -> spi_flash_model -> weight_ram_axi
// It intentionally avoids the feature and ML loops so failures localize to
// flash transfer setup rather than the rest of the top-level system flow.

#define SPI_BASE      0x0300A000u
#define WEIGHT_BASE   0x03006000u
#define TEST_BASE     0x0300F000u

#define TEST_STATUS   (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE     (*(volatile uint32_t*)(TEST_BASE + 0x04u))

#define WRAM_U32(off) (*(volatile uint32_t*)(WEIGHT_BASE + (off)))

#define SPI_CS        (*(volatile uint32_t*)(SPI_BASE + 0x00u))
#define SPI_STATUS    (*(volatile uint32_t*)(SPI_BASE + 0x04u))
#define SPI_DATA      (*(volatile uint32_t*)(SPI_BASE + 0x08u))
#define SPI_DIVIDER   (*(volatile uint32_t*)(SPI_BASE + 0x0Cu))
#define SPI_BUSY_BIT  (1u << 0)

#define TEST_PASS     0xCAFEBABEu
#define TEST_FAIL     0xDEADBEEFu

#define BOOT_WORDS    8u
#define BOOT_BASE     128u

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static uint8_t spi_xfer(uint8_t tx)
{
    uint32_t delay;
    uint32_t rx_word;

    SPI_DATA = (uint32_t)tx;
    for (delay = 0u; delay < 8u; delay++) {
        __asm__ volatile ("nop");
    }
    while ((SPI_STATUS & SPI_BUSY_BIT) != 0u) {}
    // Read twice to match the existing SPI-flash regression behavior and give
    // the memory-mapped receive register a cycle to settle on slower sims.
    rx_word = SPI_DATA;
    rx_word = SPI_DATA;
    return (uint8_t)(rx_word & 0xFFu);
}

int main(void)
{
    uint32_t i;
    uint32_t first_word = 0u;
    uint32_t last_word = 0u;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;

    SPI_DIVIDER = 2u;
    if (SPI_DIVIDER != 2u) fail(0xEB00u);

    SPI_CS = 0u;
    if ((SPI_CS & 1u) != 0u) fail(0xEB01u);

    // Standard SPI NOR READ (0x03) from byte address 0x000000.
    spi_xfer(0x03u);
    spi_xfer(0x00u);
    spi_xfer(0x00u);
    spi_xfer(0x00u);

    for (i = 0u; i < BOOT_WORDS; i++) {
        uint32_t b0 = spi_xfer(0x00u);
        uint32_t b1 = spi_xfer(0x00u);
        uint32_t b2 = spi_xfer(0x00u);
        uint32_t b3 = spi_xfer(0x00u);
        uint32_t word = b0 | (b1 << 8u) | (b2 << 16u) | (b3 << 24u);

        WRAM_U32(BOOT_BASE + (i * 4u)) = word;
        if (WRAM_U32(BOOT_BASE + (i * 4u)) != word) fail(0xEB10u | i);

        if (i == 0u) first_word = word;
        if (i == (BOOT_WORDS - 1u)) last_word = word;
    }

    SPI_CS = 1u;
    if ((SPI_CS & 1u) == 0u) fail(0xEB20u);
    if ((SPI_STATUS & SPI_BUSY_BIT) != 0u) fail(0xEB21u);

    // Compact summary:
    // [31:24] boot word count
    // [23:8]  low 16 bits of first copied word
    // [7:0]   low 8 bits of last copied word
    TEST_CODE =
        ((BOOT_WORDS & 0xFFu) << 24) |
        ((first_word & 0xFFFFu) << 8) |
        (last_word & 0xFFu);
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
