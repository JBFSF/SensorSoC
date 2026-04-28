`timescale 1ns/1ps

// Wrapper for IRQ test-pin simulation.
// Instantiates top + a boot-SPI flash model (firmware/build/irq_test/firmware.hex).
// Exposes only the 3 test_irq_src_i injection bits, irq_eoi_o, and boot_done_o.
module sim_irq_test #(
    parameter BOOT_FLASH_HEX = "firmware/build/irq_test/firmware.hex"
)(
    input  logic        clk,
    input  logic        resetn,
    input  logic [2:0]  test_irq_src,
    output logic [2:0]  irq_eoi,
    output logic        boot_done
);

    wire boot_spi_clk;
    wire boot_spi_mosi;
    wire boot_spi_miso;
    wire boot_spi_cs_n;

    tri1 sda_bus;

    top #(
        .MEM_WORDS  (8192),
        .BOOT_WORDS (256),
        .CLK_HZ     (1000),
        .GT_CLK_HZ  (1000),
        .GT_EPOCH_HZ(100),
        .GT_EPOCH_COUNT_MAX(16)
    ) u_top (
        .clk_i               (clk),
        .reset_i             (~resetn),
        .i2c_scl_i           (1'b1),
        .i2c_sda_io          (sda_bus),
        .i2c_sda_i           (1'b1),
        .i2c_sda_drive_low_o (),
        .sim_req_o           (),
        .sim_addr_o          (),
        .sim_reg_o           (),
        .sim_len_o           (),
        .sim_write_o         (),
        .sim_wdata_o         (),
        .sim_ack_i           (1'b0),
        .sim_rdata_i         (8'h00),
        .sim_rvalid_i        (1'b0),
        .sim_rlast_i         (1'b0),
        .sim_err_i           (1'b0),
        .feat_valid_o        (),
        .time_feat_o         (),
        .motion_feat_o       (),
        .delta_hr_feat_o     (),
        .mssd_feat_o         (),
        .ml_update_gate_o    (),
        .invalid_reason_o    (),
        .spi_clk_o           (),
        .spi_mosi_o          (),
        .spi_miso_i          (1'b1),
        .spi_cs_n_o          (),
        .boot_spi_clk_o      (boot_spi_clk),
        .boot_spi_mosi_o     (boot_spi_mosi),
        .boot_spi_miso_i     (boot_spi_miso),
        .boot_spi_cs_n_o     (boot_spi_cs_n),
        .epoch_end_o         (),
        .alarm_o             (),
        .test_mode_i         (4'b1011),
        .test_force_irq_i    (1'b0),
        .test_force_wake_i   (1'b0),
        .test_irq_src_i      (test_irq_src),
        .irq_eoi_o           (irq_eoi),
        .boot_done_o         (boot_done),
        .pico_trap_o         (),
        .pico_cpu_clk_en_o   (),
        .pico_mem_valid_o    (),
        .pico_mem_instr_o    (),
        .pico_mem_ready_o    (),
        .pico_mem_wstrb_o    (),
        .pico_mem_addr_o     (),
        .pico_mem_wdata_o    (),
        .pico_irq_o          (),
        .pico_sleeping_o     (),
        .host_i2c_irq_event_o(),
        .ml_irq_o            (),
        .timer_event_o       ()
    );

    spi_flash_model #(
        .FLASH_WORDS   (256),
        .FLASH_INIT_HEX(BOOT_FLASH_HEX)
    ) u_boot_flash (
        .spi_clk (boot_spi_clk),
        .spi_cs_n(boot_spi_cs_n),
        .spi_mosi(boot_spi_mosi),
        .spi_miso(boot_spi_miso)
    );

endmodule
