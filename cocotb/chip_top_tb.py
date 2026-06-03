# SPDX-FileCopyrightText: © 2025 Project Template Contributors
# SPDX-License-Identifier: Apache-2.0

import os
import logging
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.handle import Force
from cocotb.triggers import Timer, RisingEdge, ClockCycles, ReadOnly
from cocotb_tools.runner import get_runner
from cocotbext.i2c import I2cDevice

_GL_SENSOR_BRIDGE = "sim_chip_top_gl_sensor_bridge_env"

# ---------------------------------------------------------------------------
# Environment configuration
# ---------------------------------------------------------------------------
sim        = os.getenv("SIM", "icarus")
pdk_root   = os.getenv("PDK_ROOT", Path("~/.ciel").expanduser())
pdk        = os.getenv("PDK", "gf180mcuD")
scl        = os.getenv("SCL", "gf180mcu_fd_sc_mcu7t5v0")
gl         = os.getenv("GL", False)
slot       = os.getenv("SLOT", "1x1")
test_module = os.getenv("COCOTB_TEST_MODULE", "chip_top_tb")


hdl_toplevel = os.getenv("CHIP_TOPLEVEL", "chip_top_sim_wrap")
chip_netlist_top = os.getenv("CHIP_NETLIST_TOP", "chip_top")


_PROJ = Path(__file__).resolve().parent
_FIRMWARE_NAME = os.getenv("FIRMWARE_NAME", "test_top_normal")
_FIRMWARE_HEX = str(_PROJ / "firmware" / "build" / _FIRMWARE_NAME / "firmware.hex")
_WEIGHT_HEX = str(_PROJ / "firmware" / "build" / "generated" / "taketwo_params.hex")


def _u32_or_none(handle):
    try:
        return handle.value.to_unsigned()
    except ValueError:
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


async def set_defaults(dut):
    dut.input_PAD.value = 0

async def set_start(dut, cycles):
    cocotb.log.info("Start bit set high")
    dut.input_PAD.value = 0b00100000
    await ClockCycles(dut.clk_PAD, cycles)
    dut.input_PAD.value = 0b00000000
    cocotb.log.info("Start bit set low")

async def start_clock(clock, freq_mhz: float = 50.0):
    """Start the clock at freq_mhz MHz."""
    period_ns = 1_000.0 / freq_mhz
    c = Clock(clock, period_ns, "ns")
    cocotb.start_soon(c.start())


async def reset(rst_n, active_low=True, time_ns=1000):
    """Assert then deassert reset."""
    cocotb.log.info("Reset asserted...")
    rst_n.value = not active_low
    await Timer(time_ns, "ns")
    rst_n.value = active_low
    cocotb.log.info("Reset deasserted.")


async def start_up(dut):
    """Common startup: defaults → clock → reset."""
    await set_defaults(dut)
    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)


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
        return _flat_gl_bit(scope, escaped_name).value.to_unsigned()
    except (AttributeError, ValueError):
        return None


def _flat_gl_raw(scope, escaped_name):
    try:
        return str(_flat_gl_bit(scope, escaped_name).value)
    except AttributeError:
        return "MISSING"


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


def _gl_chip_inst(dut):
    """Return the chip_top instance handle in GL wrappers."""
    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        return dut.u_chip
    return dut.u_chip_top


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
        "boot":         _flat_gl_raw(scope, "i_chip_core.u_top.boot_done"),
        "fsm":          _flat_gl_vec_str(scope, "i_chip_core.u_top.fsm.state_q", 4, digits=1, missing_zero=True),
        "fsm_d":        _flat_gl_vec_str(scope, "i_chip_core.u_top.fsm.state_d", 4, digits=1, missing_zero=True),
        # FSM transition inputs — tells you why FSM isn't moving
        "fsm_bdi":      _flat_gl_raw(scope, "i_chip_core.u_top.fsm.boot_done_i"),
        "fsm_starti":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.start_i"),
        "fsm_sleepi":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.sleep_req_i"),
        "fsm_featvi":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.feat_valid_i"),
        "fsm_mlirq":    _flat_gl_raw(scope, "i_chip_core.u_top.fsm.ml_irq_i"),
        "fsm_cpualm":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.cpu_alarm_i"),
        "fsm_wakerq":   _flat_gl_raw(scope, "i_chip_core.u_top.fsm.irqc_wake_req_i"),
        "fsm_memv":     _flat_gl_raw(scope, "i_chip_core.u_top.fsm.mem_valid_i"),
        "fsm_idleR":    _flat_gl_raw(scope, "i_chip_core.u_top.fsm.cpu_idle_seen_r"),
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
        "mem_addr":     _flat_gl_vec_str(scope, "i_chip_core.pico_mem_addr_w", 32, missing_zero=True),
        "mem_wstrb":    _flat_gl_vec_str(scope, "i_chip_core.u_top.mem_wstrb", 4, digits=1, missing_zero=True),
        "mem_wdata":    _flat_gl_vec_str(scope, "i_chip_core.u_top.mem_wdata", 32, missing_zero=True),

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


def _core(dut):
    """Return the chip_core handle regardless of toplevel."""
    if hdl_toplevel in {"chip_top_sim_wrap", _GL_SENSOR_BRIDGE}:
        if gl:
            return _FlatGL(_gl_chip_inst(dut), "i_chip_core")
        return dut.u_chip_top.i_chip_core
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
    dut.input_PAD.value = 0
    await ClockCycles(dut.clk_PAD, 20)

    core = _core(dut)
    logger.info("Checking normal-mode wiring...")

    assert dut.rst_n_PAD.value == 1, "reset should be deasserted after startup"
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
    dut.input_PAD.value = 0b00100000

    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)

    core  = _core(dut)
    u_top = _top(dut)

    TIMEOUT_CYCLES = 500_000
    cocotb.log.info("Waiting for boot_done...")

    for cycle in range(TIMEOUT_CYCLES):
        await RisingEdge(dut.clk_PAD)
        if cycle % 10_000 == 0:
            logger.info(f"  cycle {cycle}: boot_done={u_top.boot_done.value}")
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError(f"boot_done never asserted within {TIMEOUT_CYCLES} cycles")

    assert core.pico_trap_w.value == 0, \
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
            ids = int(fsm.cpu_idle_seen_r.value)
        except ValueError:
            ids = "X"
        try:
            bd = int(u_top.boot_done.value)
        except ValueError:
            bd = "X"
        print(
            f"[sleep_mon] state_q={raw} ({label})  "
            f"sleep_req={sr}  idle={ids}  wake_req={wr}  boot_done={bd}",
            flush=True,
        )


async def _gl_heartbeat(dut):
    """GL-friendly progress beat — only watches pads, which survive flattening.
    Tracks SPI activity (toggle count on bidir[1] = boot_spi_clk) and alarm.
    """
    cycles = 0
    spi_clk_toggles = 0
    last_spi_clk = None
    last_alarm = None
    while True:
        await ClockCycles(dut.clk_PAD, 1)
        cycles += 1
        # Sample SPI clock and alarm
        try:
            bpad = dut.bidir_PAD.value
            # bidir_PAD[1] is boot SPI clock pre-boot_done; weight SPI after
            spi_clk_now = int(bpad[1])
            alarm_now   = int(bpad[0])
        except Exception:
            spi_clk_now = None
            alarm_now   = None

        if last_spi_clk is not None and spi_clk_now != last_spi_clk:
            spi_clk_toggles += 1
        last_spi_clk = spi_clk_now

        # Print alarm transitions immediately
        if alarm_now is not None and alarm_now != last_alarm:
            print(f"[gl_hb @{cycles:8d}] alarm_o transition: {last_alarm} -> {alarm_now}",
                  flush=True)
            last_alarm = alarm_now

        # Heartbeat every 25k cycles with rolling counts
        if cycles % 25_000 == 0:
            print(
                f"[gl_hb @{cycles:8d}]  alarm_o={alarm_now}  "
                f"spi_clk_toggles_so_far={spi_clk_toggles}",
                flush=True,
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
    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)

    core  = _core(dut)
    u_top = _top(dut)

    if gl:
        # Bypass ICG X-propagation until icgtp_1 fix is re-synthesized.
        u_top.cpu_clk_en_lat.value = Force(1)

    if gl and hdl_toplevel == _GL_SENSOR_BRIDGE:
        # Drive real sensor I2C pads with Python slave models.
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
    RUNTIME_TIMEOUT = 500_000#3_000_000
    # --- Phase 1: wait for boot ---
    logger.info("Waiting for boot_done...")
    for cycle in range(BOOT_TIMEOUT):
        await RisingEdge(dut.clk_PAD)
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError("Timeout waiting for boot_done")
    assert core.pico_trap_w.value == 0, "CPU trapped during boot"

    cocotb.log.info("Boot done. Waiting for alarm_o...")
    await set_start(dut, 10)
    logger.info(f"[gl={bool(gl)}] start_i pulsed; entering main loop")
    # Start background monitor — prints features + stale logits on every feat_valid_o
    # Skip in GL mode: feat_valid_o and logit_reg_0 are RTL-only signals
    if not gl:
        cocotb.start_soon(_feat_monitor(u_top))
        cocotb.start_soon(_logit_monitor(dut.clk_PAD, u_top))
        cocotb.start_soon(_axi_write_monitor(dut.clk_PAD, u_top))
        cocotb.start_soon(_can_sleep_monitor(dut.clk_PAD, u_top, core))
    else:
        # GL mode — internal signals are flattened away. Only pads are observable.
        cocotb.start_soon(_gl_heartbeat(dut))

    # --- Phase 2: wait for alarm_o to assert (test passes on rising edge) ---
    # The firmware runs inferences and writes ALARM_CTRL=1 once the wake streak
    # threshold is hit; that drives the FSM to ALARM state which asserts alarm_o.
    # A firmware-side DEAD_BEEF in TEST_STATUS still fails fast.
    for cycle in range(RUNTIME_TIMEOUT):
        await RisingEdge(dut.clk_PAD)

<<<<<<< HEAD
        if cycle % 10_000 == 0:
=======
        if cycle % 100_000 == 0:
>>>>>>> a7a90025da03fa71b1d93924be9b9bc10babba6e
            if gl:
                p = _gl_progress(dut)
                cocotb.log.info(f"==== cycle {cycle} GL snapshot ====")
                cocotb.log.info(
                    f"  [rst/clk]  rst_n={p['rst_n']} reset_i={p['reset_i']} "
                    f"fsm_rstn={p['fsm_rstn']} fsm_clk={p['fsm_clk']} "
                    f"core_clk={p['core_clk']} cpu_clk={p['cpu_clk']} "
                    f"cpu_clk_lat={p['cpu_clk_lat']}"
                )
                cocotb.log.info(
                    f"  [fsm]      state_q={p['fsm']} state_d={p['fsm_d']} "
                    f"boot={p['boot']} tmode={p['fsm_tmode']}"
                )
                cocotb.log.info(
                    f"  [fsm_in]   bdi={p['fsm_bdi']} start={p['fsm_starti']} "
                    f"sleep_req={p['fsm_sleepi']} feat_v={p['fsm_featvi']} "
                    f"ml_irq={p['fsm_mlirq']} cpu_alm={p['fsm_cpualm']} "
                    f"wake_req={p['fsm_wakerq']} mem_v={p['fsm_memv']} "
                    f"idle_seen={p['fsm_idleR']}"
                )
                cocotb.log.info(
                    f"  [fsm_out]  feat_en={p['feat_en']} ml_en={p['ml_en']} "
                    f"cpu_en={p['cpu_en']} alarm_o={p['fsm_alarm_o']}"
                )
                cocotb.log.info(
                    f"  [cpu]      sleep={p['sleep']} trap={p['trap']} "
                    f"mem_v={p['mem_v']} mem_i={p['mem_i']} mem_rdy={p['mem_rdy']} "
                    f"mem_addr={p['mem_addr']} mem_wstrb={p['mem_wstrb']} "
                    f"mem_wdata={p['mem_wdata']}"
                )
                cocotb.log.info(
                    f"  [test]     status={p['status']} code={p['code']}"
                )
                cocotb.log.info(
                    f"  [timer]    evt={p['tim_evt']} evt_lat={p['tim_evt_lat']} "
                    f"ctrl={p['tim_ctrl']} count={p['tim_count']}"
                )
                cocotb.log.info(
                    f"  [irqc]     pend={p['irq_pend']} mask={p['irq_mask']} "
                    f"wake_en={p['irq_wake_en']} wake_req={p['irq_wake_req']} "
                    f"to_cpu={p['irq_to_cpu']}"
                )
                cocotb.log.info(
                    f"  [pwr]      sleep_req={p['pwr_sleep_req']} "
                    f"wake_st={p['pwr_wake_st']}"
                )
                cocotb.log.info(
                    f"  [sensors]  accel_v={p['accel_v']} ppg_v={p['ppg_v']} "
                    f"epoch={p['epoch_end']} feat_v={p['feat_valid']} "
                    f"feat_latched={p['feat_latched']} feat_reason={p['feat_reason']}"
                )
                cocotb.log.info(
                    f"  [ml]       ml_irq={p['ml_irq']} ml_en={p['ml_en_w']} "
                    f"wf_state={p['wflash_state']} dbg_log0={p['dbg_logit0']} "
                    f"dbg_log1={p['dbg_logit1']} logit_reg0={p['logit0']} "
                    f"logit_reg1={p['logit1']}"
                )
                cocotb.log.info(
                    f"  [alarm]    cpu_alarm={p['cpu_alarm']} "
                    f"fsm_alarm_o={p['fsm_alarm_o']} pad={dut.alarm_o.value}"
                )
            else:
                try:
                    ts = u_top.test_status.value.to_unsigned()
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
                status = u_top.test_status.value.to_unsigned()
                if status == 0xDEAD_BEEF:
                    tc_raw = u_top.test_code.value
                    try:
                        code_str = f"0x{tc_raw.to_unsigned():08X}"
                    except ValueError:
                        code_str = f"X:{tc_raw!s}"
                    raise AssertionError(f"Firmware reported FAIL: test_code={code_str}")
            except ValueError:
                pass

        # Pass condition: alarm_o rose (output pad is always observable, even in GL)
        try:
            if int(dut.alarm_o.value) == 1:
                await ClockCycles(dut.clk_PAD, 10)
                if int(dut.alarm_o.value) == 1:
                    cocotb.log.info(f"alarm_o asserted at cycle {cycle} — test passed.")
                    return
        except ValueError:
            continue

    raise AssertionError(
        f"Timeout after {RUNTIME_TIMEOUT} cycles — alarm_o never asserted"
    )

@cocotb.test(skip=(hdl_toplevel != "chip_top_sim_wrap"))
async def test_chip_top_normal_full(dut):
    """Full pipeline: sensor → features → ML inference → alarm output."""
    logger = logging.getLogger("chip_top_full")

    # ALL mode: features + ML + CPU all active; bypasses SLEEP state in sim.
    await set_defaults(dut)
    #dut.input_PAD.value = 0b00100000 #0b00000101
    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)

    core  = _core(dut)
    u_top = _top(dut)

    BOOT_TIMEOUT    = 500_000
    RUNTIME_TIMEOUT = 500_000#3_000_000

    # --- Phase 1: wait for boot ---
    cocotb.log.info("Waiting for boot_done...")
    for cycle in range(BOOT_TIMEOUT):
        await RisingEdge(dut.clk_PAD)
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError("Timeout waiting for boot_done")

    assert core.pico_trap_w.value == 0, "CPU trapped during boot"

    cocotb.log.info("Boot done. Waiting for alarm_o...")
    await set_start(dut, 10)
    logger.info(f"[gl={bool(gl)}] start_i pulsed; entering main loop")
    # Start background monitor — prints features + stale logits on every feat_valid_o
    # Skip in GL mode: feat_valid_o and logit_reg_0 are RTL-only signals
    if not gl:
        cocotb.start_soon(_feat_monitor(u_top))
        cocotb.start_soon(_logit_monitor(dut.clk_PAD, u_top))
        cocotb.start_soon(_axi_write_monitor(dut.clk_PAD, u_top))
        cocotb.start_soon(_can_sleep_monitor(dut.clk_PAD, u_top, core))
    else:
        cocotb.start_soon(_gl_heartbeat(dut))

    # --- Phase 2: wait for alarm_o to assert (test passes on rising edge) ---
    # The firmware runs inferences and writes ALARM_CTRL=1 once the wake streak
    # threshold is hit; that drives the FSM to ALARM state which asserts alarm_o.
    # A firmware-side DEAD_BEEF in TEST_STATUS still fails fast.
    for cycle in range(RUNTIME_TIMEOUT):
        await RisingEdge(dut.clk_PAD)

<<<<<<< HEAD
        if cycle % 10_000 == 0:
=======
        if cycle % 100_000 == 0:
>>>>>>> a7a90025da03fa71b1d93924be9b9bc10babba6e
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
                    ts = u_top.test_status.value.to_unsigned()
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
                status = u_top.test_status.value.to_unsigned()
                if status == 0xDEAD_BEEF:
                    tc_raw = u_top.test_code.value
                    try:
                        code_str = f"0x{tc_raw.to_unsigned():08X}"
                    except ValueError:
                        code_str = f"X:{tc_raw!s}"
                    raise AssertionError(f"Firmware reported FAIL: test_code={code_str}")
            except ValueError:
                pass

        # Pass condition: alarm_o rose (output pad is always observable)
        try:
            if int(dut.alarm_o.value) == 1:
                await ClockCycles(dut.clk_PAD, 10)
                if int(dut.alarm_o.value) == 1:
                    cocotb.log.info(f"alarm_o asserted at cycle {cycle} — test passed.")
                    await ClockCycles(dut.clk_PAD, 1000)
                    await set_start(dut, 10)
                    await ClockCycles(dut.clk_PAD, 10)
                    await set_start(dut, 10)
                    await reset(dut.rst_n_PAD)
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
        pad_level = hdl_toplevel in {"chip_top", "chip_top_sim_wrap"}
        skip = {"dummy_top.sv", "soc_top.v"}
        if pad_level:
            skip.add("gf180mcu_fd_ip_sram__sram512x8m8wm1.v")
        sources += sorted(p for p in src_dir.glob("*.sv") if p.name not in skip)
        sources += sorted(p for p in src_dir.glob("*.v")  if p.name not in skip)
        sources.append(proj_path / "../ip/picorv32.v")

        # Simulation models
        sources.append(proj_path / "sim/tb/spi_flash_model.v")
        sources.append(proj_path / "sensors/i2c_slave_lis2dw12.sv")
        sources.append(proj_path / "sensors/i2c_slave_adpd144ri.sv")

        # Sim wrapper is only needed when it is the selected HDL toplevel.
        if hdl_toplevel == "chip_top_sim_wrap":
            sources.append(proj_path / "chip_top_sim_wrap.sv")

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
    runner.build(
        sources=sources,
        hdl_toplevel=hdl_toplevel,
        defines=defines,
        parameters=parameters,
        always=True,
        includes=includes,
        build_args=build_args,
        waves=True,
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
        waves=True,
    )


if __name__ == "__main__":
    chip_top_runner()
