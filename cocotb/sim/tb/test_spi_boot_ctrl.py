import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge

# Must match sim_spi_boot_ctrl WORDS parameter and boot_test_pattern.hex
WORDS = 16
EXPECTED = [
    0xDEADBEEF,
    0xCAFEBABE,
    0x12345678,
    0x9ABCDEF0,
    0x01234567,
    0x89ABCDEF,
    0xFEEDFACE,
    0xD00DFEED,
    0xAABBCCDD,
    0xEEFF0011,
    0x22334455,
    0x66778899,
    0xBADCAFE0,
    0x11223344,
    0x55667788,
    0x99AABBCC,
]

@cocotb.test()
async def test_boot_loads_sram(dut):
    """spi_boot_ctrl must copy flash contents into SRAM before asserting boot_done."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    dut.resetn.value = 0
    for _ in range(5):
        await RisingEdge(dut.clk)
    dut.resetn.value = 1

    # Wait for boot_done with a generous timeout.
    # Expected cycles: 2 (idle+cs) + 8*2*CLK_DIV (cmd) + 24*2*CLK_DIV (addr)
    #                  + WORDS * (4 * 8 * 2 * CLK_DIV + 3) (data+assemble+write)
    # For WORDS=16, CLK_DIV=2: ~2 + 32 + 96 + 16*(128+3) = ~2226 cycles + margin
    timeout_cycles = 10_000
    cycles = 0
    while not dut.boot_done.value and cycles < timeout_cycles:
        await RisingEdge(dut.clk)
        cycles += 1

    assert dut.boot_done.value == 1, (
        f"boot_done never asserted (timeout after {timeout_cycles} cycles)"
    )
    dut._log.info(f"boot_done asserted after {cycles} cycles")

    # Allow one extra cycle for the last SRAM write to commit.
    await RisingEdge(dut.clk)

    # Compare SRAM contents against expected flash values word-by-word.
    errors = 0
    for i in range(WORDS):
        sram_word = int(dut.u_sram.mem[i].value)
        expected  = EXPECTED[i]
        if sram_word != expected:
            dut._log.error(
                f"MISMATCH word[{i:2d}]: SRAM=0x{sram_word:08x}  expected=0x{expected:08x}"
            )
            errors += 1
        else:
            dut._log.info(f"OK word[{i:2d}]: 0x{sram_word:08x}")

    assert errors == 0, f"{errors}/{WORDS} word mismatches after boot"
    dut._log.info(f"PASS: all {WORDS} words loaded correctly from flash into SRAM")
