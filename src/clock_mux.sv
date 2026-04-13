module clock_mux (
    input  logic clk_a,
    input  logic clk_b,
    input  logic sel,
    input  logic reset_i,
    output logic clk_o
);

logic i_and1, i_and2;
logic sync1_o, sync2_o;
logic q_1, q_2;

assign i_and1 = ~sel & ~sync2_o;
assign i_and2 =  sel & ~sync1_o;

assign clk_o = (clk_a & sync1_o) | (clk_b & sync2_o);

always_ff @(posedge clk_a) begin 
    if (reset_i) begin
        q_1 <= 1'b1;
    end else begin
        q_1 <= i_and1;
    end
end

always_ff @(posedge clk_a) begin 
    if (reset_i) begin
        sync1_o <= 1'b1;
    end else begin
        sync1_o <= q_1;
    end
end

always_ff @(posedge clk_b) begin 
    if (reset_i) begin
        q_2 <= 1'b0;
    end else begin
        q_2 <= i_and2;
    end
end

always_ff @(posedge clk_b) begin 
    if (reset_i) begin
        sync2_o <= 1'b0;
    end else begin
        sync2_o <= q_2;
    end
end

endmodule
