from __future__ import annotations

from .types import MotionEpoch
from .utils import abs_signed, to_signed, to_unsigned


class MotionProcessRef:
    def __init__(self, ax_w: int = 14, energy_w: int = 48) -> None:
        self.ax_w = ax_w
        self.energy_w = energy_w
        self.mag_w = self.ax_w + 2
        self.reset()

    def reset(self) -> None:
        self.motion_energy_accum = 0
        self.motion_energy_epoch = 0
        self.epoch_done = False

    def step(
        self,
        rst: bool,
        sample_valid: bool,
        sample_ok: bool,
        ax: int,
        ay: int,
        az: int,
        epoch_end: bool,
    ) -> MotionEpoch:
        if rst:
            self.reset()
            return MotionEpoch(False, 0)

        self.epoch_done = False
        sample_fire = bool(sample_valid and sample_ok)

        ax_s = to_signed(ax, self.ax_w) if sample_fire else 0
        ay_s = to_signed(ay, self.ax_w) if sample_fire else 0
        az_s = to_signed(az, self.ax_w) if sample_fire else 0

        abs_ax = abs_signed(ax_s, self.ax_w)
        abs_ay = abs_signed(ay_s, self.ax_w)
        abs_az = abs_signed(az_s, self.ax_w)
        mag = to_unsigned(abs_ax + abs_ay + abs_az, self.mag_w)
        energy_add = to_unsigned(mag, self.energy_w)
        epoch_energy = to_unsigned(
            self.motion_energy_accum + (energy_add if sample_fire else 0),
            self.energy_w,
        )

        if sample_fire:
            self.motion_energy_accum = to_unsigned(
                self.motion_energy_accum + energy_add,
                self.energy_w,
            )

        if epoch_end:
            self.motion_energy_epoch = epoch_energy
            self.epoch_done = True
            self.motion_energy_accum = 0

        return MotionEpoch(self.epoch_done, self.motion_energy_epoch)
