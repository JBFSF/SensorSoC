# SPDX-FileCopyrightText: © 2025 Project Template Contributors
# SPDX-License-Identifier: Apache-2.0

import os
import logging
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import Timer, RisingEdge, ClockCycles, ReadOnly
from cocotb_tools.runner import get_runner

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
_FIRMWARE_NAME = os.getenv("FIRMWARE_NAME", "test_top_feature_ml_30logits")
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

async def set_defaults(dut):
    dut.input_PAD.value = 0


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


def _core(dut):
    """Return the chip_core handle regardless of toplevel."""
    if hdl_toplevel == "chip_top_sim_wrap":
        if gl:
            return _FlatGL(dut.u_chip_top, "i_chip_core")
        return dut.u_chip_top.i_chip_core
    return dut.i_chip_core


def _top(dut):
    """Return the top handle (inside chip_core)."""
    if gl:
        return _FlatGL(dut.u_chip_top, "i_chip_core.u_top")
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
    assert core.test_mode_w.value.integer == 0, "chip should be in normal mode"
    assert core.core_clk_w.value == core.clk.value, \
        "normal mode should use the onboard clock"
    assert core.bidir_oe.value[22:7].integer == 0, \
        "debug bus OE should be 0 in normal mode"

    logger.info("Smoke test passed.")


#boot test

@cocotb.test(skip=(hdl_toplevel != "chip_top_sim_wrap"))
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

    TIMEOUT_CYCLES = 1#500_000
    logger.info("Waiting for boot_done...")

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

_N_LOGITS = 10  # number of inferences firmware runs before writing CAFEBABE


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


async def _logit_monitor(clk, u_top):
    """Background coroutine: prints logit_reg_0 every time it changes.
    logit_reg_0 packs both logits: bits[15:0]=log0, bits[31:16]=log1.
    """
    # One-shot probe so we can see *why* the handle lookup fails if it does
    try:
        handle = u_top.u_weight_flash.logit_reg_0
        print(f"[logit_monitor] handle resolved: {handle}", flush=True)
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


@cocotb.test(skip=(hdl_toplevel != "chip_top_sim_wrap"))
async def test_chip_top_feature_inject(dut):
    """Full pipeline: sensor → features → ML inference → alarm output."""
    logger = logging.getLogger("chip_top_feature_inject")

    # ALL mode: features + ML + CPU all active; bypasses SLEEP state in sim.
    await set_defaults(dut)
    dut.input_PAD.value = 0b00000101
    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)

    core  = _core(dut)
    u_top = _top(dut)

    BOOT_TIMEOUT    = 500_000
    RUNTIME_TIMEOUT = 10_000_000

    # --- Phase 1: wait for boot ---
    logger.info("Waiting for boot_done...")
    for cycle in range(BOOT_TIMEOUT):
        await RisingEdge(dut.clk_PAD)
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError("Timeout waiting for boot_done")

    assert core.pico_trap_w.value == 0, "CPU trapped during boot"

    logger.info("Boot done. Waiting for 30 logits...")

    # Start background monitor — prints features + stale logits on every feat_valid_o
    cocotb.start_soon(_feat_monitor(u_top))
    cocotb.start_soon(_logit_monitor(dut.clk_PAD, u_top))

    # --- Phase 2: collect 30 logits as firmware writes them ---
    # Firmware writes TEST_STATUS = 1..30 (one per inference), then 0xCAFEBABE.
    # TEST_CODE = packed logits: bits[15:0]=log0, bits[31:16]=log1.
    last_status = 0
    logit_count = 0

    # --- Phase 2: wait for firmware test_status (CAFE_BABE = pass, DEAD_BEEF = fail) ---
    for cycle in range(RUNTIME_TIMEOUT):
        await RisingEdge(dut.clk_PAD)

        if cycle % 100_000 == 0:
            try:
                ts = u_top.test_status.value.to_unsigned()
                tc_raw = u_top.test_code.value
                tc_str = str(tc_raw)
                alarm = dut.alarm_o.value
                try:
                    tc_int = tc_raw.to_unsigned()
                    tc_display = f"0x{tc_int:08X}"
                except ValueError:
                    tc_display = f"X:{tc_str}"
                logger.info(
                    f"  cycle {cycle}: test_status=0x{ts:08X} "
                    f"test_code={tc_display} alarm={alarm}"
                )
            except Exception:
                pass

        if core.pico_trap_w.value == 1:
            raise AssertionError("CPU trapped during runtime")

        try:
            status = u_top.test_status.value.to_unsigned()
        except Exception:
            continue

        if status == 0xDEAD_BEEF:
            tc_raw = u_top.test_code.value
            try:
                code = tc_raw.to_unsigned()
                code_str = f"0x{code:08X}"
            except ValueError:
                code_str = f"X:{tc_raw!s}"
            raise AssertionError(f"Firmware reported FAIL: test_code={code_str}")

        if status == 0xCAFE_BABE:
            tc_raw = u_top.test_code.value
            try:
                code = tc_raw.to_unsigned()
                code_str = f"0x{code:08X}"
            except ValueError:
                code = None
                code_str = f"X:{tc_raw!s}"
            logger.info(
                f"Firmware reported PASS: test_code={code_str} "
                f"alarm={dut.alarm_o.value}"
            )

            # Check bits 30 and 29 by position in binary string (MSB first).
            # This handles X bits in other positions (e.g., the confidence field).
            binstr = str(tc_raw)  # 32-char string: '0'/'1'/'X'/'Z', MSB at [0]
            bit30 = binstr[1]     # bit 30 = outputs_mutated
            bit29 = binstr[2]     # bit 29 = saw_busy
            assert bit30 == "1", \
                f"Firmware: ML output mutation not observed (bit30={bit30}, test_code={code_str})"
            assert bit29 == "1", \
                f"Firmware: ML BUSY high not observed (bit29={bit29}, test_code={code_str})"

            if code is not None:
                logger.info(
                    f"  predicted_class={code >> 31} "
                    f"outputs_mutated={(code >> 30) & 1} "
                    f"saw_busy={(code >> 29) & 1} "
                    f"confidence={code & 0xFFFF}"
                )
            else:
                logger.warning(
                    f"test_code has X bits — confidence field indeterminate. "
                    f"Raw: {code_str}. Check logit WRAM region for X propagation."
                )
            await ClockCycles(dut.clk_PAD, 4)
            await ReadOnly()

            dbg_log0 = _s16_or_none(u_top.logit0)
            dbg_log1 = _s16_or_none(u_top.logit1)
            logit_word0 = _u32_or_none(u_top.u_weight_flash.logit_reg_0)
            logit_word1 = _u32_or_none(u_top.u_weight_flash.logit_reg_1)

            if dbg_log0 is not None and dbg_log1 is not None:
                logger.info(f"  logits_dbg=({dbg_log0}, {dbg_log1})")
            else:
                logger.warning(
                    f"top-level dbg logits unresolved: "
                    f"logit0={u_top.logit0.value} logit1={u_top.logit1.value}"
                )

            if logit_word0 is not None:
                reg_log0 = _s16(logit_word0)
                reg_log1 = _s16(logit_word0 >> 16)
                aux_word = "X" if logit_word1 is None else f"0x{logit_word1:08X}"
                logger.info(
                    f"  logits_reg=({reg_log0}, {reg_log1}) "
                    f"word0=0x{logit_word0:08X} word1={aux_word}"
                )
            else:
                logger.warning(
                    f"logit register window unresolved: "
                    f"word0={u_top.u_weight_flash.logit_reg_0.value} "
                    f"word1={u_top.u_weight_flash.logit_reg_1.value}"
                )

            logger.info("Full pipeline test passed.")
            return

    raise AssertionError(
        f"Timeout after {RUNTIME_TIMEOUT} cycles — "
        f"firmware never reached pass/fail state"
    )


# Normal mode test with custom firmware

# FSM state names for logging
_FSM_STATES = {
    0: "BOOT",
    1: "IDLE",
    2: "SLEEP",
    3: "FEAT_ONLY",
    4: "ALL",
    5: "CPU_FEAT",
    6: "FEAT_ML",
    7: "CPU_ONLY",
}


@cocotb.test(skip=(hdl_toplevel != "chip_top_sim_wrap"))
async def test_chip_top_normal_mode(dut):
    """Normal mode test: run chip normally, monitor CPU errors, FSM state, and alarm outputs."""
    logger = logging.getLogger("chip_top_normal_mode")

    # Normal mode (input_PAD = 0)
    await set_defaults(dut)
    dut.input_PAD.value = 0
    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)

    core  = _core(dut)
    u_top = _top(dut)

    BOOT_TIMEOUT    = 1#500_000
    RUNTIME_TIMEOUT = 1#10_000_000

    logger.info("Normal mode test started. Monitoring for boot completion...")

    # --- Phase 1: wait for boot ---
    for cycle in range(BOOT_TIMEOUT):
        await RisingEdge(dut.clk_PAD)
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError("Timeout waiting for boot_done")

    if core.pico_trap_w.value == 1:
        raise AssertionError("CPU trapped during boot")

    logger.info("Boot complete. Running in normal mode...")

    # --- Phase 2: monitor CPU errors, FSM state, and alarm ---
    last_alarm = 0
    last_fsm_state = None
    RUNTIME_TIMEOUT = 300_000
    for cycle in range(RUNTIME_TIMEOUT):
        await RisingEdge(dut.clk_PAD)

        # Check for CPU trap/error
        if core.pico_trap_w.value == 1:
            raise AssertionError(f"CPU trap detected at cycle {cycle}")

        # Check FSM state for changes
        try:
            current_fsm_state = int(u_top.fsm.state_q.value)
            if current_fsm_state != last_fsm_state:
                state_name = _FSM_STATES.get(current_fsm_state, f"UNKNOWN({current_fsm_state})")
                logger.info(f"  cycle {cycle}: FSM state changed to {state_name}")
                last_fsm_state = current_fsm_state
        except (AttributeError, ValueError, TypeError):
            pass

        # Check alarm output for changes
        current_alarm = dut.alarm_o.value
        if current_alarm != last_alarm:
            logger.info(f"  cycle {cycle}: alarm changed to {current_alarm}")
            last_alarm = current_alarm
            if int(current_alarm) == 1:
                logger.info("Alarm asserted — test passed.")
                return

        # Log periodic status
        if cycle % 100_000 == 0:
            fsm_state_name = "?"
            try:
                fsm_state = int(u_top.fsm.state_q.value)
                fsm_state_name = _FSM_STATES.get(fsm_state, f"UNKNOWN({fsm_state})")
            except (AttributeError, ValueError, TypeError):
                pass
            logger.info(f"  cycle {cycle}: FSM={fsm_state_name} trap={core.pico_trap_w.value} alarm={dut.alarm_o.value}")

    logger.info("Normal mode test completed — alarm never fired within timeout.")


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
            raise FileNotFoundError(
                f"gate-level netlist not found: {netlist}. "
                "Set FINAL_DIR=<run>/final or CHIP_NETLIST_TOP if the netlist top is not chip_top."
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
