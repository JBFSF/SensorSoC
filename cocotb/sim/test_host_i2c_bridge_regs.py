import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ClockCycles, Timer


REG_STATUS = 0x02
REG_WAKE_TS0 = 0x10
REG_WAKE_TS1 = 0x11
REG_WAKE_TS2 = 0x12
REG_WAKE_TS3 = 0x13
REG_WAKE_WIN_L = 0x14
REG_WAKE_WIN_H = 0x15
REG_STEP_SEC_L = 0x16
REG_STEP_SEC_H = 0x17
REG_WAKE_POLICY = 0x1B

REG_IRQC_OFF = 0x20
REG_IRQC_W0 = 0x21
REG_IRQC_W1 = 0x22
REG_IRQC_W2 = 0x23
REG_IRQC_W3 = 0x24
REG_IRQC_CMD = 0x25
REG_IRQC_STAT = 0x26
REG_IRQC_R0 = 0x28
REG_IRQC_R1 = 0x29
REG_IRQC_R2 = 0x2A
REG_IRQC_R3 = 0x2B

REG_CONF_THR_L = 0x30
REG_CONF_THR_H = 0x31
REG_CONF_CTRL = 0x32
REG_CONF_STAT = 0x33


async def reset_dut(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.resetn.value = 0
    dut.wr_en_i.value = 0
    dut.wr_addr_i.value = 0
    dut.wr_data_i.value = 0
    dut.rd_addr_i.value = 0
    dut.proto_err_i.value = 0
    dut.ml_score_i.value = 0
    dut.irqc_ready_i.value = 0
    dut.irqc_rdata_i.value = 0
    await ClockCycles(dut.clk, 5)
    dut.resetn.value = 1
    await ClockCycles(dut.clk, 2)


async def write_reg(dut, addr: int, data: int):
    dut.wr_addr_i.value = addr & 0xFF
    dut.wr_data_i.value = data & 0xFF
    dut.wr_en_i.value = 1
    await RisingEdge(dut.clk)
    dut.wr_en_i.value = 0
    await RisingEdge(dut.clk)


async def read_reg(dut, addr: int) -> int:
    dut.rd_addr_i.value = addr & 0xFF
    await Timer(1, unit="ns")
    return int(dut.rd_data_o.value) & 0xFF


@cocotb.test()
async def test_cfg_and_status_contract(dut):
    await reset_dut(dut)

    await write_reg(dut, REG_WAKE_TS0, 0xAA)
    await write_reg(dut, REG_WAKE_TS1, 0xBB)
    await write_reg(dut, REG_WAKE_TS2, 0xCC)
    await write_reg(dut, REG_WAKE_TS3, 0xDD)
    await write_reg(dut, REG_WAKE_WIN_L, 0x34)
    await write_reg(dut, REG_WAKE_WIN_H, 0x12)
    await write_reg(dut, REG_STEP_SEC_L, 0x2C)
    await write_reg(dut, REG_STEP_SEC_H, 0x01)
    await write_reg(dut, REG_WAKE_POLICY, 0x01)

    assert int(dut.cfg_target_wake_sec_o.value) == 0xDDCCBBAA
    assert int(dut.cfg_window_sec_o.value) == 0x00001234
    assert int(dut.cfg_step_sec_o.value) == 300
    assert int(dut.cfg_policy_o.value) == 0x01

    # Invalid host write address sets RX error status bit[1].
    await write_reg(dut, 0x7E, 0x55)
    status = await read_reg(dut, REG_STATUS)
    assert (status & 0x02) != 0, f"Expected RX error bit set, got 0x{status:02x}"

    # Protocol error pin sets status bit[2].
    dut.proto_err_i.value = 1
    await RisingEdge(dut.clk)
    dut.proto_err_i.value = 0
    status = await read_reg(dut, REG_STATUS)
    assert (status & 0x04) != 0, f"Expected proto error bit set, got 0x{status:02x}"

    # W1C clear for both bits.
    await write_reg(dut, REG_STATUS, 0x06)
    status = await read_reg(dut, REG_STATUS)
    assert (status & 0x06) == 0, f"Expected cleared status bits, got 0x{status:02x}"


@cocotb.test()
async def test_confidence_threshold_rearm_and_sticky(dut):
    await reset_dut(dut)

    await write_reg(dut, REG_CONF_THR_L, 0x20)
    await write_reg(dut, REG_CONF_THR_H, 0x00)
    await write_reg(dut, REG_CONF_CTRL, 0x03)  # conf_en + irq_en

    # Keep below threshold: armed should stay set, no event.
    dut.ml_score_i.value = 0x00000010
    await ClockCycles(dut.clk, 2)
    stat = await read_reg(dut, REG_CONF_STAT)
    assert (stat & 0x08) != 0, "Expected armed=1 before first threshold crossing"

    # Rising through threshold should pulse event once.
    dut.ml_score_i.value = 0x00000030
    pulse_count = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
        if int(dut.event_o.value):
            pulse_count += 1
    assert pulse_count >= 1, "Expected threshold crossing event pulse"

    stat = await read_reg(dut, REG_CONF_STAT)
    assert (stat & 0x06) == 0x06, f"Expected sticky bits set after crossing, got 0x{stat:02x}"
    assert (stat & 0x08) == 0, "Expected armed=0 after crossing"

    # Hold above threshold: no second pulse while unarmed.
    for _ in range(3):
        await RisingEdge(dut.clk)
        assert int(dut.event_o.value) == 0, "Unexpected repeated event while score held high"

    # Drop below threshold to re-arm, then rise above again for second pulse.
    dut.ml_score_i.value = 0x00000000
    await ClockCycles(dut.clk, 2)
    stat = await read_reg(dut, REG_CONF_STAT)
    assert (stat & 0x08) != 0, "Expected armed=1 after dropping below threshold"

    dut.ml_score_i.value = 0x00000028
    saw_second_pulse = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
        if int(dut.event_o.value):
            saw_second_pulse = 1
    assert saw_second_pulse == 1, "Expected second event after re-arm and re-cross"

    # Sticky clear via REG_CONF_CTRL bit2.
    await write_reg(dut, REG_CONF_CTRL, 0x07)
    stat = await read_reg(dut, REG_CONF_STAT)
    assert (stat & 0x06) == 0, f"Expected sticky clear, got 0x{stat:02x}"


@cocotb.test()
async def test_irqc_proxy_busy_done_and_latched_readback(dut):
    await reset_dut(dut)

    await write_reg(dut, REG_IRQC_OFF, 0x04)
    await write_reg(dut, REG_IRQC_W0, 0x44)
    await write_reg(dut, REG_IRQC_W1, 0x33)
    await write_reg(dut, REG_IRQC_W2, 0x22)
    await write_reg(dut, REG_IRQC_W3, 0x11)

    # Launch command: GO=1, WE=1.
    await write_reg(dut, REG_IRQC_CMD, 0x03)
    await RisingEdge(dut.clk)
    assert int(dut.irqc_req_o.value) == 1
    assert int(dut.irqc_we_o.value) == 1
    assert int(dut.irqc_off_o.value) == 0x04
    assert int(dut.irqc_wdata_o.value) == 0x11223344

    # Issue another GO while still busy -> should set ERR in REG_IRQC_STAT bit1.
    await write_reg(dut, REG_IRQC_CMD, 0x03)
    stat = await read_reg(dut, REG_IRQC_STAT)
    assert (stat & 0x02) != 0, f"Expected busy/err bit set, got 0x{stat:02x}"

    # Complete response from IRQC sideband.
    dut.irqc_rdata_i.value = 0xA1B2C3D4
    dut.irqc_ready_i.value = 1
    await RisingEdge(dut.clk)
    dut.irqc_ready_i.value = 0
    await RisingEdge(dut.clk)

    stat = await read_reg(dut, REG_IRQC_STAT)
    assert (stat & 0x01) != 0, f"Expected done bit set, got 0x{stat:02x}"

    r0 = await read_reg(dut, REG_IRQC_R0)
    r1 = await read_reg(dut, REG_IRQC_R1)
    r2 = await read_reg(dut, REG_IRQC_R2)
    r3 = await read_reg(dut, REG_IRQC_R3)
    assert (r3 << 24) | (r2 << 16) | (r1 << 8) | r0 == 0xA1B2C3D4

    # W1C clear done/err bits.
    await write_reg(dut, REG_IRQC_STAT, 0x03)
    stat = await read_reg(dut, REG_IRQC_STAT)
    assert (stat & 0x03) == 0
