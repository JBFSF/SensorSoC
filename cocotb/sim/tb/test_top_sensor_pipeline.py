from __future__ import annotations

from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ReadOnly, RisingEdge

from ref_pipeline.pipeline_ref import PipelineReference, PipelineStepInputs, TopPipelineConfig
from ref_pipeline.trace_loader import load_accel_trace, load_ppg_trace
from ref_pipeline.test_helpers import sig_s, sig_u


ROOT = Path(__file__).resolve().parents[3]
SIM_DATA = ROOT / "cocotb" / "sim" / "data"


def collect_inputs(dut, rst: bool) -> PipelineStepInputs:
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
        rmssd_valid=bool(int(dut.rmssd_valid_w.value)),
        rmssd_epoch=sig_u(dut.rmssd_w),
        fifo_overflow_event=bool(int(dut.fifo_overflow_event_w.value)),
        ppg_i2c_err_event=bool(int(dut.ppg_i2c_err_event_w.value)),
        epoch_end=bool(int(dut.epoch_end_w.value)),
        epoch_end_d=bool(int(dut.epoch_end_d.value)),
        cos_time=sig_s(dut.cos_time_w),
        ml_update_gate=bool(int(dut.ml_update_gate_o.value)),
    )


@cocotb.test()
async def test_top_sensor_pipeline_matches_reference_scoreboards(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    accel_trace = load_accel_trace(SIM_DATA / "accel_digital.csv")
    ppg_trace = load_ppg_trace(SIM_DATA / "ppg_digital.csv")
    ref = PipelineReference(config=TopPipelineConfig())

    dut.reset.value = 1
    for _ in range(10):
        await RisingEdge(dut.clk)
    dut.reset.value = 0

    for _ in range(20):
        await RisingEdge(dut.clk)
        await ReadOnly()

    prev_inputs = collect_inputs(dut, rst=False)
    accel_index = 0
    ppg_index = 0
    prev_ppg_time = None
    feature_count = 0
    rr_count = 0
    beat_count = 0
    rmssd_count = 0
    motion_epoch_count = 0
    max_cycles = 300_000

    for cycle in range(max_cycles):
        await RisingEdge(dut.clk)
        await ReadOnly()

        expected = ref.step(prev_inputs)

        if int(dut.motion_epoch_w.value) != int(expected.motion.epoch_done):
            raise AssertionError(
                f"motion epoch_done mismatch at cycle {cycle}: got={int(dut.motion_epoch_w.value)} "
                f"exp={int(expected.motion.epoch_done)}"
            )
        if sig_u(dut.motion_energy_w) != expected.motion.motion_energy_epoch:
            raise AssertionError(
                f"motion energy mismatch at cycle {cycle}: got={sig_u(dut.motion_energy_w)} "
                f"exp={expected.motion.motion_energy_epoch}"
            )

        beat_got = {
            "beat_pulse": int(dut.beat_pulse_w.value),
            "rr_valid": int(dut.rr_valid_w.value),
            "rr_accepted": int(dut.rr_accepted_w.value),
            "rr_interval": sig_u(dut.rr_interval_w),
            "delta_hr_bpm": sig_s(dut.delta_hr_w),
            "beat_quality": sig_u(dut.beat_quality_w),
            "double_beat": int(dut.double_beat_w.value),
            "missed_beat": int(dut.missed_beat_w.value),
            "ppg_invalid": int(dut.ppg_invalid_w.value),
        }
        beat_exp = {
            "beat_pulse": int(expected.beat.beat_pulse),
            "rr_valid": int(expected.beat.rr_valid),
            "rr_accepted": int(expected.beat.rr_accepted),
            "rr_interval": expected.beat.rr_interval,
            "delta_hr_bpm": expected.beat.delta_hr_bpm,
            "beat_quality": expected.beat.beat_quality,
            "double_beat": int(expected.beat.double_beat),
            "missed_beat": int(expected.beat.missed_beat),
            "ppg_invalid": int(expected.beat.ppg_invalid),
        }
        if beat_got != beat_exp:
            raise AssertionError(f"ppg stage mismatch at cycle {cycle}: got={beat_got} exp={beat_exp}")

        rmssd_got = {
            "rmssd_valid": int(dut.rmssd_valid_w.value),
            "rmssd_epoch": sig_u(dut.rmssd_w) & 0xFFFF,
        }
        rmssd_exp = {
            "rmssd_valid": int(expected.rmssd.rmssd_valid),
            "rmssd_epoch": expected.rmssd.rmssd_epoch & 0xFFFF,
        }
        if rmssd_got != rmssd_exp:
            raise AssertionError(f"rmssd mismatch at cycle {cycle}: got={rmssd_got} exp={rmssd_exp}")

        quality_got = {
            "ml_update_gate": int(dut.ml_update_gate_o.value),
            "invalid_reason": sig_u(dut.invalid_reason_o),
        }
        quality_exp = {
            "ml_update_gate": int(expected.quality.ml_update_gate),
            "invalid_reason": expected.quality.invalid_reason,
        }
        if quality_got != quality_exp:
            raise AssertionError(f"quality mismatch at cycle {cycle}: got={quality_got} exp={quality_exp}")

        feature_got = {
            "feat_valid": int(dut.feat_valid_o.value),
            "time_feat": sig_s(dut.time_feat_o),
            "motion_feat": sig_s(dut.motion_feat_o),
            "delta_hr_feat": sig_s(dut.delta_hr_feat_o),
            "rmssd_feat": sig_s(dut.rmssd_feat_o),
        }
        feature_exp = {
            "feat_valid": int(expected.feature.feat_valid),
            "time_feat": expected.feature.time_feat,
            "motion_feat": expected.feature.motion_feat,
            "delta_hr_feat": expected.feature.delta_hr_feat,
            "rmssd_feat": expected.feature.rmssd_feat,
        }
        if feature_got != feature_exp:
            raise AssertionError(f"feature mismatch at cycle {cycle}: got={feature_got} exp={feature_exp}")

        if int(dut.accel_valid_w.value):
            if accel_index >= len(accel_trace):
                raise AssertionError(f"accel trace exhausted at cycle {cycle}")
            expected_accel = accel_trace[accel_index]
            got_triplet = (sig_s(dut.ax_w), sig_s(dut.ay_w), sig_s(dut.az_w))
            exp_triplet = (expected_accel.ax, expected_accel.ay, expected_accel.az)
            if got_triplet != exp_triplet:
                raise AssertionError(
                    f"accel sample[{accel_index}] mismatch at cycle {cycle}: got={got_triplet} exp={exp_triplet}"
                )
            accel_index += 1

        if int(dut.ppg_sample_valid_w.value):
            if ppg_index >= len(ppg_trace):
                raise AssertionError(f"ppg trace exhausted at cycle {cycle}")
            expected_ppg = ppg_trace[ppg_index]
            got_sample = sig_u(dut.ppg_sample_w)
            if got_sample != expected_ppg.value:
                raise AssertionError(
                    f"ppg sample[{ppg_index}] mismatch at cycle {cycle}: got={got_sample} exp={expected_ppg.value}"
                )
            got_time = sig_u(dut.ppg_sample_time_w)
            if prev_ppg_time is not None and got_time <= prev_ppg_time:
                raise AssertionError(
                    f"ppg sample time did not increase at cycle {cycle}: prev={prev_ppg_time} now={got_time}"
                )
            prev_ppg_time = got_time
            ppg_index += 1

        beat_count += int(dut.beat_pulse_w.value)
        rr_count += int(dut.rr_valid_w.value)
        rmssd_count += int(dut.rmssd_valid_w.value)
        motion_epoch_count += int(dut.motion_epoch_w.value)
        feature_count += int(dut.feat_valid_o.value)

        prev_inputs = collect_inputs(dut, rst=False)

        if feature_count >= 4 and rr_count > 0 and rmssd_count > 0 and motion_epoch_count > 0:
            break
    else:
        raise AssertionError("top pipeline scoreboard timed out before enough feature events")

    assert accel_index > 0, "no accel samples observed"
    assert ppg_index > 0, "no ppg samples observed"
    assert beat_count > 0, "no beats observed"
    assert rr_count > 0, "no RR intervals observed"
    assert rmssd_count > 0, "no RMSSD epochs observed"
    assert feature_count >= 4, f"expected >=4 feature vectors, got {feature_count}"
