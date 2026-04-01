# How to complie firmware and sim

cd firmware
mkdir -p build                                                     

riscv64-unknown-elf-gcc \
  -march=rv32imc -mabi=ilp32 \               
  -nostdlib -ffreestanding -O2 \
  -Wl,-T,linker.ld \
  -o build/firmware.elf \       
  start.S \                                                             
  tests/test_sleepwake.c                   

riscv64-unknown-elf-objcopy -O binary build/firmware.elf build/firmware.bin

rishigovindan@Rishis-MacBook-Pro firmware % >....                                                              
if len(data) % 4 != 0:
    data += b"\x00" * (4 - (len(data) % 4))

out_lines = []
for i in range(0, len(data), 4):
    word = struct.unpack_from("<I", data, i)[0] 
    out_lines.append(f"{word:08x}")

pathlib.Path("build/firmware.hex").write_text("\n".join(out_lines) + "\n")
print(f"Wrote build/firmware.hex with {len(out_lines)} 32-bit words")
PY

rishigovindan@Rishis-MacBook-Pro firmware % cd ..
rishigovindan@Rishis-MacBook-Pro sleep_soc % iverilog -g2012 -s tb_soc -o sim_soc.vvp \                        
  sim/tb/tb_soc.sv \
  rtl/soc_top.v \
  ip/picorv32.v \
  rtl/gpio_mmio.v \
  rtl/test_mmio.v \
  rtl/timer_mmio.v \
  rtl/ml_stub_mmio.v \
  rtl/pwrctrl_mmio.v

vvp sim_soc.vvp
