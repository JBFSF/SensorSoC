from __future__ import annotations

from .types import QualityEpoch
from .utils import bool_bit, to_unsigned


class SignalQualityConfig:
    def __init__(
        self,
        beat_q_min: int = 16,
        min_valid_fraction: int = 96,
        max_double: int = 4,
        max_missed: int = 3,
        motion_hi_th: int = 2000,
        max_motion_hi: int = 3,
    ) -> None:
        self.beat_q_min = beat_q_min
        self.min_valid_fraction = min_valid_fraction
        self.max_double = max_double
        self.max_missed = max_missed
        self.motion_hi_th = motion_hi_th
        self.max_motion_hi = max_motion_hi


class SignalQualityRef:
    def __init__(self, motion_w: int = 16, cnt_w: int = 16) -> None:
        self.motion_w = motion_w
        self.cnt_w = cnt_w
        self.reset()

    def reset(self) -> None:
        self.beat_cnt = 0
        self.good_beat_cnt = 0
        self.double_cnt = 0
        self.missed_cnt = 0
        self.motion_hi_cnt = 0
        self.overflow_seen = False
        self.i2c_err_seen = False
        self.invalid_reason = 0
        self.ml_update_gate = False

    def step(
        self,
        rst: bool,
        epoch_end: bool,
        beat_event: bool,
        beat_quality: int,
        double_beat: bool,
        missed_beat: bool,
        fifo_overflow: bool,
        fifo_i2c_error: bool,
        motion_valid: bool,
        motion_intensity: int,
        cfg: SignalQualityConfig,
    ) -> QualityEpoch:
        if rst:
            self.reset()
            return QualityEpoch(0, False)

        beat_cnt = self.beat_cnt
        good_beat_cnt = self.good_beat_cnt
        double_cnt = self.double_cnt
        missed_cnt = self.missed_cnt
        motion_hi_cnt = self.motion_hi_cnt
        overflow_seen = self.overflow_seen
        i2c_err_seen = self.i2c_err_seen

        if beat_event:
            self.beat_cnt = to_unsigned(self.beat_cnt + 1, self.cnt_w)
            if beat_quality >= cfg.beat_q_min:
                self.good_beat_cnt = to_unsigned(self.good_beat_cnt + 1, self.cnt_w)
        if double_beat and self.double_cnt != 0xFF:
            self.double_cnt = to_unsigned(self.double_cnt + 1, 8)
        if missed_beat and self.missed_cnt != 0xFF:
            self.missed_cnt = to_unsigned(self.missed_cnt + 1, 8)
        if motion_valid and motion_intensity > cfg.motion_hi_th:
            self.motion_hi_cnt = to_unsigned(self.motion_hi_cnt + 1, self.cnt_w)
        if fifo_overflow:
            self.overflow_seen = True
        if fifo_i2c_error:
            self.i2c_err_seen = True

        if epoch_end:
            frac = 0 if beat_cnt == 0 else ((good_beat_cnt * 255) // beat_cnt)
            no_beats = beat_cnt == 0
            low_frac = frac < cfg.min_valid_fraction
            double_bad = double_cnt > cfg.max_double
            missed_bad = missed_cnt > cfg.max_missed
            motion_bad = motion_hi_cnt > cfg.max_motion_hi

            self.invalid_reason = (
                (bool_bit(overflow_seen) << 0)
                | (bool_bit(i2c_err_seen) << 1)
                | (bool_bit(no_beats) << 2)
                | (bool_bit(low_frac) << 3)
                | (bool_bit(double_bad) << 4)
                | (bool_bit(missed_bad) << 5)
                | (bool_bit(motion_bad) << 6)
            )
            self.ml_update_gate = not (
                overflow_seen
                or i2c_err_seen
                or no_beats
                or low_frac
                or double_bad
                or missed_bad
                or motion_bad
            )

            self.beat_cnt = 0
            self.good_beat_cnt = 0
            self.double_cnt = 0
            self.missed_cnt = 0
            self.motion_hi_cnt = 0
            self.overflow_seen = False
            self.i2c_err_seen = False

        return QualityEpoch(self.invalid_reason, self.ml_update_gate)
