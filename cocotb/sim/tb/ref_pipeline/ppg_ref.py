from __future__ import annotations

from .types import BeatEvent
from .utils import to_signed, to_unsigned


class PpgConfig:
    def __init__(
        self,
        enable: bool = True,
        bypass: bool = False,
        signed_samples: bool = False,
        lp_beta: int = 128,
        base_alpha: int = 16,
        env_decay: int = 8,
        abs_en: bool = True,
        thr_k: int = 512,
        thr_min: int = 32,
        refrac_ticks: int = 250,
        rr_min_ticks: int = 300,
        rr_max_ticks: int = 2000,
        q_amp_w: int = 4,
        q_slope_w: int = 2,
        q_refrac_penalty: int = 24,
        q_min_accept: int = 10,
    ) -> None:
        self.enable = enable
        self.bypass = bypass
        self.signed_samples = signed_samples
        self.lp_beta = lp_beta
        self.base_alpha = base_alpha
        self.env_decay = env_decay
        self.abs_en = abs_en
        self.thr_k = thr_k
        self.thr_min = thr_min
        self.refrac_ticks = refrac_ticks
        self.rr_min_ticks = rr_min_ticks
        self.rr_max_ticks = rr_max_ticks
        self.q_amp_w = q_amp_w
        self.q_slope_w = q_slope_w
        self.q_refrac_penalty = q_refrac_penalty
        self.q_min_accept = q_min_accept


class PpgProcessRef:
    def __init__(
        self,
        sample_w: int = 16,
        t_w: int = 32,
        x_w: int = 24,
        env_w: int = 24,
        coeff_w: int = 12,
        coeff_frac: int = 10,
        quality_margin_shift: int = 4,
    ) -> None:
        self.sample_w = sample_w
        self.t_w = t_w
        self.x_w = x_w
        self.env_w = env_w
        self.coeff_w = coeff_w
        self.coeff_frac = coeff_frac
        self.quality_margin_shift = quality_margin_shift
        self.coeff_one = 1 << self.coeff_frac
        self.reset()

    def reset(self) -> None:
        self.beat_pulse = False
        self.rr_valid = False
        self.rr_accepted = False
        self.rr_interval = 0
        self.delta_hr_bpm = 0
        self.beat_quality = 0
        self.double_beat = False
        self.missed_beat = False
        self.ppg_invalid = False

        self.x_lp = 0
        self.x_base = 0
        self.x_hp = 0
        self.env = 0
        self.thr = 0
        self.xhp_d2 = 0
        self.xhp_d1 = 0
        self.thr_d1 = 0
        self.t_d1 = 0

        self.last_beat_time = 0
        self.have_last_beat = False
        self.prev_hr_bpm = 0
        self.have_prev_hr = False
        self.have_init = False

    def _sample_to_signed(self, sample: int, signed_samples: bool) -> int:
        sample_u = to_unsigned(sample, self.sample_w)
        if signed_samples:
            return to_signed(to_signed(sample_u, self.sample_w), self.x_w)
        return to_signed(sample_u, self.x_w)

    def _abs_x(self, value: int) -> int:
        signed = to_signed(value, self.x_w)
        return to_unsigned(-signed if signed < 0 else signed, self.x_w)

    def step(
        self,
        rst: bool,
        ppg_sample: int,
        ppg_valid: bool,
        ppg_sample_time: int,
        cfg: PpgConfig,
    ) -> BeatEvent:
        if rst:
            self.reset()
            return BeatEvent(False, False, False, 0, 0, 0, False, False, False)

        self.beat_pulse = False
        self.rr_valid = False
        self.rr_accepted = False
        self.double_beat = False
        self.missed_beat = False

        t_now = to_unsigned(ppg_sample_time, self.t_w)
        elapsed_since_last = to_unsigned(t_now - self.last_beat_time, self.t_w)
        in_refrac = self.have_last_beat and elapsed_since_last < cfg.refrac_ticks

        if not cfg.enable or cfg.bypass:
            self.ppg_invalid = False
            self.have_init = False
        elif self.have_last_beat and elapsed_since_last > cfg.rr_max_ticks:
            self.ppg_invalid = True

        if ppg_valid:
            x_raw = self._sample_to_signed(ppg_sample, cfg.signed_samples)
            if not self.have_init:
                self.x_lp = x_raw
                self.x_base = x_raw
                self.x_hp = 0
                self.env = 0
                self.thr = to_unsigned(cfg.thr_min, self.env_w)
                self.xhp_d2 = 0
                self.xhp_d1 = 0
                self.thr_d1 = to_unsigned(cfg.thr_min, self.env_w)
                self.t_d1 = t_now
                self.beat_quality = 0
                self.have_init = True
            else:
                lp_err = to_signed(x_raw - self.x_lp, self.x_w)
                if cfg.lp_beta == 0:
                    x_lp_next = self.x_lp
                elif cfg.lp_beta >= self.coeff_one:
                    x_lp_next = x_raw
                else:
                    lp_step = (lp_err * cfg.lp_beta) >> self.coeff_frac
                    x_lp_next = to_signed(self.x_lp + lp_step, self.x_w)

                base_err = to_signed(x_lp_next - self.x_base, self.x_w)
                if cfg.base_alpha == 0:
                    x_base_next = self.x_base
                elif cfg.base_alpha >= self.coeff_one:
                    x_base_next = x_lp_next
                else:
                    base_step = (base_err * cfg.base_alpha) >> self.coeff_frac
                    x_base_next = to_signed(self.x_base + base_step, self.x_w)

                x_hp_next = to_signed(x_lp_next - x_base_next, self.x_w)
                if cfg.abs_en:
                    x_mag = self._abs_x(x_hp_next)
                else:
                    x_mag = 0 if x_hp_next < 0 else to_unsigned(x_hp_next, self.x_w)

                env_decay = self.env - cfg.env_decay if self.env > cfg.env_decay else 0
                env_next = x_mag if x_mag > env_decay else env_decay

                thr_scaled = (env_next * cfg.thr_k) >> self.coeff_frac
                thr_next = thr_scaled if thr_scaled > cfg.thr_min else cfg.thr_min

                localmax_candidate = (
                    self.xhp_d1 > self.xhp_d2
                    and self.xhp_d1 > x_hp_next
                    and self.xhp_d1 >= 0
                    and to_unsigned(self.xhp_d1, self.x_w) > self.thr_d1
                )

                peak_abs = self._abs_x(self.xhp_d1)
                slope_signed = to_signed(self.xhp_d1 - self.xhp_d2, self.x_w)
                beat_time = self.t_d1
                slope_mag = 0 if slope_signed < 0 else to_unsigned(slope_signed, self.x_w)
                amp_margin = peak_abs - self.thr_d1 if peak_abs > self.thr_d1 else 0
                slope_margin = slope_mag

                amp_term = cfg.q_amp_w * (amp_margin >> self.quality_margin_shift)
                slope_term = cfg.q_slope_w * (slope_margin >> self.quality_margin_shift)
                quality_raw = amp_term + slope_term

                penalty = (
                    cfg.q_refrac_penalty
                    if self.have_last_beat and elapsed_since_last < (cfg.refrac_ticks + (cfg.refrac_ticks >> 2))
                    else 0
                )

                quality_minus_pen = quality_raw - penalty if quality_raw > penalty else 0
                quality = 255 if quality_minus_pen > 255 else quality_minus_pen
                quality_ok = quality >= cfg.q_min_accept

                accept = False
                reject_short_rr = False
                flag_missed = False
                rr_should_pulse = False
                rr_value = to_unsigned(beat_time - self.last_beat_time, self.t_w)
                hr_bpm_new = self.prev_hr_bpm
                delta_hr = 0

                if cfg.enable and not cfg.bypass and localmax_candidate and not in_refrac and quality_ok:
                    if not self.have_last_beat:
                        accept = True
                    elif rr_value < cfg.rr_min_ticks:
                        reject_short_rr = True
                    else:
                        accept = True
                        rr_should_pulse = True
                        if rr_value > cfg.rr_max_ticks:
                            flag_missed = True

                if localmax_candidate and not in_refrac:
                    self.beat_quality = quality

                if reject_short_rr:
                    self.double_beat = True

                if accept:
                    self.beat_pulse = True
                    self.last_beat_time = beat_time
                    self.have_last_beat = True
                    self.ppg_invalid = False

                if rr_should_pulse:
                    self.rr_valid = True
                    self.rr_accepted = (not reject_short_rr) and (rr_value <= cfg.rr_max_ticks)
                    self.rr_interval = rr_value
                    if rr_value != 0:
                        hr_bpm_new = to_unsigned(60000 // rr_value, 16)
                        if self.have_prev_hr:
                            delta_hr = to_signed(hr_bpm_new, 17) - to_signed(self.prev_hr_bpm, 17)
                        else:
                            delta_hr = 0
                        self.delta_hr_bpm = to_signed(delta_hr, 17)
                        self.prev_hr_bpm = hr_bpm_new
                        self.have_prev_hr = True

                if flag_missed:
                    self.missed_beat = True

                self.x_lp = to_signed(x_lp_next, self.x_w)
                self.x_base = to_signed(x_base_next, self.x_w)
                self.x_hp = to_signed(x_hp_next, self.x_w)
                self.env = to_unsigned(env_next, self.env_w)
                self.thr = to_unsigned(thr_next, self.env_w)

                self.xhp_d2 = to_signed(self.xhp_d1, self.x_w)
                self.xhp_d1 = to_signed(x_hp_next, self.x_w)
                self.thr_d1 = to_unsigned(thr_next, self.env_w)
                self.t_d1 = t_now

        return BeatEvent(
            beat_pulse=self.beat_pulse,
            rr_valid=self.rr_valid,
            rr_accepted=self.rr_accepted,
            rr_interval=self.rr_interval,
            delta_hr_bpm=self.delta_hr_bpm,
            beat_quality=self.beat_quality,
            double_beat=self.double_beat,
            missed_beat=self.missed_beat,
            ppg_invalid=self.ppg_invalid,
        )
