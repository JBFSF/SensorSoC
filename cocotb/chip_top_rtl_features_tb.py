# SPDX-FileCopyrightText: © 2025 Project Template Contributors
# SPDX-License-Identifier: Apache-2.0
#
# Generates RTL feature vectors to cocotb/sim/data/rtl_features.csv.
#
# Uses test_mode[3:0] = 4'b0001 on input_PAD[3:0], which the FSM interprets as
# a hard override into FEAT_ONLY every cycle — no SPI boot, no CPU, no weights.
# The feature engine runs autonomously via the sensor sim bus.

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
slot       = os.getenv("SLOT", "1x1")
test_module = os.getenv("COCOTB_TEST_MODULE", "chip_top_rtl_features_tb")

_GL_SENSOR_BRIDGE = "sim_chip_top_gl_sensor_bridge_env"
hdl_toplevel      = os.getenv("CHIP_TOPLEVEL", "chip_top_sim_wrap")

_PROJ         = Path(__file__).resolve().parent
_FIRMWARE_HEX = str(_PROJ / "firmware" / "build" / "test_top_normal" / "firmware.hex")
_WEIGHT_HEX   = str(_PROJ / "firmware" / "build" / "generated" / "taketwo_params.hex")

# Number of feature vectors to capture before stopping (env override: N_FEAT_SAMPLES)
_N_SAMPLES = int(os.getenv("N_FEAT_SAMPLES", "100"))


def _s16(word: int) -> int:
    word &= 0xFFFF
    return word - 0x10000 if word & 0x8000 else word


def _s16_or_none(handle):
    try:
        return _s16(int(handle.value))
    except ValueError:
        return None


def _clk_handle(dut):
    return dut.clk_drv if hdl_toplevel == _GL_SENSOR_BRIDGE else dut.clk_PAD


def _rst_handle(dut):
    return dut.rst_n_drv if hdl_toplevel == _GL_SENSOR_BRIDGE else dut.rst_n_PAD


def _input_handle(dut):
    return dut.input_drv if hdl_toplevel == _GL_SENSOR_BRIDGE else dut.input_PAD


def _top(dut):
    if hdl_toplevel == _GL_SENSOR_BRIDGE:
        return dut.u_chip.i_chip_core.u_top
    if hdl_toplevel == "chip_top_sim_wrap":
        return dut.u_chip_top.i_chip_core.u_top
    return dut.i_chip_core.u_top


@cocotb.test(skip=(hdl_toplevel not in {"chip_top_sim_wrap", _GL_SENSOR_BRIDGE}))
async def test_capture_features(dut):
    """
    Run feature engine in FEAT_ONLY override mode and write feature vectors to CSV.

    test_mode[3:0] = 0b0001 forces the FSM into FEAT_ONLY every cycle, bypassing
    the normal BOOT → IDLE → SLEEP → FEAT_ONLY path and the SPI boot sequence.
    The CPU and ML subsystems are off; the feature engine runs with the sensor
    simulation models.
    """
    logger = logging.getLogger("capture_features")
    clk = _clk_handle(dut)

    # test_mode = 0b0001 forces FSM → FEAT_ONLY; hold it through reset and run
    _input_handle(dut).value = 0b0001
    cocotb.start_soon(Clock(clk, 20, "ns").start())  # 50 MHz
    _rst_handle(dut).value = 0
    await Timer(1000, "ns")
    _rst_handle(dut).value = 1

    u_top = _top(dut)

    _csv_path = _PROJ / "sim" / "data" / "rtl_features.csv"
    _csv_path.parent.mkdir(parents=True, exist_ok=True)

    logger.info(f"Collecting {_N_SAMPLES} feature vectors into {_csv_path}")

    collected = 0
    CYCLE_TIMEOUT = _N_SAMPLES * 20_000  # generous headroom per feature

    with open(_csv_path, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["sample", "time_feat", "motion_feat", "delta_hr_feat", "mssd_feat"])

        for cycle in range(CYCLE_TIMEOUT):
            await RisingEdge(clk)

            try:
                if u_top.feat_valid_o.value != 1:
                    continue
            except Exception:
                continue

            mot = _s16_or_none(u_top.feat_motion_latched_r)
            tim = _s16_or_none(u_top.feat_time_latched_r)
            dhr = _s16_or_none(u_top.feat_delta_hr_latched_r)
            msd = _s16_or_none(u_top.feat_mssd_latched_r)
            print(tim, mot, dhr, msd)
            if None in (mot, tim, dhr, msd):
                continue

            collected += 1
            writer.writerow([ tim, mot, dhr, msd])
            f.flush()
            logger.info(
                f"[{collected}/{_N_SAMPLES}] mot={mot:>7}  tim={tim:>6}  "
                f"dhr={dhr:>7}  msd={msd:>7}"
            )

            if collected >= _N_SAMPLES:
                logger.info(f"Done — {collected} features written to {_csv_path}")
                return

    raise AssertionError(
        f"Timeout: only {collected}/{_N_SAMPLES} features captured in {CYCLE_TIMEOUT} cycles"
    )


def chip_top_runner():
    proj_path = Path(__file__).resolve().parent
    src_dir   = proj_path / "../src"

    skip = {"dummy_top.sv", "soc_top.v", "gf180mcu_fd_ip_sram__sram512x8m8wm1.v"}
    netlist_suffixes = (".nl.v", ".pnl.v")

    sources  = sorted(p for p in src_dir.glob("*.sv") if p.name not in skip)
    sources += sorted(
        p for p in src_dir.glob("*.v")
        if p.name not in skip and not p.name.endswith(netlist_suffixes)
    )
    sources += [
        proj_path / "../ip/picorv32.v",
        proj_path / "sim/tb/spi_flash_model.v",
        proj_path / "sensors/i2c_slave_lis2dw12.sv",
        proj_path / "sensors/i2c_slave_adpd144ri.sv",
    ]

    if hdl_toplevel == "chip_top_sim_wrap":
        sources.append(proj_path / "chip_top_sim_wrap.sv")
    else:
        sources.append(proj_path / "sim/tb" / f"{_GL_SENSOR_BRIDGE}.sv")

    sources += [
        Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_fd_io.v",
        Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_io/verilog/gf180mcu_ws_io.v",
        Path(pdk_root) / pdk / "libs.ref/gf180mcu_fd_ip_sram/verilog/gf180mcu_fd_ip_sram__sram512x8m8wm1.v",
        proj_path / "../ip/gf180mcu_ws_ip__id/vh/gf180mcu_ws_ip__id.v",
        proj_path / "../ip/gf180mcu_ws_ip__logo/vh/gf180mcu_ws_ip__logo.v",
    ]

    runner = get_runner(sim)
    runner.build(
        sources=sources,
        hdl_toplevel=hdl_toplevel,
        defines={f"SLOT_{slot.upper().replace('.', 'P')}": True, "SIM": True},
        always=True,
        includes=[proj_path / "../src/"],
        waves=True,
    )
    runner.test(
        hdl_toplevel=hdl_toplevel,
        test_module=test_module,
        plusargs=[
            f"+FIRMWARE_HEX={_FIRMWARE_HEX}",
            f"+WEIGHT_HEX={_WEIGHT_HEX}",
            f"+DATA_DIR={proj_path}/sim/data",
        ],
        waves=True,
    )


if __name__ == "__main__":
    chip_top_runner()
