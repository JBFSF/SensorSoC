# sleep_soc/Makefile
#
# Goals:
#   - One-command build + run for your SystemVerilog SoC sim (tb_soc)
#   - One-command run for cocotb unit tests (test_mmio, timer_mmio)
#   - Simple firmware build (RISC-V GCC -> .elf/.bin/.hex)
#
# Usage:
#
#   # Build firmware only (per variant)
#   make firmware FW_VARIANT=test_sleepwake
#   make firmware FW_VARIANT=test_gpio
#   make firmware FW_VARIANT=test_sleepwake_periodic
#   make firmware FW_VARIANT=main
#
#   # Compile + run SoC testbench with a chosen firmware variant
#   make sim-soc                        # defaults to FW_VARIANT=test_sleepwake
#   make sim-soc FW_VARIANT=test_gpio
#   make sim-soc FW_VARIANT=test_sleepwake_periodic
#   make sim-soc FW_VARIANT=main
#
#   # Cocotb tests
#   make test-mmio
#   make test-timer
#	make test-cpu-ml
#
#   # Standalone SV testbench
#   make sim-reset-ctrl
#   make sim-globaltimer
#   make sim-logit-confidence
#
#   # Cleanup
#   make clean
#
# NOTE:
#   This Makefile expects a small helper script at:
#     tools/bin2hex.py
#   which converts firmware/build/firmware.bin -> firmware/build/firmware.hex
#   as 32-bit little-endian words (one word per line), suitable for $readmemh.

SHELL := /bin/bash

# ----------------------------
# Tools
IVERILOG ?= iverilog
VVP      ?= vvp
PYTHON   ?= python3

# ------------------------------------------------------------
# Derived paths
# ------------------------------------------------------------

# Cocotb VPI library
COCOTB_LIBDIR := $(shell $(PYTHON) -c "import cocotb, os; print(os.path.join(os.path.dirname(cocotb.__file__), 'libs'))" 2>/dev/null)

# Python interpreter for cocotb
PYGPI_PYTHON_BIN := $(shell $(PYTHON) -c "import sys; print(sys.executable)")

# Build directory
BUILD_DIR := sim/build

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

WAVE_DIR := sim/waves

# ------------------------------------------------------------
# Common cocotb environment (v2 naming)
# ------------------------------------------------------------
export PYGPI_PYTHON_BIN := $(PYGPI_PYTHON_BIN)
export PYTHONPATH       := $(PWD)/sim/tb
export COCOTB_LOG_LEVEL ?= INFO

# ============================================================
# MMIO TEST
# ============================================================

# ----------------------------
PYTHON       ?= python3
IVERILOG     ?= iverilog
VVP          ?= vvp

# RISC-V toolchain
RISCV_PREFIX ?= riscv64-unknown-elf-
RISCV_GCC    ?= $(RISCV_PREFIX)gcc
RISCV_OBJCOPY?= $(RISCV_PREFIX)objcopy

# ----------------------------
# Paths
# ----------------------------
RTL_DIR      := rtl
TB_DIR       := sim/tb
SIM_BUILD    := sim/build
FW_DIR       := firmware
FW_BUILD     := $(FW_DIR)/build
FW_TESTS     := $(FW_DIR)/tests
TOOLS_DIR    := tools

BIN2HEX_PY   := $(TOOLS_DIR)/bin2hex.py
HEX2CHDR_PY  := $(TOOLS_DIR)/hex_to_c_header.py
FW_GEN_DIR   := $(FW_DIR)/build/generated
FW_ML_W_HDR  := $(FW_GEN_DIR)/ml_weights_full.h

# Ensure output dirs exist
$(SIM_BUILD) $(FW_BUILD) $(FW_GEN_DIR):
	@mkdir -p $@

# ----------------------------
# Common RTL sources for SoC
# ----------------------------
SOC_RTL_SRCS := \
  $(RTL_DIR)/soc_top.v \
  $(RTL_DIR)/simple_sram.v \
  $(RTL_DIR)/third_party/picorv32.v \
  $(RTL_DIR)/gpio_mmio.v \
  $(RTL_DIR)/test_mmio.v \
  $(RTL_DIR)/timer_mmio.v \
  $(RTL_DIR)/ml_stub_mmio.v \
  $(RTL_DIR)/ml_axil_bridge_mmio.v \
  $(RTL_DIR)/weight_ram_axi.v \
  $(RTL_DIR)/irq_ctrl_mmio.v \
  $(RTL_DIR)/taketwo_wrap.v \
  $(RTL_DIR)/taketwo.v \
  $(RTL_DIR)/pwrctrl_mmio.v \
  $(RTL_DIR)/host_i2c_target.v \
  $(RTL_DIR)/host_i2c_bridge_regs.v

SOC_TB_SRCS  := $(TB_DIR)/tb_soc.sv
SOC_VVP      := sim_soc.vvp
IRQ_TB_SRCS  := $(TB_DIR)/tb_irq.sv
IRQ_VVP      := sim_irq.vvp

# ----------------------------
# Cocotb configuration helper
# ----------------------------
# cocotb's Icarus VPI shared library directory:
COCOTB_LIBDIR := $(shell $(PYTHON) -c "import cocotb, os; print(os.path.join(os.path.dirname(cocotb.__file__), 'libs'))")

# Use the same python interpreter cocotb will embed
export PYGPI_PYTHON_BIN := $(shell $(PYTHON) -c "import sys; print(sys.executable)")

# Make sure cocotb can import your tests
export PYTHONPATH := $(abspath $(TB_DIR))

define RUN_COCOTB_ICARUS
	$(VVP) -M "$(COCOTB_LIBDIR)" -m libcocotbvpi_icarus $1
endef

# ----------------------------
# Firmware build rules (per-variant output dirs)
# ----------------------------
# Produces:
#   firmware/build/<variant>/firmware.{elf,bin,hex}
#
# Variants:
#   main
#   test_sleepwake
#   test_gpio
#   test_sleepwake_periodic

FW_VARIANT ?= test_sleepwake

# Variant sources
FW_C_main                  := $(FW_DIR)/main.c
FW_C_test_sleepwake         := $(FW_TESTS)/test_sleepwake.c
FW_C_test_gpio              := $(FW_TESTS)/test_gpio.c
FW_C_test_sleepwake_periodic:= $(FW_TESTS)/test_sleepwake_periodic.c
FW_C_test_ml_weights        := $(FW_TESTS)/test_ml_weights.c
FW_C_test_ml_cpu_wake_i2c   := $(FW_TESTS)/test_ml_cpu_wake_i2c.c

# Select the C source based on FW_VARIANT
FW_SRC = $(FW_C_$(FW_VARIANT))
FW_LDSCRIPT_DEFAULT := $(FW_DIR)/linker.ld
FW_LDSCRIPT_test_ml_cpu_wake_i2c := $(FW_DIR)/linker_32k.ld
FW_LDSCRIPT := $(if $(FW_LDSCRIPT_$(FW_VARIANT)),$(FW_LDSCRIPT_$(FW_VARIANT)),$(FW_LDSCRIPT_DEFAULT))
FW_EXTRA_DEPS_test_ml_cpu_wake_i2c := $(FW_ML_W_HDR)
FW_EXTRA_DEPS := $(FW_EXTRA_DEPS_$(FW_VARIANT))
FW_ARCH_DEFAULT := rv32imc
FW_ARCH_test_ml_weights := rv32im
FW_ARCH_test_ml_cpu_wake_i2c := rv32im
FW_ARCH := $(if $(FW_ARCH_$(FW_VARIANT)),$(FW_ARCH_$(FW_VARIANT)),$(FW_ARCH_DEFAULT))
FW_OPT_DEFAULT := -O2
FW_OPT_test_ml_cpu_wake_i2c := -O0
FW_OPT := $(if $(FW_OPT_$(FW_VARIANT)),$(FW_OPT_$(FW_VARIANT)),$(FW_OPT_DEFAULT))

# Per-variant output paths
FW_OUTDIR := $(FW_DIR)/build/$(FW_VARIANT)
FW_ELF    := $(FW_OUTDIR)/firmware.elf
FW_BIN    := $(FW_OUTDIR)/firmware.bin
FW_HEX    := $(FW_OUTDIR)/firmware.hex
FW_HEX_MAIN := $(FW_DIR)/build/main/firmware.hex

$(FW_ML_W_HDR): $(RTL_DIR)/taketwo_params.hex $(HEX2CHDR_PY) | $(FW_GEN_DIR)
	@echo "[FW] Generating full-weight header: $@"
	@$(PYTHON) $(HEX2CHDR_PY) $< $@ ml_weights_full

# Build rule
$(FW_HEX): $(FW_DIR)/start.S $(FW_LDSCRIPT) $(FW_SRC) $(BIN2HEX_PY) $(FW_EXTRA_DEPS)
	@mkdir -p $(FW_OUTDIR)
	@echo "[FW] Building $(FW_SRC) -> $(FW_HEX) (LD=$(FW_LDSCRIPT))"
	$(RISCV_GCC) \
	  -march=$(FW_ARCH) -mabi=ilp32 \
	  -nostdlib -ffreestanding $(FW_OPT) \
	  -I$(FW_GEN_DIR) \
	  -Wl,-T,$(FW_LDSCRIPT) \
	  -o $(FW_ELF) \
	  $(FW_DIR)/start.S \
	  $(FW_SRC)
	$(RISCV_OBJCOPY) -O binary $(FW_ELF) $(FW_BIN)
	@echo "[FW] Converting $(FW_BIN) -> $(FW_HEX) (32-bit little-endian words)"
	@$(PYTHON) $(BIN2HEX_PY) $(FW_BIN) $(FW_HEX)

.PHONY: firmware firmware-main firmware-sleepwake firmware-gpio firmware-sleepwake-periodic

# Generic "firmware" builds whatever FW_VARIANT is set to
firmware: $(FW_HEX)

firmware-main:
	@$(MAKE) FW_VARIANT=main firmware

firmware-sleepwake:
	@$(MAKE) FW_VARIANT=test_sleepwake firmware

firmware-gpio:
	@$(MAKE) FW_VARIANT=test_gpio firmware

firmware-sleepwake-periodic:
	@$(MAKE) FW_VARIANT=test_sleepwake_periodic firmware

firmware-ml-weights:
	@$(MAKE) FW_VARIANT=test_ml_weights firmware

firmware-ml-cpu-wake-i2c:
	@$(MAKE) FW_VARIANT=test_ml_cpu_wake_i2c firmware



# ----------------------------
# SoC simulation (SystemVerilog tb)
# ----------------------------
.PHONY: build-soc sim-soc
build-soc: $(SOC_VVP)

WEIGHT_INIT_HEX   ?=
CHECK_SLEEP_WAKE  ?= 1

$(SOC_VVP): $(SOC_TB_SRCS) $(SOC_RTL_SRCS)
	@echo "[SIM] Building $@ (FW=$(FW_HEX))"
	$(IVERILOG) -g2012 -s tb_soc -o $@ \
	  -P tb_soc.FW=\"$(FW_HEX)\" \
	  $(if $(WEIGHT_INIT_HEX),-P tb_soc.WEIGHT_INIT_HEX=\"$(WEIGHT_INIT_HEX)\") \
	  -P tb_soc.CHECK_SLEEP_WAKE=$(CHECK_SLEEP_WAKE) \
	  $(SOC_TB_SRCS) \
	  $(SOC_RTL_SRCS)

# Run tb_soc. Uses FW_VARIANT to choose which firmware hex is built/loaded.
# Example:
#   make sim-soc FW_VARIANT=test_gpio
#   make sim-soc FW_VARIANT=test_sleepwake_periodic
#   make sim-soc FW_VARIANT=test_ml_weights WEIGHT_INIT_HEX=rtl/taketwo_params.hex
sim-soc: $(SOC_VVP) firmware | $(SIM_BUILD)
	@echo "[SIM] Running tb_soc (FW=$(FW_HEX))"
	$(VVP) $(SOC_VVP)

# Convenience: build + run ML weights inference test
.PHONY: sim-ml-weights
sim-ml-weights:
	@$(MAKE) FW_VARIANT=test_ml_weights \
	         WEIGHT_INIT_HEX=rtl/taketwo_params.hex \
	         CHECK_SLEEP_WAKE=0 \
	         sim-soc

# End-to-end ML + CPU sleep/wake + host-I2C wake integration
SOC_ML_CPU_WAKE_I2C_TOP     := tb_soc_ml_cpu_wake_i2c
SOC_ML_CPU_WAKE_I2C_VVP     := $(BUILD_DIR)/$(SOC_ML_CPU_WAKE_I2C_TOP).vvp
SOC_ML_CPU_WAKE_I2C_SOURCES := $(TB_DIR)/tb_soc_ml_cpu_wake_i2c.sv \
                               $(SOC_RTL_SRCS)

$(SOC_ML_CPU_WAKE_I2C_VVP): $(SOC_ML_CPU_WAKE_I2C_SOURCES)
	$(IVERILOG) -g2012 -s $(SOC_ML_CPU_WAKE_I2C_TOP) -o $@ \
	  -P $(SOC_ML_CPU_WAKE_I2C_TOP).FW=\"$(FW_DIR)/build/test_ml_cpu_wake_i2c/firmware.hex\" \
	  $(SOC_ML_CPU_WAKE_I2C_SOURCES)

.PHONY: sim-ml-cpu-wake-i2c
sim-ml-cpu-wake-i2c: $(SOC_ML_CPU_WAKE_I2C_VVP) | $(SIM_BUILD)
	@$(MAKE) FW_VARIANT=test_ml_cpu_wake_i2c firmware
	@echo "== Running $(SOC_ML_CPU_WAKE_I2C_TOP) (FW=$(FW_DIR)/build/test_ml_cpu_wake_i2c/firmware.hex) =="
	$(VVP) $(SOC_ML_CPU_WAKE_I2C_VVP)

# CPU->weight SRAM load + AXI-Lite control + AXI lifecycle proof
SOC_ML_WEIGHT_LOAD_TOP     := tb_soc_ml_weight_load
SOC_ML_WEIGHT_LOAD_VVP     := $(BUILD_DIR)/$(SOC_ML_WEIGHT_LOAD_TOP).vvp
SOC_ML_WEIGHT_LOAD_SOURCES := $(TB_DIR)/tb_soc_ml_weight_load.sv \
                              $(SOC_RTL_SRCS)

$(SOC_ML_WEIGHT_LOAD_VVP): $(SOC_ML_WEIGHT_LOAD_SOURCES)
	$(IVERILOG) -g2012 -s $(SOC_ML_WEIGHT_LOAD_TOP) -o $@ \
	  -P $(SOC_ML_WEIGHT_LOAD_TOP).FW=\"$(FW_DIR)/build/test_ml_weights/firmware.hex\" \
	  $(SOC_ML_WEIGHT_LOAD_SOURCES)

.PHONY: sim-ml-weight-load
sim-ml-weight-load: $(SOC_ML_WEIGHT_LOAD_VVP) | $(SIM_BUILD)
	@$(MAKE) FW_VARIANT=test_ml_weights firmware
	@echo "== Running $(SOC_ML_WEIGHT_LOAD_TOP) (FW=$(FW_DIR)/build/test_ml_weights/firmware.hex) =="
	$(VVP) $(SOC_ML_WEIGHT_LOAD_VVP)

.PHONY: test-cpu-ml-pipeline
test-cpu-ml-pipeline:
	@$(MAKE) test-cpu-ml
	@$(MAKE) sim-ml-weight-load

.PHONY: test-soc-wake-e2e-p0
test-soc-wake-e2e-p0:
	@$(MAKE) test-cpu-ml
	@$(MAKE) sim-ml-weight-load
	@$(MAKE) sim-ml-cpu-wake-i2c
	@$(MAKE) test-host-i2c-bridge
	@$(MAKE) test-irq-ctrl-races

.PHONY: test-functional-matrix
test-functional-matrix:
	@bash tools/test_functionality_matrix.sh
# ----------------------------
# IRQ testbench (tb_irq)
# ----------------------------
.PHONY: build-irq sim-irq
build-irq: $(IRQ_VVP)

$(IRQ_VVP): $(IRQ_TB_SRCS) $(SOC_RTL_SRCS)
	@echo "[SIM] Building $@"
	$(IVERILOG) -g2012 -s tb_irq -o $@ \
	  $(IRQ_TB_SRCS) \
	  $(SOC_RTL_SRCS)

sim-irq: $(IRQ_VVP) firmware-main | $(SIM_BUILD)
	@echo "[SIM] Running tb_irq (will read $(FW_HEX_MAIN))"
	$(VVP) $(IRQ_VVP)

# ----------------------------
# Cocotb: test_mmio
# ----------------------------
MMIO_TOP     := sim_test_mmio
MMIO_TOP_V   := $(TB_DIR)/sim_test_mmio.v
MMIO_DUT_V   := $(RTL_DIR)/test_mmio.v
MMIO_VVP     := sim_test_mmio.vvp
MMIO_PYMOD   := test_test_mmio

$(MMIO_VVP): $(MMIO_TOP_V) $(MMIO_DUT_V)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ \
	  $(MMIO_TOP_V) \
	  $(MMIO_DUT_V)

.PHONY: test-mmio
test-mmio: $(MMIO_VVP)
	@echo "[COCOTB] Running $(MMIO_PYMOD) on $(MMIO_TOP)"
	@export COCOTB_TOPLEVEL=$(MMIO_TOP); \
	export COCOTB_TEST_MODULES=$(MMIO_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(MMIO_VVP))

# ----------------------------
# Cocotb: timer_mmio
# ----------------------------
TIMER_TOP    := sim_test_timer_mmio
TIMER_TOP_V  := $(TB_DIR)/sim_test_timer_mmio.v
TIMER_DUT_V  := $(RTL_DIR)/timer_mmio.v
TIMER_VVP    := sim_test_timer_mmio.vvp

# Set this to your actual python module name (without .py)
# Example: if file is sim/tb/test_timer_mmio.py -> TIMER_PYMOD := test_timer_mmio
TIMER_PYMOD  ?= test_timer_mmio

$(TIMER_VVP): $(TIMER_TOP_V) $(TIMER_DUT_V)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ \
	  $(TIMER_TOP_V) \
	  $(TIMER_DUT_V)

.PHONY: test-timer
test-timer: $(TIMER_VVP)
	@echo "== Running test-timer =="
	COCOTB_TOPLEVEL=$(TIMER_TOP) \
	COCOTB_TEST_MODULES=$(TIMER_PYMOD) \
	$(VVP) -M "$(COCOTB_LIBDIR)" -m libcocotbvpi_icarus $(TIMER_VVP)

# ============================================================
# Cocotb: cpu_to_ml (AXI-Lite bridge + taketwo_wrap)
# ============================================================

CPU_ML_TOP    := sim_cpu_to_ml
CPU_ML_TOP_V  := $(TB_DIR)/sim_cpu_to_ml.v
CPU_ML_VVP    := sim_cpu_to_ml.vvp
CPU_ML_PYMOD  := cpu_to_ml_tb

CPU_ML_RTL_SRCS := \
  $(RTL_DIR)/cpu_to_ml.v \
  $(RTL_DIR)/ml_axil_bridge_mmio.v \
  $(RTL_DIR)/taketwo_wrap.v \
  $(RTL_DIR)/taketwo.v

$(CPU_ML_VVP): $(CPU_ML_TOP_V) $(CPU_ML_RTL_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ \
	  $(CPU_ML_TOP_V) \
	  $(CPU_ML_RTL_SRCS)

.PHONY: test-cpu-ml
test-cpu-ml: $(CPU_ML_VVP)
	@echo "[COCOTB] Running strict IRQ contract tests on $(CPU_ML_TOP)"
	@export COCOTB_TOPLEVEL=$(CPU_ML_TOP); \
	export COCOTB_TEST_MODULES=$(CPU_ML_PYMOD); \
	export COCOTB_TEST_FILTER='test_strict_irq_.*'; \
	$(call RUN_COCOTB_ICARUS,$(CPU_ML_VVP))

.PHONY: test-cpu-ml-strict-irq
test-cpu-ml-strict-irq: test-cpu-ml

# ============================================================
# Cocotb: host_i2c_bridge_regs contract
# ============================================================

HOST_BRIDGE_TOP    := sim_host_i2c_bridge_regs
HOST_BRIDGE_TOP_V  := $(TB_DIR)/sim_host_i2c_bridge_regs.v
HOST_BRIDGE_VVP    := sim_host_i2c_bridge_regs.vvp
HOST_BRIDGE_PYMOD  := test_host_i2c_bridge_regs

HOST_BRIDGE_RTL_SRCS := \
  $(RTL_DIR)/host_i2c_bridge_regs.v

$(HOST_BRIDGE_VVP): $(HOST_BRIDGE_TOP_V) $(HOST_BRIDGE_RTL_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ \
	  $(HOST_BRIDGE_TOP_V) \
	  $(HOST_BRIDGE_RTL_SRCS)

.PHONY: test-host-i2c-bridge
test-host-i2c-bridge: $(HOST_BRIDGE_VVP)
	@echo "[COCOTB] Running $(HOST_BRIDGE_PYMOD) on $(HOST_BRIDGE_TOP)"
	@export COCOTB_TOPLEVEL=$(HOST_BRIDGE_TOP); \
	export COCOTB_TEST_MODULES=$(HOST_BRIDGE_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(HOST_BRIDGE_VVP))

# ============================================================
# Cocotb: irq_ctrl_mmio race and sideband behavior
# ============================================================

IRQ_CTRL_TOP    := sim_irq_ctrl_mmio
IRQ_CTRL_TOP_V  := $(TB_DIR)/sim_irq_ctrl_mmio.v
IRQ_CTRL_VVP    := sim_irq_ctrl_mmio.vvp
IRQ_CTRL_PYMOD  := test_irq_ctrl_mmio

IRQ_CTRL_RTL_SRCS := \
  $(RTL_DIR)/irq_ctrl_mmio.v

$(IRQ_CTRL_VVP): $(IRQ_CTRL_TOP_V) $(IRQ_CTRL_RTL_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ \
	  $(IRQ_CTRL_TOP_V) \
	  $(IRQ_CTRL_RTL_SRCS)

.PHONY: test-irq-ctrl-races
test-irq-ctrl-races: $(IRQ_CTRL_VVP)
	@echo "[COCOTB] Running $(IRQ_CTRL_PYMOD) on $(IRQ_CTRL_TOP)"
	@export COCOTB_TOPLEVEL=$(IRQ_CTRL_TOP); \
	export COCOTB_TEST_MODULES=$(IRQ_CTRL_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(IRQ_CTRL_VVP))
# ============================================================
# Cocotb: ML test 
# ============================================================

.PHONY: test-ml
test-ml:
	$(MAKE) -C sim/tb/ml

# ============================================================
# RESET CONTROLLER TB (reset_ctrl_tb)
# ============================================================

RESET_CTRL_TOP     := reset_ctrl_tb
RESET_CTRL_VVP     := $(BUILD_DIR)/$(RESET_CTRL_TOP).vvp
RESET_CTRL_SOURCES := sim/tb/reset_ctrl_tb.sv rtl/reset_ctrl.v
RESET_CTRL_VCD     := $(WAVE_DIR)/reset_ctrl.vcd

$(RESET_CTRL_VVP): $(RESET_CTRL_SOURCES) | $(BUILD_DIR)
	@echo "[SIM] Building $@"
	$(IVERILOG) -g2012 -Wall -o $@ $^

.PHONY: sim-reset-ctrl
sim-reset-ctrl: $(RESET_CTRL_VVP)
	@echo "== Running $(RESET_CTRL_TOP) (VCD -> $(RESET_CTRL_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(RESET_CTRL_VVP))

.PHONY: clean-reset-ctrl
clean-reset-ctrl:
	rm -f $(RESET_CTRL_VVP) $(RESET_CTRL_VCD)
# ============================================================
# MOTION PREPROCESS
# ============================================================

MOTION_PREPROCESS_TOP     := motion_preprocess_tb
MOTION_PREPROCESS_VVP     := $(BUILD_DIR)/$(MOTION_PREPROCESS_TOP).vvp
MOTION_PREPROCESS_SOURCES := sim/tb/motion_preprocess_tb.sv rtl/sensor_processing/motion_preprocess.sv
MOTION_PREPROCESS_VCD     := $(WAVE_DIR)/motion_preprocess_tb.vcd

$(MOTION_PREPROCESS_VVP): $(MOTION_PREPROCESS_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-motion-preprocess
sim-motion-preprocess: $(MOTION_PREPROCESS_VVP)
	@echo "== Running $(MOTION_PREPROCESS_TOP) (VCD -> $(MOTION_PREPROCESS_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(MOTION_PREPROCESS_VVP))

# ============================================================
# PPG FIFO READER
# ============================================================

PPG_FIFO_READER_TOP     := ppg_fifo_reader_tb
PPG_FIFO_READER_VVP     := $(BUILD_DIR)/$(PPG_FIFO_READER_TOP).vvp
PPG_FIFO_READER_SOURCES := sim/tb/ppg_fifo_reader_tb.sv rtl/sensor_processing/ppg_fifo_reader.sv
PPG_FIFO_READER_VCD     := $(WAVE_DIR)/ppg_fifo_reader_tb.vcd

$(PPG_FIFO_READER_VVP): $(PPG_FIFO_READER_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-ppg-fifo-reader
sim-ppg-fifo-reader: $(PPG_FIFO_READER_VVP)
	@echo "== Running $(PPG_FIFO_READER_TOP) (VCD -> $(PPG_FIFO_READER_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(PPG_FIFO_READER_VVP))

# ============================================================
# PPG BEAT DETECT + RR CALC
# ============================================================

PPG_BEAT_RR_TOP     := ppg_beat_detect_rr_calc_tb
PPG_BEAT_RR_VVP     := $(BUILD_DIR)/$(PPG_BEAT_RR_TOP).vvp
PPG_BEAT_RR_SOURCES := sim/tb/ppg_beat_detect_rr_calc_tb.sv rtl/sensor_processing/ppg_beat_detect_rr_calc.sv rtl/sensor_processing/ewma_baseline.sv
PPG_BEAT_RR_VCD     := $(WAVE_DIR)/ppg_beat_detect_rr_calc_tb.vcd

$(PPG_BEAT_RR_VVP): $(PPG_BEAT_RR_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-ppg-beat-rr
sim-ppg-beat-rr: $(PPG_BEAT_RR_VVP)
	@echo "== Running $(PPG_BEAT_RR_TOP) (VCD -> $(PPG_BEAT_RR_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(PPG_BEAT_RR_VVP))

# ============================================================
# ACCEL READER
# ============================================================

ACCEL_READER_TOP     := accel_reader_tb
ACCEL_READER_VVP     := $(BUILD_DIR)/$(ACCEL_READER_TOP).vvp
ACCEL_READER_SOURCES := sim/tb/accel_reader_tb.sv rtl/sensor_processing/accel_reader.sv
ACCEL_READER_VCD     := $(WAVE_DIR)/accel_reader_tb.vcd

$(ACCEL_READER_VVP): $(ACCEL_READER_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-accel-reader
sim-accel-reader: $(ACCEL_READER_VVP)
	@echo "== Running $(ACCEL_READER_TOP) (VCD -> $(ACCEL_READER_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(ACCEL_READER_VVP))

# ============================================================
# RMSSD ENGINE
# ============================================================

RMSSD_ENGINE_TOP     := rmssd_engine_tb
RMSSD_ENGINE_VVP     := $(BUILD_DIR)/$(RMSSD_ENGINE_TOP).vvp
RMSSD_ENGINE_SOURCES := sim/tb/rmssd_engine_tb.sv rtl/sensor_processing/rmssd_engine.sv rtl/sensor_processing/ewma_baseline.sv
RMSSD_ENGINE_VCD     := $(WAVE_DIR)/rmssd_engine_tb.vcd

$(RMSSD_ENGINE_VVP): $(RMSSD_ENGINE_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-rmssd-engine
sim-rmssd-engine: $(RMSSD_ENGINE_VVP)
	@echo "== Running $(RMSSD_ENGINE_TOP) (VCD -> $(RMSSD_ENGINE_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(RMSSD_ENGINE_VVP))

# ============================================================
# SIGNAL QUALITY
# ============================================================

SIGNAL_QUALITY_TOP     := signal_quality_tb
SIGNAL_QUALITY_VVP     := $(BUILD_DIR)/$(SIGNAL_QUALITY_TOP).vvp
SIGNAL_QUALITY_SOURCES := sim/tb/signal_quality_tb.sv rtl/sensor_processing/signal_quality.sv
SIGNAL_QUALITY_VCD     := $(WAVE_DIR)/signal_quality_tb.vcd

$(SIGNAL_QUALITY_VVP): $(SIGNAL_QUALITY_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-signal-quality
sim-signal-quality: $(SIGNAL_QUALITY_VVP)
	@echo "== Running $(SIGNAL_QUALITY_TOP) (VCD -> $(SIGNAL_QUALITY_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(SIGNAL_QUALITY_VVP))

# ============================================================
# COS LUT TIMER
# ============================================================

COS_LUT_TIMER_TOP     := cos_lut_timer_tb
COS_LUT_TIMER_VVP     := $(BUILD_DIR)/$(COS_LUT_TIMER_TOP).vvp
COS_LUT_TIMER_SOURCES := sim/tb/cos_lut_timer_tb.sv rtl/cos_lut_timer.sv
COS_LUT_TIMER_VCD     := $(WAVE_DIR)/cos_lut_timer_tb.vcd

$(COS_LUT_TIMER_VVP): $(COS_LUT_TIMER_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-cos-lut-timer
sim-cos-lut-timer: $(COS_LUT_TIMER_VVP)
	@echo "== Running $(COS_LUT_TIMER_TOP) (VCD -> $(COS_LUT_TIMER_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(COS_LUT_TIMER_VVP))

# ============================================================
# TOP SENSOR PIPELINE
# ============================================================

TOP_PIPELINE_TOP     := top_pipeline_tb
TOP_PIPELINE_VVP     := $(BUILD_DIR)/$(TOP_PIPELINE_TOP).vvp
TOP_PIPELINE_SOURCES := sim/tb/top_pipeline_tb.sv \
                        rtl/top.sv \
                        rtl/i2c_master.sv \
                        rtl/accel_reader.sv \
                        rtl/motion_preprocess.sv \
                        rtl/ppg_fifo_reader.sv \
                        rtl/ppg_beat_detect_rr_calc.sv \
                        rtl/rmssd_engine.sv \
                        rtl/signal_quality.sv \
                        rtl/feature_engine.sv \
                        rtl/cos_lut_timer.sv \
                        rtl/globaltimer.sv \
                        sim/sensors/i2c_slave_lis2dw12.sv \
                        sim/sensors/i2c_slave_adpd144ri.sv
TOP_PIPELINE_VCD     := $(WAVE_DIR)/top_pipeline_tb.vcd

$(TOP_PIPELINE_VVP): $(TOP_PIPELINE_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-top-pipeline
sim-top-pipeline: $(TOP_PIPELINE_VVP)
	@echo "== Running $(TOP_PIPELINE_TOP) (VCD -> $(TOP_PIPELINE_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(TOP_PIPELINE_VVP))


# ============================================================
# HOST I2C TARGET
# ============================================================

HOST_I2C_TARGET_TOP     := tb_host_i2c_target
HOST_I2C_TARGET_VVP     := $(BUILD_DIR)/$(HOST_I2C_TARGET_TOP).vvp
HOST_I2C_TARGET_SOURCES := sim/tb/tb_host_i2c_target.sv \
                           rtl/host_i2c_target.v \
                           rtl/host_i2c_bridge_regs.v

$(HOST_I2C_TARGET_VVP): $(HOST_I2C_TARGET_SOURCES)
	$(IVERILOG) -g2012 -s $(HOST_I2C_TARGET_TOP) -o $@ $^

.PHONY: sim-host-i2c-target
sim-host-i2c-target: $(HOST_I2C_TARGET_VVP)
	@echo "== Running $(HOST_I2C_TARGET_TOP) =="
	$(VVP) $(HOST_I2C_TARGET_VVP)

# ============================================================
# SOC HOST I2C IRQ
# ============================================================

SOC_I2C_IRQ_TOP     := tb_soc_host_i2c_irq
SOC_I2C_IRQ_VVP     := $(BUILD_DIR)/$(SOC_I2C_IRQ_TOP).vvp
SOC_I2C_IRQ_SOURCES := sim/tb/tb_soc_host_i2c_irq.sv \
                       $(SOC_RTL_SRCS)

$(SOC_I2C_IRQ_VVP): $(SOC_I2C_IRQ_SOURCES)
	$(IVERILOG) -g2012 -s $(SOC_I2C_IRQ_TOP) -o $@ $^

.PHONY: sim-soc-host-i2c-irq
sim-soc-host-i2c-irq: $(SOC_I2C_IRQ_VVP)
	@echo "== Running $(SOC_I2C_IRQ_TOP) =="
	$(VVP) $(SOC_I2C_IRQ_VVP)

# ============================================================
# HOST I2C IRQC PROXY (SOC integration)
# ============================================================

HOST_I2C_IRQC_PROXY_TOP     := tb_host_i2c_irqc_proxy
HOST_I2C_IRQC_PROXY_VVP     := $(BUILD_DIR)/$(HOST_I2C_IRQC_PROXY_TOP).vvp
HOST_I2C_IRQC_PROXY_SOURCES := rtl/tb_host_i2c_irqc_proxy.sv \
                               $(SOC_RTL_SRCS)

$(HOST_I2C_IRQC_PROXY_VVP): $(HOST_I2C_IRQC_PROXY_SOURCES)
	$(IVERILOG) -g2012 -s $(HOST_I2C_IRQC_PROXY_TOP) -o $@ $^

.PHONY: sim-host-i2c-irqc-proxy
sim-host-i2c-irqc-proxy: $(HOST_I2C_IRQC_PROXY_VVP)
	@echo "== Running $(HOST_I2C_IRQC_PROXY_TOP) =="
	$(VVP) $(HOST_I2C_IRQC_PROXY_VVP)

# ============================================================
# GLOBAL TIMER
# ============================================================

GLOBALTIMER_TOP     := globaltimer_tb
GLOBALTIMER_VVP     := $(BUILD_DIR)/$(GLOBALTIMER_TOP).vvp
GLOBALTIMER_SOURCES := sim/tb/globaltimer_tb.sv rtl/globaltimer.sv
GLOBALTIMER_VCD     := $(WAVE_DIR)/globaltimer_tb.vcd

$(GLOBALTIMER_VVP): $(GLOBALTIMER_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-globaltimer
sim-globaltimer: $(GLOBALTIMER_VVP)
	@echo "== Running $(GLOBALTIMER_TOP) (VCD -> $(GLOBALTIMER_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(GLOBALTIMER_VVP))

# ============================================================
# LOGIT TO CONFIDENCE
# ============================================================

LOGIT_TO_CONF_TOP     := logit_to_confidence_tb
LOGIT_TO_CONF_VVP     := $(BUILD_DIR)/$(LOGIT_TO_CONF_TOP).vvp
LOGIT_TO_CONF_SOURCES := sim/tb/logit_to_confidence_tb.sv rtl/logit_to_confidence.sv
LOGIT_TO_CONF_VCD     := $(WAVE_DIR)/logit_to_confidence_tb.vcd

$(LOGIT_TO_CONF_VVP): $(LOGIT_TO_CONF_SOURCES)
	$(IVERILOG) -g2012 -s $(LOGIT_TO_CONF_TOP) -o $@ $^

.PHONY: sim-logit-confidence
sim-logit-confidence: $(LOGIT_TO_CONF_VVP)
	@echo "== Running $(LOGIT_TO_CONF_TOP) (VCD -> $(LOGIT_TO_CONF_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(LOGIT_TO_CONF_VVP))

# ============================================================
# Cocotb: weight_ram_axi placement test
# ============================================================

WPLACEMENT_TOP_V  := $(TB_DIR)/sim_weight_placement.v
WPLACEMENT_VVP    := sim_weight_placement.vvp
WPLACEMENT_PYMOD  := test_weight_placement

$(WPLACEMENT_VVP): $(WPLACEMENT_TOP_V) $(RTL_DIR)/weight_ram_axi.v
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ $(WPLACEMENT_TOP_V) $(RTL_DIR)/weight_ram_axi.v

.PHONY: test-weight-placement
test-weight-placement: $(WPLACEMENT_VVP)
	@echo "[COCOTB] Running $(WPLACEMENT_PYMOD) on sim_weight_placement"
	@export COCOTB_TOPLEVEL=sim_weight_placement; \
	export COCOTB_TEST_MODULES=$(WPLACEMENT_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(WPLACEMENT_VVP))

# ============================================================
# ML LOGIT SRAM MMIO (compile/elab check)
# ============================================================

ML_LOGIT_SRAM_MMIO_TOP     := ml_logit_sram_mmio
ML_LOGIT_SRAM_MMIO_VVP     := $(BUILD_DIR)/$(ML_LOGIT_SRAM_MMIO_TOP).vvp
ML_LOGIT_SRAM_MMIO_SOURCES := rtl/ml_logit_sram_mmio.v

$(ML_LOGIT_SRAM_MMIO_VVP): $(ML_LOGIT_SRAM_MMIO_SOURCES) | $(BUILD_DIR)
	$(IVERILOG) -g2012 -s $(ML_LOGIT_SRAM_MMIO_TOP) -o $@ $^

.PHONY: check-ml-logit-sram-mmio
check-ml-logit-sram-mmio: $(ML_LOGIT_SRAM_MMIO_VVP)
	@echo "== Built $(ML_LOGIT_SRAM_MMIO_VVP) =="

# ============================================================
# SENSOR PIPELINE (i2c_master + slave models + tb_sensor_pipeline)
# ============================================================

SENSOR_PIPELINE_TOP     := tb_sensor_pipeline
SENSOR_PIPELINE_VVP     := $(BUILD_DIR)/$(SENSOR_PIPELINE_TOP).vvp
SENSOR_PIPELINE_SOURCES := sim/tb/tb_sensor_pipeline.sv \
                           rtl/i2c_master.sv \
                           rtl/accel_reader.sv \
                           rtl/ppg_fifo_reader.sv \
                           rtl/motion_preprocess.sv \
                           rtl/globaltimer.sv \
                           sim/sensors/i2c_slave_lis2dw12.sv \
                           sim/sensors/i2c_slave_adpd144ri.sv
SENSOR_PIPELINE_VCD     := $(WAVE_DIR)/sensor_pipeline.vcd

$(SENSOR_PIPELINE_VVP): $(SENSOR_PIPELINE_SOURCES) | $(BUILD_DIR)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-sensor-pipeline
sim-sensor-pipeline: $(SENSOR_PIPELINE_VVP)
	$(VVP) $(SENSOR_PIPELINE_VVP)
	
# ============================================================
# Cleanup
# ============================================================

.PHONY: clean
clean:
	rm -f sim/build/*.vvp
	rm -f *.vcd
	rm -f sim/waves/*.vcd
	@echo "[COCOTB] Running $(TIMER_PYMOD) on $(TIMER_TOP)"
	@export COCOTB_TOPLEVEL=$(TIMER_TOP); \
	export COCOTB_TEST_MODULES=$(TIMER_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(TIMER_VVP))

# ----------------------------
# Convenience
# ----------------------------
.PHONY: test
test: test-mmio test-timer

.PHONY: show-tree
show-tree:
	@echo "PYTHON=$(PYTHON)"
	@echo "IVERILOG=$(IVERILOG)"
	@echo "VVP=$(VVP)"
	@echo "RISCV_GCC=$(RISCV_GCC)"
	@echo "FW_SRC=$(FW_SRC)"
	@echo "TIMER_PYMOD=$(TIMER_PYMOD)"
	@echo "BIN2HEX_PY=$(BIN2HEX_PY)"

# ----------------------------
# Clean
# ----------------------------
.PHONY: clean
clean:
	rm -f *.vvp *.vcd results.xml
	rm -rf $(SIM_BUILD)/*.vcd $(SIM_BUILD)/*.fst $(SIM_BUILD)/*.gtkw
	rm -f $(FW_BUILD)/firmware.elf $(FW_BUILD)/firmware.bin $(FW_BUILD)/firmware.hex
