import os
import struct
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import FallingEdge, ClockCycles
from cocotbext.axi import AxiLiteBus, AxiLiteMaster, AxiBus, AxiRam
import logging

SCALE = 8192

def le32(b: bytes) -> int: # interpret 4 bytes as little-endian unsigned int
    return int.from_bytes(b, "little", signed=False)

def u32(x: int) -> bytes: # convert an int to 4 bytes in little-endian order (unsigned)
    return int(x & 0xFFFFFFFF).to_bytes(4, "little")

def u16_4(x: list[int]) -> bytes: # convert 4 int16s to byte struct (feature conversion)
    return struct.pack("<4h", *x) 


async def reset_dut(dut, cycles=10):
    cocotb.start_soon(Clock(dut.CLK, 40, unit="ns").start())
    await FallingEdge(dut.CLK)
    dut.RESETN.value = 0
    await ClockCycles(dut.CLK, cycles)
    await FallingEdge(dut.CLK)
    dut.RESETN.value = 1
    await ClockCycles(dut.CLK, 2)


@cocotb.test()
async def load_weights_and_infer_once(dut):
    await reset_dut(dut)
    clk_i = dut.CLK

    logging.getLogger("cocotbext.axi").setLevel(logging.WARNING)
    
    axil = AxiLiteMaster(
        AxiLiteBus.from_prefix(dut, "saxi"),
        dut.CLK,
        dut.RESETN,
        reset_active_level=False,
    )

    axi_ram = AxiRam(
        AxiBus.from_prefix(dut, "maxi"),
        dut.CLK,
        dut.RESETN,
        reset_active_level=False,
        size=1 << 20,
    )

    # read base addresses from registers
    global_off = le32(await axil.read(0x80, 4))  # 128
    out_base   = le32(await axil.read(0x88, 4))  # 136 
    x_base     = le32(await axil.read(0x8C, 4))  # 140 
    var_base   = le32(await axil.read(0x90, 4))  # 144 

    # convert to offset matching addresses, and mask to 32 bits
    out_addr = (global_off + out_base) & 0xFFFFFFFF
    x_addr   = (global_off + x_base) & 0xFFFFFFFF
    var_addr = (global_off + var_base) & 0xFFFFFFFF

    #print offsets
    dut._log.warning(f"global_off=0x{global_off:08X}")
    dut._log.warning(f"x_addr   =0x{x_addr:08X}  (reg 0x8C + offset)")
    dut._log.warning(f"out_addr =0x{out_addr:08X}  (reg 0x88 + offset)")
    dut._log.warning(f"var_addr =0x{var_addr:08X}  (reg 0x90 + offset)")

    # load weights from bin
    bin_path = "taketwo_params.bin"
    with open(bin_path, "rb") as f:
        param_bytes = f.read()

    dut._log.warning(f"Writing {len(param_bytes)} bytes of weights to var_addr=0x{var_addr:08X}")
    axi_ram.write(var_addr, param_bytes)

    dut._log.warning("Reading weights back...")
    rb = axi_ram.read(var_addr, len(param_bytes))
    assert rb == param_bytes, "Comparison from written weights"

    # start accelerator
    #dut._log.info("Writing START=1 to reg 0x10")
    #await axil.write(0x10, u32(1))

    # writing input vector into memory (real test data from csv)
    with open("processed_sleep_dataset.csv") as f:
        ds = f.readlines()[:500]
    
    true_n=0 
    false_n=0 
    false_p=0 
    true_p = 0
    
    for line in ds:
        #print(line)
        feats = line.strip().split(",")
        #print(feats)
        #await axil.write(0x10, u32(1))
        feats[0] = max(-32768, min(int((float(feats[0])) * SCALE), 32767))    #movement
        feats[1] = max(-32768, min(int((float(feats[1])) * SCALE), 32767))        #cosine
        feats[2] = max(-32768, min(int((float(feats[2])) * SCALE), 32767))    #delta hr
        feats[3] = max(-32768, min(int((float(feats[3])) * SCALE), 32767))   #mssd
        # feats[0] = max(-32768, min(int((float(feats[0])/8.0) * SCALE), 32767))    #movement
        # feats[1] = max(-32768, min(int((float(feats[1])) * SCALE), 32767))        #cosine
        # feats[2] = max(-32768, min(int((float(feats[2])/4.0) * SCALE), 32767))    #delta hr
        # feats[3] = max(-32768, min(int((float(feats[3])*20.0) * SCALE), 32767))   #mssd
        print(feats)
        axi_ram.write(x_addr, u16_4(feats[0:4]))
        # wait for busy to clear
        await axil.write(0x10, u32(1))
        
        while(True):
            busy = le32(await axil.read(0x14, 4))
            if busy == 0:
                break
            await ClockCycles(clk_i, 10)
        await axil.write(0x10, u32(0))

        # read logits from output address
        out_bytes = axi_ram.read(out_addr, 4)
        log0, log1 = struct.unpack("<2h", out_bytes)
        print(f"logits int16: [{log0}, {log1}] (raw bytes={out_bytes.hex()})")
        pred = int(log1) > int(log0)
        if (pred == True and int(feats[4]) == 1):
            true_p += 1
        elif (pred == True and int(feats[4]) == 0):
            false_p += 1 
        elif (pred == False and int(feats[4]) == 1):
            false_n += 1
        elif (pred == False and int(feats[4]) == 0):
            true_n += 1
        print(f"Conf matrix: true_n: {true_n}, false_n: {false_n}, false_p: {false_p}, true_p: {true_p}")