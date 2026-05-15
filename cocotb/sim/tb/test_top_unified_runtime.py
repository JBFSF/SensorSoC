"""Runtime-oriented cocotb tests for the shared unified-top wrapper.

These tests sit one layer above the reset/init smoke test. They reuse the
shared wrapper and Python helpers to cover three high-value behaviors:

    1) repeated production-loop smoke behavior
    2) production alarm policy after five light-sleep classifications
    3) reset-adjacent forced wake / forced IRQ corner cases

The intent is not to replace the large production-style SystemVerilog bench.
Instead, these provide focused Python-side checks that are easier to extend and
debug while keeping the long SV bench as the final integrated guardrail.

The alarm-policy test deliberately uses cocotb ``Force`` on selected internal
signals. That test is not trying to prove real sensor sampling latency or real
taketwo execution time; it proves that once firmware is running, feature MMIO,
weight_flash_axi logit readout, ML IRQ handling, and alarm_mmio are connected
well enough for prod_main's policy to drive the top-level alarm.
"""

import cocotb
from cocotb.handle import Force, Release
from cocotb.triggers import ClockCycles, NextTimeStep, ReadOnly, RisingEdge

from top_unified_env import (
    FEATURE_DHR,
    FEATURE_MOTION,
    FEATURE_RMSSD,
    FEATURE_STATUS,
    FEATURE_TIME,
    X_BASE,
    apply_reset,
    mmio_read_active,
    mmio_write_active,
    start_clock,
    wait_for_boot_load,
)


FEATURE_VALID_MASK = 1 << 0
FORCED_WAKE_BIT = 1 << 3
FORCED_IRQ_BIT = 1 << 0
WAKE_ENABLED_IRQ_BIT = 1 << 0
TEST_FAIL = 0xDEADBEEF
ML_START_ADDR = 0x03003010
ALARM_CTRL_ADDR = 0x03000000
WAKE_WINDOW_START_SEC = 7 * 60 * 60
LIGHT_SLEEP_STREAK_REQ = 5
LIGHT_SLEEP_LOGIT_WORD = (100 << 16) | 0


def _u(handle) -> int:
    return int(handle.value)


def _s16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def _force_prod_features(dut, time_sec: int) -> None:
    """Hold top.sv's firmware-visible feature latch at deterministic values.

    Firmware consumes the feature bank through FEATURE_BASE MMIO. For the alarm
    policy, only the timestamp and valid bit matter directly, but stable
    nonzero feature values keep the feature-to-weight_flash_axi writes
    realistic enough to exercise the production loop.
    """
    dut.u_dut.feat_latched_valid_r.value = Force(1)
    dut.u_dut.feat_time_latched_r.value = Force(time_sec & 0xFFFF)
    dut.u_dut.feat_motion_latched_r.value = Force(0x0020)
    dut.u_dut.feat_delta_hr_latched_r.value = Force(0x0004)
    dut.u_dut.feat_mssd_latched_r.value = Force(0x0040)
    dut.u_dut.feat_gate_latched_r.value = Force(1)
    dut.u_dut.feat_invalid_reason_latched_r.value = Force(0)


def _release_prod_features(dut) -> None:
    dut.u_dut.feat_latched_valid_r.value = Release()
    dut.u_dut.feat_time_latched_r.value = Release()
    dut.u_dut.feat_motion_latched_r.value = Release()
    dut.u_dut.feat_delta_hr_latched_r.value = Release()
    dut.u_dut.feat_mssd_latched_r.value = Release()
    dut.u_dut.feat_gate_latched_r.value = Release()
    dut.u_dut.feat_invalid_reason_latched_r.value = Release()


def _force_light_sleep_logits(dut) -> None:
    """Force weight_flash_axi's CPU-visible logits to class 1/light sleep.

    prod_main reads LOGIT_BASE through the weight_flash_axi MMIO page. The first
    word packs logit0 in [15:0] and logit1 in [31:16], so this value makes
    logit1 > logit0 with a confidence of 100.
    """
    dut.u_dut.u_weight_ram.logit_reg_0.value = Force(LIGHT_SLEEP_LOGIT_WORD)
    dut.u_dut.u_weight_ram.logit_reg_1.value = Force(0)


def _release_light_sleep_logits(dut) -> None:
    dut.u_dut.u_weight_ram.logit_reg_0.value = Release()
    dut.u_dut.u_weight_ram.logit_reg_1.value = Release()


def _force_fast_ml_control_path(dut) -> None:
    """Make taketwo's AXI-Lite control port respond immediately after setup.

    This is test acceleration. The firmware still performs the real ML control
    MMIO writes and reads, but we bypass long accelerator latency so the test
    can focus on the firmware policy path instead of becoming a full ML soak.
    """
    dut.u_dut.ml_saxi_awready.value = Force(1)
    dut.u_dut.ml_saxi_wready.value = Force(1)
    dut.u_dut.ml_saxi_bvalid.value = Force(1)
    dut.u_dut.ml_saxi_bresp.value = Force(0)
    dut.u_dut.ml_saxi_arready.value = Force(1)
    dut.u_dut.ml_saxi_rvalid.value = Force(1)
    dut.u_dut.ml_saxi_rresp.value = Force(0)
    dut.u_dut.ml_saxi_rdata.value = Force(0)


def _release_fast_ml_control_path(dut) -> None:
    dut.u_dut.ml_saxi_awready.value = Release()
    dut.u_dut.ml_saxi_wready.value = Release()
    dut.u_dut.ml_saxi_bvalid.value = Release()
    dut.u_dut.ml_saxi_bresp.value = Release()
    dut.u_dut.ml_saxi_arready.value = Release()
    dut.u_dut.ml_saxi_rvalid.value = Release()
    dut.u_dut.ml_saxi_rresp.value = Release()
    dut.u_dut.ml_saxi_rdata.value = Release()


def _force_prod_policy_clocks(dut) -> None:
    """Keep firmware and ML MMIO live while this test drives policy stimulus.

    The top FSM can legitimately sleep between production phases. For this
    policy-focused test, holding the CPU and ML MMIO enables live avoids waiting
    on real sleep/wake cadence while still requiring firmware to issue the
    expected feature clears, ML starts, logit reads, and alarm write.
    """
    dut.u_dut.cpu_clk_en_lat.value = Force(1)
    dut.u_dut.ml_en.value = Force(1)


def _release_prod_policy_clocks(dut) -> None:
    dut.u_dut.cpu_clk_en_lat.value = Release()
    dut.u_dut.ml_en.value = Release()


def _force_ml_irq(dut, asserted: bool) -> None:
    """Drive a fresh ML-complete interrupt source for prod_main to claim."""
    dut.u_dut.ml_irq.value = Force(1 if asserted else 0)
    dut.test_irq_src.value = 0b010 if asserted else 0


def _release_ml_irq(dut) -> None:
    dut.u_dut.ml_irq.value = Release()
    dut.test_irq_src.value = 0


@cocotb.test()
async def test_repeated_production_loop_smoke(dut):
    """Check that the prod_main loop completes at least one coherent iteration.

    This is intentionally a smoke test, not a long soak. For current bring-up,
    one full feature-read -> feature-clear -> X-window write sequence is enough
    to prove the production loop is alive end-to-end in the shared wrapper.
    """
    cocotb.start_soon(start_clock(dut))
    await apply_reset(dut)
    await wait_for_boot_load(dut)

    feature_read_counts = {
        FEATURE_STATUS: 0,
        FEATURE_TIME: 0,
        FEATURE_MOTION: 0,
        FEATURE_DHR: 0,
        FEATURE_RMSSD: 0,
    }
    feature_clears = 0
    ml_start_writes = 0
    coherent_iterations = 0
    current_iter = None

    # This smoke test observes real firmware bus traffic. It does not force the
    # ML result path; it only requires one coherent iteration to prove the
    # production loop is alive after boot.
    for _ in range(2_000_000):
        await RisingEdge(dut.clk)
        await ReadOnly()

        if _u(dut.pico_trap):
            raise AssertionError("CPU trap asserted during repeated production-loop smoke test")
        if _u(dut.test_status) == TEST_FAIL:
            raise AssertionError(f"firmware reported FAIL with code 0x{_u(dut.test_code):08x}")
        if mmio_read_active(dut):
            addr = _u(dut.pico_mem_addr)
            if addr in feature_read_counts:
                feature_read_counts[addr] += 1

        if mmio_write_active(dut):
            addr = _u(dut.pico_mem_addr)
            wdata = _u(dut.pico_mem_wdata)
            wstrb = _u(dut.pico_mem_wstrb)

            if addr == FEATURE_STATUS and (wdata & FEATURE_VALID_MASK):
                # A write-one to FEATURE_STATUS[0] is firmware acknowledging
                # that it consumed the latched feature vector.
                feature_clears += 1
                current_iter = {
                    "word0_written": False,
                    "word1_written": False,
                }

            elif current_iter is not None and addr == X_BASE:
                # prod_main packs four int16 features into two 32-bit words at
                # X_BASE before starting taketwo.
                current_iter["word0_written"] = True

            elif current_iter is not None and addr == X_BASE + 4:
                current_iter["word1_written"] = True
                if current_iter["word0_written"] and current_iter["word1_written"]:
                    coherent_iterations += 1
                    current_iter = None

            elif addr == ML_START_ADDR:
                ml_start_writes += 1

        if (
            feature_read_counts[FEATURE_STATUS] >= 1 and
            feature_read_counts[FEATURE_TIME] >= 1 and
            feature_read_counts[FEATURE_MOTION] >= 1 and
            feature_read_counts[FEATURE_DHR] >= 1 and
            feature_read_counts[FEATURE_RMSSD] >= 1 and
            feature_clears >= 1 and
            coherent_iterations >= 1 and
            ml_start_writes >= 1
        ):
            break
    else:
        raise AssertionError("timed out waiting for repeated coherent production-loop iterations")

    assert feature_read_counts[FEATURE_STATUS] >= 1, "too few FEATURE_STATUS reads"
    assert feature_read_counts[FEATURE_TIME] >= 1, "too few FEATURE_TIME reads"
    assert feature_read_counts[FEATURE_MOTION] >= 1, "too few FEATURE_MOTION reads"
    assert feature_read_counts[FEATURE_DHR] >= 1, "too few FEATURE_DHR reads"
    assert feature_read_counts[FEATURE_RMSSD] >= 1, "too few FEATURE_RMSSD reads"
    assert feature_clears >= 1, "too few FEATURE_STATUS valid clears"
    assert ml_start_writes >= 1, "too few ML start writes"
    assert coherent_iterations >= 1, "too few coherent feature->WRAM iterations"


@cocotb.test()
async def test_prod_main_alarm_after_five_light_sleep_predictions(dut):
    """Force prod_main into the wake window and require alarm assertion.

    This is a targeted policy test. The required DUT behavior is still real
    firmware execution: prod_main must clear feature-valid, write the ML start
    register, service an ML IRQ, read logits from weight_flash_axi, update
    TEST_CODE, write ALARM_CTRL, and cause the top-level alarm output to assert.

    The forced pieces are only stimulus/acceleration:
      - feature latch values, including timestamps in the 7h..8h window
      - CPU-visible weight_flash_axi logits for class 1
      - short ML-complete IRQ pulses after each observed ML start
      - live CPU/ML enables so the test is not dominated by sleep cadence
    """
    cocotb.start_soon(start_clock(dut))
    await apply_reset(dut)
    await wait_for_boot_load(dut)

    # Wait until prod_main has completed its ML address-register setup. The
    # accelerated AXI-Lite response is enabled only after this point so startup
    # readback checks still verify the real taketwo control path.
    for _ in range(300_000):
        await RisingEdge(dut.clk)
        await ReadOnly()

        if _u(dut.pico_trap):
            raise AssertionError("CPU trap asserted before prod_main feature polling")
        if _u(dut.test_status) == TEST_FAIL:
            raise AssertionError(f"firmware reported FAIL with code 0x{_u(dut.test_code):08x}")
        if mmio_read_active(dut) and _u(dut.pico_mem_addr) == FEATURE_STATUS:
            break
    else:
        raise AssertionError("timed out waiting for prod_main to finish setup and poll FEATURE_STATUS")

    feature_clears = 0
    alarm_write_seen = False
    ml_start_writes = 0
    ml_irq_pulse_cycles = 0
    ml_irq_asserted = False

    await NextTimeStep()
    _force_prod_policy_clocks(dut)
    _force_fast_ml_control_path(dut)
    _force_ml_irq(dut, False)
    _force_prod_features(dut, 0)
    _force_light_sleep_logits(dut)

    try:
        for _ in range(250_000):
            pending_feature_time = None

            await RisingEdge(dut.clk)
            await ReadOnly()

            if _u(dut.pico_trap):
                raise AssertionError("CPU trap asserted during prod_main alarm-policy test")
            if _u(dut.test_status) == TEST_FAIL:
                raise AssertionError(f"firmware reported FAIL with code 0x{_u(dut.test_code):08x}")

            if mmio_write_active(dut):
                addr = _u(dut.pico_mem_addr)
                wdata = _u(dut.pico_mem_wdata)

                if addr == FEATURE_STATUS and (wdata & FEATURE_VALID_MASK):
                    feature_clears += 1
                    if feature_clears == 1:
                        # The first feature establishes prod_main's
                        # start_time_sec baseline. Put the next and following
                        # features inside the wake window.
                        pending_feature_time = WAKE_WINDOW_START_SEC
                    else:
                        pending_feature_time = WAKE_WINDOW_START_SEC + min(feature_clears - 1, 300)

                if addr == ALARM_CTRL_ADDR and (wdata & 1):
                    alarm_write_seen = True

                if addr == ML_START_ADDR and (wdata & 1):
                    # Pulse ML IRQ only after firmware starts inference. If the
                    # source is already high when firmware clears stale pending,
                    # irq_ctrl_mmio will not see a fresh rising edge.
                    ml_start_writes += 1
                    ml_irq_pulse_cycles = 12

            code = _u(dut.test_code)
            alarm_summary_seen = ((code >> 30) & 1) and (((code >> 16) & 0xFF) >= LIGHT_SLEEP_STREAK_REQ)
            if alarm_write_seen and _u(dut.alarm) and alarm_summary_seen:
                break

            # We sampled bus activity in ReadOnly above. Any Force updates must
            # happen after advancing to a writable scheduler phase.
            if pending_feature_time is not None or ml_irq_pulse_cycles > 0 or ml_irq_asserted:
                await NextTimeStep()
                if ml_irq_pulse_cycles > 0:
                    _force_ml_irq(dut, True)
                    ml_irq_asserted = True
                    ml_irq_pulse_cycles -= 1
                elif ml_irq_asserted:
                    _force_ml_irq(dut, False)
                    ml_irq_asserted = False

                if pending_feature_time is not None:
                    _force_prod_features(dut, pending_feature_time)
        else:
            raise AssertionError(
                "timed out waiting for prod_main to assert alarm after five light-sleep predictions "
                f"(feature_clears={feature_clears}, alarm_write_seen={alarm_write_seen}, "
                f"ml_start_writes={ml_start_writes}, alarm={_u(dut.alarm)}, "
                f"test_code=0x{_u(dut.test_code):08x})"
            )

        assert feature_clears >= LIGHT_SLEEP_STREAK_REQ + 1, (
            "expected one baseline feature plus five wake-window features"
        )
        assert ml_start_writes >= LIGHT_SLEEP_STREAK_REQ, "too few ML start writes"
        assert alarm_write_seen, "firmware never wrote ALARM_CTRL bit0"
        assert _u(dut.alarm) == 1, "top-level alarm output did not assert"
    finally:
        await NextTimeStep()
        _release_ml_irq(dut)
        _release_fast_ml_control_path(dut)
        _release_prod_policy_clocks(dut)
        _release_light_sleep_logits(dut)
        _release_prod_features(dut)


@cocotb.test()
async def test_reset_corner_cases_with_forced_wake_and_irq(dut):
    """Exercise reset-adjacent forced wake/IRQ hooks without needing firmware cooperation."""
    cocotb.start_soon(start_clock(dut))

    # Hold reset while both test-force sources are asserted, then release reset
    # only after the force signals have been dropped. This checks that reset
    # prevents stale wake bookkeeping from leaking into post-reset state.
    dut.reset.value = 1
    dut.test_force_irq.value = 1
    await RisingEdge(dut.clk)
    dut.test_force_wake.value = 1
    await ClockCycles(dut.clk, 8)
    dut.test_force_irq.value = 0
    dut.test_force_wake.value = 0
    await ClockCycles(dut.clk, 2)
    dut.reset.value = 0
    await ClockCycles(dut.clk, 2)
    await ReadOnly()

    assert _u(dut.irq_pending) == 0, "forced sources during reset should not leak into pending"
    assert _u(dut.pwr_wake_status) == 0, "forced wake during reset should not leak into wake_status"
    assert _u(dut.pwr_wake_reason) == 0, "forced wake during reset should not leak into wake_reason"
    assert (_u(dut.pico_irq) & FORCED_IRQ_BIT) == 0, "forced IRQ should be clear after reset release"

    # `test_force_wake` maps to IRQ source bit 3. The IRQ controller should
    # still latch it as pending, but bit 3 is not wake-enabled after reset, so it
    # should not generate pwrctrl wake_status.
    await RisingEdge(dut.clk)
    dut.test_force_wake.value = 1
    await ClockCycles(dut.clk, 2)
    dut.test_force_wake.value = 0
    await ClockCycles(dut.clk, 2)
    await ReadOnly()

    assert (_u(dut.irq_pending) & FORCED_WAKE_BIT) != 0, "forced wake should latch into IRQC pending"
    assert (_u(dut.pwr_wake_status) & WAKE_ENABLED_IRQ_BIT) == 0, (
        "non-wake-enabled forced wake source should not latch into wake_status"
    )

    # Use the wake-enabled timer/debug IRQ source for the actual power-controller
    # wake check. pwrctrl_mmio receives the aggregate irqc_wake_req as bit 0, not
    # the original IRQ source index.
    await RisingEdge(dut.clk)
    dut.test_irq_src.value = 0b001
    await ClockCycles(dut.clk, 2)
    dut.test_irq_src.value = 0
    await ClockCycles(dut.clk, 2)
    await ReadOnly()

    assert (_u(dut.irq_pending) & WAKE_ENABLED_IRQ_BIT) != 0, (
        "wake-enabled IRQ source should latch into IRQC pending"
    )
    assert (_u(dut.pwr_wake_status) & WAKE_ENABLED_IRQ_BIT) != 0, (
        "wake-enabled IRQ source should latch aggregate wake_status bit0"
    )
    assert (_u(dut.pwr_wake_reason) & WAKE_ENABLED_IRQ_BIT) == 0, (
        "wake_reason should remain clear while the CPU never transitioned from sleep to awake"
    )

    # Forced IRQ is a direct debug injection into the CPU IRQ vector, so it
    # should assert immediately while high and clear again once released.
    await RisingEdge(dut.clk)
    dut.test_force_irq.value = 1
    await ClockCycles(dut.clk, 1)
    await ReadOnly()
    assert (_u(dut.pico_irq) & FORCED_IRQ_BIT) != 0, "forced IRQ should drive PicoRV32 IRQ bit0"

    await RisingEdge(dut.clk)
    dut.test_force_irq.value = 0
    await ClockCycles(dut.clk, 1)
    await ReadOnly()
    assert (_u(dut.pico_irq) & FORCED_IRQ_BIT) == 0, "forced IRQ should clear after release"
