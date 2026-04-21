#include <stdint.h>

#define TEST_BASE     0x0300F000u
#define TEST_STATUS   (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE     (*(volatile uint32_t*)(TEST_BASE + 0x04u))

#define IRQC_PENDING  (*(volatile uint32_t*)0x03005000u)
#define IRQC_MASK     (*(volatile uint32_t*)0x03005004u)
#define IRQC_WAKE_EN  (*(volatile uint32_t*)0x03005008u)
#define IRQC_CLAIM    (*(volatile uint32_t*)0x03005014u)
#define IRQC_COMPLETE (*(volatile uint32_t*)0x03005018u)

static volatile uint32_t g_irq_count = 0;

static inline void cpu_irq_unmask_all(void) {
    // PicoRV32 custom instruction: maskirq x0, x0 (set irq_mask = 0).
    __asm__ volatile (".word 0x0600000b" ::: "memory");
}

// Overrides the weak irq_handler in start.S.
// Called with all registers saved; start.S executes retirq after return.
void irq_handler(void) {
    uint32_t claim = IRQC_CLAIM;       // encoded ID: 1=bit0(timer), 2=bit1(ML), 3=bit2(host_i2c)
    if (claim == 0) return;

    uint32_t bit  = 1u << (claim - 1u);
    TEST_CODE     = bit;               // 0x1=timer, 0x2=ML, 0x4=host_i2c
    IRQC_PENDING  = bit;               // W1C: drop irqc.irq_o before retirq to prevent re-entry
    IRQC_COMPLETE = claim;
    g_irq_count++;
}

void main(void) {
    IRQC_MASK    = 0u;
    IRQC_PENDING = 0xFFFFFFFFu;        // clear any stale latched sources
    IRQC_WAKE_EN = 0x7u;
    IRQC_MASK    = 0x7u;               // arm bits 0 (timer), 1 (ML), 2 (host_i2c)
    cpu_irq_unmask_all();
    TEST_STATUS  = 0xA000u;            // ready sentinel: tester may now inject IRQs

    while (g_irq_count < 3u) {}       // spin until all 3 sources have been handled

    TEST_STATUS = 0xDEADu;            // done sentinel
    while (1) {}
}
