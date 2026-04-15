from __future__ import annotations

import csv
from pathlib import Path

from .types import AccelSample, PpgSample
from .utils import to_signed, to_unsigned


def load_accel_trace(path: str | Path) -> list[AccelSample]:
    samples: list[AccelSample] = []
    with Path(path).open(newline="") as handle:
        reader = csv.reader(handle)
        for index, row in enumerate(reader):
            if not row:
                continue
            raw_ax, raw_ay, raw_az = (int(cell.strip()) for cell in row[:3])
            samples.append(
                AccelSample(
                    index=index,
                    ax=to_signed(raw_ax << 2, 16),
                    ay=to_signed(raw_ay << 2, 16),
                    az=to_signed(raw_az << 2, 16),
                )
            )
    return samples


def load_ppg_trace(path: str | Path) -> list[PpgSample]:
    samples: list[PpgSample] = []
    with Path(path).open(newline="") as handle:
        reader = csv.reader(handle)
        for index, row in enumerate(reader):
            if not row:
                continue
            red_counts = int(row[0].strip())
            samples.append(PpgSample(index=index, value=to_unsigned(red_counts, 16)))
    return samples
