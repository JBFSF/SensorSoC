#include <stdint.h>

// Unified-top repeated sleep/wake regression.
// Each iteration runs:
//   1. timer_mmio -> pwrctrl_mmio sleep -> timer wake -> clear sticky state
//   2. taketwo completion IRQ -> irq_ctrl_mmio claim/complete -> wake CPU
// The goal is to prove that the sleep/wake machinery keeps working across
// multiple cycles, not just the first one.

#define TIMER_BASE     0x03002000u
#define PWR_BASE       0x03001000u
#define IRQC_BASE      0x03005000u
#define TEST_BASE      0x0300F000u
#define ML_BASE        0x03003000u
#define WEIGHT_BASE    0x03006000u

#define T_CTRL         (*(volatile uint32_t*)(TIMER_BASE + 0x00u))
#define T_RELOAD       (*(volatile uint32_t*)(TIMER_BASE + 0x04u))
#define T_COUNT        (*(volatile uint32_t*)(TIMER_BASE + 0x08u))
#define T_EVENT        (*(volatile uint32_t*)(TIMER_BASE + 0x0Cu))

#define P_CTRL         (*(volatile uint32_t*)(PWR_BASE + 0x00u))
#define P_WAKE_STATUS  (*(volatile uint32_t*)(PWR_BASE + 0x04u))
#define P_WAKE_REASON  (*(volatile uint32_t*)(PWR_BASE + 0x08u))

#define IRQC_PENDING   (*(volatile uint32_t*)(IRQC_BASE + 0x00u))
#define IRQC_MASK      (*(volatile uint32_t*)(IRQC_BASE + 0x04u))
#define IRQC_WAKE_EN   (*(volatile uint32_t*)(IRQC_BASE + 0x08u))
#define IRQC_CLAIM     (*(volatile uint32_t*)(IRQC_BASE + 0x14u))
#define IRQC_COMPLETE  (*(volatile uint32_t*)(IRQC_BASE + 0x18u))

#define TEST_STATUS    (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE      (*(volatile uint32_t*)(TEST_BASE + 0x04u))

#define TEST_PASS      0xCAFEBABEu
#define TEST_FAIL      0xDEADBEEFu

#define IRQ_TIMER_BIT  (1u << 0)
#define IRQ_ML_BIT     (1u << 1)

#define ML_REG(off)    (*(volatile uint32_t*)(ML_BASE + (off)))
#define WRAM_U32(off)  (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off)  (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define ML_IRQ_EN      ML_REG(0x28u)
#define ML_IRQ_CLR     ML_REG(0x2Cu)

#define X_BASE         64u
#define VAR_BASE       128u
#define LOGIT_BASE     5504u
#define OUT0_SENTINEL  0xA5A55A5Au
#define OUT1_SENTINEL  0x5A5AA5A5u
#define NUM_ITERS      2u

// Bench-visible software counters. These are intentionally simple so the SV
// bench can tell whether the IRQ service path is behaving repeatedly.
static volatile uint32_t g_ml_done_flag;
static volatile uint32_t g_ml_irq_count;
static volatile uint32_t g_irq_claims;
static volatile uint32_t g_irq_bad_claims;

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static int wait_until_set(volatile uint32_t *reg, uint32_t mask, uint32_t limit)
{
    while (limit--) {
        if ((*reg & mask) != 0u) return 1;
        __asm__ volatile ("nop");
    }
    return 0;
}

static int wait_until_clear(volatile uint32_t *reg, uint32_t mask, uint32_t limit)
{
    while (limit--) {
        if ((*reg & mask) == 0u) return 1;
        __asm__ volatile ("nop");
    }
    return 0;
}

static inline void cpu_irq_unmask_all(void) {
    __asm__ volatile (".word 0x0600000b" ::: "memory");
}

// Minimal IRQ service routine for the dedicated sleep/wake regression.
// Only the ML path uses CPU IRQ service here; timer wake is intentionally
// validated through the polling path so the two wake mechanisms are separated.
void irq_handler(void)
{
    uint32_t guard = 16u;

    while (guard--) {
        uint32_t claim = IRQC_CLAIM;
        uint32_t bit;

        if (claim == 0u) break;
        if (claim > 32u) {
            g_irq_bad_claims++;
            break;
        }

        bit = 1u << (claim - 1u);
        g_irq_claims++;
        IRQC_CLAIM = claim;

        if (bit & IRQ_ML_BIT) {
            g_ml_irq_count++;
            IRQC_MASK = 0u;
            ML_IRQ_CLR = 1u;
            g_ml_done_flag = 1u;
        }

        IRQC_PENDING = bit;
        IRQC_COMPLETE = claim;
    }
}

// Timer-only sleep/wake subtest:
//   arm one-shot timer -> request sleep -> resume on timer wake
//   -> verify sticky state -> clear timer-related pending/status bits.
static void run_timer_phase(uint32_t iter,
                            uint32_t *wake_status_out,
                            uint32_t *wake_reason_out,
                            uint32_t *pending_out)
{
    P_CTRL = 0u;
    P_WAKE_STATUS = 0xFFFFFFFFu;
    IRQC_PENDING = 0xFFFFFFFFu;
    IRQC_MASK = 0u;
    IRQC_WAKE_EN = IRQ_TIMER_BIT;
    T_CTRL = 0u;
    T_EVENT = 1u;

    T_RELOAD = 64u + (iter * 8u);
    T_COUNT = 24u + (iter * 4u);
    T_CTRL = 0x1u;

    P_CTRL = 1u;

    if (!wait_until_set(&T_EVENT, 1u, 200000u)) fail(0xE900u | iter);
    if (!wait_until_set(&P_WAKE_STATUS, IRQ_TIMER_BIT, 200000u)) fail(0xE910u | iter);
    if (!wait_until_set(&IRQC_PENDING, IRQ_TIMER_BIT, 200000u)) fail(0xE920u | iter);

    *wake_status_out = P_WAKE_STATUS;
    *wake_reason_out = P_WAKE_REASON;
    *pending_out = IRQC_PENDING;

    if (((*wake_status_out) & IRQ_TIMER_BIT) == 0u) fail(0xE930u | iter);
    if (((*wake_reason_out) & IRQ_TIMER_BIT) == 0u) fail(0xE940u | iter);
    if (((*pending_out) & IRQ_TIMER_BIT) == 0u) fail(0xE950u | iter);

    P_CTRL = 0u;
    T_EVENT = 1u;
    IRQC_PENDING = IRQ_TIMER_BIT;
    P_WAKE_STATUS = IRQ_TIMER_BIT;

    if (!wait_until_clear(&T_EVENT, 1u, 50000u)) fail(0xE960u | iter);
    if (!wait_until_clear(&IRQC_PENDING, IRQ_TIMER_BIT, 50000u)) fail(0xE970u | iter);
    if (!wait_until_clear(&P_WAKE_STATUS, IRQ_TIMER_BIT, 50000u)) fail(0xE980u | iter);
}

// ML-only sleep/wake subtest:
//   arm ML wake -> start taketwo -> request sleep -> wake through IRQ handler
//   -> verify pending/reason bookkeeping -> clear ML-related sticky state.
static void run_ml_phase(uint32_t iter,
                         uint32_t *wake_status_out,
                         uint32_t *wake_reason_out,
                         uint32_t *pending_out)
{
    uint32_t prev_ml_irq_count = g_ml_irq_count;

    WRAM_I16(X_BASE + 0u) = (int16_t)(0x0100 + (iter * 0x0010));
    WRAM_I16(X_BASE + 2u) = (int16_t)(0x0200 + (iter * 0x0010));
    WRAM_I16(X_BASE + 4u) = (int16_t)(0x0040 + (iter * 0x0004));
    WRAM_I16(X_BASE + 6u) = (int16_t)(0x0080 + (iter * 0x0004));

    WRAM_U32(LOGIT_BASE + 0u) = OUT0_SENTINEL;
    WRAM_U32(LOGIT_BASE + 4u) = OUT1_SENTINEL;

    P_WAKE_STATUS = 0xFFFFFFFFu;
    IRQC_PENDING = 0xFFFFFFFFu;
    IRQC_MASK = IRQ_ML_BIT;
    IRQC_WAKE_EN = IRQ_ML_BIT;
    ML_IRQ_EN = 1u;
    ML_IRQ_CLR = 1u;

    g_ml_done_flag = 0u;
    ML_REG(0x10u) = 1u;
    P_CTRL = 1u;

    if (!wait_until_set(&g_ml_done_flag, 1u, 500000u)) fail(0xE990u | iter);
    if (g_ml_irq_count == prev_ml_irq_count) fail(0xE9A0u | iter);
    if (g_irq_bad_claims != 0u) fail(0xE9B0u | iter);

    *wake_status_out = P_WAKE_STATUS;
    *wake_reason_out = P_WAKE_REASON;
    *pending_out = IRQC_PENDING;

    if (((*wake_status_out) & IRQ_ML_BIT) == 0u) fail(0xE9C0u | iter);
    if (((*wake_reason_out) & IRQ_ML_BIT) == 0u) fail(0xE9D0u | iter);
    if (((*pending_out) & IRQ_ML_BIT) != 0u) fail(0xE9E0u | iter);

    while ((ML_REG(0x14u) & 1u) != 0u) {}
    ML_REG(0x10u) = 0u;
    P_CTRL = 0u;

    ML_IRQ_CLR = 1u;
    P_WAKE_STATUS = IRQ_ML_BIT;
    if (!wait_until_clear(&P_WAKE_STATUS, IRQ_ML_BIT, 200000u)) fail(0xE9F0u | iter);
}

int main(void) {
    uint32_t iter;
    uint32_t wake_status;
    uint32_t wake_reason;
    uint32_t pending_after_wake;
    uint32_t ml_wake_status;
    uint32_t ml_wake_reason;
    uint32_t ml_pending_after_wake;
    uint32_t summary;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;
    g_ml_done_flag = 0u;
    g_ml_irq_count = 0u;
    g_irq_claims = 0u;
    g_irq_bad_claims = 0u;

    ML_REG(0x80u) = WEIGHT_BASE;
    if (ML_REG(0x80u) != WEIGHT_BASE) fail(0xE909u);
    ML_REG(0x88u) = LOGIT_BASE;
    if (ML_REG(0x88u) != LOGIT_BASE) fail(0xE90Au);
    ML_REG(0x8Cu) = X_BASE;
    if (ML_REG(0x8Cu) != X_BASE) fail(0xE90Bu);
    ML_REG(0x90u) = VAR_BASE;
    if (ML_REG(0x90u) != VAR_BASE) fail(0xE90Cu);

    cpu_irq_unmask_all();

    // Repeat the two wake modes back-to-back so the test catches stale-state
    // bugs that only show up on the second or third sleep entry.
    for (iter = 0u; iter < NUM_ITERS; iter++) {
        run_timer_phase(iter, &wake_status, &wake_reason, &pending_after_wake);
        run_ml_phase(iter, &ml_wake_status, &ml_wake_reason, &ml_pending_after_wake);
    }

    // Compact summary for bench-side visibility:
    //   [31:24] iteration count
    //   [23:16] ML IRQ count low byte
    //   [15:8]  IRQ claim count low byte
    //   [7:0]   combined last wake-reason low bits
    summary =
        ((NUM_ITERS & 0xFFu) << 24) |
        ((g_ml_irq_count & 0xFFu) << 16) |
        ((g_irq_claims & 0xFFu) << 8) |
        ((wake_reason | ml_wake_reason) & 0xFFu);

    TEST_CODE = summary;
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
