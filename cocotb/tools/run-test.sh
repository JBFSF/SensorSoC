#!/usr/bin/env bash

set -euo pipefail

source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/_common.sh"

target="${1:-}"

if [[ -z "${target}" ]]; then
    echo "usage: $0 <make-target> [extra make args...]" >&2
    exit 1
fi

"${TOOLS_DIR}/check-riscv-toolchain.sh"
run_make "${target}" "${@:2}"
