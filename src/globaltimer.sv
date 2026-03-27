module globaltimer #(
  parameter int unsigned clk_speed_hz = 10_000_000, // default 10 MHz clock
  parameter int unsigned epoch_hz = 100,        // default 100 Hz sample rate
  parameter int unsigned epoch_count_max = 1000        // 1000 samples (10 seconds at 100 Hz)
) (
  input  logic clk_i,
  input  logic rst_i,
  input  logic en_i,                            // should go high and stay high as soon as the "night" starts
  output logic [15:0] time_in_night_seconds_o,         
  output logic  epoch_end_o,                      // high for 1 cycle after 1000 epochs (10 seconds at 100 Hz)
  output logic [9:0]  epoch_index_o                     // which epoch we are on (0 to 999, wraps around)
); 

  localparam int unsigned CYCLES_PER_SEC = (clk_speed_hz < 1) ? 1 : clk_speed_hz;
  localparam int unsigned CYCLES_PER_EPOCH = (clk_speed_hz >= epoch_hz && epoch_hz >= 1) ? (clk_speed_hz / epoch_hz) : 1;

  localparam int unsigned SEC_W = (CYCLES_PER_SEC <= 1) ? 1 : $clog2(CYCLES_PER_SEC);
  localparam int unsigned EPOCH_W = (CYCLES_PER_EPOCH <= 1) ? 1 : $clog2(CYCLES_PER_EPOCH);

  logic [SEC_W-1:0]   sec_div_q;
  logic [EPOCH_W-1:0] epoch_div_q;

  logic sec_tick, epoch_tick;

  // clock dividing
  always_ff @(posedge clk_i) begin
    if (rst_i) begin
      sec_div_q <= '0;
      epoch_div_q <= '0;
    end else if (en_i) begin
      // 1 Hz tick
      if (sec_div_q == CYCLES_PER_SEC-1) sec_div_q <= '0;
      else sec_div_q <= sec_div_q + 1'b1;

      // epoch_hz tick
      if (epoch_div_q == CYCLES_PER_EPOCH-1) epoch_div_q <= '0;
      else epoch_div_q <= epoch_div_q + 1'b1;
    end
  end

  assign sec_tick = en_i && (sec_div_q == CYCLES_PER_SEC-1);
  assign epoch_tick = en_i && (epoch_div_q == CYCLES_PER_EPOCH-1);

  // time in seconds counter
  always_ff @(posedge clk_i) begin
    if (rst_i) begin
      time_in_night_seconds_o <= 16'd0;
    end else if (sec_tick) begin
      time_in_night_seconds_o <= time_in_night_seconds_o + 16'd1;
    end
  end

  // epoch counter
  always_ff @(posedge clk_i) begin
    if (rst_i) begin
      epoch_index_o <= '0;
      epoch_end_o <= 1'b0;
    end else begin
      epoch_end_o <= 1'b0;

      if (epoch_tick) begin
        if (epoch_index_o == epoch_count_max-1) begin
          epoch_index_o <= '0;    // wrap after 1000 epochs
          epoch_end_o <= 1'b1;    // 1-cycle pulse on wrap
        end else begin
          epoch_index_o <= epoch_index_o + 10'd1;
        end
      end
    end
  end


endmodule
