#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

printf "\n=== Pre-flight: Python dependencies ===\n"
pip install -q --break-system-packages -r "${ROOT_DIR}/../requirements.txt"

printf "\n=== Pre-flight: RISC-V firmware build ===\n"
"${ROOT_DIR}/tools/build-all-firmware.sh"

declare -a CASES=(
  "test-irq-states|IRQ state machine: irq_test.c firmware on PicoRV32, claim/complete, re-arm"
  "sim-ml-weight-load|CPU firmware writes weight SRAM, programs ML base address, starts inference, proves AXI compute traffic"
  "test-top-ml-golden-vector-unified|Full unified-top ML golden-vector regression: weights loaded via SPI, inference run, output checked against reference"
  "test-top-mlp-features|MLP feature-extraction path: weight SRAM visibility, AXI traffic, and inference completion signalling"
  "test-top-unified-reset-init|Unified-top initialization: SPI boot, register reset state, and reset corner cases"
  "test-top-unified-runtime|Unified-top runtime integration: host-I2C bridge, production sleep/wake loop, and forced-wake IRQ path"
)

declare -a PASSED=()
declare -a FAILED=()

printf "\n=== SleepSoC Firmware Matrix ===\n"

for case in "${CASES[@]}"; do
  target="${case%%|*}"
  desc="${case#*|}"
  printf "\n[%s]\n  Functionality: %s\n" "$target" "$desc"
  if make "$target"; then
    PASSED+=("$target")
    printf "  Result: PASS\n"
  else
    FAILED+=("$target")
    printf "  Result: FAIL\n"
  fi
done

printf "\n=== Matrix Summary ===\n"
printf "Passed: %d\n" "${#PASSED[@]}"
for target in "${PASSED[@]}"; do
  printf "  - %s\n" "$target"
done

printf "Failed: %d\n" "${#FAILED[@]}"
for target in "${FAILED[@]}"; do
  printf "  - %s\n" "$target"
done

if [[ ${#FAILED[@]} -ne 0 ]]; then
  exit 1
fi
