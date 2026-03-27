#include <stdint.h>

// ----------------------
// MMIO base addresses
// ----------------------
#define GPIO_BASE      0x03000000u   // your gpio_mmio BASE_ADDR
#define TEST_BASE      0x0300F000u   // your test_mmio BASE_ADDR

// Offsets inside test_mmio
#define TEST_STATUS    (TEST_BASE + 0x0u)
#define TEST_CODE      (TEST_BASE + 0x4u)

// PASS/FAIL magic values
#define TEST_PASS      0xCAFEBABEu
#define TEST_FAIL      0xDEADBEEFu

// ----------------------
// Volatile MMIO pointers
// ----------------------
static inline void mmio_write32(uint32_t addr, uint32_t data) {
    *(volatile uint32_t *)addr = data;
}

static inline uint32_t mmio_read32(uint32_t addr) {
    return *(volatile uint32_t *)addr;
}

// Optional small delay to avoid “too fast to see” in waveforms/LEDs
static inline void delay_cycles(volatile uint32_t n) {
    while (n--) {
        __asm__ volatile ("nop");
    }
}

static void report_pass(void) {
    mmio_write32(TEST_STATUS, 0xCAFEBABEu);
    while (1) { } // stop here
}

static void report_fail(uint32_t code) {
    mmio_write32(TEST_CODE, code);
    mmio_write32(TEST_STATUS, 0xDEADBEEFu);
    while (1) { } // stop here
}

int main(void) {
    // Test pattern
    const uint32_t pat = 0xA5u;

    // Write pattern to GPIO (your gpio_mmio uses mem_wstrb[0] / low byte)
    mmio_write32(GPIO_BASE, pat);

    // Small delay (optional)
    delay_cycles(100);

    // Read back
    uint32_t r = mmio_read32(GPIO_BASE);

    // Check only low 8 bits (gpio_mmio returns {24'h0, gpio_out})
    if ( (r & 0xFFu) != (pat & 0xFFu) ) {
        // error code 1 = readback mismatch
        report_fail(0x00000001u);
    }

    // Optional: write a second pattern to test another value
    mmio_write32(GPIO_BASE, 0x3Cu);
    delay_cycles(100);
    r = mmio_read32(GPIO_BASE);
    if ( (r & 0xFFu) != 0x3Cu ) {
        // error code 2 = second pattern mismatch
        report_fail(0x00000002u);
    }

    report_pass();
    return 0;
}
