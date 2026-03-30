// Testbench for waitirq instruction test
// This tests the PicoRV32 waitirq functionality with timer interrupts

`timescale 1 ns / 1 ps

module testbench_waitirq;
    reg clk = 1;
    reg resetn = 0;
    wire trap;

    always #5 clk = ~clk;

    initial begin
        repeat (100) @(posedge clk);
        resetn <= 1;
    end

    initial begin
        if ($test$plusargs("vcd")) begin
            $dumpfile("testbench_waitirq.vcd");
            $dumpvars(0, testbench_waitirq);
        end
        // Timeout after 5 million cycles
        repeat (5000000) @(posedge clk);
        $display("TIMEOUT");
        $finish;
    end

    wire        mem_valid;
    wire        mem_instr;
    reg         mem_ready;
    wire [31:0] mem_addr;
    wire [31:0] mem_wdata;
    wire [ 3:0] mem_wstrb;
    reg  [31:0] mem_rdata;

    // No external IRQs
    wire [31:0] irq = 32'b0;

    picorv32 #(
        .ENABLE_COUNTERS(1),
        .ENABLE_COUNTERS64(0),
        .ENABLE_MUL(1),
        .ENABLE_DIV(1),
        .ENABLE_IRQ(1),
        .ENABLE_IRQ_QREGS(0),
        .ENABLE_IRQ_TIMER(1)
    ) cpu (
        .clk         (clk        ),
        .resetn      (resetn     ),
        .trap        (trap       ),
        .mem_valid   (mem_valid  ),
        .mem_instr   (mem_instr  ),
        .mem_ready   (mem_ready  ),
        .mem_addr    (mem_addr   ),
        .mem_wdata   (mem_wdata  ),
        .mem_wstrb   (mem_wstrb  ),
        .mem_rdata   (mem_rdata  ),
        .irq         (irq        )
    );

    // Memory: 128KB
    reg [31:0] memory [0:32767];

    reg tests_passed = 0;

    // Load test program
    initial begin
        $readmemh("tests/waitirq_test.hex", memory);
    end

    // Memory interface
    always @(posedge clk) begin
        mem_ready <= 0;
        if (resetn && mem_valid && !mem_ready) begin
            mem_ready <= 1;
            if (mem_addr < 32'h20000) begin

                mem_rdata <= memory[mem_addr >> 2];
                if (mem_wstrb[0]) memory[mem_addr >> 2][ 7: 0] <= mem_wdata[ 7: 0];
                if (mem_wstrb[1]) memory[mem_addr >> 2][15: 8] <= mem_wdata[15: 8];
                if (mem_wstrb[2]) memory[mem_addr >> 2][23:16] <= mem_wdata[23:16];
                if (mem_wstrb[3]) memory[mem_addr >> 2][31:24] <= mem_wdata[31:24];
            end else if (mem_addr == 32'h10000000) begin
                // UART output
                if (mem_wstrb != 0) begin
                    $write("%c", mem_wdata[7:0]);
                    $fflush();
                end
            end else if (mem_addr == 32'h20000000) begin

                if (mem_wstrb != 0 && mem_wdata == 123456789) begin
                    tests_passed <= 1;
                end
            end
        end
    end

    // Monitor for faults
    integer cycle_counter = 0;
    always @(posedge clk) begin
        if (resetn)
            cycle_counter <= cycle_counter + 1;

        if (resetn && trap) begin
            repeat (10) @(posedge clk);
            $display("\nTRAP after %0d clock cycles", cycle_counter);
            if (tests_passed) begin
                $display("ALL TESTS PASSED.");
                $finish;
            end else begin
                $display("ERROR: Tests did not pass!");
                $stop;
            end
        end
    end
endmodule
