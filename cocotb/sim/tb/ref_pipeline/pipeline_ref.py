from __future__ import annotations

from .feature_ref import FeatureEngineRef
from .motion_ref import MotionProcessRef
from .ppg_ref import PpgConfig, PpgProcessRef
from .rmssd_ref import RmssdEngineRef
from .signal_quality_ref import SignalQualityConfig, SignalQualityRef
from .types import BeatEvent, FeatureVector, MotionEpoch, QualityEpoch, RmssdEpoch
from .utils import to_signed


class PipelineStepInputs:
    def __init__(
        self,
        rst: bool = False,
        accel_valid: bool = False,
        ax: int = 0,
        ay: int = 0,
        az: int = 0,
        ppg_valid: bool = False,
        ppg_sample: int = 0,
        ppg_sample_time: int = 0,
        beat_pulse: bool = False,
        beat_quality: int = 0,
        double_beat: bool = False,
        missed_beat: bool = False,
        rr_valid: bool = False,
        rr_accepted: bool = False,
        rr_interval: int = 0,
        delta_hr: int = 0,
        motion_epoch: bool = False,
        motion_energy: int = 0,
        rmssd_valid: bool = False,
        rmssd_epoch: int = 0,
        fifo_overflow_event: bool = False,
        ppg_i2c_err_event: bool = False,
        epoch_end: bool = False,
        epoch_end_d: bool = False,
        cos_time: int = 0,
        ml_update_gate: bool = False,
    ) -> None:
        self.rst = rst
        self.accel_valid = accel_valid
        self.ax = ax
        self.ay = ay
        self.az = az
        self.ppg_valid = ppg_valid
        self.ppg_sample = ppg_sample
        self.ppg_sample_time = ppg_sample_time
        self.beat_pulse = beat_pulse
        self.beat_quality = beat_quality
        self.double_beat = double_beat
        self.missed_beat = missed_beat
        self.rr_valid = rr_valid
        self.rr_accepted = rr_accepted
        self.rr_interval = rr_interval
        self.delta_hr = delta_hr
        self.motion_epoch = motion_epoch
        self.motion_energy = motion_energy
        self.rmssd_valid = rmssd_valid
        self.rmssd_epoch = rmssd_epoch
        self.fifo_overflow_event = fifo_overflow_event
        self.ppg_i2c_err_event = ppg_i2c_err_event
        self.epoch_end = epoch_end
        self.epoch_end_d = epoch_end_d
        self.cos_time = cos_time
        self.ml_update_gate = ml_update_gate


class TopPipelineConfig:
    def __init__(
        self,
        ppg: PpgConfig | None = None,
        signal_quality: SignalQualityConfig | None = None,
        rmssd_min_rr_count: int = 1,
    ) -> None:
        self.ppg = ppg if ppg is not None else PpgConfig(q_min_accept=0)
        self.signal_quality = (
            signal_quality
            if signal_quality is not None
            else SignalQualityConfig(
                beat_q_min=0,
                min_valid_fraction=0,
                max_double=4,
                max_missed=3,
                motion_hi_th=0xFFFF,
                max_motion_hi=0xFFFF,
            )
        )
        self.rmssd_min_rr_count = rmssd_min_rr_count


class PipelineStepOutputs:
    def __init__(
        self,
        motion: MotionEpoch,
        beat: BeatEvent,
        rmssd: RmssdEpoch,
        quality: QualityEpoch,
        feature: FeatureVector,
    ) -> None:
        self.motion = motion
        self.beat = beat
        self.rmssd = rmssd
        self.quality = quality
        self.feature = feature


class PipelineReference:
    def __init__(self, config: TopPipelineConfig | None = None) -> None:
        self.config = config if config is not None else TopPipelineConfig()
        self.motion = MotionProcessRef(ax_w=16)
        self.ppg = PpgProcessRef()
        self.rmssd = RmssdEngineRef(min_rr_count=self.config.rmssd_min_rr_count)
        self.quality = SignalQualityRef()
        self.feature = FeatureEngineRef()

    def step(self, inputs: PipelineStepInputs) -> PipelineStepOutputs:
        motion_out = self.motion.step(
            rst=inputs.rst,
            sample_valid=inputs.accel_valid,
            sample_ok=True,
            ax=inputs.ax,
            ay=inputs.ay,
            az=inputs.az,
            epoch_end=inputs.epoch_end,
        )
        beat_out = self.ppg.step(
            rst=inputs.rst,
            ppg_sample=inputs.ppg_sample,
            ppg_valid=inputs.ppg_valid,
            ppg_sample_time=inputs.ppg_sample_time,
            cfg=self.config.ppg,
        )
        rmssd_out = self.rmssd.step(
            rst=inputs.rst,
            rr_valid=inputs.rr_valid,
            rr_accepted=inputs.rr_accepted,
            rr_interval=inputs.rr_interval,
            epoch_end=inputs.epoch_end,
        )
        motion_mag = abs(to_signed(inputs.ax, 16)) + abs(to_signed(inputs.ay, 16)) + abs(to_signed(inputs.az, 16))
        quality_out = self.quality.step(
            rst=inputs.rst,
            epoch_end=inputs.epoch_end,
            beat_event=inputs.beat_pulse,
            beat_quality=inputs.beat_quality,
            double_beat=inputs.double_beat,
            missed_beat=inputs.missed_beat,
            fifo_overflow=inputs.fifo_overflow_event,
            fifo_i2c_error=inputs.ppg_i2c_err_event,
            motion_valid=inputs.accel_valid,
            motion_intensity=motion_mag,
            cfg=self.config.signal_quality,
        )
        feature_out = self.feature.step(
            rst=inputs.rst,
            enable=inputs.epoch_end_d,
            seconds_valid=True,
            cos_time_feat=inputs.cos_time,
            motion_valid=inputs.motion_epoch,
            motion_energy_epoch=inputs.motion_energy,
            delta_hr_valid=inputs.rr_valid,
            delta_hr=inputs.delta_hr,
            rmssd_valid=inputs.rmssd_valid,
            rmssd=inputs.rmssd_epoch,
            ml_update_gate=inputs.ml_update_gate,
        )
        return PipelineStepOutputs(
            motion=motion_out,
            beat=beat_out,
            rmssd=rmssd_out,
            quality=quality_out,
            feature=feature_out,
        )
