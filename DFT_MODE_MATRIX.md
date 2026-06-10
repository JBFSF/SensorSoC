# DFT Mode Table

This document is a table for the chip debug / DFT test
mode scheme in `chip_core.sv`.

## Current Table

The enable posture comes from the current `top_fsm.v` test-mode overrides:

- `SLEEP`: `feat_en=0`, `ml_en=0`, `cpu_en=0`, `sleeping=1`
- `FEAT_ONLY`: `feat_en=1`, `ml_en=0`, `cpu_en=0`, `sleeping=0`
- `ALL`: `feat_en=1`, `ml_en=1`, `cpu_en=1`, `sleeping=0`
- `ML_ONLY`: `feat_en=0`, `ml_en=1`, `cpu_en=0`, `sleeping=0`
- `CPU_ONLY`: `feat_en=0`, `ml_en=0`, `cpu_en=1`, `sleeping=0`

| Mode | Name | Clock | Stimulus Needed | Firmware Needed | Sensor Models Needed | Enabled Components | `bidir[22:7]` | Pass Condition |
|---|---|---|---|---|---|---|---|---|
| `00000` | Normal | Internal | None | Yes | Maybe | Dynamic FSM path; after reset expect `SLEEP`, then wake-driven transitions into `FEAT_ONLY`, `ALL`, and `CPU_FEAT` | Debug bus disabled / zero | Debug bus inactive in normal mode |
| `00001` | MSSD Feature | Internal | Let feature pipeline run | Yes | Yes | `FEAT_ONLY`: feature on, ML off, CPU off, not sleeping | `mssd_feat[15:0]` | Matches internal feature signal at sample point |
| `00010` | Delta HR Feature | Internal | Let feature pipeline run | Yes | Yes | `FEAT_ONLY`: feature on, ML off, CPU off, not sleeping | `delta_hr_feat[15:0]` | Matches internal feature signal at sample point |
| `00011` | Time Feature | Internal | Let feature pipeline run | Yes | Maybe | `FEAT_ONLY`: feature on, ML off, CPU off, not sleeping | `time_feat[15:0]` | Matches internal feature signal at sample point |
| `00100` | Motion Feature | Internal | Let feature pipeline run | Yes | Yes | `FEAT_ONLY`: feature on, ML off, CPU off, not sleeping | `motion_feat[15:0]` | Matches internal feature signal at sample point | 
| `00101` | Pipeline Smoke Summary | Internal | Let system run | Yes | Yes | `ALL`: feature on, ML on, CPU on, not sleeping | Summary bits for feature presence, logits, gate, epoch, and alarm | Expected summary bits go active when pipeline is live |
| `00110` | ML Update / Invalid Reason | Internal | Run valid and invalid pipeline cases | Yes | Yes | `ML_ONLY`: feature off, ML on, CPU off, not sleeping | `{ml_update_gate, epoch_end, invalid_reason[7:0], 6'b0}` | Matches internal control/status signals |
| `00111` | Pico State Summary | Internal | Boot firmware | Yes | No | `CPU_ONLY`: feature off, ML off, CPU on, not sleeping | CPU trap/clock/mem summary | Reflects active CPU execution and no unexpected trap |
| `01000` | Pico MMIO Write Summary | Internal | Run firmware with MMIO writes | Yes | No | `CPU_ONLY`: feature off, ML off, CPU on, not sleeping | MMIO write summary | Shows expected address/data/write activity |
| `01001` | Pico Sleep / IRQ Summary | Internal | Drive controlled sleep, IRQ, wake, CPU-on, and trap phases | Minimal | No | Observer mode: does not override the live FSM | `{pico_trap, pico_sleeping, pico_cpu_clk_en, \|pico_irq, 12'b0}` | Matches expected sleep/awake/IRQ/CPU/trap phase |
| `01010` | Force IRQ View | Internal | Drive `bidir[37]` | Minimal | No | `CPU_ONLY`: feature off, ML off, CPU on, not sleeping | Forced IRQ summary | Forced IRQ bit and related fields respond correctly |
| `01011` | Force Wake View | Internal | Drive `bidir[38]` | Minimal | No | `CPU_ONLY`: feature off, ML off, CPU on, not sleeping | Forced wake / wake-source summary | Forced wake bit visible and wake summary coherent |
| `01100` | Logit0 View | Internal | Run ML once | Yes | Likely Yes | No current `top_fsm` override; needs clarification before locking expected enable posture | `logit0[15:0]` | Matches agreed internal/exported `logit0` value |
| `01101` | Logit1 View | Internal | Run ML once | Yes | Likely Yes | No current `top_fsm` override; needs clarification before locking expected enable posture | `logit1[15:0]` | Matches agreed internal/exported `logit1` value |
| `01110` | Unused | Internal | None | No | No | No current `top_fsm` override; treat as reserved until clarified | Zero | Reserved / no unexpected behavior |
| `01111` | Reserved | Internal | None | No | No | No current `top_fsm` override; treat as reserved until clarified | Zero | Reserved / no unexpected behavior |
| `10000` | Normal External Clock | External `bidir[39]` | Drive external clock | Maybe | Maybe | Same dynamic FSM path as `00000`, but externally clocked | Debug bus disabled / zero | Same as normal mode, but advances only on external clock |
| `1xxxx` | External-Clock Mirror Modes | External `bidir[39]` | Same as matching `0xxxx` mode plus external clock | Depends | Depends | Same enable posture as corresponding `0xxxx` mode, but externally clocked | Same mapping as the corresponding `0xxxx` mode | Same function as internal-clock mode, but externally clocked |

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
  - checks that the system settles into the expected idle/no-forcing posture in this
    no-stimulus environment:
    - `feat_en = 0`
    - `cpu_en = 0`
- `00001`
  - checks that the debug bus is enabled
  - uses the explicit debug-stim override path to drive a known MSSD value
  - checks that `bidir[22:7]` exactly matches the injected `mssd_feat[15:0]`
  - checks the expected `FEAT_ONLY` posture:
    - `feat_en = 1`
    - `ml_en = 0`
    - `cpu_en = 0`
    - `sleeping = 0`
- `00010`
  - checks that the debug bus is enabled
  - uses the explicit debug-stim override path to drive a known delta-HR value
  - checks that `bidir[22:7]` exactly matches the injected `delta_hr_feat[15:0]`
  - checks the expected `FEAT_ONLY` posture:
    - `feat_en = 1`
    - `ml_en = 0`
    - `cpu_en = 0`
    - `sleeping = 0`
- `00011`
  - checks that the debug bus is enabled
  - uses the explicit debug-stim override path to drive a known time-feature value
  - checks that `bidir[22:7]` exactly matches the injected `time_feat[15:0]`
  - checks the expected `FEAT_ONLY` posture:
    - `feat_en = 1`
    - `ml_en = 0`
    - `cpu_en = 0`
    - `sleeping = 0`
- `00100`
  - checks that the debug bus is enabled
  - uses the explicit debug-stim override path to drive a known motion-feature value
  - checks that `bidir[22:7]` exactly matches the injected `motion_feat[15:0]`
  - checks the expected `FEAT_ONLY` posture:
    - `feat_en = 1`
    - `ml_en = 0`
    - `cpu_en = 0`
    - `sleeping = 0`
- `00111`
  - checks that the debug bus is enabled
  - checks that the 16-bit Pico state summary matches the live internal packed view
    of:
    - `pico_trap`
    - `pico_cpu_clk_en`
    - `pico_mem_valid`
    - `pico_mem_instr`
    - `pico_mem_ready`
    - `pico_mem_wstrb`
    - `pico_mem_addr[6:0]`
  - checks the expected `CPU_ONLY` posture:
    - `feat_en = 0`
    - `ml_en = 0`
    - `cpu_en = 1`
    - `sleeping = 0`
  - also has a stronger firmware-stimulated smoke test:
    - preloads a tiny Pico program directly into SRAM
    - forces `boot_done` high in the cheap `chip_core` harness
    - checks that the summary bus stays bit-exact while the CPU performs:
      - instruction fetches
      - an SRAM load
      - an SRAM store
      - an MMIO store
    - checks that no unexpected Pico trap occurs during that execution window
- `01000`
  - checks that the debug bus is enabled
  - checks that the 16-bit Pico MMIO write summary matches the live internal packed view
    of:
    - `mem_valid && any_wstrb`
    - `pico_trap`
    - `any_wstrb`
    - `full_word_write`
    - `pico_mem_addr[7:0]`
    - `pico_mem_wdata[3:0]`
  - preloads a tiny Pico program into SRAM so the CPU performs a real MMIO store
    to `TIMER_CTRL`
  - checks that at least one real write-qualified cycle is observed
  - checks the expected `CPU_ONLY` posture:
    - `feat_en = 0`
    - `ml_en = 0`
    - `cpu_en = 1`
    - `sleeping = 0`
- `01001`
  - checks that the debug bus is enabled
  - checks that the 16-bit Pico sleep / IRQ summary matches the live internal packed view
    of:
    - `pico_trap`
    - `pico_sleeping`
    - `pico_cpu_clk_en`
    - `|pico_irq`
    - hard-zero low 12 bits
  - proves `01001` is an observer mode rather than a CPU-only override by driving
    the real FSM into sleep and observing `sleeping = 1`, `cpu_en = 0`
  - toggles the DFT forced-IRQ pad and checks the IRQ summary bit
  - toggles the DFT forced-wake pad and checks the sleeping bit clears
  - enters a neighboring CPU-only DFT mode, returns to `01001`, and checks
    `cpu_clk_en = 1`
  - briefly forces the trap source in the chip-core harness to verify bit 15
- `01010`
  - checks that the debug bus is enabled
  - checks that the full 16-bit packed summary matches the live internal view
    of:
    - `test_force_irq`
    - `pico_trap`
    - `pico_cpu_clk_en`
    - `pico_mem_instr`
    - `pico_mem_valid`
    - `pico_mem_ready`
    - `pico_mem_addr[9:0]`
  - toggles `bidir[37]` and checks both the debug summary bit and the routed
    Pico IRQ bit
  - preloads a tiny SRAM Pico program and checks that the summary exposes real:
    - instruction fetch
    - `mem_valid`
    - `mem_ready`
    - SRAM data access address bits
    - MMIO store address bits
  - checks that the expected CPU-only mode posture is active:
    - `feat_en = 0`
    - `ml_en = 0`
    - `cpu_en = 1`
    - `sleeping = 0`
- `01011`
  - checks that the debug bus is enabled
  - checks that the full 16-bit packed summary matches the live internal view
    of:
    - `test_force_wake`
    - `host_i2c_irq_event`
    - `ml_irq`
    - `timer_event`
    - hard-zero low 12 bits
  - checks that bit 15 reflects the forced wake input on `bidir[38]`
  - forces the internal ML IRQ and timer-event sources to prove bits 13 and 12
  - intentionally does not add host-I2C IRQ stimulus because that path is
    transitional and planned for removal
  - checks that the host-I2C bit stays low in the unstimulated harness
  - checks that the low 12 bits remain zero as expected for this summary mode
  - checks that the expected CPU-only mode posture is active:
    - `feat_en = 0`
    - `ml_en = 0`
    - `cpu_en = 1`
    - `sleeping = 0`
