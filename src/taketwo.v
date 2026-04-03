

module taketwo
(
  input CLK,
  input RESETN,
  output reg irq,
  output reg [32-1:0] maxi_awaddr,
  output reg [8-1:0] maxi_awlen,
  output [3-1:0] maxi_awsize,
  output [2-1:0] maxi_awburst,
  output [1-1:0] maxi_awlock,
  output [4-1:0] maxi_awcache,
  output [3-1:0] maxi_awprot,
  output [4-1:0] maxi_awqos,
  output [2-1:0] maxi_awuser,
  output reg maxi_awvalid,
  input maxi_awready,
  output [32-1:0] maxi_wdata,
  output [4-1:0] maxi_wstrb,
  output maxi_wlast,
  output maxi_wvalid,
  input maxi_wready,
  input [2-1:0] maxi_bresp,
  input maxi_bvalid,
  output maxi_bready,
  output reg [32-1:0] maxi_araddr,
  output reg [8-1:0] maxi_arlen,
  output [3-1:0] maxi_arsize,
  output [2-1:0] maxi_arburst,
  output [1-1:0] maxi_arlock,
  output [4-1:0] maxi_arcache,
  output [3-1:0] maxi_arprot,
  output [4-1:0] maxi_arqos,
  output [2-1:0] maxi_aruser,
  output reg maxi_arvalid,
  input maxi_arready,
  input [32-1:0] maxi_rdata,
  input [2-1:0] maxi_rresp,
  input maxi_rlast,
  input maxi_rvalid,
  output maxi_rready,
  input [32-1:0] saxi_awaddr,
  input [4-1:0] saxi_awcache,
  input [3-1:0] saxi_awprot,
  input saxi_awvalid,
  output saxi_awready,
  input [32-1:0] saxi_wdata,
  input [4-1:0] saxi_wstrb,
  input saxi_wvalid,
  output saxi_wready,
  output [2-1:0] saxi_bresp,
  output reg saxi_bvalid,
  input saxi_bready,
  input [32-1:0] saxi_araddr,
  input [4-1:0] saxi_arcache,
  input [3-1:0] saxi_arprot,
  input saxi_arvalid,
  output saxi_arready,
  output reg [32-1:0] saxi_rdata,
  output [2-1:0] saxi_rresp,
  output reg saxi_rvalid,
  input saxi_rready
);

  wire RESETN_inv;
  assign RESETN_inv = !RESETN;
  wire RESETN_inv_buf;
  reg _RESETN_inv_1;
  reg _RESETN_inv_2;
  assign RESETN_inv_buf = _RESETN_inv_2;
  assign maxi_awsize = 2;
  assign maxi_awburst = 1;
  assign maxi_awlock = 0;
  assign maxi_awcache = 3;
  assign maxi_awprot = 0;
  assign maxi_awqos = 0;
  assign maxi_awuser = 0;
  reg [32-1:0] _maxi_wdata_sb_0;
  reg [4-1:0] _maxi_wstrb_sb_0;
  reg _maxi_wlast_sb_0;
  reg _maxi_wvalid_sb_0;
  wire _maxi_wready_sb_0;
  wire _sb_maxi_writedata_s_value_0;
  assign _sb_maxi_writedata_s_value_0 = _maxi_wlast_sb_0;
  wire [4-1:0] _sb_maxi_writedata_s_value_1;
  assign _sb_maxi_writedata_s_value_1 = _maxi_wstrb_sb_0;
  wire [32-1:0] _sb_maxi_writedata_s_value_2;
  assign _sb_maxi_writedata_s_value_2 = _maxi_wdata_sb_0;
  wire [37-1:0] _sb_maxi_writedata_s_data_3;
  assign _sb_maxi_writedata_s_data_3 = { _sb_maxi_writedata_s_value_0, _sb_maxi_writedata_s_value_1, _sb_maxi_writedata_s_value_2 };
  wire _sb_maxi_writedata_s_valid_4;
  assign _sb_maxi_writedata_s_valid_4 = _maxi_wvalid_sb_0;
  wire _sb_maxi_writedata_m_ready_5;
  assign _sb_maxi_writedata_m_ready_5 = maxi_wready;
  reg [37-1:0] _sb_maxi_writedata_data_6;
  reg _sb_maxi_writedata_valid_7;
  wire _sb_maxi_writedata_ready_8;
  reg [37-1:0] _sb_maxi_writedata_tmp_data_9;
  reg _sb_maxi_writedata_tmp_valid_10;
  wire [37-1:0] _sb_maxi_writedata_next_data_11;
  wire _sb_maxi_writedata_next_valid_12;
  assign _sb_maxi_writedata_ready_8 = !_sb_maxi_writedata_tmp_valid_10;
  assign _sb_maxi_writedata_next_data_11 = (_sb_maxi_writedata_tmp_valid_10)? _sb_maxi_writedata_tmp_data_9 : _sb_maxi_writedata_s_data_3;
  assign _sb_maxi_writedata_next_valid_12 = _sb_maxi_writedata_tmp_valid_10 || _sb_maxi_writedata_s_valid_4;
  wire _sb_maxi_writedata_m_value_13;
  assign _sb_maxi_writedata_m_value_13 = _sb_maxi_writedata_data_6[36:36];
  wire [4-1:0] _sb_maxi_writedata_m_value_14;
  assign _sb_maxi_writedata_m_value_14 = _sb_maxi_writedata_data_6[35:32];
  wire [32-1:0] _sb_maxi_writedata_m_value_15;
  assign _sb_maxi_writedata_m_value_15 = _sb_maxi_writedata_data_6[31:0];
  assign _maxi_wready_sb_0 = _sb_maxi_writedata_ready_8;
  assign maxi_wdata = _sb_maxi_writedata_m_value_15;
  assign maxi_wstrb = _sb_maxi_writedata_m_value_14;
  assign maxi_wlast = _sb_maxi_writedata_m_value_13;
  assign maxi_wvalid = _sb_maxi_writedata_valid_7;
  assign maxi_bready = 1;
  assign maxi_arsize = 2;
  assign maxi_arburst = 1;
  assign maxi_arlock = 0;
  assign maxi_arcache = 3;
  assign maxi_arprot = 0;
  assign maxi_arqos = 0;
  assign maxi_aruser = 0;
  wire [32-1:0] _maxi_rdata_sb_0;
  wire _maxi_rlast_sb_0;
  wire _maxi_rvalid_sb_0;
  wire _maxi_rready_sb_0;
  wire _sb_maxi_readdata_s_value_16;
  assign _sb_maxi_readdata_s_value_16 = maxi_rlast;
  wire [32-1:0] _sb_maxi_readdata_s_value_17;
  assign _sb_maxi_readdata_s_value_17 = maxi_rdata;
  wire [33-1:0] _sb_maxi_readdata_s_data_18;
  assign _sb_maxi_readdata_s_data_18 = { _sb_maxi_readdata_s_value_16, _sb_maxi_readdata_s_value_17 };
  wire _sb_maxi_readdata_s_valid_19;
  assign _sb_maxi_readdata_s_valid_19 = maxi_rvalid;
  wire _sb_maxi_readdata_m_ready_20;
  assign _sb_maxi_readdata_m_ready_20 = _maxi_rready_sb_0;
  reg [33-1:0] _sb_maxi_readdata_data_21;
  reg _sb_maxi_readdata_valid_22;
  wire _sb_maxi_readdata_ready_23;
  reg [33-1:0] _sb_maxi_readdata_tmp_data_24;
  reg _sb_maxi_readdata_tmp_valid_25;
  wire [33-1:0] _sb_maxi_readdata_next_data_26;
  wire _sb_maxi_readdata_next_valid_27;
  assign _sb_maxi_readdata_ready_23 = !_sb_maxi_readdata_tmp_valid_25;
  assign _sb_maxi_readdata_next_data_26 = (_sb_maxi_readdata_tmp_valid_25)? _sb_maxi_readdata_tmp_data_24 : _sb_maxi_readdata_s_data_18;
  assign _sb_maxi_readdata_next_valid_27 = _sb_maxi_readdata_tmp_valid_25 || _sb_maxi_readdata_s_valid_19;
  wire _sb_maxi_readdata_m_value_28;
  assign _sb_maxi_readdata_m_value_28 = _sb_maxi_readdata_data_21[32:32];
  wire [32-1:0] _sb_maxi_readdata_m_value_29;
  assign _sb_maxi_readdata_m_value_29 = _sb_maxi_readdata_data_21[31:0];
  assign _maxi_rdata_sb_0 = _sb_maxi_readdata_m_value_29;
  assign _maxi_rlast_sb_0 = _sb_maxi_readdata_m_value_28;
  assign _maxi_rvalid_sb_0 = _sb_maxi_readdata_valid_22;
  assign maxi_rready = _sb_maxi_readdata_ready_23;
  reg [3-1:0] _maxi_outstanding_wcount;
  wire _maxi_has_outstanding_write;
  assign _maxi_has_outstanding_write = (_maxi_outstanding_wcount > 0) || maxi_awvalid;
  reg _maxi_read_start;
  reg [8-1:0] _maxi_read_op_sel;
  reg [32-1:0] _maxi_read_global_addr;
  reg [33-1:0] _maxi_read_global_size;
  reg [32-1:0] _maxi_read_local_addr;
  reg [32-1:0] _maxi_read_local_stride;
  reg [33-1:0] _maxi_read_local_size;
  reg [32-1:0] _maxi_read_local_blocksize;
  wire _maxi_read_req_fifo_enq;
  wire [137-1:0] _maxi_read_req_fifo_wdata;
  wire _maxi_read_req_fifo_full;
  wire _maxi_read_req_fifo_almost_full;
  wire _maxi_read_req_fifo_deq;
  wire [137-1:0] _maxi_read_req_fifo_rdata;
  wire _maxi_read_req_fifo_empty;
  wire _maxi_read_req_fifo_almost_empty;

  _maxi_read_req_fifo
  inst__maxi_read_req_fifo
  (
    .CLK(CLK),
    .RST(RESETN_inv_buf),
    ._maxi_read_req_fifo_enq(_maxi_read_req_fifo_enq),
    ._maxi_read_req_fifo_wdata(_maxi_read_req_fifo_wdata),
    ._maxi_read_req_fifo_full(_maxi_read_req_fifo_full),
    ._maxi_read_req_fifo_almost_full(_maxi_read_req_fifo_almost_full),
    ._maxi_read_req_fifo_deq(_maxi_read_req_fifo_deq),
    ._maxi_read_req_fifo_rdata(_maxi_read_req_fifo_rdata),
    ._maxi_read_req_fifo_empty(_maxi_read_req_fifo_empty),
    ._maxi_read_req_fifo_almost_empty(_maxi_read_req_fifo_almost_empty)
  );

  reg [4-1:0] count__maxi_read_req_fifo;
  wire [8-1:0] _maxi_read_op_sel_fifo;
  wire [32-1:0] _maxi_read_local_addr_fifo;
  wire [32-1:0] _maxi_read_local_stride_fifo;
  wire [33-1:0] _maxi_read_local_size_fifo;
  wire [32-1:0] _maxi_read_local_blocksize_fifo;
  wire [8-1:0] unpack_read_req_op_sel_30;
  wire [32-1:0] unpack_read_req_local_addr_31;
  wire [32-1:0] unpack_read_req_local_stride_32;
  wire [33-1:0] unpack_read_req_local_size_33;
  wire [32-1:0] unpack_read_req_local_blocksize_34;
  assign unpack_read_req_op_sel_30 = _maxi_read_req_fifo_rdata[136:129];
  assign unpack_read_req_local_addr_31 = _maxi_read_req_fifo_rdata[128:97];
  assign unpack_read_req_local_stride_32 = _maxi_read_req_fifo_rdata[96:65];
  assign unpack_read_req_local_size_33 = _maxi_read_req_fifo_rdata[64:32];
  assign unpack_read_req_local_blocksize_34 = _maxi_read_req_fifo_rdata[31:0];
  assign _maxi_read_op_sel_fifo = unpack_read_req_op_sel_30;
  assign _maxi_read_local_addr_fifo = unpack_read_req_local_addr_31;
  assign _maxi_read_local_stride_fifo = unpack_read_req_local_stride_32;
  assign _maxi_read_local_size_fifo = unpack_read_req_local_size_33;
  assign _maxi_read_local_blocksize_fifo = unpack_read_req_local_blocksize_34;
  reg [8-1:0] _maxi_read_op_sel_buf;
  reg [32-1:0] _maxi_read_local_addr_buf;
  reg [32-1:0] _maxi_read_local_stride_buf;
  reg [33-1:0] _maxi_read_local_size_buf;
  reg [32-1:0] _maxi_read_local_blocksize_buf;
  reg _maxi_read_req_busy;
  reg _maxi_read_data_busy;
  wire _maxi_read_req_idle;
  wire _maxi_read_data_idle;
  wire _maxi_read_idle;
  assign _maxi_read_req_idle = !_maxi_read_start && !_maxi_read_req_busy;
  assign _maxi_read_data_idle = _maxi_read_req_fifo_empty && !_maxi_read_data_busy;
  assign _maxi_read_idle = _maxi_read_req_idle && _maxi_read_data_idle;
  reg _maxi_write_start;
  reg [8-1:0] _maxi_write_op_sel;
  reg [32-1:0] _maxi_write_global_addr;
  reg [33-1:0] _maxi_write_global_size;
  reg [32-1:0] _maxi_write_local_addr;
  reg [32-1:0] _maxi_write_local_stride;
  reg [33-1:0] _maxi_write_local_size;
  reg [32-1:0] _maxi_write_local_blocksize;
  wire _maxi_write_req_fifo_enq;
  wire [137-1:0] _maxi_write_req_fifo_wdata;
  wire _maxi_write_req_fifo_full;
  wire _maxi_write_req_fifo_almost_full;
  wire _maxi_write_req_fifo_deq;
  wire [137-1:0] _maxi_write_req_fifo_rdata;
  wire _maxi_write_req_fifo_empty;
  wire _maxi_write_req_fifo_almost_empty;

  _maxi_write_req_fifo
  inst__maxi_write_req_fifo
  (
    .CLK(CLK),
    .RST(RESETN_inv_buf),
    ._maxi_write_req_fifo_enq(_maxi_write_req_fifo_enq),
    ._maxi_write_req_fifo_wdata(_maxi_write_req_fifo_wdata),
    ._maxi_write_req_fifo_full(_maxi_write_req_fifo_full),
    ._maxi_write_req_fifo_almost_full(_maxi_write_req_fifo_almost_full),
    ._maxi_write_req_fifo_deq(_maxi_write_req_fifo_deq),
    ._maxi_write_req_fifo_rdata(_maxi_write_req_fifo_rdata),
    ._maxi_write_req_fifo_empty(_maxi_write_req_fifo_empty),
    ._maxi_write_req_fifo_almost_empty(_maxi_write_req_fifo_almost_empty)
  );

  reg [4-1:0] count__maxi_write_req_fifo;
  wire [8-1:0] _maxi_write_op_sel_fifo;
  wire [32-1:0] _maxi_write_local_addr_fifo;
  wire [32-1:0] _maxi_write_local_stride_fifo;
  wire [33-1:0] _maxi_write_size_fifo;
  wire [32-1:0] _maxi_write_local_blocksize_fifo;
  wire [8-1:0] unpack_write_req_op_sel_35;
  wire [32-1:0] unpack_write_req_local_addr_36;
  wire [32-1:0] unpack_write_req_local_stride_37;
  wire [33-1:0] unpack_write_req_size_38;
  wire [32-1:0] unpack_write_req_local_blocksize_39;
  assign unpack_write_req_op_sel_35 = _maxi_write_req_fifo_rdata[136:129];
  assign unpack_write_req_local_addr_36 = _maxi_write_req_fifo_rdata[128:97];
  assign unpack_write_req_local_stride_37 = _maxi_write_req_fifo_rdata[96:65];
  assign unpack_write_req_size_38 = _maxi_write_req_fifo_rdata[64:32];
  assign unpack_write_req_local_blocksize_39 = _maxi_write_req_fifo_rdata[31:0];
  assign _maxi_write_op_sel_fifo = unpack_write_req_op_sel_35;
  assign _maxi_write_local_addr_fifo = unpack_write_req_local_addr_36;
  assign _maxi_write_local_stride_fifo = unpack_write_req_local_stride_37;
  assign _maxi_write_size_fifo = unpack_write_req_size_38;
  assign _maxi_write_local_blocksize_fifo = unpack_write_req_local_blocksize_39;
  reg [8-1:0] _maxi_write_op_sel_buf;
  reg [32-1:0] _maxi_write_local_addr_buf;
  reg [32-1:0] _maxi_write_local_stride_buf;
  reg [33-1:0] _maxi_write_size_buf;
  reg [32-1:0] _maxi_write_local_blocksize_buf;
  reg _maxi_write_req_busy;
  reg _maxi_write_data_busy;
  wire _maxi_write_req_idle;
  wire _maxi_write_data_idle;
  wire _maxi_write_idle;
  assign _maxi_write_req_idle = !_maxi_write_start && !_maxi_write_req_busy;
  assign _maxi_write_data_idle = _maxi_write_req_fifo_empty && !_maxi_write_data_busy;
  assign _maxi_write_idle = _maxi_write_req_idle && _maxi_write_data_idle;
  reg [32-1:0] _maxi_global_base_addr;
  assign saxi_bresp = 0;
  assign saxi_rresp = 0;
  reg signed [32-1:0] _saxi_register_0;
  reg signed [32-1:0] _saxi_register_1;
  reg signed [32-1:0] _saxi_register_2;
  reg signed [32-1:0] _saxi_register_3;
  reg signed [32-1:0] _saxi_register_4;
  reg signed [32-1:0] _saxi_register_5;
  reg signed [32-1:0] _saxi_register_6;
  reg signed [32-1:0] _saxi_register_7;
  reg signed [32-1:0] _saxi_register_8;
  reg signed [32-1:0] _saxi_register_9;
  reg signed [32-1:0] _saxi_register_10;
  reg signed [32-1:0] _saxi_register_11;
  reg signed [32-1:0] _saxi_register_12;
  reg signed [32-1:0] _saxi_register_13;
  reg signed [32-1:0] _saxi_register_14;
  reg signed [32-1:0] _saxi_register_15;
  reg signed [32-1:0] _saxi_register_16;
  reg signed [32-1:0] _saxi_register_17;
  reg signed [32-1:0] _saxi_register_18;
  reg signed [32-1:0] _saxi_register_19;
  reg signed [32-1:0] _saxi_register_20;
  reg signed [32-1:0] _saxi_register_21;
  reg signed [32-1:0] _saxi_register_22;
  reg signed [32-1:0] _saxi_register_23;
  reg signed [32-1:0] _saxi_register_24;
  reg signed [32-1:0] _saxi_register_25;
  reg signed [32-1:0] _saxi_register_26;
  reg signed [32-1:0] _saxi_register_27;
  reg signed [32-1:0] _saxi_register_28;
  reg signed [32-1:0] _saxi_register_29;
  reg signed [32-1:0] _saxi_register_30;
  reg signed [32-1:0] _saxi_register_31;
  reg signed [32-1:0] _saxi_register_32;
  reg signed [32-1:0] _saxi_register_33;
  reg signed [32-1:0] _saxi_register_34;
  reg signed [32-1:0] _saxi_register_35;
  reg signed [32-1:0] _saxi_register_36;
  reg _saxi_flag_0;
  reg _saxi_flag_1;
  reg _saxi_flag_2;
  reg _saxi_flag_3;
  reg _saxi_flag_4;
  reg _saxi_flag_5;
  reg _saxi_flag_6;
  reg _saxi_flag_7;
  reg _saxi_flag_8;
  reg _saxi_flag_9;
  reg _saxi_flag_10;
  reg _saxi_flag_11;
  reg _saxi_flag_12;
  reg _saxi_flag_13;
  reg _saxi_flag_14;
  reg _saxi_flag_15;
  reg _saxi_flag_16;
  reg _saxi_flag_17;
  reg _saxi_flag_18;
  reg _saxi_flag_19;
  reg _saxi_flag_20;
  reg _saxi_flag_21;
  reg _saxi_flag_22;
  reg _saxi_flag_23;
  reg _saxi_flag_24;
  reg _saxi_flag_25;
  reg _saxi_flag_26;
  reg _saxi_flag_27;
  reg _saxi_flag_28;
  reg _saxi_flag_29;
  reg _saxi_flag_30;
  reg _saxi_flag_31;
  reg _saxi_flag_32;
  reg _saxi_flag_33;
  reg _saxi_flag_34;
  reg _saxi_flag_35;
  reg _saxi_flag_36;
  reg signed [32-1:0] _saxi_resetval_0;
  reg signed [32-1:0] _saxi_resetval_1;
  reg signed [32-1:0] _saxi_resetval_2;
  reg signed [32-1:0] _saxi_resetval_3;
  reg signed [32-1:0] _saxi_resetval_4;
  reg signed [32-1:0] _saxi_resetval_5;
  reg signed [32-1:0] _saxi_resetval_6;
  reg signed [32-1:0] _saxi_resetval_7;
  reg signed [32-1:0] _saxi_resetval_8;
  reg signed [32-1:0] _saxi_resetval_9;
  reg signed [32-1:0] _saxi_resetval_10;
  reg signed [32-1:0] _saxi_resetval_11;
  reg signed [32-1:0] _saxi_resetval_12;
  reg signed [32-1:0] _saxi_resetval_13;
  reg signed [32-1:0] _saxi_resetval_14;
  reg signed [32-1:0] _saxi_resetval_15;
  reg signed [32-1:0] _saxi_resetval_16;
  reg signed [32-1:0] _saxi_resetval_17;
  reg signed [32-1:0] _saxi_resetval_18;
  reg signed [32-1:0] _saxi_resetval_19;
  reg signed [32-1:0] _saxi_resetval_20;
  reg signed [32-1:0] _saxi_resetval_21;
  reg signed [32-1:0] _saxi_resetval_22;
  reg signed [32-1:0] _saxi_resetval_23;
  reg signed [32-1:0] _saxi_resetval_24;
  reg signed [32-1:0] _saxi_resetval_25;
  reg signed [32-1:0] _saxi_resetval_26;
  reg signed [32-1:0] _saxi_resetval_27;
  reg signed [32-1:0] _saxi_resetval_28;
  reg signed [32-1:0] _saxi_resetval_29;
  reg signed [32-1:0] _saxi_resetval_30;
  reg signed [32-1:0] _saxi_resetval_31;
  reg signed [32-1:0] _saxi_resetval_32;
  reg signed [32-1:0] _saxi_resetval_33;
  reg signed [32-1:0] _saxi_resetval_34;
  reg signed [32-1:0] _saxi_resetval_35;
  reg signed [32-1:0] _saxi_resetval_36;
  localparam _saxi_maskwidth = 6;
  localparam _saxi_mask = { _saxi_maskwidth{ 1'd1 } };
  localparam _saxi_shift = 2;
  reg [32-1:0] _saxi_register_fsm;
  localparam _saxi_register_fsm_init = 0;
  reg [32-1:0] addr_40;
  reg writevalid_41;
  reg readvalid_42;
  reg prev_awvalid_43;
  reg prev_arvalid_44;
  assign saxi_awready = (_saxi_register_fsm == 0) && (!writevalid_41 && !readvalid_42 && !saxi_bvalid && prev_awvalid_43);
  assign saxi_arready = (_saxi_register_fsm == 0) && (!readvalid_42 && !writevalid_41 && prev_arvalid_44 && !prev_awvalid_43);
  reg [_saxi_maskwidth-1:0] axis_maskaddr_45;
  wire signed [32-1:0] axislite_rdata_46;
  assign axislite_rdata_46 = (axis_maskaddr_45 == 0)? _saxi_register_0 : 
                             (axis_maskaddr_45 == 1)? _saxi_register_1 : 
                             (axis_maskaddr_45 == 2)? _saxi_register_2 : 
                             (axis_maskaddr_45 == 3)? _saxi_register_3 : 
                             (axis_maskaddr_45 == 4)? _saxi_register_4 : 
                             (axis_maskaddr_45 == 5)? _saxi_register_5 : 
                             (axis_maskaddr_45 == 6)? _saxi_register_6 : 
                             (axis_maskaddr_45 == 7)? _saxi_register_7 : 
                             (axis_maskaddr_45 == 8)? _saxi_register_8 : 
                             (axis_maskaddr_45 == 9)? _saxi_register_9 : 
                             (axis_maskaddr_45 == 10)? _saxi_register_10 : 
                             (axis_maskaddr_45 == 11)? _saxi_register_11 : 
                             (axis_maskaddr_45 == 12)? _saxi_register_12 : 
                             (axis_maskaddr_45 == 13)? _saxi_register_13 : 
                             (axis_maskaddr_45 == 14)? _saxi_register_14 : 
                             (axis_maskaddr_45 == 15)? _saxi_register_15 : 
                             (axis_maskaddr_45 == 16)? _saxi_register_16 : 
                             (axis_maskaddr_45 == 17)? _saxi_register_17 : 
                             (axis_maskaddr_45 == 18)? _saxi_register_18 : 
                             (axis_maskaddr_45 == 19)? _saxi_register_19 : 
                             (axis_maskaddr_45 == 20)? _saxi_register_20 : 
                             (axis_maskaddr_45 == 21)? _saxi_register_21 : 
                             (axis_maskaddr_45 == 22)? _saxi_register_22 : 
                             (axis_maskaddr_45 == 23)? _saxi_register_23 : 
                             (axis_maskaddr_45 == 24)? _saxi_register_24 : 
                             (axis_maskaddr_45 == 25)? _saxi_register_25 : 
                             (axis_maskaddr_45 == 26)? _saxi_register_26 : 
                             (axis_maskaddr_45 == 27)? _saxi_register_27 : 
                             (axis_maskaddr_45 == 28)? _saxi_register_28 : 
                             (axis_maskaddr_45 == 29)? _saxi_register_29 : 
                             (axis_maskaddr_45 == 30)? _saxi_register_30 : 
                             (axis_maskaddr_45 == 31)? _saxi_register_31 : 
                             (axis_maskaddr_45 == 32)? _saxi_register_32 : 
                             (axis_maskaddr_45 == 33)? _saxi_register_33 : 
                             (axis_maskaddr_45 == 34)? _saxi_register_34 : 
                             (axis_maskaddr_45 == 35)? _saxi_register_35 : 
                             (axis_maskaddr_45 == 36)? _saxi_register_36 : 'hx;
  wire axislite_flag_47;
  assign axislite_flag_47 = (axis_maskaddr_45 == 0)? _saxi_flag_0 : 
                            (axis_maskaddr_45 == 1)? _saxi_flag_1 : 
                            (axis_maskaddr_45 == 2)? _saxi_flag_2 : 
                            (axis_maskaddr_45 == 3)? _saxi_flag_3 : 
                            (axis_maskaddr_45 == 4)? _saxi_flag_4 : 
                            (axis_maskaddr_45 == 5)? _saxi_flag_5 : 
                            (axis_maskaddr_45 == 6)? _saxi_flag_6 : 
                            (axis_maskaddr_45 == 7)? _saxi_flag_7 : 
                            (axis_maskaddr_45 == 8)? _saxi_flag_8 : 
                            (axis_maskaddr_45 == 9)? _saxi_flag_9 : 
                            (axis_maskaddr_45 == 10)? _saxi_flag_10 : 
                            (axis_maskaddr_45 == 11)? _saxi_flag_11 : 
                            (axis_maskaddr_45 == 12)? _saxi_flag_12 : 
                            (axis_maskaddr_45 == 13)? _saxi_flag_13 : 
                            (axis_maskaddr_45 == 14)? _saxi_flag_14 : 
                            (axis_maskaddr_45 == 15)? _saxi_flag_15 : 
                            (axis_maskaddr_45 == 16)? _saxi_flag_16 : 
                            (axis_maskaddr_45 == 17)? _saxi_flag_17 : 
                            (axis_maskaddr_45 == 18)? _saxi_flag_18 : 
                            (axis_maskaddr_45 == 19)? _saxi_flag_19 : 
                            (axis_maskaddr_45 == 20)? _saxi_flag_20 : 
                            (axis_maskaddr_45 == 21)? _saxi_flag_21 : 
                            (axis_maskaddr_45 == 22)? _saxi_flag_22 : 
                            (axis_maskaddr_45 == 23)? _saxi_flag_23 : 
                            (axis_maskaddr_45 == 24)? _saxi_flag_24 : 
                            (axis_maskaddr_45 == 25)? _saxi_flag_25 : 
                            (axis_maskaddr_45 == 26)? _saxi_flag_26 : 
                            (axis_maskaddr_45 == 27)? _saxi_flag_27 : 
                            (axis_maskaddr_45 == 28)? _saxi_flag_28 : 
                            (axis_maskaddr_45 == 29)? _saxi_flag_29 : 
                            (axis_maskaddr_45 == 30)? _saxi_flag_30 : 
                            (axis_maskaddr_45 == 31)? _saxi_flag_31 : 
                            (axis_maskaddr_45 == 32)? _saxi_flag_32 : 
                            (axis_maskaddr_45 == 33)? _saxi_flag_33 : 
                            (axis_maskaddr_45 == 34)? _saxi_flag_34 : 
                            (axis_maskaddr_45 == 35)? _saxi_flag_35 : 
                            (axis_maskaddr_45 == 36)? _saxi_flag_36 : 'hx;
  wire signed [32-1:0] axislite_resetval_48;
  assign axislite_resetval_48 = (axis_maskaddr_45 == 0)? _saxi_resetval_0 : 
                                (axis_maskaddr_45 == 1)? _saxi_resetval_1 : 
                                (axis_maskaddr_45 == 2)? _saxi_resetval_2 : 
                                (axis_maskaddr_45 == 3)? _saxi_resetval_3 : 
                                (axis_maskaddr_45 == 4)? _saxi_resetval_4 : 
                                (axis_maskaddr_45 == 5)? _saxi_resetval_5 : 
                                (axis_maskaddr_45 == 6)? _saxi_resetval_6 : 
                                (axis_maskaddr_45 == 7)? _saxi_resetval_7 : 
                                (axis_maskaddr_45 == 8)? _saxi_resetval_8 : 
                                (axis_maskaddr_45 == 9)? _saxi_resetval_9 : 
                                (axis_maskaddr_45 == 10)? _saxi_resetval_10 : 
                                (axis_maskaddr_45 == 11)? _saxi_resetval_11 : 
                                (axis_maskaddr_45 == 12)? _saxi_resetval_12 : 
                                (axis_maskaddr_45 == 13)? _saxi_resetval_13 : 
                                (axis_maskaddr_45 == 14)? _saxi_resetval_14 : 
                                (axis_maskaddr_45 == 15)? _saxi_resetval_15 : 
                                (axis_maskaddr_45 == 16)? _saxi_resetval_16 : 
                                (axis_maskaddr_45 == 17)? _saxi_resetval_17 : 
                                (axis_maskaddr_45 == 18)? _saxi_resetval_18 : 
                                (axis_maskaddr_45 == 19)? _saxi_resetval_19 : 
                                (axis_maskaddr_45 == 20)? _saxi_resetval_20 : 
                                (axis_maskaddr_45 == 21)? _saxi_resetval_21 : 
                                (axis_maskaddr_45 == 22)? _saxi_resetval_22 : 
                                (axis_maskaddr_45 == 23)? _saxi_resetval_23 : 
                                (axis_maskaddr_45 == 24)? _saxi_resetval_24 : 
                                (axis_maskaddr_45 == 25)? _saxi_resetval_25 : 
                                (axis_maskaddr_45 == 26)? _saxi_resetval_26 : 
                                (axis_maskaddr_45 == 27)? _saxi_resetval_27 : 
                                (axis_maskaddr_45 == 28)? _saxi_resetval_28 : 
                                (axis_maskaddr_45 == 29)? _saxi_resetval_29 : 
                                (axis_maskaddr_45 == 30)? _saxi_resetval_30 : 
                                (axis_maskaddr_45 == 31)? _saxi_resetval_31 : 
                                (axis_maskaddr_45 == 32)? _saxi_resetval_32 : 
                                (axis_maskaddr_45 == 33)? _saxi_resetval_33 : 
                                (axis_maskaddr_45 == 34)? _saxi_resetval_34 : 
                                (axis_maskaddr_45 == 35)? _saxi_resetval_35 : 
                                (axis_maskaddr_45 == 36)? _saxi_resetval_36 : 'hx;
  reg _saxi_rdata_cond_0_1;
  assign saxi_wready = _saxi_register_fsm == 3;
  wire maxi_idle;
  assign maxi_idle = _maxi_write_idle & _maxi_read_idle;
  wire sw_rst_logic;
  assign sw_rst_logic = maxi_idle & _saxi_register_6;
  wire rst_logic;
  assign rst_logic = RESETN_inv_buf | sw_rst_logic;
  reg RST;
  reg _rst_logic_1;
  reg _rst_logic_2;
  wire signed [32-1:0] irq_49;
  assign irq_49 = _saxi_register_9 & _saxi_register_10;
  wire irq_busy;
  assign irq_busy = _saxi_register_5[0];
  reg irq_busy_edge_50;
  wire irq_busy_edge_51;
  assign irq_busy_edge_51 = irq_busy_edge_50 & !irq_busy;
  wire irq_extern;
  assign irq_extern = |_saxi_register_7;
  reg irq_extern_edge_52;
  wire irq_extern_edge_53;
  assign irq_extern_edge_53 = !irq_extern_edge_52 & irq_extern;
  wire [8-1:0] ram_w16_l512_id0_0_0_addr;
  wire [16-1:0] ram_w16_l512_id0_0_0_rdata;
  wire [16-1:0] ram_w16_l512_id0_0_0_wdata;
  wire ram_w16_l512_id0_0_0_wenable;
  wire ram_w16_l512_id0_0_0_enable;
  wire [8-1:0] ram_w16_l512_id0_0_1_addr;
  wire [16-1:0] ram_w16_l512_id0_0_1_rdata;
  wire [16-1:0] ram_w16_l512_id0_0_1_wdata;
  wire ram_w16_l512_id0_0_1_wenable;
  wire ram_w16_l512_id0_0_1_enable;
  assign ram_w16_l512_id0_0_0_wdata = 'hx;
  assign ram_w16_l512_id0_0_0_wenable = 0;

  ram_w16_l512_id0_0
  inst_ram_w16_l512_id0_0
  (
    .CLK(CLK),
    .ram_w16_l512_id0_0_0_addr(ram_w16_l512_id0_0_0_addr),
    .ram_w16_l512_id0_0_0_rdata(ram_w16_l512_id0_0_0_rdata),
    .ram_w16_l512_id0_0_0_wdata(ram_w16_l512_id0_0_0_wdata),
    .ram_w16_l512_id0_0_0_wenable(ram_w16_l512_id0_0_0_wenable),
    .ram_w16_l512_id0_0_0_enable(ram_w16_l512_id0_0_0_enable),
    .ram_w16_l512_id0_0_1_addr(ram_w16_l512_id0_0_1_addr),
    .ram_w16_l512_id0_0_1_rdata(ram_w16_l512_id0_0_1_rdata),
    .ram_w16_l512_id0_0_1_wdata(ram_w16_l512_id0_0_1_wdata),
    .ram_w16_l512_id0_0_1_wenable(ram_w16_l512_id0_0_1_wenable),
    .ram_w16_l512_id0_0_1_enable(ram_w16_l512_id0_0_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id0_1_0_addr;
  wire [16-1:0] ram_w16_l512_id0_1_0_rdata;
  wire [16-1:0] ram_w16_l512_id0_1_0_wdata;
  wire ram_w16_l512_id0_1_0_wenable;
  wire ram_w16_l512_id0_1_0_enable;
  wire [8-1:0] ram_w16_l512_id0_1_1_addr;
  wire [16-1:0] ram_w16_l512_id0_1_1_rdata;
  wire [16-1:0] ram_w16_l512_id0_1_1_wdata;
  wire ram_w16_l512_id0_1_1_wenable;
  wire ram_w16_l512_id0_1_1_enable;
  assign ram_w16_l512_id0_1_0_wdata = 'hx;
  assign ram_w16_l512_id0_1_0_wenable = 0;

  ram_w16_l512_id0_1
  inst_ram_w16_l512_id0_1
  (
    .CLK(CLK),
    .ram_w16_l512_id0_1_0_addr(ram_w16_l512_id0_1_0_addr),
    .ram_w16_l512_id0_1_0_rdata(ram_w16_l512_id0_1_0_rdata),
    .ram_w16_l512_id0_1_0_wdata(ram_w16_l512_id0_1_0_wdata),
    .ram_w16_l512_id0_1_0_wenable(ram_w16_l512_id0_1_0_wenable),
    .ram_w16_l512_id0_1_0_enable(ram_w16_l512_id0_1_0_enable),
    .ram_w16_l512_id0_1_1_addr(ram_w16_l512_id0_1_1_addr),
    .ram_w16_l512_id0_1_1_rdata(ram_w16_l512_id0_1_1_rdata),
    .ram_w16_l512_id0_1_1_wdata(ram_w16_l512_id0_1_1_wdata),
    .ram_w16_l512_id0_1_1_wenable(ram_w16_l512_id0_1_1_wenable),
    .ram_w16_l512_id0_1_1_enable(ram_w16_l512_id0_1_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id1_0_0_addr;
  wire [16-1:0] ram_w16_l512_id1_0_0_rdata;
  wire [16-1:0] ram_w16_l512_id1_0_0_wdata;
  wire ram_w16_l512_id1_0_0_wenable;
  wire ram_w16_l512_id1_0_0_enable;
  wire [8-1:0] ram_w16_l512_id1_0_1_addr;
  wire [16-1:0] ram_w16_l512_id1_0_1_rdata;
  wire [16-1:0] ram_w16_l512_id1_0_1_wdata;
  wire ram_w16_l512_id1_0_1_wenable;
  wire ram_w16_l512_id1_0_1_enable;
  assign ram_w16_l512_id1_0_1_wdata = 'hx;
  assign ram_w16_l512_id1_0_1_wenable = 0;

  ram_w16_l512_id1_0
  inst_ram_w16_l512_id1_0
  (
    .CLK(CLK),
    .ram_w16_l512_id1_0_0_addr(ram_w16_l512_id1_0_0_addr),
    .ram_w16_l512_id1_0_0_rdata(ram_w16_l512_id1_0_0_rdata),
    .ram_w16_l512_id1_0_0_wdata(ram_w16_l512_id1_0_0_wdata),
    .ram_w16_l512_id1_0_0_wenable(ram_w16_l512_id1_0_0_wenable),
    .ram_w16_l512_id1_0_0_enable(ram_w16_l512_id1_0_0_enable),
    .ram_w16_l512_id1_0_1_addr(ram_w16_l512_id1_0_1_addr),
    .ram_w16_l512_id1_0_1_rdata(ram_w16_l512_id1_0_1_rdata),
    .ram_w16_l512_id1_0_1_wdata(ram_w16_l512_id1_0_1_wdata),
    .ram_w16_l512_id1_0_1_wenable(ram_w16_l512_id1_0_1_wenable),
    .ram_w16_l512_id1_0_1_enable(ram_w16_l512_id1_0_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id1_1_0_addr;
  wire [16-1:0] ram_w16_l512_id1_1_0_rdata;
  wire [16-1:0] ram_w16_l512_id1_1_0_wdata;
  wire ram_w16_l512_id1_1_0_wenable;
  wire ram_w16_l512_id1_1_0_enable;
  wire [8-1:0] ram_w16_l512_id1_1_1_addr;
  wire [16-1:0] ram_w16_l512_id1_1_1_rdata;
  wire [16-1:0] ram_w16_l512_id1_1_1_wdata;
  wire ram_w16_l512_id1_1_1_wenable;
  wire ram_w16_l512_id1_1_1_enable;
  assign ram_w16_l512_id1_1_1_wdata = 'hx;
  assign ram_w16_l512_id1_1_1_wenable = 0;

  ram_w16_l512_id1_1
  inst_ram_w16_l512_id1_1
  (
    .CLK(CLK),
    .ram_w16_l512_id1_1_0_addr(ram_w16_l512_id1_1_0_addr),
    .ram_w16_l512_id1_1_0_rdata(ram_w16_l512_id1_1_0_rdata),
    .ram_w16_l512_id1_1_0_wdata(ram_w16_l512_id1_1_0_wdata),
    .ram_w16_l512_id1_1_0_wenable(ram_w16_l512_id1_1_0_wenable),
    .ram_w16_l512_id1_1_0_enable(ram_w16_l512_id1_1_0_enable),
    .ram_w16_l512_id1_1_1_addr(ram_w16_l512_id1_1_1_addr),
    .ram_w16_l512_id1_1_1_rdata(ram_w16_l512_id1_1_1_rdata),
    .ram_w16_l512_id1_1_1_wdata(ram_w16_l512_id1_1_1_wdata),
    .ram_w16_l512_id1_1_1_wenable(ram_w16_l512_id1_1_1_wenable),
    .ram_w16_l512_id1_1_1_enable(ram_w16_l512_id1_1_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id2_0_0_addr;
  wire [16-1:0] ram_w16_l512_id2_0_0_rdata;
  wire [16-1:0] ram_w16_l512_id2_0_0_wdata;
  wire ram_w16_l512_id2_0_0_wenable;
  wire ram_w16_l512_id2_0_0_enable;
  wire [8-1:0] ram_w16_l512_id2_0_1_addr;
  wire [16-1:0] ram_w16_l512_id2_0_1_rdata;
  wire [16-1:0] ram_w16_l512_id2_0_1_wdata;
  wire ram_w16_l512_id2_0_1_wenable;
  wire ram_w16_l512_id2_0_1_enable;
  assign ram_w16_l512_id2_0_0_wdata = 'hx;
  assign ram_w16_l512_id2_0_0_wenable = 0;

  ram_w16_l512_id2_0
  inst_ram_w16_l512_id2_0
  (
    .CLK(CLK),
    .ram_w16_l512_id2_0_0_addr(ram_w16_l512_id2_0_0_addr),
    .ram_w16_l512_id2_0_0_rdata(ram_w16_l512_id2_0_0_rdata),
    .ram_w16_l512_id2_0_0_wdata(ram_w16_l512_id2_0_0_wdata),
    .ram_w16_l512_id2_0_0_wenable(ram_w16_l512_id2_0_0_wenable),
    .ram_w16_l512_id2_0_0_enable(ram_w16_l512_id2_0_0_enable),
    .ram_w16_l512_id2_0_1_addr(ram_w16_l512_id2_0_1_addr),
    .ram_w16_l512_id2_0_1_rdata(ram_w16_l512_id2_0_1_rdata),
    .ram_w16_l512_id2_0_1_wdata(ram_w16_l512_id2_0_1_wdata),
    .ram_w16_l512_id2_0_1_wenable(ram_w16_l512_id2_0_1_wenable),
    .ram_w16_l512_id2_0_1_enable(ram_w16_l512_id2_0_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id2_1_0_addr;
  wire [16-1:0] ram_w16_l512_id2_1_0_rdata;
  wire [16-1:0] ram_w16_l512_id2_1_0_wdata;
  wire ram_w16_l512_id2_1_0_wenable;
  wire ram_w16_l512_id2_1_0_enable;
  wire [8-1:0] ram_w16_l512_id2_1_1_addr;
  wire [16-1:0] ram_w16_l512_id2_1_1_rdata;
  wire [16-1:0] ram_w16_l512_id2_1_1_wdata;
  wire ram_w16_l512_id2_1_1_wenable;
  wire ram_w16_l512_id2_1_1_enable;
  assign ram_w16_l512_id2_1_0_wdata = 'hx;
  assign ram_w16_l512_id2_1_0_wenable = 0;

  ram_w16_l512_id2_1
  inst_ram_w16_l512_id2_1
  (
    .CLK(CLK),
    .ram_w16_l512_id2_1_0_addr(ram_w16_l512_id2_1_0_addr),
    .ram_w16_l512_id2_1_0_rdata(ram_w16_l512_id2_1_0_rdata),
    .ram_w16_l512_id2_1_0_wdata(ram_w16_l512_id2_1_0_wdata),
    .ram_w16_l512_id2_1_0_wenable(ram_w16_l512_id2_1_0_wenable),
    .ram_w16_l512_id2_1_0_enable(ram_w16_l512_id2_1_0_enable),
    .ram_w16_l512_id2_1_1_addr(ram_w16_l512_id2_1_1_addr),
    .ram_w16_l512_id2_1_1_rdata(ram_w16_l512_id2_1_1_rdata),
    .ram_w16_l512_id2_1_1_wdata(ram_w16_l512_id2_1_1_wdata),
    .ram_w16_l512_id2_1_1_wenable(ram_w16_l512_id2_1_1_wenable),
    .ram_w16_l512_id2_1_1_enable(ram_w16_l512_id2_1_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id3_0_0_addr;
  wire [16-1:0] ram_w16_l512_id3_0_0_rdata;
  wire [16-1:0] ram_w16_l512_id3_0_0_wdata;
  wire ram_w16_l512_id3_0_0_wenable;
  wire ram_w16_l512_id3_0_0_enable;
  wire [8-1:0] ram_w16_l512_id3_0_1_addr;
  wire [16-1:0] ram_w16_l512_id3_0_1_rdata;
  wire [16-1:0] ram_w16_l512_id3_0_1_wdata;
  wire ram_w16_l512_id3_0_1_wenable;
  wire ram_w16_l512_id3_0_1_enable;
  assign ram_w16_l512_id3_0_0_wdata = 'hx;
  assign ram_w16_l512_id3_0_0_wenable = 0;

  ram_w16_l512_id3_0
  inst_ram_w16_l512_id3_0
  (
    .CLK(CLK),
    .ram_w16_l512_id3_0_0_addr(ram_w16_l512_id3_0_0_addr),
    .ram_w16_l512_id3_0_0_rdata(ram_w16_l512_id3_0_0_rdata),
    .ram_w16_l512_id3_0_0_wdata(ram_w16_l512_id3_0_0_wdata),
    .ram_w16_l512_id3_0_0_wenable(ram_w16_l512_id3_0_0_wenable),
    .ram_w16_l512_id3_0_0_enable(ram_w16_l512_id3_0_0_enable),
    .ram_w16_l512_id3_0_1_addr(ram_w16_l512_id3_0_1_addr),
    .ram_w16_l512_id3_0_1_rdata(ram_w16_l512_id3_0_1_rdata),
    .ram_w16_l512_id3_0_1_wdata(ram_w16_l512_id3_0_1_wdata),
    .ram_w16_l512_id3_0_1_wenable(ram_w16_l512_id3_0_1_wenable),
    .ram_w16_l512_id3_0_1_enable(ram_w16_l512_id3_0_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id3_1_0_addr;
  wire [16-1:0] ram_w16_l512_id3_1_0_rdata;
  wire [16-1:0] ram_w16_l512_id3_1_0_wdata;
  wire ram_w16_l512_id3_1_0_wenable;
  wire ram_w16_l512_id3_1_0_enable;
  wire [8-1:0] ram_w16_l512_id3_1_1_addr;
  wire [16-1:0] ram_w16_l512_id3_1_1_rdata;
  wire [16-1:0] ram_w16_l512_id3_1_1_wdata;
  wire ram_w16_l512_id3_1_1_wenable;
  wire ram_w16_l512_id3_1_1_enable;
  assign ram_w16_l512_id3_1_0_wdata = 'hx;
  assign ram_w16_l512_id3_1_0_wenable = 0;

  ram_w16_l512_id3_1
  inst_ram_w16_l512_id3_1
  (
    .CLK(CLK),
    .ram_w16_l512_id3_1_0_addr(ram_w16_l512_id3_1_0_addr),
    .ram_w16_l512_id3_1_0_rdata(ram_w16_l512_id3_1_0_rdata),
    .ram_w16_l512_id3_1_0_wdata(ram_w16_l512_id3_1_0_wdata),
    .ram_w16_l512_id3_1_0_wenable(ram_w16_l512_id3_1_0_wenable),
    .ram_w16_l512_id3_1_0_enable(ram_w16_l512_id3_1_0_enable),
    .ram_w16_l512_id3_1_1_addr(ram_w16_l512_id3_1_1_addr),
    .ram_w16_l512_id3_1_1_rdata(ram_w16_l512_id3_1_1_rdata),
    .ram_w16_l512_id3_1_1_wdata(ram_w16_l512_id3_1_1_wdata),
    .ram_w16_l512_id3_1_1_wenable(ram_w16_l512_id3_1_1_wenable),
    .ram_w16_l512_id3_1_1_enable(ram_w16_l512_id3_1_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id4_0_0_addr;
  wire [16-1:0] ram_w16_l512_id4_0_0_rdata;
  wire [16-1:0] ram_w16_l512_id4_0_0_wdata;
  wire ram_w16_l512_id4_0_0_wenable;
  wire ram_w16_l512_id4_0_0_enable;
  wire [8-1:0] ram_w16_l512_id4_0_1_addr;
  wire [16-1:0] ram_w16_l512_id4_0_1_rdata;
  wire [16-1:0] ram_w16_l512_id4_0_1_wdata;
  wire ram_w16_l512_id4_0_1_wenable;
  wire ram_w16_l512_id4_0_1_enable;
  assign ram_w16_l512_id4_0_0_wdata = 'hx;
  assign ram_w16_l512_id4_0_0_wenable = 0;

  ram_w16_l512_id4_0
  inst_ram_w16_l512_id4_0
  (
    .CLK(CLK),
    .ram_w16_l512_id4_0_0_addr(ram_w16_l512_id4_0_0_addr),
    .ram_w16_l512_id4_0_0_rdata(ram_w16_l512_id4_0_0_rdata),
    .ram_w16_l512_id4_0_0_wdata(ram_w16_l512_id4_0_0_wdata),
    .ram_w16_l512_id4_0_0_wenable(ram_w16_l512_id4_0_0_wenable),
    .ram_w16_l512_id4_0_0_enable(ram_w16_l512_id4_0_0_enable),
    .ram_w16_l512_id4_0_1_addr(ram_w16_l512_id4_0_1_addr),
    .ram_w16_l512_id4_0_1_rdata(ram_w16_l512_id4_0_1_rdata),
    .ram_w16_l512_id4_0_1_wdata(ram_w16_l512_id4_0_1_wdata),
    .ram_w16_l512_id4_0_1_wenable(ram_w16_l512_id4_0_1_wenable),
    .ram_w16_l512_id4_0_1_enable(ram_w16_l512_id4_0_1_enable)
  );

  wire [8-1:0] ram_w16_l512_id4_1_0_addr;
  wire [16-1:0] ram_w16_l512_id4_1_0_rdata;
  wire [16-1:0] ram_w16_l512_id4_1_0_wdata;
  wire ram_w16_l512_id4_1_0_wenable;
  wire ram_w16_l512_id4_1_0_enable;
  wire [8-1:0] ram_w16_l512_id4_1_1_addr;
  wire [16-1:0] ram_w16_l512_id4_1_1_rdata;
  wire [16-1:0] ram_w16_l512_id4_1_1_wdata;
  wire ram_w16_l512_id4_1_1_wenable;
  wire ram_w16_l512_id4_1_1_enable;
  assign ram_w16_l512_id4_1_0_wdata = 'hx;
  assign ram_w16_l512_id4_1_0_wenable = 0;

  ram_w16_l512_id4_1
  inst_ram_w16_l512_id4_1
  (
    .CLK(CLK),
    .ram_w16_l512_id4_1_0_addr(ram_w16_l512_id4_1_0_addr),
    .ram_w16_l512_id4_1_0_rdata(ram_w16_l512_id4_1_0_rdata),
    .ram_w16_l512_id4_1_0_wdata(ram_w16_l512_id4_1_0_wdata),
    .ram_w16_l512_id4_1_0_wenable(ram_w16_l512_id4_1_0_wenable),
    .ram_w16_l512_id4_1_0_enable(ram_w16_l512_id4_1_0_enable),
    .ram_w16_l512_id4_1_1_addr(ram_w16_l512_id4_1_1_addr),
    .ram_w16_l512_id4_1_1_rdata(ram_w16_l512_id4_1_1_rdata),
    .ram_w16_l512_id4_1_1_wdata(ram_w16_l512_id4_1_1_wdata),
    .ram_w16_l512_id4_1_1_wenable(ram_w16_l512_id4_1_1_wenable),
    .ram_w16_l512_id4_1_1_enable(ram_w16_l512_id4_1_1_enable)
  );

  wire [1-1:0] cparam_matmul_11_act_num_col;
  wire [1-1:0] cparam_matmul_11_act_num_row;
  wire [5-1:0] cparam_matmul_11_filter_num_och;
  wire [1-1:0] cparam_matmul_11_bias_scala;
  wire [5-1:0] cparam_matmul_11_bias_num;
  wire [1-1:0] cparam_matmul_11_scale_scala;
  wire [1-1:0] cparam_matmul_11_scale_num;
  wire [1-1:0] cparam_matmul_11_vshamt_mul_scala;
  wire [1-1:0] cparam_matmul_11_vshamt_mul_num;
  wire [1-1:0] cparam_matmul_11_vshamt_sum_scala;
  wire [1-1:0] cparam_matmul_11_vshamt_sum_num;
  wire [1-1:0] cparam_matmul_11_vshamt_out_scala;
  wire [1-1:0] cparam_matmul_11_vshamt_out_num;
  wire [1-1:0] cparam_matmul_11_cshamt_mul_value;
  wire [1-1:0] cparam_matmul_11_cshamt_sum_value;
  wire [5-1:0] cparam_matmul_11_cshamt_out_value;
  wire [1-1:0] cparam_matmul_11_act_func_index;
  wire [1-1:0] cparam_matmul_11_out_num_col;
  wire [1-1:0] cparam_matmul_11_out_num_row;
  wire [1-1:0] cparam_matmul_11_pad_col_left;
  wire [1-1:0] cparam_matmul_11_pad_row_top;
  wire [1-1:0] cparam_matmul_11_max_col_count;
  wire [1-1:0] cparam_matmul_11_max_row_count;
  wire [1-1:0] cparam_matmul_11_max_bat_count;
  wire [1-1:0] cparam_matmul_11_max_och_count;
  wire [7-1:0] cparam_matmul_11_och_count_step;
  wire [1-1:0] cparam_matmul_11_dma_flag_conds_0;
  wire signed [32-1:0] cparam_matmul_11_act_offset_values_0;
  wire [6-1:0] cparam_matmul_11_act_row_step;
  wire [6-1:0] cparam_matmul_11_act_bat_step;
  wire [5-1:0] cparam_matmul_11_act_read_size;
  wire [5-1:0] cparam_matmul_11_act_read_block;
  wire [5-1:0] cparam_matmul_11_act_read_step;
  wire [9-1:0] cparam_matmul_11_filter_base_step;
  wire [8-1:0] cparam_matmul_11_filter_read_size;
  wire [5-1:0] cparam_matmul_11_filter_read_block;
  wire [8-1:0] cparam_matmul_11_filter_read_step;
  wire [1-1:0] cparam_matmul_11_out_offset_values_0;
  wire [6-1:0] cparam_matmul_11_out_col_step;
  wire [6-1:0] cparam_matmul_11_out_row_step;
  wire [6-1:0] cparam_matmul_11_out_bat_step;
  wire [6-1:0] cparam_matmul_11_out_och_step;
  wire [5-1:0] cparam_matmul_11_out_write_size;
  wire [5-1:0] cparam_matmul_11_out_write_size_res;
  wire [5-1:0] cparam_matmul_11_out_write_block;
  wire [1-1:0] cparam_matmul_11_keep_filter;
  wire [1-1:0] cparam_matmul_11_keep_input;
  wire [1-1:0] cparam_matmul_11_data_stationary;
  wire [5-1:0] cparam_matmul_11_stream_num_ops;
  wire [5-1:0] cparam_matmul_11_stream_num_ops_res;
  wire [5-1:0] cparam_matmul_11_stream_num_ops_par;
  wire [5-1:0] cparam_matmul_11_stream_num_ops_res_par;
  wire [5-1:0] cparam_matmul_11_stream_reduce_size;
  wire [5-1:0] cparam_matmul_11_stream_aligned_reduce_size;
  wire [1-1:0] cparam_matmul_11_stream_omit_mask;
  wire [1-1:0] cparam_matmul_11_col_select_initval;
  wire [1-1:0] cparam_matmul_11_stride_col_par_col;
  wire [1-1:0] cparam_matmul_11_stride_row_par_row;
  wire [1-1:0] cparam_matmul_11_stride_col_mod_filter_num;
  wire [1-1:0] cparam_matmul_11_filter_num_col_minus_stride_col_mod;
  wire [1-1:0] cparam_matmul_11_inc_act_laddr_conds_0;
  wire [5-1:0] cparam_matmul_11_inc_act_laddr_small;
  wire [5-1:0] cparam_matmul_11_inc_act_laddr_large;
  wire [5-1:0] cparam_matmul_11_inc_out_laddr_col;
  wire [1-1:0] cparam_matmul_11_stream_act_local_small_offset;
  wire [1-1:0] cparam_matmul_11_stream_act_local_large_offset;
  wire [1-1:0] cparam_matmul_11_stream_act_local_small_flags_0;
  wire [1-1:0] cparam_matmul_11_stream_act_local_large_flags_0;
  wire [1-1:0] cparam_matmul_11_inc_sync_out;
  wire [1-1:0] cparam_matmul_11_inc_sync_out_res;
  reg [2-1:0] matmul_11_control_param_index;
  assign cparam_matmul_11_act_num_col = (matmul_11_control_param_index == 0)? 32'h1 : 
                                        (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_act_num_row = (matmul_11_control_param_index == 0)? 32'h1 : 
                                        (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_filter_num_och = (matmul_11_control_param_index == 0)? 32'h10 : 
                                           (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_bias_scala = (matmul_11_control_param_index == 0)? 32'h0 : 
                                       (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_bias_num = (matmul_11_control_param_index == 0)? 32'h10 : 
                                     (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_scale_scala = (matmul_11_control_param_index == 0)? 32'h1 : 
                                        (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_scale_num = (matmul_11_control_param_index == 0)? 32'h1 : 
                                      (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_vshamt_mul_scala = (matmul_11_control_param_index == 0)? 32'h0 : 
                                             (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_vshamt_mul_num = (matmul_11_control_param_index == 0)? 32'h0 : 
                                           (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_vshamt_sum_scala = (matmul_11_control_param_index == 0)? 32'h0 : 
                                             (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_vshamt_sum_num = (matmul_11_control_param_index == 0)? 32'h0 : 
                                           (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_vshamt_out_scala = (matmul_11_control_param_index == 0)? 32'h0 : 
                                             (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_vshamt_out_num = (matmul_11_control_param_index == 0)? 32'h0 : 
                                           (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_cshamt_mul_value = (matmul_11_control_param_index == 0)? 32'h0 : 
                                             (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_cshamt_sum_value = (matmul_11_control_param_index == 0)? 32'h0 : 
                                             (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_cshamt_out_value = (matmul_11_control_param_index == 0)? 32'h1e : 
                                             (matmul_11_control_param_index == 1)? 32'h1e : 32'h1f;
  assign cparam_matmul_11_act_func_index = (matmul_11_control_param_index == 0)? 32'h0 : 
                                           (matmul_11_control_param_index == 1)? 32'h0 : 32'h1;
  assign cparam_matmul_11_out_num_col = (matmul_11_control_param_index == 0)? 32'h1 : 
                                        (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_out_num_row = (matmul_11_control_param_index == 0)? 32'h1 : 
                                        (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_pad_col_left = (matmul_11_control_param_index == 0)? 32'h0 : 
                                         (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_pad_row_top = (matmul_11_control_param_index == 0)? 32'h0 : 
                                        (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_max_col_count = (matmul_11_control_param_index == 0)? 32'h0 : 
                                          (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_max_row_count = (matmul_11_control_param_index == 0)? 32'h0 : 
                                          (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_max_bat_count = (matmul_11_control_param_index == 0)? 32'h0 : 
                                          (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_max_och_count = (matmul_11_control_param_index == 0)? 32'h0 : 
                                          (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_och_count_step = (matmul_11_control_param_index == 0)? 32'h40 : 
                                           (matmul_11_control_param_index == 1)? 32'h10 : 32'h20;
  assign cparam_matmul_11_dma_flag_conds_0 = (matmul_11_control_param_index == 0)? 32'h1 : 
                                             (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_act_offset_values_0 = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_act_row_step = (matmul_11_control_param_index == 0)? 32'h8 : 
                                         (matmul_11_control_param_index == 1)? 32'h20 : 32'h10;
  assign cparam_matmul_11_act_bat_step = (matmul_11_control_param_index == 0)? 32'h8 : 
                                         (matmul_11_control_param_index == 1)? 32'h20 : 32'h10;
  assign cparam_matmul_11_act_read_size = (matmul_11_control_param_index == 0)? 32'h4 : 
                                          (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_act_read_block = (matmul_11_control_param_index == 0)? 32'h4 : 
                                           (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_act_read_step = (matmul_11_control_param_index == 0)? 32'h4 : 
                                          (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_filter_base_step = (matmul_11_control_param_index == 0)? 32'h80 : 
                                             (matmul_11_control_param_index == 1)? 32'h100 : 32'h20;
  assign cparam_matmul_11_filter_read_size = (matmul_11_control_param_index == 0)? 32'h40 : 
                                             (matmul_11_control_param_index == 1)? 32'h80 : 32'h10;
  assign cparam_matmul_11_filter_read_block = (matmul_11_control_param_index == 0)? 32'h4 : 
                                              (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_filter_read_step = (matmul_11_control_param_index == 0)? 32'h40 : 
                                             (matmul_11_control_param_index == 1)? 32'h80 : 32'h10;
  assign cparam_matmul_11_out_offset_values_0 = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_out_col_step = (matmul_11_control_param_index == 0)? 32'h20 : 
                                         (matmul_11_control_param_index == 1)? 32'h10 : 32'h4;
  assign cparam_matmul_11_out_row_step = (matmul_11_control_param_index == 0)? 32'h20 : 
                                         (matmul_11_control_param_index == 1)? 32'h10 : 32'h4;
  assign cparam_matmul_11_out_bat_step = (matmul_11_control_param_index == 0)? 32'h20 : 
                                         (matmul_11_control_param_index == 1)? 32'h10 : 32'h4;
  assign cparam_matmul_11_out_och_step = (matmul_11_control_param_index == 0)? 32'h20 : 
                                         (matmul_11_control_param_index == 1)? 32'h10 : 32'h4;
  assign cparam_matmul_11_out_write_size = (matmul_11_control_param_index == 0)? 32'h10 : 
                                           (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_out_write_size_res = (matmul_11_control_param_index == 0)? 32'h10 : 
                                               (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_out_write_block = (matmul_11_control_param_index == 0)? 32'h10 : 
                                            (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_keep_filter = (matmul_11_control_param_index == 0)? 32'h1 : 
                                        (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_keep_input = (matmul_11_control_param_index == 0)? 32'h1 : 
                                       (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_data_stationary = (matmul_11_control_param_index == 0)? 32'h0 : 
                                            (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_stream_num_ops = (matmul_11_control_param_index == 0)? 32'h10 : 
                                           (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_stream_num_ops_res = (matmul_11_control_param_index == 0)? 32'h10 : 
                                               (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_stream_num_ops_par = (matmul_11_control_param_index == 0)? 32'h10 : 
                                               (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_stream_num_ops_res_par = (matmul_11_control_param_index == 0)? 32'h10 : 
                                                   (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_stream_reduce_size = (matmul_11_control_param_index == 0)? 32'h4 : 
                                               (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_stream_aligned_reduce_size = (matmul_11_control_param_index == 0)? 32'h4 : 
                                                       (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_stream_omit_mask = (matmul_11_control_param_index == 0)? 32'h0 : 
                                             (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_col_select_initval = (matmul_11_control_param_index == 0)? 32'h0 : 
                                               (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_stride_col_par_col = (matmul_11_control_param_index == 0)? 32'h1 : 
                                               (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_stride_row_par_row = (matmul_11_control_param_index == 0)? 32'h1 : 
                                               (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_stride_col_mod_filter_num = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                      (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_filter_num_col_minus_stride_col_mod = (matmul_11_control_param_index == 0)? 32'h1 : 
                                                                (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_inc_act_laddr_conds_0 = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                  (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_inc_act_laddr_small = (matmul_11_control_param_index == 0)? 32'h4 : 
                                                (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_inc_act_laddr_large = (matmul_11_control_param_index == 0)? 32'h4 : 
                                                (matmul_11_control_param_index == 1)? 32'h10 : 32'h8;
  assign cparam_matmul_11_inc_out_laddr_col = (matmul_11_control_param_index == 0)? 32'h10 : 
                                              (matmul_11_control_param_index == 1)? 32'h8 : 32'h2;
  assign cparam_matmul_11_stream_act_local_small_offset = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                          (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_stream_act_local_large_offset = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                          (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_stream_act_local_small_flags_0 = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                           (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_stream_act_local_large_flags_0 = (matmul_11_control_param_index == 0)? 32'h0 : 
                                                           (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  assign cparam_matmul_11_inc_sync_out = (matmul_11_control_param_index == 0)? 32'h1 : 
                                         (matmul_11_control_param_index == 1)? 32'h1 : 32'h1;
  assign cparam_matmul_11_inc_sync_out_res = (matmul_11_control_param_index == 0)? 32'h0 : 
                                             (matmul_11_control_param_index == 1)? 32'h0 : 32'h0;
  reg _acc_0_stream_ivalid;
  wire _acc_0_stream_oready;
  wire _acc_0_stream_internal_oready;
  assign _acc_0_stream_internal_oready = 1;
  reg [32-1:0] _acc_0_fsm;
  localparam _acc_0_fsm_init = 0;
  wire _acc_0_run_flag;
  assign _acc_0_run_flag = 0;
  reg _acc_0_source_start;
  wire _acc_0_source_stop;
  reg _acc_0_source_busy;
  wire _acc_0_sink_start;
  wire _acc_0_sink_stop;
  wire _acc_0_sink_busy;
  wire _acc_0_busy;
  reg _acc_0_busy_reg;
  wire _acc_0_is_root;
  reg _acc_0_x_idle;
  reg [33-1:0] _acc_0_x_source_count;
  reg [5-1:0] _acc_0_x_source_mode;
  reg [16-1:0] _acc_0_x_source_generator_id;
  reg [32-1:0] _acc_0_x_source_offset;
  reg [33-1:0] _acc_0_x_source_size;
  reg [32-1:0] _acc_0_x_source_stride;
  reg [32-1:0] _acc_0_x_source_offset_buf;
  reg [33-1:0] _acc_0_x_source_size_buf;
  reg [32-1:0] _acc_0_x_source_stride_buf;
  reg [8-1:0] _acc_0_x_source_sel;
  reg [32-1:0] _acc_0_x_source_ram_raddr;
  reg _acc_0_x_source_ram_renable;
  wire [64-1:0] _acc_0_x_source_ram_rdata;
  reg _acc_0_x_source_fifo_deq;
  wire [64-1:0] _acc_0_x_source_fifo_rdata;
  reg [64-1:0] _acc_0_x_source_empty_data;
  reg _acc_0_rshift_idle;
  reg [33-1:0] _acc_0_rshift_source_count;
  reg [5-1:0] _acc_0_rshift_source_mode;
  reg [16-1:0] _acc_0_rshift_source_generator_id;
  reg [32-1:0] _acc_0_rshift_source_offset;
  reg [33-1:0] _acc_0_rshift_source_size;
  reg [32-1:0] _acc_0_rshift_source_stride;
  reg [32-1:0] _acc_0_rshift_source_offset_buf;
  reg [33-1:0] _acc_0_rshift_source_size_buf;
  reg [32-1:0] _acc_0_rshift_source_stride_buf;
  reg [8-1:0] _acc_0_rshift_source_sel;
  reg [32-1:0] _acc_0_rshift_source_ram_raddr;
  reg _acc_0_rshift_source_ram_renable;
  wire [32-1:0] _acc_0_rshift_source_ram_rdata;
  reg _acc_0_rshift_source_fifo_deq;
  wire [32-1:0] _acc_0_rshift_source_fifo_rdata;
  reg [32-1:0] _acc_0_rshift_source_empty_data;
  reg [32-1:0] _acc_0_size_next_parameter_data;
  reg [33-1:0] _acc_0_sum_sink_count;
  reg [5-1:0] _acc_0_sum_sink_mode;
  reg [16-1:0] _acc_0_sum_sink_generator_id;
  reg [32-1:0] _acc_0_sum_sink_offset;
  reg [33-1:0] _acc_0_sum_sink_size;
  reg [32-1:0] _acc_0_sum_sink_stride;
  reg [32-1:0] _acc_0_sum_sink_offset_buf;
  reg [33-1:0] _acc_0_sum_sink_size_buf;
  reg [32-1:0] _acc_0_sum_sink_stride_buf;
  reg [8-1:0] _acc_0_sum_sink_sel;
  reg [32-1:0] _acc_0_sum_sink_waddr;
  reg _acc_0_sum_sink_wenable;
  reg [64-1:0] _acc_0_sum_sink_wdata;
  reg _acc_0_sum_sink_fifo_enq;
  reg [64-1:0] _acc_0_sum_sink_fifo_wdata;
  reg [64-1:0] _acc_0_sum_sink_immediate;
  reg [33-1:0] _acc_0_valid_sink_count;
  reg [5-1:0] _acc_0_valid_sink_mode;
  reg [16-1:0] _acc_0_valid_sink_generator_id;
  reg [32-1:0] _acc_0_valid_sink_offset;
  reg [33-1:0] _acc_0_valid_sink_size;
  reg [32-1:0] _acc_0_valid_sink_stride;
  reg [32-1:0] _acc_0_valid_sink_offset_buf;
  reg [33-1:0] _acc_0_valid_sink_size_buf;
  reg [32-1:0] _acc_0_valid_sink_stride_buf;
  reg [8-1:0] _acc_0_valid_sink_sel;
  reg [32-1:0] _acc_0_valid_sink_waddr;
  reg _acc_0_valid_sink_wenable;
  reg [1-1:0] _acc_0_valid_sink_wdata;
  reg _acc_0_valid_sink_fifo_enq;
  reg [1-1:0] _acc_0_valid_sink_fifo_wdata;
  reg [1-1:0] _acc_0_valid_sink_immediate;
  reg _add_tree_1_stream_ivalid;
  wire _add_tree_1_stream_oready;
  wire _add_tree_1_stream_internal_oready;
  assign _add_tree_1_stream_internal_oready = 1;
  reg [32-1:0] _add_tree_1_fsm;
  localparam _add_tree_1_fsm_init = 0;
  wire _add_tree_1_run_flag;
  assign _add_tree_1_run_flag = 0;
  reg _add_tree_1_source_start;
  wire _add_tree_1_source_stop;
  reg _add_tree_1_source_busy;
  wire _add_tree_1_sink_start;
  wire _add_tree_1_sink_stop;
  wire _add_tree_1_sink_busy;
  wire _add_tree_1_busy;
  reg _add_tree_1_busy_reg;
  wire _add_tree_1_is_root;
  reg _add_tree_1_var0_idle;
  reg [33-1:0] _add_tree_1_var0_source_count;
  reg [5-1:0] _add_tree_1_var0_source_mode;
  reg [16-1:0] _add_tree_1_var0_source_generator_id;
  reg [32-1:0] _add_tree_1_var0_source_offset;
  reg [33-1:0] _add_tree_1_var0_source_size;
  reg [32-1:0] _add_tree_1_var0_source_stride;
  reg [32-1:0] _add_tree_1_var0_source_offset_buf;
  reg [33-1:0] _add_tree_1_var0_source_size_buf;
  reg [32-1:0] _add_tree_1_var0_source_stride_buf;
  reg [8-1:0] _add_tree_1_var0_source_sel;
  reg [32-1:0] _add_tree_1_var0_source_ram_raddr;
  reg _add_tree_1_var0_source_ram_renable;
  wire [64-1:0] _add_tree_1_var0_source_ram_rdata;
  reg _add_tree_1_var0_source_fifo_deq;
  wire [64-1:0] _add_tree_1_var0_source_fifo_rdata;
  reg [64-1:0] _add_tree_1_var0_source_empty_data;
  reg [33-1:0] _add_tree_1_sum_sink_count;
  reg [5-1:0] _add_tree_1_sum_sink_mode;
  reg [16-1:0] _add_tree_1_sum_sink_generator_id;
  reg [32-1:0] _add_tree_1_sum_sink_offset;
  reg [33-1:0] _add_tree_1_sum_sink_size;
  reg [32-1:0] _add_tree_1_sum_sink_stride;
  reg [32-1:0] _add_tree_1_sum_sink_offset_buf;
  reg [33-1:0] _add_tree_1_sum_sink_size_buf;
  reg [32-1:0] _add_tree_1_sum_sink_stride_buf;
  reg [8-1:0] _add_tree_1_sum_sink_sel;
  reg [32-1:0] _add_tree_1_sum_sink_waddr;
  reg _add_tree_1_sum_sink_wenable;
  reg [64-1:0] _add_tree_1_sum_sink_wdata;
  reg _add_tree_1_sum_sink_fifo_enq;
  reg [64-1:0] _add_tree_1_sum_sink_fifo_wdata;
  reg [64-1:0] _add_tree_1_sum_sink_immediate;
  reg _mul_rshift_round_clip_2_stream_ivalid;
  wire _mul_rshift_round_clip_2_stream_oready;
  wire _mul_rshift_round_clip_2_stream_internal_oready;
  assign _mul_rshift_round_clip_2_stream_internal_oready = 1;
  reg [32-1:0] _mul_rshift_round_clip_2_fsm;
  localparam _mul_rshift_round_clip_2_fsm_init = 0;
  wire _mul_rshift_round_clip_2_run_flag;
  assign _mul_rshift_round_clip_2_run_flag = 0;
  reg _mul_rshift_round_clip_2_source_start;
  wire _mul_rshift_round_clip_2_source_stop;
  reg _mul_rshift_round_clip_2_source_busy;
  wire _mul_rshift_round_clip_2_sink_start;
  wire _mul_rshift_round_clip_2_sink_stop;
  wire _mul_rshift_round_clip_2_sink_busy;
  wire _mul_rshift_round_clip_2_busy;
  reg _mul_rshift_round_clip_2_busy_reg;
  wire _mul_rshift_round_clip_2_is_root;
  reg _mul_rshift_round_clip_2_x_idle;
  reg [33-1:0] _mul_rshift_round_clip_2_x_source_count;
  reg [5-1:0] _mul_rshift_round_clip_2_x_source_mode;
  reg [16-1:0] _mul_rshift_round_clip_2_x_source_generator_id;
  reg [32-1:0] _mul_rshift_round_clip_2_x_source_offset;
  reg [33-1:0] _mul_rshift_round_clip_2_x_source_size;
  reg [32-1:0] _mul_rshift_round_clip_2_x_source_stride;
  reg [32-1:0] _mul_rshift_round_clip_2_x_source_offset_buf;
  reg [33-1:0] _mul_rshift_round_clip_2_x_source_size_buf;
  reg [32-1:0] _mul_rshift_round_clip_2_x_source_stride_buf;
  reg [8-1:0] _mul_rshift_round_clip_2_x_source_sel;
  reg [32-1:0] _mul_rshift_round_clip_2_x_source_ram_raddr;
  reg _mul_rshift_round_clip_2_x_source_ram_renable;
  wire [64-1:0] _mul_rshift_round_clip_2_x_source_ram_rdata;
  reg _mul_rshift_round_clip_2_x_source_fifo_deq;
  wire [64-1:0] _mul_rshift_round_clip_2_x_source_fifo_rdata;
  reg [64-1:0] _mul_rshift_round_clip_2_x_source_empty_data;
  reg _mul_rshift_round_clip_2_y_idle;
  reg [33-1:0] _mul_rshift_round_clip_2_y_source_count;
  reg [5-1:0] _mul_rshift_round_clip_2_y_source_mode;
  reg [16-1:0] _mul_rshift_round_clip_2_y_source_generator_id;
  reg [32-1:0] _mul_rshift_round_clip_2_y_source_offset;
  reg [33-1:0] _mul_rshift_round_clip_2_y_source_size;
  reg [32-1:0] _mul_rshift_round_clip_2_y_source_stride;
  reg [32-1:0] _mul_rshift_round_clip_2_y_source_offset_buf;
  reg [33-1:0] _mul_rshift_round_clip_2_y_source_size_buf;
  reg [32-1:0] _mul_rshift_round_clip_2_y_source_stride_buf;
  reg [8-1:0] _mul_rshift_round_clip_2_y_source_sel;
  reg [32-1:0] _mul_rshift_round_clip_2_y_source_ram_raddr;
  reg _mul_rshift_round_clip_2_y_source_ram_renable;
  wire [16-1:0] _mul_rshift_round_clip_2_y_source_ram_rdata;
  reg _mul_rshift_round_clip_2_y_source_fifo_deq;
  wire [16-1:0] _mul_rshift_round_clip_2_y_source_fifo_rdata;
  reg [16-1:0] _mul_rshift_round_clip_2_y_source_empty_data;
  reg _mul_rshift_round_clip_2_rshift_idle;
  reg [33-1:0] _mul_rshift_round_clip_2_rshift_source_count;
  reg [5-1:0] _mul_rshift_round_clip_2_rshift_source_mode;
  reg [16-1:0] _mul_rshift_round_clip_2_rshift_source_generator_id;
  reg [32-1:0] _mul_rshift_round_clip_2_rshift_source_offset;
  reg [33-1:0] _mul_rshift_round_clip_2_rshift_source_size;
  reg [32-1:0] _mul_rshift_round_clip_2_rshift_source_stride;
  reg [32-1:0] _mul_rshift_round_clip_2_rshift_source_offset_buf;
  reg [33-1:0] _mul_rshift_round_clip_2_rshift_source_size_buf;
  reg [32-1:0] _mul_rshift_round_clip_2_rshift_source_stride_buf;
  reg [8-1:0] _mul_rshift_round_clip_2_rshift_source_sel;
  reg [32-1:0] _mul_rshift_round_clip_2_rshift_source_ram_raddr;
  reg _mul_rshift_round_clip_2_rshift_source_ram_renable;
  wire [32-1:0] _mul_rshift_round_clip_2_rshift_source_ram_rdata;
  reg _mul_rshift_round_clip_2_rshift_source_fifo_deq;
  wire [32-1:0] _mul_rshift_round_clip_2_rshift_source_fifo_rdata;
  reg [32-1:0] _mul_rshift_round_clip_2_rshift_source_empty_data;
  reg [33-1:0] _mul_rshift_round_clip_2_z_sink_count;
  reg [5-1:0] _mul_rshift_round_clip_2_z_sink_mode;
  reg [16-1:0] _mul_rshift_round_clip_2_z_sink_generator_id;
  reg [32-1:0] _mul_rshift_round_clip_2_z_sink_offset;
  reg [33-1:0] _mul_rshift_round_clip_2_z_sink_size;
  reg [32-1:0] _mul_rshift_round_clip_2_z_sink_stride;
  reg [32-1:0] _mul_rshift_round_clip_2_z_sink_offset_buf;
  reg [33-1:0] _mul_rshift_round_clip_2_z_sink_size_buf;
  reg [32-1:0] _mul_rshift_round_clip_2_z_sink_stride_buf;
  reg [8-1:0] _mul_rshift_round_clip_2_z_sink_sel;
  reg [32-1:0] _mul_rshift_round_clip_2_z_sink_waddr;
  reg _mul_rshift_round_clip_2_z_sink_wenable;
  reg [16-1:0] _mul_rshift_round_clip_2_z_sink_wdata;
  reg _mul_rshift_round_clip_2_z_sink_fifo_enq;
  reg [16-1:0] _mul_rshift_round_clip_2_z_sink_fifo_wdata;
  reg [16-1:0] _mul_rshift_round_clip_2_z_sink_immediate;
  reg _mul_3_stream_ivalid;
  wire _mul_3_stream_oready;
  wire _mul_3_stream_internal_oready;
  assign _mul_3_stream_internal_oready = 1;
  reg [32-1:0] _mul_3_fsm;
  localparam _mul_3_fsm_init = 0;
  wire _mul_3_run_flag;
  assign _mul_3_run_flag = 0;
  reg _mul_3_source_start;
  wire _mul_3_source_stop;
  reg _mul_3_source_busy;
  wire _mul_3_sink_start;
  wire _mul_3_sink_stop;
  wire _mul_3_sink_busy;
  wire _mul_3_busy;
  reg _mul_3_busy_reg;
  wire _mul_3_is_root;
  reg _mul_3_x_idle;
  reg [33-1:0] _mul_3_x_source_count;
  reg [5-1:0] _mul_3_x_source_mode;
  reg [16-1:0] _mul_3_x_source_generator_id;
  reg [32-1:0] _mul_3_x_source_offset;
  reg [33-1:0] _mul_3_x_source_size;
  reg [32-1:0] _mul_3_x_source_stride;
  reg [32-1:0] _mul_3_x_source_offset_buf;
  reg [33-1:0] _mul_3_x_source_size_buf;
  reg [32-1:0] _mul_3_x_source_stride_buf;
  reg [8-1:0] _mul_3_x_source_sel;
  reg [32-1:0] _mul_3_x_source_ram_raddr;
  reg _mul_3_x_source_ram_renable;
  wire [16-1:0] _mul_3_x_source_ram_rdata;
  reg _mul_3_x_source_fifo_deq;
  wire [16-1:0] _mul_3_x_source_fifo_rdata;
  reg [16-1:0] _mul_3_x_source_empty_data;
  reg _mul_3_y_idle;
  reg [33-1:0] _mul_3_y_source_count;
  reg [5-1:0] _mul_3_y_source_mode;
  reg [16-1:0] _mul_3_y_source_generator_id;
  reg [32-1:0] _mul_3_y_source_offset;
  reg [33-1:0] _mul_3_y_source_size;
  reg [32-1:0] _mul_3_y_source_stride;
  reg [32-1:0] _mul_3_y_source_offset_buf;
  reg [33-1:0] _mul_3_y_source_size_buf;
  reg [32-1:0] _mul_3_y_source_stride_buf;
  reg [8-1:0] _mul_3_y_source_sel;
  reg [32-1:0] _mul_3_y_source_ram_raddr;
  reg _mul_3_y_source_ram_renable;
  wire [16-1:0] _mul_3_y_source_ram_rdata;
  reg _mul_3_y_source_fifo_deq;
  wire [16-1:0] _mul_3_y_source_fifo_rdata;
  reg [16-1:0] _mul_3_y_source_empty_data;
  reg _mul_3_rshift_idle;
  reg [33-1:0] _mul_3_rshift_source_count;
  reg [5-1:0] _mul_3_rshift_source_mode;
  reg [16-1:0] _mul_3_rshift_source_generator_id;
  reg [32-1:0] _mul_3_rshift_source_offset;
  reg [33-1:0] _mul_3_rshift_source_size;
  reg [32-1:0] _mul_3_rshift_source_stride;
  reg [32-1:0] _mul_3_rshift_source_offset_buf;
  reg [33-1:0] _mul_3_rshift_source_size_buf;
  reg [32-1:0] _mul_3_rshift_source_stride_buf;
  reg [8-1:0] _mul_3_rshift_source_sel;
  reg [32-1:0] _mul_3_rshift_source_ram_raddr;
  reg _mul_3_rshift_source_ram_renable;
  wire [32-1:0] _mul_3_rshift_source_ram_rdata;
  reg _mul_3_rshift_source_fifo_deq;
  wire [32-1:0] _mul_3_rshift_source_fifo_rdata;
  reg [32-1:0] _mul_3_rshift_source_empty_data;
  reg [33-1:0] _mul_3_z_sink_count;
  reg [5-1:0] _mul_3_z_sink_mode;
  reg [16-1:0] _mul_3_z_sink_generator_id;
  reg [32-1:0] _mul_3_z_sink_offset;
  reg [33-1:0] _mul_3_z_sink_size;
  reg [32-1:0] _mul_3_z_sink_stride;
  reg [32-1:0] _mul_3_z_sink_offset_buf;
  reg [33-1:0] _mul_3_z_sink_size_buf;
  reg [32-1:0] _mul_3_z_sink_stride_buf;
  reg [8-1:0] _mul_3_z_sink_sel;
  reg [32-1:0] _mul_3_z_sink_waddr;
  reg _mul_3_z_sink_wenable;
  reg [32-1:0] _mul_3_z_sink_wdata;
  reg _mul_3_z_sink_fifo_enq;
  reg [32-1:0] _mul_3_z_sink_fifo_wdata;
  reg [32-1:0] _mul_3_z_sink_immediate;
  reg _stream_matmul_11_stream_ivalid;
  wire _stream_matmul_11_stream_oready;
  wire _stream_matmul_11_stream_internal_oready;
  assign _stream_matmul_11_stream_oready = _stream_matmul_11_stream_internal_oready;
  reg [32-1:0] _stream_matmul_11_fsm;
  localparam _stream_matmul_11_fsm_init = 0;
  wire _stream_matmul_11_run_flag;
  reg _stream_matmul_11_source_start;
  wire _stream_matmul_11_source_stop;
  reg _stream_matmul_11_source_busy;
  wire _stream_matmul_11_sink_start;
  wire _stream_matmul_11_sink_stop;
  wire _stream_matmul_11_sink_busy;
  wire _stream_matmul_11_busy;
  reg _stream_matmul_11_busy_reg;
  wire _stream_matmul_11_is_root;
  assign _stream_matmul_11_is_root = 1;
  reg [5-1:0] _stream_matmul_11_parameter_0_next_parameter_data;
  reg [1-1:0] _stream_matmul_11_parameter_1_next_parameter_data;
  reg [1-1:0] _stream_matmul_11_parameter_2_next_parameter_data;
  reg [1-1:0] _stream_matmul_11_parameter_3_next_parameter_data;
  reg [1-1:0] _stream_matmul_11_parameter_4_next_parameter_data;
  reg [1-1:0] _stream_matmul_11_parameter_6_next_parameter_data;
  reg _stream_matmul_11_source_7_idle;
  reg [33-1:0] _stream_matmul_11_source_7_source_count;
  reg [5-1:0] _stream_matmul_11_source_7_source_mode;
  reg [16-1:0] _stream_matmul_11_source_7_source_generator_id;
  reg [32-1:0] _stream_matmul_11_source_7_source_offset;
  reg [33-1:0] _stream_matmul_11_source_7_source_size;
  reg [32-1:0] _stream_matmul_11_source_7_source_stride;
  reg [32-1:0] _stream_matmul_11_source_7_source_offset_buf;
  reg [33-1:0] _stream_matmul_11_source_7_source_size_buf;
  reg [32-1:0] _stream_matmul_11_source_7_source_stride_buf;
  reg [8-1:0] _stream_matmul_11_source_7_source_sel;
  reg [32-1:0] _stream_matmul_11_source_7_source_ram_raddr;
  reg _stream_matmul_11_source_7_source_ram_renable;
  wire [16-1:0] _stream_matmul_11_source_7_source_ram_rdata;
  reg _stream_matmul_11_source_7_source_fifo_deq;
  wire [16-1:0] _stream_matmul_11_source_7_source_fifo_rdata;
  reg [16-1:0] _stream_matmul_11_source_7_source_empty_data;
  reg [1-1:0] _stream_matmul_11_parameter_8_next_parameter_data;
  reg _stream_matmul_11_source_9_idle;
  reg [33-1:0] _stream_matmul_11_source_9_source_count;
  reg [5-1:0] _stream_matmul_11_source_9_source_mode;
  reg [16-1:0] _stream_matmul_11_source_9_source_generator_id;
  reg [32-1:0] _stream_matmul_11_source_9_source_offset;
  reg [33-1:0] _stream_matmul_11_source_9_source_size;
  reg [32-1:0] _stream_matmul_11_source_9_source_stride;
  reg [32-1:0] _stream_matmul_11_source_9_source_offset_buf;
  reg [33-1:0] _stream_matmul_11_source_9_source_size_buf;
  reg [32-1:0] _stream_matmul_11_source_9_source_stride_buf;
  reg [8-1:0] _stream_matmul_11_source_9_source_sel;
  reg [32-1:0] _stream_matmul_11_source_9_source_ram_raddr;
  reg _stream_matmul_11_source_9_source_ram_renable;
  wire [16-1:0] _stream_matmul_11_source_9_source_ram_rdata;
  reg _stream_matmul_11_source_9_source_fifo_deq;
  wire [16-1:0] _stream_matmul_11_source_9_source_fifo_rdata;
  reg [16-1:0] _stream_matmul_11_source_9_source_empty_data;
  reg [1-1:0] _stream_matmul_11_parameter_10_next_parameter_data;
  reg _stream_matmul_11_source_11_idle;
  reg [33-1:0] _stream_matmul_11_source_11_source_count;
  reg [5-1:0] _stream_matmul_11_source_11_source_mode;
  reg [16-1:0] _stream_matmul_11_source_11_source_generator_id;
  reg [32-1:0] _stream_matmul_11_source_11_source_offset;
  reg [33-1:0] _stream_matmul_11_source_11_source_size;
  reg [32-1:0] _stream_matmul_11_source_11_source_stride;
  reg [32-1:0] _stream_matmul_11_source_11_source_offset_buf;
  reg [33-1:0] _stream_matmul_11_source_11_source_size_buf;
  reg [32-1:0] _stream_matmul_11_source_11_source_stride_buf;
  reg [8-1:0] _stream_matmul_11_source_11_source_sel;
  reg [32-1:0] _stream_matmul_11_source_11_source_ram_raddr;
  reg _stream_matmul_11_source_11_source_ram_renable;
  wire [16-1:0] _stream_matmul_11_source_11_source_ram_rdata;
  reg _stream_matmul_11_source_11_source_fifo_deq;
  wire [16-1:0] _stream_matmul_11_source_11_source_fifo_rdata;
  reg [16-1:0] _stream_matmul_11_source_11_source_empty_data;
  reg [1-1:0] _stream_matmul_11_parameter_12_next_parameter_data;
  reg _stream_matmul_11_source_13_idle;
  reg [33-1:0] _stream_matmul_11_source_13_source_count;
  reg [5-1:0] _stream_matmul_11_source_13_source_mode;
  reg [16-1:0] _stream_matmul_11_source_13_source_generator_id;
  reg [32-1:0] _stream_matmul_11_source_13_source_offset;
  reg [33-1:0] _stream_matmul_11_source_13_source_size;
  reg [32-1:0] _stream_matmul_11_source_13_source_stride;
  reg [32-1:0] _stream_matmul_11_source_13_source_offset_buf;
  reg [33-1:0] _stream_matmul_11_source_13_source_size_buf;
  reg [32-1:0] _stream_matmul_11_source_13_source_stride_buf;
  reg [8-1:0] _stream_matmul_11_source_13_source_sel;
  reg [32-1:0] _stream_matmul_11_source_13_source_ram_raddr;
  reg _stream_matmul_11_source_13_source_ram_renable;
  wire [16-1:0] _stream_matmul_11_source_13_source_ram_rdata;
  reg _stream_matmul_11_source_13_source_fifo_deq;
  wire [16-1:0] _stream_matmul_11_source_13_source_fifo_rdata;
  reg [16-1:0] _stream_matmul_11_source_13_source_empty_data;
  reg [1-1:0] _stream_matmul_11_parameter_14_next_parameter_data;
  reg _stream_matmul_11_source_15_idle;
  reg [33-1:0] _stream_matmul_11_source_15_source_count;
  reg [5-1:0] _stream_matmul_11_source_15_source_mode;
  reg [16-1:0] _stream_matmul_11_source_15_source_generator_id;
  reg [32-1:0] _stream_matmul_11_source_15_source_offset;
  reg [33-1:0] _stream_matmul_11_source_15_source_size;
  reg [32-1:0] _stream_matmul_11_source_15_source_stride;
  reg [32-1:0] _stream_matmul_11_source_15_source_offset_buf;
  reg [33-1:0] _stream_matmul_11_source_15_source_size_buf;
  reg [32-1:0] _stream_matmul_11_source_15_source_stride_buf;
  reg [8-1:0] _stream_matmul_11_source_15_source_sel;
  reg [32-1:0] _stream_matmul_11_source_15_source_ram_raddr;
  reg _stream_matmul_11_source_15_source_ram_renable;
  wire [16-1:0] _stream_matmul_11_source_15_source_ram_rdata;
  reg _stream_matmul_11_source_15_source_fifo_deq;
  wire [16-1:0] _stream_matmul_11_source_15_source_fifo_rdata;
  reg [16-1:0] _stream_matmul_11_source_15_source_empty_data;
  reg [1-1:0] _stream_matmul_11_parameter_16_next_parameter_data;
  reg [1-1:0] _stream_matmul_11_parameter_17_next_parameter_data;
  reg [5-1:0] _stream_matmul_11_parameter_18_next_parameter_data;
  reg [2-1:0] _stream_matmul_11_parameter_19_next_parameter_data;
  reg _stream_matmul_11_source_20_idle;
  reg [33-1:0] _stream_matmul_11_source_20_source_count;
  reg [5-1:0] _stream_matmul_11_source_20_source_mode;
  reg [16-1:0] _stream_matmul_11_source_20_source_generator_id;
  reg [32-1:0] _stream_matmul_11_source_20_source_offset;
  reg [33-1:0] _stream_matmul_11_source_20_source_size;
  reg [32-1:0] _stream_matmul_11_source_20_source_stride;
  reg [32-1:0] _stream_matmul_11_source_20_source_offset_buf;
  reg [33-1:0] _stream_matmul_11_source_20_source_size_buf;
  reg [32-1:0] _stream_matmul_11_source_20_source_stride_buf;
  reg [8-1:0] _stream_matmul_11_source_20_source_sel;
  reg [32-1:0] _stream_matmul_11_source_20_source_ram_raddr;
  reg _stream_matmul_11_source_20_source_ram_renable;
  wire [16-1:0] _stream_matmul_11_source_20_source_ram_rdata;
  reg _stream_matmul_11_source_20_source_fifo_deq;
  wire [16-1:0] _stream_matmul_11_source_20_source_fifo_rdata;
  reg [16-1:0] _stream_matmul_11_source_20_source_empty_data;
  reg _stream_matmul_11_source_21_idle;
  reg [33-1:0] _stream_matmul_11_source_21_source_count;
  reg [5-1:0] _stream_matmul_11_source_21_source_mode;
  reg [16-1:0] _stream_matmul_11_source_21_source_generator_id;
  reg [32-1:0] _stream_matmul_11_source_21_source_offset;
  reg [33-1:0] _stream_matmul_11_source_21_source_size;
  reg [32-1:0] _stream_matmul_11_source_21_source_stride;
  reg [32-1:0] _stream_matmul_11_source_21_source_offset_buf;
  reg [33-1:0] _stream_matmul_11_source_21_source_size_buf;
  reg [32-1:0] _stream_matmul_11_source_21_source_stride_buf;
  reg [8-1:0] _stream_matmul_11_source_21_source_sel;
  reg [32-1:0] _stream_matmul_11_source_21_source_ram_raddr;
  reg _stream_matmul_11_source_21_source_ram_renable;
  wire [16-1:0] _stream_matmul_11_source_21_source_ram_rdata;
  reg _stream_matmul_11_source_21_source_fifo_deq;
  wire [16-1:0] _stream_matmul_11_source_21_source_fifo_rdata;
  reg [16-1:0] _stream_matmul_11_source_21_source_empty_data;
  wire signed [16-1:0] mul_3_x_data;
  wire signed [16-1:0] mul_3_y_data;
  wire [5-1:0] mul_3_rshift_data;
  reg __mul_3_stream_ivalid_1;
  reg __mul_3_stream_ivalid_2;
  reg __mul_3_stream_ivalid_3;
  reg __mul_3_stream_ivalid_4;
  reg __mul_3_stream_ivalid_5;
  reg __mul_3_stream_ivalid_6;
  reg __mul_3_stream_ivalid_7;
  reg __mul_3_stream_ivalid_8;
  reg [1-1:0] _greaterthan_data_61;
  reg [5-1:0] _minus_data_63;
  reg [1-1:0] _greatereq_data_74;
  reg signed [16-1:0] __delay_data_161__variable_58;
  reg signed [16-1:0] __delay_data_164__variable_59;
  reg [5-1:0] __delay_data_167__variable_60;
  reg signed [34-1:0] _sll_data_65;
  reg [1-1:0] __delay_data_158_greaterthan_61;
  reg [1-1:0] __delay_data_159_greatereq_74;
  reg signed [16-1:0] __delay_data_162__delay_161__variable_58;
  reg signed [16-1:0] __delay_data_165__delay_164__variable_59;
  reg [5-1:0] __delay_data_168__delay_167__variable_60;
  reg signed [32-1:0] _cond_data_71;
  reg [1-1:0] __delay_data_160__delay_159_greatereq_74;
  reg signed [16-1:0] __delay_data_163__delay_162__delay_161__variable_58;
  reg signed [16-1:0] __delay_data_166__delay_165__delay_164__variable_59;
  reg [5-1:0] __delay_data_169__delay_168__delay_167__variable_60;
  wire signed [16-1:0] _uminus_data_73;
  assign _uminus_data_73 = -_cond_data_71;
  wire signed [16-1:0] _cond_data_76;
  assign _cond_data_76 = (__delay_data_160__delay_159_greatereq_74)? _cond_data_71 : _uminus_data_73;
  wire signed [32-1:0] __muladd_madd_odata_77;
  reg signed [32-1:0] __muladd_madd_odata_reg_77;
  wire signed [32-1:0] __muladd_data_77;
  assign __muladd_data_77 = __muladd_madd_odata_reg_77;
  wire __muladd_madd_update_77;
  assign __muladd_madd_update_77 = _mul_3_stream_oready;

  madd_0
  __muladd_madd_77
  (
    .CLK(CLK),
    .update(__muladd_madd_update_77),
    .a(__delay_data_163__delay_162__delay_161__variable_58),
    .b(__delay_data_166__delay_165__delay_164__variable_59),
    .c(_cond_data_76),
    .d(__muladd_madd_odata_77)
  );

  reg [5-1:0] __delay_data_170__delay_169__delay_168__delay_167__variable_60;
  reg [5-1:0] __delay_data_171__delay_170__delay_169__delay_168____variable_60;
  reg [5-1:0] __delay_data_172__delay_171__delay_170__delay_169____variable_60;
  reg [5-1:0] __delay_data_173__delay_172__delay_171__delay_170____variable_60;
  reg signed [32-1:0] _sra_data_78;
  wire signed [32-1:0] mul_3_z_data;
  assign mul_3_z_data = _sra_data_78;
  wire signed [64-1:0] add_tree_1_var0_data;
  wire signed [64-1:0] _cast_src_23;
  assign _cast_src_23 = add_tree_1_var0_data;
  wire signed [64-1:0] _cast_data_23;
  assign _cast_data_23 = _cast_src_23;
  wire signed [64-1:0] add_tree_1_sum_data;
  assign add_tree_1_sum_data = _cast_data_23;
  wire signed [64-1:0] acc_0_x_data;
  wire [7-1:0] acc_0_rshift_data;
  wire [32-1:0] acc_0_size_data;
  wire [1-1:0] acc_0__reduce_reset_data;
  reg __acc_0_stream_ivalid_1;
  reg __acc_0_stream_ivalid_2;
  reg __acc_0_stream_ivalid_3;
  reg __acc_0_stream_ivalid_4;
  reg __acc_0_stream_ivalid_5;
  reg [1-1:0] _greaterthan_data_3;
  reg [7-1:0] _minus_data_5;
  reg signed [64-1:0] _reduceadd_data_16;
  reg [33-1:0] _reduceadd_count_16;
  reg _reduceadd_prev_count_max_16;
  wire _reduceadd_reset_cond_16;
  assign _reduceadd_reset_cond_16 = acc_0__reduce_reset_data || _reduceadd_prev_count_max_16;
  wire [33-1:0] _reduceadd_current_count_16;
  assign _reduceadd_current_count_16 = (_reduceadd_reset_cond_16)? 0 : _reduceadd_count_16;
  wire signed [64-1:0] _reduceadd_current_data_16;
  assign _reduceadd_current_data_16 = (_reduceadd_reset_cond_16)? 1'sd0 : _reduceadd_data_16;
  reg [1-1:0] _pulse_data_18;
  reg [33-1:0] _pulse_count_18;
  reg _pulse_prev_count_max_18;
  wire _pulse_reset_cond_18;
  assign _pulse_reset_cond_18 = acc_0__reduce_reset_data || _pulse_prev_count_max_18;
  wire [33-1:0] _pulse_current_count_18;
  assign _pulse_current_count_18 = (_pulse_reset_cond_18)? 0 : _pulse_count_18;
  wire [1-1:0] _pulse_current_data_18;
  assign _pulse_current_data_18 = (_pulse_reset_cond_18)? 1'sd0 : _pulse_data_18;
  reg [7-1:0] __delay_data_182__variable_1;
  reg signed [130-1:0] _sll_data_7;
  reg [1-1:0] __delay_data_179_greaterthan_3;
  reg signed [64-1:0] __delay_data_180_reduceadd_16;
  reg [7-1:0] __delay_data_183__delay_182__variable_1;
  reg [1-1:0] __delay_data_186_pulse_18;
  reg signed [64-1:0] _cond_data_13;
  reg signed [64-1:0] __delay_data_181__delay_180_reduceadd_16;
  reg [7-1:0] __delay_data_184__delay_183__delay_182__variable_1;
  reg [1-1:0] __delay_data_187__delay_186_pulse_18;
  reg signed [64-1:0] _plus_data_20;
  reg [7-1:0] __delay_data_185__delay_184__delay_183__delay_182__variable_1;
  reg [1-1:0] __delay_data_188__delay_187__delay_186_pulse_18;
  reg signed [64-1:0] _sra_data_21;
  reg [1-1:0] __delay_data_189__delay_188__delay_187__delay_186_pulse_18;
  wire signed [64-1:0] acc_0_sum_data;
  assign acc_0_sum_data = _sra_data_21;
  wire [1-1:0] acc_0_valid_data;
  assign acc_0_valid_data = __delay_data_189__delay_188__delay_187__delay_186_pulse_18;
  wire signed [64-1:0] mul_rshift_round_clip_2_x_data;
  wire signed [16-1:0] mul_rshift_round_clip_2_y_data;
  wire [7-1:0] mul_rshift_round_clip_2_rshift_data;
  reg __mul_rshift_round_clip_2_stream_ivalid_1;
  reg __mul_rshift_round_clip_2_stream_ivalid_2;
  reg __mul_rshift_round_clip_2_stream_ivalid_3;
  reg __mul_rshift_round_clip_2_stream_ivalid_4;
  reg __mul_rshift_round_clip_2_stream_ivalid_5;
  reg __mul_rshift_round_clip_2_stream_ivalid_6;
  reg __mul_rshift_round_clip_2_stream_ivalid_7;
  reg __mul_rshift_round_clip_2_stream_ivalid_8;
  wire signed [80-1:0] _times_mul_odata_27;
  reg signed [80-1:0] _times_mul_odata_reg_27;
  wire signed [80-1:0] _times_data_27;
  assign _times_data_27 = _times_mul_odata_reg_27;
  wire _times_mul_update_27;
  assign _times_mul_update_27 = _mul_rshift_round_clip_2_stream_oready;

  multiplier_0
  _times_mul_27
  (
    .CLK(CLK),
    .update(_times_mul_update_27),
    .a(mul_rshift_round_clip_2_x_data),
    .b(mul_rshift_round_clip_2_y_data),
    .c(_times_mul_odata_27)
  );

  wire [7-1:0] _minus_data_30;
  assign _minus_data_30 = mul_rshift_round_clip_2_rshift_data - 2'sd1;
  wire signed [130-1:0] _sll_data_33;
  assign _sll_data_33 = 2'sd1 << _minus_data_30;
  wire [1-1:0] _eq_data_45;
  assign _eq_data_45 = mul_rshift_round_clip_2_rshift_data == 1'sd0;
  reg signed [130-1:0] __delay_data_195_sll_33;
  reg [7-1:0] __delay_data_199__variable_26;
  reg [1-1:0] __delay_data_203_eq_45;
  reg signed [130-1:0] __delay_data_196__delay_195_sll_33;
  reg [7-1:0] __delay_data_200__delay_199__variable_26;
  reg [1-1:0] __delay_data_204__delay_203_eq_45;
  reg signed [130-1:0] __delay_data_197__delay_196__delay_195_sll_33;
  reg [7-1:0] __delay_data_201__delay_200__delay_199__variable_26;
  reg [1-1:0] __delay_data_205__delay_204__delay_203_eq_45;
  reg signed [130-1:0] __delay_data_198__delay_197__delay_196__delay_195_sll_33;
  reg [7-1:0] __delay_data_202__delay_201__delay_200__delay_199__variable_26;
  reg [1-1:0] __delay_data_206__delay_205__delay_204__delay_203_eq_45;
  wire [1-1:0] _pointer_data_28;
  assign _pointer_data_28 = _times_data_27[8'sd79];
  wire signed [2-1:0] _cond_data_40;
  assign _cond_data_40 = (_pointer_data_28)? -2'sd1 : 1'sd0;
  wire signed [81-1:0] _plus_data_41;
  assign _plus_data_41 = _times_data_27 + __delay_data_198__delay_197__delay_196__delay_195_sll_33;
  wire signed [81-1:0] _plus_data_42;
  assign _plus_data_42 = _plus_data_41 + _cond_data_40;
  wire signed [80-1:0] _sra_data_43;
  assign _sra_data_43 = _plus_data_42 >>> __delay_data_202__delay_201__delay_200__delay_199__variable_26;
  reg signed [80-1:0] _cond_data_46;
  reg [1-1:0] _greaterthan_data_47;
  reg [1-1:0] _lessthan_data_51;
  reg [1-1:0] _greatereq_data_55;
  reg signed [80-1:0] __delay_data_207_cond_46;
  reg signed [80-1:0] _cond_data_49;
  reg signed [80-1:0] _cond_data_53;
  reg [1-1:0] __delay_data_208_greatereq_55;
  reg signed [16-1:0] _cond_data_57;
  wire signed [16-1:0] mul_rshift_round_clip_2_z_data;
  assign mul_rshift_round_clip_2_z_data = _cond_data_57;
  reg [33-1:0] _stream_matmul_11_sink_26_sink_count;
  reg [5-1:0] _stream_matmul_11_sink_26_sink_mode;
  reg [16-1:0] _stream_matmul_11_sink_26_sink_generator_id;
  reg [32-1:0] _stream_matmul_11_sink_26_sink_offset;
  reg [33-1:0] _stream_matmul_11_sink_26_sink_size;
  reg [32-1:0] _stream_matmul_11_sink_26_sink_stride;
  reg [32-1:0] _stream_matmul_11_sink_26_sink_offset_buf;
  reg [33-1:0] _stream_matmul_11_sink_26_sink_size_buf;
  reg [32-1:0] _stream_matmul_11_sink_26_sink_stride_buf;
  reg [8-1:0] _stream_matmul_11_sink_26_sink_sel;
  reg [32-1:0] _stream_matmul_11_sink_26_sink_waddr;
  reg _stream_matmul_11_sink_26_sink_wenable;
  reg [16-1:0] _stream_matmul_11_sink_26_sink_wdata;
  reg _stream_matmul_11_sink_26_sink_fifo_enq;
  reg [16-1:0] _stream_matmul_11_sink_26_sink_fifo_wdata;
  reg [16-1:0] _stream_matmul_11_sink_26_sink_immediate;
  reg [33-1:0] _stream_matmul_11_sink_27_sink_count;
  reg [5-1:0] _stream_matmul_11_sink_27_sink_mode;
  reg [16-1:0] _stream_matmul_11_sink_27_sink_generator_id;
  reg [32-1:0] _stream_matmul_11_sink_27_sink_offset;
  reg [33-1:0] _stream_matmul_11_sink_27_sink_size;
  reg [32-1:0] _stream_matmul_11_sink_27_sink_stride;
  reg [32-1:0] _stream_matmul_11_sink_27_sink_offset_buf;
  reg [33-1:0] _stream_matmul_11_sink_27_sink_size_buf;
  reg [32-1:0] _stream_matmul_11_sink_27_sink_stride_buf;
  reg [8-1:0] _stream_matmul_11_sink_27_sink_sel;
  reg [32-1:0] _stream_matmul_11_sink_27_sink_waddr;
  reg _stream_matmul_11_sink_27_sink_wenable;
  reg [1-1:0] _stream_matmul_11_sink_27_sink_wdata;
  reg _stream_matmul_11_sink_27_sink_fifo_enq;
  reg [1-1:0] _stream_matmul_11_sink_27_sink_fifo_wdata;
  reg [1-1:0] _stream_matmul_11_sink_27_sink_immediate;
  reg [32-1:0] main_fsm;
  localparam main_fsm_init = 0;
  reg [32-1:0] internal_state_counter;
  reg [32-1:0] matmul_11_objaddr;
  reg [32-1:0] matmul_11_arg_objaddr_0;
  reg [32-1:0] matmul_11_arg_objaddr_1;
  reg [32-1:0] matmul_11_arg_objaddr_2;
  reg [32-1:0] matmul_11_arg_objaddr_3;
  reg [32-1:0] control_matmul_11;
  localparam control_matmul_11_init = 0;
  reg _control_matmul_11_called;
  wire signed [32-1:0] matmul_11_act_base_offset;
  reg signed [32-1:0] matmul_11_act_base_offset_row;
  reg signed [32-1:0] matmul_11_act_base_offset_bat;
  assign matmul_11_act_base_offset = matmul_11_act_base_offset_row + matmul_11_act_base_offset_bat;
  reg signed [32-1:0] matmul_11_filter_base_offset;
  reg [32-1:0] matmul_11_next_stream_num_ops;
  wire signed [32-1:0] matmul_11_out_base_offset;
  reg signed [32-1:0] matmul_11_out_base_offset_val;
  reg signed [32-1:0] matmul_11_out_base_offset_col;
  reg signed [32-1:0] matmul_11_out_base_offset_row;
  reg signed [32-1:0] matmul_11_out_base_offset_bat;
  reg signed [32-1:0] matmul_11_out_base_offset_och;
  assign matmul_11_out_base_offset = matmul_11_out_base_offset_val + matmul_11_out_base_offset_col + matmul_11_out_base_offset_row + matmul_11_out_base_offset_bat + matmul_11_out_base_offset_och;
  reg matmul_11_dma_flag_0;
  reg [32-1:0] matmul_11_sync_comp_count;
  reg [32-1:0] matmul_11_sync_out_count;
  reg [32-1:0] matmul_11_write_count;
  reg [32-1:0] matmul_11_next_out_write_size;
  reg [32-1:0] matmul_11_col_count;
  reg [32-1:0] matmul_11_row_count;
  reg [32-1:0] matmul_11_bat_count;
  reg [32-1:0] matmul_11_och_count;
  reg [1-1:0] matmul_11_col_select;
  reg [1-1:0] matmul_11_row_select;
  reg [32-1:0] matmul_11_out_col_count;
  reg [32-1:0] matmul_11_out_row_count;
  reg [32-1:0] matmul_11_out_ram_select;
  reg [32-1:0] matmul_11_prev_col_count;
  reg [32-1:0] matmul_11_prev_row_count;
  reg [32-1:0] matmul_11_prev_bat_count;
  reg [32-1:0] matmul_11_prev_och_count;
  reg [1-1:0] matmul_11_prev_row_select;
  reg [32-1:0] matmul_11_stream_act_local_0;
  reg [32-1:0] matmul_11_stream_out_local_val;
  reg [32-1:0] matmul_11_stream_out_local_col;
  wire [32-1:0] matmul_11_stream_out_local;
  assign matmul_11_stream_out_local = matmul_11_stream_out_local_val + matmul_11_stream_out_local_col;
  reg [32-1:0] matmul_11_act_page_comp_offset_0;
  reg [32-1:0] matmul_11_act_page_dma_offset_0;
  reg [32-1:0] matmul_11_filter_page_comp_offset;
  reg [32-1:0] matmul_11_filter_page_dma_offset;
  reg matmul_11_out_page;
  reg [32-1:0] matmul_11_out_page_comp_offset;
  reg [32-1:0] matmul_11_out_page_dma_offset;
  reg [32-1:0] matmul_11_out_laddr_offset;
  reg matmul_11_skip_read_filter;
  reg matmul_11_skip_read_act;
  reg matmul_11_skip_comp;
  reg matmul_11_skip_write_out;
  wire [5-1:0] _dma_read_packed_high_local_size_54;
  assign _dma_read_packed_high_local_size_54 = cparam_matmul_11_bias_num >> 1;
  wire [1-1:0] _dma_read_packed_low_local_size_55;
  assign _dma_read_packed_low_local_size_55 = cparam_matmul_11_bias_num & { 1{ 1'd1 } };
  wire [5-1:0] _dma_read_packed_local_packed_size_56;
  assign _dma_read_packed_local_packed_size_56 = (_dma_read_packed_low_local_size_55 > 0)? _dma_read_packed_high_local_size_54 + 1 : _dma_read_packed_high_local_size_54;
  wire [32-1:0] mask_addr_shifted_57;
  assign mask_addr_shifted_57 = matmul_11_arg_objaddr_2 + _maxi_global_base_addr >> 2;
  wire [32-1:0] mask_addr_masked_58;
  assign mask_addr_masked_58 = mask_addr_shifted_57 << 2;
  reg [32-1:0] _maxi_read_req_fsm;
  localparam _maxi_read_req_fsm_init = 0;
  reg [33-1:0] _maxi_read_cur_global_size;
  reg _maxi_read_cont;
  wire [8-1:0] pack_read_req_op_sel_59;
  wire [32-1:0] pack_read_req_local_addr_60;
  wire [32-1:0] pack_read_req_local_stride_61;
  wire [33-1:0] pack_read_req_local_size_62;
  wire [32-1:0] pack_read_req_local_blocksize_63;
  assign pack_read_req_op_sel_59 = _maxi_read_op_sel;
  assign pack_read_req_local_addr_60 = _maxi_read_local_addr;
  assign pack_read_req_local_stride_61 = _maxi_read_local_stride;
  assign pack_read_req_local_size_62 = _maxi_read_local_size;
  assign pack_read_req_local_blocksize_63 = _maxi_read_local_blocksize;
  wire [137-1:0] pack_read_req_packed_64;
  assign pack_read_req_packed_64 = { pack_read_req_op_sel_59, pack_read_req_local_addr_60, pack_read_req_local_stride_61, pack_read_req_local_size_62, pack_read_req_local_blocksize_63 };
  assign _maxi_read_req_fifo_wdata = ((_maxi_read_req_fsm == 0) && _maxi_read_start && !_maxi_read_req_fifo_almost_full)? pack_read_req_packed_64 : 'hx;
  assign _maxi_read_req_fifo_enq = ((_maxi_read_req_fsm == 0) && _maxi_read_start && !_maxi_read_req_fifo_almost_full)? (_maxi_read_req_fsm == 0) && _maxi_read_start && !_maxi_read_req_fifo_almost_full && !_maxi_read_req_fifo_almost_full : 0;
  localparam _tmp_65 = 1;
  wire [_tmp_65-1:0] _tmp_66;
  assign _tmp_66 = !_maxi_read_req_fifo_almost_full;
  reg [_tmp_65-1:0] __tmp_66_1;
  wire [32-1:0] mask_addr_shifted_67;
  assign mask_addr_shifted_67 = _maxi_read_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_68;
  assign mask_addr_masked_68 = mask_addr_shifted_67 << 2;
  wire [32-1:0] mask_addr_shifted_69;
  assign mask_addr_shifted_69 = _maxi_read_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_70;
  assign mask_addr_masked_70 = mask_addr_shifted_69 << 2;
  wire [32-1:0] mask_addr_shifted_71;
  assign mask_addr_shifted_71 = _maxi_read_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_72;
  assign mask_addr_masked_72 = mask_addr_shifted_71 << 2;
  wire [32-1:0] mask_addr_shifted_73;
  assign mask_addr_shifted_73 = _maxi_read_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_74;
  assign mask_addr_masked_74 = mask_addr_shifted_73 << 2;
  wire [32-1:0] mask_addr_shifted_75;
  assign mask_addr_shifted_75 = _maxi_read_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_76;
  assign mask_addr_masked_76 = mask_addr_shifted_75 << 2;
  wire [32-1:0] mask_addr_shifted_77;
  assign mask_addr_shifted_77 = _maxi_read_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_78;
  assign mask_addr_masked_78 = mask_addr_shifted_77 << 2;
  reg _maxi_raddr_cond_0_1;
  reg [32-1:0] _maxi_read_data_fsm;
  localparam _maxi_read_data_fsm_init = 0;
  reg [32-1:0] write_burst_packed_fsm_0;
  localparam write_burst_packed_fsm_0_init = 0;
  reg [9-1:0] write_burst_packed_addr_79;
  reg [9-1:0] write_burst_packed_stride_80;
  reg [33-1:0] write_burst_packed_length_81;
  reg write_burst_packed_done_82;
  wire [8-1:0] write_burst_packed_ram_addr_83;
  assign write_burst_packed_ram_addr_83 = write_burst_packed_addr_79 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_84;
  assign write_burst_packed_ram_wdata_84 = _maxi_rdata_sb_0 >> 0;
  assign ram_w16_l512_id3_0_1_addr = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_83 : 'hx;
  assign ram_w16_l512_id3_0_1_wdata = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_84 : 'hx;
  assign ram_w16_l512_id3_0_1_wenable = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id3_0_1_enable = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  wire [8-1:0] write_burst_packed_ram_addr_85;
  assign write_burst_packed_ram_addr_85 = write_burst_packed_addr_79 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_86;
  assign write_burst_packed_ram_wdata_86 = _maxi_rdata_sb_0 >> 16;
  assign ram_w16_l512_id3_1_1_addr = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_85 : 'hx;
  assign ram_w16_l512_id3_1_1_wdata = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_86 : 'hx;
  assign ram_w16_l512_id3_1_1_wenable = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id3_1_1_enable = ((write_burst_packed_fsm_0 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  wire [1-1:0] _dma_read_packed_high_local_size_87;
  assign _dma_read_packed_high_local_size_87 = cparam_matmul_11_scale_num >> 1;
  wire [1-1:0] _dma_read_packed_low_local_size_88;
  assign _dma_read_packed_low_local_size_88 = cparam_matmul_11_scale_num & { 1{ 1'd1 } };
  wire [1-1:0] _dma_read_packed_local_packed_size_89;
  assign _dma_read_packed_local_packed_size_89 = (_dma_read_packed_low_local_size_88 > 0)? _dma_read_packed_high_local_size_87 + 1 : _dma_read_packed_high_local_size_87;
  wire [32-1:0] mask_addr_shifted_90;
  assign mask_addr_shifted_90 = matmul_11_arg_objaddr_3 + _maxi_global_base_addr >> 2;
  wire [32-1:0] mask_addr_masked_91;
  assign mask_addr_masked_91 = mask_addr_shifted_90 << 2;
  reg [32-1:0] write_burst_packed_fsm_1;
  localparam write_burst_packed_fsm_1_init = 0;
  reg [9-1:0] write_burst_packed_addr_92;
  reg [9-1:0] write_burst_packed_stride_93;
  reg [33-1:0] write_burst_packed_length_94;
  reg write_burst_packed_done_95;
  wire [8-1:0] write_burst_packed_ram_addr_96;
  assign write_burst_packed_ram_addr_96 = write_burst_packed_addr_92 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_97;
  assign write_burst_packed_ram_wdata_97 = _maxi_rdata_sb_0 >> 0;
  assign ram_w16_l512_id0_0_1_addr = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_96 : 'hx;
  assign ram_w16_l512_id0_0_1_wdata = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_97 : 'hx;
  assign ram_w16_l512_id0_0_1_wenable = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id0_0_1_enable = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  wire [8-1:0] write_burst_packed_ram_addr_98;
  assign write_burst_packed_ram_addr_98 = write_burst_packed_addr_92 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_99;
  assign write_burst_packed_ram_wdata_99 = _maxi_rdata_sb_0 >> 16;
  assign ram_w16_l512_id0_1_1_addr = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_98 : 'hx;
  assign ram_w16_l512_id0_1_1_wdata = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_99 : 'hx;
  assign ram_w16_l512_id0_1_1_wenable = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id0_1_1_enable = ((write_burst_packed_fsm_1 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  wire [8-1:0] _dma_read_packed_high_local_size_100;
  assign _dma_read_packed_high_local_size_100 = cparam_matmul_11_filter_read_size >> 1;
  wire [1-1:0] _dma_read_packed_low_local_size_101;
  assign _dma_read_packed_low_local_size_101 = cparam_matmul_11_filter_read_size & { 1{ 1'd1 } };
  wire [8-1:0] _dma_read_packed_local_packed_size_102;
  assign _dma_read_packed_local_packed_size_102 = (_dma_read_packed_low_local_size_101 > 0)? _dma_read_packed_high_local_size_100 + 1 : _dma_read_packed_high_local_size_100;
  wire [32-1:0] mask_addr_shifted_103;
  assign mask_addr_shifted_103 = matmul_11_arg_objaddr_1 + matmul_11_filter_base_offset + _maxi_global_base_addr >> 2;
  wire [32-1:0] mask_addr_masked_104;
  assign mask_addr_masked_104 = mask_addr_shifted_103 << 2;
  reg [32-1:0] write_burst_packed_fsm_2;
  localparam write_burst_packed_fsm_2_init = 0;
  reg [9-1:0] write_burst_packed_addr_105;
  reg [9-1:0] write_burst_packed_stride_106;
  reg [33-1:0] write_burst_packed_length_107;
  reg write_burst_packed_done_108;
  wire [8-1:0] write_burst_packed_ram_addr_109;
  assign write_burst_packed_ram_addr_109 = write_burst_packed_addr_105 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_110;
  assign write_burst_packed_ram_wdata_110 = _maxi_rdata_sb_0 >> 0;
  assign ram_w16_l512_id4_0_1_addr = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_109 : 'hx;
  assign ram_w16_l512_id4_0_1_wdata = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_110 : 'hx;
  assign ram_w16_l512_id4_0_1_wenable = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id4_0_1_enable = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  wire [8-1:0] write_burst_packed_ram_addr_111;
  assign write_burst_packed_ram_addr_111 = write_burst_packed_addr_105 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_112;
  assign write_burst_packed_ram_wdata_112 = _maxi_rdata_sb_0 >> 16;
  assign ram_w16_l512_id4_1_1_addr = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_111 : 'hx;
  assign ram_w16_l512_id4_1_1_wdata = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_112 : 'hx;
  assign ram_w16_l512_id4_1_1_wenable = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id4_1_1_enable = ((write_burst_packed_fsm_2 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  wire [32-1:0] matmul_11_mux_act_gaddr_0;
  assign matmul_11_mux_act_gaddr_0 = (matmul_11_row_select == 0)? matmul_11_arg_objaddr_0 + (matmul_11_act_base_offset + cparam_matmul_11_act_offset_values_0) : 1'd0;
  wire matmul_11_dma_pad_mask_0;
  assign matmul_11_dma_pad_mask_0 = (matmul_11_row_count + 0 < cparam_matmul_11_pad_row_top) || (matmul_11_row_count + 0 >= cparam_matmul_11_act_num_row + cparam_matmul_11_pad_row_top);
  wire matmul_11_mux_dma_pad_mask_0;
  assign matmul_11_mux_dma_pad_mask_0 = (matmul_11_row_select == 0)? matmul_11_dma_pad_mask_0 : 1'd0;
  wire matmul_11_mux_dma_flag_0;
  assign matmul_11_mux_dma_flag_0 = (matmul_11_prev_row_select == 0)? matmul_11_dma_flag_0 : 1'd0;
  wire [5-1:0] _dma_read_packed_high_local_size_113;
  assign _dma_read_packed_high_local_size_113 = cparam_matmul_11_act_read_size >> 1;
  wire [1-1:0] _dma_read_packed_low_local_size_114;
  assign _dma_read_packed_low_local_size_114 = cparam_matmul_11_act_read_size & { 1{ 1'd1 } };
  wire [5-1:0] _dma_read_packed_local_packed_size_115;
  assign _dma_read_packed_local_packed_size_115 = (_dma_read_packed_low_local_size_114 > 0)? _dma_read_packed_high_local_size_113 + 1 : _dma_read_packed_high_local_size_113;
  wire [32-1:0] mask_addr_shifted_116;
  assign mask_addr_shifted_116 = matmul_11_mux_act_gaddr_0 + _maxi_global_base_addr >> 2;
  wire [32-1:0] mask_addr_masked_117;
  assign mask_addr_masked_117 = mask_addr_shifted_116 << 2;
  assign _maxi_read_req_fifo_deq = ((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 4)) && !_maxi_read_req_fifo_empty)? 1 : 
                                   ((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 3)) && !_maxi_read_req_fifo_empty)? 1 : 
                                   ((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 2)) && !_maxi_read_req_fifo_empty)? 1 : 
                                   ((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 1)) && !_maxi_read_req_fifo_empty)? 1 : 0;
  reg [32-1:0] write_burst_packed_fsm_3;
  localparam write_burst_packed_fsm_3_init = 0;
  reg [9-1:0] write_burst_packed_addr_118;
  reg [9-1:0] write_burst_packed_stride_119;
  reg [33-1:0] write_burst_packed_length_120;
  reg write_burst_packed_done_121;
  wire [8-1:0] write_burst_packed_ram_addr_122;
  assign write_burst_packed_ram_addr_122 = write_burst_packed_addr_118 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_123;
  assign write_burst_packed_ram_wdata_123 = _maxi_rdata_sb_0 >> 0;
  assign ram_w16_l512_id2_0_1_addr = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_122 : 'hx;
  assign ram_w16_l512_id2_0_1_wdata = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_123 : 'hx;
  assign ram_w16_l512_id2_0_1_wenable = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id2_0_1_enable = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  wire [8-1:0] write_burst_packed_ram_addr_124;
  assign write_burst_packed_ram_addr_124 = write_burst_packed_addr_118 >> 1;
  wire [16-1:0] write_burst_packed_ram_wdata_125;
  assign write_burst_packed_ram_wdata_125 = _maxi_rdata_sb_0 >> 16;
  assign ram_w16_l512_id2_1_1_addr = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_addr_124 : 'hx;
  assign ram_w16_l512_id2_1_1_wdata = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? write_burst_packed_ram_wdata_125 : 'hx;
  assign ram_w16_l512_id2_1_1_wenable = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign ram_w16_l512_id2_1_1_enable = ((write_burst_packed_fsm_3 == 1) && _maxi_rvalid_sb_0)? 1'd1 : 0;
  assign _maxi_rready_sb_0 = (_maxi_read_data_fsm == 2) || (_maxi_read_data_fsm == 2) || (_maxi_read_data_fsm == 2) || (_maxi_read_data_fsm == 2);
  reg [32-1:0] matmul_11_comp_fsm;
  localparam matmul_11_comp_fsm_init = 0;
  reg [32-1:0] matmul_11_filter_page_comp_offset_buf;
  reg [32-1:0] matmul_11_act_page_comp_offset_buf_0;
  reg [32-1:0] matmul_11_out_page_comp_offset_buf;
  reg [32-1:0] matmul_11_row_count_buf;
  reg [1-1:0] matmul_11_row_select_buf;
  reg [32-1:0] matmul_11_och_count_buf;
  wire matmul_11_stream_pad_mask_0_0;
  assign matmul_11_stream_pad_mask_0_0 = (matmul_11_col_count + 0 < cparam_matmul_11_pad_col_left) || (matmul_11_col_count + 0 >= cparam_matmul_11_act_num_col + cparam_matmul_11_pad_col_left) || (matmul_11_row_count_buf + 0 < cparam_matmul_11_pad_row_top) || (matmul_11_row_count_buf + 0 >= cparam_matmul_11_act_num_row + cparam_matmul_11_pad_row_top);
  reg [1-1:0] matmul_11_stream_pad_masks;
  wire [5-1:0] stream_matmul_11_parameter_0_data;
  wire [1-1:0] stream_matmul_11_parameter_1_data;
  wire [1-1:0] stream_matmul_11_parameter_2_data;
  wire [1-1:0] stream_matmul_11_parameter_3_data;
  wire [1-1:0] stream_matmul_11_parameter_4_data;
  wire [1-1:0] stream_matmul_11__reduce_reset_data;
  wire [1-1:0] stream_matmul_11_parameter_6_data;
  wire [16-1:0] stream_matmul_11_source_7_data;
  wire [1-1:0] stream_matmul_11_parameter_8_data;
  wire [16-1:0] stream_matmul_11_source_9_data;
  wire [1-1:0] stream_matmul_11_parameter_10_data;
  wire [16-1:0] stream_matmul_11_source_11_data;
  wire [1-1:0] stream_matmul_11_parameter_12_data;
  wire [16-1:0] stream_matmul_11_source_13_data;
  wire [1-1:0] stream_matmul_11_parameter_14_data;
  wire [16-1:0] stream_matmul_11_source_15_data;
  wire [1-1:0] stream_matmul_11_parameter_16_data;
  wire [1-1:0] stream_matmul_11_parameter_17_data;
  wire [5-1:0] stream_matmul_11_parameter_18_data;
  wire [2-1:0] stream_matmul_11_parameter_19_data;
  wire [16-1:0] stream_matmul_11_source_20_data;
  wire [16-1:0] stream_matmul_11_source_21_data;
  reg __stream_matmul_11_stream_ivalid_1;
  reg __stream_matmul_11_stream_ivalid_2;
  reg __stream_matmul_11_stream_ivalid_3;
  reg __stream_matmul_11_stream_ivalid_4;
  reg __stream_matmul_11_stream_ivalid_5;
  reg __stream_matmul_11_stream_ivalid_6;
  reg __stream_matmul_11_stream_ivalid_7;
  reg __stream_matmul_11_stream_ivalid_8;
  reg __stream_matmul_11_stream_ivalid_9;
  reg __stream_matmul_11_stream_ivalid_10;
  reg __stream_matmul_11_stream_ivalid_11;
  reg __stream_matmul_11_stream_ivalid_12;
  reg __stream_matmul_11_stream_ivalid_13;
  reg __stream_matmul_11_stream_ivalid_14;
  reg __stream_matmul_11_stream_ivalid_15;
  reg __stream_matmul_11_stream_ivalid_16;
  reg __stream_matmul_11_stream_ivalid_17;
  reg __stream_matmul_11_stream_ivalid_18;
  reg __stream_matmul_11_stream_ivalid_19;
  reg __stream_matmul_11_stream_ivalid_20;
  reg __stream_matmul_11_stream_ivalid_21;
  reg __stream_matmul_11_stream_ivalid_22;
  reg __stream_matmul_11_stream_ivalid_23;
  reg __stream_matmul_11_stream_ivalid_24;
  reg __stream_matmul_11_stream_ivalid_25;
  reg __stream_matmul_11_stream_ivalid_26;
  reg __stream_matmul_11_stream_ivalid_27;
  reg __stream_matmul_11_stream_ivalid_28;
  reg __stream_matmul_11_stream_ivalid_29;
  wire [16-1:0] _slice_data_98;
  assign _slice_data_98 = stream_matmul_11_source_7_data[5'd15:1'd0];
  wire [16-1:0] _reinterpretcast_src_99;
  assign _reinterpretcast_src_99 = _slice_data_98;
  wire signed [16-1:0] _reinterpretcast_data_99;
  assign _reinterpretcast_data_99 = _reinterpretcast_src_99;
  wire signed [16-1:0] _cond_data_100;
  assign _cond_data_100 = (stream_matmul_11_parameter_6_data)? _reinterpretcast_data_99 : _reinterpretcast_data_99;
  wire [16-1:0] _slice_data_105;
  assign _slice_data_105 = stream_matmul_11_source_9_data[5'd15:1'd0];
  wire [16-1:0] _reinterpretcast_src_106;
  assign _reinterpretcast_src_106 = _slice_data_105;
  wire signed [16-1:0] _reinterpretcast_data_106;
  assign _reinterpretcast_data_106 = _reinterpretcast_src_106;
  wire signed [16-1:0] _cond_data_107;
  assign _cond_data_107 = (stream_matmul_11_parameter_8_data)? _reinterpretcast_data_106 : _reinterpretcast_data_106;
  wire [16-1:0] _slice_data_112;
  assign _slice_data_112 = stream_matmul_11_source_11_data[5'd15:1'd0];
  wire [16-1:0] _reinterpretcast_src_113;
  assign _reinterpretcast_src_113 = _slice_data_112;
  wire [16-1:0] _reinterpretcast_data_113;
  assign _reinterpretcast_data_113 = _reinterpretcast_src_113;
  wire [16-1:0] _cond_data_114;
  assign _cond_data_114 = (stream_matmul_11_parameter_10_data)? _reinterpretcast_data_113 : _reinterpretcast_data_113;
  wire [16-1:0] _slice_data_119;
  assign _slice_data_119 = stream_matmul_11_source_13_data[5'd15:1'd0];
  wire [16-1:0] _reinterpretcast_src_120;
  assign _reinterpretcast_src_120 = _slice_data_119;
  wire [16-1:0] _reinterpretcast_data_120;
  assign _reinterpretcast_data_120 = _reinterpretcast_src_120;
  wire [16-1:0] _cond_data_121;
  assign _cond_data_121 = (stream_matmul_11_parameter_12_data)? _reinterpretcast_data_120 : _reinterpretcast_data_120;
  wire [16-1:0] _slice_data_126;
  assign _slice_data_126 = stream_matmul_11_source_15_data[5'd15:1'd0];
  wire [16-1:0] _reinterpretcast_src_127;
  assign _reinterpretcast_src_127 = _slice_data_126;
  wire [16-1:0] _reinterpretcast_data_127;
  assign _reinterpretcast_data_127 = _reinterpretcast_src_127;
  wire [16-1:0] _cond_data_128;
  assign _cond_data_128 = (stream_matmul_11_parameter_14_data)? _reinterpretcast_data_127 : _reinterpretcast_data_127;
  reg [1-1:0] _eq_data_134;
  reg [1-1:0] _eq_data_138;
  wire [16-1:0] _reinterpretcast_src_152;
  assign _reinterpretcast_src_152 = stream_matmul_11_source_21_data;
  wire signed [16-1:0] _reinterpretcast_data_152;
  assign _reinterpretcast_data_152 = _reinterpretcast_src_152;
  wire [1-1:0] _pointer_data_153;
  assign _pointer_data_153 = stream_matmul_11_parameter_3_data[1'sd0];
  reg [16-1:0] _plus_data_174;
  reg [16-1:0] _plus_data_190;
  reg [16-1:0] _plus_data_209;
  reg [1-1:0] _eq_data_215;
  reg [1-1:0] _eq_data_218;
  reg [16-1:0] __delay_data_222__variable_133;
  reg [1-1:0] __delay_data_223_pointer_153;
  reg signed [16-1:0] __delay_data_224_reinterpretcast_152;
  reg [1-1:0] __delay_data_225__variable_84;
  reg [5-1:0] __delay_data_246__variable_79;
  reg signed [16-1:0] __delay_data_257_cond_100;
  reg signed [16-1:0] __delay_data_274_cond_107;
  wire signed [16-1:0] _cond_data_136;
  assign _cond_data_136 = (_eq_data_134)? __delay_data_222__variable_133 : 1'sd0;
  wire signed [16-1:0] _cond_data_140;
  assign _cond_data_140 = (_eq_data_138)? _cond_data_136 : 1'sd0;
  wire signed [16-1:0] _reinterpretcast_src_146;
  assign _reinterpretcast_src_146 = _cond_data_140;
  wire signed [16-1:0] _reinterpretcast_data_146;
  assign _reinterpretcast_data_146 = _reinterpretcast_src_146;
  wire signed [16-1:0] _cond_data_156;
  assign _cond_data_156 = (__delay_data_223_pointer_153)? 1'sd0 : _reinterpretcast_data_146;
  reg signed [16-1:0] __variable_wdata_58;
  assign mul_3_x_data = __variable_wdata_58;
  reg signed [16-1:0] __variable_wdata_59;
  assign mul_3_y_data = __variable_wdata_59;
  reg [5-1:0] __variable_wdata_60;
  assign mul_3_rshift_data = __variable_wdata_60;
  assign _mul_3_is_root = ((_stream_matmul_11_busy)? 0 : 1) && 1;
  assign _mul_3_stream_oready = ((_stream_matmul_11_busy)? _stream_matmul_11_stream_oready : 1) && _mul_3_stream_internal_oready;
  reg [1-1:0] __delay_data_226__delay_225__variable_84;
  reg [16-1:0] __delay_data_236_plus_190;
  reg [5-1:0] __delay_data_247__delay_246__variable_79;
  reg signed [16-1:0] __delay_data_258__delay_257_cond_100;
  reg signed [16-1:0] __delay_data_275__delay_274_cond_107;
  reg [16-1:0] __delay_data_292_plus_209;
  reg [1-1:0] __delay_data_310_eq_215;
  reg [1-1:0] __delay_data_339_eq_218;
  reg [1-1:0] __delay_data_227__delay_226__delay_225__variable_84;
  reg [16-1:0] __delay_data_237__delay_236_plus_190;
  reg [5-1:0] __delay_data_248__delay_247__delay_246__variable_79;
  reg signed [16-1:0] __delay_data_259__delay_258__delay_257_cond_100;
  reg signed [16-1:0] __delay_data_276__delay_275__delay_274_cond_107;
  reg [16-1:0] __delay_data_293__delay_292_plus_209;
  reg [1-1:0] __delay_data_311__delay_310_eq_215;
  reg [1-1:0] __delay_data_340__delay_339_eq_218;
  reg [1-1:0] __delay_data_228__delay_227__delay_226__delay_225__variable_84;
  reg [16-1:0] __delay_data_238__delay_237__delay_236_plus_190;
  reg [5-1:0] __delay_data_249__delay_248__delay_247__delay_246__variable_79;
  reg signed [16-1:0] __delay_data_260__delay_259__delay_258__delay_257_cond_100;
  reg signed [16-1:0] __delay_data_277__delay_276__delay_275__delay_274_cond_107;
  reg [16-1:0] __delay_data_294__delay_293__delay_292_plus_209;
  reg [1-1:0] __delay_data_312__delay_311__delay_310_eq_215;
  reg [1-1:0] __delay_data_341__delay_340__delay_339_eq_218;
  reg [1-1:0] __delay_data_229__delay_228__delay_227__delay_226____variable_84;
  reg [16-1:0] __delay_data_239__delay_238__delay_237__delay_236_plus_190;
  reg [5-1:0] __delay_data_250__delay_249__delay_248__delay_247____variable_79;
  reg signed [16-1:0] __delay_data_261__delay_260__delay_259__delay_258___cond_100;
  reg signed [16-1:0] __delay_data_278__delay_277__delay_276__delay_275___cond_107;
  reg [16-1:0] __delay_data_295__delay_294__delay_293__delay_292_plus_209;
  reg [1-1:0] __delay_data_313__delay_312__delay_311__delay_310_eq_215;
  reg [1-1:0] __delay_data_342__delay_341__delay_340__delay_339_eq_218;
  reg [1-1:0] __delay_data_230__delay_229__delay_228__delay_227____variable_84;
  reg [16-1:0] __delay_data_240__delay_239__delay_238__delay_237___plus_190;
  reg [5-1:0] __delay_data_251__delay_250__delay_249__delay_248____variable_79;
  reg signed [16-1:0] __delay_data_262__delay_261__delay_260__delay_259___cond_100;
  reg signed [16-1:0] __delay_data_279__delay_278__delay_277__delay_276___cond_107;
  reg [16-1:0] __delay_data_296__delay_295__delay_294__delay_293___plus_209;
  reg [1-1:0] __delay_data_314__delay_313__delay_312__delay_311___eq_215;
  reg [1-1:0] __delay_data_343__delay_342__delay_341__delay_340___eq_218;
  reg [1-1:0] __delay_data_231__delay_230__delay_229__delay_228____variable_84;
  reg [16-1:0] __delay_data_241__delay_240__delay_239__delay_238___plus_190;
  reg [5-1:0] __delay_data_252__delay_251__delay_250__delay_249____variable_79;
  reg signed [16-1:0] __delay_data_263__delay_262__delay_261__delay_260___cond_100;
  reg signed [16-1:0] __delay_data_280__delay_279__delay_278__delay_277___cond_107;
  reg [16-1:0] __delay_data_297__delay_296__delay_295__delay_294___plus_209;
  reg [1-1:0] __delay_data_315__delay_314__delay_313__delay_312___eq_215;
  reg [1-1:0] __delay_data_344__delay_343__delay_342__delay_341___eq_218;
  reg [1-1:0] __delay_data_232__delay_231__delay_230__delay_229____variable_84;
  reg [16-1:0] __delay_data_242__delay_241__delay_240__delay_239___plus_190;
  reg [5-1:0] __delay_data_253__delay_252__delay_251__delay_250____variable_79;
  reg signed [16-1:0] __delay_data_264__delay_263__delay_262__delay_261___cond_100;
  reg signed [16-1:0] __delay_data_281__delay_280__delay_279__delay_278___cond_107;
  reg [16-1:0] __delay_data_298__delay_297__delay_296__delay_295___plus_209;
  reg [1-1:0] __delay_data_316__delay_315__delay_314__delay_313___eq_215;
  reg [1-1:0] __delay_data_345__delay_344__delay_343__delay_342___eq_218;
  reg [1-1:0] __delay_data_233__delay_232__delay_231__delay_230____variable_84;
  reg [16-1:0] __delay_data_243__delay_242__delay_241__delay_240___plus_190;
  reg [5-1:0] __delay_data_254__delay_253__delay_252__delay_251____variable_79;
  reg signed [16-1:0] __delay_data_265__delay_264__delay_263__delay_262___cond_100;
  reg signed [16-1:0] __delay_data_282__delay_281__delay_280__delay_279___cond_107;
  reg [16-1:0] __delay_data_299__delay_298__delay_297__delay_296___plus_209;
  reg [1-1:0] __delay_data_317__delay_316__delay_315__delay_314___eq_215;
  reg [1-1:0] __delay_data_346__delay_345__delay_344__delay_343___eq_218;
  reg [1-1:0] __delay_data_234__delay_233__delay_232__delay_231____variable_84;
  reg [16-1:0] __delay_data_244__delay_243__delay_242__delay_241___plus_190;
  reg [5-1:0] __delay_data_255__delay_254__delay_253__delay_252____variable_79;
  reg signed [16-1:0] __delay_data_266__delay_265__delay_264__delay_263___cond_100;
  reg signed [16-1:0] __delay_data_283__delay_282__delay_281__delay_280___cond_107;
  reg [16-1:0] __delay_data_300__delay_299__delay_298__delay_297___plus_209;
  reg [1-1:0] __delay_data_318__delay_317__delay_316__delay_315___eq_215;
  reg [1-1:0] __delay_data_347__delay_346__delay_345__delay_344___eq_218;
  wire signed [32-1:0] __substreamoutput_data_175;
  assign __substreamoutput_data_175 = mul_3_z_data;
  reg signed [64-1:0] __variable_wdata_22;
  assign add_tree_1_var0_data = __variable_wdata_22;
  assign _add_tree_1_is_root = ((_stream_matmul_11_busy)? 0 : 1) && 1;
  assign _add_tree_1_stream_oready = ((_stream_matmul_11_busy)? _stream_matmul_11_stream_oready : 1) && _add_tree_1_stream_internal_oready;
  reg [1-1:0] __delay_data_235__delay_234__delay_233__delay_232____variable_84;
  reg [16-1:0] __delay_data_245__delay_244__delay_243__delay_242___plus_190;
  reg [5-1:0] __delay_data_256__delay_255__delay_254__delay_253____variable_79;
  reg signed [16-1:0] __delay_data_267__delay_266__delay_265__delay_264___cond_100;
  reg signed [16-1:0] __delay_data_284__delay_283__delay_282__delay_281___cond_107;
  reg [16-1:0] __delay_data_301__delay_300__delay_299__delay_298___plus_209;
  reg [1-1:0] __delay_data_319__delay_318__delay_317__delay_316___eq_215;
  reg [1-1:0] __delay_data_348__delay_347__delay_346__delay_345___eq_218;
  wire signed [64-1:0] __substreamoutput_data_177;
  assign __substreamoutput_data_177 = add_tree_1_sum_data;
  reg [1-1:0] __variable_wdata_15;
  assign acc_0__reduce_reset_data = __variable_wdata_15;
  reg signed [64-1:0] __variable_wdata_0;
  assign acc_0_x_data = __variable_wdata_0;
  reg [7-1:0] __variable_wdata_1;
  assign acc_0_rshift_data = __variable_wdata_1;
  reg [32-1:0] __variable_wdata_2;
  assign acc_0_size_data = __variable_wdata_2;
  assign _acc_0_is_root = ((_stream_matmul_11_busy)? 0 : 1) && 1;
  assign _acc_0_stream_oready = ((_stream_matmul_11_busy)? _stream_matmul_11_stream_oready : 1) && _acc_0_stream_internal_oready;
  reg signed [16-1:0] __delay_data_268__delay_267__delay_266__delay_265___cond_100;
  reg signed [16-1:0] __delay_data_285__delay_284__delay_283__delay_282___cond_107;
  reg [16-1:0] __delay_data_302__delay_301__delay_300__delay_299___plus_209;
  reg [1-1:0] __delay_data_320__delay_319__delay_318__delay_317___eq_215;
  reg [1-1:0] __delay_data_349__delay_348__delay_347__delay_346___eq_218;
  reg signed [16-1:0] __delay_data_269__delay_268__delay_267__delay_266___cond_100;
  reg signed [16-1:0] __delay_data_286__delay_285__delay_284__delay_283___cond_107;
  reg [16-1:0] __delay_data_303__delay_302__delay_301__delay_300___plus_209;
  reg [1-1:0] __delay_data_321__delay_320__delay_319__delay_318___eq_215;
  reg [1-1:0] __delay_data_350__delay_349__delay_348__delay_347___eq_218;
  reg signed [16-1:0] __delay_data_270__delay_269__delay_268__delay_267___cond_100;
  reg signed [16-1:0] __delay_data_287__delay_286__delay_285__delay_284___cond_107;
  reg [16-1:0] __delay_data_304__delay_303__delay_302__delay_301___plus_209;
  reg [1-1:0] __delay_data_322__delay_321__delay_320__delay_319___eq_215;
  reg [1-1:0] __delay_data_351__delay_350__delay_349__delay_348___eq_218;
  reg signed [16-1:0] __delay_data_271__delay_270__delay_269__delay_268___cond_100;
  reg signed [16-1:0] __delay_data_288__delay_287__delay_286__delay_285___cond_107;
  reg [16-1:0] __delay_data_305__delay_304__delay_303__delay_302___plus_209;
  reg [1-1:0] __delay_data_323__delay_322__delay_321__delay_320___eq_215;
  reg [1-1:0] __delay_data_352__delay_351__delay_350__delay_349___eq_218;
  reg signed [16-1:0] __delay_data_272__delay_271__delay_270__delay_269___cond_100;
  reg signed [16-1:0] __delay_data_289__delay_288__delay_287__delay_286___cond_107;
  reg [16-1:0] __delay_data_306__delay_305__delay_304__delay_303___plus_209;
  reg [1-1:0] __delay_data_324__delay_323__delay_322__delay_321___eq_215;
  reg [1-1:0] __delay_data_353__delay_352__delay_351__delay_350___eq_218;
  reg signed [16-1:0] __delay_data_273__delay_272__delay_271__delay_270___cond_100;
  reg signed [16-1:0] __delay_data_290__delay_289__delay_288__delay_287___cond_107;
  reg [16-1:0] __delay_data_307__delay_306__delay_305__delay_304___plus_209;
  reg [1-1:0] __delay_data_325__delay_324__delay_323__delay_322___eq_215;
  reg [1-1:0] __delay_data_354__delay_353__delay_352__delay_351___eq_218;
  wire signed [64-1:0] __substreamoutput_data_191;
  assign __substreamoutput_data_191 = acc_0_sum_data;
  wire [1-1:0] __substreamoutput_data_192;
  assign __substreamoutput_data_192 = acc_0_valid_data;
  reg signed [64-1:0] _plus_data_193;
  reg signed [16-1:0] __delay_data_291__delay_290__delay_289__delay_288___cond_107;
  reg [16-1:0] __delay_data_308__delay_307__delay_306__delay_305___plus_209;
  reg [1-1:0] __delay_data_326__delay_325__delay_324__delay_323___eq_215;
  reg [1-1:0] __delay_data_355__delay_354__delay_353__delay_352___eq_218;
  reg [1-1:0] __delay_data_367__substreamoutput_192;
  reg signed [64-1:0] __variable_wdata_24;
  assign mul_rshift_round_clip_2_x_data = __variable_wdata_24;
  reg signed [16-1:0] __variable_wdata_25;
  assign mul_rshift_round_clip_2_y_data = __variable_wdata_25;
  reg [7-1:0] __variable_wdata_26;
  assign mul_rshift_round_clip_2_rshift_data = __variable_wdata_26;
  assign _mul_rshift_round_clip_2_is_root = ((_stream_matmul_11_busy)? 0 : 1) && 1;
  assign _mul_rshift_round_clip_2_stream_oready = ((_stream_matmul_11_busy)? _stream_matmul_11_stream_oready : 1) && _mul_rshift_round_clip_2_stream_internal_oready;
  assign _stream_matmul_11_stream_internal_oready = ((_stream_matmul_11_busy)? _mul_rshift_round_clip_2_stream_internal_oready : 1) && (((_stream_matmul_11_busy)? _acc_0_stream_internal_oready : 1) && (((_stream_matmul_11_busy)? _add_tree_1_stream_internal_oready : 1) && (((_stream_matmul_11_busy)? _mul_3_stream_internal_oready : 1) && 1)));
  reg [1-1:0] __delay_data_327__delay_326__delay_325__delay_324___eq_215;
  reg [1-1:0] __delay_data_356__delay_355__delay_354__delay_353___eq_218;
  reg [1-1:0] __delay_data_368__delay_367__substreamoutput_192;
  reg [1-1:0] __delay_data_328__delay_327__delay_326__delay_325___eq_215;
  reg [1-1:0] __delay_data_357__delay_356__delay_355__delay_354___eq_218;
  reg [1-1:0] __delay_data_369__delay_368__delay_367__substreamoutput_192;
  reg [1-1:0] __delay_data_329__delay_328__delay_327__delay_326___eq_215;
  reg [1-1:0] __delay_data_358__delay_357__delay_356__delay_355___eq_218;
  reg [1-1:0] __delay_data_370__delay_369__delay_368____substreamoutput_192;
  reg [1-1:0] __delay_data_330__delay_329__delay_328__delay_327___eq_215;
  reg [1-1:0] __delay_data_359__delay_358__delay_357__delay_356___eq_218;
  reg [1-1:0] __delay_data_371__delay_370__delay_369____substreamoutput_192;
  reg [1-1:0] __delay_data_331__delay_330__delay_329__delay_328___eq_215;
  reg [1-1:0] __delay_data_360__delay_359__delay_358__delay_357___eq_218;
  reg [1-1:0] __delay_data_372__delay_371__delay_370____substreamoutput_192;
  reg [1-1:0] __delay_data_332__delay_331__delay_330__delay_329___eq_215;
  reg [1-1:0] __delay_data_361__delay_360__delay_359__delay_358___eq_218;
  reg [1-1:0] __delay_data_373__delay_372__delay_371____substreamoutput_192;
  reg [1-1:0] __delay_data_333__delay_332__delay_331__delay_330___eq_215;
  reg [1-1:0] __delay_data_362__delay_361__delay_360__delay_359___eq_218;
  reg [1-1:0] __delay_data_374__delay_373__delay_372____substreamoutput_192;
  reg [1-1:0] __delay_data_334__delay_333__delay_332__delay_331___eq_215;
  reg [1-1:0] __delay_data_363__delay_362__delay_361__delay_360___eq_218;
  reg [1-1:0] __delay_data_375__delay_374__delay_373____substreamoutput_192;
  reg [1-1:0] __delay_data_335__delay_334__delay_333__delay_332___eq_215;
  reg [1-1:0] __delay_data_364__delay_363__delay_362__delay_361___eq_218;
  reg [1-1:0] __delay_data_376__delay_375__delay_374____substreamoutput_192;
  wire signed [16-1:0] __substreamoutput_data_210;
  assign __substreamoutput_data_210 = mul_rshift_round_clip_2_z_data;
  reg [1-1:0] _greaterthan_data_212;
  reg signed [16-1:0] __delay_data_309__substreamoutput_210;
  reg [1-1:0] __delay_data_336__delay_335__delay_334__delay_333___eq_215;
  reg [1-1:0] __delay_data_365__delay_364__delay_363__delay_362___eq_218;
  reg [1-1:0] __delay_data_377__delay_376__delay_375____substreamoutput_192;
  reg signed [16-1:0] _cond_data_214;
  reg [1-1:0] __delay_data_337__delay_336__delay_335__delay_334___eq_215;
  reg signed [16-1:0] __delay_data_338__delay_309__substreamoutput_210;
  reg [1-1:0] __delay_data_366__delay_365__delay_364__delay_363___eq_218;
  reg [1-1:0] __delay_data_378__delay_377__delay_376____substreamoutput_192;
  wire signed [16-1:0] _cond_data_217;
  assign _cond_data_217 = (__delay_data_337__delay_336__delay_335__delay_334___eq_215)? _cond_data_214 : __delay_data_338__delay_309__substreamoutput_210;
  wire signed [16-1:0] _cond_data_220;
  assign _cond_data_220 = (__delay_data_366__delay_365__delay_364__delay_363___eq_218)? __delay_data_338__delay_309__substreamoutput_210 : _cond_data_217;
  wire signed [16-1:0] _reinterpretcast_src_221;
  assign _reinterpretcast_src_221 = _cond_data_220;
  wire signed [16-1:0] _reinterpretcast_data_221;
  assign _reinterpretcast_data_221 = _reinterpretcast_src_221;
  wire signed [16-1:0] stream_matmul_11_sink_26_data;
  assign stream_matmul_11_sink_26_data = _reinterpretcast_data_221;
  wire [1-1:0] stream_matmul_11_sink_27_data;
  assign stream_matmul_11_sink_27_data = __delay_data_378__delay_377__delay_376____substreamoutput_192;
  wire _set_flag_126;
  assign _set_flag_126 = matmul_11_comp_fsm == 3;
  reg [5-1:0] __variable_wdata_79;
  assign stream_matmul_11_parameter_0_data = __variable_wdata_79;
  wire _set_flag_127;
  assign _set_flag_127 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_80;
  assign stream_matmul_11_parameter_1_data = __variable_wdata_80;
  wire _set_flag_128;
  assign _set_flag_128 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_81;
  assign stream_matmul_11_parameter_2_data = __variable_wdata_81;
  wire _set_flag_129;
  assign _set_flag_129 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_82;
  assign stream_matmul_11_parameter_3_data = __variable_wdata_82;
  wire _set_flag_130;
  assign _set_flag_130 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_83;
  assign stream_matmul_11_parameter_4_data = __variable_wdata_83;
  wire _set_flag_131;
  assign _set_flag_131 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_94;
  assign stream_matmul_11_parameter_6_data = __variable_wdata_94;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_cur_offset_0;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_cur_offset_1;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_cur_offset_2;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_cur_offset_3;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_0;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_1;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_2;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_3;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_0;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_1;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_2;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_3;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_count_0;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_count_1;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_count_2;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_count_3;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_buf_0;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_buf_1;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_buf_2;
  reg [33-1:0] _source_stream_matmul_11_source_7_pat_size_buf_3;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_buf_0;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_buf_1;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_buf_2;
  reg [32-1:0] _source_stream_matmul_11_source_7_pat_stride_buf_3;
  wire _set_flag_132;
  assign _set_flag_132 = matmul_11_comp_fsm == 3;
  wire [1-1:0] read_rtl_bank_133;
  assign read_rtl_bank_133 = _stream_matmul_11_source_7_source_ram_raddr;
  reg [1-1:0] _tmp_134;
  assign ram_w16_l512_id3_0_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_7_source_ram_renable && (_stream_matmul_11_source_7_source_sel == 1))? _stream_matmul_11_source_7_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id3_0_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_7_source_ram_renable && (_stream_matmul_11_source_7_source_sel == 1))? 1'd1 : 0;
  localparam _tmp_135 = 1;
  wire [_tmp_135-1:0] _tmp_136;
  assign _tmp_136 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_7_source_ram_renable && (_stream_matmul_11_source_7_source_sel == 1);
  reg [_tmp_135-1:0] __tmp_136_1;
  assign ram_w16_l512_id3_1_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_7_source_ram_renable && (_stream_matmul_11_source_7_source_sel == 1))? _stream_matmul_11_source_7_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id3_1_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_7_source_ram_renable && (_stream_matmul_11_source_7_source_sel == 1))? 1'd1 : 0;
  localparam _tmp_137 = 1;
  wire [_tmp_137-1:0] _tmp_138;
  assign _tmp_138 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_7_source_ram_renable && (_stream_matmul_11_source_7_source_sel == 1);
  reg [_tmp_137-1:0] __tmp_138_1;
  wire signed [16-1:0] read_rtl_rdata_139;
  wire read_rtl_rvalid_140;
  assign read_rtl_rdata_139 = (_tmp_134 == 0)? ram_w16_l512_id3_0_0_rdata : 
                              (_tmp_134 == 1)? ram_w16_l512_id3_1_0_rdata : 0;
  assign read_rtl_rvalid_140 = __tmp_136_1;
  assign _stream_matmul_11_source_7_source_ram_rdata = (_stream_matmul_11_source_7_source_sel == 1)? read_rtl_rdata_139 : 'hx;
  reg [16-1:0] __variable_wdata_95;
  assign stream_matmul_11_source_7_data = __variable_wdata_95;
  reg [32-1:0] _stream_matmul_11_source_7_source_pat_fsm_0;
  localparam _stream_matmul_11_source_7_source_pat_fsm_0_init = 0;
  wire [32-1:0] _stream_matmul_11_source_7_source_pat_all_offset;
  assign _stream_matmul_11_source_7_source_pat_all_offset = _stream_matmul_11_source_7_source_offset_buf + _source_stream_matmul_11_source_7_pat_cur_offset_0 + _source_stream_matmul_11_source_7_pat_cur_offset_1 + _source_stream_matmul_11_source_7_pat_cur_offset_2 + _source_stream_matmul_11_source_7_pat_cur_offset_3;
  wire _set_flag_141;
  assign _set_flag_141 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_101;
  assign stream_matmul_11_parameter_8_data = __variable_wdata_101;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_cur_offset_0;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_cur_offset_1;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_cur_offset_2;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_cur_offset_3;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_0;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_1;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_2;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_3;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_0;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_1;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_2;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_3;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_count_0;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_count_1;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_count_2;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_count_3;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_buf_0;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_buf_1;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_buf_2;
  reg [33-1:0] _source_stream_matmul_11_source_9_pat_size_buf_3;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_buf_0;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_buf_1;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_buf_2;
  reg [32-1:0] _source_stream_matmul_11_source_9_pat_stride_buf_3;
  wire _set_flag_142;
  assign _set_flag_142 = matmul_11_comp_fsm == 3;
  wire [1-1:0] read_rtl_bank_143;
  assign read_rtl_bank_143 = _stream_matmul_11_source_9_source_ram_raddr;
  reg [1-1:0] _tmp_144;
  assign ram_w16_l512_id0_0_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_9_source_ram_renable && (_stream_matmul_11_source_9_source_sel == 2))? _stream_matmul_11_source_9_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id0_0_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_9_source_ram_renable && (_stream_matmul_11_source_9_source_sel == 2))? 1'd1 : 0;
  localparam _tmp_145 = 1;
  wire [_tmp_145-1:0] _tmp_146;
  assign _tmp_146 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_9_source_ram_renable && (_stream_matmul_11_source_9_source_sel == 2);
  reg [_tmp_145-1:0] __tmp_146_1;
  assign ram_w16_l512_id0_1_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_9_source_ram_renable && (_stream_matmul_11_source_9_source_sel == 2))? _stream_matmul_11_source_9_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id0_1_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_9_source_ram_renable && (_stream_matmul_11_source_9_source_sel == 2))? 1'd1 : 0;
  localparam _tmp_147 = 1;
  wire [_tmp_147-1:0] _tmp_148;
  assign _tmp_148 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_9_source_ram_renable && (_stream_matmul_11_source_9_source_sel == 2);
  reg [_tmp_147-1:0] __tmp_148_1;
  wire signed [16-1:0] read_rtl_rdata_149;
  wire read_rtl_rvalid_150;
  assign read_rtl_rdata_149 = (_tmp_144 == 0)? ram_w16_l512_id0_0_0_rdata : 
                              (_tmp_144 == 1)? ram_w16_l512_id0_1_0_rdata : 0;
  assign read_rtl_rvalid_150 = __tmp_146_1;
  assign _stream_matmul_11_source_9_source_ram_rdata = (_stream_matmul_11_source_9_source_sel == 2)? read_rtl_rdata_149 : 'hx;
  reg [16-1:0] __variable_wdata_102;
  assign stream_matmul_11_source_9_data = __variable_wdata_102;
  reg [32-1:0] _stream_matmul_11_source_9_source_pat_fsm_1;
  localparam _stream_matmul_11_source_9_source_pat_fsm_1_init = 0;
  wire [32-1:0] _stream_matmul_11_source_9_source_pat_all_offset;
  assign _stream_matmul_11_source_9_source_pat_all_offset = _stream_matmul_11_source_9_source_offset_buf + _source_stream_matmul_11_source_9_pat_cur_offset_0 + _source_stream_matmul_11_source_9_pat_cur_offset_1 + _source_stream_matmul_11_source_9_pat_cur_offset_2 + _source_stream_matmul_11_source_9_pat_cur_offset_3;
  wire _set_flag_151;
  assign _set_flag_151 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_108;
  assign stream_matmul_11_parameter_10_data = __variable_wdata_108;
  wire _set_flag_152;
  assign _set_flag_152 = matmul_11_comp_fsm == 3;
  reg [16-1:0] __variable_wdata_109;
  assign stream_matmul_11_source_11_data = __variable_wdata_109;
  wire _set_flag_153;
  assign _set_flag_153 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_115;
  assign stream_matmul_11_parameter_12_data = __variable_wdata_115;
  wire _set_flag_154;
  assign _set_flag_154 = matmul_11_comp_fsm == 3;
  reg [16-1:0] __variable_wdata_116;
  assign stream_matmul_11_source_13_data = __variable_wdata_116;
  wire _set_flag_155;
  assign _set_flag_155 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_122;
  assign stream_matmul_11_parameter_14_data = __variable_wdata_122;
  wire _set_flag_156;
  assign _set_flag_156 = matmul_11_comp_fsm == 3;
  reg [16-1:0] __variable_wdata_123;
  assign stream_matmul_11_source_15_data = __variable_wdata_123;
  wire _set_flag_157;
  assign _set_flag_157 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_129;
  assign stream_matmul_11_parameter_16_data = __variable_wdata_129;
  wire _set_flag_158;
  assign _set_flag_158 = matmul_11_comp_fsm == 3;
  reg [1-1:0] __variable_wdata_130;
  assign stream_matmul_11_parameter_17_data = __variable_wdata_130;
  wire _set_flag_159;
  assign _set_flag_159 = matmul_11_comp_fsm == 3;
  reg [5-1:0] __variable_wdata_131;
  assign stream_matmul_11_parameter_18_data = __variable_wdata_131;
  wire _set_flag_160;
  assign _set_flag_160 = matmul_11_comp_fsm == 3;
  reg [2-1:0] __variable_wdata_132;
  assign stream_matmul_11_parameter_19_data = __variable_wdata_132;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_cur_offset_0;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_cur_offset_1;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_cur_offset_2;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_cur_offset_3;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_0;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_1;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_2;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_3;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_0;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_1;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_2;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_3;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_count_0;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_count_1;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_count_2;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_count_3;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_buf_0;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_buf_1;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_buf_2;
  reg [33-1:0] _source_stream_matmul_11_source_20_pat_size_buf_3;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_buf_0;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_buf_1;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_buf_2;
  reg [32-1:0] _source_stream_matmul_11_source_20_pat_stride_buf_3;
  wire _set_flag_161;
  assign _set_flag_161 = matmul_11_comp_fsm == 3;
  wire [1-1:0] read_rtl_bank_162;
  assign read_rtl_bank_162 = _stream_matmul_11_source_20_source_ram_raddr;
  reg [1-1:0] _tmp_163;
  assign ram_w16_l512_id2_0_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_20_source_ram_renable && (_stream_matmul_11_source_20_source_sel == 3))? _stream_matmul_11_source_20_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id2_0_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_20_source_ram_renable && (_stream_matmul_11_source_20_source_sel == 3))? 1'd1 : 0;
  localparam _tmp_164 = 1;
  wire [_tmp_164-1:0] _tmp_165;
  assign _tmp_165 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_20_source_ram_renable && (_stream_matmul_11_source_20_source_sel == 3);
  reg [_tmp_164-1:0] __tmp_165_1;
  assign ram_w16_l512_id2_1_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_20_source_ram_renable && (_stream_matmul_11_source_20_source_sel == 3))? _stream_matmul_11_source_20_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id2_1_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_20_source_ram_renable && (_stream_matmul_11_source_20_source_sel == 3))? 1'd1 : 0;
  localparam _tmp_166 = 1;
  wire [_tmp_166-1:0] _tmp_167;
  assign _tmp_167 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_20_source_ram_renable && (_stream_matmul_11_source_20_source_sel == 3);
  reg [_tmp_166-1:0] __tmp_167_1;
  wire signed [16-1:0] read_rtl_rdata_168;
  wire read_rtl_rvalid_169;
  assign read_rtl_rdata_168 = (_tmp_163 == 0)? ram_w16_l512_id2_0_0_rdata : 
                              (_tmp_163 == 1)? ram_w16_l512_id2_1_0_rdata : 0;
  assign read_rtl_rvalid_169 = __tmp_165_1;
  assign _stream_matmul_11_source_20_source_ram_rdata = (_stream_matmul_11_source_20_source_sel == 3)? read_rtl_rdata_168 : 'hx;
  reg [16-1:0] __variable_wdata_133;
  assign stream_matmul_11_source_20_data = __variable_wdata_133;
  reg [32-1:0] _stream_matmul_11_source_20_source_pat_fsm_2;
  localparam _stream_matmul_11_source_20_source_pat_fsm_2_init = 0;
  wire [32-1:0] _stream_matmul_11_source_20_source_pat_all_offset;
  assign _stream_matmul_11_source_20_source_pat_all_offset = _stream_matmul_11_source_20_source_offset_buf + _source_stream_matmul_11_source_20_pat_cur_offset_0 + _source_stream_matmul_11_source_20_pat_cur_offset_1 + _source_stream_matmul_11_source_20_pat_cur_offset_2 + _source_stream_matmul_11_source_20_pat_cur_offset_3;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_cur_offset_0;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_cur_offset_1;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_cur_offset_2;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_cur_offset_3;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_0;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_1;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_2;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_3;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_0;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_1;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_2;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_3;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_count_0;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_count_1;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_count_2;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_count_3;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_buf_0;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_buf_1;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_buf_2;
  reg [33-1:0] _source_stream_matmul_11_source_21_pat_size_buf_3;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_buf_0;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_buf_1;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_buf_2;
  reg [32-1:0] _source_stream_matmul_11_source_21_pat_stride_buf_3;
  wire _set_flag_170;
  assign _set_flag_170 = matmul_11_comp_fsm == 3;
  wire [1-1:0] read_rtl_bank_171;
  assign read_rtl_bank_171 = _stream_matmul_11_source_21_source_ram_raddr;
  reg [1-1:0] _tmp_172;
  assign ram_w16_l512_id4_0_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_21_source_ram_renable && (_stream_matmul_11_source_21_source_sel == 4))? _stream_matmul_11_source_21_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id4_0_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_21_source_ram_renable && (_stream_matmul_11_source_21_source_sel == 4))? 1'd1 : 0;
  localparam _tmp_173 = 1;
  wire [_tmp_173-1:0] _tmp_174;
  assign _tmp_174 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_21_source_ram_renable && (_stream_matmul_11_source_21_source_sel == 4);
  reg [_tmp_173-1:0] __tmp_174_1;
  assign ram_w16_l512_id4_1_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_21_source_ram_renable && (_stream_matmul_11_source_21_source_sel == 4))? _stream_matmul_11_source_21_source_ram_raddr >> 1 : 'hx;
  assign ram_w16_l512_id4_1_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_source_21_source_ram_renable && (_stream_matmul_11_source_21_source_sel == 4))? 1'd1 : 0;
  localparam _tmp_175 = 1;
  wire [_tmp_175-1:0] _tmp_176;
  assign _tmp_176 = _stream_matmul_11_stream_oready && _stream_matmul_11_source_21_source_ram_renable && (_stream_matmul_11_source_21_source_sel == 4);
  reg [_tmp_175-1:0] __tmp_176_1;
  wire signed [16-1:0] read_rtl_rdata_177;
  wire read_rtl_rvalid_178;
  assign read_rtl_rdata_177 = (_tmp_172 == 0)? ram_w16_l512_id4_0_0_rdata : 
                              (_tmp_172 == 1)? ram_w16_l512_id4_1_0_rdata : 0;
  assign read_rtl_rvalid_178 = __tmp_174_1;
  assign _stream_matmul_11_source_21_source_ram_rdata = (_stream_matmul_11_source_21_source_sel == 4)? read_rtl_rdata_177 : 'hx;
  reg [16-1:0] __variable_wdata_147;
  assign stream_matmul_11_source_21_data = __variable_wdata_147;
  reg [32-1:0] _stream_matmul_11_source_21_source_pat_fsm_3;
  localparam _stream_matmul_11_source_21_source_pat_fsm_3_init = 0;
  wire [32-1:0] _stream_matmul_11_source_21_source_pat_all_offset;
  assign _stream_matmul_11_source_21_source_pat_all_offset = _stream_matmul_11_source_21_source_offset_buf + _source_stream_matmul_11_source_21_pat_cur_offset_0 + _source_stream_matmul_11_source_21_pat_cur_offset_1 + _source_stream_matmul_11_source_21_pat_cur_offset_2 + _source_stream_matmul_11_source_21_pat_cur_offset_3;
  wire _set_flag_179;
  assign _set_flag_179 = matmul_11_comp_fsm == 3;
  reg _tmp_180;
  reg _tmp_181;
  reg _tmp_182;
  reg _tmp_183;
  reg _tmp_184;
  reg _tmp_185;
  reg _tmp_186;
  reg _tmp_187;
  reg _tmp_188;
  reg _tmp_189;
  reg _tmp_190;
  reg _tmp_191;
  reg _tmp_192;
  reg _tmp_193;
  reg _tmp_194;
  reg _tmp_195;
  reg _tmp_196;
  reg _tmp_197;
  reg _tmp_198;
  reg _tmp_199;
  reg _tmp_200;
  reg _tmp_201;
  reg _tmp_202;
  reg _tmp_203;
  reg _tmp_204;
  reg _tmp_205;
  reg _tmp_206;
  reg _tmp_207;
  reg _tmp_208;
  reg _tmp_209;
  reg _tmp_210;
  localparam _tmp_211 = 33;
  wire [_tmp_211-1:0] _tmp_212;
  assign _tmp_212 = matmul_11_stream_out_local + matmul_11_out_page_comp_offset_buf;
  reg [_tmp_211-1:0] _tmp_213;
  reg [_tmp_211-1:0] _tmp_214;
  reg [_tmp_211-1:0] _tmp_215;
  reg [_tmp_211-1:0] _tmp_216;
  reg [_tmp_211-1:0] _tmp_217;
  reg [_tmp_211-1:0] _tmp_218;
  reg [_tmp_211-1:0] _tmp_219;
  reg [_tmp_211-1:0] _tmp_220;
  reg [_tmp_211-1:0] _tmp_221;
  reg [_tmp_211-1:0] _tmp_222;
  reg [_tmp_211-1:0] _tmp_223;
  reg [_tmp_211-1:0] _tmp_224;
  reg [_tmp_211-1:0] _tmp_225;
  reg [_tmp_211-1:0] _tmp_226;
  reg [_tmp_211-1:0] _tmp_227;
  reg [_tmp_211-1:0] _tmp_228;
  reg [_tmp_211-1:0] _tmp_229;
  reg [_tmp_211-1:0] _tmp_230;
  reg [_tmp_211-1:0] _tmp_231;
  reg [_tmp_211-1:0] _tmp_232;
  reg [_tmp_211-1:0] _tmp_233;
  reg [_tmp_211-1:0] _tmp_234;
  reg [_tmp_211-1:0] _tmp_235;
  reg [_tmp_211-1:0] _tmp_236;
  reg [_tmp_211-1:0] _tmp_237;
  reg [_tmp_211-1:0] _tmp_238;
  reg [_tmp_211-1:0] _tmp_239;
  reg [_tmp_211-1:0] _tmp_240;
  reg [_tmp_211-1:0] _tmp_241;
  reg [_tmp_211-1:0] _tmp_242;
  reg [_tmp_211-1:0] _tmp_243;
  reg [32-1:0] _tmp_244;
  reg [32-1:0] _tmp_245;
  reg [32-1:0] _tmp_246;
  reg [32-1:0] _tmp_247;
  reg [32-1:0] _tmp_248;
  reg [32-1:0] _tmp_249;
  reg [32-1:0] _tmp_250;
  reg [32-1:0] _tmp_251;
  reg [32-1:0] _tmp_252;
  reg [32-1:0] _tmp_253;
  reg [32-1:0] _tmp_254;
  reg [32-1:0] _tmp_255;
  reg [32-1:0] _tmp_256;
  reg [32-1:0] _tmp_257;
  reg [32-1:0] _tmp_258;
  reg [32-1:0] _tmp_259;
  reg [32-1:0] _tmp_260;
  reg [32-1:0] _tmp_261;
  reg [32-1:0] _tmp_262;
  reg [32-1:0] _tmp_263;
  reg [32-1:0] _tmp_264;
  reg [32-1:0] _tmp_265;
  reg [32-1:0] _tmp_266;
  reg [32-1:0] _tmp_267;
  reg [32-1:0] _tmp_268;
  reg [32-1:0] _tmp_269;
  reg [32-1:0] _tmp_270;
  reg [32-1:0] _tmp_271;
  reg [32-1:0] _tmp_272;
  reg [32-1:0] _tmp_273;
  reg [32-1:0] _tmp_274;
  wire [1-1:0] write_rtl_bank_275;
  assign write_rtl_bank_275 = _stream_matmul_11_sink_26_sink_waddr;
  assign ram_w16_l512_id1_0_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 0))? _stream_matmul_11_sink_26_sink_waddr >> 1 : 'hx;
  assign ram_w16_l512_id1_0_0_wdata = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 0))? _stream_matmul_11_sink_26_sink_wdata : 'hx;
  assign ram_w16_l512_id1_0_0_wenable = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 0))? 1'd1 : 0;
  assign ram_w16_l512_id1_0_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 0))? 1'd1 : 0;
  assign ram_w16_l512_id1_1_0_addr = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 1))? _stream_matmul_11_sink_26_sink_waddr >> 1 : 'hx;
  assign ram_w16_l512_id1_1_0_wdata = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 1))? _stream_matmul_11_sink_26_sink_wdata : 'hx;
  assign ram_w16_l512_id1_1_0_wenable = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 1))? 1'd1 : 0;
  assign ram_w16_l512_id1_1_0_enable = (_stream_matmul_11_stream_oready && _stream_matmul_11_sink_26_sink_wenable && (_stream_matmul_11_sink_26_sink_sel == 5) && (write_rtl_bank_275 == 1))? 1'd1 : 0;
  reg [32-1:0] _stream_matmul_11_sink_26_sink_fsm_4;
  localparam _stream_matmul_11_sink_26_sink_fsm_4_init = 0;
  wire _set_flag_276;
  assign _set_flag_276 = matmul_11_comp_fsm == 4;
  assign _stream_matmul_11_run_flag = (_set_flag_276)? 1 : 0;
  reg _tmp_277;
  reg _tmp_278;
  reg _tmp_279;
  assign _mul_3_source_stop = _mul_3_stream_oready && 1'd0;
  reg _tmp_280;
  reg _tmp_281;
  reg _tmp_282;
  reg _tmp_283;
  reg _tmp_284;
  reg _tmp_285;
  reg _tmp_286;
  reg _tmp_287;
  reg _tmp_288;
  reg _tmp_289;
  assign _mul_3_sink_start = _tmp_289;
  reg _tmp_290;
  reg _tmp_291;
  reg _tmp_292;
  reg _tmp_293;
  reg _tmp_294;
  reg _tmp_295;
  reg _tmp_296;
  reg _tmp_297;
  reg _tmp_298;
  reg _tmp_299;
  assign _mul_3_sink_stop = _tmp_299;
  reg _tmp_300;
  reg _tmp_301;
  reg _tmp_302;
  reg _tmp_303;
  reg _tmp_304;
  reg _tmp_305;
  reg _tmp_306;
  reg _tmp_307;
  reg _tmp_308;
  reg _tmp_309;
  assign _mul_3_sink_busy = _tmp_309;
  reg _tmp_310;
  assign _mul_3_busy = _mul_3_source_busy || _mul_3_sink_busy || _mul_3_busy_reg;
  reg _tmp_311;
  reg _tmp_312;
  reg _tmp_313;
  assign _add_tree_1_source_stop = _add_tree_1_stream_oready && 1'd0;
  reg _tmp_314;
  reg _tmp_315;
  assign _add_tree_1_sink_start = _tmp_315;
  reg _tmp_316;
  reg _tmp_317;
  assign _add_tree_1_sink_stop = _tmp_317;
  reg _tmp_318;
  reg _tmp_319;
  assign _add_tree_1_sink_busy = _tmp_319;
  reg _tmp_320;
  assign _add_tree_1_busy = _add_tree_1_source_busy || _add_tree_1_sink_busy || _add_tree_1_busy_reg;
  reg _tmp_321;
  reg _tmp_322;
  reg _tmp_323;
  reg _tmp_324;
  reg _tmp_325;
  reg _tmp_326;
  reg _tmp_327;
  reg _tmp_328;
  reg _tmp_329;
  reg _tmp_330;
  assign _acc_0_source_stop = _acc_0_stream_oready && 1'd0;
  reg _tmp_331;
  reg _tmp_332;
  reg _tmp_333;
  reg _tmp_334;
  reg _tmp_335;
  reg _tmp_336;
  reg _tmp_337;
  assign _acc_0_sink_start = _tmp_337;
  reg _tmp_338;
  reg _tmp_339;
  reg _tmp_340;
  reg _tmp_341;
  reg _tmp_342;
  reg _tmp_343;
  reg _tmp_344;
  assign _acc_0_sink_stop = _tmp_344;
  reg _tmp_345;
  reg _tmp_346;
  reg _tmp_347;
  reg _tmp_348;
  reg _tmp_349;
  reg _tmp_350;
  reg _tmp_351;
  assign _acc_0_sink_busy = _tmp_351;
  reg _tmp_352;
  assign _acc_0_busy = _acc_0_source_busy || _acc_0_sink_busy || _acc_0_busy_reg;
  reg _tmp_353;
  reg _tmp_354;
  reg _tmp_355;
  assign _mul_rshift_round_clip_2_source_stop = _mul_rshift_round_clip_2_stream_oready && 1'd0;
  reg _tmp_356;
  reg _tmp_357;
  reg _tmp_358;
  reg _tmp_359;
  reg _tmp_360;
  reg _tmp_361;
  reg _tmp_362;
  reg _tmp_363;
  reg _tmp_364;
  reg _tmp_365;
  assign _mul_rshift_round_clip_2_sink_start = _tmp_365;
  reg _tmp_366;
  reg _tmp_367;
  reg _tmp_368;
  reg _tmp_369;
  reg _tmp_370;
  reg _tmp_371;
  reg _tmp_372;
  reg _tmp_373;
  reg _tmp_374;
  reg _tmp_375;
  assign _mul_rshift_round_clip_2_sink_stop = _tmp_375;
  reg _tmp_376;
  reg _tmp_377;
  reg _tmp_378;
  reg _tmp_379;
  reg _tmp_380;
  reg _tmp_381;
  reg _tmp_382;
  reg _tmp_383;
  reg _tmp_384;
  reg _tmp_385;
  assign _mul_rshift_round_clip_2_sink_busy = _tmp_385;
  reg _tmp_386;
  assign _mul_rshift_round_clip_2_busy = _mul_rshift_round_clip_2_source_busy || _mul_rshift_round_clip_2_sink_busy || _mul_rshift_round_clip_2_busy_reg;
  reg _tmp_387;
  reg _tmp_388;
  reg _tmp_389;
  reg _tmp_390;
  reg _tmp_391;
  reg _tmp_392;
  reg [1-1:0] __variable_wdata_84;
  assign stream_matmul_11__reduce_reset_data = __variable_wdata_84;
  reg _tmp_393;
  reg _tmp_394;
  reg _tmp_395;
  reg _tmp_396;
  assign _stream_matmul_11_source_stop = _stream_matmul_11_stream_oready && (_stream_matmul_11_source_11_idle && _stream_matmul_11_source_13_idle && _stream_matmul_11_source_15_idle && _stream_matmul_11_source_20_idle && _stream_matmul_11_source_21_idle && _stream_matmul_11_source_7_idle && _stream_matmul_11_source_9_idle && (_stream_matmul_11_fsm == 3));
  localparam _tmp_397 = 1;
  wire [_tmp_397-1:0] _tmp_398;
  assign _tmp_398 = _stream_matmul_11_source_11_idle && _stream_matmul_11_source_13_idle && _stream_matmul_11_source_15_idle && _stream_matmul_11_source_20_idle && _stream_matmul_11_source_21_idle && _stream_matmul_11_source_7_idle && _stream_matmul_11_source_9_idle && (_stream_matmul_11_fsm == 3);
  reg [_tmp_397-1:0] _tmp_399;
  localparam _tmp_400 = 1;
  wire [_tmp_400-1:0] _tmp_401;
  assign _tmp_401 = _stream_matmul_11_source_11_idle && _stream_matmul_11_source_13_idle && _stream_matmul_11_source_15_idle && _stream_matmul_11_source_20_idle && _stream_matmul_11_source_21_idle && _stream_matmul_11_source_7_idle && _stream_matmul_11_source_9_idle && (_stream_matmul_11_fsm == 3);
  reg [_tmp_400-1:0] _tmp_402;
  reg _tmp_403;
  reg _tmp_404;
  reg _tmp_405;
  reg _tmp_406;
  reg _tmp_407;
  reg _tmp_408;
  reg _tmp_409;
  reg _tmp_410;
  reg _tmp_411;
  reg _tmp_412;
  reg _tmp_413;
  reg _tmp_414;
  reg _tmp_415;
  reg _tmp_416;
  reg _tmp_417;
  reg _tmp_418;
  reg _tmp_419;
  reg _tmp_420;
  reg _tmp_421;
  reg _tmp_422;
  reg _tmp_423;
  reg _tmp_424;
  reg _tmp_425;
  reg _tmp_426;
  reg _tmp_427;
  reg _tmp_428;
  reg _tmp_429;
  reg _tmp_430;
  reg _tmp_431;
  reg _tmp_432;
  reg _tmp_433;
  assign _stream_matmul_11_sink_start = _tmp_433;
  reg _tmp_434;
  reg _tmp_435;
  reg _tmp_436;
  reg _tmp_437;
  reg _tmp_438;
  reg _tmp_439;
  reg _tmp_440;
  reg _tmp_441;
  reg _tmp_442;
  reg _tmp_443;
  reg _tmp_444;
  reg _tmp_445;
  reg _tmp_446;
  reg _tmp_447;
  reg _tmp_448;
  reg _tmp_449;
  reg _tmp_450;
  reg _tmp_451;
  reg _tmp_452;
  reg _tmp_453;
  reg _tmp_454;
  reg _tmp_455;
  reg _tmp_456;
  reg _tmp_457;
  reg _tmp_458;
  reg _tmp_459;
  reg _tmp_460;
  reg _tmp_461;
  reg _tmp_462;
  reg _tmp_463;
  reg _tmp_464;
  assign _stream_matmul_11_sink_stop = _tmp_464;
  reg _tmp_465;
  reg _tmp_466;
  reg _tmp_467;
  reg _tmp_468;
  reg _tmp_469;
  reg _tmp_470;
  reg _tmp_471;
  reg _tmp_472;
  reg _tmp_473;
  reg _tmp_474;
  reg _tmp_475;
  reg _tmp_476;
  reg _tmp_477;
  reg _tmp_478;
  reg _tmp_479;
  reg _tmp_480;
  reg _tmp_481;
  reg _tmp_482;
  reg _tmp_483;
  reg _tmp_484;
  reg _tmp_485;
  reg _tmp_486;
  reg _tmp_487;
  reg _tmp_488;
  reg _tmp_489;
  reg _tmp_490;
  reg _tmp_491;
  reg _tmp_492;
  reg _tmp_493;
  reg _tmp_494;
  reg _tmp_495;
  assign _stream_matmul_11_sink_busy = _tmp_495;
  reg _tmp_496;
  assign _stream_matmul_11_busy = _stream_matmul_11_source_busy || _stream_matmul_11_sink_busy || _stream_matmul_11_busy_reg;
  wire matmul_11_dma_out_mask_0;
  assign matmul_11_dma_out_mask_0 = matmul_11_out_row_count + 0 >= cparam_matmul_11_out_num_row;
  wire [32-1:0] _dma_write_packed_high_local_size_497;
  assign _dma_write_packed_high_local_size_497 = matmul_11_next_out_write_size >> 1;
  wire [1-1:0] _dma_write_packed_low_local_size_498;
  assign _dma_write_packed_low_local_size_498 = matmul_11_next_out_write_size & { 1{ 1'd1 } };
  wire [32-1:0] _dma_write_packed_local_packed_size_499;
  assign _dma_write_packed_local_packed_size_499 = (_dma_write_packed_low_local_size_498 > 0)? _dma_write_packed_high_local_size_497 + 1 : _dma_write_packed_high_local_size_497;
  wire [32-1:0] mask_addr_shifted_500;
  assign mask_addr_shifted_500 = matmul_11_objaddr + (matmul_11_out_base_offset + cparam_matmul_11_out_offset_values_0) + _maxi_global_base_addr >> 2;
  wire [32-1:0] mask_addr_masked_501;
  assign mask_addr_masked_501 = mask_addr_shifted_500 << 2;
  reg [32-1:0] _maxi_write_req_fsm;
  localparam _maxi_write_req_fsm_init = 0;
  reg [33-1:0] _maxi_write_cur_global_size;
  reg _maxi_write_cont;
  wire [8-1:0] pack_write_req_op_sel_502;
  wire [32-1:0] pack_write_req_local_addr_503;
  wire [32-1:0] pack_write_req_local_stride_504;
  wire [33-1:0] pack_write_req_size_505;
  wire [32-1:0] pack_write_req_local_blocksize_506;
  assign pack_write_req_op_sel_502 = _maxi_write_op_sel;
  assign pack_write_req_local_addr_503 = _maxi_write_local_addr;
  assign pack_write_req_local_stride_504 = _maxi_write_local_stride;
  assign pack_write_req_size_505 = _maxi_write_local_size;
  assign pack_write_req_local_blocksize_506 = _maxi_write_local_blocksize;
  wire [137-1:0] pack_write_req_packed_507;
  assign pack_write_req_packed_507 = { pack_write_req_op_sel_502, pack_write_req_local_addr_503, pack_write_req_local_stride_504, pack_write_req_size_505, pack_write_req_local_blocksize_506 };
  localparam _tmp_508 = 1;
  wire [_tmp_508-1:0] _tmp_509;
  assign _tmp_509 = !_maxi_write_req_fifo_almost_full;
  reg [_tmp_508-1:0] __tmp_509_1;
  wire [32-1:0] mask_addr_shifted_510;
  assign mask_addr_shifted_510 = _maxi_write_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_511;
  assign mask_addr_masked_511 = mask_addr_shifted_510 << 2;
  wire [32-1:0] mask_addr_shifted_512;
  assign mask_addr_shifted_512 = _maxi_write_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_513;
  assign mask_addr_masked_513 = mask_addr_shifted_512 << 2;
  wire [32-1:0] mask_addr_shifted_514;
  assign mask_addr_shifted_514 = _maxi_write_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_515;
  assign mask_addr_masked_515 = mask_addr_shifted_514 << 2;
  wire [32-1:0] mask_addr_shifted_516;
  assign mask_addr_shifted_516 = _maxi_write_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_517;
  assign mask_addr_masked_517 = mask_addr_shifted_516 << 2;
  wire [32-1:0] mask_addr_shifted_518;
  assign mask_addr_shifted_518 = _maxi_write_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_519;
  assign mask_addr_masked_519 = mask_addr_shifted_518 << 2;
  wire [32-1:0] mask_addr_shifted_520;
  assign mask_addr_shifted_520 = _maxi_write_global_addr >> 2;
  wire [32-1:0] mask_addr_masked_521;
  assign mask_addr_masked_521 = mask_addr_shifted_520 << 2;
  wire [8-1:0] pack_write_req_op_sel_522;
  wire [32-1:0] pack_write_req_local_addr_523;
  wire [32-1:0] pack_write_req_local_stride_524;
  wire [33-1:0] pack_write_req_size_525;
  wire [32-1:0] pack_write_req_local_blocksize_526;
  assign pack_write_req_op_sel_522 = _maxi_write_op_sel;
  assign pack_write_req_local_addr_523 = _maxi_write_local_addr;
  assign pack_write_req_local_stride_524 = _maxi_write_local_stride;
  assign pack_write_req_size_525 = _maxi_write_cur_global_size;
  assign pack_write_req_local_blocksize_526 = _maxi_write_local_blocksize;
  wire [137-1:0] pack_write_req_packed_527;
  assign pack_write_req_packed_527 = { pack_write_req_op_sel_522, pack_write_req_local_addr_523, pack_write_req_local_stride_524, pack_write_req_size_525, pack_write_req_local_blocksize_526 };
  assign _maxi_write_req_fifo_wdata = ((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6))? pack_write_req_packed_527 : 
                                      ((_maxi_write_req_fsm == 0) && _maxi_write_start && !_maxi_write_req_fifo_almost_full)? pack_write_req_packed_507 : 'hx;
  assign _maxi_write_req_fifo_enq = ((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6))? (_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6) && !_maxi_write_req_fifo_almost_full : 
                                    ((_maxi_write_req_fsm == 0) && _maxi_write_start && !_maxi_write_req_fifo_almost_full)? (_maxi_write_req_fsm == 0) && _maxi_write_start && !_maxi_write_req_fifo_almost_full && !_maxi_write_req_fifo_almost_full : 0;
  localparam _tmp_528 = 1;
  wire [_tmp_528-1:0] _tmp_529;
  assign _tmp_529 = !_maxi_write_req_fifo_almost_full;
  reg [_tmp_528-1:0] __tmp_529_1;
  reg _maxi_waddr_cond_0_1;
  reg [32-1:0] _maxi_write_data_fsm;
  localparam _maxi_write_data_fsm_init = 0;
  reg [32-1:0] read_burst_packed_fsm_4;
  localparam read_burst_packed_fsm_4_init = 0;
  reg [9-1:0] read_burst_packed_addr_530;
  reg [9-1:0] read_burst_packed_stride_531;
  reg [33-1:0] read_burst_packed_length_532;
  reg read_burst_packed_rvalid_533;
  reg read_burst_packed_rlast_534;
  wire [8-1:0] read_burst_packed_ram_addr_535;
  assign read_burst_packed_ram_addr_535 = read_burst_packed_addr_530 >> 1;
  assign ram_w16_l512_id1_0_1_addr = ((read_burst_packed_fsm_4 == 1) && (!read_burst_packed_rvalid_533 || (_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0)))? read_burst_packed_ram_addr_535 : 'hx;
  assign ram_w16_l512_id1_0_1_enable = ((read_burst_packed_fsm_4 == 1) && (!read_burst_packed_rvalid_533 || (_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0)))? 1'd1 : 0;
  localparam _tmp_536 = 1;
  wire [_tmp_536-1:0] _tmp_537;
  assign _tmp_537 = (read_burst_packed_fsm_4 == 1) && (!read_burst_packed_rvalid_533 || (_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0));
  reg [_tmp_536-1:0] __tmp_537_1;
  wire [16-1:0] read_burst_packed_ram_rdata_538;
  assign read_burst_packed_ram_rdata_538 = ram_w16_l512_id1_0_1_rdata;
  wire [8-1:0] read_burst_packed_ram_addr_539;
  assign read_burst_packed_ram_addr_539 = read_burst_packed_addr_530 >> 1;
  assign ram_w16_l512_id1_1_1_addr = ((read_burst_packed_fsm_4 == 1) && (!read_burst_packed_rvalid_533 || (_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0)))? read_burst_packed_ram_addr_539 : 'hx;
  assign ram_w16_l512_id1_1_1_enable = ((read_burst_packed_fsm_4 == 1) && (!read_burst_packed_rvalid_533 || (_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0)))? 1'd1 : 0;
  localparam _tmp_540 = 1;
  wire [_tmp_540-1:0] _tmp_541;
  assign _tmp_541 = (read_burst_packed_fsm_4 == 1) && (!read_burst_packed_rvalid_533 || (_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0));
  reg [_tmp_540-1:0] __tmp_541_1;
  wire [16-1:0] read_burst_packed_ram_rdata_542;
  assign read_burst_packed_ram_rdata_542 = ram_w16_l512_id1_1_1_rdata;
  wire [32-1:0] read_burst_packed_rdata_543;
  assign read_burst_packed_rdata_543 = { read_burst_packed_ram_rdata_542, read_burst_packed_ram_rdata_538 };
  assign _maxi_write_req_fifo_deq = ((_maxi_write_data_fsm == 2) && (!_maxi_write_req_fifo_empty && (_maxi_write_size_buf == 0)) && !_maxi_write_req_fifo_empty)? 1 : 
                                    ((_maxi_write_data_fsm == 0) && (!_maxi_write_data_busy && !_maxi_write_req_fifo_empty && (_maxi_write_op_sel_fifo == 1)) && !_maxi_write_req_fifo_empty)? 1 : 0;
  reg _maxi_wdata_cond_0_1;
  wire matmul_11_update_filter;
  assign matmul_11_update_filter = (cparam_matmul_11_data_stationary == 0) && (matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count) || (cparam_matmul_11_data_stationary == 1) && !cparam_matmul_11_keep_filter;
  wire matmul_11_update_act;
  assign matmul_11_update_act = (cparam_matmul_11_data_stationary == 1) && (matmul_11_och_count >= cparam_matmul_11_max_och_count) || (cparam_matmul_11_data_stationary == 0);
  wire matmul_11_mux_next_dma_flag_0;
  assign matmul_11_mux_next_dma_flag_0 = (matmul_11_row_select == 0)? (matmul_11_row_count >= cparam_matmul_11_max_row_count)? 1 : cparam_matmul_11_dma_flag_conds_0 : 1'd0;

  always @(posedge CLK) begin
    _RESETN_inv_1 <= RESETN_inv;
    _RESETN_inv_2 <= _RESETN_inv_1;
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      maxi_awaddr <= 0;
      maxi_awlen <= 0;
      maxi_awvalid <= 0;
      _maxi_waddr_cond_0_1 <= 0;
    end else begin
      if(_maxi_waddr_cond_0_1) begin
        maxi_awvalid <= 0;
      end 
      if((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (_maxi_outstanding_wcount < 6) && ((_maxi_outstanding_wcount < 6) && (maxi_awready || !maxi_awvalid))) begin
        maxi_awaddr <= _maxi_write_global_addr;
        maxi_awlen <= _maxi_write_cur_global_size - 1;
        maxi_awvalid <= 1;
      end 
      if((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (_maxi_outstanding_wcount < 6) && ((_maxi_outstanding_wcount < 6) && (maxi_awready || !maxi_awvalid)) && (_maxi_write_cur_global_size == 0)) begin
        maxi_awvalid <= 0;
      end 
      _maxi_waddr_cond_0_1 <= 1;
      if(maxi_awvalid && !maxi_awready) begin
        maxi_awvalid <= maxi_awvalid;
      end 
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _maxi_wdata_sb_0 <= 0;
      _maxi_wvalid_sb_0 <= 0;
      _maxi_wlast_sb_0 <= 0;
      _maxi_wstrb_sb_0 <= 0;
      _maxi_wdata_cond_0_1 <= 0;
    end else begin
      if(_maxi_wdata_cond_0_1) begin
        _maxi_wvalid_sb_0 <= 0;
        _maxi_wlast_sb_0 <= 0;
      end 
      if((_maxi_write_op_sel_buf == 1) && read_burst_packed_rvalid_533 && ((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0)) && (_maxi_wready_sb_0 || !_maxi_wvalid_sb_0)) begin
        _maxi_wdata_sb_0 <= read_burst_packed_rdata_543;
        _maxi_wvalid_sb_0 <= 1;
        _maxi_wlast_sb_0 <= read_burst_packed_rlast_534 || (_maxi_write_size_buf == 1);
        _maxi_wstrb_sb_0 <= { 4{ 1'd1 } };
      end 
      _maxi_wdata_cond_0_1 <= 1;
      if(_maxi_wvalid_sb_0 && !_maxi_wready_sb_0) begin
        _maxi_wvalid_sb_0 <= _maxi_wvalid_sb_0;
        _maxi_wlast_sb_0 <= _maxi_wlast_sb_0;
      end 
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _sb_maxi_writedata_data_6 <= 0;
      _sb_maxi_writedata_valid_7 <= 0;
      _sb_maxi_writedata_tmp_data_9 <= 0;
      _sb_maxi_writedata_tmp_valid_10 <= 0;
    end else begin
      if(_sb_maxi_writedata_m_ready_5 || !_sb_maxi_writedata_valid_7) begin
        _sb_maxi_writedata_data_6 <= _sb_maxi_writedata_next_data_11;
        _sb_maxi_writedata_valid_7 <= _sb_maxi_writedata_next_valid_12;
      end 
      if(!_sb_maxi_writedata_tmp_valid_10 && _sb_maxi_writedata_valid_7 && !_sb_maxi_writedata_m_ready_5) begin
        _sb_maxi_writedata_tmp_data_9 <= _sb_maxi_writedata_s_data_3;
        _sb_maxi_writedata_tmp_valid_10 <= _sb_maxi_writedata_s_valid_4;
      end 
      if(_sb_maxi_writedata_tmp_valid_10 && _sb_maxi_writedata_m_ready_5) begin
        _sb_maxi_writedata_tmp_valid_10 <= 0;
      end 
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      maxi_araddr <= 0;
      maxi_arlen <= 0;
      maxi_arvalid <= 0;
      _maxi_raddr_cond_0_1 <= 0;
    end else begin
      if(_maxi_raddr_cond_0_1) begin
        maxi_arvalid <= 0;
      end 
      if((_maxi_read_req_fsm == 1) && (maxi_arready || !maxi_arvalid)) begin
        maxi_araddr <= _maxi_read_global_addr;
        maxi_arlen <= _maxi_read_cur_global_size - 1;
        maxi_arvalid <= 1;
      end 
      _maxi_raddr_cond_0_1 <= 1;
      if(maxi_arvalid && !maxi_arready) begin
        maxi_arvalid <= maxi_arvalid;
      end 
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _sb_maxi_readdata_data_21 <= 0;
      _sb_maxi_readdata_valid_22 <= 0;
      _sb_maxi_readdata_tmp_data_24 <= 0;
      _sb_maxi_readdata_tmp_valid_25 <= 0;
    end else begin
      if(_sb_maxi_readdata_m_ready_20 || !_sb_maxi_readdata_valid_22) begin
        _sb_maxi_readdata_data_21 <= _sb_maxi_readdata_next_data_26;
        _sb_maxi_readdata_valid_22 <= _sb_maxi_readdata_next_valid_27;
      end 
      if(!_sb_maxi_readdata_tmp_valid_25 && _sb_maxi_readdata_valid_22 && !_sb_maxi_readdata_m_ready_20) begin
        _sb_maxi_readdata_tmp_data_24 <= _sb_maxi_readdata_s_data_18;
        _sb_maxi_readdata_tmp_valid_25 <= _sb_maxi_readdata_s_valid_19;
      end 
      if(_sb_maxi_readdata_tmp_valid_25 && _sb_maxi_readdata_m_ready_20) begin
        _sb_maxi_readdata_tmp_valid_25 <= 0;
      end 
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _maxi_outstanding_wcount <= 0;
      _maxi_read_start <= 0;
      _maxi_write_start <= 0;
      _maxi_global_base_addr <= 0;
      _maxi_read_op_sel <= 0;
      _maxi_read_global_addr <= 0;
      _maxi_read_global_size <= 0;
      _maxi_read_local_addr <= 0;
      _maxi_read_local_stride <= 0;
      _maxi_read_local_size <= 0;
      _maxi_read_local_blocksize <= 0;
      _maxi_read_req_busy <= 0;
      _maxi_read_cur_global_size <= 0;
      _maxi_read_data_busy <= 0;
      _maxi_read_op_sel_buf <= 0;
      _maxi_read_local_addr_buf <= 0;
      _maxi_read_local_stride_buf <= 0;
      _maxi_read_local_size_buf <= 0;
      _maxi_read_local_blocksize_buf <= 0;
      _maxi_write_op_sel <= 0;
      _maxi_write_global_addr <= 0;
      _maxi_write_global_size <= 0;
      _maxi_write_local_addr <= 0;
      _maxi_write_local_stride <= 0;
      _maxi_write_local_size <= 0;
      _maxi_write_local_blocksize <= 0;
      _maxi_write_req_busy <= 0;
      _maxi_write_cur_global_size <= 0;
      _maxi_write_data_busy <= 0;
      _maxi_write_op_sel_buf <= 0;
      _maxi_write_local_addr_buf <= 0;
      _maxi_write_local_stride_buf <= 0;
      _maxi_write_size_buf <= 0;
      _maxi_write_local_blocksize_buf <= 0;
    end else begin
      if(maxi_awvalid && maxi_awready && !(maxi_bvalid && maxi_bready) && (_maxi_outstanding_wcount < 7)) begin
        _maxi_outstanding_wcount <= _maxi_outstanding_wcount + 1;
      end 
      if(!(maxi_awvalid && maxi_awready) && (maxi_bvalid && maxi_bready) && (_maxi_outstanding_wcount > 0)) begin
        _maxi_outstanding_wcount <= _maxi_outstanding_wcount - 1;
      end 
      _maxi_read_start <= 0;
      _maxi_write_start <= 0;
      _maxi_global_base_addr <= _saxi_register_32;
      if((control_matmul_11 == 2) && _maxi_read_req_idle) begin
        _maxi_read_start <= 1;
        _maxi_read_op_sel <= 1;
        _maxi_read_global_addr <= mask_addr_masked_58;
        _maxi_read_global_size <= _dma_read_packed_local_packed_size_56;
        _maxi_read_local_addr <= 0;
        _maxi_read_local_stride <= 2;
        _maxi_read_local_size <= _dma_read_packed_local_packed_size_56;
        _maxi_read_local_blocksize <= 1;
      end 
      if((_maxi_read_req_fsm == 0) && _maxi_read_start) begin
        _maxi_read_req_busy <= 1;
      end 
      if(_maxi_read_start && _maxi_read_req_fifo_almost_full) begin
        _maxi_read_start <= 1;
      end 
      if((_maxi_read_req_fsm == 0) && (_maxi_read_start || _maxi_read_cont) && !_maxi_read_req_fifo_almost_full && (_maxi_read_global_size <= 256) && ((mask_addr_masked_68 & 4095) + (_maxi_read_global_size << 2) >= 4096)) begin
        _maxi_read_cur_global_size <= 4096 - (mask_addr_masked_70 & 4095) >> 2;
        _maxi_read_global_size <= _maxi_read_global_size - (4096 - (mask_addr_masked_72 & 4095) >> 2);
      end else if((_maxi_read_req_fsm == 0) && (_maxi_read_start || _maxi_read_cont) && !_maxi_read_req_fifo_almost_full && (_maxi_read_global_size <= 256)) begin
        _maxi_read_cur_global_size <= _maxi_read_global_size;
        _maxi_read_global_size <= 0;
      end else if((_maxi_read_req_fsm == 0) && (_maxi_read_start || _maxi_read_cont) && !_maxi_read_req_fifo_almost_full && ((mask_addr_masked_74 & 4095) + 1024 >= 4096)) begin
        _maxi_read_cur_global_size <= 4096 - (mask_addr_masked_76 & 4095) >> 2;
        _maxi_read_global_size <= _maxi_read_global_size - (4096 - (mask_addr_masked_78 & 4095) >> 2);
      end else if((_maxi_read_req_fsm == 0) && (_maxi_read_start || _maxi_read_cont) && !_maxi_read_req_fifo_almost_full) begin
        _maxi_read_cur_global_size <= 256;
        _maxi_read_global_size <= _maxi_read_global_size - 256;
      end 
      if((_maxi_read_req_fsm == 1) && (maxi_arready || !maxi_arvalid)) begin
        _maxi_read_global_addr <= _maxi_read_global_addr + (_maxi_read_cur_global_size << 2);
      end 
      if((_maxi_read_req_fsm == 1) && (maxi_arready || !maxi_arvalid) && (_maxi_read_global_size == 0)) begin
        _maxi_read_req_busy <= 0;
      end 
      if((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 1))) begin
        _maxi_read_data_busy <= 1;
        _maxi_read_op_sel_buf <= _maxi_read_op_sel_fifo;
        _maxi_read_local_addr_buf <= _maxi_read_local_addr_fifo;
        _maxi_read_local_stride_buf <= _maxi_read_local_stride_fifo;
        _maxi_read_local_size_buf <= _maxi_read_local_size_fifo;
        _maxi_read_local_blocksize_buf <= _maxi_read_local_blocksize_fifo;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0) begin
        _maxi_read_local_size_buf <= _maxi_read_local_size_buf - 1;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
        _maxi_read_data_busy <= 0;
      end 
      if((control_matmul_11 == 4) && _maxi_read_req_idle) begin
        _maxi_read_start <= 1;
        _maxi_read_op_sel <= 2;
        _maxi_read_global_addr <= mask_addr_masked_91;
        _maxi_read_global_size <= _dma_read_packed_local_packed_size_89;
        _maxi_read_local_addr <= 0;
        _maxi_read_local_stride <= 2;
        _maxi_read_local_size <= _dma_read_packed_local_packed_size_89;
        _maxi_read_local_blocksize <= 1;
      end 
      if((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 2))) begin
        _maxi_read_data_busy <= 1;
        _maxi_read_op_sel_buf <= _maxi_read_op_sel_fifo;
        _maxi_read_local_addr_buf <= _maxi_read_local_addr_fifo;
        _maxi_read_local_stride_buf <= _maxi_read_local_stride_fifo;
        _maxi_read_local_size_buf <= _maxi_read_local_size_fifo;
        _maxi_read_local_blocksize_buf <= _maxi_read_local_blocksize_fifo;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0) begin
        _maxi_read_local_size_buf <= _maxi_read_local_size_buf - 1;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
        _maxi_read_data_busy <= 0;
      end 
      if((control_matmul_11 == 8) && _maxi_read_req_idle) begin
        _maxi_read_start <= 1;
        _maxi_read_op_sel <= 3;
        _maxi_read_global_addr <= mask_addr_masked_104;
        _maxi_read_global_size <= _dma_read_packed_local_packed_size_102;
        _maxi_read_local_addr <= matmul_11_filter_page_dma_offset;
        _maxi_read_local_stride <= 2;
        _maxi_read_local_size <= _dma_read_packed_local_packed_size_102;
        _maxi_read_local_blocksize <= 1;
      end 
      if((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 3))) begin
        _maxi_read_data_busy <= 1;
        _maxi_read_op_sel_buf <= _maxi_read_op_sel_fifo;
        _maxi_read_local_addr_buf <= _maxi_read_local_addr_fifo;
        _maxi_read_local_stride_buf <= _maxi_read_local_stride_fifo;
        _maxi_read_local_size_buf <= _maxi_read_local_size_fifo;
        _maxi_read_local_blocksize_buf <= _maxi_read_local_blocksize_fifo;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0) begin
        _maxi_read_local_size_buf <= _maxi_read_local_size_buf - 1;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
        _maxi_read_data_busy <= 0;
      end 
      if((control_matmul_11 == 14) && _maxi_read_req_idle) begin
        _maxi_read_start <= 1;
        _maxi_read_op_sel <= 4;
        _maxi_read_global_addr <= mask_addr_masked_117;
        _maxi_read_global_size <= _dma_read_packed_local_packed_size_115;
        _maxi_read_local_addr <= matmul_11_act_page_dma_offset_0;
        _maxi_read_local_stride <= 2;
        _maxi_read_local_size <= _dma_read_packed_local_packed_size_115;
        _maxi_read_local_blocksize <= 1;
      end 
      if((_maxi_read_data_fsm == 0) && (!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 4))) begin
        _maxi_read_data_busy <= 1;
        _maxi_read_op_sel_buf <= _maxi_read_op_sel_fifo;
        _maxi_read_local_addr_buf <= _maxi_read_local_addr_fifo;
        _maxi_read_local_stride_buf <= _maxi_read_local_stride_fifo;
        _maxi_read_local_size_buf <= _maxi_read_local_size_fifo;
        _maxi_read_local_blocksize_buf <= _maxi_read_local_blocksize_fifo;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0) begin
        _maxi_read_local_size_buf <= _maxi_read_local_size_buf - 1;
      end 
      if((_maxi_read_data_fsm == 2) && _maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
        _maxi_read_data_busy <= 0;
      end 
      if((control_matmul_11 == 23) && _maxi_write_req_idle) begin
        _maxi_write_start <= 1;
        _maxi_write_op_sel <= 1;
        _maxi_write_global_addr <= mask_addr_masked_501;
        _maxi_write_global_size <= _dma_write_packed_local_packed_size_499;
        _maxi_write_local_addr <= matmul_11_out_laddr_offset + matmul_11_out_page_dma_offset;
        _maxi_write_local_stride <= 2;
        _maxi_write_local_size <= _dma_write_packed_local_packed_size_499;
        _maxi_write_local_blocksize <= 1;
      end 
      if((_maxi_write_req_fsm == 0) && _maxi_write_start) begin
        _maxi_write_req_busy <= 1;
      end 
      if(_maxi_write_start && _maxi_write_req_fifo_almost_full) begin
        _maxi_write_start <= 1;
      end 
      if((_maxi_write_req_fsm == 0) && (_maxi_write_start || _maxi_write_cont) && !_maxi_write_req_fifo_almost_full && (_maxi_write_global_size <= 256) && ((mask_addr_masked_511 & 4095) + (_maxi_write_global_size << 2) >= 4096)) begin
        _maxi_write_cur_global_size <= 4096 - (mask_addr_masked_513 & 4095) >> 2;
        _maxi_write_global_size <= _maxi_write_global_size - (4096 - (mask_addr_masked_515 & 4095) >> 2);
      end else if((_maxi_write_req_fsm == 0) && (_maxi_write_start || _maxi_write_cont) && !_maxi_write_req_fifo_almost_full && (_maxi_write_global_size <= 256)) begin
        _maxi_write_cur_global_size <= _maxi_write_global_size;
        _maxi_write_global_size <= 0;
      end else if((_maxi_write_req_fsm == 0) && (_maxi_write_start || _maxi_write_cont) && !_maxi_write_req_fifo_almost_full && ((mask_addr_masked_517 & 4095) + 1024 >= 4096)) begin
        _maxi_write_cur_global_size <= 4096 - (mask_addr_masked_519 & 4095) >> 2;
        _maxi_write_global_size <= _maxi_write_global_size - (4096 - (mask_addr_masked_521 & 4095) >> 2);
      end else if((_maxi_write_req_fsm == 0) && (_maxi_write_start || _maxi_write_cont) && !_maxi_write_req_fifo_almost_full) begin
        _maxi_write_cur_global_size <= 256;
        _maxi_write_global_size <= _maxi_write_global_size - 256;
      end 
      if((_maxi_write_req_fsm == 1) && ((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6))) begin
        _maxi_write_global_addr <= _maxi_write_global_addr + (_maxi_write_cur_global_size << 2);
      end 
      if((_maxi_write_req_fsm == 1) && ((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6)) && (_maxi_write_global_size == 0)) begin
        _maxi_write_req_busy <= 0;
      end 
      if((_maxi_write_data_fsm == 0) && (!_maxi_write_data_busy && !_maxi_write_req_fifo_empty && (_maxi_write_op_sel_fifo == 1))) begin
        _maxi_write_data_busy <= 1;
        _maxi_write_op_sel_buf <= _maxi_write_op_sel_fifo;
        _maxi_write_local_addr_buf <= _maxi_write_local_addr_fifo;
        _maxi_write_local_stride_buf <= _maxi_write_local_stride_fifo;
        _maxi_write_size_buf <= _maxi_write_size_fifo;
        _maxi_write_local_blocksize_buf <= _maxi_write_local_blocksize_fifo;
      end 
      if(_maxi_write_data_fsm == 1) begin
        _maxi_write_size_buf <= 0;
      end 
      if((_maxi_write_data_fsm == 2) && (!_maxi_write_req_fifo_empty && (_maxi_write_size_buf == 0))) begin
        _maxi_write_size_buf <= _maxi_write_size_fifo;
      end 
      if((_maxi_write_data_fsm == 2) && read_burst_packed_rvalid_533 && ((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0))) begin
        _maxi_write_size_buf <= _maxi_write_size_buf - 1;
      end 
      if((_maxi_write_data_fsm == 2) && ((_maxi_write_op_sel_buf == 1) && read_burst_packed_rvalid_533 && ((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0))) && read_burst_packed_rlast_534) begin
        _maxi_write_data_busy <= 0;
      end 
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      count__maxi_read_req_fifo <= 0;
      __tmp_66_1 <= 0;
    end else begin
      if(_maxi_read_req_fifo_enq && !_maxi_read_req_fifo_full && (_maxi_read_req_fifo_deq && !_maxi_read_req_fifo_empty)) begin
        count__maxi_read_req_fifo <= count__maxi_read_req_fifo;
      end else if(_maxi_read_req_fifo_enq && !_maxi_read_req_fifo_full) begin
        count__maxi_read_req_fifo <= count__maxi_read_req_fifo + 1;
      end else if(_maxi_read_req_fifo_deq && !_maxi_read_req_fifo_empty) begin
        count__maxi_read_req_fifo <= count__maxi_read_req_fifo - 1;
      end 
      __tmp_66_1 <= _tmp_66;
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      count__maxi_write_req_fifo <= 0;
      __tmp_509_1 <= 0;
      __tmp_529_1 <= 0;
    end else begin
      if(_maxi_write_req_fifo_enq && !_maxi_write_req_fifo_full && (_maxi_write_req_fifo_deq && !_maxi_write_req_fifo_empty)) begin
        count__maxi_write_req_fifo <= count__maxi_write_req_fifo;
      end else if(_maxi_write_req_fifo_enq && !_maxi_write_req_fifo_full) begin
        count__maxi_write_req_fifo <= count__maxi_write_req_fifo + 1;
      end else if(_maxi_write_req_fifo_deq && !_maxi_write_req_fifo_empty) begin
        count__maxi_write_req_fifo <= count__maxi_write_req_fifo - 1;
      end 
      __tmp_509_1 <= _tmp_509;
      __tmp_529_1 <= _tmp_529;
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      saxi_rdata <= 0;
      saxi_rvalid <= 0;
      _saxi_rdata_cond_0_1 <= 0;
    end else begin
      if(_saxi_rdata_cond_0_1) begin
        saxi_rvalid <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid)) begin
        saxi_rdata <= axislite_rdata_46;
        saxi_rvalid <= 1;
      end 
      _saxi_rdata_cond_0_1 <= 1;
      if(saxi_rvalid && !saxi_rready) begin
        saxi_rvalid <= saxi_rvalid;
      end 
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      saxi_bvalid <= 0;
      prev_awvalid_43 <= 0;
      prev_arvalid_44 <= 0;
      writevalid_41 <= 0;
      readvalid_42 <= 0;
      addr_40 <= 0;
      _saxi_register_0 <= 0;
      _saxi_flag_0 <= 0;
      _saxi_register_1 <= 0;
      _saxi_flag_1 <= 0;
      _saxi_register_2 <= 0;
      _saxi_flag_2 <= 0;
      _saxi_register_3 <= 0;
      _saxi_flag_3 <= 0;
      _saxi_register_4 <= 0;
      _saxi_flag_4 <= 0;
      _saxi_register_5 <= 0;
      _saxi_flag_5 <= 0;
      _saxi_register_6 <= 0;
      _saxi_flag_6 <= 0;
      _saxi_register_7 <= 0;
      _saxi_flag_7 <= 0;
      _saxi_register_8 <= 0;
      _saxi_flag_8 <= 0;
      _saxi_register_9 <= 0;
      _saxi_flag_9 <= 0;
      _saxi_register_10 <= 0;
      _saxi_flag_10 <= 0;
      _saxi_register_11 <= 0;
      _saxi_flag_11 <= 0;
      _saxi_register_12 <= 0;
      _saxi_flag_12 <= 0;
      _saxi_register_13 <= 0;
      _saxi_flag_13 <= 0;
      _saxi_register_14 <= 0;
      _saxi_flag_14 <= 0;
      _saxi_register_15 <= 0;
      _saxi_flag_15 <= 0;
      _saxi_register_16 <= 0;
      _saxi_flag_16 <= 0;
      _saxi_register_17 <= 0;
      _saxi_flag_17 <= 0;
      _saxi_register_18 <= 0;
      _saxi_flag_18 <= 0;
      _saxi_register_19 <= 0;
      _saxi_flag_19 <= 0;
      _saxi_register_20 <= 0;
      _saxi_flag_20 <= 0;
      _saxi_register_21 <= 0;
      _saxi_flag_21 <= 0;
      _saxi_register_22 <= 0;
      _saxi_flag_22 <= 0;
      _saxi_register_23 <= 0;
      _saxi_flag_23 <= 0;
      _saxi_register_24 <= 0;
      _saxi_flag_24 <= 0;
      _saxi_register_25 <= 0;
      _saxi_flag_25 <= 0;
      _saxi_register_26 <= 0;
      _saxi_flag_26 <= 0;
      _saxi_register_27 <= 0;
      _saxi_flag_27 <= 0;
      _saxi_register_28 <= 0;
      _saxi_flag_28 <= 0;
      _saxi_register_29 <= 0;
      _saxi_flag_29 <= 0;
      _saxi_register_30 <= 0;
      _saxi_flag_30 <= 0;
      _saxi_register_31 <= 1088;
      _saxi_flag_31 <= 0;
      _saxi_register_32 <= 0;
      _saxi_flag_32 <= 0;
      _saxi_register_33 <= 960;
      _saxi_flag_33 <= 0;
      _saxi_register_34 <= 0;
      _saxi_flag_34 <= 0;
      _saxi_register_35 <= 64;
      _saxi_flag_35 <= 0;
      _saxi_register_36 <= 128;
      _saxi_flag_36 <= 0;
      _saxi_register_11[0] <= (0 >> 0) & 1'd1;
      _saxi_register_9[0] <= (0 >> 0) & 1'd1;
      _saxi_register_11[1] <= (0 >> 1) & 1'd1;
      _saxi_register_9[1] <= (0 >> 1) & 1'd1;
      _saxi_register_11[2] <= (0 >> 2) & 1'd1;
      _saxi_register_9[2] <= (0 >> 2) & 1'd1;
      _saxi_register_11[3] <= (0 >> 3) & 1'd1;
      _saxi_register_9[3] <= (0 >> 3) & 1'd1;
      _saxi_register_11[4] <= (0 >> 4) & 1'd1;
      _saxi_register_9[4] <= (0 >> 4) & 1'd1;
      _saxi_register_11[5] <= (0 >> 5) & 1'd1;
      _saxi_register_9[5] <= (0 >> 5) & 1'd1;
      _saxi_register_11[6] <= (0 >> 6) & 1'd1;
      _saxi_register_9[6] <= (0 >> 6) & 1'd1;
      _saxi_register_11[7] <= (0 >> 7) & 1'd1;
      _saxi_register_9[7] <= (0 >> 7) & 1'd1;
      _saxi_register_11[8] <= (0 >> 8) & 1'd1;
      _saxi_register_9[8] <= (0 >> 8) & 1'd1;
      _saxi_register_11[9] <= (0 >> 9) & 1'd1;
      _saxi_register_9[9] <= (0 >> 9) & 1'd1;
      _saxi_register_11[10] <= (0 >> 10) & 1'd1;
      _saxi_register_9[10] <= (0 >> 10) & 1'd1;
      _saxi_register_11[11] <= (0 >> 11) & 1'd1;
      _saxi_register_9[11] <= (0 >> 11) & 1'd1;
      _saxi_register_11[12] <= (0 >> 12) & 1'd1;
      _saxi_register_9[12] <= (0 >> 12) & 1'd1;
      _saxi_register_11[13] <= (0 >> 13) & 1'd1;
      _saxi_register_9[13] <= (0 >> 13) & 1'd1;
      _saxi_register_11[14] <= (0 >> 14) & 1'd1;
      _saxi_register_9[14] <= (0 >> 14) & 1'd1;
      _saxi_register_11[15] <= (0 >> 15) & 1'd1;
      _saxi_register_9[15] <= (0 >> 15) & 1'd1;
      _saxi_register_11[16] <= (0 >> 16) & 1'd1;
      _saxi_register_9[16] <= (0 >> 16) & 1'd1;
      _saxi_register_11[17] <= (0 >> 17) & 1'd1;
      _saxi_register_9[17] <= (0 >> 17) & 1'd1;
      _saxi_register_11[18] <= (0 >> 18) & 1'd1;
      _saxi_register_9[18] <= (0 >> 18) & 1'd1;
      _saxi_register_11[19] <= (0 >> 19) & 1'd1;
      _saxi_register_9[19] <= (0 >> 19) & 1'd1;
      _saxi_register_11[20] <= (0 >> 20) & 1'd1;
      _saxi_register_9[20] <= (0 >> 20) & 1'd1;
      _saxi_register_11[21] <= (0 >> 21) & 1'd1;
      _saxi_register_9[21] <= (0 >> 21) & 1'd1;
      _saxi_register_11[22] <= (0 >> 22) & 1'd1;
      _saxi_register_9[22] <= (0 >> 22) & 1'd1;
      _saxi_register_11[23] <= (0 >> 23) & 1'd1;
      _saxi_register_9[23] <= (0 >> 23) & 1'd1;
      _saxi_register_11[24] <= (0 >> 24) & 1'd1;
      _saxi_register_9[24] <= (0 >> 24) & 1'd1;
      _saxi_register_11[25] <= (0 >> 25) & 1'd1;
      _saxi_register_9[25] <= (0 >> 25) & 1'd1;
      _saxi_register_11[26] <= (0 >> 26) & 1'd1;
      _saxi_register_9[26] <= (0 >> 26) & 1'd1;
      _saxi_register_11[27] <= (0 >> 27) & 1'd1;
      _saxi_register_9[27] <= (0 >> 27) & 1'd1;
      _saxi_register_11[28] <= (0 >> 28) & 1'd1;
      _saxi_register_9[28] <= (0 >> 28) & 1'd1;
      _saxi_register_11[29] <= (0 >> 29) & 1'd1;
      _saxi_register_9[29] <= (0 >> 29) & 1'd1;
      _saxi_register_11[30] <= (0 >> 30) & 1'd1;
      _saxi_register_9[30] <= (0 >> 30) & 1'd1;
      _saxi_register_11[31] <= (0 >> 31) & 1'd1;
      _saxi_register_9[31] <= (0 >> 31) & 1'd1;
      internal_state_counter <= 0;
    end else begin
      if(saxi_bvalid && saxi_bready) begin
        saxi_bvalid <= 0;
      end 
      if(saxi_wvalid && saxi_wready) begin
        saxi_bvalid <= 1;
      end 
      prev_awvalid_43 <= saxi_awvalid;
      prev_arvalid_44 <= saxi_arvalid;
      writevalid_41 <= 0;
      readvalid_42 <= 0;
      if(saxi_awready && saxi_awvalid && !saxi_bvalid) begin
        addr_40 <= saxi_awaddr;
        writevalid_41 <= 1;
      end else if(saxi_arready && saxi_arvalid) begin
        addr_40 <= saxi_araddr;
        readvalid_42 <= 1;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 0)) begin
        _saxi_register_0 <= axislite_resetval_48;
        _saxi_flag_0 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 1)) begin
        _saxi_register_1 <= axislite_resetval_48;
        _saxi_flag_1 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 2)) begin
        _saxi_register_2 <= axislite_resetval_48;
        _saxi_flag_2 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 3)) begin
        _saxi_register_3 <= axislite_resetval_48;
        _saxi_flag_3 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 4)) begin
        _saxi_register_4 <= axislite_resetval_48;
        _saxi_flag_4 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 5)) begin
        _saxi_register_5 <= axislite_resetval_48;
        _saxi_flag_5 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 6)) begin
        _saxi_register_6 <= axislite_resetval_48;
        _saxi_flag_6 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 7)) begin
        _saxi_register_7 <= axislite_resetval_48;
        _saxi_flag_7 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 8)) begin
        _saxi_register_8 <= axislite_resetval_48;
        _saxi_flag_8 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 9)) begin
        _saxi_register_9 <= axislite_resetval_48;
        _saxi_flag_9 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 10)) begin
        _saxi_register_10 <= axislite_resetval_48;
        _saxi_flag_10 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 11)) begin
        _saxi_register_11 <= axislite_resetval_48;
        _saxi_flag_11 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 12)) begin
        _saxi_register_12 <= axislite_resetval_48;
        _saxi_flag_12 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 13)) begin
        _saxi_register_13 <= axislite_resetval_48;
        _saxi_flag_13 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 14)) begin
        _saxi_register_14 <= axislite_resetval_48;
        _saxi_flag_14 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 15)) begin
        _saxi_register_15 <= axislite_resetval_48;
        _saxi_flag_15 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 16)) begin
        _saxi_register_16 <= axislite_resetval_48;
        _saxi_flag_16 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 17)) begin
        _saxi_register_17 <= axislite_resetval_48;
        _saxi_flag_17 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 18)) begin
        _saxi_register_18 <= axislite_resetval_48;
        _saxi_flag_18 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 19)) begin
        _saxi_register_19 <= axislite_resetval_48;
        _saxi_flag_19 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 20)) begin
        _saxi_register_20 <= axislite_resetval_48;
        _saxi_flag_20 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 21)) begin
        _saxi_register_21 <= axislite_resetval_48;
        _saxi_flag_21 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 22)) begin
        _saxi_register_22 <= axislite_resetval_48;
        _saxi_flag_22 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 23)) begin
        _saxi_register_23 <= axislite_resetval_48;
        _saxi_flag_23 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 24)) begin
        _saxi_register_24 <= axislite_resetval_48;
        _saxi_flag_24 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 25)) begin
        _saxi_register_25 <= axislite_resetval_48;
        _saxi_flag_25 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 26)) begin
        _saxi_register_26 <= axislite_resetval_48;
        _saxi_flag_26 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 27)) begin
        _saxi_register_27 <= axislite_resetval_48;
        _saxi_flag_27 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 28)) begin
        _saxi_register_28 <= axislite_resetval_48;
        _saxi_flag_28 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 29)) begin
        _saxi_register_29 <= axislite_resetval_48;
        _saxi_flag_29 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 30)) begin
        _saxi_register_30 <= axislite_resetval_48;
        _saxi_flag_30 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 31)) begin
        _saxi_register_31 <= axislite_resetval_48;
        _saxi_flag_31 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 32)) begin
        _saxi_register_32 <= axislite_resetval_48;
        _saxi_flag_32 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 33)) begin
        _saxi_register_33 <= axislite_resetval_48;
        _saxi_flag_33 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 34)) begin
        _saxi_register_34 <= axislite_resetval_48;
        _saxi_flag_34 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 35)) begin
        _saxi_register_35 <= axislite_resetval_48;
        _saxi_flag_35 <= 0;
      end 
      if((_saxi_register_fsm == 1) && (saxi_rready || !saxi_rvalid) && axislite_flag_47 && (axis_maskaddr_45 == 36)) begin
        _saxi_register_36 <= axislite_resetval_48;
        _saxi_flag_36 <= 0;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 0)) begin
        _saxi_register_0 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 1)) begin
        _saxi_register_1 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 2)) begin
        _saxi_register_2 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 3)) begin
        _saxi_register_3 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 4)) begin
        _saxi_register_4 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 5)) begin
        _saxi_register_5 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 6)) begin
        _saxi_register_6 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 7)) begin
        _saxi_register_7 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 8)) begin
        _saxi_register_8 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 9)) begin
        _saxi_register_9 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 10)) begin
        _saxi_register_10 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 11)) begin
        _saxi_register_11 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 12)) begin
        _saxi_register_12 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 13)) begin
        _saxi_register_13 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 14)) begin
        _saxi_register_14 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 15)) begin
        _saxi_register_15 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 16)) begin
        _saxi_register_16 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 17)) begin
        _saxi_register_17 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 18)) begin
        _saxi_register_18 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 19)) begin
        _saxi_register_19 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 20)) begin
        _saxi_register_20 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 21)) begin
        _saxi_register_21 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 22)) begin
        _saxi_register_22 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 23)) begin
        _saxi_register_23 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 24)) begin
        _saxi_register_24 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 25)) begin
        _saxi_register_25 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 26)) begin
        _saxi_register_26 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 27)) begin
        _saxi_register_27 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 28)) begin
        _saxi_register_28 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 29)) begin
        _saxi_register_29 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 30)) begin
        _saxi_register_30 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 31)) begin
        _saxi_register_31 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 32)) begin
        _saxi_register_32 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 33)) begin
        _saxi_register_33 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 34)) begin
        _saxi_register_34 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 35)) begin
        _saxi_register_35 <= saxi_wdata;
      end 
      if((_saxi_register_fsm == 3) && saxi_wvalid && (axis_maskaddr_45 == 36)) begin
        _saxi_register_36 <= saxi_wdata;
      end 
      if(_saxi_register_11[0] == 1) begin
        _saxi_register_11[0] <= 0;
        _saxi_register_9[0] <= 0;
      end 
      if(_saxi_register_11[1] == 1) begin
        _saxi_register_11[1] <= 0;
        _saxi_register_9[1] <= 0;
      end 
      if(_saxi_register_11[2] == 1) begin
        _saxi_register_11[2] <= 0;
        _saxi_register_9[2] <= 0;
      end 
      if(_saxi_register_11[3] == 1) begin
        _saxi_register_11[3] <= 0;
        _saxi_register_9[3] <= 0;
      end 
      if(_saxi_register_11[4] == 1) begin
        _saxi_register_11[4] <= 0;
        _saxi_register_9[4] <= 0;
      end 
      if(_saxi_register_11[5] == 1) begin
        _saxi_register_11[5] <= 0;
        _saxi_register_9[5] <= 0;
      end 
      if(_saxi_register_11[6] == 1) begin
        _saxi_register_11[6] <= 0;
        _saxi_register_9[6] <= 0;
      end 
      if(_saxi_register_11[7] == 1) begin
        _saxi_register_11[7] <= 0;
        _saxi_register_9[7] <= 0;
      end 
      if(_saxi_register_11[8] == 1) begin
        _saxi_register_11[8] <= 0;
        _saxi_register_9[8] <= 0;
      end 
      if(_saxi_register_11[9] == 1) begin
        _saxi_register_11[9] <= 0;
        _saxi_register_9[9] <= 0;
      end 
      if(_saxi_register_11[10] == 1) begin
        _saxi_register_11[10] <= 0;
        _saxi_register_9[10] <= 0;
      end 
      if(_saxi_register_11[11] == 1) begin
        _saxi_register_11[11] <= 0;
        _saxi_register_9[11] <= 0;
      end 
      if(_saxi_register_11[12] == 1) begin
        _saxi_register_11[12] <= 0;
        _saxi_register_9[12] <= 0;
      end 
      if(_saxi_register_11[13] == 1) begin
        _saxi_register_11[13] <= 0;
        _saxi_register_9[13] <= 0;
      end 
      if(_saxi_register_11[14] == 1) begin
        _saxi_register_11[14] <= 0;
        _saxi_register_9[14] <= 0;
      end 
      if(_saxi_register_11[15] == 1) begin
        _saxi_register_11[15] <= 0;
        _saxi_register_9[15] <= 0;
      end 
      if(_saxi_register_11[16] == 1) begin
        _saxi_register_11[16] <= 0;
        _saxi_register_9[16] <= 0;
      end 
      if(_saxi_register_11[17] == 1) begin
        _saxi_register_11[17] <= 0;
        _saxi_register_9[17] <= 0;
      end 
      if(_saxi_register_11[18] == 1) begin
        _saxi_register_11[18] <= 0;
        _saxi_register_9[18] <= 0;
      end 
      if(_saxi_register_11[19] == 1) begin
        _saxi_register_11[19] <= 0;
        _saxi_register_9[19] <= 0;
      end 
      if(_saxi_register_11[20] == 1) begin
        _saxi_register_11[20] <= 0;
        _saxi_register_9[20] <= 0;
      end 
      if(_saxi_register_11[21] == 1) begin
        _saxi_register_11[21] <= 0;
        _saxi_register_9[21] <= 0;
      end 
      if(_saxi_register_11[22] == 1) begin
        _saxi_register_11[22] <= 0;
        _saxi_register_9[22] <= 0;
      end 
      if(_saxi_register_11[23] == 1) begin
        _saxi_register_11[23] <= 0;
        _saxi_register_9[23] <= 0;
      end 
      if(_saxi_register_11[24] == 1) begin
        _saxi_register_11[24] <= 0;
        _saxi_register_9[24] <= 0;
      end 
      if(_saxi_register_11[25] == 1) begin
        _saxi_register_11[25] <= 0;
        _saxi_register_9[25] <= 0;
      end 
      if(_saxi_register_11[26] == 1) begin
        _saxi_register_11[26] <= 0;
        _saxi_register_9[26] <= 0;
      end 
      if(_saxi_register_11[27] == 1) begin
        _saxi_register_11[27] <= 0;
        _saxi_register_9[27] <= 0;
      end 
      if(_saxi_register_11[28] == 1) begin
        _saxi_register_11[28] <= 0;
        _saxi_register_9[28] <= 0;
      end 
      if(_saxi_register_11[29] == 1) begin
        _saxi_register_11[29] <= 0;
        _saxi_register_9[29] <= 0;
      end 
      if(_saxi_register_11[30] == 1) begin
        _saxi_register_11[30] <= 0;
        _saxi_register_9[30] <= 0;
      end 
      if(_saxi_register_11[31] == 1) begin
        _saxi_register_11[31] <= 0;
        _saxi_register_9[31] <= 0;
      end 
      if(irq_busy_edge_51) begin
        _saxi_register_9[0] <= irq_busy_edge_51;
      end 
      if(irq_extern_edge_53) begin
        _saxi_register_9[1] <= irq_extern_edge_53;
      end 
      if(main_fsm == 0) begin
        _saxi_register_5 <= 0;
        _saxi_register_6 <= 0;
        _saxi_register_7 <= 0;
      end 
      if(main_fsm == 1) begin
        internal_state_counter <= 0;
        _saxi_register_12 <= 0;
      end else if(main_fsm == _saxi_register_13) begin
        if(internal_state_counter == _saxi_register_14) begin
          internal_state_counter <= 0;
          _saxi_register_12 <= _saxi_register_12 + 1;
        end else begin
          internal_state_counter <= internal_state_counter + 1;
        end
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_0 <= 1;
        _saxi_flag_0 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_1 <= 1;
        _saxi_flag_1 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_2 <= 1;
        _saxi_flag_2 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_3 <= 1;
        _saxi_flag_3 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_4 <= 1;
        _saxi_flag_4 <= 0;
      end 
      if((main_fsm == 1) && 1) begin
        _saxi_register_5 <= 1;
        _saxi_flag_5 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_6 <= 1;
        _saxi_flag_6 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_7 <= 1;
        _saxi_flag_7 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_8 <= 1;
        _saxi_flag_8 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_9 <= 1;
        _saxi_flag_9 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_10 <= 1;
        _saxi_flag_10 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_11 <= 1;
        _saxi_flag_11 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_12 <= 1;
        _saxi_flag_12 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_13 <= 1;
        _saxi_flag_13 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_14 <= 1;
        _saxi_flag_14 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_15 <= 1;
        _saxi_flag_15 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_16 <= 1;
        _saxi_flag_16 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_17 <= 1;
        _saxi_flag_17 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_18 <= 1;
        _saxi_flag_18 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_19 <= 1;
        _saxi_flag_19 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_20 <= 1;
        _saxi_flag_20 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_21 <= 1;
        _saxi_flag_21 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_22 <= 1;
        _saxi_flag_22 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_23 <= 1;
        _saxi_flag_23 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_24 <= 1;
        _saxi_flag_24 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_25 <= 1;
        _saxi_flag_25 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_26 <= 1;
        _saxi_flag_26 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_27 <= 1;
        _saxi_flag_27 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_28 <= 1;
        _saxi_flag_28 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_29 <= 1;
        _saxi_flag_29 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_30 <= 1;
        _saxi_flag_30 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_31 <= 1;
        _saxi_flag_31 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_32 <= 1;
        _saxi_flag_32 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_33 <= 1;
        _saxi_flag_33 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_34 <= 1;
        _saxi_flag_34 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_35 <= 1;
        _saxi_flag_35 <= 0;
      end 
      if((main_fsm == 1) && 0) begin
        _saxi_register_36 <= 1;
        _saxi_flag_36 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_0 <= 0;
        _saxi_flag_0 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_1 <= 0;
        _saxi_flag_1 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_2 <= 0;
        _saxi_flag_2 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_3 <= 0;
        _saxi_flag_3 <= 0;
      end 
      if((main_fsm == 2) && 1) begin
        _saxi_register_4 <= 0;
        _saxi_flag_4 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_5 <= 0;
        _saxi_flag_5 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_6 <= 0;
        _saxi_flag_6 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_7 <= 0;
        _saxi_flag_7 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_8 <= 0;
        _saxi_flag_8 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_9 <= 0;
        _saxi_flag_9 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_10 <= 0;
        _saxi_flag_10 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_11 <= 0;
        _saxi_flag_11 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_12 <= 0;
        _saxi_flag_12 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_13 <= 0;
        _saxi_flag_13 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_14 <= 0;
        _saxi_flag_14 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_15 <= 0;
        _saxi_flag_15 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_16 <= 0;
        _saxi_flag_16 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_17 <= 0;
        _saxi_flag_17 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_18 <= 0;
        _saxi_flag_18 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_19 <= 0;
        _saxi_flag_19 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_20 <= 0;
        _saxi_flag_20 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_21 <= 0;
        _saxi_flag_21 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_22 <= 0;
        _saxi_flag_22 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_23 <= 0;
        _saxi_flag_23 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_24 <= 0;
        _saxi_flag_24 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_25 <= 0;
        _saxi_flag_25 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_26 <= 0;
        _saxi_flag_26 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_27 <= 0;
        _saxi_flag_27 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_28 <= 0;
        _saxi_flag_28 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_29 <= 0;
        _saxi_flag_29 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_30 <= 0;
        _saxi_flag_30 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_31 <= 0;
        _saxi_flag_31 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_32 <= 0;
        _saxi_flag_32 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_33 <= 0;
        _saxi_flag_33 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_34 <= 0;
        _saxi_flag_34 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_35 <= 0;
        _saxi_flag_35 <= 0;
      end 
      if((main_fsm == 2) && 0) begin
        _saxi_register_36 <= 0;
        _saxi_flag_36 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_0 <= 0;
        _saxi_flag_0 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_1 <= 0;
        _saxi_flag_1 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_2 <= 0;
        _saxi_flag_2 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_3 <= 0;
        _saxi_flag_3 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_4 <= 0;
        _saxi_flag_4 <= 0;
      end 
      if((main_fsm == 40) && 1) begin
        _saxi_register_5 <= 0;
        _saxi_flag_5 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_6 <= 0;
        _saxi_flag_6 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_7 <= 0;
        _saxi_flag_7 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_8 <= 0;
        _saxi_flag_8 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_9 <= 0;
        _saxi_flag_9 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_10 <= 0;
        _saxi_flag_10 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_11 <= 0;
        _saxi_flag_11 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_12 <= 0;
        _saxi_flag_12 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_13 <= 0;
        _saxi_flag_13 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_14 <= 0;
        _saxi_flag_14 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_15 <= 0;
        _saxi_flag_15 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_16 <= 0;
        _saxi_flag_16 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_17 <= 0;
        _saxi_flag_17 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_18 <= 0;
        _saxi_flag_18 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_19 <= 0;
        _saxi_flag_19 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_20 <= 0;
        _saxi_flag_20 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_21 <= 0;
        _saxi_flag_21 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_22 <= 0;
        _saxi_flag_22 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_23 <= 0;
        _saxi_flag_23 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_24 <= 0;
        _saxi_flag_24 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_25 <= 0;
        _saxi_flag_25 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_26 <= 0;
        _saxi_flag_26 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_27 <= 0;
        _saxi_flag_27 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_28 <= 0;
        _saxi_flag_28 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_29 <= 0;
        _saxi_flag_29 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_30 <= 0;
        _saxi_flag_30 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_31 <= 0;
        _saxi_flag_31 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_32 <= 0;
        _saxi_flag_32 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_33 <= 0;
        _saxi_flag_33 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_34 <= 0;
        _saxi_flag_34 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_35 <= 0;
        _saxi_flag_35 <= 0;
      end 
      if((main_fsm == 40) && 0) begin
        _saxi_register_36 <= 0;
        _saxi_flag_36 <= 0;
      end 
    end
  end

  localparam _saxi_register_fsm_1 = 1;
  localparam _saxi_register_fsm_2 = 2;
  localparam _saxi_register_fsm_3 = 3;
  localparam _saxi_register_fsm_4 = 4;

  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _saxi_register_fsm <= _saxi_register_fsm_init;
      axis_maskaddr_45 <= 0;
    end else begin
      case(_saxi_register_fsm)
        _saxi_register_fsm_init: begin
          if(readvalid_42 || writevalid_41) begin
            axis_maskaddr_45 <= (addr_40 >> _saxi_shift) & _saxi_mask;
          end 
          if(readvalid_42) begin
            _saxi_register_fsm <= _saxi_register_fsm_1;
          end 
          if(writevalid_41) begin
            _saxi_register_fsm <= _saxi_register_fsm_3;
          end 
        end
        _saxi_register_fsm_1: begin
          if(saxi_rready || !saxi_rvalid) begin
            _saxi_register_fsm <= _saxi_register_fsm_2;
          end 
        end
        _saxi_register_fsm_2: begin
          if(saxi_rready && saxi_rvalid) begin
            _saxi_register_fsm <= _saxi_register_fsm_init;
          end 
        end
        _saxi_register_fsm_3: begin
          if(saxi_wvalid) begin
            _saxi_register_fsm <= _saxi_register_fsm_4;
          end 
        end
        _saxi_register_fsm_4: begin
          if(saxi_bready && saxi_bvalid) begin
            _saxi_register_fsm <= _saxi_register_fsm_init;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    _rst_logic_1 <= rst_logic;
    _rst_logic_2 <= _rst_logic_1;
    RST <= rst_logic | _rst_logic_1 | _rst_logic_2;
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      irq <= 0;
    end else begin
      irq <= |irq_49;
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      irq_busy_edge_50 <= 0;
    end else begin
      irq_busy_edge_50 <= irq_busy;
    end
  end


  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      irq_extern_edge_52 <= 0;
    end else begin
      irq_extern_edge_52 <= irq_extern;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_146_1 <= 0;
    end else begin
      __tmp_146_1 <= _tmp_146;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_148_1 <= 0;
    end else begin
      __tmp_148_1 <= _tmp_148;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_537_1 <= 0;
    end else begin
      __tmp_537_1 <= _tmp_537;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_541_1 <= 0;
    end else begin
      __tmp_541_1 <= _tmp_541;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_165_1 <= 0;
    end else begin
      __tmp_165_1 <= _tmp_165;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_167_1 <= 0;
    end else begin
      __tmp_167_1 <= _tmp_167;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_136_1 <= 0;
    end else begin
      __tmp_136_1 <= _tmp_136;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_138_1 <= 0;
    end else begin
      __tmp_138_1 <= _tmp_138;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_174_1 <= 0;
    end else begin
      __tmp_174_1 <= _tmp_174;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      __tmp_176_1 <= 0;
    end else begin
      __tmp_176_1 <= _tmp_176;
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _acc_0_x_source_ram_renable <= 0;
      _acc_0_x_source_fifo_deq <= 0;
      _acc_0_x_idle <= 1;
      _acc_0_rshift_source_ram_renable <= 0;
      _acc_0_rshift_source_fifo_deq <= 0;
      _acc_0_rshift_idle <= 1;
      _acc_0_sum_sink_wenable <= 0;
      _acc_0_sum_sink_fifo_enq <= 0;
      _acc_0_valid_sink_wenable <= 0;
      _acc_0_valid_sink_fifo_enq <= 0;
      __acc_0_stream_ivalid_1 <= 0;
      __acc_0_stream_ivalid_2 <= 0;
      __acc_0_stream_ivalid_3 <= 0;
      __acc_0_stream_ivalid_4 <= 0;
      __acc_0_stream_ivalid_5 <= 0;
      _greaterthan_data_3 <= 0;
      _minus_data_5 <= 0;
      _reduceadd_data_16 <= 1'sd0;
      _reduceadd_count_16 <= 0;
      _reduceadd_prev_count_max_16 <= 0;
      _pulse_data_18 <= 1'sd0;
      _pulse_count_18 <= 0;
      _pulse_prev_count_max_18 <= 0;
      __delay_data_182__variable_1 <= 0;
      _sll_data_7 <= 0;
      __delay_data_179_greaterthan_3 <= 0;
      __delay_data_180_reduceadd_16 <= 0;
      __delay_data_183__delay_182__variable_1 <= 0;
      __delay_data_186_pulse_18 <= 0;
      _cond_data_13 <= 0;
      __delay_data_181__delay_180_reduceadd_16 <= 0;
      __delay_data_184__delay_183__delay_182__variable_1 <= 0;
      __delay_data_187__delay_186_pulse_18 <= 0;
      _plus_data_20 <= 0;
      __delay_data_185__delay_184__delay_183__delay_182__variable_1 <= 0;
      __delay_data_188__delay_187__delay_186_pulse_18 <= 0;
      _sra_data_21 <= 0;
      __delay_data_189__delay_188__delay_187__delay_186_pulse_18 <= 0;
      __variable_wdata_15 <= 0;
      __variable_wdata_0 <= 0;
      __variable_wdata_1 <= 0;
      __variable_wdata_2 <= 0;
      _tmp_321 <= 0;
      _tmp_322 <= 0;
      _tmp_323 <= 0;
      _tmp_324 <= 0;
      _tmp_325 <= 0;
      _tmp_326 <= 0;
      _tmp_327 <= 0;
      _tmp_328 <= 0;
      _tmp_329 <= 0;
      _tmp_330 <= 0;
      _tmp_331 <= 0;
      _tmp_332 <= 0;
      _tmp_333 <= 0;
      _tmp_334 <= 0;
      _tmp_335 <= 0;
      _tmp_336 <= 0;
      _tmp_337 <= 0;
      _tmp_338 <= 0;
      _tmp_339 <= 0;
      _tmp_340 <= 0;
      _tmp_341 <= 0;
      _tmp_342 <= 0;
      _tmp_343 <= 0;
      _tmp_344 <= 0;
      _tmp_345 <= 0;
      _tmp_346 <= 0;
      _tmp_347 <= 0;
      _tmp_348 <= 0;
      _tmp_349 <= 0;
      _tmp_350 <= 0;
      _tmp_351 <= 0;
      _tmp_352 <= 0;
      _acc_0_busy_reg <= 0;
    end else begin
      if(_acc_0_stream_oready) begin
        _acc_0_x_source_ram_renable <= 0;
        _acc_0_x_source_fifo_deq <= 0;
      end 
      _acc_0_x_idle <= _acc_0_x_idle;
      if(_acc_0_stream_oready) begin
        _acc_0_rshift_source_ram_renable <= 0;
        _acc_0_rshift_source_fifo_deq <= 0;
      end 
      _acc_0_rshift_idle <= _acc_0_rshift_idle;
      if(_acc_0_stream_oready) begin
        _acc_0_sum_sink_wenable <= 0;
        _acc_0_sum_sink_fifo_enq <= 0;
      end 
      if(_acc_0_stream_oready) begin
        _acc_0_valid_sink_wenable <= 0;
        _acc_0_valid_sink_fifo_enq <= 0;
      end 
      if(_acc_0_stream_oready) begin
        __acc_0_stream_ivalid_1 <= _acc_0_stream_ivalid;
      end 
      if(_acc_0_stream_oready) begin
        __acc_0_stream_ivalid_2 <= __acc_0_stream_ivalid_1;
      end 
      if(_acc_0_stream_oready) begin
        __acc_0_stream_ivalid_3 <= __acc_0_stream_ivalid_2;
      end 
      if(_acc_0_stream_oready) begin
        __acc_0_stream_ivalid_4 <= __acc_0_stream_ivalid_3;
      end 
      if(_acc_0_stream_oready) begin
        __acc_0_stream_ivalid_5 <= __acc_0_stream_ivalid_4;
      end 
      if(_acc_0_stream_oready) begin
        _greaterthan_data_3 <= acc_0_rshift_data > 1'sd0;
      end 
      if(_acc_0_stream_oready) begin
        _minus_data_5 <= acc_0_rshift_data - 2'sd1;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready && _reduceadd_reset_cond_16) begin
        _reduceadd_data_16 <= 1'sd0;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready) begin
        _reduceadd_count_16 <= (_reduceadd_current_count_16 >= acc_0_size_data - 1)? 0 : _reduceadd_current_count_16 + 1;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready) begin
        _reduceadd_prev_count_max_16 <= _reduceadd_current_count_16 >= acc_0_size_data - 1;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready) begin
        _reduceadd_data_16 <= _reduceadd_current_data_16 + acc_0_x_data;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready && _pulse_reset_cond_18) begin
        _pulse_data_18 <= 1'sd0;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready) begin
        _pulse_count_18 <= (_pulse_current_count_18 >= acc_0_size_data - 1)? 0 : _pulse_current_count_18 + 1;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready) begin
        _pulse_prev_count_max_18 <= _pulse_current_count_18 >= acc_0_size_data - 1;
      end 
      if(_acc_0_stream_ivalid && _acc_0_stream_oready) begin
        _pulse_data_18 <= _pulse_current_count_18 >= acc_0_size_data - 1;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_182__variable_1 <= acc_0_rshift_data;
      end 
      if(_acc_0_stream_oready) begin
        _sll_data_7 <= 2'sd1 << _minus_data_5;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_179_greaterthan_3 <= _greaterthan_data_3;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_180_reduceadd_16 <= _reduceadd_data_16;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_183__delay_182__variable_1 <= __delay_data_182__variable_1;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_186_pulse_18 <= _pulse_data_18;
      end 
      if(_acc_0_stream_oready) begin
        _cond_data_13 <= (__delay_data_179_greaterthan_3)? _sll_data_7 : 1'sd0;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_181__delay_180_reduceadd_16 <= __delay_data_180_reduceadd_16;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_184__delay_183__delay_182__variable_1 <= __delay_data_183__delay_182__variable_1;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_187__delay_186_pulse_18 <= __delay_data_186_pulse_18;
      end 
      if(_acc_0_stream_oready) begin
        _plus_data_20 <= __delay_data_181__delay_180_reduceadd_16 + _cond_data_13;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_185__delay_184__delay_183__delay_182__variable_1 <= __delay_data_184__delay_183__delay_182__variable_1;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_188__delay_187__delay_186_pulse_18 <= __delay_data_187__delay_186_pulse_18;
      end 
      if(_acc_0_stream_oready) begin
        _sra_data_21 <= _plus_data_20 >>> __delay_data_185__delay_184__delay_183__delay_182__variable_1;
      end 
      if(_acc_0_stream_oready) begin
        __delay_data_189__delay_188__delay_187__delay_186_pulse_18 <= __delay_data_188__delay_187__delay_186_pulse_18;
      end 
      if(__stream_matmul_11_stream_ivalid_11 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_15 <= __delay_data_235__delay_234__delay_233__delay_232____variable_84;
      end 
      if(__stream_matmul_11_stream_ivalid_11 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_0 <= __substreamoutput_data_177;
      end 
      if(__stream_matmul_11_stream_ivalid_11 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_1 <= __delay_data_245__delay_244__delay_243__delay_242___plus_190;
      end 
      if(__stream_matmul_11_stream_ivalid_11 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_2 <= __delay_data_256__delay_255__delay_254__delay_253____variable_79;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_321 <= _acc_0_source_start;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_322 <= _tmp_321;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_323 <= _tmp_322;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_324 <= _acc_0_source_start;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_325 <= _tmp_324;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_326 <= _tmp_325;
      end 
      if(_acc_0_stream_oready && _tmp_326) begin
        __variable_wdata_15 <= 1;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_327 <= _acc_0_source_start;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_328 <= _tmp_327;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_329 <= _tmp_328;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_330 <= _tmp_329;
      end 
      if(_acc_0_stream_oready && _tmp_330) begin
        __variable_wdata_15 <= 0;
      end 
      if(_acc_0_stream_oready && 1'd0) begin
        __variable_wdata_15 <= 1;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_331 <= _acc_0_source_start;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_332 <= _tmp_331;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_333 <= _tmp_332;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_334 <= _tmp_333;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_335 <= _tmp_334;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_336 <= _tmp_335;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_337 <= _tmp_336;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_338 <= _acc_0_source_stop;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_339 <= _tmp_338;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_340 <= _tmp_339;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_341 <= _tmp_340;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_342 <= _tmp_341;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_343 <= _tmp_342;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_344 <= _tmp_343;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_345 <= _acc_0_source_busy;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_346 <= _tmp_345;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_347 <= _tmp_346;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_348 <= _tmp_347;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_349 <= _tmp_348;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_350 <= _tmp_349;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_351 <= _tmp_350;
      end 
      if(_acc_0_stream_oready) begin
        _tmp_352 <= _acc_0_sink_busy;
      end 
      if(!_acc_0_sink_busy && _tmp_352) begin
        _acc_0_busy_reg <= 0;
      end 
      if(_acc_0_source_busy) begin
        _acc_0_busy_reg <= 1;
      end 
    end
  end

  localparam _acc_0_fsm_1 = 1;
  localparam _acc_0_fsm_2 = 2;
  localparam _acc_0_fsm_3 = 3;

  always @(posedge CLK) begin
    if(RST) begin
      _acc_0_fsm <= _acc_0_fsm_init;
      _acc_0_source_start <= 0;
      _acc_0_source_busy <= 0;
      _acc_0_stream_ivalid <= 0;
    end else begin
      if(__stream_matmul_11_stream_ivalid_11 && _stream_matmul_11_stream_oready) begin
        _acc_0_stream_ivalid <= 1'd1;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_busy) begin
        _acc_0_source_busy <= _stream_matmul_11_source_busy;
      end 
      if(_acc_0_stream_oready && _tmp_323) begin
        _acc_0_stream_ivalid <= 1;
      end 
      if(_acc_0_stream_oready && 1'd0) begin
        _acc_0_stream_ivalid <= 0;
      end 
      case(_acc_0_fsm)
        _acc_0_fsm_init: begin
          if(_acc_0_run_flag) begin
            _acc_0_source_start <= 1;
          end 
          if(_acc_0_run_flag) begin
            _acc_0_fsm <= _acc_0_fsm_1;
          end 
        end
        _acc_0_fsm_1: begin
          if(_acc_0_source_start && _acc_0_stream_oready) begin
            _acc_0_source_start <= 0;
            _acc_0_source_busy <= 1;
          end 
          if(_acc_0_source_start && _acc_0_stream_oready) begin
            _acc_0_fsm <= _acc_0_fsm_2;
          end 
        end
        _acc_0_fsm_2: begin
          if(_acc_0_stream_oready) begin
            _acc_0_fsm <= _acc_0_fsm_3;
          end 
        end
        _acc_0_fsm_3: begin
          if(_acc_0_stream_oready && 1'd0) begin
            _acc_0_source_busy <= 0;
          end 
          if(_acc_0_stream_oready && 1'd0 && _acc_0_run_flag) begin
            _acc_0_source_start <= 1;
          end 
          if(_acc_0_stream_oready && 1'd0) begin
            _acc_0_fsm <= _acc_0_fsm_init;
          end 
          if(_acc_0_stream_oready && 1'd0 && _acc_0_run_flag) begin
            _acc_0_fsm <= _acc_0_fsm_1;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _add_tree_1_var0_source_ram_renable <= 0;
      _add_tree_1_var0_source_fifo_deq <= 0;
      _add_tree_1_var0_idle <= 1;
      _add_tree_1_sum_sink_wenable <= 0;
      _add_tree_1_sum_sink_fifo_enq <= 0;
      __variable_wdata_22 <= 0;
      _tmp_311 <= 0;
      _tmp_312 <= 0;
      _tmp_313 <= 0;
      _tmp_314 <= 0;
      _tmp_315 <= 0;
      _tmp_316 <= 0;
      _tmp_317 <= 0;
      _tmp_318 <= 0;
      _tmp_319 <= 0;
      _tmp_320 <= 0;
      _add_tree_1_busy_reg <= 0;
    end else begin
      if(_add_tree_1_stream_oready) begin
        _add_tree_1_var0_source_ram_renable <= 0;
        _add_tree_1_var0_source_fifo_deq <= 0;
      end 
      _add_tree_1_var0_idle <= _add_tree_1_var0_idle;
      if(_add_tree_1_stream_oready) begin
        _add_tree_1_sum_sink_wenable <= 0;
        _add_tree_1_sum_sink_fifo_enq <= 0;
      end 
      if(__stream_matmul_11_stream_ivalid_10 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_22 <= __substreamoutput_data_175;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_311 <= _add_tree_1_source_start;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_312 <= _tmp_311;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_313 <= _tmp_312;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_314 <= _add_tree_1_source_start;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_315 <= _tmp_314;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_316 <= _add_tree_1_source_stop;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_317 <= _tmp_316;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_318 <= _add_tree_1_source_busy;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_319 <= _tmp_318;
      end 
      if(_add_tree_1_stream_oready) begin
        _tmp_320 <= _add_tree_1_sink_busy;
      end 
      if(!_add_tree_1_sink_busy && _tmp_320) begin
        _add_tree_1_busy_reg <= 0;
      end 
      if(_add_tree_1_source_busy) begin
        _add_tree_1_busy_reg <= 1;
      end 
    end
  end

  localparam _add_tree_1_fsm_1 = 1;
  localparam _add_tree_1_fsm_2 = 2;
  localparam _add_tree_1_fsm_3 = 3;

  always @(posedge CLK) begin
    if(RST) begin
      _add_tree_1_fsm <= _add_tree_1_fsm_init;
      _add_tree_1_source_start <= 0;
      _add_tree_1_source_busy <= 0;
      _add_tree_1_stream_ivalid <= 0;
    end else begin
      if(__stream_matmul_11_stream_ivalid_10 && _stream_matmul_11_stream_oready) begin
        _add_tree_1_stream_ivalid <= 1'd1;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_busy) begin
        _add_tree_1_source_busy <= _stream_matmul_11_source_busy;
      end 
      if(_add_tree_1_stream_oready && _tmp_313) begin
        _add_tree_1_stream_ivalid <= 1;
      end 
      if(_add_tree_1_stream_oready && 1'd0) begin
        _add_tree_1_stream_ivalid <= 0;
      end 
      case(_add_tree_1_fsm)
        _add_tree_1_fsm_init: begin
          if(_add_tree_1_run_flag) begin
            _add_tree_1_source_start <= 1;
          end 
          if(_add_tree_1_run_flag) begin
            _add_tree_1_fsm <= _add_tree_1_fsm_1;
          end 
        end
        _add_tree_1_fsm_1: begin
          if(_add_tree_1_source_start && _add_tree_1_stream_oready) begin
            _add_tree_1_source_start <= 0;
            _add_tree_1_source_busy <= 1;
          end 
          if(_add_tree_1_source_start && _add_tree_1_stream_oready) begin
            _add_tree_1_fsm <= _add_tree_1_fsm_2;
          end 
        end
        _add_tree_1_fsm_2: begin
          if(_add_tree_1_stream_oready) begin
            _add_tree_1_fsm <= _add_tree_1_fsm_3;
          end 
        end
        _add_tree_1_fsm_3: begin
          if(_add_tree_1_stream_oready && 1'd0) begin
            _add_tree_1_source_busy <= 0;
          end 
          if(_add_tree_1_stream_oready && 1'd0 && _add_tree_1_run_flag) begin
            _add_tree_1_source_start <= 1;
          end 
          if(_add_tree_1_stream_oready && 1'd0) begin
            _add_tree_1_fsm <= _add_tree_1_fsm_init;
          end 
          if(_add_tree_1_stream_oready && 1'd0 && _add_tree_1_run_flag) begin
            _add_tree_1_fsm <= _add_tree_1_fsm_1;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _mul_rshift_round_clip_2_x_source_ram_renable <= 0;
      _mul_rshift_round_clip_2_x_source_fifo_deq <= 0;
      _mul_rshift_round_clip_2_x_idle <= 1;
      _mul_rshift_round_clip_2_y_source_ram_renable <= 0;
      _mul_rshift_round_clip_2_y_source_fifo_deq <= 0;
      _mul_rshift_round_clip_2_y_idle <= 1;
      _mul_rshift_round_clip_2_rshift_source_ram_renable <= 0;
      _mul_rshift_round_clip_2_rshift_source_fifo_deq <= 0;
      _mul_rshift_round_clip_2_rshift_idle <= 1;
      _mul_rshift_round_clip_2_z_sink_wenable <= 0;
      _mul_rshift_round_clip_2_z_sink_fifo_enq <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_1 <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_2 <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_3 <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_4 <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_5 <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_6 <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_7 <= 0;
      __mul_rshift_round_clip_2_stream_ivalid_8 <= 0;
      _times_mul_odata_reg_27 <= 0;
      __delay_data_195_sll_33 <= 0;
      __delay_data_199__variable_26 <= 0;
      __delay_data_203_eq_45 <= 0;
      __delay_data_196__delay_195_sll_33 <= 0;
      __delay_data_200__delay_199__variable_26 <= 0;
      __delay_data_204__delay_203_eq_45 <= 0;
      __delay_data_197__delay_196__delay_195_sll_33 <= 0;
      __delay_data_201__delay_200__delay_199__variable_26 <= 0;
      __delay_data_205__delay_204__delay_203_eq_45 <= 0;
      __delay_data_198__delay_197__delay_196__delay_195_sll_33 <= 0;
      __delay_data_202__delay_201__delay_200__delay_199__variable_26 <= 0;
      __delay_data_206__delay_205__delay_204__delay_203_eq_45 <= 0;
      _cond_data_46 <= 0;
      _greaterthan_data_47 <= 0;
      _lessthan_data_51 <= 0;
      _greatereq_data_55 <= 0;
      __delay_data_207_cond_46 <= 0;
      _cond_data_49 <= 0;
      _cond_data_53 <= 0;
      __delay_data_208_greatereq_55 <= 0;
      _cond_data_57 <= 0;
      __variable_wdata_24 <= 0;
      __variable_wdata_25 <= 0;
      __variable_wdata_26 <= 0;
      _tmp_353 <= 0;
      _tmp_354 <= 0;
      _tmp_355 <= 0;
      _tmp_356 <= 0;
      _tmp_357 <= 0;
      _tmp_358 <= 0;
      _tmp_359 <= 0;
      _tmp_360 <= 0;
      _tmp_361 <= 0;
      _tmp_362 <= 0;
      _tmp_363 <= 0;
      _tmp_364 <= 0;
      _tmp_365 <= 0;
      _tmp_366 <= 0;
      _tmp_367 <= 0;
      _tmp_368 <= 0;
      _tmp_369 <= 0;
      _tmp_370 <= 0;
      _tmp_371 <= 0;
      _tmp_372 <= 0;
      _tmp_373 <= 0;
      _tmp_374 <= 0;
      _tmp_375 <= 0;
      _tmp_376 <= 0;
      _tmp_377 <= 0;
      _tmp_378 <= 0;
      _tmp_379 <= 0;
      _tmp_380 <= 0;
      _tmp_381 <= 0;
      _tmp_382 <= 0;
      _tmp_383 <= 0;
      _tmp_384 <= 0;
      _tmp_385 <= 0;
      _tmp_386 <= 0;
      _mul_rshift_round_clip_2_busy_reg <= 0;
    end else begin
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _mul_rshift_round_clip_2_x_source_ram_renable <= 0;
        _mul_rshift_round_clip_2_x_source_fifo_deq <= 0;
      end 
      _mul_rshift_round_clip_2_x_idle <= _mul_rshift_round_clip_2_x_idle;
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _mul_rshift_round_clip_2_y_source_ram_renable <= 0;
        _mul_rshift_round_clip_2_y_source_fifo_deq <= 0;
      end 
      _mul_rshift_round_clip_2_y_idle <= _mul_rshift_round_clip_2_y_idle;
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _mul_rshift_round_clip_2_rshift_source_ram_renable <= 0;
        _mul_rshift_round_clip_2_rshift_source_fifo_deq <= 0;
      end 
      _mul_rshift_round_clip_2_rshift_idle <= _mul_rshift_round_clip_2_rshift_idle;
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _mul_rshift_round_clip_2_z_sink_wenable <= 0;
        _mul_rshift_round_clip_2_z_sink_fifo_enq <= 0;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_1 <= _mul_rshift_round_clip_2_stream_ivalid;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_2 <= __mul_rshift_round_clip_2_stream_ivalid_1;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_3 <= __mul_rshift_round_clip_2_stream_ivalid_2;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_4 <= __mul_rshift_round_clip_2_stream_ivalid_3;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_5 <= __mul_rshift_round_clip_2_stream_ivalid_4;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_6 <= __mul_rshift_round_clip_2_stream_ivalid_5;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_7 <= __mul_rshift_round_clip_2_stream_ivalid_6;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __mul_rshift_round_clip_2_stream_ivalid_8 <= __mul_rshift_round_clip_2_stream_ivalid_7;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _times_mul_odata_reg_27 <= _times_mul_odata_27;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_195_sll_33 <= _sll_data_33;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_199__variable_26 <= mul_rshift_round_clip_2_rshift_data;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_203_eq_45 <= _eq_data_45;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_196__delay_195_sll_33 <= __delay_data_195_sll_33;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_200__delay_199__variable_26 <= __delay_data_199__variable_26;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_204__delay_203_eq_45 <= __delay_data_203_eq_45;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_197__delay_196__delay_195_sll_33 <= __delay_data_196__delay_195_sll_33;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_201__delay_200__delay_199__variable_26 <= __delay_data_200__delay_199__variable_26;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_205__delay_204__delay_203_eq_45 <= __delay_data_204__delay_203_eq_45;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_198__delay_197__delay_196__delay_195_sll_33 <= __delay_data_197__delay_196__delay_195_sll_33;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_202__delay_201__delay_200__delay_199__variable_26 <= __delay_data_201__delay_200__delay_199__variable_26;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_206__delay_205__delay_204__delay_203_eq_45 <= __delay_data_205__delay_204__delay_203_eq_45;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _cond_data_46 <= (__delay_data_206__delay_205__delay_204__delay_203_eq_45)? _times_data_27 : _sra_data_43;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _greaterthan_data_47 <= _cond_data_46 > 16'sd32767;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _lessthan_data_51 <= _cond_data_46 < -16'sd32767;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _greatereq_data_55 <= _cond_data_46 >= 1'sd0;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_207_cond_46 <= _cond_data_46;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _cond_data_49 <= (_greaterthan_data_47)? 16'sd32767 : __delay_data_207_cond_46;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _cond_data_53 <= (_lessthan_data_51)? -16'sd32767 : __delay_data_207_cond_46;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        __delay_data_208_greatereq_55 <= _greatereq_data_55;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _cond_data_57 <= (__delay_data_208_greatereq_55)? _cond_data_49 : _cond_data_53;
      end 
      if(__stream_matmul_11_stream_ivalid_18 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_24 <= _plus_data_193;
      end 
      if(__stream_matmul_11_stream_ivalid_18 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_25 <= __delay_data_291__delay_290__delay_289__delay_288___cond_107;
      end 
      if(__stream_matmul_11_stream_ivalid_18 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_26 <= __delay_data_308__delay_307__delay_306__delay_305___plus_209;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_353 <= _mul_rshift_round_clip_2_source_start;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_354 <= _tmp_353;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_355 <= _tmp_354;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_356 <= _mul_rshift_round_clip_2_source_start;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_357 <= _tmp_356;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_358 <= _tmp_357;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_359 <= _tmp_358;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_360 <= _tmp_359;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_361 <= _tmp_360;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_362 <= _tmp_361;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_363 <= _tmp_362;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_364 <= _tmp_363;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_365 <= _tmp_364;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_366 <= _mul_rshift_round_clip_2_source_stop;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_367 <= _tmp_366;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_368 <= _tmp_367;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_369 <= _tmp_368;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_370 <= _tmp_369;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_371 <= _tmp_370;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_372 <= _tmp_371;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_373 <= _tmp_372;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_374 <= _tmp_373;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_375 <= _tmp_374;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_376 <= _mul_rshift_round_clip_2_source_busy;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_377 <= _tmp_376;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_378 <= _tmp_377;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_379 <= _tmp_378;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_380 <= _tmp_379;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_381 <= _tmp_380;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_382 <= _tmp_381;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_383 <= _tmp_382;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_384 <= _tmp_383;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_385 <= _tmp_384;
      end 
      if(_mul_rshift_round_clip_2_stream_oready) begin
        _tmp_386 <= _mul_rshift_round_clip_2_sink_busy;
      end 
      if(!_mul_rshift_round_clip_2_sink_busy && _tmp_386) begin
        _mul_rshift_round_clip_2_busy_reg <= 0;
      end 
      if(_mul_rshift_round_clip_2_source_busy) begin
        _mul_rshift_round_clip_2_busy_reg <= 1;
      end 
    end
  end

  localparam _mul_rshift_round_clip_2_fsm_1 = 1;
  localparam _mul_rshift_round_clip_2_fsm_2 = 2;
  localparam _mul_rshift_round_clip_2_fsm_3 = 3;

  always @(posedge CLK) begin
    if(RST) begin
      _mul_rshift_round_clip_2_fsm <= _mul_rshift_round_clip_2_fsm_init;
      _mul_rshift_round_clip_2_source_start <= 0;
      _mul_rshift_round_clip_2_source_busy <= 0;
      _mul_rshift_round_clip_2_stream_ivalid <= 0;
    end else begin
      if(__stream_matmul_11_stream_ivalid_18 && _stream_matmul_11_stream_oready) begin
        _mul_rshift_round_clip_2_stream_ivalid <= 1'd1;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_busy) begin
        _mul_rshift_round_clip_2_source_busy <= _stream_matmul_11_source_busy;
      end 
      if(_mul_rshift_round_clip_2_stream_oready && _tmp_355) begin
        _mul_rshift_round_clip_2_stream_ivalid <= 1;
      end 
      if(_mul_rshift_round_clip_2_stream_oready && 1'd0) begin
        _mul_rshift_round_clip_2_stream_ivalid <= 0;
      end 
      case(_mul_rshift_round_clip_2_fsm)
        _mul_rshift_round_clip_2_fsm_init: begin
          if(_mul_rshift_round_clip_2_run_flag) begin
            _mul_rshift_round_clip_2_source_start <= 1;
          end 
          if(_mul_rshift_round_clip_2_run_flag) begin
            _mul_rshift_round_clip_2_fsm <= _mul_rshift_round_clip_2_fsm_1;
          end 
        end
        _mul_rshift_round_clip_2_fsm_1: begin
          if(_mul_rshift_round_clip_2_source_start && _mul_rshift_round_clip_2_stream_oready) begin
            _mul_rshift_round_clip_2_source_start <= 0;
            _mul_rshift_round_clip_2_source_busy <= 1;
          end 
          if(_mul_rshift_round_clip_2_source_start && _mul_rshift_round_clip_2_stream_oready) begin
            _mul_rshift_round_clip_2_fsm <= _mul_rshift_round_clip_2_fsm_2;
          end 
        end
        _mul_rshift_round_clip_2_fsm_2: begin
          if(_mul_rshift_round_clip_2_stream_oready) begin
            _mul_rshift_round_clip_2_fsm <= _mul_rshift_round_clip_2_fsm_3;
          end 
        end
        _mul_rshift_round_clip_2_fsm_3: begin
          if(_mul_rshift_round_clip_2_stream_oready && 1'd0) begin
            _mul_rshift_round_clip_2_source_busy <= 0;
          end 
          if(_mul_rshift_round_clip_2_stream_oready && 1'd0 && _mul_rshift_round_clip_2_run_flag) begin
            _mul_rshift_round_clip_2_source_start <= 1;
          end 
          if(_mul_rshift_round_clip_2_stream_oready && 1'd0) begin
            _mul_rshift_round_clip_2_fsm <= _mul_rshift_round_clip_2_fsm_init;
          end 
          if(_mul_rshift_round_clip_2_stream_oready && 1'd0 && _mul_rshift_round_clip_2_run_flag) begin
            _mul_rshift_round_clip_2_fsm <= _mul_rshift_round_clip_2_fsm_1;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _mul_3_x_source_ram_renable <= 0;
      _mul_3_x_source_fifo_deq <= 0;
      _mul_3_x_idle <= 1;
      _mul_3_y_source_ram_renable <= 0;
      _mul_3_y_source_fifo_deq <= 0;
      _mul_3_y_idle <= 1;
      _mul_3_rshift_source_ram_renable <= 0;
      _mul_3_rshift_source_fifo_deq <= 0;
      _mul_3_rshift_idle <= 1;
      _mul_3_z_sink_wenable <= 0;
      _mul_3_z_sink_fifo_enq <= 0;
      __mul_3_stream_ivalid_1 <= 0;
      __mul_3_stream_ivalid_2 <= 0;
      __mul_3_stream_ivalid_3 <= 0;
      __mul_3_stream_ivalid_4 <= 0;
      __mul_3_stream_ivalid_5 <= 0;
      __mul_3_stream_ivalid_6 <= 0;
      __mul_3_stream_ivalid_7 <= 0;
      __mul_3_stream_ivalid_8 <= 0;
      _greaterthan_data_61 <= 0;
      _minus_data_63 <= 0;
      _greatereq_data_74 <= 0;
      __delay_data_161__variable_58 <= 0;
      __delay_data_164__variable_59 <= 0;
      __delay_data_167__variable_60 <= 0;
      _sll_data_65 <= 0;
      __delay_data_158_greaterthan_61 <= 0;
      __delay_data_159_greatereq_74 <= 0;
      __delay_data_162__delay_161__variable_58 <= 0;
      __delay_data_165__delay_164__variable_59 <= 0;
      __delay_data_168__delay_167__variable_60 <= 0;
      _cond_data_71 <= 0;
      __delay_data_160__delay_159_greatereq_74 <= 0;
      __delay_data_163__delay_162__delay_161__variable_58 <= 0;
      __delay_data_166__delay_165__delay_164__variable_59 <= 0;
      __delay_data_169__delay_168__delay_167__variable_60 <= 0;
      __muladd_madd_odata_reg_77 <= 0;
      __delay_data_170__delay_169__delay_168__delay_167__variable_60 <= 0;
      __delay_data_171__delay_170__delay_169__delay_168____variable_60 <= 0;
      __delay_data_172__delay_171__delay_170__delay_169____variable_60 <= 0;
      __delay_data_173__delay_172__delay_171__delay_170____variable_60 <= 0;
      _sra_data_78 <= 0;
      __variable_wdata_58 <= 0;
      __variable_wdata_59 <= 0;
      __variable_wdata_60 <= 0;
      _tmp_277 <= 0;
      _tmp_278 <= 0;
      _tmp_279 <= 0;
      _tmp_280 <= 0;
      _tmp_281 <= 0;
      _tmp_282 <= 0;
      _tmp_283 <= 0;
      _tmp_284 <= 0;
      _tmp_285 <= 0;
      _tmp_286 <= 0;
      _tmp_287 <= 0;
      _tmp_288 <= 0;
      _tmp_289 <= 0;
      _tmp_290 <= 0;
      _tmp_291 <= 0;
      _tmp_292 <= 0;
      _tmp_293 <= 0;
      _tmp_294 <= 0;
      _tmp_295 <= 0;
      _tmp_296 <= 0;
      _tmp_297 <= 0;
      _tmp_298 <= 0;
      _tmp_299 <= 0;
      _tmp_300 <= 0;
      _tmp_301 <= 0;
      _tmp_302 <= 0;
      _tmp_303 <= 0;
      _tmp_304 <= 0;
      _tmp_305 <= 0;
      _tmp_306 <= 0;
      _tmp_307 <= 0;
      _tmp_308 <= 0;
      _tmp_309 <= 0;
      _tmp_310 <= 0;
      _mul_3_busy_reg <= 0;
    end else begin
      if(_mul_3_stream_oready) begin
        _mul_3_x_source_ram_renable <= 0;
        _mul_3_x_source_fifo_deq <= 0;
      end 
      _mul_3_x_idle <= _mul_3_x_idle;
      if(_mul_3_stream_oready) begin
        _mul_3_y_source_ram_renable <= 0;
        _mul_3_y_source_fifo_deq <= 0;
      end 
      _mul_3_y_idle <= _mul_3_y_idle;
      if(_mul_3_stream_oready) begin
        _mul_3_rshift_source_ram_renable <= 0;
        _mul_3_rshift_source_fifo_deq <= 0;
      end 
      _mul_3_rshift_idle <= _mul_3_rshift_idle;
      if(_mul_3_stream_oready) begin
        _mul_3_z_sink_wenable <= 0;
        _mul_3_z_sink_fifo_enq <= 0;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_1 <= _mul_3_stream_ivalid;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_2 <= __mul_3_stream_ivalid_1;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_3 <= __mul_3_stream_ivalid_2;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_4 <= __mul_3_stream_ivalid_3;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_5 <= __mul_3_stream_ivalid_4;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_6 <= __mul_3_stream_ivalid_5;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_7 <= __mul_3_stream_ivalid_6;
      end 
      if(_mul_3_stream_oready) begin
        __mul_3_stream_ivalid_8 <= __mul_3_stream_ivalid_7;
      end 
      if(_mul_3_stream_oready) begin
        _greaterthan_data_61 <= mul_3_rshift_data > 1'sd0;
      end 
      if(_mul_3_stream_oready) begin
        _minus_data_63 <= mul_3_rshift_data - 2'sd1;
      end 
      if(_mul_3_stream_oready) begin
        _greatereq_data_74 <= mul_3_x_data >= 1'sd0;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_161__variable_58 <= mul_3_x_data;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_164__variable_59 <= mul_3_y_data;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_167__variable_60 <= mul_3_rshift_data;
      end 
      if(_mul_3_stream_oready) begin
        _sll_data_65 <= 2'sd1 << _minus_data_63;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_158_greaterthan_61 <= _greaterthan_data_61;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_159_greatereq_74 <= _greatereq_data_74;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_162__delay_161__variable_58 <= __delay_data_161__variable_58;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_165__delay_164__variable_59 <= __delay_data_164__variable_59;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_168__delay_167__variable_60 <= __delay_data_167__variable_60;
      end 
      if(_mul_3_stream_oready) begin
        _cond_data_71 <= (__delay_data_158_greaterthan_61)? _sll_data_65 : 1'sd0;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_160__delay_159_greatereq_74 <= __delay_data_159_greatereq_74;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_163__delay_162__delay_161__variable_58 <= __delay_data_162__delay_161__variable_58;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_166__delay_165__delay_164__variable_59 <= __delay_data_165__delay_164__variable_59;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_169__delay_168__delay_167__variable_60 <= __delay_data_168__delay_167__variable_60;
      end 
      if(_mul_3_stream_oready) begin
        __muladd_madd_odata_reg_77 <= __muladd_madd_odata_77;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_170__delay_169__delay_168__delay_167__variable_60 <= __delay_data_169__delay_168__delay_167__variable_60;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_171__delay_170__delay_169__delay_168____variable_60 <= __delay_data_170__delay_169__delay_168__delay_167__variable_60;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_172__delay_171__delay_170__delay_169____variable_60 <= __delay_data_171__delay_170__delay_169__delay_168____variable_60;
      end 
      if(_mul_3_stream_oready) begin
        __delay_data_173__delay_172__delay_171__delay_170____variable_60 <= __delay_data_172__delay_171__delay_170__delay_169____variable_60;
      end 
      if(_mul_3_stream_oready) begin
        _sra_data_78 <= __muladd_data_77 >>> __delay_data_173__delay_172__delay_171__delay_170____variable_60;
      end 
      if(__stream_matmul_11_stream_ivalid_1 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_58 <= _cond_data_156;
      end 
      if(__stream_matmul_11_stream_ivalid_1 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_59 <= __delay_data_224_reinterpretcast_152;
      end 
      if(__stream_matmul_11_stream_ivalid_1 && _stream_matmul_11_stream_oready) begin
        __variable_wdata_60 <= _plus_data_174;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_277 <= _mul_3_source_start;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_278 <= _tmp_277;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_279 <= _tmp_278;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_280 <= _mul_3_source_start;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_281 <= _tmp_280;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_282 <= _tmp_281;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_283 <= _tmp_282;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_284 <= _tmp_283;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_285 <= _tmp_284;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_286 <= _tmp_285;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_287 <= _tmp_286;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_288 <= _tmp_287;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_289 <= _tmp_288;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_290 <= _mul_3_source_stop;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_291 <= _tmp_290;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_292 <= _tmp_291;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_293 <= _tmp_292;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_294 <= _tmp_293;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_295 <= _tmp_294;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_296 <= _tmp_295;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_297 <= _tmp_296;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_298 <= _tmp_297;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_299 <= _tmp_298;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_300 <= _mul_3_source_busy;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_301 <= _tmp_300;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_302 <= _tmp_301;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_303 <= _tmp_302;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_304 <= _tmp_303;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_305 <= _tmp_304;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_306 <= _tmp_305;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_307 <= _tmp_306;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_308 <= _tmp_307;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_309 <= _tmp_308;
      end 
      if(_mul_3_stream_oready) begin
        _tmp_310 <= _mul_3_sink_busy;
      end 
      if(!_mul_3_sink_busy && _tmp_310) begin
        _mul_3_busy_reg <= 0;
      end 
      if(_mul_3_source_busy) begin
        _mul_3_busy_reg <= 1;
      end 
    end
  end

  localparam _mul_3_fsm_1 = 1;
  localparam _mul_3_fsm_2 = 2;
  localparam _mul_3_fsm_3 = 3;

  always @(posedge CLK) begin
    if(RST) begin
      _mul_3_fsm <= _mul_3_fsm_init;
      _mul_3_source_start <= 0;
      _mul_3_source_busy <= 0;
      _mul_3_stream_ivalid <= 0;
    end else begin
      if(__stream_matmul_11_stream_ivalid_1 && _stream_matmul_11_stream_oready) begin
        _mul_3_stream_ivalid <= 1'd1;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_busy) begin
        _mul_3_source_busy <= _stream_matmul_11_source_busy;
      end 
      if(_mul_3_stream_oready && _tmp_279) begin
        _mul_3_stream_ivalid <= 1;
      end 
      if(_mul_3_stream_oready && 1'd0) begin
        _mul_3_stream_ivalid <= 0;
      end 
      case(_mul_3_fsm)
        _mul_3_fsm_init: begin
          if(_mul_3_run_flag) begin
            _mul_3_source_start <= 1;
          end 
          if(_mul_3_run_flag) begin
            _mul_3_fsm <= _mul_3_fsm_1;
          end 
        end
        _mul_3_fsm_1: begin
          if(_mul_3_source_start && _mul_3_stream_oready) begin
            _mul_3_source_start <= 0;
            _mul_3_source_busy <= 1;
          end 
          if(_mul_3_source_start && _mul_3_stream_oready) begin
            _mul_3_fsm <= _mul_3_fsm_2;
          end 
        end
        _mul_3_fsm_2: begin
          if(_mul_3_stream_oready) begin
            _mul_3_fsm <= _mul_3_fsm_3;
          end 
        end
        _mul_3_fsm_3: begin
          if(_mul_3_stream_oready && 1'd0) begin
            _mul_3_source_busy <= 0;
          end 
          if(_mul_3_stream_oready && 1'd0 && _mul_3_run_flag) begin
            _mul_3_source_start <= 1;
          end 
          if(_mul_3_stream_oready && 1'd0) begin
            _mul_3_fsm <= _mul_3_fsm_init;
          end 
          if(_mul_3_stream_oready && 1'd0 && _mul_3_run_flag) begin
            _mul_3_fsm <= _mul_3_fsm_1;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _stream_matmul_11_source_7_source_ram_renable <= 0;
      _stream_matmul_11_source_7_source_fifo_deq <= 0;
      _stream_matmul_11_source_7_idle <= 1;
      _stream_matmul_11_source_9_source_ram_renable <= 0;
      _stream_matmul_11_source_9_source_fifo_deq <= 0;
      _stream_matmul_11_source_9_idle <= 1;
      _stream_matmul_11_source_11_source_ram_renable <= 0;
      _stream_matmul_11_source_11_source_fifo_deq <= 0;
      _stream_matmul_11_source_11_idle <= 1;
      _stream_matmul_11_source_13_source_ram_renable <= 0;
      _stream_matmul_11_source_13_source_fifo_deq <= 0;
      _stream_matmul_11_source_13_idle <= 1;
      _stream_matmul_11_source_15_source_ram_renable <= 0;
      _stream_matmul_11_source_15_source_fifo_deq <= 0;
      _stream_matmul_11_source_15_idle <= 1;
      _stream_matmul_11_source_20_source_ram_renable <= 0;
      _stream_matmul_11_source_20_source_fifo_deq <= 0;
      _stream_matmul_11_source_20_idle <= 1;
      _stream_matmul_11_source_21_source_ram_renable <= 0;
      _stream_matmul_11_source_21_source_fifo_deq <= 0;
      _stream_matmul_11_source_21_idle <= 1;
      _stream_matmul_11_sink_26_sink_wenable <= 0;
      _stream_matmul_11_sink_26_sink_fifo_enq <= 0;
      _stream_matmul_11_sink_27_sink_wenable <= 0;
      _stream_matmul_11_sink_27_sink_fifo_enq <= 0;
      __stream_matmul_11_stream_ivalid_1 <= 0;
      __stream_matmul_11_stream_ivalid_2 <= 0;
      __stream_matmul_11_stream_ivalid_3 <= 0;
      __stream_matmul_11_stream_ivalid_4 <= 0;
      __stream_matmul_11_stream_ivalid_5 <= 0;
      __stream_matmul_11_stream_ivalid_6 <= 0;
      __stream_matmul_11_stream_ivalid_7 <= 0;
      __stream_matmul_11_stream_ivalid_8 <= 0;
      __stream_matmul_11_stream_ivalid_9 <= 0;
      __stream_matmul_11_stream_ivalid_10 <= 0;
      __stream_matmul_11_stream_ivalid_11 <= 0;
      __stream_matmul_11_stream_ivalid_12 <= 0;
      __stream_matmul_11_stream_ivalid_13 <= 0;
      __stream_matmul_11_stream_ivalid_14 <= 0;
      __stream_matmul_11_stream_ivalid_15 <= 0;
      __stream_matmul_11_stream_ivalid_16 <= 0;
      __stream_matmul_11_stream_ivalid_17 <= 0;
      __stream_matmul_11_stream_ivalid_18 <= 0;
      __stream_matmul_11_stream_ivalid_19 <= 0;
      __stream_matmul_11_stream_ivalid_20 <= 0;
      __stream_matmul_11_stream_ivalid_21 <= 0;
      __stream_matmul_11_stream_ivalid_22 <= 0;
      __stream_matmul_11_stream_ivalid_23 <= 0;
      __stream_matmul_11_stream_ivalid_24 <= 0;
      __stream_matmul_11_stream_ivalid_25 <= 0;
      __stream_matmul_11_stream_ivalid_26 <= 0;
      __stream_matmul_11_stream_ivalid_27 <= 0;
      __stream_matmul_11_stream_ivalid_28 <= 0;
      __stream_matmul_11_stream_ivalid_29 <= 0;
      _eq_data_134 <= 0;
      _eq_data_138 <= 0;
      _plus_data_174 <= 0;
      _plus_data_190 <= 0;
      _plus_data_209 <= 0;
      _eq_data_215 <= 0;
      _eq_data_218 <= 0;
      __delay_data_222__variable_133 <= 0;
      __delay_data_223_pointer_153 <= 0;
      __delay_data_224_reinterpretcast_152 <= 0;
      __delay_data_225__variable_84 <= 0;
      __delay_data_246__variable_79 <= 0;
      __delay_data_257_cond_100 <= 0;
      __delay_data_274_cond_107 <= 0;
      __delay_data_226__delay_225__variable_84 <= 0;
      __delay_data_236_plus_190 <= 0;
      __delay_data_247__delay_246__variable_79 <= 0;
      __delay_data_258__delay_257_cond_100 <= 0;
      __delay_data_275__delay_274_cond_107 <= 0;
      __delay_data_292_plus_209 <= 0;
      __delay_data_310_eq_215 <= 0;
      __delay_data_339_eq_218 <= 0;
      __delay_data_227__delay_226__delay_225__variable_84 <= 0;
      __delay_data_237__delay_236_plus_190 <= 0;
      __delay_data_248__delay_247__delay_246__variable_79 <= 0;
      __delay_data_259__delay_258__delay_257_cond_100 <= 0;
      __delay_data_276__delay_275__delay_274_cond_107 <= 0;
      __delay_data_293__delay_292_plus_209 <= 0;
      __delay_data_311__delay_310_eq_215 <= 0;
      __delay_data_340__delay_339_eq_218 <= 0;
      __delay_data_228__delay_227__delay_226__delay_225__variable_84 <= 0;
      __delay_data_238__delay_237__delay_236_plus_190 <= 0;
      __delay_data_249__delay_248__delay_247__delay_246__variable_79 <= 0;
      __delay_data_260__delay_259__delay_258__delay_257_cond_100 <= 0;
      __delay_data_277__delay_276__delay_275__delay_274_cond_107 <= 0;
      __delay_data_294__delay_293__delay_292_plus_209 <= 0;
      __delay_data_312__delay_311__delay_310_eq_215 <= 0;
      __delay_data_341__delay_340__delay_339_eq_218 <= 0;
      __delay_data_229__delay_228__delay_227__delay_226____variable_84 <= 0;
      __delay_data_239__delay_238__delay_237__delay_236_plus_190 <= 0;
      __delay_data_250__delay_249__delay_248__delay_247____variable_79 <= 0;
      __delay_data_261__delay_260__delay_259__delay_258___cond_100 <= 0;
      __delay_data_278__delay_277__delay_276__delay_275___cond_107 <= 0;
      __delay_data_295__delay_294__delay_293__delay_292_plus_209 <= 0;
      __delay_data_313__delay_312__delay_311__delay_310_eq_215 <= 0;
      __delay_data_342__delay_341__delay_340__delay_339_eq_218 <= 0;
      __delay_data_230__delay_229__delay_228__delay_227____variable_84 <= 0;
      __delay_data_240__delay_239__delay_238__delay_237___plus_190 <= 0;
      __delay_data_251__delay_250__delay_249__delay_248____variable_79 <= 0;
      __delay_data_262__delay_261__delay_260__delay_259___cond_100 <= 0;
      __delay_data_279__delay_278__delay_277__delay_276___cond_107 <= 0;
      __delay_data_296__delay_295__delay_294__delay_293___plus_209 <= 0;
      __delay_data_314__delay_313__delay_312__delay_311___eq_215 <= 0;
      __delay_data_343__delay_342__delay_341__delay_340___eq_218 <= 0;
      __delay_data_231__delay_230__delay_229__delay_228____variable_84 <= 0;
      __delay_data_241__delay_240__delay_239__delay_238___plus_190 <= 0;
      __delay_data_252__delay_251__delay_250__delay_249____variable_79 <= 0;
      __delay_data_263__delay_262__delay_261__delay_260___cond_100 <= 0;
      __delay_data_280__delay_279__delay_278__delay_277___cond_107 <= 0;
      __delay_data_297__delay_296__delay_295__delay_294___plus_209 <= 0;
      __delay_data_315__delay_314__delay_313__delay_312___eq_215 <= 0;
      __delay_data_344__delay_343__delay_342__delay_341___eq_218 <= 0;
      __delay_data_232__delay_231__delay_230__delay_229____variable_84 <= 0;
      __delay_data_242__delay_241__delay_240__delay_239___plus_190 <= 0;
      __delay_data_253__delay_252__delay_251__delay_250____variable_79 <= 0;
      __delay_data_264__delay_263__delay_262__delay_261___cond_100 <= 0;
      __delay_data_281__delay_280__delay_279__delay_278___cond_107 <= 0;
      __delay_data_298__delay_297__delay_296__delay_295___plus_209 <= 0;
      __delay_data_316__delay_315__delay_314__delay_313___eq_215 <= 0;
      __delay_data_345__delay_344__delay_343__delay_342___eq_218 <= 0;
      __delay_data_233__delay_232__delay_231__delay_230____variable_84 <= 0;
      __delay_data_243__delay_242__delay_241__delay_240___plus_190 <= 0;
      __delay_data_254__delay_253__delay_252__delay_251____variable_79 <= 0;
      __delay_data_265__delay_264__delay_263__delay_262___cond_100 <= 0;
      __delay_data_282__delay_281__delay_280__delay_279___cond_107 <= 0;
      __delay_data_299__delay_298__delay_297__delay_296___plus_209 <= 0;
      __delay_data_317__delay_316__delay_315__delay_314___eq_215 <= 0;
      __delay_data_346__delay_345__delay_344__delay_343___eq_218 <= 0;
      __delay_data_234__delay_233__delay_232__delay_231____variable_84 <= 0;
      __delay_data_244__delay_243__delay_242__delay_241___plus_190 <= 0;
      __delay_data_255__delay_254__delay_253__delay_252____variable_79 <= 0;
      __delay_data_266__delay_265__delay_264__delay_263___cond_100 <= 0;
      __delay_data_283__delay_282__delay_281__delay_280___cond_107 <= 0;
      __delay_data_300__delay_299__delay_298__delay_297___plus_209 <= 0;
      __delay_data_318__delay_317__delay_316__delay_315___eq_215 <= 0;
      __delay_data_347__delay_346__delay_345__delay_344___eq_218 <= 0;
      __delay_data_235__delay_234__delay_233__delay_232____variable_84 <= 0;
      __delay_data_245__delay_244__delay_243__delay_242___plus_190 <= 0;
      __delay_data_256__delay_255__delay_254__delay_253____variable_79 <= 0;
      __delay_data_267__delay_266__delay_265__delay_264___cond_100 <= 0;
      __delay_data_284__delay_283__delay_282__delay_281___cond_107 <= 0;
      __delay_data_301__delay_300__delay_299__delay_298___plus_209 <= 0;
      __delay_data_319__delay_318__delay_317__delay_316___eq_215 <= 0;
      __delay_data_348__delay_347__delay_346__delay_345___eq_218 <= 0;
      __delay_data_268__delay_267__delay_266__delay_265___cond_100 <= 0;
      __delay_data_285__delay_284__delay_283__delay_282___cond_107 <= 0;
      __delay_data_302__delay_301__delay_300__delay_299___plus_209 <= 0;
      __delay_data_320__delay_319__delay_318__delay_317___eq_215 <= 0;
      __delay_data_349__delay_348__delay_347__delay_346___eq_218 <= 0;
      __delay_data_269__delay_268__delay_267__delay_266___cond_100 <= 0;
      __delay_data_286__delay_285__delay_284__delay_283___cond_107 <= 0;
      __delay_data_303__delay_302__delay_301__delay_300___plus_209 <= 0;
      __delay_data_321__delay_320__delay_319__delay_318___eq_215 <= 0;
      __delay_data_350__delay_349__delay_348__delay_347___eq_218 <= 0;
      __delay_data_270__delay_269__delay_268__delay_267___cond_100 <= 0;
      __delay_data_287__delay_286__delay_285__delay_284___cond_107 <= 0;
      __delay_data_304__delay_303__delay_302__delay_301___plus_209 <= 0;
      __delay_data_322__delay_321__delay_320__delay_319___eq_215 <= 0;
      __delay_data_351__delay_350__delay_349__delay_348___eq_218 <= 0;
      __delay_data_271__delay_270__delay_269__delay_268___cond_100 <= 0;
      __delay_data_288__delay_287__delay_286__delay_285___cond_107 <= 0;
      __delay_data_305__delay_304__delay_303__delay_302___plus_209 <= 0;
      __delay_data_323__delay_322__delay_321__delay_320___eq_215 <= 0;
      __delay_data_352__delay_351__delay_350__delay_349___eq_218 <= 0;
      __delay_data_272__delay_271__delay_270__delay_269___cond_100 <= 0;
      __delay_data_289__delay_288__delay_287__delay_286___cond_107 <= 0;
      __delay_data_306__delay_305__delay_304__delay_303___plus_209 <= 0;
      __delay_data_324__delay_323__delay_322__delay_321___eq_215 <= 0;
      __delay_data_353__delay_352__delay_351__delay_350___eq_218 <= 0;
      __delay_data_273__delay_272__delay_271__delay_270___cond_100 <= 0;
      __delay_data_290__delay_289__delay_288__delay_287___cond_107 <= 0;
      __delay_data_307__delay_306__delay_305__delay_304___plus_209 <= 0;
      __delay_data_325__delay_324__delay_323__delay_322___eq_215 <= 0;
      __delay_data_354__delay_353__delay_352__delay_351___eq_218 <= 0;
      _plus_data_193 <= 0;
      __delay_data_291__delay_290__delay_289__delay_288___cond_107 <= 0;
      __delay_data_308__delay_307__delay_306__delay_305___plus_209 <= 0;
      __delay_data_326__delay_325__delay_324__delay_323___eq_215 <= 0;
      __delay_data_355__delay_354__delay_353__delay_352___eq_218 <= 0;
      __delay_data_367__substreamoutput_192 <= 0;
      __delay_data_327__delay_326__delay_325__delay_324___eq_215 <= 0;
      __delay_data_356__delay_355__delay_354__delay_353___eq_218 <= 0;
      __delay_data_368__delay_367__substreamoutput_192 <= 0;
      __delay_data_328__delay_327__delay_326__delay_325___eq_215 <= 0;
      __delay_data_357__delay_356__delay_355__delay_354___eq_218 <= 0;
      __delay_data_369__delay_368__delay_367__substreamoutput_192 <= 0;
      __delay_data_329__delay_328__delay_327__delay_326___eq_215 <= 0;
      __delay_data_358__delay_357__delay_356__delay_355___eq_218 <= 0;
      __delay_data_370__delay_369__delay_368____substreamoutput_192 <= 0;
      __delay_data_330__delay_329__delay_328__delay_327___eq_215 <= 0;
      __delay_data_359__delay_358__delay_357__delay_356___eq_218 <= 0;
      __delay_data_371__delay_370__delay_369____substreamoutput_192 <= 0;
      __delay_data_331__delay_330__delay_329__delay_328___eq_215 <= 0;
      __delay_data_360__delay_359__delay_358__delay_357___eq_218 <= 0;
      __delay_data_372__delay_371__delay_370____substreamoutput_192 <= 0;
      __delay_data_332__delay_331__delay_330__delay_329___eq_215 <= 0;
      __delay_data_361__delay_360__delay_359__delay_358___eq_218 <= 0;
      __delay_data_373__delay_372__delay_371____substreamoutput_192 <= 0;
      __delay_data_333__delay_332__delay_331__delay_330___eq_215 <= 0;
      __delay_data_362__delay_361__delay_360__delay_359___eq_218 <= 0;
      __delay_data_374__delay_373__delay_372____substreamoutput_192 <= 0;
      __delay_data_334__delay_333__delay_332__delay_331___eq_215 <= 0;
      __delay_data_363__delay_362__delay_361__delay_360___eq_218 <= 0;
      __delay_data_375__delay_374__delay_373____substreamoutput_192 <= 0;
      __delay_data_335__delay_334__delay_333__delay_332___eq_215 <= 0;
      __delay_data_364__delay_363__delay_362__delay_361___eq_218 <= 0;
      __delay_data_376__delay_375__delay_374____substreamoutput_192 <= 0;
      _greaterthan_data_212 <= 0;
      __delay_data_309__substreamoutput_210 <= 0;
      __delay_data_336__delay_335__delay_334__delay_333___eq_215 <= 0;
      __delay_data_365__delay_364__delay_363__delay_362___eq_218 <= 0;
      __delay_data_377__delay_376__delay_375____substreamoutput_192 <= 0;
      _cond_data_214 <= 0;
      __delay_data_337__delay_336__delay_335__delay_334___eq_215 <= 0;
      __delay_data_338__delay_309__substreamoutput_210 <= 0;
      __delay_data_366__delay_365__delay_364__delay_363___eq_218 <= 0;
      __delay_data_378__delay_377__delay_376____substreamoutput_192 <= 0;
      _stream_matmul_11_parameter_0_next_parameter_data <= 0;
      __variable_wdata_79 <= 0;
      _stream_matmul_11_parameter_1_next_parameter_data <= 0;
      __variable_wdata_80 <= 0;
      _stream_matmul_11_parameter_2_next_parameter_data <= 0;
      __variable_wdata_81 <= 0;
      _stream_matmul_11_parameter_3_next_parameter_data <= 0;
      __variable_wdata_82 <= 0;
      _stream_matmul_11_parameter_4_next_parameter_data <= 0;
      __variable_wdata_83 <= 0;
      _stream_matmul_11_parameter_6_next_parameter_data <= 0;
      __variable_wdata_94 <= 0;
      _stream_matmul_11_source_7_source_mode <= 5'b0;
      _stream_matmul_11_source_7_source_offset <= 0;
      _source_stream_matmul_11_source_7_pat_size_0 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_0 <= 0;
      _source_stream_matmul_11_source_7_pat_size_1 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_1 <= 0;
      _source_stream_matmul_11_source_7_pat_size_2 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_2 <= 0;
      _source_stream_matmul_11_source_7_pat_size_3 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_3 <= 0;
      _stream_matmul_11_source_7_source_sel <= 0;
      _stream_matmul_11_source_7_source_offset_buf <= 0;
      _source_stream_matmul_11_source_7_pat_cur_offset_0 <= 0;
      _source_stream_matmul_11_source_7_pat_cur_offset_1 <= 0;
      _source_stream_matmul_11_source_7_pat_cur_offset_2 <= 0;
      _source_stream_matmul_11_source_7_pat_cur_offset_3 <= 0;
      _source_stream_matmul_11_source_7_pat_count_0 <= 0;
      _source_stream_matmul_11_source_7_pat_count_1 <= 0;
      _source_stream_matmul_11_source_7_pat_count_2 <= 0;
      _source_stream_matmul_11_source_7_pat_count_3 <= 0;
      _source_stream_matmul_11_source_7_pat_size_buf_0 <= 0;
      _source_stream_matmul_11_source_7_pat_size_buf_1 <= 0;
      _source_stream_matmul_11_source_7_pat_size_buf_2 <= 0;
      _source_stream_matmul_11_source_7_pat_size_buf_3 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_buf_0 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_buf_1 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_buf_2 <= 0;
      _source_stream_matmul_11_source_7_pat_stride_buf_3 <= 0;
      __variable_wdata_95 <= 0;
      _stream_matmul_11_source_7_source_ram_raddr <= 0;
      _stream_matmul_11_parameter_8_next_parameter_data <= 0;
      __variable_wdata_101 <= 0;
      _stream_matmul_11_source_9_source_mode <= 5'b0;
      _stream_matmul_11_source_9_source_offset <= 0;
      _source_stream_matmul_11_source_9_pat_size_0 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_0 <= 0;
      _source_stream_matmul_11_source_9_pat_size_1 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_1 <= 0;
      _source_stream_matmul_11_source_9_pat_size_2 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_2 <= 0;
      _source_stream_matmul_11_source_9_pat_size_3 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_3 <= 0;
      _stream_matmul_11_source_9_source_sel <= 0;
      _stream_matmul_11_source_9_source_offset_buf <= 0;
      _source_stream_matmul_11_source_9_pat_cur_offset_0 <= 0;
      _source_stream_matmul_11_source_9_pat_cur_offset_1 <= 0;
      _source_stream_matmul_11_source_9_pat_cur_offset_2 <= 0;
      _source_stream_matmul_11_source_9_pat_cur_offset_3 <= 0;
      _source_stream_matmul_11_source_9_pat_count_0 <= 0;
      _source_stream_matmul_11_source_9_pat_count_1 <= 0;
      _source_stream_matmul_11_source_9_pat_count_2 <= 0;
      _source_stream_matmul_11_source_9_pat_count_3 <= 0;
      _source_stream_matmul_11_source_9_pat_size_buf_0 <= 0;
      _source_stream_matmul_11_source_9_pat_size_buf_1 <= 0;
      _source_stream_matmul_11_source_9_pat_size_buf_2 <= 0;
      _source_stream_matmul_11_source_9_pat_size_buf_3 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_buf_0 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_buf_1 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_buf_2 <= 0;
      _source_stream_matmul_11_source_9_pat_stride_buf_3 <= 0;
      __variable_wdata_102 <= 0;
      _stream_matmul_11_source_9_source_ram_raddr <= 0;
      _stream_matmul_11_parameter_10_next_parameter_data <= 0;
      __variable_wdata_108 <= 0;
      _stream_matmul_11_source_11_source_mode <= 5'b0;
      _stream_matmul_11_source_11_source_empty_data <= 0;
      __variable_wdata_109 <= 0;
      _stream_matmul_11_parameter_12_next_parameter_data <= 0;
      __variable_wdata_115 <= 0;
      _stream_matmul_11_source_13_source_mode <= 5'b0;
      _stream_matmul_11_source_13_source_empty_data <= 0;
      __variable_wdata_116 <= 0;
      _stream_matmul_11_parameter_14_next_parameter_data <= 0;
      __variable_wdata_122 <= 0;
      _stream_matmul_11_source_15_source_mode <= 5'b0;
      _stream_matmul_11_source_15_source_empty_data <= 0;
      __variable_wdata_123 <= 0;
      _stream_matmul_11_parameter_16_next_parameter_data <= 0;
      __variable_wdata_129 <= 0;
      _stream_matmul_11_parameter_17_next_parameter_data <= 0;
      __variable_wdata_130 <= 0;
      _stream_matmul_11_parameter_18_next_parameter_data <= 0;
      __variable_wdata_131 <= 0;
      _stream_matmul_11_parameter_19_next_parameter_data <= 0;
      __variable_wdata_132 <= 0;
      _stream_matmul_11_source_20_source_mode <= 5'b0;
      _stream_matmul_11_source_20_source_offset <= 0;
      _source_stream_matmul_11_source_20_pat_size_0 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_0 <= 0;
      _source_stream_matmul_11_source_20_pat_size_1 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_1 <= 0;
      _source_stream_matmul_11_source_20_pat_size_2 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_2 <= 0;
      _source_stream_matmul_11_source_20_pat_size_3 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_3 <= 0;
      _stream_matmul_11_source_20_source_sel <= 0;
      _stream_matmul_11_source_20_source_offset_buf <= 0;
      _source_stream_matmul_11_source_20_pat_cur_offset_0 <= 0;
      _source_stream_matmul_11_source_20_pat_cur_offset_1 <= 0;
      _source_stream_matmul_11_source_20_pat_cur_offset_2 <= 0;
      _source_stream_matmul_11_source_20_pat_cur_offset_3 <= 0;
      _source_stream_matmul_11_source_20_pat_count_0 <= 0;
      _source_stream_matmul_11_source_20_pat_count_1 <= 0;
      _source_stream_matmul_11_source_20_pat_count_2 <= 0;
      _source_stream_matmul_11_source_20_pat_count_3 <= 0;
      _source_stream_matmul_11_source_20_pat_size_buf_0 <= 0;
      _source_stream_matmul_11_source_20_pat_size_buf_1 <= 0;
      _source_stream_matmul_11_source_20_pat_size_buf_2 <= 0;
      _source_stream_matmul_11_source_20_pat_size_buf_3 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_buf_0 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_buf_1 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_buf_2 <= 0;
      _source_stream_matmul_11_source_20_pat_stride_buf_3 <= 0;
      __variable_wdata_133 <= 0;
      _stream_matmul_11_source_20_source_ram_raddr <= 0;
      _stream_matmul_11_source_21_source_mode <= 5'b0;
      _stream_matmul_11_source_21_source_offset <= 0;
      _source_stream_matmul_11_source_21_pat_size_0 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_0 <= 0;
      _source_stream_matmul_11_source_21_pat_size_1 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_1 <= 0;
      _source_stream_matmul_11_source_21_pat_size_2 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_2 <= 0;
      _source_stream_matmul_11_source_21_pat_size_3 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_3 <= 0;
      _stream_matmul_11_source_21_source_sel <= 0;
      _stream_matmul_11_source_21_source_offset_buf <= 0;
      _source_stream_matmul_11_source_21_pat_cur_offset_0 <= 0;
      _source_stream_matmul_11_source_21_pat_cur_offset_1 <= 0;
      _source_stream_matmul_11_source_21_pat_cur_offset_2 <= 0;
      _source_stream_matmul_11_source_21_pat_cur_offset_3 <= 0;
      _source_stream_matmul_11_source_21_pat_count_0 <= 0;
      _source_stream_matmul_11_source_21_pat_count_1 <= 0;
      _source_stream_matmul_11_source_21_pat_count_2 <= 0;
      _source_stream_matmul_11_source_21_pat_count_3 <= 0;
      _source_stream_matmul_11_source_21_pat_size_buf_0 <= 0;
      _source_stream_matmul_11_source_21_pat_size_buf_1 <= 0;
      _source_stream_matmul_11_source_21_pat_size_buf_2 <= 0;
      _source_stream_matmul_11_source_21_pat_size_buf_3 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_buf_0 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_buf_1 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_buf_2 <= 0;
      _source_stream_matmul_11_source_21_pat_stride_buf_3 <= 0;
      __variable_wdata_147 <= 0;
      _stream_matmul_11_source_21_source_ram_raddr <= 0;
      _tmp_180 <= 0;
      _tmp_181 <= 0;
      _tmp_182 <= 0;
      _tmp_183 <= 0;
      _tmp_184 <= 0;
      _tmp_185 <= 0;
      _tmp_186 <= 0;
      _tmp_187 <= 0;
      _tmp_188 <= 0;
      _tmp_189 <= 0;
      _tmp_190 <= 0;
      _tmp_191 <= 0;
      _tmp_192 <= 0;
      _tmp_193 <= 0;
      _tmp_194 <= 0;
      _tmp_195 <= 0;
      _tmp_196 <= 0;
      _tmp_197 <= 0;
      _tmp_198 <= 0;
      _tmp_199 <= 0;
      _tmp_200 <= 0;
      _tmp_201 <= 0;
      _tmp_202 <= 0;
      _tmp_203 <= 0;
      _tmp_204 <= 0;
      _tmp_205 <= 0;
      _tmp_206 <= 0;
      _tmp_207 <= 0;
      _tmp_208 <= 0;
      _tmp_209 <= 0;
      _tmp_210 <= 0;
      _tmp_213 <= 0;
      _tmp_214 <= 0;
      _tmp_215 <= 0;
      _tmp_216 <= 0;
      _tmp_217 <= 0;
      _tmp_218 <= 0;
      _tmp_219 <= 0;
      _tmp_220 <= 0;
      _tmp_221 <= 0;
      _tmp_222 <= 0;
      _tmp_223 <= 0;
      _tmp_224 <= 0;
      _tmp_225 <= 0;
      _tmp_226 <= 0;
      _tmp_227 <= 0;
      _tmp_228 <= 0;
      _tmp_229 <= 0;
      _tmp_230 <= 0;
      _tmp_231 <= 0;
      _tmp_232 <= 0;
      _tmp_233 <= 0;
      _tmp_234 <= 0;
      _tmp_235 <= 0;
      _tmp_236 <= 0;
      _tmp_237 <= 0;
      _tmp_238 <= 0;
      _tmp_239 <= 0;
      _tmp_240 <= 0;
      _tmp_241 <= 0;
      _tmp_242 <= 0;
      _tmp_243 <= 0;
      _tmp_244 <= 0;
      _tmp_245 <= 0;
      _tmp_246 <= 0;
      _tmp_247 <= 0;
      _tmp_248 <= 0;
      _tmp_249 <= 0;
      _tmp_250 <= 0;
      _tmp_251 <= 0;
      _tmp_252 <= 0;
      _tmp_253 <= 0;
      _tmp_254 <= 0;
      _tmp_255 <= 0;
      _tmp_256 <= 0;
      _tmp_257 <= 0;
      _tmp_258 <= 0;
      _tmp_259 <= 0;
      _tmp_260 <= 0;
      _tmp_261 <= 0;
      _tmp_262 <= 0;
      _tmp_263 <= 0;
      _tmp_264 <= 0;
      _tmp_265 <= 0;
      _tmp_266 <= 0;
      _tmp_267 <= 0;
      _tmp_268 <= 0;
      _tmp_269 <= 0;
      _tmp_270 <= 0;
      _tmp_271 <= 0;
      _tmp_272 <= 0;
      _tmp_273 <= 0;
      _tmp_274 <= 0;
      _stream_matmul_11_sink_26_sink_mode <= 5'b0;
      _stream_matmul_11_sink_26_sink_offset <= 0;
      _stream_matmul_11_sink_26_sink_size <= 0;
      _stream_matmul_11_sink_26_sink_stride <= 0;
      _stream_matmul_11_sink_26_sink_sel <= 0;
      _stream_matmul_11_sink_26_sink_offset_buf <= 0;
      _stream_matmul_11_sink_26_sink_size_buf <= 0;
      _stream_matmul_11_sink_26_sink_stride_buf <= 0;
      _stream_matmul_11_sink_26_sink_waddr <= 0;
      _stream_matmul_11_sink_26_sink_count <= 0;
      _stream_matmul_11_sink_26_sink_wdata <= 0;
      _tmp_387 <= 0;
      _tmp_388 <= 0;
      _tmp_389 <= 0;
      _tmp_390 <= 0;
      _tmp_391 <= 0;
      _tmp_392 <= 0;
      __variable_wdata_84 <= 0;
      _tmp_393 <= 0;
      _tmp_394 <= 0;
      _tmp_395 <= 0;
      _tmp_396 <= 0;
      _tmp_399 <= 0;
      _tmp_402 <= 0;
      _tmp_403 <= 0;
      _tmp_404 <= 0;
      _tmp_405 <= 0;
      _tmp_406 <= 0;
      _tmp_407 <= 0;
      _tmp_408 <= 0;
      _tmp_409 <= 0;
      _tmp_410 <= 0;
      _tmp_411 <= 0;
      _tmp_412 <= 0;
      _tmp_413 <= 0;
      _tmp_414 <= 0;
      _tmp_415 <= 0;
      _tmp_416 <= 0;
      _tmp_417 <= 0;
      _tmp_418 <= 0;
      _tmp_419 <= 0;
      _tmp_420 <= 0;
      _tmp_421 <= 0;
      _tmp_422 <= 0;
      _tmp_423 <= 0;
      _tmp_424 <= 0;
      _tmp_425 <= 0;
      _tmp_426 <= 0;
      _tmp_427 <= 0;
      _tmp_428 <= 0;
      _tmp_429 <= 0;
      _tmp_430 <= 0;
      _tmp_431 <= 0;
      _tmp_432 <= 0;
      _tmp_433 <= 0;
      _tmp_434 <= 0;
      _tmp_435 <= 0;
      _tmp_436 <= 0;
      _tmp_437 <= 0;
      _tmp_438 <= 0;
      _tmp_439 <= 0;
      _tmp_440 <= 0;
      _tmp_441 <= 0;
      _tmp_442 <= 0;
      _tmp_443 <= 0;
      _tmp_444 <= 0;
      _tmp_445 <= 0;
      _tmp_446 <= 0;
      _tmp_447 <= 0;
      _tmp_448 <= 0;
      _tmp_449 <= 0;
      _tmp_450 <= 0;
      _tmp_451 <= 0;
      _tmp_452 <= 0;
      _tmp_453 <= 0;
      _tmp_454 <= 0;
      _tmp_455 <= 0;
      _tmp_456 <= 0;
      _tmp_457 <= 0;
      _tmp_458 <= 0;
      _tmp_459 <= 0;
      _tmp_460 <= 0;
      _tmp_461 <= 0;
      _tmp_462 <= 0;
      _tmp_463 <= 0;
      _tmp_464 <= 0;
      _tmp_465 <= 0;
      _tmp_466 <= 0;
      _tmp_467 <= 0;
      _tmp_468 <= 0;
      _tmp_469 <= 0;
      _tmp_470 <= 0;
      _tmp_471 <= 0;
      _tmp_472 <= 0;
      _tmp_473 <= 0;
      _tmp_474 <= 0;
      _tmp_475 <= 0;
      _tmp_476 <= 0;
      _tmp_477 <= 0;
      _tmp_478 <= 0;
      _tmp_479 <= 0;
      _tmp_480 <= 0;
      _tmp_481 <= 0;
      _tmp_482 <= 0;
      _tmp_483 <= 0;
      _tmp_484 <= 0;
      _tmp_485 <= 0;
      _tmp_486 <= 0;
      _tmp_487 <= 0;
      _tmp_488 <= 0;
      _tmp_489 <= 0;
      _tmp_490 <= 0;
      _tmp_491 <= 0;
      _tmp_492 <= 0;
      _tmp_493 <= 0;
      _tmp_494 <= 0;
      _tmp_495 <= 0;
      _tmp_496 <= 0;
      _stream_matmul_11_busy_reg <= 0;
    end else begin
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_7_source_ram_renable <= 0;
        _stream_matmul_11_source_7_source_fifo_deq <= 0;
      end 
      _stream_matmul_11_source_7_idle <= _stream_matmul_11_source_7_idle;
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_9_source_ram_renable <= 0;
        _stream_matmul_11_source_9_source_fifo_deq <= 0;
      end 
      _stream_matmul_11_source_9_idle <= _stream_matmul_11_source_9_idle;
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_11_source_ram_renable <= 0;
        _stream_matmul_11_source_11_source_fifo_deq <= 0;
      end 
      _stream_matmul_11_source_11_idle <= _stream_matmul_11_source_11_idle;
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_13_source_ram_renable <= 0;
        _stream_matmul_11_source_13_source_fifo_deq <= 0;
      end 
      _stream_matmul_11_source_13_idle <= _stream_matmul_11_source_13_idle;
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_15_source_ram_renable <= 0;
        _stream_matmul_11_source_15_source_fifo_deq <= 0;
      end 
      _stream_matmul_11_source_15_idle <= _stream_matmul_11_source_15_idle;
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_20_source_ram_renable <= 0;
        _stream_matmul_11_source_20_source_fifo_deq <= 0;
      end 
      _stream_matmul_11_source_20_idle <= _stream_matmul_11_source_20_idle;
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_21_source_ram_renable <= 0;
        _stream_matmul_11_source_21_source_fifo_deq <= 0;
      end 
      _stream_matmul_11_source_21_idle <= _stream_matmul_11_source_21_idle;
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_sink_26_sink_wenable <= 0;
        _stream_matmul_11_sink_26_sink_fifo_enq <= 0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _stream_matmul_11_sink_27_sink_wenable <= 0;
        _stream_matmul_11_sink_27_sink_fifo_enq <= 0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_1 <= _stream_matmul_11_stream_ivalid;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_2 <= __stream_matmul_11_stream_ivalid_1;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_3 <= __stream_matmul_11_stream_ivalid_2;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_4 <= __stream_matmul_11_stream_ivalid_3;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_5 <= __stream_matmul_11_stream_ivalid_4;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_6 <= __stream_matmul_11_stream_ivalid_5;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_7 <= __stream_matmul_11_stream_ivalid_6;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_8 <= __stream_matmul_11_stream_ivalid_7;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_9 <= __stream_matmul_11_stream_ivalid_8;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_10 <= __stream_matmul_11_stream_ivalid_9;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_11 <= __stream_matmul_11_stream_ivalid_10;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_12 <= __stream_matmul_11_stream_ivalid_11;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_13 <= __stream_matmul_11_stream_ivalid_12;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_14 <= __stream_matmul_11_stream_ivalid_13;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_15 <= __stream_matmul_11_stream_ivalid_14;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_16 <= __stream_matmul_11_stream_ivalid_15;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_17 <= __stream_matmul_11_stream_ivalid_16;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_18 <= __stream_matmul_11_stream_ivalid_17;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_19 <= __stream_matmul_11_stream_ivalid_18;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_20 <= __stream_matmul_11_stream_ivalid_19;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_21 <= __stream_matmul_11_stream_ivalid_20;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_22 <= __stream_matmul_11_stream_ivalid_21;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_23 <= __stream_matmul_11_stream_ivalid_22;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_24 <= __stream_matmul_11_stream_ivalid_23;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_25 <= __stream_matmul_11_stream_ivalid_24;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_26 <= __stream_matmul_11_stream_ivalid_25;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_27 <= __stream_matmul_11_stream_ivalid_26;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_28 <= __stream_matmul_11_stream_ivalid_27;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __stream_matmul_11_stream_ivalid_29 <= __stream_matmul_11_stream_ivalid_28;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _eq_data_134 <= stream_matmul_11_parameter_1_data == 1'sd0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _eq_data_138 <= stream_matmul_11_parameter_2_data == 1'sd0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _plus_data_174 <= _cond_data_114 + stream_matmul_11_parameter_16_data;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _plus_data_190 <= _cond_data_121 + stream_matmul_11_parameter_17_data;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _plus_data_209 <= _cond_data_128 + stream_matmul_11_parameter_18_data;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _eq_data_215 <= stream_matmul_11_parameter_19_data == 1'sd0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _eq_data_218 <= stream_matmul_11_parameter_19_data == 2'sd1;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_222__variable_133 <= stream_matmul_11_source_20_data;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_223_pointer_153 <= _pointer_data_153;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_224_reinterpretcast_152 <= _reinterpretcast_data_152;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_225__variable_84 <= stream_matmul_11__reduce_reset_data;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_246__variable_79 <= stream_matmul_11_parameter_0_data;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_257_cond_100 <= _cond_data_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_274_cond_107 <= _cond_data_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_226__delay_225__variable_84 <= __delay_data_225__variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_236_plus_190 <= _plus_data_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_247__delay_246__variable_79 <= __delay_data_246__variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_258__delay_257_cond_100 <= __delay_data_257_cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_275__delay_274_cond_107 <= __delay_data_274_cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_292_plus_209 <= _plus_data_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_310_eq_215 <= _eq_data_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_339_eq_218 <= _eq_data_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_227__delay_226__delay_225__variable_84 <= __delay_data_226__delay_225__variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_237__delay_236_plus_190 <= __delay_data_236_plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_248__delay_247__delay_246__variable_79 <= __delay_data_247__delay_246__variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_259__delay_258__delay_257_cond_100 <= __delay_data_258__delay_257_cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_276__delay_275__delay_274_cond_107 <= __delay_data_275__delay_274_cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_293__delay_292_plus_209 <= __delay_data_292_plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_311__delay_310_eq_215 <= __delay_data_310_eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_340__delay_339_eq_218 <= __delay_data_339_eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_228__delay_227__delay_226__delay_225__variable_84 <= __delay_data_227__delay_226__delay_225__variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_238__delay_237__delay_236_plus_190 <= __delay_data_237__delay_236_plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_249__delay_248__delay_247__delay_246__variable_79 <= __delay_data_248__delay_247__delay_246__variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_260__delay_259__delay_258__delay_257_cond_100 <= __delay_data_259__delay_258__delay_257_cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_277__delay_276__delay_275__delay_274_cond_107 <= __delay_data_276__delay_275__delay_274_cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_294__delay_293__delay_292_plus_209 <= __delay_data_293__delay_292_plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_312__delay_311__delay_310_eq_215 <= __delay_data_311__delay_310_eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_341__delay_340__delay_339_eq_218 <= __delay_data_340__delay_339_eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_229__delay_228__delay_227__delay_226____variable_84 <= __delay_data_228__delay_227__delay_226__delay_225__variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_239__delay_238__delay_237__delay_236_plus_190 <= __delay_data_238__delay_237__delay_236_plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_250__delay_249__delay_248__delay_247____variable_79 <= __delay_data_249__delay_248__delay_247__delay_246__variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_261__delay_260__delay_259__delay_258___cond_100 <= __delay_data_260__delay_259__delay_258__delay_257_cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_278__delay_277__delay_276__delay_275___cond_107 <= __delay_data_277__delay_276__delay_275__delay_274_cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_295__delay_294__delay_293__delay_292_plus_209 <= __delay_data_294__delay_293__delay_292_plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_313__delay_312__delay_311__delay_310_eq_215 <= __delay_data_312__delay_311__delay_310_eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_342__delay_341__delay_340__delay_339_eq_218 <= __delay_data_341__delay_340__delay_339_eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_230__delay_229__delay_228__delay_227____variable_84 <= __delay_data_229__delay_228__delay_227__delay_226____variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_240__delay_239__delay_238__delay_237___plus_190 <= __delay_data_239__delay_238__delay_237__delay_236_plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_251__delay_250__delay_249__delay_248____variable_79 <= __delay_data_250__delay_249__delay_248__delay_247____variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_262__delay_261__delay_260__delay_259___cond_100 <= __delay_data_261__delay_260__delay_259__delay_258___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_279__delay_278__delay_277__delay_276___cond_107 <= __delay_data_278__delay_277__delay_276__delay_275___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_296__delay_295__delay_294__delay_293___plus_209 <= __delay_data_295__delay_294__delay_293__delay_292_plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_314__delay_313__delay_312__delay_311___eq_215 <= __delay_data_313__delay_312__delay_311__delay_310_eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_343__delay_342__delay_341__delay_340___eq_218 <= __delay_data_342__delay_341__delay_340__delay_339_eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_231__delay_230__delay_229__delay_228____variable_84 <= __delay_data_230__delay_229__delay_228__delay_227____variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_241__delay_240__delay_239__delay_238___plus_190 <= __delay_data_240__delay_239__delay_238__delay_237___plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_252__delay_251__delay_250__delay_249____variable_79 <= __delay_data_251__delay_250__delay_249__delay_248____variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_263__delay_262__delay_261__delay_260___cond_100 <= __delay_data_262__delay_261__delay_260__delay_259___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_280__delay_279__delay_278__delay_277___cond_107 <= __delay_data_279__delay_278__delay_277__delay_276___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_297__delay_296__delay_295__delay_294___plus_209 <= __delay_data_296__delay_295__delay_294__delay_293___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_315__delay_314__delay_313__delay_312___eq_215 <= __delay_data_314__delay_313__delay_312__delay_311___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_344__delay_343__delay_342__delay_341___eq_218 <= __delay_data_343__delay_342__delay_341__delay_340___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_232__delay_231__delay_230__delay_229____variable_84 <= __delay_data_231__delay_230__delay_229__delay_228____variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_242__delay_241__delay_240__delay_239___plus_190 <= __delay_data_241__delay_240__delay_239__delay_238___plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_253__delay_252__delay_251__delay_250____variable_79 <= __delay_data_252__delay_251__delay_250__delay_249____variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_264__delay_263__delay_262__delay_261___cond_100 <= __delay_data_263__delay_262__delay_261__delay_260___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_281__delay_280__delay_279__delay_278___cond_107 <= __delay_data_280__delay_279__delay_278__delay_277___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_298__delay_297__delay_296__delay_295___plus_209 <= __delay_data_297__delay_296__delay_295__delay_294___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_316__delay_315__delay_314__delay_313___eq_215 <= __delay_data_315__delay_314__delay_313__delay_312___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_345__delay_344__delay_343__delay_342___eq_218 <= __delay_data_344__delay_343__delay_342__delay_341___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_233__delay_232__delay_231__delay_230____variable_84 <= __delay_data_232__delay_231__delay_230__delay_229____variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_243__delay_242__delay_241__delay_240___plus_190 <= __delay_data_242__delay_241__delay_240__delay_239___plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_254__delay_253__delay_252__delay_251____variable_79 <= __delay_data_253__delay_252__delay_251__delay_250____variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_265__delay_264__delay_263__delay_262___cond_100 <= __delay_data_264__delay_263__delay_262__delay_261___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_282__delay_281__delay_280__delay_279___cond_107 <= __delay_data_281__delay_280__delay_279__delay_278___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_299__delay_298__delay_297__delay_296___plus_209 <= __delay_data_298__delay_297__delay_296__delay_295___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_317__delay_316__delay_315__delay_314___eq_215 <= __delay_data_316__delay_315__delay_314__delay_313___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_346__delay_345__delay_344__delay_343___eq_218 <= __delay_data_345__delay_344__delay_343__delay_342___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_234__delay_233__delay_232__delay_231____variable_84 <= __delay_data_233__delay_232__delay_231__delay_230____variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_244__delay_243__delay_242__delay_241___plus_190 <= __delay_data_243__delay_242__delay_241__delay_240___plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_255__delay_254__delay_253__delay_252____variable_79 <= __delay_data_254__delay_253__delay_252__delay_251____variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_266__delay_265__delay_264__delay_263___cond_100 <= __delay_data_265__delay_264__delay_263__delay_262___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_283__delay_282__delay_281__delay_280___cond_107 <= __delay_data_282__delay_281__delay_280__delay_279___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_300__delay_299__delay_298__delay_297___plus_209 <= __delay_data_299__delay_298__delay_297__delay_296___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_318__delay_317__delay_316__delay_315___eq_215 <= __delay_data_317__delay_316__delay_315__delay_314___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_347__delay_346__delay_345__delay_344___eq_218 <= __delay_data_346__delay_345__delay_344__delay_343___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_235__delay_234__delay_233__delay_232____variable_84 <= __delay_data_234__delay_233__delay_232__delay_231____variable_84;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_245__delay_244__delay_243__delay_242___plus_190 <= __delay_data_244__delay_243__delay_242__delay_241___plus_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_256__delay_255__delay_254__delay_253____variable_79 <= __delay_data_255__delay_254__delay_253__delay_252____variable_79;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_267__delay_266__delay_265__delay_264___cond_100 <= __delay_data_266__delay_265__delay_264__delay_263___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_284__delay_283__delay_282__delay_281___cond_107 <= __delay_data_283__delay_282__delay_281__delay_280___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_301__delay_300__delay_299__delay_298___plus_209 <= __delay_data_300__delay_299__delay_298__delay_297___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_319__delay_318__delay_317__delay_316___eq_215 <= __delay_data_318__delay_317__delay_316__delay_315___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_348__delay_347__delay_346__delay_345___eq_218 <= __delay_data_347__delay_346__delay_345__delay_344___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_268__delay_267__delay_266__delay_265___cond_100 <= __delay_data_267__delay_266__delay_265__delay_264___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_285__delay_284__delay_283__delay_282___cond_107 <= __delay_data_284__delay_283__delay_282__delay_281___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_302__delay_301__delay_300__delay_299___plus_209 <= __delay_data_301__delay_300__delay_299__delay_298___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_320__delay_319__delay_318__delay_317___eq_215 <= __delay_data_319__delay_318__delay_317__delay_316___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_349__delay_348__delay_347__delay_346___eq_218 <= __delay_data_348__delay_347__delay_346__delay_345___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_269__delay_268__delay_267__delay_266___cond_100 <= __delay_data_268__delay_267__delay_266__delay_265___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_286__delay_285__delay_284__delay_283___cond_107 <= __delay_data_285__delay_284__delay_283__delay_282___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_303__delay_302__delay_301__delay_300___plus_209 <= __delay_data_302__delay_301__delay_300__delay_299___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_321__delay_320__delay_319__delay_318___eq_215 <= __delay_data_320__delay_319__delay_318__delay_317___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_350__delay_349__delay_348__delay_347___eq_218 <= __delay_data_349__delay_348__delay_347__delay_346___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_270__delay_269__delay_268__delay_267___cond_100 <= __delay_data_269__delay_268__delay_267__delay_266___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_287__delay_286__delay_285__delay_284___cond_107 <= __delay_data_286__delay_285__delay_284__delay_283___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_304__delay_303__delay_302__delay_301___plus_209 <= __delay_data_303__delay_302__delay_301__delay_300___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_322__delay_321__delay_320__delay_319___eq_215 <= __delay_data_321__delay_320__delay_319__delay_318___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_351__delay_350__delay_349__delay_348___eq_218 <= __delay_data_350__delay_349__delay_348__delay_347___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_271__delay_270__delay_269__delay_268___cond_100 <= __delay_data_270__delay_269__delay_268__delay_267___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_288__delay_287__delay_286__delay_285___cond_107 <= __delay_data_287__delay_286__delay_285__delay_284___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_305__delay_304__delay_303__delay_302___plus_209 <= __delay_data_304__delay_303__delay_302__delay_301___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_323__delay_322__delay_321__delay_320___eq_215 <= __delay_data_322__delay_321__delay_320__delay_319___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_352__delay_351__delay_350__delay_349___eq_218 <= __delay_data_351__delay_350__delay_349__delay_348___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_272__delay_271__delay_270__delay_269___cond_100 <= __delay_data_271__delay_270__delay_269__delay_268___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_289__delay_288__delay_287__delay_286___cond_107 <= __delay_data_288__delay_287__delay_286__delay_285___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_306__delay_305__delay_304__delay_303___plus_209 <= __delay_data_305__delay_304__delay_303__delay_302___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_324__delay_323__delay_322__delay_321___eq_215 <= __delay_data_323__delay_322__delay_321__delay_320___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_353__delay_352__delay_351__delay_350___eq_218 <= __delay_data_352__delay_351__delay_350__delay_349___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_273__delay_272__delay_271__delay_270___cond_100 <= __delay_data_272__delay_271__delay_270__delay_269___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_290__delay_289__delay_288__delay_287___cond_107 <= __delay_data_289__delay_288__delay_287__delay_286___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_307__delay_306__delay_305__delay_304___plus_209 <= __delay_data_306__delay_305__delay_304__delay_303___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_325__delay_324__delay_323__delay_322___eq_215 <= __delay_data_324__delay_323__delay_322__delay_321___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_354__delay_353__delay_352__delay_351___eq_218 <= __delay_data_353__delay_352__delay_351__delay_350___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _plus_data_193 <= __substreamoutput_data_191 + __delay_data_273__delay_272__delay_271__delay_270___cond_100;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_291__delay_290__delay_289__delay_288___cond_107 <= __delay_data_290__delay_289__delay_288__delay_287___cond_107;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_308__delay_307__delay_306__delay_305___plus_209 <= __delay_data_307__delay_306__delay_305__delay_304___plus_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_326__delay_325__delay_324__delay_323___eq_215 <= __delay_data_325__delay_324__delay_323__delay_322___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_355__delay_354__delay_353__delay_352___eq_218 <= __delay_data_354__delay_353__delay_352__delay_351___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_367__substreamoutput_192 <= __substreamoutput_data_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_327__delay_326__delay_325__delay_324___eq_215 <= __delay_data_326__delay_325__delay_324__delay_323___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_356__delay_355__delay_354__delay_353___eq_218 <= __delay_data_355__delay_354__delay_353__delay_352___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_368__delay_367__substreamoutput_192 <= __delay_data_367__substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_328__delay_327__delay_326__delay_325___eq_215 <= __delay_data_327__delay_326__delay_325__delay_324___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_357__delay_356__delay_355__delay_354___eq_218 <= __delay_data_356__delay_355__delay_354__delay_353___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_369__delay_368__delay_367__substreamoutput_192 <= __delay_data_368__delay_367__substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_329__delay_328__delay_327__delay_326___eq_215 <= __delay_data_328__delay_327__delay_326__delay_325___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_358__delay_357__delay_356__delay_355___eq_218 <= __delay_data_357__delay_356__delay_355__delay_354___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_370__delay_369__delay_368____substreamoutput_192 <= __delay_data_369__delay_368__delay_367__substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_330__delay_329__delay_328__delay_327___eq_215 <= __delay_data_329__delay_328__delay_327__delay_326___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_359__delay_358__delay_357__delay_356___eq_218 <= __delay_data_358__delay_357__delay_356__delay_355___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_371__delay_370__delay_369____substreamoutput_192 <= __delay_data_370__delay_369__delay_368____substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_331__delay_330__delay_329__delay_328___eq_215 <= __delay_data_330__delay_329__delay_328__delay_327___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_360__delay_359__delay_358__delay_357___eq_218 <= __delay_data_359__delay_358__delay_357__delay_356___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_372__delay_371__delay_370____substreamoutput_192 <= __delay_data_371__delay_370__delay_369____substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_332__delay_331__delay_330__delay_329___eq_215 <= __delay_data_331__delay_330__delay_329__delay_328___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_361__delay_360__delay_359__delay_358___eq_218 <= __delay_data_360__delay_359__delay_358__delay_357___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_373__delay_372__delay_371____substreamoutput_192 <= __delay_data_372__delay_371__delay_370____substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_333__delay_332__delay_331__delay_330___eq_215 <= __delay_data_332__delay_331__delay_330__delay_329___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_362__delay_361__delay_360__delay_359___eq_218 <= __delay_data_361__delay_360__delay_359__delay_358___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_374__delay_373__delay_372____substreamoutput_192 <= __delay_data_373__delay_372__delay_371____substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_334__delay_333__delay_332__delay_331___eq_215 <= __delay_data_333__delay_332__delay_331__delay_330___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_363__delay_362__delay_361__delay_360___eq_218 <= __delay_data_362__delay_361__delay_360__delay_359___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_375__delay_374__delay_373____substreamoutput_192 <= __delay_data_374__delay_373__delay_372____substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_335__delay_334__delay_333__delay_332___eq_215 <= __delay_data_334__delay_333__delay_332__delay_331___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_364__delay_363__delay_362__delay_361___eq_218 <= __delay_data_363__delay_362__delay_361__delay_360___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_376__delay_375__delay_374____substreamoutput_192 <= __delay_data_375__delay_374__delay_373____substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _greaterthan_data_212 <= __substreamoutput_data_210 > 1'sd0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_309__substreamoutput_210 <= __substreamoutput_data_210;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_336__delay_335__delay_334__delay_333___eq_215 <= __delay_data_335__delay_334__delay_333__delay_332___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_365__delay_364__delay_363__delay_362___eq_218 <= __delay_data_364__delay_363__delay_362__delay_361___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_377__delay_376__delay_375____substreamoutput_192 <= __delay_data_376__delay_375__delay_374____substreamoutput_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _cond_data_214 <= (_greaterthan_data_212)? __delay_data_309__substreamoutput_210 : 1'sd0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_337__delay_336__delay_335__delay_334___eq_215 <= __delay_data_336__delay_335__delay_334__delay_333___eq_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_338__delay_309__substreamoutput_210 <= __delay_data_309__substreamoutput_210;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_366__delay_365__delay_364__delay_363___eq_218 <= __delay_data_365__delay_364__delay_363__delay_362___eq_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        __delay_data_378__delay_377__delay_376____substreamoutput_192 <= __delay_data_377__delay_376__delay_375____substreamoutput_192;
      end 
      if(_set_flag_126) begin
        _stream_matmul_11_parameter_0_next_parameter_data <= cparam_matmul_11_stream_reduce_size;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_79 <= _stream_matmul_11_parameter_0_next_parameter_data;
      end 
      if(_set_flag_127) begin
        _stream_matmul_11_parameter_1_next_parameter_data <= matmul_11_col_select;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_80 <= _stream_matmul_11_parameter_1_next_parameter_data;
      end 
      if(_set_flag_128) begin
        _stream_matmul_11_parameter_2_next_parameter_data <= matmul_11_row_select_buf;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_81 <= _stream_matmul_11_parameter_2_next_parameter_data;
      end 
      if(_set_flag_129) begin
        _stream_matmul_11_parameter_3_next_parameter_data <= matmul_11_stream_pad_masks;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_82 <= _stream_matmul_11_parameter_3_next_parameter_data;
      end 
      if(_set_flag_130) begin
        _stream_matmul_11_parameter_4_next_parameter_data <= cparam_matmul_11_stream_omit_mask;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_83 <= _stream_matmul_11_parameter_4_next_parameter_data;
      end 
      if(_set_flag_131) begin
        _stream_matmul_11_parameter_6_next_parameter_data <= cparam_matmul_11_bias_scala;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_94 <= _stream_matmul_11_parameter_6_next_parameter_data;
      end 
      if(_set_flag_132) begin
        _stream_matmul_11_source_7_source_mode <= 5'b10;
        _stream_matmul_11_source_7_source_offset <= (cparam_matmul_11_bias_num == 1)? 0 : matmul_11_och_count_buf;
      end 
      if(_set_flag_132) begin
        _source_stream_matmul_11_source_7_pat_size_0 <= cparam_matmul_11_stream_reduce_size;
        _source_stream_matmul_11_source_7_pat_stride_0 <= 0;
      end 
      if(_set_flag_132) begin
        _source_stream_matmul_11_source_7_pat_size_1 <= matmul_11_next_stream_num_ops;
        _source_stream_matmul_11_source_7_pat_stride_1 <= (cparam_matmul_11_bias_num == 1)? 0 : 1;
      end 
      if(_set_flag_132) begin
        _source_stream_matmul_11_source_7_pat_size_2 <= 1;
        _source_stream_matmul_11_source_7_pat_stride_2 <= 0;
      end 
      if(_set_flag_132) begin
        _source_stream_matmul_11_source_7_pat_size_3 <= 1;
        _source_stream_matmul_11_source_7_pat_stride_3 <= 0;
      end 
      if(_set_flag_132) begin
        _stream_matmul_11_source_7_source_sel <= 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_7_source_offset_buf <= _stream_matmul_11_source_7_source_offset;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_0 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_1 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_2 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_3 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_count_0 <= _source_stream_matmul_11_source_7_pat_size_0 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_count_1 <= _source_stream_matmul_11_source_7_pat_size_1 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_count_2 <= _source_stream_matmul_11_source_7_pat_size_2 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_count_3 <= _source_stream_matmul_11_source_7_pat_size_3 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_size_buf_0 <= _source_stream_matmul_11_source_7_pat_size_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_size_buf_1 <= _source_stream_matmul_11_source_7_pat_size_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_size_buf_2 <= _source_stream_matmul_11_source_7_pat_size_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_size_buf_3 <= _source_stream_matmul_11_source_7_pat_size_3;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_stride_buf_0 <= _source_stream_matmul_11_source_7_pat_stride_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_stride_buf_1 <= _source_stream_matmul_11_source_7_pat_stride_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_stride_buf_2 <= _source_stream_matmul_11_source_7_pat_stride_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_stride_buf_3 <= _source_stream_matmul_11_source_7_pat_stride_3;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_busy && _stream_matmul_11_is_root) begin
        __variable_wdata_95 <= _stream_matmul_11_source_7_source_ram_rdata;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_7_idle <= 0;
        _stream_matmul_11_source_7_source_ram_raddr <= _stream_matmul_11_source_7_source_pat_all_offset;
        _stream_matmul_11_source_7_source_ram_renable <= 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_0 <= _source_stream_matmul_11_source_7_pat_cur_offset_0 + _source_stream_matmul_11_source_7_pat_stride_buf_0;
        _source_stream_matmul_11_source_7_pat_count_0 <= _source_stream_matmul_11_source_7_pat_count_0 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && (_source_stream_matmul_11_source_7_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_0 <= 0;
        _source_stream_matmul_11_source_7_pat_count_0 <= _source_stream_matmul_11_source_7_pat_size_buf_0 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && (_source_stream_matmul_11_source_7_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_1 <= _source_stream_matmul_11_source_7_pat_cur_offset_1 + _source_stream_matmul_11_source_7_pat_stride_buf_1;
        _source_stream_matmul_11_source_7_pat_count_1 <= _source_stream_matmul_11_source_7_pat_count_1 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && (_source_stream_matmul_11_source_7_pat_count_0 == 0) && (_source_stream_matmul_11_source_7_pat_count_1 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_1 <= 0;
        _source_stream_matmul_11_source_7_pat_count_1 <= _source_stream_matmul_11_source_7_pat_size_buf_1 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && ((_source_stream_matmul_11_source_7_pat_count_0 == 0) && (_source_stream_matmul_11_source_7_pat_count_1 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_2 <= _source_stream_matmul_11_source_7_pat_cur_offset_2 + _source_stream_matmul_11_source_7_pat_stride_buf_2;
        _source_stream_matmul_11_source_7_pat_count_2 <= _source_stream_matmul_11_source_7_pat_count_2 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && ((_source_stream_matmul_11_source_7_pat_count_0 == 0) && (_source_stream_matmul_11_source_7_pat_count_1 == 0)) && (_source_stream_matmul_11_source_7_pat_count_2 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_2 <= 0;
        _source_stream_matmul_11_source_7_pat_count_2 <= _source_stream_matmul_11_source_7_pat_size_buf_2 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && ((_source_stream_matmul_11_source_7_pat_count_0 == 0) && (_source_stream_matmul_11_source_7_pat_count_1 == 0) && (_source_stream_matmul_11_source_7_pat_count_2 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_3 <= _source_stream_matmul_11_source_7_pat_cur_offset_3 + _source_stream_matmul_11_source_7_pat_stride_buf_3;
        _source_stream_matmul_11_source_7_pat_count_3 <= _source_stream_matmul_11_source_7_pat_count_3 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && ((_source_stream_matmul_11_source_7_pat_count_0 == 0) && (_source_stream_matmul_11_source_7_pat_count_1 == 0) && (_source_stream_matmul_11_source_7_pat_count_2 == 0)) && (_source_stream_matmul_11_source_7_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_7_pat_cur_offset_3 <= 0;
        _source_stream_matmul_11_source_7_pat_count_3 <= _source_stream_matmul_11_source_7_pat_size_buf_3 - 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 1) && _stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_7_source_ram_renable <= 0;
        _stream_matmul_11_source_7_idle <= 1;
      end 
      if((_stream_matmul_11_source_7_source_pat_fsm_0 == 2) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_7_source_ram_renable <= 0;
        _stream_matmul_11_source_7_idle <= 1;
      end 
      if(_set_flag_141) begin
        _stream_matmul_11_parameter_8_next_parameter_data <= cparam_matmul_11_scale_scala;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_101 <= _stream_matmul_11_parameter_8_next_parameter_data;
      end 
      if(_set_flag_142) begin
        _stream_matmul_11_source_9_source_mode <= 5'b10;
        _stream_matmul_11_source_9_source_offset <= (cparam_matmul_11_scale_num == 1)? 0 : matmul_11_och_count_buf;
      end 
      if(_set_flag_142) begin
        _source_stream_matmul_11_source_9_pat_size_0 <= cparam_matmul_11_stream_reduce_size;
        _source_stream_matmul_11_source_9_pat_stride_0 <= 0;
      end 
      if(_set_flag_142) begin
        _source_stream_matmul_11_source_9_pat_size_1 <= matmul_11_next_stream_num_ops;
        _source_stream_matmul_11_source_9_pat_stride_1 <= (cparam_matmul_11_scale_num == 1)? 0 : 1;
      end 
      if(_set_flag_142) begin
        _source_stream_matmul_11_source_9_pat_size_2 <= 1;
        _source_stream_matmul_11_source_9_pat_stride_2 <= 0;
      end 
      if(_set_flag_142) begin
        _source_stream_matmul_11_source_9_pat_size_3 <= 1;
        _source_stream_matmul_11_source_9_pat_stride_3 <= 0;
      end 
      if(_set_flag_142) begin
        _stream_matmul_11_source_9_source_sel <= 2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_9_source_offset_buf <= _stream_matmul_11_source_9_source_offset;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_0 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_1 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_2 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_3 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_count_0 <= _source_stream_matmul_11_source_9_pat_size_0 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_count_1 <= _source_stream_matmul_11_source_9_pat_size_1 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_count_2 <= _source_stream_matmul_11_source_9_pat_size_2 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_count_3 <= _source_stream_matmul_11_source_9_pat_size_3 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_size_buf_0 <= _source_stream_matmul_11_source_9_pat_size_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_size_buf_1 <= _source_stream_matmul_11_source_9_pat_size_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_size_buf_2 <= _source_stream_matmul_11_source_9_pat_size_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_size_buf_3 <= _source_stream_matmul_11_source_9_pat_size_3;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_stride_buf_0 <= _source_stream_matmul_11_source_9_pat_stride_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_stride_buf_1 <= _source_stream_matmul_11_source_9_pat_stride_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_stride_buf_2 <= _source_stream_matmul_11_source_9_pat_stride_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_stride_buf_3 <= _source_stream_matmul_11_source_9_pat_stride_3;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_busy && _stream_matmul_11_is_root) begin
        __variable_wdata_102 <= _stream_matmul_11_source_9_source_ram_rdata;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_9_idle <= 0;
        _stream_matmul_11_source_9_source_ram_raddr <= _stream_matmul_11_source_9_source_pat_all_offset;
        _stream_matmul_11_source_9_source_ram_renable <= 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_0 <= _source_stream_matmul_11_source_9_pat_cur_offset_0 + _source_stream_matmul_11_source_9_pat_stride_buf_0;
        _source_stream_matmul_11_source_9_pat_count_0 <= _source_stream_matmul_11_source_9_pat_count_0 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && (_source_stream_matmul_11_source_9_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_0 <= 0;
        _source_stream_matmul_11_source_9_pat_count_0 <= _source_stream_matmul_11_source_9_pat_size_buf_0 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && (_source_stream_matmul_11_source_9_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_1 <= _source_stream_matmul_11_source_9_pat_cur_offset_1 + _source_stream_matmul_11_source_9_pat_stride_buf_1;
        _source_stream_matmul_11_source_9_pat_count_1 <= _source_stream_matmul_11_source_9_pat_count_1 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && (_source_stream_matmul_11_source_9_pat_count_0 == 0) && (_source_stream_matmul_11_source_9_pat_count_1 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_1 <= 0;
        _source_stream_matmul_11_source_9_pat_count_1 <= _source_stream_matmul_11_source_9_pat_size_buf_1 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && ((_source_stream_matmul_11_source_9_pat_count_0 == 0) && (_source_stream_matmul_11_source_9_pat_count_1 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_2 <= _source_stream_matmul_11_source_9_pat_cur_offset_2 + _source_stream_matmul_11_source_9_pat_stride_buf_2;
        _source_stream_matmul_11_source_9_pat_count_2 <= _source_stream_matmul_11_source_9_pat_count_2 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && ((_source_stream_matmul_11_source_9_pat_count_0 == 0) && (_source_stream_matmul_11_source_9_pat_count_1 == 0)) && (_source_stream_matmul_11_source_9_pat_count_2 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_2 <= 0;
        _source_stream_matmul_11_source_9_pat_count_2 <= _source_stream_matmul_11_source_9_pat_size_buf_2 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && ((_source_stream_matmul_11_source_9_pat_count_0 == 0) && (_source_stream_matmul_11_source_9_pat_count_1 == 0) && (_source_stream_matmul_11_source_9_pat_count_2 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_3 <= _source_stream_matmul_11_source_9_pat_cur_offset_3 + _source_stream_matmul_11_source_9_pat_stride_buf_3;
        _source_stream_matmul_11_source_9_pat_count_3 <= _source_stream_matmul_11_source_9_pat_count_3 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && ((_source_stream_matmul_11_source_9_pat_count_0 == 0) && (_source_stream_matmul_11_source_9_pat_count_1 == 0) && (_source_stream_matmul_11_source_9_pat_count_2 == 0)) && (_source_stream_matmul_11_source_9_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_9_pat_cur_offset_3 <= 0;
        _source_stream_matmul_11_source_9_pat_count_3 <= _source_stream_matmul_11_source_9_pat_size_buf_3 - 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 1) && _stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_9_source_ram_renable <= 0;
        _stream_matmul_11_source_9_idle <= 1;
      end 
      if((_stream_matmul_11_source_9_source_pat_fsm_1 == 2) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_9_source_ram_renable <= 0;
        _stream_matmul_11_source_9_idle <= 1;
      end 
      if(_set_flag_151) begin
        _stream_matmul_11_parameter_10_next_parameter_data <= 1;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_108 <= _stream_matmul_11_parameter_10_next_parameter_data;
      end 
      if(_set_flag_152) begin
        _stream_matmul_11_source_11_source_mode <= 5'b0;
        _stream_matmul_11_source_11_source_empty_data <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready && !(|(_stream_matmul_11_source_11_source_mode & 5'b0))) begin
        _stream_matmul_11_source_11_idle <= 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready && !(|(_stream_matmul_11_source_11_source_mode & 5'b0)) && _stream_matmul_11_is_root) begin
        __variable_wdata_109 <= _stream_matmul_11_source_11_source_empty_data;
      end 
      if(_set_flag_153) begin
        _stream_matmul_11_parameter_12_next_parameter_data <= 1;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_115 <= _stream_matmul_11_parameter_12_next_parameter_data;
      end 
      if(_set_flag_154) begin
        _stream_matmul_11_source_13_source_mode <= 5'b0;
        _stream_matmul_11_source_13_source_empty_data <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready && !(|(_stream_matmul_11_source_13_source_mode & 5'b0))) begin
        _stream_matmul_11_source_13_idle <= 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready && !(|(_stream_matmul_11_source_13_source_mode & 5'b0)) && _stream_matmul_11_is_root) begin
        __variable_wdata_116 <= _stream_matmul_11_source_13_source_empty_data;
      end 
      if(_set_flag_155) begin
        _stream_matmul_11_parameter_14_next_parameter_data <= 1;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_122 <= _stream_matmul_11_parameter_14_next_parameter_data;
      end 
      if(_set_flag_156) begin
        _stream_matmul_11_source_15_source_mode <= 5'b0;
        _stream_matmul_11_source_15_source_empty_data <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready && !(|(_stream_matmul_11_source_15_source_mode & 5'b0))) begin
        _stream_matmul_11_source_15_idle <= 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready && !(|(_stream_matmul_11_source_15_source_mode & 5'b0)) && _stream_matmul_11_is_root) begin
        __variable_wdata_123 <= _stream_matmul_11_source_15_source_empty_data;
      end 
      if(_set_flag_157) begin
        _stream_matmul_11_parameter_16_next_parameter_data <= cparam_matmul_11_cshamt_mul_value;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_129 <= _stream_matmul_11_parameter_16_next_parameter_data;
      end 
      if(_set_flag_158) begin
        _stream_matmul_11_parameter_17_next_parameter_data <= cparam_matmul_11_cshamt_sum_value;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_130 <= _stream_matmul_11_parameter_17_next_parameter_data;
      end 
      if(_set_flag_159) begin
        _stream_matmul_11_parameter_18_next_parameter_data <= cparam_matmul_11_cshamt_out_value;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_131 <= _stream_matmul_11_parameter_18_next_parameter_data;
      end 
      if(_set_flag_160) begin
        _stream_matmul_11_parameter_19_next_parameter_data <= cparam_matmul_11_act_func_index;
      end 
      if(_stream_matmul_11_source_start) begin
        __variable_wdata_132 <= _stream_matmul_11_parameter_19_next_parameter_data;
      end 
      if(_set_flag_161) begin
        _stream_matmul_11_source_20_source_mode <= 5'b10;
        _stream_matmul_11_source_20_source_offset <= matmul_11_stream_act_local_0 + matmul_11_act_page_comp_offset_buf_0;
      end 
      if(_set_flag_161) begin
        _source_stream_matmul_11_source_20_pat_size_0 <= cparam_matmul_11_stream_reduce_size;
        _source_stream_matmul_11_source_20_pat_stride_0 <= 1;
      end 
      if(_set_flag_161) begin
        _source_stream_matmul_11_source_20_pat_size_1 <= matmul_11_next_stream_num_ops;
        _source_stream_matmul_11_source_20_pat_stride_1 <= 0;
      end 
      if(_set_flag_161) begin
        _source_stream_matmul_11_source_20_pat_size_2 <= 1;
        _source_stream_matmul_11_source_20_pat_stride_2 <= 0;
      end 
      if(_set_flag_161) begin
        _source_stream_matmul_11_source_20_pat_size_3 <= 1;
        _source_stream_matmul_11_source_20_pat_stride_3 <= 0;
      end 
      if(_set_flag_161) begin
        _stream_matmul_11_source_20_source_sel <= 3;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_20_source_offset_buf <= _stream_matmul_11_source_20_source_offset;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_0 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_1 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_2 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_3 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_count_0 <= _source_stream_matmul_11_source_20_pat_size_0 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_count_1 <= _source_stream_matmul_11_source_20_pat_size_1 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_count_2 <= _source_stream_matmul_11_source_20_pat_size_2 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_count_3 <= _source_stream_matmul_11_source_20_pat_size_3 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_size_buf_0 <= _source_stream_matmul_11_source_20_pat_size_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_size_buf_1 <= _source_stream_matmul_11_source_20_pat_size_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_size_buf_2 <= _source_stream_matmul_11_source_20_pat_size_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_size_buf_3 <= _source_stream_matmul_11_source_20_pat_size_3;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_stride_buf_0 <= _source_stream_matmul_11_source_20_pat_stride_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_stride_buf_1 <= _source_stream_matmul_11_source_20_pat_stride_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_stride_buf_2 <= _source_stream_matmul_11_source_20_pat_stride_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_stride_buf_3 <= _source_stream_matmul_11_source_20_pat_stride_3;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_busy && _stream_matmul_11_is_root) begin
        __variable_wdata_133 <= _stream_matmul_11_source_20_source_ram_rdata;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_20_idle <= 0;
        _stream_matmul_11_source_20_source_ram_raddr <= _stream_matmul_11_source_20_source_pat_all_offset;
        _stream_matmul_11_source_20_source_ram_renable <= 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_0 <= _source_stream_matmul_11_source_20_pat_cur_offset_0 + _source_stream_matmul_11_source_20_pat_stride_buf_0;
        _source_stream_matmul_11_source_20_pat_count_0 <= _source_stream_matmul_11_source_20_pat_count_0 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && (_source_stream_matmul_11_source_20_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_0 <= 0;
        _source_stream_matmul_11_source_20_pat_count_0 <= _source_stream_matmul_11_source_20_pat_size_buf_0 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && (_source_stream_matmul_11_source_20_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_1 <= _source_stream_matmul_11_source_20_pat_cur_offset_1 + _source_stream_matmul_11_source_20_pat_stride_buf_1;
        _source_stream_matmul_11_source_20_pat_count_1 <= _source_stream_matmul_11_source_20_pat_count_1 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && (_source_stream_matmul_11_source_20_pat_count_0 == 0) && (_source_stream_matmul_11_source_20_pat_count_1 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_1 <= 0;
        _source_stream_matmul_11_source_20_pat_count_1 <= _source_stream_matmul_11_source_20_pat_size_buf_1 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && ((_source_stream_matmul_11_source_20_pat_count_0 == 0) && (_source_stream_matmul_11_source_20_pat_count_1 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_2 <= _source_stream_matmul_11_source_20_pat_cur_offset_2 + _source_stream_matmul_11_source_20_pat_stride_buf_2;
        _source_stream_matmul_11_source_20_pat_count_2 <= _source_stream_matmul_11_source_20_pat_count_2 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && ((_source_stream_matmul_11_source_20_pat_count_0 == 0) && (_source_stream_matmul_11_source_20_pat_count_1 == 0)) && (_source_stream_matmul_11_source_20_pat_count_2 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_2 <= 0;
        _source_stream_matmul_11_source_20_pat_count_2 <= _source_stream_matmul_11_source_20_pat_size_buf_2 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && ((_source_stream_matmul_11_source_20_pat_count_0 == 0) && (_source_stream_matmul_11_source_20_pat_count_1 == 0) && (_source_stream_matmul_11_source_20_pat_count_2 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_3 <= _source_stream_matmul_11_source_20_pat_cur_offset_3 + _source_stream_matmul_11_source_20_pat_stride_buf_3;
        _source_stream_matmul_11_source_20_pat_count_3 <= _source_stream_matmul_11_source_20_pat_count_3 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && ((_source_stream_matmul_11_source_20_pat_count_0 == 0) && (_source_stream_matmul_11_source_20_pat_count_1 == 0) && (_source_stream_matmul_11_source_20_pat_count_2 == 0)) && (_source_stream_matmul_11_source_20_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_20_pat_cur_offset_3 <= 0;
        _source_stream_matmul_11_source_20_pat_count_3 <= _source_stream_matmul_11_source_20_pat_size_buf_3 - 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 1) && _stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_20_source_ram_renable <= 0;
        _stream_matmul_11_source_20_idle <= 1;
      end 
      if((_stream_matmul_11_source_20_source_pat_fsm_2 == 2) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_20_source_ram_renable <= 0;
        _stream_matmul_11_source_20_idle <= 1;
      end 
      if(_set_flag_170) begin
        _stream_matmul_11_source_21_source_mode <= 5'b10;
        _stream_matmul_11_source_21_source_offset <= matmul_11_filter_page_comp_offset_buf;
      end 
      if(_set_flag_170) begin
        _source_stream_matmul_11_source_21_pat_size_0 <= cparam_matmul_11_stream_reduce_size;
        _source_stream_matmul_11_source_21_pat_stride_0 <= 1;
      end 
      if(_set_flag_170) begin
        _source_stream_matmul_11_source_21_pat_size_1 <= matmul_11_next_stream_num_ops;
        _source_stream_matmul_11_source_21_pat_stride_1 <= cparam_matmul_11_stream_aligned_reduce_size;
      end 
      if(_set_flag_170) begin
        _source_stream_matmul_11_source_21_pat_size_2 <= 1;
        _source_stream_matmul_11_source_21_pat_stride_2 <= 0;
      end 
      if(_set_flag_170) begin
        _source_stream_matmul_11_source_21_pat_size_3 <= 1;
        _source_stream_matmul_11_source_21_pat_stride_3 <= 0;
      end 
      if(_set_flag_170) begin
        _stream_matmul_11_source_21_source_sel <= 4;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_21_source_offset_buf <= _stream_matmul_11_source_21_source_offset;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_0 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_1 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_2 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_3 <= 0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_count_0 <= _source_stream_matmul_11_source_21_pat_size_0 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_count_1 <= _source_stream_matmul_11_source_21_pat_size_1 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_count_2 <= _source_stream_matmul_11_source_21_pat_size_2 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_count_3 <= _source_stream_matmul_11_source_21_pat_size_3 - 1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_size_buf_0 <= _source_stream_matmul_11_source_21_pat_size_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_size_buf_1 <= _source_stream_matmul_11_source_21_pat_size_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_size_buf_2 <= _source_stream_matmul_11_source_21_pat_size_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_size_buf_3 <= _source_stream_matmul_11_source_21_pat_size_3;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_stride_buf_0 <= _source_stream_matmul_11_source_21_pat_stride_0;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_stride_buf_1 <= _source_stream_matmul_11_source_21_pat_stride_1;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_stride_buf_2 <= _source_stream_matmul_11_source_21_pat_stride_2;
      end 
      if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_stride_buf_3 <= _source_stream_matmul_11_source_21_pat_stride_3;
      end 
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_busy && _stream_matmul_11_is_root) begin
        __variable_wdata_147 <= _stream_matmul_11_source_21_source_ram_rdata;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_21_idle <= 0;
        _stream_matmul_11_source_21_source_ram_raddr <= _stream_matmul_11_source_21_source_pat_all_offset;
        _stream_matmul_11_source_21_source_ram_renable <= 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_0 <= _source_stream_matmul_11_source_21_pat_cur_offset_0 + _source_stream_matmul_11_source_21_pat_stride_buf_0;
        _source_stream_matmul_11_source_21_pat_count_0 <= _source_stream_matmul_11_source_21_pat_count_0 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && (_source_stream_matmul_11_source_21_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_0 <= 0;
        _source_stream_matmul_11_source_21_pat_count_0 <= _source_stream_matmul_11_source_21_pat_size_buf_0 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && (_source_stream_matmul_11_source_21_pat_count_0 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_1 <= _source_stream_matmul_11_source_21_pat_cur_offset_1 + _source_stream_matmul_11_source_21_pat_stride_buf_1;
        _source_stream_matmul_11_source_21_pat_count_1 <= _source_stream_matmul_11_source_21_pat_count_1 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && (_source_stream_matmul_11_source_21_pat_count_0 == 0) && (_source_stream_matmul_11_source_21_pat_count_1 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_1 <= 0;
        _source_stream_matmul_11_source_21_pat_count_1 <= _source_stream_matmul_11_source_21_pat_size_buf_1 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && ((_source_stream_matmul_11_source_21_pat_count_0 == 0) && (_source_stream_matmul_11_source_21_pat_count_1 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_2 <= _source_stream_matmul_11_source_21_pat_cur_offset_2 + _source_stream_matmul_11_source_21_pat_stride_buf_2;
        _source_stream_matmul_11_source_21_pat_count_2 <= _source_stream_matmul_11_source_21_pat_count_2 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && ((_source_stream_matmul_11_source_21_pat_count_0 == 0) && (_source_stream_matmul_11_source_21_pat_count_1 == 0)) && (_source_stream_matmul_11_source_21_pat_count_2 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_2 <= 0;
        _source_stream_matmul_11_source_21_pat_count_2 <= _source_stream_matmul_11_source_21_pat_size_buf_2 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && ((_source_stream_matmul_11_source_21_pat_count_0 == 0) && (_source_stream_matmul_11_source_21_pat_count_1 == 0) && (_source_stream_matmul_11_source_21_pat_count_2 == 0)) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_3 <= _source_stream_matmul_11_source_21_pat_cur_offset_3 + _source_stream_matmul_11_source_21_pat_stride_buf_3;
        _source_stream_matmul_11_source_21_pat_count_3 <= _source_stream_matmul_11_source_21_pat_count_3 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && ((_source_stream_matmul_11_source_21_pat_count_0 == 0) && (_source_stream_matmul_11_source_21_pat_count_1 == 0) && (_source_stream_matmul_11_source_21_pat_count_2 == 0)) && (_source_stream_matmul_11_source_21_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
        _source_stream_matmul_11_source_21_pat_cur_offset_3 <= 0;
        _source_stream_matmul_11_source_21_pat_count_3 <= _source_stream_matmul_11_source_21_pat_size_buf_3 - 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 1) && _stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_21_source_ram_renable <= 0;
        _stream_matmul_11_source_21_idle <= 1;
      end 
      if((_stream_matmul_11_source_21_source_pat_fsm_3 == 2) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_source_21_source_ram_renable <= 0;
        _stream_matmul_11_source_21_idle <= 1;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_180 <= _set_flag_179;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_181 <= _tmp_180;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_182 <= _tmp_181;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_183 <= _tmp_182;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_184 <= _tmp_183;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_185 <= _tmp_184;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_186 <= _tmp_185;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_187 <= _tmp_186;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_188 <= _tmp_187;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_189 <= _tmp_188;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_190 <= _tmp_189;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_191 <= _tmp_190;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_192 <= _tmp_191;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_193 <= _tmp_192;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_194 <= _tmp_193;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_195 <= _tmp_194;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_196 <= _tmp_195;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_197 <= _tmp_196;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_198 <= _tmp_197;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_199 <= _tmp_198;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_200 <= _tmp_199;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_201 <= _tmp_200;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_202 <= _tmp_201;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_203 <= _tmp_202;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_204 <= _tmp_203;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_205 <= _tmp_204;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_206 <= _tmp_205;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_207 <= _tmp_206;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_208 <= _tmp_207;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_209 <= _tmp_208;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_210 <= _tmp_209;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_213 <= _tmp_212;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_214 <= _tmp_213;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_215 <= _tmp_214;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_216 <= _tmp_215;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_217 <= _tmp_216;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_218 <= _tmp_217;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_219 <= _tmp_218;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_220 <= _tmp_219;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_221 <= _tmp_220;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_222 <= _tmp_221;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_223 <= _tmp_222;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_224 <= _tmp_223;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_225 <= _tmp_224;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_226 <= _tmp_225;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_227 <= _tmp_226;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_228 <= _tmp_227;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_229 <= _tmp_228;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_230 <= _tmp_229;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_231 <= _tmp_230;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_232 <= _tmp_231;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_233 <= _tmp_232;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_234 <= _tmp_233;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_235 <= _tmp_234;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_236 <= _tmp_235;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_237 <= _tmp_236;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_238 <= _tmp_237;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_239 <= _tmp_238;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_240 <= _tmp_239;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_241 <= _tmp_240;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_242 <= _tmp_241;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_243 <= _tmp_242;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_244 <= matmul_11_next_stream_num_ops;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_245 <= _tmp_244;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_246 <= _tmp_245;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_247 <= _tmp_246;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_248 <= _tmp_247;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_249 <= _tmp_248;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_250 <= _tmp_249;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_251 <= _tmp_250;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_252 <= _tmp_251;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_253 <= _tmp_252;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_254 <= _tmp_253;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_255 <= _tmp_254;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_256 <= _tmp_255;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_257 <= _tmp_256;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_258 <= _tmp_257;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_259 <= _tmp_258;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_260 <= _tmp_259;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_261 <= _tmp_260;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_262 <= _tmp_261;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_263 <= _tmp_262;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_264 <= _tmp_263;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_265 <= _tmp_264;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_266 <= _tmp_265;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_267 <= _tmp_266;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_268 <= _tmp_267;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_269 <= _tmp_268;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_270 <= _tmp_269;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_271 <= _tmp_270;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_272 <= _tmp_271;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_273 <= _tmp_272;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_274 <= _tmp_273;
      end 
      if(_tmp_210) begin
        _stream_matmul_11_sink_26_sink_mode <= 5'b1;
        _stream_matmul_11_sink_26_sink_offset <= _tmp_243;
        _stream_matmul_11_sink_26_sink_size <= _tmp_274;
        _stream_matmul_11_sink_26_sink_stride <= 1;
      end 
      if(_tmp_210) begin
        _stream_matmul_11_sink_26_sink_sel <= 5;
      end 
      if(_stream_matmul_11_sink_start && _stream_matmul_11_sink_26_sink_mode & 5'b1 && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_sink_26_sink_offset_buf <= _stream_matmul_11_sink_26_sink_offset;
        _stream_matmul_11_sink_26_sink_size_buf <= _stream_matmul_11_sink_26_sink_size;
        _stream_matmul_11_sink_26_sink_stride_buf <= _stream_matmul_11_sink_26_sink_stride;
      end 
      if((_stream_matmul_11_sink_26_sink_fsm_4 == 1) && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_sink_26_sink_waddr <= _stream_matmul_11_sink_26_sink_offset_buf - _stream_matmul_11_sink_26_sink_stride_buf;
        _stream_matmul_11_sink_26_sink_count <= _stream_matmul_11_sink_26_sink_size_buf;
      end 
      if((_stream_matmul_11_sink_26_sink_fsm_4 == 2) && stream_matmul_11_sink_27_data && _stream_matmul_11_stream_oready) begin
        _stream_matmul_11_sink_26_sink_waddr <= _stream_matmul_11_sink_26_sink_waddr + _stream_matmul_11_sink_26_sink_stride_buf;
        _stream_matmul_11_sink_26_sink_wdata <= stream_matmul_11_sink_26_data;
        _stream_matmul_11_sink_26_sink_wenable <= 1;
        _stream_matmul_11_sink_26_sink_count <= _stream_matmul_11_sink_26_sink_count - 1;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_387 <= _stream_matmul_11_source_start;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_388 <= _tmp_387;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_389 <= _tmp_388;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_390 <= _stream_matmul_11_source_start;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_391 <= _tmp_390;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_392 <= _tmp_391;
      end 
      if(_stream_matmul_11_stream_oready && _tmp_392) begin
        __variable_wdata_84 <= 1;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_393 <= _stream_matmul_11_source_start;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_394 <= _tmp_393;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_395 <= _tmp_394;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_396 <= _tmp_395;
      end 
      if(_stream_matmul_11_stream_oready && _tmp_396) begin
        __variable_wdata_84 <= 0;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_399 <= _tmp_398;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_402 <= _tmp_401;
      end 
      if(_stream_matmul_11_stream_oready && _tmp_402) begin
        __variable_wdata_84 <= 1;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_403 <= _stream_matmul_11_source_start;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_404 <= _tmp_403;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_405 <= _tmp_404;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_406 <= _tmp_405;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_407 <= _tmp_406;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_408 <= _tmp_407;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_409 <= _tmp_408;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_410 <= _tmp_409;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_411 <= _tmp_410;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_412 <= _tmp_411;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_413 <= _tmp_412;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_414 <= _tmp_413;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_415 <= _tmp_414;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_416 <= _tmp_415;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_417 <= _tmp_416;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_418 <= _tmp_417;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_419 <= _tmp_418;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_420 <= _tmp_419;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_421 <= _tmp_420;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_422 <= _tmp_421;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_423 <= _tmp_422;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_424 <= _tmp_423;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_425 <= _tmp_424;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_426 <= _tmp_425;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_427 <= _tmp_426;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_428 <= _tmp_427;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_429 <= _tmp_428;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_430 <= _tmp_429;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_431 <= _tmp_430;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_432 <= _tmp_431;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_433 <= _tmp_432;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_434 <= _stream_matmul_11_source_stop;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_435 <= _tmp_434;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_436 <= _tmp_435;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_437 <= _tmp_436;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_438 <= _tmp_437;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_439 <= _tmp_438;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_440 <= _tmp_439;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_441 <= _tmp_440;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_442 <= _tmp_441;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_443 <= _tmp_442;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_444 <= _tmp_443;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_445 <= _tmp_444;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_446 <= _tmp_445;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_447 <= _tmp_446;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_448 <= _tmp_447;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_449 <= _tmp_448;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_450 <= _tmp_449;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_451 <= _tmp_450;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_452 <= _tmp_451;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_453 <= _tmp_452;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_454 <= _tmp_453;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_455 <= _tmp_454;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_456 <= _tmp_455;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_457 <= _tmp_456;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_458 <= _tmp_457;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_459 <= _tmp_458;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_460 <= _tmp_459;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_461 <= _tmp_460;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_462 <= _tmp_461;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_463 <= _tmp_462;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_464 <= _tmp_463;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_465 <= _stream_matmul_11_source_busy;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_466 <= _tmp_465;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_467 <= _tmp_466;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_468 <= _tmp_467;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_469 <= _tmp_468;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_470 <= _tmp_469;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_471 <= _tmp_470;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_472 <= _tmp_471;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_473 <= _tmp_472;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_474 <= _tmp_473;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_475 <= _tmp_474;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_476 <= _tmp_475;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_477 <= _tmp_476;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_478 <= _tmp_477;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_479 <= _tmp_478;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_480 <= _tmp_479;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_481 <= _tmp_480;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_482 <= _tmp_481;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_483 <= _tmp_482;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_484 <= _tmp_483;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_485 <= _tmp_484;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_486 <= _tmp_485;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_487 <= _tmp_486;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_488 <= _tmp_487;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_489 <= _tmp_488;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_490 <= _tmp_489;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_491 <= _tmp_490;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_492 <= _tmp_491;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_493 <= _tmp_492;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_494 <= _tmp_493;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_495 <= _tmp_494;
      end 
      if(_stream_matmul_11_stream_oready) begin
        _tmp_496 <= _stream_matmul_11_sink_busy;
      end 
      if(!_stream_matmul_11_sink_busy && _tmp_496) begin
        _stream_matmul_11_busy_reg <= 0;
      end 
      if(_stream_matmul_11_source_busy) begin
        _stream_matmul_11_busy_reg <= 1;
      end 
    end
  end

  localparam _stream_matmul_11_fsm_1 = 1;
  localparam _stream_matmul_11_fsm_2 = 2;
  localparam _stream_matmul_11_fsm_3 = 3;

  always @(posedge CLK) begin
    if(RST) begin
      _stream_matmul_11_fsm <= _stream_matmul_11_fsm_init;
      _stream_matmul_11_source_start <= 0;
      _stream_matmul_11_source_busy <= 0;
      _stream_matmul_11_stream_ivalid <= 0;
    end else begin
      if(_stream_matmul_11_stream_oready && _tmp_389) begin
        _stream_matmul_11_stream_ivalid <= 1;
      end 
      if(_stream_matmul_11_stream_oready && _tmp_399) begin
        _stream_matmul_11_stream_ivalid <= 0;
      end 
      case(_stream_matmul_11_fsm)
        _stream_matmul_11_fsm_init: begin
          if(_stream_matmul_11_run_flag) begin
            _stream_matmul_11_source_start <= 1;
          end 
          if(_stream_matmul_11_run_flag) begin
            _stream_matmul_11_fsm <= _stream_matmul_11_fsm_1;
          end 
        end
        _stream_matmul_11_fsm_1: begin
          if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_start <= 0;
            _stream_matmul_11_source_busy <= 1;
          end 
          if(_stream_matmul_11_source_start && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_fsm <= _stream_matmul_11_fsm_2;
          end 
        end
        _stream_matmul_11_fsm_2: begin
          if(_stream_matmul_11_stream_oready) begin
            _stream_matmul_11_fsm <= _stream_matmul_11_fsm_3;
          end 
        end
        _stream_matmul_11_fsm_3: begin
          if(_stream_matmul_11_stream_oready && (_stream_matmul_11_source_11_idle && _stream_matmul_11_source_13_idle && _stream_matmul_11_source_15_idle && _stream_matmul_11_source_20_idle && _stream_matmul_11_source_21_idle && _stream_matmul_11_source_7_idle && _stream_matmul_11_source_9_idle && (_stream_matmul_11_fsm == 3))) begin
            _stream_matmul_11_source_busy <= 0;
          end 
          if(_stream_matmul_11_stream_oready && (_stream_matmul_11_source_11_idle && _stream_matmul_11_source_13_idle && _stream_matmul_11_source_15_idle && _stream_matmul_11_source_20_idle && _stream_matmul_11_source_21_idle && _stream_matmul_11_source_7_idle && _stream_matmul_11_source_9_idle && (_stream_matmul_11_fsm == 3)) && _stream_matmul_11_run_flag) begin
            _stream_matmul_11_source_start <= 1;
          end 
          if(_stream_matmul_11_stream_oready && (_stream_matmul_11_source_11_idle && _stream_matmul_11_source_13_idle && _stream_matmul_11_source_15_idle && _stream_matmul_11_source_20_idle && _stream_matmul_11_source_21_idle && _stream_matmul_11_source_7_idle && _stream_matmul_11_source_9_idle && (_stream_matmul_11_fsm == 3))) begin
            _stream_matmul_11_fsm <= _stream_matmul_11_fsm_init;
          end 
          if(_stream_matmul_11_stream_oready && (_stream_matmul_11_source_11_idle && _stream_matmul_11_source_13_idle && _stream_matmul_11_source_15_idle && _stream_matmul_11_source_20_idle && _stream_matmul_11_source_21_idle && _stream_matmul_11_source_7_idle && _stream_matmul_11_source_9_idle && (_stream_matmul_11_fsm == 3)) && _stream_matmul_11_run_flag) begin
            _stream_matmul_11_fsm <= _stream_matmul_11_fsm_1;
          end 
        end
      endcase
    end
  end

  localparam main_fsm_1 = 1;
  localparam main_fsm_2 = 2;
  localparam main_fsm_3 = 3;
  localparam main_fsm_4 = 4;
  localparam main_fsm_5 = 5;
  localparam main_fsm_6 = 6;
  localparam main_fsm_7 = 7;
  localparam main_fsm_8 = 8;
  localparam main_fsm_9 = 9;
  localparam main_fsm_10 = 10;
  localparam main_fsm_11 = 11;
  localparam main_fsm_12 = 12;
  localparam main_fsm_13 = 13;
  localparam main_fsm_14 = 14;
  localparam main_fsm_15 = 15;
  localparam main_fsm_16 = 16;
  localparam main_fsm_17 = 17;
  localparam main_fsm_18 = 18;
  localparam main_fsm_19 = 19;
  localparam main_fsm_20 = 20;
  localparam main_fsm_21 = 21;
  localparam main_fsm_22 = 22;
  localparam main_fsm_23 = 23;
  localparam main_fsm_24 = 24;
  localparam main_fsm_25 = 25;
  localparam main_fsm_26 = 26;
  localparam main_fsm_27 = 27;
  localparam main_fsm_28 = 28;
  localparam main_fsm_29 = 29;
  localparam main_fsm_30 = 30;
  localparam main_fsm_31 = 31;
  localparam main_fsm_32 = 32;
  localparam main_fsm_33 = 33;
  localparam main_fsm_34 = 34;
  localparam main_fsm_35 = 35;
  localparam main_fsm_36 = 36;
  localparam main_fsm_37 = 37;
  localparam main_fsm_38 = 38;
  localparam main_fsm_39 = 39;
  localparam main_fsm_40 = 40;
  localparam main_fsm_41 = 41;
  localparam main_fsm_42 = 42;
  localparam main_fsm_43 = 43;

  always @(posedge CLK) begin
    if(RST) begin
      main_fsm <= main_fsm_init;
      matmul_11_objaddr <= 0;
      matmul_11_arg_objaddr_0 <= 0;
      matmul_11_arg_objaddr_1 <= 0;
      matmul_11_arg_objaddr_2 <= 0;
      matmul_11_arg_objaddr_3 <= 0;
      matmul_11_control_param_index <= 0;
    end else begin
      case(main_fsm)
        main_fsm_init: begin
          if(_saxi_register_4 != 0) begin
            main_fsm <= main_fsm_1;
          end 
        end
        main_fsm_1: begin
          main_fsm <= main_fsm_2;
        end
        main_fsm_2: begin
          main_fsm <= main_fsm_3;
        end
        main_fsm_3: begin
          main_fsm <= main_fsm_4;
        end
        main_fsm_4: begin
          main_fsm <= main_fsm_5;
        end
        main_fsm_5: begin
          main_fsm <= main_fsm_6;
        end
        main_fsm_6: begin
          main_fsm <= main_fsm_7;
        end
        main_fsm_7: begin
          main_fsm <= main_fsm_8;
        end
        main_fsm_8: begin
          main_fsm <= main_fsm_9;
        end
        main_fsm_9: begin
          matmul_11_objaddr <= _saxi_register_33;
          main_fsm <= main_fsm_10;
        end
        main_fsm_10: begin
          matmul_11_arg_objaddr_0 <= _saxi_register_35;
          main_fsm <= main_fsm_11;
        end
        main_fsm_11: begin
          matmul_11_arg_objaddr_1 <= _saxi_register_36;
          main_fsm <= main_fsm_12;
        end
        main_fsm_12: begin
          matmul_11_arg_objaddr_2 <= _saxi_register_36 + 128;
          main_fsm <= main_fsm_13;
        end
        main_fsm_13: begin
          matmul_11_arg_objaddr_3 <= _saxi_register_36 + 192;
          main_fsm <= main_fsm_14;
        end
        main_fsm_14: begin
          matmul_11_control_param_index <= 0;
          main_fsm <= main_fsm_15;
        end
        main_fsm_15: begin
          main_fsm <= main_fsm_16;
        end
        main_fsm_16: begin
          main_fsm <= main_fsm_17;
        end
        main_fsm_17: begin
          if(control_matmul_11 == 28) begin
            main_fsm <= main_fsm_18;
          end 
        end
        main_fsm_18: begin
          main_fsm <= main_fsm_19;
        end
        main_fsm_19: begin
          matmul_11_objaddr <= _saxi_register_33 + 64;
          main_fsm <= main_fsm_20;
        end
        main_fsm_20: begin
          matmul_11_arg_objaddr_0 <= _saxi_register_33;
          main_fsm <= main_fsm_21;
        end
        main_fsm_21: begin
          matmul_11_arg_objaddr_1 <= _saxi_register_36 + 256;
          main_fsm <= main_fsm_22;
        end
        main_fsm_22: begin
          matmul_11_arg_objaddr_2 <= _saxi_register_36 + 512;
          main_fsm <= main_fsm_23;
        end
        main_fsm_23: begin
          matmul_11_arg_objaddr_3 <= _saxi_register_36 + 576;
          main_fsm <= main_fsm_24;
        end
        main_fsm_24: begin
          matmul_11_control_param_index <= 1;
          main_fsm <= main_fsm_25;
        end
        main_fsm_25: begin
          main_fsm <= main_fsm_26;
        end
        main_fsm_26: begin
          main_fsm <= main_fsm_27;
        end
        main_fsm_27: begin
          if(control_matmul_11 == 28) begin
            main_fsm <= main_fsm_28;
          end 
        end
        main_fsm_28: begin
          main_fsm <= main_fsm_29;
        end
        main_fsm_29: begin
          matmul_11_objaddr <= _saxi_register_34;
          main_fsm <= main_fsm_30;
        end
        main_fsm_30: begin
          matmul_11_arg_objaddr_0 <= _saxi_register_33 + 64;
          main_fsm <= main_fsm_31;
        end
        main_fsm_31: begin
          matmul_11_arg_objaddr_1 <= _saxi_register_36 + 640;
          main_fsm <= main_fsm_32;
        end
        main_fsm_32: begin
          matmul_11_arg_objaddr_2 <= _saxi_register_36 + 704;
          main_fsm <= main_fsm_33;
        end
        main_fsm_33: begin
          matmul_11_arg_objaddr_3 <= _saxi_register_36 + 768;
          main_fsm <= main_fsm_34;
        end
        main_fsm_34: begin
          matmul_11_control_param_index <= 2;
          main_fsm <= main_fsm_35;
        end
        main_fsm_35: begin
          main_fsm <= main_fsm_36;
        end
        main_fsm_36: begin
          main_fsm <= main_fsm_37;
        end
        main_fsm_37: begin
          if(control_matmul_11 == 28) begin
            main_fsm <= main_fsm_38;
          end 
        end
        main_fsm_38: begin
          main_fsm <= main_fsm_39;
        end
        main_fsm_39: begin
          main_fsm <= main_fsm_40;
        end
        main_fsm_40: begin
          main_fsm <= main_fsm_41;
        end
        main_fsm_41: begin
          main_fsm <= main_fsm_42;
        end
        main_fsm_42: begin
          main_fsm <= main_fsm_43;
        end
        main_fsm_43: begin
          main_fsm <= main_fsm_init;
        end
      endcase
    end
  end

  localparam control_matmul_11_1 = 1;
  localparam control_matmul_11_2 = 2;
  localparam control_matmul_11_3 = 3;
  localparam control_matmul_11_4 = 4;
  localparam control_matmul_11_5 = 5;
  localparam control_matmul_11_6 = 6;
  localparam control_matmul_11_7 = 7;
  localparam control_matmul_11_8 = 8;
  localparam control_matmul_11_9 = 9;
  localparam control_matmul_11_10 = 10;
  localparam control_matmul_11_11 = 11;
  localparam control_matmul_11_12 = 12;
  localparam control_matmul_11_13 = 13;
  localparam control_matmul_11_14 = 14;
  localparam control_matmul_11_15 = 15;
  localparam control_matmul_11_16 = 16;
  localparam control_matmul_11_17 = 17;
  localparam control_matmul_11_18 = 18;
  localparam control_matmul_11_19 = 19;
  localparam control_matmul_11_20 = 20;
  localparam control_matmul_11_21 = 21;
  localparam control_matmul_11_22 = 22;
  localparam control_matmul_11_23 = 23;
  localparam control_matmul_11_24 = 24;
  localparam control_matmul_11_25 = 25;
  localparam control_matmul_11_26 = 26;
  localparam control_matmul_11_27 = 27;
  localparam control_matmul_11_28 = 28;

  always @(posedge CLK) begin
    if(RST) begin
      control_matmul_11 <= control_matmul_11_init;
      _control_matmul_11_called <= 0;
      matmul_11_filter_base_offset <= 0;
      matmul_11_filter_page_comp_offset <= 0;
      matmul_11_filter_page_dma_offset <= 0;
      matmul_11_act_base_offset_row <= 0;
      matmul_11_act_base_offset_bat <= 0;
      matmul_11_dma_flag_0 <= 0;
      matmul_11_act_page_comp_offset_0 <= 0;
      matmul_11_act_page_dma_offset_0 <= 0;
      matmul_11_out_base_offset_val <= 0;
      matmul_11_out_base_offset_col <= 0;
      matmul_11_out_base_offset_row <= 0;
      matmul_11_out_base_offset_bat <= 0;
      matmul_11_out_base_offset_och <= 0;
      matmul_11_out_page <= 0;
      matmul_11_out_page_comp_offset <= 0;
      matmul_11_out_page_dma_offset <= 0;
      matmul_11_out_laddr_offset <= 0;
      matmul_11_sync_out_count <= 0;
      matmul_11_write_count <= 0;
      matmul_11_next_out_write_size <= 0;
      matmul_11_row_count <= 0;
      matmul_11_bat_count <= 0;
      matmul_11_och_count <= 0;
      matmul_11_row_select <= 0;
      matmul_11_prev_row_count <= 0;
      matmul_11_prev_bat_count <= 0;
      matmul_11_prev_och_count <= 0;
      matmul_11_prev_row_select <= 0;
      matmul_11_out_col_count <= 0;
      matmul_11_out_row_count <= 0;
      matmul_11_out_ram_select <= 0;
      matmul_11_skip_read_filter <= 0;
      matmul_11_skip_read_act <= 0;
      matmul_11_skip_comp <= 0;
      matmul_11_skip_write_out <= 1;
    end else begin
      case(control_matmul_11)
        control_matmul_11_init: begin
          if(main_fsm == 15) begin
            _control_matmul_11_called <= 1;
          end 
          if(main_fsm == 25) begin
            _control_matmul_11_called <= 1;
          end 
          if(main_fsm == 35) begin
            _control_matmul_11_called <= 1;
          end 
          if(main_fsm == 15) begin
            control_matmul_11 <= control_matmul_11_1;
          end 
          if(main_fsm == 25) begin
            control_matmul_11 <= control_matmul_11_1;
          end 
          if(main_fsm == 35) begin
            control_matmul_11 <= control_matmul_11_1;
          end 
        end
        control_matmul_11_1: begin
          control_matmul_11 <= control_matmul_11_2;
        end
        control_matmul_11_2: begin
          matmul_11_filter_base_offset <= 0;
          matmul_11_filter_page_comp_offset <= 0;
          matmul_11_filter_page_dma_offset <= 0;
          matmul_11_act_base_offset_row <= 0;
          matmul_11_act_base_offset_bat <= 0;
          matmul_11_dma_flag_0 <= 1;
          matmul_11_act_page_comp_offset_0 <= 0;
          matmul_11_act_page_dma_offset_0 <= 0;
          matmul_11_out_base_offset_val <= 0;
          matmul_11_out_base_offset_col <= 0;
          matmul_11_out_base_offset_row <= 0;
          matmul_11_out_base_offset_bat <= 0;
          matmul_11_out_base_offset_och <= 0;
          matmul_11_out_page <= 0;
          matmul_11_out_page_comp_offset <= 0;
          matmul_11_out_page_dma_offset <= 0;
          matmul_11_out_laddr_offset <= 0;
          matmul_11_sync_out_count <= 0;
          matmul_11_write_count <= 0;
          matmul_11_next_out_write_size <= (cparam_matmul_11_max_och_count == 0)? cparam_matmul_11_out_write_size_res : cparam_matmul_11_out_write_size;
          matmul_11_row_count <= 0;
          matmul_11_bat_count <= 0;
          matmul_11_och_count <= 0;
          matmul_11_row_select <= 0;
          matmul_11_prev_row_count <= 0;
          matmul_11_prev_bat_count <= 0;
          matmul_11_prev_och_count <= 0;
          matmul_11_prev_row_select <= 0;
          matmul_11_out_col_count <= 0;
          matmul_11_out_row_count <= 0;
          matmul_11_out_ram_select <= 0;
          matmul_11_skip_read_filter <= 0;
          matmul_11_skip_read_act <= 0;
          matmul_11_skip_comp <= 0;
          matmul_11_skip_write_out <= 1;
          if(_maxi_read_req_idle) begin
            control_matmul_11 <= control_matmul_11_3;
          end 
        end
        control_matmul_11_3: begin
          if(_maxi_read_idle) begin
            control_matmul_11 <= control_matmul_11_4;
          end 
        end
        control_matmul_11_4: begin
          if(_maxi_read_req_idle) begin
            control_matmul_11 <= control_matmul_11_5;
          end 
        end
        control_matmul_11_5: begin
          if(_maxi_read_idle) begin
            control_matmul_11 <= control_matmul_11_6;
          end 
        end
        control_matmul_11_6: begin
          if(cparam_matmul_11_data_stationary == 0) begin
            control_matmul_11 <= control_matmul_11_7;
          end 
          if(cparam_matmul_11_data_stationary == 1) begin
            control_matmul_11 <= control_matmul_11_12;
          end 
        end
        control_matmul_11_7: begin
          control_matmul_11 <= control_matmul_11_8;
          if(matmul_11_skip_read_filter) begin
            control_matmul_11 <= control_matmul_11_11;
          end 
        end
        control_matmul_11_8: begin
          if(_maxi_read_req_idle) begin
            control_matmul_11 <= control_matmul_11_9;
          end 
        end
        control_matmul_11_9: begin
          if(_maxi_read_idle) begin
            control_matmul_11 <= control_matmul_11_10;
          end 
        end
        control_matmul_11_10: begin
          control_matmul_11 <= control_matmul_11_11;
        end
        control_matmul_11_11: begin
          if(cparam_matmul_11_data_stationary == 0) begin
            control_matmul_11 <= control_matmul_11_12;
          end 
          if(cparam_matmul_11_data_stationary == 1) begin
            control_matmul_11 <= control_matmul_11_18;
          end 
        end
        control_matmul_11_12: begin
          control_matmul_11 <= control_matmul_11_13;
          if(matmul_11_skip_read_act) begin
            control_matmul_11 <= control_matmul_11_17;
          end 
        end
        control_matmul_11_13: begin
          control_matmul_11 <= control_matmul_11_14;
          if(matmul_11_mux_dma_pad_mask_0 || !matmul_11_mux_dma_flag_0) begin
            control_matmul_11 <= control_matmul_11_16;
          end 
        end
        control_matmul_11_14: begin
          if(_maxi_read_req_idle) begin
            control_matmul_11 <= control_matmul_11_15;
          end 
        end
        control_matmul_11_15: begin
          if(_maxi_read_idle) begin
            control_matmul_11 <= control_matmul_11_16;
          end 
        end
        control_matmul_11_16: begin
          control_matmul_11 <= control_matmul_11_17;
        end
        control_matmul_11_17: begin
          if(cparam_matmul_11_data_stationary == 0) begin
            control_matmul_11 <= control_matmul_11_18;
          end 
          if(cparam_matmul_11_data_stationary == 1) begin
            control_matmul_11 <= control_matmul_11_7;
          end 
        end
        control_matmul_11_18: begin
          if(_maxi_write_idle) begin
            control_matmul_11 <= control_matmul_11_19;
          end 
        end
        control_matmul_11_19: begin
          if(matmul_11_comp_fsm == 0) begin
            control_matmul_11 <= control_matmul_11_20;
          end 
        end
        control_matmul_11_20: begin
          control_matmul_11 <= control_matmul_11_21;
          if(matmul_11_skip_write_out) begin
            control_matmul_11 <= control_matmul_11_26;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_prev_och_count < cparam_matmul_11_max_och_count)) begin
            control_matmul_11 <= control_matmul_11_26;
          end 
        end
        control_matmul_11_21: begin
          if(matmul_11_sync_comp_count >= matmul_11_sync_out_count + cparam_matmul_11_inc_sync_out) begin
            control_matmul_11 <= control_matmul_11_22;
          end 
        end
        control_matmul_11_22: begin
          if(!matmul_11_dma_out_mask_0) begin
            control_matmul_11 <= control_matmul_11_23;
          end 
          if(matmul_11_dma_out_mask_0) begin
            control_matmul_11 <= control_matmul_11_24;
          end 
        end
        control_matmul_11_23: begin
          if(_maxi_write_req_idle) begin
            control_matmul_11 <= control_matmul_11_24;
          end 
        end
        control_matmul_11_24: begin
          control_matmul_11 <= control_matmul_11_25;
        end
        control_matmul_11_25: begin
          matmul_11_write_count <= matmul_11_write_count + 1;
          if(matmul_11_out_ram_select == 0) begin
            matmul_11_out_laddr_offset <= matmul_11_out_laddr_offset + matmul_11_next_out_write_size;
          end 
          if((cparam_matmul_11_data_stationary == 0) && !cparam_matmul_11_keep_filter) begin
            matmul_11_out_base_offset_col <= matmul_11_out_base_offset_col + cparam_matmul_11_out_col_step;
            matmul_11_out_col_count <= matmul_11_out_col_count + 1;
          end 
          matmul_11_out_ram_select <= matmul_11_out_ram_select + 1;
          if(matmul_11_out_ram_select == 0) begin
            matmul_11_out_ram_select <= 0;
          end 
          matmul_11_sync_out_count <= matmul_11_sync_out_count + cparam_matmul_11_inc_sync_out;
          if((cparam_matmul_11_data_stationary == 0) && !cparam_matmul_11_keep_filter && (matmul_11_write_count >= cparam_matmul_11_out_num_col - 1) || (cparam_matmul_11_data_stationary == 0) && cparam_matmul_11_keep_filter || (cparam_matmul_11_data_stationary == 1)) begin
            matmul_11_sync_out_count <= matmul_11_sync_out_count + (cparam_matmul_11_inc_sync_out + cparam_matmul_11_inc_sync_out_res);
          end 
          if((cparam_matmul_11_data_stationary == 0) && !cparam_matmul_11_keep_filter) begin
            control_matmul_11 <= control_matmul_11_20;
          end 
          if((cparam_matmul_11_data_stationary == 0) && !cparam_matmul_11_keep_filter && (matmul_11_write_count >= cparam_matmul_11_out_num_col - 1) || (cparam_matmul_11_data_stationary == 0) && cparam_matmul_11_keep_filter || (cparam_matmul_11_data_stationary == 1)) begin
            control_matmul_11 <= control_matmul_11_26;
          end 
        end
        control_matmul_11_26: begin
          if(matmul_11_update_filter) begin
            matmul_11_filter_base_offset <= matmul_11_filter_base_offset + cparam_matmul_11_filter_base_step;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_och_count >= cparam_matmul_11_max_och_count)) begin
            matmul_11_filter_base_offset <= 0;
          end 
          if(matmul_11_update_filter) begin
            matmul_11_och_count <= matmul_11_och_count + cparam_matmul_11_och_count_step;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_och_count >= cparam_matmul_11_max_och_count)) begin
            matmul_11_och_count <= 0;
          end 
          if(matmul_11_update_filter) begin
            matmul_11_filter_page_comp_offset <= matmul_11_filter_page_comp_offset + cparam_matmul_11_filter_read_step;
            matmul_11_filter_page_dma_offset <= matmul_11_filter_page_dma_offset + cparam_matmul_11_filter_read_step;
          end 
          if(matmul_11_update_filter && (matmul_11_filter_page_comp_offset + cparam_matmul_11_filter_read_step + cparam_matmul_11_filter_read_step > 512)) begin
            matmul_11_filter_page_comp_offset <= 0;
            matmul_11_filter_page_dma_offset <= 0;
          end 
          if(matmul_11_update_act) begin
            matmul_11_act_base_offset_row <= matmul_11_act_base_offset_row + cparam_matmul_11_act_row_step;
          end 
          if(matmul_11_update_act && (matmul_11_row_count >= cparam_matmul_11_max_row_count)) begin
            matmul_11_act_base_offset_row <= 0;
            matmul_11_act_base_offset_bat <= matmul_11_act_base_offset_bat + cparam_matmul_11_act_bat_step;
          end 
          if(matmul_11_update_act && (matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count)) begin
            matmul_11_act_base_offset_bat <= 0;
          end 
          if(!matmul_11_update_act) begin
            matmul_11_dma_flag_0 <= 0;
          end 
          if(matmul_11_update_act) begin
            matmul_11_dma_flag_0 <= cparam_matmul_11_dma_flag_conds_0;
          end 
          if(matmul_11_update_act && (matmul_11_row_count >= cparam_matmul_11_max_row_count)) begin
            matmul_11_dma_flag_0 <= 1;
          end 
          if(matmul_11_update_act) begin
            matmul_11_row_count <= matmul_11_row_count + cparam_matmul_11_stride_row_par_row;
          end 
          if(matmul_11_update_act && (matmul_11_row_count >= cparam_matmul_11_max_row_count)) begin
            matmul_11_row_count <= 0;
            matmul_11_bat_count <= matmul_11_bat_count + 1;
          end 
          if(matmul_11_update_act && (matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count)) begin
            matmul_11_bat_count <= 0;
          end 
          if(matmul_11_update_act && (cparam_matmul_11_stride_row_par_row < 1)) begin
            matmul_11_row_select <= matmul_11_row_select + cparam_matmul_11_stride_row_par_row;
            matmul_11_prev_row_select <= matmul_11_row_select;
          end 
          if(matmul_11_update_act && (cparam_matmul_11_stride_row_par_row < 1) && (matmul_11_row_select + cparam_matmul_11_stride_row_par_row >= 1)) begin
            matmul_11_row_select <= matmul_11_row_select - (1 - cparam_matmul_11_stride_row_par_row);
            matmul_11_prev_row_select <= matmul_11_row_select;
          end 
          if(matmul_11_update_act && !(cparam_matmul_11_stride_row_par_row < 1)) begin
            matmul_11_row_select <= 0;
            matmul_11_prev_row_select <= 0;
          end 
          if(matmul_11_update_act && (matmul_11_row_count >= cparam_matmul_11_max_row_count)) begin
            matmul_11_row_select <= 0;
            matmul_11_prev_row_select <= 0;
          end 
          if(matmul_11_update_act && matmul_11_mux_next_dma_flag_0) begin
            matmul_11_act_page_comp_offset_0 <= matmul_11_act_page_comp_offset_0 + cparam_matmul_11_act_read_step;
            matmul_11_act_page_dma_offset_0 <= matmul_11_act_page_dma_offset_0 + cparam_matmul_11_act_read_step;
          end 
          if(matmul_11_update_act && matmul_11_mux_next_dma_flag_0 && (matmul_11_act_page_comp_offset_0 + cparam_matmul_11_act_read_step + cparam_matmul_11_act_read_step > 512)) begin
            matmul_11_act_page_comp_offset_0 <= 0;
            matmul_11_act_page_dma_offset_0 <= 0;
          end 
          if((cparam_matmul_11_data_stationary == 0) && (matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count) && cparam_matmul_11_keep_input) begin
            matmul_11_act_page_comp_offset_0 <= 0;
            matmul_11_act_page_dma_offset_0 <= 0;
          end 
          matmul_11_next_out_write_size <= (matmul_11_och_count >= cparam_matmul_11_max_och_count)? cparam_matmul_11_out_write_size_res : cparam_matmul_11_out_write_size;
          if(!matmul_11_skip_write_out) begin
            matmul_11_write_count <= 0;
            matmul_11_out_laddr_offset <= 0;
            matmul_11_out_ram_select <= 0;
          end 
          if((cparam_matmul_11_data_stationary == 0) && !matmul_11_skip_write_out) begin
            matmul_11_out_base_offset_col <= 0;
            matmul_11_out_base_offset_row <= matmul_11_out_base_offset_row + cparam_matmul_11_out_row_step;
            matmul_11_out_col_count <= 0;
            matmul_11_out_row_count <= matmul_11_out_row_count + 1;
          end 
          if((cparam_matmul_11_data_stationary == 0) && !matmul_11_skip_write_out && (matmul_11_prev_row_count >= cparam_matmul_11_max_row_count)) begin
            matmul_11_out_base_offset_row <= 0;
            matmul_11_out_base_offset_bat <= matmul_11_out_base_offset_bat + cparam_matmul_11_out_bat_step;
            matmul_11_out_row_count <= 0;
          end 
          if((cparam_matmul_11_data_stationary == 0) && !matmul_11_skip_write_out && (matmul_11_prev_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_prev_bat_count >= cparam_matmul_11_max_bat_count)) begin
            matmul_11_out_base_offset_bat <= 0;
            matmul_11_out_base_offset_och <= matmul_11_out_base_offset_och + cparam_matmul_11_out_och_step;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_prev_och_count >= cparam_matmul_11_max_och_count) && !matmul_11_skip_write_out) begin
            matmul_11_out_base_offset_row <= matmul_11_out_base_offset_row + cparam_matmul_11_out_row_step;
          end 
          if((cparam_matmul_11_data_stationary == 0) && !matmul_11_out_page) begin
            matmul_11_out_page_comp_offset <= 256;
            matmul_11_out_page_dma_offset <= 0;
            matmul_11_out_page <= 1;
          end 
          if((cparam_matmul_11_data_stationary == 0) && matmul_11_out_page) begin
            matmul_11_out_page_comp_offset <= 0;
            matmul_11_out_page_dma_offset <= 256;
            matmul_11_out_page <= 0;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_och_count >= cparam_matmul_11_max_och_count) && !matmul_11_out_page) begin
            matmul_11_out_page_comp_offset <= 256;
            matmul_11_out_page_dma_offset <= 0;
            matmul_11_out_page <= 1;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_och_count >= cparam_matmul_11_max_och_count) && matmul_11_out_page) begin
            matmul_11_out_page_comp_offset <= 0;
            matmul_11_out_page_dma_offset <= 256;
            matmul_11_out_page <= 0;
          end 
          matmul_11_prev_row_count <= matmul_11_row_count;
          matmul_11_prev_bat_count <= matmul_11_bat_count;
          matmul_11_prev_och_count <= matmul_11_och_count;
          if((matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count) && (matmul_11_och_count >= cparam_matmul_11_max_och_count)) begin
            matmul_11_skip_read_filter <= 1;
          end 
          if((cparam_matmul_11_data_stationary == 1) && cparam_matmul_11_keep_filter) begin
            matmul_11_skip_read_filter <= 1;
          end 
          if((matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count) && (matmul_11_och_count >= cparam_matmul_11_max_och_count)) begin
            matmul_11_skip_read_act <= 1;
          end 
          if((cparam_matmul_11_data_stationary == 0) && (matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count) && cparam_matmul_11_keep_input) begin
            matmul_11_skip_read_act <= 1;
          end 
          if((matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count) && (matmul_11_och_count >= cparam_matmul_11_max_och_count)) begin
            matmul_11_skip_comp <= 1;
          end 
          if(matmul_11_skip_write_out && (matmul_11_prev_row_count == 0) && (matmul_11_prev_bat_count == 0) && (matmul_11_prev_och_count == 0)) begin
            matmul_11_skip_write_out <= 0;
          end 
          if(cparam_matmul_11_data_stationary == 0) begin
            control_matmul_11 <= control_matmul_11_12;
          end 
          if((cparam_matmul_11_data_stationary == 0) && (matmul_11_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_bat_count >= cparam_matmul_11_max_bat_count)) begin
            control_matmul_11 <= control_matmul_11_7;
          end 
          if(cparam_matmul_11_data_stationary == 1) begin
            control_matmul_11 <= control_matmul_11_7;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_och_count >= cparam_matmul_11_max_och_count)) begin
            control_matmul_11 <= control_matmul_11_12;
          end 
          if(!matmul_11_skip_write_out && (matmul_11_prev_och_count >= cparam_matmul_11_max_och_count) && (matmul_11_prev_row_count >= cparam_matmul_11_max_row_count) && (matmul_11_prev_bat_count >= cparam_matmul_11_max_bat_count)) begin
            control_matmul_11 <= control_matmul_11_27;
          end 
        end
        control_matmul_11_27: begin
          if(_maxi_write_idle && !_maxi_has_outstanding_write) begin
            control_matmul_11 <= control_matmul_11_28;
          end 
        end
        control_matmul_11_28: begin
          if(main_fsm == 18) begin
            _control_matmul_11_called <= 0;
          end 
          if(main_fsm == 28) begin
            _control_matmul_11_called <= 0;
          end 
          if(main_fsm == 38) begin
            _control_matmul_11_called <= 0;
          end 
          if(main_fsm == 18) begin
            control_matmul_11 <= control_matmul_11_init;
          end 
          if(main_fsm == 28) begin
            control_matmul_11 <= control_matmul_11_init;
          end 
          if(main_fsm == 38) begin
            control_matmul_11 <= control_matmul_11_init;
          end 
        end
      endcase
    end
  end

  localparam _maxi_read_req_fsm_1 = 1;

  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _maxi_read_req_fsm <= _maxi_read_req_fsm_init;
      _maxi_read_cont <= 0;
    end else begin
      case(_maxi_read_req_fsm)
        _maxi_read_req_fsm_init: begin
          if((_maxi_read_req_fsm == 0) && (_maxi_read_start || _maxi_read_cont) && !_maxi_read_req_fifo_almost_full) begin
            _maxi_read_req_fsm <= _maxi_read_req_fsm_1;
          end 
        end
        _maxi_read_req_fsm_1: begin
          if(maxi_arready || !maxi_arvalid) begin
            _maxi_read_cont <= 1;
          end 
          if((maxi_arready || !maxi_arvalid) && (_maxi_read_global_size == 0)) begin
            _maxi_read_cont <= 0;
          end 
          if(maxi_arready || !maxi_arvalid) begin
            _maxi_read_req_fsm <= _maxi_read_req_fsm_init;
          end 
        end
      endcase
    end
  end

  localparam _maxi_read_data_fsm_1 = 1;
  localparam _maxi_read_data_fsm_2 = 2;

  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _maxi_read_data_fsm <= _maxi_read_data_fsm_init;
    end else begin
      case(_maxi_read_data_fsm)
        _maxi_read_data_fsm_init: begin
          if(!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 1)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_1;
          end 
          if(!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 2)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_1;
          end 
          if(!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 3)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_1;
          end 
          if(!_maxi_read_data_busy && !_maxi_read_req_fifo_empty && (_maxi_read_op_sel_fifo == 4)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_1;
          end 
        end
        _maxi_read_data_fsm_1: begin
          _maxi_read_data_fsm <= _maxi_read_data_fsm_2;
          _maxi_read_data_fsm <= _maxi_read_data_fsm_2;
          _maxi_read_data_fsm <= _maxi_read_data_fsm_2;
          _maxi_read_data_fsm <= _maxi_read_data_fsm_2;
        end
        _maxi_read_data_fsm_2: begin
          if(_maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_init;
          end 
          if(_maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_init;
          end 
          if(_maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_init;
          end 
          if(_maxi_rvalid_sb_0 && (_maxi_read_local_size_buf <= 1)) begin
            _maxi_read_data_fsm <= _maxi_read_data_fsm_init;
          end 
        end
      endcase
    end
  end

  localparam write_burst_packed_fsm_0_1 = 1;

  always @(posedge CLK) begin
    if(RST) begin
      write_burst_packed_fsm_0 <= write_burst_packed_fsm_0_init;
      write_burst_packed_addr_79 <= 0;
      write_burst_packed_stride_80 <= 0;
      write_burst_packed_length_81 <= 0;
      write_burst_packed_done_82 <= 0;
    end else begin
      case(write_burst_packed_fsm_0)
        write_burst_packed_fsm_0_init: begin
          write_burst_packed_addr_79 <= _maxi_read_local_addr_buf;
          write_burst_packed_stride_80 <= _maxi_read_local_stride_buf;
          write_burst_packed_length_81 <= _maxi_read_local_size_buf;
          write_burst_packed_done_82 <= 0;
          if((_maxi_read_data_fsm == 1) && (_maxi_read_op_sel_buf == 1) && (_maxi_read_local_size_buf > 0)) begin
            write_burst_packed_fsm_0 <= write_burst_packed_fsm_0_1;
          end 
        end
        write_burst_packed_fsm_0_1: begin
          if(_maxi_rvalid_sb_0) begin
            write_burst_packed_addr_79 <= write_burst_packed_addr_79 + write_burst_packed_stride_80;
            write_burst_packed_length_81 <= write_burst_packed_length_81 - 1;
            write_burst_packed_done_82 <= 0;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_81 <= 1)) begin
            write_burst_packed_done_82 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_done_82 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_81 <= 1)) begin
            write_burst_packed_fsm_0 <= write_burst_packed_fsm_0_init;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_fsm_0 <= write_burst_packed_fsm_0_init;
          end 
          if(0) begin
            write_burst_packed_fsm_0 <= write_burst_packed_fsm_0_init;
          end 
        end
      endcase
    end
  end

  localparam write_burst_packed_fsm_1_1 = 1;

  always @(posedge CLK) begin
    if(RST) begin
      write_burst_packed_fsm_1 <= write_burst_packed_fsm_1_init;
      write_burst_packed_addr_92 <= 0;
      write_burst_packed_stride_93 <= 0;
      write_burst_packed_length_94 <= 0;
      write_burst_packed_done_95 <= 0;
    end else begin
      case(write_burst_packed_fsm_1)
        write_burst_packed_fsm_1_init: begin
          write_burst_packed_addr_92 <= _maxi_read_local_addr_buf;
          write_burst_packed_stride_93 <= _maxi_read_local_stride_buf;
          write_burst_packed_length_94 <= _maxi_read_local_size_buf;
          write_burst_packed_done_95 <= 0;
          if((_maxi_read_data_fsm == 1) && (_maxi_read_op_sel_buf == 2) && (_maxi_read_local_size_buf > 0)) begin
            write_burst_packed_fsm_1 <= write_burst_packed_fsm_1_1;
          end 
        end
        write_burst_packed_fsm_1_1: begin
          if(_maxi_rvalid_sb_0) begin
            write_burst_packed_addr_92 <= write_burst_packed_addr_92 + write_burst_packed_stride_93;
            write_burst_packed_length_94 <= write_burst_packed_length_94 - 1;
            write_burst_packed_done_95 <= 0;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_94 <= 1)) begin
            write_burst_packed_done_95 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_done_95 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_94 <= 1)) begin
            write_burst_packed_fsm_1 <= write_burst_packed_fsm_1_init;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_fsm_1 <= write_burst_packed_fsm_1_init;
          end 
          if(0) begin
            write_burst_packed_fsm_1 <= write_burst_packed_fsm_1_init;
          end 
        end
      endcase
    end
  end

  localparam write_burst_packed_fsm_2_1 = 1;

  always @(posedge CLK) begin
    if(RST) begin
      write_burst_packed_fsm_2 <= write_burst_packed_fsm_2_init;
      write_burst_packed_addr_105 <= 0;
      write_burst_packed_stride_106 <= 0;
      write_burst_packed_length_107 <= 0;
      write_burst_packed_done_108 <= 0;
    end else begin
      case(write_burst_packed_fsm_2)
        write_burst_packed_fsm_2_init: begin
          write_burst_packed_addr_105 <= _maxi_read_local_addr_buf;
          write_burst_packed_stride_106 <= _maxi_read_local_stride_buf;
          write_burst_packed_length_107 <= _maxi_read_local_size_buf;
          write_burst_packed_done_108 <= 0;
          if((_maxi_read_data_fsm == 1) && (_maxi_read_op_sel_buf == 3) && (_maxi_read_local_size_buf > 0)) begin
            write_burst_packed_fsm_2 <= write_burst_packed_fsm_2_1;
          end 
        end
        write_burst_packed_fsm_2_1: begin
          if(_maxi_rvalid_sb_0) begin
            write_burst_packed_addr_105 <= write_burst_packed_addr_105 + write_burst_packed_stride_106;
            write_burst_packed_length_107 <= write_burst_packed_length_107 - 1;
            write_burst_packed_done_108 <= 0;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_107 <= 1)) begin
            write_burst_packed_done_108 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_done_108 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_107 <= 1)) begin
            write_burst_packed_fsm_2 <= write_burst_packed_fsm_2_init;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_fsm_2 <= write_burst_packed_fsm_2_init;
          end 
          if(0) begin
            write_burst_packed_fsm_2 <= write_burst_packed_fsm_2_init;
          end 
        end
      endcase
    end
  end

  localparam write_burst_packed_fsm_3_1 = 1;

  always @(posedge CLK) begin
    if(RST) begin
      write_burst_packed_fsm_3 <= write_burst_packed_fsm_3_init;
      write_burst_packed_addr_118 <= 0;
      write_burst_packed_stride_119 <= 0;
      write_burst_packed_length_120 <= 0;
      write_burst_packed_done_121 <= 0;
    end else begin
      case(write_burst_packed_fsm_3)
        write_burst_packed_fsm_3_init: begin
          write_burst_packed_addr_118 <= _maxi_read_local_addr_buf;
          write_burst_packed_stride_119 <= _maxi_read_local_stride_buf;
          write_burst_packed_length_120 <= _maxi_read_local_size_buf;
          write_burst_packed_done_121 <= 0;
          if((_maxi_read_data_fsm == 1) && (_maxi_read_op_sel_buf == 4) && (_maxi_read_local_size_buf > 0)) begin
            write_burst_packed_fsm_3 <= write_burst_packed_fsm_3_1;
          end 
        end
        write_burst_packed_fsm_3_1: begin
          if(_maxi_rvalid_sb_0) begin
            write_burst_packed_addr_118 <= write_burst_packed_addr_118 + write_burst_packed_stride_119;
            write_burst_packed_length_120 <= write_burst_packed_length_120 - 1;
            write_burst_packed_done_121 <= 0;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_120 <= 1)) begin
            write_burst_packed_done_121 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_done_121 <= 1;
          end 
          if(_maxi_rvalid_sb_0 && (write_burst_packed_length_120 <= 1)) begin
            write_burst_packed_fsm_3 <= write_burst_packed_fsm_3_init;
          end 
          if(_maxi_rvalid_sb_0 && 0) begin
            write_burst_packed_fsm_3 <= write_burst_packed_fsm_3_init;
          end 
          if(0) begin
            write_burst_packed_fsm_3 <= write_burst_packed_fsm_3_init;
          end 
        end
      endcase
    end
  end

  localparam matmul_11_comp_fsm_1 = 1;
  localparam matmul_11_comp_fsm_2 = 2;
  localparam matmul_11_comp_fsm_3 = 3;
  localparam matmul_11_comp_fsm_4 = 4;
  localparam matmul_11_comp_fsm_5 = 5;
  localparam matmul_11_comp_fsm_6 = 6;

  always @(posedge CLK) begin
    if(RST) begin
      matmul_11_comp_fsm <= matmul_11_comp_fsm_init;
      matmul_11_stream_act_local_0 <= 0;
      matmul_11_stream_out_local_col <= 0;
      matmul_11_stream_out_local_val <= 0;
      matmul_11_col_count <= 0;
      matmul_11_col_select <= 0;
      matmul_11_filter_page_comp_offset_buf <= 0;
      matmul_11_act_page_comp_offset_buf_0 <= 0;
      matmul_11_out_page_comp_offset_buf <= 0;
      matmul_11_row_count_buf <= 0;
      matmul_11_row_select_buf <= 0;
      matmul_11_och_count_buf <= 0;
      matmul_11_next_stream_num_ops <= 0;
      matmul_11_stream_pad_masks <= 0;
      matmul_11_sync_comp_count <= 0;
    end else begin
      if(_stream_matmul_11_sink_stop) begin
        matmul_11_sync_comp_count <= matmul_11_sync_comp_count + 1;
      end 
      if(control_matmul_11 == 6) begin
        matmul_11_sync_comp_count <= 0;
      end 
      case(matmul_11_comp_fsm)
        matmul_11_comp_fsm_init: begin
          if((control_matmul_11 == 19) && !matmul_11_skip_comp) begin
            matmul_11_comp_fsm <= matmul_11_comp_fsm_1;
          end 
        end
        matmul_11_comp_fsm_1: begin
          matmul_11_stream_act_local_0 <= 0;
          if(cparam_matmul_11_stream_act_local_small_flags_0) begin
            matmul_11_stream_act_local_0 <= cparam_matmul_11_stream_act_local_small_offset;
          end 
          if(cparam_matmul_11_stream_act_local_large_flags_0) begin
            matmul_11_stream_act_local_0 <= cparam_matmul_11_stream_act_local_large_offset;
          end 
          matmul_11_stream_out_local_col <= 0;
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_och_count == 0)) begin
            matmul_11_stream_out_local_val <= 0;
          end 
          matmul_11_col_count <= 0;
          matmul_11_col_select <= cparam_matmul_11_col_select_initval;
          matmul_11_filter_page_comp_offset_buf <= matmul_11_filter_page_comp_offset;
          matmul_11_act_page_comp_offset_buf_0 <= matmul_11_act_page_comp_offset_0;
          matmul_11_out_page_comp_offset_buf <= matmul_11_out_page_comp_offset;
          matmul_11_row_count_buf <= matmul_11_row_count;
          matmul_11_row_select_buf <= matmul_11_row_select;
          matmul_11_och_count_buf <= matmul_11_och_count;
          matmul_11_next_stream_num_ops <= (matmul_11_och_count >= cparam_matmul_11_max_och_count)? cparam_matmul_11_stream_num_ops_res : cparam_matmul_11_stream_num_ops;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_2;
        end
        matmul_11_comp_fsm_2: begin
          matmul_11_stream_pad_masks <= { matmul_11_stream_pad_mask_0_0 };
          matmul_11_comp_fsm <= matmul_11_comp_fsm_3;
        end
        matmul_11_comp_fsm_3: begin
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          if(_stream_matmul_11_stream_oready) begin
            matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
          end 
          matmul_11_comp_fsm <= matmul_11_comp_fsm_4;
        end
        matmul_11_comp_fsm_4: begin
          if(!_stream_matmul_11_source_busy) begin
            matmul_11_comp_fsm <= matmul_11_comp_fsm_5;
          end 
        end
        matmul_11_comp_fsm_5: begin
          if(_stream_matmul_11_busy) begin
            matmul_11_comp_fsm <= matmul_11_comp_fsm_6;
          end 
        end
        matmul_11_comp_fsm_6: begin
          if(!((matmul_11_col_select == 0)? cparam_matmul_11_inc_act_laddr_conds_0 : 0)) begin
            matmul_11_stream_act_local_0 <= matmul_11_stream_act_local_0 + cparam_matmul_11_inc_act_laddr_small;
          end 
          if((matmul_11_col_select == 0)? cparam_matmul_11_inc_act_laddr_conds_0 : 0) begin
            matmul_11_stream_act_local_0 <= matmul_11_stream_act_local_0 + cparam_matmul_11_inc_act_laddr_large;
          end 
          if(matmul_11_col_count >= cparam_matmul_11_max_col_count) begin
            matmul_11_stream_act_local_0 <= 0;
          end 
          if((matmul_11_col_count >= cparam_matmul_11_max_col_count) && cparam_matmul_11_stream_act_local_small_flags_0) begin
            matmul_11_stream_act_local_0 <= cparam_matmul_11_stream_act_local_small_offset;
          end 
          if((matmul_11_col_count >= cparam_matmul_11_max_col_count) && cparam_matmul_11_stream_act_local_large_flags_0) begin
            matmul_11_stream_act_local_0 <= cparam_matmul_11_stream_act_local_large_offset;
          end 
          if(cparam_matmul_11_data_stationary == 0) begin
            matmul_11_stream_out_local_col <= matmul_11_stream_out_local_col + matmul_11_next_stream_num_ops;
          end 
          if((cparam_matmul_11_data_stationary == 0) && (matmul_11_col_count >= cparam_matmul_11_max_col_count)) begin
            matmul_11_stream_out_local_col <= 0;
          end 
          if(cparam_matmul_11_data_stationary == 1) begin
            matmul_11_stream_out_local_col <= matmul_11_stream_out_local_col + cparam_matmul_11_inc_out_laddr_col;
          end 
          if((cparam_matmul_11_data_stationary == 1) && (matmul_11_col_count >= cparam_matmul_11_max_col_count)) begin
            matmul_11_stream_out_local_val <= matmul_11_stream_out_local_val + matmul_11_next_stream_num_ops;
            matmul_11_stream_out_local_col <= 0;
          end 
          matmul_11_col_count <= matmul_11_col_count + cparam_matmul_11_stride_col_par_col;
          if(matmul_11_col_count >= cparam_matmul_11_max_col_count) begin
            matmul_11_col_count <= 0;
          end 
          matmul_11_col_select <= matmul_11_col_select + cparam_matmul_11_stride_col_mod_filter_num;
          if(matmul_11_col_select + cparam_matmul_11_stride_col_mod_filter_num >= 1) begin
            matmul_11_col_select <= matmul_11_col_select - cparam_matmul_11_filter_num_col_minus_stride_col_mod;
          end 
          if(matmul_11_col_count >= cparam_matmul_11_max_col_count) begin
            matmul_11_col_select <= cparam_matmul_11_col_select_initval;
          end 
          matmul_11_comp_fsm <= matmul_11_comp_fsm_2;
          if(matmul_11_col_count >= cparam_matmul_11_max_col_count) begin
            matmul_11_comp_fsm <= matmul_11_comp_fsm_init;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _tmp_134 <= 0;
    end else begin
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_7_source_ram_renable && (_stream_matmul_11_source_7_source_sel == 1)) begin
        _tmp_134 <= read_rtl_bank_133;
      end 
    end
  end

  localparam _stream_matmul_11_source_7_source_pat_fsm_0_1 = 1;
  localparam _stream_matmul_11_source_7_source_pat_fsm_0_2 = 2;

  always @(posedge CLK) begin
    if(RST) begin
      _stream_matmul_11_source_7_source_pat_fsm_0 <= _stream_matmul_11_source_7_source_pat_fsm_0_init;
    end else begin
      case(_stream_matmul_11_source_7_source_pat_fsm_0)
        _stream_matmul_11_source_7_source_pat_fsm_0_init: begin
          if(_stream_matmul_11_source_start && _stream_matmul_11_source_7_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_7_source_pat_fsm_0 <= _stream_matmul_11_source_7_source_pat_fsm_0_1;
          end 
        end
        _stream_matmul_11_source_7_source_pat_fsm_0_1: begin
          if(_stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_7_source_pat_fsm_0 <= _stream_matmul_11_source_7_source_pat_fsm_0_init;
          end 
          if((_source_stream_matmul_11_source_7_pat_count_0 == 0) && (_source_stream_matmul_11_source_7_pat_count_1 == 0) && (_source_stream_matmul_11_source_7_pat_count_2 == 0) && (_source_stream_matmul_11_source_7_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_7_source_pat_fsm_0 <= _stream_matmul_11_source_7_source_pat_fsm_0_2;
          end 
        end
        _stream_matmul_11_source_7_source_pat_fsm_0_2: begin
          if(_stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_7_source_pat_fsm_0 <= _stream_matmul_11_source_7_source_pat_fsm_0_init;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _tmp_144 <= 0;
    end else begin
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_9_source_ram_renable && (_stream_matmul_11_source_9_source_sel == 2)) begin
        _tmp_144 <= read_rtl_bank_143;
      end 
    end
  end

  localparam _stream_matmul_11_source_9_source_pat_fsm_1_1 = 1;
  localparam _stream_matmul_11_source_9_source_pat_fsm_1_2 = 2;

  always @(posedge CLK) begin
    if(RST) begin
      _stream_matmul_11_source_9_source_pat_fsm_1 <= _stream_matmul_11_source_9_source_pat_fsm_1_init;
    end else begin
      case(_stream_matmul_11_source_9_source_pat_fsm_1)
        _stream_matmul_11_source_9_source_pat_fsm_1_init: begin
          if(_stream_matmul_11_source_start && _stream_matmul_11_source_9_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_9_source_pat_fsm_1 <= _stream_matmul_11_source_9_source_pat_fsm_1_1;
          end 
        end
        _stream_matmul_11_source_9_source_pat_fsm_1_1: begin
          if(_stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_9_source_pat_fsm_1 <= _stream_matmul_11_source_9_source_pat_fsm_1_init;
          end 
          if((_source_stream_matmul_11_source_9_pat_count_0 == 0) && (_source_stream_matmul_11_source_9_pat_count_1 == 0) && (_source_stream_matmul_11_source_9_pat_count_2 == 0) && (_source_stream_matmul_11_source_9_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_9_source_pat_fsm_1 <= _stream_matmul_11_source_9_source_pat_fsm_1_2;
          end 
        end
        _stream_matmul_11_source_9_source_pat_fsm_1_2: begin
          if(_stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_9_source_pat_fsm_1 <= _stream_matmul_11_source_9_source_pat_fsm_1_init;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _tmp_163 <= 0;
    end else begin
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_20_source_ram_renable && (_stream_matmul_11_source_20_source_sel == 3)) begin
        _tmp_163 <= read_rtl_bank_162;
      end 
    end
  end

  localparam _stream_matmul_11_source_20_source_pat_fsm_2_1 = 1;
  localparam _stream_matmul_11_source_20_source_pat_fsm_2_2 = 2;

  always @(posedge CLK) begin
    if(RST) begin
      _stream_matmul_11_source_20_source_pat_fsm_2 <= _stream_matmul_11_source_20_source_pat_fsm_2_init;
    end else begin
      case(_stream_matmul_11_source_20_source_pat_fsm_2)
        _stream_matmul_11_source_20_source_pat_fsm_2_init: begin
          if(_stream_matmul_11_source_start && _stream_matmul_11_source_20_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_20_source_pat_fsm_2 <= _stream_matmul_11_source_20_source_pat_fsm_2_1;
          end 
        end
        _stream_matmul_11_source_20_source_pat_fsm_2_1: begin
          if(_stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_20_source_pat_fsm_2 <= _stream_matmul_11_source_20_source_pat_fsm_2_init;
          end 
          if((_source_stream_matmul_11_source_20_pat_count_0 == 0) && (_source_stream_matmul_11_source_20_pat_count_1 == 0) && (_source_stream_matmul_11_source_20_pat_count_2 == 0) && (_source_stream_matmul_11_source_20_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_20_source_pat_fsm_2 <= _stream_matmul_11_source_20_source_pat_fsm_2_2;
          end 
        end
        _stream_matmul_11_source_20_source_pat_fsm_2_2: begin
          if(_stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_20_source_pat_fsm_2 <= _stream_matmul_11_source_20_source_pat_fsm_2_init;
          end 
        end
      endcase
    end
  end


  always @(posedge CLK) begin
    if(RST) begin
      _tmp_172 <= 0;
    end else begin
      if(_stream_matmul_11_stream_oready && _stream_matmul_11_source_21_source_ram_renable && (_stream_matmul_11_source_21_source_sel == 4)) begin
        _tmp_172 <= read_rtl_bank_171;
      end 
    end
  end

  localparam _stream_matmul_11_source_21_source_pat_fsm_3_1 = 1;
  localparam _stream_matmul_11_source_21_source_pat_fsm_3_2 = 2;

  always @(posedge CLK) begin
    if(RST) begin
      _stream_matmul_11_source_21_source_pat_fsm_3 <= _stream_matmul_11_source_21_source_pat_fsm_3_init;
    end else begin
      case(_stream_matmul_11_source_21_source_pat_fsm_3)
        _stream_matmul_11_source_21_source_pat_fsm_3_init: begin
          if(_stream_matmul_11_source_start && _stream_matmul_11_source_21_source_mode & 5'b10 && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_21_source_pat_fsm_3 <= _stream_matmul_11_source_21_source_pat_fsm_3_1;
          end 
        end
        _stream_matmul_11_source_21_source_pat_fsm_3_1: begin
          if(_stream_matmul_11_source_stop && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_21_source_pat_fsm_3 <= _stream_matmul_11_source_21_source_pat_fsm_3_init;
          end 
          if((_source_stream_matmul_11_source_21_pat_count_0 == 0) && (_source_stream_matmul_11_source_21_pat_count_1 == 0) && (_source_stream_matmul_11_source_21_pat_count_2 == 0) && (_source_stream_matmul_11_source_21_pat_count_3 == 0) && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_21_source_pat_fsm_3 <= _stream_matmul_11_source_21_source_pat_fsm_3_2;
          end 
        end
        _stream_matmul_11_source_21_source_pat_fsm_3_2: begin
          if(_stream_matmul_11_stream_oready) begin
            _stream_matmul_11_source_21_source_pat_fsm_3 <= _stream_matmul_11_source_21_source_pat_fsm_3_init;
          end 
        end
      endcase
    end
  end

  localparam _stream_matmul_11_sink_26_sink_fsm_4_1 = 1;
  localparam _stream_matmul_11_sink_26_sink_fsm_4_2 = 2;

  always @(posedge CLK) begin
    if(RST) begin
      _stream_matmul_11_sink_26_sink_fsm_4 <= _stream_matmul_11_sink_26_sink_fsm_4_init;
    end else begin
      case(_stream_matmul_11_sink_26_sink_fsm_4)
        _stream_matmul_11_sink_26_sink_fsm_4_init: begin
          if(_stream_matmul_11_sink_start && _stream_matmul_11_sink_26_sink_mode & 5'b1 && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_sink_26_sink_fsm_4 <= _stream_matmul_11_sink_26_sink_fsm_4_1;
          end 
        end
        _stream_matmul_11_sink_26_sink_fsm_4_1: begin
          if(_stream_matmul_11_stream_oready) begin
            _stream_matmul_11_sink_26_sink_fsm_4 <= _stream_matmul_11_sink_26_sink_fsm_4_2;
          end 
        end
        _stream_matmul_11_sink_26_sink_fsm_4_2: begin
          if(stream_matmul_11_sink_27_data && (_stream_matmul_11_sink_26_sink_count == 1) && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_sink_26_sink_fsm_4 <= _stream_matmul_11_sink_26_sink_fsm_4_init;
          end 
          if(_stream_matmul_11_sink_stop && _stream_matmul_11_stream_oready) begin
            _stream_matmul_11_sink_26_sink_fsm_4 <= _stream_matmul_11_sink_26_sink_fsm_4_init;
          end 
        end
      endcase
    end
  end

  localparam _maxi_write_req_fsm_1 = 1;

  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _maxi_write_req_fsm <= _maxi_write_req_fsm_init;
      _maxi_write_cont <= 0;
    end else begin
      case(_maxi_write_req_fsm)
        _maxi_write_req_fsm_init: begin
          if((_maxi_write_req_fsm == 0) && (_maxi_write_start || _maxi_write_cont) && !_maxi_write_req_fifo_almost_full) begin
            _maxi_write_req_fsm <= _maxi_write_req_fsm_1;
          end 
        end
        _maxi_write_req_fsm_1: begin
          if((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6)) begin
            _maxi_write_cont <= 1;
          end 
          if((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6) && (_maxi_write_global_size == 0)) begin
            _maxi_write_cont <= 0;
          end 
          if((_maxi_write_req_fsm == 1) && !_maxi_write_req_fifo_almost_full && (maxi_awready || !maxi_awvalid) && (_maxi_outstanding_wcount < 6)) begin
            _maxi_write_req_fsm <= _maxi_write_req_fsm_init;
          end 
        end
      endcase
    end
  end

  localparam _maxi_write_data_fsm_1 = 1;
  localparam _maxi_write_data_fsm_2 = 2;

  always @(posedge CLK) begin
    if(RESETN_inv_buf) begin
      _maxi_write_data_fsm <= _maxi_write_data_fsm_init;
    end else begin
      case(_maxi_write_data_fsm)
        _maxi_write_data_fsm_init: begin
          if(!_maxi_write_data_busy && !_maxi_write_req_fifo_empty && (_maxi_write_op_sel_fifo == 1)) begin
            _maxi_write_data_fsm <= _maxi_write_data_fsm_1;
          end 
        end
        _maxi_write_data_fsm_1: begin
          _maxi_write_data_fsm <= _maxi_write_data_fsm_2;
        end
        _maxi_write_data_fsm_2: begin
          if((_maxi_write_op_sel_buf == 1) && read_burst_packed_rvalid_533 && ((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0)) && read_burst_packed_rlast_534) begin
            _maxi_write_data_fsm <= _maxi_write_data_fsm_init;
          end 
        end
      endcase
    end
  end

  localparam read_burst_packed_fsm_4_1 = 1;

  always @(posedge CLK) begin
    if(RST) begin
      read_burst_packed_fsm_4 <= read_burst_packed_fsm_4_init;
      read_burst_packed_addr_530 <= 0;
      read_burst_packed_stride_531 <= 0;
      read_burst_packed_length_532 <= 0;
      read_burst_packed_rvalid_533 <= 0;
      read_burst_packed_rlast_534 <= 0;
    end else begin
      case(read_burst_packed_fsm_4)
        read_burst_packed_fsm_4_init: begin
          read_burst_packed_addr_530 <= _maxi_write_local_addr_buf;
          read_burst_packed_stride_531 <= _maxi_write_local_stride_buf;
          read_burst_packed_length_532 <= _maxi_write_size_buf;
          read_burst_packed_rvalid_533 <= 0;
          read_burst_packed_rlast_534 <= 0;
          if((_maxi_write_data_fsm == 1) && (_maxi_write_op_sel_buf == 1) && (_maxi_write_size_buf > 0)) begin
            read_burst_packed_fsm_4 <= read_burst_packed_fsm_4_1;
          end 
        end
        read_burst_packed_fsm_4_1: begin
          if((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0) && (read_burst_packed_length_532 > 0)) begin
            read_burst_packed_addr_530 <= read_burst_packed_addr_530 + read_burst_packed_stride_531;
            read_burst_packed_length_532 <= read_burst_packed_length_532 - 1;
            read_burst_packed_rvalid_533 <= 1;
          end 
          if((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0) && (read_burst_packed_length_532 <= 1)) begin
            read_burst_packed_rlast_534 <= 1;
          end 
          if(read_burst_packed_rlast_534 && read_burst_packed_rvalid_533 && ((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0))) begin
            read_burst_packed_rvalid_533 <= 0;
            read_burst_packed_rlast_534 <= 0;
          end 
          if(0) begin
            read_burst_packed_rvalid_533 <= 0;
            read_burst_packed_rlast_534 <= 0;
          end 
          if(read_burst_packed_rlast_534 && read_burst_packed_rvalid_533 && ((_maxi_wready_sb_0 || !_maxi_wvalid_sb_0) && (_maxi_write_size_buf > 0))) begin
            read_burst_packed_fsm_4 <= read_burst_packed_fsm_4_init;
          end 
          if(0) begin
            read_burst_packed_fsm_4 <= read_burst_packed_fsm_4_init;
          end 
        end
      endcase
    end
  end


endmodule



module _maxi_read_req_fifo
(
  input CLK,
  input RST,
  input _maxi_read_req_fifo_enq,
  input [137-1:0] _maxi_read_req_fifo_wdata,
  output _maxi_read_req_fifo_full,
  output _maxi_read_req_fifo_almost_full,
  input _maxi_read_req_fifo_deq,
  output [137-1:0] _maxi_read_req_fifo_rdata,
  output _maxi_read_req_fifo_empty,
  output _maxi_read_req_fifo_almost_empty
);

  reg [137-1:0] mem [0:8-1];
  reg [3-1:0] head;
  reg [3-1:0] tail;
  wire is_empty;
  wire is_almost_empty;
  wire is_full;
  wire is_almost_full;
  assign is_empty = head == tail;
  assign is_almost_empty = head == (tail + 1 & 7);
  assign is_full = (head + 1 & 7) == tail;
  assign is_almost_full = (head + 2 & 7) == tail;
  wire [137-1:0] rdata;
  assign _maxi_read_req_fifo_full = is_full;
  assign _maxi_read_req_fifo_almost_full = is_almost_full || is_full;
  assign _maxi_read_req_fifo_empty = is_empty;
  assign _maxi_read_req_fifo_almost_empty = is_almost_empty || is_empty;
  assign rdata = mem[tail];
  assign _maxi_read_req_fifo_rdata = rdata;

  always @(posedge CLK) begin
    if(RST) begin
      head <= 0;
      tail <= 0;
    end else begin
      if(_maxi_read_req_fifo_enq && !is_full) begin
        mem[head] <= _maxi_read_req_fifo_wdata;
        head <= head + 1;
      end 
      if(_maxi_read_req_fifo_deq && !is_empty) begin
        tail <= tail + 1;
      end 
    end
  end


endmodule



module _maxi_write_req_fifo
(
  input CLK,
  input RST,
  input _maxi_write_req_fifo_enq,
  input [137-1:0] _maxi_write_req_fifo_wdata,
  output _maxi_write_req_fifo_full,
  output _maxi_write_req_fifo_almost_full,
  input _maxi_write_req_fifo_deq,
  output [137-1:0] _maxi_write_req_fifo_rdata,
  output _maxi_write_req_fifo_empty,
  output _maxi_write_req_fifo_almost_empty
);

  reg [137-1:0] mem [0:8-1];
  reg [3-1:0] head;
  reg [3-1:0] tail;
  wire is_empty;
  wire is_almost_empty;
  wire is_full;
  wire is_almost_full;
  assign is_empty = head == tail;
  assign is_almost_empty = head == (tail + 1 & 7);
  assign is_full = (head + 1 & 7) == tail;
  assign is_almost_full = (head + 2 & 7) == tail;
  wire [137-1:0] rdata;
  assign _maxi_write_req_fifo_full = is_full;
  assign _maxi_write_req_fifo_almost_full = is_almost_full || is_full;
  assign _maxi_write_req_fifo_empty = is_empty;
  assign _maxi_write_req_fifo_almost_empty = is_almost_empty || is_empty;
  assign rdata = mem[tail];
  assign _maxi_write_req_fifo_rdata = rdata;

  always @(posedge CLK) begin
    if(RST) begin
      head <= 0;
      tail <= 0;
    end else begin
      if(_maxi_write_req_fifo_enq && !is_full) begin
        mem[head] <= _maxi_write_req_fifo_wdata;
        head <= head + 1;
      end 
      if(_maxi_write_req_fifo_deq && !is_empty) begin
        tail <= tail + 1;
      end 
    end
  end


endmodule



module ram_w16_l512_id0_0
(
  input CLK,
  input [8-1:0] ram_w16_l512_id0_0_0_addr,
  output [16-1:0] ram_w16_l512_id0_0_0_rdata,
  input [16-1:0] ram_w16_l512_id0_0_0_wdata,
  input ram_w16_l512_id0_0_0_wenable,
  input ram_w16_l512_id0_0_0_enable,
  input [8-1:0] ram_w16_l512_id0_0_1_addr,
  output [16-1:0] ram_w16_l512_id0_0_1_rdata,
  input [16-1:0] ram_w16_l512_id0_0_1_wdata,
  input ram_w16_l512_id0_0_1_wenable,
  input ram_w16_l512_id0_0_1_enable
);
  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id0_0_0_enable & ram_w16_l512_id0_0_1_enable;
  assign write_en_n = ~(ram_w16_l512_id0_0_1_wenable && ram_w16_l512_id0_0_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id0_0_1_enable) ? ram_w16_l512_id0_0_1_addr : ram_w16_l512_id0_0_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id0_0_1_wdata[15:8]),
    .Q(ram_w16_l512_id0_0_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id0_0_1_wdata[7:0]),
    .Q(ram_w16_l512_id0_0_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id0_0_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id0_0_0_rdata_out;
  // assign ram_w16_l512_id0_0_0_rdata = ram_w16_l512_id0_0_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id0_0_1_rdata_out;
  // assign ram_w16_l512_id0_0_1_rdata = ram_w16_l512_id0_0_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id0_0_0_enable) begin
  //     if(ram_w16_l512_id0_0_0_wenable) begin
  //       mem[ram_w16_l512_id0_0_0_addr] <= ram_w16_l512_id0_0_0_wdata;
  //       ram_w16_l512_id0_0_0_rdata_out <= ram_w16_l512_id0_0_0_wdata;
  //     end else begin
  //       ram_w16_l512_id0_0_0_rdata_out <= mem[ram_w16_l512_id0_0_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id0_0_1_enable) begin
  //     if(ram_w16_l512_id0_0_1_wenable) begin
  //       mem[ram_w16_l512_id0_0_1_addr] <= ram_w16_l512_id0_0_1_wdata;
  //       ram_w16_l512_id0_0_1_rdata_out <= ram_w16_l512_id0_0_1_wdata;
  //     end else begin
  //       ram_w16_l512_id0_0_1_rdata_out <= mem[ram_w16_l512_id0_0_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id0_1
(
  input CLK,
  input [8-1:0] ram_w16_l512_id0_1_0_addr,
  output [16-1:0] ram_w16_l512_id0_1_0_rdata,
  input [16-1:0] ram_w16_l512_id0_1_0_wdata,
  input ram_w16_l512_id0_1_0_wenable,
  input ram_w16_l512_id0_1_0_enable,
  input [8-1:0] ram_w16_l512_id0_1_1_addr,
  output [16-1:0] ram_w16_l512_id0_1_1_rdata,
  input [16-1:0] ram_w16_l512_id0_1_1_wdata,
  input ram_w16_l512_id0_1_1_wenable,
  input ram_w16_l512_id0_1_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id0_1_0_enable & ram_w16_l512_id0_1_1_enable;
  assign write_en_n = ~(ram_w16_l512_id0_1_1_wenable && ram_w16_l512_id0_1_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id0_1_1_enable) ? ram_w16_l512_id0_1_1_addr : ram_w16_l512_id0_1_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id0_1_1_wdata[15:8]),
    .Q(ram_w16_l512_id0_1_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id0_1_1_wdata[7:0]),
    .Q(ram_w16_l512_id0_1_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id0_1_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id0_1_0_rdata_out;
  // assign ram_w16_l512_id0_1_0_rdata = ram_w16_l512_id0_1_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id0_1_1_rdata_out;
  // assign ram_w16_l512_id0_1_1_rdata = ram_w16_l512_id0_1_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id0_1_0_enable) begin
  //     if(ram_w16_l512_id0_1_0_wenable) begin
  //       mem[ram_w16_l512_id0_1_0_addr] <= ram_w16_l512_id0_1_0_wdata;
  //       ram_w16_l512_id0_1_0_rdata_out <= ram_w16_l512_id0_1_0_wdata;
  //     end else begin
  //       ram_w16_l512_id0_1_0_rdata_out <= mem[ram_w16_l512_id0_1_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id0_1_1_enable) begin
  //     if(ram_w16_l512_id0_1_1_wenable) begin
  //       mem[ram_w16_l512_id0_1_1_addr] <= ram_w16_l512_id0_1_1_wdata;
  //       ram_w16_l512_id0_1_1_rdata_out <= ram_w16_l512_id0_1_1_wdata;
  //     end else begin
  //       ram_w16_l512_id0_1_1_rdata_out <= mem[ram_w16_l512_id0_1_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id1_0
(
  input CLK,
  input [8-1:0] ram_w16_l512_id1_0_0_addr,
  output [16-1:0] ram_w16_l512_id1_0_0_rdata,
  input [16-1:0] ram_w16_l512_id1_0_0_wdata,
  input ram_w16_l512_id1_0_0_wenable,
  input ram_w16_l512_id1_0_0_enable,
  input [8-1:0] ram_w16_l512_id1_0_1_addr,
  output [16-1:0] ram_w16_l512_id1_0_1_rdata,
  input [16-1:0] ram_w16_l512_id1_0_1_wdata,
  input ram_w16_l512_id1_0_1_wenable,
  input ram_w16_l512_id1_0_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id1_0_0_enable & ram_w16_l512_id1_0_1_enable;
  assign write_en_n = ~(ram_w16_l512_id1_0_1_wenable && ram_w16_l512_id1_0_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id1_0_1_enable) ? ram_w16_l512_id1_0_1_addr : ram_w16_l512_id1_0_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id1_0_1_wdata[15:8]),
    .Q(ram_w16_l512_id1_0_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id1_0_1_wdata[7:0]),
    .Q(ram_w16_l512_id1_0_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id1_0_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id1_0_0_rdata_out;
  // assign ram_w16_l512_id1_0_0_rdata = ram_w16_l512_id1_0_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id1_0_1_rdata_out;
  // assign ram_w16_l512_id1_0_1_rdata = ram_w16_l512_id1_0_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id1_0_0_enable) begin
  //     if(ram_w16_l512_id1_0_0_wenable) begin
  //       mem[ram_w16_l512_id1_0_0_addr] <= ram_w16_l512_id1_0_0_wdata;
  //       ram_w16_l512_id1_0_0_rdata_out <= ram_w16_l512_id1_0_0_wdata;
  //     end else begin
  //       ram_w16_l512_id1_0_0_rdata_out <= mem[ram_w16_l512_id1_0_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id1_0_1_enable) begin
  //     if(ram_w16_l512_id1_0_1_wenable) begin
  //       mem[ram_w16_l512_id1_0_1_addr] <= ram_w16_l512_id1_0_1_wdata;
  //       ram_w16_l512_id1_0_1_rdata_out <= ram_w16_l512_id1_0_1_wdata;
  //     end else begin
  //       ram_w16_l512_id1_0_1_rdata_out <= mem[ram_w16_l512_id1_0_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id1_1
(
  input CLK,
  input [8-1:0] ram_w16_l512_id1_1_0_addr,
  output [16-1:0] ram_w16_l512_id1_1_0_rdata,
  input [16-1:0] ram_w16_l512_id1_1_0_wdata,
  input ram_w16_l512_id1_1_0_wenable,
  input ram_w16_l512_id1_1_0_enable,
  input [8-1:0] ram_w16_l512_id1_1_1_addr,
  output [16-1:0] ram_w16_l512_id1_1_1_rdata,
  input [16-1:0] ram_w16_l512_id1_1_1_wdata,
  input ram_w16_l512_id1_1_1_wenable,
  input ram_w16_l512_id1_1_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id1_1_0_enable & ram_w16_l512_id1_1_1_enable;
  assign write_en_n = ~(ram_w16_l512_id1_1_1_wenable && ram_w16_l512_id1_1_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id1_1_1_enable) ? ram_w16_l512_id1_1_1_addr : ram_w16_l512_id1_1_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id1_1_1_wdata[15:8]),
    .Q(ram_w16_l512_id1_1_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id1_1_1_wdata[7:0]),
    .Q(ram_w16_l512_id1_1_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id1_1_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id1_1_0_rdata_out;
  // assign ram_w16_l512_id1_1_0_rdata = ram_w16_l512_id1_1_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id1_1_1_rdata_out;
  // assign ram_w16_l512_id1_1_1_rdata = ram_w16_l512_id1_1_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id1_1_0_enable) begin
  //     if(ram_w16_l512_id1_1_0_wenable) begin
  //       mem[ram_w16_l512_id1_1_0_addr] <= ram_w16_l512_id1_1_0_wdata;
  //       ram_w16_l512_id1_1_0_rdata_out <= ram_w16_l512_id1_1_0_wdata;
  //     end else begin
  //       ram_w16_l512_id1_1_0_rdata_out <= mem[ram_w16_l512_id1_1_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id1_1_1_enable) begin
  //     if(ram_w16_l512_id1_1_1_wenable) begin
  //       mem[ram_w16_l512_id1_1_1_addr] <= ram_w16_l512_id1_1_1_wdata;
  //       ram_w16_l512_id1_1_1_rdata_out <= ram_w16_l512_id1_1_1_wdata;
  //     end else begin
  //       ram_w16_l512_id1_1_1_rdata_out <= mem[ram_w16_l512_id1_1_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id2_0
(
  input CLK,
  input [8-1:0] ram_w16_l512_id2_0_0_addr,
  output [16-1:0] ram_w16_l512_id2_0_0_rdata,
  input [16-1:0] ram_w16_l512_id2_0_0_wdata,
  input ram_w16_l512_id2_0_0_wenable,
  input ram_w16_l512_id2_0_0_enable,
  input [8-1:0] ram_w16_l512_id2_0_1_addr,
  output [16-1:0] ram_w16_l512_id2_0_1_rdata,
  input [16-1:0] ram_w16_l512_id2_0_1_wdata,
  input ram_w16_l512_id2_0_1_wenable,
  input ram_w16_l512_id2_0_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id2_0_0_enable & ram_w16_l512_id2_0_1_enable;
  assign write_en_n = ~(ram_w16_l512_id2_0_1_wenable && ram_w16_l512_id2_0_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id2_0_1_enable) ? ram_w16_l512_id2_0_1_addr : ram_w16_l512_id2_0_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id2_0_1_wdata[15:8]),
    .Q(ram_w16_l512_id2_0_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id2_0_1_wdata[7:0]),
    .Q(ram_w16_l512_id2_0_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id2_0_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id2_0_0_rdata_out;
  // assign ram_w16_l512_id2_0_0_rdata = ram_w16_l512_id2_0_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id2_0_1_rdata_out;
  // assign ram_w16_l512_id2_0_1_rdata = ram_w16_l512_id2_0_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id2_0_0_enable) begin
  //     if(ram_w16_l512_id2_0_0_wenable) begin
  //       mem[ram_w16_l512_id2_0_0_addr] <= ram_w16_l512_id2_0_0_wdata;
  //       ram_w16_l512_id2_0_0_rdata_out <= ram_w16_l512_id2_0_0_wdata;
  //     end else begin
  //       ram_w16_l512_id2_0_0_rdata_out <= mem[ram_w16_l512_id2_0_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id2_0_1_enable) begin
  //     if(ram_w16_l512_id2_0_1_wenable) begin
  //       mem[ram_w16_l512_id2_0_1_addr] <= ram_w16_l512_id2_0_1_wdata;
  //       ram_w16_l512_id2_0_1_rdata_out <= ram_w16_l512_id2_0_1_wdata;
  //     end else begin
  //       ram_w16_l512_id2_0_1_rdata_out <= mem[ram_w16_l512_id2_0_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id2_1
(
  input CLK,
  input [8-1:0] ram_w16_l512_id2_1_0_addr,
  output [16-1:0] ram_w16_l512_id2_1_0_rdata,
  input [16-1:0] ram_w16_l512_id2_1_0_wdata,
  input ram_w16_l512_id2_1_0_wenable,
  input ram_w16_l512_id2_1_0_enable,
  input [8-1:0] ram_w16_l512_id2_1_1_addr,
  output [16-1:0] ram_w16_l512_id2_1_1_rdata,
  input [16-1:0] ram_w16_l512_id2_1_1_wdata,
  input ram_w16_l512_id2_1_1_wenable,
  input ram_w16_l512_id2_1_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id2_1_0_enable & ram_w16_l512_id2_1_1_enable;
  assign write_en_n = ~(ram_w16_l512_id2_1_1_wenable && ram_w16_l512_id2_1_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id2_1_1_enable) ? ram_w16_l512_id2_1_1_addr : ram_w16_l512_id2_1_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id2_1_1_wdata[15:8]),
    .Q(ram_w16_l512_id2_1_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id2_1_1_wdata[7:0]),
    .Q(ram_w16_l512_id2_1_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id2_1_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id2_1_0_rdata_out;
  // assign ram_w16_l512_id2_1_0_rdata = ram_w16_l512_id2_1_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id2_1_1_rdata_out;
  // assign ram_w16_l512_id2_1_1_rdata = ram_w16_l512_id2_1_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id2_1_0_enable) begin
  //     if(ram_w16_l512_id2_1_0_wenable) begin
  //       mem[ram_w16_l512_id2_1_0_addr] <= ram_w16_l512_id2_1_0_wdata;
  //       ram_w16_l512_id2_1_0_rdata_out <= ram_w16_l512_id2_1_0_wdata;
  //     end else begin
  //       ram_w16_l512_id2_1_0_rdata_out <= mem[ram_w16_l512_id2_1_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id2_1_1_enable) begin
  //     if(ram_w16_l512_id2_1_1_wenable) begin
  //       mem[ram_w16_l512_id2_1_1_addr] <= ram_w16_l512_id2_1_1_wdata;
  //       ram_w16_l512_id2_1_1_rdata_out <= ram_w16_l512_id2_1_1_wdata;
  //     end else begin
  //       ram_w16_l512_id2_1_1_rdata_out <= mem[ram_w16_l512_id2_1_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id3_0
(
  input CLK,
  input [8-1:0] ram_w16_l512_id3_0_0_addr,
  output [16-1:0] ram_w16_l512_id3_0_0_rdata,
  input [16-1:0] ram_w16_l512_id3_0_0_wdata,
  input ram_w16_l512_id3_0_0_wenable,
  input ram_w16_l512_id3_0_0_enable,
  input [8-1:0] ram_w16_l512_id3_0_1_addr,
  output [16-1:0] ram_w16_l512_id3_0_1_rdata,
  input [16-1:0] ram_w16_l512_id3_0_1_wdata,
  input ram_w16_l512_id3_0_1_wenable,
  input ram_w16_l512_id3_0_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id3_0_0_enable & ram_w16_l512_id3_0_1_enable;
  assign write_en_n = ~(ram_w16_l512_id3_0_1_wenable && ram_w16_l512_id3_0_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id3_0_1_enable) ? ram_w16_l512_id3_0_1_addr : ram_w16_l512_id3_0_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id3_0_1_wdata[15:8]),
    .Q(ram_w16_l512_id3_0_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id3_0_1_wdata[7:0]),
    .Q(ram_w16_l512_id3_0_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id3_0_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id3_0_0_rdata_out;
  // assign ram_w16_l512_id3_0_0_rdata = ram_w16_l512_id3_0_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id3_0_1_rdata_out;
  // assign ram_w16_l512_id3_0_1_rdata = ram_w16_l512_id3_0_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id3_0_0_enable) begin
  //     if(ram_w16_l512_id3_0_0_wenable) begin
  //       mem[ram_w16_l512_id3_0_0_addr] <= ram_w16_l512_id3_0_0_wdata;
  //       ram_w16_l512_id3_0_0_rdata_out <= ram_w16_l512_id3_0_0_wdata;
  //     end else begin
  //       ram_w16_l512_id3_0_0_rdata_out <= mem[ram_w16_l512_id3_0_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id3_0_1_enable) begin
  //     if(ram_w16_l512_id3_0_1_wenable) begin
  //       mem[ram_w16_l512_id3_0_1_addr] <= ram_w16_l512_id3_0_1_wdata;
  //       ram_w16_l512_id3_0_1_rdata_out <= ram_w16_l512_id3_0_1_wdata;
  //     end else begin
  //       ram_w16_l512_id3_0_1_rdata_out <= mem[ram_w16_l512_id3_0_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id3_1
(
  input CLK,
  input [8-1:0] ram_w16_l512_id3_1_0_addr,
  output [16-1:0] ram_w16_l512_id3_1_0_rdata,
  input [16-1:0] ram_w16_l512_id3_1_0_wdata,
  input ram_w16_l512_id3_1_0_wenable,
  input ram_w16_l512_id3_1_0_enable,
  input [8-1:0] ram_w16_l512_id3_1_1_addr,
  output [16-1:0] ram_w16_l512_id3_1_1_rdata,
  input [16-1:0] ram_w16_l512_id3_1_1_wdata,
  input ram_w16_l512_id3_1_1_wenable,
  input ram_w16_l512_id3_1_1_enable
);

    supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id3_1_0_enable & ram_w16_l512_id3_1_1_enable;
  assign write_en_n = ~(ram_w16_l512_id3_1_1_wenable && ram_w16_l512_id3_1_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id3_1_1_enable) ? ram_w16_l512_id3_1_1_addr : ram_w16_l512_id3_1_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id3_1_1_wdata[15:8]),
    .Q(ram_w16_l512_id3_1_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id3_1_1_wdata[7:0]),
    .Q(ram_w16_l512_id3_1_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id3_1_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id3_1_0_rdata_out;
  // assign ram_w16_l512_id3_1_0_rdata = ram_w16_l512_id3_1_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id3_1_1_rdata_out;
  // assign ram_w16_l512_id3_1_1_rdata = ram_w16_l512_id3_1_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id3_1_0_enable) begin
  //     if(ram_w16_l512_id3_1_0_wenable) begin
  //       mem[ram_w16_l512_id3_1_0_addr] <= ram_w16_l512_id3_1_0_wdata;
  //       ram_w16_l512_id3_1_0_rdata_out <= ram_w16_l512_id3_1_0_wdata;
  //     end else begin
  //       ram_w16_l512_id3_1_0_rdata_out <= mem[ram_w16_l512_id3_1_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id3_1_1_enable) begin
  //     if(ram_w16_l512_id3_1_1_wenable) begin
  //       mem[ram_w16_l512_id3_1_1_addr] <= ram_w16_l512_id3_1_1_wdata;
  //       ram_w16_l512_id3_1_1_rdata_out <= ram_w16_l512_id3_1_1_wdata;
  //     end else begin
  //       ram_w16_l512_id3_1_1_rdata_out <= mem[ram_w16_l512_id3_1_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id4_0
(
  input CLK,
  input [8-1:0] ram_w16_l512_id4_0_0_addr,
  output [16-1:0] ram_w16_l512_id4_0_0_rdata,
  input [16-1:0] ram_w16_l512_id4_0_0_wdata,
  input ram_w16_l512_id4_0_0_wenable,
  input ram_w16_l512_id4_0_0_enable,
  input [8-1:0] ram_w16_l512_id4_0_1_addr,
  output [16-1:0] ram_w16_l512_id4_0_1_rdata,
  input [16-1:0] ram_w16_l512_id4_0_1_wdata,
  input ram_w16_l512_id4_0_1_wenable,
  input ram_w16_l512_id4_0_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id4_0_0_enable & ram_w16_l512_id4_0_1_enable;
  assign write_en_n = ~(ram_w16_l512_id4_0_1_wenable && ram_w16_l512_id4_0_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id4_0_1_enable) ? ram_w16_l512_id4_0_1_addr : ram_w16_l512_id4_0_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id4_0_1_wdata[15:8]),
    .Q(ram_w16_l512_id4_0_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id4_0_1_wdata[7:0]),
    .Q(ram_w16_l512_id4_0_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id4_0_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id4_0_0_rdata_out;
  // assign ram_w16_l512_id4_0_0_rdata = ram_w16_l512_id4_0_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id4_0_1_rdata_out;
  // assign ram_w16_l512_id4_0_1_rdata = ram_w16_l512_id4_0_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id4_0_0_enable) begin
  //     if(ram_w16_l512_id4_0_0_wenable) begin
  //       mem[ram_w16_l512_id4_0_0_addr] <= ram_w16_l512_id4_0_0_wdata;
  //       ram_w16_l512_id4_0_0_rdata_out <= ram_w16_l512_id4_0_0_wdata;
  //     end else begin
  //       ram_w16_l512_id4_0_0_rdata_out <= mem[ram_w16_l512_id4_0_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id4_0_1_enable) begin
  //     if(ram_w16_l512_id4_0_1_wenable) begin
  //       mem[ram_w16_l512_id4_0_1_addr] <= ram_w16_l512_id4_0_1_wdata;
  //       ram_w16_l512_id4_0_1_rdata_out <= ram_w16_l512_id4_0_1_wdata;
  //     end else begin
  //       ram_w16_l512_id4_0_1_rdata_out <= mem[ram_w16_l512_id4_0_1_addr];
  //     end
  //   end 
  // end


endmodule



module ram_w16_l512_id4_1
(
  input CLK,
  input [8-1:0] ram_w16_l512_id4_1_0_addr,
  output [16-1:0] ram_w16_l512_id4_1_0_rdata,
  input [16-1:0] ram_w16_l512_id4_1_0_wdata,
  input ram_w16_l512_id4_1_0_wenable,
  input ram_w16_l512_id4_1_0_enable,
  input [8-1:0] ram_w16_l512_id4_1_1_addr,
  output [16-1:0] ram_w16_l512_id4_1_1_rdata,
  input [16-1:0] ram_w16_l512_id4_1_1_wdata,
  input ram_w16_l512_id4_1_1_wenable,
  input ram_w16_l512_id4_1_1_enable
);

  supply1 vdd;
  supply0 vss;

  wire write_en_n;
  wire [8:0] addr;
  wire activate = ram_w16_l512_id4_1_0_enable & ram_w16_l512_id4_1_1_enable;
  assign write_en_n = ~(ram_w16_l512_id4_1_1_wenable && ram_w16_l512_id4_1_1_enable);
  assign addr = {1'b0,(ram_w16_l512_id4_1_1_enable) ? ram_w16_l512_id4_1_1_addr : ram_w16_l512_id4_1_0_addr};

  gf180mcu_fd_ip_sram__sram512x8m8wm1
  mem_top (
    .CLK(CLK), 
    .CEN(~activate), //chip enable, just hardcoded one for now
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id4_1_1_wdata[15:8]),
    .Q(ram_w16_l512_id4_1_0_rdata[15:8]),
    .VDD(vdd), 
    .VSS(vss)
  );

  gf180mcu_fd_ip_sram__sram512x8m8wm1 
  mem_bot (
    .CLK(CLK), 
    .CEN(~activate), 
    .GWEN(write_en_n),
    .WEN(8'b00000000), 
    .A(addr),
    .D(ram_w16_l512_id4_1_1_wdata[7:0]),
    .Q(ram_w16_l512_id4_1_0_rdata[7:0]),
    .VDD(vdd), 
    .VSS(vss)
  );

  assign ram_w16_l512_id4_1_1_rdata = 16'h0000;

  // reg [16-1:0] ram_w16_l512_id4_1_0_rdata_out;
  // assign ram_w16_l512_id4_1_0_rdata = ram_w16_l512_id4_1_0_rdata_out;
  // reg [16-1:0] ram_w16_l512_id4_1_1_rdata_out;
  // assign ram_w16_l512_id4_1_1_rdata = ram_w16_l512_id4_1_1_rdata_out;
  // reg [16-1:0] mem [0:256-1];

  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id4_1_0_enable) begin
  //     if(ram_w16_l512_id4_1_0_wenable) begin
  //       mem[ram_w16_l512_id4_1_0_addr] <= ram_w16_l512_id4_1_0_wdata;
  //       ram_w16_l512_id4_1_0_rdata_out <= ram_w16_l512_id4_1_0_wdata;
  //     end else begin
  //       ram_w16_l512_id4_1_0_rdata_out <= mem[ram_w16_l512_id4_1_0_addr];
  //     end
  //   end 
  // end


  // always @(posedge CLK) begin
  //   if(ram_w16_l512_id4_1_1_enable) begin
  //     if(ram_w16_l512_id4_1_1_wenable) begin
  //       mem[ram_w16_l512_id4_1_1_addr] <= ram_w16_l512_id4_1_1_wdata;
  //       ram_w16_l512_id4_1_1_rdata_out <= ram_w16_l512_id4_1_1_wdata;
  //     end else begin
  //       ram_w16_l512_id4_1_1_rdata_out <= mem[ram_w16_l512_id4_1_1_addr];
  //     end
  //   end 
  // end


endmodule



module madd_0
(
  input CLK,
  input update,
  input [16-1:0] a,
  input [16-1:0] b,
  input [16-1:0] c,
  output [32-1:0] d
);


  madd_core_0
  madd
  (
    .CLK(CLK),
    .update(update),
    .a(a),
    .b(b),
    .c(c),
    .d(d)
  );


endmodule



module madd_core_0
(
  input CLK,
  input update,
  input [16-1:0] a,
  input [16-1:0] b,
  input [16-1:0] c,
  output [32-1:0] d
);

  reg signed [16-1:0] _a;
  reg signed [16-1:0] _b;
  reg signed [16-1:0] _c;
  wire signed [32-1:0] _mul;
  wire signed [32-1:0] _madd;
  reg signed [32-1:0] _pipe_madd0;
  reg signed [32-1:0] _pipe_madd1;
  assign _mul = _a * _b;
  assign _madd = _mul + _c;
  assign d = _pipe_madd1;

  always @(posedge CLK) begin
    if(update) begin
      _a <= a;
      _b <= b;
      _c <= c;
      _pipe_madd0 <= _madd;
      _pipe_madd1 <= _pipe_madd0;
    end 
  end


endmodule



module multiplier_0
(
  input CLK,
  input update,
  input [64-1:0] a,
  input [16-1:0] b,
  output [80-1:0] c
);


  multiplier_core_0
  mult
  (
    .CLK(CLK),
    .update(update),
    .a(a),
    .b(b),
    .c(c)
  );


endmodule



module multiplier_core_0
(
  input CLK,
  input update,
  input [64-1:0] a,
  input [16-1:0] b,
  output [80-1:0] c
);

  reg signed [64-1:0] _a;
  reg signed [16-1:0] _b;
  wire signed [80-1:0] _mul;
  reg signed [80-1:0] _pipe_mul0;
  reg signed [80-1:0] _pipe_mul1;
  assign _mul = _a * _b;
  assign c = _pipe_mul1;

  always @(posedge CLK) begin
    if(update) begin
      _a <= a;
      _b <= b;
      _pipe_mul0 <= _mul;
      _pipe_mul1 <= _pipe_mul0;
    end 
  end


endmodule

