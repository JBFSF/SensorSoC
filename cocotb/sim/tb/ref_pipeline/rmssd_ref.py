from __future__ import annotations

from .types import RmssdEpoch
from .utils import to_signed, to_unsigned


class RmssdEngineRef:
    def __init__(
        self,
        rr_w: int = 16,
        acc_w: int = 40,
        cnt_w: int = 16,
        min_rr_count: int = 1,
        max_diff_count: int = 64,
    ) -> None:
        self.rr_w = rr_w
        self.acc_w = acc_w
        self.cnt_w = cnt_w
        self.min_rr_count = min_rr_count
        self.max_diff_count = max_diff_count
        self.reset()

    def reset(self) -> None:
        self.prev_rr = 0
        self.have_prev_rr = False
        self.sum_sq = 0
        self.diff_cnt = 0
        self.rmssd_epoch = 0
        self.rmssd_valid = False
        self.rr_diff_count = 0

    def step(
        self,
        rst: bool,
        rr_valid: bool,
        rr_accepted: bool,
        rr_interval: int,
        epoch_end: bool,
    ) -> RmssdEpoch:
        if rst:
            self.reset()
            return RmssdEpoch(0, False, 0)

        self.rmssd_valid = False
        prev_rr = self.prev_rr
        have_prev_rr = self.have_prev_rr
        sum_sq = self.sum_sq
        diff_cnt = self.diff_cnt

        rr_interval_u = to_unsigned(rr_interval, self.rr_w)
        if rr_valid and rr_accepted:
            if have_prev_rr:
                diff = to_signed(rr_interval_u, self.rr_w + 1) - to_signed(prev_rr, self.rr_w + 1)
                diff_sq = diff * diff
                self.sum_sq = to_unsigned(sum_sq + diff_sq, self.acc_w)
                if diff_cnt < self.max_diff_count:
                    self.diff_cnt = to_unsigned(diff_cnt + 1, self.cnt_w)

            self.prev_rr = rr_interval_u
            self.have_prev_rr = True

        if epoch_end:
            self.rr_diff_count = diff_cnt
            if diff_cnt >= self.min_rr_count:
                self.rmssd_epoch = 0xFFFF if (sum_sq >> 16) else (sum_sq & 0xFFFF)
                self.rmssd_valid = True
            else:
                self.rmssd_epoch = 0

            self.sum_sq = 0
            self.diff_cnt = 0
            self.have_prev_rr = False

        return RmssdEpoch(self.rmssd_epoch, self.rmssd_valid, self.rr_diff_count)
