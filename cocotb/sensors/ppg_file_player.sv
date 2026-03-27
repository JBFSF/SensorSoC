`timescale 1ns/1ps

// ppg_file_player.sv
//
// Simulation file player for ADPD144RI PPG optical sensor.
//
// Reads pre-generated CSV from ppg.py (ppg_digital.csv).
// Format: one row per sample, two unsigned integers: red_counts,ir_counts
//
// Sensor specs modeled:
//   - Analog Devices ADPD144RI
//   - 14-bit unsigned ADC counts (0..16383)
//   - Two channels: 660nm red (slot A), 880nm IR (slot B)
//   - ODR: 100 Hz
//
// Outputs two 14-bit unsigned sample values per clock tick.

module ppg_file_player #(
    parameter int    FS_HZ    = 100,            // ADPD144RI ODR (100 Hz)
    parameter string CSV_FILE = "sim/data/ppg_digital.csv"
)(
    input  logic         clk,
    input  logic         resetn,

    output logic         sample_valid,          // pulses high 1 cycle when sample ready
    output logic [13:0]  red_counts,            // 660nm red channel (14-bit unsigned)
    output logic [13:0]  ir_counts              // 880nm IR channel  (14-bit unsigned)
);

    // Clock divider: 50 MHz / 100 Hz = 500_000 cycles per sample
    localparam int DIVIDER = 50_000_000 / FS_HZ;

    int  fd;
    int  r;
    int  cnt;
    int  raw_red, raw_ir;

    initial begin
        fd = $fopen(CSV_FILE, "r");
        if (fd == 0) begin
            $display("ERROR: ppg_file_player: cannot open %s", CSV_FILE);
            $fatal(1);
        end
        $display("ppg_file_player: opened %s  (ODR=%0d Hz, divider=%0d)",
                 CSV_FILE, FS_HZ, DIVIDER);
    end

    always @(posedge clk) begin
        if (!resetn) begin
            cnt          <= 0;
            sample_valid <= 1'b0;
            red_counts   <= '0;
            ir_counts    <= '0;
        end else begin
            sample_valid <= 1'b0;

            if (cnt >= DIVIDER - 1) begin
                cnt <= 0;

                r = $fscanf(fd, "%d,%d\n", raw_red, raw_ir);

                if (r == 2) begin
                    // Clamp to 14-bit unsigned range
                    red_counts   <= raw_red[13:0];
                    ir_counts    <= raw_ir[13:0];
                    sample_valid <= 1'b1;
                end else begin
                    sample_valid <= 1'b0;
                    $display("ppg_file_player: EOF or read error (r=%0d) at time %0t", r, $time);
                end
            end else begin
                cnt <= cnt + 1;
            end
        end
    end

endmodule
