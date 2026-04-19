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
    -> upsample + interpolate to 100 Hz
    -> synthesize PPG optical waveform (AC + DC components, red + IR)
    -> apply gain error, offset, noise
    -> 14-bit ADC quantization (unsigned 0..16383)
    -> save as CSV: two columns (red_counts, ir_counts)

Default parameter values match ADPD144RI datasheet specs and typical optical
signal levels for wrist-worn PPG. All parameters can be overridden at call time.
"""

import numpy as np
import os
import matplotlib.pyplot as plt
from pathlib import Path
from scipy.interpolate import interp1d

# Reference defaults -- documented here for traceability but not used directly.
# Pass overrides to process_ppg() as keyword arguments.
_DEFAULT_ODR_HZ       = 100    # output data rate in Hz
_DEFAULT_DC_RED       = 12000  # red channel DC level (counts)
_DEFAULT_DC_IR        = 14000  # IR channel DC level (counts)
_DEFAULT_AC_AMPLITUDE = 400    # pulsatile AC amplitude (counts, ~3.3% modulation)
_DEFAULT_GAIN_ERROR   = 0.01   # +/-1% gain error per channel
_DEFAULT_OFFSET       = 30     # fixed offset in counts
_DEFAULT_NOISE_STD    = 8      # ~8 counts RMS noise (14-bit optical ADC)

ADC_BITS = 14
ADC_MAX  = (1 << ADC_BITS) - 1  # 16383

PLOT_DIR = "sensor_output"   # validation plots only -- gitignored


# PPG waveform synthesis

def _synthesize_ppg_from_bpm(t_bpm, bpm, odr_hz):
    """Upsample 1 Hz BPM labels to odr_hz and synthesize a realistic PPG waveform."""
    t_end     = t_bpm[-1]
    t_hr      = np.arange(0, t_end, 1.0 / odr_hz)
    interp_fn = interp1d(t_bpm, bpm, kind="linear", fill_value="extrapolate")
    bpm_hr    = np.clip(interp_fn(t_hr), 30, 220)
    freq_hz   = bpm_hr / 60.0
    phase     = 2 * np.pi * np.cumsum(freq_hz) / odr_hz
    # Fundamental + 2nd harmonic (realistic PPG shape)
    ppg_wave  = np.sin(phase) + 0.3 * np.sin(2 * phase)
    ppg_wave /= np.max(np.abs(ppg_wave))
    return t_hr, ppg_wave, bpm_hr


# ADPD144RI sensor model

def _apply_adpd144ri_model(ppg_wave, dc_red, dc_ir, ac_amplitude, gain_error, offset_counts, noise_std):
    """Produce two channels (red 660 nm, IR 880 nm) of 14-bit unsigned counts."""
    # Red channel
    gain_r   = 1.0 + np.random.uniform(-gain_error, gain_error)
    offset_r = offset_counts + np.random.uniform(-5, 5)
    noise_r  = np.random.normal(0, noise_std, len(ppg_wave))
    red      = dc_red + ac_amplitude * ppg_wave * gain_r + offset_r + noise_r

    # IR channel -- AC amplitude slightly smaller (models SpO2 ratio R~0.85 at SpO2~98%)
    gain_ir   = 1.0 + np.random.uniform(-gain_error, gain_error)
    offset_ir = offset_counts + np.random.uniform(-5, 5)
    noise_ir  = np.random.normal(0, noise_std, len(ppg_wave))
    ac_ir     = ac_amplitude * 0.85
    ir        = dc_ir + ac_ir * ppg_wave * gain_ir + offset_ir + noise_ir

    red_counts = np.clip(np.round(red), 0, ADC_MAX).astype(np.uint16)
    ir_counts  = np.clip(np.round(ir),  0, ADC_MAX).astype(np.uint16)
    return red_counts, ir_counts


# Validation plot

def _save_validation_plot(t_hr, red, ir, bpm_hr, odr_hz):
    duration_s = 5
    n = duration_s * odr_hz
    t = t_hr[:n]

    fig, axes = plt.subplots(3, 1, figsize=(10, 8), sharex=True)
    axes[0].plot(t, red[:n], color="red",    label="Red 660nm (counts)")
    axes[0].set_ylabel("ADC counts")
    axes[0].legend()
    axes[1].plot(t, ir[:n], color="darkred", label="IR 880nm (counts)")
    axes[1].set_ylabel("ADC counts")
    axes[1].legend()
    axes[2].plot(t, bpm_hr[:n], color="blue", label="Heart rate (BPM)")
    axes[2].set_ylabel("BPM")
    axes[2].set_xlabel("Time (s)")
    axes[2].legend()
    fig.suptitle("ADPD144RI Model -- Red + IR channels (first 5 s)")
    plt.tight_layout()

    os.makedirs(PLOT_DIR, exist_ok=True)
    path = os.path.join(PLOT_DIR, "ppg_validation.png")
    plt.savefig(path)
    plt.close()
    print("  Validation plot ->", path)


# Main entry point

def process_ppg(
    t_bpm,
    bpm,
    output_dir,
    *,
    odr_hz=_DEFAULT_ODR_HZ,
    dc_red=_DEFAULT_DC_RED,
    dc_ir=_DEFAULT_DC_IR,
    ac_amplitude=_DEFAULT_AC_AMPLITUDE,
    gain_error=_DEFAULT_GAIN_ERROR,
    offset_counts=_DEFAULT_OFFSET,
    noise_std=_DEFAULT_NOISE_STD,
):
    """
    Run the ADPD144RI sensor model pipeline on BPM time-series data.

    Args:
        t_bpm:      1-D array of timestamps in seconds (~1 Hz).
        bpm:        1-D array of heart rate values in BPM.
        output_dir: Path to write ppg_digital.csv.

    Keyword-only args (all have datasheet-accurate defaults):
        odr_hz:        Output data rate in Hz. Default 100.
        dc_red:        Red channel DC level in counts. Default 12000.
        dc_ir:         IR channel DC level in counts. Default 14000.
        ac_amplitude:  Pulsatile AC amplitude in counts. Default 400.
        gain_error:    Per-channel gain error fraction (+/-). Default 0.01.
        offset_counts: Fixed offset in counts. Default 30.
        noise_std:     Gaussian noise in counts RMS. Default 8.

    Returns:
        (red_counts, ir_counts): two uint16 arrays at odr_hz.
    """
    t_hr, ppg_wave, bpm_hr = _synthesize_ppg_from_bpm(t_bpm, bpm, odr_hz)
    red, ir                 = _apply_adpd144ri_model(
        ppg_wave, dc_red, dc_ir, ac_amplitude, gain_error, offset_counts, noise_std
    )

    _save_validation_plot(t_hr, red, ir, bpm_hr, odr_hz)

    out = Path(output_dir)
    out.mkdir(parents=True, exist_ok=True)
    csv_path = out / "ppg_digital.csv"
    data = np.column_stack([red, ir])
    np.savetxt(csv_path, data, fmt="%d", delimiter=",")
    print(f"  PPG digital stream -> {csv_path}  ({len(red)} samples @ {odr_hz} Hz)")

    return red, ir
