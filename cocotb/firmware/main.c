#include <stdint.h>

// TEST MMIO
#define TEST_STATUS      (*(volatile uint32_t*)0x0300F000u)
#define TEST_CODE        (*(volatile uint32_t*)0x0300F004u)
#define TEST_PASS        0xCAFEBABEu
#define TEST_FAIL        0xDEADBEEFu

// TIMER MMIO (base 0x03002000)
#define TIMER_CTRL       (*(volatile uint32_t*)0x03002000u)  // bit0=enable, bit1=periodic
#define TIMER_RELOAD     (*(volatile uint32_t*)0x03002004u)
#define TIMER_COUNT      (*(volatile uint32_t*)0x03002008u)
#define TIMER_EVENT      (*(volatile uint32_t*)0x0300200Cu)  // W1C bit0

// ML AXI-Lite MMIO (base 0x03003000 in soc_top)
#define ML_BASE          0x03003000u
#define ML_REG(off)      (*(volatile uint32_t*)(ML_BASE + (off)))
#define ML_START         ML_REG(0x10u)  // taketwo reg4
#define ML_BUSY          ML_REG(0x14u)  // taketwo reg5
#define ML_IRQ_STAT      ML_REG(0x24u)  // taketwo reg9
#define ML_IRQ_EN        ML_REG(0x28u)  // taketwo reg10
#define ML_IRQ_CLR       ML_REG(0x2Cu)  // taketwo reg11 (W1C)

// GPIO MMIO (base 0x03000000)
#define GPIO_OUT         (*(volatile uint32_t*)0x03000000u)
#define GPIO_TRIG        (1u << 0)

// POWER MMIO (base 0x03001000)
#define PWR_CTRL         (*(volatile uint32_t*)0x03001000u)  // bit0=sleep_req
#define PWR_WAKE_STATUS  (*(volatile uint32_t*)0x03001004u)
#define PWR_WAKE_REASON  (*(volatile uint32_t*)0x03001008u)

// IRQ controller MMIO (base 0x03005000)
#define IRQC_PENDING     (*(volatile uint32_t*)0x03005000u)  // W1C pending bits
#define IRQC_MASK        (*(volatile uint32_t*)0x03005004u)  // source enable bits
#define IRQC_WAKE_EN     (*(volatile uint32_t*)0x03005008u)  // wake enable bits

#define IRQ_TIMER_BIT    (1u << 0)
#define IRQ_ML_BIT       (1u << 1)

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

int main(void) {
    uint32_t timeout;

    // Known reset state.
    TEST_STATUS = 0u;
    TEST_CODE = 0u;
    GPIO_OUT = 0u;
    TIMER_CTRL = 0u;
    TIMER_EVENT = 1u;
    PWR_WAKE_STATUS = 0xFFFFFFFFu;
    IRQC_PENDING = 0xFFFFFFFFu;

    // Enable timer (bit0) and ML (bit1) in IRQ routing + wake policy.
    IRQC_MASK = IRQ_TIMER_BIT | IRQ_ML_BIT;
    IRQC_WAKE_EN = IRQ_TIMER_BIT | IRQ_ML_BIT;

    // Short timer period for simulation.
    TIMER_RELOAD = 10000u;
    TIMER_COUNT = 10000u;
    TIMER_CTRL = 0x3u;  // enable + periodic

    // Sleep until timer IRQ is observed.
    PWR_CTRL = 1u;
    timeout = 1000000u;
    while (((IRQC_PENDING & IRQ_TIMER_BIT) == 0u) && timeout--) {}
    PWR_CTRL = 0u;
    if ((IRQC_PENDING & IRQ_TIMER_BIT) == 0u) fail(0xE201u);
    if ((PWR_WAKE_REASON & IRQ_TIMER_BIT) == 0u) fail(0xE202u);
    TIMER_EVENT = 1u;
    IRQC_PENDING = IRQ_TIMER_BIT;

    // Program taketwo WRAM base and field offsets before starting inference.
    // Without this, taketwo's AXI4 master defaults to address 0, which is
    // outside weight_ram_axi's window and causes the AXI4 bus to hang.
    ML_REG(0x80u) = 0x03006000u;  // global WRAM base (soc_top WEIGHT_BASE)
    ML_REG(0x88u) = 5504u;         // output logit offset
    ML_REG(0x8Cu) = 64u;           // input (x) offset
    ML_REG(0x90u) = 128u;          // weight/var offset

    // Prepare ML completion IRQ generation in taketwo.
    ML_IRQ_EN = 1u;
    ML_IRQ_CLR = 1u;
    if ((ML_IRQ_EN & 1u) == 0u) fail(0xE203u);

    // Trigger ML inference and sleep until ML IRQ pending.
    GPIO_OUT = GPIO_TRIG;
    ML_START = 1u;
    GPIO_OUT = 0u;

    PWR_CTRL = 1u;
    timeout = 5000000u;
    while (((IRQC_PENDING & IRQ_ML_BIT) == 0u) && timeout--) {}
    PWR_CTRL = 0u;
    if ((IRQC_PENDING & IRQ_ML_BIT) == 0u) fail(0xE204u);
    if ((PWR_WAKE_REASON & IRQ_ML_BIT) == 0u) fail(0xE205u);

    // Completion coherence: busy must clear and irq status must have asserted.
    timeout = 500000u;
    while ((ML_BUSY != 0u) && timeout--) {}
    if (ML_BUSY != 0u) fail(0xE206u);
    if ((ML_IRQ_STAT & 1u) == 0u) fail(0xE207u);

    ML_IRQ_CLR = 1u;
    IRQC_PENDING = IRQ_ML_BIT;
    PWR_WAKE_STATUS = 0xFFFFFFFFu;
    TEST_CODE = 0x1BADB002u;
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
