# SPDX-FileCopyrightText: © 2026 SensorSoC Authors
# SPDX-License-Identifier: Apache-2.0

"""Focused DFT smoke tests for chip_core test-mode logic.

This is the cheapest reliable entry point for DFT verification because it
avoids depending on external GF180 IO pad models while still exercising the
real debug-bus and test-mode logic used by `chip_top`.
"""

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, Timer


DEBUG_BUS_LO = 7
DEBUG_BUS_HI = 22
DEBUG_BUS_MASK = (1 << (DEBUG_BUS_HI - DEBUG_BUS_LO + 1)) - 1
FORCE_IRQ_PAD = 37
FORCE_WAKE_PAD = 38


def _set_defaults(dut) -> None:
    dut.input_in.value = 0
    dut.bidir_in.value = 0
    dut.sim_ack_i.value = 0
    dut.sim_rdata_i.value = 0
    dut.sim_rvalid_i.value = 0
    dut.sim_rlast_i.value = 0
    dut.sim_err_i.value = 0
    dut.debug_stim_override_en_i.value = 0
    dut.debug_stim_mssd_i.value = 0
    dut.debug_stim_delta_hr_i.value = 0
    dut.debug_stim_time_i.value = 0
    dut.debug_stim_motion_i.value = 0
    dut.analog.value = 0


async def _start_up(dut) -> None:
    _set_defaults(dut)
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    dut.rst_n.value = 0
    await Timer(200, unit="ns")
    dut.rst_n.value = 1
    await ClockCycles(dut.clk, 5)


def _set_test_mode(dut, mode: int) -> None:
    dut.input_in.value = mode & 0x1F


def _drive_bidir_input(dut, index: int, value: int) -> None:
    current = int(dut.bidir_in.value)
    if value:
        current |= (1 << index)
    else:
        current &= ~(1 << index)
    dut.bidir_in.value = current


def _debug_bus(dut) -> int:
    return (int(dut.bidir_out.value) >> DEBUG_BUS_LO) & DEBUG_BUS_MASK


def _debug_oe(dut) -> int:
    return (int(dut.bidir_oe.value) >> DEBUG_BUS_LO) & DEBUG_BUS_MASK


def _debug_bit(dut, bit_index: int) -> int:
    value = dut.bidir_out.value
    return int(value[DEBUG_BUS_LO + bit_index])


@cocotb.test()
async def test_mode_00000_debug_bus_disabled(dut):
    """Normal mode should keep the debug bus disabled and drive zeros."""
    await _start_up(dut)
    _set_test_mode(dut, 0b00000)
    await ClockCycles(dut.clk, 2)

    assert _debug_oe(dut) == 0, f"expected debug OE=0, got 0x{_debug_oe(dut):04x}"
    assert _debug_bus(dut) == 0, f"expected debug bus=0, got 0x{_debug_bus(dut):04x}"


@cocotb.test()
async def test_mode_01010_force_irq_reflects_pad(dut):
    """Force-IRQ mode should enable the debug bus and mirror bidir_in[37] in bit 15."""
    await _start_up(dut)
    _set_test_mode(dut, 0b01010)
    await ClockCycles(dut.clk, 2)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert _debug_bit(dut, 15) == 0, "expected force IRQ summary bit low before forcing"

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 1)
    await ClockCycles(dut.clk, 2)
    assert _debug_bit(dut, 15) == 1, "expected force IRQ summary bit high when bidir_in[37] is high"

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert _debug_bit(dut, 15) == 0, "expected force IRQ summary bit to clear after releasing bidir_in[37]"


@cocotb.test()
async def test_mode_01011_force_wake_reflects_pad(dut):
    """Force-wake mode should enable the debug bus and mirror bidir_in[38] in bit 15."""
    await _start_up(dut)
    _set_test_mode(dut, 0b01011)
    await ClockCycles(dut.clk, 2)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert ((_debug_bus(dut) >> 15) & 1) == 0, f"expected force wake bit low, got 0x{_debug_bus(dut):04x}"
    assert (_debug_bus(dut) & 0x0FFF) == 0, f"expected low 12 bits zero, got 0x{_debug_bus(dut):04x}"

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 1)
    await ClockCycles(dut.clk, 2)
    assert ((_debug_bus(dut) >> 15) & 1) == 1, f"expected force wake bit high, got 0x{_debug_bus(dut):04x}"
    assert (_debug_bus(dut) & 0x0FFF) == 0, f"expected low 12 bits zero, got 0x{_debug_bus(dut):04x}"

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert ((_debug_bus(dut) >> 15) & 1) == 0, f"expected force wake bit cleared, got 0x{_debug_bus(dut):04x}"
