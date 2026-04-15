import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, RisingEdge, ClockCycles


# ------------------------------------------------------
# RAM tests I want:
# 1. Reset test, checking ready signal
# 2. Reading from both banks
# 4. Partial byte writes? (on both banks)
# 5. (Optionally) alternating read/write timing, unnessecary as it's just instruction memory that gets loaded once then read out, but maybe good
# ------------------------------------------------------


#   reg        CLK    = 1'b0;
#   reg        resetn = 1'b0;

#   reg        valid  = 1'b0;
#   wire       ready;
#   reg  [3:0] wstrb  = 4'b0;
#   reg [31:0] addr   = 32'h0;
#   reg [31:0] wdata  = 32'h0;
#   wire[31:0] rdata;

# ------------------------------------------------------
# Address is from [10:2] -->  [0,511] * 4
# Bank addressing --> Bank A: [0,511] + 0
#                     Bank B: [0,511] + 512
# ------------------------------------------------------

def conv_addr(addr):
    return (addr * 4) & 0x00000FFC

async def reset_dut(dut, cycles=10):
    # 60 ns > 55.6 ns minimum cycle time required by gf180mcu SRAM model (specparam Tcyc=55600)
    cocotb.start_soon(Clock(dut.CLK, 60, unit="ns").start())
    await FallingEdge(dut.CLK)
    dut.resetn.value = 0
    await ClockCycles(dut.CLK, cycles)
    await FallingEdge(dut.CLK)
    dut.resetn.value = 1
    dut.valid.value = 0
    dut.wstrb.value = 0
    dut.addr.value = 0
    dut.wdata.value = 0
    await ClockCycles(dut.CLK, 2)

async def read_val(dut, addr):
    # Assert on falling edge: gives full setup margin (30 ns) before next posedge,
    # and guarantees valid_r is 0 going into the cycle (flushed by the gap since last op).
    await FallingEdge(dut.CLK)
    dut.addr.value = conv_addr(addr)
    dut.valid.value = 1
    await RisingEdge(dut.ready)
    await ClockCycles(dut.CLK, 1)
    result = int(dut.rdata.value)  # capture before deasserting; cocotb 2.x returns LogicArray
    # Deassert on falling edge: holds valid high for 30 ns past posedge, satisfying tch=10 ns hold.
    await FallingEdge(dut.CLK)
    dut.valid.value = 0
    return result

async def write_val(dut, addr, data, partial=0xf):
    await FallingEdge(dut.CLK)
    dut.addr.value = conv_addr(addr)
    dut.wdata.value = data & 0xFFFFFFFF
    dut.wstrb.value = partial & 0xF
    dut.valid.value = 1
    await RisingEdge(dut.ready)
    await FallingEdge(dut.CLK)
    dut.valid.value = 0
    dut.wstrb.value = 0

@cocotb.test()
async def reset_test(dut):
    await reset_dut(dut)
    assert dut.ready.value == 0, "Ready not low to begin"
    await FallingEdge(dut.CLK)
    dut.valid.value = 1
    await RisingEdge(dut.ready)  # ready takes 2 posedges (valid_r pipeline): wait for it
    dut.valid.value = 0
    assert dut.ready.value == 1, "Ready not high after valid asserted"
    print("Reset Test Complete Without Errors")

@cocotb.test()
async def dual_read_test(dut):
    await reset_dut(dut)
    await write_val(dut, 0, 0xFCFCFCFC)       # write into addr[0], bank A
    await write_val(dut, 512, 0xDEDEDEDE)     # write into addr[512], bank B
    await ClockCycles(dut.CLK, 5)
    assert await read_val(dut, 0) == 0xFCFCFCFC, "Bank A incorrect data"
    assert await read_val(dut, 512) == 0xDEDEDEDE, "Bank B incorrect data"
    print("Dual Test Complete Without Errors")


@cocotb.test()
async def max_read_test(dut):  # If this takes forever just comment it out, probably just need to make sure this works once
    await reset_dut(dut)
    for i in range(0, 1023):
        await write_val(dut, i, 0xABCDEF01)
    for i in range(0, 1023):
        assert await read_val(dut, i) == 0xABCDEF01, f"Error at address {i}"
    print("Max Test Complete Without Errors")

@cocotb.test()
async def partial_write_test(dut):
    await reset_dut(dut)
    await write_val(dut, 0, 0x00000000)
    await write_val(dut, 0, 0xFFFFFFFF, 0x1)  # just first byte
    assert await read_val(dut, 0) == 0x000000FF, "partial write returned incorrectly"
    print("Partial Test Complete Without Errors")



@cocotb.test()
async def alternating_test(dut):
    await reset_dut(dut)
    for i in range(0, 6):
        await write_val(dut, i, 0xABCDEF01)
        assert await read_val(dut, i) == 0xABCDEF01
    print("Alternating Test Complete Without Errors")
