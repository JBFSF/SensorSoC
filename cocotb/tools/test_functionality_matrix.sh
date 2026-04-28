#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"
TEST_TIMEOUT="${TEST_TIMEOUT:-300s}"

printf "\n=== Pre-flight: Python dependencies ===\n"
pip install -q --break-system-packages -r "${ROOT_DIR}/../requirements.txt"

printf "\n=== Pre-flight: RISC-V firmware build ===\n"
"${ROOT_DIR}/tools/build-all-firmware.sh"

declare -a CASES=(
  "test-irq-states|IRQ state machine: irq_test.c firmware on PicoRV32, claim/complete, re-arm"
  "test-top-mlp-features|MLP feature-extraction path: weight SRAM visibility, AXI traffic, and inference completion signalling"
  "test-top-unified-reset-init|Unified-top initialization: SPI boot, register reset state, and reset corner cases"
  "sim-top-feature-ml-cpu|Full top: sensor pipeline -> feature MMIO -> CPU-driven ML start -> AXI compute"
  "sim-top-feature-ml-cpu-spi-flash|Full top with SPI flash weight loading via spi_master_mmio"
  "sim-top-spi-init-unified|SPI boot-copy isolation: firmware -> spi_master_mmio -> weight_ram_axi"
  "sim-top-spi-weights|CPU-driven ML weight load from SPI flash: BOOT_WORDS=1 then weight fetch and verify"
  "sim-top-ml-control-unified|CPU-owned taketwo control: WRAM writes -> ML base-reg -> START/BUSY/IRQ"
  "sim-top-sleep-wake-unified|Timer sleep/wake cycle: firmware requests sleep -> timer wake -> firmware clears sticky state"
  "sim-irq|main.c firmware on soc_top: timer wake, ML IRQ wake, and full N-sample timer->ML loop"
  "test-ml-canonical-v1|Isolated taketwo_wrap golden-vector check: AXI-driven inference vs golden_vectors.py, no firmware or top RTL"
)

declare -a PASSED=()
declare -a FAILED=()

printf "\n=== SleepSoC Firmware Matrix ===\n"

for case in "${CASES[@]}"; do
  target="${case%%|*}"
  desc="${case#*|}"
  printf "\n[%s]\n  Functionality: %s\n" "$target" "$desc"
  if timeout "$TEST_TIMEOUT" make "$target"; then
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
