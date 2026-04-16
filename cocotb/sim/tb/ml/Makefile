SIM ?= icarus
TOPLEVEL_LANG ?= verilog

# RTL path relative to sim/tb/ml
RTL_DIR := ../../../../src
IP_DIR := ../../../../ip

VERILOG_SOURCES := \
    $(RTL_DIR)/taketwo.v \
    $(RTL_DIR)/taketwo_wrap.v \
    $(IP_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v 

TOPLEVEL := taketwo_wrap
MODULE ?= ml_tb

COCOTB_LOG_LEVEL = WARNING

include $(shell cocotb-config --makefiles)/Makefile.sim
