"""
main.py

System-level integration of wearable sensor interface model.

Functionality:
- Processes accelerometer and PPG sensor modules
- Generates digital sensor streams
- Computes I2C bandwidth requirements
- Verifies that combined sensor load fits within 100 kbps I2C limit

This represents:
Sensors → I2C bus → SoC interface validation
"""

from sensors.accelerometer import process_accelerometer
from sensors.ppg import process_ppg


def main():
    # these are the files from the PhysioNet Dataset, can be changed here based on location of txt files
    motion_path = r"C:\Users\amand\CSE127A\sensor_model_project\sleep-accel-1.0.0\motion-and-heart-rate-from-a-wrist-worn-wearable-and-labeled-sleep-from-polysomnography-1.0.0\motion"
    heartrate_path = r"C:\Users\amand\CSE127A\sensor_model_project\sleep-accel-1.0.0\motion-and-heart-rate-from-a-wrist-worn-wearable-and-labeled-sleep-from-polysomnography-1.0.0\heart_rate"

    # Accelerometer
    accel_data = process_accelerometer(motion_path)

    # PPG
    ppg_data = process_ppg(heartrate_path)

    print("\n--- Interface Summary ---")
    accel_rate = 50 * 3 * 12
    ppg_rate = 1 * 12
    total_bps = accel_rate + ppg_rate

    print("Accel data rate:", accel_rate, "bps")
    print("PPG data rate:", ppg_rate, "bps")
    print("Total data rate:", total_bps, "bps")

    if total_bps < 100000:
        print("Standard I2C (100 kbps) is sufficient")


if __name__ == "__main__":
    main()
