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
static inline void short_delay(volatile uint32_t n) {
    while (n--) __asm__ volatile ("nop");
}
static volatile const uint32_t TEST_PASS_VAL = 0xCAFEBABEu;
static volatile const uint32_t TEST_FAIL_VAL = 0xDEADBEEFu;

static void pass(void) {
    mmio_write32(TEST_STATUS, TEST_PASS_VAL);
    while (1) { }
}
static void fail(uint32_t code) {
    mmio_write32(TEST_CODE, code);
    mmio_write32(TEST_STATUS, TEST_FAIL_VAL);
    while (1) { }
}

static int wait_until_set(uint32_t addr, uint32_t mask, uint32_t iters)
{
    while (iters--) {
        if (mmio_read32(addr) & mask) return 1;
        short_delay(50);
    }
    return 0;
}

static int wait_until_clear(uint32_t addr, uint32_t mask, uint32_t iters)
{
    while (iters--) {
        if ((mmio_read32(addr) & mask) == 0) return 1;
        short_delay(50);
    }
    return 0;
}

int main(void) {
    // clean slate
    mmio_write32(P_CTRL, 0u);
    mmio_write32(P_WAKE_STATUS, 0xFFFFFFFFu);
    mmio_write32(T_CTRL, 0u);
    mmio_write32(T_EVENT, 1u);

    // periodic timer (fast in sim)
    mmio_write32(T_RELOAD, 50000u);
    mmio_write32(T_COUNT,  50000u);
    mmio_write32(T_CTRL,   0x3u); // enable + periodic

    // request sleep
    mmio_write32(P_CTRL, 1u);

    // wait for timer event and wake status
    if (!wait_until_set(T_EVENT, 1u, 200000u))            fail(0x20);
    if (!wait_until_set(P_WAKE_STATUS, WAKE_TIMER_BIT, 200000u)) fail(0x21);

    // STOP re-sleeping now (critical in periodic mode)
    mmio_write32(P_CTRL, 0u);

    // reason should have snapped on the wake edge
    uint32_t reason = mmio_read32(P_WAKE_REASON);
    if ((reason & WAKE_TIMER_BIT) == 0u) fail(0x22);

    // stop timer before W1C tests
    mmio_write32(T_CTRL, 0u);

    // clear event and verify it stays cleared
    mmio_write32(T_EVENT, 1u);
    if (!wait_until_clear(T_EVENT, 1u, 10000u)) fail(0x23);

    // clear wake_status bit and verify
    mmio_write32(P_WAKE_STATUS, WAKE_TIMER_BIT);
    if (!wait_until_clear(P_WAKE_STATUS, WAKE_TIMER_BIT, 10000u)) fail(0x24);

    mmio_write32(TEST_CODE, 0x11111111u);
    mmio_write32(TEST_STATUS, TEST_PASS_VAL);
    while (1) { }
    pass();
}
