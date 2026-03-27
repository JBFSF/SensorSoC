`timescale 1ns/1ps

module globaltimer_tb;

  logic        clk;
  logic        rst;
  logic        en;
  logic [15:0] time_in_night_seconds;
  logic        epoch_end;
  logic [9:0] epoch_index;

  globaltimer #(
    .clk_speed_hz(10000),                    //ADJUST THIS ALONG WITH THE CLOCK GEN TO TEST AT DIFFERENT CLOCK SPEEDS:
                                             //if we add a zero to this, take a zero off of the clock gen below (and vice versa).
                                             //the higher this number here is, the longer the sim runs so be careful
    .epoch_hz(100),
    .epoch_count_max(1000) 
  ) dut (
    .clk_i(clk),
    .rst_i(rst),
    .en_i(en),
    .time_in_night_seconds_o(time_in_night_seconds),
    .epoch_end_o(epoch_end),
    .epoch_index_o(epoch_index)
  );

  initial begin
    $dumpfile("globaltimer_tb.vcd");
    $dumpvars(0, globaltimer_tb);
  end


  initial begin
    clk = 1'b0;
    forever #50_000 clk = ~clk;
  end

  initial begin
    rst = 1'b1;
    en  = 1'b0;

    repeat (3) @(negedge clk);
    rst = 1'b0;

    @(negedge clk);
    en = 1'b1;

    // run for 101 seconds
    #101_000_000_000;

    $finish;
  end

endmodule