import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge

BASE = 0x0300_F000

async def reset(dut, cycles=5):
    dut.resetn.value = 0
    dut.mem_valid.value = 0
    dut.mem_addr.value = 0
    dut.mem_wdata.value = 0
    dut.mem_wstrb.value = 0

    for _ in range(cycles):
        await RisingEdge(dut.clk)

    dut.resetn.value = 1
    for _ in range(2):
        await RisingEdge(dut.clk)


async def mmio_cycle(dut, addr, wdata=0, wstrb=0):
    dut.mem_addr.value  = addr
    dut.mem_wdata.value = wdata
    dut.mem_wstrb.value = wstrb
    dut.mem_valid.value = 1

    # Cycle 1: present request
    await RisingEdge(dut.clk)

    # Cycle 2: peripheral responds (mem_ready asserted here)
    await RisingEdge(dut.clk)
    ready = int(dut.mem_ready.value)
    rdata = int(dut.mem_rdata.value)

    dut.mem_valid.value = 0
    dut.mem_wstrb.value = 0
    await RisingEdge(dut.clk)  # let ready drop back to 0 cleanly

    return ready, rdata


@cocotb.test()
async def test_test_mmio_regs(dut):
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())  # 50 MHz
    await reset(dut)

    dut._log.info(f"resetn={int(dut.resetn.value)} status_o={int(dut.status_o.value)} mem_ready={int(dut.mem_ready.value)}")


    # Reset state
    assert int(dut.status_o.value) == 0
    assert int(dut.code_o.value) == 0

    # Write/read STATUS
    ready, _ = await mmio_cycle(dut, BASE + 0x0, 0xCAFEBABE, 0xF)
    assert ready == 1
    ready, r = await mmio_cycle(dut, BASE + 0x0, 0, 0x0)
    assert ready == 1 and r == 0xCAFEBABE

    # Write/read CODE
    ready, _ = await mmio_cycle(dut, BASE + 0x4, 0x12345678, 0xF)
    assert ready == 1
    ready, r = await mmio_cycle(dut, BASE + 0x4, 0, 0x0)
    assert ready == 1 and r == 0x12345678

    # Unmapped offset: device still responds (ready=1) but returns 0 and ignores writes
    before_status = int(dut.status_o.value)
    before_code   = int(dut.code_o.value)

    ready, r = await mmio_cycle(dut, BASE + 0x80, 0xDEADBEEF, 0xF)
    assert ready == 1
    assert r == 0

    assert int(dut.status_o.value) == before_status
    assert int(dut.code_o.value) == before_code
