import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ReadOnly, RisingEdge

from ref_pipeline.signal_quality_ref import SignalQualityConfig, SignalQualityRef
from ref_pipeline.test_helpers import sig_u


async def drive_and_check(
    dut,
    ref,
    cfg,
    *,
    rst,
    epoch_end=False,
    beat_event=False,
    beat_quality=0,
    double_beat=False,
    missed_beat=False,
    fifo_overflow=False,
    fifo_i2c_error=False,
    motion_valid=False,
    motion_intensity=0,
):
    await FallingEdge(dut.clk)
    dut.rst_i.value = int(rst)
    dut.epoch_end.value = int(epoch_end)
    dut.beat_event.value = int(beat_event)
    dut.beat_quality.value = beat_quality
    dut.double_beat.value = int(double_beat)
    dut.missed_beat.value = int(missed_beat)
    dut.fifo_overflow.value = int(fifo_overflow)
    dut.fifo_i2c_error.value = int(fifo_i2c_error)
    dut.motion_valid.value = int(motion_valid)
    dut.motion_intensity.value = motion_intensity
    dut.cfg_beat_q_min.value = cfg.beat_q_min
    dut.cfg_min_valid_fraction.value = cfg.min_valid_fraction
    dut.cfg_max_double.value = cfg.max_double
    dut.cfg_max_missed.value = cfg.max_missed
    dut.cfg_motion_hi_th.value = cfg.motion_hi_th
    dut.cfg_max_motion_hi.value = cfg.max_motion_hi

    await RisingEdge(dut.clk)
    await ReadOnly()

    expected = ref.step(
        rst=rst,
        epoch_end=epoch_end,
        beat_event=beat_event,
        beat_quality=beat_quality,
        double_beat=double_beat,
        missed_beat=missed_beat,
        fifo_overflow=fifo_overflow,
        fifo_i2c_error=fifo_i2c_error,
        motion_valid=motion_valid,
        motion_intensity=motion_intensity,
        cfg=cfg,
    )
    assert sig_u(dut.invalid_reason) == expected.invalid_reason
    assert int(dut.ml_update_gate.value) == int(expected.ml_update_gate)


@cocotb.test()
async def test_signal_quality_matches_reference(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cfg = SignalQualityConfig(
        beat_q_min=120,
        min_valid_fraction=180,
        max_double=2,
        max_missed=2,
        motion_hi_th=500,
        max_motion_hi=3,
    )
    ref = SignalQualityRef()

    for _ in range(4):
        await drive_and_check(dut, ref, cfg, rst=True)

    for quality in (200, 190, 180):
        await drive_and_check(dut, ref, cfg, rst=False, beat_event=True, beat_quality=quality)
    for motion in (100, 120):
        await drive_and_check(dut, ref, cfg, rst=False, motion_valid=True, motion_intensity=motion)
    await drive_and_check(dut, ref, cfg, rst=False, epoch_end=True)
    assert int(dut.ml_update_gate.value) == 1
    assert sig_u(dut.invalid_reason) == 0

    for quality in (80, 90, 70):
        await drive_and_check(dut, ref, cfg, rst=False, beat_event=True, beat_quality=quality)
    for _ in range(4):
        await drive_and_check(dut, ref, cfg, rst=False, double_beat=True)
    for _ in range(4):
        await drive_and_check(dut, ref, cfg, rst=False, missed_beat=True)
    for _ in range(5):
        await drive_and_check(dut, ref, cfg, rst=False, motion_valid=True, motion_intensity=700)
    await drive_and_check(dut, ref, cfg, rst=False, fifo_overflow=True, fifo_i2c_error=True)
    await drive_and_check(dut, ref, cfg, rst=False, epoch_end=True)
    assert int(dut.ml_update_gate.value) == 0
    assert sig_u(dut.invalid_reason) & 0x7B == 0x7B

    await drive_and_check(dut, ref, cfg, rst=False, motion_valid=True, motion_intensity=100)
    await drive_and_check(dut, ref, cfg, rst=False, epoch_end=True)
    assert int(dut.ml_update_gate.value) == 0
    assert sig_u(dut.invalid_reason) & (1 << 2)
