`timescale 1ns/1ps

module tb_host_i2c_irqc_proxy;
    reg clk;
    reg resetn;

    reg scl_drv;
    reg sda_drv_low;
    tri1 sda_line;

    wire [7:0] gpio_out;
    wire cpu_clk_o;
    wire cpu_awake_o;

    integer failures;
    integer wake_pulse_count;

    reg [7:0] r0, r1, r2, r3;
    reg [7:0] ack;

    assign sda_line = sda_drv_low ? 1'b0 : 1'bz;

    soc_top dut (
        .clk(clk),
        .resetn(resetn),
        .i2c_scl_i(scl_drv),
        .i2c_sda_io(sda_line),
        .gpio_out(gpio_out),
        .cpu_clk_o(cpu_clk_o),
        .cpu_awake_o(cpu_awake_o)
    );

    always #5 clk = ~clk;

    always @(posedge clk) begin
        if (!resetn)
            wake_pulse_count <= 0;
        else if (dut.irqc_wake_req)
            wake_pulse_count <= wake_pulse_count + 1;
    end

    task i2c_tick;
        begin
            #100;
        end
    endtask

    task i2c_start;
        begin
            sda_drv_low = 1'b0;
            scl_drv = 1'b1;
            i2c_tick();
            sda_drv_low = 1'b1;
            i2c_tick();
            scl_drv = 1'b0;
            i2c_tick();
        end
    endtask

    task i2c_stop;
        begin
            sda_drv_low = 1'b1;
            scl_drv = 1'b0;
            i2c_tick();
            scl_drv = 1'b1;
            i2c_tick();
            sda_drv_low = 1'b0;
            i2c_tick();
        end
    endtask

    task i2c_write_bit;
        input bitval;
        begin
            scl_drv = 1'b0;
            sda_drv_low = bitval ? 1'b0 : 1'b1;
            i2c_tick();
            scl_drv = 1'b1;
            i2c_tick();
            scl_drv = 1'b0;
            i2c_tick();
        end
    endtask

    task i2c_read_bit;
        output bitval;
        begin
            scl_drv = 1'b0;
            sda_drv_low = 1'b0;
            i2c_tick();
            scl_drv = 1'b1;
            i2c_tick();
            bitval = sda_line;
            scl_drv = 1'b0;
            i2c_tick();
        end
    endtask

    task i2c_write_byte;
        input [7:0] byte_in;
        output ack_out;
        integer i;
        reg bitv;
        begin
            for (i = 7; i >= 0; i = i - 1)
                i2c_write_bit(byte_in[i]);
            i2c_read_bit(bitv);
            ack_out = ~bitv;
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
        reg local_ack;
        begin
            i2c_start();
            i2c_write_byte(8'h84, local_ack);
            if (!local_ack) begin
                $display("FAIL: no ACK on slave write address");
                failures = failures + 1;
            end
            i2c_write_byte(reg_addr, local_ack);
            if (!local_ack) begin
                $display("FAIL: no ACK on register pointer");
                failures = failures + 1;
            end
            i2c_write_byte(reg_data, local_ack);
            if (!local_ack) begin
                $display("FAIL: no ACK on register data");
                failures = failures + 1;
            end
            i2c_stop();
        end
    endtask

    task i2c_read_reg;
        input [7:0] reg_addr;
        output [7:0] reg_data;
        reg local_ack;
        begin
            i2c_start();
            i2c_write_byte(8'h84, local_ack);
            if (!local_ack) begin
                $display("FAIL: no ACK on slave write address before read");
                failures = failures + 1;
            end
            i2c_write_byte(reg_addr, local_ack);
            if (!local_ack) begin
                $display("FAIL: no ACK on register pointer before read");
                failures = failures + 1;
            end
            i2c_start();
            i2c_write_byte(8'h85, local_ack);
            if (!local_ack) begin
                $display("FAIL: no ACK on slave read address");
                failures = failures + 1;
            end
            i2c_read_byte(reg_data, 1'b1); // NACK then STOP
            i2c_stop();
        end
    endtask

    task proxy_write32;
        input [7:0] off;
        input [31:0] wdata;
        begin
            i2c_write_reg(8'h20, off);
            i2c_write_reg(8'h21, wdata[7:0]);
            i2c_write_reg(8'h22, wdata[15:8]);
            i2c_write_reg(8'h23, wdata[23:16]);
            i2c_write_reg(8'h24, wdata[31:24]);
            i2c_write_reg(8'h25, 8'h03); // GO=1, WE=1
            i2c_read_reg(8'h26, ack);
            if (!ack[0]) begin
                $display("FAIL: proxy write did not report DONE");
                failures = failures + 1;
            end
            if (ack[1]) begin
                $display("FAIL: proxy write reported ERR");
                failures = failures + 1;
            end
            i2c_write_reg(8'h26, 8'h03); // clear DONE/ERR
        end
    endtask

    task proxy_read32;
        input [7:0] off;
        output [31:0] rdata;
        reg [7:0] stat;
        begin
            i2c_write_reg(8'h20, off);
            i2c_write_reg(8'h25, 8'h01); // GO=1, WE=0
            i2c_read_reg(8'h26, stat);
            if (!stat[0]) begin
                $display("FAIL: proxy read did not report DONE");
                failures = failures + 1;
            end
            if (stat[1]) begin
                $display("FAIL: proxy read reported ERR");
                failures = failures + 1;
            end
            i2c_read_reg(8'h28, r0);
            i2c_read_reg(8'h29, r1);
            i2c_read_reg(8'h2A, r2);
            i2c_read_reg(8'h2B, r3);
            rdata = {r3, r2, r1, r0};
            i2c_write_reg(8'h26, 8'h03); // clear DONE/ERR
        end
    endtask

    initial begin
        reg [31:0] rd32;
        integer wake_before;
        integer irq_before;

        $dumpfile("/tmp/tb_host_i2c_irqc_proxy.vcd");
        $dumpvars(0, tb_host_i2c_irqc_proxy);

        failures = 0;
        wake_pulse_count = 0;
        clk = 1'b0;
        resetn = 1'b0;
        scl_drv = 1'b1;
        sda_drv_low = 1'b0;
        r0 = 8'h0; r1 = 8'h0; r2 = 8'h0; r3 = 8'h0; ack = 8'h0;

        repeat (10) @(posedge clk);
        resetn = 1'b1;
        repeat (20) @(posedge clk);

        // Configure IRQ path for host bit2 wake behavior.
        proxy_write32(8'h04, 32'h0000_0004); // MASK bit2 only
        proxy_write32(8'h08, 32'h0000_0004); // WAKE_EN bit2 only

        // Configure threshold logic directly for deterministic threshold-path proof.
        // (Host-I2C path is still exercised for IRQC proxy reads/writes below.)
        dut.u_host_i2c_bridge_regs.conf_thr = 16'h3000;
        dut.u_host_i2c_bridge_regs.conf_en = 1'b1;
        dut.u_host_i2c_bridge_regs.conf_irq_en = 1'b1;

        // Below threshold: no IRQ expected.
        force dut.u_ml.score_o = 32'h0000_1000;
        repeat (10) @(posedge clk);

        // Check direct score/confidence contract internally.
        if (dut.u_host_i2c_bridge_regs.score_conf !== 16'h1000) begin
            $display("FAIL: SCORE_CONF mismatch, got %04x", dut.u_host_i2c_bridge_regs.score_conf);
            failures = failures + 1;
        end
        if (dut.u_host_i2c_bridge_regs.score_proxy0 !== 16'h1000) begin
            $display("FAIL: SCORE_PROXY0 mismatch, got %04x", dut.u_host_i2c_bridge_regs.score_proxy0);
            failures = failures + 1;
        end
        if (dut.u_host_i2c_bridge_regs.score_proxy1 !== 16'h0000) begin
            $display("FAIL: SCORE_PROXY1 mismatch, got %04x", dut.u_host_i2c_bridge_regs.score_proxy1);
            failures = failures + 1;
        end
        if (dut.u_host_i2c_bridge_regs.score_conf !== 16'h1000) begin
            $display("FAIL: CONF_ABS source mismatch, got %04x", dut.u_host_i2c_bridge_regs.score_conf);
            failures = failures + 1;
        end

        // Cross above threshold: should fire exactly one event.
        wake_before = wake_pulse_count;
        irq_before = dut.u_host_i2c_bridge_regs.irq_count;
        force dut.u_ml.score_o = 32'h0000_4000;
        repeat (20) @(posedge clk);

        if (!dut.u_irqc.pending[2]) begin
            $display("FAIL: irqc.pending[2] not set after threshold crossing");
            failures = failures + 1;
        end
        if (wake_pulse_count <= wake_before) begin
            $display("FAIL: wake pulse not observed on threshold crossing");
            failures = failures + 1;
        end
        if (dut.u_host_i2c_bridge_regs.irq_count != (irq_before + 1)) begin
            $display("FAIL: irq_count did not increment once on threshold crossing");
            failures = failures + 1;
        end

        // Stay above threshold: must not retrigger.
        wake_before = wake_pulse_count;
        irq_before = dut.u_host_i2c_bridge_regs.irq_count;
        repeat (20) @(posedge clk);
        if (wake_pulse_count != wake_before) begin
            $display("FAIL: wake retriggered while still above threshold");
            failures = failures + 1;
        end
        if (dut.u_host_i2c_bridge_regs.irq_count != irq_before) begin
            $display("FAIL: irq_count retriggered while still above threshold");
            failures = failures + 1;
        end

        // Clear pending so next crossing can generate a fresh wake_rise pulse.
        proxy_write32(8'h00, 32'h0000_0004);
        repeat (5) @(posedge clk);

        // Drop below then rise again: should re-arm and fire second event.
        force dut.u_ml.score_o = 32'h0000_0100;
        repeat (10) @(posedge clk);
        wake_before = wake_pulse_count;
        irq_before = dut.u_host_i2c_bridge_regs.irq_count;
        force dut.u_ml.score_o = 32'h0000_5000;
        repeat (20) @(posedge clk);
        if (wake_pulse_count <= wake_before) begin
            $display("FAIL: wake did not retrigger after re-arm");
            failures = failures + 1;
        end
        if (dut.u_host_i2c_bridge_regs.irq_count != (irq_before + 1)) begin
            $display("FAIL: irq_count did not retrigger after re-arm");
            failures = failures + 1;
        end

        // Proxy readback of pending must include bit2.
        proxy_read32(8'h00, rd32);
        if (!rd32[2]) begin
            $display("FAIL: proxy read pending missing bit2, got %08x", rd32);
            failures = failures + 1;
        end

        // Clear pending bit2 via proxy write (W1C).
        proxy_write32(8'h00, 32'h0000_0004);
        repeat (5) @(posedge clk);
        if (dut.u_irqc.pending[2]) begin
            $display("FAIL: irqc.pending[2] did not clear");
            failures = failures + 1;
        end

        // ------------------------------------------------------------------
        // Force sleep entry conditions:
        // 1) sleep_req=1 (via pwrctrl reg output in this TB)
        // 2) stop wake events (disable threshold IRQ + wake_en mask)
        // 3) CPU idle cycle observed (force mem_valid low briefly)
        // ------------------------------------------------------------------
        dut.u_host_i2c_bridge_regs.conf_en = 1'b0;
        dut.u_host_i2c_bridge_regs.conf_irq_en = 1'b0;
        proxy_write32(8'h08, 32'h0000_0000); // WAKE_EN = 0
        force dut.u_pwr.sleep_req_o = 1'b1;
        force dut.mem_valid = 1'b0;
        repeat (20) @(posedge clk);
        release dut.mem_valid;
        repeat (20) @(posedge clk);
        if (cpu_awake_o !== 1'b0) begin
            $display("FAIL: cpu_awake_o did not go low after sleep conditions");
            failures = failures + 1;
        end
        release dut.u_pwr.sleep_req_o;

        release dut.u_ml.score_o;

        if (failures == 0) begin
            $display("PASS: tb_host_i2c_irqc_proxy");
        end else begin
            $display("FAIL: tb_host_i2c_irqc_proxy failures=%0d", failures);
            $fatal(1);
        end

        #100;
        $finish;
    end
endmodule
