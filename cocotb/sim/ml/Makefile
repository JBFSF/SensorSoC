SIM ?= icarus
TOPLEVEL_LANG ?= verilog

# RTL path relative to sim/tb/ml
RTL_DIR := ../../../rtl

VERILOG_SOURCES := \
    $(RTL_DIR)/taketwo.v \
    $(RTL_DIR)/taketwo_wrap.v

TOPLEVEL := taketwo_wrap
MODULE := ml_tb

COCOTB_LOG_LEVEL = WARNING

include $(shell cocotb-config --makefiles)/Makefile.sim