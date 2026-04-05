import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, ReadOnly, RisingEdge, with_timeout


def expected_status(valid: int, invalid_reason: int, gate: int) -> int:
    return ((gate & 0x1) << 17) | ((invalid_reason & 0xFF) << 1) | (valid & 0x1)


async def reset_dut(dut, cycles: int = 20) -> None:
    dut.reset.value = 1
    await ClockCycles(dut.clk, cycles)
    dut.reset.value = 0
    await ClockCycles(dut.clk, 2)


@cocotb.test()
async def test_sensor_features_latch_into_soc_visible_mmio_bank(dut):
    """Verify the unified top captures sensor features into the sticky MMIO bank."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    feature_checks = 0
    target_checks = 4

    while feature_checks < target_checks:
        await with_timeout(RisingEdge(dut.feat_valid), 40, "ms")
        # The unified top now captures feature events into the CPU-visible
        # MMIO bank using a one-cycle delayed copy of feat_valid_o, so sample
        # the sticky bank on the following clock edge.
        await RisingEdge(dut.clk)
        await ReadOnly()

        time_feat = dut.time_feat.value.to_signed()
        motion_feat = dut.motion_feat.value.to_signed()
        delta_hr_feat = dut.delta_hr_feat.value.to_signed()
        rmssd_feat = dut.rmssd_feat.value.to_signed()
        gate = int(dut.ml_update_gate.value)
        invalid_reason = dut.invalid_reason.value.to_unsigned()

        latched_valid = int(dut.feat_latched_valid.value)
        latched_time = dut.feat_latched_time.value.to_signed()
        latched_motion = dut.feat_latched_motion.value.to_signed()
        latched_delta_hr = dut.feat_latched_delta_hr.value.to_signed()
        latched_rmssd = dut.feat_latched_rmssd.value.to_signed()
        latched_gate = int(dut.feat_latched_gate.value)
        latched_invalid_reason = dut.feat_latched_invalid_reason.value.to_unsigned()
        status = dut.feat_status_mirror.value.to_unsigned()

        dut._log.info(
            "feature[%d] time=%d motion=%d delta_hr=%d rmssd=%d gate=%d invalid_reason=0x%02x status=0x%08x",
            feature_checks,
            time_feat,
            motion_feat,
            delta_hr_feat,
            rmssd_feat,
            gate,
            invalid_reason,
            status,
        )

        assert latched_valid == 1, "feature latch valid bit did not set after feat_valid pulse"
        assert latched_time == time_feat, (
            f"latched time mismatch: expected {time_feat}, got {latched_time}"
        )
        assert latched_motion == motion_feat, (
            f"latched motion mismatch: expected {motion_feat}, got {latched_motion}"
        )
        assert latched_delta_hr == delta_hr_feat, (
            f"latched delta_hr mismatch: expected {delta_hr_feat}, got {latched_delta_hr}"
        )
        assert latched_rmssd == rmssd_feat, (
            f"latched rmssd mismatch: expected {rmssd_feat}, got {latched_rmssd}"
        )
        assert latched_gate == gate, (
            f"latched gate mismatch: expected {gate}, got {latched_gate}"
        )
        assert latched_invalid_reason == invalid_reason, (
            f"latched invalid_reason mismatch: expected 0x{invalid_reason:02x}, got 0x{latched_invalid_reason:02x}"
        )

        expected = expected_status(1, invalid_reason, gate)
        assert status == expected, (
            f"feature status mirror mismatch: expected 0x{expected:08x}, got 0x{status:08x}"
        )

        feature_checks += 1

    assert feature_checks == target_checks
