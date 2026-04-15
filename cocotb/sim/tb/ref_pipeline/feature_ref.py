from __future__ import annotations

from .types import FeatureVector
from .utils import to_signed


class FeatureEngineRef:
    def __init__(self) -> None:
        self.reset()

    def reset(self) -> None:
        self.feat_valid = False
        self.time_feat = 0
        self.motion_feat = 0
        self.delta_hr_feat = 0
        self.rmssd_feat = 0

    def step(
        self,
        rst: bool,
        enable: bool,
        seconds_valid: bool,
        cos_time_feat: int,
        motion_valid: bool,
        motion_energy_epoch: int,
        delta_hr_valid: bool,
        delta_hr: int,
        rmssd_valid: bool,
        rmssd: int,
        ml_update_gate: bool,
    ) -> FeatureVector:
        if rst:
            self.reset()
            return FeatureVector(False, 0, 0, 0, 0)

        self.feat_valid = False

        if seconds_valid:
            self.time_feat = to_signed(cos_time_feat, 16)
        if motion_valid:
            self.motion_feat = to_signed(motion_energy_epoch, 16)
        if delta_hr_valid:
            self.delta_hr_feat = to_signed(delta_hr, 16)
        if rmssd_valid:
            self.rmssd_feat = to_signed(rmssd, 16)
        if enable and ml_update_gate:
            self.feat_valid = True

        return FeatureVector(
            feat_valid=self.feat_valid,
            time_feat=self.time_feat,
            motion_feat=self.motion_feat,
            delta_hr_feat=self.delta_hr_feat,
            rmssd_feat=self.rmssd_feat,
        )
