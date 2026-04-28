"""Frozen golden-vector artifacts for ML correctness tests.

This module is the Python-side source of truth for golden vectors used by
unified-top ML regressions.  The intent is to keep three layers explicit:

1. Model semantics from ``taketwo.py`` via the float-domain input vector.
2. Quantization expectations for the hardware-facing int16 feature vector.
3. Implementation-aligned logits from ``writeverilog.py``.

The current canonical case is ``canonical_v1``:
    x_float = [0.5, -0.25, 0.1, -1.0]
    x_int   = [256, -128, 51, -512]
    y_int   = [-823, 1031]

The helper functions below intentionally keep packing/class/confidence logic in
one place so future cocotb tests can import the artifact instead of retyping
these assumptions in multiple benches.
"""

from __future__ import annotations


def to_u16(value: int) -> int:
    """Return the low 16 bits of a signed or unsigned integer."""
    return value & 0xFFFF


def pack_int16_pair(logit0: int, logit1: int) -> int:
    """Pack two signed int16 logits into the WRAM output-word format."""
    return (to_u16(logit1) << 16) | to_u16(logit0)


def unpack_int16_pair(word: int) -> tuple[int, int]:
    """Unpack the WRAM output word into signed int16 logits."""
    logit0 = word & 0xFFFF
    logit1 = (word >> 16) & 0xFFFF
    if logit0 & 0x8000:
        logit0 -= 0x10000
    if logit1 & 0x8000:
        logit1 -= 0x10000
    return logit0, logit1


def predicted_class_from_logits(logit0: int, logit1: int) -> int:
    """Mirror the current firmware policy: class 1 wins when logit1 > logit0."""
    return 1 if logit1 > logit0 else 0


def absdiff_confidence(logit0: int, logit1: int) -> int:
    """Mirror the current firmware confidence heuristic."""
    return abs(int(logit0) - int(logit1))


GOLDEN_VECTORS = [
    {
        "name": "canonical_v1",
        "source_model": "taketwo.py",
        "source_impl": "writeverilog.py",
        "feature_order": ["motion", "time", "delta_hr", "rmssd"],
        "x_float": [0.5, -0.25, 0.1, -1.0],
        "x_int": [256, -128, 51, -512],
        "x_base_bytes": 64,
        "var_base_bytes": 128,
        "logit_base_bytes": 5504,
        "y_int": [-823, 1031],
        "packed_logits_word": pack_int16_pair(-823, 1031),
        "predicted_class": predicted_class_from_logits(-823, 1031),
        "confidence_absdiff": absdiff_confidence(-823, 1031),
        "quantization": {
            "x_scale": 512,
            "input_dtype": "int16",
            "logit_dtype": "int16",
            "packing": "logit0 in bits[15:0], logit1 in bits[31:16]",
        },
        "notes": (
            "First frozen vector for unified-top ML correctness. "
            "Float-domain semantics come from taketwo.py; integer logits are "
            "aligned to writeverilog.py."
        ),
    },
]


def get_vector(name: str) -> dict:
    """Return a golden vector by stable name."""
    for vector in GOLDEN_VECTORS:
        if vector["name"] == name:
            return vector
    raise KeyError(f"unknown golden vector: {name}")


# Example usage for future Python/cocotb unified-top checks:
#
#     from golden_vectors import get_vector, unpack_int16_pair
#
#     v = get_vector("canonical_v1")
#     expected_x = v["x_int"]
#     expected_word = v["packed_logits_word"]
#     expected_y = tuple(v["y_int"])
#
#     assert observed_inputs == tuple(expected_x)
#     assert observed_word == expected_word
#     assert unpack_int16_pair(observed_word) == expected_y
#     assert abs(expected_y[0] - expected_y[1]) == v["confidence_absdiff"]
