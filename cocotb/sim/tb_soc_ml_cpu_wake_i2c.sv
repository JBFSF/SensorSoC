`timescale 1ns/1ps

module tb_soc_ml_cpu_wake_i2c #(
    parameter string FW = "firmware/build/test_ml_cpu_wake_i2c/firmware.hex"
);
localparam int unsigned TB_TIMEOUT_CYCLES = 20_000_000;
localparam int unsigned TB_PROGRESS_EVERY = 1_000_000;

reg clk;
reg resetn;
reg scl_drv;
reg sda_drv_low;
tri1 sda_line;

wire [7:0] gpio_out;
wire       cpu_clk_o;
wire       cpu_awake_o;

integer failures;
integer sleep_edges;
integer wake_edges;
bit conf_programmed;
bit saw_host_pending;
bit saw_host_event_pulse;
bit saw_ml_pending;
bit saw_ml_irq_pulse;
reg prev_awake;
reg prev_ml_irq;

assign sda_line = sda_drv_low ? 1'b0 : 1'bz;

soc_top #(
    .MEM_WORDS    (8192),
    .FIRMWARE_HEX (FW)
) dut (
    .clk        (clk),
    .resetn     (resetn),
    .i2c_scl_i  (scl_drv),
    .i2c_sda_io (sda_line),
    .gpio_out   (gpio_out),
    .cpu_clk_o  (cpu_clk_o),
    .cpu_awake_o(cpu_awake_o)
);

always #10 clk = ~clk;  // 50MHz

initial begin
    $display("[%0t] TB start FW=%s", $time, FW);
end

always @(posedge clk) begin
    if (!resetn) begin
        sleep_edges <= 0;
        wake_edges <= 0;
        prev_awake <= 1'b1;
        prev_ml_irq <= 1'b0;
        saw_host_pending <= 1'b0;
        saw_host_event_pulse <= 1'b0;
        saw_ml_pending <= 1'b0;
        saw_ml_irq_pulse <= 1'b0;
    end else begin
        if (prev_awake && !cpu_awake_o) begin
            sleep_edges <= sleep_edges + 1;
            $display("[%0t] CPU -> SLEEP (%0d)", $time, sleep_edges + 1);
        end
        if (!prev_awake && cpu_awake_o) begin
            wake_edges <= wake_edges + 1;
            $display("[%0t] CPU -> WAKE  (%0d)", $time, wake_edges + 1);
        end
        prev_awake <= cpu_awake_o;

        if (dut.u_irqc.pending[2]) saw_host_pending <= 1'b1;
        if (dut.host_i2c_irq_event) saw_host_event_pulse <= 1'b1;
        if (dut.u_irqc.pending[1]) saw_ml_pending <= 1'b1;
        if (!prev_ml_irq && dut.ml_irq) saw_ml_irq_pulse <= 1'b1;
        prev_ml_irq <= dut.ml_irq;

    end
end

task i2c_tick;
begin
    #120;
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
    i2c_write_byte(8'h84, ack); // 7'h42 + write
    if (!ack) begin
        $display("FAIL: no ACK on host write address");
        failures = failures + 1;
    end
    i2c_write_byte(reg_addr, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host register pointer");
        failures = failures + 1;
    end
    i2c_write_byte(reg_data, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host register data");
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
        $display("FAIL: no ACK on host write address before read");
        failures = failures + 1;
    end
    i2c_write_byte(reg_addr, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host register pointer before read");
        failures = failures + 1;
    end
    i2c_start();
    i2c_write_byte(8'h85, ack);
    if (!ack) begin
        $display("FAIL: no ACK on host read address");
        failures = failures + 1;
    end
    i2c_read_byte(reg_data, 1'b1); // NACK then stop
    i2c_stop();
end
endtask

initial begin
    failures = 0;
    conf_programmed = 1'b0;

    clk = 1'b0;
    resetn = 1'b0;
    scl_drv = 1'b1;
    sda_drv_low = 1'b0;

    repeat (10) @(posedge clk);
    resetn = 1'b1;
    $display("[%0t] Reset released", $time);

    // Program smart-alarm config via host I2C.
    // target_wake_sec = 900 (3 * 300s epochs), window = 600s.
    i2c_write_reg(8'h10, 8'h84);
    i2c_write_reg(8'h11, 8'h03);
    i2c_write_reg(8'h12, 8'h00);
    i2c_write_reg(8'h13, 8'h00);
    i2c_write_reg(8'h14, 8'h58);
    i2c_write_reg(8'h15, 8'h02);
    i2c_write_reg(8'h16, 8'h2C); // step_sec = 300
    i2c_write_reg(8'h17, 8'h01);
    i2c_write_reg(8'h18, 8'h20); // motion threshold = 800
    i2c_write_reg(8'h19, 8'h03);
    i2c_write_reg(8'h1A, 8'h02); // high-motion sustain count
    i2c_write_reg(8'h1B, 8'h01); // deadline override enabled

    // Confidence threshold = 0x0001 and threshold IRQ enabled.
    i2c_write_reg(8'h30, 8'h01);
    i2c_write_reg(8'h31, 8'h00);
    i2c_write_reg(8'h32, 8'h03);
    conf_programmed = 1'b1;
    $display("[%0t] Programmed host wake policy + confidence threshold IRQ", $time);
end

initial begin
    integer cycles;
    reg [7:0] conf_stat;
    reg [7:0] irq_count_l;
    reg [31:0] summary;
    reg [7:0] ml_runs;
    reg [7:0] skip_runs;
    reg [7:0] boundary_flags;
    cycles = 0;
    wait (resetn);
    while (cycles < TB_TIMEOUT_CYCLES) begin
        @(posedge clk);
        cycles = cycles + 1;

        if ((cycles % TB_PROGRESS_EVERY) == 0) begin
            $display("[cyc %0d] alive: awake=%0b sleep=%0d wake=%0d pending=0x%08x test_status=0x%08x test_code=0x%08x",
                     cycles, cpu_awake_o, sleep_edges, wake_edges, dut.u_irqc.pending,
                     dut.test_status, dut.test_code);
        end

        if (dut.test_status == 32'hDEAD_BEEF) begin
            $display("FAIL: firmware reported FAIL code=0x%08x", dut.test_code);
            $fatal(1);
        end

        if (dut.trap) begin
            $display("FAIL: CPU trap asserted test_code=0x%08x mem_valid=%0b mem_ready=%0b mem_addr=0x%08x wstrb=%b pc=0x%08x next_pc=0x%08x cpu_state=0x%02x irq_state=%0d",
                     dut.test_code, dut.mem_valid, dut.mem_ready, dut.mem_addr, dut.mem_wstrb,
                     dut.cpu.reg_pc, dut.cpu.reg_next_pc, dut.cpu.cpu_state, dut.cpu.irq_state);
            $fatal(1);
        end

        if (dut.test_status == 32'hCAFE_BABE) begin
            if (!conf_programmed) begin
                $display("FAIL: firmware passed before confidence threshold was programmed");
                failures = failures + 1;
            end
            if (sleep_edges < 2 || wake_edges < 2) begin
                $display("FAIL: expected at least 2 sleep/wake cycles, got sleep=%0d wake=%0d",
                         sleep_edges, wake_edges);
                failures = failures + 1;
            end
            summary = dut.test_code;
            ml_runs = summary[31:24];
            skip_runs = summary[23:16];
            boundary_flags = summary[15:8];
            if (ml_runs == 0) begin
                $display("FAIL: firmware reported zero ML runs in summary=0x%08x", summary);
                failures = failures + 1;
            end
            if (boundary_flags != 8'h1F) begin
                $display("FAIL: wake boundary matrix mismatch flags=0x%02x expected=0x1F summary=0x%08x",
                         boundary_flags, summary);
                failures = failures + 1;
            end
            if (!saw_host_event_pulse) begin
                $display("FAIL: never observed host_i2c_irq_event pulse");
                failures = failures + 1;
            end
            if (!saw_ml_irq_pulse) begin
                $display("FAIL: never observed ml_irq completion pulse");
                failures = failures + 1;
            end
            if (!saw_ml_pending) begin
                $display("FAIL: never observed IRQC pending bit1 (ml)");
                failures = failures + 1;
            end
            if (dut.u_irqc.pending[1]) begin
                $display("FAIL: IRQC pending bit1 still set at test completion");
                failures = failures + 1;
            end
            if (dut.ml_irq) begin
                $display("FAIL: ml_irq still high at test completion");
                failures = failures + 1;
            end
            if (!saw_host_pending) begin
                $display("FAIL: never observed IRQC pending bit2 (host)");
                failures = failures + 1;
            end

            i2c_read_reg(8'h33, conf_stat);  // REG_CONF_STAT
            if (!conf_stat[2]) begin
                $display("FAIL: conf fired sticky bit not set (CONF_STAT=0x%02x)", conf_stat);
                failures = failures + 1;
            end
            i2c_read_reg(8'h05, irq_count_l); // REG_IRQ_COUNT_L
            if (irq_count_l == 8'h00) begin
                $display("FAIL: host bridge IRQ count did not increment");
                failures = failures + 1;
            end

            if (failures == 0) begin
                $display("PASS: tb_soc_ml_cpu_wake_i2c");
                $display("  summary=0x%08x ml_runs=%0d skip_runs=%0d wake_boundary=0x%02x sleep=%0d wake=%0d conf_stat=0x%02x irq_count_l=%0d",
                         summary, ml_runs, skip_runs, boundary_flags, sleep_edges, wake_edges, conf_stat, irq_count_l);
                $finish;
            end else begin
                $display("FAIL: tb_soc_ml_cpu_wake_i2c failures=%0d", failures);
                $fatal(1);
            end
        end
    end

    $display("FAIL: timeout after %0d cycles", TB_TIMEOUT_CYCLES);
    $display("  Final awake=%0b sleep=%0d wake=%0d pending=0x%08x wake_reason=0x%08x test_status=0x%08x test_code=0x%08x ml_irq=%0b",
             cpu_awake_o, sleep_edges, wake_edges, dut.u_irqc.pending, dut.u_pwr.wake_reason,
             dut.test_status, dut.test_code, dut.ml_irq);
    $display("  Bus snapshot mem_valid=%0b mem_ready=%0b mem_addr=0x%08x wstrb=%b instr=%0b trap=%0b",
             dut.mem_valid, dut.mem_ready, dut.mem_addr, dut.mem_wstrb, dut.mem_instr, dut.trap);
    $fatal(1);
end

initial begin
    $dumpfile("/tmp/ml_cpu_wake_i2c.vcd");
    $dumpvars(0, tb_soc_ml_cpu_wake_i2c);
end

endmodule
