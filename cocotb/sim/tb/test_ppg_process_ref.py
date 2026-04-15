import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ReadOnly, RisingEdge

from ref_pipeline.ppg_ref import PpgConfig, PpgProcessRef
from ref_pipeline.test_helpers import sig_s, sig_u


def apply_cfg(dut, cfg: PpgConfig) -> None:
    dut.cfg_enable.value = int(cfg.enable)
    dut.cfg_bypass.value = int(cfg.bypass)
    dut.cfg_signed.value = int(cfg.signed_samples)
    dut.cfg_lp_beta.value = cfg.lp_beta
    dut.cfg_base_alpha.value = cfg.base_alpha
    dut.cfg_env_decay.value = cfg.env_decay
    dut.cfg_abs_en.value = int(cfg.abs_en)
    dut.cfg_thr_k.value = cfg.thr_k
    dut.cfg_thr_min.value = cfg.thr_min
    dut.cfg_refrac_ticks.value = cfg.refrac_ticks
    dut.cfg_rr_min_ticks.value = cfg.rr_min_ticks
    dut.cfg_rr_max_ticks.value = cfg.rr_max_ticks
    dut.cfg_q_amp_w.value = cfg.q_amp_w
    dut.cfg_q_slope_w.value = cfg.q_slope_w
    dut.cfg_q_refrac_penalty.value = cfg.q_refrac_penalty
    dut.cfg_q_min_accept.value = cfg.q_min_accept


async def step_and_check(dut, ref, cfg, *, rst, sample, valid, sample_time):
    await FallingEdge(dut.clk)
    dut.rst_i.value = int(rst)
    dut.ppg_sample.value = sample
    dut.ppg_valid.value = int(valid)
    dut.ppg_sample_time.value = sample_time
    apply_cfg(dut, cfg)

    await RisingEdge(dut.clk)
    await ReadOnly()

    expected = ref.step(rst, sample, valid, sample_time, cfg)
    assert int(dut.beat_pulse.value) == int(expected.beat_pulse)
    assert int(dut.rr_valid.value) == int(expected.rr_valid)
    assert int(dut.rr_accepted.value) == int(expected.rr_accepted)
    assert sig_u(dut.rr_interval) == expected.rr_interval
    assert sig_s(dut.delta_hr_bpm) == expected.delta_hr_bpm
    assert sig_u(dut.beat_quality) == expected.beat_quality
    assert int(dut.double_beat.value) == int(expected.double_beat)
    assert int(dut.missed_beat.value) == int(expected.missed_beat)
    assert int(dut.ppg_invalid.value) == int(expected.ppg_invalid)


async def emit_peak(dut, ref, cfg, sim_time, amp):
    pattern = [0, amp // 3, (2 * amp) // 3, amp, (2 * amp) // 3, amp // 3, 0]
    for sample in pattern:
        await step_and_check(dut, ref, cfg, rst=False, sample=sample, valid=True, sample_time=sim_time)
        sim_time += 1
    return sim_time


async def idle_cycles(dut, ref, cfg, sim_time, count):
    for _ in range(count):
        await step_and_check(dut, ref, cfg, rst=False, sample=0, valid=True, sample_time=sim_time)
        sim_time += 1
    return sim_time


@cocotb.test()
async def test_ppg_process_matches_reference(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    base_cfg = PpgConfig(
        enable=True,
        bypass=False,
        signed_samples=False,
        lp_beta=1 << 10,
        base_alpha=0,
        env_decay=2,
        abs_en=True,
        thr_k=(1 << 9),
        thr_min=40,
        refrac_ticks=250,
        rr_min_ticks=300,
        rr_max_ticks=2000,
        q_amp_w=4,
        q_slope_w=2,
        q_refrac_penalty=8,
        q_min_accept=5,
    )

    ref = PpgProcessRef()
    sim_time = 0
    for _ in range(5):
        await step_and_check(dut, ref, base_cfg, rst=True, sample=0, valid=False, sample_time=0)

    sim_time = await emit_peak(dut, ref, base_cfg, sim_time, 600)
    sim_time = await idle_cycles(dut, ref, base_cfg, sim_time, 20)

    ref = PpgProcessRef()
    sim_time = 0
    for _ in range(5):
        await step_and_check(dut, ref, base_cfg, rst=True, sample=0, valid=False, sample_time=0)
    sim_time = await emit_peak(dut, ref, base_cfg, sim_time, 600)
    sim_time = await idle_cycles(dut, ref, base_cfg, sim_time, 950)
    sim_time = await emit_peak(dut, ref, base_cfg, sim_time, 600)
    sim_time = await idle_cycles(dut, ref, base_cfg, sim_time, 20)

    refrac_cfg = PpgConfig(**{**base_cfg.__dict__, "refrac_ticks": 50})
    ref = PpgProcessRef()
    sim_time = 0
    for _ in range(5):
        await step_and_check(dut, ref, refrac_cfg, rst=True, sample=0, valid=False, sample_time=0)
    sim_time = await emit_peak(dut, ref, refrac_cfg, sim_time, 600)
    sim_time = await idle_cycles(dut, ref, refrac_cfg, sim_time, 120)
    sim_time = await emit_peak(dut, ref, refrac_cfg, sim_time, 600)
    sim_time = await idle_cycles(dut, ref, refrac_cfg, sim_time, 20)

    missed_cfg = PpgConfig(**{**base_cfg.__dict__, "rr_max_ticks": 500})
    ref = PpgProcessRef()
    sim_time = 0
    for _ in range(5):
        await step_and_check(dut, ref, missed_cfg, rst=True, sample=0, valid=False, sample_time=0)
    sim_time = await emit_peak(dut, ref, missed_cfg, sim_time, 600)
    sim_time = await idle_cycles(dut, ref, missed_cfg, sim_time, 800)
    sim_time = await emit_peak(dut, ref, missed_cfg, sim_time, 600)
    sim_time = await idle_cycles(dut, ref, missed_cfg, sim_time, 20)

    reject_cfg = PpgConfig(**{**base_cfg.__dict__, "q_amp_w": 0, "q_slope_w": 0, "q_min_accept": 1})
    ref = PpgProcessRef()
    sim_time = 0
    for _ in range(5):
        await step_and_check(dut, ref, reject_cfg, rst=True, sample=0, valid=False, sample_time=0)
    sim_time = await idle_cycles(dut, ref, reject_cfg, sim_time, 50)
    sim_time = await emit_peak(dut, ref, reject_cfg, sim_time, 700)
    sim_time = await idle_cycles(dut, ref, reject_cfg, sim_time, 50)

    accept_cfg = PpgConfig(**{**base_cfg.__dict__, "q_amp_w": 4, "q_slope_w": 2, "q_min_accept": 5})
    sim_time = await emit_peak(dut, ref, accept_cfg, sim_time, 700)
    sim_time = await idle_cycles(dut, ref, accept_cfg, sim_time, 10)

    ref = PpgProcessRef()
    sim_time = 0
    for _ in range(5):
        await step_and_check(dut, ref, base_cfg, rst=True, sample=0, valid=False, sample_time=0)
    sim_time = await emit_peak(dut, ref, base_cfg, sim_time, 700)
    sim_time = await idle_cycles(dut, ref, base_cfg, sim_time, 20)
    sim_time = await idle_cycles(dut, ref, base_cfg, sim_time, 2100)
    assert int(dut.ppg_invalid.value) == 1

    bypass_cfg = PpgConfig(**{**base_cfg.__dict__, "bypass": True})
    ref = PpgProcessRef()
    sim_time = 0
    for _ in range(5):
        await step_and_check(dut, ref, bypass_cfg, rst=True, sample=0, valid=False, sample_time=0)
    sim_time = await emit_peak(dut, ref, bypass_cfg, sim_time, 700)
    sim_time = await idle_cycles(dut, ref, bypass_cfg, sim_time, 20)
    assert int(dut.beat_pulse.value) == 0
