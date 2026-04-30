
module taketwo_wrap (
  `ifdef USE_POWER_PINS
  inout  wire         VDD,
  inout  wire         VSS,
  `endif
  input  wire         CLK,
  input  wire         RESETN,
  input  wire         en_i,
  output wire         irq,

  output wire [0:0]   maxi_awid,
  output wire [31:0]  maxi_awaddr,
  output wire [7:0]   maxi_awlen,
  output wire [2:0]   maxi_awsize,
  output wire [1:0]   maxi_awburst,
  output wire [0:0]   maxi_awlock,
  output wire [3:0]   maxi_awcache,
  output wire [2:0]   maxi_awprot,
  output wire [3:0]   maxi_awqos,
  output wire [1:0]   maxi_awuser,
  output wire         maxi_awvalid,
  input  wire         maxi_awready,

  output wire [31:0]  maxi_wdata,
  output wire [3:0]   maxi_wstrb,
  output wire         maxi_wlast,
  output wire         maxi_wvalid,
  input  wire         maxi_wready,

  input  wire [0:0]   maxi_bid,
  input  wire [1:0]   maxi_bresp,
  input  wire         maxi_bvalid,
  output wire         maxi_bready,

  output wire [0:0]   maxi_arid,
  output wire [31:0]  maxi_araddr,
  output wire [7:0]   maxi_arlen,
  output wire [2:0]   maxi_arsize,
  output wire [1:0]   maxi_arburst,
  output wire [0:0]   maxi_arlock,
  output wire [3:0]   maxi_arcache,
  output wire [2:0]   maxi_arprot,
  output wire [3:0]   maxi_arqos,
  output wire [1:0]   maxi_aruser,
  output wire         maxi_arvalid,
  input  wire         maxi_arready,

  input  wire [0:0]   maxi_rid,
  input  wire [31:0]  maxi_rdata,
  input  wire [1:0]   maxi_rresp,
  input  wire         maxi_rlast,
  input  wire         maxi_rvalid,
  output wire         maxi_rready,

  input  wire [31:0]  saxi_awaddr,
  input  wire [2:0]   saxi_awprot,
  input  wire         saxi_awvalid,
  output wire         saxi_awready,

  input  wire [31:0]  saxi_wdata,
  input  wire [3:0]   saxi_wstrb,
  input  wire         saxi_wvalid,
  output wire         saxi_wready,

  output wire [1:0]   saxi_bresp,
  output wire         saxi_bvalid,
  input  wire         saxi_bready,

  input  wire [31:0]  saxi_araddr,
  input  wire [2:0]   saxi_arprot,
  input  wire         saxi_arvalid,
  output wire         saxi_arready,

  output wire [31:0]  saxi_rdata,
  output wire [1:0]   saxi_rresp,
  output wire         saxi_rvalid,
  input  wire         saxi_rready,
  
  output wire signed [15:0] dbg_logit0,
  output wire signed [15:0] dbg_logit1
);

  // Tie master IDs to 0 (cocotbext needs them to exist)
  assign maxi_awid = 1'b0;
  assign maxi_arid = 1'b0;

  // Gate AXI master handshake signals so the core cannot initiate new
  // memory transactions when the ML domain is disabled.
  wire core_maxi_awvalid, core_maxi_wvalid, core_maxi_arvalid;
  wire core_maxi_bready,  core_maxi_rready;

  assign maxi_awvalid = core_maxi_awvalid & en_i;
  assign maxi_wvalid  = core_maxi_wvalid  & en_i;
  assign maxi_arvalid = core_maxi_arvalid & en_i;
  assign maxi_bready  = core_maxi_bready  & en_i;
  assign maxi_rready  = core_maxi_rready  & en_i;

  taketwo u_core (
    `ifdef USE_POWER_PINS
    .VDD(VDD),
    .VSS(VSS),
    `endif
    .CLK(CLK),
    .RESETN(RESETN),
    .irq(irq),

    .maxi_awaddr (maxi_awaddr),
    .maxi_awlen  (maxi_awlen),
    .maxi_awsize (maxi_awsize),
    .maxi_awburst(maxi_awburst),
    .maxi_awlock (maxi_awlock),
    .maxi_awcache(maxi_awcache),
    .maxi_awprot (maxi_awprot),
    .maxi_awqos  (maxi_awqos),
    .maxi_awuser (maxi_awuser),
    .maxi_awvalid(core_maxi_awvalid),
    .maxi_awready(maxi_awready),

    .maxi_wdata  (maxi_wdata),
    .maxi_wstrb  (maxi_wstrb),
    .maxi_wlast  (maxi_wlast),
    .maxi_wvalid (core_maxi_wvalid),
    .maxi_wready (maxi_wready),

    .maxi_bresp  (maxi_bresp),
    .maxi_bvalid (maxi_bvalid),
    .maxi_bready (core_maxi_bready),

    .maxi_araddr (maxi_araddr),
    .maxi_arlen  (maxi_arlen),
    .maxi_arsize (maxi_arsize),
    .maxi_arburst(maxi_arburst),
    .maxi_arlock (maxi_arlock),
    .maxi_arcache(maxi_arcache),
    .maxi_arprot (maxi_arprot),
    .maxi_arqos  (maxi_arqos),
    .maxi_aruser (maxi_aruser),
    .maxi_arvalid(core_maxi_arvalid),
    .maxi_arready(maxi_arready),

    .maxi_rdata  (maxi_rdata),
    .maxi_rresp  (maxi_rresp),
    .maxi_rlast  (maxi_rlast),
    .maxi_rvalid (maxi_rvalid),
    .maxi_rready (core_maxi_rready),


    .saxi_awaddr (saxi_awaddr),
    .saxi_awprot (saxi_awprot),
    .saxi_awvalid(saxi_awvalid),
    .saxi_awready(saxi_awready),

    .saxi_wdata  (saxi_wdata),
    .saxi_wstrb  (saxi_wstrb),
    .saxi_wvalid (saxi_wvalid),
    .saxi_wready (saxi_wready),

    .saxi_bresp  (saxi_bresp),
    .saxi_bvalid (saxi_bvalid),
    .saxi_bready (saxi_bready),

    .saxi_araddr (saxi_araddr),
    .saxi_arprot (saxi_arprot),
    .saxi_arvalid(saxi_arvalid),
    .saxi_arready(saxi_arready),

    .saxi_rdata  (saxi_rdata),
    .saxi_rresp  (saxi_rresp),
    .saxi_rvalid (saxi_rvalid),
    .saxi_rready (saxi_rready),
    .dbg_logit0  (dbg_logit0),
    .dbg_logit1  (dbg_logit1)
  );

endmodule
