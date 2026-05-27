`timescale 1ns/1ps

`define SLOT_1X1

module chip_top_sim_wrap #(
    // Firmware and weight hex paths are passed at runtime via plusargs.
    // The current top.sv architecture uses one shared SPI flash bus:
    //   words [0:1023]     : boot firmware image
    //   words [1024:$end]  : ML weights fetched by weight_flash_axi after boot
    // Parameters kept as overrides for direct instantiation (leave "" to use plusargs).
    parameter FIRMWARE_HEX       = "",
    parameter WEIGHT_HEX         = "",
    parameter integer FLASH_WORDS = 3072,
    parameter integer WEIGHT_FLASH_OFFSET_WORDS = 1024
)(
    input  wire        clk_PAD,
    input  wire        rst_n_PAD,
    input  wire [11:0] input_PAD,
    output wire        alarm_o          // driven by bidir_PAD[0] (alarm output pad)
);

    wire [39:0] bidir_PAD;
    wire  [1:0] analog_PAD;

    wire        sim_req_o;
    wire  [6:0] sim_addr_o;
    wire  [7:0] sim_reg_o;
    wire  [7:0] sim_len_o;
    wire        sim_write_o;
    wire  [7:0] sim_wdata_o;
    wire        sim_ack_i;
    wire  [7:0] sim_rdata_i;
    wire        sim_rvalid_i;
    wire        sim_rlast_i;
    wire        sim_err_i;

    // Sensor mux outputs
    wire        accel_sim_ack,    ppg_sim_ack;
    wire  [7:0] accel_sim_rdata,  ppg_sim_rdata;
    wire        accel_sim_rvalid, ppg_sim_rvalid;
    wire        accel_sim_rlast,  ppg_sim_rlast;
    wire        accel_sim_err,    ppg_sim_err;

    localparam [6:0] ACC_ADDR = 7'h19;
    localparam [6:0] PPG_ADDR = 7'h64;

    // Route sim bus responses to the correct sensor model by I2C address
    assign sim_ack_i    = (sim_addr_o == ACC_ADDR) ? accel_sim_ack    :
                          (sim_addr_o == PPG_ADDR) ? ppg_sim_ack      : 1'b0;
    assign sim_rdata_i  = (sim_addr_o == ACC_ADDR) ? accel_sim_rdata  :
                          (sim_addr_o == PPG_ADDR) ? ppg_sim_rdata    : 8'h00;
    assign sim_rvalid_i = (sim_addr_o == ACC_ADDR) ? accel_sim_rvalid :
                          (sim_addr_o == PPG_ADDR) ? ppg_sim_rvalid   : 1'b0;
    assign sim_rlast_i  = (sim_addr_o == ACC_ADDR) ? accel_sim_rlast  :
                          (sim_addr_o == PPG_ADDR) ? ppg_sim_rlast    : 1'b0;
    assign sim_err_i    = (sim_addr_o == ACC_ADDR) ? accel_sim_err    :
                          (sim_addr_o == PPG_ADDR) ? ppg_sim_err      : 1'b1;

    // Alarm is bidir_PAD[0] driven by the core (OE=1, output only)
    assign alarm_o = bidir_PAD[0];


    chip_top
    `ifndef FUNCTIONAL
    #(
        .FIRMWARE_HEX           (""),   // spi_boot_ctrl loads firmware; simple_sram skips readmemh
        .WEIGHT_INIT_HEX        (""),   // weight_flash_axi streams from flash; no preload needed
        .CLK_HZ                 (1000),
        .GT_CLK_HZ              (1000),
        .GT_EPOCH_HZ            (100),
        .GT_EPOCH_COUNT_MAX     (300),
        .ACC_POLL_PERIOD_TICKS  (8),
        .PPG_POLL_PERIOD_TICKS  (2),
        .PPG_WATERMARK          (8),
        .PPG_MAX_BURST_SAMPLES  (32),
        .TIMER_RELOAD_DEFAULT   (1000)
    )
    `endif
    u_chip_top (
        .clk_PAD    (clk_PAD),
        .rst_n_PAD  (rst_n_PAD),
        .input_PAD  (input_PAD),
        .bidir_PAD  (bidir_PAD),
        .analog_PAD (analog_PAD)
        // sim bus only exists when SIM is defined — not present in GL netlist
        `ifdef SIM
        ,.sim_req_o    (sim_req_o)
        ,.sim_addr_o   (sim_addr_o)
        ,.sim_reg_o    (sim_reg_o)
        ,.sim_len_o    (sim_len_o)
        ,.sim_write_o  (sim_write_o)
        ,.sim_wdata_o  (sim_wdata_o)
        ,.sim_ack_i    (sim_ack_i)
        ,.sim_rdata_i  (sim_rdata_i)
        ,.sim_rvalid_i (sim_rvalid_i)
        ,.sim_rlast_i  (sim_rlast_i)
        ,.sim_err_i    (sim_err_i)
        `endif
    );

    // Shared external SPI flash. spi_boot_ctrl owns this bus until boot_done;
    // weight_flash_axi owns the same bus afterward and reads weights at byte
    // address 0x1000, i.e. word offset 1024.
    spi_flash_model #(
        .FLASH_WORDS    (FLASH_WORDS),
        .FLASH_INIT_HEX ("")   // loaded at sim start via $readmemh in initial block below
    ) u_boot_flash (
        .spi_clk  (bidir_PAD[1]),
        .spi_cs_n (bidir_PAD[3]),
        .spi_mosi (bidir_PAD[2]),
        .spi_miso (bidir_PAD[4])
    );

    i2c_slave_lis2dw12 #(
        .I2C_ADDR (ACC_ADDR)
    ) u_accel (
        .clk     (clk_PAD),
        .resetn  (rst_n_PAD),
        .sim_req    (sim_req_o),
        .sim_addr   (sim_addr_o),
        .sim_reg    (sim_reg_o),
        .sim_len    (sim_len_o),
        .sim_ack    (accel_sim_ack),
        .sim_rdata  (accel_sim_rdata),
        .sim_rvalid (accel_sim_rvalid),
        .sim_rlast  (accel_sim_rlast),
        .sim_err    (accel_sim_err)
    );


    i2c_slave_adpd144ri #(
        .I2C_ADDR (PPG_ADDR)
    ) u_ppg (
        .clk      (clk_PAD),
        .resetn   (rst_n_PAD),
        .sim_req    (sim_req_o),
        .sim_addr   (sim_addr_o),
        .sim_reg    (sim_reg_o),
        .sim_len    (sim_len_o),
        .sim_write  (sim_write_o),
        .sim_wdata  (sim_wdata_o),
        .sim_ack    (ppg_sim_ack),
        .sim_rdata  (ppg_sim_rdata),
        .sim_rvalid (ppg_sim_rvalid),
        .sim_rlast  (ppg_sim_rlast),
        .sim_err    (ppg_sim_err)
    );

    string fw_hex, wt_hex;
    integer k;
    initial begin
        // Firmware flash
        if (FIRMWARE_HEX != "")
            fw_hex = FIRMWARE_HEX;
        else if (!$value$plusargs("FIRMWARE_HEX=%s", fw_hex))
            fw_hex = "";

        if (WEIGHT_FLASH_OFFSET_WORDS >= FLASH_WORDS) begin
            $fatal(1, "chip_top_sim_wrap: WEIGHT_FLASH_OFFSET_WORDS must be less than FLASH_WORDS");
        end

        if (fw_hex != "") begin
            $readmemh(fw_hex, u_boot_flash.mem, 0, WEIGHT_FLASH_OFFSET_WORDS - 1);
            $display("chip_top_sim_wrap: boot flash loaded from %s", fw_hex);
        end else begin
            $fatal(1, "chip_top_sim_wrap: no FIRMWARE_HEX — pass +FIRMWARE_HEX=<abs_path>");
        end

        // Weight flash
        if (WEIGHT_HEX != "")
            wt_hex = WEIGHT_HEX;
        else if (!$value$plusargs("WEIGHT_HEX=%s", wt_hex))
            wt_hex = "";

        if (wt_hex != "") begin
            $readmemh(wt_hex, u_boot_flash.mem, WEIGHT_FLASH_OFFSET_WORDS, FLASH_WORDS - 1);
            $display("chip_top_sim_wrap: weight flash loaded into shared flash at word offset %0d from %s",
                     WEIGHT_FLASH_OFFSET_WORDS, wt_hex);
        end else begin
            $fatal(1, "chip_top_sim_wrap: no WEIGHT_HEX — pass +WEIGHT_HEX=<abs_path>");
        end

        // taketwo SRAM zero-init — RTL paths only; GL netlist maps these to SRAM macros
        `ifndef FUNCTIONAL
        for (k = 0; k < 512; k = k + 1) begin
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id0_0.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id0_0.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id0_1.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id0_1.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id1_0.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id1_0.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id1_1.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id1_1.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id2_0.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id2_0.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id2_1.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id2_1.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id3_0.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id3_0.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id3_1.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id3_1.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id4_0.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id4_0.mem_bot.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id4_1.mem_top.mem[k] = 8'h00;
            u_chip_top.i_chip_core.u_top.u_taketwo_wrap.u_core.inst_ram_w16_l512_id4_1.mem_bot.mem[k] = 8'h00;
        end
        `endif
    end

endmodule
