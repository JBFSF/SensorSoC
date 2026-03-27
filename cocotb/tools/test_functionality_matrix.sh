#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

declare -a CASES=(
  "test-cpu-ml|Strict ML IRQ contract: completion edge, latched status, clear, and rearm (including tight-gap restart)"
  "sim-ml-weight-load|CPU writes weight SRAM, programs ML base address, starts inference, and proves AXI compute traffic"
  "sim-ml-cpu-wake-i2c|End-to-end SoC path: timer wake, ML IRQ wake, host-I2C wake event, and wake policy boundary checks"
  "test-host-i2c-bridge|Host-I2C bridge register contract, threshold event behavior, and IRQC proxy interactions"
  "test-irq-ctrl-races|IRQ controller simultaneous-source, masking/reassert, claim/complete, and sideband access races"
)

declare -a PASSED=()
declare -a FAILED=()

printf "\n=== SleepSoC Functionality Matrix ===\n"

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
