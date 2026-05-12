"""Runtime-oriented cocotb tests for the shared unified-top wrapper.

These tests sit one layer above the reset/init smoke test. They reuse the
shared wrapper and Python helpers to cover three high-value behaviors:

    1) repeated production-loop smoke behavior
    2) reset-adjacent forced wake / forced IRQ corner cases

The intent is not to replace the large production-style SystemVerilog bench.
Instead, these provide focused Python-side checks that are easier to extend and
debug while keeping the long SV bench as the final integrated guardrail.
"""

import cocotb
from cocotb.triggers import ClockCycles, ReadOnly, RisingEdge

from top_unified_env import (
    FEATURE_DHR,
    FEATURE_MOTION,
    FEATURE_RMSSD,
    FEATURE_STATUS,
    FEATURE_TIME,
    X_BASE,
    apply_reset,
    mmio_read_active,
    mmio_write_active,
    start_clock,
    wait_for_boot_load,
)


FEATURE_VALID_MASK = 1 << 0
FORCED_WAKE_BIT = 1 << 3
FORCED_IRQ_BIT = 1 << 0
TEST_FAIL = 0xDEADBEEF
ML_START_ADDR = 0x03003010


def _u(handle) -> int:
    return int(handle.value)


def _s16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


@cocotb.test()
async def test_repeated_production_loop_smoke(dut):
    """Check that the prod_main loop completes at least one coherent iteration.

    This is intentionally a smoke test, not a long soak. For current bring-up,
    one full feature-read -> feature-clear -> X-window write sequence is enough
    to prove the production loop is alive end-to-end in the shared wrapper.
    """
    cocotb.start_soon(start_clock(dut))
    await apply_reset(dut)
    await wait_for_boot_load(dut)

    feature_read_counts = {
        FEATURE_STATUS: 0,
        FEATURE_TIME: 0,
        FEATURE_MOTION: 0,
        FEATURE_DHR: 0,
        FEATURE_RMSSD: 0,
    }
    feature_clears = 0
    ml_start_writes = 0
    coherent_iterations = 0
    current_iter = None

    for _ in range(2_000_000):
        await RisingEdge(dut.clk)
        await ReadOnly()

        if _u(dut.pico_trap):
            raise AssertionError("CPU trap asserted during repeated production-loop smoke test")
        if _u(dut.test_status) == TEST_FAIL:
            raise AssertionError(f"firmware reported FAIL with code 0x{_u(dut.test_code):08x}")
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

            elif addr == ML_START_ADDR:
                ml_start_writes += 1

        if (
            feature_read_counts[FEATURE_STATUS] >= 1 and
            feature_read_counts[FEATURE_TIME] >= 1 and
            feature_read_counts[FEATURE_MOTION] >= 1 and
            feature_read_counts[FEATURE_DHR] >= 1 and
            feature_read_counts[FEATURE_RMSSD] >= 1 and
            feature_clears >= 1 and
            coherent_iterations >= 1 and
            ml_start_writes >= 1
        ):
            break
    else:
        raise AssertionError("timed out waiting for repeated coherent production-loop iterations")

    assert feature_read_counts[FEATURE_STATUS] >= 1, "too few FEATURE_STATUS reads"
    assert feature_read_counts[FEATURE_TIME] >= 1, "too few FEATURE_TIME reads"
    assert feature_read_counts[FEATURE_MOTION] >= 1, "too few FEATURE_MOTION reads"
    assert feature_read_counts[FEATURE_DHR] >= 1, "too few FEATURE_DHR reads"
    assert feature_read_counts[FEATURE_RMSSD] >= 1, "too few FEATURE_RMSSD reads"
    assert feature_clears >= 1, "too few FEATURE_STATUS valid clears"
    assert ml_start_writes >= 1, "too few ML start writes"
    assert coherent_iterations >= 1, "too few coherent feature->WRAM iterations"


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
