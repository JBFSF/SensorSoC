import logging
import os
from collections import defaultdict
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ReadOnly, RisingEdge, Timer
from cocotb.utils import get_sim_time

from ref_pipeline.pipeline_ref import PipelineReference, PipelineStepInputs, TopPipelineConfig
from ref_pipeline.trace_loader import load_accel_trace, load_ppg_trace


SENSOR_SCL_PAD = 23
SENSOR_SDA_PAD = 24

TEST_MODE_MSSD = 0x1
TEST_MODE_DELTA_HR = 0x2
TEST_MODE_TIME = 0x3
TEST_MODE_MOTION = 0x4
DEBUG_BUS_LO = 7
DEBUG_BUS_HI = 22

ACC_ADDR = 0x19
PPG_ADDR = 0x64
ACC_REG_CTRL1 = 0x20
ACC_REG_RANGE = 0x23
ACC_REG_STATUS = 0x27
ACC_REG_OUT_X_L = 0x28
PPG_REG_STATUS = 0x00
PPG_REG_FIFO_THRESH = 0x06
PPG_REG_FIFO_ACCESS_ENA = 0x5F
PPG_REG_FIFO_ACCESS = 0x60

CLK_HZ = 10_000_000
GT_EPOCH_HZ = 100
GT_EPOCH_COUNT_MAX = 1000
SAMPLE_PERIOD_TICKS = 10
PAD_MODE_SETTLE_NS = 20
CLOCK_PERIOD_PS = 40_000

ROOT = Path(__file__).resolve().parents[3]
SIM_DATA = ROOT / "cocotb" / "sim" / "data"


def _input_value(mode=TEST_MODE_MSSD):
    return mode & 0x1F


async def _startup(dut, post_reset_ns=0):
    dut.input_drv.value = _input_value(TEST_MODE_MSSD)
    dut.bidir_drv.value = 0
    dut.bidir_oe.value = 0
    dut.sensor_sda_drive_low.value = 0
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


class PadPipelineReference:
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

        if outputs.feature.feat_valid:
            self.last_feature = outputs.feature
            self.feature_count += 1


class SensorI2CBfm:
    def __init__(self, dut, ref=None):
        self.dut = dut
        self.ref = ref
        self.log = logging.getLogger("sensor_i2c_bfm")
        self.accel_trace = load_accel_trace(SIM_DATA / "accel_digital.csv")
        self.ppg_trace = load_ppg_trace(SIM_DATA / "ppg_digital.csv")
        self.accel_index = 0
        self.ppg_index = 0
        self.transactions = 0
        self.accel_reads = 0
        self.ppg_reads = 0
        self.writes = 0
        self.seen_addrs = set()
        self.ppg_next_time = 0
        self._pending_start = False

    def _scl_is_high(self):
        return str(self.dut.sensor_scl_sample.value) == "1"

    def _sda_is_high(self):
        return str(self.dut.sensor_sda_sample.value) == "1"

    def _drive_sda_low(self, enable):
        self.dut.sensor_sda_drive_low.value = 1 if enable else 0

    async def wait_start(self):
        if self._pending_start:
            self._pending_start = False
            return
        while True:
            await FallingEdge(self.dut.sensor_sda_sample)
            await ReadOnly()
            if self._scl_is_high():
                return

    async def recv_byte(self):
        value = 0
        for bit in range(7, -1, -1):
            await RisingEdge(self.dut.sensor_scl_sample)
            await ReadOnly()
            if self._sda_is_high():
                value |= 1 << bit
        return value

    async def send_ack(self):
        await FallingEdge(self.dut.sensor_scl_sample)
        self._drive_sda_low(True)
        await RisingEdge(self.dut.sensor_scl_sample)
        await FallingEdge(self.dut.sensor_scl_sample)
        self._drive_sda_low(False)

    async def send_byte(self, value):
        for bit in range(7, -1, -1):
            await FallingEdge(self.dut.sensor_scl_sample)
            self._drive_sda_low(((value >> bit) & 1) == 0)
            await RisingEdge(self.dut.sensor_scl_sample)
        await FallingEdge(self.dut.sensor_scl_sample)
        self._drive_sda_low(False)
        await RisingEdge(self.dut.sensor_scl_sample)
        await ReadOnly()
        master_ack = not self._sda_is_high()
        await FallingEdge(self.dut.sensor_scl_sample)
        return master_ack

    def _accel_response(self, reg):
        if reg == ACC_REG_STATUS:
            return [0x01], None
        if reg == ACC_REG_OUT_X_L:
            if self.accel_index >= len(self.accel_trace):
                raise AssertionError("accelerometer trace exhausted")
            sample = self.accel_trace[self.accel_index]
            self.accel_index += 1
            ax = sample.ax & 0xFFFF
            ay = sample.ay & 0xFFFF
            az = sample.az & 0xFFFF
            data = [ax & 0xFF, ax >> 8, ay & 0xFF, ay >> 8, az & 0xFF, az >> 8]
            return data, sample
        return [0x00], None

    def _ppg_static_response(self, reg):
        if reg == PPG_REG_STATUS:
            return [0x00, 0x10]
        if reg == PPG_REG_FIFO_THRESH:
            return [0x00, 0x02]
        if reg != PPG_REG_FIFO_ACCESS:
            return [0x00]
        return None

    def _next_ppg_fifo_byte(self, byte_index):
        if byte_index % 2 == 0:
            if self.ppg_index >= len(self.ppg_trace):
                raise AssertionError("PPG trace exhausted")
            sample = self.ppg_trace[self.ppg_index]
            self.ppg_index += 1
            self._last_ppg_sample = sample.value
            return sample.value & 0xFF
        sample = self._last_ppg_sample
        sample_time = self.ppg_next_time
        self.ppg_next_time += SAMPLE_PERIOD_TICKS
        if self.ref is not None:
            self.ref.ppg_last_sample_time = sample_time
            self.ref.ppg_last_observed_sample_time = sample_time
            self.ref.schedule_ppg(self.ref.cycle + 2, sample, sample_time)
        return (sample >> 8) & 0xFF

    async def _send_response(self, addr, reg):
        byte_index = 0
        if addr == ACC_ADDR:
            response, accel_sample = self._accel_response(reg)
            self.accel_reads += int(reg == ACC_REG_OUT_X_L)
        else:
            response = self._ppg_static_response(reg)
            accel_sample = None
            self.ppg_reads += int(reg == PPG_REG_FIFO_ACCESS)

        while True:
            if response is None:
                byte = self._next_ppg_fifo_byte(byte_index)
            else:
                byte = response[byte_index] if byte_index < len(response) else 0x00
            master_ack = await self.send_byte(byte)
            byte_index += 1
            if not master_ack:
                break

        if accel_sample is not None and self.ref is not None:
            self.ref.schedule_accel(
                self.ref.cycle + 2,
                accel_sample.ax,
                accel_sample.ay,
                accel_sample.az,
            )

    async def run(self):
        self._drive_sda_low(False)
        while True:
            await self.wait_start()
            addr_rw = await self.recv_byte()
            addr = (addr_rw >> 1) & 0x7F
            read = bool(addr_rw & 1)
            if addr not in (ACC_ADDR, PPG_ADDR):
                continue
            self.seen_addrs.add(addr)
            await self.send_ack()

            if read:
                await self._send_response(addr, 0x00)
                self.transactions += 1
                continue

            reg = await self.recv_byte()
            await self.send_ack()

            if (addr == ACC_ADDR and reg in (ACC_REG_CTRL1, ACC_REG_RANGE)) or (
                addr == PPG_ADDR and reg == PPG_REG_FIFO_ACCESS_ENA
            ):
                _ = await self.recv_byte()
                await self.send_ack()
                self.writes += 1
                self.transactions += 1
                continue

            await self.wait_start()
            addr_rw = await self.recv_byte()
            read_addr = (addr_rw >> 1) & 0x7F
            if read_addr != addr or not (addr_rw & 1):
                raise AssertionError(
                    f"unexpected repeated-start address 0x{addr_rw:02x} after addr=0x{addr:02x} reg=0x{reg:02x}"
                )
            await self.send_ack()
            await self._send_response(addr, reg)
            self.transactions += 1


async def _run_pad_i2c_smoke(dut):
    await _startup(dut)
    bfm = SensorI2CBfm(dut)
    cocotb.start_soon(bfm.run())

    saw_scl_toggle = False
    last_scl = str(dut.sensor_scl_sample.value)
    max_cycles = int(os.getenv("GL_SENSOR_I2C_SMOKE_CYCLES", "250000"))

    for _ in range(max_cycles):
        await RisingEdge(dut.clk_drv)
        await ReadOnly()
        scl = str(dut.sensor_scl_sample.value)
        saw_scl_toggle = saw_scl_toggle or (scl != last_scl)
        last_scl = scl
        if saw_scl_toggle and bfm.accel_reads > 0 and bfm.writes >= 2:
            break
    else:
        raise AssertionError(
            f"timed out waiting for pad-level sensor I2C; scl_toggle={saw_scl_toggle}, "
            f"transactions={bfm.transactions}, writes={bfm.writes}, accel_reads={bfm.accel_reads}, "
            f"ppg_reads={bfm.ppg_reads}, addrs={[hex(a) for a in sorted(bfm.seen_addrs)]}"
        )

    assert ACC_ADDR in bfm.seen_addrs, "accelerometer I2C address was not observed on sensor pads"
    assert bfm.accel_reads > 0, "no accelerometer data read completed over sensor I2C pads"
    return bfm


@cocotb.test()
async def test_chip_top_gl_sensor_bridge_reaches_models(dut):
    """Check GL sensor traffic over the real sensor I2C pads."""

    await _run_pad_i2c_smoke(dut)


async def _read_debug_bus(dut, mode, ref=None):
    dut.input_drv.value = _input_value(mode)
    await _timer_step_ref(PAD_MODE_SETTLE_NS, ref)
    value = dut.bidir_sample.value[DEBUG_BUS_HI:DEBUG_BUS_LO]
    try:
        return value.to_unsigned()
    except ValueError as exc:
        raise AssertionError(f"debug mode 0x{mode:x} has unknown pad bits: {value}") from exc


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
            f"debug mode 0x{mode:x} mismatch: got=0x{got:04x} expected=0x{expected_value & 0xFFFF:04x}; "
            f"ref_rr_count={ref.rr_count if ref is not None else 'n/a'} "
            f"ref_last_rr_cycle={ref.last_rr_cycle if ref is not None else 'n/a'}"
        )


@cocotb.test()
async def test_chip_top_gl_sensor_bridge_debug_features_match_python_reference(dut):
    """Run sensor pad I2C and optionally compare debug-pad features to Python refs.

    The current production GL netlist is built with the real 10 MHz/10 s epoch
    constants. Set GL_SENSOR_I2C_FULL_FEATURES=1 to run the long feature check;
    otherwise this target performs the pad-level I2C connectivity check.
    """

    if os.getenv("GL_SENSOR_I2C_FULL_FEATURES") != "1":
        await _run_pad_i2c_smoke(dut)
        return

    log = logging.getLogger("gl_sensor_i2c_features")
    await _startup(dut, post_reset_ns=0)

    ref = PadPipelineReference()
    bfm = SensorI2CBfm(dut, ref)
    cocotb.start_soon(bfm.run())

    checked_features = 0
    target_features = int(os.getenv("GL_SENSOR_BRIDGE_FEATURES", "1"))
    max_cycles = int(os.getenv("GL_SENSOR_BRIDGE_MAX_CYCLES", "25000000"))
    consumed_ref_features = 0

    for _ in range(max_cycles):
        await RisingEdge(dut.clk_drv)
        await ReadOnly()
        ref.step()

        if ref.feature_count <= consumed_ref_features:
            continue

        await Timer(1, "ps")
        assert ref.last_feature is not None
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
        dut.input_drv.value = _input_value(TEST_MODE_MSSD)
        if checked_features >= target_features:
            break
    else:
        raise AssertionError(
            f"timed out after {max_cycles} cycles; checked {checked_features}/{target_features}; "
            f"reference_features={ref.feature_count}, accel_reads={bfm.accel_reads}, ppg_reads={bfm.ppg_reads}"
        )

    assert bfm.accel_reads > 0, "no accelerometer samples were observed through sensor I2C pads"
    assert bfm.ppg_index > 0, "no PPG samples were observed through sensor I2C pads"
