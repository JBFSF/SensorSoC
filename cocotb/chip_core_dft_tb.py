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
    """Drive the harness into a quiet baseline state.

    These smoke tests are intentionally narrow: we are checking DFT muxing and
    mode posture, not full sensor/firmware behavior. Keep the simulated sensor
    side idle and clear all debug-stim hooks unless a test explicitly enables
    them.
    """
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
    """Common reset/clock sequence for chip_core-only DFT checks."""
    _set_defaults(dut)
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    dut.rst_n.value = 0
    await Timer(200, unit="ns")
    dut.rst_n.value = 1
    await ClockCycles(dut.clk, 5)


def _set_test_mode(dut, mode: int) -> None:
    """Drive the 5-bit test-mode selector on input pads."""
    dut.input_in.value = mode & 0x1F


def _drive_bidir_input(dut, index: int, value: int) -> None:
    """Convenience helper for toggling one bidir input without disturbing others."""
    current = int(dut.bidir_in.value)
    if value:
        current |= (1 << index)
    else:
        current &= ~(1 << index)
    dut.bidir_in.value = current


def _debug_bus(dut) -> int:
    """Return the 16-bit debug-bus payload exposed on bidir[22:7]."""
    return (int(dut.bidir_out.value) >> DEBUG_BUS_LO) & DEBUG_BUS_MASK


def _debug_oe(dut) -> int:
    """Return the 16-bit debug-bus output-enable mask for bidir[22:7]."""
    return (int(dut.bidir_oe.value) >> DEBUG_BUS_LO) & DEBUG_BUS_MASK


def _debug_bit(dut, bit_index: int) -> int:
    value = dut.bidir_out.value
    return int(value[DEBUG_BUS_LO + bit_index])


def _u16(value: int) -> int:
    """Normalize Python ints to the unsigned 16-bit bus representation."""
    return value & 0xFFFF


def _assert_mode_enables(dut, *, feat_en: int, ml_en: int, cpu_en: int, sleeping: int) -> None:
    """Check the high-level posture that top_fsm should force for a mode.

    This keeps the DFT tests honest: a mode is only "working" if the debug bus
    is correct *and* the expected subsystem enable state is present.
    """
    assert int(dut.u_top.feat_en.value) == feat_en, (
        f"expected feat_en={feat_en}, got {int(dut.u_top.feat_en.value)}"
    )
    assert int(dut.u_top.ml_en.value) == ml_en, (
        f"expected ml_en={ml_en}, got {int(dut.u_top.ml_en.value)}"
    )
    assert int(dut.u_top.cpu_clk_en.value) == cpu_en, (
        f"expected cpu_clk_en={cpu_en}, got {int(dut.u_top.cpu_clk_en.value)}"
    )
    assert int(dut.u_top.sleeping_r.value) == sleeping, (
        f"expected sleeping_r={sleeping}, got {int(dut.u_top.sleeping_r.value)}"
    )


async def _assert_feature_view_mode(
    dut,
    *,
    mode: int,
    field_name: str,
    drive_attr: str,
    sample_value: int,
) -> None:
    """Check the feature-view modes using the explicit debug-stim override path.

    This is the cheapest exact-value check for 00001/00010/00011/00100 because
    it validates the chip_core debug mux directly before depending on the live
    sensor pipeline.
    """
    _set_test_mode(dut, mode)
    dut.debug_stim_override_en_i.value = 1
    getattr(dut, drive_attr).value = _u16(sample_value)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    assert _debug_bus(dut) == _u16(sample_value), (
        f"expected {field_name}=0x{_u16(sample_value):04x} on debug bus, "
        f"got 0x{_debug_bus(dut):04x}"
    )
    _assert_mode_enables(dut, feat_en=1, ml_en=0, cpu_en=0, sleeping=0)


@cocotb.test()
async def test_mode_00000_debug_bus_disabled(dut):
    """Normal mode should keep the debug bus disabled and drive zeros."""
    await _start_up(dut)
    _set_test_mode(dut, 0b00000)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0, f"expected debug OE=0, got 0x{_debug_oe(dut):04x}"
    assert _debug_bus(dut) == 0, f"expected debug bus=0, got 0x{_debug_bus(dut):04x}"
    # In this harness the top-level FSM is still in early boot-time posture, so
    # keep the normal-mode check lightweight: we only require that DFT does not
    # force the feature or CPU domains on.
    assert int(dut.u_top.feat_en.value) == 0, "normal mode should not force feature domain on"
    assert int(dut.u_top.cpu_clk_en.value) == 0, "normal mode should not force CPU clock on in this harness"


@cocotb.test()
async def test_mode_00001_mssd_feature_view(dut):
    """MSSD feature mode should drive the debug bus from the MSSD feature path."""
    await _start_up(dut)
    await _assert_feature_view_mode(
        dut,
        mode=0b00001,
        field_name="mssd",
        drive_attr="debug_stim_mssd_i",
        sample_value=-1234,
    )


@cocotb.test()
async def test_mode_00010_delta_hr_feature_view(dut):
    """Delta-HR feature mode should drive the debug bus from the delta-HR path."""
    await _start_up(dut)
    await _assert_feature_view_mode(
        dut,
        mode=0b00010,
        field_name="delta_hr",
        drive_attr="debug_stim_delta_hr_i",
        sample_value=0x1234,
    )


@cocotb.test()
async def test_mode_00011_time_feature_view(dut):
    """Time feature mode should drive the debug bus from the time feature path."""
    await _start_up(dut)
    await _assert_feature_view_mode(
        dut,
        mode=0b00011,
        field_name="time",
        drive_attr="debug_stim_time_i",
        sample_value=0x00C7,
    )


@cocotb.test()
async def test_mode_00100_motion_feature_view(dut):
    """Motion feature mode should drive the debug bus from the motion feature path."""
    await _start_up(dut)
    await _assert_feature_view_mode(
        dut,
        mode=0b00100,
        field_name="motion",
        drive_attr="debug_stim_motion_i",
        sample_value=-2,
    )


@cocotb.test()
async def test_mode_01010_force_irq_reflects_pad(dut):
    """Force-IRQ mode should enable the debug bus and mirror bidir_in[37] in bit 15."""
    await _start_up(dut)
    _set_test_mode(dut, 0b01010)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

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
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

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
