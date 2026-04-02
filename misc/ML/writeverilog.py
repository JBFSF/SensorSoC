"""
writeverilog_with_sim.py

End-to-end NNgen flow for your 4->64->32->2 MLP ONNX:
  (1) Import ONNX
  (2) Quantize (ng.quantize) using a fixed input scale for 'x'
  (4) Software check with ng.eval
  (5) Generate Verilog (via ng.to_veriloggen) + export packed params (ng.export_ndarray)
  (6) RTL simulation using Veriloggen + (iverilog or verilator) and verify RTL output == ng.eval output

Run:
  python3 writeverilog_with_sim.py
Optional:
  SIM=verilator python3 writeverilog_with_sim.py
  SIM=iverilog   python3 writeverilog_with_sim.py
"""

import os
import math
import shutil
import numpy as np
import nngen as ng

from veriloggen import Module, Seq, Delay, Systask, Not, simulation
import veriloggen.thread as vthread
import veriloggen.types.axi as axi


# --------- user knobs ----------
ONNX_PATH  = "taketwo_nngen.onnx"
OUT_DIR    = "nngen_out"
PROJECT    = "taketwo"
CHUNK_SIZE = 64

# input quantization: x_int = round(x_float * X_SCALE)
X_SCALE =  512 #Q3.13, this is maybe 6.9 now

# RTL simulator: "iverilog" or "verilator"
SIMTYPE    = os.environ.get("SIM", "verilator")
AXI_DATAWIDTH = 32
MEMIMG_DATAWIDTH = 32  # memory model word width (keep 32; matches examples)


def main():
    os.makedirs(OUT_DIR, exist_ok=True)

    # (1) Import ONNX -> NNgen graph
    (outputs, placeholders, variables, constants, operators) = ng.from_onnx(
        ONNX_PATH,
        # Important: keep dtypes consistent
        value_dtypes={"x": ng.int16},
        default_placeholder_dtype=ng.int16,
        default_variable_dtype=ng.int16,
        default_constant_dtype=ng.int16,
        default_operator_dtype=ng.int16,
        default_scale_dtype=ng.int16,
        default_bias_dtype=ng.int16,   # keep biases packed at 16 bits with the rest of the parameters
        disable_fusion=False,
        verbose=True,
    )
    
    print(operators)

    out_nodes = list(outputs.values())
    if len(out_nodes) != 1:
        raise RuntimeError(f"Expected exactly 1 output. Got outputs={list(outputs.keys())}")
    top = out_nodes[0]
    x_pl = placeholders["x"]

    print("\nImported ONNX into NNgen")
    print("Output node:", top)

    # (2) Quantize
    input_scale_factors = {"x": X_SCALE}
    ng.quantize(out_nodes, input_scale_factors)
    print("Quantization complete (input_scale_factors =", input_scale_factors, ")")

    # (4) Software verify (ng.eval)
    # Use a deterministic test vector (change/extend later)
    x_float = np.array([[0.5, -0.25, 0.1, -1.0]], dtype=np.float32)
    x_int = np.round(x_float * X_SCALE).astype(np.int64)

    y_int = ng.eval([top], x=x_int)[0]
    print("\nng.eval test:")
    print("x_float:", x_float)
    print("x_int  :", x_int)
    print("y_int  :", y_int)

    # (5) Generate Veriloggen object (this "finalizes" schedule/memory map)
    targ = ng.to_veriloggen([top], PROJECT, silent=False,
                            config={'maxi_datawidth': AXI_DATAWIDTH})

    # Write RTL
    rtl = targ.to_verilog()
    out_v = os.path.join(OUT_DIR, f"{PROJECT}.v")
    with open(out_v, "w") as f:
        f.write(rtl)
    print("\nWrote Verilog to:", out_v)

    # Export packed parameters *after* compilation
    param_data = ng.export_ndarray([top], CHUNK_SIZE)
    if param_data.size == 0:
        raise RuntimeError("export_ndarray returned empty. This usually means the graph wasn't compiled yet.")

    npy_path = os.path.join(OUT_DIR, f"{PROJECT}_params.npy")
    np.save(npy_path, param_data)
    print("Saved packed params (.npy):", npy_path)
    print("param_data dtype:", param_data.dtype, "shape:", param_data.shape, "bytes:", int(param_data.size))

    bin_path = os.path.join(OUT_DIR, f"{PROJECT}_params.bin")
    with open(bin_path, "wb") as f:
        f.write(np.asarray(param_data, dtype=np.uint8).tobytes())
    print("Saved packed params (.bin):", bin_path, "bytes:", os.path.getsize(bin_path))

    # (6) RTL simulation + compare against ng.eval output
    print(f"\nStarting RTL simulation via Veriloggen (SIM={SIMTYPE}) ...")

    # Compute addresses like the README does (uses x_pl.addr/memory_size etc.)
    # NOTE: These addresses are *relative* addresses, and NNgen also exposes registers to override them.
    param_bytes = len(np.asarray(param_data, dtype=np.uint8).tobytes())

    variable_addr = int(math.ceil((x_pl.addr + x_pl.memory_size) / CHUNK_SIZE)) * CHUNK_SIZE
    check_addr    = int(math.ceil((variable_addr + param_bytes) / CHUNK_SIZE)) * CHUNK_SIZE
    tmp_addr      = int(math.ceil((check_addr + top.memory_size) / CHUNK_SIZE)) * CHUNK_SIZE

    # Make an off-chip memory image (size is arbitrary as long as it covers your addresses)
    # We'll allocate 1MB worth of 32-bit words, which is plenty for this tiny model.
    mem_words = (1 * 1024 * 1024) // (MEMIMG_DATAWIDTH // 8)
    mem = np.zeros([mem_words], dtype=np.int64)

    # Place input
    # The last arg is "size_factor" for burst/parallel packing; safe choice is ceil(AXI/act_width)
    act_width = x_pl.dtype.width
    pack = max(int(math.ceil(AXI_DATAWIDTH / act_width)), 1)
    axi.set_memory(mem, x_int, MEMIMG_DATAWIDTH,
                   act_width, x_pl.addr, pack)

    # Place packed params (byte-addressed blob)
    axi.set_memory(mem, param_data, MEMIMG_DATAWIDTH,
                   8, variable_addr)

    # Place expected output (for comparison)
    axi.set_memory(mem, y_int, MEMIMG_DATAWIDTH,
                   top.dtype.width, check_addr, pack)

    # Build a testbench module around 'targ'
    outputfile = os.path.join(OUT_DIR, f"{PROJECT}.out")
    memimg_name = 'memimg_' + os.path.basename(outputfile)

    # Verilator leaves dependency files with absolute paths in the output dir.
    # If this tree was generated on another machine/user account, rebuild it cleanly.
    if os.path.isdir(outputfile):
        shutil.rmtree(outputfile)

    m = Module('test')

    params = m.copy_params(targ)
    ports = m.copy_sim_ports(targ)
    clk = ports['CLK']
    resetn = ports['RESETN']
    rst = m.Wire('RST')
    rst.assign(Not(resetn))

    # AXI memory model connected to 'maxi_*'
    memory = axi.AxiMemoryModel(m, 'memory', clk, rst,
                               datawidth=AXI_DATAWIDTH,
                               memimg=mem, memimg_name=memimg_name,
                               memimg_datawidth=MEMIMG_DATAWIDTH)
    memory.connect(ports, 'maxi')

    # AXI-Lite controller connected to 'saxi_*' (writes start, addresses, etc.)
    saxi = vthread.AXIMLite(m, '_saxi', clk, rst, noio=True)
    saxi.connect(ports, 'saxi')

    # timer
    time_counter = m.Reg('time_counter', 32, initval=0)
    seq = Seq(m, 'seq', clk, rst)
    seq(time_counter.inc())

    def ctrl():
        # let reset settle
        for _ in range(100):
            pass

        # program the global addrs / temp/output/input/var addrs the way NNgen expects
        ng.sim.set_global_addrs(saxi, tmp_addr)

        start_time = time_counter.value
        ng.sim.start(saxi)
        print('# start')

        ng.sim.wait(saxi)
        end_time = time_counter.value
        print('# end')
        print('# execution cycles: %d' % (end_time - start_time))

        # verify RTL output at 'top.addr' matches reference written at check_addr
        ok = True
        for bat in range(top.shape[0]):
            for i in range(top.shape[1]):
                orig = memory.read_word(bat * top.aligned_shape[1] + i,
                                        top.addr, top.dtype.width)
                check = memory.read_word(bat * top.aligned_shape[1] + i,
                                         check_addr, top.dtype.width)
                if vthread.verilog.NotEql(orig, check):
                    print('NG (', bat, i, ') orig:', orig, 'check:', check)
                    ok = False
                else:
                    print('OK (', bat, i, ') orig:', orig, 'check:', check)

        if ok:
            print('# verify: PASSED')
        else:
            print('# verify: FAILED')

        vthread.finish()

    th = vthread.Thread(m, 'th_ctrl', clk, rst, ctrl)
    th.start()

    # instantiate DUT
    m.Instance(targ, 'taketwo',
               params=m.connect_params(targ),
               ports=m.connect_ports(targ))

    # clock/reset
    simulation.setup_clock(m, clk, hperiod=5)
    init = simulation.setup_reset(m, resetn, m.make_reset(), period=100, polarity='low')
    simulation.setup_waveform(m, 'taketwo')
    init.add(
        Delay(10_000_000),
        Systask('finish'),
    )

    # write testbench RTL (optional but useful)
    tb_v = os.path.join(OUT_DIR, f"{PROJECT}_tb.v")
    m.to_verilog(tb_v)
    print("Wrote testbench Verilog to:", tb_v)

    sim = simulation.Simulator(m, sim=SIMTYPE)
    rslt = sim.run(outputfile=outputfile)
    print(rslt)

    print("\nDONE. If verify PASSED, your exported weights + RTL are consistent with ng.eval.")


if __name__ == "__main__":
    main()
