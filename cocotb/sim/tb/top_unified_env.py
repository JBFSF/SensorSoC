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
    - future host-I2C checks
    - future repeated production-loop smoke checks
"""

from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, NextTimeStep, ReadOnly, RisingEdge, Timer


HOST_I2C_ADDR = 0x42

HOST_WHOAMI = 0x00
HOST_VERSION = 0x01
HOST_IRQ_COUNT_L = 0x05
HOST_IRQ_COUNT_H = 0x06
HOST_CONF_THR_L = 0x30
HOST_CONF_THR_H = 0x31
HOST_CONF_CTRL = 0x32
HOST_CONF_STAT = 0x33
HOST_LOGIT0_L = 0x34
HOST_LOGIT0_H = 0x35
HOST_CONF_ABS_L = 0x38
HOST_CONF_ABS_H = 0x39

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
    await ClockCycles(dut.clk, cycles)
    dut.reset.value = 0
    await ClockCycles(dut.clk, 2)


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
    """Wait until firmware has copied the first flash words into WRAM.

    The production firmware first streams the taketwo parameter image from the
    SPI flash model into WRAM. A simple and stable "boot complete" checkpoint is
    to wait until the leading WRAM words match the leading flash words.
    """
    for _ in range(timeout_cycles):
        await RisingEdge(dut.clk)
        await ReadOnly()
        if (
            int(dut.u_dut.u_weight_ram.mem[32].value) == int(dut.u_flash.mem[0].value)
            and int(dut.u_dut.u_weight_ram.mem[33].value) == int(dut.u_flash.mem[1].value)
            and int(dut.u_dut.u_weight_ram.mem[34].value) == int(dut.u_flash.mem[2].value)
            and int(dut.u_dut.u_weight_ram.mem[35].value) == int(dut.u_flash.mem[3].value)
        ):
            return
    raise AssertionError("timed out waiting for firmware SPI boot load into WRAM")


async def wait_for_coherent_score(dut, timeout_cycles: int = 600000) -> None:
    """Wait until firmware has completed at least one real inference iteration."""
    for _ in range(timeout_cycles):
        await RisingEdge(dut.clk)
        await ReadOnly()
        score = int(dut.ml_score_hw.value)
        code = int(dut.test_code.value)
        logit_word = int(dut.u_dut.u_weight_ram.mem[1376].value)
        if score != 0 and (code & 0xFFFF) == (score & 0xFFFF) and logit_word != 0xA5A55A5A:
            return
    raise AssertionError("timed out waiting for first coherent firmware score/logit update")


async def i2c_tick(step_ns: int = 120) -> None:
    """Mirror the timing used by the existing SV production-style bench."""
    await Timer(step_ns, unit="ns")


async def i2c_start(dut) -> None:
    await NextTimeStep()
    dut.host_sda_drv_low.value = 0
    dut.host_scl_drv.value = 1
    await i2c_tick()
    dut.host_sda_drv_low.value = 1
    await i2c_tick()
    dut.host_scl_drv.value = 0
    await i2c_tick()


async def i2c_stop(dut) -> None:
    await NextTimeStep()
    dut.host_sda_drv_low.value = 1
    dut.host_scl_drv.value = 0
    await i2c_tick()
    dut.host_scl_drv.value = 1
    await i2c_tick()
    dut.host_sda_drv_low.value = 0
    await i2c_tick()


async def i2c_write_bit(dut, bitval: int) -> None:
    await NextTimeStep()
    dut.host_scl_drv.value = 0
    dut.host_sda_drv_low.value = 0 if bitval else 1
    await i2c_tick()
    dut.host_scl_drv.value = 1
    await i2c_tick()
    dut.host_scl_drv.value = 0
    await i2c_tick()


async def i2c_read_bit(dut) -> int:
    await NextTimeStep()
    dut.host_scl_drv.value = 0
    dut.host_sda_drv_low.value = 0
    await i2c_tick()
    dut.host_scl_drv.value = 1
    await i2c_tick()
    bitval = int(dut.host_i2c_sda.value)
    dut.host_scl_drv.value = 0
    await i2c_tick()
    return bitval


async def i2c_write_byte(dut, value: int) -> bool:
    for shift in range(7, -1, -1):
        await i2c_write_bit(dut, (value >> shift) & 0x1)
    ack_bit = await i2c_read_bit(dut)
    return ack_bit == 0


async def i2c_read_byte(dut, ack_from_master: bool) -> int:
    value = 0
    for shift in range(7, -1, -1):
        bitval = await i2c_read_bit(dut)
        value |= (bitval & 0x1) << shift
    await i2c_write_bit(dut, 1 if ack_from_master else 0)
    return value


async def i2c_write_reg(dut, reg_addr: int, reg_data: int) -> None:
    await i2c_start(dut)
    assert await i2c_write_byte(dut, (HOST_I2C_ADDR << 1) | 0), "no ACK on host write address"
    assert await i2c_write_byte(dut, reg_addr & 0xFF), "no ACK on host register pointer"
    assert await i2c_write_byte(dut, reg_data & 0xFF), "no ACK on host register data"
    await i2c_stop(dut)


async def i2c_read_reg(dut, reg_addr: int) -> int:
    await i2c_start(dut)
    assert await i2c_write_byte(dut, (HOST_I2C_ADDR << 1) | 0), "no ACK on host write address before read"
    assert await i2c_write_byte(dut, reg_addr & 0xFF), "no ACK on host register pointer before read"
    await i2c_start(dut)
    assert await i2c_write_byte(dut, (HOST_I2C_ADDR << 1) | 1), "no ACK on host read address"
    value = await i2c_read_byte(dut, ack_from_master=True)
    await i2c_stop(dut)
    return value


async def i2c_read_reg16_stable(dut, reg_addr_lo: int, reg_addr_hi: int) -> int:
    """Mirror the stable two-read strategy used by the long SV production bench."""
    lo0 = await i2c_read_reg(dut, reg_addr_lo)
    hi0 = await i2c_read_reg(dut, reg_addr_hi)
    lo1 = await i2c_read_reg(dut, reg_addr_lo)
    hi1 = await i2c_read_reg(dut, reg_addr_hi)
    if lo0 == lo1 and hi0 == hi1:
        return (hi0 << 8) | lo0
    return (hi1 << 8) | lo1
