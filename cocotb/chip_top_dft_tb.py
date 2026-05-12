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
NUM_BIDIR_PADS = 40
FORCE_IRQ_PAD = 37
FORCE_WAKE_PAD = 38
EXTERNAL_CLOCK_PAD = 39
SPI_MISO_PAD = 4
I2C_SCL_PAD = 5


def _as_int(handle) -> int:
    return handle.value.to_unsigned()


def _bit_value(handle, index: int) -> str:
    return str(handle.value[index]).upper()


def _drive_bidir_pads(dut, driven_bits: dict[int, int]) -> None:
    bits = ["Z"] * NUM_BIDIR_PADS
    for index, value in driven_bits.items():
        bits[NUM_BIDIR_PADS - 1 - index] = "1" if value else "0"
    dut.bidir_PAD.value = "".join(bits)


def read_debug_bus(dut) -> int:
    value = 0
    for bit in range(DEBUG_BUS_WIDTH):
        pad_index = DEBUG_BUS_LO + bit
        value |= read_debug_bit(dut, bit) << bit
    return value


def read_debug_bit(dut, bit: int) -> int:
    pad_index = DEBUG_BUS_LO + bit
    bit_value = _bit_value(dut.bidir_PAD, pad_index)
    assert bit_value in {"0", "1"}, f"debug bus pad {pad_index} is {bit_value}, expected 0/1"
    return int(bit_value)


def expect_debug_low_12_zero(dut) -> None:
    for bit in range(12):
        got = read_debug_bit(dut, bit)
        assert got == 0, f"expected debug bit {bit} low, got {got}"


def read_debug_oe(dut) -> int:
    return (read_bidir_oe(dut) >> DEBUG_BUS_LO) & DEBUG_BUS_MASK


def read_bidir_oe(dut) -> int:
    return _as_int(dut.bidir_CORE2PAD_OE)


def set_test_mode(dut, mode: int) -> None:
    # Only input_PAD[4:0] participate in test-mode selection.
    dut.input_PAD.value = mode & 0x1F


def drive_bidir_input(dut, index: int, value: int) -> None:
    driven = getattr(dut, "_dft_bidir_driven_bits", {})
    driven[index] = 1 if value else 0
    dut._dft_bidir_driven_bits = driven
    _drive_bidir_pads(dut, driven)


def release_bidir_inputs(dut) -> None:
    dut._dft_bidir_driven_bits = {}
    _drive_bidir_pads(dut, {})


def expect_oe_bit(dut, index: int, expected: int) -> None:
    got = (read_bidir_oe(dut) >> index) & 1
    assert got == expected, f"expected bidir[{index}] OE={expected}, got {got}"


def expect_static_non_debug_oe(dut) -> None:
    """Check pad directions that should not change when DFT debug is enabled."""
    for index in (0, 1, 2, 3):
        expect_oe_bit(dut, index, 1)

    expect_oe_bit(dut, I2C_SCL_PAD, 1)

    for index in (SPI_MISO_PAD, FORCE_IRQ_PAD, FORCE_WAKE_PAD, EXTERNAL_CLOCK_PAD):
        expect_oe_bit(dut, index, 0)


def expect_debug_bus_oe(dut, expected: int) -> None:
    debug_oe = read_debug_oe(dut)
    assert debug_oe == expected, f"expected debug OE=0x{expected:04x}, got 0x{debug_oe:04x}"


@cocotb.test()
async def test_mode_00000_debug_bus_disabled(dut):
    """Normal mode should keep the 16-bit debug bus off/zero."""
    await start_up(dut)
    release_bidir_inputs(dut)
    set_test_mode(dut, 0b00000)
    await ClockCycles(dut.clk_PAD, 5)

    debug_oe = read_debug_oe(dut)

    assert debug_oe == 0, f"expected debug OE=0 in normal mode, got 0x{debug_oe:04x}"
    expect_debug_bus_oe(dut, 0x0000)
    expect_static_non_debug_oe(dut)


@cocotb.test()
async def test_mode_01010_force_irq_reflects_pad(dut):
    """Force-IRQ mode should enable the debug bus and mirror bidir[37] in bit 15."""
    await start_up(dut)
    release_bidir_inputs(dut)
    set_test_mode(dut, 0b01010)
    drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)

    debug_oe = read_debug_oe(dut)
    assert debug_oe == 0xFFFF, f"expected debug OE fully enabled, got 0x{debug_oe:04x}"
    expect_debug_bus_oe(dut, 0xFFFF)
    expect_static_non_debug_oe(dut)
    assert read_debug_bit(dut, 15) == 0, "expected force IRQ bit low"

    drive_bidir_input(dut, FORCE_IRQ_PAD, 1)
    await ClockCycles(dut.clk_PAD, 2)
    assert read_debug_bit(dut, 15) == 1, "expected force IRQ bit high"

    drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)
    assert read_debug_bit(dut, 15) == 0, "expected force IRQ bit to clear"


@cocotb.test()
async def test_mode_01011_force_wake_reflects_pad(dut):
    """Force-wake mode should enable the debug bus and mirror bidir[38] in bit 15."""
    await start_up(dut)
    release_bidir_inputs(dut)
    set_test_mode(dut, 0b01011)
    drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)

    debug_oe = read_debug_oe(dut)
    assert debug_oe == 0xFFFF, f"expected debug OE fully enabled, got 0x{debug_oe:04x}"
    expect_debug_bus_oe(dut, 0xFFFF)
    expect_static_non_debug_oe(dut)
    assert read_debug_bit(dut, 15) == 0, "expected force wake bit low"
    expect_debug_low_12_zero(dut)

    drive_bidir_input(dut, FORCE_WAKE_PAD, 1)
    await ClockCycles(dut.clk_PAD, 2)
    assert read_debug_bit(dut, 15) == 1, "expected force wake bit high"
    expect_debug_low_12_zero(dut)

    drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk_PAD, 2)
    assert read_debug_bit(dut, 15) == 0, "expected force wake bit to clear"
