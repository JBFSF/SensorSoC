`timescale 1ns/1ps

//------------------------------------------------------------------------------
// test_mmio.v
//
// Simple Test / Debug MMIO Peripheral
//
// Purpose
// -------
// This module provides a very small MMIO register block used primarily for
// simulation bring-up and firmware debugging. It allows firmware running on
// the CPU to communicate simple status codes to the testbench or external
// debug logic.
//
// In the Sleep SoC simulation environment, firmware can write values to these
// registers to indicate:
//
//   • Test PASS
//   • Test FAIL
//   • Debug checkpoints or error codes
//
// The testbench can monitor `status_o` and `code_o` to determine whether the
// firmware executed correctly.
//
// Typical firmware usage
// ----------------------
// Example:
//
//   STATUS = 0xCAFEBABE  -> Test passed
//   STATUS = 0xDEADBEEF  -> Test failed
//
//   CODE register may contain:
//     • step numbers
//     • error identifiers
//     • debug values
//
// This peripheral is mainly intended for simulation and bring-up rather than
// final hardware functionality.
//
//------------------------------------------------------------------------------
// Memory Map (BASE_ADDR = 0x0300_F000)
//
// Address Offset | Register | Access | Description
// ------------------------------------------------------------
// 0x00           | STATUS   | RW     | Firmware test status
// 0x04           | CODE     | RW     | Debug code or step indicator
//
//------------------------------------------------------------------------------
// Bus Interface Behavior
// ----------------------
// • Address decode uses a 4KB page comparison:
//       mem_addr[31:12] == BASE_ADDR[31:12]
//
// • When selected (`sel` asserted):
//       mem_ready is asserted for one cycle
//
// • Reads:
//       mem_rdata returns the selected register value
//
// • Writes:
//       If any byte write strobe is active (mem_wstrb != 0),
//       the register is updated with mem_wdata.
//
// Note:
// This simple module does not implement per-byte write masking. Any non-zero
// write strobe updates the entire 32-bit register. This is acceptable for
// simulation/debug purposes.
//
//------------------------------------------------------------------------------

module test_mmio #(
    parameter BASE_ADDR = 32'h0300_F000   // Base address of test MMIO region
)(
    input  wire        clk,
    input  wire        resetn,

    // Memory bus interface
    input  wire        mem_valid,         // request valid
    input  wire [31:0] mem_addr,          // address
    input  wire [31:0] mem_wdata,         // write data
    input  wire [3:0]  mem_wstrb,         // write byte strobes
    input  wire [31:0] cfg_target_wake_sec_i,
    input  wire [31:0] cfg_window_sec_i,
    input  wire [15:0] cfg_step_sec_i,
    input  wire [15:0] cfg_motion_hi_th_i,
    input  wire [7:0]  cfg_motion_hi_count_i,
    input  wire [7:0]  cfg_policy_i,
    input  wire [15:0] cfg_conf_thr_i,

    output reg         mem_ready,         // transaction complete
    output reg  [31:0] mem_rdata,         // read data

    // Debug outputs (observed by testbench)
    output reg  [31:0] status_o,          // firmware test status
    output reg  [31:0] code_o,            // debug code / step number
    output reg  [31:0] score_o            // ML confidence score for host I2C threshold compare
);

    //-------------------------------------------------------------------------
    // Address decode
    //-------------------------------------------------------------------------
    // Select this peripheral when the CPU accesses the same 4KB page
    // as BASE_ADDR.
    wire sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);

    // Compute byte offset inside the MMIO page
    wire [31:0] off = mem_addr - BASE_ADDR;

    //-------------------------------------------------------------------------
    // Register offsets
    //-------------------------------------------------------------------------
    localparam OFF_STATUS   = 32'h0;  // status register
    localparam OFF_CODE     = 32'h4;  // debug code register
    localparam OFF_ML_SCORE = 32'h20; // ML confidence score (drives ml_score_i)
    localparam OFF_CFG_TARGET_SEC = 32'h8;
    localparam OFF_CFG_WINDOW_SEC = 32'hC;
    localparam OFF_CFG_STEP_SEC   = 32'h10;
    localparam OFF_CFG_MOTION     = 32'h14;
    localparam OFF_CFG_CONF_THR   = 32'h18;
    localparam OFF_CFG_POLICY     = 32'h1C;

    //-------------------------------------------------------------------------
    // MMIO register logic
    //-------------------------------------------------------------------------
    always @(posedge clk) begin
        if (!resetn) begin
            // Reset state
            mem_ready <= 1'b0;
            mem_rdata <= 32'h0;

            status_o  <= 32'h0;
            code_o    <= 32'h0;
            score_o   <= 32'h0;

        end else begin
            // Default: no response
            mem_ready <= 1'b0;

            // Peripheral selected by CPU
            if (sel) begin
                // One-cycle ready handshake
                mem_ready <= 1'b1;

                // -------------------------
                // Read path
                // -------------------------
                case (off)
                    OFF_STATUS:   mem_rdata <= status_o;
                    OFF_CODE:     mem_rdata <= code_o;
                    OFF_ML_SCORE: mem_rdata <= score_o;
                    OFF_CFG_TARGET_SEC: mem_rdata <= cfg_target_wake_sec_i;
                    OFF_CFG_WINDOW_SEC: mem_rdata <= cfg_window_sec_i;
                    OFF_CFG_STEP_SEC:   mem_rdata <= {16'h0, cfg_step_sec_i};
                    OFF_CFG_MOTION:     mem_rdata <= {8'h0, cfg_motion_hi_count_i, cfg_motion_hi_th_i};
                    OFF_CFG_CONF_THR:   mem_rdata <= {16'h0, cfg_conf_thr_i};
                    OFF_CFG_POLICY:     mem_rdata <= {24'h0, cfg_policy_i};
                    default:    mem_rdata <= 32'h0;
                endcase

                // -------------------------
                // Write path
                // -------------------------
                if (mem_wstrb != 4'b0000) begin
                    case (off)
                        OFF_STATUS:   status_o <= mem_wdata;
                        OFF_CODE:     code_o   <= mem_wdata;
                        OFF_ML_SCORE: score_o  <= mem_wdata;
                        default: begin end
                    endcase
                end
            end
        end
    end

endmodule
