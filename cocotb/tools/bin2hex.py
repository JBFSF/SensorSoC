import pathlib
import struct
import sys

bin_path = sys.argv[1]
hex_path = sys.argv[2]

data = pathlib.Path(bin_path).read_bytes()

# pad to multiple of 4 bytes
data += b"\x00" * ((4 - len(data) % 4) % 4)

out_lines = []
for i in range(0, len(data), 4):
    word = struct.unpack_from("<I", data, i)[0]
    out_lines.append(f"{word:08x}")

pathlib.Path(hex_path).write_text("\n".join(out_lines) + "\n")

print(f"Wrote {hex_path} with {len(out_lines)} 32-bit words")
