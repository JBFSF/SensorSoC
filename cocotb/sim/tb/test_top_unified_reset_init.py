import cocotb
from cocotb.triggers import ClockCycles, ReadOnly, RisingEdge

from top_unified_env import apply_reset, start_clock


def _u(value) -> int:
    """Return an integer view of a cocotb handle's current value."""
    return int(value.value)


@cocotb.test()
async def test_unified_top_reset_and_init_state(dut):
    """Check the clean reset/initialization contract for the shared wrapper.

    What this test is trying to prove
    ---------------------------------
    Before we build more cocotb regressions on the shared unified-top wrapper,
    we want one foundational smoke test that verifies the post-reset contract is
    sane and repeatable.

    This test focuses on the system state that other regressions will rely on:

        - feature latch starts empty
        - IRQ controller state starts clean
        - wake bookkeeping starts clean
        - no spurious timer / ML / host IRQ events appear during early boot
        - CPU begins normal memory traffic after reset release
        - no immediate trap occurs

    This intentionally does *not* try to validate the full production loop.
    Its job is to catch bad reset behavior early and cheaply.
    """
    cocotb.start_soon(start_clock(dut))

    # While reset is asserted, the always-on bookkeeping and sticky state
    # should remain clear regardless of what the CPU will do after release.
    dut.reset.value = 1
    dut.test_force_irq.value = 0
    dut.test_force_wake.value = 0
    await ClockCycles(dut.clk, 5)
    await ReadOnly()

    assert _u(dut.feat_latched_valid) == 0, "feature latch valid should reset low"
    assert _u(dut.irq_pending) == 0, "IRQC pending should reset clear"
    assert _u(dut.irq_mask) == 0, "IRQC mask should reset clear"
    assert _u(dut.irq_wake_en) == 0x7, "IRQC wake enable should reset to timer/ML/host default"
    assert _u(dut.pwr_wake_status) == 0, "wake status should reset clear"
    assert _u(dut.pwr_wake_reason) == 0, "wake reason should reset clear"
    assert _u(dut.sleep_req) == 0, "sleep request should reset clear"
    assert _u(dut.ml_irq) == 0, "ML IRQ should be idle during reset"
    assert _u(dut.timer_event) == 0, "timer event should be idle during reset"
    assert _u(dut.host_i2c_irq_event) == 0, "host-I2C IRQ event should be idle during reset"
    assert _u(dut.pico_sleeping) == 0, "CPU should not report sleeping during reset"
    assert _u(dut.pico_cpu_clk_en) == 1, "CPU clock gate should default enabled at reset"
    assert _u(dut.pico_irq) == 0, "CPU IRQ vector should be clear during reset"
    assert _u(dut.test_status) == 0, "test status mailbox should reset clear"
    assert _u(dut.test_code) == 0, "test code mailbox should reset clear"

    await apply_reset(dut, cycles=20)
    await ReadOnly()

    # On the first clean cycle after reset release, we still expect no stale
    # sticky state. The CPU may begin fetching immediately, so we do not insist
    # on mem_valid being low here; we only care that reset bookkeeping is clean.
    assert _u(dut.feat_latched_valid) == 0, "feature latch valid came up stale after reset release"
    assert _u(dut.irq_pending) == 0, "IRQC pending came up stale after reset release"
    assert _u(dut.pwr_wake_status) == 0, "wake status came up stale after reset release"
    assert _u(dut.pwr_wake_reason) == 0, "wake reason came up stale after reset release"
    assert _u(dut.pico_sleeping) == 0, "CPU should start awake after reset release"
    assert _u(dut.pico_trap) == 0, "CPU trap should not assert immediately after reset release"

    # Watch a short initialization window to make sure no spurious wake/IRQ
    # activity is generated before boot-side firmware configures anything.
    saw_mem_activity = False
    for _ in range(64):
        await RisingEdge(dut.clk)
        await ReadOnly()
        saw_mem_activity |= (_u(dut.pico_mem_valid) != 0)
        assert _u(dut.feat_latched_valid) == 0, "feature latch should remain clear during early boot"
        assert _u(dut.pwr_wake_status) == 0, "wake status should remain clear during early boot"
        assert _u(dut.pwr_wake_reason) == 0, "wake reason should remain clear during early boot"
        assert _u(dut.host_i2c_irq_event) == 0, "host-I2C IRQ event should not spuriously pulse during init"
        assert _u(dut.ml_irq) == 0, "ML IRQ should not spuriously assert during init"
        assert _u(dut.timer_event) == 0, "timer event should not spuriously assert during init"
        assert _u(dut.pico_trap) == 0, "CPU trap asserted during early init"

    assert saw_mem_activity, "CPU never began instruction/data traffic after reset release"
