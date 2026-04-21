`timescale 1ns/1ps

// Hardware SPI boot controller.
// On reset, issues a READ (0x03) command to external SPI NOR flash starting
// at FLASH_ADDR, streams WORDS 32-bit words into SRAM via the write port,
// then asserts boot_done. CPU should be held in reset until boot_done.
//
// SPI Mode 0 (CPOL=0 CPHA=0): MOSI is set before the rising edge; MISO is
// sampled on each rising edge after the flash advances it on the falling edge.
module spi_boot_ctrl #(
    parameter integer WORDS      = 16,
    parameter integer CLK_DIV    = 2,
    parameter [23:0]  FLASH_ADDR = 24'h000000
)(
    input  wire        clk,
    input  wire        resetn,

    output reg         spi_clk_o,
    output wire        spi_mosi_o,
    input  wire        spi_miso_i,
    output reg         spi_cs_n_o,

    output reg         sram_valid_o,
    output reg  [3:0]  sram_wstrb_o,
    output reg  [31:0] sram_addr_o,
    output reg  [31:0] sram_wdata_o,

    output reg         boot_done
);

    localparam ST_IDLE        = 4'd0;
    localparam ST_CS_ASSERT   = 4'd1;
    localparam ST_SEND_CMD    = 4'd2;
    localparam ST_SEND_ADDR   = 4'd3;
    localparam ST_RX_BYTE     = 4'd4;
    localparam ST_ASSEMBLE    = 4'd5;
    localparam ST_SRAM_WR     = 4'd6;
    localparam ST_NEXT_WORD   = 4'd7;
    localparam ST_CS_DEASSERT = 4'd8;
    localparam ST_DONE        = 4'd9;

    reg [3:0]  state;
    reg [7:0]  tx_shift;
    reg [2:0]  bit_cnt;
    reg [23:0] addr_shift;
    reg [4:0]  addr_cnt;
    reg [7:0]  rx_shift;
    reg [2:0]  rx_cnt;
    reg [31:0] word_buf;
    reg [1:0]  byte_pos;
    reg [11:0] word_cnt;
    reg [7:0]  div_cnt;
    reg        sck_phase;

    assign spi_mosi_o = (state == ST_SEND_ADDR) ? addr_shift[23] : tx_shift[7];

    always @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            state        <= ST_IDLE;
            spi_clk_o    <= 1'b0;
            spi_cs_n_o   <= 1'b1;
            sram_valid_o <= 1'b0;
            sram_wstrb_o <= 4'h0;
            sram_addr_o  <= 32'h0;
            sram_wdata_o <= 32'h0;
            boot_done    <= 1'b0;
            tx_shift     <= 8'h0;
            bit_cnt      <= 3'd0;
            addr_shift   <= 24'h0;
            addr_cnt     <= 5'd0;
            rx_shift     <= 8'h0;
            rx_cnt       <= 3'd0;
            word_buf     <= 32'h0;
            byte_pos     <= 2'd0;
            word_cnt     <= 12'd0;
            div_cnt      <= 8'd0;
            sck_phase    <= 1'b0;
        end else begin
            case (state)
                ST_IDLE: begin
                    state <= ST_CS_ASSERT;
                end

                ST_CS_ASSERT: begin
                    spi_cs_n_o <= 1'b0;
                    tx_shift   <= 8'h03;
                    bit_cnt    <= 3'd7;
                    div_cnt    <= CLK_DIV - 1;
                    sck_phase  <= 1'b0;
                    state      <= ST_SEND_CMD;
                end

                ST_SEND_CMD: begin
                    if (div_cnt != 8'd0) begin
                        div_cnt <= div_cnt - 8'd1;
                    end else begin
                        div_cnt <= CLK_DIV - 1;
                        if (!sck_phase) begin
                            spi_clk_o <= 1'b1;
                            sck_phase <= 1'b1;
                        end else begin
                            spi_clk_o <= 1'b0;
                            sck_phase <= 1'b0;
                            if (bit_cnt == 3'd0) begin
                                addr_shift <= FLASH_ADDR;
                                addr_cnt   <= 5'd23;
                                state      <= ST_SEND_ADDR;
                            end else begin
                                tx_shift <= {tx_shift[6:0], 1'b0};
                                bit_cnt  <= bit_cnt - 3'd1;
                            end
                        end
                    end
                end

                ST_SEND_ADDR: begin
                    if (div_cnt != 8'd0) begin
                        div_cnt <= div_cnt - 8'd1;
                    end else begin
                        div_cnt <= CLK_DIV - 1;
                        if (!sck_phase) begin
                            spi_clk_o <= 1'b1;
                            sck_phase <= 1'b1;
                        end else begin
                            spi_clk_o <= 1'b0;
                            sck_phase <= 1'b0;
                            if (addr_cnt == 5'd0) begin
                                rx_cnt   <= 3'd7;
                                byte_pos <= 2'd0;
                                state    <= ST_RX_BYTE;
                            end else begin
                                addr_shift <= {addr_shift[22:0], 1'b0};
                                addr_cnt   <= addr_cnt - 5'd1;
                            end
                        end
                    end
                end

                ST_RX_BYTE: begin
                    if (div_cnt != 8'd0) begin
                        div_cnt <= div_cnt - 8'd1;
                    end else begin
                        div_cnt <= CLK_DIV - 1;
                        if (!sck_phase) begin
                            spi_clk_o <= 1'b1;
                            rx_shift  <= {rx_shift[6:0], spi_miso_i};
                            sck_phase <= 1'b1;
                        end else begin
                            spi_clk_o <= 1'b0;
                            sck_phase <= 1'b0;
                            if (rx_cnt == 3'd0) begin
                                state <= ST_ASSEMBLE;
                            end else begin
                                rx_cnt <= rx_cnt - 3'd1;
                            end
                        end
                    end
                end

                ST_ASSEMBLE: begin
                    case (byte_pos)
                        2'd0: word_buf[ 7: 0] <= rx_shift;
                        2'd1: word_buf[15: 8] <= rx_shift;
                        2'd2: word_buf[23:16] <= rx_shift;
                        2'd3: word_buf[31:24] <= rx_shift;
                    endcase
                    if (byte_pos == 2'd3) begin
                        state <= ST_SRAM_WR;
                    end else begin
                        byte_pos <= byte_pos + 2'd1;
                        rx_cnt   <= 3'd7;
                        state    <= ST_RX_BYTE;
                    end
                end

                ST_SRAM_WR: begin
                    sram_valid_o <= 1'b1;
                    sram_wstrb_o <= 4'hF;
                    sram_addr_o  <= {18'b0, word_cnt, 2'b00};
                    sram_wdata_o <= word_buf;
                    state        <= ST_NEXT_WORD;
                end

                ST_NEXT_WORD: begin
                    sram_valid_o <= 1'b0;
                    if (word_cnt == WORDS - 1) begin
                        state <= ST_CS_DEASSERT;
                    end else begin
                        word_cnt <= word_cnt + 12'd1;
                        byte_pos <= 2'd0;
                        rx_cnt   <= 3'd7;
                        state    <= ST_RX_BYTE;
                    end
                end

                ST_CS_DEASSERT: begin
                    spi_cs_n_o <= 1'b1;
                    state      <= ST_DONE;
                end

                ST_DONE: begin
                    boot_done <= 1'b1;
                end

                default: begin
                    state <= ST_IDLE;
                end
            endcase
        end
    end

endmodule
