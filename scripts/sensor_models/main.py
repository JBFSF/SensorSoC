"""
main.py

System-level integration of wearable sensor interface model.

Functionality:
- Streams sensor data from PhysioNet
- Processes accelerometer and PPG sensor modules
- Writes digital sensor streams to sim/data/ for use by SV simulation
- Computes I2C bandwidth requirements
- Verifies that combined sensor load fits within 100 kbps I2C limit

This represents:
  Sensors → I2C bus → SoC interface validation

Usage:
  Run once from anywhere to generate sim/data/accel_digital.csv
  and sim/data/ppg_digital.csv. The SV simulation reads these directly.
"""

from pathlib import Path
from data.loader import load_motion, load_heartrate
from sensors.accelerometer import process_accelerometer
from sensors.ppg import process_ppg

# Resolves to repo_root/sim/data/ regardless of where main.py is invoked from
SIM_DATA_DIR = Path(__file__).parent.parent.parent / "cocotb" / "sim" / "data"


def main():
    # Load data — streamed directly from PhysioNet, nothing saved to disk
    raw_g      = load_motion()
    t_bpm, bpm = load_heartrate()

    # Run sensor models, writing CSVs to sim/data/
    process_accelerometer(raw_g, SIM_DATA_DIR)
    process_ppg(t_bpm, bpm, SIM_DATA_DIR)

    # I2C bandwidth summary
    print("\n--- Interface Summary ---")
    accel_rate = 50 * 3 * 12      # 50 Hz * 3 axes * 12 bits
    ppg_rate   = 1 * 12           # 1 Hz * 12 bits
    total_bps  = accel_rate + ppg_rate

    print("Accel data rate:", accel_rate, "bps")
    print("PPG data rate:  ", ppg_rate,   "bps")
    print("Total data rate:", total_bps,  "bps")

    if total_bps < 100_000:
        print("Standard I2C (100 kbps) is sufficient")


if __name__ == "__main__":
    main()
    