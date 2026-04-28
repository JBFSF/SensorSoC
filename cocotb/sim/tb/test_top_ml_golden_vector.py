"""Cocotb unified-top golden-vector regression.

This test is the Python-side version of the unified-top golden check.  Unlike
the legacy self-checking SV bench, it imports ``golden_vectors.py`` so the
canonical vector, quantization expectations, packed logit word, class, and
confidence all come from one shared artifact.

What it checks
--------------
1. The golden metadata is self-consistent.
2. The unified top boots through the hardware boot SPI path.
3. The golden firmware writes the expected quantized feature vector into WRAM.
4. Firmware reaches PASS without trapping.
5. The final WRAM logit word matches the packed logits for ``canonical_v1``.
"""

import cocotb
from cocotb.triggers import ClockCycles, ReadOnly, RisingEdge

from golden_vectors import (
    absdiff_confidence,
    get_vector,
    pack_int16_pair,
    predicted_class_from_logits,
    unpack_int16_pair,
)
from top_unified_env import apply_reset, start_clock


TEST_PASS = 0xCAFEBABE
TEST_FAIL = 0xDEADBEEF
WEIGHT_BASE = 0x03006000
X_BASE_BYTES = 64
LOGIT_BASE_BYTES = 5504
X_WORD0_IDX = X_BASE_BYTES // 4
X_WORD1_IDX = X_WORD0_IDX + 1
LOGIT_WORD_IDX = LOGIT_BASE_BYTES // 4


def _u(handle) -> int:
    return int(handle.value)


@cocotb.test()
async def test_unified_top_canonical_v1(dut):
    """Check the unified-top golden-vector flow against canonical_v1."""
    vector = get_vector("canonical_v1")
    x_int = vector["x_int"]
    y_int = tuple(vector["y_int"])
    expected_word = vector["packed_logits_word"]

    # Self-consistency checks on the frozen artifact before touching hardware.
    assert len(x_int) == 4, "golden vector must contain four input features"
    assert tuple(y_int) == unpack_int16_pair(expected_word)
    assert predicted_class_from_logits(*y_int) == vector["predicted_class"]
    assert absdiff_confidence(*y_int) == vector["confidence_absdiff"]

    expected_x_word0 = pack_int16_pair(x_int[0], x_int[1])
    expected_x_word1 = pack_int16_pair(x_int[2], x_int[3])

    cocotb.start_soon(start_clock(dut))
    await apply_reset(dut)

    for _ in range(3_000_000):
        await RisingEdge(dut.clk)
        await ReadOnly()

        if _u(dut.pico_trap):
            raise AssertionError("CPU trap asserted during unified-top golden test")
        if _u(dut.test_status) == TEST_FAIL:
            raise AssertionError(f"firmware reported FAIL with code 0x{_u(dut.test_code):08x}")
        if _u(dut.test_status) == TEST_PASS:
            break
    else:
        raise AssertionError("timed out waiting for unified-top golden firmware to finish")

    await ClockCycles(dut.clk, 4)
    await ReadOnly()

    observed_x_word0 = _u(dut.u_dut.u_weight_ram.mem[X_WORD0_IDX])
    observed_x_word1 = _u(dut.u_dut.u_weight_ram.mem[X_WORD1_IDX])
    observed_logit_word = _u(dut.u_dut.u_weight_ram.mem[LOGIT_WORD_IDX])
    observed_logits = unpack_int16_pair(observed_logit_word)

    assert observed_x_word0 == expected_x_word0, (
        f"quantized input word0 mismatch: got 0x{observed_x_word0:08x}, "
        f"expected 0x{expected_x_word0:08x}"
    )
    assert observed_x_word1 == expected_x_word1, (
        f"quantized input word1 mismatch: got 0x{observed_x_word1:08x}, "
        f"expected 0x{expected_x_word1:08x}"
    )
    assert observed_logit_word == expected_word, (
        f"golden logits mismatch: got word 0x{observed_logit_word:08x} "
        f"({observed_logits}), expected 0x{expected_word:08x} ({y_int})"
    )
    assert predicted_class_from_logits(*observed_logits) == vector["predicted_class"]
    assert absdiff_confidence(*observed_logits) == vector["confidence_absdiff"]
