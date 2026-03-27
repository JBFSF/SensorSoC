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
"""

import numpy as np
import os
import matplotlib.pyplot as plt

# LIS2DW12 config
ACCEL_FS_G      = 4          # ±4g full scale
ACCEL_ODR_HZ    = 25         # 25 Hz ODR (low-power mode 2)
ADC_BITS        = 14         # 14-bit output
SENSITIVITY_MG  = 0.488      # mg per LSB at ±4g low-power mode
NOISE_RMS_G     = 0.0013     # 1.3 mg RMS noise floor
GAIN_ERROR      = 0.02       # ±2% gain error (typ spec)
OFFSET_G        = 0.040      # up to 40 mg zero-g offset (typ spec)

OUTPUT_DIR      = "sensor_output"
MAX_SAMPLES     = 10_000

# Downsample ratio: PhysioNet is 50 Hz, sensor ODR is 25 Hz
DS_RATIO        = 2


# Data loading

def load_motion_directory(directory):
    print("Loading motion directory...")
    all_data = []
    for fname in os.listdir(directory):
        if fname.endswith(".txt"):
            path = os.path.join(directory, fname)
            print("  Loading", fname)
            data = np.loadtxt(path)          # cols: time, x, y, z
            all_data.append(data[:, 1:4])    # keep x,y,z only
    data = np.vstack(all_data)

    if MAX_SAMPLES is not None:
        data = data[:MAX_SAMPLES]
    # Downsample 50 Hz → 25 Hz
    data = data[::DS_RATIO]
    print(f"  Samples after downsample: {len(data)}  (ODR={ACCEL_ODR_HZ} Hz)")
    return data


# LIS2DW12 sensor model

def apply_lis2dw12_model(accel_g):
    """
    Applies per-axis gain error, fixed offset, and noise floor matching
    LIS2DW12 datasheet specs.
    """
    # Per-axis gain error (same draw for all axes, like a real production part)
    gain = 1.0 + np.random.uniform(-GAIN_ERROR, GAIN_ERROR, size=(1, 3))
    accel = accel_g * gain

    # Fixed zero-g offset per axis (random draw in ±OFFSET_G)
    offset = np.random.uniform(-OFFSET_G, OFFSET_G, size=(1, 3))
    accel = accel + offset

    # Gaussian noise floor (1.3 mg RMS)
    accel = accel + np.random.normal(0, NOISE_RMS_G, size=accel.shape)

    # Clip to full-scale range
    accel = np.clip(accel, -ACCEL_FS_G, ACCEL_FS_G)

    return accel


def adc_quantize_lis2dw12(accel_g):
    """
    14-bit two's complement quantization.
    Sensitivity: SENSITIVITY_MG mg/LSB  →  counts = g_value / (SENSITIVITY_MG/1000)
    Range: -8192 to +8191
    """
    counts_per_g = 1000.0 / SENSITIVITY_MG        # LSB/g
    digital = np.round(accel_g * counts_per_g).astype(np.int32)

    # Clip to 14-bit signed range
    digital = np.clip(digital, -8192, 8191)
    return digital.astype(np.int16)


# Validation plot

def save_validation_plot(raw_g, digital, filename):
    duration_s = 10
    n = duration_s * ACCEL_ODR_HZ

    raw_plot  = raw_g[:n, 0]
    dig_plot  = digital[:n, 0].astype(float) * (SENSITIVITY_MG / 1000.0)  # back to g
    time      = np.arange(n) / ACCEL_ODR_HZ

    plt.figure(figsize=(10, 4))
    plt.plot(time, raw_plot,  label="Raw input (g)")
    plt.plot(time, dig_plot,  label="LIS2DW12 model (g)", alpha=0.75, linestyle="--")
    plt.xlabel("Time (s)")
    plt.ylabel("Acceleration (g)")
    plt.title("LIS2DW12 Accel Model — X axis (first 10 s)")
    plt.legend()
    plt.tight_layout()

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    path = os.path.join(OUTPUT_DIR, filename)
    plt.savefig(path)
    plt.close()
    print("  Validation plot →", path)


# Main

def process_accelerometer(directory):
    raw_g   = load_motion_directory(directory)
    analog  = apply_lis2dw12_model(raw_g)
    digital = adc_quantize_lis2dw12(analog)

    save_validation_plot(raw_g, digital, "accel_validation.png")


    os.makedirs(OUTPUT_DIR, exist_ok=True)
    csv_path = os.path.join(OUTPUT_DIR, "accel_digital.csv")
    # No header — $fscanf in accel_file_player.sv reads bare integers
    np.savetxt(csv_path, digital, fmt="%d", delimiter=",")
    print(f"  Accel digital stream → {csv_path}  ({len(digital)} samples @ {ACCEL_ODR_HZ} Hz)")

    return digital
