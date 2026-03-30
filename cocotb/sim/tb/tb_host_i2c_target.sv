`timescale 1ns/1ps
module tb_host_i2c_target;

reg clk;
reg resetn;
reg scl_drv;
reg sda_drv_low;
tri1 sda_line;

wire       wr_en;
wire [7:0] wr_addr;
wire [7:0] wr_data;
wire [7:0] rd_addr;
wire [7:0] rd_data;
wire       proto_err;
wire       event_o;

integer failures;
integer event_count;

assign sda_line = sda_drv_low ? 1'b0 : 1'bz;

host_i2c_target #(.SLAVE_ADDR(7'h42)) dut_target (
    .clk         (clk),
    .resetn      (resetn),
    .i2c_scl_i   (scl_drv),
    .i2c_sda_io  (sda_line),
    .wr_en_o     (wr_en),
    .wr_addr_o   (wr_addr),
    .wr_data_o   (wr_data),
    .rd_addr_o   (rd_addr),
    .rd_data_i   (rd_data),
    .proto_err_o (proto_err)
);

host_i2c_bridge_regs dut_regs (
    .clk        (clk),
    .resetn     (resetn),
    .wr_en_i    (wr_en),
    .wr_addr_i  (wr_addr),
    .wr_data_i  (wr_data),
    .rd_addr_i  (rd_addr),
    .rd_data_o  (rd_data),
    .proto_err_i(proto_err),
    .event_o    (event_o)
);

always #5 clk = ~clk;

always @(posedge clk) begin
    if (!resetn) event_count <= 0;
    else if (event_o) event_count <= event_count + 1;
end


task i2c_tick;
begin
    #100;
end
endtask

task i2c_start;
begin
    sda_drv_low = 1'b0;
    scl_drv     = 1'b1;
    i2c_tick();
    sda_drv_low = 1'b1;
    i2c_tick();
    scl_drv     = 1'b0;
    i2c_tick();
end
endtask

task i2c_stop;
begin
    sda_drv_low = 1'b1;
    scl_drv     = 1'b0;
    i2c_tick();
    scl_drv     = 1'b1;
    i2c_tick();
    sda_drv_low = 1'b0;
    i2c_tick();
end
endtask

task i2c_write_bit;
    input bitval;
begin
    scl_drv     = 1'b0;
    sda_drv_low = bitval ? 1'b0 : 1'b1;
    i2c_tick();
    scl_drv     = 1'b1;
    i2c_tick();
    scl_drv     = 1'b0;
    i2c_tick();
end
endtask

task i2c_read_bit;
    output bitval;
begin
    scl_drv     = 1'b0;
    sda_drv_low = 1'b0;
    i2c_tick();
    scl_drv     = 1'b1;
    i2c_tick();
    bitval      = sda_line;
    scl_drv     = 1'b0;
    i2c_tick();
end
endtask

task i2c_write_byte;
    input [7:0] byte_in;
    output ack;
    integer i;
    reg bitv;
begin
    for (i = 7; i >= 0; i = i - 1) i2c_write_bit(byte_in[i]);
    i2c_read_bit(bitv);
    ack = ~bitv;
end
endtask

task i2c_read_byte;
    output [7:0] byte_out;
    input ack_from_master;
    integer i;
    reg bitv;
begin
    byte_out = 8'h00;
    for (i = 7; i >= 0; i = i - 1) begin
        i2c_read_bit(bitv);
        byte_out[i] = bitv;
    end
    i2c_write_bit(ack_from_master);
end
endtask

task i2c_write_reg;
    input [7:0] reg_addr;
    input [7:0] reg_data;
    reg ack;
begin
    i2c_start();
    i2c_write_byte(8'h84, ack);
    if (!ack) begin
        $display("FAIL: no ACK on slave write address");
        failures = failures + 1;
    end
    i2c_write_byte(reg_addr, ack);
    if (!ack) begin
        $display("FAIL: no ACK on register pointer");
        failures = failures + 1;
    end
    i2c_write_byte(reg_data, ack);
    if (!ack) begin
        $display("FAIL: no ACK on register data");
        failures = failures + 1;
    end
    i2c_stop();
end
endtask

task i2c_read_reg;
    input  [7:0] reg_addr;
    output [7:0] reg_data;
    reg ack;
begin
    i2c_start();
    i2c_write_byte(8'h84, ack);
    if (!ack) begin
        $display("FAIL: no ACK on slave write address before read");
        failures = failures + 1;
    end
    i2c_write_byte(reg_addr, ack);
    if (!ack) begin
        $display("FAIL: no ACK on register pointer before read");
        failures = failures + 1;
    end
    i2c_start();
    i2c_write_byte(8'h85, ack);
    if (!ack) begin
        $display("FAIL: no ACK on slave read address");
        failures = failures + 1;
    end
    i2c_read_byte(reg_data, 1'b1);  // NACK and stop
    i2c_stop();
end
endtask

`define DUMPFILE "/tmp/tb_host_i2c_target.vcd"
initial $dumpfile(`DUMPFILE);
initial $dumpvars(0, tb_host_i2c_target);

initial begin
    reg ack;
    reg [7:0] rdata;
    failures    = 0;
    event_count = 0;
    clk         = 1'b0;
    resetn      = 1'b0;
    scl_drv     = 1'b1;
    sda_drv_low = 1'b0;

    repeat (10) @(posedge clk);
    resetn = 1'b1;
    repeat (10) @(posedge clk);

    // Wrong address should NACK.
    i2c_start();
    i2c_write_byte(8'h82, ack);
    if (ack) begin
        $display("FAIL: wrong address ACKed unexpectedly");
        failures = failures + 1;
    end
    i2c_stop();

    // Basic identity register reads.
    i2c_read_reg(8'h00, rdata);
    if (rdata !== 8'hA5) begin
        $display("FAIL: WHOAMI expected A5 got %02x", rdata);
        failures = failures + 1;
    end

    i2c_read_reg(8'h01, rdata);
    if (rdata !== 8'h01) begin
        $display("FAIL: VERSION expected 01 got %02x", rdata);
        failures = failures + 1;
    end

    // Kick IRQ via bridge register.
    i2c_write_reg(8'h04, 8'h01);
    repeat (10) @(posedge clk);
    if (event_count != 1) begin
        $display("FAIL: expected exactly one event pulse, count=%0d", event_count);
        failures = failures + 1;
    end

    // STATUS bit0 should be sticky after IRQ kick.
    i2c_read_reg(8'h02, rdata);
    if (!rdata[0]) begin
        $display("FAIL: STATUS.irq_kick_seen not set");
        failures = failures + 1;
    end

    // IRQ count should increment to 1.
    i2c_read_reg(8'h05, rdata);
    if (rdata !== 8'h01) begin
        $display("FAIL: IRQ_COUNT_L expected 01 got %02x", rdata);
        failures = failures + 1;
    end

    // W1C: write 1 to bit0 of STATUS to clear irq_kick_seen.
    i2c_write_reg(8'h02, 8'h01);
    repeat (4) @(posedge clk);
    i2c_read_reg(8'h02, rdata);
    if (rdata[0]) begin
        $display("FAIL: STATUS.irq_kick_seen not cleared by W1C (STATUS=0x%02x)", rdata);
        failures = failures + 1;
    end

    // W1C must not clear bits that were written 0 — bit1 and bit2 untouched.
    if (rdata[2:1] !== 2'b00) begin
        $display("FAIL: STATUS W1C clobbered other bits (STATUS=0x%02x)", rdata);
        failures = failures + 1;
    end

    if (failures == 0) begin
        $display("PASS: tb_host_i2c_target");
    end else begin
        $display("FAIL: tb_host_i2c_target failures=%0d", failures);
        $fatal(1);
    end

    #100;
    $finish;
end

endmodule
