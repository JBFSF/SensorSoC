`timescale 1ns/1ps

//------------------------------------------------------------------------------
// pwrctrl_mmio.v
//
// Power / Sleep Control MMIO Peripheral (Always-On Domain)
//
// Purpose
// -------
// This block is the software-visible "power controller" for the SoC.
// It sits in the always-on clock domain and provides:
//
//   1) A firmware-controlled sleep request bit (sleep_req_o)
//   2) A sticky latch of wake source events (wake_status)
//   3) A snapshot of the wake reason taken at the moment the CPU wakes (wake_reason)
//
// This allows firmware to:
//   • request sleep (CPU clock gating handled elsewhere, e.g. in soc_top FSM)
//   • figure out why it woke up (timer event, ML event, etc.)
//   • clear wake status bits once handled (W1C behavior)
//
// -------------------------
// - Always-on blocks (timer_mmio, ml_stub_mmio, future sensors/IRQ sources) raise
//   event bits into wake_src_i.
// - pwrctrl_mmio captures those bits so they aren't missed.
// - soc_top uses sleep_req_o + wake events to gate / ungate the CPU clock.
// - When the CPU wakes, this block snapshots the reason for that wake.
//
//------------------------------------------------------------------------------
// Memory Map (BASE_ADDR = 0x0300_1000)
//
// Address Offset | Register        | Access  | Description
// -----------------------------------------------------------------------------
// 0x00           | CTRL            | RW      | bit0 = sleep_req
// 0x04           | WAKE_STATUS     | R/W1C   | Sticky OR of wake_src_i (clear by writing 1s)
// 0x08           | WAKE_REASON     | RO      | Snapshot of wake flags taken on asleep->awake
//
// Notes:
// - "W1C" = Write-1-to-Clear. Writing a '1' clears that bit; writing '0' leaves it.
// - WAKE_REASON is not cleared by W1C directly; it updates on each wake.
//
//------------------------------------------------------------------------------
// Bus Interface Behavior
// ----------------------
// • Address decode uses a 4KB page compare:
//       mem_addr[31:12] == BASE_ADDR[31:12]
//
// • When selected (`sel` asserted):
//       mem_ready is asserted for one cycle.
//
// • Reads are combinationally chosen via a sequential case statement, returning:
//       CTRL        -> {31'b0, sleep_req_o}
//       WAKE_STATUS -> wake_status
//       WAKE_REASON -> wake_reason
//
// • Writes occur when any byte lane is enabled (mem_wstrb != 0).
//   - CTRL only respects mem_wstrb[0] (byte 0) because only bit0 is meaningful.
//   - WAKE_STATUS uses W1C semantics.
//
//------------------------------------------------------------------------------
// Key Implementation Details
// --------------------------
// 1) Sticky wake_status capture
//    wake_status <= wake_status | wake_src_i;
//    This makes wake_status "edge-loss tolerant": even a 1-cycle wake pulse will
//    be captured and held until software clears it.
//
// 2) Wake reason snapshot
//    The module detects a CPU asleep->awake transition using cpu_awake_i.
//    On that transition, it snapshots the wake flags into wake_reason:
//
//       if (!cpu_awake_d && cpu_awake_i) wake_reason <= wake_status | wake_src_i;
//
//    This is important because wake_status may accumulate multiple sources over
//    time; wake_reason records "what was pending at the moment we woke."
//
// 3) Clearing sleep_req_o on wake
//    sleep_req_o is cleared automatically on wake so periodic wake scenarios
//    don't immediately re-sleep the CPU without firmware explicitly re-requesting.
//
//------------------------------------------------------------------------------
// Typical firmware flow
// ---------------------
// (1) Configure wake sources (timer, ML, etc.)
// (2) Write CTRL.sleep_req = 1 to request sleep
// (3) CPU sleeps (clock gated in soc_top)
// (4) Wake event occurs in always-on domain
// (5) CPU wakes; firmware reads WAKE_REASON / WAKE_STATUS
// (6) Firmware clears handled wake bits by writing 1s to WAKE_STATUS
//------------------------------------------------------------------------------

module pwrctrl_mmio #(
    parameter BASE_ADDR = 32'h0300_1000
)(
    input  wire        clk,
    input  wire        resetn,

    // Memory bus interface
    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,

    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    // Sleep request output to top-level power FSM / clock gating
    output reg         sleep_req_o,

    // Wake sources from always-on blocks (timer, ML, etc.)
    input  wire [31:0] wake_src_i,

    // Indicates whether CPU clock is currently enabled (used to detect wake)
    input  wire        cpu_awake_i
);

    //-------------------------------------------------------------------------
    // Register offsets
    //-------------------------------------------------------------------------
    localparam OFF_CTRL        = 32'h0;  // RW: bit0 sleep_req
    localparam OFF_WAKE_STATUS = 32'h4;  // R/W1C: sticky latched wake flags
    localparam OFF_WAKE_REASON = 32'h8;  // RO: snapshot of wake flags on wake

    // 4KB page decode (matches your other MMIOs)
    wire sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);
    wire [31:0] off = mem_addr - BASE_ADDR;

    //-------------------------------------------------------------------------
    // Wake capture registers
    //-------------------------------------------------------------------------
    reg [31:0] wake_status;  // sticky OR of wake_src_i until software clears via W1C
    reg [31:0] wake_reason;  // snapshot taken on asleep->awake transition

    // Used to detect asleep->awake transition
    reg cpu_awake_d;

    always @(posedge clk) begin
        if (!resetn) begin
            // Reset state
            mem_ready   <= 1'b0;
            mem_rdata   <= 32'h0;

            sleep_req_o <= 1'b0;
            wake_status <= 32'h0;
            wake_reason <= 32'h0;

            cpu_awake_d <= 1'b1;

        end else begin
            // Default: no response
            mem_ready <= 1'b0;

            // ------------------------------------------------------------
            // 1) Continuously latch wake sources (sticky until W1C clears)
            // ------------------------------------------------------------
            // Any asserted bit in wake_src_i becomes sticky in wake_status.
            wake_status <= wake_status | wake_src_i;

            // ------------------------------------------------------------
            // 2) Detect asleep->awake transition and snapshot wake reason
            // ------------------------------------------------------------
            cpu_awake_d <= cpu_awake_i;

            // Rising transition: CPU was asleep (0) and is now awake (1)
            if (!cpu_awake_d && cpu_awake_i) begin
                // Snapshot what wake flags were present at wake time
                wake_reason <= wake_status | wake_src_i;

                // Clear sleep request on wake to avoid immediately re-sleeping
                sleep_req_o <= 1'b0;
            end

            // ------------------------------------------------------------
            // 3) MMIO access
            // ------------------------------------------------------------
            if (sel) begin
                // One-cycle ready handshake
                mem_ready <= 1'b1;

                // -------------------------
                // Reads
                // -------------------------
                case (off)
                    OFF_CTRL:        mem_rdata <= {31'b0, sleep_req_o};
                    OFF_WAKE_STATUS: mem_rdata <= wake_status;
                    OFF_WAKE_REASON: mem_rdata <= wake_reason;
                    default:         mem_rdata <= 32'h0;
                endcase

                // -------------------------
                // Writes
                // -------------------------
                if (mem_wstrb != 4'b0000) begin
                    case (off)
                        OFF_CTRL: begin
                            // Only bit0 is meaningful; respect byte0 writes.
                            if (mem_wstrb[0])
                                sleep_req_o <= mem_wdata[0];
                        end

                        OFF_WAKE_STATUS: begin
                            // W1C: clear bits where mem_wdata has 1s.
                            // Include same-cycle wake_src_i OR before clearing
                            // so events arriving this cycle aren’t lost.
                            wake_status <= (wake_status | wake_src_i) & ~mem_wdata;
                        end

                        default: begin end
                    endcase
                end
            end
        end
    end

endmodule