import struct, pathlib

REPO  = pathlib.Path(__file__).resolve().parent.parent
BIN   = REPO / "ML/nngen_out/taketwo_params.bin"
HEX   = REPO / "sleep_soc/rtl/taketwo_params.hex"
WORDS = 4096
OFFSET_WORDS = 32          # var_base = 128 bytes = 32 words

data = BIN.read_bytes()
assert len(data) % 4 == 0, f"Binary size {len(data)} not divisible by 4"
weight_words = [struct.unpack_from("<I", data, i)[0] for i in range(0, len(data), 4)]

mem = [0] * WORDS
for i, w in enumerate(weight_words):
    mem[OFFSET_WORDS + i] = w

HEX.write_text("\n".join(f"{w:08x}" for w in mem) + "\n")
print(f"Wrote {WORDS} words to {HEX}")
print(f"Weight words: {len(weight_words)}, placed at words {OFFSET_WORDS}–{OFFSET_WORDS + len(weight_words) - 1}")
print(f"Word 32 (first weight): 0x{mem[32]:08x}")
