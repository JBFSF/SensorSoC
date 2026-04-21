import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ClockCycles

BOOT_WAIT_CYCLES = 120_000   # covers ~33k SPI boot (256 words) + firmware init
INJECT_HOLD      = 10        # cycles to hold test_irq_src high (IRQC edge capture)
TIMEOUT          = 200_000   # cycles per step before failing

IRQ_NAMES = ["timer", "ML", "host_i2c"]

def maybe_getattr(obj, name):
    try:
        return getattr(obj, name)
    except AttributeError:
        return None

def read_int(sig):
    return int(sig.value)

async def poll_value(sig, value, timeout):
    """Return True if sig reaches value within timeout rising edges."""
    for _ in range(timeout):
        await RisingEdge(cocotb.top.clk)
        try:
            if read_int(sig) == value:
                return True
        except ValueError:
            pass
    return False

async def poll_nonzero_mask(sig, mask, timeout):
    """Return True if (sig & mask) becomes nonzero within timeout rising edges."""
    for _ in range(timeout):
        await RisingEdge(cocotb.top.clk)
        try:
            if read_int(sig) & mask:
                return True
        except ValueError:
            pass
    return False

@cocotb.test()
async def test_irq_injection(dut):
    """Inject each of the 3 IRQ sources via test_irq_src and verify IRQC pending + TEST_CODE."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    dut.test_irq_src.value = 0
    dut.resetn.value = 0
    await ClockCycles(dut.clk, 10)
    dut.resetn.value = 1

    # Wait for hardware boot_done
    dut._log.info("Waiting for boot_done...")
    assert await poll_value(dut.boot_done, 1, BOOT_WAIT_CYCLES), \
        f"boot_done never asserted (timeout {BOOT_WAIT_CYCLES} cycles)"
    dut._log.info("boot_done asserted — CPU is running")

    # Wait for firmware ready sentinel
    dut._log.info("Waiting for firmware ready (TEST_STATUS=0xA000)...")
    assert await poll_value(dut.u_top.u_test.status_o, 0xA000, TIMEOUT), \
        "firmware never wrote ready sentinel 0xA000"
    dut._log.info("Firmware ready — IRQC armed, injecting IRQs")

    irqc_mask = read_int(dut.u_top.u_irqc.mask) & 0x7
    irqc_wake_en = read_int(dut.u_top.u_irqc.wake_en) & 0x7
    assert irqc_mask == 0x7, f"IRQC mask[2:0]=0x{irqc_mask:x}, expected 0x7"
    assert irqc_wake_en == 0x7, f"IRQC wake_en[2:0]=0x{irqc_wake_en:x}, expected 0x7"

    cpu_irq_mask = maybe_getattr(dut.u_top.cpu, "irq_mask")
    if cpu_irq_mask is not None:
        pico_mask = read_int(cpu_irq_mask) & 0x7
        assert pico_mask == 0, f"PicoRV32 irq_mask[2:0]=0x{pico_mask:x}, expected 0x0"

    for bit in range(3):
        expected_code = 1 << bit
        name = IRQ_NAMES[bit]
        other_bits = 0x7 & ~expected_code

        # Start edge-sensitive monitors before injection so short pulses are not missed.
        pico_irq_seen = cocotb.start_soon(
            poll_nonzero_mask(dut.u_top.pico_irq, expected_code, TIMEOUT))
        eoi_seen = cocotb.start_soon(
            poll_nonzero_mask(dut.irq_eoi, expected_code, TIMEOUT))

        # Step 1: inject IRQ source
        dut.test_irq_src.value = 1 << bit
        await ClockCycles(dut.clk, INJECT_HOLD)
        dut.test_irq_src.value = 0  # deassert before retirq

        # Step 2: verify IRQC latched it (pending bit set)
        dut._log.info(f"[{name}] Verifying IRQC pending[{bit}] latches...")
        assert await poll_nonzero_mask(dut.u_top.u_irqc.pending, 1 << bit, 50), \
            f"IRQC pending[{bit}] never set after injection"
        dut._log.info(f"[{name}] IRQC pending[{bit}] confirmed set")

        assert await pico_irq_seen, f"CPU-visible pico_irq[{bit}] never asserted for {name} IRQ"

        # Step 3: wait for firmware to handle it (TEST_CODE updated)
        dut._log.info(f"[{name}] Waiting for firmware TEST_CODE=0x{expected_code:08x}...")
        assert await poll_value(dut.u_top.u_test.code_o, expected_code, TIMEOUT), \
            f"TEST_CODE never became 0x{expected_code:08x} for {name} IRQ"

        # Step 4: verify EOI pulsed on the correct bit (firmware ran handler + retirq)
        dut._log.info(f"[{name}] Verifying irq_eoi_o[{bit}] pulsed...")
        assert await eoi_seen, f"irq_eoi_o[{bit}] never pulsed for {name} IRQ"
        dut._log.info(f"[{name}] irq_eoi_o[{bit}] confirmed pulsed (irq_state 01->10->retirq)")

        # Step 5: verify IRQC pending cleared (W1C by firmware)
        pending_cleared = await poll_value(dut.u_top.u_irqc.pending, 0, 500)
        assert pending_cleared, \
            f"[{name}] IRQC pending still 0x{read_int(dut.u_top.u_irqc.pending):08x} after handler"
        dut._log.info(f"[{name}] IRQC pending cleared by firmware handler")

        pending_low = read_int(dut.u_top.u_irqc.pending) & 0x7
        assert (pending_low & other_bits) == 0, \
            f"[{name}] unrelated IRQC pending bits stuck: 0x{pending_low & other_bits:08x}"

        code = read_int(dut.u_top.u_test.code_o)
        assert code == expected_code, \
            f"TEST_CODE=0x{code:08x} expected 0x{expected_code:08x} for {name} IRQ"
        dut._log.info(f"PASS [{name}]: TEST_CODE=0x{code:08x}")

    # Wait for done sentinel
    dut._log.info("Waiting for done sentinel (TEST_STATUS=0xDEAD)...")
    assert await poll_value(dut.u_top.u_test.status_o, 0xDEAD, TIMEOUT), \
        "firmware never wrote done sentinel 0xDEAD"
    dut._log.info("PASS: all 3 IRQ sources verified end-to-end")
