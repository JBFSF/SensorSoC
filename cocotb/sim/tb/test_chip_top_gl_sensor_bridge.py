import logging
import os
from collections import defaultdict
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ReadOnly, RisingEdge, Timer
from cocotb.utils import get_sim_time

from ref_pipeline.pipeline_ref import PipelineReference, PipelineStepInputs, TopPipelineConfig
from ref_pipeline.trace_loader import load_accel_trace, load_ppg_trace
from ref_pipeline.utils import to_signed


PIN_SIM_REQ = 8
PIN_SIM_ACK = 33
PIN_SIM_RVALID = 34
PIN_SIM_RLAST = 35
PIN_FEATURE_SEEN = 33
PIN_FEATURE_VALID = 34
PIN_EPOCH_END = 35
PIN_ML_GATE = 36

TEST_MODE_MSSD = 0x1
TEST_MODE_DELTA_HR = 0x2
TEST_MODE_TIME = 0x3
TEST_MODE_MOTION = 0x4
TEST_MODE_STATUS = 0x6
DEBUG_BUS_LO = 7
DEBUG_BUS_HI = 22
SENSOR_STATUS_CLEAR = 1 << 10
SENSOR_BRIDGE_EN = 1 << 11

ACC_ADDR = 0x19
PPG_ADDR = 0x64
ACC_REG_OUT_X_L = 0x28
PPG_REG_FIFO_ACCESS = 0x60

CLK_HZ = 1000
GT_EPOCH_HZ = 100
GT_EPOCH_COUNT_MAX = 300
SAMPLE_PERIOD_TICKS = 10
PAD_MODE_SETTLE_NS = 20
CLOCK_PERIOD_PS = 40_000

ROOT = Path(__file__).resolve().parents[3]
SIM_DATA = ROOT / "cocotb" / "sim" / "data"


def _pad_bit(dut, bit):
    return str(dut.bidir_sample.value[bit])


def _pad_slice_int(dut, high, low):
    return dut.bidir_sample.value[high:low].to_unsigned()


def _pad_slice_resolved_int(dut, high, low):
    value = dut.bidir_sample.value[high:low]
    bits = str(value)
    unknowns = sum(bit not in "01" for bit in bits)
    resolved = "".join(bit if bit in "01" else "0" for bit in bits)
    return int(resolved, 2), unknowns


def _input_value(mode=TEST_MODE_MSSD, *, bridge=True, clear=False):
    value = mode & 0x1F
    if bridge:
        value |= SENSOR_BRIDGE_EN
    if clear:
        value |= SENSOR_STATUS_CLEAR
    return value


def _u16_to_s16(value):
    return to_signed(value, 16)


async def _startup(dut, post_reset_ns=400):
    dut.input_drv.value = _input_value(TEST_MODE_MSSD, bridge=True)
    dut.bidir_drv.value = 0
    dut.bidir_oe.value = 0
    dut.rst_n_drv.value = 0
    cocotb.start_soon(Clock(dut.clk_drv, 40, "ns").start())
    await Timer(400, "ns")
    dut.rst_n_drv.value = 1
    if post_reset_ns:
        await Timer(post_reset_ns, "ns")


async def _timer_step_ref(duration_ns, ref=None):
    start_ps = int(get_sim_time("ps"))
    await Timer(duration_ns, "ns")
    if ref is not None:
        end_ps = int(get_sim_time("ps"))
        for _ in range((end_ps // CLOCK_PERIOD_PS) - (start_ps // CLOCK_PERIOD_PS)):
            ref.step()


@cocotb.test()
async def test_chip_top_gl_sensor_bridge_reaches_models(dut):
    """Check that the special GL netlist drives sensor sim transactions through pads."""

    log = logging.getLogger("gl_sensor_bridge")
    await _startup(dut)

    saw_req = False
    saw_ack = False
    saw_rvalid = False
    seen_addrs = set()

    for _ in range(200_000):
        await RisingEdge(dut.clk_drv)

        if _pad_bit(dut, PIN_SIM_REQ) == "1":
            saw_req = True
            seen_addrs.add(_pad_slice_int(dut, 16, 10))

        saw_ack = saw_ack or (_pad_bit(dut, PIN_SIM_ACK) == "1")
        saw_rvalid = saw_rvalid or (_pad_bit(dut, PIN_SIM_RVALID) == "1")

        if saw_req and saw_ack and saw_rvalid:
            break

    log.info("sensor bridge addrs seen: %s", [f"0x{addr:02x}" for addr in sorted(seen_addrs)])

    assert saw_req, "chip did not drive a sensor sim_req onto bidir[8]"
    assert seen_addrs & {0x19, 0x64}, "sensor bridge did not expose accel/PPG target addresses"
    assert saw_ack, "sensor models did not return sim_ack through bidir[33]"
    assert saw_rvalid, "sensor models did not return sim_rvalid through bidir[34]"


class PadPipelineReference:
    """Reference model fed only from pad-visible bridge traffic and cycle count."""

    def __init__(self):
        self.ref = PipelineReference(config=TopPipelineConfig())
        self.cycle = 0
        self.prev_epoch_end = False
        self.pending = defaultdict(list)
        self.prev_motion = None
        self.prev_beat = None
        self.prev_mssd = None
        self.prev_quality = None
        self.last_feature = None
        self.feature_count = 0
        self.ppg_last_sample_time = 0
        self.ppg_last_observed_sample_time = 0
        self.last_rr_cycle = None
        self.last_rr_interval = 0
        self.last_delta_hr = 0
        self.rr_count = 0
        self.motion_epoch_history = []

    def schedule_accel(self, due_cycle, ax, ay, az):
        self.pending[due_cycle].append(("accel", ax, ay, az))

    def schedule_ppg(self, due_cycle, sample, sample_time):
        self.pending[due_cycle].append(("ppg", sample, sample_time))

    def step(self):
        self.cycle += 1
        events = self.pending.pop(self.cycle, [])

        accel_valid = False
        ax = ay = az = 0
        ppg_valid = False
        ppg_sample = 0
        ppg_sample_time = 0

        for event in events:
            if event[0] == "accel":
                _, ax, ay, az = event
                accel_valid = True
            elif event[0] == "ppg":
                _, ppg_sample, ppg_sample_time = event
                ppg_valid = True

        cycles_per_epoch = CLK_HZ // GT_EPOCH_HZ
        epoch_end = (self.cycle % (cycles_per_epoch * GT_EPOCH_COUNT_MAX)) == 0
        seconds = self.cycle // CLK_HZ

        inputs = PipelineStepInputs(
            rst=False,
            accel_valid=accel_valid,
            ax=ax,
            ay=ay,
            az=az,
            ppg_valid=ppg_valid,
            ppg_sample=ppg_sample,
            ppg_sample_time=ppg_sample_time,
            beat_pulse=bool(self.prev_beat and self.prev_beat.beat_pulse),
            beat_quality=self.prev_beat.beat_quality if self.prev_beat else 0,
            double_beat=bool(self.prev_beat and self.prev_beat.double_beat),
            missed_beat=bool(self.prev_beat and self.prev_beat.missed_beat),
            rr_valid=bool(self.prev_beat and self.prev_beat.rr_valid),
            rr_accepted=bool(self.prev_beat and self.prev_beat.rr_accepted),
            rr_interval=self.prev_beat.rr_interval if self.prev_beat else 0,
            delta_hr=self.prev_beat.delta_hr_bpm if self.prev_beat else 0,
            motion_epoch=bool(self.prev_motion and self.prev_motion.epoch_done),
            motion_energy=self.prev_motion.motion_energy_epoch if self.prev_motion else 0,
            mssd_valid=bool(self.prev_mssd and self.prev_mssd.mssd_valid),
            mssd_epoch=self.prev_mssd.mssd_epoch if self.prev_mssd else 0,
            fifo_overflow_event=False,
            ppg_i2c_err_event=False,
            epoch_end=epoch_end,
            epoch_end_d=self.prev_epoch_end,
            time_value=seconds,
            ml_update_gate=bool(self.prev_quality and self.prev_quality.ml_update_gate),
        )

        outputs = self.ref.step(inputs)
        self.prev_motion = outputs.motion
        self.prev_beat = outputs.beat
        self.prev_mssd = outputs.mssd
        self.prev_quality = outputs.quality
        self.prev_epoch_end = epoch_end

        if outputs.beat.rr_valid:
            self.last_rr_cycle = self.cycle
            self.last_rr_interval = outputs.beat.rr_interval
            self.last_delta_hr = outputs.beat.delta_hr_bpm
            self.rr_count += 1

        if outputs.motion.epoch_done:
            self.motion_epoch_history.append((self.cycle, outputs.motion.motion_energy_epoch & 0xFFFF))

        if outputs.feature.feat_valid:
            self.last_feature = outputs.feature
            self.feature_count += 1


class BridgeMonitor:
    def __init__(self, dut, ref):
        self.dut = dut
        self.ref = ref
        self.current = None
        self.accel_index = 0
        self.ppg_index = 0
        self.accel_alignments = 0
        self.ppg_alignments = 0
        self.accel_trace = load_accel_trace(SIM_DATA / "accel_digital.csv")
        self.ppg_trace = load_ppg_trace(SIM_DATA / "ppg_digital.csv")
        self.ppg_fifo_bytes_avail = 0
        self.ppg_fifo_thresh_words = 0
        self.ppg_next_time = None
        self.accel_events = []

    @staticmethod
    def _find_trace_match(trace, start, observed, getter, window=32):
        for index in range(start, min(start + window, len(trace))):
            if getter(trace[index]) == observed:
                return index
        return None

    def safe_to_pause(self):
        return self.current is None and _pad_bit(self.dut, PIN_SIM_REQ) != "1" and _pad_bit(self.dut, PIN_SIM_RVALID) != "1"

    def observe(self):
        if self.current is None and _pad_bit(self.dut, PIN_SIM_REQ) == "1":
            self.current = {
                "addr": _pad_slice_int(self.dut, 16, 10),
                "reg": _pad_slice_int(self.dut, 24, 17),
                "len": _pad_slice_int(self.dut, 32, 25),
                "write": _pad_slice_int(self.dut, 9, 9),
                "bytes": [],
            }

        if self.current and self.current["write"]:
            if _pad_bit(self.dut, PIN_SIM_ACK) == "1":
                self.current = None
            return

        if not self.current or _pad_bit(self.dut, PIN_SIM_RVALID) != "1":
            return

        byte = _pad_slice_int(self.dut, 7, 0)
        self.current["bytes"].append(byte)

        is_ppg_read = self.current["addr"] == PPG_ADDR and not self.current["write"]

        if is_ppg_read and self.current["reg"] == PPG_REG_FIFO_ACCESS and len(self.current["bytes"]) % 2 == 0:
            lo = self.current["bytes"][-2]
            hi = self.current["bytes"][-1]
            sample = lo | (hi << 8)
            if self.ppg_index >= len(self.ppg_trace):
                raise AssertionError("PPG trace exhausted while monitoring GL bridge")
            if self.ppg_next_time is None:
                samples_in_burst = max(1, self.current["len"] // 2)
                backfill = (samples_in_burst - 1) * SAMPLE_PERIOD_TICKS
                start_time = max(0, self.ref.cycle - backfill)
                if self.ref.ppg_last_sample_time:
                    start_time = max(start_time, self.ref.ppg_last_sample_time + SAMPLE_PERIOD_TICKS)
                self.ppg_next_time = start_time
            expected = self.ppg_trace[self.ppg_index].value
            if sample != expected:
                matched_index = self._find_trace_match(
                    self.ppg_trace, self.ppg_index + 1, sample, lambda entry: entry.value
                )
                assert matched_index is not None, (
                    f"PPG sample[{self.ppg_index}] bridge data mismatch: got={sample} exp={expected}"
                )
                if self.ppg_alignments < 3:
                    self.dut._log.info(
                        "aligning PPG trace index from %d to %d after prior sensor-model reads",
                        self.ppg_index,
                        matched_index,
                    )
                self.ppg_alignments += 1
                self.ppg_index = matched_index
            self.ppg_index += 1
            sample_time = self.ppg_next_time
            self.ppg_next_time += SAMPLE_PERIOD_TICKS
            self.ref.ppg_last_sample_time = sample_time
            self.ref.ppg_last_observed_sample_time = sample_time
            self.ref.schedule_ppg(self.ref.cycle + 2, sample, sample_time)

        if _pad_bit(self.dut, PIN_SIM_RLAST) != "1":
            return

        if is_ppg_read and self.current["reg"] == 0x00 and len(self.current["bytes"]) >= 2:
            status = self.current["bytes"][0] | (self.current["bytes"][1] << 8)
            self.ppg_fifo_bytes_avail = (status >> 8) & 0xFF

        if is_ppg_read and self.current["reg"] == 0x06 and len(self.current["bytes"]) >= 2:
            threshold = self.current["bytes"][0] | (self.current["bytes"][1] << 8)
            self.ppg_fifo_thresh_words = (threshold >> 8) & 0x3F
            max_burst_bytes = 32 * 2
            read_bytes_pre = min(self.ppg_fifo_bytes_avail, max_burst_bytes)
            read_bytes = (read_bytes_pre // 2) * 2
            read_samples = read_bytes // 2
            threshold_words = self.ppg_fifo_thresh_words or 8
            threshold_bytes = threshold_words * 2
            should_read = self.ppg_fifo_bytes_avail >= threshold_bytes and read_bytes >= 2
            if should_read:
                backfill = max(0, read_samples - 1) * SAMPLE_PERIOD_TICKS
                decide_cycle = self.ref.cycle + 1
                start_time = max(0, decide_cycle - backfill)
                if self.ref.ppg_last_sample_time:
                    start_time = max(start_time, self.ref.ppg_last_sample_time + SAMPLE_PERIOD_TICKS)
                self.ppg_next_time = start_time

        if (
            self.current["addr"] == ACC_ADDR
            and self.current["reg"] == ACC_REG_OUT_X_L
            and not self.current["write"]
        ):
            data = self.current["bytes"]
            if len(data) != 6:
                raise AssertionError(f"accelerometer read returned {len(data)} bytes, expected 6")
            ax = _u16_to_s16(data[0] | (data[1] << 8))
            ay = _u16_to_s16(data[2] | (data[3] << 8))
            az = _u16_to_s16(data[4] | (data[5] << 8))
            if self.accel_index >= len(self.accel_trace):
                raise AssertionError("accelerometer trace exhausted while monitoring GL bridge")
            expected = self.accel_trace[self.accel_index]
            got_triplet = (ax, ay, az)
            exp_triplet = (expected.ax, expected.ay, expected.az)
            if got_triplet != exp_triplet:
                matched_index = self._find_trace_match(
                    self.accel_trace,
                    self.accel_index + 1,
                    got_triplet,
                    lambda entry: (entry.ax, entry.ay, entry.az),
                )
                assert matched_index is not None, (
                    f"accelerometer sample[{self.accel_index}] bridge data mismatch: got={got_triplet} exp={exp_triplet}"
                )
                if self.accel_alignments < 3:
                    self.dut._log.info(
                        "aligning accelerometer trace index from %d to %d after prior sensor-model reads",
                        self.accel_index,
                        matched_index,
                    )
                self.accel_alignments += 1
                self.accel_index = matched_index
            self.accel_index += 1
            mag = abs(ax) + abs(ay) + abs(az)
            self.accel_events.append((self.ref.cycle, self.ref.cycle + 1, self.accel_index - 1, ax, ay, az, mag))
            self.ref.schedule_accel(self.ref.cycle + 1, ax, ay, az)

        self.current = None


async def _read_debug_bus(dut, mode, ref=None):
    dut.input_drv.value = _input_value(mode, bridge=False)
    await _timer_step_ref(PAD_MODE_SETTLE_NS, ref)
    value = dut.bidir_sample.value[DEBUG_BUS_HI:DEBUG_BUS_LO]
    try:
        return value.to_unsigned()
    except ValueError as exc:
        extra = f"; gl_motion={_gl_motion_debug(dut)}" if mode == TEST_MODE_MOTION else ""
        raise AssertionError(f"debug mode 0x{mode:x} has unknown pad bits: {value}{extra}") from exc


def _logic_to_int(value):
    bits = str(value)
    if any(bit not in "01" for bit in bits):
        return None
    return int(bits, 2)


def _to_signed(value, width):
    if value is None:
        return None
    sign = 1 << (width - 1)
    mask = (1 << width) - 1
    value &= mask
    return value - (1 << width) if value & sign else value


def _gl_signed_vector(dut, escaped_base, width):
    return _to_signed(_gl_vector(dut, escaped_base, width), width)


def _gl_scalar(dut, escaped_name):
    try:
        return _logic_to_int(dut.u_chip._id(f"\\{escaped_name} ", extended=False).value)
    except (AttributeError, KeyError, ValueError):
        return None


def _gl_vector(dut, escaped_base, width):
    value = 0
    for bit in range(width):
        bit_value = _gl_scalar(dut, f"{escaped_base}[{bit}]")
        if bit_value is None:
            return None
        value |= bit_value << bit
    return value


def _gl_delta_debug(dut):
    return {
        "rr_valid_w": _gl_scalar(dut, "i_chip_core.u_top.rr_valid_w"),
        "rr_interval_w": _gl_vector(dut, "i_chip_core.u_top.rr_interval_w", 16),
        "delta_hr_w": _to_signed(_gl_vector(dut, "i_chip_core.u_top.delta_hr_w", 16), 16),
        "delta_hr_feat_top_w": _to_signed(_gl_vector(dut, "i_chip_core.delta_hr_feat_top_w", 16), 16),
        "have_prev_hr_r": _gl_scalar(dut, "i_chip_core.u_top.u_beat_detect.have_prev_hr_r"),
        "prev_hr_bpm_r": _gl_vector(dut, "i_chip_core.u_top.u_beat_detect.prev_hr_bpm_r", 16),
        "ppg_sample_time_w": _gl_vector(dut, "i_chip_core.u_top.ppg_sample_time_w", 32),
    }


def _gl_motion_debug(dut):
    return {
        "motion_epoch_w": _gl_scalar(dut, "i_chip_core.u_top.motion_epoch_w"),
        "motion_energy_w": _gl_vector(dut, "i_chip_core.u_top.motion_energy_w", 16),
        "motion_feat_top_w": _gl_vector(dut, "i_chip_core.motion_feat_top_w", 16),
        "motion_accum_lo": _gl_vector(dut, "i_chip_core.u_top.u_motion_process.motion_energy_accum_r", 16),
        "epoch_end_w": _gl_scalar(dut, "i_chip_core.u_top.epoch_end_w"),
        "epoch_end_d": _gl_scalar(dut, "i_chip_core.u_top.epoch_end_d"),
        "accel_valid_w": _gl_scalar(dut, "i_chip_core.u_top.accel_valid_w"),
    }


def _recent_accel_debug(ref):
    monitor = getattr(ref, "monitor", None)
    if monitor is None:
        return ""
    recent = monitor.accel_events[-8:]
    motion_epochs = getattr(ref, "motion_epoch_history", [])[-4:]
    epoch_sums = []
    for start, stop in ((0, 3000), (3000, 6000), (6000, 9000)):
        total = sum(event[6] for event in monitor.accel_events if start < event[1] <= stop)
        count = sum(1 for event in monitor.accel_events if start < event[1] <= stop)
        epoch_sums.append((start, stop, count, total & 0xFFFF))
    return (
        " motion_epochs=" + repr(motion_epochs)
        + " epoch_sums=" + repr(epoch_sums)
        + " recent_accel=" + repr(recent)
    )


async def _clear_feature_seen(dut, ref=None):
    dut.input_drv.value = _input_value(TEST_MODE_MSSD, bridge=False, clear=True)
    await RisingEdge(dut.clk_drv)
    await ReadOnly()
    if ref is not None:
        ref.step()
    await Timer(1, "ps")
    dut.input_drv.value = _input_value(TEST_MODE_MSSD, bridge=False, clear=False)
    await _timer_step_ref(PAD_MODE_SETTLE_NS, ref)


async def _check_latest_feature_on_debug_pads(dut, expected, ref=None):
    expected_by_mode = {
        TEST_MODE_MSSD: expected.mssd_feat,
        TEST_MODE_DELTA_HR: expected.delta_hr_feat,
        TEST_MODE_TIME: expected.time_feat,
        TEST_MODE_MOTION: expected.motion_feat,
    }

    for mode, expected_value in expected_by_mode.items():
        got = await _read_debug_bus(dut, mode, ref)
        assert got == (expected_value & 0xFFFF), (
            f"debug mode 0x{mode:x} mismatch: got=0x{got:04x} expected=0x{expected_value & 0xFFFF:04x}"
            + (
                f"; ref_motion={expected.motion_feat & 0xFFFF:04x} gl_motion={_gl_motion_debug(dut)}"
                f"{_recent_accel_debug(ref)}"
                if ref is not None and mode == TEST_MODE_MOTION
                else ""
            )
            + (
                f"; ref_rr_count={ref.rr_count} ref_last_rr_cycle={ref.last_rr_cycle} "
                f"ref_last_rr_interval={ref.last_rr_interval} ref_last_delta_hr={ref.last_delta_hr} "
                f"ref_last_ppg_time={ref.ppg_last_observed_sample_time} "
                f"gl_delta={_gl_delta_debug(dut)}"
                if ref is not None and mode == TEST_MODE_DELTA_HR
                else ""
            )
        )


def _maybe_internal_debug(dut):
    signals = {}
    try:
        chip = dut.u_chip
    except AttributeError:
        return signals

    for name in (
        "sensor_feature_valid_seen_q",
        "feat_valid_w",
        "epoch_end_w",
        "ml_update_gate_w",
        "invalid_reason_w",
        "feat_en",
        "test_mode_w",
    ):
        try:
            handle = chip._id(f"\\i_chip_core.{name} ", extended=False)
            signals[name] = str(handle.value)
        except (AttributeError, KeyError, ValueError):
            try:
                signals[name] = str(getattr(chip, name).value)
            except AttributeError:
                pass
    return signals


@cocotb.test()
async def test_chip_top_gl_sensor_bridge_debug_features_match_python_reference(dut):
    """Run raw sensor data through GL and compare pad debug features to Python refs."""

    log = logging.getLogger("gl_sensor_bridge_features")
    await _startup(dut, post_reset_ns=0)

    ref = PadPipelineReference()
    monitor = BridgeMonitor(dut, ref)
    ref.monitor = monitor

    checked_features = 0
    target_features = int(os.getenv("GL_SENSOR_BRIDGE_FEATURES", "4"))
    max_cycles = int(os.getenv("GL_SENSOR_BRIDGE_MAX_CYCLES", "30000"))
    warmup_features = int(os.getenv("GL_SENSOR_BRIDGE_WARMUP_FEATURES", "1"))
    debug_internals = os.getenv("GL_SENSOR_BRIDGE_DEBUG_INTERNALS") == "1"
    status_polls = 0
    feature_seen_polls = 0
    feature_valid_polls = 0
    epoch_seen_polls = 0
    ml_gate_seen_polls = 0
    status_debug_epoch_polls = 0
    status_debug_ml_gate_polls = 0
    status_debug_invalid_or = 0
    status_debug_unknown_polls = 0
    last_feature_poll_cycle = -1_000_000
    next_debug_poll_cycle = 1500
    consumed_ref_features = 0

    for _ in range(max_cycles):
        await RisingEdge(dut.clk_drv)
        await ReadOnly()

        ref.step()
        monitor.observe()

        feature_poll_due = (
            ref.feature_count > consumed_ref_features and (_ - last_feature_poll_cycle) >= 100
        )
        debug_poll_due = debug_internals and _ >= next_debug_poll_cycle
        if not (feature_poll_due or debug_poll_due):
            continue

        if not monitor.safe_to_pause():
            continue

        await Timer(1, "ps")
        dut.input_drv.value = _input_value(TEST_MODE_MSSD, bridge=False)
        await _timer_step_ref(PAD_MODE_SETTLE_NS, ref)
        status_polls += 1
        feature_seen = _pad_bit(dut, PIN_FEATURE_SEEN) == "1"
        feature_valid = _pad_bit(dut, PIN_FEATURE_VALID) == "1"
        epoch_seen = _pad_bit(dut, PIN_EPOCH_END) == "1"
        ml_gate_seen = _pad_bit(dut, PIN_ML_GATE) == "1"
        feature_seen_polls += int(feature_seen)
        feature_valid_polls += int(feature_valid)
        epoch_seen_polls += int(epoch_seen)
        ml_gate_seen_polls += int(ml_gate_seen)
        dut.input_drv.value = _input_value(TEST_MODE_STATUS, bridge=False)
        await _timer_step_ref(PAD_MODE_SETTLE_NS, ref)
        status_debug, status_unknowns = _pad_slice_resolved_int(dut, DEBUG_BUS_HI, DEBUG_BUS_LO)
        status_debug_unknown_polls += int(status_unknowns != 0)
        status_debug_ml_gate_polls += int(bool(status_debug & (1 << 15)))
        status_debug_epoch_polls += int(bool(status_debug & (1 << 14)))
        status_debug_invalid_or |= (status_debug >> 6) & 0xFF

        if feature_poll_due:
            last_feature_poll_cycle = _
        if debug_poll_due:
            next_debug_poll_cycle += 1500

        if debug_internals and (debug_poll_due or feature_seen or ml_gate_seen):
            dut._log.info(
                "cycle=%d status pads: seen=%d valid=%d epoch=%d ml_gate=%d status_debug=0x%04x status_unknowns=%d internals=%s",
                _,
                feature_seen,
                feature_valid,
                epoch_seen,
                ml_gate_seen,
                status_debug,
                status_unknowns,
                _maybe_internal_debug(dut),
            )

        if not feature_seen:
            dut.input_drv.value = _input_value(TEST_MODE_MSSD, bridge=True)
            continue

        assert ref.last_feature is not None, "GL reported feature_valid before Python reference did"
        if warmup_features > 0:
            warmup_features -= 1
            consumed_ref_features += 1
            log.info("skipping warm-up feature vector before strict debug-pad comparison")
            await _clear_feature_seen(dut, ref)
            dut.input_drv.value = _input_value(TEST_MODE_MSSD, bridge=True)
            continue

        await _check_latest_feature_on_debug_pads(dut, ref.last_feature, ref)
        checked_features += 1
        consumed_ref_features += 1
        log.info(
            "feature[%d] matched: time=%d motion=%d delta_hr=%d mssd=%d",
            checked_features,
            ref.last_feature.time_feat,
            ref.last_feature.motion_feat,
            ref.last_feature.delta_hr_feat,
            ref.last_feature.mssd_feat,
        )

        await _clear_feature_seen(dut, ref)
        dut.input_drv.value = _input_value(TEST_MODE_MSSD, bridge=True)

        if checked_features >= target_features:
            break
    else:
        raise AssertionError(
            f"timed out after {max_cycles} cycles; checked {checked_features}/{target_features} feature vectors; "
            f"reference_features={ref.feature_count}, accel_samples={monitor.accel_index}, "
            f"ppg_samples={monitor.ppg_index}, status_polls={status_polls}, "
            f"feature_seen_polls={feature_seen_polls}, feature_valid_polls={feature_valid_polls}, "
            f"epoch_seen_polls={epoch_seen_polls}, ml_gate_seen_polls={ml_gate_seen_polls}, "
            f"status_debug_epoch_polls={status_debug_epoch_polls}, "
            f"status_debug_ml_gate_polls={status_debug_ml_gate_polls}, "
            f"status_debug_invalid_or=0x{status_debug_invalid_or:02x}, "
            f"status_debug_unknown_polls={status_debug_unknown_polls}, "
            f"accel_alignments={monitor.accel_alignments}, ppg_alignments={monitor.ppg_alignments}."
        )

    assert monitor.accel_index > 0, "no accelerometer samples were observed through the bridge"
    assert monitor.ppg_index > 0, "no PPG samples were observed through the bridge"
    assert ref.feature_count >= checked_features, "reference did not produce enough feature vectors"
