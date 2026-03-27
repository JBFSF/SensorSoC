//ASSUMING logit 1 = wake, need to double check this
//logit 1 lower for a while -> confidence should drop, no wake
//logit 1 higher for a while -> confidence should rise, wake

module logit_to_confidence #(
  parameter int SHIFT_INST = 3,   // gain for instantaneous mapping (diff >>> SHIFT_INST)
  parameter int IIR_SHIFT = 4    // smoothing: avg += (inst-avg) >>> IIR_SHIFT
)(
  input  logic clk_i,
  input  logic rst_ni,          // active-low reset
  input  logic en_i,            // set this high when we are at the minimum hours and minutes of sleep (someone wants to wake up around 8, so we set this high at 7:30, for example)
  input  logic sample_valid_i,  // pulse when new logits are ready
  input  logic signed [15:0] log0,
  input  logic signed [15:0] log1,

  output logic [7:0]         confidence_o,     // closer to 255 -> wake, closer to 0, sleep
  output logic [7:0]         inst_confidence_o // for debug 
);

  logic signed [16:0] diff;
  logic signed [16:0] scaled;
  logic signed [17:0] inst_temp;
  logic [7:0] inst_conf;

  always_comb begin
    diff = log1 - log0;
    scaled = diff >>> SHIFT_INST;
    inst_temp = 18'sd128 + scaled;

    if (inst_temp <= 18'sd0)        inst_conf = 8'd0;
    else if (inst_temp >= 18'sd255) inst_conf = 8'd255;
    else                            inst_conf = inst_temp[7:0];

    inst_confidence_o = inst_conf;
  end

  logic signed [8:0] avg_q;
  logic signed [8:0] inst_q;
    logic signed [9:0] err;
  logic signed [9:0] delta;
  logic signed [9:0] next_avg;

 
  always_comb begin
    inst_q = {1'b0, inst_conf};
    err = inst_q - avg_q; 
    delta = err >>> IIR_SHIFT;
    next_avg = avg_q + delta;
  end

  // update avg when enabled + new sample arrives
  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      avg_q <= 9'd128;
    end else begin
      if (!en_i) begin 
        avg_q <= 9'd128; // if not enabled, reset avg to neutral (128), we can change this to decay over time if we want
      end else if (sample_valid_i) begin
        if (next_avg < 10'sd0)
          avg_q <= 9'd0;
        else if (next_avg > 10'sd255)
          avg_q <= 9'd255;
        else
          avg_q <= next_avg[8:0];
      end
    end
  end

  assign confidence_o = avg_q[7:0];

endmodule