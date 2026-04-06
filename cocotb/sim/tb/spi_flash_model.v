`timescale 1ns/1ps

// Behavioural SPI NOR flash with READ (0x03) support only.
module spi_flash_model #(
    parameter integer FLASH_WORDS    = 256,
    parameter         FLASH_INIT_HEX = ""
)(
    input  wire spi_clk,
    input  wire spi_cs_n,
    input  wire spi_mosi,
    output reg  spi_miso
);

    reg [31:0] mem [0:FLASH_WORDS-1];
    integer fi;
    initial begin
        for (fi = 0; fi < FLASH_WORDS; fi = fi + 1)
            mem[fi] = 32'h0;
        if (FLASH_INIT_HEX != "")
            $readmemh(FLASH_INIT_HEX, mem);
    end

    localparam ST_CMD    = 2'd0;
    localparam ST_ADDR   = 2'd1;
    localparam ST_DATA   = 2'd2;
    localparam ST_IGNORE = 2'd3;

    reg [1:0]  state;
    reg [7:0]  shift_in;
    reg [4:0]  bit_cnt;
    reg [23:0] addr_shift;
    reg [31:0] byte_addr;
    reg [7:0]  tx_byte;
    reg [2:0]  tx_bit_cnt;

    wire [31:0] cur_word = mem[byte_addr[31:2]];
    wire [7:0]  cur_byte = cur_word[byte_addr[1:0] * 8 +: 8];

    always @(posedge spi_clk or posedge spi_cs_n) begin
        if (spi_cs_n) begin
            state      <= ST_CMD;
            bit_cnt    <= 5'd7;
            shift_in   <= 8'h0;
            addr_shift <= 24'h0;
            byte_addr  <= 32'h0;
        end else begin
            shift_in <= {shift_in[6:0], spi_mosi};
            case (state)
                ST_CMD: begin
                    if (bit_cnt == 5'd0) begin
                        if ({shift_in[6:0], spi_mosi} == 8'h03) begin
                            state   <= ST_ADDR;
                            bit_cnt <= 5'd23;
                        end else begin
                            state <= ST_IGNORE;
                        end
                    end else begin
                        bit_cnt <= bit_cnt - 1'b1;
                    end
                end
                ST_ADDR: begin
                    addr_shift <= {addr_shift[22:0], spi_mosi};
                    if (bit_cnt == 5'd0) begin
                        byte_addr <= {8'h0, addr_shift[22:0], spi_mosi};
                        state     <= ST_DATA;
                        bit_cnt   <= 5'd7;
                    end else begin
                        bit_cnt <= bit_cnt - 1'b1;
                    end
                end
                ST_DATA: begin
                    if (bit_cnt == 5'd0) begin
                        byte_addr <= byte_addr + 1'b1;
                        bit_cnt   <= 5'd7;
                    end else begin
                        bit_cnt <= bit_cnt - 1'b1;
                    end
                end
                ST_IGNORE: ;
                default: ;
            endcase
        end
    end

    always @(negedge spi_clk or posedge spi_cs_n) begin
        if (spi_cs_n) begin
            spi_miso   <= 1'b1;
            tx_byte    <= 8'hFF;
            tx_bit_cnt <= 3'd7;
        end else begin
            if (state == ST_DATA) begin
                if (bit_cnt == 5'd7) begin
                    tx_byte    <= cur_byte;
                    spi_miso   <= cur_byte[7];
                    tx_bit_cnt <= 3'd6;
                end else begin
                    spi_miso   <= tx_byte[tx_bit_cnt];
                    tx_bit_cnt <= tx_bit_cnt - 1'b1;
                end
            end else begin
                spi_miso <= 1'b1;
            end
        end
    end

endmodule
