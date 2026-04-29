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
#   # Standalone SV testbenches
#   make sim-reset-ctrl
#   make sim-globaltimer              # epoch/timebase generator smoke test
#
#   # Cocotb unit tests (simple_sram_tb.py wrapper)
#   make test-simple-sram
#   make sim-logit-confidence
#   make test-ml-canonical-v1
#   make sim-top-feature-ml-cpu
#   make sim-top-feature-ml-cpu-spi-flash
#   make sim-top-spi-init-unified
#   make sim-top-ml-control-unified
#   make sim-top-feature-ml-prod-main-host-i2c
#   make sim-top-sleep-wake-unified
#   make test-top-unified-reset-init
#   make test-top-unified-runtime
#   make test-top-unified-host-i2c
#   make test-top-unified-prod-loop
#   make test-top-unified-forced-wake-irq
#   make test-top-ml-golden-vector-unified
#
#   # Cleanup
#   make clean
#
# Unified top command guide:
#   make test-top-feature-mmio-unified
#     Sensor pipeline -> feature MMIO latch proof for unified top.sv.
#
#   make sim-top-feature-ml-cpu
#     CPU reads feature MMIO, writes weight_ram_axi, and starts ML.
#
#   make sim-top-feature-ml-cpu-spi-flash
#     Same CPU-owned ML path, but with weights streamed from simulated SPI flash.
#
#   make sim-top-spi-init-unified
#     Short SPI-only boot-copy proof for unified top.sv.
#
#   make sim-top-ml-control-unified
#     Short ML-control-only proof for unified top.sv.
#
#   make test-top-ml-golden-vector-unified
#     Python/cocotb unified-top golden-vector check importing golden_vectors.py.
#
#   make test-top-unified-reset-init
#     Shared cocotb wrapper smoke test for unified top.sv reset/init state.
#
#   make test-top-unified-runtime
#     Shared cocotb runtime checks for host-I2C, repeated prod loop, and forced wake/IRQ corners.
#   make test-top-unified-host-i2c
#     Shared cocotb host-I2C register/score visibility check.
#   make test-top-unified-prod-loop
#     Shared cocotb repeated production-loop smoke check.
#   make test-top-unified-forced-wake-irq
#     Shared cocotb forced wake/IRQ reset-corner check.
#
#   make sim-top-feature-ml-prod-main-host-i2c
#     Most production-like unified-top flow: SPI load + ML loop + host-I2C visibility.
#
#   make sim-top-sleep-wake-unified
#     Repeated timer-wake + ML-IRQ-wake regression for unified top.sv.
#
#   make sim-top-spi-boot
#   make sim-top-spi-weights
#
# NOTE:
#   This Makefile expects a small helper script at:
#     scripts/bin2hex.py
#   which converts firmware/build/firmware.bin -> firmware/build/firmware.hex
#   as 32-bit little-endian words (one word per line), suitable for $readmemh.

SHELL := /bin/bash

MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
THIS_MAKEFILE := $(abspath $(lastword $(MAKEFILE_LIST)))
SELF_MAKE := $(MAKE) -f $(THIS_MAKEFILE)

# ----------------------------
# Tools
IVERILOG ?= iverilog
VVP      ?= vvp
PYTHON   ?= python3
COCOTB_PYENV_PYTHON := $(HOME)/.pyenv/versions/cocotb-env/bin/python
COCOTB_PYENV_CONFIG := $(HOME)/.pyenv/versions/cocotb-env/bin/cocotb-config
ifeq ($(wildcard $(COCOTB_PYENV_PYTHON)), $(COCOTB_PYENV_PYTHON))
PYTHON := $(COCOTB_PYENV_PYTHON)
endif
COCOTB_CONFIG ?= $(if $(wildcard $(COCOTB_PYENV_CONFIG)),$(COCOTB_PYENV_CONFIG),cocotb-config)

# ------------------------------------------------------------
# Derived paths
# ------------------------------------------------------------

# Cocotb VPI library
COCOTB_LIBDIR := $(shell $(COCOTB_CONFIG) --lib-dir 2>/dev/null)

# Python interpreter for cocotb
PYGPI_PYTHON_BIN := $(shell $(PYTHON) -c "import sys; print(sys.executable)")
LIBPYTHON_LOC := $(shell $(PYTHON) -m cocotb_tools.config --libpython 2>/dev/null)

# Build directory
BUILD_DIR := $(MAKEFILE_DIR)/sim/build

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

WAVE_DIR := $(MAKEFILE_DIR)/sim/waves

# ------------------------------------------------------------
# Common cocotb environment (v2 naming)
# ------------------------------------------------------------
export PYGPI_PYTHON_BIN := $(PYGPI_PYTHON_BIN)
export LIBPYTHON_LOC    := $(LIBPYTHON_LOC)
export PYTHONPATH       := $(MAKEFILE_DIR)/sim/tb
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
RTL_DIR      := $(MAKEFILE_DIR)/../src
TB_DIR       := $(MAKEFILE_DIR)/sim/tb
SIM_BUILD    := $(MAKEFILE_DIR)/sim/build
FW_DIR       := $(MAKEFILE_DIR)/firmware
FW_BUILD     := $(FW_DIR)/build
FW_TESTS     := $(FW_DIR)/tests
TOOLS_DIR    := $(MAKEFILE_DIR)/tools
SCRIPTS_DIR  := $(MAKEFILE_DIR)/../scripts

BIN2HEX_PY   := $(SCRIPTS_DIR)/bin2hex.py
HEX2CHDR_PY  := $(TOOLS_DIR)/hex_to_c_header.py
FW_GEN_DIR   := $(FW_DIR)/build/generated
FW_ML_W_HDR  := $(FW_GEN_DIR)/ml_weights_full.h
TAKETWO_PARAMS_BIN := $(MAKEFILE_DIR)/sim/tb/ml/taketwo_params.bin
TAKETWO_PARAMS_HEX := $(FW_GEN_DIR)/taketwo_params.hex

# Ensure output dirs exist
$(SIM_BUILD) $(FW_BUILD) $(FW_GEN_DIR):
	@mkdir -p $@

# ----------------------------
# Common RTL sources for SoC
# ----------------------------
SOC_RTL_SRCS := \
  $(RTL_DIR)/soc_top.v \
  $(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
  $(MAKEFILE_DIR)/../ip/picorv32.v \
  $(RTL_DIR)/gpio_mmio.v \
  $(RTL_DIR)/test_mmio.v \
  $(RTL_DIR)/timer_mmio.v \
  $(RTL_DIR)/ml_stub_mmio.v \
  $(RTL_DIR)/ml_axil_bridge_mmio.v \
  $(RTL_DIR)/weight_ram_axi.v \
  $(RTL_DIR)/irq_ctrl_mmio.v \
  $(RTL_DIR)/taketwo_wrap.v \
  $(RTL_DIR)/taketwo.v \
  $(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v \
  $(RTL_DIR)/pwrctrl_mmio.v \
  $(RTL_DIR)/host_i2c_target.v \
  $(RTL_DIR)/host_i2c_bridge_regs.v

UNIFIED_TOP_RTL_SRCS := \
  $(RTL_DIR)/top.sv \
  $(RTL_DIR)/top_fsm.v \
  $(RTL_DIR)/host_i2c_target.v \
  $(RTL_DIR)/host_i2c_bridge_regs.v \
  $(RTL_DIR)/spi_master_mmio.v \
  $(RTL_DIR)/i2c_master.sv \
  $(RTL_DIR)/accel_reader.sv \
  $(RTL_DIR)/motion_process.sv \
  $(RTL_DIR)/ppg_fifo_reader.sv \
  $(RTL_DIR)/ppg_process.sv \
  $(RTL_DIR)/mssd_engine.sv \
  $(RTL_DIR)/signal_quality.sv \
  $(RTL_DIR)/feature_engine.sv \
  $(RTL_DIR)/globaltimer.sv \
  $(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
  $(MAKEFILE_DIR)/../ip/picorv32.v \
  $(RTL_DIR)/test_mmio.v \
  $(RTL_DIR)/timer_mmio.v \
  $(RTL_DIR)/ml_axil_bridge_mmio.v \
  $(RTL_DIR)/weight_flash_axi.v \
  $(RTL_DIR)/irq_ctrl_mmio.v \
  $(RTL_DIR)/taketwo_wrap.v \
  $(RTL_DIR)/taketwo.v \
  $(RTL_DIR)/pwrctrl_mmio.v \
  $(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v

SOC_TB_SRCS  := $(TB_DIR)/tb_soc.sv
SOC_VVP      := sim_soc.vvp
IRQ_TB_SRCS  := $(TB_DIR)/tb_irq.sv
IRQ_VVP      := sim_irq.vvp

# ----------------------------
# Cocotb configuration helper (cocotb 2.x via oss-cad-suite)
# ----------------------------
# cocotb's Icarus VPI shared library directory:
COCOTB_LIBDIR := $(shell $(COCOTB_CONFIG) --lib-dir 2>/dev/null)

# Absolute path + entry point needed by cocotb 2.x GPI loader:
COCOTB_PYGPI  := $(shell $(COCOTB_CONFIG) --pygpi-entry-point 2>/dev/null)
COCOTB_LIBPYTHON := $(shell $(COCOTB_CONFIG) --libpython 2>/dev/null)

# Use the same python interpreter cocotb will embed
export PYGPI_PYTHON_BIN := $(shell $(COCOTB_CONFIG) --python-bin 2>/dev/null)

# Make sure cocotb can import your tests
export PYTHONPATH := $(abspath $(TB_DIR))

define RUN_COCOTB_ICARUS
	GPI_USERS="$(COCOTB_PYGPI)" LD_PRELOAD="$(COCOTB_LIBPYTHON):$$LD_PRELOAD" LD_LIBRARY_PATH="$(COCOTB_LIBDIR):$$LD_LIBRARY_PATH" $(VVP) -M "$(COCOTB_LIBDIR)" -m libcocotbvpi_icarus $1
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
FW_C_prod_main             := $(FW_DIR)/prod_main.c
FW_C_test_sleepwake         := $(FW_TESTS)/test_sleepwake.c
FW_C_test_gpio              := $(FW_TESTS)/test_gpio.c
FW_C_test_sleepwake_periodic:= $(FW_TESTS)/test_sleepwake_periodic.c
FW_C_test_ml_weights        := $(FW_TESTS)/test_ml_weights.c
FW_C_test_ml_cpu_wake_i2c   := $(FW_TESTS)/test_ml_cpu_wake_i2c.c
FW_C_test_top_feature_ml_cpu:= $(FW_TESTS)/test_top_feature_ml_cpu.c
FW_C_test_top_feature_ml_cpu_spi_flash:= $(FW_TESTS)/test_top_feature_ml_cpu_spi_flash.c
FW_C_test_top_spi_init_unified := $(FW_TESTS)/test_top_spi_init_unified.c
FW_C_test_top_ml_control_unified := $(FW_TESTS)/test_top_ml_control_unified.c
FW_C_test_top_sleep_wake_unified := $(FW_TESTS)/test_top_sleep_wake_unified.c
FW_C_test_top_ml_golden_vector_unified := $(FW_TESTS)/test_top_ml_golden_vector_unified.c
FW_C_irq_test              := $(FW_DIR)/irq_test.c
FW_C_test_top_spi_boot_weights := $(FW_TESTS)/test_top_spi_boot_weights.c
FW_ARCH_test_top_spi_boot_weights := rv32im

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
FW_ARCH_prod_main := rv32im
FW_ARCH_test_top_feature_ml_cpu := rv32im
FW_ARCH_test_top_feature_ml_cpu_spi_flash := rv32im
FW_ARCH_test_top_spi_init_unified := rv32im
FW_ARCH_test_top_ml_control_unified := rv32im
FW_ARCH_test_top_sleep_wake_unified := rv32im
FW_ARCH_test_top_ml_golden_vector_unified := rv32im
FW_ARCH_irq_test := rv32im
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

$(TAKETWO_PARAMS_HEX): $(TAKETWO_PARAMS_BIN) $(BIN2HEX_PY) | $(FW_GEN_DIR)
	@echo "[FW] Generating weight hex: $@"
	@$(PYTHON) $(BIN2HEX_PY) $< $@

$(FW_ML_W_HDR): $(TAKETWO_PARAMS_HEX) $(HEX2CHDR_PY) | $(FW_GEN_DIR)
	@echo "[FW] Generating full-weight header: $@"
	@$(PYTHON) $(HEX2CHDR_PY) $< $@ ml_weights_full

# Build rule
$(FW_HEX): $(THIS_MAKEFILE) $(FW_DIR)/start.S $(FW_LDSCRIPT) $(FW_SRC) $(BIN2HEX_PY) $(FW_EXTRA_DEPS)
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

.PHONY: firmware firmware-main firmware-sleepwake firmware-gpio firmware-sleepwake-periodic firmware-rebuild

# Generic "firmware" builds whatever FW_VARIANT is set to
firmware: $(FW_HEX)

firmware-rebuild:
	@rm -f $(FW_ELF) $(FW_BIN) $(FW_HEX)
	@$(SELF_MAKE) FW_VARIANT=$(FW_VARIANT) firmware

firmware-main:
	@$(SELF_MAKE) FW_VARIANT=main firmware

firmware-sleepwake:
	@$(SELF_MAKE) FW_VARIANT=test_sleepwake firmware

firmware-gpio:
	@$(SELF_MAKE) FW_VARIANT=test_gpio firmware

firmware-sleepwake-periodic:
	@$(SELF_MAKE) FW_VARIANT=test_sleepwake_periodic firmware

firmware-ml-weights:
	@$(SELF_MAKE) FW_VARIANT=test_ml_weights firmware

firmware-ml-cpu-wake-i2c:
	@$(SELF_MAKE) FW_VARIANT=test_ml_cpu_wake_i2c firmware

firmware-top-feature-ml-cpu:
	@$(SELF_MAKE) FW_VARIANT=test_top_feature_ml_cpu firmware

firmware-top-feature-ml-cpu-spi-flash:
	@$(SELF_MAKE) FW_VARIANT=test_top_feature_ml_cpu_spi_flash firmware

firmware-top-sleep-wake-unified:
	@$(SELF_MAKE) FW_VARIANT=test_top_sleep_wake_unified firmware

firmware-top-ml-golden-vector-unified:
	@$(SELF_MAKE) FW_VARIANT=test_top_ml_golden_vector_unified firmware



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
#   make sim-soc FW_VARIANT=test_ml_weights WEIGHT_INIT_HEX=$(RTL_DIR)/taketwo_params.hex
sim-soc: $(SOC_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=$(FW_VARIANT) firmware-rebuild
	@echo "[SIM] Running tb_soc (FW=$(FW_HEX))"
	$(VVP) $(SOC_VVP)

# Convenience: build + run ML weights inference test
.PHONY: sim-ml-weights
sim-ml-weights:
	@$(SELF_MAKE) FW_VARIANT=test_ml_weights \
	         WEIGHT_INIT_HEX=$(TAKETWO_PARAMS_HEX) \
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
	@$(SELF_MAKE) FW_VARIANT=test_ml_cpu_wake_i2c firmware
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
	@$(SELF_MAKE) FW_VARIANT=test_ml_weights firmware
	@echo "== Running $(SOC_ML_WEIGHT_LOAD_TOP) (FW=$(FW_DIR)/build/test_ml_weights/firmware.hex) =="
	$(VVP) $(SOC_ML_WEIGHT_LOAD_VVP)

# Unified top: sensor models + feature MMIO + CPU-driven ML start.
# This is the first full `top.sv` proof that:
#   sensor pipeline -> feature MMIO -> CPU reads -> weight_ram_axi writes
#   -> ml_axil_bridge_mmio start -> taketwo AXI traffic
TOP_FEATURE_ML_CPU_TOP     := tb_top_feature_ml_cpu
TOP_FEATURE_ML_CPU_VVP     := $(BUILD_DIR)/$(TOP_FEATURE_ML_CPU_TOP).vvp
TOP_FEATURE_ML_CPU_SOURCES := \
	$(TB_DIR)/tb_top_feature_ml_cpu.sv \
	$(RTL_DIR)/top.sv \
	$(RTL_DIR)/top_fsm.v \
	$(RTL_DIR)/host_i2c_target.v \
	$(RTL_DIR)/host_i2c_bridge_regs.v \
	$(RTL_DIR)/i2c_master.sv \
	$(RTL_DIR)/accel_reader.sv \
	$(RTL_DIR)/motion_process.sv \
	$(RTL_DIR)/ppg_fifo_reader.sv \
	$(RTL_DIR)/ppg_process.sv \
	$(RTL_DIR)/mssd_engine.sv \
	$(RTL_DIR)/signal_quality.sv \
	$(RTL_DIR)/feature_engine.sv \
	$(RTL_DIR)/globaltimer.sv \
	$(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
	$(RTL_DIR)/spi_master_mmio.v \
	$(MAKEFILE_DIR)/../ip/picorv32.v \
	$(RTL_DIR)/test_mmio.v \
	$(RTL_DIR)/timer_mmio.v \
	$(RTL_DIR)/ml_axil_bridge_mmio.v \
	$(RTL_DIR)/weight_flash_axi.v \
	$(RTL_DIR)/irq_ctrl_mmio.v \
	$(RTL_DIR)/taketwo_wrap.v \
	$(RTL_DIR)/taketwo.v \
	$(RTL_DIR)/pwrctrl_mmio.v \
	$(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_FEATURE_ML_CPU_VVP): $(TOP_FEATURE_ML_CPU_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_FEATURE_ML_CPU_TOP) -o $@ \
	  $(TOP_FEATURE_ML_CPU_SOURCES)

.PHONY: sim-top-feature-ml-cpu
sim-top-feature-ml-cpu: $(TOP_FEATURE_ML_CPU_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=test_top_feature_ml_cpu firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(TOP_FEATURE_ML_CPU_TOP) (FW=$(FW_DIR)/build/test_top_feature_ml_cpu/firmware.hex) =="
	$(VVP) $(TOP_FEATURE_ML_CPU_VVP)

TOP_FEATURE_ML_CPU_SPI_FLASH_TOP     := tb_top_feature_ml_cpu_spi_flash
TOP_FEATURE_ML_CPU_SPI_FLASH_VVP     := $(BUILD_DIR)/$(TOP_FEATURE_ML_CPU_SPI_FLASH_TOP).vvp
TOP_FEATURE_ML_CPU_SPI_FLASH_SOURCES := \
	$(TB_DIR)/tb_top_feature_ml_cpu_spi_flash.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(RTL_DIR)/top.sv \
	$(RTL_DIR)/top_fsm.v \
	$(RTL_DIR)/host_i2c_target.v \
	$(RTL_DIR)/host_i2c_bridge_regs.v \
	$(RTL_DIR)/i2c_master.sv \
	$(RTL_DIR)/accel_reader.sv \
	$(RTL_DIR)/motion_process.sv \
	$(RTL_DIR)/ppg_fifo_reader.sv \
	$(RTL_DIR)/ppg_process.sv \
	$(RTL_DIR)/mssd_engine.sv \
	$(RTL_DIR)/signal_quality.sv \
	$(RTL_DIR)/feature_engine.sv \
	$(RTL_DIR)/globaltimer.sv \
	$(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
	$(RTL_DIR)/spi_master_mmio.v \
	$(MAKEFILE_DIR)/../ip/picorv32.v \
	$(RTL_DIR)/test_mmio.v \
	$(RTL_DIR)/timer_mmio.v \
	$(RTL_DIR)/ml_axil_bridge_mmio.v \
	$(RTL_DIR)/weight_flash_axi.v \
	$(RTL_DIR)/irq_ctrl_mmio.v \
	$(RTL_DIR)/taketwo_wrap.v \
	$(RTL_DIR)/taketwo.v \
	$(RTL_DIR)/pwrctrl_mmio.v \
	$(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_FEATURE_ML_CPU_SPI_FLASH_VVP): $(TOP_FEATURE_ML_CPU_SPI_FLASH_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_FEATURE_ML_CPU_SPI_FLASH_TOP) -o $@ \
	  $(TOP_FEATURE_ML_CPU_SPI_FLASH_SOURCES)

.PHONY: sim-top-feature-ml-cpu-spi-flash
sim-top-feature-ml-cpu-spi-flash: $(TOP_FEATURE_ML_CPU_SPI_FLASH_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=test_top_feature_ml_cpu_spi_flash firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(TOP_FEATURE_ML_CPU_SPI_FLASH_TOP) (FW=$(FW_DIR)/build/test_top_feature_ml_cpu_spi_flash/firmware.hex FLASH=$(TAKETWO_PARAMS_HEX)) =="
	$(VVP) $(TOP_FEATURE_ML_CPU_SPI_FLASH_VVP)


# Unified top: short SPI-only regression. This isolates the boot-copy plumbing:
#   CPU firmware -> spi_master_mmio -> spi_flash_model -> weight_ram_axi
# without waiting on features, ML, or host policy behavior.
TOP_SPI_INIT_UNIFIED_TOP     := tb_top_spi_init_unified
TOP_SPI_INIT_UNIFIED_VVP     := $(BUILD_DIR)/$(TOP_SPI_INIT_UNIFIED_TOP).vvp
TOP_SPI_INIT_UNIFIED_SOURCES := \
	$(TB_DIR)/tb_top_spi_init_unified.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(RTL_DIR)/top.sv \
	$(RTL_DIR)/top_fsm.v \
	$(RTL_DIR)/host_i2c_target.v \
	$(RTL_DIR)/host_i2c_bridge_regs.v \
	$(RTL_DIR)/i2c_master.sv \
	$(RTL_DIR)/accel_reader.sv \
	$(RTL_DIR)/motion_process.sv \
	$(RTL_DIR)/ppg_fifo_reader.sv \
	$(RTL_DIR)/ppg_process.sv \
	$(RTL_DIR)/mssd_engine.sv \
	$(RTL_DIR)/signal_quality.sv \
	$(RTL_DIR)/feature_engine.sv \
	$(RTL_DIR)/globaltimer.sv \
	$(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
	$(RTL_DIR)/spi_master_mmio.v \
	$(MAKEFILE_DIR)/../ip/picorv32.v \
	$(RTL_DIR)/test_mmio.v \
	$(RTL_DIR)/timer_mmio.v \
	$(RTL_DIR)/ml_axil_bridge_mmio.v \
	$(RTL_DIR)/weight_flash_axi.v \
	$(RTL_DIR)/irq_ctrl_mmio.v \
	$(RTL_DIR)/taketwo_wrap.v \
	$(RTL_DIR)/taketwo.v \
	$(RTL_DIR)/pwrctrl_mmio.v \
	$(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_SPI_INIT_UNIFIED_VVP): $(TOP_SPI_INIT_UNIFIED_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_SPI_INIT_UNIFIED_TOP) -o $@ \
	  $(TOP_SPI_INIT_UNIFIED_SOURCES)

.PHONY: sim-top-spi-init-unified
sim-top-spi-init-unified: $(TOP_SPI_INIT_UNIFIED_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=test_top_spi_init_unified firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(TOP_SPI_INIT_UNIFIED_TOP) (FW=$(FW_DIR)/build/test_top_spi_init_unified/firmware.hex FLASH=$(TAKETWO_PARAMS_HEX)) =="
	$(VVP) $(TOP_SPI_INIT_UNIFIED_VVP)

# ============================================================
# Unified top: hardware SPI boot controller isolation test
# Verifies spi_boot_ctrl loads firmware into simple_sram and
# asserts boot_done before releasing the CPU.
# ============================================================

TOP_SPI_BOOT_WEIGHTS_TOP     := tb_top_spi_boot
TOP_SPI_BOOT_WEIGHTS_VVP     := $(BUILD_DIR)/$(TOP_SPI_BOOT_WEIGHTS_TOP).vvp
TOP_SPI_BOOT_WEIGHTS_SOURCES := \
	$(TB_DIR)/tb_top_spi_boot.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(UNIFIED_TOP_RTL_SRCS) \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_SPI_BOOT_WEIGHTS_VVP): $(TOP_SPI_BOOT_WEIGHTS_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) \
	  -s $(TOP_SPI_BOOT_WEIGHTS_TOP) -o $@ $(TOP_SPI_BOOT_WEIGHTS_SOURCES)

.PHONY: sim-top-spi-boot
sim-top-spi-boot: $(TOP_SPI_BOOT_WEIGHTS_VVP) | $(SIM_BUILD)
	@echo "== Running $(TOP_SPI_BOOT_WEIGHTS_TOP) =="
	$(VVP) $(TOP_SPI_BOOT_WEIGHTS_VVP)

# ============================================================
# Unified top: CPU-driven ML weight loading from SPI flash
# Firmware boots (BOOT_WORDS=1), then loads weights from weight
# flash via spi_master_mmio into weight_ram_axi and verifies.
# ============================================================

TOP_SPI_WEIGHTS_TOP     := tb_top_spi_weights
TOP_SPI_WEIGHTS_VVP     := $(BUILD_DIR)/$(TOP_SPI_WEIGHTS_TOP).vvp
TOP_SPI_WEIGHTS_SOURCES := \
	$(TB_DIR)/tb_top_spi_weights.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(UNIFIED_TOP_RTL_SRCS) \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_SPI_WEIGHTS_VVP): $(TOP_SPI_WEIGHTS_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) \
	  -s $(TOP_SPI_WEIGHTS_TOP) -o $@ $(TOP_SPI_WEIGHTS_SOURCES)

.PHONY: sim-top-spi-weights
sim-top-spi-weights: $(TOP_SPI_WEIGHTS_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=test_top_spi_boot_weights firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(TOP_SPI_WEIGHTS_TOP) (FW=$(FW_DIR)/build/test_top_spi_boot_weights/firmware.hex FLASH=$(TAKETWO_PARAMS_HEX)) =="
	$(VVP) $(TOP_SPI_WEIGHTS_VVP)

# ============================================================
# Hardware weight boot: SPI flash -> weight_ram_axi -> taketwo SRAMs
# No firmware required. tb drives taketwo's saxi directly via
# force/release after weight_boot_done asserts.
# ============================================================

WEIGHT_BOOT_TOP     := tb_weight_boot
WEIGHT_BOOT_VVP     := $(BUILD_DIR)/$(WEIGHT_BOOT_TOP).vvp
WEIGHT_BOOT_SOURCES := \
	$(TB_DIR)/tb_weight_boot.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(UNIFIED_TOP_RTL_SRCS) \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(WEIGHT_BOOT_VVP): $(WEIGHT_BOOT_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) \
	  -s $(WEIGHT_BOOT_TOP) -o $@ $(WEIGHT_BOOT_SOURCES)

.PHONY: sim-weight-boot
sim-weight-boot: $(WEIGHT_BOOT_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(WEIGHT_BOOT_TOP) (FLASH=$(TAKETWO_PARAMS_HEX)) =="
	$(VVP) $(WEIGHT_BOOT_VVP)

# Unified top: short ML-control-only regression. This isolates the CPU-owned
# taketwo control path from the feature and SPI flows:
#   WRAM input writes -> ML base-register programming -> START/BUSY/IRQ
#   -> output mutation in shared WRAM.
TOP_ML_CONTROL_UNIFIED_TOP     := tb_top_ml_control_unified
TOP_ML_CONTROL_UNIFIED_VVP     := $(BUILD_DIR)/$(TOP_ML_CONTROL_UNIFIED_TOP).vvp
TOP_ML_CONTROL_UNIFIED_SOURCES := \
	$(TB_DIR)/tb_top_ml_control_unified.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(RTL_DIR)/top.sv \
	$(RTL_DIR)/top_fsm.v \
	$(RTL_DIR)/host_i2c_target.v \
	$(RTL_DIR)/host_i2c_bridge_regs.v \
	$(RTL_DIR)/i2c_master.sv \
	$(RTL_DIR)/accel_reader.sv \
	$(RTL_DIR)/motion_process.sv \
	$(RTL_DIR)/ppg_fifo_reader.sv \
	$(RTL_DIR)/ppg_process.sv \
	$(RTL_DIR)/mssd_engine.sv \
	$(RTL_DIR)/signal_quality.sv \
	$(RTL_DIR)/feature_engine.sv \
	$(RTL_DIR)/globaltimer.sv \
	$(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
	$(RTL_DIR)/spi_master_mmio.v \
	$(MAKEFILE_DIR)/../ip/picorv32.v \
	$(RTL_DIR)/test_mmio.v \
	$(RTL_DIR)/timer_mmio.v \
	$(RTL_DIR)/ml_axil_bridge_mmio.v \
	$(RTL_DIR)/weight_flash_axi.v \
	$(RTL_DIR)/irq_ctrl_mmio.v \
	$(RTL_DIR)/taketwo_wrap.v \
	$(RTL_DIR)/taketwo.v \
	$(RTL_DIR)/pwrctrl_mmio.v \
	$(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_ML_CONTROL_UNIFIED_VVP): $(TOP_ML_CONTROL_UNIFIED_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_ML_CONTROL_UNIFIED_TOP) -o $@ \
	  $(TOP_ML_CONTROL_UNIFIED_SOURCES)

.PHONY: sim-top-ml-control-unified
sim-top-ml-control-unified: $(TOP_ML_CONTROL_UNIFIED_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=test_top_ml_control_unified firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(TOP_ML_CONTROL_UNIFIED_TOP) (FW=$(FW_DIR)/build/test_top_ml_control_unified/firmware.hex WEIGHTS=$(TAKETWO_PARAMS_HEX)) =="
	$(VVP) $(TOP_ML_CONTROL_UNIFIED_VVP)

TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_TOP     := tb_top_feature_ml_prod_main_host_i2c
TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_VVP     := $(BUILD_DIR)/$(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_TOP).vvp
TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_SOURCES := \
	$(TB_DIR)/tb_top_feature_ml_prod_main_host_i2c.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(RTL_DIR)/top.sv \
	$(RTL_DIR)/top_fsm.v \
	$(RTL_DIR)/host_i2c_target.v \
	$(RTL_DIR)/host_i2c_bridge_regs.v \
	$(RTL_DIR)/i2c_master.sv \
	$(RTL_DIR)/accel_reader.sv \
	$(RTL_DIR)/motion_process.sv \
	$(RTL_DIR)/ppg_fifo_reader.sv \
	$(RTL_DIR)/ppg_process.sv \
	$(RTL_DIR)/mssd_engine.sv \
	$(RTL_DIR)/signal_quality.sv \
	$(RTL_DIR)/feature_engine.sv \
	$(RTL_DIR)/globaltimer.sv \
	$(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
	$(RTL_DIR)/spi_master_mmio.v \
	$(MAKEFILE_DIR)/../ip/picorv32.v \
	$(RTL_DIR)/test_mmio.v \
	$(RTL_DIR)/timer_mmio.v \
	$(RTL_DIR)/ml_axil_bridge_mmio.v \
	$(RTL_DIR)/weight_flash_axi.v \
	$(RTL_DIR)/irq_ctrl_mmio.v \
	$(RTL_DIR)/taketwo_wrap.v \
	$(RTL_DIR)/taketwo.v \
	$(RTL_DIR)/pwrctrl_mmio.v \
	$(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_VVP): $(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_TOP) -o $@ \
	  $(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_SOURCES)

.PHONY: sim-top-feature-ml-prod-main-host-i2c
sim-top-feature-ml-prod-main-host-i2c: $(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=prod_main firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_TOP) (FW=$(FW_DIR)/build/prod_main/firmware.hex FLASH=$(TAKETWO_PARAMS_HEX)) =="
	$(VVP) $(TOP_FEATURE_ML_PROD_MAIN_HOST_I2C_VVP)

# Unified top: dedicated timer sleep/wake regression.
# This bench isolates the always-on timer + pwrctrl + irq_ctrl sleep path:
#   firmware requests sleep -> CPU clock gates -> timer wake arrives
#   -> wake bookkeeping latches -> firmware clears sticky state.
TOP_SLEEP_WAKE_UNIFIED_TOP     := tb_top_sleep_wake_unified
TOP_SLEEP_WAKE_UNIFIED_VVP     := $(BUILD_DIR)/$(TOP_SLEEP_WAKE_UNIFIED_TOP).vvp
TOP_SLEEP_WAKE_UNIFIED_SOURCES := \
	$(TB_DIR)/tb_top_sleep_wake_unified.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(RTL_DIR)/top.sv \
	$(RTL_DIR)/top_fsm.v \
	$(RTL_DIR)/host_i2c_target.v \
	$(RTL_DIR)/host_i2c_bridge_regs.v \
	$(RTL_DIR)/i2c_master.sv \
	$(RTL_DIR)/accel_reader.sv \
	$(RTL_DIR)/motion_process.sv \
	$(RTL_DIR)/ppg_fifo_reader.sv \
	$(RTL_DIR)/ppg_process.sv \
	$(RTL_DIR)/mssd_engine.sv \
	$(RTL_DIR)/signal_quality.sv \
	$(RTL_DIR)/feature_engine.sv \
	$(RTL_DIR)/globaltimer.sv \
	$(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
	$(RTL_DIR)/spi_master_mmio.v \
	$(MAKEFILE_DIR)/../ip/picorv32.v \
	$(RTL_DIR)/test_mmio.v \
	$(RTL_DIR)/timer_mmio.v \
	$(RTL_DIR)/ml_axil_bridge_mmio.v \
	$(RTL_DIR)/weight_flash_axi.v \
	$(RTL_DIR)/irq_ctrl_mmio.v \
	$(RTL_DIR)/taketwo_wrap.v \
	$(RTL_DIR)/taketwo.v \
	$(RTL_DIR)/pwrctrl_mmio.v \
	$(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v \
	sensors/i2c_slave_lis2dw12.sv \
	sensors/i2c_slave_adpd144ri.sv

$(TOP_SLEEP_WAKE_UNIFIED_VVP): $(TOP_SLEEP_WAKE_UNIFIED_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_SLEEP_WAKE_UNIFIED_TOP) -o $@ \
	  $(TOP_SLEEP_WAKE_UNIFIED_SOURCES)

.PHONY: sim-top-sleep-wake-unified
sim-top-sleep-wake-unified: $(TOP_SLEEP_WAKE_UNIFIED_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=test_top_sleep_wake_unified firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "== Running $(TOP_SLEEP_WAKE_UNIFIED_TOP) (FW=$(FW_DIR)/build/test_top_sleep_wake_unified/firmware.hex) =="
	$(VVP) $(TOP_SLEEP_WAKE_UNIFIED_VVP)

.PHONY: test-cpu-ml-pipeline
test-cpu-ml-pipeline:
	@$(SELF_MAKE) test-cpu-ml
	@$(SELF_MAKE) sim-ml-weight-load

.PHONY: test-soc-wake-e2e-p0
test-soc-wake-e2e-p0:
	@$(SELF_MAKE) test-cpu-ml
	@$(SELF_MAKE) sim-ml-weight-load
	@$(SELF_MAKE) sim-ml-cpu-wake-i2c
	@$(SELF_MAKE) test-host-i2c-bridge
	@$(SELF_MAKE) test-irq-ctrl-races

.PHONY: test-functional-matrix
test-functional-matrix:
	@bash tools/test_functionality_matrix.sh

.PHONY: test-firmware-matrix
test-firmware-matrix:
	@bash $(TOOLS_DIR)/test_functionality_matrix.sh
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

sim-irq: $(IRQ_VVP) | $(SIM_BUILD)
	@$(SELF_MAKE) FW_VARIANT=main firmware-rebuild
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
  $(RTL_DIR)/taketwo.v \
  $(RTL_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v

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
	$(MAKE) -C $(MAKEFILE_DIR)/sim/tb/ml

# ============================================================
# RESET CONTROLLER TB (reset_ctrl_tb)
# ============================================================

RESET_CTRL_TOP     := reset_ctrl_tb
RESET_CTRL_VVP     := $(BUILD_DIR)/$(RESET_CTRL_TOP).vvp
RESET_CTRL_SOURCES := sim/tb/reset_ctrl_tb.sv $(RTL_DIR)/reset_ctrl.v
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
# SIMPLE SRAM COCOTB TEST (tb_simple_sram + simple_sram_tb.py)
# ============================================================

SIMPLE_SRAM_TOP     := tb_simple_sram
SIMPLE_SRAM_VVP     := $(BUILD_DIR)/$(SIMPLE_SRAM_TOP).vvp
SIMPLE_SRAM_PYMOD   := simple_sram_tb
SIMPLE_SRAM_SOURCES := $(TB_DIR)/tb_simple_sram.sv \
                       $(RTL_DIR)/simple_sram.v \
	$(RTL_DIR)/spi_boot_ctrl.v \
                       $(MAKEFILE_DIR)/../ip/gf180mcu_fd_ip_sram__sram512x8m8wm1.v

$(SIMPLE_SRAM_VVP): $(SIMPLE_SRAM_SOURCES) | $(BUILD_DIR)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: test-simple-sram
test-simple-sram: $(SIMPLE_SRAM_VVP)
	@echo "[COCOTB] Running $(SIMPLE_SRAM_PYMOD) on $(SIMPLE_SRAM_TOP)"
	@export COCOTB_TOPLEVEL=$(SIMPLE_SRAM_TOP); \
	export COCOTB_TEST_MODULES=$(SIMPLE_SRAM_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(SIMPLE_SRAM_VVP))

.PHONY: clean-simple-sram
clean-simple-sram:
	rm -f $(SIMPLE_SRAM_VVP)

# ============================================================
# TOP FSM COCOTB TEST (tb_top_fsm + test_top_fsm.py)
# ============================================================

TOP_FSM_TOP     := tb_top_fsm
TOP_FSM_VVP     := $(BUILD_DIR)/$(TOP_FSM_TOP).vvp
TOP_FSM_PYMOD   := test_top_fsm
TOP_FSM_SOURCES := $(TB_DIR)/tb_top_fsm.sv \
                   $(RTL_DIR)/top_fsm.v

$(TOP_FSM_VVP): $(TOP_FSM_SOURCES) | $(BUILD_DIR)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: test-top-fsm
test-top-fsm: $(TOP_FSM_VVP)
	@echo "[COCOTB] Running $(TOP_FSM_PYMOD) on $(TOP_FSM_TOP)"
	@mkdir -p $(WAVE_DIR)
	@export COCOTB_TOPLEVEL=$(TOP_FSM_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_FSM_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(TOP_FSM_VVP))

.PHONY: clean-top-fsm
clean-top-fsm:
	rm -f $(TOP_FSM_VVP)

# ============================================================
# MOTION PREPROCESS
# ============================================================

motion_process_TOP     := motion_process_tb
motion_process_VVP     := $(BUILD_DIR)/$(motion_process_TOP).vvp
motion_process_SOURCES := sim/tb/motion_process_tb.sv $(RTL_DIR)/motion_process.sv
motion_process_VCD     := $(WAVE_DIR)/motion_process_tb.vcd

$(motion_process_VVP): $(motion_process_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-motion-preprocess
sim-motion-preprocess: $(motion_process_VVP)
	@echo "== Running $(motion_process_TOP) (VCD -> $(motion_process_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(motion_process_VVP))

# ============================================================
# PPG FIFO READER
# ============================================================

PPG_FIFO_READER_TOP     := ppg_fifo_reader_tb
PPG_FIFO_READER_VVP     := $(BUILD_DIR)/$(PPG_FIFO_READER_TOP).vvp
PPG_FIFO_READER_SOURCES := sim/tb/ppg_fifo_reader_tb.sv $(RTL_DIR)/ppg_fifo_reader.sv
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

PPG_BEAT_RR_TOP     := ppg_process_tb
PPG_BEAT_RR_VVP     := $(BUILD_DIR)/$(PPG_BEAT_RR_TOP).vvp
PPG_BEAT_RR_SOURCES := sim/tb/ppg_process_tb.sv $(RTL_DIR)/ppg_process.sv $(RTL_DIR)/ewma_baseline.sv
PPG_BEAT_RR_VCD     := $(WAVE_DIR)/ppg_process_tb.vcd

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
ACCEL_READER_SOURCES := sim/tb/accel_reader_tb.sv $(RTL_DIR)/accel_reader.sv
ACCEL_READER_VCD     := $(WAVE_DIR)/accel_reader_tb.vcd

$(ACCEL_READER_VVP): $(ACCEL_READER_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-accel-reader
sim-accel-reader: $(ACCEL_READER_VVP)
	@echo "== Running $(ACCEL_READER_TOP) (VCD -> $(ACCEL_READER_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(ACCEL_READER_VVP))

# ============================================================
# MSSD ENGINE
# ============================================================

MSSD_ENGINE_TOP     := mssd_engine_tb
MSSD_ENGINE_VVP     := $(BUILD_DIR)/$(MSSD_ENGINE_TOP).vvp
MSSD_ENGINE_SOURCES := sim/tb/mssd_engine_tb.sv $(RTL_DIR)/mssd_engine.sv $(RTL_DIR)/ewma_baseline.sv
MSSD_ENGINE_VCD     := $(WAVE_DIR)/mssd_engine_tb.vcd

$(MSSD_ENGINE_VVP): $(MSSD_ENGINE_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-MSSD-engine
sim-MSSD-engine: $(MSSD_ENGINE_VVP)
	@echo "== Running $(MSSD_ENGINE_TOP) (VCD -> $(MSSD_ENGINE_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(MSSD_ENGINE_VVP))

# ============================================================
# SIGNAL QUALITY
# ============================================================

SIGNAL_QUALITY_TOP     := signal_quality_tb
SIGNAL_QUALITY_VVP     := $(BUILD_DIR)/$(SIGNAL_QUALITY_TOP).vvp
SIGNAL_QUALITY_SOURCES := sim/tb/signal_quality_tb.sv $(RTL_DIR)/signal_quality.sv
SIGNAL_QUALITY_VCD     := $(WAVE_DIR)/signal_quality_tb.vcd

$(SIGNAL_QUALITY_VVP): $(SIGNAL_QUALITY_SOURCES)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-signal-quality
sim-signal-quality: $(SIGNAL_QUALITY_VVP)
	@echo "== Running $(SIGNAL_QUALITY_TOP) (VCD -> $(SIGNAL_QUALITY_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(SIGNAL_QUALITY_VVP))

# ============================================================
# TOP SENSOR PIPELINE
# ============================================================

TOP_PIPELINE_TOP     := top_pipeline_tb
TOP_PIPELINE_VVP     := $(BUILD_DIR)/$(TOP_PIPELINE_TOP).vvp
TOP_PIPELINE_SOURCES := sim/tb/top_pipeline_tb.sv \
                        $(UNIFIED_TOP_RTL_SRCS) \
                        sensors/i2c_slave_lis2dw12.sv \
                        sensors/i2c_slave_adpd144ri.sv
TOP_PIPELINE_VCD     := $(WAVE_DIR)/top_pipeline_tb.vcd

$(TOP_PIPELINE_VVP): $(TOP_PIPELINE_SOURCES)
	$(IVERILOG) -g2012 -grelative-include -I $(RTL_DIR) -s $(TOP_PIPELINE_TOP) -o $@ $^

.PHONY: sim-top-pipeline
sim-top-pipeline: $(TOP_PIPELINE_VVP)
	@echo "== Running $(TOP_PIPELINE_TOP) (VCD -> $(TOP_PIPELINE_VCD)) =="
	@mkdir -p $(WAVE_DIR)
	@cd $(WAVE_DIR) && $(VVP) $(abspath $(TOP_PIPELINE_VVP)) +DATA_DIR=$(abspath $(MAKEFILE_DIR)/sim/data)

# ============================================================
# Cocotb: top -> taketwo feature load check
# ============================================================

TOP_MLP_FEATURES_TOP    := sim_top_mlp_features
TOP_MLP_FEATURES_TOP_V  := $(TB_DIR)/sim_top_mlp_features.sv
TOP_MLP_FEATURES_VVP    := sim_top_mlp_features.vvp
TOP_MLP_FEATURES_PYMOD  := test_top_mlp_features
TOP_MLP_FEATURES_SRCS   := \
  $(TOP_MLP_FEATURES_TOP_V) \
  $(UNIFIED_TOP_RTL_SRCS) \
  sensors/i2c_slave_lis2dw12.sv \
  sensors/i2c_slave_adpd144ri.sv

$(TOP_MLP_FEATURES_VVP): $(TOP_MLP_FEATURES_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -I $(RTL_DIR) -s $(TOP_MLP_FEATURES_TOP) -o $@ $(TOP_MLP_FEATURES_SRCS)

.PHONY: test-top-mlp-features
test-top-mlp-features: $(TOP_MLP_FEATURES_VVP)
	@$(SELF_MAKE) FW_VARIANT=test_top_feature_ml_cpu firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "[COCOTB] Running $(TOP_MLP_FEATURES_PYMOD) on $(TOP_MLP_FEATURES_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_MLP_FEATURES_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_MLP_FEATURES_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(TOP_MLP_FEATURES_VVP))

# ============================================================
# Cocotb: shared unified-top environment + reset/init smoke test
# ============================================================

TOP_UNIFIED_ENV_TOP    := sim_top_unified_env
TOP_UNIFIED_ENV_TOP_V  := $(TB_DIR)/sim_top_unified_env.sv
TOP_UNIFIED_ENV_VVP    := $(BUILD_DIR)/$(TOP_UNIFIED_ENV_TOP).vvp
TOP_UNIFIED_ENV_PYMOD  := test_top_unified_reset_init
TOP_UNIFIED_ENV_SRCS   := \
  $(TOP_UNIFIED_ENV_TOP_V) \
  $(UNIFIED_TOP_RTL_SRCS) \
  $(TB_DIR)/spi_flash_model.v \
  sensors/i2c_slave_lis2dw12.sv \
  sensors/i2c_slave_adpd144ri.sv

$(TOP_UNIFIED_ENV_VVP): $(TOP_UNIFIED_ENV_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_UNIFIED_ENV_TOP) -o $@ $(TOP_UNIFIED_ENV_SRCS)

.PHONY: test-top-unified-reset-init
test-top-unified-reset-init: $(TOP_UNIFIED_ENV_VVP)
	@$(SELF_MAKE) FW_VARIANT=prod_main firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "[COCOTB] Running $(TOP_UNIFIED_ENV_PYMOD) on $(TOP_UNIFIED_ENV_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_UNIFIED_ENV_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_UNIFIED_ENV_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(TOP_UNIFIED_ENV_VVP))

TOP_UNIFIED_RUNTIME_PYMOD := test_top_unified_runtime

.PHONY: test-top-unified-host-i2c
test-top-unified-host-i2c: $(TOP_UNIFIED_ENV_VVP)
	@echo "[COCOTB] Running host-I2C runtime check on $(TOP_UNIFIED_ENV_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_UNIFIED_ENV_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_UNIFIED_RUNTIME_PYMOD); \
	export COCOTB_TEST_FILTER=test_host_i2c_registers_and_score_visibility; \
	$(call RUN_COCOTB_ICARUS,$(TOP_UNIFIED_ENV_VVP))

.PHONY: test-top-unified-prod-loop
test-top-unified-prod-loop: $(TOP_UNIFIED_ENV_VVP)
	@echo "[COCOTB] Running repeated production-loop smoke check on $(TOP_UNIFIED_ENV_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_UNIFIED_ENV_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_UNIFIED_RUNTIME_PYMOD); \
	export COCOTB_TEST_FILTER=test_repeated_production_loop_smoke; \
	$(call RUN_COCOTB_ICARUS,$(TOP_UNIFIED_ENV_VVP))

.PHONY: test-top-unified-forced-wake-irq
test-top-unified-forced-wake-irq: $(TOP_UNIFIED_ENV_VVP)
	@echo "[COCOTB] Running forced wake/IRQ corner check on $(TOP_UNIFIED_ENV_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_UNIFIED_ENV_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_UNIFIED_RUNTIME_PYMOD); \
	export COCOTB_TEST_FILTER=test_reset_corner_cases_with_forced_wake_and_irq; \
	$(call RUN_COCOTB_ICARUS,$(TOP_UNIFIED_ENV_VVP))

.PHONY: test-top-unified-runtime
test-top-unified-runtime: test-top-unified-host-i2c test-top-unified-prod-loop test-top-unified-forced-wake-irq
	@true

# ============================================================
# Bare taketwo_wrap: canonical_v1 isolated golden-vector check
# ============================================================

.PHONY: test-ml-canonical-v1
test-ml-canonical-v1:
	@echo "[COCOTB] Running isolated taketwo_wrap canonical_v1 check"
	@$(MAKE) -C $(TB_DIR)/ml MODULE=ml_tb_canonical

# ============================================================
# Cocotb: unified-top golden-vector check via golden_vectors.py
# ============================================================

TOP_ML_GOLDEN_ENV_TOP    := sim_top_ml_golden_env
TOP_ML_GOLDEN_ENV_TOP_V  := $(TB_DIR)/sim_top_ml_golden_env.sv
TOP_ML_GOLDEN_ENV_VVP    := $(BUILD_DIR)/$(TOP_ML_GOLDEN_ENV_TOP).vvp
TOP_ML_GOLDEN_ENV_PYMOD  := test_top_ml_golden_vector
TOP_ML_GOLDEN_ENV_SRCS   := \
  $(TOP_ML_GOLDEN_ENV_TOP_V) \
  $(UNIFIED_TOP_RTL_SRCS) \
  $(TB_DIR)/spi_flash_model.v \
  sensors/i2c_slave_lis2dw12.sv \
  sensors/i2c_slave_adpd144ri.sv

$(TOP_ML_GOLDEN_ENV_VVP): $(TOP_ML_GOLDEN_ENV_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_ML_GOLDEN_ENV_TOP) -o $@ $(TOP_ML_GOLDEN_ENV_SRCS)

.PHONY: test-top-ml-golden-vector-unified
test-top-ml-golden-vector-unified: $(TOP_ML_GOLDEN_ENV_VVP)
	@$(SELF_MAKE) FW_VARIANT=test_top_ml_golden_vector_unified firmware
	@$(SELF_MAKE) $(TAKETWO_PARAMS_HEX)
	@echo "[COCOTB] Running $(TOP_ML_GOLDEN_ENV_PYMOD) on $(TOP_ML_GOLDEN_ENV_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_ML_GOLDEN_ENV_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_ML_GOLDEN_ENV_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(TOP_ML_GOLDEN_ENV_VVP))

# ============================================================
# Cocotb: unified top feature latch/MMIO check
# ============================================================

TOP_FEATURE_MMIO_TOP    := sim_top_feature_mmio_unified
TOP_FEATURE_MMIO_TOP_V  := $(TB_DIR)/sim_top_feature_mmio_unified.sv
TOP_FEATURE_MMIO_VVP    := sim_top_feature_mmio_unified.vvp
TOP_FEATURE_MMIO_PYMOD  := test_top_feature_mmio_unified
TOP_FEATURE_MMIO_SRCS   := \
  $(TOP_FEATURE_MMIO_TOP_V) \
  $(UNIFIED_TOP_RTL_SRCS) \
  $(TB_DIR)/spi_flash_model.v \
  sensors/i2c_slave_lis2dw12.sv \
  sensors/i2c_slave_adpd144ri.sv

$(TOP_FEATURE_MMIO_VVP): $(TOP_FEATURE_MMIO_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_FEATURE_MMIO_TOP) -o $@ $(TOP_FEATURE_MMIO_SRCS)

.PHONY: test-top-feature-mmio-unified
test-top-feature-mmio-unified: $(TOP_FEATURE_MMIO_VVP)
	@echo "[COCOTB] Running $(TOP_FEATURE_MMIO_PYMOD) on $(TOP_FEATURE_MMIO_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_FEATURE_MMIO_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_FEATURE_MMIO_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(TOP_FEATURE_MMIO_VVP))

# ============================================================
# Cocotb: sensor pipeline debug mode test
# ============================================================

CHIP_CORE_DEBUG_TOP    := sim_chip_core_debug_modes
CHIP_CORE_DEBUG_TOP_V  := $(TB_DIR)/sim_chip_core_debug_modes.sv
CHIP_CORE_DEBUG_VVP    := $(BUILD_DIR)/$(CHIP_CORE_DEBUG_TOP).vvp
CHIP_CORE_DEBUG_PYMOD  := test_chip_core_debug_modes
CHIP_CORE_DEBUG_SRCS   := \
  $(CHIP_CORE_DEBUG_TOP_V) \
  $(RTL_DIR)/chip_core.sv \
  $(UNIFIED_TOP_RTL_SRCS) \
  sensors/i2c_slave_lis2dw12.sv \
  sensors/i2c_slave_adpd144ri.sv

$(CHIP_CORE_DEBUG_VVP): $(CHIP_CORE_DEBUG_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(CHIP_CORE_DEBUG_TOP) -o $@ $(CHIP_CORE_DEBUG_SRCS)

.PHONY: test-chip-core-debug-modes
test-chip-core-debug-modes: $(CHIP_CORE_DEBUG_VVP)
	@echo "[COCOTB] Running $(CHIP_CORE_DEBUG_PYMOD) on $(CHIP_CORE_DEBUG_TOP)"
	@export COCOTB_TOPLEVEL=$(CHIP_CORE_DEBUG_TOP); \
	export COCOTB_TEST_MODULES=$(CHIP_CORE_DEBUG_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(CHIP_CORE_DEBUG_VVP))

# ============================================================
# Cocotb: top sensor pipeline stage-by-stage reference
# ============================================================

TOP_SENSOR_PIPELINE_TOP    := sim_top_sensor_pipeline
TOP_SENSOR_PIPELINE_TOP_V  := $(TB_DIR)/sim_top_sensor_pipeline.sv
TOP_SENSOR_PIPELINE_VVP    := $(BUILD_DIR)/$(TOP_SENSOR_PIPELINE_TOP).vvp
TOP_SENSOR_PIPELINE_PYMOD  := test_top_sensor_pipeline
TOP_SENSOR_PIPELINE_SRCS   := \
  $(TOP_SENSOR_PIPELINE_TOP_V) \
  $(UNIFIED_TOP_RTL_SRCS) \
  sensors/i2c_slave_lis2dw12.sv \
  sensors/i2c_slave_adpd144ri.sv

$(TOP_SENSOR_PIPELINE_VVP): $(TOP_SENSOR_PIPELINE_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -DSIM -I $(RTL_DIR) -s $(TOP_SENSOR_PIPELINE_TOP) -o $@ $(TOP_SENSOR_PIPELINE_SRCS)

.PHONY: test-top-sensor-pipeline
test-top-sensor-pipeline: $(TOP_SENSOR_PIPELINE_VVP)
	@echo "[COCOTB] Running $(TOP_SENSOR_PIPELINE_PYMOD) on $(TOP_SENSOR_PIPELINE_TOP)"
	@export COCOTB_TOPLEVEL=$(TOP_SENSOR_PIPELINE_TOP); \
	export COCOTB_TEST_MODULES=$(TOP_SENSOR_PIPELINE_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(TOP_SENSOR_PIPELINE_VVP))

.PHONY: test-top-pipeline
test-top-pipeline: test-top-sensor-pipeline
	@true

.PHONY: test-chip-debug-feature-regression
test-chip-debug-feature-regression: test-chip-core-debug-modes test-MSSD-engine-ref test-motion-process-ref test-ppg-process-ref test-top-sensor-pipeline
	@true

.PHONY: test-top-e2e-inference
test-top-e2e-inference: test-top-sensor-pipeline
	@true

# ============================================================
# Cocotb: module scoreboards against Python references
# ============================================================

MOTION_REF_TOP     := sim_motion_process_ref
MOTION_REF_TOP_V   := $(TB_DIR)/sim_motion_process_ref.sv
MOTION_REF_VVP     := $(BUILD_DIR)/$(MOTION_REF_TOP).vvp
MOTION_REF_PYMOD   := test_motion_process_ref
MOTION_REF_SRCS    := $(MOTION_REF_TOP_V) $(RTL_DIR)/motion_process.sv

$(MOTION_REF_VVP): $(MOTION_REF_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -s $(MOTION_REF_TOP) -o $@ $(MOTION_REF_SRCS)

.PHONY: test-motion-process-ref
test-motion-process-ref: $(MOTION_REF_VVP)
	@export COCOTB_TOPLEVEL=$(MOTION_REF_TOP); \
	export COCOTB_TEST_MODULES=$(MOTION_REF_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(MOTION_REF_VVP))

PPG_REF_TOP      := sim_ppg_process_ref
PPG_REF_TOP_V    := $(TB_DIR)/sim_ppg_process_ref.sv
PPG_REF_VVP      := $(BUILD_DIR)/$(PPG_REF_TOP).vvp
PPG_REF_PYMOD    := test_ppg_process_ref
PPG_REF_SRCS     := $(PPG_REF_TOP_V) $(RTL_DIR)/ppg_process.sv

$(PPG_REF_VVP): $(PPG_REF_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -s $(PPG_REF_TOP) -o $@ $(PPG_REF_SRCS)

.PHONY: test-ppg-process-ref
test-ppg-process-ref: $(PPG_REF_VVP)
	@export COCOTB_TOPLEVEL=$(PPG_REF_TOP); \
	export COCOTB_TEST_MODULES=$(PPG_REF_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(PPG_REF_VVP))

MSSD_REF_TOP      := sim_mssd_engine_ref
MSSD_REF_TOP_V    := $(TB_DIR)/sim_mssd_engine_ref.sv
MSSD_REF_VVP      := $(BUILD_DIR)/$(MSSD_REF_TOP).vvp
MSSD_REF_PYMOD    := test_mssd_engine_ref
MSSD_REF_SRCS     := $(MSSD_REF_TOP_V) $(RTL_DIR)/mssd_engine.sv

$(MSSD_REF_VVP): $(MSSD_REF_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -s $(MSSD_REF_TOP) -o $@ $(MSSD_REF_SRCS)

.PHONY: test-MSSD-engine-ref
test-MSSD-engine-ref: $(MSSD_REF_VVP)
	@export COCOTB_TOPLEVEL=$(MSSD_REF_TOP); \
	export COCOTB_TEST_MODULES=$(MSSD_REF_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(MSSD_REF_VVP))

SIGNAL_QUALITY_REF_TOP      := sim_signal_quality_ref
SIGNAL_QUALITY_REF_TOP_V    := $(TB_DIR)/sim_signal_quality_ref.sv
SIGNAL_QUALITY_REF_VVP      := $(BUILD_DIR)/$(SIGNAL_QUALITY_REF_TOP).vvp
SIGNAL_QUALITY_REF_PYMOD    := test_signal_quality_ref
SIGNAL_QUALITY_REF_SRCS     := $(SIGNAL_QUALITY_REF_TOP_V) $(RTL_DIR)/signal_quality.sv

$(SIGNAL_QUALITY_REF_VVP): $(SIGNAL_QUALITY_REF_SRCS)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -s $(SIGNAL_QUALITY_REF_TOP) -o $@ $(SIGNAL_QUALITY_REF_SRCS)

.PHONY: test-signal-quality-ref
test-signal-quality-ref: $(SIGNAL_QUALITY_REF_VVP)
	@export COCOTB_TOPLEVEL=$(SIGNAL_QUALITY_REF_TOP); \
	export COCOTB_TEST_MODULES=$(SIGNAL_QUALITY_REF_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(SIGNAL_QUALITY_REF_VVP))


# ============================================================
# HOST I2C TARGET
# ============================================================

HOST_I2C_TARGET_TOP     := tb_host_i2c_target
HOST_I2C_TARGET_VVP     := $(BUILD_DIR)/$(HOST_I2C_TARGET_TOP).vvp
HOST_I2C_TARGET_SOURCES := sim/tb/tb_host_i2c_target.sv \
                           $(RTL_DIR)/host_i2c_target.v \
                           $(RTL_DIR)/host_i2c_bridge_regs.v

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
HOST_I2C_IRQC_PROXY_SOURCES := sim/tb/tb_host_i2c_irqc_proxy.sv \
                               $(SOC_RTL_SRCS)

$(HOST_I2C_IRQC_PROXY_VVP): $(HOST_I2C_IRQC_PROXY_SOURCES)
	$(IVERILOG) -g2012 -s $(HOST_I2C_IRQC_PROXY_TOP) -o $@ $^

.PHONY: sim-host-i2c-irqc-proxy
sim-host-i2c-irqc-proxy: $(HOST_I2C_IRQC_PROXY_VVP)
	@echo "== Running $(HOST_I2C_IRQC_PROXY_TOP) =="
	$(VVP) $(HOST_I2C_IRQC_PROXY_VVP)

# ============================================================
# GLOBAL TIMER / EPOCH TIMEBASE
# ============================================================

GLOBALTIMER_TOP     := globaltimer_tb
GLOBALTIMER_VVP     := $(BUILD_DIR)/$(GLOBALTIMER_TOP).vvp
GLOBALTIMER_SOURCES := sim/tb/globaltimer_tb.sv $(RTL_DIR)/globaltimer.sv
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
LOGIT_TO_CONF_SOURCES := sim/tb/logit_to_confidence_tb.sv $(RTL_DIR)/logit_to_confidence.sv
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
# Cocotb: spi_boot_ctrl standalone SPI boot load verification
# ============================================================

SPI_BOOT_CTRL_TOP    := sim_spi_boot_ctrl
SPI_BOOT_CTRL_TOP_V  := $(TB_DIR)/sim_spi_boot_ctrl.v
SPI_BOOT_CTRL_VVP    := $(BUILD_DIR)/$(SPI_BOOT_CTRL_TOP).vvp
SPI_BOOT_CTRL_PYMOD  := test_spi_boot_ctrl

SPI_BOOT_CTRL_SRCS := \
  $(SPI_BOOT_CTRL_TOP_V) \
  $(RTL_DIR)/spi_boot_ctrl.v \
  $(RTL_DIR)/simple_sram.v \
  $(TB_DIR)/spi_flash_model.v \
  $(MAKEFILE_DIR)/../ip/gf180mcu_fd_ip_sram__sram512x8m8wm1.v

$(SPI_BOOT_CTRL_VVP): $(SPI_BOOT_CTRL_SRCS) | $(BUILD_DIR)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -s $(SPI_BOOT_CTRL_TOP) -o $@ $(SPI_BOOT_CTRL_SRCS)

.PHONY: test-spi-boot-ctrl
test-spi-boot-ctrl: $(SPI_BOOT_CTRL_VVP)
	@echo "[COCOTB] Running $(SPI_BOOT_CTRL_PYMOD) on $(SPI_BOOT_CTRL_TOP)"
	@export COCOTB_TOPLEVEL=$(SPI_BOOT_CTRL_TOP); \
	export COCOTB_TEST_MODULES=$(SPI_BOOT_CTRL_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(SPI_BOOT_CTRL_VVP))

# ============================================================
# Cocotb: external IRQ source injection through top.sv
# ============================================================

IRQ_STATES_TOP    := sim_irq_test
IRQ_STATES_VVP    := $(BUILD_DIR)/$(IRQ_STATES_TOP).vvp
IRQ_STATES_PYMOD  := test_irq_states

IRQ_STATES_SRCS := \
	$(TB_DIR)/sim_irq_test.sv \
	$(TB_DIR)/spi_flash_model.v \
	$(UNIFIED_TOP_RTL_SRCS)

$(IRQ_STATES_VVP): $(IRQ_STATES_SRCS) | $(BUILD_DIR)
	@echo "[COCOTB] Building $@"
	$(IVERILOG) -g2012 -grelative-include -DTAKETWO_V_SOURCE -I $(RTL_DIR) \
	  -s $(IRQ_STATES_TOP) -o $@ $(IRQ_STATES_SRCS)

.PHONY: test-irq-states
test-irq-states: $(IRQ_STATES_VVP)
	@$(SELF_MAKE) FW_VARIANT=irq_test firmware
	@echo "[COCOTB] Running $(IRQ_STATES_PYMOD) on $(IRQ_STATES_TOP)"
	@export COCOTB_TOPLEVEL=$(IRQ_STATES_TOP); \
	export COCOTB_TEST_MODULES=$(IRQ_STATES_PYMOD); \
	$(call RUN_COCOTB_ICARUS,$(IRQ_STATES_VVP))

# ============================================================
# ML LOGIT SRAM MMIO (compile/elab check)
# ============================================================

ML_LOGIT_SRAM_MMIO_TOP     := ml_logit_sram_mmio
ML_LOGIT_SRAM_MMIO_VVP     := $(BUILD_DIR)/$(ML_LOGIT_SRAM_MMIO_TOP).vvp
ML_LOGIT_SRAM_MMIO_SOURCES := $(RTL_DIR)/ml_logit_sram_mmio.v

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
                           $(RTL_DIR)/i2c_master.sv \
                           $(RTL_DIR)/accel_reader.sv \
                           $(RTL_DIR)/ppg_fifo_reader.sv \
                           $(RTL_DIR)/motion_process.sv \
                           $(RTL_DIR)/globaltimer.sv \
                           sensors/i2c_slave_lis2dw12.sv \
                           sensors/i2c_slave_adpd144ri.sv
SENSOR_PIPELINE_VCD     := $(WAVE_DIR)/sensor_pipeline.vcd

$(SENSOR_PIPELINE_VVP): $(SENSOR_PIPELINE_SOURCES) | $(BUILD_DIR)
	$(IVERILOG) -g2012 -o $@ $^

.PHONY: sim-sensor-pipeline
sim-sensor-pipeline: $(SENSOR_PIPELINE_VVP)
	$(VVP) $(SENSOR_PIPELINE_VVP)
	
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
	rm -f $(SIM_BUILD)/*.vvp $(SIM_BUILD)/*.vcd $(SIM_BUILD)/*.fst $(SIM_BUILD)/*.gtkw
	rm -f $(WAVE_DIR)/*.vcd
	rm -f $(FW_BUILD)/firmware.elf $(FW_BUILD)/firmware.bin $(FW_BUILD)/firmware.hex
