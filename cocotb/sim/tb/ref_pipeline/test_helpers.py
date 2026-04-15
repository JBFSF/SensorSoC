from __future__ import annotations

from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, ReadOnly, RisingEdge


async def start_clock(dut, period_ns: int = 10) -> None:
    cocotb_clock = Clock(dut.clk, period_ns, unit="ns")
    cocotb_clock.start()


async def apply_reset(dut, reset_name: str = "rst_i", cycles: int = 5) -> None:
    reset = getattr(dut, reset_name)
    reset.value = 1
    await ClockCycles(dut.clk, cycles)
    reset.value = 0
    await RisingEdge(dut.clk)
    await ReadOnly()


def sig_u(signal) -> int:
    return signal.value.to_unsigned()


def sig_s(signal) -> int:
    return signal.value.to_signed()
