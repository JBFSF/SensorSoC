#include <stdint.h>

#define TIMER_BASE     0x03002000u
#define PWR_BASE       0x03001000u
#define TEST_BASE      0x0300F000u

#define T_CTRL         (TIMER_BASE + 0x0u)
#define T_RELOAD       (TIMER_BASE + 0x4u)
#define T_COUNT        (TIMER_BASE + 0x8u)
#define T_EVENT        (TIMER_BASE + 0xCu)

#define P_CTRL         (PWR_BASE + 0x0u)
#define P_WAKE_STATUS  (PWR_BASE + 0x4u)
#define P_WAKE_REASON  (PWR_BASE + 0x8u)

#define TEST_STATUS    (TEST_BASE + 0x0u)
#define TEST_CODE      (TEST_BASE + 0x4u)

#define TEST_PASS      0xCAFEBABEu
#define TEST_FAIL      0xDEADBEEFu

#define WAKE_TIMER_BIT (1u << 0)

static inline void mmio_write32(uint32_t addr, uint32_t data) {
    *(volatile uint32_t *)addr = data;
}

static inline uint32_t mmio_read32(uint32_t addr) {
    return *(volatile uint32_t *)addr;
}

static void pass(void) {
    mmio_write32(TEST_STATUS, TEST_PASS);
    while (1) { }
}

static void fail(uint32_t code) {
    mmio_write32(TEST_CODE, code);
    mmio_write32(TEST_STATUS, TEST_FAIL);
    while (1) { }
}

int main(void) {
    // Clear old latches
    mmio_write32(P_WAKE_STATUS, 0xFFFFFFFFu);
    mmio_write32(T_EVENT, 1u);

    // Program one-shot timer
    mmio_write32(T_RELOAD, 50u);
    mmio_write32(T_COUNT,  20u);
    mmio_write32(T_CTRL,   0x1u);   // enable=1, periodic=0

    // Request sleep
    mmio_write32(P_CTRL, 1u);

    // Wait until timer event is latched (wake)
    while ((mmio_read32(T_EVENT) & 1u) == 0u) {
        __asm__ volatile ("nop");
    }

    // IMPORTANT: clear sleep request BEFORE clearing the wake source
    mmio_write32(P_CTRL, 0u);

    // Now it’s safe to read status/reason and clear latches
    uint32_t reason = mmio_read32(P_WAKE_REASON);
    uint32_t status = mmio_read32(P_WAKE_STATUS);
    uint32_t tev    = mmio_read32(T_EVENT) & 1u;

    if (!tev) fail(0x10);
    if (((reason | status) & WAKE_TIMER_BIT) == 0u) fail(0x11);

    // Clear latches
    mmio_write32(T_EVENT, 1u);
    mmio_write32(P_WAKE_STATUS, 0xFFFFFFFFu);

    pass();
}
