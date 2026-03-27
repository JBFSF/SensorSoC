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
