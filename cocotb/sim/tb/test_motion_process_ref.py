import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ReadOnly, RisingEdge

from ref_pipeline.motion_ref import MotionProcessRef
from ref_pipeline.test_helpers import sig_s, sig_u


async def drive_and_check(dut, ref, *, rst, sample_valid, ax, ay, az, epoch_end):
    await FallingEdge(dut.clk)
    dut.rst_i.value = int(rst)
    dut.sample_valid.value = int(sample_valid)
    dut.ax.value = ax
    dut.ay.value = ay
    dut.az.value = az
    dut.epoch_end.value = int(epoch_end)

    await RisingEdge(dut.clk)
    await ReadOnly()

    expected = ref.step(rst, sample_valid, ax, ay, az, epoch_end)
    assert int(dut.epoch_done.value) == int(expected.epoch_done)
    assert sig_u(dut.motion_energy_epoch) == expected.motion_energy_epoch


@cocotb.test()
async def test_motion_process_matches_reference(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    ref = MotionProcessRef(ax_w=16)

    for _ in range(5):
        await drive_and_check(dut, ref, rst=True, sample_valid=False, ax=0, ay=0, az=0, epoch_end=False)

    await drive_and_check(dut, ref, rst=False, sample_valid=True, ax=3, ay=-4, az=5, epoch_end=False)
    await drive_and_check(dut, ref, rst=False, sample_valid=True, ax=1, ay=2, az=3, epoch_end=False)
    await drive_and_check(dut, ref, rst=False, sample_valid=False, ax=10, ay=0, az=0, epoch_end=False)
    await drive_and_check(dut, ref, rst=False, sample_valid=False, ax=0, ay=0, az=0, epoch_end=True)
    assert sig_u(dut.motion_energy_epoch) == 18

    for _ in range(3):
        await drive_and_check(dut, ref, rst=True, sample_valid=False, ax=0, ay=0, az=0, epoch_end=False)
    await drive_and_check(dut, ref, rst=False, sample_valid=True, ax=2, ay=0, az=0, epoch_end=False)
    await drive_and_check(dut, ref, rst=False, sample_valid=True, ax=3, ay=0, az=0, epoch_end=False)
    await drive_and_check(dut, ref, rst=False, sample_valid=False, ax=0, ay=0, az=0, epoch_end=True)
    assert sig_u(dut.motion_energy_epoch) == 5

    await drive_and_check(dut, ref, rst=False, sample_valid=False, ax=0, ay=0, az=0, epoch_end=False)
    assert int(dut.epoch_done.value) == 0
