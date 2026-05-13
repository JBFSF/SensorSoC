#!/usr/bin/env python3
"""
Combine a firmware .hex and a weight .hex into a single flash image.
Usage: combine_flash_hex.py <fw.hex> <weights.hex> <fw_word_count> <output.hex>

The firmware section is zero-padded to exactly fw_word_count words.
The weight section follows immediately after.
"""
import sys

if len(sys.argv) != 5:
    print(f"Usage: {sys.argv[0]} <fw.hex> <weights.hex> <fw_word_count> <output.hex>",
          file=sys.stderr)
    sys.exit(1)

fw_hex, weight_hex, fw_words_str, out_hex = sys.argv[1:]
fw_words = int(fw_words_str)

with open(fw_hex) as f:
    fw_lines = [l.strip() for l in f if l.strip()]
with open(weight_hex) as f:
    wt_lines = [l.strip() for l in f if l.strip()]

fw_lines = fw_lines[:fw_words]
fw_lines += ['00000000'] * (fw_words - len(fw_lines))

with open(out_hex, 'w') as f:
    for line in fw_lines + wt_lines:
        f.write(line + '\n')
