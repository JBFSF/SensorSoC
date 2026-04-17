#!/usr/bin/env bash

set -euo pipefail

TOOLS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${TOOLS_DIR}/../.." && pwd)"
COCOTB_DIR="${REPO_ROOT}/cocotb"
LOCAL_RISCV_BIN="${REPO_ROOT}/../riscv-toolchain/bin"

detect_riscv_prefix() {
    local candidate
    for candidate in \
        "${LOCAL_RISCV_BIN}/riscv-none-elf-" \
        "${LOCAL_RISCV_BIN}/riscv64-unknown-elf-" \
        "riscv-none-elf-" \
        "riscv64-unknown-elf-"
    do
        if command -v "${candidate}gcc" >/dev/null 2>&1; then
            printf '%s\n' "${candidate}"
            return 0
        fi
    done

    return 1
}

default_riscv_prefix() {
    if detect_riscv_prefix; then
        return 0
    fi

    printf '%s\n' "riscv-none-elf-"
}

resolve_riscv_prefix() {
    if [[ -n "${RISCV_PREFIX:-}" ]]; then
        printf '%s\n' "${RISCV_PREFIX}"
    elif [[ -n "${RISCV_TOOLCHAIN_DIR:-}" ]]; then
        if [[ -x "${RISCV_TOOLCHAIN_DIR%/}/riscv-none-elf-gcc" ]]; then
            printf '%s\n' "${RISCV_TOOLCHAIN_DIR%/}/riscv-none-elf-"
        elif [[ -x "${RISCV_TOOLCHAIN_DIR%/}/riscv64-unknown-elf-gcc" ]]; then
            printf '%s\n' "${RISCV_TOOLCHAIN_DIR%/}/riscv64-unknown-elf-"
        else
            printf '%s\n' "${RISCV_TOOLCHAIN_DIR%/}/riscv-none-elf-"
        fi
    else
        default_riscv_prefix
    fi
}

run_make() {
    local prefix
    prefix="$(resolve_riscv_prefix)"
    make -C "${COCOTB_DIR}" RISCV_PREFIX="${prefix}" "$@"
}
