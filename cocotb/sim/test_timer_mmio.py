import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge

BASE = 0x0300_2000
OFF_CTRL   = 0x0
OFF_RELOAD = 0x4
OFF_COUNT  = 0x8
OFF_EVENT  = 0xC

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

async def mmio_write(dut, addr, data):
    dut.mem_addr.value  = addr
    dut.mem_wdata.value = data
    dut.mem_wstrb.value = 0xF
    dut.mem_valid.value = 1

    await RisingEdge(dut.clk)  # request
    await RisingEdge(dut.clk)  # response

    ready = int(dut.mem_ready.value)

    dut.mem_valid.value = 0
    dut.mem_wstrb.value = 0
    await RisingEdge(dut.clk)

    assert ready == 1, f"write: expected ready=1 at 0x{addr:08x}"

async def mmio_read(dut, addr):
    # Use rdata_o because mem_rdata in your RTL can lag by 1 cycle (due to mem_rdata <= rdata_o)
    dut.mem_addr.value  = addr
    dut.mem_wdata.value = 0
    dut.mem_wstrb.value = 0
    dut.mem_valid.value = 1

    await RisingEdge(dut.clk)  # request
    await RisingEdge(dut.clk)  # response

    ready = int(dut.mem_ready.value)
    rdata = int(dut.rdata_o.value)

    dut.mem_valid.value = 0
    await RisingEdge(dut.clk)

    assert ready == 1, f"read: expected ready=1 at 0x{addr:08x}"
    return rdata

@cocotb.test()
async def test_timer_mmio_basic(dut):
    cocotb.start_soon(Clock(dut.clk, 20, unit="ns").start())  # 50 MHz
    await reset(dut)

    # Reset defaults
    ctrl = await mmio_read(dut, BASE + OFF_CTRL)
    assert (ctrl & 0x1) == 0, "enable should reset to 0"
    assert ((ctrl >> 1) & 0x1) == 1, "periodic should reset to 1"
    assert int(dut.event_o.value) == 0, "event should reset low"

    # One-shot: periodic=0, enable=1
    await mmio_write(dut, BASE + OFF_RELOAD, 3)
    await mmio_write(dut, BASE + OFF_COUNT,  3)
    await mmio_write(dut, BASE + OFF_CTRL,   0b01)  # enable=1, periodic=0

    # Wait for event (should happen quickly)
    for _ in range(20):
        await RisingEdge(dut.clk)
        if int(dut.event_o.value) == 1:
            break
    assert int(dut.event_o.value) == 1, "event did not assert in one-shot mode"

    # One-shot should auto-disable
    ctrl = await mmio_read(dut, BASE + OFF_CTRL)
    assert (ctrl & 0x1) == 0, "enable should auto-clear in one-shot mode"

    # W1C clear event
    await mmio_write(dut, BASE + OFF_EVENT, 1)
    assert int(dut.event_o.value) == 0, "event should clear after W1C"

    # Periodic mode
    await mmio_write(dut, BASE + OFF_RELOAD, 4)
    await mmio_write(dut, BASE + OFF_COUNT,  2)
    await mmio_write(dut, BASE + OFF_CTRL,   0b11)  # enable=1, periodic=1

    for _ in range(20):
        await RisingEdge(dut.clk)
        if int(dut.event_o.value) == 1:
            break
    assert int(dut.event_o.value) == 1, "event did not assert in periodic mode"

    # Should stay enabled in periodic mode
    ctrl = await mmio_read(dut, BASE + OFF_CTRL)
    assert (ctrl & 0x1) == 1, "enable should remain 1 in periodic mode"

    # Writing 0 should NOT clear W1C
    await mmio_write(dut, BASE + OFF_EVENT, 0)
    assert int(dut.event_o.value) == 1, "event unexpectedly cleared by writing 0"

    # Writing 1 clears
    await mmio_write(dut, BASE + OFF_EVENT, 1)
    assert int(dut.event_o.value) == 0, "event should clear after W1C in periodic mode"
