"""
ppg.py

Models the Analog Devices ADPD144RI optical PPG sensor.

Real sensor specs:
- 14-bit ADC (single pulse); up to 27-bit with burst accumulation
- Two channels: Time Slot A (660 nm red), Time Slot B (880 nm IR)
- ODR: configurable; we use 100 Hz (typical for PPG heart rate)
- Outputs raw optical intensity counts, NOT BPM
- I2C interface, 1.8 V
- FIFO with overflow/count status register

PhysioNet dataset (heart_rate):
- Columns: timestamp, bpm  (sampled ~1 Hz)
- We upsample to 100 Hz and synthesize a realistic PPG waveform from BPM,
  because the raw dataset has HR labels not raw optical data.

Pipeline:
  BPM labels (1 Hz)
    → upsample + interpolate to 100 Hz
    → synthesize PPG optical waveform (AC + DC components, red + IR)
    → apply gain error, offset, noise
    → 14-bit ADC quantization (unsigned 0..16383)
    → save as CSV: two columns (red_counts, ir_counts)
"""

import numpy as np
import os
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

# ADPD144RI config
PPG_ODR_HZ      = 100        # output data rate in Hz
ADC_BITS        = 14         # 14-bit unsigned counts
ADC_MAX         = (1 << ADC_BITS) - 1   # 16383

# Typical optical signal levels (arbitrary units scaled to 14-bit range)
DC_LEVEL_RED    = 12000      # red channel DC (ambient + LED reflected)
DC_LEVEL_IR     = 14000      # IR channel DC (higher because IR LED is stronger)
AC_AMPLITUDE    = 400        # pulsatile AC component (about 3% modulation — realistic)

# Sensor imperfection model
GAIN_ERROR      = 0.01       # ±1% gain error
OFFSET_COUNTS   = 30         # fixed offset in counts
NOISE_STD       = 8          # ~8 counts RMS noise (reasonable for 14-bit optical ADC)

OUTPUT_DIR      = "sensor_output"
MAX_SAMPLES     = 10_000


# Data loading

def load_heartrate_directory(directory):
    print("Loading heart rate directory...")
    all_bpm = []
    all_t   = []
    t_offset = 0.0
    for fname in sorted(os.listdir(directory)):
        if fname.endswith(".txt"):
            path = os.path.join(directory, fname)
            print("  Loading", fname)
            data = np.loadtxt(path, delimiter=",")   # cols: time, bpm
            t   = data[:, 0] + t_offset
            bpm = data[:, 1]
            all_t.append(t)
            all_bpm.append(bpm)
            t_offset = t[-1] + 1.0   # small gap between subjects
    t_all   = np.concatenate(all_t)
    bpm_all = np.concatenate(all_bpm)
    if MAX_SAMPLES is not None:
        t_all   = t_all[:MAX_SAMPLES]
        bpm_all = bpm_all[:MAX_SAMPLES]
    print(f"  HR samples loaded: {len(bpm_all)}")
    return t_all, bpm_all


# PPG waveform synthesis

def synthesize_ppg_from_bpm(t_bpm, bpm, odr=PPG_ODR_HZ):
    """
    Upsample 1 Hz BPM labels to `odr` Hz and synthesize a realistic
    PPG optical waveform.

    A real PPG waveform has:
      - A large DC component (reflected LED light)
      - A small AC pulsatile component at the heart rate frequency
      - Slight harmonic content (we add 2nd harmonic at 30% amplitude)
    """
    # Build high-rate time axis
    t_end    = t_bpm[-1]
    t_hr     = np.arange(0, t_end, 1.0 / odr)

    # Interpolate BPM to high rate
    interp   = interp1d(t_bpm, bpm, kind="linear", fill_value="extrapolate")
    bpm_hr   = np.clip(interp(t_hr), 30, 220)   # clamp to physiological range

    # Instantaneous phase via cumulative integration of frequency
    freq_hz  = bpm_hr / 60.0                     # BPM → Hz
    phase    = 2 * np.pi * np.cumsum(freq_hz) / odr

    # Fundamental + 2nd harmonic (realistic PPG shape)
    ppg_wave = np.sin(phase) + 0.3 * np.sin(2 * phase)
    ppg_wave /= np.max(np.abs(ppg_wave))          # normalise to ±1

    return t_hr, ppg_wave, bpm_hr


# ADPD144RI sensor model

def apply_adpd144ri_model(ppg_wave):
    """
    Produce two channels (red 660 nm, IR 880 nm) of 14-bit unsigned counts.

    Red channel:  lower DC level, same AC pulsatile
    IR channel:   higher DC level, AC pulsatile slightly different amplitude
                  (SpO2 ratio of AC/DC differs between wavelengths)
    """
    # Red channel
    gain_r   = 1.0 + np.random.uniform(-GAIN_ERROR, GAIN_ERROR)
    offset_r = OFFSET_COUNTS + np.random.uniform(-5, 5)
    noise_r  = np.random.normal(0, NOISE_STD, len(ppg_wave))

    red = DC_LEVEL_RED + AC_AMPLITUDE * ppg_wave * gain_r + offset_r + noise_r

    # IR channel (slightly different gain and AC amplitude — simulates SpO2 ratio)
    gain_ir   = 1.0 + np.random.uniform(-GAIN_ERROR, GAIN_ERROR)
    offset_ir = OFFSET_COUNTS + np.random.uniform(-5, 5)
    noise_ir  = np.random.normal(0, NOISE_STD, len(ppg_wave))
    ac_ir     = AC_AMPLITUDE * 0.85   # IR AC slightly smaller (typical R~0.85 at SpO2 ~98%)

    ir = DC_LEVEL_IR + ac_ir * ppg_wave * gain_ir + offset_ir + noise_ir

    # Clip and quantize to 14-bit unsigned
    red_counts = np.clip(np.round(red), 0, ADC_MAX).astype(np.uint16)
    ir_counts  = np.clip(np.round(ir),  0, ADC_MAX).astype(np.uint16)

    return red_counts, ir_counts


# Validation plot

def save_validation_plot(t_hr, red, ir, bpm_hr, filename):
    duration_s = 5
    n = duration_s * PPG_ODR_HZ
    t  = t_hr[:n]
    r  = red[:n]
    i  = ir[:n]

    fig, axes = plt.subplots(3, 1, figsize=(10, 8), sharex=True)

    axes[0].plot(t, r, color="red",  label="Red 660nm (counts)")
    axes[0].set_ylabel("ADC counts")
    axes[0].legend()

    axes[1].plot(t, i, color="darkred", label="IR 880nm (counts)")
    axes[1].set_ylabel("ADC counts")
    axes[1].legend()

    axes[2].plot(t, bpm_hr[:n], color="blue", label="Heart rate (BPM)")
    axes[2].set_ylabel("BPM")
    axes[2].set_xlabel("Time (s)")
    axes[2].legend()

    fig.suptitle("ADPD144RI Model — Red + IR channels (first 5 s)")
    plt.tight_layout()

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    path = os.path.join(OUTPUT_DIR, filename)
    plt.savefig(path)
    plt.close()
    print("  Validation plot →", path)


# Main


def process_ppg(directory):
    t_bpm, bpm      = load_heartrate_directory(directory)
    t_hr, ppg_wave, bpm_hr = synthesize_ppg_from_bpm(t_bpm, bpm)
    red, ir          = apply_adpd144ri_model(ppg_wave)

    save_validation_plot(t_hr, red, ir, bpm_hr, "ppg_validation.png")


    os.makedirs(OUTPUT_DIR, exist_ok=True)
    csv_path = os.path.join(OUTPUT_DIR, "ppg_digital.csv")
    # Two columns: red_counts, ir_counts — no header (for $fscanf compatibility)
    data = np.column_stack([red, ir])
    np.savetxt(csv_path, data, fmt="%d", delimiter=",")
    print(f"  PPG digital stream → {csv_path}  ({len(red)} samples @ {PPG_ODR_HZ} Hz)")

    return red, ir