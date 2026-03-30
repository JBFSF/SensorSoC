`timescale 1ns/1ps
module sim_weight_placement;
  reg clk    = 0;
  reg resetn = 0;

  // CPU MMIO port
  reg        mem_valid;
  reg [31:0] mem_addr;
  reg [31:0] mem_wdata;
  reg [3:0]  mem_wstrb;
  wire       mem_ready;
  wire [31:0] mem_rdata;

  // AXI4 slave — write address channel
  reg  [0:0]  saxi_awid;
  reg  [31:0] saxi_awaddr;
  reg  [7:0]  saxi_awlen;
  reg  [2:0]  saxi_awsize;
  reg  [1:0]  saxi_awburst;
  reg  [0:0]  saxi_awlock;
  reg  [3:0]  saxi_awcache;
  reg  [2:0]  saxi_awprot;
  reg  [3:0]  saxi_awqos;
  reg  [1:0]  saxi_awuser;
  reg         saxi_awvalid;
  wire        saxi_awready;

  // AXI4 slave — write data channel
  reg  [31:0] saxi_wdata;
  reg  [3:0]  saxi_wstrb;
  reg         saxi_wlast;
  reg         saxi_wvalid;
  wire        saxi_wready;

  // AXI4 slave — write response channel
  wire [0:0]  saxi_bid;
  wire [1:0]  saxi_bresp;
  wire        saxi_bvalid;
  reg         saxi_bready;

  // AXI4 slave — read address channel
  reg  [0:0]  saxi_arid;
  reg  [31:0] saxi_araddr;
  reg  [7:0]  saxi_arlen;
  reg  [2:0]  saxi_arsize;
  reg  [1:0]  saxi_arburst;
  reg  [0:0]  saxi_arlock;
  reg  [3:0]  saxi_arcache;
  reg  [2:0]  saxi_arprot;
  reg  [3:0]  saxi_arqos;
  reg  [1:0]  saxi_aruser;
  reg         saxi_arvalid;
  wire        saxi_arready;

  // AXI4 slave — read data channel
  wire [0:0]  saxi_rid;
  wire [31:0] saxi_rdata;
  wire [1:0]  saxi_rresp;
  wire        saxi_rlast;
  wire        saxi_rvalid;
  reg         saxi_rready;

  weight_ram_axi #(
    .BASE_ADDR(32'h0300_6000),
    .WEIGHT_INIT_HEX("rtl/taketwo_params.hex")
  ) dut (
    .clk(clk),
    .resetn(resetn),

    .mem_valid(mem_valid),
    .mem_addr(mem_addr),
    .mem_wdata(mem_wdata),
    .mem_wstrb(mem_wstrb),
    .mem_ready(mem_ready),
    .mem_rdata(mem_rdata),

    .saxi_awid(saxi_awid),
    .saxi_awaddr(saxi_awaddr),
    .saxi_awlen(saxi_awlen),
    .saxi_awsize(saxi_awsize),
    .saxi_awburst(saxi_awburst),
    .saxi_awlock(saxi_awlock),
    .saxi_awcache(saxi_awcache),
    .saxi_awprot(saxi_awprot),
    .saxi_awqos(saxi_awqos),
    .saxi_awuser(saxi_awuser),
    .saxi_awvalid(saxi_awvalid),
    .saxi_awready(saxi_awready),

    .saxi_wdata(saxi_wdata),
    .saxi_wstrb(saxi_wstrb),
    .saxi_wlast(saxi_wlast),
    .saxi_wvalid(saxi_wvalid),
    .saxi_wready(saxi_wready),

    .saxi_bid(saxi_bid),
    .saxi_bresp(saxi_bresp),
    .saxi_bvalid(saxi_bvalid),
    .saxi_bready(saxi_bready),

    .saxi_arid(saxi_arid),
    .saxi_araddr(saxi_araddr),
    .saxi_arlen(saxi_arlen),
    .saxi_arsize(saxi_arsize),
    .saxi_arburst(saxi_arburst),
    .saxi_arlock(saxi_arlock),
    .saxi_arcache(saxi_arcache),
    .saxi_arprot(saxi_arprot),
    .saxi_arqos(saxi_arqos),
    .saxi_aruser(saxi_aruser),
    .saxi_arvalid(saxi_arvalid),
    .saxi_arready(saxi_arready),

    .saxi_rid(saxi_rid),
    .saxi_rdata(saxi_rdata),
    .saxi_rresp(saxi_rresp),
    .saxi_rlast(saxi_rlast),
    .saxi_rvalid(saxi_rvalid),
    .saxi_rready(saxi_rready)
  );

  // cocotb drives clk/resetn from Python
endmodule
