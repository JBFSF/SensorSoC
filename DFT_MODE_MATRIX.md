# DFT Mode Table

This document is a first-pass coordination table for the chip debug / DFT test
mode scheme in `chip_core.sv`.

Purpose:

- give one row per test mode
- define what stimulus is needed
- define what should appear on `bidir[22:7]`
- identify which modes need firmware and/or sensor models
- provide a place to agree on golden outputs with Shane

## Current Table

| Mode | Name | Clock | Stimulus Needed | Firmware Needed | Sensor Models Needed | Expected `bidir[22:7]` | Golden / Pass Condition | Priority |
|---|---|---|---|---|---|---|---|---|
| `00000` | Normal | Internal | None | Yes | Maybe | Debug bus disabled / zero | Debug bus inactive in normal mode | High |
| `00001` | MSSD Feature | Internal | Let feature pipeline run | Yes | Yes | `mssd_feat[15:0]` | Matches internal feature signal at sample point | Medium |
| `00010` | Delta HR Feature | Internal | Let feature pipeline run | Yes | Yes | `delta_hr_feat[15:0]` | Matches internal feature signal at sample point | Medium |
| `00011` | Time Feature | Internal | Let feature pipeline run | Yes | Maybe | `time_feat[15:0]` | Matches internal feature signal at sample point | Medium |
| `00100` | Motion Feature | Internal | Let feature pipeline run | Yes | Yes | `motion_feat[15:0]` | Matches internal feature signal at sample point | Medium |
| `00101` | Pipeline Smoke Summary | Internal | Let system run | Yes | Yes | Summary bits for feature presence, logits, gate, epoch, and alarm | Expected summary bits go active when pipeline is live | High |
| `00110` | ML Update / Invalid Reason | Internal | Run valid and invalid pipeline cases | Yes | Yes | `{ml_update_gate, epoch_end, invalid_reason[7:0], 6'b0}` | Matches internal control/status signals | Medium |
| `00111` | Pico State Summary | Internal | Boot firmware | Yes | No | CPU trap/clock/mem summary | Reflects active CPU execution and no unexpected trap | High |
| `01000` | Pico MMIO Write Summary | Internal | Run firmware with MMIO writes | Yes | No | MMIO write summary | Shows expected address/data/write activity | High |
| `01001` | Pico Sleep / IRQ Summary | Internal | Run sleep/wake firmware | Yes | No | Sleep/IRQ summary | Matches expected sleep/awake/IRQ phase | High |
| `01010` | Force IRQ View | Internal | Drive `bidir[37]` | Minimal | No | Forced IRQ summary | Forced IRQ bit and related fields respond correctly | Very High |
| `01011` | Force Wake View | Internal | Drive `bidir[38]` | Minimal | No | Forced wake / wake-source summary | Forced wake bit visible and wake summary coherent | Very High |
| `01100` | Logit0 View | Internal | Run ML once | Yes | Likely Yes | `logit0[15:0]` | Matches agreed internal/exported `logit0` value | Medium |
| `01101` | Logit1 View | Internal | Run ML once | Yes | Likely Yes | `logit1[15:0]` | Matches agreed internal/exported `logit1` value | Medium |
| `01110` | Unused | Internal | None | No | No | Zero | Reserved / no unexpected behavior | Low |
| `01111` | Reserved | Internal | None | No | No | Zero | Reserved / no unexpected behavior | Low |
| `10000` | Normal External Clock | External `bidir[39]` | Drive external clock | Maybe | Maybe | Debug bus disabled / zero | Same as normal mode, but advances only on external clock | High |
| `1xxxx` | External-Clock Mirror Modes | External `bidir[39]` | Same as matching `0xxxx` mode plus external clock | Depends | Depends | Same mapping as the corresponding `0xxxx` mode | Same function as internal-clock mode, but externally clocked | Medium |

## Current Regression Coverage

The first DFT smoke regression now exists in:

- `cocotb/chip_core_dft_tb.py`

Run it with:

```bash
make sim-dft-smoke
```

Currently covered modes:

- `00000`
  - checks that the debug bus is disabled / zero in normal mode
  - checks that the system settles into the expected idle/sleep posture in this
    no-stimulus environment:
    - `feat_en = 0`
    - `ml_en = 0`
    - `cpu_en = 0`
    - `sleeping = 1`
- `01010`
  - checks that the debug bus is enabled
  - checks that bit 15 reflects the forced IRQ input on `bidir[37]`
  - checks that the expected CPU-only mode posture is active:
    - `feat_en = 0`
    - `ml_en = 0`
    - `cpu_en = 1`
    - `sleeping = 0`
- `01011`
  - checks that the debug bus is enabled
  - checks that bit 15 reflects the forced wake input on `bidir[38]`
  - checks that the low 12 bits remain zero as expected for this summary mode
  - checks that the expected CPU-only mode posture is active:
    - `feat_en = 0`
    - `ml_en = 0`
    - `cpu_en = 1`
    - `sleeping = 0`

Current coverage note:

- this smoke regression runs on `chip_core` rather than full `chip_top`
- that was intentional for now, so DFT logic can be verified without depending
  on the external GF180 pad-model setup
- this still validates the real test-mode and debug-bus logic that `chip_top`
  uses

## Best First Tests

These are the best modes to bring up first:

1. `00000`
   - normal mode
   - confirm debug bus is disabled / zero
2. `01010`
   - forced IRQ view
   - easy to stimulate from the testbench
3. `01011`
   - forced wake view
   - easy to stimulate from the testbench
4. `10000`
   - normal external-clock mode
   - proves external test clock selection works
5. `00111` and `01000`
   - CPU state / MMIO write summaries
   - useful sanity checks once firmware is running

## Coordination Items

These are the main things to align on before locking down golden checks for every mode:

- exact sample point for each mode
- exact internal source signal for the debug-bus value
- whether the check is:
  - exact value
  - nonzero/activity-based
  - phase-based
- whether firmware must be running
- whether sensor models must be active

Most important rows to clarify:

- `00101` pipeline smoke summary
- `00110` ML update / invalid-reason summary
- `01100` logit0
- `01101` logit1
- all `1xxxx` external-clock expectations

## Suggested Future Columns

Once the mode plan is more mature, table can be extended with:

- `TB Name`
- `Golden Source`
- `Sample Trigger`
- `Status`
