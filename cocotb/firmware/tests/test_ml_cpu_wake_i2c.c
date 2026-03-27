#include <stdint.h>

#define TEST_BASE        0x0300F000u
#define TEST_STATUS      (*(volatile uint32_t*)(TEST_BASE + 0x00u))
#define TEST_CODE        (*(volatile uint32_t*)(TEST_BASE + 0x04u))
#define CFG_TARGET_SEC   (*(volatile uint32_t*)(TEST_BASE + 0x08u))
#define CFG_WINDOW_SEC   (*(volatile uint32_t*)(TEST_BASE + 0x0Cu))
#define CFG_STEP_SEC     (*(volatile uint32_t*)(TEST_BASE + 0x10u))
#define CFG_MOTION       (*(volatile uint32_t*)(TEST_BASE + 0x14u))
#define CFG_CONF_THR     (*(volatile uint32_t*)(TEST_BASE + 0x18u))
#define CFG_POLICY       (*(volatile uint32_t*)(TEST_BASE + 0x1Cu))
#define ML_SCORE         (*(volatile uint32_t*)(TEST_BASE + 0x20u))

#define GPIO_OUT         (*(volatile uint32_t*)0x03000000u)
#define GPIO_TRIG        (1u << 0)

#define PWR_CTRL         (*(volatile uint32_t*)0x03001000u)
#define PWR_WAKE_STATUS  (*(volatile uint32_t*)0x03001004u)
#define PWR_WAKE_REASON  (*(volatile uint32_t*)0x03001008u)

#define TIMER_CTRL       (*(volatile uint32_t*)0x03002000u)
#define TIMER_RELOAD     (*(volatile uint32_t*)0x03002004u)
#define TIMER_COUNT      (*(volatile uint32_t*)0x03002008u)
#define TIMER_EVENT      (*(volatile uint32_t*)0x0300200Cu)

#define ML_BASE          0x03003000u
#define ML_REG(off)      (*(volatile uint32_t*)(ML_BASE + (off)))
#define ML_IRQ_STAT      ML_REG(0x24u)  // taketwo reg9
#define ML_IRQ_EN        ML_REG(0x28u)  // taketwo reg10
#define ML_IRQ_CLR       ML_REG(0x2Cu)  // taketwo reg11 (W1C bits)

#define IRQC_PENDING     (*(volatile uint32_t*)0x03005000u)
#define IRQC_MASK        (*(volatile uint32_t*)0x03005004u)
#define IRQC_WAKE_EN     (*(volatile uint32_t*)0x03005008u)
#define IRQC_CLAIM       (*(volatile uint32_t*)0x03005014u)
#define IRQC_COMPLETE    (*(volatile uint32_t*)0x03005018u)

#define WEIGHT_BASE      0x03006000u
#define WRAM_U32(off)    (*(volatile uint32_t*)(WEIGHT_BASE + (off)))
#define WRAM_I16(off)    (*(volatile int16_t*) (WEIGHT_BASE + (off)))

#define TEST_PASS        0xCAFEBABEu
#define TEST_FAIL        0xDEADBEEFu

#define IRQ_TIMER_BIT    (1u << 0)
#define IRQ_ML_BIT       (1u << 1)
#define IRQ_HOST_BIT     (1u << 2)

#define FEAT_X_BASE      64u
#define FEAT_LOGIT_BASE  5504u
#define WEIGHT_WORDS     16u

#define POLICY_DEADLINE_OVERRIDE (1u << 0)

#define BP_PREWINDOW_NOALARM   (1u << 0)
#define BP_INWINDOW_ALARM      (1u << 1)
#define BP_DEADLINE_NOOVR      (1u << 2)
#define BP_DEADLINE_OVR        (1u << 3)
#define BP_MISSED_NOOVR        (1u << 4)
#define BP_ALL_EXPECTED (BP_PREWINDOW_NOALARM | BP_INWINDOW_ALARM | \
                         BP_DEADLINE_NOOVR | BP_DEADLINE_OVR | BP_MISSED_NOOVR)

static void fail(uint32_t code) {
    TEST_CODE = code;
    TEST_STATUS = TEST_FAIL;
    for (;;) {}
}

static volatile uint32_t g_timer_irq_count;
static volatile uint32_t g_ml_irq_count;
static volatile uint32_t g_host_irq_count;
static volatile uint32_t g_ml_done_flag;
static volatile uint32_t g_irq_entries;
static volatile uint32_t g_irq_claims;
static volatile uint32_t g_irq_bad_claims;
static volatile uint32_t g_irq_unknown_src;
static volatile uint32_t g_irq_guard_exhausted;
static volatile uint32_t g_irq_late_count;

void irq_handler(void) {
    uint32_t guard = 16u;
    g_irq_entries++;
    while (guard--) {
        uint32_t claim = IRQC_CLAIM;
        uint32_t bit;
        uint32_t pending_snapshot;
        if (claim == 0u) break;
        if (claim > 32u) {
            g_irq_bad_claims++;
            break;
        }
        bit = 1u << (claim - 1u);
        g_irq_claims++;

        // Mark active claim for visibility in controller state.
        IRQC_CLAIM = claim;
        pending_snapshot = IRQC_PENDING;
        if ((pending_snapshot & bit) == 0u) g_irq_late_count++;

        if (bit & IRQ_TIMER_BIT) {
            g_timer_irq_count++;
            TIMER_EVENT = 1u;
        } else if (bit & IRQ_ML_BIT) {
            g_ml_irq_count++;
            g_ml_done_flag = 1u;
            // taketwo IRQ is level-latched via status bit; clear it in ISR.
            ML_IRQ_CLR = 1u;
        } else if (bit & IRQ_HOST_BIT) {
            g_host_irq_count++;
        } else {
            g_irq_unknown_src++;
        }

        IRQC_PENDING = bit;     // W1C pending source
        IRQC_COMPLETE = claim;  // clear active claim slot
    }
    if (guard == 0u) g_irq_guard_exhausted++;
}

static inline void cpu_irq_unmask_all(void) {
    // PicoRV32 custom instruction: maskirq x0, x0 (set irq_mask = 0).
    __asm__ volatile (".word 0x0600000b" ::: "memory");
}

static int wait_irq_pending(uint32_t mask, uint32_t limit) {
    while (limit--) {
        if (IRQC_PENDING & mask) return 1;
    }
    return 0;
}

static int wait_ml_done(uint32_t limit) {
    while (limit--) {
        if (ML_REG(0x14) == 0u) return 1;
    }
    return 0;
}

static uint16_t abs_i16(int16_t x) {
    return (x < 0) ? (uint16_t)(-x) : (uint16_t)x;
}

static int16_t clamp_i16(int32_t v) {
    if (v > 32767) return 32767;
    if (v < -32768) return -32768;
    return (int16_t)v;
}

static uint16_t synthetic_motion(uint32_t epoch) {
    switch (epoch & 3u) {
        case 0u: return 220u;
        case 1u: return 260u;
        case 2u: return 920u;
        default: return 180u;
    }
}

static int16_t synthetic_cosine_q13(uint32_t elapsed_sec, uint32_t step_sec) {
    uint32_t phase = (step_sec == 0u) ? 0u : ((elapsed_sec / step_sec) & 3u);
    if (phase == 0u) return 8192;
    if (phase == 2u) return -8192;
    return 0;
}

static uint32_t sat_u16_from_u32(uint32_t v) {
    return (v > 0xFFFFu) ? 0xFFFFu : v;
}

static uint32_t should_alarm(uint32_t elapsed_sec,
                             uint32_t target_sec,
                             uint32_t window_sec,
                             uint16_t conf,
                             uint16_t conf_thr,
                             uint32_t policy) {
    uint32_t lower;
    uint32_t in_window;
    uint32_t deadline_reached;

    if (window_sec > target_sec) lower = 0u;
    else lower = target_sec - window_sec;
    in_window = (elapsed_sec >= lower) && (elapsed_sec < target_sec);
    deadline_reached = (elapsed_sec >= target_sec);

    if ((in_window && (conf >= conf_thr)) ||
        (deadline_reached && (policy & POLICY_DEADLINE_OVERRIDE))) {
        return 1u;
    }
    return 0u;
}

int main(void) {
    uint32_t i;
    uint32_t epoch;
    uint32_t elapsed_sec;
    uint32_t ml_runs;
    uint32_t skip_runs;
    uint32_t motion_hi_streak;
    uint32_t target_sec;
    uint32_t window_sec;
    uint32_t step_sec;
    uint32_t conf_thr;
    uint32_t policy;
    uint32_t alarm_fired;
    uint32_t last_conf;
    uint32_t boundary_flags;

    TEST_STATUS = 0u;
    TEST_CODE = 0u;
    GPIO_OUT = 0u;
    g_timer_irq_count = 0u;
    g_ml_irq_count = 0u;
    g_host_irq_count = 0u;
    g_ml_done_flag = 0u;
    g_irq_entries = 0u;
    g_irq_claims = 0u;
    g_irq_bad_claims = 0u;
    g_irq_unknown_src = 0u;
    g_irq_guard_exhausted = 0u;
    g_irq_late_count = 0u;

    PWR_CTRL = 0u;
    PWR_WAKE_STATUS = 0xFFFFFFFFu;
    IRQC_PENDING = 0xFFFFFFFFu;
    TIMER_CTRL = 0u;
    TIMER_EVENT = 1u;

    IRQC_MASK = IRQ_TIMER_BIT | IRQ_ML_BIT | IRQ_HOST_BIT;
    IRQC_WAKE_EN = IRQ_TIMER_BIT | IRQ_ML_BIT | IRQ_HOST_BIT;
    cpu_irq_unmask_all();

    for (i = 0; i < WEIGHT_WORDS; i++) {
        WRAM_U32(i * 4u) = 0u;
    }

    if (WRAM_U32(0u) != 0u) fail(0xE001u);
    if (WRAM_U32(32u * 4u) != 0u) fail(0xE002u);
    if (WRAM_U32((WEIGHT_WORDS - 1u) * 4u) != 0u) fail(0xE003u);

    ML_REG(0x80) = WEIGHT_BASE;
    ML_IRQ_EN = 1u;      // enable busy-edge completion IRQ inside taketwo
    ML_IRQ_CLR = 1u;     // clear stale status bit0
    if ((ML_IRQ_EN & 1u) == 0u) fail(0xE004u);

    // Let host-I2C programming settle before latching policy/config values.
    // TB drives target=900, window=600, step=300 using byte writes.
    {
        uint32_t cfg_wait = 12000000u;
        while (((CFG_TARGET_SEC != 900u) ||
                (CFG_WINDOW_SEC != 600u) ||
                ((CFG_STEP_SEC & 0xFFFFu) != 300u)) && cfg_wait--) {
            __asm__ volatile ("nop");
        }
    }

    target_sec = CFG_TARGET_SEC;
    if (target_sec == 0u) target_sec = 1800u;
    window_sec = CFG_WINDOW_SEC;
    if (window_sec == 0u) window_sec = target_sec;
    step_sec = CFG_STEP_SEC & 0xFFFFu;
    if (step_sec == 0u) step_sec = 300u;
    conf_thr = CFG_CONF_THR & 0xFFFFu;
    if (conf_thr == 0u) conf_thr = 0x0400u;
    policy = CFG_POLICY & 0xFFu;

    TIMER_RELOAD = 2000u;
    TIMER_COUNT = 2000u;
    TIMER_CTRL = 0x3u; // periodic

    elapsed_sec = 0u;
    ml_runs = 0u;
    skip_runs = 0u;
    motion_hi_streak = 0u;
    alarm_fired = 0u;
    last_conf = 1u;
    boundary_flags = 0u;

    for (epoch = 0u; epoch < 3u; epoch++) {
        uint32_t motion_cfg;
        uint32_t motion_hi_th;
        uint32_t motion_hi_cnt;
        uint32_t motion_mag;
        uint32_t lower;

        TEST_CODE = 0x10000000u | epoch;

        // Sleep until periodic timer interrupt serviced by irq_handler().
        PWR_WAKE_STATUS = 0xFFFFFFFFu;
        TIMER_EVENT = 1u;
        {
            uint32_t timer_before = g_timer_irq_count;
            uint32_t timeout = 200000u;
            PWR_CTRL = 1u;
            while ((g_timer_irq_count == timer_before) &&
                   ((IRQC_PENDING & IRQ_TIMER_BIT) == 0u) &&
                   timeout--) {
                __asm__ volatile ("nop");
            }
            PWR_CTRL = 0u;
            if ((g_timer_irq_count == timer_before) &&
                ((IRQC_PENDING & IRQ_TIMER_BIT) == 0u)) fail(0xE110u);
            IRQC_PENDING = IRQ_TIMER_BIT;
        }
        if ((PWR_WAKE_REASON & IRQ_TIMER_BIT) == 0u) fail(0xE111u);
        TEST_CODE = 0x11000000u | epoch;

        elapsed_sec += step_sec;

        motion_cfg = CFG_MOTION;
        motion_hi_th = motion_cfg & 0xFFFFu;
        motion_hi_cnt = (motion_cfg >> 16) & 0xFFu;
        if (motion_hi_th == 0u) motion_hi_th = 800u;
        if (motion_hi_cnt == 0u) motion_hi_cnt = 2u;

        motion_mag = (uint32_t)synthetic_motion(epoch);
        if (motion_mag >= motion_hi_th) motion_hi_streak++;
        else motion_hi_streak = 0u;

        if (motion_hi_streak >= motion_hi_cnt) {
            // Consider user awake: skip inference this epoch.
            skip_runs++;
            TEST_CODE = 0xA0000000u | (motion_mag & 0xFFFFu);
            continue;
        }

        // Build feature vector into x_base (Q3.13).
        {
            int16_t movement_q13 = clamp_i16((int32_t)(motion_mag << 3));
            int16_t cosine_q13 = synthetic_cosine_q13(elapsed_sec, step_sec);
            int16_t delta_hr_q13 = (int16_t)((int32_t)((epoch % 3u) * 1024u) - 1024);
            int16_t rmssd_q13 = (int16_t)(2048 + (int16_t)(epoch * 128u));
            WRAM_I16(FEAT_X_BASE + 0u) = movement_q13;
            WRAM_I16(FEAT_X_BASE + 2u) = cosine_q13;
            WRAM_I16(FEAT_X_BASE + 4u) = delta_hr_q13;
            WRAM_I16(FEAT_X_BASE + 6u) = rmssd_q13;
        }

        TEST_CODE = 0x13000000u | epoch;
        // Strict IRQ contract: completion must assert ml_irq -> IRQC pending bit1.
        {
            uint32_t ml_before = g_ml_irq_count;
            uint32_t timeout = 200000u;
            g_ml_done_flag = 0u;
            IRQC_PENDING = IRQ_ML_BIT;
            ML_IRQ_CLR = 1u;
            ML_REG(0x10) = 1u;
            while ((g_ml_done_flag == 0u) && timeout--) {
                __asm__ volatile ("nop");
            }
            if (g_ml_done_flag == 0u) fail(0xE122u);
            if (g_ml_irq_count == ml_before) fail(0xE124u);
        }
        if (!wait_ml_done(100000u)) fail(0xE123u);
        if ((ML_IRQ_STAT & 1u) != 0u) fail(0xE125u);
        TEST_CODE = 0x14000000u | epoch;
        ML_REG(0x10) = 0u;

        {
            int16_t log0 = WRAM_I16(FEAT_LOGIT_BASE + 0u);
            int16_t log1 = WRAM_I16(FEAT_LOGIT_BASE + 2u);
            int16_t diff = (int16_t)(log0 - log1);
            uint16_t conf = abs_i16(diff);
            uint32_t in_window;
            uint32_t deadline_reached;

            if (window_sec > target_sec) lower = 0u;
            else lower = target_sec - window_sec;
            in_window = (elapsed_sec >= lower) && (elapsed_sec < target_sec);
            deadline_reached = (elapsed_sec >= target_sec);

            if (conf == 0u) conf = 1u;
            TEST_CODE = (uint32_t)conf; // host I2C confidence threshold compares this
            ml_runs++;

            last_conf = conf;
            if (should_alarm(elapsed_sec, target_sec, window_sec, (uint16_t)conf, (uint16_t)conf_thr, policy)) {
                alarm_fired = 1u;
                GPIO_OUT = GPIO_TRIG;
                break;
            }
        }
    }

    if (!alarm_fired) fail(0xE130u);

    // Confirm host-I2C threshold event path also wakes CPU when armed.
    // Write score=0 first so above_thr_live goes low, re-arming conf_armed.
    // Then clear the pending bit. Then re-write score to create a guaranteed
    // 0→1 rising edge on host_i2c_irq_event → new pending bit → CPU wakes.
    ML_SCORE = 0u;
    PWR_WAKE_STATUS = 0xFFFFFFFFu;
    {
        uint32_t host_before = g_host_irq_count;
        uint32_t timeout = 200000u;
        IRQC_PENDING = IRQ_HOST_BIT;
        ML_SCORE = last_conf;
        PWR_CTRL = 1u;
        while ((g_host_irq_count == host_before) &&
               ((IRQC_PENDING & IRQ_HOST_BIT) == 0u) &&
               timeout--) {
            __asm__ volatile ("nop");
        }
        PWR_CTRL = 0u;
        if ((g_host_irq_count == host_before) &&
            ((IRQC_PENDING & IRQ_HOST_BIT) == 0u)) fail(0xE131u);
        IRQC_PENDING = IRQ_HOST_BIT;
    }
    if ((PWR_WAKE_REASON & IRQ_HOST_BIT) == 0u) fail(0xE132u);

    // Wake-policy boundary matrix checks:
    //  pre-window: no alarm even when confidence is high.
    //  in-window: alarm when confidence is high.
    //  deadline/no-override: no alarm.
    //  deadline/override: alarm even with low confidence.
    //  missed window/no-override: no alarm.
    {
        uint32_t lower = (window_sec > target_sec) ? 0u : (target_sec - window_sec);
        uint32_t pre = (lower > 0u) ? (lower - 1u) : 0u;
        if (should_alarm(pre, target_sec, window_sec, (uint16_t)(conf_thr + 8u), (uint16_t)conf_thr, policy) == 0u)
            boundary_flags |= BP_PREWINDOW_NOALARM;
        if (should_alarm(lower, target_sec, window_sec, (uint16_t)(conf_thr + 8u), (uint16_t)conf_thr, policy) == 1u)
            boundary_flags |= BP_INWINDOW_ALARM;
        if (should_alarm(target_sec, target_sec, window_sec, (uint16_t)(conf_thr + 8u), (uint16_t)conf_thr, 0u) == 0u)
            boundary_flags |= BP_DEADLINE_NOOVR;
        if (should_alarm(target_sec, target_sec, window_sec, 1u, (uint16_t)conf_thr, POLICY_DEADLINE_OVERRIDE) == 1u)
            boundary_flags |= BP_DEADLINE_OVR;
        if (should_alarm(target_sec + step_sec, target_sec, window_sec, (uint16_t)(conf_thr + 8u), (uint16_t)conf_thr, 0u) == 0u)
            boundary_flags |= BP_MISSED_NOOVR;
    }

    if (boundary_flags != BP_ALL_EXPECTED) {
        fail(0xE1330000u | (boundary_flags & 0xFFu));
    }
    if (g_irq_entries < 4u) fail(0xE134u);
    if (g_irq_claims < 4u) fail(0xE135u);
    if (g_irq_bad_claims != 0u) fail(0xE136u);
    if (g_irq_unknown_src != 0u) fail(0xE137u);
    if (g_irq_guard_exhausted != 0u) fail(0xE138u);
    if (g_irq_late_count != 0u) fail(0xE139u);

    // Pack summary: [31:24]=ml_runs [23:16]=skip_runs [15:8]=boundary_flags [7:0]=elapsed steps
    TEST_CODE = ((sat_u16_from_u32(ml_runs) & 0xFFu) << 24) |
                ((sat_u16_from_u32(skip_runs) & 0xFFu) << 16) |
                ((boundary_flags & 0xFFu) << 8) |
                ((step_sec == 0u) ? 0u : ((elapsed_sec / step_sec) & 0xFFu));
    TEST_STATUS = TEST_PASS;

    for (;;) {}
}
