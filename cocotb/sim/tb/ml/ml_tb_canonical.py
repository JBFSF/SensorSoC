"""Tiny isolated taketwo_wrap golden-vector check.

This cocotb test drives the bare accelerator wrapper directly:

  - load the packed parameter image into AXI RAM
  - write canonical_v1 into the input buffer
  - start inference through AXI-Lite
  - compare the raw output elements against golden_vectors.py

It is intentionally much smaller than the dataset-looping ml_tb.py so we can
use it as the first branch point in debugging:

  - if this fails, inspect src/taketwo.v vs the generated writeverilog output
  - if this passes, debug unified-top memory/base-address integration instead
"""

import sys
import math
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, FallingEdge
from cocotbext.axi import AxiBus, AxiLiteBus, AxiLiteMaster, AxiRam


THIS_DIR = Path(__file__).resolve().parent
TB_DIR = THIS_DIR.parent
if str(TB_DIR) not in sys.path:
    sys.path.insert(0, str(TB_DIR))

from golden_vectors import get_vector, pack_int16_pair, unpack_int16_pair


def le32(b: bytes) -> int:
    return int.from_bytes(b, "little", signed=False)


def u32(x: int) -> bytes:
    return int(x & 0xFFFFFFFF).to_bytes(4, "little")


def pack_4x_i16(values: list[int]) -> bytes:
    return int(values[0] & 0xFFFF).to_bytes(2, "little") + \
           int(values[1] & 0xFFFF).to_bytes(2, "little") + \
           int(values[2] & 0xFFFF).to_bytes(2, "little") + \
           int(values[3] & 0xFFFF).to_bytes(2, "little")


def align_up(value: int, chunk: int) -> int:
    return int(math.ceil(value / chunk)) * chunk


async def reset_dut(dut, cycles: int = 10) -> None:
    cocotb.start_soon(Clock(dut.CLK, 40, unit="ns").start())
    await FallingEdge(dut.CLK)
    dut.RESETN.value = 0
    await ClockCycles(dut.CLK, cycles)
    await FallingEdge(dut.CLK)
    dut.RESETN.value = 1
    await ClockCycles(dut.CLK, 2)


@cocotb.test()
async def canonical_v1_matches_golden_artifact(dut):
    """Run one isolated taketwo_wrap inference for canonical_v1."""
    await reset_dut(dut)

    vector = get_vector("canonical_v1")
    expected_word = vector["packed_logits_word"]
    expected_logits = tuple(vector["y_int"])

    axil = AxiLiteMaster(
        AxiLiteBus.from_prefix(dut, "saxi"),
        dut.CLK,
        dut.RESETN,
        reset_active_level=False,
    )
    axi_ram = AxiRam(
        AxiBus.from_prefix(dut, "maxi"),
        dut.CLK,
        dut.RESETN,
        reset_active_level=False,
        size=1 << 20,
    )

    global_off = le32(await axil.read(0x80, 4))
    out_base = le32(await axil.read(0x88, 4))
    x_base = le32(await axil.read(0x8C, 4))
    var_base = le32(await axil.read(0x90, 4))

    out_addr = (global_off + out_base) & 0xFFFFFFFF
    x_addr = (global_off + x_base) & 0xFFFFFFFF
    var_addr = (global_off + var_base) & 0xFFFFFFFF

    # Mirror writeverilog.py's address derivation more closely:
    #   variable_addr = align(x_pl.addr + x_pl.memory_size, 64)
    #   check_addr    = align(variable_addr + param_bytes, 64)
    #   tmp_addr      = align(check_addr + top.memory_size, 64)
    # In the generated flow for this 4->2 network, x_addr is 0x40 and the
    # output occupies one 32-bit word (two int16 logits).
    x_mem_size = 8
    top_mem_size = 4

    # Use the NNGen-generated packed parameter image, not the smaller stale
    # copy that lives beside the old dataset-looping cocotb test.
    bin_path = THIS_DIR.parent.parent.parent.parent / "misc" / "ML" / "nngen_out" / "taketwo_params.bin"
    param_bytes = bin_path.read_bytes()
    variable_addr = align_up(x_addr + x_mem_size, 64)
    check_addr = align_up(variable_addr + len(param_bytes), 64)
    tmp_addr = align_up(check_addr + top_mem_size, 64)

    # Program the same global temporary-address register that the generated
    # NNGen testbench writes before asserting START.
    await axil.write(0x84, u32(tmp_addr))

    axi_ram.write(variable_addr, param_bytes)
    assert axi_ram.read(variable_addr, len(param_bytes)) == param_bytes

    x_bytes = pack_4x_i16(vector["x_int"])
    axi_ram.write(x_addr, x_bytes)
    assert axi_ram.read(x_addr, len(x_bytes)) == x_bytes

    await axil.write(0x10, u32(1))
    for _ in range(20000):
        busy = le32(await axil.read(0x14, 4))
        if busy == 0:
            break
        await ClockCycles(dut.CLK, 10)
    else:
        raise AssertionError("timed out waiting for isolated taketwo_wrap busy to clear")
    out_bytes = axi_ram.read(out_addr, 4)
    observed_word = le32(out_bytes)
    observed_logits = unpack_int16_pair(observed_word)

    # First compare element-wise 16-bit outputs, matching writeverilog.py's
    # generated testbench style more closely than a packed-word-only check.
    assert observed_logits == expected_logits, (
        f"isolated taketwo_wrap logits mismatch: got {observed_logits}, "
        f"expected {expected_logits} "
        f"(word 0x{observed_word:08x}, expected 0x{expected_word:08x})"
    )
    assert observed_word == pack_int16_pair(*expected_logits)
