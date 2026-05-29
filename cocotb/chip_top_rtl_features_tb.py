# SPDX-FileCopyrightText: © 2025 Project Template Contributors
# SPDX-License-Identifier: Apache-2.0
#
# Standalone testbench for capturing RTL feature vectors to CSV.
# Run with: COCOTB_TEST_MODULE=chip_top_rtl_features_tb FIRMWARE_NAME=test_top_feature_ml_30logits

import csv
import os
import logging
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import Timer, RisingEdge, ClockCycles
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
test_module = os.getenv("COCOTB_TEST_MODULE", "chip_top_rtl_features_tb")

hdl_toplevel     = os.getenv("CHIP_TOPLEVEL", "chip_top_sim_wrap")
chip_netlist_top = os.getenv("CHIP_NETLIST_TOP", "chip_top")

_PROJ = Path(__file__).resolve().parent
_FIRMWARE_NAME = os.getenv("FIRMWARE_NAME", "test_top_feature_ml_30logits")
_FIRMWARE_HEX = str(_PROJ / "firmware" / "build" / _FIRMWARE_NAME / "firmware.hex")
_WEIGHT_HEX   = str(_PROJ / "firmware" / "build" / "generated" / "taketwo_params.hex")


def _s16(word: int) -> int:
    word &= 0xFFFF
    return word - 0x10000 if word & 0x8000 else word


def _s16_or_none(handle):
    try:
        return _s16(int(handle.value))
    except ValueError:
        return None


async def _set_defaults(dut):
    dut.input_PAD.value = 0


async def _start_clock(clock, freq_mhz: float = 50.0):
    period_ns = 1_000.0 / freq_mhz
    c = Clock(clock, period_ns, "ns")
    cocotb.start_soon(c.start())


async def _reset(rst_n, active_low=True, time_ns=1000):
    rst_n.value = not active_low
    await Timer(time_ns, "ns")
    rst_n.value = active_low


class _FlatGL:
    def __init__(self, scope, prefix):
        object.__setattr__(self, "_scope", scope)
        object.__setattr__(self, "_prefix", prefix)

    def __getattr__(self, name):
        scope  = object.__getattribute__(self, "_scope")
        prefix = object.__getattribute__(self, "_prefix")
        for escaped in (f"\\{prefix}.{name} ", f"\\{prefix}.{name}"):
            try:
                return scope._id(escaped, extended=False)
            except AttributeError:
                pass
        raise AttributeError(f"{scope._path} has no flat GL net for '{prefix}.{name}'")


def _core(dut):
    if hdl_toplevel == "chip_top_sim_wrap":
        if gl:
            return _FlatGL(dut.u_chip_top, "i_chip_core")
        return dut.u_chip_top.i_chip_core
    return dut.i_chip_core


def _top(dut):
    if gl:
        return _FlatGL(dut.u_chip_top, "i_chip_core.u_top")
    return _core(dut).u_top


async def _feat_monitor(u_top, csv_writer=None, csv_file=None):
    """Background coroutine: captures features on every feat_valid_o, writes to CSV if provided."""
    count = 0
    prev_feat = None
    while True:
        await RisingEdge(u_top.feat_valid_o)
        count += 1

        mot = _s16_or_none(u_top.feat_motion_latched_r)
        tim = _s16_or_none(u_top.feat_time_latched_r)
        dhr = _s16_or_none(u_top.feat_delta_hr_latched_r)
        msd = _s16_or_none(u_top.feat_mssd_latched_r)
        curr_feat = (mot, tim, dhr, msd)
        if curr_feat != prev_feat:
            print(
                f"[feat {count}]  mot={mot!s:>7}  tim={tim!s:>6}  "
                f"dhr={dhr!s:>7}  msd={msd!s:>7}",
                flush=True,
            )
            prev_feat = curr_feat

        if csv_writer is not None and None not in (mot, tim, dhr, msd):
            csv_writer.writerow([count, tim, mot, dhr, msd])
            csv_file.flush()


@cocotb.test(skip=(hdl_toplevel != "chip_top_sim_wrap"))
async def test_chip_top_feature_inject(dut):
    """Full pipeline: sensor → features → 30 ML inferences → write RTL features to CSV."""
    logger = logging.getLogger("chip_top_feature_inject")

    await _set_defaults(dut)
    dut.input_PAD.value = 0b00000101
    await _start_clock(dut.clk_PAD)
    await _reset(dut.rst_n_PAD)
    core  = _core(dut)
    u_top = _top(dut)
    BOOT_TIMEOUT    = 500_000
    RUNTIME_TIMEOUT = 10_000_000

    logger.info("Waiting for boot_done...")
    for cycle in range(BOOT_TIMEOUT):
        await RisingEdge(dut.clk_PAD)
        if u_top.boot_done.value == 1:
            break
    else:
        raise AssertionError("Timeout waiting for boot_done")

    assert core.pico_trap_w.value == 0, "CPU trapped during boot"
    logger.info("Boot done. Running feature pipeline...")

    _csv_path = Path(__file__).parent / "sim" / "data" / "rtl_features.csv"
    _csv_path.parent.mkdir(parents=True, exist_ok=True)
    _csv_file = open(_csv_path, "w", newline="")
    _csv_writer = csv.writer(_csv_file)
    _csv_writer.writerow(["sample", "time_feat", "motion_feat", "delta_hr_feat", "mssd_feat"])
    logger.info(f"Writing RTL features to {_csv_path}")

    cocotb.start_soon(_feat_monitor(u_top, _csv_writer, _csv_file))

    last_status = 0
    for cycle in range(RUNTIME_TIMEOUT):
        await RisingEdge(dut.clk_PAD)

        if core.pico_trap_w.value == 1:
            _csv_file.close()
            raise AssertionError(f"CPU trapped at cycle {cycle}")

        try:
            status = u_top.test_status.value.to_unsigned()
        except Exception:
            continue

        if status == 0xDEAD_BEEF:
            _csv_file.close()
            try:
                code_str = f"0x{u_top.test_code.value.to_unsigned():08X}"
            except Exception:
                code_str = str(u_top.test_code.value)
            raise AssertionError(f"Firmware reported FAIL: test_code={code_str}")

        if status != last_status:
            last_status = status
            if status == 0xCAFE_BABE:
                _csv_file.close()
                logger.info(f"Full pipeline PASS — RTL features written to {_csv_path}")
                return

    _csv_file.close()
    raise AssertionError(f"Timeout after {RUNTIME_TIMEOUT} cycles")


def chip_top_runner():
    proj_path = Path(__file__).resolve().parent

    sources = []
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
        sources.append(proj_path / "sim/tb/spi_flash_model.v")
        sources.append(proj_path / "sensors/i2c_slave_lis2dw12.sv")
        sources.append(proj_path / "sensors/i2c_slave_adpd144ri.sv")
        if hdl_toplevel == "chip_top_sim_wrap":
            sources.append(proj_path / "chip_top_sim_wrap.sv")
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
