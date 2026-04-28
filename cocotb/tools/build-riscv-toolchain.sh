#!/usr/bin/env bash

set -euo pipefail

source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/_common.sh"

toolchain_src="${RISCV_TOOLCHAIN_SRC:-${REPO_ROOT}/third_party/riscv-gnu-toolchain}"
toolchain_prefix="${RISCV_TOOLCHAIN_PREFIX:-${REPO_ROOT}/third_party/riscv-toolchain}"
jobs="${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || printf '1')}"

if [[ ! -d "${toolchain_src}" ]]; then
    cat >&2 <<EOF
Missing RISC-V toolchain source tree:
  ${toolchain_src}

Add it as a submodule first, for example:
  git submodule add https://github.com/riscv-collab/riscv-gnu-toolchain.git third_party/riscv-gnu-toolchain
  git submodule update --init --recursive

Then rerun:
  $0
EOF
    exit 1
fi

if [[ -x "${toolchain_prefix}/bin/riscv-none-elf-gcc" ]]; then
    echo "RISC-V toolchain already exists at ${toolchain_prefix}"
    "${toolchain_prefix}/bin/riscv-none-elf-gcc" --version | sed -n '1p'
    exit 0
fi

echo "Building RISC-V bare-metal toolchain"
echo "  source: ${toolchain_src}"
echo "  prefix: ${toolchain_prefix}"
echo "  jobs:   ${jobs}"

mkdir -p "${toolchain_prefix}"
cd "${toolchain_src}"

./configure --prefix="${toolchain_prefix}" --with-arch=rv32imc --with-abi=ilp32
make -j"${jobs}" newlib

echo
echo "Toolchain built. Use it with:"
echo "  export RISCV_TOOLCHAIN_DIR=${toolchain_prefix}/bin"
