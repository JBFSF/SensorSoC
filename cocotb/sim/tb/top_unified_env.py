"""Shared cocotb helpers for the reusable unified-top environment wrapper.

Purpose
-------
This module provides the small set of helper routines that should be common
across cocotb tests built on top of:

    sim_top_unified_env.sv

The goal is to avoid repeating the same setup logic in every test:

    - start the shared clock
    - drive a clean reset pulse
    - clear test-force hooks before release

This is intentionally lightweight. It is not a giant framework layer. The idea
is to give future tests a stable foundation while we incrementally move
narrow and medium-sized unified-top checks into cocotb.

Why not put this logic in every test?
-------------------------------------
Because once the test count grows, duplicated reset/clock code becomes one of
the easiest ways for regressions to drift. Keeping the setup here makes the
first few shared-wrapper tests consistent:

    - reset/init smoke
    - future repeated production-loop smoke checks
"""

from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, NextTimeStep, ReadOnly, RisingEdge

FEATURE_BASE = 0x03004000
FEATURE_STATUS = FEATURE_BASE + 0x00
FEATURE_TIME = FEATURE_BASE + 0x04
FEATURE_MOTION = FEATURE_BASE + 0x08
FEATURE_DHR = FEATURE_BASE + 0x0C
FEATURE_RMSSD = FEATURE_BASE + 0x10

TEST_BASE = 0x0300F000
TEST_STATUS_ADDR = TEST_BASE + 0x00
TEST_CODE_ADDR = TEST_BASE + 0x04
ML_SCORE_ADDR = TEST_BASE + 0x20

WEIGHT_BASE = 0x03006000
X_BASE = WEIGHT_BASE + 64

SPI_BASE = 0x0300A000
SPI_DATA_ADDR = SPI_BASE + 0x08


async def start_clock(dut, period_ns: int = 20) -> None:
    """Start the wrapper clock unless a test already started it.

    Tests may import and call this helper freely without worrying about double-
    starting the same clock coroutine. The helper records a small marker on the
    DUT object after the first successful start.
    """
    if getattr(dut, "_unified_clock_started", False):
        return
    dut._unified_clock_started = True
    await Clock(dut.clk, period_ns, unit="ns").start()


async def apply_reset(dut, cycles: int = 20) -> None:
    """Drive a clean reset pulse for the shared unified-top environment.

    The wrapper includes always-on logic, sensor-side logic, and the CPU path,
    so the reset pulse is deliberately a little longer than a minimal one-shot.

    This helper also clears the wrapper's test-force hooks so a previous test's
    injected IRQ/wake state cannot leak into the next scenario.
    """
    await NextTimeStep()
    dut.reset.value = 1
    dut.test_force_irq.value = 0
    dut.test_force_wake.value = 0
    dut.test_irq_src.value = 0
    await ClockCycles(dut.clk, cycles)
    dut.reset.value = 0
    await ClockCycles(dut.clk, 2)


async def pulse_forced_wake(dut, cycles: int = 2) -> None:
    """Inject a short wake pulse through a wake-enabled test source.

    ``test_force_wake`` maps to IRQ bit 3, while the IRQ controller reset
    enables wake on bits 0..2. For runtime boot helpers, pulse
    ``test_irq_src[0]`` so the FSM sees a real ``irqc_wake_req`` and leaves
    sleep without requiring firmware to reprogram wake_en first.
    """
    await NextTimeStep()
    dut.test_irq_src.value = 0b001
    await ClockCycles(dut.clk, cycles)
    dut.test_irq_src.value = 0
    await ClockCycles(dut.clk, 2)


def _handle_nonzero(dut, name: str) -> bool:
    """Return True when an optional wrapper signal exists and is nonzero."""
    try:
        return int(getattr(dut, name).value) != 0
    except AttributeError:
        return False


def mmio_write_active(dut) -> bool:
    """True when PicoRV32 is completing an MMIO write in the current cycle."""
    return (
        int(dut.pico_mem_valid.value)
        and int(dut.pico_mem_ready.value)
        and int(dut.pico_mem_wstrb.value) != 0
        and ((int(dut.pico_mem_addr.value) >> 24) == 0x03)
    )


def mmio_read_active(dut) -> bool:
    """True when PicoRV32 is completing an MMIO read in the current cycle."""
    return (
        int(dut.pico_mem_valid.value)
        and int(dut.pico_mem_ready.value)
        and int(dut.pico_mem_wstrb.value) == 0
        and ((int(dut.pico_mem_addr.value) >> 24) == 0x03)
    )


async def wait_for_boot_load(dut, timeout_cycles: int = 200000) -> None:
    """Wait until the hardware boot paths complete and the CPU has been woken.

    The current architecture no longer uses deep WRAM probing as the bring-up
    checkpoint. Instead, the stable contracts are:

    - firmware boot controller asserted ``boot_done``
    - weight boot controller asserted ``weight_boot_done``
    - the shared-wrapper test hook can wake the system out of the reset-time
      sleep posture so the feature pipeline can run
    - in normal mode, CPU activity is expected only after the feature path
      advances far enough to transition the FSM into a CPU-enabled state
    """
    for _ in range(timeout_cycles):
        await RisingEdge(dut.clk)
        await ReadOnly()
        if int(dut.boot_done.value) != 0 and int(dut.weight_boot_done.value) != 0:
            break
    else:
        raise AssertionError("timed out waiting for boot_done and weight_boot_done")

    # Let the BOOT->IDLE->SLEEP handoff settle before deciding whether a wake
    # pulse is needed. In the current top-level architecture, `boot_done`
    # asserts first, then the FSM needs a cycle to enter its normal sleep
    # posture when `start_i` is high.
    for _ in range(8):
        await RisingEdge(dut.clk)
        await ReadOnly()

    if int(dut.pico_sleeping.value) != 0:
        await pulse_forced_wake(dut)

    for _ in range(timeout_cycles):
        await RisingEdge(dut.clk)
        await ReadOnly()
        if (
            int(dut.pico_sleeping.value) == 0 or
            int(dut.feat_valid.value) != 0 or
            _handle_nonzero(dut, "feat_latched_valid") or
            int(dut.pico_mem_valid.value) != 0 or
            int(dut.test_status.value) != 0 or
            int(dut.pico_cpu_clk_en.value) != 0
        ):
            return
    raise AssertionError("timed out waiting for post-wake feature/CPU activity after boot")


async def wait_for_coherent_score(dut, timeout_cycles: int = 600000) -> None:
    """Wait until firmware has completed at least one real inference iteration."""
    for _ in range(timeout_cycles):
        await RisingEdge(dut.clk)
        await ReadOnly()
        score = int(dut.ml_score_hw.value)
        code = int(dut.test_code.value)
        if score != 0 and (code & 0xFFFF) == (score & 0xFFFF):
            return
    raise AssertionError("timed out waiting for first coherent firmware score/logit update")
