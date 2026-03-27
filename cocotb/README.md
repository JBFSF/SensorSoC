# sleep_soc
Our overall simulation design in RTL, with simulation and testbenches in cocotb/. Full end-to-end sim tbd

# Using the Makefile
 * ML test - command: `make test-ml`
   * Runs the first 1000 lines of the ml training data through the RTL and outputs it in Confusion Matrix form
 * Globaltimer test - command: `make sim-globaltimer`
  *  
 * Top pipeline sim (sim top) - command: `make sim-top-pipeline`
   * From repo root: `make -C sleep_soc sim-top-pipeline` (or `cd sleep_soc && make sim-top-pipeline`)
   * Runs `sim/tb/top_pipeline_tb.sv` with the full sensor-processing pipeline (`rtl/top.sv`)
   * Outputs a waveform at `sim/waves/top_pipeline_tb.vcd`
* SoC Watchdog Timer Sleep/Wake test - command: `make sim-soc FW_VARIANT=test_sleepwake_periodic`
  * Runs `sim/tb/tb_soc.sv` with chosen firmware loaded, and ran with CPU and MMIO instances (`rtl/soc_top.v`)
  * Outputs a waveform at `sleep_soc/soc.vcd`
* Watchdog-like Timer test - command: `make test-timer`
  * Runs cocotb unit test for timer (`test_timer_mmio.py`)
* Reset Controller test - command: `make sim-reset-ctrl`
  * 
* CPU to ML test - command: `make test-cpu-ml`
  * Cocotb test (`cpu_to_ml_tb.py`) that verifies Axi-Lite bridge mmio module, connection to ml wrapper, and ability to read and write
* Sensor pipeline integration test - command: `make sim-sensor-pipeline`
   * Runs `sim/tb/tb_sensor_pipeline.sv` integrating the I2C master, LIS2DW12 accel slave model, ADPD144RI PPG slave model, accel reader, PPG FIFO reader, motion preprocessor, and global timer
   * Slave models stream real sensor data from `sim/data/accel_digital.csv` and `sim/data/ppg_digital.csv`
   * PASS criteria: ≥25 accel samples at 25Hz, ≥3 PPG samples, ≥1 motion energy epoch
   * Outputs a waveform at `sim/waves/sensor_pipeline.vcd` (or run directly: `vvp sim/build/tb_se
*  IRQ Sleep/Wake test - command: command: make `firmware-main && make sim-irq`
  *  Runs `sim/tb/tb_irq.sv`, validates wake behavior
  *  Writes `irq.vcd`
* Host I2C target & bridge regs test  - command: `make sim-host-i2c-target`
  * Runs `sim/tb/tb_host_i2c_target.sv` as a unit test for `host_i2c_target.v` and `host_i2c_bridge_regs.v` for i2c transactions/reads and an event pulse for the gpio.
  * Writes `/tmp/tb_host_i2c_target.vcd`
* Host I2C to IRQ integration test - command: `make sim-host-i2c-irqc-proxy`
  *  Runs `rtl/tb_host_i2c_irqc_proxy.sv` and tests the integration of the Host i2c register accesses into the irq wotjpit firmware.
  *  Writes `/tmp/tb_soc_host_i2c_irq.vcd`
