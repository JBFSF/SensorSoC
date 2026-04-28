#!/usr/bin/env bash

set -euo pipefail

source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/_common.sh"

run_tests=1
init_submodules=1
regression_timeout="${REGRESSION_TIMEOUT:-300s}"

usage() {
    cat >&2 <<EOF
usage: $0 [--build-only] [--skip-submodules]

Reproducible firmware smoke flow:
  1. initialize git submodules
  2. check the RISC-V toolchain selected by _common.sh
  3. rebuild the two integration firmwares:
       - irq_test
       - prod_main
  4. optionally run the matching smoke regressions plus DFT smoke
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --build-only)
            run_tests=0
            shift
            ;;
        --skip-submodules)
            init_submodules=0
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            usage
            exit 1
            ;;
    esac
done

cd "${REPO_ROOT}"

if [[ "${init_submodules}" -eq 1 ]]; then
    echo "=== Submodules ==="
    git submodule update --init --recursive
    echo
fi

echo "=== Toolchain ==="
"${TOOLS_DIR}/check-riscv-toolchain.sh"
echo

echo "=== Firmware ==="
"${TOOLS_DIR}/build-firmware.sh" irq_test
"${TOOLS_DIR}/build-firmware.sh" prod_main
echo

if [[ "${run_tests}" -eq 0 ]]; then
    echo "Build-only flow complete."
    exit 0
fi

echo "=== Regressions ==="
timeout "${regression_timeout}" make sim-dft-smoke
timeout "${regression_timeout}" bash -c \
    "source '${TOOLS_DIR}/_common.sh'; run_make test-irq-states"
timeout "${regression_timeout}" bash -c \
    "source '${TOOLS_DIR}/_common.sh'; run_make sim-top-feature-ml-prod-main-host-i2c"

echo
echo "Reproducible firmware flow passed."
