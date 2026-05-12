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


_PROJ = Path(__file__).resolve().parent
_FIRMWARE_HEX = str(
    _PROJ / "firmware/build/test_top_feature_ml_cpu_spi_flash/firmware.hex"
)
_WEIGHT_HEX = str(_PROJ / "firmware/build/generated/taketwo_params.hex")


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


def _core(dut):
    """Return the chip_core handle regardless of toplevel."""
    if hdl_toplevel == "chip_top_sim_wrap":
        return dut.u_chip_top.i_chip_core
    return dut.i_chip_core 


def _top(dut):
    """Return the top handle (inside chip_core)."""
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
    dut.input_PAD.value = 0b00000101
    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)

    core  = _core(dut)
    u_top = _top(dut)

    TIMEOUT_CYCLES = 500_000
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
    logger.info("Boot done. Waiting for firmware to signal pass/fail...")

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
            logit_word0 = _u32_or_none(u_top.u_weight_ram.logit_reg_0)
            logit_word1 = _u32_or_none(u_top.u_weight_ram.logit_reg_1)

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
                    f"word0={u_top.u_weight_ram.logit_reg_0.value} "
                    f"word1={u_top.u_weight_ram.logit_reg_1.value}"
                )

            logger.info("Full pipeline test passed.")
            return

    raise AssertionError(
        f"Timeout after {RUNTIME_TIMEOUT} cycles — "
        f"firmware never reached pass/fail state"
    )



def chip_top_runner():
    proj_path = Path(__file__).resolve().parent

    sources = []
    # Compile with SIM define so the sim bus and sensor models are active.
    defines = {f"SLOT_{slot.upper().replace('.', 'P')}": True, "SIM": True}
    includes = [proj_path / "../src/"]

    if gl:
        sources.append(Path(pdk_root) / pdk / "libs.ref" / scl / "verilog" / f"{scl}.v")
        sources.append(Path(pdk_root) / pdk / "libs.ref" / scl / "verilog" / "primitives.v")
        sources.append(proj_path / f"../final/pnl/{hdl_toplevel}.pnl.v")
        defines = {"FUNCTIONAL": True, "USE_POWER_PINS": True}
    else:
        src_dir = proj_path / "../src"
        skip = {"gf180mcu_fd_ip_sram__sram512x8m8wm1.v", "dummy_top.sv", "soc_top.v"}
        sources += sorted(p for p in src_dir.glob("*.sv") if p.name not in skip)
        sources += sorted(p for p in src_dir.glob("*.v")  if p.name not in skip)
        sources.append(proj_path / "../ip/picorv32.v")

        # Simulation models
        sources.append(proj_path / "sim/tb/spi_flash_model.v")
        sources.append(proj_path / "sensors/i2c_slave_lis2dw12.sv")
        sources.append(proj_path / "sensors/i2c_slave_adpd144ri.sv")

        # Sim wrapper (HDL toplevel for full tests; ignored when hdl_toplevel=chip_top)
        sources.append(proj_path / "sim/tb/chip_top_sim_wrap.sv")

        # Always include pad and SRAM models (needed by chip_top inside the wrapper)
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

    runner = get_runner(sim)
    runner.build(
        sources=sources,
        hdl_toplevel=hdl_toplevel,
        defines=defines,
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
