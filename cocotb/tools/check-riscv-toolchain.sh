#!/usr/bin/env bash

set -euo pipefail

source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/_common.sh"

prefix="$(resolve_riscv_prefix)"
gcc_bin="${prefix}gcc"
objcopy_bin="${prefix}objcopy"

echo "Using RISCV_PREFIX=${prefix}"

if ! command -v "${gcc_bin}" >/dev/null 2>&1; then
    echo "Missing compiler: ${gcc_bin}" >&2
    exit 1
fi

if ! command -v "${objcopy_bin}" >/dev/null 2>&1; then
    echo "Missing objcopy: ${objcopy_bin}" >&2
    exit 1
fi

"${gcc_bin}" --version | sed -n '1p'
"${objcopy_bin}" --version | sed -n '1p'
