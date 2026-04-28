import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ClockCycles

CLK_PERIOD_NS = 10

# States (for readability in failure messages)
IDLE      = 0
SLEEP     = 1
FEAT_ONLY = 2
ALL       = 3
CPU_FEAT  = 4
ML_ONLY   = 5
CPU_ONLY  = 6


async def reset_dut(dut, cycles=5):
    """Start clock, hold reset for `cycles` cycles, release, settle."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_PERIOD_NS, unit="ns").start())
    dut.resetn_i.value        = 0
    dut.feat_valid_i.value    = 0
    dut.ml_irq_i.value        = 0
    dut.wake_sources_i.value  = 0
    dut.sleep_req_i.value     = 0
    dut.mem_valid_i.value     = 0
    dut.irqc_wake_req_i.value = 0
    dut.test_mode_i.value     = 0
    await ClockCycles(dut.clk_i, cycles)
    await FallingEdge(dut.clk_i)
    dut.resetn_i.value = 1
    await ClockCycles(dut.clk_i, 2)   # settle: IDLE->SLEEP takes 1 posedge


async def wake_to_feat_only(dut):
    dut.irqc_wake_req_i.value = 1
    await ClockCycles(dut.clk_i, 1)
    dut.irqc_wake_req_i.value = 0
    await ClockCycles(dut.clk_i, 1)


async def advance_to_all(dut):
    dut.feat_valid_i.value = 1
    await ClockCycles(dut.clk_i, 1)
    dut.feat_valid_i.value = 0
    await ClockCycles(dut.clk_i, 1)


async def advance_to_cpu_feat(dut):
    dut.ml_irq_i.value = 1
    await ClockCycles(dut.clk_i, 1)
    dut.ml_irq_i.value = 0
    await ClockCycles(dut.clk_i, 1)


async def do_can_sleep(dut, cycles = 5):
    dut.mem_valid_i.value  = 0
    dut.sleep_req_i.value  = 1
    await ClockCycles(dut.clk_i, cycles)
    dut.sleep_req_i.value  = 0
    await ClockCycles(dut.clk_i, 2)


# ---------------------------------------------------------------
# Tests
# ---------------------------------------------------------------

@cocotb.test()
async def test_reset_goes_to_sleep(dut): #Basic reset
    await reset_dut(dut)
    assert dut.sleeping_o.value == 1, "sleeping_o not asserted after reset"
    assert dut.feat_en_o.value  == 0, "feat_en_o should be 0 in SLEEP"
    assert dut.ml_en_o.value    == 0, "ml_en_o should be 0 in SLEEP"
    assert dut.cpu_en_o.value   == 0, "cpu_en_o should be 0 in SLEEP"


@cocotb.test()
async def test_irqc_wake(dut): #See if we go into FEAT_ONLY after watchdog goes off
    """irqc_wake_req_i wakes FSM from SLEEP to FEAT_ONLY."""
    await reset_dut(dut)
    assert dut.sleeping_o.value == 1

    await wake_to_feat_only(dut)

    assert dut.sleeping_o.value == 0, "Should have woken from SLEEP"
    assert dut.feat_en_o.value  == 1, "feat_en_o should be 1 in FEAT_ONLY"
    assert dut.ml_en_o.value    == 0, "ml_en_o should be 0 in FEAT_ONLY"
    assert dut.cpu_en_o.value   == 0, "cpu_en_o should be 1 after wake"

@cocotb.test()
async def test_random_reset(dut): #Test for weird behavior on resets
    cocotb.start_soon(Clock(dut.clk_i, CLK_PERIOD_NS, unit="ns").start())
    dut.resetn_i.value        = 0
    dut.feat_valid_i.value    = 1
    dut.ml_irq_i.value        = 1
    dut.wake_sources_i.value  = 0xF0EF_9FDF # arbitrary garbage input to wake sources
    dut.sleep_req_i.value     = 1
    dut.mem_valid_i.value     = 1
    dut.irqc_wake_req_i.value = 1
    dut.test_mode_i.value     = 0
    await ClockCycles(dut.clk_i, 5)
    await FallingEdge(dut.clk_i)
    dut.resetn_i.value        = 1
    dut.feat_valid_i.value    = 0
    dut.ml_irq_i.value        = 0
    #dut.wake_sources_i.value  = 0x0000_0000  
    dut.sleep_req_i.value     = 0
    dut.mem_valid_i.value     = 0
    dut.irqc_wake_req_i.value = 0
    await ClockCycles(dut.clk_i, 5)   # extra margin

    assert dut.sleeping_o.value == 1, "Static-high wake_sources must not wake FSM"


@cocotb.test()
async def test_feat_only_to_all(dut): #Features to all
    await reset_dut(dut)
    await wake_to_feat_only(dut)
    assert dut.feat_en_o.value == 1 and dut.ml_en_o.value == 0

    await advance_to_all(dut)

    assert dut.feat_en_o.value == 1, "feat_en_o should remain 1 in ALL"
    assert dut.ml_en_o.value   == 1, "ml_en_o should be 1 in ALL"
    assert dut.cpu_en_o.value  == 1, "cpu_en_o should be 1 in ALL"
    assert dut.sleeping_o.value == 0


@cocotb.test()
async def test_all_to_cpu_feat(dut): #All the CPU
    await reset_dut(dut)
    await wake_to_feat_only(dut)
    await advance_to_all(dut)
    assert dut.ml_en_o.value == 1

    await advance_to_cpu_feat(dut)

    assert dut.ml_en_o.value    == 0, "ml_en_o should be 0 in CPU_FEAT"
    assert dut.feat_en_o.value  == 1, "feat_en_o should be 1 in CPU_FEAT"
    assert dut.cpu_en_o.value   == 1, "cpu_en_o should be 1 in CPU_FEAT"
    assert dut.sleeping_o.value == 0


@cocotb.test()
async def test_cpu_feat_can_sleep(dut): #CPU sleep
    await reset_dut(dut)
    await wake_to_feat_only(dut)
    await advance_to_all(dut)
    await advance_to_cpu_feat(dut)

    # cpu_en_o is driven by cpu_clk_en_r which stays high until state_d==SLEEP
    assert dut.cpu_en_o.value == 1

    await do_can_sleep(dut)

    # Back in FEAT_ONLY: feat pipeline still runs, ML off
    # cpu_clk_en_r stays 1 (state_d was FEAT_ONLY, not SLEEP)
    assert dut.feat_en_o.value  == 1, "feat_en_o should be 1 back in FEAT_ONLY"
    assert dut.ml_en_o.value    == 0, "ml_en_o should be 0 in FEAT_ONLY"
    assert dut.cpu_en_o.value   == 0, "cpu_clk_en_r stays 1 until state_d==SLEEP"
    assert dut.sleeping_o.value == 0


@cocotb.test()
async def test_full_pipeline_cycle(dut):
    """Drive the complete SLEEP->FEAT_ONLY->ALL->CPU_FEAT->FEAT_ONLY arc."""
    await reset_dut(dut)

    # SLEEP
    assert dut.sleeping_o.value == 1

    # SLEEP -> FEAT_ONLY
    await wake_to_feat_only(dut)
    assert dut.feat_en_o.value == 1
    assert dut.ml_en_o.value   == 0
    assert dut.cpu_en_o.value == 0

    # FEAT_ONLY -> ALL
    await advance_to_all(dut)
    assert dut.feat_en_o.value == 1
    assert dut.ml_en_o.value   == 1
    assert dut.cpu_en_o.value == 1

    # ALL -> CPU_FEAT
    await advance_to_cpu_feat(dut)
    assert dut.feat_en_o.value == 1
    assert dut.ml_en_o.value   == 0
    assert dut.cpu_en_o.value  == 1

    # CPU_FEAT -> FEAT_ONLY
    await do_can_sleep(dut)
    assert dut.feat_en_o.value  == 1
    assert dut.ml_en_o.value    == 0
    assert dut.sleeping_o.value == 0
    
@cocotb.test()
async def test_modes_test(dut):
    await reset_dut(dut)
    
    for i in range(1,5): #Feats tests
        dut.test_mode_i.value = i & 0xF
        await ClockCycles(dut.clk_i, 2)
        assert dut.feat_en_o.value  == 1
        assert dut.ml_en_o.value    == 0
        assert dut.cpu_en_o.value == 0
        

    dut.test_mode_i.value = 6 & 0xF #ML test
    await ClockCycles(dut.clk_i, 2)
    assert dut.feat_en_o.value  == 1
    assert dut.ml_en_o.value    == 1
    assert dut.cpu_en_o.value == 0
    
    dut.test_mode_i.value = 12 & 0xF #ML test
    await ClockCycles(dut.clk_i, 2)
    assert dut.feat_en_o.value  == 1
    assert dut.ml_en_o.value    == 1
    assert dut.cpu_en_o.value == 0
    
    dut.test_mode_i.value = 13 & 0xF #ML test
    await ClockCycles(dut.clk_i, 2)
    assert dut.feat_en_o.value  == 1
    assert dut.ml_en_o.value    == 1
    assert dut.cpu_en_o.value == 0
    
    for i in range(7,12): #CPU tests
        dut.test_mode_i.value = i & 0xF
        await ClockCycles(dut.clk_i, 2)
        assert dut.feat_en_o.value  == 0
        assert dut.ml_en_o.value    == 0
        assert dut.cpu_en_o.value == 1
    
