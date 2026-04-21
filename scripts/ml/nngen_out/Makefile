# Makefile

# defaults
SIM ?= icarus
TOPLEVEL_LANG ?= verilog
IP_DIR ?= ../../../ip 

VERILOG_SOURCES += $(PWD)/taketwo_wrap.v $(PWD)/taketwo.v $(IP_DIR)/gf180mcu_fd_ip_sram__sram512x8m8wm1.v 
# use VHDL_SOURCES for VHDL files

# COCOTB_TOPLEVEL is the name of the toplevel module in your Verilog or VHDL file
COCOTB_TOPLEVEL = taketwo_wrap

# COCOTB_TEST_MODULES is the basename of the Python test file(s)
COCOTB_TEST_MODULES = ml_tb

COCOTB_LOG_LEVEL = WARNING

# include cocotb's make rules to take care of the simulator setup
include $(shell cocotb-config --makefiles)/Makefile.sim