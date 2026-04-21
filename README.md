# SensorSoC

A UCSC Chip Design Capstone project by Ananya Manduva, Jackson Friday, Nathan Nakamoto, Nithin Duvvuru, Rishi Govindan, and Shane Stearns.

The goal is a custom ASIC SoC that intakes accelerometer and PPG sensor data, processes it, and feeds a lightweight three-layer MLP model that determines whether the user is in a good stage to wake (NREM/light sleep) or not (REM/deep sleep). A PicoRV32 core on chip sends a GPIO alarm signal at wake time. The chip sleeps until a watchdog timer fires, indicating it's time to check sleep states.

Fabricated on the GF180MCU process via [wafer.space](https://wafer.space) MPW runs.

## Directories

* `src/` — All RTL sources (SystemVerilog/Verilog)
* `cocotb/` — Simulation testbenches (cocotb + Icarus Verilog)
* `scripts/` — Utility scripts (padring flow, GDS rendering)
* `librelane/` — LibreLane PnR configuration and slot definitions
* `ip/` — Custom IP blocks (chip ID, wafer.space logo)
* `misc/` — ML model pipeline, sensor models, datasets

## Prerequisites

We use a custom fork of the [gf180mcuD PDK variant](https://github.com/wafer-space/gf180mcu) until all changes have been upstreamed.

To clone the latest PDK version, run:

```
make clone-pdk
```

Install LibreLane by following the Nix-based installation instructions: https://librelane.readthedocs.io/en/latest/installation/nix_installation/index.html

## Implement the Design

This repository contains a Nix flake that provides a shell with the [`leo/gf180mcu`](https://github.com/librelane/librelane/tree/leo/gf180mcu) branch of LibreLane.

Run `nix-shell` in the root of this repository, then:

```
make librelane
```

## View the Design

After completion, view using the OpenROAD GUI:

```
make librelane-openroad
```

Or using KLayout:

```
make librelane-klayout
```

## Simulation

We use [cocotb](https://www.cocotb.org/) with Icarus Verilog for RTL verification. See `cocotb/README.md` for the full list of testbench targets.

To run the top-level chip RTL simulation:

```
make sim
```

To run the gate-level simulation (requires a completed LibreLane run in `final/`):

```
make sim-gl
```

View waveforms:

```
make sim-view
```

Waveform output: `cocotb/sim_build/chip_top.fst`

## Slot Sizes

Supported slot sizes: `1x1` (default), `0p5x1`, `1x0p5`, `0p5x0p5`.

```
SLOT=0p5x0p5 make librelane
```

## Standalone Padring (Analog Design)

```
make librelane-padring
```

## Precheck

Run the [gf180mcu-precheck](https://github.com/wafer-space/gf180mcu-precheck) with your layout before submission.

## Dataset

ML training data sourced from PhysioNet:

Walch, Olivia. "Motion and heart rate from a wrist-worn wearable and labeled sleep from polysomnography" (version 1.0.0). PhysioNet (2019). https://doi.org/10.13026/hmhs-py35

## Pinout
### Normal Mode
Standard chip behavior when

`input_in[3:0] = 4'b0000;`

#### Input Pins (12)

* `input_in[3:0]` — test mode selector
* `input_in[11:4]` — unused

#### Bidirectional IO Pins (40)

* `bidir[0]` — alarm output
* `bidir[1]` — SPI flash clock output
* `bidir[2]` — SPI flash MOSI output
* `bidir[3]` — SPI flash CS_n output
* `bidir[4]` — SPI flash MISO input
* `bidir[5]` — I2C SCL input
* `bidir[6]` — I2C SDA open drain in/out
* `bidir[22:7]` — 16-bit debug bus outputs in test modes
* `bidir[37]` — force Pico IRQ input used in test mode `4'b1010`
* `bidir[38]` — force wake source input used in test mode `4'b1011`
* `bidir[39]` — external test clock input used in test mode `4'b0101`
* `bidir[36:23]` — unused

#### Analog Pins (2)

* `analog[1:0]` — unused

### Test Modes

* `4'b0000` — normal mode; debug bus is disabled.
* `4'b0001` — drives `rmssd_feat[15:0]` onto `bidir[22:7]`.
* `4'b0010` — drives `delta_hr_feat[15:0]` onto `bidir[22:7]`.
* `4'b0011` — drives `time_feat[15:0]` onto `bidir[22:7]`.
* `4'b0100` — drives `motion_feat[15:0]` onto `bidir[22:7]`.
* `4'b0101` — uses `bidir[39]` as an external test clock.
* `4'b0110` — drives `{ml_update_gate, epoch_end, invalid_reason[7:0], 6'b0}` onto `bidir[22:7]`.
* `4'b0111` — drives `{pico_trap, pico_cpu_clk_en, pico_mem_valid, pico_mem_instr, pico_mem_ready, pico_mem_wstrb[3:0], pico_mem_addr[6:0]}` onto `bidir[22:7]`.
* `4'b1000` — drives `{pico_mem_valid && (pico_mem_wstrb != 4'b0000), pico_trap, |pico_mem_wstrb, pico_mem_wstrb == 4'hF, pico_mem_addr[7:0], pico_mem_wdata[3:0]}` onto `bidir[22:7]`.
* `4'b1001` — drives `{pico_trap, pico_sleeping, pico_cpu_clk_en, |pico_irq, 12'b0}` onto `bidir[22:7]`.
* `4'b1010` — uses `bidir[37]` to force Pico IRQ and drives `{test_force_irq, pico_trap, pico_cpu_clk_en, pico_mem_instr, pico_mem_valid, pico_mem_ready, pico_mem_addr[9:0]}` onto `bidir[22:7]`.
* `4'b1011` — uses `bidir[38]` to force wake and drives `{test_force_wake, host_i2c_irq_event, ml_irq, timer_event, 12'b0}` onto `bidir[22:7]`.

