# SPDX-FileCopyrightText: © 2026 SensorSoC Authors
# SPDX-License-Identifier: Apache-2.0

"""Focused DFT smoke tests for chip_top test-mode pin behavior.

This module intentionally starts with the cheapest, least ambiguous checks:

- `00000`: normal mode keeps the debug bus disabled
- `01010`: force-IRQ mode drives the debug bus and reflects bidir[37]
- `01011`: force-wake mode drives the debug bus and reflects bidir[38]

These tests use the real chip-level pad wrapper so we exercise the actual
`input_PAD` and `bidir_PAD` pin interface that DFT bring-up will rely on.
"""

import cocotb
from cocotb.triggers import ClockCycles

from chip_top_tb import start_up


DEBUG_BUS_LO = 7
DEBUG_BUS_HI = 22
DEBUG_BUS_WIDTH = DEBUG_BUS_HI - DEBUG_BUS_LO + 1
DEBUG_BUS_MASK = (1 << DEBUG_BUS_WIDTH) - 1
FORCE_IRQ_PAD = 37
FORCE_WAKE_PAD = 38
EXTERNAL_CLOCK_PAD = 39
SPI_MISO_PAD = 4
I2C_SCL_PAD = 5


def _as_int(handle) -> int:
    return int(handle.value)


def read_debug_bus(dut) -> int:
    value = _as_int(dut.bidir_PAD)
    return (value >> DEBUG_BUS_LO) & DEBUG_BUS_MASK


def read_debug_oe(dut) -> int:
    return (read_bidir_oe(dut) >> DEBUG_BUS_LO) & DEBUG_BUS_MASK


def read_bidir_oe(dut) -> int:
    return _as_int(dut.bidir_CORE2PAD_OE)


def set_test_mode(dut, mode: int) -> None:
    # Only input_PAD[4:0] participate in test-mode selection.
    dut.input_PAD.value = mode & 0x1F


def drive_bidir_input(dut, index: int, value: int) -> None:
    current = _as_int(dut.bidir_PAD)
    if value:
        current |= (1 << index)
    else:
        current &= ~(1 << index)
    dut.bidir_PAD.value = current


def expect_oe_bit(dut, index: int, expected: int) -> None:
    got = (read_bidir_oe(dut) >> index) & 1
    assert got == expected, f"expected bidir[{index}] OE={expected}, got {got}"


def expect_static_non_debug_oe(dut) -> None:
    """Check pad directions that should not change when DFT debug is enabled."""
    for index in (0, 1, 2, 3):
        expect_oe_bit(dut, index, 1)

    for index in (SPI_MISO_PAD, I2C_SCL_PAD, FORCE_IRQ_PAD, FORCE_WAKE_PAD, EXTERNAL_CLOCK_PAD):
        expect_oe_bit(dut, index, 0)


def expect_debug_bus_oe(dut, expected: int) -> None:
    debug_oe = read_debug_oe(dut)
    assert debug_oe == expected, f"expected debug OE=0x{expected:04x}, got 0x{debug_oe:04x}"


@cocotb.test()
async def test_mode_00000_debug_bus_disabled(dut):
    """Normal mode should keep the 16-bit debug bus off/zero."""
    await start_up(dut)
    set_test_mode(dut, 0b00000)
    await ClockCycles(dut.clk_PAD, 5)

    debug_oe = read_debug_oe(dut)
    debug_bus = read_debug_bus(dut)

    assert debug_oe == 0, f"expected debug OE=0 in normal mode, got 0x{debug_oe:04x}"
    assert debug_bus == 0, f"expected debug bus=0 in normal mode, got 0x{debug_bus:04x}"
    expect_debug_bus_oe(dut, 0x0000)
    expect_static_non_debug_oe(dut)


@cocotb.test()
async def test_mode_01010_force_irq_reflects_pad(dut):
    """Force-IRQ mode should enable the debug bus and mirror bidir[37] in bit 15."""
    await start_up(dut)
    set_test_mode(dut, 0b01010)
    drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)

    debug_oe = read_debug_oe(dut)
    debug_bus = read_debug_bus(dut)
    assert debug_oe == 0xFFFF, f"expected debug OE fully enabled, got 0x{debug_oe:04x}"
    expect_debug_bus_oe(dut, 0xFFFF)
    expect_static_non_debug_oe(dut)
    assert ((debug_bus >> 15) & 1) == 0, f"expected force IRQ bit low, got debug bus 0x{debug_bus:04x}"

    drive_bidir_input(dut, FORCE_IRQ_PAD, 1)
    await ClockCycles(dut.clk_PAD, 2)
    debug_bus = read_debug_bus(dut)
    assert ((debug_bus >> 15) & 1) == 1, f"expected force IRQ bit high, got debug bus 0x{debug_bus:04x}"

    drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)
    debug_bus = read_debug_bus(dut)
    assert ((debug_bus >> 15) & 1) == 0, f"expected force IRQ bit to clear, got debug bus 0x{debug_bus:04x}"


@cocotb.test()
async def test_mode_01011_force_wake_reflects_pad(dut):
    """Force-wake mode should enable the debug bus and mirror bidir[38] in bit 15."""
    await start_up(dut)
    set_test_mode(dut, 0b01011)
    drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)

    debug_oe = read_debug_oe(dut)
    debug_bus = read_debug_bus(dut)
    assert debug_oe == 0xFFFF, f"expected debug OE fully enabled, got 0x{debug_oe:04x}"
    expect_debug_bus_oe(dut, 0xFFFF)
    expect_static_non_debug_oe(dut)
    assert ((debug_bus >> 15) & 1) == 0, f"expected force wake bit low, got debug bus 0x{debug_bus:04x}"
    assert (debug_bus & 0x0FFF) == 0, f"expected low 12 bits hardwired to 0, got 0x{debug_bus:04x}"

    drive_bidir_input(dut, FORCE_WAKE_PAD, 1)
    await ClockCycles(dut.clk_PAD, 2)
    debug_bus = read_debug_bus(dut)
    assert ((debug_bus >> 15) & 1) == 1, f"expected force wake bit high, got debug bus 0x{debug_bus:04x}"
    assert (debug_bus & 0x0FFF) == 0, f"expected low 12 bits hardwired to 0, got 0x{debug_bus:04x}"

    drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)
    debug_bus = read_debug_bus(dut)
    assert ((debug_bus >> 15) & 1) == 0, f"expected force wake bit to clear, got debug bus 0x{debug_bus:04x}"
