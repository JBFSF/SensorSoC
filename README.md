# SensorSoC

A UCSC Chip Design Capstone project by Ananya Manduva, Jackson Friday, Nathan Nakamoto, Nithin Duvvuru, Rishi Govindan, and Shane Stearns.

The goal is a custom ASIC SoC that intakes accelerometer and PPG sensor data, processes it, and feeds a lightweight three-layer MLP model that determines whether the user is in a good stage to wake (NREM/light sleep) or not (REM/deep sleep). A PicoRV32 core on chip sends a GPIO alarm signal at wake time. The chip sleeps until a watchdog timer fires, indicating it's time to check sleep states.

Fabricated on the GF180MCU process via [wafer.space](https://wafer.space) MPW runs.

## Directories

* `src/` - All RTL sources (SystemVerilog/Verilog)
* `cocotb/` - Simulation testbenches (cocotb + Icarus Verilog)
* `scripts/` - Utility scripts (padring flow, GDS rendering)
* `librelane/` - LibreLane PnR configuration and slot definitions
* `ip/` - Custom IP blocks (chip ID, wafer.space logo)
* `misc/` - ML model pipeline, sensor models, datasets

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

To rerun the current reproducible firmware smoke flow:

```
make repro-firmware-flow
```

That script initializes submodules, checks the RISC-V toolchain, rebuilds both
firmware integration images (`irq_test` and `prod_main`), then runs the DFT
smoke test, IRQ-state regression, and production firmware host-I2C/ML smoke
regression.

The reproducible setup is split into smaller Make targets:

```
make init-submodules          # git submodule update --init --recursive
make python-deps              # install requirements.txt into .venv
make check-riscv-toolchain    # verify riscv-none-elf/riscv64-unknown-elf tools
make repro-firmware-build     # rebuild irq_test and prod_main only
make repro-firmware-flow      # rebuild firmware and run smoke regressions
```

If the RISC-V GCC toolchain is vendored as a submodule, put the source at
`third_party/riscv-gnu-toolchain` and build it with:

```
git submodule update --init --recursive
make build-riscv-toolchain
```

The build installs into `third_party/riscv-toolchain`, which the firmware
scripts automatically detect. Skip `make build-riscv-toolchain` when
`make check-riscv-toolchain` already finds an external toolchain.

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

`input_in[4:0] = 5'b00000;`

#### Input Pins (12)

* `input_in[4:0]` - test mode selector
* `input_in[11:5]` - unused

#### Bidirectional IO Pins (40)

* `bidir[0]` - alarm output
* `bidir[1]` - SPI flash clock output
* `bidir[2]` - SPI flash MOSI output
* `bidir[3]` - SPI flash CS_n output
* `bidir[4]` - SPI flash MISO input
* `bidir[5]` - I2C SCL input
* `bidir[6]` - I2C SDA open drain in/out
* `bidir[22:7]` - 16-bit debug bus outputs in debug/test modes
* `bidir[37]` - force Pico IRQ input used in test modes `5'b01010` and `5'b11010`
* `bidir[38]` - force wake source input used in test modes `5'b01011` and `5'b11011`
* `bidir[39]` - external test clock input used by the `1xxxx` test-mode bank
* `bidir[36:23]` - unused

#### Analog Pins (2)

* `analog[1:0]` - unused

### Test Modes

* `5'b00000` - normal mode on the onboard PLL clock; debug bus is disabled.
* `5'b00001` - drives `mssd_feat[15:0]` onto `bidir[22:7]`.
* `5'b00010` - drives `delta_hr_feat[15:0]` onto `bidir[22:7]`.
* `5'b00011` - drives `time_feat[15:0]` onto `bidir[22:7]`.
* `5'b00100` - drives `motion_feat[15:0]` onto `bidir[22:7]`.
* `5'b00101` - drives `{|mssd_feat, |delta_hr_feat, |time_feat, |motion_feat, feat_valid, |logit0, |logit1, ml_update_gate, epoch_end, alarm, 6'b0}` onto `bidir[22:7]`.
* `5'b00110` - drives `{ml_update_gate, epoch_end, invalid_reason[7:0], 6'b0}` onto `bidir[22:7]`.
* `5'b00111` - drives `{pico_trap, pico_cpu_clk_en, pico_mem_valid, pico_mem_instr, pico_mem_ready, pico_mem_wstrb[3:0], pico_mem_addr[6:0]}` onto `bidir[22:7]`.
* `5'b01000` - drives `{pico_mem_valid && (pico_mem_wstrb != 4'b0000), pico_trap, |pico_mem_wstrb, pico_mem_wstrb == 4'hF, pico_mem_addr[7:0], pico_mem_wdata[3:0]}` onto `bidir[22:7]`.
* `5'b01001` - drives `{pico_trap, pico_sleeping, pico_cpu_clk_en, |pico_irq, 12'b0}` onto `bidir[22:7]`.
* `5'b01010` - uses `bidir[37]` to force Pico IRQ and drives `{test_force_irq, pico_trap, pico_cpu_clk_en, pico_mem_instr, pico_mem_valid, pico_mem_ready, pico_mem_addr[9:0]}` onto `bidir[22:7]`.
* `5'b01011` - uses `bidir[38]` to force wake and drives `{test_force_wake, host_i2c_irq_event, ml_irq, timer_event, 12'b0}` onto `bidir[22:7]`.
* `5'b01100` - drives `logit0[15:0]` onto `bidir[22:7]`.
* `5'b01101` - drives `logit1[15:0]` onto `bidir[22:7]`.
* `5'b01110` - currently unused
* `5'b01111` - currently unused
* `5'b10000` - normal mode on the external test clock from `bidir[39]`; debug bus is disabled.
* `5'b1xxxx` - same debug-bus mapping as `0xxxx`, but clocked from `bidir[39]` instead of `clk`.
