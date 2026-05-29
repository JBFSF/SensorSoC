# SPDX-FileCopyrightText: © 2026 SensorSoC Authors
# SPDX-License-Identifier: Apache-2.0

"""Focused DFT smoke tests for chip_core test-mode logic.

This is the cheapest reliable entry point for DFT verification because it
avoids depending on external GF180 IO pad models while still exercising the
real debug-bus and test-mode logic used by `chip_top`.
"""

import cocotb
from cocotb.clock import Clock
from cocotb.handle import Force, Release
from cocotb.triggers import ClockCycles, RisingEdge, Timer


DEBUG_BUS_LO = 7
DEBUG_BUS_HI = 22
DEBUG_BUS_MASK = (1 << (DEBUG_BUS_HI - DEBUG_BUS_LO + 1)) - 1
FORCE_IRQ_PAD = 37
FORCE_WAKE_PAD = 38
TIMER_CTRL_ADDR = 0x0300_2000
SRAM_DATA_ADDR = 0x0000_0040

# Tiny RV32I program used to provoke one real Pico MMIO store in the cheap
# chip_core harness:
#   lui  x1, 0x03002      ; x1 = 0x0300_2000 (timer MMIO base)
#   addi x2, x0, 3        ; x2 = 0x0000_0003
#   sw   x2, 0(x1)        ; write TIMER_CTRL = 3
#   jal  x0, 0            ; spin forever
#
# This lets mode 01000 observe an actual CPU-issued write even though the bare
# chip_core DFT harness does not have a boot-flash model attached.
PICO_TIMER_WRITE_PROGRAM = (
    0x030020B7,
    0x00300113,
    0x0020A023,
    0x0000006F,
)

# Tiny RV32I program that enables the DFT wake source, then requests sleep
# through the real IRQC and pwrctrl MMIO paths:
#   lui  x1, 0x03005      ; x1 = 0x0300_5000 (IRQC base)
#   addi x2, x0, 15       ; x2 = wake_en bits [3:0]
#   sw   x2, 8(x1)        ; write IRQC_WAKE_EN = 0x0000_000f
#   lui  x1, 0x03001      ; x1 = 0x0300_1000 (PWR_CTRL)
#   addi x2, x0, 1        ; x2 = 0x0000_0001
#   sw   x2, 0(x1)        ; write PWR_CTRL.sleep_req = 1
#   jal  x0, 0            ; spin forever
PICO_SLEEP_REQUEST_PROGRAM = (
    0x030050B7,
    0x00F00113,
    0x0020A423,
    0x030010B7,
    0x00100113,
    0x0020A023,
    0x0000006F,
)

# Tiny RV32I program for richer Pico-state visibility:
#   addi x1, x0, 64       ; x1 = SRAM data address 0x40
#   lw   x2, 0(x1)        ; real SRAM load
#   sw   x2, 4(x1)        ; real SRAM store
#   lui  x3, 0x03002      ; x3 = 0x0300_2000 (timer MMIO base)
#   sw   x2, 0(x3)        ; real MMIO store
#   jal  x0, 0            ; spin forever
#
# Preload word 16 in SRAM with a known value so the load path has real data.
PICO_STATE_VISIBILITY_PROGRAM = (
    0x04000093,
    0x0000A103,
    0x0020A223,
    0x030021B7,
    0x0021A023,
    0x0000006F,
)
PICO_STATE_VISIBILITY_DATA = {
    16: 0x12345678,  # byte address 0x40
}


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
    dut.test_irq_src_i.value = 0
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


def _preload_sram_words(dut, words) -> None:
    """Write a small program directly into top.sram before releasing reset."""
    for index, word in enumerate(words):
        dut.u_top.sram.mem[index].value = word & 0xFFFF_FFFF


def _preload_sram_map(dut, word_map) -> None:
    """Write sparse data words into top.sram before releasing reset."""
    for index, word in word_map.items():
        dut.u_top.sram.mem[index].value = word & 0xFFFF_FFFF


async def _start_up_with_preloaded_program(dut, words) -> None:
    """Bring up chip_core with a tiny SRAM-resident Pico program.

    The bare chip_core harness ties the boot-flash input high internally, so
    there is no real firmware source. For CPU-summary DFT modes we can still
    exercise genuine Pico bus activity by preloading SRAM and forcing boot_done
    high before reset release.
    """
    _set_defaults(dut)
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    dut.rst_n.value = 0
    _preload_sram_words(dut, words)
    dut.u_top.boot_done.value = Force(1)
    await Timer(200, unit="ns")
    dut.rst_n.value = 1
    await ClockCycles(dut.clk, 5)


async def _start_up_with_preloaded_program_and_data(dut, words, word_map) -> None:
    """Bring up chip_core with a tiny Pico program plus sparse SRAM data."""
    _set_defaults(dut)
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    dut.rst_n.value = 0
    _preload_sram_words(dut, words)
    _preload_sram_map(dut, word_map)
    dut.u_top.boot_done.value = Force(1)
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


def _debug_bus_str(dut) -> str:
    """Return the debug bus as a 16-bit MSB->LSB string, preserving X/Z."""
    return str(dut.bidir_out.value[DEBUG_BUS_HI:DEBUG_BUS_LO]).upper()


def _bit_str(signal) -> str:
    """Return a single-bit cocotb value as `0/1/X/Z`."""
    return str(signal.value).upper()


def _bits_str(signal) -> str:
    """Return a vector cocotb value as an MSB->LSB `0/1/X/Z` string."""
    return str(signal.value).upper()


def _pack_pico_state_summary_str(dut) -> str:
    """Mirror chip_core mode 00111 exactly as a 16-bit bitstring.

    Layout:
      [15] trap
      [14] cpu_clk_en
      [13] mem_valid
      [12] mem_instr
      [11] mem_ready
      [10:7] mem_wstrb
      [6:0] mem_addr[6:0]
    """
    return (
        _bit_str(dut.u_top.pico_trap_o)
        + _bit_str(dut.u_top.pico_cpu_clk_en_o)
        + _bit_str(dut.u_top.pico_mem_valid_o)
        + _bit_str(dut.u_top.pico_mem_instr_o)
        + _bit_str(dut.u_top.pico_mem_ready_o)
        + _bits_str(dut.u_top.pico_mem_wstrb_o)
        + str(dut.u_top.pico_mem_addr_o.value[6:0]).upper()
    )


def _pack_pico_mmio_write_summary_str(dut) -> str:
    """Mirror chip_core mode 01000 exactly as a 16-bit bitstring.

    Layout:
      [15] mem_valid && any byte strobe
      [14] trap
      [13] any byte strobe
      [12] full-word write
      [11:4] mem_addr[7:0]
      [3:0] mem_wdata[3:0]
    """
    mem_valid = _bit_str(dut.u_top.pico_mem_valid_o)
    wstrb = _bits_str(dut.u_top.pico_mem_wstrb_o)
    any_wstrb = "1" if "1" in wstrb else ("0" if "x" not in wstrb.lower() and "z" not in wstrb.lower() else "X")
    full_wstrb = "1" if wstrb == "1111" else ("0" if "x" not in wstrb.lower() and "z" not in wstrb.lower() else "X")
    write_qual = "1" if (mem_valid == "1" and any_wstrb == "1") else ("0" if mem_valid == "0" or any_wstrb == "0" else "X")
    return (
        write_qual
        + _bit_str(dut.u_top.pico_trap_o)
        + any_wstrb
        + full_wstrb
        + str(dut.u_top.pico_mem_addr_o.value[7:0]).upper()
        + str(dut.u_top.pico_mem_wdata_o.value[3:0]).upper()
    )


def _pack_pico_sleep_irq_summary_str(dut) -> str:
    """Mirror chip_core mode 01001 exactly as a 16-bit bitstring.

    Layout:
      [15] trap
      [14] top/FSM sleeping state
      [13] CPU clock enable
      [12] any Pico IRQ
      [11:0] zero
    """
    irq_bits = _bits_str(dut.u_top.pico_irq_o)
    irq_any = "1" if "1" in irq_bits else ("X" if any(bit in irq_bits for bit in "XZ") else "0")
    return (
        _bit_str(dut.u_top.pico_trap_o)
        + _bit_str(dut.u_top.pico_sleeping_o)
        + _bit_str(dut.u_top.pico_cpu_clk_en_o)
        + irq_any
        + "0" * 12
    )


def _pack_force_irq_summary_str(dut) -> str:
    """Mirror chip_core mode 01010 exactly as a 16-bit bitstring.

    Layout:
      [15] DFT force-IRQ pad
      [14] trap
      [13] CPU clock enable
      [12] instruction access
      [11] memory valid
      [10] memory ready
      [9:0] mem_addr[9:0]
    """
    return (
        str(dut.bidir_in.value[FORCE_IRQ_PAD]).upper()
        + _bit_str(dut.u_top.pico_trap_o)
        + _bit_str(dut.u_top.pico_cpu_clk_en_o)
        + _bit_str(dut.u_top.pico_mem_instr_o)
        + _bit_str(dut.u_top.pico_mem_valid_o)
        + _bit_str(dut.u_top.pico_mem_ready_o)
        + str(dut.u_top.pico_mem_addr_o.value[9:0]).upper()
    )


def _pack_force_wake_summary_str(dut) -> str:
    """Mirror chip_core mode 01011 exactly as a 16-bit bitstring.

    Layout:
      [15] DFT force-wake pad
      [14] reserved, tied low
      [13] ML IRQ
      [12] timer event
      [11:0] zero
    """
    return (
        str(dut.bidir_in.value[FORCE_WAKE_PAD]).upper()
        + "0"
        + _bit_str(dut.u_top.ml_irq_o)
        + _bit_str(dut.u_top.timer_event_o)
        + "0" * 12
    )


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


def _assert_sleep_irq_summary(dut, *, trap: str, sleeping: str, cpu_clk_en: str, irq: str) -> None:
    expected = trap + sleeping + cpu_clk_en + irq + "0" * 12
    packed = _pack_pico_sleep_irq_summary_str(dut)
    got = _debug_bus_str(dut)
    assert got == expected, f"mode 01001 summary mismatch: expected {expected}, got {got}"
    assert got == packed, f"mode 01001 did not mirror internal signals: expected {packed}, got {got}"


async def _wait_for_pico_sleeping(dut, timeout_cycles: int = 200) -> None:
    for _ in range(timeout_cycles):
        await RisingEdge(dut.clk)
        if int(dut.u_top.pico_sleeping_o.value) == 1:
            return
    raise AssertionError(
        "timed out waiting for Pico sleep state: "
        f"state_q={dut.u_top.fsm.state_q.value}, "
        f"sleep_req={dut.u_top.sleep_req.value}, "
        f"cpu_idle_seen={dut.u_top.fsm.cpu_idle_seen_r.value}, "
        f"cpu_clk_en={dut.u_top.cpu_clk_en.value}, "
        f"cpu_clk_en_lat={dut.u_top.cpu_clk_en_lat.value}, "
        f"mem_valid={dut.u_top.mem_valid.value}, "
        f"mem_addr={dut.u_top.mem_addr.value}, "
        f"mem_wstrb={dut.u_top.mem_wstrb.value}, "
        f"mem_wdata={dut.u_top.mem_wdata.value}, "
        f"pwr_ready={dut.u_top.pwr_ready.value}, "
        f"trap={dut.u_top.trap.value}"
    )


async def _wait_for_pico_awake(dut, timeout_cycles: int = 50) -> None:
    for _ in range(timeout_cycles):
        await RisingEdge(dut.clk)
        if int(dut.u_top.pico_sleeping_o.value) == 0:
            return
    raise AssertionError(
        "timed out waiting for Pico wake state: "
        f"state_q={dut.u_top.fsm.state_q.value}, "
        f"irq_sources={dut.u_top.irq_sources.value}, "
        f"irqc_wake_req={dut.u_top.irqc_wake_req.value}, "
        f"wake_en={dut.u_top.u_irqc.wake_en.value}, "
        f"pending={dut.u_top.u_irqc.pending.value}, "
        f"force_wake={dut.u_top.test_force_wake_i.value}, "
        f"sleeping={dut.u_top.pico_sleeping_o.value}"
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
    """Force-IRQ mode should expose force IRQ plus live Pico bus activity.

    This strengthens the original bit-only smoke check: the test now compares
    the whole 01010 packed summary every cycle while a tiny SRAM program causes
    real instruction fetch, load, store, and MMIO-store traffic.
    """
    await _start_up_with_preloaded_program_and_data(
        dut,
        PICO_STATE_VISIBILITY_PROGRAM,
        PICO_STATE_VISIBILITY_DATA,
    )
    _set_test_mode(dut, 0b01010)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert _debug_bus_str(dut) == _pack_force_irq_summary_str(dut), (
        f"force IRQ summary mismatch: expected {_pack_force_irq_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 15) == 0, "expected force IRQ bit low before forcing"

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 1)
    await ClockCycles(dut.clk, 2)
    assert _debug_bus_str(dut) == _pack_force_irq_summary_str(dut), (
        f"force IRQ summary mismatch after forcing IRQ: expected {_pack_force_irq_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 15) == 1, "expected force IRQ bit high when bidir_in[37] is high"
    assert (int(dut.u_top.pico_irq_o.value) & 1) == 1, "expected force IRQ to reach Pico IRQ bit 0"

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert _debug_bus_str(dut) == _pack_force_irq_summary_str(dut), (
        f"force IRQ summary mismatch after releasing IRQ: expected {_pack_force_irq_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 15) == 0, "expected force IRQ bit to clear after releasing bidir_in[37]"

    saw_instr_fetch = False
    saw_mem_valid = False
    saw_mem_ready = False
    saw_sram_data_access = False
    saw_timer_mmio_store = False

    for _ in range(200):
        await RisingEdge(dut.clk)
        expected = _pack_force_irq_summary_str(dut)
        got = _debug_bus_str(dut)
        assert got == expected, (
            f"force IRQ summary mismatch during Pico execution: expected {expected}, got {got}"
        )

        mem_valid = int(dut.u_top.pico_mem_valid_o.value)
        mem_instr = int(dut.u_top.pico_mem_instr_o.value)
        mem_ready = int(dut.u_top.pico_mem_ready_o.value)
        wstrb = int(dut.u_top.pico_mem_wstrb_o.value)
        addr = int(dut.u_top.pico_mem_addr_o.value)

        saw_instr_fetch |= bool(mem_valid and mem_instr)
        saw_mem_valid |= bool(mem_valid)
        saw_mem_ready |= bool(mem_valid and mem_ready)
        if mem_valid and not mem_instr and mem_ready and addr in (SRAM_DATA_ADDR, SRAM_DATA_ADDR + 4):
            saw_sram_data_access = True
        if mem_valid and not mem_instr and mem_ready and wstrb != 0 and addr == TIMER_CTRL_ADDR:
            saw_timer_mmio_store = True

    assert int(dut.u_top.pico_trap_o.value) == 0, "unexpected Pico trap during force-IRQ summary test"
    assert saw_instr_fetch, "expected mode 01010 to expose at least one Pico instruction fetch"
    assert saw_mem_valid, "expected mode 01010 to expose Pico mem_valid activity"
    assert saw_mem_ready, "expected mode 01010 to expose Pico mem_ready activity"
    assert saw_sram_data_access, "expected mode 01010 to expose SRAM data access address bits"
    assert saw_timer_mmio_store, f"expected mode 01010 to expose MMIO store to 0x{TIMER_CTRL_ADDR:08x}"


@cocotb.test()
async def test_mode_00111_pico_state_summary_matches_internal_signals(dut):
    """Pico state summary mode should mirror the packed CPU-state view."""
    await _start_up(dut)
    _set_test_mode(dut, 0b00111)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

    for _ in range(32):
        await RisingEdge(dut.clk)
        expected = _pack_pico_state_summary_str(dut)
        got = _debug_bus_str(dut)
        assert got == expected, (
            f"pico state summary mismatch: expected {expected}, got {got}"
        )


@cocotb.test()
async def test_mode_00111_pico_state_summary_shows_real_cpu_execution(dut):
    """Pico state summary mode should reflect real fetch/load/store activity.

    This complements the cheap structural summary check with a tiny SRAM-
    preloaded Pico program so we can see instruction fetches plus real data-side
    accesses from the CPU itself.
    """
    await _start_up_with_preloaded_program_and_data(
        dut,
        PICO_STATE_VISIBILITY_PROGRAM,
        PICO_STATE_VISIBILITY_DATA,
    )
    _set_test_mode(dut, 0b00111)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

    saw_instr_fetch = False
    saw_data_load = False
    saw_data_store = False
    saw_mmio_store = False

    for _ in range(200):
        await RisingEdge(dut.clk)
        expected = _pack_pico_state_summary_str(dut)
        got = _debug_bus_str(dut)
        assert got == expected, (
            f"pico state summary mismatch during execution: expected {expected}, got {got}"
        )

        mem_valid = int(dut.u_top.pico_mem_valid_o.value)
        mem_instr = int(dut.u_top.pico_mem_instr_o.value)
        mem_ready = int(dut.u_top.pico_mem_ready_o.value)
        wstrb = int(dut.u_top.pico_mem_wstrb_o.value)
        addr = int(dut.u_top.pico_mem_addr_o.value)

        if mem_valid and mem_instr:
            saw_instr_fetch = True
        if mem_valid and not mem_instr and mem_ready and wstrb == 0:
            saw_data_load = True
            assert addr == SRAM_DATA_ADDR, (
                f"expected Pico SRAM load from 0x{SRAM_DATA_ADDR:08x}, got 0x{addr:08x}"
            )
        if mem_valid and not mem_instr and mem_ready and wstrb != 0:
            saw_data_store = True
            if addr == TIMER_CTRL_ADDR:
                saw_mmio_store = True

    assert int(dut.u_top.pico_trap_o.value) == 0, "unexpected Pico trap during execution-visibility test"
    assert saw_instr_fetch, "expected to observe at least one Pico instruction fetch"
    assert saw_data_load, "expected to observe at least one real Pico SRAM load"
    assert saw_data_store, "expected to observe at least one real Pico store"
    assert saw_mmio_store, f"expected to observe Pico MMIO store to 0x{TIMER_CTRL_ADDR:08x}"


@cocotb.test()
async def test_mode_01000_pico_mmio_write_summary_matches_internal_signals(dut):
    """Pico MMIO write-summary mode should show a real Pico MMIO store.

    This test still checks the exact debug-bus packing every cycle, but it also
    injects a tiny SRAM-resident Pico program so we can observe at least one
    genuine CPU write in the otherwise minimal chip_core harness.
    """
    await _start_up_with_preloaded_program(dut, PICO_TIMER_WRITE_PROGRAM)
    _set_test_mode(dut, 0b01000)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

    saw_write_qualifier = False
    for _ in range(200):
        await RisingEdge(dut.clk)
        expected = _pack_pico_mmio_write_summary_str(dut)
        got = _debug_bus_str(dut)
        assert got == expected, (
            f"pico MMIO write summary mismatch: expected {expected}, got {got}"
        )
        if expected[0] == "1":
            saw_write_qualifier = True
            assert int(dut.u_top.pico_mem_addr_o.value) == TIMER_CTRL_ADDR, (
                f"expected Pico MMIO write to TIMER_CTRL 0x{TIMER_CTRL_ADDR:08x}, "
                f"got 0x{int(dut.u_top.pico_mem_addr_o.value):08x}"
            )
            assert int(dut.u_top.pico_mem_wstrb_o.value) == 0xF, (
                f"expected full-word Pico store, got wstrb=0x{int(dut.u_top.pico_mem_wstrb_o.value):x}"
            )
            assert int(dut.u_top.pico_mem_wdata_o.value) == 0x3, (
                f"expected TIMER_CTRL write data 0x00000003, got 0x{int(dut.u_top.pico_mem_wdata_o.value):08x}"
            )
            break

    assert saw_write_qualifier, "expected at least one real Pico MMIO write in mode 01000"


@cocotb.test()
async def test_mode_01001_pico_sleep_irq_summary_tracks_sleep_irq_cpu_and_trap(dut):
    """Pico sleep/IRQ summary mode should observe live FSM and IRQ state.

    Mode 01001 is intentionally an observer mode: it should not force CPU_ONLY,
    otherwise the debug bus could never show a real sleeping state. This test
    drives the normal FSM into SLEEP, toggles the DFT IRQ/wake inputs, then uses
    a neighboring CPU-only DFT mode to prove the CPU-clock summary bit.
    """
    _set_defaults(dut)
    dut.rst_n.value = 1
    await Timer(1, unit="ns")
    dut.rst_n.value = 0
    _preload_sram_words(dut, PICO_SLEEP_REQUEST_PROGRAM)
    dut.u_top.boot_done.value = Force(1)
    dut.u_top.start_i.value = Force(1)
    _set_test_mode(dut, 0b01001)
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    await Timer(200, unit="ns")
    dut.rst_n.value = 1
    await _wait_for_pico_sleeping(dut)
    await ClockCycles(dut.clk, 2)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_sleep_irq_summary(dut, trap="0", sleeping="1", cpu_clk_en="0", irq="0")
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=0, sleeping=1)

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 1)
    await ClockCycles(dut.clk, 2)
    _assert_sleep_irq_summary(dut, trap="0", sleeping="1", cpu_clk_en="0", irq="1")

    _drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    await ClockCycles(dut.clk, 2)
    _assert_sleep_irq_summary(dut, trap="0", sleeping="1", cpu_clk_en="0", irq="0")

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 1)
    await _wait_for_pico_awake(dut)
    await ClockCycles(dut.clk, 1)
    _assert_sleep_irq_summary(dut, trap="0", sleeping="0", cpu_clk_en="0", irq="0")

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk, 1)

    # Move through a neighboring CPU-only DFT mode, then return to 01001 to
    # observe that the CPU clock-enable bit is reflected by this summary view.
    _set_test_mode(dut, 0b01010)
    await ClockCycles(dut.clk, 4)
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

    _set_test_mode(dut, 0b01001)
    await ClockCycles(dut.clk, 2)
    _assert_sleep_irq_summary(dut, trap="0", sleeping="0", cpu_clk_en="1", irq="0")

    # The chip_core-only harness has no pad-level trap stimulus. Force the trap
    # source briefly to verify bit 15 of the debug-bus packing.
    dut.u_top.trap.value = Force(1)
    await Timer(1, unit="ns")
    _assert_sleep_irq_summary(dut, trap="1", sleeping="0", cpu_clk_en="1", irq="0")

    dut.u_top.trap.value = Release()
    dut.u_top.start_i.value = Release()
    dut.u_top.boot_done.value = Release()
    _drive_bidir_input(dut, FORCE_IRQ_PAD, 0)
    _drive_bidir_input(dut, FORCE_WAKE_PAD, 0)


@cocotb.test()
async def test_mode_01011_force_wake_reflects_pad(dut):
    """Force-wake mode should expose wake/IRQ sources without retired sideband stimulus."""
    await _start_up(dut)
    _set_test_mode(dut, 0b01011)
    await ClockCycles(dut.clk, 4)

    assert _debug_oe(dut) == 0xFFFF, f"expected debug OE enabled, got 0x{_debug_oe(dut):04x}"
    _assert_mode_enables(dut, feat_en=0, ml_en=0, cpu_en=1, sleeping=0)

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert _debug_bus_str(dut) == _pack_force_wake_summary_str(dut), (
        f"force wake summary mismatch: expected {_pack_force_wake_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 15) == 0, f"expected force wake bit low, got 0x{_debug_bus(dut):04x}"
    assert _debug_bit(dut, 14) == 0, "reserved wake-source summary bit should stay low"
    assert (_debug_bus(dut) & 0x0FFF) == 0, f"expected low 12 bits zero, got 0x{_debug_bus(dut):04x}"

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 1)
    await ClockCycles(dut.clk, 2)
    assert _debug_bus_str(dut) == _pack_force_wake_summary_str(dut), (
        f"force wake summary mismatch after forcing wake: expected {_pack_force_wake_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 15) == 1, f"expected force wake bit high, got 0x{_debug_bus(dut):04x}"
    assert (_debug_bus(dut) & 0x0FFF) == 0, f"expected low 12 bits zero, got 0x{_debug_bus(dut):04x}"

    dut.u_top.ml_irq.value = Force(1)
    await Timer(1, unit="ns")
    assert _debug_bus_str(dut) == _pack_force_wake_summary_str(dut), (
        f"force wake summary mismatch after forcing ML IRQ: expected {_pack_force_wake_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 13) == 1, "expected ML IRQ summary bit high"

    dut.u_top.timer_event.value = Force(1)
    await Timer(1, unit="ns")
    assert _debug_bus_str(dut) == _pack_force_wake_summary_str(dut), (
        f"force wake summary mismatch after forcing timer event: expected {_pack_force_wake_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 12) == 1, "expected timer-event summary bit high"

    dut.u_top.ml_irq.value = Release()
    dut.u_top.timer_event.value = Release()
    await Timer(1, unit="ns")

    _drive_bidir_input(dut, FORCE_WAKE_PAD, 0)
    await ClockCycles(dut.clk, 2)
    assert _debug_bus_str(dut) == _pack_force_wake_summary_str(dut), (
        f"force wake summary mismatch after release: expected {_pack_force_wake_summary_str(dut)}, "
        f"got {_debug_bus_str(dut)}"
    )
    assert _debug_bit(dut, 15) == 0, f"expected force wake bit cleared, got 0x{_debug_bus(dut):04x}"
    assert _debug_bit(dut, 14) == 0, "reserved wake-source summary bit should remain low"
