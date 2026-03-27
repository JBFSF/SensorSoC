// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vout.h for the primary calling header

#include "Vout__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vout___024root___eval_triggers__ico(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_triggers__ico\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vout___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool Vout___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vout___024root___ico_sequent__TOP__0(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___ico_sequent__TOP__0\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.test__DOT__CLK = vlSelfRef.io_CLK;
    vlSelfRef.test__DOT__RESETN = vlSelfRef.io_RESETN;
}

void Vout___024root___eval_ico(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_ico\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vout___024root___ico_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

bool Vout___024root___eval_phase__ico(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_phase__ico\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vout___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = Vout___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vout___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vout___024root___eval_triggers__act(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_triggers__act\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.test__DOT__CLK) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__test__DOT__CLK__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__test__DOT__CLK__0 
        = vlSelfRef.test__DOT__CLK;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vout___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vout___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlUnpacked<CData/*0:0*/, 128> Vout__ConstPool__TABLE_h996f76d5_0;
extern const VlUnpacked<CData/*2:0*/, 128> Vout__ConstPool__TABLE_h5d4012b8_0;

void Vout___024root___nba_sequent__TOP__0(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___nba_sequent__TOP__0\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41;
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41 = 0;
    CData/*0:0*/ test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59;
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59 = 0;
    CData/*6:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    QData/*32:0*/ __Vdly__test__DOT___keep_sleep_count;
    __Vdly__test__DOT___keep_sleep_count = 0;
    QData/*32:0*/ __Vdly__test__DOT___sleep_interval_count;
    __Vdly__test__DOT___sleep_interval_count = 0;
    CData/*0:0*/ __Vdly__test__DOT__memory_awready;
    __Vdly__test__DOT__memory_awready = 0;
    IData/*31:0*/ __Vdly__test__DOT___memory_waddr_fsm;
    __Vdly__test__DOT___memory_waddr_fsm = 0;
    IData/*31:0*/ __Vdly__test__DOT___write_addr;
    __Vdly__test__DOT___write_addr = 0;
    QData/*32:0*/ __Vdly__test__DOT___write_count;
    __Vdly__test__DOT___write_count = 0;
    IData/*31:0*/ __Vdly__test__DOT___memory_wdata_fsm;
    __Vdly__test__DOT___memory_wdata_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__memory_arready;
    __Vdly__test__DOT__memory_arready = 0;
    IData/*31:0*/ __Vdly__test__DOT___memory_raddr_fsm;
    __Vdly__test__DOT___memory_raddr_fsm = 0;
    IData/*31:0*/ __Vdly__test__DOT___d1___05Fmemory_rdata_fsm;
    __Vdly__test__DOT___d1___05Fmemory_rdata_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__memory_rvalid;
    __Vdly__test__DOT__memory_rvalid = 0;
    CData/*0:0*/ __Vdly__test__DOT__memory_rlast;
    __Vdly__test__DOT__memory_rlast = 0;
    IData/*31:0*/ __Vdly__test__DOT___read_addr;
    __Vdly__test__DOT___read_addr = 0;
    QData/*32:0*/ __Vdly__test__DOT___read_count;
    __Vdly__test__DOT___read_count = 0;
    IData/*31:0*/ __Vdly__test__DOT___memory_rdata_fsm;
    __Vdly__test__DOT___memory_rdata_fsm = 0;
    IData/*31:0*/ __Vdly__test__DOT__memory_rdata;
    __Vdly__test__DOT__memory_rdata = 0;
    CData/*3:0*/ __Vdly__test__DOT__count___05Fmemory_wreq_fifo;
    __Vdly__test__DOT__count___05Fmemory_wreq_fifo = 0;
    CData/*3:0*/ __Vdly__test__DOT__count___05Fmemory_rreq_fifo;
    __Vdly__test__DOT__count___05Fmemory_rreq_fifo = 0;
    CData/*3:0*/ __Vdly__test__DOT__count___05Fmemory_wdata_fifo;
    __Vdly__test__DOT__count___05Fmemory_wdata_fifo = 0;
    CData/*0:0*/ __Vdly__test__DOT___sb___05Fsaxi_readdata_valid_53;
    __Vdly__test__DOT___sb___05Fsaxi_readdata_valid_53 = 0;
    IData/*31:0*/ __Vdly__test__DOT__time_counter;
    __Vdly__test__DOT__time_counter = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl___05F_0;
    __Vdly__test__DOT___th_ctrl___05F_0 = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl_start_time_1;
    __Vdly__test__DOT___th_ctrl_start_time_1 = 0;
    IData/*31:0*/ __Vdly__test__DOT__axim_rdata_73;
    __Vdly__test__DOT__axim_rdata_73 = 0;
    IData/*31:0*/ __Vdly__test__DOT__axim_rdata_74;
    __Vdly__test__DOT__axim_rdata_74 = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl_end_time_2;
    __Vdly__test__DOT___th_ctrl_end_time_2 = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl_ok_3;
    __Vdly__test__DOT___th_ctrl_ok_3 = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl_bat_4;
    __Vdly__test__DOT___th_ctrl_bat_4 = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl_i_5;
    __Vdly__test__DOT___th_ctrl_i_5 = 0;
    SData/*15:0*/ __Vdly__test__DOT__rdata_75;
    __Vdly__test__DOT__rdata_75 = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl_orig_6;
    __Vdly__test__DOT___th_ctrl_orig_6 = 0;
    SData/*15:0*/ __Vdly__test__DOT__rdata_76;
    __Vdly__test__DOT__rdata_76 = 0;
    IData/*31:0*/ __Vdly__test__DOT___th_ctrl_check_7;
    __Vdly__test__DOT___th_ctrl_check_7 = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0;
    __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0 = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0;
    __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0 = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7 = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10 = 0;
    CData/*0:0*/ __Vdly__test__DOT__maxi_arvalid;
    __Vdly__test__DOT__maxi_arvalid = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22 = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_start;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_start;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_start = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_global_addr;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_global_addr = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_data_busy;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_data_busy = 0;
    CData/*7:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_op_sel_buf;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_op_sel_buf = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf = 0;
    CData/*3:0*/ __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo;
    __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo = 0;
    CData/*3:0*/ __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo;
    __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___saxi_register_11;
    __Vdly__test__DOT__taketwo__DOT___saxi_register_11 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___saxi_register_12;
    __Vdly__test__DOT__taketwo__DOT___saxi_register_12 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT__internal_state_counter;
    __Vdly__test__DOT__taketwo__DOT__internal_state_counter = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___acc_0_fsm;
    __Vdly__test__DOT__taketwo__DOT___acc_0_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___acc_0_source_start;
    __Vdly__test__DOT__taketwo__DOT___acc_0_source_start = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___add_tree_1_fsm;
    __Vdly__test__DOT__taketwo__DOT___add_tree_1_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___add_tree_1_source_start;
    __Vdly__test__DOT__taketwo__DOT___add_tree_1_source_start = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm;
    __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start;
    __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___mul_3_fsm;
    __Vdly__test__DOT__taketwo__DOT___mul_3_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___mul_3_source_start;
    __Vdly__test__DOT__taketwo__DOT___mul_3_source_start = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr;
    __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count;
    __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_req_fsm;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_req_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_cont;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_cont = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_0;
    __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_0 = 0;
    CData/*6:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_addr_76;
    __Vdly__test__DOT__taketwo__DOT__write_burst_addr_76 = 0;
    CData/*6:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_stride_77;
    __Vdly__test__DOT__taketwo__DOT__write_burst_stride_77 = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_length_78;
    __Vdly__test__DOT__taketwo__DOT__write_burst_length_78 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_1;
    __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_1 = 0;
    CData/*6:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_addr_82;
    __Vdly__test__DOT__taketwo__DOT__write_burst_addr_82 = 0;
    CData/*6:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_stride_83;
    __Vdly__test__DOT__taketwo__DOT__write_burst_stride_83 = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_length_84;
    __Vdly__test__DOT__taketwo__DOT__write_burst_length_84 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_2;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_2 = 0;
    SData/*8:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_91;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_91 = 0;
    SData/*8:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_92;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_92 = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_93;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_93 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_3;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_3 = 0;
    SData/*8:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_104;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_104 = 0;
    SData/*8:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_105;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_105 = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_106;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_106 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4;
    __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_req_fsm;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_req_fsm = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_cont;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_cont = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm = 0;
    IData/*31:0*/ __Vdly__test__DOT__taketwo__DOT__read_burst_packed_fsm_4;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_fsm_4 = 0;
    SData/*8:0*/ __Vdly__test__DOT__taketwo__DOT__read_burst_packed_addr_504;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_addr_504 = 0;
    SData/*8:0*/ __Vdly__test__DOT__taketwo__DOT__read_burst_packed_stride_505;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_stride_505 = 0;
    QData/*32:0*/ __Vdly__test__DOT__taketwo__DOT__read_burst_packed_length_506;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_length_506 = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 = 0;
    CData/*0:0*/ __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508 = 0;
    CData/*2:0*/ __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head = 0;
    CData/*2:0*/ __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail = 0;
    CData/*2:0*/ __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head = 0;
    CData/*2:0*/ __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail = 0;
    CData/*7:0*/ __VdlyVal__test__DOT___memory_mem__v0;
    __VdlyVal__test__DOT___memory_mem__v0 = 0;
    IData/*19:0*/ __VdlyDim0__test__DOT___memory_mem__v0;
    __VdlyDim0__test__DOT___memory_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT___memory_mem__v0;
    __VdlySet__test__DOT___memory_mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__test__DOT___memory_mem__v1;
    __VdlyVal__test__DOT___memory_mem__v1 = 0;
    IData/*19:0*/ __VdlyDim0__test__DOT___memory_mem__v1;
    __VdlyDim0__test__DOT___memory_mem__v1 = 0;
    CData/*0:0*/ __VdlySet__test__DOT___memory_mem__v1;
    __VdlySet__test__DOT___memory_mem__v1 = 0;
    CData/*7:0*/ __VdlyVal__test__DOT___memory_mem__v2;
    __VdlyVal__test__DOT___memory_mem__v2 = 0;
    IData/*19:0*/ __VdlyDim0__test__DOT___memory_mem__v2;
    __VdlyDim0__test__DOT___memory_mem__v2 = 0;
    CData/*0:0*/ __VdlySet__test__DOT___memory_mem__v2;
    __VdlySet__test__DOT___memory_mem__v2 = 0;
    CData/*7:0*/ __VdlyVal__test__DOT___memory_mem__v3;
    __VdlyVal__test__DOT___memory_mem__v3 = 0;
    IData/*19:0*/ __VdlyDim0__test__DOT___memory_mem__v3;
    __VdlyDim0__test__DOT___memory_mem__v3 = 0;
    CData/*0:0*/ __VdlySet__test__DOT___memory_mem__v3;
    __VdlySet__test__DOT___memory_mem__v3 = 0;
    QData/*40:0*/ __VdlyVal__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0;
    __VdlyVal__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0 = 0;
    CData/*2:0*/ __VdlyDim0__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0;
    __VdlyDim0__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0;
    __VdlySet__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0 = 0;
    QData/*40:0*/ __VdlyVal__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0;
    __VdlyVal__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0 = 0;
    CData/*2:0*/ __VdlyDim0__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0;
    __VdlyDim0__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0;
    __VdlySet__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0 = 0;
    QData/*36:0*/ __VdlyVal__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0;
    __VdlyVal__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0 = 0;
    CData/*2:0*/ __VdlyDim0__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0;
    __VdlyDim0__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0;
    __VdlySet__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0 = 0;
    VlWide<5>/*136:0*/ __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0;
    VL_ZERO_W(137, __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0);
    CData/*2:0*/ __VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0;
    __VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0;
    __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0 = 0;
    VlWide<5>/*136:0*/ __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0;
    VL_ZERO_W(137, __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0);
    CData/*2:0*/ __VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0;
    __VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0;
    __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0 = 0;
    SData/*15:0*/ __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0;
    __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0;
    __VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0;
    __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0 = 0;
    SData/*15:0*/ __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0;
    __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0;
    __VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0;
    __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0 = 0;
    VlWide<3>/*95:0*/ __Vtemp_16;
    VlWide<3>/*95:0*/ __Vtemp_17;
    VlWide<3>/*95:0*/ __Vtemp_18;
    VlWide<5>/*159:0*/ __Vtemp_23;
    VlWide<4>/*127:0*/ __Vtemp_25;
    VlWide<4>/*127:0*/ __Vtemp_26;
    VlWide<4>/*127:0*/ __Vtemp_27;
    VlWide<4>/*127:0*/ __Vtemp_28;
    VlWide<4>/*127:0*/ __Vtemp_29;
    VlWide<4>/*127:0*/ __Vtemp_30;
    VlWide<4>/*127:0*/ __Vtemp_31;
    VlWide<3>/*95:0*/ __Vtemp_39;
    VlWide<3>/*95:0*/ __Vtemp_40;
    VlWide<5>/*159:0*/ __Vtemp_43;
    VlWide<5>/*159:0*/ __Vtemp_44;
    VlWide<5>/*159:0*/ __Vtemp_50;
    VlWide<5>/*159:0*/ __Vtemp_51;
    // Body
    __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0 = 0U;
    __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0 = 0U;
    __Vdly__test__DOT__time_counter = vlSelfRef.test__DOT__time_counter;
    __Vdly__test__DOT___keep_sleep_count = vlSelfRef.test__DOT___keep_sleep_count;
    __Vdly__test__DOT___sleep_interval_count = vlSelfRef.test__DOT___sleep_interval_count;
    __Vdly__test__DOT__count___05Fmemory_wreq_fifo 
        = vlSelfRef.test__DOT__count___05Fmemory_wreq_fifo;
    __Vdly__test__DOT__count___05Fmemory_rreq_fifo 
        = vlSelfRef.test__DOT__count___05Fmemory_rreq_fifo;
    __Vdly__test__DOT__count___05Fmemory_wdata_fifo 
        = vlSelfRef.test__DOT__count___05Fmemory_wdata_fifo;
    vlSelfRef.__Vdly__test__DOT_____05Fsaxi_outstanding_wcount 
        = vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount;
    __Vdly__test__DOT__memory_arready = vlSelfRef.test__DOT__memory_arready;
    __Vdly__test__DOT___memory_raddr_fsm = vlSelfRef.test__DOT___memory_raddr_fsm;
    __Vdly__test__DOT___write_addr = vlSelfRef.test__DOT___write_addr;
    __Vdly__test__DOT___write_count = vlSelfRef.test__DOT___write_count;
    __Vdly__test__DOT___memory_wdata_fsm = vlSelfRef.test__DOT___memory_wdata_fsm;
    __Vdly__test__DOT___memory_waddr_fsm = vlSelfRef.test__DOT___memory_waddr_fsm;
    __Vdly__test__DOT__memory_awready = vlSelfRef.test__DOT__memory_awready;
    __Vdly__test__DOT___d1___05Fmemory_rdata_fsm = vlSelfRef.test__DOT___d1___05Fmemory_rdata_fsm;
    __Vdly__test__DOT___read_addr = vlSelfRef.test__DOT___read_addr;
    __Vdly__test__DOT___read_count = vlSelfRef.test__DOT___read_count;
    __Vdly__test__DOT__memory_rvalid = vlSelfRef.test__DOT__memory_rvalid;
    __Vdly__test__DOT___memory_rdata_fsm = vlSelfRef.test__DOT___memory_rdata_fsm;
    __Vdly__test__DOT__memory_rlast = vlSelfRef.test__DOT__memory_rlast;
    __Vdly__test__DOT__memory_rdata = vlSelfRef.test__DOT__memory_rdata;
    vlSelfRef.__Vdly__test__DOT___saxi_arvalid = vlSelfRef.test__DOT___saxi_arvalid;
    vlSelfRef.__Vdly__test__DOT___saxi_awvalid = vlSelfRef.test__DOT___saxi_awvalid;
    vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 
        = vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0;
    __VdlySet__test__DOT___memory_mem__v0 = 0U;
    __VdlySet__test__DOT___memory_mem__v1 = 0U;
    __VdlySet__test__DOT___memory_mem__v2 = 0U;
    __VdlySet__test__DOT___memory_mem__v3 = 0U;
    vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_valid_40 
        = vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40;
    vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 
        = vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43;
    __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo 
        = vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo;
    __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo 
        = vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_cont 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_req_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7 
        = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10 
        = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_cont 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_req_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25 
        = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_op_sel_buf 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel_buf;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_data_busy 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf;
    __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22 
        = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_start 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail;
    __VdlySet__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0 = 0U;
    vlSelfRef.__Vdly__test__DOT__maxi_awvalid = vlSelfRef.test__DOT__maxi_awvalid;
    __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_wlast_sb_0;
    __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0;
    vlSelfRef.__Vdly__test__DOT__saxi_rvalid = vlSelfRef.test__DOT__saxi_rvalid;
    vlSelfRef.__Vdly__test__DOT__saxi_bvalid = vlSelfRef.test__DOT__saxi_bvalid;
    __Vdly__test__DOT__maxi_arvalid = vlSelfRef.test__DOT__maxi_arvalid;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle;
    __Vdly__test__DOT___sb___05Fsaxi_readdata_valid_53 
        = vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53;
    vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 
        = vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_start 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm;
    __Vdly__test__DOT___th_ctrl___05F_0 = vlSelfRef.test__DOT___th_ctrl___05F_0;
    __Vdly__test__DOT___th_ctrl_start_time_1 = vlSelfRef.test__DOT___th_ctrl_start_time_1;
    __Vdly__test__DOT__axim_rdata_73 = vlSelfRef.test__DOT__axim_rdata_73;
    __Vdly__test__DOT__axim_rdata_74 = vlSelfRef.test__DOT__axim_rdata_74;
    __Vdly__test__DOT___th_ctrl_end_time_2 = vlSelfRef.test__DOT___th_ctrl_end_time_2;
    __Vdly__test__DOT___th_ctrl_ok_3 = vlSelfRef.test__DOT___th_ctrl_ok_3;
    __Vdly__test__DOT___th_ctrl_bat_4 = vlSelfRef.test__DOT___th_ctrl_bat_4;
    __Vdly__test__DOT___th_ctrl_i_5 = vlSelfRef.test__DOT___th_ctrl_i_5;
    __Vdly__test__DOT__rdata_75 = vlSelfRef.test__DOT__rdata_75;
    __Vdly__test__DOT___th_ctrl_orig_6 = vlSelfRef.test__DOT___th_ctrl_orig_6;
    __Vdly__test__DOT__rdata_76 = vlSelfRef.test__DOT__rdata_76;
    __Vdly__test__DOT___th_ctrl_check_7 = vlSelfRef.test__DOT___th_ctrl_check_7;
    vlSelfRef.__Vdly__test__DOT__th_ctrl = vlSelfRef.test__DOT__th_ctrl;
    __VdlySet__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0 = 0U;
    __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0 = 0U;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_stride_505 
        = vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_stride_505;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_length_506 
        = vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_length_506;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508 
        = vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rlast_508;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_addr_504 
        = vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_addr_504;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_fsm_4 
        = vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_fsm_4;
    __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 
        = vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507;
    __VdlySet__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0 = 0U;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3;
    __Vdly__test__DOT__taketwo__DOT___add_tree_1_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_fsm;
    __Vdly__test__DOT__taketwo__DOT___add_tree_1_source_start 
        = vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_start;
    __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm;
    __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start 
        = vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start;
    __Vdly__test__DOT__taketwo__DOT___mul_3_fsm = vlSelfRef.test__DOT__taketwo__DOT___mul_3_fsm;
    __Vdly__test__DOT__taketwo__DOT___mul_3_source_start 
        = vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_start;
    __Vdly__test__DOT__taketwo__DOT___acc_0_fsm = vlSelfRef.test__DOT__taketwo__DOT___acc_0_fsm;
    __Vdly__test__DOT__taketwo__DOT___acc_0_source_start 
        = vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start;
    __Vdly__test__DOT__taketwo__DOT__write_burst_stride_77 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_77;
    __Vdly__test__DOT__taketwo__DOT__write_burst_length_78 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_78;
    __Vdly__test__DOT__taketwo__DOT__write_burst_stride_83 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_83;
    __Vdly__test__DOT__taketwo__DOT__write_burst_length_84 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_84;
    __Vdly__test__DOT__taketwo__DOT__write_burst_addr_76 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_76;
    __Vdly__test__DOT__taketwo__DOT__write_burst_addr_82 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_82;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_92 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_92;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_93 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_93;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_105 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_105;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_106 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_106;
    __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_0 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_0;
    __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_1 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_1;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_91 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_91;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_104 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_104;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_2 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_2;
    __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_3 
        = vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm;
    __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
        = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3;
    __Vdly__test__DOT__taketwo__DOT__internal_state_counter 
        = vlSelfRef.test__DOT__taketwo__DOT__internal_state_counter;
    __Vdly__test__DOT__taketwo__DOT___saxi_register_12 
        = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_12;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT__main_fsm;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 
        = vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_base_offset 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_base_offset;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_row 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_och 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_page 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_laddr_offset 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_laddr_offset;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_out_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_out_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_write_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_write_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_bat_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_bat_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_och_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_row_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_bat_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_bat_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_och_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_och_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_col_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_col_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_ram_select;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_filter 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_filter;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_act 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_act;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_write_out 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_write_out;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_out_write_size 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_row_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_row_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_row_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count;
    __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0 = 0U;
    __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_comp_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_comp_count;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_global_addr 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___maxi_outstanding_wcount 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount;
    __Vdly__test__DOT__taketwo__DOT___maxi_write_start 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_act_local_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_out_local_col 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_col;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_count 
        = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_count;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2;
    vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3 
        = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3;
    __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr 
        = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr;
    __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4;
    __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count;
    __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr 
        = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr;
    __Vtableidx1 = ((((IData)(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount) 
                      << 4U) | ((IData)(vlSelfRef.test__DOT__saxi_bvalid) 
                                << 3U)) | (((IData)(vlSelfRef.test__DOT__saxi_awready) 
                                            << 2U) 
                                           | (((IData)(vlSelfRef.test__DOT___saxi_awvalid) 
                                               << 1U) 
                                              | (1U 
                                                 & (~ (IData)(vlSelfRef.test__DOT__RESETN))))));
    if (Vout__ConstPool__TABLE_h996f76d5_0[__Vtableidx1]) {
        vlSelfRef.__Vdly__test__DOT_____05Fsaxi_outstanding_wcount 
            = Vout__ConstPool__TABLE_h5d4012b8_0[__Vtableidx1];
    }
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_rshift_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_rshift_idle));
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_x_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_x_idle));
    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_var0_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_var0_idle));
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_idle));
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_idle));
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_idle));
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_rshift_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_rshift_idle));
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_y_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_y_idle));
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_x_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__RST) 
           || (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_x_idle));
    if (vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) {
        __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo = 0U;
        __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_read_req_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_read_cont = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_req_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_cont = 0U;
        __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail = 0U;
        __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail = 0U;
    } else {
        if ((((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_enq) 
              & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full))) 
             & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_deq) 
                & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))))) {
            __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo 
                = vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo;
        } else if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_enq) 
                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full)))) {
            __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo)));
        } else if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_deq) 
                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)))) {
            __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo 
                = (0x0000000fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo) 
                                  - (IData)(1U)));
        }
        if ((((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_enq) 
              & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full))) 
             & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_deq) 
                & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty))))) {
            __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo 
                = vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo;
        } else if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_enq) 
                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full)))) {
            __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo)));
        } else if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_deq) 
                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)))) {
            __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo 
                = (0x0000000fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo) 
                                  - (IData)(1U)));
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm)) {
            if ((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
                  & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start) 
                     | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont))) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full)))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_req_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm)) {
            if ((1U & ((IData)(vlSelfRef.test__DOT__memory_arready) 
                       | (~ (IData)(vlSelfRef.test__DOT__maxi_arvalid))))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_cont = 1U;
                __Vdly__test__DOT__taketwo__DOT___maxi_read_req_fsm = 0U;
            }
            if ((((IData)(vlSelfRef.test__DOT__memory_arready) 
                  | (~ (IData)(vlSelfRef.test__DOT__maxi_arvalid))) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_cont = 0U;
            }
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm)) {
            if ((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                 & (2U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U])))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 1U;
            }
            if ((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                 & (4U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U])))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 1U;
            }
            if ((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                 & (6U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U])))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 1U;
            }
            if ((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                 & (8U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U])))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm)) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 2U;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 2U;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 2U;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 2U;
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) 
                 & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 0U;
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 0U;
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 0U;
                __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm = 0U;
            }
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm)) {
            if ((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy)) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty))) 
                 & (2U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U])))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm)) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm = 2U;
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm)) {
            if (((((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel_buf)) 
                   & (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507)) 
                  & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                      | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
                     & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf))) 
                 & (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rlast_508))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm = 0U;
            }
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm)) {
            if ((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                  & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start) 
                     | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont))) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_write_req_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm)) {
            if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                   & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
                  & ((IData)(vlSelfRef.test__DOT__memory_awready) 
                     | (~ (IData)(vlSelfRef.test__DOT__maxi_awvalid)))) 
                 & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_write_cont = 1U;
                __Vdly__test__DOT__taketwo__DOT___maxi_write_req_fsm = 0U;
            }
            if ((((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
                   & ((IData)(vlSelfRef.test__DOT__memory_awready) 
                      | (~ (IData)(vlSelfRef.test__DOT__maxi_awvalid)))) 
                  & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount))) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size))) {
                __Vdly__test__DOT__taketwo__DOT___maxi_write_cont = 0U;
            }
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_deq) 
             & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)))) {
            __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail)));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_deq) 
             & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)))) {
            __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail)));
        }
    }
    if (vlSelfRef.test__DOT__RESETN) {
        __Vdly__test__DOT__time_counter = ((IData)(1U) 
                                           + vlSelfRef.test__DOT__time_counter);
        if ((0x000000000000000fULL == vlSelfRef.test__DOT___sleep_interval_count)) {
            __Vdly__test__DOT___keep_sleep_count = 
                (0x00000001ffffffffULL & (1ULL + vlSelfRef.test__DOT___keep_sleep_count));
        }
        if (((0x000000000000000fULL == vlSelfRef.test__DOT___sleep_interval_count) 
             & (3ULL == vlSelfRef.test__DOT___keep_sleep_count))) {
            __Vdly__test__DOT___keep_sleep_count = 0ULL;
        }
        if ((0x000000000000000fULL > vlSelfRef.test__DOT___sleep_interval_count)) {
            __Vdly__test__DOT___sleep_interval_count 
                = (0x00000001ffffffffULL & (1ULL + vlSelfRef.test__DOT___sleep_interval_count));
        }
        if (((3ULL == vlSelfRef.test__DOT___keep_sleep_count) 
             & (0x000000000000000fULL == vlSelfRef.test__DOT___sleep_interval_count))) {
            __Vdly__test__DOT___sleep_interval_count = 0ULL;
        }
        if ((((IData)(vlSelfRef.test__DOT___memory_wreq_fifo_enq) 
              & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_full))) 
             & ((IData)(vlSelfRef.test__DOT___memory_wreq_fifo_deq) 
                & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_empty))))) {
            __Vdly__test__DOT__count___05Fmemory_wreq_fifo 
                = vlSelfRef.test__DOT__count___05Fmemory_wreq_fifo;
        } else if (((IData)(vlSelfRef.test__DOT___memory_wreq_fifo_enq) 
                    & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_full)))) {
            __Vdly__test__DOT__count___05Fmemory_wreq_fifo 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__count___05Fmemory_wreq_fifo)));
        } else if (((IData)(vlSelfRef.test__DOT___memory_wreq_fifo_deq) 
                    & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_empty)))) {
            __Vdly__test__DOT__count___05Fmemory_wreq_fifo 
                = (0x0000000fU & ((IData)(vlSelfRef.test__DOT__count___05Fmemory_wreq_fifo) 
                                  - (IData)(1U)));
        }
        if ((((IData)(vlSelfRef.test__DOT___memory_rreq_fifo_enq) 
              & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_full))) 
             & ((IData)(vlSelfRef.test__DOT___memory_rreq_fifo_deq) 
                & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_empty))))) {
            __Vdly__test__DOT__count___05Fmemory_rreq_fifo 
                = vlSelfRef.test__DOT__count___05Fmemory_rreq_fifo;
        } else if (((IData)(vlSelfRef.test__DOT___memory_rreq_fifo_enq) 
                    & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_full)))) {
            __Vdly__test__DOT__count___05Fmemory_rreq_fifo 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__count___05Fmemory_rreq_fifo)));
        } else if (((IData)(vlSelfRef.test__DOT___memory_rreq_fifo_deq) 
                    & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_empty)))) {
            __Vdly__test__DOT__count___05Fmemory_rreq_fifo 
                = (0x0000000fU & ((IData)(vlSelfRef.test__DOT__count___05Fmemory_rreq_fifo) 
                                  - (IData)(1U)));
        }
        if ((((IData)(vlSelfRef.test__DOT___memory_wdata_fifo_enq) 
              & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_full))) 
             & ((IData)(vlSelfRef.test__DOT___memory_wdata_fifo_deq) 
                & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty))))) {
            __Vdly__test__DOT__count___05Fmemory_wdata_fifo 
                = vlSelfRef.test__DOT__count___05Fmemory_wdata_fifo;
        } else if (((IData)(vlSelfRef.test__DOT___memory_wdata_fifo_enq) 
                    & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_full)))) {
            __Vdly__test__DOT__count___05Fmemory_wdata_fifo 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__count___05Fmemory_wdata_fifo)));
        } else if (((IData)(vlSelfRef.test__DOT___memory_wdata_fifo_deq) 
                    & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)))) {
            __Vdly__test__DOT__count___05Fmemory_wdata_fifo 
                = (0x0000000fU & ((IData)(vlSelfRef.test__DOT__count___05Fmemory_wdata_fifo) 
                                  - (IData)(1U)));
        }
        if ((0U == vlSelfRef.test__DOT___memory_raddr_fsm)) {
            __Vdly__test__DOT__memory_arready = 0U;
            if (vlSelfRef.test__DOT__maxi_arvalid) {
                __Vdly__test__DOT___memory_raddr_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT___memory_raddr_fsm)) {
            if ((1U & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_almost_full)))) {
                __Vdly__test__DOT__memory_arready = 1U;
            }
            if ((1U & (~ (IData)(vlSelfRef.test__DOT__maxi_arvalid)))) {
                __Vdly__test__DOT___memory_raddr_fsm = 0U;
            }
            if (((IData)(vlSelfRef.test__DOT__maxi_arvalid) 
                 & (IData)(vlSelfRef.test__DOT__memory_arready))) {
                __Vdly__test__DOT__memory_arready = 0U;
                __Vdly__test__DOT___memory_raddr_fsm = 0U;
            }
        }
        if (((IData)(vlSelfRef.test__DOT___memory_wreq_fifo_deq) 
             & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_empty)))) {
            vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail)));
        }
        if (((IData)(vlSelfRef.test__DOT___memory_rreq_fifo_deq) 
             & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_empty)))) {
            vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail)));
        }
        if (((((((((0U == vlSelfRef.test__DOT___memory_waddr_fsm) 
                   | (1U == vlSelfRef.test__DOT___memory_waddr_fsm)) 
                  | (2U == vlSelfRef.test__DOT___memory_waddr_fsm)) 
                 | (3U == vlSelfRef.test__DOT___memory_waddr_fsm)) 
                | (4U == vlSelfRef.test__DOT___memory_waddr_fsm)) 
               | (5U == vlSelfRef.test__DOT___memory_waddr_fsm)) 
              | (6U == vlSelfRef.test__DOT___memory_waddr_fsm)) 
             | (7U == vlSelfRef.test__DOT___memory_waddr_fsm))) {
            if ((0U == vlSelfRef.test__DOT___memory_waddr_fsm)) {
                __Vdly__test__DOT__memory_awready = 0U;
                if (vlSelfRef.test__DOT__maxi_awvalid) {
                    __Vdly__test__DOT___memory_waddr_fsm = 1U;
                }
            } else {
                __Vdly__test__DOT___memory_waddr_fsm 
                    = ((1U == vlSelfRef.test__DOT___memory_waddr_fsm)
                        ? 2U : ((2U == vlSelfRef.test__DOT___memory_waddr_fsm)
                                 ? 3U : ((3U == vlSelfRef.test__DOT___memory_waddr_fsm)
                                          ? 4U : ((4U 
                                                   == vlSelfRef.test__DOT___memory_waddr_fsm)
                                                   ? 5U
                                                   : 
                                                  ((5U 
                                                    == vlSelfRef.test__DOT___memory_waddr_fsm)
                                                    ? 6U
                                                    : 
                                                   ((6U 
                                                     == vlSelfRef.test__DOT___memory_waddr_fsm)
                                                     ? 7U
                                                     : 8U))))));
            }
        } else if ((8U == vlSelfRef.test__DOT___memory_waddr_fsm)) {
            __Vdly__test__DOT___memory_waddr_fsm = 9U;
        } else if ((9U == vlSelfRef.test__DOT___memory_waddr_fsm)) {
            __Vdly__test__DOT___memory_waddr_fsm = 0x0000000aU;
        } else if ((0x0000000aU == vlSelfRef.test__DOT___memory_waddr_fsm)) {
            __Vdly__test__DOT___memory_waddr_fsm = 0x0000000bU;
        } else if ((0x0000000bU == vlSelfRef.test__DOT___memory_waddr_fsm)) {
            if ((1U & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_almost_full)))) {
                __Vdly__test__DOT__memory_awready = 1U;
            }
            if ((1U & (~ (IData)(vlSelfRef.test__DOT__maxi_awvalid)))) {
                __Vdly__test__DOT___memory_waddr_fsm = 0U;
            }
            if (((IData)(vlSelfRef.test__DOT__maxi_awvalid) 
                 & (IData)(vlSelfRef.test__DOT__memory_awready))) {
                __Vdly__test__DOT__memory_awready = 0U;
                __Vdly__test__DOT___memory_waddr_fsm = 0U;
            }
        }
        if (((IData)(vlSelfRef.test__DOT___memory_wdata_fifo_deq) 
             & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)))) {
            vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail)));
        }
        __Vdly__test__DOT___d1___05Fmemory_rdata_fsm 
            = vlSelfRef.test__DOT___memory_rdata_fsm;
        if ((0x0000000bU == vlSelfRef.test__DOT___d1___05Fmemory_rdata_fsm)) {
            if (vlSelfRef.test__DOT_____05Fmemory_rdata_fsm_cond_11_0_1) {
                __Vdly__test__DOT__memory_rvalid = 0U;
                __Vdly__test__DOT__memory_rlast = 0U;
            }
        }
        if (((((((((0U == vlSelfRef.test__DOT___memory_rdata_fsm) 
                   | (1U == vlSelfRef.test__DOT___memory_rdata_fsm)) 
                  | (2U == vlSelfRef.test__DOT___memory_rdata_fsm)) 
                 | (3U == vlSelfRef.test__DOT___memory_rdata_fsm)) 
                | (4U == vlSelfRef.test__DOT___memory_rdata_fsm)) 
               | (5U == vlSelfRef.test__DOT___memory_rdata_fsm)) 
              | (6U == vlSelfRef.test__DOT___memory_rdata_fsm)) 
             | (7U == vlSelfRef.test__DOT___memory_rdata_fsm))) {
            if ((0U == vlSelfRef.test__DOT___memory_rdata_fsm)) {
                if ((1U & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_empty)))) {
                    __Vdly__test__DOT___read_addr = (IData)(
                                                            (vlSelfRef.test__DOT___memory_rreq_fifo_rdata 
                                                             >> 9U));
                    __Vdly__test__DOT___read_count 
                        = (QData)((IData)((0x000001ffU 
                                           & (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_rdata))));
                    __Vdly__test__DOT___memory_rdata_fsm = 1U;
                }
            } else {
                __Vdly__test__DOT___memory_rdata_fsm 
                    = ((1U == vlSelfRef.test__DOT___memory_rdata_fsm)
                        ? 2U : ((2U == vlSelfRef.test__DOT___memory_rdata_fsm)
                                 ? 3U : ((3U == vlSelfRef.test__DOT___memory_rdata_fsm)
                                          ? 4U : ((4U 
                                                   == vlSelfRef.test__DOT___memory_rdata_fsm)
                                                   ? 5U
                                                   : 
                                                  ((5U 
                                                    == vlSelfRef.test__DOT___memory_rdata_fsm)
                                                    ? 6U
                                                    : 
                                                   ((6U 
                                                     == vlSelfRef.test__DOT___memory_rdata_fsm)
                                                     ? 7U
                                                     : 8U))))));
            }
        } else if ((8U == vlSelfRef.test__DOT___memory_rdata_fsm)) {
            __Vdly__test__DOT___memory_rdata_fsm = 9U;
        } else if ((9U == vlSelfRef.test__DOT___memory_rdata_fsm)) {
            __Vdly__test__DOT___memory_rdata_fsm = 0x0000000aU;
        } else if ((0x0000000aU == vlSelfRef.test__DOT___memory_rdata_fsm)) {
            __Vdly__test__DOT___memory_rdata_fsm = 0x0000000bU;
        } else if ((0x0000000bU == vlSelfRef.test__DOT___memory_rdata_fsm)) {
            if ((1U & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)) 
                       | (~ (IData)(vlSelfRef.test__DOT__memory_rvalid))))) {
                __Vdly__test__DOT__memory_rdata = (
                                                   (0xffffff00U 
                                                    & __Vdly__test__DOT__memory_rdata) 
                                                   | vlSelfRef.test__DOT___memory_mem
                                                   [
                                                   (0x000fffffU 
                                                    & vlSelfRef.test__DOT___read_addr)]);
                __Vdly__test__DOT__memory_rdata = (
                                                   (0xffff00ffU 
                                                    & __Vdly__test__DOT__memory_rdata) 
                                                   | (vlSelfRef.test__DOT___memory_mem
                                                      [
                                                      (0x000fffffU 
                                                       & ((IData)(1U) 
                                                          + vlSelfRef.test__DOT___read_addr))] 
                                                      << 8U));
                __Vdly__test__DOT__memory_rdata = (
                                                   (0xff00ffffU 
                                                    & __Vdly__test__DOT__memory_rdata) 
                                                   | (vlSelfRef.test__DOT___memory_mem
                                                      [
                                                      (0x000fffffU 
                                                       & ((IData)(2U) 
                                                          + vlSelfRef.test__DOT___read_addr))] 
                                                      << 0x00000010U));
                __Vdly__test__DOT__memory_rdata = (
                                                   (0x00ffffffU 
                                                    & __Vdly__test__DOT__memory_rdata) 
                                                   | (vlSelfRef.test__DOT___memory_mem
                                                      [
                                                      (0x000fffffU 
                                                       & ((IData)(3U) 
                                                          + vlSelfRef.test__DOT___read_addr))] 
                                                      << 0x00000018U));
            }
            vlSelfRef.test__DOT_____05Fmemory_rdata_fsm_cond_11_0_1 = 1U;
            if ((((0x000000000000000fULL > vlSelfRef.test__DOT___sleep_interval_count) 
                  & (0ULL < vlSelfRef.test__DOT___read_count)) 
                 & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)) 
                    | (~ (IData)(vlSelfRef.test__DOT__memory_rvalid))))) {
                __Vdly__test__DOT___read_addr = ((IData)(4U) 
                                                 + vlSelfRef.test__DOT___read_addr);
                __Vdly__test__DOT___read_count = (0x00000001ffffffffULL 
                                                  & (vlSelfRef.test__DOT___read_count 
                                                     - 1ULL));
                __Vdly__test__DOT__memory_rvalid = 1U;
            }
            if ((((0x000000000000000fULL > vlSelfRef.test__DOT___sleep_interval_count) 
                  & (1ULL == vlSelfRef.test__DOT___read_count)) 
                 & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)) 
                    | (~ (IData)(vlSelfRef.test__DOT__memory_rvalid))))) {
                __Vdly__test__DOT__memory_rlast = 1U;
            }
            if (((IData)(vlSelfRef.test__DOT__memory_rvalid) 
                 & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25))) {
                __Vdly__test__DOT__memory_rvalid = vlSelfRef.test__DOT__memory_rvalid;
                __Vdly__test__DOT__memory_rdata = vlSelfRef.test__DOT__memory_rdata;
                __Vdly__test__DOT__memory_rlast = vlSelfRef.test__DOT__memory_rlast;
            }
            if ((((IData)(vlSelfRef.test__DOT__memory_rvalid) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25))) 
                 & (0ULL == vlSelfRef.test__DOT___read_count))) {
                __Vdly__test__DOT___memory_rdata_fsm = 0U;
            }
        }
        if (((((1U == vlSelfRef.test__DOT___memory_wdata_fsm) 
               & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty))) 
              & (IData)(vlSelfRef.test__DOT__write_data_wready_17)) 
             & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                        >> 0x00000020U)))) {
            __VdlyVal__test__DOT___memory_mem__v0 = 
                (0x000000ffU & (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_rdata));
            __VdlyDim0__test__DOT___memory_mem__v0 
                = (0x000fffffU & vlSelfRef.test__DOT___write_addr);
            __VdlySet__test__DOT___memory_mem__v0 = 1U;
        }
        if (((((1U == vlSelfRef.test__DOT___memory_wdata_fsm) 
               & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty))) 
              & (IData)(vlSelfRef.test__DOT__write_data_wready_17)) 
             & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                        >> 0x00000021U)))) {
            __VdlyVal__test__DOT___memory_mem__v1 = 
                (0x000000ffU & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                                        >> 8U)));
            __VdlyDim0__test__DOT___memory_mem__v1 
                = (0x000fffffU & ((IData)(1U) + vlSelfRef.test__DOT___write_addr));
            __VdlySet__test__DOT___memory_mem__v1 = 1U;
        }
        if (((((1U == vlSelfRef.test__DOT___memory_wdata_fsm) 
               & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty))) 
              & (IData)(vlSelfRef.test__DOT__write_data_wready_17)) 
             & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                        >> 0x00000022U)))) {
            __VdlyVal__test__DOT___memory_mem__v2 = 
                (0x000000ffU & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                                        >> 0x00000010U)));
            __VdlyDim0__test__DOT___memory_mem__v2 
                = (0x000fffffU & ((IData)(2U) + vlSelfRef.test__DOT___write_addr));
            __VdlySet__test__DOT___memory_mem__v2 = 1U;
        }
        if (((((1U == vlSelfRef.test__DOT___memory_wdata_fsm) 
               & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty))) 
              & (IData)(vlSelfRef.test__DOT__write_data_wready_17)) 
             & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                        >> 0x00000023U)))) {
            __VdlyVal__test__DOT___memory_mem__v3 = 
                (0x000000ffU & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                                        >> 0x00000018U)));
            __VdlyDim0__test__DOT___memory_mem__v3 
                = (0x000fffffU & ((IData)(3U) + vlSelfRef.test__DOT___write_addr));
            __VdlySet__test__DOT___memory_mem__v3 = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT___memory_wdata_fifo_enq) 
             & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_full)))) {
            __VdlyVal__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0 
                = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_0)
                    ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6
                    : 0ULL);
            __VdlyDim0__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0 
                = vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head;
            __VdlySet__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0 = 1U;
            vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head)));
        }
    } else {
        __Vdly__test__DOT__time_counter = 0U;
        __Vdly__test__DOT___keep_sleep_count = 0ULL;
        __Vdly__test__DOT___sleep_interval_count = 0ULL;
        __Vdly__test__DOT__count___05Fmemory_wreq_fifo = 0U;
        __Vdly__test__DOT__count___05Fmemory_rreq_fifo = 0U;
        __Vdly__test__DOT__count___05Fmemory_wdata_fifo = 0U;
        __Vdly__test__DOT__memory_arready = 0U;
        __Vdly__test__DOT___memory_raddr_fsm = 0U;
        vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail = 0U;
        vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail = 0U;
        __Vdly__test__DOT__memory_awready = 0U;
        __Vdly__test__DOT___memory_waddr_fsm = 0U;
        vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail = 0U;
        __Vdly__test__DOT__memory_rdata = 0U;
        __Vdly__test__DOT__memory_rvalid = 0U;
        __Vdly__test__DOT__memory_rlast = 0U;
        __Vdly__test__DOT___memory_rdata_fsm = 0U;
        __Vdly__test__DOT___d1___05Fmemory_rdata_fsm = 0U;
        __Vdly__test__DOT___read_addr = 0U;
        __Vdly__test__DOT___read_count = 0ULL;
        vlSelfRef.test__DOT_____05Fmemory_rdata_fsm_cond_11_0_1 = 0U;
        __Vdly__test__DOT__memory_rdata = 0U;
        vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head = 0U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable) {
        vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wdata;
        vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_addr;
        vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0 = 1U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable) {
        vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata;
        vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr;
        vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0 = 1U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable) {
        vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wdata;
        vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr;
        vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0 = 1U;
        vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_1_1_wdata;
        vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr;
        vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0 = 1U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable) {
        vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wdata;
        vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr;
        vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0 = 1U;
        vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_1_1_wdata;
        vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr;
        vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0 = 1U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable) {
        __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wdata;
        __VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_addr;
        __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0 = 1U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable) {
        __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wdata;
        __VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0 
            = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_addr;
        __VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0 = 1U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle = 1U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle = 1U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle = 1U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle = 1U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle = 1U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle = 1U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle = 1U;
    } else {
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle = 0U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle = 1U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle = 1U;
        }
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle = 0U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle = 1U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle = 1U;
        }
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle = 0U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle = 1U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle = 1U;
        }
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle = 0U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle = 1U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle = 1U;
        }
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle;
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle = 1U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle = 1U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle = 1U;
        }
    }
    if (vlSelfRef.test__DOT__RESETN) {
        if (((((((((0U == vlSelfRef.test__DOT__th_ctrl) 
                   | (1U == vlSelfRef.test__DOT__th_ctrl)) 
                  | (2U == vlSelfRef.test__DOT__th_ctrl)) 
                 | (3U == vlSelfRef.test__DOT__th_ctrl)) 
                | (4U == vlSelfRef.test__DOT__th_ctrl)) 
               | (5U == vlSelfRef.test__DOT__th_ctrl)) 
              | (6U == vlSelfRef.test__DOT__th_ctrl)) 
             | (7U == vlSelfRef.test__DOT__th_ctrl))) {
            if ((0U == vlSelfRef.test__DOT__th_ctrl)) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 1U;
            } else if ((1U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl___05F_0 = 0U;
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 2U;
            } else if ((2U == vlSelfRef.test__DOT__th_ctrl)) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl 
                    = (VL_GTS_III(32, 0x00000064U, vlSelfRef.test__DOT___th_ctrl___05F_0)
                        ? 3U : 4U);
            } else if ((3U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl___05F_0 
                    = ((IData)(1U) + vlSelfRef.test__DOT___th_ctrl___05F_0);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 2U;
            } else if ((4U == vlSelfRef.test__DOT__th_ctrl)) {
                if (((0U == (IData)(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount)) 
                     & ((IData)(vlSelfRef.test__DOT__saxi_awready) 
                        | (~ (IData)(vlSelfRef.test__DOT___saxi_awvalid))))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 5U;
                }
            } else if ((5U == vlSelfRef.test__DOT__th_ctrl)) {
                if (((IData)(vlSelfRef.test__DOT___saxi_awvalid) 
                     & (IData)(vlSelfRef.test__DOT__saxi_awready))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 6U;
                }
            } else if ((6U == vlSelfRef.test__DOT__th_ctrl)) {
                if ((1U & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)) 
                           | (~ (IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0))))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 7U;
                }
            } else if (((IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0) 
                        & (~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)))) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 8U;
            }
        } else if (((((((((8U == vlSelfRef.test__DOT__th_ctrl) 
                          | (9U == vlSelfRef.test__DOT__th_ctrl)) 
                         | (0x0000000aU == vlSelfRef.test__DOT__th_ctrl)) 
                        | (0x0000000bU == vlSelfRef.test__DOT__th_ctrl)) 
                       | (0x0000000cU == vlSelfRef.test__DOT__th_ctrl)) 
                      | (0x0000000dU == vlSelfRef.test__DOT__th_ctrl)) 
                     | (0x0000000eU == vlSelfRef.test__DOT__th_ctrl)) 
                    | (0x0000000fU == vlSelfRef.test__DOT__th_ctrl))) {
            if ((8U == vlSelfRef.test__DOT__th_ctrl)) {
                if ((1U & (~ (IData)(vlSelfRef.test__DOT_____05Fsaxi_has_outstanding_write)))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 9U;
                }
            } else if ((9U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_start_time_1 
                    = vlSelfRef.test__DOT__time_counter;
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000000aU;
            } else if ((0x0000000aU == vlSelfRef.test__DOT__th_ctrl)) {
                if (((0U == (IData)(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount)) 
                     & ((IData)(vlSelfRef.test__DOT__saxi_awready) 
                        | (~ (IData)(vlSelfRef.test__DOT___saxi_awvalid))))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000000bU;
                }
            } else if ((0x0000000bU == vlSelfRef.test__DOT__th_ctrl)) {
                if (((IData)(vlSelfRef.test__DOT___saxi_awvalid) 
                     & (IData)(vlSelfRef.test__DOT__saxi_awready))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000000cU;
                }
            } else if ((0x0000000cU == vlSelfRef.test__DOT__th_ctrl)) {
                if ((1U & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)) 
                           | (~ (IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0))))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000000dU;
                }
            } else if ((0x0000000dU == vlSelfRef.test__DOT__th_ctrl)) {
                if (((IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0) 
                     & (~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000000eU;
                }
            } else if ((0x0000000eU == vlSelfRef.test__DOT__th_ctrl)) {
                if ((1U & (~ (IData)(vlSelfRef.test__DOT_____05Fsaxi_has_outstanding_write)))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000000fU;
                }
            } else if ((1U & ((IData)(vlSelfRef.test__DOT__saxi_arready) 
                              | (~ (IData)(vlSelfRef.test__DOT___saxi_arvalid))))) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000010U;
            }
        } else if (((((((((0x00000010U == vlSelfRef.test__DOT__th_ctrl) 
                          | (0x00000011U == vlSelfRef.test__DOT__th_ctrl)) 
                         | (0x00000012U == vlSelfRef.test__DOT__th_ctrl)) 
                        | (0x00000013U == vlSelfRef.test__DOT__th_ctrl)) 
                       | (0x00000014U == vlSelfRef.test__DOT__th_ctrl)) 
                      | (0x00000015U == vlSelfRef.test__DOT__th_ctrl)) 
                     | (0x00000016U == vlSelfRef.test__DOT__th_ctrl)) 
                    | (0x00000017U == vlSelfRef.test__DOT__th_ctrl))) {
            if ((0x00000010U == vlSelfRef.test__DOT__th_ctrl)) {
                if (((IData)(vlSelfRef.test__DOT___saxi_arvalid) 
                     & (IData)(vlSelfRef.test__DOT__saxi_arready))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000011U;
                }
            } else if ((0x00000011U == vlSelfRef.test__DOT__th_ctrl)) {
                if (vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53) {
                    __Vdly__test__DOT__axim_rdata_73 
                        = vlSelfRef.test__DOT___sb___05Fsaxi_readdata_data_52;
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000012U;
                }
            } else if ((0x00000012U == vlSelfRef.test__DOT__th_ctrl)) {
                if ((0U != vlSelfRef.test__DOT__axim_rdata_73)) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000000fU;
                }
                if ((0U == vlSelfRef.test__DOT__axim_rdata_73)) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000013U;
                }
            } else if (VL_UNLIKELY(((0x00000013U == vlSelfRef.test__DOT__th_ctrl)))) {
                VL_WRITEF_NX("# start\n",0);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000014U;
            } else if ((0x00000014U == vlSelfRef.test__DOT__th_ctrl)) {
                if ((1U & ((IData)(vlSelfRef.test__DOT__saxi_arready) 
                           | (~ (IData)(vlSelfRef.test__DOT___saxi_arvalid))))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000015U;
                }
            } else if ((0x00000015U == vlSelfRef.test__DOT__th_ctrl)) {
                if (((IData)(vlSelfRef.test__DOT___saxi_arvalid) 
                     & (IData)(vlSelfRef.test__DOT__saxi_arready))) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000016U;
                }
            } else if ((0x00000016U == vlSelfRef.test__DOT__th_ctrl)) {
                if (vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53) {
                    __Vdly__test__DOT__axim_rdata_74 
                        = vlSelfRef.test__DOT___sb___05Fsaxi_readdata_data_52;
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000017U;
                }
            } else {
                if ((0U != vlSelfRef.test__DOT__axim_rdata_74)) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000014U;
                }
                if ((0U == vlSelfRef.test__DOT__axim_rdata_74)) {
                    vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000018U;
                }
            }
        } else if (((((((((0x00000018U == vlSelfRef.test__DOT__th_ctrl) 
                          | (0x00000019U == vlSelfRef.test__DOT__th_ctrl)) 
                         | (0x0000001aU == vlSelfRef.test__DOT__th_ctrl)) 
                        | (0x0000001bU == vlSelfRef.test__DOT__th_ctrl)) 
                       | (0x0000001cU == vlSelfRef.test__DOT__th_ctrl)) 
                      | (0x0000001dU == vlSelfRef.test__DOT__th_ctrl)) 
                     | (0x0000001eU == vlSelfRef.test__DOT__th_ctrl)) 
                    | (0x0000001fU == vlSelfRef.test__DOT__th_ctrl))) {
            if ((0x00000018U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_end_time_2 
                    = vlSelfRef.test__DOT__time_counter;
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000019U;
            } else if (VL_UNLIKELY(((0x00000019U == vlSelfRef.test__DOT__th_ctrl)))) {
                VL_WRITEF_NX("# end\n",0);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000001aU;
            } else if (VL_UNLIKELY(((0x0000001aU == vlSelfRef.test__DOT__th_ctrl)))) {
                VL_WRITEF_NX("# execution cycles: %11d\n",0,
                             32,(vlSelfRef.test__DOT___th_ctrl_end_time_2 
                                 - vlSelfRef.test__DOT___th_ctrl_start_time_1));
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000001bU;
            } else if ((0x0000001bU == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_ok_3 = 1U;
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000001cU;
            } else if ((0x0000001cU == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_bat_4 = 0U;
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000001dU;
            } else if ((0x0000001dU == vlSelfRef.test__DOT__th_ctrl)) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl 
                    = (VL_GTS_III(32, 1U, vlSelfRef.test__DOT___th_ctrl_bat_4)
                        ? 0x0000001eU : 0x0000002bU);
            } else if ((0x0000001eU == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_i_5 = 0U;
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000001fU;
            } else {
                vlSelfRef.__Vdly__test__DOT__th_ctrl 
                    = (VL_GTS_III(32, 2U, vlSelfRef.test__DOT___th_ctrl_i_5)
                        ? 0x00000020U : 0x0000002aU);
            }
        } else if (((((((((0x00000020U == vlSelfRef.test__DOT__th_ctrl) 
                          | (0x00000021U == vlSelfRef.test__DOT__th_ctrl)) 
                         | (0x00000022U == vlSelfRef.test__DOT__th_ctrl)) 
                        | (0x00000023U == vlSelfRef.test__DOT__th_ctrl)) 
                       | (0x00000024U == vlSelfRef.test__DOT__th_ctrl)) 
                      | (0x00000025U == vlSelfRef.test__DOT__th_ctrl)) 
                     | (0x00000026U == vlSelfRef.test__DOT__th_ctrl)) 
                    | (0x00000027U == vlSelfRef.test__DOT__th_ctrl))) {
            if ((0x00000020U == vlSelfRef.test__DOT__th_ctrl)) {
                if ((0x00000020U == vlSelfRef.test__DOT__th_ctrl)) {
                    __Vdly__test__DOT__rdata_75 = (0x0000ffffU 
                                                   & VL_SHIFTR_III(16,16,32, 
                                                                   ((vlSelfRef.test__DOT___memory_mem
                                                                     [
                                                                     (0x000fffffU 
                                                                      & ((IData)(1U) 
                                                                         + 
                                                                         VL_DIVS_III(32, 
                                                                                VL_MULS_III(32, (IData)(0x00000010U), 
                                                                                (VL_SHIFTL_III(32,32,32, vlSelfRef.test__DOT___th_ctrl_bat_4, 1U) 
                                                                                + vlSelfRef.test__DOT___th_ctrl_i_5)), (IData)(8U))))] 
                                                                     << 8U) 
                                                                    | vlSelfRef.test__DOT___memory_mem
                                                                    [
                                                                    (0x000fffffU 
                                                                     & VL_DIVS_III(32, 
                                                                                VL_MULS_III(32, (IData)(0x00000010U), 
                                                                                (VL_SHIFTL_III(32,32,32, vlSelfRef.test__DOT___th_ctrl_bat_4, 1U) 
                                                                                + vlSelfRef.test__DOT___th_ctrl_i_5)), (IData)(8U)))]), 
                                                                   VL_MODDIVS_III(32, 
                                                                                VL_MULS_III(32, (IData)(0x00000010U), 
                                                                                (VL_SHIFTL_III(32,32,32, vlSelfRef.test__DOT___th_ctrl_bat_4, 1U) 
                                                                                + vlSelfRef.test__DOT___th_ctrl_i_5)), (IData)(8U))));
                }
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000021U;
            } else if ((0x00000021U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_orig_6 
                    = VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__rdata_75));
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000022U;
            } else if ((0x00000022U == vlSelfRef.test__DOT__th_ctrl)) {
                if ((0x00000022U == vlSelfRef.test__DOT__th_ctrl)) {
                    __Vdly__test__DOT__rdata_76 = (0x0000ffffU 
                                                   & VL_SHIFTR_III(16,16,32, 
                                                                   ((vlSelfRef.test__DOT___memory_mem
                                                                     [
                                                                     (0x000fffffU 
                                                                      & ((IData)(0x00001581U) 
                                                                         + 
                                                                         VL_DIVS_III(32, 
                                                                                VL_MULS_III(32, (IData)(0x00000010U), 
                                                                                (VL_SHIFTL_III(32,32,32, vlSelfRef.test__DOT___th_ctrl_bat_4, 1U) 
                                                                                + vlSelfRef.test__DOT___th_ctrl_i_5)), (IData)(8U))))] 
                                                                     << 8U) 
                                                                    | vlSelfRef.test__DOT___memory_mem
                                                                    [
                                                                    (0x000fffffU 
                                                                     & ((IData)(0x00001580U) 
                                                                        + 
                                                                        VL_DIVS_III(32, 
                                                                                VL_MULS_III(32, (IData)(0x00000010U), 
                                                                                (VL_SHIFTL_III(32,32,32, vlSelfRef.test__DOT___th_ctrl_bat_4, 1U) 
                                                                                + vlSelfRef.test__DOT___th_ctrl_i_5)), (IData)(8U))))]), 
                                                                   VL_MODDIVS_III(32, 
                                                                                VL_MULS_III(32, (IData)(0x00000010U), 
                                                                                (VL_SHIFTL_III(32,32,32, vlSelfRef.test__DOT___th_ctrl_bat_4, 1U) 
                                                                                + vlSelfRef.test__DOT___th_ctrl_i_5)), (IData)(8U))));
                }
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000023U;
            } else if ((0x00000023U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_check_7 
                    = VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__rdata_76));
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000024U;
            } else if ((0x00000024U == vlSelfRef.test__DOT__th_ctrl)) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl 
                    = ((vlSelfRef.test__DOT___th_ctrl_orig_6 
                        != vlSelfRef.test__DOT___th_ctrl_check_7)
                        ? 0x00000025U : 0x00000028U);
            } else if (VL_UNLIKELY(((0x00000025U == vlSelfRef.test__DOT__th_ctrl)))) {
                VL_WRITEF_NX("NG ( %11d %11d ) orig: %11d check: %11d\n",0,
                             32,vlSelfRef.test__DOT___th_ctrl_bat_4,
                             32,vlSelfRef.test__DOT___th_ctrl_i_5,
                             32,vlSelfRef.test__DOT___th_ctrl_orig_6,
                             32,vlSelfRef.test__DOT___th_ctrl_check_7);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000026U;
            } else if ((0x00000026U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_ok_3 = 0U;
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000027U;
            } else {
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000029U;
            }
        } else if (((((((((0x00000028U == vlSelfRef.test__DOT__th_ctrl) 
                          | (0x00000029U == vlSelfRef.test__DOT__th_ctrl)) 
                         | (0x0000002aU == vlSelfRef.test__DOT__th_ctrl)) 
                        | (0x0000002bU == vlSelfRef.test__DOT__th_ctrl)) 
                       | (0x0000002cU == vlSelfRef.test__DOT__th_ctrl)) 
                      | (0x0000002dU == vlSelfRef.test__DOT__th_ctrl)) 
                     | (0x0000002eU == vlSelfRef.test__DOT__th_ctrl)) 
                    | (0x0000002fU == vlSelfRef.test__DOT__th_ctrl))) {
            if (VL_UNLIKELY(((0x00000028U == vlSelfRef.test__DOT__th_ctrl)))) {
                VL_WRITEF_NX("OK ( %11d %11d ) orig: %11d check: %11d\n",0,
                             32,vlSelfRef.test__DOT___th_ctrl_bat_4,
                             32,vlSelfRef.test__DOT___th_ctrl_i_5,
                             32,vlSelfRef.test__DOT___th_ctrl_orig_6,
                             32,vlSelfRef.test__DOT___th_ctrl_check_7);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000029U;
            } else if ((0x00000029U == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_i_5 = ((IData)(1U) 
                                                   + vlSelfRef.test__DOT___th_ctrl_i_5);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000001fU;
            } else if ((0x0000002aU == vlSelfRef.test__DOT__th_ctrl)) {
                __Vdly__test__DOT___th_ctrl_bat_4 = 
                    ((IData)(1U) + vlSelfRef.test__DOT___th_ctrl_bat_4);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000001dU;
            } else if ((0x0000002bU == vlSelfRef.test__DOT__th_ctrl)) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl 
                    = ((0U != vlSelfRef.test__DOT___th_ctrl_ok_3)
                        ? 0x0000002cU : 0x0000002eU);
            } else if (VL_UNLIKELY(((0x0000002cU == vlSelfRef.test__DOT__th_ctrl)))) {
                VL_WRITEF_NX("# verify: PASSED\n",0);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000002dU;
            } else if ((0x0000002dU == vlSelfRef.test__DOT__th_ctrl)) {
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000002fU;
            } else if ((0x0000002eU == vlSelfRef.test__DOT__th_ctrl)) {
                VL_WRITEF_NX("# verify: FAILED\n",0);
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x0000002fU;
            } else {
                VL_FINISH_MT("/home/jfriday/sensorsoc/ML/nngen_out/taketwo.out/out.v", 1534, "");
                vlSelfRef.__Vdly__test__DOT__th_ctrl = 0x00000030U;
            }
        }
    } else {
        vlSelfRef.__Vdly__test__DOT__th_ctrl = 0U;
        __Vdly__test__DOT___th_ctrl___05F_0 = 0U;
        __Vdly__test__DOT___th_ctrl_start_time_1 = 0U;
        __Vdly__test__DOT__axim_rdata_73 = 0U;
        __Vdly__test__DOT__axim_rdata_74 = 0U;
        __Vdly__test__DOT___th_ctrl_end_time_2 = 0U;
        __Vdly__test__DOT___th_ctrl_ok_3 = 0U;
        __Vdly__test__DOT___th_ctrl_bat_4 = 0U;
        __Vdly__test__DOT___th_ctrl_i_5 = 0U;
        __Vdly__test__DOT__rdata_75 = 0U;
        __Vdly__test__DOT___th_ctrl_orig_6 = 0U;
        __Vdly__test__DOT__rdata_76 = 0U;
        __Vdly__test__DOT___th_ctrl_check_7 = 0U;
    }
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_valid_sink_wenable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_sum_sink_fifo_enq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_sum_sink_wenable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_valid_sink_fifo_enq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_rshift_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_rshift_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_x_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_x_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_sum_sink_fifo_enq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_sum_sink_wenable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_var0_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_var0_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_fifo_enq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_wenable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_z_sink_fifo_enq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_z_sink_wenable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_rshift_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_rshift_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_y_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_y_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_x_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_x_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_ram_renable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_fifo_deq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fifo_enq = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_wenable = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_fifo_enq = 0U;
    vlSelfRef.test__DOT_____05Ftmp_10_1 = ((IData)(vlSelfRef.test__DOT__RESETN) 
                                           && (1U & 
                                               (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_almost_full))));
    vlSelfRef.test__DOT_____05Ftmp_22_1 = ((IData)(vlSelfRef.test__DOT__RESETN) 
                                           && (1U & 
                                               (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_almost_full))));
    vlSelfRef.test__DOT_____05Ftmp_5_1 = ((IData)(vlSelfRef.test__DOT__RESETN) 
                                          && (1U & 
                                              (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full))));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_63_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
           && (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full))));
    vlSelfRef.test__DOT__taketwo__DOT__prev_arvalid_44 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
           && (IData)(vlSelfRef.test__DOT___saxi_arvalid));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_483_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
           && (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_503_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
           && (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))));
    vlSelfRef.test__DOT__taketwo__DOT__prev_awvalid_43 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
           && (IData)(vlSelfRef.test__DOT___saxi_awvalid));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_124_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_120_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_139_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_141_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_148_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_150_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_291 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_290));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_511_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable));
    vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_515_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_289 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_288));
    vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_50 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
           && (1U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5));
    vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_52 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
           && (0U != vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_318 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_317));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_311 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_310));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_349 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_348));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_273 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_272));
    vlSelfRef.test__DOT__irq = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2))) 
                                && (0U != (vlSelfRef.test__DOT__taketwo__DOT___saxi_register_10 
                                           & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9)));
    if (vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) {
        __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head = 0U;
        __Vdly__test__DOT__taketwo__DOT___saxi_register_12 = 0U;
        __Vdly__test__DOT__taketwo__DOT__internal_state_counter = 0U;
        __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_data_24 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_sb_0 = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0 = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_wstrb_sb_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_10 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_36 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_35 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_34 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_33 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_32 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_31 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_30 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_29 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_28 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_27 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_9 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_8 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_7 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_6 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_11 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_26 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_12 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_13 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_14 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_15 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_16 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_17 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_18 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_19 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_20 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_21 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_22 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_23 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_24 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_25 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_5 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_4 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_31 = 0x00001640U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_30 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_29 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_28 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_8 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_26 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_27 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_15 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_16 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_17 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_18 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_19 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_20 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_21 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_22 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_23 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_24 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_25 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___maxi_outstanding_wcount = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_start = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_global_addr = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_busy = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size = 0ULL;
    } else {
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_enq) 
             & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full)))) {
            if (vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_45) {
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[0U] 
                    = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[1U] 
                    = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size);
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[2U] 
                    = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride 
                        << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size 
                                          >> 0x00000020U)));
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[3U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr)))) 
                        << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride 
                                  >> 0x0000001fU));
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[4U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr)))) 
                        >> 0x0000001fU) | ((IData)(
                                                   ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                                      << 0x00000020U) 
                                                     | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr))) 
                                                    >> 0x00000020U)) 
                                           << 1U));
            } else {
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[0U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[1U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[2U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[3U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[4U] = 0U;
            }
            __VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0 
                = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head;
            __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0 = 1U;
            __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head)));
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0cU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_12 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_12 = 0U;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x0cU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_12 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_enq) 
             & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full)))) {
            if (vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44) {
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[0U] 
                    = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[1U] 
                    = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size);
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[2U] 
                    = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                        << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size 
                                          >> 0x00000020U)));
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[3U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                        << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                                  >> 0x0000001fU));
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[4U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                        >> 0x0000001fU) | ((IData)(
                                                   ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                                      << 0x00000020U) 
                                                     | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr))) 
                                                    >> 0x00000020U)) 
                                           << 1U));
            } else if (vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43) {
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[0U] 
                    = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[1U] 
                    = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size);
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[2U] 
                    = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                        << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size 
                                          >> 0x00000020U)));
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[3U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                        << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                                  >> 0x0000001fU));
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[4U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                        >> 0x0000001fU) | ((IData)(
                                                   ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                                      << 0x00000020U) 
                                                     | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr))) 
                                                    >> 0x00000020U)) 
                                           << 1U));
            } else {
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[0U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[1U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[2U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[3U] = 0U;
                __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[4U] = 0U;
            }
            __VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0 
                = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head;
            __VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0 = 1U;
            __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head)));
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr 
                = (0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                  + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
             & ((IData)(vlSelfRef.test__DOT__memory_arready) 
                | (~ (IData)(vlSelfRef.test__DOT__maxi_arvalid))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr 
                = (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr 
                   + (IData)((0x00000001ffffffffULL 
                              & VL_SHIFTL_QQI(33,33,32, vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size, 2U))));
        }
        if (((4U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr 
                = (0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                  + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3));
        }
        if (((8U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr 
                = (0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 
                                  + (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                     + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_base_offset)));
        }
        if (((0x0000000eU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr 
                = (0xfffffffcU & (((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)
                                    ? 0U : (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 
                                            + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
                                               + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row))) 
                                  + vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr));
        }
        if ((1U & ((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                   | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22))))) {
            vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21 
                = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_next_data_26;
            __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22 
                = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_next_valid_27;
        }
        if ((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22)) 
             & (2U != vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm))) {
            vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_data_24 
                = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18;
            __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25 
                = vlSelfRef.test__DOT__memory_rvalid;
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25) 
             & (2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm))) {
            __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25 = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_cond_0_1) {
            __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0 = 0U;
            __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0 = 0U;
        }
        if (((((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel_buf)) 
               & (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507)) 
              & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                  | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
                 & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf))) 
             & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_sb_0 
                = (((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_1_rdata_out) 
                    << 0x00000010U) | (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_1_rdata_out));
            __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0 = 1U;
            __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0 
                = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rlast_508) 
                   | (1ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_wstrb_sb_0 = 0x0fU;
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0;
            __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_wlast_sb_0;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0aU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_10 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x24U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_36 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x23U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_35 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x22U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_34 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x21U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_33 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x20U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_32 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x1fU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_31 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_31 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x1eU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_30 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_30 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x1dU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_29 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_29 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x1cU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_28 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_28 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x1bU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_27 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_27 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (9U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_9 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (8U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_8 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_8 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (7U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_7 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (6U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_6 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0bU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_11 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x1aU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_26 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_26 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_3 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_3 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_0 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_0 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_1 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_1 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_2 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_2 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0dU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_13 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0eU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_14 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0fU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_15 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_15 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x10U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_16 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_16 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x11U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_17 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_17 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x12U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_18 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_18 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x13U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_19 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_19 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x14U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_20 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_20 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x15U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_21 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_21 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x16U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_22 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_22 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x17U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_23 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_23 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x18U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_24 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_24 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x19U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_25 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_25 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (5U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_5 = 0U;
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            __Vdly__test__DOT__taketwo__DOT__internal_state_counter = 0U;
            __Vdly__test__DOT__taketwo__DOT___saxi_register_12 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_5 = 0U;
        } else if ((vlSelfRef.test__DOT__taketwo__DOT__main_fsm 
                    == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_13)) {
            if ((vlSelfRef.test__DOT__taketwo__DOT__internal_state_counter 
                 == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_14)) {
                __Vdly__test__DOT__taketwo__DOT___saxi_register_12 
                    = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_12);
                __Vdly__test__DOT__taketwo__DOT__internal_state_counter = 0U;
            } else {
                __Vdly__test__DOT__taketwo__DOT__internal_state_counter 
                    = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__internal_state_counter);
            }
        }
        if ((0x00000028U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_5 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_4 = 0U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_4 = 0U;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x1fU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_31 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x1eU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_30 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x1dU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_29 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x1cU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_28 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (8U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_8 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_1 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x1aU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_26 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x1bU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_27 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_0 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_2 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_3 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x0fU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_15 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x10U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_16 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x11U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_17 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x12U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_18 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x13U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_19 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x14U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_20 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x15U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_21 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x16U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_22 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x17U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_23 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x18U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_24 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x19U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_25 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (6U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6 = 0U;
        }
        if (((((IData)(vlSelfRef.test__DOT__maxi_awvalid) 
               & (IData)(vlSelfRef.test__DOT__memory_awready)) 
              & (~ (IData)(vlSelfRef.test__DOT__memory_bvalid))) 
             & (7U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___maxi_outstanding_wcount 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)));
        }
        if ((((~ ((IData)(vlSelfRef.test__DOT__maxi_awvalid) 
                  & (IData)(vlSelfRef.test__DOT__memory_awready))) 
              & (IData)(vlSelfRef.test__DOT__memory_bvalid)) 
             & (0U < (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___maxi_outstanding_wcount 
                = (7U & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount) 
                         - (IData)(1U)));
        }
        __Vdly__test__DOT__taketwo__DOT___maxi_write_start = 0U;
        if (((0x00000017U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_start = 1U;
            __Vdly__test__DOT__taketwo__DOT___maxi_write_global_addr 
                = (0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr 
                                  + ((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_val 
                                      + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
                                         + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
                                            + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
                                               + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och)))) 
                                     + vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr)));
            __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___dma_write_packed_local_packed_size_473));
        }
        if (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_busy = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_start = 1U;
        }
        if ((((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start) 
                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont))) 
               & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
              & (0x0000000000000100ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size)) 
             & (0x0000000000001000ULL <= (0x00000001ffffffffULL 
                                          & ((0x0000000000000fffULL 
                                              & (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485))) 
                                             + VL_SHIFTL_QQI(33,33,32, vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size, 2U)))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size 
                                            - VL_SHIFTR_QQI(33,33,32, 
                                                            (0x00000001ffffffffULL 
                                                             & (0x0000000000001000ULL 
                                                                - 
                                                                (0x0000000000000fffULL 
                                                                 & (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485))))), 2U)));
            __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size 
                = (0x00000001ffffffffULL & VL_SHIFTR_QQI(33,33,32, 
                                                         (0x00000001ffffffffULL 
                                                          & (0x0000000000001000ULL 
                                                             - 
                                                             (0x0000000000000fffULL 
                                                              & (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485))))), 2U));
        } else if (((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                      & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start) 
                         | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont))) 
                     & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
                    & (0x0000000000000100ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size;
            __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size = 0ULL;
        } else if (((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                      & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start) 
                         | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont))) 
                     & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
                    & (0x00001000U <= ((IData)(0x00000400U) 
                                       + (0x00000fffU 
                                          & vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size 
                                            - VL_SHIFTR_QQI(33,33,32, 
                                                            (0x00000001ffffffffULL 
                                                             & (0x0000000000001000ULL 
                                                                - 
                                                                (0x0000000000000fffULL 
                                                                 & (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485))))), 2U)));
            __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size 
                = (0x00000001ffffffffULL & VL_SHIFTR_QQI(33,33,32, 
                                                         (0x00000001ffffffffULL 
                                                          & (0x0000000000001000ULL 
                                                             - 
                                                             (0x0000000000000fffULL 
                                                              & (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485))))), 2U));
        } else if ((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                     & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start) 
                        | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont))) 
                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size 
                                            - 0x0000000000000100ULL));
            __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size = 0x0000000000000100ULL;
        }
        if ((IData)((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                      & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
                     & (((IData)(vlSelfRef.test__DOT__memory_awready) 
                         | (~ (IData)(vlSelfRef.test__DOT__maxi_awvalid))) 
                        & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_global_addr 
                = (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr 
                   + (IData)((0x00000001ffffffffULL 
                              & VL_SHIFTL_QQI(33,33,32, vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size, 2U))));
        }
        if (((IData)((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                       & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
                      & (((IData)(vlSelfRef.test__DOT__memory_awready) 
                          | (~ (IData)(vlSelfRef.test__DOT__maxi_awvalid))) 
                         & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount))))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_busy = 0U;
        }
    }
    if (vlSelfRef.test__DOT__RESETN) {
        if (((IData)(vlSelfRef.test__DOT___memory_wreq_fifo_enq) 
             & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_full)))) {
            __VdlyVal__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0 
                = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_1)
                    ? (((QData)((IData)(vlSelfRef.test__DOT__maxi_awaddr)) 
                        << 9U) | (QData)((IData)((0x000001ffU 
                                                  & ((IData)(1U) 
                                                     + (IData)(vlSelfRef.test__DOT__maxi_awlen))))))
                    : 0ULL);
            __VdlyDim0__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0 
                = vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head;
            __VdlySet__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0 = 1U;
            vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head)));
        }
        if (((IData)(vlSelfRef.test__DOT___memory_rreq_fifo_enq) 
             & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_full)))) {
            __VdlyVal__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0 
                = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_2)
                    ? (((QData)((IData)(vlSelfRef.test__DOT__maxi_araddr)) 
                        << 9U) | (QData)((IData)((0x000001ffU 
                                                  & ((IData)(1U) 
                                                     + (IData)(vlSelfRef.test__DOT__maxi_arlen))))))
                    : 0ULL);
            __VdlyDim0__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0 
                = vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head;
            __VdlySet__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0 = 1U;
            vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head)));
        }
        if (vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_0_1) {
            vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 = 0U;
        }
        if (vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_1_1) {
            vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 = 0U;
        }
        if (((6U == vlSelfRef.test__DOT__th_ctrl) & 
             ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)) 
              | (~ (IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0))))) {
            vlSelfRef.test__DOT_____05Fsaxi_wdata_sb_0 = 0x000015c0U;
            vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 = 1U;
            vlSelfRef.test__DOT_____05Fsaxi_wstrb_sb_0 = 0x0fU;
        }
        if (((IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0) 
             & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43))) {
            vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 
                = vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0;
        }
        if (((0x0000000cU == vlSelfRef.test__DOT__th_ctrl) 
             & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)) 
                | (~ (IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0))))) {
            vlSelfRef.test__DOT_____05Fsaxi_wdata_sb_0 = 1U;
            vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 = 1U;
            vlSelfRef.test__DOT_____05Fsaxi_wstrb_sb_0 = 0x0fU;
        }
        if (((IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0) 
             & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43))) {
            vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 
                = vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0;
        }
        if ((1U & ((IData)(vlSelfRef.test__DOT_____05Fsaxi_rready_sb_0) 
                   | (~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53))))) {
            vlSelfRef.test__DOT___sb___05Fsaxi_readdata_data_52 
                = vlSelfRef.test__DOT___sb___05Fsaxi_readdata_next_data_57;
            __Vdly__test__DOT___sb___05Fsaxi_readdata_valid_53 
                = vlSelfRef.test__DOT___sb___05Fsaxi_readdata_next_valid_58;
        }
        if ((((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53)) 
             & (~ (IData)(vlSelfRef.test__DOT_____05Fsaxi_rready_sb_0)))) {
            vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_data_55 
                = vlSelfRef.test__DOT__saxi_rdata;
            vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 
                = vlSelfRef.test__DOT__saxi_rvalid;
        }
        if (((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56) 
             & (IData)(vlSelfRef.test__DOT_____05Fsaxi_rready_sb_0))) {
            vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 = 0U;
        }
        if ((0U == vlSelfRef.test__DOT___memory_wdata_fsm)) {
            vlSelfRef.test__DOT__memory_bvalid = 0U;
            if ((1U & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_empty)))) {
                __Vdly__test__DOT___write_addr = (IData)(
                                                         (vlSelfRef.test__DOT___memory_wreq_fifo_rdata 
                                                          >> 9U));
                __Vdly__test__DOT___write_count = (QData)((IData)(
                                                                  (0x000001ffU 
                                                                   & (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_rdata))));
                __Vdly__test__DOT___memory_wdata_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT___memory_wdata_fsm)) {
            if (((~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)) 
                 & (IData)(vlSelfRef.test__DOT__write_data_wready_17))) {
                __Vdly__test__DOT___write_addr = ((IData)(4U) 
                                                  + vlSelfRef.test__DOT___write_addr);
                __Vdly__test__DOT___write_count = (0x00000001ffffffffULL 
                                                   & (vlSelfRef.test__DOT___write_count 
                                                      - 1ULL));
            }
            if ((((~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)) 
                  & (IData)(vlSelfRef.test__DOT__write_data_wready_17)) 
                 & (1ULL == vlSelfRef.test__DOT___write_count))) {
                vlSelfRef.test__DOT__memory_bvalid = 1U;
                __Vdly__test__DOT___memory_wdata_fsm = 0U;
            }
            if ((((~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)) 
                  & (IData)(vlSelfRef.test__DOT__write_data_wready_17)) 
                 & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                            >> 0x00000024U)))) {
                vlSelfRef.test__DOT__memory_bvalid = 1U;
                __Vdly__test__DOT___memory_wdata_fsm = 0U;
            }
        }
    } else {
        vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head = 0U;
        vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head = 0U;
        vlSelfRef.test__DOT_____05Fsaxi_wdata_sb_0 = 0U;
        vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 = 0U;
        vlSelfRef.test__DOT_____05Fsaxi_wstrb_sb_0 = 0U;
        vlSelfRef.test__DOT___sb___05Fsaxi_readdata_data_52 = 0U;
        __Vdly__test__DOT___sb___05Fsaxi_readdata_valid_53 = 0U;
        vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_data_55 = 0U;
        vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 = 0U;
        __Vdly__test__DOT___memory_wdata_fsm = 0U;
        vlSelfRef.test__DOT__memory_bvalid = 0U;
        __Vdly__test__DOT___write_addr = 0U;
        __Vdly__test__DOT___write_count = 0ULL;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) {
        vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_data_9 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10 = 0U;
        vlSelfRef.test__DOT__maxi_awaddr = 0U;
        vlSelfRef.test__DOT__maxi_awlen = 0U;
        vlSelfRef.__Vdly__test__DOT__maxi_awvalid = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size = 0ULL;
    } else {
        if ((1U & ((~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full)) 
                   | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7))))) {
            vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6 
                = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_next_data_11;
            __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7 
                = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_next_valid_12;
        }
        if ((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7)) 
             & (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full))) {
            vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_data_9 
                = vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3;
            __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0;
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10) 
             & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full)))) {
            __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10 = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___maxi_waddr_cond_0_1) {
            vlSelfRef.__Vdly__test__DOT__maxi_awvalid = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
               & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
              & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount))) 
             & ((6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)) 
                & ((IData)(vlSelfRef.test__DOT__memory_awready) 
                   | (~ (IData)(vlSelfRef.test__DOT__maxi_awvalid)))))) {
            vlSelfRef.test__DOT__maxi_awaddr = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr;
            vlSelfRef.test__DOT__maxi_awlen = (0x000000ffU 
                                               & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size) 
                                                  - (IData)(1U)));
            vlSelfRef.__Vdly__test__DOT__maxi_awvalid = 1U;
        }
        if ((((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
                & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full))) 
               & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount))) 
              & ((6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)) 
                 & ((IData)(vlSelfRef.test__DOT__memory_awready) 
                    | (~ (IData)(vlSelfRef.test__DOT__maxi_awvalid))))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size))) {
            vlSelfRef.__Vdly__test__DOT__maxi_awvalid = 0U;
        }
        if (((IData)(vlSelfRef.test__DOT__maxi_awvalid) 
             & (~ (IData)(vlSelfRef.test__DOT__memory_awready)))) {
            vlSelfRef.__Vdly__test__DOT__maxi_awvalid 
                = vlSelfRef.test__DOT__maxi_awvalid;
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och));
        }
        if (((4U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size = 1ULL;
        }
        if (((8U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel = 3U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_88));
        }
        if (((0x0000000eU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel = 4U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_101));
        }
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_fsm_4 = 0U;
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_addr_504 = 0U;
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_stride_505 = 0U;
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_length_506 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 = 0U;
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508 = 0U;
    } else if ((0U == vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_fsm_4)) {
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_addr_504 
            = (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr_buf);
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_stride_505 
            = (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride_buf);
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_length_506 
            = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf;
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 = 0U;
        __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508 = 0U;
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
              & (1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel_buf))) 
             & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf))) {
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_fsm_4 = 1U;
        }
    } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_fsm_4)) {
        if (((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
               | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
              & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf)) 
             & (0ULL < vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_length_506))) {
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_addr_504 
                = (0x000001ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_addr_504) 
                                  + (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_stride_505)));
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_length_506 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_length_506 
                                            - 1ULL));
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 = 1U;
        }
        if (((((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
               | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
              & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf)) 
             & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_length_506))) {
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508 = 1U;
        }
        if ((((IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rlast_508) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507)) 
             & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                 | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
                & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf)))) {
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 = 0U;
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508 = 0U;
            __Vdly__test__DOT__taketwo__DOT__read_burst_packed_fsm_4 = 0U;
        }
    }
    if (vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) {
        __Vdly__test__DOT__taketwo__DOT___maxi_write_data_busy = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_op_sel_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride_buf = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize_buf = 0U;
        vlSelfRef.test__DOT__maxi_araddr = 0U;
        vlSelfRef.test__DOT__maxi_arlen = 0U;
        __Vdly__test__DOT__maxi_arvalid = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_13 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_14 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr = 0U;
    } else {
        if (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
             & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy)) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty))) 
                & (2U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U]))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_data_busy = 1U;
            __Vdly__test__DOT__taketwo__DOT___maxi_write_op_sel_buf 
                = (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U] 
                                  >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[3U] 
                                       >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[3U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[2U] 
                                       >> 1U));
            __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf 
                = (0x00000001ffffffffULL & (((QData)((IData)(
                                                             vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[2U])) 
                                             << 0x00000020U) 
                                            | (QData)((IData)(
                                                              vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[1U]))));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[0U];
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm)) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf = 0ULL;
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
             & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf)))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf 
                = (0x00000001ffffffffULL & (((QData)((IData)(
                                                             vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[2U])) 
                                             << 0x00000020U) 
                                            | (QData)((IData)(
                                                              vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[1U]))));
        }
        if ((((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507)) 
             & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                 | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
                & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf)))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf 
                                            - 1ULL));
        }
        if ((((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
              & (((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel_buf)) 
                  & (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507)) 
                 & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                     | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
                    & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf)))) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rlast_508))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_write_data_busy = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___maxi_raddr_cond_0_1) {
            __Vdly__test__DOT__maxi_arvalid = 0U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
             & ((IData)(vlSelfRef.test__DOT__memory_arready) 
                | (~ (IData)(vlSelfRef.test__DOT__maxi_arvalid))))) {
            vlSelfRef.test__DOT__maxi_araddr = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr;
            vlSelfRef.test__DOT__maxi_arlen = (0x000000ffU 
                                               & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size) 
                                                  - (IData)(1U)));
            __Vdly__test__DOT__maxi_arvalid = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT__maxi_arvalid) 
             & (~ (IData)(vlSelfRef.test__DOT__memory_arready)))) {
            __Vdly__test__DOT__maxi_arvalid = vlSelfRef.test__DOT__maxi_arvalid;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0dU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_13 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x0dU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_13 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0eU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_14 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x0eU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_14 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((0x00000017U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___dma_write_packed_local_packed_size_473));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_laddr_offset 
                   + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_dma_offset);
        }
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_comp_count = 0U;
        __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 = 0U;
        __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_122 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_115 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_108 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_94 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_83 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_101 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_0 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_addr_76 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_stride_77 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_length_78 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_79 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_1 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_addr_82 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_stride_83 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_length_84 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_85 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_2 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_91 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_92 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_93 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_94 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_3 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_104 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_105 = 0U;
        __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_106 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_107 = 0U;
    } else {
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
                 & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode))))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 = 0U;
            }
            if (((((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0) 
                   & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1)) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 = 2U;
            }
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 = 0U;
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
                 & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode))))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 = 0U;
            }
            if (((((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0) 
                   & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1)) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 = 2U;
            }
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 = 0U;
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
                 & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode))))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 = 0U;
            }
            if (((((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0) 
                   & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1)) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 = 2U;
            }
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 = 0U;
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
                 & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode))))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 = 0U;
            }
            if (((((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0) 
                   & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1)) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 = 2U;
            }
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_438) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_comp_count 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_comp_count);
        }
        if ((6U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_comp_count = 0U;
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_407) 
                 & (0U != (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_mode))))) {
                __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4)) {
            __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 = 2U;
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_378___05Fdelay_377___05Fdelay_376___05F___05Fsubstreamoutput_192) 
                 & (1ULL == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count))) {
                __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 = 0U;
            }
            if (vlSelfRef.test__DOT__taketwo__DOT___tmp_438) {
                __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 = 0U;
            }
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4)) {
            __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size_buf;
            __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr 
                = (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset_buf 
                   - vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride_buf);
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_378___05Fdelay_377___05Fdelay_376___05F___05Fsubstreamoutput_192))) {
            __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count 
                                            - 1ULL));
            __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr 
                = (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr 
                   + vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride_buf);
        }
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable = 0U;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable = 1U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable = 0U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable = 0U;
        }
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable = 0U;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable = 1U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable = 0U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable = 0U;
        }
        if ((3U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_mode = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_mode = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_mode = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_122 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_14_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_115 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_12_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_108 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_10_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_94 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_6_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_83 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_4_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_101 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_8_next_parameter_data;
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_0)) {
            __Vdly__test__DOT__taketwo__DOT__write_burst_addr_76 
                = (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_stride_77 
                = (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_length_78 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf;
            vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_79 = 0U;
            if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                  & (1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf))) 
                 & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_0 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_0)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_addr_76 
                    = (0x0000007fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_76) 
                                      + (IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_77)));
                __Vdly__test__DOT__taketwo__DOT__write_burst_length_78 
                    = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_78 
                                                - 1ULL));
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_79 = 0U;
            }
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) 
                 & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_78))) {
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_79 = 1U;
                __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_0 = 0U;
            }
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_1)) {
            __Vdly__test__DOT__taketwo__DOT__write_burst_addr_82 
                = (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_stride_83 
                = (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_length_84 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf;
            vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_85 = 0U;
            if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                  & (2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf))) 
                 & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_1 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_1)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_addr_82 
                    = (0x0000007fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_82) 
                                      + (IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_83)));
                __Vdly__test__DOT__taketwo__DOT__write_burst_length_84 
                    = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_84 
                                                - 1ULL));
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_85 = 0U;
            }
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) 
                 & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_84))) {
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_85 = 1U;
                __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_1 = 0U;
            }
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_2)) {
            __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_91 
                = (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_92 
                = (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_93 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf;
            vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_94 = 0U;
            if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                  & (3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf))) 
                 & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_2 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_2)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_91 
                    = (0x000001ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_91) 
                                      + (IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_92)));
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_93 
                    = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_93 
                                                - 1ULL));
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_94 = 0U;
            }
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) 
                 & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_93))) {
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_94 = 1U;
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_2 = 0U;
            }
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_3)) {
            __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_104 
                = (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_105 
                = (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf);
            __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_106 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf;
            vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_107 = 0U;
            if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                  & (4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf))) 
                 & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_3 = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_3)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) {
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_104 
                    = (0x000001ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_104) 
                                      + (IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_105)));
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_106 
                    = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_106 
                                                - 1ULL));
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_107 = 0U;
            }
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22) 
                 & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_106))) {
                vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_107 = 1U;
                __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_3 = 0U;
            }
        }
    }
    if (vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) {
        __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_10 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 = 0U;
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 = 0U;
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffffffeU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffffffeU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffffffdU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffffffdU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffffffbU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffffffbU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffffff7U & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffffff7U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffffffefU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffffffefU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffffffdfU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffffffdfU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffffffbfU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffffffbfU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffffff7fU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffffff7fU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffffeffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffffeffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffffdffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffffdffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffffbffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffffbffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffff7ffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffff7ffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffffefffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffffefffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffffdfffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffffdfffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffffbfffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffffbfffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffff7fffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffff7fffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffeffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffeffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffdffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffdffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfffbffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfffbffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfff7ffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfff7ffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffefffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffefffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffdfffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffdfffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xffbfffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xffbfffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xff7fffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xff7fffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfeffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfeffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfdffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfdffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xfbffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xfbffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xf7ffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xf7ffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xefffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xefffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xdfffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xdfffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0xbfffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0xbfffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
            = (0x7fffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
            = (0x7fffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr = 0U;
        vlSelfRef.test__DOT__saxi_rdata = 0U;
        vlSelfRef.__Vdly__test__DOT__saxi_rvalid = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 0U;
        __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_busy = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_32 = 0U;
    } else {
        if (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                & (2U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U]))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf 
                = (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                                  >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                                       >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U] 
                                       >> 1U));
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (((QData)((IData)(
                                                             vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U])) 
                                             << 0x00000020U) 
                                            | (QData)((IData)(
                                                              vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[1U]))));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[0U];
        }
        if ((((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22)) 
             & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 0U;
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                                            - 1ULL));
        }
        if (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                & (4U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U]))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf 
                = (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                                  >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                                       >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U] 
                                       >> 1U));
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (((QData)((IData)(
                                                             vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U])) 
                                             << 0x00000020U) 
                                            | (QData)((IData)(
                                                              vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[1U]))));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[0U];
        }
        if ((((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22)) 
             & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 0U;
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                                            - 1ULL));
        }
        if (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                & (6U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U]))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf 
                = (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                                  >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                                       >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U] 
                                       >> 1U));
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (((QData)((IData)(
                                                             vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U])) 
                                             << 0x00000020U) 
                                            | (QData)((IData)(
                                                              vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[1U]))));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[0U];
        }
        if ((((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22)) 
             & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 0U;
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                                            - 1ULL));
        }
        if (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))) 
                & (8U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U]))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf 
                = (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                                  >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                                       >> 1U));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf 
                = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                    << 0x0000001fU) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U] 
                                       >> 1U));
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (((QData)((IData)(
                                                             vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U])) 
                                             << 0x00000020U) 
                                            | (QData)((IData)(
                                                              vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[1U]))));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[0U];
        }
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf 
                                            - 1ULL));
        }
        if ((((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22)) 
             & (1ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (5U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (5U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5 = 0U;
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5 = 1U;
        }
        if ((0x00000028U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (7U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (7U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7 = 0U;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0aU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_10 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x0aU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_10 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (9U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x0bU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (9U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x0bU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((1U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffffffeU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffffffeU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((2U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffffffdU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffffffdU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((4U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffffffbU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffffffbU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((8U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffffff7U & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffffff7U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000010U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffffffefU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffffffefU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000020U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffffffdfU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffffffdfU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000040U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffffffbfU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffffffbfU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000080U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffffff7fU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffffff7fU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000100U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffffeffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffffeffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000200U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffffdffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffffdffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000400U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffffbffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffffbffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00000800U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffff7ffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffff7ffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00001000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffffefffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffffefffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00002000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffffdfffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffffdfffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00004000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffffbfffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffffbfffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00008000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffff7fffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffff7fffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00010000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffeffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffeffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00020000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffdffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffdffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00040000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfffbffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfffbffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00080000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfff7ffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfff7ffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00100000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffefffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffefffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00200000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffdfffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffdfffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00400000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xffbfffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xffbfffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x00800000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xff7fffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xff7fffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x01000000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfeffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfeffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x02000000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfdffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfdffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x04000000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xfbffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xfbffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x08000000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xf7ffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xf7ffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x10000000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xefffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xefffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x20000000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xdfffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xdfffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((0x40000000U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0xbfffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0xbfffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if ((vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11 
             >> 0x1fU)) {
            __Vdly__test__DOT__taketwo__DOT___saxi_register_11 
                = (0x7fffffffU & __Vdly__test__DOT__taketwo__DOT___saxi_register_11);
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = (0x7fffffffU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9);
        }
        if (vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_51) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = ((0xfffffffeU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9) 
                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_51));
        }
        if (vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_53) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9 
                = ((0xfffffffdU & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9) 
                   | ((IData)(vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_53) 
                      << 1U));
        }
        vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_32;
        if (vlSelfRef.test__DOT__taketwo__DOT___saxi_rdata_cond_0_1) {
            vlSelfRef.__Vdly__test__DOT__saxi_rvalid = 0U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
             & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid))))) {
            vlSelfRef.test__DOT__saxi_rdata = vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46;
            vlSelfRef.__Vdly__test__DOT__saxi_rvalid = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT__saxi_rvalid) 
             & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56))) {
            vlSelfRef.__Vdly__test__DOT__saxi_rvalid 
                = vlSelfRef.test__DOT__saxi_rvalid;
        }
        __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 0U;
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 1U;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och));
        }
        if (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_busy = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 1U;
        }
        if ((((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
                & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start) 
                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont))) 
               & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full))) 
              & (0x0000000000000100ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size)) 
             & (0x0000000000001000ULL <= (0x00000001ffffffffULL 
                                          & ((0x0000000000000fffULL 
                                              & (QData)((IData)(
                                                                (0xfffffffcU 
                                                                 & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr)))) 
                                             + VL_SHIFTL_QQI(33,33,32, vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size, 2U)))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size 
                                            - VL_SHIFTR_QQI(33,33,32, 
                                                            (0x00000001ffffffffULL 
                                                             & (0x0000000000001000ULL 
                                                                - 
                                                                (0x0000000000000fffULL 
                                                                 & (QData)((IData)(
                                                                                (0xfffffffcU 
                                                                                & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr)))))), 2U)));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size 
                = (0x00000001ffffffffULL & VL_SHIFTR_QQI(33,33,32, 
                                                         (0x00000001ffffffffULL 
                                                          & (0x0000000000001000ULL 
                                                             - 
                                                             (0x0000000000000fffULL 
                                                              & (QData)((IData)(
                                                                                (0xfffffffcU 
                                                                                & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr)))))), 2U));
        } else if (((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
                      & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start) 
                         | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont))) 
                     & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full))) 
                    & (0x0000000000000100ULL >= vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size 
                = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size = 0ULL;
        } else if (((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
                      & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start) 
                         | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont))) 
                     & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full))) 
                    & (0x00001000U <= ((IData)(0x00000400U) 
                                       + (0x00000ffcU 
                                          & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr))))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size 
                                            - VL_SHIFTR_QQI(33,33,32, 
                                                            (0x00000001ffffffffULL 
                                                             & (0x0000000000001000ULL 
                                                                - 
                                                                (0x0000000000000fffULL 
                                                                 & (QData)((IData)(
                                                                                (0xfffffffcU 
                                                                                & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr)))))), 2U)));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size 
                = (0x00000001ffffffffULL & VL_SHIFTR_QQI(33,33,32, 
                                                         (0x00000001ffffffffULL 
                                                          & (0x0000000000001000ULL 
                                                             - 
                                                             (0x0000000000000fffULL 
                                                              & (QData)((IData)(
                                                                                (0xfffffffcU 
                                                                                & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr)))))), 2U));
        } else if ((((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
                     & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start) 
                        | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont))) 
                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full)))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size 
                                            - 0x0000000000000100ULL));
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size = 0x0000000000000100ULL;
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
              & ((IData)(vlSelfRef.test__DOT__memory_arready) 
                 | (~ (IData)(vlSelfRef.test__DOT__maxi_arvalid)))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size))) {
            vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_busy = 0U;
        }
        if (((4U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 1U;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size = 1ULL;
        }
        if (((8U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 1U;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_88));
        }
        if (((0x0000000eU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle))) {
            __Vdly__test__DOT__taketwo__DOT___maxi_read_start = 1U;
            __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_101));
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x20U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_32 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x20U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_32 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_339 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_338));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_263 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_262));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_8 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_7));
    vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_5 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_4));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_29 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_28));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_8 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_7));
    vlSelfRef.test__DOT___keep_sleep_count = __Vdly__test__DOT___keep_sleep_count;
    vlSelfRef.test__DOT__count___05Fmemory_wreq_fifo 
        = __Vdly__test__DOT__count___05Fmemory_wreq_fifo;
    vlSelfRef.test__DOT__count___05Fmemory_rreq_fifo 
        = __Vdly__test__DOT__count___05Fmemory_rreq_fifo;
    vlSelfRef.test__DOT__count___05Fmemory_wdata_fifo 
        = __Vdly__test__DOT__count___05Fmemory_wdata_fifo;
    vlSelfRef.test__DOT___memory_raddr_fsm = __Vdly__test__DOT___memory_raddr_fsm;
    vlSelfRef.test__DOT___memory_waddr_fsm = __Vdly__test__DOT___memory_waddr_fsm;
    vlSelfRef.test__DOT___d1___05Fmemory_rdata_fsm 
        = __Vdly__test__DOT___d1___05Fmemory_rdata_fsm;
    vlSelfRef.test__DOT___read_addr = __Vdly__test__DOT___read_addr;
    vlSelfRef.test__DOT___read_count = __Vdly__test__DOT___read_count;
    vlSelfRef.test__DOT___memory_rdata_fsm = __Vdly__test__DOT___memory_rdata_fsm;
    vlSelfRef.test__DOT___sleep_interval_count = __Vdly__test__DOT___sleep_interval_count;
    vlSelfRef.test__DOT__memory_rlast = __Vdly__test__DOT__memory_rlast;
    vlSelfRef.test__DOT__memory_rdata = __Vdly__test__DOT__memory_rdata;
    vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo 
        = __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo;
    vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo 
        = __Vdly__test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo;
    vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail 
        = __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail;
    vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail 
        = __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail;
    if (__VdlySet__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0) {
        vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[__VdlyDim0__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0] 
            = __VdlyVal__test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem__v0;
    }
    vlSelfRef.test__DOT___th_ctrl___05F_0 = __Vdly__test__DOT___th_ctrl___05F_0;
    vlSelfRef.test__DOT__time_counter = __Vdly__test__DOT__time_counter;
    vlSelfRef.test__DOT___th_ctrl_start_time_1 = __Vdly__test__DOT___th_ctrl_start_time_1;
    vlSelfRef.test__DOT__axim_rdata_73 = __Vdly__test__DOT__axim_rdata_73;
    vlSelfRef.test__DOT__axim_rdata_74 = __Vdly__test__DOT__axim_rdata_74;
    vlSelfRef.test__DOT___th_ctrl_end_time_2 = __Vdly__test__DOT___th_ctrl_end_time_2;
    vlSelfRef.test__DOT___th_ctrl_ok_3 = __Vdly__test__DOT___th_ctrl_ok_3;
    vlSelfRef.test__DOT___th_ctrl_bat_4 = __Vdly__test__DOT___th_ctrl_bat_4;
    vlSelfRef.test__DOT___th_ctrl_i_5 = __Vdly__test__DOT___th_ctrl_i_5;
    vlSelfRef.test__DOT__rdata_75 = __Vdly__test__DOT__rdata_75;
    vlSelfRef.test__DOT___th_ctrl_orig_6 = __Vdly__test__DOT___th_ctrl_orig_6;
    vlSelfRef.test__DOT__rdata_76 = __Vdly__test__DOT__rdata_76;
    vlSelfRef.test__DOT___th_ctrl_check_7 = __Vdly__test__DOT___th_ctrl_check_7;
    if (__VdlySet__test__DOT___memory_mem__v0) {
        vlSelfRef.test__DOT___memory_mem[__VdlyDim0__test__DOT___memory_mem__v0] 
            = __VdlyVal__test__DOT___memory_mem__v0;
    }
    if (__VdlySet__test__DOT___memory_mem__v1) {
        vlSelfRef.test__DOT___memory_mem[__VdlyDim0__test__DOT___memory_mem__v1] 
            = __VdlyVal__test__DOT___memory_mem__v1;
    }
    if (__VdlySet__test__DOT___memory_mem__v2) {
        vlSelfRef.test__DOT___memory_mem[__VdlyDim0__test__DOT___memory_mem__v2] 
            = __VdlyVal__test__DOT___memory_mem__v2;
    }
    if (__VdlySet__test__DOT___memory_mem__v3) {
        vlSelfRef.test__DOT___memory_mem[__VdlyDim0__test__DOT___memory_mem__v3] 
            = __VdlyVal__test__DOT___memory_mem__v3;
    }
    if (__VdlySet__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0) {
        vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[__VdlyDim0__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0] 
            = __VdlyVal__test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem__v0;
    }
    if (__VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0][0U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[0U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0][1U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[1U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0][2U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[2U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0][3U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[3U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0][4U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem__v0[4U];
    }
    vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head 
        = __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head;
    vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_stride_505 
        = __Vdly__test__DOT__taketwo__DOT__read_burst_packed_stride_505;
    vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_length_506 
        = __Vdly__test__DOT__taketwo__DOT__read_burst_packed_length_506;
    vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_addr_504 
        = __Vdly__test__DOT__taketwo__DOT__read_burst_packed_addr_504;
    vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_fsm_4 
        = __Vdly__test__DOT__taketwo__DOT__read_burst_packed_fsm_4;
    if (__VdlySet__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0) {
        vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[__VdlyDim0__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0] 
            = __VdlyVal__test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem__v0;
    }
    vlSelfRef.test__DOT__taketwo__DOT__internal_state_counter 
        = __Vdly__test__DOT__taketwo__DOT__internal_state_counter;
    vlSelfRef.test__DOT__taketwo__DOT___saxi_register_12 
        = __Vdly__test__DOT__taketwo__DOT___saxi_register_12;
    if (__VdlySet__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0][0U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[0U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0][1U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[1U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0][2U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[2U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0][3U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[3U];
        vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0][4U] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem__v0[4U];
    }
    vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head 
        = __Vdly__test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count 
        = __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr 
        = __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr;
    vlSelfRef.test__DOT__memory_rvalid = __Vdly__test__DOT__memory_rvalid;
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25 
        = __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_wlast_sb_0 
        = __Vdly__test__DOT__taketwo__DOT___maxi_wlast_sb_0;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_77 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_stride_77;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_78 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_length_78;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_76 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_addr_76;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_0 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_0;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_83 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_stride_83;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_84 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_length_84;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_82 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_addr_82;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_1 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_fsm_1;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_92 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_92;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_93 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_93;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_91 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_91;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_2 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_2;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_105 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_stride_105;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_106 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_length_106;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_104 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_addr_104;
    vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_3 
        = __Vdly__test__DOT__taketwo__DOT__write_burst_packed_fsm_3;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_cont;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_global_size;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_start;
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_busy_reg = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_stream_ivalid = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___acc_0_busy_reg = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_busy_reg = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___mul_3_busy_reg = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_count_16 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___pulse_count_18 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___pulse_prev_count_max_18 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_prev_count_max_16 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy_reg = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wenable = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wdata = 0U;
    } else {
        if (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_293)) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_294))) {
            vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_busy_reg = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_busy_reg = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_10) {
            vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_stream_ivalid = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_287) {
            vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_stream_ivalid = 1U;
        }
        if (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_325)) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_326))) {
            vlSelfRef.test__DOT__taketwo__DOT___acc_0_busy_reg = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___acc_0_busy_reg = 1U;
        }
        if (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_359)) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_360))) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_busy_reg = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_busy_reg = 1U;
        }
        if (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_283)) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_284))) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_3_busy_reg = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_3_busy_reg = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_11) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_235___05Fdelay_234___05Fdelay_233___05Fdelay_232___05F___05Fvariable_84;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_300) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15 = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_304) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15 = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid) {
            vlSelfRef.test__DOT__taketwo__DOT___reduceadd_count_16 
                = ((vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16 
                    >= (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_2)) 
                                                 - 1ULL)))
                    ? 0ULL : (0x00000001ffffffffULL 
                              & (1ULL + vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16)));
            if ((vlSelfRef.test__DOT__taketwo__DOT___pulse_current_count_18 
                 >= (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_2)) 
                                              - 1ULL)))) {
                vlSelfRef.test__DOT__taketwo__DOT___pulse_count_18 = 0ULL;
                vlSelfRef.test__DOT__taketwo__DOT___pulse_prev_count_max_18 = 1U;
            } else {
                vlSelfRef.test__DOT__taketwo__DOT___pulse_count_18 
                    = (0x00000001ffffffffULL & (1ULL 
                                                + vlSelfRef.test__DOT__taketwo__DOT___pulse_current_count_18));
                vlSelfRef.test__DOT__taketwo__DOT___pulse_prev_count_max_18 = 0U;
            }
            vlSelfRef.test__DOT__taketwo__DOT___reduceadd_prev_count_max_16 
                = (vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16 
                   >= (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_2)) 
                                                - 1ULL)));
        }
        if (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_469)) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_470))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy_reg = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy_reg = 1U;
        }
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wenable = 0U;
        if (((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_378___05Fdelay_377___05Fdelay_376___05F___05Fsubstreamoutput_192))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wenable = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wdata 
                = ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_366___05Fdelay_365___05Fdelay_364___05Fdelay_363___05F_eq_218)
                    ? (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210)
                    : ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_337___05Fdelay_336___05Fdelay_335___05Fdelay_334___05F_eq_215)
                        ? (IData)(vlSelfRef.test__DOT__taketwo__DOT___cond_data_214)
                        : (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210)));
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 
        = __Vdly__test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4;
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18 
        = (((QData)((IData)(vlSelfRef.test__DOT__memory_rlast)) 
            << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__memory_rdata)));
    vlSelfRef.test__DOT___memory_wdata_fifo_full = 
        ((7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head))) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail));
    vlSelfRef.test__DOT___memory_wreq_fifo_full = (
                                                   (7U 
                                                    & ((IData)(1U) 
                                                       + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head))) 
                                                   == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full 
        = ((7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head))) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail));
    vlSelfRef.test__DOT___memory_rreq_fifo_rdata = 
        vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem
        [vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail];
    vlSelfRef.test__DOT___memory_rreq_fifo_empty = 
        ((IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail));
    vlSelfRef.test__DOT___memory_rreq_fifo_full = (
                                                   (7U 
                                                    & ((IData)(1U) 
                                                       + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head))) 
                                                   == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full 
        = ((7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head))) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_438 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_437));
    vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_0_1 
        = vlSelfRef.test__DOT__RESETN;
    vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_1_1 
        = vlSelfRef.test__DOT__RESETN;
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_next_valid_27 
        = ((IData)(vlSelfRef.test__DOT__memory_rvalid) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_cond_0_1 
        = (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2)));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_290 = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_288 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_317 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_316));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_310 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_309));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_348 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_347));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_272 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_271));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_338 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_337));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_262 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_261));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_294 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_293));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_7 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_6));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_287 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_286));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_326 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_325));
    vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_4 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_3));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_360 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_359));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_284 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_283));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_28 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_27));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_7 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_6));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_300 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_299));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_304 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_303));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_235___05Fdelay_234___05Fdelay_233___05Fdelay_232___05F___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_234___05Fdelay_233___05Fdelay_232___05Fdelay_231___05F___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_470 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_469));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_366___05Fdelay_365___05Fdelay_364___05Fdelay_363___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_365___05Fdelay_364___05Fdelay_363___05Fdelay_362___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_337___05Fdelay_336___05Fdelay_335___05Fdelay_334___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_336___05Fdelay_335___05Fdelay_334___05Fdelay_333___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_378___05Fdelay_377___05Fdelay_376___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_377___05Fdelay_376___05Fdelay_375___05F___05Fsubstreamoutput_192));
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_next_data_26 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)
            ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_data_24
            : vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18);
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3 
        = (((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wlast_sb_0)) 
            << 0x00000024U) | (((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wstrb_sb_0)) 
                                << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_sb_0))));
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7 
        = __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7;
    vlSelfRef.test__DOT___memory_wdata_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_full));
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53 
        = __Vdly__test__DOT___sb___05Fsaxi_readdata_valid_53;
    vlSelfRef.test__DOT___memory_wreq_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_full));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_cur_global_size;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_global_addr;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_req_fsm;
    vlSelfRef.test__DOT__memory_awready = __Vdly__test__DOT__memory_awready;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel_buf 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_op_sel_buf;
    vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rlast_508 
        = __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rlast_508;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_data_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[0U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail][0U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[1U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail][1U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[2U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail][2U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[3U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail][3U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail][4U];
    vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 
        = __Vdly__test__DOT__taketwo__DOT__read_burst_packed_rvalid_507;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_data_busy;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0 
        = __Vdly__test__DOT__taketwo__DOT___maxi_wvalid_sb_0;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf 
        = __Vdly__test__DOT__taketwo__DOT___maxi_write_size_buf;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10 
        = __Vdly__test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10;
    vlSelfRef.test__DOT___memory_rreq_fifo_deq = ((~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_empty)) 
                                                  & (0U 
                                                     == vlSelfRef.test__DOT___memory_rdata_fsm));
    vlSelfRef.test__DOT___memory_rreq_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_full));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full));
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_1_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem
            [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_addr];
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_0_rdata_out 
            = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable)
                ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wdata)
                : vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem
               [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_addr]);
    }
    if (__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem__v0;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_1_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem
            [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_addr];
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_0_rdata_out 
            = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable)
                ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wdata)
                : vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem
               [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_addr]);
    }
    if (__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem[__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0] 
            = __VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem__v0;
    }
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_local_size_buf;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[0U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail][0U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[1U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail][1U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail][2U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail][3U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
        = vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem
        [vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail][4U];
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_data_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_data_busy;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22 
        = __Vdly__test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22;
    vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11 
        = __Vdly__test__DOT__taketwo__DOT___saxi_register_11;
    vlSelfRef.test__DOT___memory_wreq_fifo_rdata = 
        vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem
        [vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail];
    vlSelfRef.test__DOT___write_count = __Vdly__test__DOT___write_count;
    vlSelfRef.test__DOT___write_addr = __Vdly__test__DOT___write_addr;
    vlSelfRef.test__DOT___memory_wdata_fifo_rdata = 
        vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem
        [vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail];
    vlSelfRef.test__DOT___memory_wreq_fifo_empty = 
        ((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail));
    vlSelfRef.test__DOT___memory_wdata_fifo_empty = 
        ((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail));
    vlSelfRef.test__DOT___memory_wdata_fsm = __Vdly__test__DOT___memory_wdata_fsm;
    vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_0 
        = ((~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full)) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7));
    vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485 
        = (0xfffffffcU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr);
    vlSelfRef.test__DOT__taketwo__DOT___maxi_waddr_cond_0_1 
        = (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_deq 
        = (((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
            & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)) 
               & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf))) 
           | ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
              & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy))) 
                 & (2U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U])))));
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_next_valid_12 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10));
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_next_data_11 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)
            ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_data_9
            : vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3);
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_fsm_4) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507)) 
              | (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                  | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
                 & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf))));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_addr 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable)
            ? (0x000000ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_addr_504) 
                              >> 1U)) : 0U);
    vlSelfRef.test__DOT__taketwo__DOT___maxi_raddr_cond_0_1 
        = (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2)));
    vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43 
        = ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start)));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_437 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_436));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size_buf = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride_buf = 0U;
    } else if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_407) 
                & (0U != (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_mode))))) {
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset_buf 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size_buf 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride_buf 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride;
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_407 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_406));
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41 
        = (1U & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))));
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_1_rdata_out 
            = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable)
                ? vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wdata
                : vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem
               [vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_addr]);
    }
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_1) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_addr 
            = vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_82;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wdata 
            = (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21);
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wdata = 0U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_1_rdata_out 
            = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable)
                ? vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata
                : vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem
               [vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr]);
    }
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_0) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr 
            = vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_76;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata 
            = (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21);
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata = 0U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable) {
        if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable) {
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wdata;
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_1_1_wdata;
        } else {
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem
                [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr];
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem
                [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr];
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_3) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr 
            = (0x000000ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_104) 
                              >> 1U));
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wdata 
            = (0x0000ffffU & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21));
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_1_1_wdata 
            = (0x0000ffffU & (IData)((vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21 
                                      >> 0x00000010U)));
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wdata = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_1_1_wdata = 0U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable) {
        if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable) {
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wdata;
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_1_1_wdata;
        } else {
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem
                [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr];
            vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_1_rdata_out 
                = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem
                [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr];
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_2) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr 
            = (0x000000ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_91) 
                              >> 1U));
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wdata 
            = (0x0000ffffU & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21));
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_1_1_wdata 
            = (0x0000ffffU & (IData)((vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21 
                                      >> 0x00000010U)));
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wdata = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_1_1_wdata = 0U;
    }
    vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_51 
        = ((~ vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_50));
    vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_53 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_52)) 
           & (0U != vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_316 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_315));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_309 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_308));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_347 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_346));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_271 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_270));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_337 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_336));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_261 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_260));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_293 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_292));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_6 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_5));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_286 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_285));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_325 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_324));
    vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_3 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_2));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_359 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_358));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_283 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_282));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_27 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_26));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_6 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_5));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_299 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_298));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_303 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_302));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_234___05Fdelay_233___05Fdelay_232___05Fdelay_231___05F___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_233___05Fdelay_232___05Fdelay_231___05Fdelay_230___05F___05Fvariable_84));
    vlSelfRef.test__DOT___memory_wreq_fifo_deq = ((~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_empty)) 
                                                  & (0U 
                                                     == vlSelfRef.test__DOT___memory_wdata_fsm));
    vlSelfRef.test__DOT__write_data_wready_17 = ((1U 
                                                  == vlSelfRef.test__DOT___memory_wdata_fsm) 
                                                 & (0x000000000000000fULL 
                                                    != vlSelfRef.test__DOT___sleep_interval_count));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_469 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_468));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_365___05Fdelay_364___05Fdelay_363___05Fdelay_362___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_364___05Fdelay_363___05Fdelay_362___05Fdelay_361___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_336___05Fdelay_335___05Fdelay_334___05Fdelay_333___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_335___05Fdelay_334___05Fdelay_333___05Fdelay_332___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_377___05Fdelay_376___05Fdelay_375___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_376___05Fdelay_375___05Fdelay_374___05F___05Fsubstreamoutput_192));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_14_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_12_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_10_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_6_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_4_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_8_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_214 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210 = 0U;
    } else {
        if ((3U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_14_next_parameter_data = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_12_next_parameter_data = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_10_next_parameter_data = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_6_next_parameter_data = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_4_next_parameter_data = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_8_next_parameter_data = 1U;
        }
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_214 
            = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_212)
                ? (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_309___05Fsubstreamoutput_210)
                : 0U);
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_309___05Fsubstreamoutput_210;
    }
    vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_212 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && VL_LTS_III(16, 0U, (IData)(vlSelfRef.test__DOT__taketwo__DOT___cond_data_57)));
    vlSelfRef.test__DOT___memory_wdata_fifo_enq = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_0) 
                                                   & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_cont;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_global_size;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_global_addr;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_req_fsm;
    vlSelfRef.test__DOT__memory_arready = __Vdly__test__DOT__memory_arready;
    vlSelfRef.test__DOT__maxi_arvalid = __Vdly__test__DOT__maxi_arvalid;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start 
        = __Vdly__test__DOT__taketwo__DOT___maxi_read_start;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_deq 
        = (1U & (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                  & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)) 
                     & ((IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41) 
                        & (8U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U]))))) 
                 | (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                     & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)) 
                        & ((IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41) 
                           & (6U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U]))))) 
                    | (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                        & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)) 
                           & ((IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41) 
                              & (4U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U]))))) 
                       | (((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm) 
                           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)) 
                              & ((IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41) 
                                 & (2U == (0x01feU 
                                           & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U])))))
                           ? 1U : 0U)))));
    vlSelfRef.test__DOT___memory_wdata_fifo_deq = (
                                                   (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)) 
                                                   & (IData)(vlSelfRef.test__DOT__write_data_wready_17));
    vlSelfRef.test__DOT__taketwo__DOT___saxi_rdata_cond_0_1 
        = (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2)));
    vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_2 
        = ((1U == vlSelfRef.test__DOT___memory_raddr_fsm) 
           & ((IData)(vlSelfRef.test__DOT__maxi_arvalid) 
              & (IData)(vlSelfRef.test__DOT__memory_arready)));
    vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_45 
        = ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start)));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_436 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_435));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_406 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_405));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_sel = 0U;
    } else if (vlSelfRef.test__DOT__taketwo__DOT___tmp_184) {
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_mode = 1U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset 
            = (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_217);
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size 
            = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_248));
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride = 1U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_sel = 5U;
    }
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wenable) 
           & (5U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_sel)));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_184 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_183));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_315 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_314));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_308 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_307));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_346 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_345));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_270 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_269));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_336 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_335));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_260 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_259));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_292 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_busy));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_5 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_4));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_285 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_324 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_323));
    vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_2 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_1));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_358 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_357));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_282 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_281));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_26 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_25));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_5 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_4));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_298 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_302 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_301));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_233___05Fdelay_232___05Fdelay_231___05Fdelay_230___05F___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_232___05Fdelay_231___05Fdelay_230___05Fdelay_229___05F___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_468 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_467));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_364___05Fdelay_363___05Fdelay_362___05Fdelay_361___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_363___05Fdelay_362___05Fdelay_361___05Fdelay_360___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_335___05Fdelay_334___05Fdelay_333___05Fdelay_332___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_334___05Fdelay_333___05Fdelay_332___05Fdelay_331___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_376___05Fdelay_375___05Fdelay_374___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_375___05Fdelay_374___05Fdelay_373___05F___05Fsubstreamoutput_192));
    vlSelfRef.test__DOT___memory_rreq_fifo_enq = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_2) 
                                                  & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_almost_full)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_enq 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_45) 
           & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full)));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable 
        = ((~ vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr) 
           & (IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59));
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_addr 
            = (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr 
                              >> 1U));
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wdata 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wdata;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wdata = 0U;
    }
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable 
        = ((IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59) 
           & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr);
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable) {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_addr 
            = (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr 
                              >> 1U));
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wdata 
            = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wdata;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wdata = 0U;
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_435 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_434));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_405 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_404));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_183 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_182));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_314 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_313));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_307 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_306));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_345 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_344));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_269 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_268));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_335 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_334));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_259 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_258));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_4 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_3));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_323 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_322));
    vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_357 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_356));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_281 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_280));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_25 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_24));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_4 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_3));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_301 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_232___05Fdelay_231___05Fdelay_230___05Fdelay_229___05F___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_231___05Fdelay_230___05Fdelay_229___05Fdelay_228___05F___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_467 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_466));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_363___05Fdelay_362___05Fdelay_361___05Fdelay_360___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_362___05Fdelay_361___05Fdelay_360___05Fdelay_359___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_334___05Fdelay_333___05Fdelay_332___05Fdelay_331___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_333___05Fdelay_332___05Fdelay_331___05Fdelay_330___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_375___05Fdelay_374___05Fdelay_373___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_374___05Fdelay_373___05Fdelay_372___05F___05Fsubstreamoutput_192));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_309___05Fsubstreamoutput_210 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_248 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_217 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_57 = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_309___05Fsubstreamoutput_210 
            = vlSelfRef.test__DOT__taketwo__DOT___cond_data_57;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_248 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_247;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_217 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_216;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_57 
            = (0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_208_greatereq_55)
                               ? vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[0U]
                               : vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[0U]));
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_208_greatereq_55 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___greatereq_data_55));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_247 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_216 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___add_tree_1_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___add_tree_1_source_start = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_busy = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_247 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_246;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_216 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_215;
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_busy 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy;
        }
        if ((0U != vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_fsm)) {
            if ((1U == vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_fsm)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_start) {
                    __Vdly__test__DOT__taketwo__DOT___add_tree_1_source_start = 0U;
                    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_busy = 1U;
                    __Vdly__test__DOT__taketwo__DOT___add_tree_1_fsm = 2U;
                }
            } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_fsm)) {
                __Vdly__test__DOT__taketwo__DOT___add_tree_1_fsm = 3U;
            }
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_fsm 
        = __Vdly__test__DOT__taketwo__DOT___add_tree_1_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_start 
        = __Vdly__test__DOT__taketwo__DOT___add_tree_1_source_start;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_434 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_433));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_404 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_403));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_182 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_181));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_313 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_312));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_306 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_305));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_344 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_343));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_268 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_267));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_334 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_333));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_258 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_257));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_3 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_2));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_322 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_321));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_356 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_355));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_280 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_279));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_24 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_23));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_3 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_2));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_231___05Fdelay_230___05Fdelay_229___05Fdelay_228___05F___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_230___05Fdelay_229___05Fdelay_228___05Fdelay_227___05F___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_466 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_465));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_362___05Fdelay_361___05Fdelay_360___05Fdelay_359___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_361___05Fdelay_360___05Fdelay_359___05Fdelay_358___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_333___05Fdelay_332___05Fdelay_331___05Fdelay_330___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_332___05Fdelay_331___05Fdelay_330___05Fdelay_329___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_374___05Fdelay_373___05Fdelay_372___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_373___05Fdelay_372___05Fdelay_371___05F___05Fsubstreamoutput_192));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_433 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_432));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_403 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_402));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_181 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_180));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_312 = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_305 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_343 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_342));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_267 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_266));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_333 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_332));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_257 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_256));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_2 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_1));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_321 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_320));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_355 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_354));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_279 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_278));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_23 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_22));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_2 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_1));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_230___05Fdelay_229___05Fdelay_228___05Fdelay_227___05F___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_229___05Fdelay_228___05Fdelay_227___05Fdelay_226___05F___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_465 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_464));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_361___05Fdelay_360___05Fdelay_359___05Fdelay_358___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_360___05Fdelay_359___05Fdelay_358___05Fdelay_357___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_332___05Fdelay_331___05Fdelay_330___05Fdelay_329___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_331___05Fdelay_330___05Fdelay_329___05Fdelay_328___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_373___05Fdelay_372___05Fdelay_371___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_372___05Fdelay_371___05Fdelay_370___05F___05Fsubstreamoutput_192));
    VL_EXTENDS_WW(130,96, __Vtemp_23, vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27);
    __Vtemp_25[0U] = __Vtemp_23[0U];
    __Vtemp_25[1U] = __Vtemp_23[1U];
    __Vtemp_25[2U] = __Vtemp_23[2U];
    __Vtemp_25[3U] = __Vtemp_23[3U];
    __Vtemp_26[0U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[0U];
    __Vtemp_26[1U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[1U];
    __Vtemp_26[2U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[2U];
    __Vtemp_26[3U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[3U];
    VL_ADD_W(4, __Vtemp_27, __Vtemp_25, __Vtemp_26);
    VL_EXTENDS_WI(97,2, __Vtemp_28, ((vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U] 
                                      >> 0x0000001fU)
                                      ? 3U : 0U));
    VL_ADD_W(4, __Vtemp_29, __Vtemp_27, __Vtemp_28);
    __Vtemp_30[0U] = __Vtemp_29[0U];
    __Vtemp_30[1U] = __Vtemp_29[1U];
    __Vtemp_30[2U] = __Vtemp_29[2U];
    __Vtemp_30[3U] = (1U & __Vtemp_29[3U]);
    VL_SHIFTRS_WWI(97,97,7, __Vtemp_31, __Vtemp_30, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_202___05Fdelay_201___05Fdelay_200___05Fdelay_199___05Fvariable_26));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_432 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_431));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_402 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_401));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_180 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_179));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_342 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_341));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_266 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_265));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_332 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_331));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_256 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_255));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_stream_ivalid));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_320 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_319));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_354 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_353));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_278 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_277));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_22 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_21));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_stream_ivalid));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_229___05Fdelay_228___05Fdelay_227___05Fdelay_226___05F___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_228___05Fdelay_227___05Fdelay_226___05Fdelay_225___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_464 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_463));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_360___05Fdelay_359___05Fdelay_358___05Fdelay_357___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_359___05Fdelay_358___05Fdelay_357___05Fdelay_356___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_331___05Fdelay_330___05Fdelay_329___05Fdelay_328___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_330___05Fdelay_329___05Fdelay_328___05Fdelay_327___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_372___05Fdelay_371___05Fdelay_370___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_371___05Fdelay_370___05Fdelay_369___05F___05Fsubstreamoutput_192));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_246 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_215 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_47 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___lessthan_data_51 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___greatereq_data_55 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_245 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_214 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[2U] = 0U;
    } else {
        if (vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_47) {
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[0U] = 0x00007fffU;
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[1U] = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[2U] = 0U;
        } else {
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[0U] 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[0U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[1U] 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[1U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_49[2U] 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[2U];
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___lessthan_data_51) {
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[0U] = 0xffff8001U;
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[1U] = 0xffffffffU;
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[2U] = 0xffffffffU;
        } else {
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[0U] 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[0U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[1U] 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[1U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_53[2U] 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[2U];
        }
        vlSelfRef.test__DOT__taketwo__DOT___tmp_246 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_245;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_215 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_214;
        __Vtemp_16[0U] = 0x00007fffU;
        __Vtemp_16[1U] = 0U;
        __Vtemp_16[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_47 
            = VL_LTS_IWW(96, __Vtemp_16, vlSelfRef.test__DOT__taketwo__DOT___cond_data_46);
        __Vtemp_17[0U] = 0xffff8001U;
        __Vtemp_17[1U] = 0xffffffffU;
        __Vtemp_17[2U] = 0xffffffffU;
        vlSelfRef.test__DOT__taketwo__DOT___lessthan_data_51 
            = VL_GTS_IWW(96, __Vtemp_17, vlSelfRef.test__DOT__taketwo__DOT___cond_data_46);
        __Vtemp_18[0U] = 0U;
        __Vtemp_18[1U] = 0U;
        __Vtemp_18[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___greatereq_data_55 
            = VL_LTES_IWW(96, __Vtemp_18, vlSelfRef.test__DOT__taketwo__DOT___cond_data_46);
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[0U] 
            = vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[0U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[1U] 
            = vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[1U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46[2U] 
            = vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[2U];
        vlSelfRef.test__DOT__taketwo__DOT___tmp_245 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_244;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_214 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_213;
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_206___05Fdelay_205___05Fdelay_204___05Fdelay_203_eq_45) {
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[0U] 
                = vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[0U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[1U] 
                = vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[1U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[2U] 
                = vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U];
        } else {
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[0U] 
                = __Vtemp_31[0U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[1U] 
                = __Vtemp_31[1U];
            vlSelfRef.test__DOT__taketwo__DOT___cond_data_46[2U] 
                = __Vtemp_31[2U];
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_206___05Fdelay_205___05Fdelay_204___05Fdelay_203_eq_45 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_205___05Fdelay_204___05Fdelay_203_eq_45));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_431 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_430));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_401 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_400));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_179 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_178));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_341 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_340));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_265 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_264));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_331 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_330));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_255 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_254));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_319 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_busy));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_353 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_352));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_277 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_276));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_21 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_20));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_228___05Fdelay_227___05Fdelay_226___05Fdelay_225___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_227___05Fdelay_226___05Fdelay_225___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_463 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_462));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_359___05Fdelay_358___05Fdelay_357___05Fdelay_356___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_358___05Fdelay_357___05Fdelay_356___05Fdelay_355___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_330___05Fdelay_329___05Fdelay_328___05Fdelay_327___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_329___05Fdelay_328___05Fdelay_327___05Fdelay_326___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_371___05Fdelay_370___05Fdelay_369___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_370___05Fdelay_369___05Fdelay_368___05F___05Fsubstreamoutput_192));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_205___05Fdelay_204___05Fdelay_203_eq_45 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_204___05Fdelay_203_eq_45));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_244 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_213 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[3U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[4U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_202___05Fdelay_201___05Fdelay_200___05Fdelay_199___05Fvariable_26 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U] = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_244 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_243;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_213 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_212;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[0U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[0U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[1U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[1U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[2U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[2U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[3U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[3U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[4U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[4U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_202___05Fdelay_201___05Fdelay_200___05Fdelay_199___05Fvariable_26 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_201___05Fdelay_200___05Fdelay_199___05Fvariable_26;
        vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[0U] 
            = vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1[0U];
        vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[1U] 
            = vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1[1U];
        vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U] 
            = vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1[2U];
    }
    vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1[0U] 
        = vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul0[0U];
    vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1[1U] 
        = vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul0[1U];
    vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1[2U] 
        = vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul0[2U];
    vlSelfRef.test__DOT__taketwo__DOT___tmp_430 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_429));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_400 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_399));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_178 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_177));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_340 = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_264 = 0U;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_330 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_254 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_start));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_243 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_212 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___mul_3_stream_ivalid = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_243 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_242;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_212 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_211;
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_1) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_3_stream_ivalid = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_253) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_3_stream_ivalid = 1U;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_253 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_252));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_352 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_351));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_276 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_275));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_20 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_19));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_stream_ivalid = 0U;
    } else {
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_18) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_stream_ivalid = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_329) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_stream_ivalid = 1U;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_329 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_328));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_227___05Fdelay_226___05Fdelay_225___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_226___05Fdelay_225___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_462 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_461));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_358___05Fdelay_357___05Fdelay_356___05Fdelay_355___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_357___05Fdelay_356___05Fdelay_355___05Fdelay_354___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_329___05Fdelay_328___05Fdelay_327___05Fdelay_326___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_328___05Fdelay_327___05Fdelay_326___05Fdelay_325___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_370___05Fdelay_369___05Fdelay_368___05F___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_369___05Fdelay_368___05Fdelay_367___05Fsubstreamoutput_192));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_204___05Fdelay_203_eq_45 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_203_eq_45));
    VL_EXTENDS_WQ(96,64, __Vtemp_39, vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___a);
    VL_EXTENDS_WI(96,32, __Vtemp_40, vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___b);
    VL_MULS_WWW(96, vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul0, __Vtemp_39, __Vtemp_40);
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[3U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[4U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_201___05Fdelay_200___05Fdelay_199___05Fvariable_26 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_242 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_211 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___acc_0_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___acc_0_source_start = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_busy = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[0U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[0U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[1U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[1U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[2U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[2U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[3U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[3U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33[4U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[4U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_201___05Fdelay_200___05Fdelay_199___05Fvariable_26 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_200___05Fdelay_199___05Fvariable_26;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_242 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_241;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_211 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_210;
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_busy 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy;
        }
        if ((0U != vlSelfRef.test__DOT__taketwo__DOT___acc_0_fsm)) {
            if ((1U == vlSelfRef.test__DOT__taketwo__DOT___acc_0_fsm)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start) {
                    __Vdly__test__DOT__taketwo__DOT___acc_0_source_start = 0U;
                    vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_busy = 1U;
                    __Vdly__test__DOT__taketwo__DOT___acc_0_fsm = 2U;
                }
            } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___acc_0_fsm)) {
                __Vdly__test__DOT__taketwo__DOT___acc_0_fsm = 3U;
            }
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_fsm = __Vdly__test__DOT__taketwo__DOT___acc_0_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_429 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_428));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_399 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_398));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_177 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_176));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_252 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_251));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_351 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_350));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_275 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_274));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_19 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_18));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_328 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_327));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_226___05Fdelay_225___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_225___05Fvariable_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_461 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_460));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_357___05Fdelay_356___05Fdelay_355___05Fdelay_354___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_356___05Fdelay_355___05Fdelay_354___05Fdelay_353___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_328___05Fdelay_327___05Fdelay_326___05Fdelay_325___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_327___05Fdelay_326___05Fdelay_325___05Fdelay_324___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_369___05Fdelay_368___05Fdelay_367___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_368___05Fdelay_367___05Fsubstreamoutput_192));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_203_eq_45 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26)));
    __Vtemp_43[0U] = 1U;
    __Vtemp_43[1U] = 0U;
    __Vtemp_43[2U] = 0U;
    __Vtemp_43[3U] = 0U;
    __Vtemp_43[4U] = 0U;
    VL_SHIFTL_WWI(130,130,7, __Vtemp_44, __Vtemp_43, 
                  (0x0000007fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26) 
                                  - (IData)(1U))));
    vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___b 
        = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_25;
    vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___a 
        = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_24;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_428 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_427));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_398 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_397));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_176 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_175));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_251 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_350 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_274 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_busy));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_327 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_225___05Fvariable_84 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_84));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_460 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_459));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_356___05Fdelay_355___05Fdelay_354___05Fdelay_353___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_355___05Fdelay_354___05Fdelay_353___05Fdelay_352___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_327___05Fdelay_326___05Fdelay_325___05Fdelay_324___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_326___05Fdelay_325___05Fdelay_324___05Fdelay_323___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_368___05Fdelay_367___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_367___05Fsubstreamoutput_192));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_427 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_426));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_397 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_396));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_175 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_174));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_459 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_458));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_355___05Fdelay_354___05Fdelay_353___05Fdelay_352___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_354___05Fdelay_353___05Fdelay_352___05Fdelay_351___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_326___05Fdelay_325___05Fdelay_324___05Fdelay_323___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_325___05Fdelay_324___05Fdelay_323___05Fdelay_322___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_367___05Fsubstreamoutput_192 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_189___05Fdelay_188___05Fdelay_187___05Fdelay_186_pulse_18));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[3U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[4U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_200___05Fdelay_199___05Fvariable_26 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_241 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_210 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[3U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[4U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_199___05Fvariable_26 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_240 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_209 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_25 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_24 = 0ULL;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[0U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[0U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[1U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[1U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[2U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[2U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[3U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[3U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33[4U] 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[4U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_200___05Fdelay_199___05Fvariable_26 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_199___05Fvariable_26;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_241 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_240;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_210 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[0U] 
            = __Vtemp_44[0U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[1U] 
            = __Vtemp_44[1U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[2U] 
            = __Vtemp_44[2U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[3U] 
            = __Vtemp_44[3U];
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33[4U] 
            = (3U & __Vtemp_44[4U]);
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_199___05Fvariable_26 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_240 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_239;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_209 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_208;
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_18) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26 
                = (0x0000007fU & (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_308___05Fdelay_307___05Fdelay_306___05Fdelay_305___05F_plus_209));
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_25 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_291___05Fdelay_290___05Fdelay_289___05Fdelay_288___05F_cond_107;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_24 
                = vlSelfRef.test__DOT__taketwo__DOT___plus_data_193;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_18 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_17));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_239 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_208 = 0ULL;
        __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm 
            = __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm;
        vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start 
            = __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start;
        __Vdly__test__DOT__taketwo__DOT___mul_3_fsm = 0U;
        __Vdly__test__DOT__taketwo__DOT___mul_3_source_start = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_busy = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_239 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_238;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_208 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_207;
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy) {
            vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy;
            vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_busy 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy;
        }
        if ((0U != vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm)) {
            if ((1U == vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start) {
                    __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start = 0U;
                    vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy = 1U;
                    __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm = 2U;
                }
            } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm)) {
                __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm = 3U;
            }
        }
        vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm 
            = __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm;
        vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start 
            = __Vdly__test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start;
        if ((0U != vlSelfRef.test__DOT__taketwo__DOT___mul_3_fsm)) {
            if ((1U == vlSelfRef.test__DOT__taketwo__DOT___mul_3_fsm)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_start) {
                    __Vdly__test__DOT__taketwo__DOT___mul_3_source_start = 0U;
                    vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_busy = 1U;
                    __Vdly__test__DOT__taketwo__DOT___mul_3_fsm = 2U;
                }
            } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___mul_3_fsm)) {
                __Vdly__test__DOT__taketwo__DOT___mul_3_fsm = 3U;
            }
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_fsm = __Vdly__test__DOT__taketwo__DOT___mul_3_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_start 
        = __Vdly__test__DOT__taketwo__DOT___mul_3_source_start;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_426 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_425));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_396 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_395));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_174 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_173));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_84 = 0U;
    } else {
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_366) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_84 = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_370) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_84 = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_376) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_84 = 1U;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_376 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_366 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_365));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_370 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_369));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_458 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_457));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_354___05Fdelay_353___05Fdelay_352___05Fdelay_351___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_353___05Fdelay_352___05Fdelay_351___05Fdelay_350___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_325___05Fdelay_324___05Fdelay_323___05Fdelay_322___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_324___05Fdelay_323___05Fdelay_322___05Fdelay_321___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_189___05Fdelay_188___05Fdelay_187___05Fdelay_186_pulse_18 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_188___05Fdelay_187___05Fdelay_186_pulse_18));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_17 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_16));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_425 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_424));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_395 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_394));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_173 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_172));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_365 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_364));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_369 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_368));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_457 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_456));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_353___05Fdelay_352___05Fdelay_351___05Fdelay_350___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_352___05Fdelay_351___05Fdelay_350___05Fdelay_349___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_324___05Fdelay_323___05Fdelay_322___05Fdelay_321___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_323___05Fdelay_322___05Fdelay_321___05Fdelay_320___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_188___05Fdelay_187___05Fdelay_186_pulse_18 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_187___05Fdelay_186_pulse_18));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_16 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_15));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_424 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_423));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_394 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_393));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_172 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_171));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_364 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_368 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_367));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_456 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_455));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_352___05Fdelay_351___05Fdelay_350___05Fdelay_349___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_351___05Fdelay_350___05Fdelay_349___05Fdelay_348___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_323___05Fdelay_322___05Fdelay_321___05Fdelay_320___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_322___05Fdelay_321___05Fdelay_320___05Fdelay_319___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_187___05Fdelay_186_pulse_18 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_186_pulse_18));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_15 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_14));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_423 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_422));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_393 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_392));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_171 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_170));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_367 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_455 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_454));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_351___05Fdelay_350___05Fdelay_349___05Fdelay_348___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_350___05Fdelay_349___05Fdelay_348___05Fdelay_347___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_322___05Fdelay_321___05Fdelay_320___05Fdelay_319___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_321___05Fdelay_320___05Fdelay_319___05Fdelay_318___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_186_pulse_18 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_data_18));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_14 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_13));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_308___05Fdelay_307___05Fdelay_306___05Fdelay_305___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_291___05Fdelay_290___05Fdelay_289___05Fdelay_288___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_193 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_238 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_207 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_307___05Fdelay_306___05Fdelay_305___05Fdelay_304___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_290___05Fdelay_289___05Fdelay_288___05Fdelay_287___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_273___05Fdelay_272___05Fdelay_271___05Fdelay_270___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sra_data_21 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_237 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_206 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_306___05Fdelay_305___05Fdelay_304___05Fdelay_303___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_289___05Fdelay_288___05Fdelay_287___05Fdelay_286___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_272___05Fdelay_271___05Fdelay_270___05Fdelay_269___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_185___05Fdelay_184___05Fdelay_183___05Fdelay_182___05Fvariable_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_20 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_236 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_205 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_305___05Fdelay_304___05Fdelay_303___05Fdelay_302___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_288___05Fdelay_287___05Fdelay_286___05Fdelay_285___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_271___05Fdelay_270___05Fdelay_269___05Fdelay_268___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_184___05Fdelay_183___05Fdelay_182___05Fvariable_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_13 = 0ULL;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_308___05Fdelay_307___05Fdelay_306___05Fdelay_305___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_307___05Fdelay_306___05Fdelay_305___05Fdelay_304___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_291___05Fdelay_290___05Fdelay_289___05Fdelay_288___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_290___05Fdelay_289___05Fdelay_288___05Fdelay_287___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_193 
            = (vlSelfRef.test__DOT__taketwo__DOT___sra_data_21 
               + VL_EXTENDS_QI(64,32, vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_273___05Fdelay_272___05Fdelay_271___05Fdelay_270___05F_cond_100));
        vlSelfRef.test__DOT__taketwo__DOT___tmp_238 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_237;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_207 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_206;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_307___05Fdelay_306___05Fdelay_305___05Fdelay_304___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_306___05Fdelay_305___05Fdelay_304___05Fdelay_303___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_290___05Fdelay_289___05Fdelay_288___05Fdelay_287___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_289___05Fdelay_288___05Fdelay_287___05Fdelay_286___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_273___05Fdelay_272___05Fdelay_271___05Fdelay_270___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_272___05Fdelay_271___05Fdelay_270___05Fdelay_269___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT___sra_data_21 
            = VL_SHIFTRS_QQI(64,64,7, vlSelfRef.test__DOT__taketwo__DOT___plus_data_20, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_185___05Fdelay_184___05Fdelay_183___05Fdelay_182___05Fvariable_1));
        vlSelfRef.test__DOT__taketwo__DOT___tmp_237 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_236;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_206 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_205;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_306___05Fdelay_305___05Fdelay_304___05Fdelay_303___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_305___05Fdelay_304___05Fdelay_303___05Fdelay_302___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_289___05Fdelay_288___05Fdelay_287___05Fdelay_286___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_288___05Fdelay_287___05Fdelay_286___05Fdelay_285___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_272___05Fdelay_271___05Fdelay_270___05Fdelay_269___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_271___05Fdelay_270___05Fdelay_269___05Fdelay_268___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_185___05Fdelay_184___05Fdelay_183___05Fdelay_182___05Fvariable_1 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_184___05Fdelay_183___05Fdelay_182___05Fvariable_1;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_20 
            = (vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_181___05Fdelay_180_reduceadd_16 
               + vlSelfRef.test__DOT__taketwo__DOT___cond_data_13);
        vlSelfRef.test__DOT__taketwo__DOT___tmp_236 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_235;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_205 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_204;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_305___05Fdelay_304___05Fdelay_303___05Fdelay_302___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_304___05Fdelay_303___05Fdelay_302___05Fdelay_301___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_288___05Fdelay_287___05Fdelay_286___05Fdelay_285___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_287___05Fdelay_286___05Fdelay_285___05Fdelay_284___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_271___05Fdelay_270___05Fdelay_269___05Fdelay_268___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_270___05Fdelay_269___05Fdelay_268___05Fdelay_267___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_184___05Fdelay_183___05Fdelay_182___05Fvariable_1 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_183___05Fdelay_182___05Fvariable_1;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_13 
            = (((QData)((IData)(((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_179_greaterthan_3)
                                  ? vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[1U]
                                  : 0U))) << 0x00000020U) 
               | (QData)((IData)(((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_179_greaterthan_3)
                                   ? vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[0U]
                                   : 0U))));
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_179_greaterthan_3 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_3));
    __Vtemp_50[0U] = 1U;
    __Vtemp_50[1U] = 0U;
    __Vtemp_50[2U] = 0U;
    __Vtemp_50[3U] = 0U;
    __Vtemp_50[4U] = 0U;
    VL_SHIFTL_WWI(130,130,7, __Vtemp_51, __Vtemp_50, (IData)(vlSelfRef.test__DOT__taketwo__DOT___minus_data_5));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_422 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_421));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_392 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_391));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_170 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_169));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_454 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_453));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_350___05Fdelay_349___05Fdelay_348___05Fdelay_347___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_349___05Fdelay_348___05Fdelay_347___05Fdelay_346___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_321___05Fdelay_320___05Fdelay_319___05Fdelay_318___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_320___05Fdelay_319___05Fdelay_318___05Fdelay_317___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_13 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_12));
    vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_3 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (0U < (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_1)));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_181___05Fdelay_180_reduceadd_16 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_235 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_204 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_304___05Fdelay_303___05Fdelay_302___05Fdelay_301___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_287___05Fdelay_286___05Fdelay_285___05Fdelay_284___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_270___05Fdelay_269___05Fdelay_268___05Fdelay_267___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_183___05Fdelay_182___05Fvariable_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[0U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[1U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[2U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[3U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[4U] = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_180_reduceadd_16 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_234 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_203 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___pulse_data_18 = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_181___05Fdelay_180_reduceadd_16 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_180_reduceadd_16;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_235 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_234;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_204 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_203;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_304___05Fdelay_303___05Fdelay_302___05Fdelay_301___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_303___05Fdelay_302___05Fdelay_301___05Fdelay_300___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_287___05Fdelay_286___05Fdelay_285___05Fdelay_284___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_286___05Fdelay_285___05Fdelay_284___05Fdelay_283___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_270___05Fdelay_269___05Fdelay_268___05Fdelay_267___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_269___05Fdelay_268___05Fdelay_267___05Fdelay_266___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_183___05Fdelay_182___05Fvariable_1 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_182___05Fvariable_1;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[0U] 
            = __Vtemp_51[0U];
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[1U] 
            = __Vtemp_51[1U];
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[2U] 
            = __Vtemp_51[2U];
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[3U] 
            = __Vtemp_51[3U];
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_7[4U] 
            = (3U & __Vtemp_51[4U]);
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_180_reduceadd_16 
            = vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_234 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_233;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_203 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_202;
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_reset_cond_18))) {
            vlSelfRef.test__DOT__taketwo__DOT___pulse_data_18 = 0U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid) {
            vlSelfRef.test__DOT__taketwo__DOT___pulse_data_18 
                = (vlSelfRef.test__DOT__taketwo__DOT___pulse_current_count_18 
                   >= (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_2)) 
                                                - 1ULL)));
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___pulse_reset_cond_18 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_prev_count_max_18));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_303___05Fdelay_302___05Fdelay_301___05Fdelay_300___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_286___05Fdelay_285___05Fdelay_284___05Fdelay_283___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_269___05Fdelay_268___05Fdelay_267___05Fdelay_266___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_182___05Fvariable_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___minus_data_5 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16 = 0ULL;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_303___05Fdelay_302___05Fdelay_301___05Fdelay_300___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_302___05Fdelay_301___05Fdelay_300___05Fdelay_299___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_286___05Fdelay_285___05Fdelay_284___05Fdelay_283___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_285___05Fdelay_284___05Fdelay_283___05Fdelay_282___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_269___05Fdelay_268___05Fdelay_267___05Fdelay_266___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_268___05Fdelay_267___05Fdelay_266___05Fdelay_265___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_182___05Fvariable_1 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_1;
        vlSelfRef.test__DOT__taketwo__DOT___minus_data_5 
            = (0x0000007fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_1) 
                              - (IData)(1U)));
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_reset_cond_16))) {
            vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16 = 0ULL;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid) {
            vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16 
                = (vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_data_16 
                   + vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_0);
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___reduceadd_reset_cond_16 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_prev_count_max_16));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_421 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_420));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_391 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_390));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_169 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_168));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_453 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_452));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_349___05Fdelay_348___05Fdelay_347___05Fdelay_346___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_348___05Fdelay_347___05Fdelay_346___05Fdelay_345___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_320___05Fdelay_319___05Fdelay_318___05Fdelay_317___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_319___05Fdelay_318___05Fdelay_317___05Fdelay_316___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT___pulse_current_count_18 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_reset_cond_18)
            ? 0ULL : vlSelfRef.test__DOT__taketwo__DOT___pulse_count_18);
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_12 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_11));
    if (vlSelfRef.test__DOT__taketwo__DOT___reduceadd_reset_cond_16) {
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_data_16 = 0ULL;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16 
            = vlSelfRef.test__DOT__taketwo__DOT___reduceadd_count_16;
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_data_16 
            = vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16;
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_420 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_419));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_390 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_389));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_168 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_167));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_452 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_451));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_348___05Fdelay_347___05Fdelay_346___05Fdelay_345___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_347___05Fdelay_346___05Fdelay_345___05Fdelay_344___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_319___05Fdelay_318___05Fdelay_317___05Fdelay_316___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_318___05Fdelay_317___05Fdelay_316___05Fdelay_315___05F_eq_215));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_233 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_202 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_302___05Fdelay_301___05Fdelay_300___05Fdelay_299___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_285___05Fdelay_284___05Fdelay_283___05Fdelay_282___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_268___05Fdelay_267___05Fdelay_266___05Fdelay_265___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_233 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_232;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_202 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_201;
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_11) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_2 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_256___05Fdelay_255___05Fdelay_254___05Fdelay_253___05F___05Fvariable_79;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_1 
                = (0x0000007fU & (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_245___05Fdelay_244___05Fdelay_243___05Fdelay_242___05F_plus_190));
            vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid = 1U;
        }
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_302___05Fdelay_301___05Fdelay_300___05Fdelay_299___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_301___05Fdelay_300___05Fdelay_299___05Fdelay_298___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_285___05Fdelay_284___05Fdelay_283___05Fdelay_282___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_284___05Fdelay_283___05Fdelay_282___05Fdelay_281___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_268___05Fdelay_267___05Fdelay_266___05Fdelay_265___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_267___05Fdelay_266___05Fdelay_265___05Fdelay_264___05F_cond_100;
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_297) {
            vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid = 1U;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_297 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_296));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_0 = 0ULL;
    } else if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_11) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_0 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_22;
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_11 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_10));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_419 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_418));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_389 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_388));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_167 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_166));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_451 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_450));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_347___05Fdelay_346___05Fdelay_345___05Fdelay_344___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_346___05Fdelay_345___05Fdelay_344___05Fdelay_343___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_318___05Fdelay_317___05Fdelay_316___05Fdelay_315___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_317___05Fdelay_316___05Fdelay_315___05Fdelay_314___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_296 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_295));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_232 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_201 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_256___05Fdelay_255___05Fdelay_254___05Fdelay_253___05F___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_301___05Fdelay_300___05Fdelay_299___05Fdelay_298___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_284___05Fdelay_283___05Fdelay_282___05Fdelay_281___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_267___05Fdelay_266___05Fdelay_265___05Fdelay_264___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_245___05Fdelay_244___05Fdelay_243___05Fdelay_242___05F_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_22 = 0ULL;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_232 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_231;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_201 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_200;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_256___05Fdelay_255___05Fdelay_254___05Fdelay_253___05F___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_255___05Fdelay_254___05Fdelay_253___05Fdelay_252___05F___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_301___05Fdelay_300___05Fdelay_299___05Fdelay_298___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_300___05Fdelay_299___05Fdelay_298___05Fdelay_297___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_284___05Fdelay_283___05Fdelay_282___05Fdelay_281___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_283___05Fdelay_282___05Fdelay_281___05Fdelay_280___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_267___05Fdelay_266___05Fdelay_265___05Fdelay_264___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_266___05Fdelay_265___05Fdelay_264___05Fdelay_263___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_245___05Fdelay_244___05Fdelay_243___05Fdelay_242___05F_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_244___05Fdelay_243___05Fdelay_242___05Fdelay_241___05F_plus_190;
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_10) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_22 
                = VL_EXTENDS_QI(64,32, vlSelfRef.test__DOT__taketwo__DOT___sra_data_78);
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_10 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_9));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_418 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_417));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_388 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_387));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_166 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_165));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_450 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_449));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_346___05Fdelay_345___05Fdelay_344___05Fdelay_343___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_345___05Fdelay_344___05Fdelay_343___05Fdelay_342___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_317___05Fdelay_316___05Fdelay_315___05Fdelay_314___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_316___05Fdelay_315___05Fdelay_314___05Fdelay_313___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_295 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_9 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_8));
    vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start 
        = __Vdly__test__DOT__taketwo__DOT___acc_0_source_start;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_417 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_416));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_387 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_386));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_165 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_164));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_449 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_448));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_345___05Fdelay_344___05Fdelay_343___05Fdelay_342___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_344___05Fdelay_343___05Fdelay_342___05Fdelay_341___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_316___05Fdelay_315___05Fdelay_314___05Fdelay_313___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_315___05Fdelay_314___05Fdelay_313___05Fdelay_312___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_8 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_7));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_231 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_200 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_255___05Fdelay_254___05Fdelay_253___05Fdelay_252___05F___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_300___05Fdelay_299___05Fdelay_298___05Fdelay_297___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_283___05Fdelay_282___05Fdelay_281___05Fdelay_280___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_266___05Fdelay_265___05Fdelay_264___05Fdelay_263___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_244___05Fdelay_243___05Fdelay_242___05Fdelay_241___05F_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sra_data_78 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_230 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_199 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_254___05Fdelay_253___05Fdelay_252___05Fdelay_251___05F___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_299___05Fdelay_298___05Fdelay_297___05Fdelay_296___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_282___05Fdelay_281___05Fdelay_280___05Fdelay_279___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_265___05Fdelay_264___05Fdelay_263___05Fdelay_262___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_243___05Fdelay_242___05Fdelay_241___05Fdelay_240___05F_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_173___05Fdelay_172___05Fdelay_171___05Fdelay_170___05F___05Fvariable_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_odata_reg_77 = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_231 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_230;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_200 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_199;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_255___05Fdelay_254___05Fdelay_253___05Fdelay_252___05F___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_254___05Fdelay_253___05Fdelay_252___05Fdelay_251___05F___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_300___05Fdelay_299___05Fdelay_298___05Fdelay_297___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_299___05Fdelay_298___05Fdelay_297___05Fdelay_296___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_283___05Fdelay_282___05Fdelay_281___05Fdelay_280___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_282___05Fdelay_281___05Fdelay_280___05Fdelay_279___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_266___05Fdelay_265___05Fdelay_264___05Fdelay_263___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_265___05Fdelay_264___05Fdelay_263___05Fdelay_262___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_244___05Fdelay_243___05Fdelay_242___05Fdelay_241___05F_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_243___05Fdelay_242___05Fdelay_241___05Fdelay_240___05F_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT___sra_data_78 
            = VL_SHIFTRS_III(32,32,5, vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_odata_reg_77, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_173___05Fdelay_172___05Fdelay_171___05Fdelay_170___05F___05Fvariable_60));
        vlSelfRef.test__DOT__taketwo__DOT___tmp_230 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_229;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_199 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_198;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_254___05Fdelay_253___05Fdelay_252___05Fdelay_251___05F___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_253___05Fdelay_252___05Fdelay_251___05Fdelay_250___05F___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_299___05Fdelay_298___05Fdelay_297___05Fdelay_296___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_298___05Fdelay_297___05Fdelay_296___05Fdelay_295___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_282___05Fdelay_281___05Fdelay_280___05Fdelay_279___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_281___05Fdelay_280___05Fdelay_279___05Fdelay_278___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_265___05Fdelay_264___05Fdelay_263___05Fdelay_262___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_264___05Fdelay_263___05Fdelay_262___05Fdelay_261___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_243___05Fdelay_242___05Fdelay_241___05Fdelay_240___05F_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_242___05Fdelay_241___05Fdelay_240___05Fdelay_239___05F_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_173___05Fdelay_172___05Fdelay_171___05Fdelay_170___05F___05Fvariable_60 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_172___05Fdelay_171___05Fdelay_170___05Fdelay_169___05F___05Fvariable_60;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_odata_reg_77 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd1;
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd1 
        = vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd0;
    vlSelfRef.test__DOT__taketwo__DOT___tmp_416 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_415));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_386 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_385));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_164 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_163));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_448 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_447));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_344___05Fdelay_343___05Fdelay_342___05Fdelay_341___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_343___05Fdelay_342___05Fdelay_341___05Fdelay_340___05F_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_315___05Fdelay_314___05Fdelay_313___05Fdelay_312___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_314___05Fdelay_313___05Fdelay_312___05Fdelay_311___05F_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_7 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_6));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd0 
        = (VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___a)), 
                       VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___b))) 
           + VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___c)));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_415 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_414));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_385 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_384));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_163 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_162));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_447 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_446));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_343___05Fdelay_342___05Fdelay_341___05Fdelay_340___05F_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_342___05Fdelay_341___05Fdelay_340___05Fdelay_339_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_314___05Fdelay_313___05Fdelay_312___05Fdelay_311___05F_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_313___05Fdelay_312___05Fdelay_311___05Fdelay_310_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_6 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_5));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___b 
        = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_166___05Fdelay_165___05Fdelay_164___05Fvariable_59;
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___a 
        = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_163___05Fdelay_162___05Fdelay_161___05Fvariable_58;
    vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___c 
        = (0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_160___05Fdelay_159_greatereq_74)
                           ? vlSelfRef.test__DOT__taketwo__DOT___cond_data_71
                           : VL_EXTENDS_II(32,16, (0x0000ffffU 
                                                   & (- vlSelfRef.test__DOT__taketwo__DOT___cond_data_71)))));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_414 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_413));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_384 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_383));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_162 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_161));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_446 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_445));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_342___05Fdelay_341___05Fdelay_340___05Fdelay_339_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_341___05Fdelay_340___05Fdelay_339_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_313___05Fdelay_312___05Fdelay_311___05Fdelay_310_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_312___05Fdelay_311___05Fdelay_310_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_5 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_4));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_160___05Fdelay_159_greatereq_74 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_159_greatereq_74));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_413 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_412));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_383 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_382));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_161 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_160));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_445 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_444));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_341___05Fdelay_340___05Fdelay_339_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_340___05Fdelay_339_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_312___05Fdelay_311___05Fdelay_310_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_311___05Fdelay_310_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_4 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_3));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_229 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_198 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_253___05Fdelay_252___05Fdelay_251___05Fdelay_250___05F___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_298___05Fdelay_297___05Fdelay_296___05Fdelay_295___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_281___05Fdelay_280___05Fdelay_279___05Fdelay_278___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_264___05Fdelay_263___05Fdelay_262___05Fdelay_261___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_242___05Fdelay_241___05Fdelay_240___05Fdelay_239___05F_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_172___05Fdelay_171___05Fdelay_170___05Fdelay_169___05F___05Fvariable_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_228 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_197 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_252___05Fdelay_251___05Fdelay_250___05Fdelay_249___05F___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_297___05Fdelay_296___05Fdelay_295___05Fdelay_294___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_280___05Fdelay_279___05Fdelay_278___05Fdelay_277___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_263___05Fdelay_262___05Fdelay_261___05Fdelay_260___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_241___05Fdelay_240___05Fdelay_239___05Fdelay_238___05F_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_171___05Fdelay_170___05Fdelay_169___05Fdelay_168___05F___05Fvariable_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_227 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_196 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_251___05Fdelay_250___05Fdelay_249___05Fdelay_248___05F___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_296___05Fdelay_295___05Fdelay_294___05Fdelay_293___05F_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_279___05Fdelay_278___05Fdelay_277___05Fdelay_276___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_262___05Fdelay_261___05Fdelay_260___05Fdelay_259___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_240___05Fdelay_239___05Fdelay_238___05Fdelay_237___05F_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_170___05Fdelay_169___05Fdelay_168___05Fdelay_167___05Fvariable_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_226 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_195 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_250___05Fdelay_249___05Fdelay_248___05Fdelay_247___05F___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_295___05Fdelay_294___05Fdelay_293___05Fdelay_292_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_278___05Fdelay_277___05Fdelay_276___05Fdelay_275___05F_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_261___05Fdelay_260___05Fdelay_259___05Fdelay_258___05F_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_239___05Fdelay_238___05Fdelay_237___05Fdelay_236_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_169___05Fdelay_168___05Fdelay_167___05Fvariable_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_166___05Fdelay_165___05Fdelay_164___05Fvariable_59 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_163___05Fdelay_162___05Fdelay_161___05Fvariable_58 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_71 = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_229 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_228;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_198 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_197;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_253___05Fdelay_252___05Fdelay_251___05Fdelay_250___05F___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_252___05Fdelay_251___05Fdelay_250___05Fdelay_249___05F___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_298___05Fdelay_297___05Fdelay_296___05Fdelay_295___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_297___05Fdelay_296___05Fdelay_295___05Fdelay_294___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_281___05Fdelay_280___05Fdelay_279___05Fdelay_278___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_280___05Fdelay_279___05Fdelay_278___05Fdelay_277___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_264___05Fdelay_263___05Fdelay_262___05Fdelay_261___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_263___05Fdelay_262___05Fdelay_261___05Fdelay_260___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_242___05Fdelay_241___05Fdelay_240___05Fdelay_239___05F_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_241___05Fdelay_240___05Fdelay_239___05Fdelay_238___05F_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_172___05Fdelay_171___05Fdelay_170___05Fdelay_169___05F___05Fvariable_60 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_171___05Fdelay_170___05Fdelay_169___05Fdelay_168___05F___05Fvariable_60;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_228 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_227;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_197 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_196;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_252___05Fdelay_251___05Fdelay_250___05Fdelay_249___05F___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_251___05Fdelay_250___05Fdelay_249___05Fdelay_248___05F___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_297___05Fdelay_296___05Fdelay_295___05Fdelay_294___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_296___05Fdelay_295___05Fdelay_294___05Fdelay_293___05F_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_280___05Fdelay_279___05Fdelay_278___05Fdelay_277___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_279___05Fdelay_278___05Fdelay_277___05Fdelay_276___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_263___05Fdelay_262___05Fdelay_261___05Fdelay_260___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_262___05Fdelay_261___05Fdelay_260___05Fdelay_259___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_241___05Fdelay_240___05Fdelay_239___05Fdelay_238___05F_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_240___05Fdelay_239___05Fdelay_238___05Fdelay_237___05F_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_171___05Fdelay_170___05Fdelay_169___05Fdelay_168___05F___05Fvariable_60 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_170___05Fdelay_169___05Fdelay_168___05Fdelay_167___05Fvariable_60;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_227 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_226;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_196 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_195;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_251___05Fdelay_250___05Fdelay_249___05Fdelay_248___05F___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_250___05Fdelay_249___05Fdelay_248___05Fdelay_247___05F___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_296___05Fdelay_295___05Fdelay_294___05Fdelay_293___05F_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_295___05Fdelay_294___05Fdelay_293___05Fdelay_292_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_279___05Fdelay_278___05Fdelay_277___05Fdelay_276___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_278___05Fdelay_277___05Fdelay_276___05Fdelay_275___05F_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_262___05Fdelay_261___05Fdelay_260___05Fdelay_259___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_261___05Fdelay_260___05Fdelay_259___05Fdelay_258___05F_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_240___05Fdelay_239___05Fdelay_238___05Fdelay_237___05F_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_239___05Fdelay_238___05Fdelay_237___05Fdelay_236_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_170___05Fdelay_169___05Fdelay_168___05Fdelay_167___05Fvariable_60 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_169___05Fdelay_168___05Fdelay_167___05Fvariable_60;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_226 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_225;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_195 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_194;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_250___05Fdelay_249___05Fdelay_248___05Fdelay_247___05F___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_249___05Fdelay_248___05Fdelay_247___05Fdelay_246___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_295___05Fdelay_294___05Fdelay_293___05Fdelay_292_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_294___05Fdelay_293___05Fdelay_292_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_278___05Fdelay_277___05Fdelay_276___05Fdelay_275___05F_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_277___05Fdelay_276___05Fdelay_275___05Fdelay_274_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_261___05Fdelay_260___05Fdelay_259___05Fdelay_258___05F_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_260___05Fdelay_259___05Fdelay_258___05Fdelay_257_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_239___05Fdelay_238___05Fdelay_237___05Fdelay_236_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_238___05Fdelay_237___05Fdelay_236_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_169___05Fdelay_168___05Fdelay_167___05Fvariable_60 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_168___05Fdelay_167___05Fvariable_60;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_166___05Fdelay_165___05Fdelay_164___05Fvariable_59 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_165___05Fdelay_164___05Fvariable_59;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_163___05Fdelay_162___05Fdelay_161___05Fvariable_58 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_162___05Fdelay_161___05Fvariable_58;
        vlSelfRef.test__DOT__taketwo__DOT___cond_data_71 
            = (IData)(((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_158_greaterthan_61)
                        ? vlSelfRef.test__DOT__taketwo__DOT___sll_data_65
                        : 0ULL));
    }
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_158_greaterthan_61 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_61));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_159_greatereq_74 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___greatereq_data_74));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_412 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_411));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_382 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_381));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_160 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_159));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_444 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_443));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_340___05Fdelay_339_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_339_eq_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_311___05Fdelay_310_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_310_eq_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_3 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_2));
    vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_61 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (0U < (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_60)));
    vlSelfRef.test__DOT__taketwo__DOT___greatereq_data_74 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && VL_LTES_III(16, 0U, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_58)));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_411 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_410));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_381 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_380));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_159 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_158));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_443 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_442));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_339_eq_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_218));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_310_eq_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_215));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_2 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_1));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_410 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_409));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_380 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_379));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_158 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_157));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_442 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_441));
    vlSelfRef.test__DOT__taketwo__DOT___eq_data_218 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_132)));
    vlSelfRef.test__DOT__taketwo__DOT___eq_data_215 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_132)));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_225 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_194 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_249___05Fdelay_248___05Fdelay_247___05Fdelay_246___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_294___05Fdelay_293___05Fdelay_292_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_277___05Fdelay_276___05Fdelay_275___05Fdelay_274_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_260___05Fdelay_259___05Fdelay_258___05Fdelay_257_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_238___05Fdelay_237___05Fdelay_236_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_168___05Fdelay_167___05Fvariable_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_165___05Fdelay_164___05Fvariable_59 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_162___05Fdelay_161___05Fvariable_58 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_65 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_224 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_193 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_248___05Fdelay_247___05Fdelay_246___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_293___05Fdelay_292_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_276___05Fdelay_275___05Fdelay_274_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_259___05Fdelay_258___05Fdelay_257_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_237___05Fdelay_236_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_167___05Fvariable_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_164___05Fvariable_59 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_161___05Fvariable_58 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___minus_data_63 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_223 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_192 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_247___05Fdelay_246___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_292_plus_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_275___05Fdelay_274_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_258___05Fdelay_257_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_236_plus_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_59 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_60 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_58 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_222 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_191 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_246___05Fvariable_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_209 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_274_cond_107 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_257_cond_100 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_190 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_224_reinterpretcast_152 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_174 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_221 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_190 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_132 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_79 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_123 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_131 = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_225 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_224;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_194 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_193;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_249___05Fdelay_248___05Fdelay_247___05Fdelay_246___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_248___05Fdelay_247___05Fdelay_246___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_294___05Fdelay_293___05Fdelay_292_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_293___05Fdelay_292_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_277___05Fdelay_276___05Fdelay_275___05Fdelay_274_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_276___05Fdelay_275___05Fdelay_274_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_260___05Fdelay_259___05Fdelay_258___05Fdelay_257_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_259___05Fdelay_258___05Fdelay_257_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_238___05Fdelay_237___05Fdelay_236_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_237___05Fdelay_236_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_168___05Fdelay_167___05Fvariable_60 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_167___05Fvariable_60;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_165___05Fdelay_164___05Fvariable_59 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_164___05Fvariable_59;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_162___05Fdelay_161___05Fvariable_58 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_161___05Fvariable_58;
        vlSelfRef.test__DOT__taketwo__DOT___sll_data_65 
            = (0x00000003ffffffffULL & (1ULL << (IData)(vlSelfRef.test__DOT__taketwo__DOT___minus_data_63)));
        vlSelfRef.test__DOT__taketwo__DOT___tmp_224 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_223;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_193 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_192;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_248___05Fdelay_247___05Fdelay_246___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_247___05Fdelay_246___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_293___05Fdelay_292_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_292_plus_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_276___05Fdelay_275___05Fdelay_274_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_275___05Fdelay_274_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_259___05Fdelay_258___05Fdelay_257_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_258___05Fdelay_257_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_237___05Fdelay_236_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_236_plus_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_167___05Fvariable_60 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_60;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_164___05Fvariable_59 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_59;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_161___05Fvariable_58 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_58;
        vlSelfRef.test__DOT__taketwo__DOT___minus_data_63 
            = (0x0000001fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_60) 
                              - (IData)(1U)));
        vlSelfRef.test__DOT__taketwo__DOT___tmp_223 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_222;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_192 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_191;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_247___05Fdelay_246___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_246___05Fvariable_79;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_292_plus_209 
            = vlSelfRef.test__DOT__taketwo__DOT___plus_data_209;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_275___05Fdelay_274_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_274_cond_107;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_258___05Fdelay_257_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_257_cond_100;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_236_plus_190 
            = vlSelfRef.test__DOT__taketwo__DOT___plus_data_190;
        if (vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_1) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_59 
                = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_224_reinterpretcast_152;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_60 
                = (0x0000001fU & (IData)(vlSelfRef.test__DOT__taketwo__DOT___plus_data_174));
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_58 
                = ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_223_pointer_153)
                    ? 0U : ((IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_138)
                             ? ((IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_134)
                                 ? (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133)
                                 : 0U) : 0U));
        }
        vlSelfRef.test__DOT__taketwo__DOT___tmp_222 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_221;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_191 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_190;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_246___05Fvariable_79 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_79;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_209 
            = (0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_123) 
                              + (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_131)));
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_274_cond_107 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_102;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_257_cond_100 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_95;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_190 
            = (0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_116) 
                              + (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_130)));
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_224_reinterpretcast_152 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_147;
        vlSelfRef.test__DOT__taketwo__DOT___plus_data_174 
            = (0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_109) 
                              + (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_129)));
        vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133 
            = vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_133;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_221 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_220;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_190 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_189;
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_132 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_19_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_79 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_0_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_123 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_empty_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_131 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_18_next_parameter_data;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___eq_data_134 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_80))));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_1 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_stream_ivalid));
    vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_223_pointer_153 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_82));
    vlSelfRef.test__DOT__taketwo__DOT___eq_data_138 
        = ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
           && (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_81))));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_409 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_408));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_379 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_378));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_157 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_156));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_441 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_440));
}

void Vout___024root___nba_sequent__TOP__1(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___nba_sequent__TOP__1\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.test__DOT__taketwo__DOT___tmp_408 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_378 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_377));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_156 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_155));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_440 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_439));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_102 = 0U;
    } else if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_102 
            = ((2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel))
                ? vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_0_rdata_out
                : 0U);
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_0_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem
            [((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable)
               ? (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_raddr)
               : 0U)];
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_95 = 0U;
    } else if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_95 
            = ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel))
                ? vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_0_rdata_out
                : 0U);
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_0_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem
            [((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable)
               ? (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_raddr)
               : 0U)];
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_116 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_130 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_147 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_109 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_129 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_80 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_stream_ivalid = 0U;
    } else {
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_116 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_empty_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_130 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_17_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_109 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_empty_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_129 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_16_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_80 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_1_next_parameter_data;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_147 
                = ((4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel))
                    ? (0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_146)
                                       ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_0_rdata_out)
                                       : (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_0_rdata_out)))
                    : 0U);
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_363) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_stream_ivalid = 1U;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___tmp_373) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_stream_ivalid = 0U;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_373 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_363 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_362));
    if (vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem[vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0;
    }
    if (vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem[vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_0_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem
            [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_addr];
    }
    if (vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem[vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_0_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem
            [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_addr];
    }
    if (vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem[vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_82 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_81 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_133 = 0U;
    } else {
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_82 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_3_next_parameter_data;
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_81 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_2_next_parameter_data;
        }
        if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy) {
            vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_133 
                = ((3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel))
                    ? (0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_137)
                                       ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_0_rdata_out)
                                       : (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_0_rdata_out)))
                    : 0U);
        }
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_0_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem
            [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_addr];
    }
    if (vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem[vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_0_rdata_out 
            = vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem
            [vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_addr];
    }
    if (vlSelfRef.__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0) {
        vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem[vlSelfRef.__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0;
    }
    vlSelfRef.test__DOT__taketwo__DOT___tmp_377 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_155 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_154));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_439 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy));
    if (vlSelfRef.test__DOT__taketwo__DOT__RST) {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_220 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_189 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_19_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_0_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_empty_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_18_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_empty_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_17_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_146 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_empty_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_16_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_1_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_3_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_2_next_parameter_data = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_137 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_219 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_188 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_raddr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_raddr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_218 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_187 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset_buf = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset_buf = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset_buf = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset_buf = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3 = 0ULL;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_val = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_2 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_3 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_1 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_0 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_2 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_3 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_1 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_0 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_2 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_3 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_1 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_0 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_2 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_3 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_1 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_0 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_out_local_col = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_buf_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select_buf = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count_buf = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_pad_masks = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_start = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_base_offset = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_row = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_val = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_col = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_row = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_och = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_page = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_dma_offset = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_laddr_offset = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_out_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_write_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_out_write_size = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_row_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_bat_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_och_count = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_row_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_bat_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_och_count = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_col_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_row_count = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_filter = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_act = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_comp = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_write_out = 1U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index = 0U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___tmp_220 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_219;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_189 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_188;
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable) 
             & (4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel)))) {
            vlSelfRef.test__DOT__taketwo__DOT___tmp_146 
                = (1U & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr);
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable) 
             & (3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel)))) {
            vlSelfRef.test__DOT__taketwo__DOT___tmp_137 
                = (1U & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr);
        }
        vlSelfRef.test__DOT__taketwo__DOT___tmp_219 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_218;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_188 
            = vlSelfRef.test__DOT__taketwo__DOT___tmp_187;
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable = 0U;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable = 1U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable = 0U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable = 0U;
        }
        vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable = 0U;
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable = 1U;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable = 0U;
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable = 0U;
        }
        vlSelfRef.test__DOT__taketwo__DOT___tmp_218 
            = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops;
        vlSelfRef.test__DOT__taketwo__DOT___tmp_187 
            = (0x00000001ffffffffULL & ((QData)((IData)(
                                                        (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_col 
                                                         + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_val))) 
                                        + (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset_buf))));
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 = 0U;
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_raddr 
                = (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset_buf 
                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 
                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 
                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 
                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3))));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode))))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_0 
                                            - 1ULL));
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 
                                            - 1ULL));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_1 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_2 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_3 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_3;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_3;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
              & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0)) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
             & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
              & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
             & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1)) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1) 
              & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3 
                                            - 1ULL));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 = 0U;
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_raddr 
                = (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset_buf 
                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 
                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 
                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 
                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3))));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode))))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_0 
                                            - 1ULL));
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 
                                            - 1ULL));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_1 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_2 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_3 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_3;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_3;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
              & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0)) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
             & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
              & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
             & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1)) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0) 
              & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3 
                                            - 1ULL));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 = 0U;
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr 
                = (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset_buf 
                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 
                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 
                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 
                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3))));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode))))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_0 
                                            - 1ULL));
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 
                                            - 1ULL));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_1 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_2 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_3 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_3;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_3;
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
              & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0)) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
             & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
              & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
             & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1)) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3) 
              & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3 
                                            - 1ULL));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 = 0U;
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr 
                = (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset_buf 
                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 
                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 
                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 
                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3))));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode))))) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset_buf 
                = vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_0 
                                            - 1ULL));
        }
        if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 
                                            - 1ULL));
        }
        if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) 
             & (0U != (2U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode))))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_1 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_2 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_3 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_1;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_2;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_3;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3 
                = vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_3;
        }
        if ((3U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_19_next_parameter_data 
                = ((0U != (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index)) 
                   & (1U != (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index)));
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_0_next_parameter_data 
                = (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51);
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_empty_data = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_18_next_parameter_data 
                = ((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                    ? 0x1eU : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                ? 0x1dU : 0x1eU));
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_empty_data = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_17_next_parameter_data = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_empty_data = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_16_next_parameter_data = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_1_next_parameter_data 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_3_next_parameter_data 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_pad_masks;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_2_next_parameter_data 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select_buf;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel = 4U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel = 3U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_2 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_3 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_0 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_1 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_2 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_3 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_1 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops));
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_0 
                = (QData)((IData)((0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)));
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_2 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_3 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_0 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_2 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_3 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode = 2U;
            if ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och))) {
                vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_1 = 0U;
                vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset = 0U;
            } else {
                vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_1 = 1U;
                vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset 
                    = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count_buf;
            }
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_1 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops));
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_0 
                = (QData)((IData)((0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)));
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_2 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_3 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_0 = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_2 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_3 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_1 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops));
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_0 
                = (QData)((IData)((0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)));
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_1 
                = (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51);
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset_buf;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_2 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_3 = 1ULL;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_0 = 1U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_1 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_2 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_3 = 0U;
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode = 2U;
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_1 
                = (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops));
            vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_0 
                = (QData)((IData)((0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)));
            vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 
                   + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_buf_0);
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0 
                                            - 1ULL));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
              & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0)) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
             & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
              & ((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2 
                                            - 1ULL));
        }
        if (((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
             & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1)) 
                & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2)))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 
                = (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 
                   + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 
                                            - 1ULL));
        }
        if ((((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2) 
              & (((0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0) 
                  & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1)) 
                 & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2))) 
             & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3))) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 
                = (0x00000001ffffffffULL & (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3 
                                            - 1ULL));
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            if (((0x00000013U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_comp)))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_out_local_col = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_count = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select = 0U;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset_buf 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_buf_0 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset_buf 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count_buf 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select_buf 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count_buf 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops 
                = vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 2U;
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_pad_masks 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_pad_mask_0_0;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 3U;
        } else if ((3U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 4U;
        } else if ((4U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            if ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy)))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 5U;
            }
        } else if ((5U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 6U;
            }
        } else if ((6U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_out_local_col 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_col 
                   + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_count 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_count);
            if ((! ((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select)
                     ? 0U : 0U))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 
                       + (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51));
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 2U;
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select)
                  ? 0U : 0U)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 
                       + (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51));
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_out_local_col = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_count = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select;
            if ((1U <= (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select 
                    = (1U & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select) 
                             - (IData)(1U)));
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select = 0U;
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm)) {
            if ((4U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_start = 1U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm = 1U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm)) {
            if (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_start = 0U;
                vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy = 1U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm = 2U;
            }
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm = 3U;
        } else if ((3U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm)) {
            if (((((((((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle) 
                       & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle)) 
                      & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle)) 
                     & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle)) 
                    & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle)) 
                   & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle)) 
                  & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle)) 
                 & (3U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm))) {
                vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm = 0U;
            }
            if ((((((((((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle) 
                        & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle)) 
                       & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle)) 
                      & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle)) 
                     & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle)) 
                    & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle)) 
                   & (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle)) 
                  & (3U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm)) 
                 & (4U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_start = 1U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm = 1U;
            }
        }
        if (((((((((0U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
                   | (1U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                  | (2U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                 | (3U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                | (4U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
               | (5U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
              | (6U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
             | (7U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11))) {
            if ((0U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if ((0x0000000fU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                    vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called = 1U;
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 1U;
                }
                if ((0x00000019U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                    vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called = 1U;
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 1U;
                }
                if ((0x00000023U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                    vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called = 1U;
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 1U;
                }
            } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 2U;
            } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_base_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_row = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0 = 1U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_val = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_col = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_row = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_och = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_page = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_dma_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_laddr_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_out_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_write_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_out_write_size 
                    = vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_row_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_bat_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_och_count = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_row_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_bat_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_och_count = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_col_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_row_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_filter = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_act = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_comp = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_write_out = 1U;
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 3U;
                }
            } else if ((3U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 4U;
                }
            } else if ((4U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 5U;
                }
            } else if ((5U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 6U;
                }
            } else if ((6U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 7U;
            } else {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 8U;
                if (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_filter) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000bU;
                }
            }
        } else if (((((((((8U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
                          | (9U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                         | (0x0000000aU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                        | (0x0000000bU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                       | (0x0000000cU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                      | (0x0000000dU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                     | (0x0000000eU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                    | (0x0000000fU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11))) {
            if ((8U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 9U;
                }
            } else if ((9U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000aU;
                }
            } else if ((0x0000000aU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000bU;
            } else if ((0x0000000bU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000cU;
            } else if ((0x0000000cU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000dU;
                if (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_act) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000011U;
                }
            } else if ((0x0000000dU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000eU;
                if ((1U & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_dma_pad_mask_0) 
                           | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_dma_flag_0))))) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000010U;
                }
            } else if ((0x0000000eU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000fU;
                }
            } else if (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000010U;
            }
        } else if (((((((((0x00000010U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11) 
                          | (0x00000011U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                         | (0x00000012U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                        | (0x00000013U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                       | (0x00000014U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                      | (0x00000015U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                     | (0x00000016U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) 
                    | (0x00000017U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11))) {
            if ((0x00000010U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000011U;
            } else if ((0x00000011U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000012U;
            } else if ((0x00000012U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000013U;
                }
            } else if ((0x00000013U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if ((0U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000014U;
                }
            } else if ((0x00000014U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000015U;
                if (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_write_out) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000001aU;
                }
            } else if ((0x00000015U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if ((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_comp_count 
                     >= ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_out_count))) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000016U;
                }
            } else if ((0x00000016U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                if ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_out_mask_0)))) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000017U;
                }
                if (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_out_mask_0) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000018U;
                }
            } else if (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000018U;
            }
        } else if ((0x00000018U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000019U;
        } else if ((0x00000019U == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_write_count 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_write_count);
            if ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_keep_filter)))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
                       + (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step));
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_col_count 
                    = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_col_count);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x00000014U;
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_out_count 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_out_count);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_ram_select);
            if ((0U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_ram_select)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_laddr_offset 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_laddr_offset 
                       + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select = 0U;
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_out_count 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_out_count);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000001aU;
        } else if ((0x0000001aU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_base_offset 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_base_offset 
                   + ((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                       ? 0x0200U : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                     ? 0x0200U : 0x0080U)));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_och_count 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count 
                   + ((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                       ? 0x40U : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                   ? 4U : 8U)));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_row 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row 
                   + (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_act_row_step));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
                   + (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_act_row_step));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset 
                   + (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52));
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0 = 1U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_row_count 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count);
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_bat_count 
                = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_bat_count);
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select = 0U;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select = 0U;
            if (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_next_dma_flag_0) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 
                       + (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51));
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 
                       + (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51));
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_out_write_size 
                = vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size;
            if ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_write_out)))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_write_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_laddr_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
                       + (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step));
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_row_count 
                    = ((IData)(1U) + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_row_count);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_col = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_col_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
                       + (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step));
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_row = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_row_count = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_och 
                    = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och 
                       + ((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                           ? 0x80U : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                       ? 8U : 4U)));
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat = 0U;
            }
            if ((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page)))) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset = 0x00000100U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_dma_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_page = 1U;
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset 
                = (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset 
                   + (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52));
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_row = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat = 0U;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0 = 1U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_row_count = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_bat_count = 0U;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select = 0U;
            vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select = 0U;
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_next_dma_flag_0) 
                 & (0x00000200U < ((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 
                                    + (0x0000007fU 
                                       & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)) 
                                   + (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51))))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 = 0U;
            }
            if (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset = 0U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_dma_offset = 0x00000100U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_page = 0U;
            }
            if ((0x00000200U < ((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset 
                                 + (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52)) 
                                + (0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52)))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset = 0U;
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 = 0U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 = 0U;
            if (((((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_write_out) 
                   & (0U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_count)) 
                  & (0U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_bat_count)) 
                 & (0U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_och_count))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_write_out = 0U;
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000000cU;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 7U;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_row_count 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count;
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_bat_count 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_bat_count;
            if (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_write_out)) 
                 & (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_och_count 
                    >= (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_max_och_count)))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000001bU;
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_och_count 
                = vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count;
            if ((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count 
                 >= (IData)(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_max_och_count))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_filter = 1U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_act = 1U;
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_comp = 1U;
            }
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_act = 1U;
        } else if ((0x0000001bU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle) 
                 & (~ ((0U < (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)) 
                       | (IData)(vlSelfRef.test__DOT__maxi_awvalid))))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0x0000001cU;
            }
        } else if ((0x0000001cU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
            if ((0x00000012U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0U;
            }
            if ((0x0000001cU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0U;
            }
            if ((0x00000026U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0U;
            }
        }
        if (((((((((0U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm) 
                   | (1U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                  | (2U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                 | (3U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                | (4U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
               | (5U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
              | (6U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
             | (7U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm))) {
            if ((0U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                if ((0U != vlSelfRef.test__DOT__taketwo__DOT___saxi_register_4)) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 1U;
                }
            } else {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm 
                    = ((1U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)
                        ? 2U : ((2U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)
                                 ? 3U : ((3U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)
                                          ? 4U : ((4U 
                                                   == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)
                                                   ? 5U
                                                   : 
                                                  ((5U 
                                                    == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)
                                                    ? 6U
                                                    : 
                                                   ((6U 
                                                     == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)
                                                     ? 7U
                                                     : 8U))))));
            }
        } else if (((((((((8U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm) 
                          | (9U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                         | (0x0000000aU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                        | (0x0000000bU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                       | (0x0000000cU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                      | (0x0000000dU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                     | (0x0000000eU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                    | (0x0000000fU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm))) {
            if ((8U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 9U;
            } else if ((9U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr 
                    = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000000aU;
            } else if ((0x0000000aU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 
                    = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_35;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000000bU;
            } else if ((0x0000000bU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 
                    = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000000cU;
            } else if ((0x0000000cU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2 
                    = ((IData)(0x00000200U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000000dU;
            } else if ((0x0000000dU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3 
                    = ((IData)(0x00000300U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000000eU;
            } else if ((0x0000000eU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index = 0U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000000fU;
            } else {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000010U;
            }
        } else if (((((((((0x00000010U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm) 
                          | (0x00000011U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                         | (0x00000012U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                        | (0x00000013U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                       | (0x00000014U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                      | (0x00000015U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                     | (0x00000016U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                    | (0x00000017U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm))) {
            if ((0x00000010U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000011U;
            } else if ((0x00000011U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                if ((0x0000001cU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000012U;
                }
            } else if ((0x00000012U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000013U;
            } else if ((0x00000013U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr 
                    = ((IData)(0x00000080U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000014U;
            } else if ((0x00000014U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 
                    = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000015U;
            } else if ((0x00000015U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 
                    = ((IData)(0x00000340U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000016U;
            } else if ((0x00000016U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2 
                    = ((IData)(0x00001340U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000017U;
            } else {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3 
                    = ((IData)(0x000013c0U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000018U;
            }
        } else if (((((((((0x00000018U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm) 
                          | (0x00000019U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                         | (0x0000001aU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                        | (0x0000001bU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                       | (0x0000001cU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                      | (0x0000001dU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                     | (0x0000001eU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                    | (0x0000001fU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm))) {
            if ((0x00000018U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index = 1U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000019U;
            } else if ((0x00000019U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000001aU;
            } else if ((0x0000001aU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000001bU;
            } else if ((0x0000001bU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                if ((0x0000001cU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000001cU;
                }
            } else if ((0x0000001cU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000001dU;
            } else if ((0x0000001dU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr 
                    = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_34;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000001eU;
            } else if ((0x0000001eU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 
                    = ((IData)(0x00000080U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000001fU;
            } else {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 
                    = ((IData)(0x00001400U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000020U;
            }
        } else if (((((((((0x00000020U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm) 
                          | (0x00000021U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                         | (0x00000022U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                        | (0x00000023U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                       | (0x00000024U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                      | (0x00000025U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                     | (0x00000026U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) 
                    | (0x00000027U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm))) {
            if ((0x00000020U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2 
                    = ((IData)(0x00001480U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000021U;
            } else if ((0x00000021U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3 
                    = ((IData)(0x000014c0U) + vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36);
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000022U;
            } else if ((0x00000022U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index = 2U;
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000023U;
            } else if ((0x00000023U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000024U;
            } else if ((0x00000024U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000025U;
            } else if ((0x00000025U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
                if ((0x0000001cU == vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11)) {
                    vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000026U;
                }
            } else {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm 
                    = ((0x00000026U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)
                        ? 0x00000027U : 0x00000028U);
            }
        } else if ((0x00000028U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x00000029U;
        } else if ((0x00000029U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000002aU;
        } else if ((0x0000002aU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0x0000002bU;
        } else if ((0x0000002bU == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm = 0U;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable) 
           & (2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel)));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable) 
           & (1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel)));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_362 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_361));
    vlSelfRef.test__DOT__taketwo__DOT___tmp_154 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (3U 
                                                       == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable) 
           & (4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel)));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_addr 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable)
            ? (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr 
                              >> 1U)) : 0U);
    vlSelfRef.test__DOT__taketwo__DOT___tmp_361 = (
                                                   (1U 
                                                    & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__RST))) 
                                                   && (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable) 
           & (3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel)));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_addr 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable)
            ? (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr 
                              >> 1U)) : 0U);
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3;
    vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_col 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_out_local_col;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_col_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_pad_mask_0_0 
        = ((1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_count) 
           | (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count_buf));
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_start;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_page;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_out_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_out_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_write_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_write_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_bat_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_bat_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_row_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_bat_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_bat_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_och_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_och_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_col_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_col_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_ram_select 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_filter 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_filter;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_act 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_act;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_write_out 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_write_out;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_comp_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_comp_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_laddr_offset 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_laddr_offset;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_col;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_base_offset 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_base_offset;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_och_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_row;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_row;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_och;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_next_out_write_size;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_row_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_out_row_count;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_row_count;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___maxi_outstanding_wcount;
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle 
        = (1U & (~ ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_busy) 
                    | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start))));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle 
        = (1U & (~ ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_busy) 
                    | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start))));
    vlSelfRef.test__DOT__maxi_awvalid = vlSelfRef.__Vdly__test__DOT__maxi_awvalid;
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy) 
           | ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy_reg) 
              | (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_469)));
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle) 
           & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle) 
              & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle) 
                 & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle) 
                    & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle) 
                       & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle) 
                          & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle) 
                             & (3U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm))))))));
    vlSelfRef.test__DOT__taketwo__DOT___dma_write_packed_local_packed_size_473 
        = (VL_SHIFTR_III(32,32,32, vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size, 1U) 
           + (1U & vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size));
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_out_mask_0 
        = (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_row_count);
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_dma_flag_0 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select)) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0));
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_next_dma_flag_0 
        = (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)));
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_dma_pad_mask_0 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)) 
           & (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)));
    vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_1 
        = ((0x0000000bU == vlSelfRef.test__DOT___memory_waddr_fsm) 
           & ((IData)(vlSelfRef.test__DOT__maxi_awvalid) 
              & (IData)(vlSelfRef.test__DOT__memory_awready)));
    vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
           & ((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
              & (((~ (IData)(vlSelfRef.test__DOT__maxi_awvalid)) 
                  | (IData)(vlSelfRef.test__DOT__memory_awready)) 
                 & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)))));
    vlSelfRef.test__DOT___memory_wreq_fifo_enq = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_1) 
                                                  & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_almost_full)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_enq 
        = (1U & ((IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44)
                  ? ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
                     & (IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44))
                  : ((IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43)
                      ? ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
                         & (IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43))
                      : 0U)));
    vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__control_matmul_11;
    if ((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))) {
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och = 0x40U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_max_och_count = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_act_row_step = 8U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step = 0x80U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size = 0x40U;
        vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51 = 4U;
        vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52 = 0x00000100U;
    } else if ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))) {
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och = 0x20U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_max_och_count = 0x1cU;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_act_row_step = 0x80U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step = 0x40U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size = 4U;
        vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51 = 0x00000040U;
        vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52 = 0x00000100U;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och = 2U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_max_och_count = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_act_row_step = 0x40U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step = 4U;
        vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size = 2U;
        vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51 = 0x00000020U;
        vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52 = 0x00000040U;
    }
    vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_keep_filter 
        = ((1U != (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index)) 
           | (0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index)));
    vlSelfRef.test__DOT__taketwo__DOT__RST = (((IData)(vlSelfRef.test__DOT__taketwo__DOT__rst_logic) 
                                               | (IData)(vlSelfRef.test__DOT__taketwo__DOT___rst_logic_1)) 
                                              | (IData)(vlSelfRef.test__DOT__taketwo__DOT___rst_logic_2));
    vlSelfRef.test__DOT__taketwo__DOT___rst_logic_2 
        = vlSelfRef.test__DOT__taketwo__DOT___rst_logic_1;
    if (vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) {
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33 = 0x00001580U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_35 = 0x00000040U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36 = 0x00000080U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_34 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT___saxi_register_4 = 0U;
        vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45 = 0U;
        vlSelfRef.__Vdly__test__DOT__saxi_bvalid = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__writevalid_41 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__readvalid_42 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__addr_40 = 0U;
    } else {
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x21U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x21U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x23U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_35 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x23U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_35 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x24U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x24U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (0x22U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_34 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (0x22U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_34 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if (((((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
               & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                  | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid)))) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47)) 
             & (4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_4 
                = vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48;
        }
        if ((((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45)))) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_4 
                = (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39);
        }
        if ((2U == vlSelfRef.test__DOT__taketwo__DOT__main_fsm)) {
            vlSelfRef.test__DOT__taketwo__DOT___saxi_register_4 = 0U;
        }
        if ((0U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm)) {
            if (((IData)(vlSelfRef.test__DOT__taketwo__DOT__readvalid_42) 
                 | (IData)(vlSelfRef.test__DOT__taketwo__DOT__writevalid_41))) {
                vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45 
                    = (0x0000003fU & (vlSelfRef.test__DOT__taketwo__DOT__addr_40 
                                      >> 2U));
            }
            if (vlSelfRef.test__DOT__taketwo__DOT__readvalid_42) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 1U;
            }
            if (vlSelfRef.test__DOT__taketwo__DOT__writevalid_41) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 3U;
            }
        } else if ((1U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm)) {
            if ((1U & ((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                       | (~ (IData)(vlSelfRef.test__DOT__saxi_rvalid))))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 2U;
            }
        } else if ((2U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm)) {
            if (((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)) 
                 & (IData)(vlSelfRef.test__DOT__saxi_rvalid))) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 0U;
            }
        } else if ((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm)) {
            if (vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 4U;
            }
        } else if ((4U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm)) {
            if (vlSelfRef.test__DOT__saxi_bvalid) {
                vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 0U;
            }
        }
        if (vlSelfRef.test__DOT__saxi_bvalid) {
            vlSelfRef.__Vdly__test__DOT__saxi_bvalid = 0U;
        }
        if (((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40) 
             & (3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm))) {
            vlSelfRef.__Vdly__test__DOT__saxi_bvalid = 1U;
        }
        vlSelfRef.test__DOT__taketwo__DOT__writevalid_41 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__readvalid_42 = 0U;
        if ((((IData)(vlSelfRef.test__DOT__saxi_awready) 
              & (IData)(vlSelfRef.test__DOT___saxi_awvalid)) 
             & (~ (IData)(vlSelfRef.test__DOT__saxi_bvalid)))) {
            vlSelfRef.test__DOT__taketwo__DOT__addr_40 
                = vlSelfRef.test__DOT___saxi_awaddr;
            vlSelfRef.test__DOT__taketwo__DOT__writevalid_41 = 1U;
        } else if (((IData)(vlSelfRef.test__DOT__saxi_arready) 
                    & (IData)(vlSelfRef.test__DOT___saxi_arvalid))) {
            vlSelfRef.test__DOT__taketwo__DOT__addr_40 
                = vlSelfRef.test__DOT___saxi_araddr;
            vlSelfRef.test__DOT__taketwo__DOT__readvalid_42 = 1U;
        }
    }
    vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_101 
        = (0x0000007fU & (VL_SHIFTR_III(7,7,32, (0x0000007fU 
                                                 & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51), 1U) 
                          + (1U & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)));
    vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_88 
        = (0x000001ffU & (VL_SHIFTR_III(9,9,32, (0x000001ffU 
                                                 & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52), 1U) 
                          + (1U & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52)));
    vlSelfRef.test__DOT__taketwo__DOT__main_fsm = vlSelfRef.__Vdly__test__DOT__taketwo__DOT__main_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___rst_logic_1 
        = vlSelfRef.test__DOT__taketwo__DOT__rst_logic;
    if (vlSelfRef.test__DOT__RESETN) {
        if ((1U & ((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
                   | (~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40))))) {
            vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39 
                = vlSelfRef.test__DOT___sb___05Fsaxi_writedata_next_data_44;
            vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_valid_40 
                = vlSelfRef.test__DOT___sb___05Fsaxi_writedata_next_valid_45;
        }
        if ((((~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)) 
              & (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40)) 
             & (3U != vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm))) {
            vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_data_42 
                = vlSelfRef.test__DOT___sb___05Fsaxi_writedata_s_data_36;
            vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 
                = vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0;
        }
        if (((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43) 
             & (3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm))) {
            vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 = 0U;
        }
        if (vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_0_1) {
            vlSelfRef.__Vdly__test__DOT___saxi_arvalid = 0U;
        }
        if (vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_1_1) {
            vlSelfRef.__Vdly__test__DOT___saxi_arvalid = 0U;
        }
        if (((0x0000000fU == vlSelfRef.test__DOT__th_ctrl) 
             & ((IData)(vlSelfRef.test__DOT__saxi_arready) 
                | (~ (IData)(vlSelfRef.test__DOT___saxi_arvalid))))) {
            vlSelfRef.test__DOT___saxi_araddr = 0x00000010U;
            vlSelfRef.__Vdly__test__DOT___saxi_arvalid = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT___saxi_arvalid) 
             & (~ (IData)(vlSelfRef.test__DOT__saxi_arready)))) {
            vlSelfRef.__Vdly__test__DOT___saxi_arvalid 
                = vlSelfRef.test__DOT___saxi_arvalid;
        }
        if (((0x00000014U == vlSelfRef.test__DOT__th_ctrl) 
             & ((IData)(vlSelfRef.test__DOT__saxi_arready) 
                | (~ (IData)(vlSelfRef.test__DOT___saxi_arvalid))))) {
            vlSelfRef.test__DOT___saxi_araddr = 0x00000014U;
            vlSelfRef.__Vdly__test__DOT___saxi_arvalid = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT___saxi_arvalid) 
             & (~ (IData)(vlSelfRef.test__DOT__saxi_arready)))) {
            vlSelfRef.__Vdly__test__DOT___saxi_arvalid 
                = vlSelfRef.test__DOT___saxi_arvalid;
        }
        if (vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_0_1) {
            vlSelfRef.__Vdly__test__DOT___saxi_awvalid = 0U;
        }
        if (vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_1_1) {
            vlSelfRef.__Vdly__test__DOT___saxi_awvalid = 0U;
        }
        if (((4U == vlSelfRef.test__DOT__th_ctrl) & 
             ((0U == (IData)(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount)) 
              & ((IData)(vlSelfRef.test__DOT__saxi_awready) 
                 | (~ (IData)(vlSelfRef.test__DOT___saxi_awvalid)))))) {
            vlSelfRef.test__DOT___saxi_awaddr = 0x00000084U;
            vlSelfRef.__Vdly__test__DOT___saxi_awvalid = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT___saxi_awvalid) 
             & (~ (IData)(vlSelfRef.test__DOT__saxi_awready)))) {
            vlSelfRef.__Vdly__test__DOT___saxi_awvalid 
                = vlSelfRef.test__DOT___saxi_awvalid;
        }
        if (((0x0000000aU == vlSelfRef.test__DOT__th_ctrl) 
             & ((0U == (IData)(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount)) 
                & ((IData)(vlSelfRef.test__DOT__saxi_awready) 
                   | (~ (IData)(vlSelfRef.test__DOT___saxi_awvalid)))))) {
            vlSelfRef.test__DOT___saxi_awaddr = 0x00000010U;
            vlSelfRef.__Vdly__test__DOT___saxi_awvalid = 1U;
        }
        if (((IData)(vlSelfRef.test__DOT___saxi_awvalid) 
             & (~ (IData)(vlSelfRef.test__DOT__saxi_awready)))) {
            vlSelfRef.__Vdly__test__DOT___saxi_awvalid 
                = vlSelfRef.test__DOT___saxi_awvalid;
        }
    } else {
        vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39 = 0ULL;
        vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_valid_40 = 0U;
        vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_data_42 = 0ULL;
        vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 = 0U;
        vlSelfRef.test__DOT___saxi_araddr = 0U;
        vlSelfRef.__Vdly__test__DOT___saxi_arvalid = 0U;
        vlSelfRef.test__DOT___saxi_awaddr = 0U;
        vlSelfRef.__Vdly__test__DOT___saxi_awvalid = 0U;
    }
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_s_data_36 
        = (((QData)((IData)(vlSelfRef.test__DOT_____05Fsaxi_wstrb_sb_0)) 
            << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT_____05Fsaxi_wdata_sb_0)));
    vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0 = vlSelfRef.__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0;
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 
        = vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_tmp_valid_43;
    vlSelfRef.test__DOT__saxi_rvalid = vlSelfRef.__Vdly__test__DOT__saxi_rvalid;
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 
        = vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_readdata_tmp_valid_56;
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_next_valid_45 
        = ((IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0) 
           | (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43));
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_next_data_44 
        = ((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)
            ? vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_data_42
            : vlSelfRef.test__DOT___sb___05Fsaxi_writedata_s_data_36);
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_next_valid_58 
        = ((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56) 
           | (IData)(vlSelfRef.test__DOT__saxi_rvalid));
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_next_data_57 
        = ((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)
            ? vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_data_55
            : vlSelfRef.test__DOT__saxi_rdata);
    if ((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_0;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_0));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_0;
    } else if ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_1;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_1));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_1;
    } else if ((2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_2;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_2));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_2;
    } else if ((3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_3;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_3));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_3;
    } else if ((4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_4;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_4));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_4;
    } else if ((5U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_5));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_5;
    } else if ((6U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_6));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_6;
    } else if ((7U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_7));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_7;
    } else if ((8U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_8;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_8));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_8;
    } else if ((9U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_9));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_9;
    } else if ((0x0aU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_10;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_10));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_10;
    } else if ((0x0bU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_11));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_11;
    } else if ((0x0cU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_12;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_12));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_12;
    } else if ((0x0dU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_13;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_13));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_13;
    } else if ((0x0eU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_14;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_14));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_14;
    } else if ((0x0fU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_15;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_15));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_15;
    } else if ((0x10U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_16;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_16));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_16;
    } else if ((0x11U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_17;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_17));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_17;
    } else if ((0x12U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_18;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_18));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_18;
    } else if ((0x13U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_19;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_19));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_19;
    } else if ((0x14U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_20;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_20));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_20;
    } else if ((0x15U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_21;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_21));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_21;
    } else if ((0x16U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_22;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_22));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_22;
    } else if ((0x17U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_23;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_23));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_23;
    } else if ((0x18U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_24;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_24));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_24;
    } else if ((0x19U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_25;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_25));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_25;
    } else if ((0x1aU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_26;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_26));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_26;
    } else if ((0x1bU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_27;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_27));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_27;
    } else if ((0x1cU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_28;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_28));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_28;
    } else if ((0x1dU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_29;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_29));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_29;
    } else if ((0x1eU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_30;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_30));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_30;
    } else if ((0x1fU == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_31;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_31));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_31;
    } else if ((0x20U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_32;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_32));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_32;
    } else if ((0x21U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_33));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_33;
    } else if ((0x22U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_34;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_34));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_34;
    } else if ((0x23U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_35;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_35));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_35;
    } else if ((0x24U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45))) {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & (IData)(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_36));
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 
            = vlSelfRef.test__DOT__taketwo__DOT___saxi_resetval_36;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46 = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47 
            = (1U & 0U);
        vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48 = 0U;
    }
    vlSelfRef.test__DOT__saxi_bvalid = vlSelfRef.__Vdly__test__DOT__saxi_bvalid;
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40 
        = vlSelfRef.__Vdly__test__DOT___sb___05Fsaxi_writedata_valid_40;
    vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm 
        = vlSelfRef.__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm;
    vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2 
        = vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_1;
    vlSelfRef.test__DOT___saxi_arvalid = vlSelfRef.__Vdly__test__DOT___saxi_arvalid;
    vlSelfRef.test__DOT__saxi_arready = ((0U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
                                         & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__readvalid_42)) 
                                            & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__writevalid_41)) 
                                               & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__prev_awvalid_43)) 
                                                  & (IData)(vlSelfRef.test__DOT__taketwo__DOT__prev_arvalid_44)))));
    vlSelfRef.test__DOT__th_ctrl = vlSelfRef.__Vdly__test__DOT__th_ctrl;
    vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount 
        = vlSelfRef.__Vdly__test__DOT_____05Fsaxi_outstanding_wcount;
    vlSelfRef.test__DOT__saxi_awready = ((0U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
                                         & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__writevalid_41)) 
                                            & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__readvalid_42)) 
                                               & ((~ (IData)(vlSelfRef.test__DOT__saxi_bvalid)) 
                                                  & (IData)(vlSelfRef.test__DOT__taketwo__DOT__prev_awvalid_43)))));
    vlSelfRef.test__DOT___saxi_awvalid = vlSelfRef.__Vdly__test__DOT___saxi_awvalid;
    vlSelfRef.test__DOT__taketwo__DOT__rst_logic = 
        ((IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) 
         | (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle)) 
            & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6));
    vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_1 
        = (1U & (~ (IData)(vlSelfRef.test__DOT__RESETN)));
    vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_0_1 
        = vlSelfRef.test__DOT__RESETN;
    vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_1_1 
        = vlSelfRef.test__DOT__RESETN;
    vlSelfRef.test__DOT_____05Fsaxi_rready_sb_0 = (
                                                   (0x00000011U 
                                                    == vlSelfRef.test__DOT__th_ctrl) 
                                                   | (0x00000016U 
                                                      == vlSelfRef.test__DOT__th_ctrl));
    vlSelfRef.test__DOT_____05Fsaxi_has_outstanding_write 
        = ((0U < (IData)(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount)) 
           | (IData)(vlSelfRef.test__DOT___saxi_awvalid));
    vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_0_1 
        = vlSelfRef.test__DOT__RESETN;
    vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_1_1 
        = vlSelfRef.test__DOT__RESETN;
}
