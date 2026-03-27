//------------------------------------------------------------------------------
// timer_mmio.v
//
// Always-on countdown timer with MMIO programming interface.
//
// - Runs on the always-on clock `clk`, so it keeps time even when the CPU clock
//   is gated off (sleep mode).
// - Produces a sticky event flag (`event_o`) when the counter expires.
// - Firmware can use it as:
//     (1) a one-shot wake timer (enable=1, periodic=0)
//     (2) a periodic “heartbeat / watchdog-like” wake source (enable=1, periodic=1)
//
// Address map (BASE_ADDR + offset)
//   0x0  CTRL    [RW] bit0=enable, bit1=periodic
//   0x4  RELOAD  [RW] reload value loaded into COUNT when (re)starting periodic timer
//   0x8  COUNT   [RW] current counter value (can be written to "kick"/adjust)
//   0xC  EVENT   [R/W1C] bit0=event_latched (sticky until cleared)
//                      Write-1-to-clear: writing bit0=1 clears event_latched.
//
// Event behavior
// - While enable=1:
//     count decrements every cycle until it reaches 0.
// - When count hits 0:
//     event_latched is set to 1 (sticky)
//     If periodic=1: count reloads from `reload` and continues running.
//     If periodic=0: enable is cleared (timer stops) and count stays at 0.
//
// “Kick” / clear behavior
// - Writing COUNT clears event_latched (treat as acknowledging/kicking).
// - Writing CTRL with enable=1 also clears event_latched and reloads COUNT.
// - Writing EVENT with bit0=1 clears event_latched (W1C).
//
// Bus behavior
// - 4KB page decode using mem_addr[31:12] == BASE_ADDR[31:12]
// - Single-cycle response: when sel is high, mem_ready is asserted for that cycle.
// - `mem_rdata` and `rdata_o` both return the addressed register.
//
// Notes
// - CTRL write respects mem_wstrb[0] so firmware can do byte writes safely.
// - RELOAD writes update the reload register but do NOT automatically update COUNT
//   unless you (re)enable or explicitly write COUNT.
// - COUNT is a simple down-counter in the always-on clock domain; in a real ASIC,
//   you may later replace `clk` with a low-frequency oscillator tick.
//------------------------------------------------------------------------------
`timescale 1ns/1ps

module timer_mmio #(
    parameter BASE_ADDR = 32'h0300_2000
)(
    input  wire        clk,
    input  wire        resetn,

    input  wire        mem_valid,
    input  wire [31:0] mem_addr,
    input  wire [31:0] mem_wdata,
    input  wire [3:0]  mem_wstrb,

    output reg         mem_ready,
    output reg  [31:0] mem_rdata,

    output wire        event_o,
    output reg  [31:0] rdata_o
);

    localparam [31:0] OFF_CTRL   = 32'h0;  // bit0 enable, bit1 periodic
    localparam [31:0] OFF_RELOAD = 32'h4;
    localparam [31:0] OFF_COUNT  = 32'h8;
    localparam [31:0] OFF_EVENT  = 32'hC;  // W1C bit0, read shows latched

    // 4KB page decode (matches other MMIOs)
    wire        sel = mem_valid && (mem_addr[31:12] == BASE_ADDR[31:12]);
    wire [31:0] off = mem_addr - BASE_ADDR;

    reg         enable, periodic;
    reg [31:0]  reload, count;
    reg         event_latched;

    assign event_o = event_latched;

    // Icarus-friendly "read mux" as a reg set inside sequential block
    reg [31:0] read_data;

    wire wr = sel && (mem_wstrb != 4'b0000);

    always @(posedge clk) begin
        if (!resetn) begin
            // timer regs
            enable        <= 1'b0;
            periodic      <= 1'b1;
            reload        <= 32'd5_000_000;
            count         <= 32'd5_000_000;
            event_latched <= 1'b0;

            // bus regs
            mem_ready <= 1'b0;
            mem_rdata <= 32'h0;
            rdata_o   <= 32'h0;

            read_data <= 32'h0;
        end else begin
            // default
            mem_ready <= 1'b0;

            // -------------------------
            // Timer countdown (always-on)
            // -------------------------
            if (enable) begin
                if (count != 32'd0) begin
                    count <= count - 32'd1;
                end else begin
                    event_latched <= 1'b1;
                    if (periodic) begin
                        count <= reload;
                    end else begin
                        enable <= 1'b0;
                    end
                end
            end

            // -------------------------
            // MMIO access (1-cycle ready)
            // -------------------------
            if (sel) begin
                mem_ready <= 1'b1;

                // Build read_data *fresh* (no stale rdata issues)
                read_data = 32'h0;
                case (off)
                    OFF_CTRL:   read_data = {30'b0, periodic, enable};
                    OFF_RELOAD: read_data = reload;
                    OFF_COUNT:  read_data = count;
                    OFF_EVENT:  read_data = {31'b0, event_latched};
                    default:    read_data = 32'h0;
                endcase

                // Drive outputs from the same computed value
                mem_rdata <= read_data;
                rdata_o   <= read_data;

                // Writes
                if (wr) begin
                    case (off)
                        OFF_CTRL: begin
                            // bus is 32-bit, but typically only byte0 matters.
                            // Respect wstrb[0] so firmware can byte-write.
                            if (mem_wstrb[0]) begin
                                enable   <= mem_wdata[0];
                                periodic <= mem_wdata[1];
                                if(mem_wdata[0]) begin
                                    event_latched <= 1'b0;
                                    count <= reload;
                                end
                            end
                        end

                        OFF_RELOAD: begin
                            reload <= mem_wdata;
                        end

                        OFF_COUNT: begin
                            count <= mem_wdata;
                            event_latched <= 1'b0; //KICK: clear pending timeout
                        end

                        OFF_EVENT: begin
                            // W1C bit0
                            if (mem_wdata[0]) event_latched <= 1'b0;
                        end
                        default: begin end
                    endcase
                end
            end
        end
    end

endmodule
