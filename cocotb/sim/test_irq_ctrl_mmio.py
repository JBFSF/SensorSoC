import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ClockCycles
from cocotb.triggers import Timer


BASE = 0x03005000
OFF_PENDING = 0x00
OFF_MASK = 0x04
OFF_WAKE_EN = 0x08
OFF_ACTIVE = 0x0C
OFF_CLAIM = 0x14
OFF_COMPLETE = 0x18


async def reset_dut(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.resetn.value = 0
    dut.mem_valid.value = 0
    dut.mem_addr.value = 0
    dut.mem_wdata.value = 0
    dut.mem_wstrb.value = 0
    dut.host_req_i.value = 0
    dut.host_we_i.value = 0
    dut.host_off_i.value = 0
    dut.host_wdata_i.value = 0
    dut.irq_src_i.value = 0
    await ClockCycles(dut.clk, 5)
    dut.resetn.value = 1
    await ClockCycles(dut.clk, 2)


async def mmio_write(dut, off: int, data: int):
    dut.mem_addr.value = BASE + off
    dut.mem_wdata.value = data & 0xFFFFFFFF
    dut.mem_wstrb.value = 0xF
    dut.mem_valid.value = 1
    ready = 0
    for _ in range(5):
        await RisingEdge(dut.clk)
        if int(dut.mem_ready.value) == 1:
            ready = 1
            break
    assert ready == 1, f"mem_ready timeout on write off=0x{off:02x}"
    dut.mem_valid.value = 0
    dut.mem_wstrb.value = 0
    await RisingEdge(dut.clk)


async def mmio_read(dut, off: int) -> int:
    dut.mem_addr.value = BASE + off
    dut.mem_wstrb.value = 0
    dut.mem_valid.value = 1
    data = 0
    ready = 0
    for _ in range(5):
        await RisingEdge(dut.clk)
        if int(dut.mem_ready.value) == 1:
            data = int(dut.mem_rdata.value) & 0xFFFFFFFF
            ready = 1
            break
    assert ready == 1, f"mem_ready timeout on read off=0x{off:02x}"
    dut.mem_valid.value = 0
    await RisingEdge(dut.clk)
    return data


async def host_write(dut, off: int, data: int):
    dut.host_off_i.value = off & 0xFF
    dut.host_wdata_i.value = data & 0xFFFFFFFF
    dut.host_we_i.value = 1
    dut.host_req_i.value = 1
    ready = 0
    for _ in range(5):
        await RisingEdge(dut.clk)
        if int(dut.host_ready_o.value) == 1:
            ready = 1
            break
    assert ready == 1, f"host_ready timeout on write off=0x{off:02x}"
    dut.host_req_i.value = 0
    dut.host_we_i.value = 0
    await RisingEdge(dut.clk)


async def host_read(dut, off: int) -> int:
    dut.host_off_i.value = off & 0xFF
    dut.host_we_i.value = 0
    dut.host_req_i.value = 1
    data = 0
    ready = 0
    for _ in range(5):
        await RisingEdge(dut.clk)
        if int(dut.host_ready_o.value) == 1:
            data = int(dut.host_rdata_o.value) & 0xFFFFFFFF
            ready = 1
            break
    assert ready == 1, f"host_ready timeout on read off=0x{off:02x}"
    dut.host_req_i.value = 0
    await RisingEdge(dut.clk)
    return data


async def expect_wake_pulse(dut, window_ns: int = 40):
    for _ in range(window_ns):
        if int(dut.wake_req_o.value):
            return
        await Timer(1, unit="ns")
    raise AssertionError("Expected wake_req_o pulse in observation window")


@cocotb.test()
async def test_simultaneous_sources_claim_complete(dut):
    await reset_dut(dut)
    await mmio_write(dut, OFF_MASK, 0x00000007)
    await mmio_write(dut, OFF_WAKE_EN, 0x00000007)

    dut.irq_src_i.value = 0x00000007
    await expect_wake_pulse(dut)
    await ClockCycles(dut.clk, 2)
    assert int(dut.wake_req_o.value) == 0, "Wake pulse should not stick"

    pending = await mmio_read(dut, OFF_PENDING)
    assert pending & 0x7 == 0x7
    assert int(dut.irq_o.value) & 0x7 == 0x7

    claim = await mmio_read(dut, OFF_CLAIM)
    assert claim == 1, f"Expected claim id=1, got {claim}"
    await mmio_write(dut, OFF_CLAIM, 0)
    active = await mmio_read(dut, OFF_ACTIVE)
    assert active == 0x1, f"Expected active bit0 set, got 0x{active:08x}"

    await mmio_write(dut, OFF_COMPLETE, 1)
    active = await mmio_read(dut, OFF_ACTIVE)
    assert active == 0, "Expected active cleared after complete"


@cocotb.test()
async def test_masking_and_pending_reassert_on_new_edge(dut):
    await reset_dut(dut)
    await mmio_write(dut, OFF_MASK, 0x00000000)
    await mmio_write(dut, OFF_WAKE_EN, 0x00000004)

    # Rising edge with mask=0 should still set pending and pulse wake.
    dut.irq_src_i.value = 0x00000004
    await expect_wake_pulse(dut)
    await ClockCycles(dut.clk, 3)
    assert int(dut.wake_req_o.value) == 0

    pending = await mmio_read(dut, OFF_PENDING)
    assert pending & 0x4
    assert (int(dut.irq_o.value) & 0x4) == 0, "Masked source should not drive irq_o"

    # Unmask should expose existing pending without requiring new source edge.
    await mmio_write(dut, OFF_MASK, 0x00000004)
    await RisingEdge(dut.clk)
    assert int(dut.irq_o.value) & 0x4

    # Clear pending while source is still high; should stay cleared until new edge.
    await mmio_write(dut, OFF_PENDING, 0x00000004)
    pending = await mmio_read(dut, OFF_PENDING)
    assert (pending & 0x4) == 0
    await ClockCycles(dut.clk, 2)
    pending = await mmio_read(dut, OFF_PENDING)
    assert (pending & 0x4) == 0, "No re-pend expected without a new source edge"

    # Create a fresh edge low->high and expect pending + wake again.
    dut.irq_src_i.value = 0x00000000
    await RisingEdge(dut.clk)
    dut.irq_src_i.value = 0x00000004
    await expect_wake_pulse(dut)
    pending = await mmio_read(dut, OFF_PENDING)
    assert pending & 0x4


@cocotb.test()
async def test_host_sideband_register_access(dut):
    await reset_dut(dut)

    await host_write(dut, OFF_MASK, 0x00000002)
    await host_write(dut, OFF_WAKE_EN, 0x00000002)
    assert await host_read(dut, OFF_MASK) == 0x00000002
    assert await host_read(dut, OFF_WAKE_EN) == 0x00000002

    dut.irq_src_i.value = 0x00000002
    await expect_wake_pulse(dut)
    await ClockCycles(dut.clk, 3)
    assert int(dut.wake_req_o.value) == 0

    pending = await host_read(dut, OFF_PENDING)
    assert pending & 0x2
    assert int(dut.irq_o.value) & 0x2

    await host_write(dut, OFF_PENDING, 0x00000002)
    pending = await host_read(dut, OFF_PENDING)
    assert (pending & 0x2) == 0


@cocotb.test()
async def test_clear_then_immediate_new_edge_repends(dut):
    await reset_dut(dut)
    await mmio_write(dut, OFF_MASK, 0x00000002)
    await mmio_write(dut, OFF_WAKE_EN, 0x00000002)

    # First edge latches pending.
    dut.irq_src_i.value = 0x00000002
    await expect_wake_pulse(dut)
    pending = await mmio_read(dut, OFF_PENDING)
    assert pending & 0x2

    # Drive low, clear pending, then immediately re-edge high.
    dut.irq_src_i.value = 0x00000000
    await RisingEdge(dut.clk)
    await mmio_write(dut, OFF_PENDING, 0x00000002)
    dut.irq_src_i.value = 0x00000002
    await expect_wake_pulse(dut)

    pending = await mmio_read(dut, OFF_PENDING)
    assert pending & 0x2, "Expected fresh pending after immediate new edge"
