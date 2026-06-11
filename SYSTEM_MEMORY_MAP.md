# System Memory Map

This document collects the current system-level address map in one place for the unified RTL in [top.sv].

It is meant to be a practical debug reference for firmware, cocotb, and RTL work.

## Top-Level MMIO Pages

| Block | Base Address | Source | Notes |
|---|---:|---|---|
| Power control | `0x0300_1000` | [pwrctrl_mmio.v](pwrctrl_mmio.v) | Sleep request and wake reason/status |
| Timer | `0x0300_2000` | [timer_mmio.v](timer_mmio.v) | Always-on wake timer |
| ML AXI-Lite bridge | `0x0300_3000` | [ml_axil_bridge_mmio.v](ml_axil_bridge_mmio.v) | CPU-facing control path into `taketwo` |
| Feature MMIO | `0x0300_4000` | [top.sv](top.sv) | Latched feature outputs from feature engine |
| IRQ controller | `0x0300_5000` | [irq_ctrl_mmio.v](irq_ctrl_mmio.v) | Pending/mask/wake/claim/complete |
| ML weight/feature/logit window | `0x0300_6000` | [weight_flash_axi.v](weight_flash_axi.v) | Feature input regs, weight flash bridge, logit output regs |
| Firmware SPI master MMIO | `0x0300_A000` | [spi_master_mmio.v](spi_master_mmio.v) | CPU-driven SPI master |
| Test/debug MMIO | `0x0300_F000` | [test_mmio.v](test_mmio.v) | PASS/FAIL/status/config visibility |


## Power Control Page

Base: `0x0300_1000`

| Offset | Address | Name | Access | Meaning |
|---|---:|---|---|---|
| `0x00` | `0x0300_1000` | `CTRL` | `RW` | bit0 = `sleep_req` |
| `0x04` | `0x0300_1004` | `WAKE_STATUS` | `R/W1C` | Sticky OR of wake sources |
| `0x08` | `0x0300_1008` | `WAKE_REASON` | `RO` | Snapshot of wake flags on asleep->awake |

## Timer Page

Base: `0x0300_2000`

| Offset | Address | Name | Access | Meaning |
|---|---:|---|---|---|
| `0x00` | `0x0300_2000` | `CTRL` | `RW` | bit0 = enable, bit1 = periodic |
| `0x04` | `0x0300_2004` | `RELOAD` | `RW` | Reload value |
| `0x08` | `0x0300_2008` | `COUNT` | `RW` | Current counter |
| `0x0C` | `0x0300_200C` | `EVENT` | `R/W1C` | bit0 = sticky timeout event |

## ML AXI-Lite Page

Base: `0x0300_3000`

This page is the CPU-facing register window into `taketwo`. The offsets below are the ones currently used by firmware and tests.

| Offset | Address | Meaning | Current Usage |
|---|---:|---|---|
| `0x10` | `0x0300_3010` | Start/control register | `ML_REG(0x10) = 1` starts ML |
| `0x14` | `0x0300_3014` | Busy/status register | `ML_REG(0x14) & 1` used as busy bit |
| `0x80` | `0x0300_3080` | Global base | Usually programmed to `0x0300_6000` |
| `0x88` | `0x0300_3088` | Final output base offset | Usually programmed to `5504` |
| `0x8C` | `0x0300_308C` | Input feature base offset | Usually programmed to `64` |
| `0x90` | `0x0300_3090` | Weight/parameter base offset | Usually programmed to `128` |

### Current ML Programming Convention

Common firmware pattern:

| Register | Value | Meaning |
|---|---:|---|
| `ML_REG(0x80)` | `0x0300_6000` | Global base = weight/feature/logit page |
| `ML_REG(0x88)` | `5504` | Final output goes to `WEIGHT_BASE + 5504` |
| `ML_REG(0x8C)` | `64` | Input features at `WEIGHT_BASE + 64` |
| `ML_REG(0x90)` | `128` | Weight/parameter region starts at offset `128` |

## Feature MMIO Page

Base: `0x0300_4000`

This page is built directly in [top.sv]. It exposes the latched feature vector from the feature engine.

| Offset | Address | Name | Access | Meaning |
|---|---:|---|---|---|
| `0x00` | `0x0300_4000` | `FEATURE_STATUS` | `RW` | bit0 = valid, bits `[8:1]` = invalid reason, bit16 = gate |
| `0x04` | `0x0300_4004` | `FEATURE_TIME` | `RO` | Signed 16-bit time feature |
| `0x08` | `0x0300_4008` | `FEATURE_MOTION` | `RO` | Signed 16-bit motion feature |
| `0x0C` | `0x0300_400C` | `FEATURE_DHR` | `RO` | Signed 16-bit delta-HR feature |
| `0x10` | `0x0300_4010` | `FEATURE_RMSSD` | `RO` | Signed 16-bit MSSD feature |

### `FEATURE_STATUS` Bit Layout

Current packing in [top.sv]:

- bit `0`: `feat_latched_valid`
- bits `8:1`: `feat_invalid_reason_latched`
- bit `16`: `feat_gate_latched`

## IRQ Controller Page

Base: `0x0300_5000`

| Offset | Address | Name | Access | Meaning |
|---|---:|---|---|---|
| `0x00` | `0x0300_5000` | `PENDING` | `RO/W1C` | Sticky pending IRQ bits |
| `0x04` | `0x0300_5004` | `MASK` | `RW` | Enabled IRQ mask |
| `0x08` | `0x0300_5008` | `WAKE_EN` | `RW` | Wake-enabled IRQ mask |
| `0x0C` | `0x0300_500C` | `ACTIVE` | `RO` | Active claimed IRQ bit |
| `0x10` | `0x0300_5010` | `RAW` | `RO` | Raw synchronized source bits |
| `0x14` | `0x0300_5014` | `CLAIM` | `RO` | Encoded claim ID |
| `0x18` | `0x0300_5018` | `COMPLETE` | `WO` | Encoded completion ID |

## ML Weight / Feature / Logit Page

Base: `0x0300_6000`

This page is currently implemented by [weight_flash_axi.v].

It has three roles:

- CPU writes feature input words here
- `taketwo` reads features here and reads weights from flash through this bridge
- `taketwo` writes final logits back here for CPU visibility

### Current Important Offsets

| Offset | Address | Name | Access | Meaning |
|---|---:|---|---|---|
| `0x40` | `0x0300_6040` | `X_OFFSET` word 0 | `RW` | Feature input word 0 |
| `0x44` | `0x0300_6044` | `X_OFFSET` word 1 | `RW` | Feature input word 1 |
| `0x80` | `0x0300_6080` | `VAR_BASE` | convention | Weight/parameter base offset used by firmware |
| `0x1580` | `0x0300_7580` | `LOGIT_OFFSET` word 0 | `RO` from CPU view | Final output/logit word 0 |
| `0x1584` | `0x0300_7584` | `LOGIT_OFFSET` word 1 | `RO` from CPU view | Final output/logit word 1 |

### Current Semantics

- CPU writes at `0x40` and `0x44` update `feat_reg_0` and `feat_reg_1`
- CPU reads at `0x1580` and `0x1584` return `logit_reg_0` and `logit_reg_1`
- `taketwo` AXI reads in the `X_OFFSET` window are served from feature registers
- `taketwo` AXI reads outside that window go to the dedicated weight SPI flash
- `taketwo` AXI writes at `LOGIT_OFFSET` are snooped into the CPU-visible logit registers

## Firmware SPI Master Page

Base: `0x0300_A000`

| Offset | Address | Name | Access | Meaning |
|---|---:|---|---|---|
| `0x00` | `0x0300_A000` | `CS` | `RW` | Chip select control |
| `0x04` | `0x0300_A004` | `STATUS` | `RO` | bit0 = busy |
| `0x08` | `0x0300_A008` | `DATA` | `RW` | Writing triggers 8-bit transfer; read returns RX byte |
| `0x0C` | `0x0300_A00C` | `DIVIDER` | `RW` | SPI clock divider |

## Test / Debug Page

Base: `0x0300_F000`

| Offset | Address | Name | Access | Meaning |
|---|---:|---|---|---|
| `0x00` | `0x0300_F000` | `STATUS` | `RW` | PASS/FAIL/status word |
| `0x04` | `0x0300_F004` | `CODE` | `RW` | Debug code / checkpoint |
| `0x08` | `0x0300_F008` | `CFG_TARGET_SEC` | `RO` | Mirrored wake config |
| `0x0C` | `0x0300_F00C` | `CFG_WINDOW_SEC` | `RO` | Mirrored wake config |
| `0x10` | `0x0300_F010` | `CFG_STEP_SEC` | `RO` | Mirrored wake config |
| `0x14` | `0x0300_F014` | `CFG_MOTION` | `RO` | `{count, threshold}` view |
| `0x18` | `0x0300_F018` | `CFG_CONF_THR` | `RO` | Confidence threshold |
| `0x1C` | `0x0300_F01C` | `CFG_POLICY` | `RO` | Wake policy |
| `0x20` | `0x0300_F020` | `ML_SCORE` | `RW` | Score/confidence proxy |


## Current Debugging Notes

- The ML output address contract is currently:
  - global base `0x0300_6000`
  - final output base offset `5504`
  - final output word 0 at `0x0300_7580`
- The final output write address has been confirmed in the short ML-control bench.
- The current ML issue is not the address map itself. The final output data is still becoming `X` inside `taketwo` before it reaches the CPU-visible logit registers.
