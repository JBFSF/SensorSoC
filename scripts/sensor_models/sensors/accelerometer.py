"""
accelerometer.py

Models the STMicroelectronics LIS2DW12 3-axis MEMS accelerometer.

Real sensor specs:
- Full scale: ±2g / ±4g / ±8g / ±16g (we use ±4g for sleep tracking)
- ADC: 14-bit output (left-justified in 16-bit register)
- ODR: 1.6 Hz to 1600 Hz (we use 25 Hz for sleep — low-power mode)
- Sensitivity: 0.488 mg/LSB at ±4g in low-power mode (12-bit effective)
- Noise: ~1.3 mg RMS in low-power mode
- I2C interface, 7-bit address 0x18 or 0x19 (SA0 pin)
- 32-level FIFO buffer

PhysioNet dataset (motion):
- Columns: timestamp, ax, ay, az (units: g)
- Originally captured at 50 Hz — we downsample to 25 Hz

Pipeline:
  Raw g values
    → gain error + offset (sensor imperfection model)
    → noise (1.3 mg RMS)
    → clip to ±4g
    → 14-bit ADC quantization (sensitivity 0.488 mg/LSB)
    → save as int16 CSV (one row per sample: ax, ay, az)

Default parameter values match LIS2DW12 datasheet specs at ±4g low-power mode.
All sensor model parameters can be overridden at call time for flexibility.
"""

import numpy as np
import os
import matplotlib.pyplot as plt
from pathlib import Path

# Reference defaults — documented here for traceability but not used directly.
# Pass overrides to process_accelerometer() as keyword arguments.
_DEFAULT_FS_G         = 4       # ±4g full scale
_DEFAULT_ODR_HZ       = 25      # 25 Hz ODR (low-power mode 2)
_DEFAULT_SENSITIVITY  = 0.488   # mg per LSB at ±4g low-power mode
_DEFAULT_NOISE_RMS_G  = 0.0013  # 1.3 mg RMS noise floor
_DEFAULT_GAIN_ERROR   = 0.02    # ±2% gain error (typ spec)
_DEFAULT_OFFSET_G     = 0.040   # up to 40 mg zero-g offset (typ spec)

PLOT_DIR = "sensor_output"   # validation plots only — gitignored


# LIS2DW12 sensor model

def _apply_lis2dw12_model(accel_g, fs_g, noise_rms_g, gain_error, offset_g):
    """Apply gain error, offset, noise, and clipping to raw g values."""
    gain   = 1.0 + np.random.uniform(-gain_error, gain_error, size=(1, 3))
    accel  = accel_g * gain
    offset = np.random.uniform(-offset_g, offset_g, size=(1, 3))
    accel  = accel + offset
    accel  = accel + np.random.normal(0, noise_rms_g, size=accel.shape)
    accel  = np.clip(accel, -fs_g, fs_g)
    return accel


def _adc_quantize_lis2dw12(accel_g, sensitivity_mg):
    """Quantize analog g values to 14-bit two's complement counts."""
    counts_per_g = 1000.0 / sensitivity_mg
    digital = np.round(accel_g * counts_per_g).astype(np.int32)
    digital = np.clip(digital, -8192, 8191)
    return digital.astype(np.int16)


# Validation plot

def _save_validation_plot(raw_g, digital, odr_hz, sensitivity_mg):
    duration_s = 10
    n = duration_s * odr_hz

    raw_plot = raw_g[:n, 0]
    dig_plot = digital[:n, 0].astype(float) * (sensitivity_mg / 1000.0)
    time     = np.arange(n) / odr_hz

    plt.figure(figsize=(10, 4))
    plt.plot(time, raw_plot, label="Raw input (g)")
    plt.plot(time, dig_plot, label="LIS2DW12 model (g)", alpha=0.75, linestyle="--")
    plt.xlabel("Time (s)")
    plt.ylabel("Acceleration (g)")
    plt.title("LIS2DW12 Accel Model — X axis (first 10 s)")
    plt.legend()
    plt.tight_layout()

    os.makedirs(PLOT_DIR, exist_ok=True)
    path = os.path.join(PLOT_DIR, "accel_validation.png")
    plt.savefig(path)
    plt.close()
    print("  Validation plot →", path)


# Main entry point

def process_accelerometer(
    raw_g: np.ndarray,
    output_dir,
    *,
    fs_g: float           = _DEFAULT_FS_G,
    odr_hz: int           = _DEFAULT_ODR_HZ,
    sensitivity_mg: float = _DEFAULT_SENSITIVITY,
    noise_rms_g: float    = _DEFAULT_NOISE_RMS_G,
    gain_error: float     = _DEFAULT_GAIN_ERROR,
    offset_g: float       = _DEFAULT_OFFSET_G,
) -> np.ndarray:
    """
    Run the LIS2DW12 sensor model pipeline on a (N, 3) array of raw g values.

    Args:
        raw_g:          NumPy array of shape (N, 3) — accelerometer x/y/z in g.
        output_dir:     Path to write accel_digital.csv.

    Keyword-only args (all have datasheet-accurate defaults):
        fs_g:           Full-scale range in g. Default 4 (±4g).
        odr_hz:         Output data rate in Hz. Default 25.
        sensitivity_mg: ADC sensitivity in mg/LSB. Default 0.488.
        noise_rms_g:    Gaussian noise floor in g RMS. Default 0.0013.
        gain_error:     Per-axis gain error fraction (±). Default 0.02.
        offset_g:       Zero-g offset in g (±). Default 0.040.

    Returns:
        digital: int16 array of shape (N, 3) — quantized ADC counts.
    """
    analog  = _apply_lis2dw12_model(raw_g, fs_g, noise_rms_g, gain_error, offset_g)
    digital = _adc_quantize_lis2dw12(analog, sensitivity_mg)

    _save_validation_plot(raw_g, digital, odr_hz, sensitivity_mg)

    out = Path(output_dir)
    out.mkdir(parents=True, exist_ok=True)
    csv_path = out / "accel_digital.csv"
    np.savetxt(csv_path, digital, fmt="%d", delimiter=",")
    print(f"  Accel digital stream → {csv_path}  ({len(digital)} samples @ {odr_hz} Hz)")

    return digital
