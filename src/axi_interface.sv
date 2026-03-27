module axi_interface (
  input  logic        CLK,
  input  logic        RESETN,

  // control
  input  logic        start,
  input  logic [31:0] x_addr,
  input  logic signed [15:0] x0,     // movement
  input  logic signed [15:0] x1,     // cosine
  input  logic signed [15:0] x2,     // delta_hr
  input  logic signed [15:0] x3,     // rmssd
  output logic        done,          // high when writes completed
  output logic        busy,          // high while writing

  // AXI4 write address channel
  output logic [31:0] maxi_awaddr,
  output logic [7:0]  maxi_awlen,
  output logic [2:0]  maxi_awsize,
  output logic [1:0]  maxi_awburst,
  output logic        maxi_awlock,
  output logic [3:0]  maxi_awcache,
  output logic [2:0]  maxi_awprot,
  output logic [3:0]  maxi_awqos,
  output logic [1:0]  maxi_awuser,
  output logic        maxi_awvalid,
  input  logic        maxi_awready,

  // AXI4 write data channel
  output logic [31:0] maxi_wdata,
  output logic [3:0]  maxi_wstrb,
  output logic        maxi_wlast,
  output logic        maxi_wvalid,
  input  logic        maxi_wready,

  // AXI4 write response channel
  input  logic [1:0]  maxi_bresp,
  input  logic        maxi_bvalid,
  output logic        maxi_bready
);

  assign maxi_awlen   = 8'd0;
  assign maxi_awsize  = 3'b010;   // 32-bit writes
  assign maxi_awburst = 2'b01; 
  assign maxi_awlock  = 1'b0;
  assign maxi_awcache = 4'b0000;
  assign maxi_awprot  = 3'b000;
  assign maxi_awqos   = 4'b0000;
  assign maxi_awuser  = 2'b00;

  assign maxi_wstrb   = 4'b1111;
  assign maxi_wlast   = 1'b1;
  assign maxi_bready  = 1'b1;


  logic [31:0] w0, w1;
  assign w0 = {x1[15:0], x0[15:0]};
  assign w1 = {x3[15:0], x2[15:0]};

  typedef enum logic [2:0] 
      {IDLE,
      AW0,
      W0S,
      B0,
      AW1,
      W1S,
      B1,
      DONE} st_t;
  st_t st;


  logic [31:0] awaddr_r, wdata_r;
  logic        awvalid_r, wvalid_r;

  assign maxi_awaddr  = awaddr_r;
  assign maxi_awvalid = awvalid_r;

  assign maxi_wdata   = wdata_r;
  assign maxi_wvalid  = wvalid_r;

  assign busy = (st != IDLE);

  always_ff @(posedge CLK) begin
    if (!RESETN) begin
      st       <= IDLE;
      done     <= 1'b0;

      awaddr_r <= 32'd0;
      awvalid_r<= 1'b0;

      wdata_r  <= 32'd0;
      wvalid_r <= 1'b0;
    end else begin
      done <= 1'b0;

      case (st)
        IDLE: begin
          awvalid_r <= 1'b0;
          wvalid_r  <= 1'b0;
          if (start) begin
            // set up first write
            awaddr_r  <= x_addr;
            awvalid_r <= 1'b1;
            st <= AW0;
          end
        end

        // ---- write 0: address ----
        AW0: begin
          if (awvalid_r && maxi_awready) begin
            awvalid_r <= 1'b0;
            // present data for write0
            wdata_r  <= w0;
            wvalid_r <= 1'b1;
            st <= W0S;
          end
        end

        // ---- write 0: data ----
        W0S: begin
          if (wvalid_r && maxi_wready) begin
            wvalid_r <= 1'b0;
            st <= B0;
          end
        end

        // ---- write 0: response ----
        B0: begin
          if (maxi_bvalid) begin
            // set up second write
            awaddr_r  <= x_addr + 32'd4;
            awvalid_r <= 1'b1;
            st <= AW1;
          end
        end

        // ---- write 1: address ----
        AW1: begin
          if (awvalid_r && maxi_awready) begin
            awvalid_r <= 1'b0;
            // present data for write1
            wdata_r  <= w1;
            wvalid_r <= 1'b1;
            st <= W1S;
          end
        end

        // ---- write 1: data ----
        W1S: begin
          if (wvalid_r && maxi_wready) begin
            wvalid_r <= 1'b0;
            st <= B1;
          end
        end

        // ---- write 1: response ----
        B1: begin
          if (maxi_bvalid) begin
            st <= DONE;
          end
        end

        DONE: begin
          done <= 1'b1;   // 1-cycle pulse
          st   <= IDLE;
        end

        default: st <= IDLE;
      endcase
    end
  end

endmodule