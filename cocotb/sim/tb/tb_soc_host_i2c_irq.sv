`timescale 1ns/1ps
module tb_soc_host_i2c_irq;

reg clk;
reg resetn;
reg scl_drv;
reg sda_drv_low;
tri1 sda_line;

wire [7:0] gpio_out;
wire       cpu_clk_o;
wire       cpu_awake_o;

integer failures;
integer irq_evt_count;

assign sda_line = sda_drv_low ? 1'b0 : 1'bz;

soc_top #(
    .FIRMWARE_HEX("")
) dut (
    .clk        (clk),
    .resetn     (resetn),
    .i2c_scl_i  (scl_drv),
    .i2c_sda_io (sda_line),
    .gpio_out   (gpio_out),
    .cpu_clk_o  (cpu_clk_o),
    .cpu_awake_o(cpu_awake_o)
);

always #5 clk = ~clk;

always @(posedge clk) begin
    if (!resetn) irq_evt_count <= 0;
    else if (dut.host_i2c_irq_event) irq_evt_count <= irq_evt_count + 1;
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

`define DUMPFILE "/tmp/tb_soc_host_i2c_irq.vcd"
initial $dumpfile(`DUMPFILE);
initial $dumpvars(0, tb_soc_host_i2c_irq);

initial begin
    failures      = 0;
    irq_evt_count = 0;
    clk           = 1'b0;
    resetn        = 1'b0;
    scl_drv       = 1'b1;
    sda_drv_low   = 1'b0;

    repeat (10) @(posedge clk);
    resetn = 1'b1;
    repeat (20) @(posedge clk);

    // Trigger host I2C IRQ event via bridge register.
    i2c_write_reg(8'h04, 8'h01);
    repeat (20) @(posedge clk);

    if (irq_evt_count != 1) begin
        $display("FAIL: expected one host_i2c_irq_event pulse, got %0d", irq_evt_count);
        failures = failures + 1;
    end

    if (!dut.u_irqc.pending[2]) begin
        $display("FAIL: irq_ctrl pending[2] was not set by host I2C event");
        failures = failures + 1;
    end

    if (failures == 0) begin
        $display("PASS: tb_soc_host_i2c_irq");
    end else begin
        $display("FAIL: tb_soc_host_i2c_irq failures=%0d", failures);
        $fatal(1);
    end

    #100;
    $finish;
end

endmodule
