#!/usr/bin/env python3
"""
Convert a word-per-line hex file into a C header with a uint32_t array.

Usage:
  python3 tools/hex_to_c_header.py <in_hex> <out_header> <symbol_name>
"""

from __future__ import annotations

import pathlib
import sys


def parse_words(path: pathlib.Path) -> list[int]:
    words: list[int] = []
    for raw in path.read_text().splitlines():
        line = raw.strip()
        if not line:
            continue
        if line.startswith("//") or line.startswith("#"):
            continue
        words.append(int(line, 16) & 0xFFFFFFFF)
    return words


def emit_header(out_path: pathlib.Path, symbol: str, words: list[int]) -> None:
    guard = f"{symbol.upper()}_H_"
    lines: list[str] = []
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append("#include <stdint.h>")
    lines.append("")
    lines.append(f"#define {symbol.upper()}_WORDS {len(words)}u")
    lines.append(f"static const uint32_t {symbol}[{len(words)}] = {{")

    for i, word in enumerate(words):
        end = "," if i != len(words) - 1 else ""
        lines.append(f"    0x{word:08x}u{end}")

    lines.append("};")
    lines.append("")
    lines.append(f"#endif  // {guard}")
    lines.append("")
    out_path.write_text("\n".join(lines))


def main() -> int:
    if len(sys.argv) != 4:
        print(
            "Usage: python3 tools/hex_to_c_header.py <in_hex> <out_header> <symbol_name>",
            file=sys.stderr,
        )
        return 2

    in_hex = pathlib.Path(sys.argv[1])
    out_header = pathlib.Path(sys.argv[2])
    symbol = sys.argv[3]

    words = parse_words(in_hex)
    out_header.parent.mkdir(parents=True, exist_ok=True)
    emit_header(out_header, symbol, words)
    print(f"Wrote {out_header} with {len(words)} words")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
