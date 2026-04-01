"""
data/loader.py

Streams the PhysioNet sleep-accel dataset directly over HTTP.
Only the first MAX_SAMPLES lines are downloaded per file — the connection
is closed as soon as enough rows have been fetched, so nothing is saved
to disk and bandwidth usage is minimal.

Dataset: https://physionet.org/content/sleep-accel/1.0.0/
Files:   motion/{id}_acceleration.txt  — cols: time, x, y, z  (g, 50 Hz)
         heart_rate/{id}_heartrate.txt — cols: time, bpm       (~1 Hz)

Requires:
    pip install requests numpy
"""

import io
import itertools
import numpy as np
import requests

BASE_URL    = "https://physionet.org/files/sleep-accel/1.0.0"

# A small representative sample of subject IDs (31 total in the dataset)
SUBJECT_IDS = ["2598705", "4018081", "5498603"]

MAX_SAMPLES = 10_000


def _fetch_txt_partial(url: str, max_lines: int, delimiter=None) -> np.ndarray:
    """
    Stream a .txt file from `url`, downloading only the first `max_lines`
    rows. The connection is closed immediately after, so only the needed
    bytes are transferred.
    """
    with requests.get(url, stream=True, timeout=30) as resp:
        resp.raise_for_status()
        lines = list(itertools.islice(resp.iter_lines(), max_lines))
    text = "\n".join(line.decode() for line in lines)
    return np.loadtxt(io.StringIO(text), delimiter=delimiter)


def load_motion() -> np.ndarray:
    """
    Stream accelerometer data directly from PhysioNet.

    Returns:
        (N, 3) float array of x/y/z acceleration in g, downsampled to 25 Hz.
    """
    print("Streaming motion data from PhysioNet...")
    all_data = []
    # Each subject contributes up to MAX_SAMPLES rows before downsampling;
    # after 2x downsample we need 2× that many raw rows to hit the cap.
    rows_per_subject = (MAX_SAMPLES * 2) // len(SUBJECT_IDS)
    for subject in SUBJECT_IDS:
        url = f"{BASE_URL}/motion/{subject}_acceleration.txt"
        try:
            data = _fetch_txt_partial(url, rows_per_subject)
            xyz  = data[:, 1:4]   # drop timestamp, keep x/y/z
            all_data.append(xyz)
            print(f"  Streamed subject {subject}: {len(xyz)} samples")
        except Exception as e:
            print(f"  Warning: could not stream subject {subject}: {e}")

    if not all_data:
        raise RuntimeError("Failed to stream any motion data from PhysioNet.")

    data = np.vstack(all_data)[:MAX_SAMPLES * 2]
    data = data[::2]   # 50 Hz → 25 Hz
    data = data[:MAX_SAMPLES]
    print(f"  Samples after downsample: {len(data)}")
    return data


def load_heartrate():
    """
    Stream heart rate data directly from PhysioNet.

    Returns:
        (timestamps, bpm): two 1-D float arrays, timestamps in seconds (~1 Hz).
    """
    print("Streaming heart rate data from PhysioNet...")
    all_t, all_bpm = [], []
    t_offset = 0.0
    rows_per_subject = MAX_SAMPLES // len(SUBJECT_IDS)
    for subject in SUBJECT_IDS:
        url = f"{BASE_URL}/heart_rate/{subject}_heartrate.txt"
        try:
            data = _fetch_txt_partial(url, rows_per_subject, delimiter=",")
            t    = data[:, 0] + t_offset
            bpm  = data[:, 1]
            all_t.append(t)
            all_bpm.append(bpm)
            t_offset = t[-1] + 1.0
            print(f"  Streamed subject {subject}: {len(bpm)} samples")
        except Exception as e:
            print(f"  Warning: could not stream subject {subject}: {e}")

    if not all_t:
        raise RuntimeError("Failed to stream any heart rate data from PhysioNet.")

    t_all   = np.concatenate(all_t)[:MAX_SAMPLES]
    bpm_all = np.concatenate(all_bpm)[:MAX_SAMPLES]
    print(f"  HR samples loaded: {len(bpm_all)}")
    return t_all, bpm_all
