import struct
import logging

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ClockCycles
from cocotbext.axi import AxiLiteBus, AxiLiteMaster, AxiBus, AxiRam


# Single-vector ML reference probe.
#
# Purpose:
#   - keep the original dataset-looping ml_tb.py intact
#   - run exactly one inference on one canonical vector
#   - align the input scaling with misc/ML/writeverilog.py
#   - print one deterministic output pair that can be frozen into a
#     unified-top numerical-correctness regression later
#
# Flow:
#   1. reset taketwo_wrap
#   2. read the ML address registers (global/input/output/param base)
#   3. load taketwo_params.bin into the AXI RAM model at var_addr
#   4. write one fixed int16 feature vector at x_addr
#   5. assert START over AXI-Lite and poll BUSY until inference completes
#   6. read the output word from out_addr and print logit0/logit1
#
# This is Stage A of the golden-vector flow:
#   "What logits should the raw accelerator produce for the canonical vector?"

SCALE = 512
INPUT_FLOAT = [0.5, -0.25, 0.1, -1.0]
INPUT_INT = [256, -128, 51, -512]


def le32(b: bytes) -> int:
    return int.from_bytes(b, "little", signed=False)


def u32(x: int) -> bytes:
    return int(x & 0xFFFFFFFF).to_bytes(4, "little")


def pack_i16_4(x: list[int]) -> bytes:
    return struct.pack("<4h", *x)


async def reset_dut(dut, cycles=10):
    cocotb.start_soon(Clock(dut.CLK, 40, unit="ns").start())
    await FallingEdge(dut.CLK)
    dut.RESETN.value = 0
    await ClockCycles(dut.CLK, cycles)
    await FallingEdge(dut.CLK)
    dut.RESETN.value = 1
    await ClockCycles(dut.CLK, 2)


@cocotb.test()
async def infer_single_reference_vector(dut):
    await reset_dut(dut)
    clk_i = dut.CLK

    logging.getLogger("cocotbext.axi").setLevel(logging.WARNING)

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

    # taketwo exposes relative addresses through AXI-Lite control registers.
    # We read them rather than hardcoding offsets so this probe stays aligned
    # with the generated hardware contract.
    global_off = le32(await axil.read(0x80, 4))
    out_base = le32(await axil.read(0x88, 4))
    x_base = le32(await axil.read(0x8C, 4))
    var_base = le32(await axil.read(0x90, 4))

    out_addr = (global_off + out_base) & 0xFFFFFFFF
    x_addr = (global_off + x_base) & 0xFFFFFFFF
    var_addr = (global_off + var_base) & 0xFFFFFFFF

    dut._log.info(
        "single-vector addresses: global=0x%08X x=0x%08X out=0x%08X var=0x%08X",
        global_off, x_addr, out_addr, var_addr
    )

    # This probe talks directly to the bare accelerator, so the packed
    # parameter blob is written straight into the AXI RAM model instead of
    # going through the unified-top SPI boot path.
    with open("taketwo_params.bin", "rb") as f:
        param_bytes = f.read()

    axi_ram.write(var_addr, param_bytes)
    rb = axi_ram.read(var_addr, len(param_bytes))
    assert rb == param_bytes, "parameter blob mismatch after AXI RAM write"

    # Write the canonical int16 input vector in the same order the accelerator
    # expects it in memory.
    axi_ram.write(x_addr, pack_i16_4(INPUT_INT))

    await axil.write(0x10, u32(1))
    while True:
        busy = le32(await axil.read(0x14, 4))
        if busy == 0:
            break
        await ClockCycles(clk_i, 10)
    await axil.write(0x10, u32(0))

    out_bytes = axi_ram.read(out_addr, 4)
    log0, log1 = struct.unpack("<2h", out_bytes)

    # Keep the output format intentionally simple so it can be copied directly
    # into a frozen golden-vector regression without extra parsing.
    print("GOLDEN_VECTOR_INPUT_FLOAT", INPUT_FLOAT)
    print("GOLDEN_VECTOR_INPUT_INT", INPUT_INT)
    print(f"GOLDEN_VECTOR_LOGITS logit0={log0} logit1={log1}")
