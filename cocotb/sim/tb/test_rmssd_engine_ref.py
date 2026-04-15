import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ReadOnly, RisingEdge

from ref_pipeline.rmssd_ref import RmssdEngineRef
from ref_pipeline.test_helpers import sig_u


async def drive_and_check(dut, ref, *, rst, rr_interval, rr_valid, rr_accepted, epoch_end):
    await FallingEdge(dut.clk)
    dut.rst_i.value = int(rst)
    dut.rr_interval.value = rr_interval
    dut.rr_valid.value = int(rr_valid)
    dut.rr_accepted.value = int(rr_accepted)
    dut.epoch_end.value = int(epoch_end)

    await RisingEdge(dut.clk)
    await ReadOnly()

    expected = ref.step(rst, rr_valid, rr_accepted, rr_interval, epoch_end)
    assert int(dut.rmssd_valid.value) == int(expected.rmssd_valid)
    assert sig_u(dut.rmssd_epoch) == expected.rmssd_epoch
    assert sig_u(dut.rr_diff_count) == expected.rr_diff_count


@cocotb.test()
async def test_rmssd_engine_matches_reference(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    ref = RmssdEngineRef(min_rr_count=2)

    for _ in range(4):
        await drive_and_check(dut, ref, rst=True, rr_interval=0, rr_valid=False, rr_accepted=False, epoch_end=False)

    seq = [
        (1000, True, True, False),
        (1100, True, True, False),
        (900, True, True, False),
        (1000, True, True, False),
        (0, False, False, True),
    ]
    for rr_interval, rr_valid, rr_accepted, epoch_end in seq:
        await drive_and_check(
            dut,
            ref,
            rst=False,
            rr_interval=rr_interval,
            rr_valid=rr_valid,
            rr_accepted=rr_accepted,
            epoch_end=epoch_end,
        )
    assert int(dut.rmssd_valid.value) == 1
    assert sig_u(dut.rmssd_epoch) == 60000

    seq = [
        (1000, True, True, False),
        (700, True, False, False),
        (1200, True, True, False),
        (1000, True, True, False),
        (0, False, False, True),
    ]
    for rr_interval, rr_valid, rr_accepted, epoch_end in seq:
        await drive_and_check(
            dut,
            ref,
            rst=False,
            rr_interval=rr_interval,
            rr_valid=rr_valid,
            rr_accepted=rr_accepted,
            epoch_end=epoch_end,
        )
    assert int(dut.rmssd_valid.value) == 1
    assert sig_u(dut.rmssd_epoch) == 0xFFFF

    for rr_interval, rr_valid, rr_accepted, epoch_end in [
        (1000, True, True, False),
        (1100, True, True, False),
        (0, False, False, True),
    ]:
        await drive_and_check(
            dut,
            ref,
            rst=False,
            rr_interval=rr_interval,
            rr_valid=rr_valid,
            rr_accepted=rr_accepted,
            epoch_end=epoch_end,
        )
    assert int(dut.rmssd_valid.value) == 0
