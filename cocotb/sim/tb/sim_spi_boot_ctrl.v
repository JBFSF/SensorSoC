`timescale 1ns/1ps

// Standalone wrapper for spi_boot_ctrl cocotb test.
// Wires together: spi_boot_ctrl + simple_sram + spi_flash_model.
// SRAM starts zeroed (INIT_HEX=""); flash is initialized from FLASH_INIT_HEX.
// After boot_done asserts, sram.mem should match flash.mem word-for-word.
module sim_spi_boot_ctrl #(
    parameter integer WORDS          = 16,
    parameter         FLASH_INIT_HEX = "sim/tb/boot_test_pattern.hex",
    parameter integer CLK_DIV        = 2
)(
    input  wire clk,
    input  wire resetn,
    output wire boot_done
);

    wire        spi_clk;
    wire        spi_mosi;
    wire        spi_miso;
    wire        spi_cs_n;

    wire        sram_valid;
    wire        sram_ready;
    wire [3:0]  sram_wstrb;
    wire [31:0] sram_addr;
    wire [31:0] sram_wdata;
    wire [31:0] sram_rdata;

    spi_boot_ctrl #(
        .WORDS     (WORDS),
        .CLK_DIV   (CLK_DIV),
        .FLASH_ADDR(24'h000000)
    ) u_boot_ctrl (
        .clk         (clk),
        .resetn      (resetn),
        .spi_clk_o   (spi_clk),
        .spi_mosi_o  (spi_mosi),
        .spi_miso_i  (spi_miso),
        .spi_cs_n_o  (spi_cs_n),
        .sram_valid_o(sram_valid),
        .sram_wstrb_o(sram_wstrb),
        .sram_addr_o (sram_addr),
        .sram_wdata_o(sram_wdata),
        .boot_done   (boot_done)
    );

    simple_sram #(
        .WORDS   (WORDS),
        .INIT_HEX("")
    ) u_sram (
        .clk   (clk),
        .resetn(resetn),
        .valid (sram_valid),
        .ready (sram_ready),
        .wstrb (sram_wstrb),
        .addr  (sram_addr),
        .wdata (sram_wdata),
        .rdata (sram_rdata)
    );

    spi_flash_model #(
        .FLASH_WORDS   (WORDS),
        .FLASH_INIT_HEX(FLASH_INIT_HEX)
    ) u_flash (
        .spi_clk (spi_clk),
        .spi_cs_n(spi_cs_n),
        .spi_mosi(spi_mosi),
        .spi_miso(spi_miso)
    );

endmodule
