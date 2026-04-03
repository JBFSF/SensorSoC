import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ClockCycles, with_timeout


def pack_feature_word(upper_16: int, lower_16: int) -> int:
    return ((upper_16 & 0xFFFF) << 16) | (lower_16 & 0xFFFF)


async def reset_dut(dut, cycles: int = 20) -> None:
    dut.reset.value = 1
    await ClockCycles(dut.clk, cycles)
    dut.reset.value = 0
    await ClockCycles(dut.clk, 2)


@cocotb.test()
async def test_sensor_features_are_loaded_into_taketwo_buffer(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    feature_checks = 0
    target_checks = 4

    while feature_checks < target_checks:
        await with_timeout(RisingEdge(dut.feat_valid), 40, "ms")

        time_feat = dut.time_feat.value.to_signed()
        motion_feat = dut.motion_feat.value.to_signed()
        delta_hr_feat = dut.delta_hr_feat.value.to_signed()
        rmssd_feat = dut.rmssd_feat.value.to_signed()

        expected_w0 = pack_feature_word(time_feat, motion_feat)
        expected_w1 = pack_feature_word(rmssd_feat, delta_hr_feat)

        await with_timeout(RisingEdge(dut.axi_done), 2, "ms")
        await RisingEdge(dut.clk)

        got_w0 = dut.mlp_word0.value.to_unsigned()
        got_w1 = dut.mlp_word1.value.to_unsigned()

        dut._log.info(
            "feature[%d] time=%d motion=%d delta_hr=%d rmssd=%d buffer_word0=0x%08x buffer_word1=0x%08x",
            feature_checks,
            time_feat,
            motion_feat,
            delta_hr_feat,
            rmssd_feat,
            got_w0,
            got_w1,
        )

        assert got_w0 == expected_w0, (
            f"taketwo input word0 mismatch: expected 0x{expected_w0:08x}, got 0x{got_w0:08x}"
        )
        assert got_w1 == expected_w1, (
            f"taketwo input word1 mismatch: expected 0x{expected_w1:08x}, got 0x{got_w1:08x}"
        )

        read_hits = []
        while len(read_hits) < 2:
            await with_timeout(RisingEdge(dut.tk_ar_fire), 2, "ms")
            read_addr = dut.tk_araddr.value.to_unsigned()
            if read_addr in (0x40, 0x44):
                read_hits.append(read_addr)

        dut._log.info("feature[%d] taketwo read sequence=%s", feature_checks, [hex(v) for v in read_hits])

        assert len(read_hits) == 2, "taketwo did not fetch two feature-buffer reads"

        feature_checks += 1

    assert feature_checks == target_checks
