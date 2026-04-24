from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, ReadOnly, RisingEdge, Timer

from ref_pipeline.pipeline_ref import PipelineReference, PipelineStepInputs, TopPipelineConfig
from ref_pipeline.test_helpers import sig_s, sig_u
from ref_pipeline.trace_loader import load_accel_trace, load_ppg_trace


ROOT = Path(__file__).resolve().parents[3]
SIM_DATA = ROOT / "cocotb" / "sim" / "data"


MODE_TO_NAME = {
    0x1: "mssd",
    0x2: "delta_hr",
    0x3: "time",
    0x4: "motion",
}


async def reset_dut(dut) -> None:
    dut.mode_sel.value = 0
    dut.stim_override_en.value = 0
    dut.stim_mssd.value = 0
    dut.stim_delta_hr.value = 0
    dut.stim_time.value = 0
    dut.stim_motion.value = 0
    dut.rst_n.value = 0
    await ClockCycles(dut.clk, 5)
    dut.rst_n.value = 1
    await ClockCycles(dut.clk, 2)


async def settle_debug_bus(dut) -> None:
    await Timer(1, unit="ns")


def collect_real_pipeline_inputs(dut, rst: bool) -> PipelineStepInputs:
    return PipelineStepInputs(
        rst=rst,
        accel_valid=bool(int(dut.accel_valid_w.value)),
        ax=sig_s(dut.ax_w),
        ay=sig_s(dut.ay_w),
        az=sig_s(dut.az_w),
        ppg_valid=bool(int(dut.ppg_sample_valid_w.value)),
        ppg_sample=sig_u(dut.ppg_sample_w),
        ppg_sample_time=sig_u(dut.ppg_sample_time_w),
        beat_pulse=bool(int(dut.beat_pulse_w.value)),
        beat_quality=sig_u(dut.beat_quality_w),
        double_beat=bool(int(dut.double_beat_w.value)),
        missed_beat=bool(int(dut.missed_beat_w.value)),
        rr_valid=bool(int(dut.rr_valid_w.value)),
        rr_accepted=bool(int(dut.rr_accepted_w.value)),
        rr_interval=sig_u(dut.rr_interval_w),
        delta_hr=sig_s(dut.delta_hr_w),
        motion_epoch=bool(int(dut.motion_epoch_w.value)),
        motion_energy=sig_u(dut.motion_energy_w),
        mssd_valid=bool(int(dut.mssd_valid_w.value)),
        mssd_epoch=sig_u(dut.mssd_w),
        fifo_overflow_event=bool(int(dut.fifo_overflow_event_w.value)),
        ppg_i2c_err_event=bool(int(dut.ppg_i2c_err_event_w.value)),
        epoch_end=bool(int(dut.epoch_end_w.value)),
        epoch_end_d=bool(int(dut.epoch_end_d.value)),
        time_value=sig_u(dut.seconds_w),
        ml_update_gate=bool(int(dut.ml_update_gate_o.value)),
    )


def set_feature_patterns(dut, *, mssd: int, delta_hr: int, time: int, motion: int) -> None:
    dut.stim_mssd.value = mssd & 0xFFFF
    dut.stim_delta_hr.value = delta_hr & 0xFFFF
    dut.stim_time.value = time & 0xFFFF
    dut.stim_motion.value = motion & 0xFFFF


def set_feature_patterns_by_mode(dut, patterns: dict[int, int]) -> None:
    set_feature_patterns(
        dut,
        mssd=patterns[0x1],
        delta_hr=patterns[0x2],
        time=patterns[0x3],
        motion=patterns[0x4],
    )


async def expect_debug_mode(dut, mode: int, expected: int) -> None:
    dut.mode_sel.value = mode
    await settle_debug_bus(dut)

    got_bus = dut.debug_bus.value.to_unsigned()
    got_oe = dut.debug_oe.value.to_unsigned()
    assert got_oe == 0xFFFF, (
        f"mode {mode} should enable all debug bus outputs, got 0x{got_oe:04x}"
    )
    assert got_bus == (expected & 0xFFFF), (
        f"mode {mode} selected {MODE_TO_NAME[mode]} but drove 0x{got_bus:04x}, expected 0x{expected & 0xFFFF:04x}"
    )


@cocotb.test()
async def test_chip_core_debug_modes_mux_features_onto_debug_bus(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    feature_patterns = {
        0x1: 0x1357,
        0x2: 0x2468,
        0x3: 0xA55A,
        0x4: 0xDEAD,
    }
    set_feature_patterns_by_mode(dut, feature_patterns)
    dut.stim_override_en.value = 1
    await ClockCycles(dut.clk, 1)

    dut.mode_sel.value = 0x0
    await settle_debug_bus(dut)
    got_oe = dut.debug_oe.value.to_unsigned()
    got_bus = dut.debug_bus.value.to_unsigned()
    assert got_oe == 0x0000, (
        f"debug OE should be disabled in mode 0, got 0x{got_oe:04x}"
    )
    assert got_bus == 0x0000, (
        f"debug bus should idle low in mode 0, got 0x{got_bus:04x}"
    )

    for mode, expected in feature_patterns.items():
        dut.mode_sel.value = mode
        await settle_debug_bus(dut)

        got_bus = dut.debug_bus.value.to_unsigned()
        got_oe = dut.debug_oe.value.to_unsigned()
        dut._log.info(
            "mode=%d (%s) debug_bus=0x%04x debug_oe=0x%04x",
            mode,
            MODE_TO_NAME[mode],
            got_bus,
            got_oe,
        )

        assert got_oe == 0xFFFF, (
            f"mode {mode} should enable all debug bus outputs, got 0x{got_oe:04x}"
        )
        assert got_bus == expected, (
            f"mode {mode} selected {MODE_TO_NAME[mode]} but drove 0x{got_bus:04x}, expected 0x{expected:04x}"
        )

        for other_mode, other_value in feature_patterns.items():
            if other_mode == mode:
                continue
            assert got_bus != other_value, (
                f"mode {mode} leaked {MODE_TO_NAME[other_mode]} value 0x{other_value:04x} onto debug bus"
            )

    switch_sequence = [0x4, 0x2, 0x3, 0x1, 0x4]
    for mode in switch_sequence:
        dut.mode_sel.value = mode
        await settle_debug_bus(dut)
        got_bus = dut.debug_bus.value.to_unsigned()
        expected = feature_patterns[mode]
        assert got_bus == expected, (
            f"back-to-back mode switch to {mode} failed: got 0x{got_bus:04x}, expected 0x{expected:04x}"
        )

    dut.stim_override_en.value = 0
    dut.mode_sel.value = 0
    await ClockCycles(dut.clk, 1)


@cocotb.test()
async def test_chip_core_debug_modes_track_selected_feature_only(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    patterns = {
        0x1: 0x0001,
        0x2: 0x0010,
        0x3: 0x0100,
        0x4: 0x1000,
    }
    set_feature_patterns_by_mode(dut, patterns)
    dut.stim_override_en.value = 1
    await ClockCycles(dut.clk, 1)

    updates = {
        0x1: (0xF00D, {0x2: 0x2222, 0x3: 0x3333, 0x4: 0x4444}),
        0x2: (0x8001, {0x1: 0x1111, 0x3: 0x3333, 0x4: 0x4444}),
        0x3: (0x7FFE, {0x1: 0x1111, 0x2: 0x2222, 0x4: 0x4444}),
        0x4: (0xCAFE, {0x1: 0x1111, 0x2: 0x2222, 0x3: 0x3333}),
    }

    for mode, (selected_value, other_updates) in updates.items():
        dut.mode_sel.value = mode
        await settle_debug_bus(dut)

        for other_mode, other_value in other_updates.items():
            patterns[other_mode] = other_value
        set_feature_patterns_by_mode(dut, patterns)
        await settle_debug_bus(dut)
        got_bus = dut.debug_bus.value.to_unsigned()
        assert got_bus == patterns[mode], (
            f"mode {mode} changed when non-selected features updated: got 0x{got_bus:04x}, expected 0x{patterns[mode]:04x}"
        )

        patterns[mode] = selected_value
        set_feature_patterns_by_mode(dut, patterns)
        await expect_debug_mode(dut, mode, selected_value)

    dut.stim_override_en.value = 0
    dut.mode_sel.value = 0
    await ClockCycles(dut.clk, 1)


@cocotb.test()
async def test_chip_core_debug_modes_match_real_pipeline_features(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    accel_trace = load_accel_trace(SIM_DATA / "accel_digital.csv")
    ppg_trace = load_ppg_trace(SIM_DATA / "ppg_digital.csv")
    ref = PipelineReference(config=TopPipelineConfig())

    await reset_dut(dut)
    dut.stim_override_en.value = 0

    for _ in range(20):
        await RisingEdge(dut.clk)
        await ReadOnly()

    prev_inputs = collect_real_pipeline_inputs(dut, rst=False)
    accel_index = 0
    ppg_index = 0
    feature_count = 0
    rr_count = 0
    mssd_count = 0
    motion_epoch_count = 0
    checked_feature_count = 0
    max_cycles = 300_000

    for cycle in range(max_cycles):
        await RisingEdge(dut.clk)
        await ReadOnly()

        expected = ref.step(prev_inputs)

        if int(dut.accel_valid_w.value):
            if accel_index >= len(accel_trace):
                raise AssertionError(f"accel trace exhausted at cycle {cycle}")
            expected_accel = accel_trace[accel_index]
            got_triplet = (sig_s(dut.ax_w), sig_s(dut.ay_w), sig_s(dut.az_w))
            exp_triplet = (expected_accel.ax, expected_accel.ay, expected_accel.az)
            assert got_triplet == exp_triplet, (
                f"accel sample[{accel_index}] mismatch at cycle {cycle}: got={got_triplet} exp={exp_triplet}"
            )
            accel_index += 1

        if int(dut.ppg_sample_valid_w.value):
            if ppg_index >= len(ppg_trace):
                raise AssertionError(f"ppg trace exhausted at cycle {cycle}")
            expected_ppg = ppg_trace[ppg_index]
            got_sample = sig_u(dut.ppg_sample_w)
            assert got_sample == expected_ppg.value, (
                f"ppg sample[{ppg_index}] mismatch at cycle {cycle}: got={got_sample} exp={expected_ppg.value}"
            )
            ppg_index += 1

        feature_got = {
            "feat_valid": int(dut.feat_valid_o.value),
            "time_feat": sig_s(dut.time_feat_o),
            "motion_feat": sig_s(dut.motion_feat_o),
            "delta_hr_feat": sig_s(dut.delta_hr_feat_o),
            "mssd_feat": sig_s(dut.mssd_feat_o),
        }
        feature_exp = {
            "feat_valid": int(expected.feature.feat_valid),
            "time_feat": expected.feature.time_feat,
            "motion_feat": expected.feature.motion_feat,
            "delta_hr_feat": expected.feature.delta_hr_feat,
            "mssd_feat": expected.feature.mssd_feat,
        }
        assert feature_got == feature_exp, (
            f"feature mismatch at cycle {cycle}: got={feature_got} exp={feature_exp}"
        )

        rr_count += int(dut.rr_valid_w.value)
        mssd_count += int(dut.mssd_valid_w.value)
        motion_epoch_count += int(dut.motion_epoch_w.value)
        feature_count += int(dut.feat_valid_o.value)

        if expected.feature.feat_valid:
            await Timer(1, unit="ns")
            expected_by_mode = {
                0x1: expected.feature.mssd_feat,
                0x2: expected.feature.delta_hr_feat,
                0x3: expected.feature.time_feat,
                0x4: expected.feature.motion_feat,
            }
            for mode, expected_value in expected_by_mode.items():
                await expect_debug_mode(dut, mode, expected_value)
            dut.mode_sel.value = 0
            checked_feature_count += 1

        prev_inputs = collect_real_pipeline_inputs(dut, rst=False)

        if (
            checked_feature_count >= 4
            and accel_index > 0
            and ppg_index > 0
            and rr_count > 0
            and mssd_count > 0
            and motion_epoch_count > 0
        ):
            break
    else:
        raise AssertionError("real chip_core debug-bus pipeline test timed out before enough feature events")

    assert feature_count >= 4, f"expected >=4 feature vectors, got {feature_count}"
    assert checked_feature_count >= 4, f"expected >=4 debug-bus feature checks, got {checked_feature_count}"

    await Timer(1, unit="ns")
    dut.mode_sel.value = 0
    await ClockCycles(dut.clk, 1)
