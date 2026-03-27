// dummy_top.v
`timescale 1ns/1ps

module dummy_top();

    // ---------------------------------------------------
    // SoC top-level
    // ---------------------------------------------------
    soc_top soc_top_inst ();

    // ---------------------------------------------------
    // Accelerator wrapper
    // ---------------------------------------------------
    taketwo_wrap taketwo_wrap_inst ();

    // ---------------------------------------------------
    // ML AXI-Lite bridge
    // ---------------------------------------------------
    ml_axil_bridge_mmio ml_axil_inst ();

    // ---------------------------------------------------
    // CPU to ML interface
    // ---------------------------------------------------
    cpu_to_ml cpu2ml_inst ();

    // ---------------------------------------------------
    // Logic modules
    // ---------------------------------------------------
    logit_to_confidence logit2conf_inst ();
    reset_ctrl reset_inst ();
    host_i2c_bridge_regs host_i2c_inst ();

endmodule