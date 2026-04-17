#!/usr/bin/env bash

set -euo pipefail

source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/_common.sh"

variant="${1:-}"

if [[ -z "${variant}" ]]; then
    echo "usage: $0 <firmware-variant>" >&2
    exit 1
fi

"${TOOLS_DIR}/check-riscv-toolchain.sh"
run_make FW_VARIANT="${variant}" firmware-rebuild
