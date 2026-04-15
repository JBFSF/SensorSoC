from __future__ import annotations


def mask(width: int) -> int:
    return (1 << width) - 1


def to_unsigned(value: int, width: int) -> int:
    return value & mask(width)


def to_signed(value: int, width: int) -> int:
    value &= mask(width)
    sign_bit = 1 << (width - 1)
    return value - (1 << width) if value & sign_bit else value


def abs_signed(value: int, width: int) -> int:
    signed = to_signed(value, width)
    if signed < 0:
        return to_unsigned(-signed, width)
    return to_unsigned(signed, width)


def bool_bit(value: bool | int) -> int:
    return 1 if value else 0
