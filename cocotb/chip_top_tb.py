# SPDX-FileCopyrightText: © 2025 Project Template Contributors
# SPDX-License-Identifier: Apache-2.0

import os
import logging
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import Timer, RisingEdge, ClockCycles, ReadOnly
from cocotb.handle import Force
from cocotb_tools.runner import get_runner
from cocotbext.i2c import I2cDevice

_GL_SENSOR_BRIDGE = "sim_chip_top_gl_sensor_bridge_env"

# ---------------------------------------------------------------------------
# Environment configuration
# ---------------------------------------------------------------------------
def _env_flag(name, default=False):
    value = os.getenv(name)
    if value is None:
        return default
    return value.strip().lower() not in {"", "0", "false", "no", "off"}


def _env_int(name, default):
    value = os.getenv(name)
    if value is None:
        return default
    return int(value, 0)


sim         = os.getenv("SIM", "icarus")
pdk_root    = os.getenv("PDK_ROOT", Path("~/.ciel").expanduser())
pdk         = os.getenv("PDK", "gf180mcuD")
scl         = os.getenv("SCL", "gf180mcu_fd_sc_mcu7t5v0")
gl          = _env_flag("GL")
waves       = _env_flag("WAVES", True)
clk_freq_mhz = float(os.getenv("CLK_FREQ_MHZ", "10.0" if gl else "50.0"))
slot        = os.getenv("SLOT", "1x1")
test_module = os.getenv("COCOTB_TEST_MODULE", "chip_top_tb")
gl_debug_probes = _env_flag("GL_DEBUG_PROBES")
gl_sram_probes = _env_flag("GL_SRAM_PROBES", gl_debug_probes)
gl_fetch_monitor = _env_flag("GL_FETCH_MONITOR", gl_debug_probes)
gl_snapshot_interval = _env_int("GL_SNAPSHOT_INTERVAL", 50_000 if gl_debug_probes else 0)


hdl_toplevel = os.getenv("CHIP_TOPLEVEL", "sim_chip_top_gl_sensor_bridge_env")#"chip_top_sim_wrap" )
chip_netlist_top = os.getenv("CHIP_NETLIST_TOP", "chip_top")


_PROJ = Path(__file__).resolve().parent
_FIRMWARE_NAME = os.getenv("FIRMWARE_NAME", "test_top_normal")
_FIRMWARE_HEX = str(_PROJ / "firmware" / "build" / _FIRMWARE_NAME / "firmware.hex")
_WEIGHT_HEX = str(_PROJ / "firmware" / "build" / "generated" / "taketwo_params.hex")


def _u32_or_none(handle):
    try:
        return int(handle.value)
    except (ValueError, TypeError):
        return None


def _s16(word: int) -> int:
    word &= 0xFFFF
    return word - 0x10000 if word & 0x8000 else word


def _s16_or_none(handle):
    try:
        return _s16(int(handle.value))
    except ValueError:
        return None


def _fmt_hex(value, digits=8):
    return "X" if value is None else f"0x{value:0{digits}X}"


def _clk_handle(dut):
    """Return the clock handle that the testbench actually drives.

    chip_top_sim_wrap exposes clk_PAD as a module input port (driveable).
    sim_chip_top_gl_sensor_bridge_env has clk_PAD as an internal wire
    driven by clk_drv; cocotb can only poke the reg, not the wire.
    """
    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        return dut.clk_drv
    return dut.clk_PAD


def _rst_handle(dut):
    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        return dut.rst_n_drv
    return dut.rst_n_PAD


def _input_handle(dut):
    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        return dut.input_drv
    return dut.input_PAD


async def set_defaults(dut):
    _input_handle(dut).value = 0

async def set_start(dut, cycles):
    cocotb.log.info("Start bit set high")
    _input_handle(dut).value = 0b00100000
    await ClockCycles(_clk_handle(dut), cycles)
    _input_handle(dut).value = 0b00000000
    cocotb.log.info("Start bit set low")

async def start_clock(clock, freq_mhz: float | None = None):
    """Start the clock at freq_mhz MHz."""
    if freq_mhz is None:
        freq_mhz = clk_freq_mhz
    period_ns = 1_000.0 / freq_mhz
    cocotb.log.info(f"Starting clock at {freq_mhz:g} MHz ({period_ns:g} ns period)")
    c = Clock(clock, period_ns, "ns")
    cocotb.start_soon(c.start())


async def reset(dut, time_ns=1000):
    """Assert then deassert reset."""
    cocotb.log.info("Reset asserted...")
    _rst_handle(dut).value = 0
    await Timer(time_ns, "ns")
    _rst_handle(dut).value = 1
    cocotb.log.info("Reset deasserted.")


async def start_up(dut):
    """Common startup: defaults → clock → reset."""
    await set_defaults(dut)
    await start_clock(_clk_handle(dut))
    await reset(dut)


class _FlatGL:
    """Proxy for a flat GL module scope.

    After synthesis flattening, nets that were inside sub-modules become
    escaped identifiers in the top-level module (e.g. ``\\i_chip_core.u_top.boot_done ``).
    Attribute access on this proxy translates to a VPI lookup by escaped name.
    """
    def __init__(self, scope, prefix):
        object.__setattr__(self, "_scope", scope)
        object.__setattr__(self, "_prefix", prefix)

    def __getattr__(self, name):
        scope  = object.__getattribute__(self, "_scope")
        prefix = object.__getattribute__(self, "_prefix")
        # Try with backslash+trailing-space (Verilog escaped identifier syntax),
        # then without trailing space as a fallback.
        for escaped in (f"\\{prefix}.{name} ", f"\\{prefix}.{name}"):
            try:
                return scope._id(escaped, extended=False)
            except AttributeError:
                pass
        raise AttributeError(f"{scope._path} has no flat GL net for '{prefix}.{name}'")


def _flat_gl_bit(scope, escaped_name):
    """Look up one escaped flat GL net by exact flattened name."""
    for escaped in (f"\\{escaped_name} ", f"\\{escaped_name}"):
        try:
            return scope._id(escaped, extended=False)
        except AttributeError:
            pass
    raise AttributeError(f"{scope._path} has no flat GL net '{escaped_name}'")


def _flat_gl_u(scope, escaped_name):
    try:
        return int(_flat_gl_bit(scope, escaped_name).value)
    except (AttributeError, ValueError, TypeError):
        return None


def _flat_gl_raw(scope, escaped_name):
    try:
        return str(_flat_gl_bit(scope, escaped_name).value)
    except AttributeError:
        return "MISSING"


def _child_raw(scope, name):
    try:
        return str(scope._id(name, extended=False).value)
    except AttributeError:
        return "MISSING"


def _child_vec_str(scope, name, digits=None):
    try:
        value = scope._id(name, extended=False).value
    except AttributeError:
        return "MISSING"
    try:
        unsigned = value.to_unsigned()
    except ValueError:
        return "X"
    if digits is None:
        digits = max(1, (len(value) + 3) // 4)
    return f"0x{unsigned:0{digits}X}"


def _flat_gl_handle(scope, escaped_name):
    for escaped in (f"\\{escaped_name} ", f"\\{escaped_name}"):
        try:
            return scope._id(escaped, extended=False)
        except AttributeError:
            pass
    return None


def _flat_gl_vec(scope, escaped_name, width, missing_zero=False):
    value = 0
    for bit in range(width):
        bit_value = _flat_gl_u(scope, f"{escaped_name}[{bit}]")
        if bit_value is None:
            if missing_zero:
                bit_value = 0
            else:
                return None
        value |= (bit_value & 1) << bit
    return value


def _flat_gl_vec_str(scope, escaped_name, width, digits=None, missing_zero=False):
    value = _flat_gl_vec(scope, escaped_name, width, missing_zero=missing_zero)
    if value is not None:
        if digits is None:
            digits = max(1, (width + 3) // 4)
        return f"0x{value:0{digits}X}"

    raw_bits = []
    for bit in reversed(range(width)):
        raw_bits.append(_flat_gl_raw(scope, f"{escaped_name}[{bit}]"))
    if any(bit == "MISSING" for bit in raw_bits):
        return "MISSING"
    return "X"


def _readmemh_words(path, count):
    words = []
    address = 0
    try:
        with open(path, encoding="ascii") as f:
            for line in f:
                line = line.split("//", 1)[0]
                for token in line.split():
                    if token.startswith("@"):
                        try:
                            address = int(token[1:], 16)
                        except ValueError:
                            address = len(words)
                        while len(words) < address:
                            words.append(0)
                        continue
                    if any(ch in token.lower() for ch in "xz"):
                        value = None
                    else:
                        value = int(token, 16) & 0xFFFF_FFFF
                    if address == len(words):
                        words.append(value)
                    else:
                        while len(words) <= address:
                            words.append(0)
                        words[address] = value
                    address += 1
                    if len(words) >= count:
                        return words[:count]
    except OSError:
        return []
    return words[:count]


def _gl_sram_macro(scope, name):
    return _flat_gl_handle(scope, f"i_chip_core.u_top.sram.{name}")


def _gl_sram_macro_probe(scope, name):
    macro = _gl_sram_macro(scope, name)
    if macro is None:
        return {
            "name": name, "present": False, "cen": "MISSING", "gwen": "MISSING",
            "a": "MISSING", "d": "MISSING", "q": "MISSING", "mem": ["MISSING"] * 4,
        }
    return {
        "name": name,
        "present": True,
        "cen": _child_raw(macro, "CEN"),
        "gwen": _child_raw(macro, "GWEN"),
        "a": _child_vec_str(macro, "A", digits=3),
        "d": _child_vec_str(macro, "D", digits=2),
        "q": _child_vec_str(macro, "Q", digits=2),
        "mem": [_child_vec_str(macro, f"mem_{idx}", digits=2) for idx in range(4)],
    }


def _hex_byte(value):
    if value in {"MISSING", "X"}:
        return None
    try:
        return int(value, 16) & 0xFF
    except ValueError:
        return None


def _gl_sram_word_from_macros(scope, bank, word_index):
    if bank not in {"A", "B"} or not 0 <= word_index <= 3:
        return None
    byte_values = []
    for byte_lane in range(1, 5):
        macro = _gl_sram_macro(scope, f"mem_{bank}_{byte_lane}")
        if macro is None:
            return None
        raw = _child_vec_str(macro, f"mem_{word_index}", digits=2)
        value = _hex_byte(raw)
        if value is None:
            return None
        byte_values.append(value)
    return (
        byte_values[0]
        | (byte_values[1] << 8)
        | (byte_values[2] << 16)
        | (byte_values[3] << 24)
    )


def _gl_sram_boot_words(scope, count=4):
    words = []
    for word_index in range(count):
        bank = "A" if word_index < 512 else "B"
        bank_word = word_index if bank == "A" else word_index - 512
        words.append(_gl_sram_word_from_macros(scope, bank, bank_word))
    return words


def _fmt_word(value):
    return "MISSING/X" if value is None else f"0x{value:08X}"


def _gl_boot_integrity(scope, count=4):
    expected = _readmemh_words(_FIRMWARE_HEX, count)
    observed = _gl_sram_boot_words(scope, count)
    rows = []
    ok = True
    for idx in range(count):
        exp = expected[idx] if idx < len(expected) else None
        obs = observed[idx] if idx < len(observed) else None
        match = exp is not None and obs == exp
        ok = ok and match
        rows.append((idx, exp, obs, match))
    return ok, rows


def _gl_chip_inst(dut):
    """Return the chip_top instance handle in GL wrappers."""
    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        return dut.u_chip
    return dut.u_chip_top


def _gl_force_vector_zero(scope, escaped_base, width, name_for_log=None):
    """Force every existing bit of a vector net to 0. Returns list of bit indices
    that were actually found in the netlist (the rest were optimized away)."""
    forced = []
    for bit in range(width):
        try:
            h = _flat_gl_bit(scope, f"{escaped_base}[{bit}]")
            h.value = Force(0)
            forced.append(bit)
        except AttributeError:
            pass
    if name_for_log:
        cocotb.log.info(f"Forced {name_for_log}: {len(forced)}/{width} bits present (indices {forced})")
    return forced


def _gl_force_bit_zero(scope, escaped_name, name_for_log=None):
    """Force a single net to 0. Returns True if found, False if missing."""
    try:
        h = _flat_gl_bit(scope, escaped_name)
        h.value = Force(0)
        if name_for_log:
            cocotb.log.info(f"Forced {name_for_log}=0")
        return True
    except AttributeError:
        if name_for_log:
            cocotb.log.info(f"Skipped {name_for_log} (not in netlist)")
        return False


def _gl_release_vector(scope, escaped_base, bit_indices):
    """Release Forces previously applied to a vector net."""
    from cocotb.handle import Release
    for bit in bit_indices:
        try:
            h = _flat_gl_bit(scope, f"{escaped_base}[{bit}]")
            h.value = Release()
        except AttributeError:
            pass


def _gl_release_bit(scope, escaped_name):
    """Release a Force previously applied to a single-bit net."""
    from cocotb.handle import Release
    try:
        h = _flat_gl_bit(scope, escaped_name)
        h.value = Release()
    except AttributeError:
        pass


_FSM_ONEHOT_NAMES = {
    0: "BOOT", 1: "IDLE", 2: "SLEEP", 3: "FEAT_ONLY",
    4: "ALL", 5: "CPU_FEAT", 6: "FEAT_ML", 7: "CPU_ONLY",
    8: "ALARM", 9: "CPU_INIT",
}


def _gl_decode_fsm_state(scope):
    """Read state_q as a one-hot vector and decode which state is active.

    Yosys synthesized state_q as one-hot (each bit = one state). Bits 1 and 3
    (IDLE/FEAT_ONLY) were optimized away — likely transient states that never
    hold for a full clock. Returns a string like "ALL(4)" or "X-MULTI(0,9)" if
    multiple bits set, or "X-NONE" if all 0 (could be IDLE/FEAT_ONLY).
    """
    active = []
    has_x = False
    bits_present = []
    for state_num in range(10):
        raw = _flat_gl_raw(scope, f"i_chip_core.u_top.fsm.state_q[{state_num}]")
        if raw == "MISSING":
            continue
        bits_present.append(state_num)
        if raw == "1":
            active.append(state_num)
        elif raw not in ("0",):
            has_x = True

    if has_x and not active:
        return "X-BITS"
    if len(active) == 0:
        # Could be the optimized-away IDLE(1) or FEAT_ONLY(3)
        return f"NONE-SET (transient? present_bits={bits_present})"
    if len(active) == 1:
        n = active[0]
        return f"{_FSM_ONEHOT_NAMES.get(n, '?')}({n})"
    names = ",".join(f"{_FSM_ONEHOT_NAMES.get(n, '?')}({n})" for n in active)
    return f"MULTI[{names}]"


def _gl_progress(dut):
    """Collect GL-only flattened debug state for runtime progress logs.

    Probes are grouped by subsystem; signals that didn't survive synthesis
    return "MISSING" — useful info itself (tells you what got optimized).
    """
    scope = _gl_chip_inst(dut)
    return {
        # ---------- reset / clock health (start here if FSM stuck) ----------
        "rst_n":        _flat_gl_raw(scope, "i_chip_core.rst_n"),
        "reset_i":      _flat_gl_raw(scope, "i_chip_core.u_top.reset_i"),
        "fsm_rstn":     _flat_gl_raw(scope, "i_chip_core.u_top.fsm.resetn_i"),
        "fsm_clk":      _flat_gl_raw(scope, "i_chip_core.u_top.fsm.clk_i"),
        "core_clk":     _flat_gl_raw(scope, "i_chip_core.core_clk_w"),
        "cpu_clk":      _flat_gl_raw(scope, "i_chip_core.pico_cpu_clk_en_w"),
        "cpu_clk_lat":  _flat_gl_raw(scope, "i_chip_core.u_top.cpu_clk_en_lat"),

        # ---------- top FSM ----------
        # In the synthesized netlist, state_q is one-hot encoded:
        #   state_q[N] == 1 means FSM is in state N (BOOT=0, IDLE=1, SLEEP=2,
        #   FEAT_ONLY=3, ALL=4, CPU_FEAT=5, FEAT_ML=6, CPU_ONLY=7, ALARM=8, CPU_INIT=9).
        # Yosys optimized away bits for IDLE and FEAT_ONLY (likely pass-through states).
        "boot":         _flat_gl_raw(scope, "i_chip_core.u_top.boot_done"),
        "fsm":          _gl_decode_fsm_state(scope),
        "fsm_d":        _flat_gl_vec_str(scope, "i_chip_core.u_top.fsm.state_d", 4, digits=1, missing_zero=True),
        # FSM transition inputs — tells you why FSM isn't moving
        "fsm_bdi":      _flat_gl_raw(scope, "i_chip_core.u_top.fsm.boot_done_i"),
        "fsm_starti":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.start_i"),
        "fsm_sleepi":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.sleep_req_i"),
        "fsm_featvi":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.feat_valid_i"),
        "fsm_mlirq":    _flat_gl_raw(scope, "i_chip_core.u_top.fsm.ml_irq_i"),
        "fsm_cpualm":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.cpu_alarm_i"),
        "fsm_wakerq":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.irqc_wake_req_i"),
        "fsm_tmode":    _flat_gl_vec_str(scope, "i_chip_core.u_top.fsm.test_mode_i", 4, digits=1, missing_zero=True),
        # FSM outputs
        "feat_en":      _flat_gl_raw(scope, "i_chip_core.u_top.fsm.feat_en_o"),
        "ml_en":        _flat_gl_raw(scope, "i_chip_core.u_top.fsm.ml_en_o"),
        "cpu_en":       _flat_gl_raw(scope, "i_chip_core.u_top.fsm.cpu_en_o"),

        # ---------- CPU activity ----------
        "sleep":        _flat_gl_raw(scope, "i_chip_core.pico_sleeping_w"),
        "trap":         _flat_gl_raw(scope, "i_chip_core.pico_trap_w"),
        "mem_v":        _flat_gl_raw(scope, "i_chip_core.pico_mem_valid_w"),
        "mem_i":        _flat_gl_raw(scope, "i_chip_core.pico_mem_instr_w"),
        "mem_rdy":      _flat_gl_raw(scope, "i_chip_core.u_top.mem_ready"),
        "pico_rdy":     _flat_gl_raw(scope, "i_chip_core.pico_mem_ready_w"),
        "mem_addr":     _flat_gl_vec_str(scope, "i_chip_core.pico_mem_addr_w", 32),
        "mem_wstrb":    _flat_gl_vec_str(scope, "i_chip_core.u_top.mem_wstrb", 4, digits=1),
        "mem_wdata":    _flat_gl_vec_str(scope, "i_chip_core.u_top.mem_wdata", 32),
        "mem_rdata":    _flat_gl_vec_str(scope, "i_chip_core.u_top.mem_rdata", 32),
        "sram_ready":   _flat_gl_raw(scope, "i_chip_core.u_top.sram_ready"),
        "sram_rdata":   _flat_gl_vec_str(scope, "i_chip_core.u_top.sram_rdata", 32),

        # ---------- Test/diag MMIO registers ----------
        "status":       _flat_gl_vec_str(scope, "i_chip_core.u_top.test_status", 32),
        "code":         _flat_gl_vec_str(scope, "i_chip_core.u_top.test_code", 32),

        # ---------- Timer ----------
        "tim_evt":      _flat_gl_raw(scope, "i_chip_core.u_top.u_timer.event_o"),
        "tim_evt_lat":  _flat_gl_raw(scope, "i_chip_core.u_top.u_timer.event_latched"),
        "tim_ctrl":     _flat_gl_vec_str(scope, "i_chip_core.u_top.u_timer.ctrl_r", 32),
        "tim_count":    _flat_gl_vec_str(scope, "i_chip_core.u_top.u_timer.count_r", 32),

        # ---------- IRQ controller ----------
        "irq_pend":     _flat_gl_vec_str(scope, "i_chip_core.u_top.u_irqc.pending", 32),
        "irq_mask":     _flat_gl_vec_str(scope, "i_chip_core.u_top.u_irqc.mask", 32),
        "irq_wake_en":  _flat_gl_vec_str(scope, "i_chip_core.u_top.u_irqc.wake_en", 32),
        "irq_wake_req": _flat_gl_raw(scope, "i_chip_core.u_top.u_irqc.wake_req_o"),
        "irq_to_cpu":   _flat_gl_raw(scope, "i_chip_core.u_top.u_irqc.irq_o"),

        # ---------- Power ----------
        "pwr_sleep_req":_flat_gl_raw(scope, "i_chip_core.u_top.u_pwr.sleep_req_o"),
        "pwr_wake_st":  _flat_gl_vec_str(scope, "i_chip_core.u_top.u_pwr.wake_status", 32),

        # ---------- Sensor pipeline (post-I2C) ----------
        "accel_v":      _flat_gl_raw(scope, "i_chip_core.u_top.accel_valid_w"),
        "ppg_v":        _flat_gl_raw(scope, "i_chip_core.u_top.ppg_sample_valid_w"),
        "epoch_end":    _flat_gl_raw(scope, "i_chip_core.u_top.epoch_end_w"),
        "feat_valid":   _flat_gl_raw(scope, "i_chip_core.feat_valid_w"),
        "feat_latched": _flat_gl_raw(scope, "i_chip_core.u_top.feat_latched_valid_r"),
        "feat_reason":  _flat_gl_vec_str(scope, "i_chip_core.u_top.feat_invalid_reason_latched_r", 7, digits=2),

        # ---------- ML accelerator ----------
        "ml_irq":       _flat_gl_raw(scope, "i_chip_core.ml_irq_w"),
        "ml_en_w":      _flat_gl_raw(scope, "i_chip_core.u_top.ml_en"),
        "wflash_state": _flat_gl_vec_str(scope, "i_chip_core.u_top.u_weight_flash.state", 4, digits=1),
        "logit0":       _flat_gl_vec_str(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_0", 32),
        "logit1":       _flat_gl_vec_str(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_1", 32),
        "dbg_logit0":   _flat_gl_vec_str(scope, "i_chip_core.u_top.logit0", 16),
        "dbg_logit1":   _flat_gl_vec_str(scope, "i_chip_core.u_top.logit1", 16),

        # ---------- Alarm ----------
        "cpu_alarm":    _flat_gl_raw(scope, "i_chip_core.u_top.cpu_alarm_w"),
        "fsm_alarm_o":  _flat_gl_raw(scope, "i_chip_core.u_top.fsm.alarm_o"),
    }


def _log_gl_sram_macros(dut, logger, label=""):
    scope = _gl_chip_inst(dut)
    suffix = f" {label}" if label else ""
    logger.info(f"[gl_sram{suffix}] first four boot words:")
    ok, rows = _gl_boot_integrity(scope, count=4)
    for idx, expected, observed, match in rows:
        verdict = "OK" if match else "MISMATCH"
        logger.info(
            f"  word[{idx}] expected={_fmt_word(expected)} "
            f"observed={_fmt_word(observed)} {verdict}"
        )
    logger.info(f"[gl_sram{suffix}] boot integrity first4={'OK' if ok else 'FAIL'}")

    for bank in ("A", "B"):
        for lane in range(1, 5):
            probe = _gl_sram_macro_probe(scope, f"mem_{bank}_{lane}")
            logger.info(
                f"  sram.{probe['name']} CEN={probe['cen']} GWEN={probe['gwen']} "
                f"A={probe['a']} D={probe['d']} Q={probe['q']} "
                f"mem0..3={','.join(probe['mem'])}"
            )


async def _gl_pico_fetch_monitor(dut, logger, cycles=2_000, limit=16):
    """Log the first visible Pico memory handshakes after GL boot."""
    if not gl:
        return

    prev = None
    logged = 0
    for cycle in range(cycles):
        await RisingEdge(_clk_handle(dut))
        p = _gl_progress(dut)
        snapshot = (
            p["mem_v"], p["mem_i"], p["pico_rdy"], p["mem_rdy"],
            p["mem_addr"], p["mem_wstrb"], p["mem_wdata"],
            p["mem_rdata"], p["sram_ready"], p["sram_rdata"],
        )
        interesting = (
            snapshot != prev
            and any(value not in {"0", "0x0", "0x00000000", "MISSING"} for value in snapshot)
        )
        if interesting:
            logger.info(
                f"[gl_fetch {cycle:5d}] mem_v={p['mem_v']} instr={p['mem_i']} "
                f"pico_ready={p['pico_rdy']} top_ready={p['mem_rdy']} "
                f"addr={p['mem_addr']} wstrb={p['mem_wstrb']} "
                f"wdata={p['mem_wdata']} rdata={p['mem_rdata']} "
                f"sram_ready={p['sram_ready']} sram_rdata={p['sram_rdata']}"
            )
            logged += 1
            if logged >= limit:
                return
        prev = snapshot


def _core(dut):
    """Return the chip_core handle regardless of toplevel."""
    if hdl_toplevel in {"chip_top_sim_wrap", _GL_SENSOR_BRIDGE}:
        if gl:
            return _FlatGL(_gl_chip_inst(dut), "i_chip_core")
        # chip_top_sim_wrap instantiates `u_chip_top`; the bridge uses `u_chip`.
        return _gl_chip_inst(dut).i_chip_core
    return dut.i_chip_core


def _top(dut):
    """Return the top handle (inside chip_core)."""
    if gl:
        return _FlatGL(_gl_chip_inst(dut), "i_chip_core.u_top")
    return _core(dut).u_top


@cocotb.test()
async def test_chip_top_smoke(dut):
    """Basic smoke test: clock passes, reset releases, normal mode active."""
    logger = logging.getLogger("chip_top_smoke")
    logger.info("Startup sequence...")
    await start_up(dut)

    # Normal mode
    _input_handle(dut).value = 0
    await ClockCycles(_clk_handle(dut), 20)

    core = _core(dut)
    logger.info("Checking normal-mode wiring...")

    assert _rst_handle(dut).value == 1, "reset should be deasserted after startup"
    if not gl:
        assert core.test_mode_w.value.integer == 0, "chip should be in normal mode"
        assert core.core_clk_w.value == core.clk.value, \
            "normal mode should use the onboard clock"
        assert core.bidir_oe.value[22:7].integer == 0, \
            "debug bus OE should be 0 in normal mode"

    logger.info("Smoke test passed.")


#boot test

@cocotb.test(skip=(hdl_toplevel not in {"chip_top_sim_wrap", _GL_SENSOR_BRIDGE}))
async def test_chip_top_boot(dut):
    """Boot test: wait for boot_done, verify CPU is running (no trap)."""
    logger = logging.getLogger("chip_top_boot")

    # Force FSM to ALL mode so feat+ML+CPU all run without sleeping.
    # input_PAD[3:0] drives test_mode[3:0]; 4'b0101 = ALL mode.
    await set_defaults(dut)
    _input_handle(dut).value = 0b00100000

    await start_clock(_clk_handle(dut))
    await reset(dut)

    core  = _core(dut)
    u_top = _top(dut)

    TIMEOUT_CYCLES = 500_000
    cocotb.log.info("Waiting for boot_done...")

    for cycle in range(TIMEOUT_CYCLES):
        await RisingEdge(_clk_handle(dut))
        if cycle % 10_000 == 0:
            logger.info(f"  cycle {cycle}: boot_done={u_top.boot_done.value}")
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError(f"boot_done never asserted within {TIMEOUT_CYCLES} cycles")

    if gl and gl_sram_probes:
        _log_gl_sram_macros(dut, logger, "after boot_done")
    if gl and gl_fetch_monitor:
        await _gl_pico_fetch_monitor(dut, logger, cycles=2_000, limit=8)

    assert int(core.pico_trap_w.value) != 1, \
        "CPU trapped — firmware likely loaded incorrectly"

    logger.info(f"Boot complete. CPU running (no trap).")


#full pipeline test

_N_LOGITS = 2  # number of inferences firmware runs before writing CAFEBABE


async def _feat_monitor(u_top):
    """Background coroutine: prints features when they change."""
    prev_feat = None
    while True:
        await RisingEdge(u_top.feat_valid_o)
        mot = _s16_or_none(u_top.feat_motion_latched_r)
        tim = _s16_or_none(u_top.feat_time_latched_r)
        dhr = _s16_or_none(u_top.feat_delta_hr_latched_r)
        msd = _s16_or_none(u_top.feat_mssd_latched_r)
        curr_feat = (mot, tim, dhr, msd)
        if curr_feat != prev_feat:
            print(
                f"[feat]  mot={mot!s:>7}  tim={tim!s:>6}  "
                f"dhr={dhr!s:>7}  msd={msd!s:>7}",
                flush=True,
            )
            prev_feat = curr_feat


async def _axi_write_monitor(clk, u_top):
    """Print every taketwo→weight_flash_axi AXI write: addr + data.
    This tells us which addresses taketwo is actually writing on each inference,
    so we can see if the final logit write is landing where weight_flash_axi
    expects (LOGIT_OFFSET = 5504 = 0x1580 from WEIGHT_BASE).
    """
    try:
        awvalid = u_top.wram_awvalid
        awaddr  = u_top.wram_awaddr
        wvalid  = u_top.wram_wvalid
        wdata   = u_top.wram_wdata
        wlast   = u_top.wram_wlast
    except Exception as e:
        print(f"[axi_mon] could not resolve wram_* signals: {e!r}", flush=True)
        return

    captured_addr = None
    while True:
        await RisingEdge(clk)
        try:
            if int(awvalid.value) == 1:
                captured_addr = int(awaddr.value)
            if int(wvalid.value) == 1 and captured_addr is not None:
                d = int(wdata.value)
                last = int(wlast.value)
                off = (captured_addr - 0x03006000) & 0xFFFFFFFF
                print(
                    f"[axi-w]  addr=0x{captured_addr:08X} (off=0x{off:X})  "
                    f"data=0x{d:08X}  wlast={last}",
                    flush=True,
                )
        except ValueError:
            continue


_FSM_LABELS = {
    0: "BOOT", 1: "IDLE", 2: "SLEEP", 3: "FEAT_ONLY",
    4: "ALL", 5: "CPU_FEAT", 6: "FEAT_ML", 7: "CPU_ONLY",
    8: "ALARM", 9: "CPU_INIT",
}


async def _can_sleep_monitor(clk, u_top, core):
    """Print FSM state on every transition + can_sleep_w inputs."""
    try:
        fsm = u_top.fsm
    except AttributeError:
        print("[sleep_mon] could not find fsm instance", flush=True)
        return
    prev = None
    while True:
        await RisingEdge(clk)
        raw = str(fsm.state_q.value)
        if raw == prev:
            continue
        prev = raw
        try:
            st_int = int(fsm.state_q.value)
            label = _FSM_LABELS.get(st_int, f"?({st_int})")
        except ValueError:
            label = "X-BITS"
        try:
            sr = int(u_top.sleep_req.value)
        except ValueError:
            sr = "X"
        try:
            wr = int(u_top.irqc_wake_req.value)
        except ValueError:
            wr = "X"
        try:
            bd = int(u_top.boot_done.value)
        except ValueError:
            bd = "X"
        print(
            f"[sleep_mon] state_q={raw} ({label})  "
            f"sleep_req={sr}  wake_req={wr}  boot_done={bd}",
            flush=True,
        )


async def _gl_heartbeat(dut):
    """GL-friendly progress beat — only watches pads, which survive flattening.
    Tracks SPI activity (toggle count on bidir[1] = boot_spi_clk) and alarm.
    Also tracks sensor SCL (bidir[23]) to diagnose I2C sensor communication.
    """
    cycles = 0
    spi_clk_toggles = 0
    sensor_scl_toggles = 0
    last_spi_clk = None
    last_sensor_scl = None
    last_alarm = None
    while True:
        await ClockCycles(_clk_handle(dut), 1)
        cycles += 1
        try:
            bpad = dut.bidir_PAD.value
            spi_clk_now    = int(bpad[1])
            alarm_now      = int(bpad[0])
            sensor_scl_now = int(bpad[23])
        except Exception:
            spi_clk_now    = None
            alarm_now      = None
            sensor_scl_now = None

        if last_spi_clk is not None and spi_clk_now != last_spi_clk:
            spi_clk_toggles += 1
        last_spi_clk = spi_clk_now

        if last_sensor_scl is not None and sensor_scl_now != last_sensor_scl:
            sensor_scl_toggles += 1
        last_sensor_scl = sensor_scl_now

        if alarm_now is not None and alarm_now != last_alarm:
            print(f"[gl_hb @{cycles:8d}] alarm_o transition: {last_alarm} -> {alarm_now}",
                  flush=True)
            last_alarm = alarm_now

        if cycles % 25_000 == 0:
            print(
                f"[gl_hb @{cycles:8d}]  alarm_o={alarm_now}  "
                f"spi_clk_toggles={spi_clk_toggles}  "
                f"sensor_scl_toggles={sensor_scl_toggles}",
                flush=True,
            )


async def _sec_results_logger(dut, results_path):
    """Write a CSV row to `results_path` every time time_in_night_seconds_o
    changes. Captures key signals (reset, boot, fsm, alarm, features, logits)
    so we can review chip behavior post-run without waveforms."""
    clk = _clk_handle(dut)
    u_top = _top(dut)
    core  = _core(dut)
    scope = _gl_chip_inst(dut)

    # Open the file and write header
    f = open(results_path, "w", buffering=1)  # line-buffered
    f.write(
        "sec,rst_n,boot,fsm,alarm_o,"
        "motion,time,delta_hr,mssd,"
        "logit_reg0,logit_reg1,dbg_logit0,dbg_logit1\n"
    )
    cocotb.log.info(f"[sec_log] writing results to {results_path}")

    def read_signed_or_x(handle):
        try:
            return str(_s16(int(handle.value)))
        except (ValueError, AttributeError):
            return "X"

    def read_u32_or_x(handle, digits=8):
        try:
            return f"0x{int(handle.value):0{digits}X}"
        except (ValueError, AttributeError):
            return "X"

    def read_bit(handle):
        try:
            return str(int(handle.value))
        except (ValueError, AttributeError):
            return "X"

    # Find the seconds register — globaltimer hierarchical name
    # Try multiple ways since hierarchy may flatten
    sec_handle = None
    try:
        sec_handle = u_top.u_globaltimer.time_in_night_seconds_o
    except AttributeError:
        try:
            sec_handle = u_top.seconds_w  # latched signal in top.sv
        except AttributeError:
            cocotb.log.warning("[sec_log] could not find time_in_night_seconds_o; falling back to cycle-based logging")

    last_sec = -1
    cycle_count = 0
    while True:
        await RisingEdge(clk)
        cycle_count += 1

        # Determine current second
        try:
            if sec_handle is not None:
                cur_sec = int(sec_handle.value)
            else:
                # Fallback: log every ~10K cycles when seconds reg is missing
                if cycle_count % 10_000 != 0:
                    continue
                cur_sec = cycle_count // 10_000
        except ValueError:
            continue
        if cur_sec == last_sec:
            continue
        last_sec = cur_sec

        # Snapshot signals — robust to missing handles
        rst_n  = read_bit(_rst_handle(dut))
        try:
            boot = read_bit(u_top.boot_done)
        except AttributeError:
            boot = "X"

        # FSM state — use the existing one-hot decoder
        if gl:
            fsm = _gl_decode_fsm_state(scope)
        else:
            try:
                fsm_int = int(u_top.fsm.state_q.value)
                fsm = _FSM_LABELS.get(fsm_int, f"?({fsm_int})")
            except (AttributeError, ValueError):
                fsm = "X"

        try:
            alarm = read_bit(dut.alarm_o)
        except AttributeError:
            alarm = "X"

        # Feature latched values
        motion = read_signed_or_x(getattr(u_top, "feat_motion_latched_r", None))
        timev  = read_signed_or_x(getattr(u_top, "feat_time_latched_r",   None))
        dhr    = read_signed_or_x(getattr(u_top, "feat_delta_hr_latched_r", None))
        mssd   = read_signed_or_x(getattr(u_top, "feat_mssd_latched_r",   None))

        # Logit registers from weight_flash
        try:
            logit0 = read_u32_or_x(u_top.u_weight_flash.logit_reg_0)
        except AttributeError:
            logit0 = "X"
        try:
            logit1 = read_u32_or_x(u_top.u_weight_flash.logit_reg_1)
        except AttributeError:
            logit1 = "X"

        # Debug logits driven directly by taketwo
        try:
            dbg0 = read_signed_or_x(u_top.logit0)
        except AttributeError:
            dbg0 = "X"
        try:
            dbg1 = read_signed_or_x(u_top.logit1)
        except AttributeError:
            dbg1 = "X"

        f.write(
            f"{cur_sec},{rst_n},{boot},{fsm},{alarm},"
            f"{motion},{timev},{dhr},{mssd},"
            f"{logit0},{logit1},{dbg0},{dbg1}\n"
        )


async def _logit_monitor(clk, u_top):
    """Background coroutine: prints logit_reg_0 every time it changes.
    logit_reg_0 packs both logits: bits[15:0]=log0, bits[31:16]=log1.
    """
    # One-shot probe so we can see *why* the handle lookup fails if it does
    try:
        handle = u_top.u_weight_flash.logit_reg_0
        print(f"[logit_monitor] handle resolved: {handle._path}", flush=True)
    except Exception as e:
        print(f"[logit_monitor] could not resolve u_top.u_weight_flash.logit_reg_0: {e!r}",
              flush=True)
        return

    prev = None
    first_value_logged = False
    while True:
        await RisingEdge(clk)
        try:
            packed = int(handle.value)
        except ValueError:
            # Contains X's — skip silently
            continue
        except Exception as e:
            if not first_value_logged:
                print(f"[logit_monitor] read error: {e!r}", flush=True)
                first_value_logged = True
            continue
        if not first_value_logged:
            print(f"[logit_monitor] first valid read: packed=0x{packed:08X}", flush=True)
            first_value_logged = True
        if packed != prev:
            u0 = packed & 0xFFFF
            u1 = (packed >> 16) & 0xFFFF
            log0 = _s16(u0)
            log1 = _s16(u1)
            pred = "bad time to wake" if log1 > log0 else "good time to wake"
            print(
                f"[logit]  packed=0x{packed:08X}  "
                f"log0=0x{u0:04X} ({log0:6d})  "
                f"log1=0x{u1:04X} ({log1:6d})  → {pred}",
                flush=True,
            )
            prev = packed


@cocotb.test(skip=(hdl_toplevel not in {"chip_top_sim_wrap", _GL_SENSOR_BRIDGE}))
async def test_chip_top_normal(dut):
    """Full pipeline: sensor → features → ML inference → alarm output."""
    logger = logging.getLogger("chip_top_normal")

    await set_defaults(dut)
    await start_clock(_clk_handle(dut))

    # Assert reset (active low) BEFORE forcing so we can latch FSM state in
    # one-hot BOOT during the reset window.
    cocotb.log.info("Reset asserted (pre-force)")
    _rst_handle(dut).value = 0
    await ClockCycles(_clk_handle(dut), 5)

    core  = _core(dut)
    u_top = _top(dut)

    forced_fsm_bits = []
    forced_irq_pend = []
    forced_irq_mask = []
    forced_irq_wake_en = []
    forced_irq_src_d = []
    forced_irq_active = []
    forced_irq_wake_pd = []
    forced_tim_ctrl = []
    forced_tim_count = []
    forced_pwr_wake_st = []
    forced_pwr_wake_rsn = []
    forced_wf_logit0 = []
    forced_wf_logit1 = []
    forced_wf_feat0 = []
    forced_wf_feat1 = []
    forced_wf_state = []

    if gl:
        # Bypass ICG X-propagation if icgtp_1 was not yet re-synthesized.
        # Net is absent in netlists where the fix is already in — skip silently.
        try:
            u_top.cpu_clk_en_lat.value = Force(1)
        except AttributeError:
            cocotb.log.info("cpu_clk_en_lat not in netlist — ICG fix present, skipping force")

        # Yosys mapped sync-reset RTL to plain dffq_1 cells (no reset port).
        # In GL sim, flops power up to X and the sync-reset combo path computes
        # D = f(X) = X, locking the X forever. Force critical control flops to
        # their reset values during the reset window so they have a defined
        # starting point; release after reset deasserts.
        scope = _gl_chip_inst(dut)

        # --- top_fsm: state_q is one-hot, force BOOT (bit 0 = 1, others = 0)
        for n in range(10):
            try:
                h = _flat_gl_bit(scope, f"i_chip_core.u_top.fsm.state_q[{n}]")
                h.value = Force(1 if n == 0 else 0)
                forced_fsm_bits.append(n)
            except AttributeError:
                pass
        cocotb.log.info(f"Forced state_q one-hot BOOT (bits present: {forced_fsm_bits})")
        # FSM internal trackers
        _gl_force_bit_zero(scope, "i_chip_core.u_top.fsm.cpu_idle_seen_r", "fsm.cpu_idle_seen_r")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.fsm.cpu_clk_en_r",    "fsm.cpu_clk_en_r")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.fsm.sleep_req_d_r",   "fsm.sleep_req_d_r")

        # --- irq_ctrl_mmio: pending, mask, wake_en, src_d, active, wake_pending_d
        forced_irq_pend    = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.pending",        32, "irqc.pending")
        forced_irq_mask    = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.mask",           32, "irqc.mask")
        forced_irq_wake_en = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.wake_en",        32, "irqc.wake_en")
        forced_irq_src_d   = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.src_d",          32, "irqc.src_d")
        forced_irq_active  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.active",         32, "irqc.active")
        forced_irq_wake_pd = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.wake_pending_d", 32, "irqc.wake_pending_d")

        # --- timer_mmio: control + counter + event-latched
        forced_tim_ctrl  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_timer.ctrl_r",  32, "timer.ctrl_r")
        forced_tim_count = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_timer.count_r", 32, "timer.count_r")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.u_timer.event_latched", "timer.event_latched")

        # --- pwrctrl_mmio: sleep_req, wake_status, wake_reason, cpu_awake_d
        _gl_force_bit_zero(scope, "i_chip_core.u_top.u_pwr.sleep_req_o", "pwr.sleep_req_o")
        forced_pwr_wake_st  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_pwr.wake_status", 32, "pwr.wake_status")
        forced_pwr_wake_rsn = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_pwr.wake_reason", 32, "pwr.wake_reason")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.u_pwr.cpu_awake_d", "pwr.cpu_awake_d")

        # --- weight_flash_axi: state machine + captured logits + feature regs
        forced_wf_state  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.state",       4,  "wflash.state")
        forced_wf_logit0 = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_0", 32, "wflash.logit_reg_0")
        forced_wf_logit1 = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_1", 32, "wflash.logit_reg_1")
        forced_wf_feat0  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_0",  32, "wflash.feat_reg_0")
        forced_wf_feat1  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_1",  32, "wflash.feat_reg_1")

    # Hold reset asserted for a few more cycles so the forced values propagate
    await ClockCycles(dut.clk_PAD, 5)

    # Deassert reset (active low → high)
    _rst_handle(dut).value = 1
    await ClockCycles(_clk_handle(dut), 2)
    cocotb.log.info("Reset deasserted")
    await reset(dut)

    if gl:
        # Release all the forces so logic can run normally
        for n in forced_fsm_bits:
            _gl_release_bit(scope, f"i_chip_core.u_top.fsm.state_q[{n}]")
        _gl_release_bit(scope, "i_chip_core.u_top.fsm.cpu_idle_seen_r")
        _gl_release_bit(scope, "i_chip_core.u_top.fsm.cpu_clk_en_r")
        _gl_release_bit(scope, "i_chip_core.u_top.fsm.sleep_req_d_r")

        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.pending",        forced_irq_pend)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.mask",           forced_irq_mask)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.wake_en",        forced_irq_wake_en)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.src_d",          forced_irq_src_d)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.active",         forced_irq_active)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.wake_pending_d", forced_irq_wake_pd)

        _gl_release_vector(scope, "i_chip_core.u_top.u_timer.ctrl_r",  forced_tim_ctrl)
        _gl_release_vector(scope, "i_chip_core.u_top.u_timer.count_r", forced_tim_count)
        _gl_release_bit(scope, "i_chip_core.u_top.u_timer.event_latched")

        _gl_release_bit(scope, "i_chip_core.u_top.u_pwr.sleep_req_o")
        _gl_release_vector(scope, "i_chip_core.u_top.u_pwr.wake_status", forced_pwr_wake_st)
        _gl_release_vector(scope, "i_chip_core.u_top.u_pwr.wake_reason", forced_pwr_wake_rsn)
        _gl_release_bit(scope, "i_chip_core.u_top.u_pwr.cpu_awake_d")

        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.state",       forced_wf_state)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_0", forced_wf_logit0)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_1", forced_wf_logit1)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_0",  forced_wf_feat0)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_1",  forced_wf_feat1)

        cocotb.log.info("Released all force-init nets — chip should run with defined initial state")

    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        # Drive real sensor I2C pads with Python slave models.
        # The bridge wrapper exposes scl/sda hooks regardless of RTL or GL.
        from test_chip_top_i2c_pads import (
            Lis2dw12Device, Adpd144riDevice, _build_sensor_model_streams,
        )
        accel_samples, ppg_samples = _build_sensor_model_streams()
        _accel = Lis2dw12Device(
            sda=dut.sensor_sda_sample, sda_o=dut.accel_sda_o,
            scl=dut.sensor_scl_sample, scl_o=dut.accel_scl_o,
            samples=accel_samples,
        )
        _ppg = Adpd144riDevice(
            sda=dut.sensor_sda_sample, sda_o=dut.ppg_sda_o,
            scl=dut.sensor_scl_sample, scl_o=dut.ppg_scl_o,
            samples=ppg_samples,
        )
        cocotb.start_soon(_accel._run())
        cocotb.start_soon(_ppg._run())

    BOOT_TIMEOUT    = 500_000
    RUNTIME_TIMEOUT = 4_000_000
    # --- Phase 1: wait for boot ---
    logger.info("Waiting for boot_done...")
    cocotb.log.info(f"Firmware.hex is: {_FIRMWARE_HEX}")
    for cycle in range(BOOT_TIMEOUT):
        await RisingEdge(_clk_handle(dut))
        if u_top.boot_done.value == 1:
            await ClockCycles(_clk_handle(dut), 10)
            break
    else:
        raise AssertionError("Timeout waiting for boot_done")
    #assert core.pico_trap_w.value == 0, "CPU trapped during boot"

    if gl and gl_sram_probes:
        _log_gl_sram_macros(dut, logger, "after boot_done")
    if gl and gl_fetch_monitor:
        cocotb.start_soon(_gl_pico_fetch_monitor(dut, logger, cycles=5_000, limit=16))

    cocotb.log.info("Boot done. Waiting for alarm_o...")
    await set_start(dut, 10)
    logger.info(f"[gl={bool(gl)}] start_i pulsed; entering main loop")
    # Start background monitor — prints features + stale logits on every feat_valid_o
    # Skip in GL mode: feat_valid_o and logit_reg_0 are RTL-only signals
    if not gl:
        cocotb.start_soon(_feat_monitor(u_top))
        cocotb.start_soon(_logit_monitor(_clk_handle(dut), u_top))
        cocotb.start_soon(_axi_write_monitor(_clk_handle(dut), u_top))
        cocotb.start_soon(_can_sleep_monitor(_clk_handle(dut), u_top, core))
    else:
        # GL mode — internal signals are flattened away. Only pads are observable.
        cocotb.start_soon(_gl_heartbeat(dut))

    # Per-second CSV results logger (always on — no waves means we need this)
    results_path = str(_PROJ / "sim_results.csv")
    cocotb.start_soon(_sec_results_logger(dut, results_path))

    # --- Phase 2: wait for alarm_o to assert (test passes on rising edge) ---
    # The firmware runs inferences and writes ALARM_CTRL=1 once the wake streak
    # threshold is hit; that drives the FSM to ALARM state which asserts alarm_o.
    # A firmware-side DEAD_BEEF in TEST_STATUS still fails fast.
    for cycle in range(RUNTIME_TIMEOUT):
        await RisingEdge(_clk_handle(dut))

        if cycle % 10_000 == 0:
            if gl:
                try:
                    p = _gl_progress(dut)
                    print(f"[GL @{cycle:7d}] rst_n={p['rst_n']} reset_i={p['reset_i']} core_clk={p['core_clk']} cpu_clk={p['cpu_clk']}", flush=True)
                    print(f"[GL @{cycle:7d}] fsm={p['fsm']} boot={p['boot']} start={p['fsm_starti']} feat_v={p['fsm_featvi']} ml_irq={p['fsm_mlirq']} alarm={p['fsm_alarm_o']}", flush=True)
                    print(f"[GL @{cycle:7d}] cpu_sleep={p['sleep']} trap={p['trap']} status={p['status']} code={p['code']}", flush=True)
                    print(f"[GL @{cycle:7d}] timer_evt={p['tim_evt']} tim_ctrl={p['tim_ctrl']} tim_count={p['tim_count']}", flush=True)
                    print(f"[GL @{cycle:7d}] irq_pend={p['irq_pend']} wake_en={p['irq_wake_en']} wake_req={p['irq_wake_req']}", flush=True)
                    print(f"[GL @{cycle:7d}] accel_v={p['accel_v']} ppg_v={p['ppg_v']} feat_valid={p['feat_valid']} logit0={p['logit0']} logit1={p['logit1']}", flush=True)
                    print(f"[GL @{cycle:7d}] pad_alarm={dut.alarm_o.value}", flush=True)
                except Exception as e:
                    print(f"[GL @{cycle:7d}] _gl_progress ERROR: {e}", flush=True)
            else:
                try:
                    ts = int(u_top.test_status.value)
                    alarm = dut.alarm_o.value
                    cocotb.log.info(
                        f"  cycle {cycle}: test_status=0x{ts:08X} alarm={alarm}"
                    )
                except Exception:
                    pass

        # CPU trap check (RTL-only — pico_trap_w doesn't survive synthesis flattening)
        if not gl:
            try:
                if core.pico_trap_w.value == 1:
                    raise AssertionError("CPU trapped during runtime")
            except AttributeError:
                pass

        # Fast-fail on firmware-reported error in RTL. In GL, these debug
        # mailbox vectors are flattened into per-bit escaped nets; keep the
        # GL pass/fail criterion focused on the real pad-level alarm output.
        if not gl:
            try:
                status = int(u_top.test_status.value)
                if status == 0xDEAD_BEEF:
                    tc_raw = u_top.test_code.value
                    try:
                        code_str = f"0x{int(tc_raw):08X}"
                    except (ValueError, TypeError):
                        code_str = f"X:{tc_raw!s}"
                    raise AssertionError(f"Firmware reported FAIL: test_code={code_str}")
            except ValueError:
                pass

        # Pass condition: alarm_o rose (output pad is always observable, even in GL)
        try:
            if int(dut.alarm_o.value) == 1:
                await ClockCycles(_clk_handle(dut), 10)
                if int(dut.alarm_o.value) == 1:
                    cocotb.log.info(f"alarm_o asserted at cycle {cycle} — test passed.")
                    return
        except ValueError:
            continue

    raise AssertionError(
        f"Timeout after {RUNTIME_TIMEOUT} cycles — alarm_o never asserted"
    )

@cocotb.test(skip=(hdl_toplevel not in {"chip_top_sim_wrap", _GL_SENSOR_BRIDGE}))
async def test_chip_top_normal_full(dut):
    """Full pipeline: sensor → features → ML inference → alarm output."""
    logger = logging.getLogger("chip_top_full")

    # ALL mode: features + ML + CPU all active; bypasses SLEEP state in sim.
    await set_defaults(dut)
    await start_clock(_clk_handle(dut))

    core  = _core(dut)
    u_top = _top(dut)

    if gl:
        # Same GL force-init as test_chip_top_normal: prevents X-lock on
        # dffq_1 flops (no async reset) and the icgtp_1 ICG that gates cpu_clk.
        _rst_handle(dut).value = 0
        await ClockCycles(_clk_handle(dut), 5)
        scope = _gl_chip_inst(dut)
        try:
            u_top.cpu_clk_en_lat.value = Force(1)
        except AttributeError:
            cocotb.log.info("cpu_clk_en_lat not in netlist — ICG fix present, skipping force")
        forced_fsm_bits = []
        for n in range(10):
            try:
                h = _flat_gl_bit(scope, f"i_chip_core.u_top.fsm.state_q[{n}]")
                h.value = Force(1 if n == 0 else 0)
                forced_fsm_bits.append(n)
            except AttributeError:
                pass
        _gl_force_bit_zero(scope, "i_chip_core.u_top.fsm.cpu_idle_seen_r", "fsm.cpu_idle_seen_r")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.fsm.cpu_clk_en_r",    "fsm.cpu_clk_en_r")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.fsm.sleep_req_d_r",   "fsm.sleep_req_d_r")
        forced_irq_pend    = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.pending",        32, "irqc.pending")
        forced_irq_mask    = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.mask",           32, "irqc.mask")
        forced_irq_wake_en = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.wake_en",        32, "irqc.wake_en")
        forced_irq_src_d   = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.src_d",          32, "irqc.src_d")
        forced_irq_active  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.active",         32, "irqc.active")
        forced_irq_wake_pd = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_irqc.wake_pending_d", 32, "irqc.wake_pending_d")
        forced_tim_ctrl    = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_timer.ctrl_r",  32, "timer.ctrl_r")
        forced_tim_count   = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_timer.count_r", 32, "timer.count_r")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.u_timer.event_latched", "timer.event_latched")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.u_pwr.sleep_req_o", "pwr.sleep_req_o")
        forced_pwr_wake_st  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_pwr.wake_status", 32, "pwr.wake_status")
        forced_pwr_wake_rsn = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_pwr.wake_reason", 32, "pwr.wake_reason")
        _gl_force_bit_zero(scope, "i_chip_core.u_top.u_pwr.cpu_awake_d", "pwr.cpu_awake_d")
        forced_wf_state  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.state",       4,  "wflash.state")
        forced_wf_logit0 = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_0", 32, "wflash.logit_reg_0")
        forced_wf_logit1 = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_1", 32, "wflash.logit_reg_1")
        forced_wf_feat0  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_0",  32, "wflash.feat_reg_0")
        forced_wf_feat1  = _gl_force_vector_zero(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_1",  32, "wflash.feat_reg_1")
        await ClockCycles(dut.clk_PAD, 5)
        _rst_handle(dut).value = 1
        await ClockCycles(_clk_handle(dut), 2)
        await reset(dut)
        for n in forced_fsm_bits:
            _gl_release_bit(scope, f"i_chip_core.u_top.fsm.state_q[{n}]")
        _gl_release_bit(scope, "i_chip_core.u_top.fsm.cpu_idle_seen_r")
        _gl_release_bit(scope, "i_chip_core.u_top.fsm.cpu_clk_en_r")
        _gl_release_bit(scope, "i_chip_core.u_top.fsm.sleep_req_d_r")
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.pending",        forced_irq_pend)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.mask",           forced_irq_mask)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.wake_en",        forced_irq_wake_en)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.src_d",          forced_irq_src_d)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.active",         forced_irq_active)
        _gl_release_vector(scope, "i_chip_core.u_top.u_irqc.wake_pending_d", forced_irq_wake_pd)
        _gl_release_vector(scope, "i_chip_core.u_top.u_timer.ctrl_r",  forced_tim_ctrl)
        _gl_release_vector(scope, "i_chip_core.u_top.u_timer.count_r", forced_tim_count)
        _gl_release_bit(scope, "i_chip_core.u_top.u_timer.event_latched")
        _gl_release_bit(scope, "i_chip_core.u_top.u_pwr.sleep_req_o")
        _gl_release_vector(scope, "i_chip_core.u_top.u_pwr.wake_status", forced_pwr_wake_st)
        _gl_release_vector(scope, "i_chip_core.u_top.u_pwr.wake_reason", forced_pwr_wake_rsn)
        _gl_release_bit(scope, "i_chip_core.u_top.u_pwr.cpu_awake_d")
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.state",       forced_wf_state)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_0", forced_wf_logit0)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.logit_reg_1", forced_wf_logit1)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_0",  forced_wf_feat0)
        _gl_release_vector(scope, "i_chip_core.u_top.u_weight_flash.feat_reg_1",  forced_wf_feat1)
        cocotb.log.info("Released all force-init nets")
    else:
        await reset(dut)

    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        from test_chip_top_i2c_pads import (
            Lis2dw12Device, Adpd144riDevice, _build_sensor_model_streams,
        )
        accel_samples, ppg_samples = _build_sensor_model_streams()
        _accel = Lis2dw12Device(
            sda=dut.sensor_sda_sample, sda_o=dut.accel_sda_o,
            scl=dut.sensor_scl_sample, scl_o=dut.accel_scl_o,
            samples=accel_samples,
        )
        _ppg = Adpd144riDevice(
            sda=dut.sensor_sda_sample, sda_o=dut.ppg_sda_o,
            scl=dut.sensor_scl_sample, scl_o=dut.ppg_scl_o,
            samples=ppg_samples,
        )
        cocotb.start_soon(_accel._run())
        cocotb.start_soon(_ppg._run())

    BOOT_TIMEOUT    = _env_int("BOOT_TIMEOUT_CYCLES", 250_000 if gl else 500_000)
    RUNTIME_TIMEOUT = _env_int("RUNTIME_TIMEOUT_CYCLES", 15_00_000 if gl else 30_00_000)

    # --- Phase 1: wait for boot ---
    cocotb.log.info("Waiting for boot_done...")
    for cycle in range(BOOT_TIMEOUT):
        await RisingEdge(_clk_handle(dut))
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError("Timeout waiting for boot_done")

    assert _u32_or_none(core.pico_trap_w) != 1, "CPU trapped during boot"

    cocotb.log.info("Boot done. Waiting for alarm_o...")
    await set_start(dut, 10)
    logger.info(f"[gl={bool(gl)}] start_i pulsed; entering main loop")
    # Start background monitor — prints features + stale logits on every feat_valid_o
    # Skip in GL mode: feat_valid_o and logit_reg_0 are RTL-only signals
    if not gl:
        cocotb.start_soon(_feat_monitor(u_top))
        cocotb.start_soon(_logit_monitor(_clk_handle(dut), u_top))
        cocotb.start_soon(_axi_write_monitor(_clk_handle(dut), u_top))
        cocotb.start_soon(_can_sleep_monitor(_clk_handle(dut), u_top, core))
    else:
        cocotb.start_soon(_gl_heartbeat(dut))

    # --- Phase 2: wait for alarm_o to assert (test passes on rising edge) ---
    # The firmware runs inferences and writes ALARM_CTRL=1 once the wake streak
    # threshold is hit; that drives the FSM to ALARM state which asserts alarm_o.
    # A firmware-side DEAD_BEEF in TEST_STATUS still fails fast.
    for cycle in range(RUNTIME_TIMEOUT):
        await RisingEdge(_clk_handle(dut))

        if cycle % 10_000 == 0:
            if gl:
                p = _gl_progress(dut)
                cocotb.log.info(
                    f"  cycle {cycle}: "
                    f"boot={p['boot']} status={p['status']} code={p['code']} "
                    f"fsm={p['fsm']} cpu_clk={p['cpu_clk']} sleep={p['sleep']} "
                    f"trap={p['trap']} mem_v={p['mem_v']} mem_i={p['mem_i']} "
                    f"mem_addr={p['mem_addr']} feat={p['feat_valid']} "
                    f"latched={p['feat_latched']} reason={p['feat_reason']} "
                    f"ml_irq={p['ml_irq']} wf_state={p['wflash_state']} "
                    f"logit0={p['logit0']} logit1={p['logit1']} "
                    f"cpu_alarm={p['cpu_alarm']} "
                    f"pad_alarm={dut.alarm_o.value}"
                )
            else:
                try:
                    ts = int(u_top.test_status.value)
                    alarm = dut.alarm_o.value
                    cocotb.log.info(
                        f"  cycle {cycle}: test_status=0x{ts:08X} alarm={alarm}"
                    )
                except Exception:
                    pass

        # CPU trap check (RTL-only — pico_trap_w doesn't survive synthesis flattening)
        if not gl:
            try:
                if core.pico_trap_w.value == 1:
                    raise AssertionError("CPU trapped during runtime")
            except AttributeError:
                pass

        # Fast-fail on firmware-reported error in RTL. In GL, these debug
        # mailbox vectors are flattened into per-bit escaped nets; keep the
        # GL pass/fail criterion focused on the real pad-level alarm output.
        if not gl:
            try:
                status = int(u_top.test_status.value)
                if status == 0xDEAD_BEEF:
                    tc_raw = u_top.test_code.value
                    try:
                        code_str = f"0x{int(tc_raw):08X}"
                    except (ValueError, TypeError):
                        code_str = f"X:{tc_raw!s}"
                    raise AssertionError(f"Firmware reported FAIL: test_code={code_str}")
            except ValueError:
                pass

        # Pass condition: alarm_o rose (output pad is always observable)
        try:
            if int(dut.alarm_o.value) == 1:
                await ClockCycles(_clk_handle(dut), 10)
                if int(dut.alarm_o.value) == 1:
                    cocotb.log.info(f"alarm_o asserted at cycle {cycle} — test passed.")
                    await ClockCycles(_clk_handle(dut), 1000)
                    await set_start(dut, 10)
                    await ClockCycles(_clk_handle(dut), 10)
                    await set_start(dut, 10)
                    await reset(dut)
                    await ClockCycles(dut.clk_PAD, 10_000)
                    await set_start(dut, 10)

                    return
        except ValueError:
            continue

    raise AssertionError(
        f"Timeout after {RUNTIME_TIMEOUT} cycles — alarm_o never asserted"
    )

def chip_top_runner():
    proj_path = Path(__file__).resolve().parent

    sources = []
    # RTL builds use the SIM-only sensor bus; GL builds below intentionally do not.
    defines = {f"SLOT_{slot.upper().replace('.', 'P')}": True, "SIM": True}
    includes = [proj_path / "../src/"]

    if gl:
        final_dir = Path(os.getenv("FINAL_DIR", proj_path / "../final")).resolve()
        netlist = final_dir / "pnl" / f"{chip_netlist_top}.pnl.v"
        if not netlist.exists():
            netlist = proj_path / "../src" / f"{chip_netlist_top}.pnl.v"
        if not netlist.exists():
            netlist = proj_path / "../src" / f"{chip_netlist_top}.nl.v"
        if not netlist.exists():
            raise FileNotFoundError(
                f"gate-level netlist not found: {netlist}. "
                "Set FINAL_DIR=<run>/final, add src/<top>.pnl.v or src/<top>.nl.v, or set "
                "CHIP_NETLIST_TOP if the netlist top is not chip_top."
            )

        sources += [
            Path(pdk_root) / pdk / "libs.ref" / scl / "verilog" / f"{scl}.v",
            Path(pdk_root) / pdk / "libs.ref" / scl / "verilog" / "primitives.v",
            Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_fd_io.v",
            Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_ws_io.v",
            Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_ip_sram/verilog/gf180mcu_fd_ip_sram__sram512x8m8wm1.v",
            proj_path / "../ip/gf180mcu_ws_ip__id/vh/gf180mcu_ws_ip__id.v",
            proj_path / "../ip/gf180mcu_ws_ip__logo/vh/gf180mcu_ws_ip__logo.v",
            netlist,
        ]

        if hdl_toplevel != chip_netlist_top:
            wrapper = proj_path / "sim/tb" / f"{hdl_toplevel}.sv"
            if not wrapper.exists():
                wrapper = proj_path / f"{hdl_toplevel}.sv"
            if not wrapper.exists():
                raise FileNotFoundError(f"gate-level wrapper not found: {wrapper}")
            sources.append(wrapper)
            if hdl_toplevel == "chip_top_sim_wrap":
                sources.append(proj_path / "sim/tb/spi_flash_model.v")
                sources.append(proj_path / "sensors/i2c_slave_lis2dw12.sv")
                sources.append(proj_path / "sensors/i2c_slave_adpd144ri.sv")
            elif hdl_toplevel == _GL_SENSOR_BRIDGE:
                # Sensor bridge uses Python cocotbext I2C slaves (no SV models).
                # Flash model still needed for SPI boot + weight loading.
                sources.append(proj_path / "sim/tb/spi_flash_model.v")

        defines = {"FUNCTIONAL": True, "functional": True, "USE_POWER_PINS": True}
    else:
        src_dir = proj_path / "../src"
        pad_level = hdl_toplevel in {"chip_top", "chip_top_sim_wrap", _GL_SENSOR_BRIDGE}
        skip = {"dummy_top.sv", "soc_top.v"}
        netlist_suffixes = (".nl.v", ".pnl.v")
        if pad_level:
            skip.add("gf180mcu_fd_ip_sram__sram512x8m8wm1.v")
        sources += sorted(p for p in src_dir.glob("*.sv") if p.name not in skip)
        sources += sorted(
            p for p in src_dir.glob("*.v")
            if p.name not in skip and not p.name.endswith(netlist_suffixes)
        )
        sources.append(proj_path / "../ip/picorv32.v")

        # Simulation models
        sources.append(proj_path / "sim/tb/spi_flash_model.v")
        sources.append(proj_path / "sensors/i2c_slave_lis2dw12.sv")
        sources.append(proj_path / "sensors/i2c_slave_adpd144ri.sv")

        # Pick the right wrapper based on the selected HDL toplevel.
        if hdl_toplevel == "chip_top_sim_wrap":
            sources.append(proj_path / "chip_top_sim_wrap.sv")
        elif hdl_toplevel == _GL_SENSOR_BRIDGE:
            # Bridge wrapper drives real SCL/SDA pads with Python BFMs; no SV
            # I2C slave models needed (cocotbext-i2c provides them at runtime).
            sources.append(proj_path / "sim/tb" / f"{_GL_SENSOR_BRIDGE}.sv")

        # Pad-level builds need GF180 IO models. Direct chip_core RTL DFT does not.
        if pad_level:
            sources += [
                Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_fd_io.v",
                Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_ws_io.v",
                Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_ip_sram/verilog/gf180mcu_fd_ip_sram__sram512x8m8wm1.v",
                proj_path / "../ip/gf180mcu_ws_ip__id/vh/gf180mcu_ws_ip__id.v",
                proj_path / "../ip/gf180mcu_ws_ip__logo/vh/gf180mcu_ws_ip__logo.v",
            ]

    build_args = []
    if sim == "verilator":
        build_args = ["--timing", "--trace", "--trace-fst", "--trace-structs"]

    parameters = {}
    if hdl_toplevel == "chip_core" and test_module == "chip_core_dft_tb":
        parameters["DEBUG_STIM_EN"] = 1

    runner = get_runner(sim)
    # Wave dumping is expensive for long GL/bridge runs. Set WAVES=0 to disable.
    waves_on = os.getenv("WAVES", "1") != "0"

    runner.build(
        sources=sources,
        hdl_toplevel=hdl_toplevel,
        defines=defines,
        parameters=parameters,
        always=True,
        includes=includes,
        build_args=build_args,
        waves=waves_on,
    )

    # Absolute paths — VVP runs from sim_build/, so relative paths fail.
    plusargs = [
        f"+FIRMWARE_HEX={_FIRMWARE_HEX}",
        f"+WEIGHT_HEX={_WEIGHT_HEX}",
        f"+DATA_DIR={proj_path}/sim/data",
    ]

    runner.test(
        hdl_toplevel=hdl_toplevel,
        test_module=test_module,
        plusargs=plusargs,
        waves=waves_on,
    )


if __name__ == "__main__":
    chip_top_runner()
