from __future__ import annotations


class _Record:
    def __repr__(self) -> str:
        fields = ", ".join(f"{name}={value!r}" for name, value in self.__dict__.items())
        return f"{self.__class__.__name__}({fields})"


class AccelSample(_Record):
    def __init__(self, index: int, ax: int, ay: int, az: int) -> None:
        self.index = index
        self.ax = ax
        self.ay = ay
        self.az = az


class PpgSample(_Record):
    def __init__(self, index: int, value: int, time: int = 0) -> None:
        self.index = index
        self.value = value
        self.time = time


class MotionEpoch(_Record):
    def __init__(self, epoch_done: bool, motion_energy_epoch: int) -> None:
        self.epoch_done = epoch_done
        self.motion_energy_epoch = motion_energy_epoch


class BeatEvent(_Record):
    def __init__(
        self,
        beat_pulse: bool,
        rr_valid: bool,
        rr_accepted: bool,
        rr_interval: int,
        delta_hr_bpm: int,
        beat_quality: int,
        double_beat: bool,
        missed_beat: bool,
        ppg_invalid: bool,
    ) -> None:
        self.beat_pulse = beat_pulse
        self.rr_valid = rr_valid
        self.rr_accepted = rr_accepted
        self.rr_interval = rr_interval
        self.delta_hr_bpm = delta_hr_bpm
        self.beat_quality = beat_quality
        self.double_beat = double_beat
        self.missed_beat = missed_beat
        self.ppg_invalid = ppg_invalid


class RmssdEpoch(_Record):
    def __init__(self, rmssd_epoch: int, rmssd_valid: bool, rr_diff_count: int) -> None:
        self.rmssd_epoch = rmssd_epoch
        self.rmssd_valid = rmssd_valid
        self.rr_diff_count = rr_diff_count


class QualityEpoch(_Record):
    def __init__(self, invalid_reason: int, ml_update_gate: bool) -> None:
        self.invalid_reason = invalid_reason
        self.ml_update_gate = ml_update_gate


class FeatureVector(_Record):
    def __init__(
        self,
        feat_valid: bool,
        time_feat: int,
        motion_feat: int,
        delta_hr_feat: int,
        rmssd_feat: int,
    ) -> None:
        self.feat_valid = feat_valid
        self.time_feat = time_feat
        self.motion_feat = motion_feat
        self.delta_hr_feat = delta_hr_feat
        self.rmssd_feat = rmssd_feat
