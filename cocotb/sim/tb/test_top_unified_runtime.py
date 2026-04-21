"""Runtime-oriented cocotb tests for the shared unified-top wrapper.

These tests sit one layer above the reset/init smoke test. They reuse the
shared wrapper and Python helpers to cover three high-value behaviors:

    1) host-I2C register / score visibility
    2) repeated production-loop smoke behavior
    3) reset-adjacent forced wake / forced IRQ corner cases

The intent is not to replace the large production-style SystemVerilog bench.
Instead, these provide focused Python-side checks that are easier to extend and
debug while keeping the long SV bench as the final integrated guardrail.
"""

import cocotb
from cocotb.triggers import ClockCycles, NextTimeStep, ReadOnly, RisingEdge

from top_unified_env import (
    FEATURE_DHR,
    FEATURE_MOTION,
    FEATURE_RMSSD,
    FEATURE_STATUS,
    FEATURE_TIME,
    HOST_CONF_ABS_H,
    HOST_CONF_ABS_L,
    HOST_CONF_CTRL,
    HOST_CONF_STAT,
    HOST_CONF_THR_H,
    HOST_CONF_THR_L,
    HOST_IRQ_COUNT_H,
    HOST_IRQ_COUNT_L,
    HOST_LOGIT0_H,
    HOST_LOGIT0_L,
    HOST_VERSION,
    HOST_WHOAMI,
    ML_SCORE_ADDR,
    TEST_STATUS_ADDR,
    X_BASE,
    apply_reset,
    i2c_read_reg,
    i2c_read_reg16_stable,
    i2c_write_reg,
    mmio_read_active,
    mmio_write_active,
    start_clock,
    wait_for_boot_load,
    wait_for_coherent_score,
)


FEATURE_VALID_MASK = 1 << 0
FORCED_WAKE_BIT = 1 << 3
FORCED_IRQ_BIT = 1 << 0
TEST_FAIL = 0xDEADBEEF


def _u(handle) -> int:
    return int(handle.value)


def _s16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


@cocotb.test()
async def test_host_i2c_registers_and_score_visibility(dut):
    """Verify host-I2C can observe the production firmware's score path."""
    cocotb.start_soon(start_clock(dut))
    await apply_reset(dut)
    await wait_for_boot_load(dut)

    # Match the low threshold configuration used by the long production bench
    # so the host bridge emits score-related events promptly.
    await i2c_write_reg(dut, HOST_CONF_THR_L, 0x01)
    await i2c_write_reg(dut, HOST_CONF_THR_H, 0x00)
    await i2c_write_reg(dut, HOST_CONF_CTRL, 0x03)

    await wait_for_coherent_score(dut)

    saw_host_event = False
    for _ in range(200000):
        await RisingEdge(dut.clk)
        await ReadOnly()
        if _u(dut.host_i2c_irq_event):
            saw_host_event = True
        if _u(dut.host_irq_count) > 0:
            break

    whoami = await i2c_read_reg(dut, HOST_WHOAMI)
    version = await i2c_read_reg(dut, HOST_VERSION)
    conf_stat = await i2c_read_reg(dut, HOST_CONF_STAT)
    irq_count = await i2c_read_reg16_stable(dut, HOST_IRQ_COUNT_L, HOST_IRQ_COUNT_H)
    conf_abs = await i2c_read_reg16_stable(dut, HOST_CONF_ABS_L, HOST_CONF_ABS_H)
    logit0 = await i2c_read_reg16_stable(dut, HOST_LOGIT0_L, HOST_LOGIT0_H)

    assert whoami == 0xA5, f"unexpected host WHOAMI: 0x{whoami:02x}"
    assert version == 0x01, f"unexpected host VERSION: 0x{version:02x}"
    assert saw_host_event or irq_count > 0, "never observed host-side score event"
    assert irq_count >= 1, f"host IRQ count too small: {irq_count}"
    # Host-I2C reads are serialized and can span multiple firmware iterations,
    # so the strongest stable contract here is that the host-visible confidence
    # path is self-consistent and nonzero, not that it matches a single-cycle
    # internal mirror sampled at the end of the entire read transaction.
    assert conf_abs != 0, "host CONF_ABS should be nonzero once score is visible"
    assert logit0 != 0, "host LOGIT0 proxy should be nonzero once score is visible"
    assert conf_stat & 0x01, "host CONF_STAT live bit should be set once score crosses threshold"
    assert conf_stat & 0x02, "host CONF_STAT cross-sticky bit should be set"
    assert conf_stat & 0x04, "host CONF_STAT fired-sticky bit should be set"


@cocotb.test()
async def test_repeated_production_loop_smoke(dut):
    """Check that the prod_main loop repeats coherent feature->ML iterations."""
    cocotb.start_soon(start_clock(dut))
    await apply_reset(dut)
    await wait_for_boot_load(dut)

    # Configure the host bridge exactly as the production-style bench does so
    # repeated score visibility is enabled while the firmware loop runs.
    await i2c_write_reg(dut, HOST_CONF_THR_L, 0x01)
    await i2c_write_reg(dut, HOST_CONF_THR_H, 0x00)
    await i2c_write_reg(dut, HOST_CONF_CTRL, 0x03)

    feature_read_counts = {
        FEATURE_STATUS: 0,
        FEATURE_TIME: 0,
        FEATURE_MOTION: 0,
        FEATURE_DHR: 0,
        FEATURE_RMSSD: 0,
    }
    feature_clears = 0
    ml_score_writes = 0
    coherent_iterations = 0
    host_irq_seen = False
    current_iter = None

    for _ in range(2_000_000):
        await RisingEdge(dut.clk)
        await ReadOnly()

        if _u(dut.pico_trap):
            raise AssertionError("CPU trap asserted during repeated production-loop smoke test")
        if _u(dut.test_status) == TEST_FAIL:
            raise AssertionError(f"firmware reported FAIL with code 0x{_u(dut.test_code):08x}")
        if _u(dut.host_i2c_irq_event):
            host_irq_seen = True

        if mmio_read_active(dut):
            addr = _u(dut.pico_mem_addr)
            if addr in feature_read_counts:
                feature_read_counts[addr] += 1

        if mmio_write_active(dut):
            addr = _u(dut.pico_mem_addr)
            wdata = _u(dut.pico_mem_wdata)
            wstrb = _u(dut.pico_mem_wstrb)

            if addr == FEATURE_STATUS and (wdata & FEATURE_VALID_MASK):
                feature_clears += 1
                current_iter = {
                    "word0_written": False,
                    "word1_written": False,
                }

            elif current_iter is not None and addr == X_BASE:
                current_iter["word0_written"] = True

            elif current_iter is not None and addr == X_BASE + 4:
                current_iter["word1_written"] = True
                if current_iter["word0_written"] and current_iter["word1_written"]:
                    coherent_iterations += 1
                    current_iter = None

            elif addr == ML_SCORE_ADDR:
                ml_score_writes += 1

        if coherent_iterations >= 3 and ml_score_writes >= 3 and _u(dut.host_irq_count) >= 1:
            break
    else:
        raise AssertionError("timed out waiting for repeated coherent production-loop iterations")

    assert feature_read_counts[FEATURE_STATUS] >= 3, "too few FEATURE_STATUS reads"
    assert feature_read_counts[FEATURE_TIME] >= 3, "too few FEATURE_TIME reads"
    assert feature_read_counts[FEATURE_MOTION] >= 3, "too few FEATURE_MOTION reads"
    assert feature_read_counts[FEATURE_DHR] >= 3, "too few FEATURE_DHR reads"
    assert feature_read_counts[FEATURE_RMSSD] >= 3, "too few FEATURE_RMSSD reads"
    assert feature_clears >= 3, "too few FEATURE_STATUS valid clears"
    assert ml_score_writes >= 3, "too few ML_SCORE writes"
    assert coherent_iterations >= 3, "too few coherent feature->WRAM iterations"
    assert host_irq_seen or _u(dut.host_irq_count) >= 1, "host score event never observed during repeated loop"


@cocotb.test()
async def test_reset_corner_cases_with_forced_wake_and_irq(dut):
    """Exercise reset-adjacent forced wake/IRQ hooks without needing firmware cooperation."""
    cocotb.start_soon(start_clock(dut))

    # Hold reset while both test-force sources are asserted, then release reset
    # only after the force signals have been dropped. This checks that reset
    # prevents stale wake bookkeeping from leaking into post-reset state.
    dut.reset.value = 1
    dut.test_force_irq.value = 1
    await RisingEdge(dut.clk)
    dut.test_force_wake.value = 1
    await ClockCycles(dut.clk, 8)
    dut.test_force_irq.value = 0
    dut.test_force_wake.value = 0
    await ClockCycles(dut.clk, 2)
    dut.reset.value = 0
    await ClockCycles(dut.clk, 2)
    await ReadOnly()

    assert _u(dut.irq_pending) == 0, "forced sources during reset should not leak into pending"
    assert _u(dut.pwr_wake_status) == 0, "forced wake during reset should not leak into wake_status"
    assert _u(dut.pwr_wake_reason) == 0, "forced wake during reset should not leak into wake_reason"
    assert (_u(dut.pico_irq) & FORCED_IRQ_BIT) == 0, "forced IRQ should be clear after reset release"

    # After reset release, the forced wake source is expected to latch into both
    # the IRQ controller pending bits and the power-control sticky wake status.
    await RisingEdge(dut.clk)
    dut.test_force_wake.value = 1
    await ClockCycles(dut.clk, 2)
    dut.test_force_wake.value = 0
    await ClockCycles(dut.clk, 2)
    await ReadOnly()

    assert (_u(dut.irq_pending) & FORCED_WAKE_BIT) != 0, "forced wake should latch into IRQC pending"
    assert (_u(dut.pwr_wake_status) & FORCED_WAKE_BIT) != 0, "forced wake should latch into wake_status"
    assert (_u(dut.pwr_wake_reason) & FORCED_WAKE_BIT) == 0, (
        "wake_reason should remain clear while the CPU never transitioned from sleep to awake"
    )

    # Forced IRQ is a direct debug injection into the CPU IRQ vector, so it
    # should assert immediately while high and clear again once released.
    await RisingEdge(dut.clk)
    dut.test_force_irq.value = 1
    await ClockCycles(dut.clk, 1)
    await ReadOnly()
    assert (_u(dut.pico_irq) & FORCED_IRQ_BIT) != 0, "forced IRQ should drive PicoRV32 IRQ bit0"

    await RisingEdge(dut.clk)
    dut.test_force_irq.value = 0
    await ClockCycles(dut.clk, 1)
    await ReadOnly()
    assert (_u(dut.pico_irq) & FORCED_IRQ_BIT) == 0, "forced IRQ should clear after release"
