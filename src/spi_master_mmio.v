`timescale 1ns/1ps

// Firmware controls CS and each write to DATA triggers one 8-bit transfer.
module spi_master_mmio #(
    parameter [31:0] BASE_ADDR       = 32'h0300_A000,
    parameter [31:0] DEFAULT_DIVIDER = 32'd2
)(
    input  wire        clk,
    input  wire        resetn,

    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,
    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    output reg         spi_clk_o,
    output wire        spi_mosi_o,
    input  wire        spi_miso_i,
    output reg         spi_cs_n_o
);

    wire        sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);
    wire [31:0] off = mem_addr - BASE_ADDR;
    wire        wr  = sel && (mem_wstrb != 4'h0);

    localparam OFF_CS      = 32'h00;
    localparam OFF_STATUS  = 32'h04;
    localparam OFF_DATA    = 32'h08;
    localparam OFF_DIVIDER = 32'h0C;

    reg [31:0] divider_reg;
    reg [7:0]  rx_data;
    reg        busy;
    reg [7:0]  tx_shift;
    reg [7:0]  rx_shift;
    reg [2:0]  bit_cnt;
    reg [31:0] div_cnt;
    reg        sck_phase;

    assign spi_mosi_o = tx_shift[7];

    always @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            mem_ready   <= 1'b0;
            mem_rdata   <= 32'h0;
            spi_cs_n_o  <= 1'b1;
            spi_clk_o   <= 1'b0;
            divider_reg <= DEFAULT_DIVIDER;
            rx_data     <= 8'h0;
            busy        <= 1'b0;
            tx_shift    <= 8'h0;
            rx_shift    <= 8'h0;
            bit_cnt     <= 3'd7;
            div_cnt     <= 32'h0;
            sck_phase   <= 1'b0;
        end else begin
            mem_ready <= 1'b0;

            if (sel) begin
                mem_ready <= 1'b1;
                case (off)
                    OFF_CS:      mem_rdata <= {31'h0, spi_cs_n_o};
                    OFF_STATUS:  mem_rdata <= {31'h0, busy};
                    OFF_DATA:    mem_rdata <= {24'h0, rx_data};
                    OFF_DIVIDER: mem_rdata <= divider_reg;
                    default:     mem_rdata <= 32'h0;
                endcase

                if (wr) begin
                    case (off)
                        OFF_CS: begin
                            if (mem_wstrb[0]) spi_cs_n_o <= mem_wdata[0];
                        end
                        OFF_DATA: begin
                            if (mem_wstrb[0] && !busy) begin
                                tx_shift  <= mem_wdata[7:0];
                                bit_cnt   <= 3'd7;
                                div_cnt   <= divider_reg - 1'b1;
                                sck_phase <= 1'b0;
                                busy      <= 1'b1;
                            end
                        end
                        OFF_DIVIDER: begin
                            if (mem_wstrb[0]) divider_reg[ 7: 0] <= mem_wdata[ 7: 0];
                            if (mem_wstrb[1]) divider_reg[15: 8] <= mem_wdata[15: 8];
                            if (mem_wstrb[2]) divider_reg[23:16] <= mem_wdata[23:16];
                            if (mem_wstrb[3]) divider_reg[31:24] <= mem_wdata[31:24];
                        end
                        default: ;
                    endcase
                end
            end

            if (busy) begin
                if (div_cnt != 32'h0) begin
                    div_cnt <= div_cnt - 1'b1;
                end else begin
                    div_cnt <= divider_reg - 1'b1;
                    if (!sck_phase) begin
                        spi_clk_o <= 1'b1;
                        rx_shift  <= {rx_shift[6:0], spi_miso_i};
                        sck_phase <= 1'b1;
                    end else begin
                        spi_clk_o <= 1'b0;
                        sck_phase <= 1'b0;
                        if (bit_cnt == 3'd0) begin
                            rx_data <= rx_shift;
                            busy    <= 1'b0;
                        end else begin
                            tx_shift <= {tx_shift[6:0], 1'b0};
                            bit_cnt  <= bit_cnt - 1'b1;
                        end
                    end
                end
            end
        end
    end

endmodule
