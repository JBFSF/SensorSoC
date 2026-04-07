# RTL

This directory contains the main SystemVerilog RTL for `SensorSoC`, including the sensor-processing pipeline and feature extraction blocks.

# Inside this Directory
* ppg_fifo_reader.sv
  * Reads PPG samples from the sensor FIFO over I2C and outputs timestamped samples + status/error flags.
* ppg_process.sv
  * Detects beats from the PPG stream and computes RR intervals and beat-quality signals.
* motion_process.sv
  * Preprocesses accelerometer samples into a per-epoch motion-energy feature.
* cos_lut_timer.sv
  * Generates a cosine time feature from the seconds counter using a small LUT (configurable period/scale).
* accel_reader.sv
  * Polls/configures the accelerometer over I2C and outputs X/Y/Z samples with a valid strobe.
* rmssd_engine.sv
  * Computes epoch RMSSD from accepted RR intervals.
* feature_engine.sv
  * Latches per-epoch features (time, motion, delta-HR, RMSSD) and outputs a single `feat_valid_o` strobe.
* signal_quality.sv
  * Aggregates beat quality, motion intensity, and FIFO/I2C faults to gate ML updates (`ml_update_gate_o`).
* cpu_to_ml.v
  * Small standalone integration module used to validate the ML control path without involving (`soc_top`) or the full PicoRV32 system
  * It connects a "fake CPU" MMIO interface (driven by cocotb) to the (`taketwo`) ML wrapper through the (`ml_axil_bridge_mmio`) AXI-Lite bridge
* timer_mmio.v
  * programmable countdown timer with a memory mapped control interface. It runs on the always on clk, so it continues counting even when the CPU is gated off.
  * The timer can also act as a watchdog style monitor. Firmware must periodically reload or update the counter. If the counter reaches zero before being serviced, the module raises a sticky event flag. This allows the system to detect stalled firmware or missed scheduling deadlines and trigger a wake up or recovery action.
* test_mmio.v
  * Minimal memmory mapped peripheral used for simulation and firmware debugging.
  * Provides a simple way for firmware running on the CPU to communicate test results and debug information to the simulation testbench
  * Intended for verification, not final hardware functionality
* pwrctrl_mmio.v
  * The SoC's power controller, lives in the always on clock domain.
  * Its job is to let firmware, request sleep, capture wake events, and report why the CPU woke up
  * This module does not gate the CPU clock itself. Instead it outputs a sleep request signal that the clock gating logic in (`soc_top`) can use.
* ml_stub_mmio.v
  * Stand in ML peripheral used for testing before the actual ML accelerator + AXI interface is ready.
  * Provides a tiny MMIO block that firmware can use to manually trigger an "ML result ready" event
* reset_ctrl.v
  * Reset controller ran in the always on clock domain. Turns multiple reset sources into clean, timed reset pulses.
* simple_sram.v
  * 32-bit synchronous memory model used by the SoC during sim. Behaves similarly to a small on chip SRAM, and is used to store firmware, stack data, and program state for the CPU
  * Likely to synthesize to flip flops, replace with generated SRAM macro soon (SRAM-Forge)
* soc_top.v
  * Instantiates the PicoRV32, SRAM, all MMIO peripherals, and an always on sleep/wake controller that gates the CPU clock while keeping wake sources on.
* ml_axil_bridge_mmio.v
  * MMIO peripheral that lets the PicoRV32 CPU acess an AXI-Lite slave (ML accelerator's (`saxi_*`) interface) using the SoC's ready/valid bus.

