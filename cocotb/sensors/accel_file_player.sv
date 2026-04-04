`timescale 1ns/1ps

// accel_file_player.sv
//
// Simulation file player for LIS2DW12 accelerometer.
//
// Reads pre-generated CSV from accelerometer.py (accel_digital.csv).
// Format: one row per sample, three signed integers: ax,ay,az
//
// Sensor specs modeled:
//   - STMicroelectronics LIS2DW12
//   - ±4g full scale, 14-bit two's complement output
//   - ODR: 25 Hz (low-power mode, suitable for sleep tracking)
//   - Sensitivity: 0.488 mg/LSB
//
// Output width is 14 bits signed to match motion_preprocess.sv (AX_W=14).
//
// CSV path is set at runtime via plusarg:
//   vvp sim.out +DATA_DIR=cocotb/sim/data   (from repo root)
//   vvp sim.out +DATA_DIR=sim/data          (from cocotb/)
//   vvp sim.out                             (uses default: sim/data)

module accel_file_player #(
    parameter int    FS_HZ = 25             // LIS2DW12 ODR (25 Hz)
)(
    input  logic        clk,
    input  logic        resetn,

    output logic        sample_valid,   // pulses high for 1 cycle when new sample ready
    output logic        sample_ok,      // always 1 when sample_valid (no error model)
    output logic signed [13:0] ax,      // 14-bit signed acceleration X
    output logic signed [13:0] ay,      // 14-bit signed acceleration Y
    output logic signed [13:0] az       // 14-bit signed acceleration Z
);

    // Number of 50 MHz clock cycles between samples at FS_HZ
    localparam int DIVIDER = 50_000_000 / FS_HZ;   // 2_000_000 at 25 Hz

    int    fd;
    int    r;
    int    cnt;
    int    raw_ax, raw_ay, raw_az;
    string data_dir;
    string csv_file;

    initial begin
        if (!$value$plusargs("DATA_DIR=%s", data_dir))
            data_dir = "sim/data";          // default: invoke from cocotb/
        csv_file = {data_dir, "/accel_digital.csv"};

        fd = $fopen(csv_file, "r");
        if (fd == 0) begin
            $display("ERROR: accel_file_player: cannot open %s", csv_file);
            $fatal(1);
        end
        $display("accel_file_player: opened %s  (ODR=%0d Hz, divider=%0d)",
                 csv_file, FS_HZ, DIVIDER);
    end

    always @(posedge clk) begin
        if (!resetn) begin
            cnt          <= 0;
            sample_valid <= 1'b0;
            sample_ok    <= 1'b0;
            ax           <= '0;
            ay           <= '0;
            az           <= '0;
        end else begin
            sample_valid <= 1'b0;

            if (cnt >= DIVIDER - 1) begin
                cnt <= 0;

                r = $fscanf(fd, "%d,%d,%d\n", raw_ax, raw_ay, raw_az);

                if (r == 3) begin
                    ax           <= raw_ax[13:0];
                    ay           <= raw_ay[13:0];
                    az           <= raw_az[13:0];
                    sample_valid <= 1'b1;
                    sample_ok    <= 1'b1;
                end else begin
                    sample_valid <= 1'b0;
                    sample_ok    <= 1'b0;
                    $display("accel_file_player: EOF or read error (r=%0d) at time %0t", r, $time);
                end
            end else begin
                cnt <= cnt + 1;
            end
        end
    end

endmodule
