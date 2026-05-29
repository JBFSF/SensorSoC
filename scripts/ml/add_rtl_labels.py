"""
add_rtl_labels.py

Joins rtl_features.csv (output from cocotb simulation) with sleep stage
labels from processed_sleep_dataset.csv and writes rtl_features_labeled.csv.

Column layout of processed_sleep_dataset.csv (no header):
  col 1: time_s — recording timestamp in seconds, 30-second steps
  col 4: label — 0=non-N3, 1=N3

Mapping logic:
  The accel data used by the sim was generated at ACCEL_ODR_HZ from a
  specific point in the PhysioNet recording.  Each RTL epoch consumes
  ACCEL_SAMPLES_PER_EPOCH raw accel samples, so:

    real_time(epoch N) = RECORDING_START_S + N * (ACCEL_SAMPLES_PER_EPOCH / ACCEL_ODR_HZ)

  We then find the closest 30-second PSG epoch in the label file.

IMPORTANT — RECORDING_START_S:
  The current sensor_models/loader.py fetches from the start of each
  PhysioNet motion file (t=0).  The sleep labels in processed_sleep_dataset
  begin at t≈1470 s.  If your accel_digital.csv was generated from t=0
  there is no overlap and all labels will be NaN.

  Set RECORDING_START_S to the actual start time of your accel data in the
  recording (must be >= 1470 to hit labeled data).
"""

import csv
import os
import sys

# ── Configuration ─────────────────────────────────────────────────────────────

ACCEL_ODR_HZ            = 25    # ODR written to accel_digital.csv
ACCEL_SAMPLES_PER_EPOCH = 189   # empirical: 9998 accel rows / 53 RTL epochs
PSG_EPOCH_S             = 30    # sleep-scoring epoch length (PhysioNet standard)

# Time in the PhysioNet recording (seconds) where your accel_digital.csv starts.
# The first N3 epoch for the primary subject block appears at t=2790s, so this
# must be >= 2790 to get any N3 labels.
RECORDING_START_S       = 2790

# col0 value that identifies the subject block to use for labels.
# col0=0.0 is the largest block (972 epochs, ~8 hrs) with N3 starting at t=2790s.
SUBJECT_COL0            = 0.0

# Paths (relative to this script's directory)
_HERE    = os.path.dirname(os.path.abspath(__file__))
_REPO    = os.path.join(_HERE, "..", "..")
RTL_FEATURES_CSV  = os.path.join(_REPO, "cocotb", "sim", "data", "rtl_features.csv")
SLEEP_DATASET_CSV = os.path.join(_HERE, "processed_sleep_dataset.csv")
OUTPUT_CSV        = os.path.join(_HERE, "rtl_features_labeled.csv")

# ── Load sleep labels ─────────────────────────────────────────────────────────

sleep_labels = {}   # time_s (rounded to nearest 30) -> label int

with open(SLEEP_DATASET_CSV, newline="") as f:
    for row in csv.reader(f):
        if float(row[0]) != SUBJECT_COL0:
            continue
        t   = float(row[1])
        lbl = int(row[4])
        sleep_labels[round(t / PSG_EPOCH_S) * PSG_EPOCH_S] = lbl

if not sleep_labels:
    print("ERROR: no rows loaded from", SLEEP_DATASET_CSV)
    sys.exit(1)

label_times = sorted(sleep_labels.keys())
t_min, t_max = label_times[0], label_times[-1]
print(f"Sleep labels: {len(sleep_labels)} epochs, t=[{t_min:.0f}, {t_max:.0f}] s")

# ── Helper: find nearest PSG label ───────────────────────────────────────────

def lookup_label(real_t):
    """Return the label for the PSG epoch closest to real_t, or None if out of range."""
    nearest = round(real_t / PSG_EPOCH_S) * PSG_EPOCH_S
    if nearest in sleep_labels:
        return sleep_labels[nearest]
    # fall back to closest available time
    closest = min(label_times, key=lambda t: abs(t - real_t))
    if abs(closest - real_t) <= PSG_EPOCH_S:
        return sleep_labels[closest]
    return None

# ── Process rtl_features.csv ─────────────────────────────────────────────────

rows_in  = []
with open(RTL_FEATURES_CSV, newline="") as f:
    reader = csv.DictReader(f)
    for row in reader:
        rows_in.append(row)

if not rows_in:
    print("ERROR: no rows in", RTL_FEATURES_CSV)
    sys.exit(1)

missing = 0
rows_out = []
for row in rows_in:
    sample_idx = int(row["sample"])   # 1-based

    # Compute real recording time for the midpoint of this epoch
    elapsed_accel_samples = (sample_idx - 0.5) * ACCEL_SAMPLES_PER_EPOCH
    real_t = RECORDING_START_S + elapsed_accel_samples / ACCEL_ODR_HZ

    label = lookup_label(real_t)
    if label is None:
        missing += 1

    rows_out.append({
        "sample":        row["sample"],
        "time_feat":     row["time_feat"],
        "motion_feat":   row["motion_feat"],
        "delta_hr_feat": row["delta_hr_feat"],
        "mssd_feat":     row["mssd_feat"],
        "label":         "" if label is None else str(label),
    })

# ── Write output ──────────────────────────────────────────────────────────────

fieldnames = ["sample", "time_feat", "motion_feat", "delta_hr_feat", "mssd_feat", "label"]

with open(OUTPUT_CSV, "w", newline="") as f:
    writer = csv.DictWriter(f, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(rows_out)

labeled = len(rows_out) - missing
print(f"Wrote {len(rows_out)} rows to {OUTPUT_CSV}")
print(f"  Labeled: {labeled}  |  No label (out of range): {missing}")

if missing == len(rows_out):
    print()
    print("WARNING: all epochs fell outside the labeled time range.")
    print(f"  Epoch times spanned {RECORDING_START_S:.0f} – "
          f"{RECORDING_START_S + len(rows_out)*ACCEL_SAMPLES_PER_EPOCH/ACCEL_ODR_HZ:.0f} s")
    print(f"  Label file covers {t_min:.0f} – {t_max:.0f} s")
    print()
    print("Fix: regenerate accel_digital.csv starting at RECORDING_START_S >= "
          f"{t_min:.0f} s (set start_time_s in scripts/sensor_models/loader.py)")
