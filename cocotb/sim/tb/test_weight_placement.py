import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge
from cocotbext.axi import AxiBus, AxiMaster

# Memory map constants
BASE_ADDR = 0x0300_6000
X_BASE    = BASE_ADDR + 64     # word index 16: 4x int16 feature inputs
VAR_BASE  = BASE_ADDR + 128    # word index 32: weights from taketwo_params.hex
OUT_BASE  = BASE_ADDR + 5504   # word index 1376: logit outputs

EXPECTED_FIRST_WEIGHT = 0x1637fe23  # word 32 in taketwo_params.hex


async def reset_dut(dut, cycles=5):
    dut.resetn.value    = 0
    dut.mem_valid.value = 0
    dut.mem_addr.value  = 0
    dut.mem_wdata.value = 0
    dut.mem_wstrb.value = 0
    for _ in range(cycles):
        await RisingEdge(dut.clk)
    dut.resetn.value = 1
    for _ in range(2):
        await RisingEdge(dut.clk)


TIMEOUT_CYCLES = 200


async def cpu_write(dut, addr, data):
    """32-bit MMIO write. Polls mem_ready after each rising edge (Icarus NBA timing)."""
    dut.mem_addr.value  = addr
    dut.mem_wdata.value = data
    dut.mem_wstrb.value = 0xF
    dut.mem_valid.value = 1
    for _ in range(TIMEOUT_CYCLES):
        await RisingEdge(dut.clk)
        if int(dut.mem_ready.value) == 1:
            break
    else:
        raise TimeoutError(f"cpu_write timeout at addr 0x{addr:08x}")
    dut.mem_valid.value = 0
    dut.mem_wstrb.value = 0
    await RisingEdge(dut.clk)


async def cpu_read(dut, addr):
    """32-bit MMIO read. Polls mem_ready after each rising edge (Icarus NBA timing)."""
    dut.mem_addr.value  = addr
    dut.mem_wstrb.value = 0
    dut.mem_wdata.value = 0
    dut.mem_valid.value = 1
    rdata = None
    for _ in range(TIMEOUT_CYCLES):
        await RisingEdge(dut.clk)
        if int(dut.mem_ready.value) == 1:
            rdata = int(dut.mem_rdata.value)
            break
    else:
        raise TimeoutError(f"cpu_read timeout at addr 0x{addr:08x}")
    dut.mem_valid.value = 0
    await RisingEdge(dut.clk)
    return rdata


@cocotb.test()
async def test_cpu_write_readback(dut):
    """CPU MMIO write to x_base is readable back via CPU MMIO."""
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    await reset_dut(dut)

    test_val = 0xDEADBEEF
    await cpu_write(dut, X_BASE, test_val)
    got = await cpu_read(dut, X_BASE)
    assert got == test_val, \
        f"test_cpu_write_readback: expected 0x{test_val:08x}, got 0x{got:08x}"
    dut._log.info(f"PASS: readback = 0x{got:08x}")


@cocotb.test()
async def test_weight_preload(dut):
    """Hex-initialized weights at var_base match taketwo_params.hex (first word)."""
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    await reset_dut(dut)

    got = await cpu_read(dut, VAR_BASE)
    assert got == EXPECTED_FIRST_WEIGHT, \
        f"test_weight_preload: expected 0x{EXPECTED_FIRST_WEIGHT:08x}, got 0x{got:08x}"
    dut._log.info(f"PASS: first weight = 0x{got:08x}")


@cocotb.test()
async def test_cpu_write_axi_read(dut):
    """CPU write to x_base is readable via AXI4 (path taketwo uses)."""
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    await reset_dut(dut)

    axi = AxiMaster(
        AxiBus.from_prefix(dut, "saxi"),
        dut.clk,
        dut.resetn,
        reset_active_level=False,
    )

    test_val = 0x12345678
    await cpu_write(dut, X_BASE, test_val)

    rd = await axi.read(X_BASE, 4)
    got = int.from_bytes(rd.data, "little")
    assert got == test_val, \
        f"test_cpu_write_axi_read: expected 0x{test_val:08x}, got 0x{got:08x}"
    dut._log.info(f"PASS: AXI read = 0x{got:08x}")


@cocotb.test()
async def test_axi_write_cpu_read(dut):
    """AXI4 write to out_base is readable via CPU MMIO (firmware reads logits)."""
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())
    await reset_dut(dut)

    axi = AxiMaster(
        AxiBus.from_prefix(dut, "saxi"),
        dut.clk,
        dut.resetn,
        reset_active_level=False,
    )

    test_val = 0xABCD1234
    await axi.write(OUT_BASE, test_val.to_bytes(4, "little"))

    got = await cpu_read(dut, OUT_BASE)
    assert got == test_val, \
        f"test_axi_write_cpu_read: expected 0x{test_val:08x}, got 0x{got:08x}"
    dut._log.info(f"PASS: CPU read after AXI write = 0x{got:08x}")
