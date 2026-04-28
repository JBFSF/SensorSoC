# SPDX-FileCopyrightText: © 2025 Project Template Contributors
# SPDX-License-Identifier: Apache-2.0

import os
import random
import logging
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import Timer, Edge, RisingEdge, FallingEdge, ClockCycles
from cocotb_tools.runner import get_runner

sim = os.getenv("SIM", "icarus")
pdk_root = os.getenv("PDK_ROOT", Path("~/.ciel").expanduser())
pdk = os.getenv("PDK", "gf180mcuD")
scl = os.getenv("SCL", "gf180mcu_fd_sc_mcu7t5v0")
gl = os.getenv("GL", False)
slot = os.getenv("SLOT", "1x1")
test_module = os.getenv("COCOTB_TEST_MODULE", "chip_top_tb")
toplevel = os.getenv("CHIP_TOPLEVEL", "chip_top")

hdl_toplevel = toplevel

async def set_defaults(dut):
    dut.input_PAD.value = 0
    dut.bidir_PAD.value = 0

async def enable_power(dut):
    dut.VDD.value = 1
    dut.VSS.value = 0

async def start_clock(clock, freq=50):
    """Start the clock @ freq MHz"""
    c = Clock(clock, 1 / freq * 1000, "ns")
    cocotb.start_soon(c.start())


async def reset(reset, active_low=True, time_ns=1000):
    """Reset dut"""
    cocotb.log.info("Reset asserted...")

    reset.value = not active_low
    await Timer(time_ns, "ns")
    reset.value = active_low

    cocotb.log.info("Reset deasserted.")


async def start_up(dut):
    """Startup sequence"""
    await set_defaults(dut)
    if gl:
        await enable_power(dut)
    await start_clock(dut.clk_PAD)
    await reset(dut.rst_n_PAD)


@cocotb.test()
async def test_chip_top_smoke(dut):
    """Basic chip-top smoke test: clock, reset, and normal-mode startup."""

    logger = logging.getLogger("chip_top_smoke")

    logger.info("Startup sequence...")
    await start_up(dut)

    # Keep the chip in normal mode and allow a few cycles for reset release.
    dut.input_PAD.value = 0
    await ClockCycles(dut.clk_PAD, 20)

    logger.info("Checking normal-mode wiring...")

    assert dut.rst_n_PAD.value == 1, "reset should be deasserted after startup"
    assert dut.i_chip_core.test_mode_w.value.integer == 0, "chip should remain in normal mode"
    assert dut.i_chip_core.core_clk_w.value == dut.i_chip_core.clk.value, \
        "normal mode should use the onboard clock"
    assert dut.i_chip_core.bidir_oe.value[22:7].integer == 0, \
        "debug bus should be disabled in normal mode"

    logger.info("Smoke test passed.")


def chip_top_runner():

    proj_path = Path(__file__).resolve().parent

    sources = []
    defines = {f"SLOT_{slot.upper()}": True}
    includes = [proj_path / "../src/"]

    if gl:
        # SCL models
        sources.append(Path(pdk_root) / pdk / "libs.ref" / scl / "verilog" / f"{scl}.v")
        sources.append(Path(pdk_root) / pdk / "libs.ref" / scl / "verilog" / "primitives.v")

        # We use the powered netlist
        sources.append(proj_path / f"../final/pnl/{hdl_toplevel}.pnl.v")

        defines = {"FUNCTIONAL": True, "USE_POWER_PINS": True}
    else:
        # sources.append(proj_path / "../src/chip_top.sv")
        # sources.append(proj_path / "../src/chip_core.sv")
        src_dir = proj_path / "../src"
        
        skip = {
            "gf180mcu_fd_ip_sram__sram512x8m8wm1.v",
            "dummy_top.sv",
            "soc_top.v",
        }
        sources += sorted(p for p in src_dir.glob("*.sv") if p.name not in skip)
        sources += sorted(p for p in src_dir.glob("*.v") if p.name not in skip)
        sources.append(proj_path / "../ip/picorv32.v")
        
    if hdl_toplevel == "chip_top":
        sources += [
            # IO pad models
            Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_fd_io.v",
            Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_ws_io.v",
            
            # SRAM macros
            Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_ip_sram/verilog/gf180mcu_fd_ip_sram__sram512x8m8wm1.v",
            
            # Custom IP
            proj_path / "../ip/gf180mcu_ws_ip__id/vh/gf180mcu_ws_ip__id.v",
            proj_path / "../ip/gf180mcu_ws_ip__logo/vh/gf180mcu_ws_ip__logo.v",
        ]

    build_args = []

    if sim == "icarus":
        # For debugging
        # build_args = ["-Winfloop", "-pfileline=1"]
        pass

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

    plusargs = []

    runner.test(
        hdl_toplevel=hdl_toplevel,
        test_module=test_module,
        plusargs=plusargs,
        waves=True,
    )


if __name__ == "__main__":
    chip_top_runner()
