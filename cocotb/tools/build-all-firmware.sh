#!/usr/bin/env bash
# Build every firmware variant defined in cocotb/Makefile.
# Reports pass/fail per variant and prints a summary at the end.
#
# Usage: cocotb/tools/build-all-firmware.sh [--stop-on-fail]

set -uo pipefail

source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/_common.sh"

STOP_ON_FAIL=0
while [[ $# -gt 0 ]]; do
    case "$1" in
        --stop-on-fail) STOP_ON_FAIL=1; shift ;;
        *) echo "usage: $0 [--stop-on-fail]" >&2; exit 1 ;;
    esac
done

VARIANTS=(
    main
    prod_main
    test_sleepwake
    test_gpio
    test_sleepwake_periodic
    test_ml_weights
    test_ml_cpu_wake_i2c
    test_top_feature_ml_cpu
    test_top_feature_ml_cpu_spi_flash
    test_top_spi_init_unified
    test_top_ml_control_unified
    test_top_sleep_wake_unified
    test_top_ml_golden_vector_unified
    irq_test
    test_top_spi_boot_weights
)

"${TOOLS_DIR}/check-riscv-toolchain.sh"
echo

declare -a PASSED=()
declare -a FAILED=()

printf "=== Building %d firmware variants ===\n\n" "${#VARIANTS[@]}"

for variant in "${VARIANTS[@]}"; do
    printf "[%s]\n" "$variant"
    if run_make firmware-rebuild FW_VARIANT="$variant" 2>&1; then
        PASSED+=("$variant")
        printf "  -> PASS\n\n"
    else
        FAILED+=("$variant")
        printf "  -> FAIL\n\n"
        if [[ $STOP_ON_FAIL -eq 1 ]]; then
            echo "Stopping on first failure (--stop-on-fail)."
            break
        fi
    fi
done

printf "=== Summary ===\n"
printf "Passed: %d\n" "${#PASSED[@]}"
for v in "${PASSED[@]}"; do printf "  + %s\n" "$v"; done

printf "Failed: %d\n" "${#FAILED[@]}"
for v in "${FAILED[@]}"; do printf "  - %s\n" "$v"; done

if [[ ${#FAILED[@]} -gt 0 ]]; then
    exit 1
fi
