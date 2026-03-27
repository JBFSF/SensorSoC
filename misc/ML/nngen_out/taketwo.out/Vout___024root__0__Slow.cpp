// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vout.h for the primary calling header

#include "Vout__pch.h"

VL_ATTR_COLD void Vout___024root___eval_static(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_static\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__test__DOT__CLK__0 
        = vlSelfRef.test__DOT__CLK;
}

VL_ATTR_COLD void Vout___024root___eval_initial__TOP(Vout___024root* vlSelf);
VL_ATTR_COLD void Vout___024root____Vm_traceActivitySetAll(Vout___024root* vlSelf);

VL_ATTR_COLD void Vout___024root___eval_initial(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_initial\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vout___024root___eval_initial__TOP(vlSelf);
    Vout___024root____Vm_traceActivitySetAll(vlSelf);
}

VL_ATTR_COLD void Vout___024root___eval_initial__TOP(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_initial__TOP\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_READMEM_N(true, 8, 1048576, 0, "memimg_taketwo.out"s
                 ,  &(vlSelfRef.test__DOT___memory_mem)
                 , 0, ~0ULL);
    vlSelfRef.test__DOT__CLK = 0U;
    vlSelfRef.test__DOT__memory_awready = 0U;
    vlSelfRef.test__DOT__memory_bvalid = 0U;
    vlSelfRef.test__DOT__memory_arready = 0U;
    vlSelfRef.test__DOT__memory_rdata = 0U;
    vlSelfRef.test__DOT__memory_rlast = 0U;
    vlSelfRef.test__DOT__memory_rvalid = 0U;
    vlSelfRef.test__DOT___memory_waddr_fsm = 0U;
    vlSelfRef.test__DOT___memory_wdata_fsm = 0U;
    vlSelfRef.test__DOT___memory_raddr_fsm = 0U;
    vlSelfRef.test__DOT___memory_rdata_fsm = 0U;
    vlSelfRef.test__DOT__count___05Fmemory_wreq_fifo = 0U;
    vlSelfRef.test__DOT__count___05Fmemory_rreq_fifo = 0U;
    vlSelfRef.test__DOT__count___05Fmemory_wdata_fifo = 0U;
    vlSelfRef.test__DOT_____05Ftmp_5_1 = 0U;
    vlSelfRef.test__DOT___write_count = 0ULL;
    vlSelfRef.test__DOT___write_addr = 0U;
    vlSelfRef.test__DOT___read_count = 0ULL;
    vlSelfRef.test__DOT___read_addr = 0U;
    vlSelfRef.test__DOT___sleep_interval_count = 0ULL;
    vlSelfRef.test__DOT___keep_sleep_count = 0ULL;
    vlSelfRef.test__DOT_____05Ftmp_10_1 = 0U;
    vlSelfRef.test__DOT_____05Ftmp_22_1 = 0U;
    vlSelfRef.test__DOT___d1___05Fmemory_rdata_fsm = 0U;
    vlSelfRef.test__DOT_____05Fmemory_rdata_fsm_cond_11_0_1 = 0U;
    vlSelfRef.test__DOT___saxi_awaddr = 0U;
    vlSelfRef.test__DOT___saxi_awvalid = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_wdata_sb_0 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_wstrb_sb_0 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0 = 0U;
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39 = 0ULL;
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40 = 0U;
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_data_42 = 0ULL;
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 = 0U;
    vlSelfRef.test__DOT___saxi_araddr = 0U;
    vlSelfRef.test__DOT___saxi_arvalid = 0U;
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_data_52 = 0U;
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53 = 0U;
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_data_55 = 0U;
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount = 0U;
    vlSelfRef.test__DOT__time_counter = 0U;
    vlSelfRef.test__DOT__th_ctrl = 0U;
    vlSelfRef.test__DOT___th_ctrl___05F_0 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_0_1 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_0_1 = 0U;
    vlSelfRef.test__DOT___th_ctrl_start_time_1 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_1_1 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_1_1 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_0_1 = 0U;
    vlSelfRef.test__DOT__axim_rdata_73 = 0U;
    vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_1_1 = 0U;
    vlSelfRef.test__DOT__axim_rdata_74 = 0U;
    vlSelfRef.test__DOT___th_ctrl_end_time_2 = 0U;
    vlSelfRef.test__DOT___th_ctrl_ok_3 = 0U;
    vlSelfRef.test__DOT___th_ctrl_bat_4 = 0U;
    vlSelfRef.test__DOT___th_ctrl_i_5 = 0U;
    vlSelfRef.test__DOT__rdata_75 = 0U;
    vlSelfRef.test__DOT___th_ctrl_orig_6 = 0U;
    vlSelfRef.test__DOT__rdata_76 = 0U;
    vlSelfRef.test__DOT___th_ctrl_check_7 = 0U;
    vlSelfRef.test__DOT__RESETN = 1U;
}

VL_ATTR_COLD void Vout___024root___eval_final(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_final\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vout___024root___eval_phase__stl(Vout___024root* vlSelf);

VL_ATTR_COLD void Vout___024root___eval_settle(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_settle\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vout___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/jfriday/sensorsoc/ML/nngen_out/taketwo.out/out.v", 3, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vout___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vout___024root___eval_triggers__stl(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_triggers__stl\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vout___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vout___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vout___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vout___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vout___024root___stl_sequent__TOP__0(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___stl_sequent__TOP__0\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41;
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41 = 0;
    CData/*0:0*/ test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59;
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59 = 0;
    // Body
    vlSelfRef.test__DOT__CLK = vlSelfRef.io_CLK;
    vlSelfRef.test__DOT__RESETN = vlSelfRef.io_RESETN;
    vlSelfRef.test__DOT_____05Fsaxi_rready_sb_0 = (
                                                   (0x00000011U 
                                                    == vlSelfRef.test__DOT__th_ctrl) 
                                                   | (0x00000016U 
                                                      == vlSelfRef.test__DOT__th_ctrl));
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
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_next_dma_flag_0 
        = (1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)));
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_out_mask_0 
        = (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_row_count);
    vlSelfRef.test__DOT__taketwo__DOT___dma_write_packed_local_packed_size_473 
        = (VL_SHIFTR_III(32,32,32, vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size, 1U) 
           + (1U & vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size));
    vlSelfRef.test__DOT__taketwo__DOT__mask_addr_masked_485 
        = (0xfffffffcU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr);
    vlSelfRef.test__DOT___memory_wreq_fifo_rdata = 
        vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem
        [vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail];
    vlSelfRef.test__DOT___memory_wdata_fifo_rdata = 
        vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem
        [vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail];
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_next_valid_12 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10));
    vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_51 
        = ((~ vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_50));
    vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_53 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_52)) 
           & (0U != vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7));
    vlSelfRef.test__DOT___memory_rreq_fifo_rdata = 
        vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem
        [vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail];
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_next_valid_27 
        = ((IData)(vlSelfRef.test__DOT__memory_rvalid) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25));
    vlSelfRef.test__DOT_____05Fsaxi_has_outstanding_write 
        = ((0U < (IData)(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount)) 
           | (IData)(vlSelfRef.test__DOT___saxi_awvalid));
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_next_valid_58 
        = ((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56) 
           | (IData)(vlSelfRef.test__DOT__saxi_rvalid));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable) 
           & (2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel)));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable) 
           & (1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel)));
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_next_valid_45 
        = ((IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0) 
           | (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43));
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_dma_pad_mask_0 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)) 
           & (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count));
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_mux_dma_flag_0 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select)) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0));
    vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_pad_mask_0_0 
        = ((1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_count) 
           | (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count_buf));
    vlSelfRef.test__DOT___sb___05Fsaxi_readdata_next_data_57 
        = ((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)
            ? vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_data_55
            : vlSelfRef.test__DOT__saxi_rdata);
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy) 
           | ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy_reg) 
              | (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_469)));
    vlSelfRef.test__DOT__saxi_awready = ((0U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
                                         & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__writevalid_41)) 
                                            & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__readvalid_42)) 
                                               & ((~ (IData)(vlSelfRef.test__DOT__saxi_bvalid)) 
                                                  & (IData)(vlSelfRef.test__DOT__taketwo__DOT__prev_awvalid_43)))));
    vlSelfRef.test__DOT__saxi_arready = ((0U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm) 
                                         & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__readvalid_42)) 
                                            & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__writevalid_41)) 
                                               & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__prev_awvalid_43)) 
                                                  & (IData)(vlSelfRef.test__DOT__taketwo__DOT__prev_arvalid_44)))));
    vlSelfRef.test__DOT___memory_wreq_fifo_empty = 
        ((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail));
    vlSelfRef.test__DOT___memory_wdata_fifo_empty = 
        ((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail));
    vlSelfRef.test__DOT__write_data_wready_17 = ((1U 
                                                  == vlSelfRef.test__DOT___memory_wdata_fsm) 
                                                 & (0x000000000000000fULL 
                                                    != vlSelfRef.test__DOT___sleep_interval_count));
    vlSelfRef.test__DOT___memory_rreq_fifo_empty = 
        ((IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable) 
           & (3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel)));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable) 
           & (4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel)));
    vlSelfRef.test__DOT__taketwo__DOT___pulse_reset_cond_18 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_prev_count_max_18));
    vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_1 
        = ((0x0000000bU == vlSelfRef.test__DOT___memory_waddr_fsm) 
           & ((IData)(vlSelfRef.test__DOT__maxi_awvalid) 
              & (IData)(vlSelfRef.test__DOT__memory_awready)));
    vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_2 
        = ((1U == vlSelfRef.test__DOT___memory_raddr_fsm) 
           & ((IData)(vlSelfRef.test__DOT__maxi_arvalid) 
              & (IData)(vlSelfRef.test__DOT__memory_arready)));
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18 
        = (((QData)((IData)(vlSelfRef.test__DOT__memory_rlast)) 
            << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__memory_rdata)));
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_s_data_36 
        = (((QData)((IData)(vlSelfRef.test__DOT_____05Fsaxi_wstrb_sb_0)) 
            << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT_____05Fsaxi_wdata_sb_0)));
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
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3 
        = (((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wlast_sb_0)) 
            << 0x00000024U) | (((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wstrb_sb_0)) 
                                << 0x00000020U) | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_sb_0))));
    vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle) 
           & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle) 
              & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle) 
                 & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle) 
                    & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle) 
                       & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle) 
                          & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle) 
                             & (3U == vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm))))))));
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
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_fsm_4) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507)) 
              | (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)) 
                  | (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0))) 
                 & (0ULL < vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf))));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_1) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_0) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    vlSelfRef.test__DOT__taketwo__DOT___reduceadd_reset_cond_16 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_prev_count_max_16));
    vlSelfRef.test__DOT___memory_wreq_fifo_full = (
                                                   (7U 
                                                    & ((IData)(1U) 
                                                       + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head))) 
                                                   == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail));
    vlSelfRef.test__DOT___memory_rreq_fifo_full = (
                                                   (7U 
                                                    & ((IData)(1U) 
                                                       + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head))) 
                                                   == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle 
        = (1U & (~ ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_busy) 
                    | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start))));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle 
        = (1U & (~ ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_busy) 
                    | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start))));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_3) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable 
        = ((1U == vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_2) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
    vlSelfRef.test__DOT___memory_wdata_fifo_full = 
        ((7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head))) 
         == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full 
        = ((7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head))) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail));
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wenable) 
           & (5U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_sel)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full 
        = ((7U & ((IData)(1U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head))) 
           == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail));
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
    vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_101 
        = (0x0000007fU & (VL_SHIFTR_III(7,7,32, (0x0000007fU 
                                                 & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51), 1U) 
                          + (1U & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)));
    vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_88 
        = (0x000001ffU & (VL_SHIFTR_III(9,9,32, (0x000001ffU 
                                                 & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52), 1U) 
                          + (1U & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52)));
    vlSelfRef.test__DOT___memory_wreq_fifo_deq = ((~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_empty)) 
                                                  & (0U 
                                                     == vlSelfRef.test__DOT___memory_wdata_fsm));
    vlSelfRef.test__DOT___memory_wdata_fifo_deq = (
                                                   (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)) 
                                                   & (IData)(vlSelfRef.test__DOT__write_data_wready_17));
    vlSelfRef.test__DOT___memory_rreq_fifo_deq = ((~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_empty)) 
                                                  & (0U 
                                                     == vlSelfRef.test__DOT___memory_rdata_fsm));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_addr 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable)
            ? (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr 
                              >> 1U)) : 0U);
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_addr 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable)
            ? (0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr 
                              >> 1U)) : 0U);
    vlSelfRef.test__DOT__taketwo__DOT___pulse_current_count_18 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_reset_cond_18)
            ? 0ULL : vlSelfRef.test__DOT__taketwo__DOT___pulse_count_18);
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_next_data_26 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)
            ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_data_24
            : vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18);
    vlSelfRef.test__DOT___sb___05Fsaxi_writedata_next_data_44 
        = ((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)
            ? vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_data_42
            : vlSelfRef.test__DOT___sb___05Fsaxi_writedata_s_data_36);
    vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_next_data_11 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)
            ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_data_9
            : vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3);
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_addr 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable)
            ? (0x000000ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_addr_504) 
                              >> 1U)) : 0U);
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
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr 
            = vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_76;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata 
            = (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21);
    } else {
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr = 0U;
        vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata = 0U;
    }
    if (vlSelfRef.test__DOT__taketwo__DOT___reduceadd_reset_cond_16) {
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16 = 0ULL;
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_data_16 = 0ULL;
    } else {
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16 
            = vlSelfRef.test__DOT__taketwo__DOT___reduceadd_count_16;
        vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_data_16 
            = vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16;
    }
    vlSelfRef.test__DOT___memory_wreq_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_full));
    vlSelfRef.test__DOT___memory_rreq_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_full));
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
    vlSelfRef.test__DOT___memory_wdata_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_full));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_deq 
        = (((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
            & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)) 
               & (0ULL == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf))) 
           | ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm) 
              & (((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)) 
                  & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy))) 
                 & (2U == (0x01feU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U])))));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty)));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable 
        = ((~ vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr) 
           & (IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59));
    vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable 
        = ((IData)(test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_59) 
           & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr);
    test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_41 
        = (1U & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                 & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full 
        = (((7U & ((IData)(2U) + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head))) 
            == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail)) 
           | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full));
    vlSelfRef.test__DOT___memory_wreq_fifo_enq = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_1) 
                                                  & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_almost_full)));
    vlSelfRef.test__DOT___memory_rreq_fifo_enq = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_2) 
                                                  & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_almost_full)));
    vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_0 
        = ((~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full)) 
           & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7));
    vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_45 
        = ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start)));
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
    vlSelfRef.test__DOT__taketwo__DOT__rst_logic = 
        ((IData)(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2) 
         | (((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle) 
             & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle)) 
            & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6));
    vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43 
        = ((0U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
           & ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
              & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start)));
    vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44 
        = ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
           & ((1U == vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm) 
              & (((~ (IData)(vlSelfRef.test__DOT__maxi_awvalid)) 
                  | (IData)(vlSelfRef.test__DOT__memory_awready)) 
                 & (6U > (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)))));
    vlSelfRef.test__DOT___memory_wdata_fifo_enq = ((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_0) 
                                                   & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_enq 
        = ((IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_45) 
           & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full)));
    vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_enq 
        = (1U & ((IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44)
                  ? ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
                     & (IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44))
                  : ((IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43)
                      ? ((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)) 
                         & (IData)(vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43))
                      : 0U)));
}

VL_ATTR_COLD void Vout___024root___eval_stl(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_stl\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vout___024root___stl_sequent__TOP__0(vlSelf);
        Vout___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vout___024root___eval_phase__stl(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_phase__stl\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vout___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vout___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vout___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vout___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vout___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vout___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vout___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge test.CLK)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vout___024root____Vm_traceActivitySetAll(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root____Vm_traceActivitySetAll\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
}

VL_ATTR_COLD void Vout___024root___ctor_var_reset(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___ctor_var_reset\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->io_CLK = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1967078938261226962ull);
    vlSelf->io_RESETN = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13466473256941481365ull);
    vlSelf->test__DOT__CLK = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6280348511867792827ull);
    vlSelf->test__DOT__RESETN = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15353063937873969893ull);
    vlSelf->test__DOT__irq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14286324462264411705ull);
    vlSelf->test__DOT__maxi_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7425577022896182805ull);
    vlSelf->test__DOT__maxi_awlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4704484019044855834ull);
    vlSelf->test__DOT__maxi_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12416125364113867063ull);
    vlSelf->test__DOT__maxi_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9684874823111558544ull);
    vlSelf->test__DOT__maxi_arlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5321528698070023503ull);
    vlSelf->test__DOT__maxi_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8434133617086123375ull);
    vlSelf->test__DOT__saxi_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8828748150478383453ull);
    vlSelf->test__DOT__saxi_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10311354915193950580ull);
    vlSelf->test__DOT__saxi_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4350138368080880511ull);
    vlSelf->test__DOT__saxi_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16254473463684895261ull);
    vlSelf->test__DOT__saxi_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 510394342479540581ull);
    vlSelf->test__DOT__memory_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5016104125907412254ull);
    vlSelf->test__DOT__memory_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9357875952996683383ull);
    vlSelf->test__DOT__memory_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8301749306790612970ull);
    vlSelf->test__DOT__memory_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9927449321895086757ull);
    vlSelf->test__DOT__memory_rlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15298597833017207127ull);
    vlSelf->test__DOT__memory_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3089983278391256018ull);
    vlSelf->test__DOT___memory_waddr_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1814022849392911915ull);
    vlSelf->test__DOT___memory_wdata_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11938471232557084606ull);
    vlSelf->test__DOT___memory_raddr_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7876949292899234461ull);
    vlSelf->test__DOT___memory_rdata_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10932512506525425091ull);
    vlSelf->test__DOT___memory_wreq_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9193235028840136706ull);
    vlSelf->test__DOT___memory_wreq_fifo_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7564128052109863358ull);
    vlSelf->test__DOT___memory_wreq_fifo_almost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12801206400105458200ull);
    vlSelf->test__DOT___memory_wreq_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6790608812640882532ull);
    vlSelf->test__DOT___memory_wreq_fifo_rdata = VL_SCOPED_RAND_RESET_Q(41, __VscopeHash, 2199271561774372166ull);
    vlSelf->test__DOT___memory_wreq_fifo_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4741512488432998755ull);
    vlSelf->test__DOT__count___05Fmemory_wreq_fifo = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9667532511063340908ull);
    vlSelf->test__DOT___memory_rreq_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9438823303280846862ull);
    vlSelf->test__DOT___memory_rreq_fifo_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7726987788851392351ull);
    vlSelf->test__DOT___memory_rreq_fifo_almost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1169014579750199330ull);
    vlSelf->test__DOT___memory_rreq_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2794976808284202668ull);
    vlSelf->test__DOT___memory_rreq_fifo_rdata = VL_SCOPED_RAND_RESET_Q(41, __VscopeHash, 8221046593237189785ull);
    vlSelf->test__DOT___memory_rreq_fifo_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3797991251537223301ull);
    vlSelf->test__DOT__count___05Fmemory_rreq_fifo = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10662049880493940996ull);
    vlSelf->test__DOT___memory_wdata_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8935094727715297192ull);
    vlSelf->test__DOT___memory_wdata_fifo_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4143577006886392317ull);
    vlSelf->test__DOT___memory_wdata_fifo_almost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15894741438172022280ull);
    vlSelf->test__DOT___memory_wdata_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4997732468621321695ull);
    vlSelf->test__DOT___memory_wdata_fifo_rdata = VL_SCOPED_RAND_RESET_Q(37, __VscopeHash, 5894363994425866860ull);
    vlSelf->test__DOT___memory_wdata_fifo_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10984876125370536610ull);
    vlSelf->test__DOT__count___05Fmemory_wdata_fifo = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15682053540757219719ull);
    vlSelf->test__DOT_____05Ftmp_5_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 24287273303091405ull);
    for (int __Vi0 = 0; __Vi0 < 1048576; ++__Vi0) {
        vlSelf->test__DOT___memory_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2451097105527488037ull);
    }
    vlSelf->test__DOT___write_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14990407987334683719ull);
    vlSelf->test__DOT___write_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7417322033577849601ull);
    vlSelf->test__DOT___read_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5176525338734682570ull);
    vlSelf->test__DOT___read_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11794749974241270321ull);
    vlSelf->test__DOT___sleep_interval_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11539370939254418610ull);
    vlSelf->test__DOT___keep_sleep_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17158749649578946904ull);
    vlSelf->test__DOT_____05Ftmp_10_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8623435371127694043ull);
    vlSelf->test__DOT__write_data_wready_17 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1762768115641846414ull);
    vlSelf->test__DOT_____05Ftmp_22_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17555973001696658146ull);
    vlSelf->test__DOT___d1___05Fmemory_rdata_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8337758828390569083ull);
    vlSelf->test__DOT_____05Fmemory_rdata_fsm_cond_11_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9019114503043830004ull);
    vlSelf->test__DOT___saxi_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16540737671020931775ull);
    vlSelf->test__DOT___saxi_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2535715285433749616ull);
    vlSelf->test__DOT_____05Fsaxi_wdata_sb_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2764847206221795160ull);
    vlSelf->test__DOT_____05Fsaxi_wstrb_sb_0 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1669728113970062101ull);
    vlSelf->test__DOT_____05Fsaxi_wvalid_sb_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 720120880746549993ull);
    vlSelf->test__DOT___sb___05Fsaxi_writedata_s_data_36 = VL_SCOPED_RAND_RESET_Q(36, __VscopeHash, 14902584908474922250ull);
    vlSelf->test__DOT___sb___05Fsaxi_writedata_data_39 = VL_SCOPED_RAND_RESET_Q(36, __VscopeHash, 1194160248607262348ull);
    vlSelf->test__DOT___sb___05Fsaxi_writedata_valid_40 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5747543895101437142ull);
    vlSelf->test__DOT___sb___05Fsaxi_writedata_tmp_data_42 = VL_SCOPED_RAND_RESET_Q(36, __VscopeHash, 4245022006921709492ull);
    vlSelf->test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14855558930971643651ull);
    vlSelf->test__DOT___sb___05Fsaxi_writedata_next_data_44 = VL_SCOPED_RAND_RESET_Q(36, __VscopeHash, 15491349705522591781ull);
    vlSelf->test__DOT___sb___05Fsaxi_writedata_next_valid_45 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13315973845689801965ull);
    vlSelf->test__DOT___saxi_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7038405414115077469ull);
    vlSelf->test__DOT___saxi_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10635213447920634839ull);
    vlSelf->test__DOT_____05Fsaxi_rready_sb_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14779171355377734450ull);
    vlSelf->test__DOT___sb___05Fsaxi_readdata_data_52 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 174220199385886164ull);
    vlSelf->test__DOT___sb___05Fsaxi_readdata_valid_53 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12105210529003871672ull);
    vlSelf->test__DOT___sb___05Fsaxi_readdata_tmp_data_55 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17943371481397457416ull);
    vlSelf->test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8233636281453790196ull);
    vlSelf->test__DOT___sb___05Fsaxi_readdata_next_data_57 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8183193987901127048ull);
    vlSelf->test__DOT___sb___05Fsaxi_readdata_next_valid_58 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8160252363245170832ull);
    vlSelf->test__DOT_____05Fsaxi_outstanding_wcount = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 18116253528641085376ull);
    vlSelf->test__DOT_____05Fsaxi_has_outstanding_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17753084492599820116ull);
    vlSelf->test__DOT__time_counter = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13565711374787164639ull);
    vlSelf->test__DOT__th_ctrl = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2587895339329065885ull);
    vlSelf->test__DOT___th_ctrl___05F_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12519119635743739017ull);
    vlSelf->test__DOT_____05Fsaxi_waddr_cond_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8924961415602271854ull);
    vlSelf->test__DOT_____05Fsaxi_wdata_cond_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4828920670796656590ull);
    vlSelf->test__DOT___th_ctrl_start_time_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11538998792040126928ull);
    vlSelf->test__DOT_____05Fsaxi_waddr_cond_1_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10860054231959195885ull);
    vlSelf->test__DOT_____05Fsaxi_wdata_cond_1_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7877360446030565794ull);
    vlSelf->test__DOT_____05Fsaxi_raddr_cond_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13851992182504187058ull);
    vlSelf->test__DOT__axim_rdata_73 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 484583470969329078ull);
    vlSelf->test__DOT_____05Fsaxi_raddr_cond_1_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4537793805739650836ull);
    vlSelf->test__DOT__axim_rdata_74 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17060046391674401724ull);
    vlSelf->test__DOT___th_ctrl_end_time_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17411103424760874640ull);
    vlSelf->test__DOT___th_ctrl_ok_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12157347212807561370ull);
    vlSelf->test__DOT___th_ctrl_bat_4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8640448121828754150ull);
    vlSelf->test__DOT___th_ctrl_i_5 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16078189835099649300ull);
    vlSelf->test__DOT__rdata_75 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16366150632892327709ull);
    vlSelf->test__DOT___th_ctrl_orig_6 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16982763574050420339ull);
    vlSelf->test__DOT__rdata_76 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9820423213927692142ull);
    vlSelf->test__DOT___th_ctrl_check_7 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11186668280472256845ull);
    vlSelf->test__DOT____VdfgRegularize_h0a7a19fb_0_0 = 0;
    vlSelf->test__DOT____VdfgRegularize_h0a7a19fb_0_1 = 0;
    vlSelf->test__DOT____VdfgRegularize_h0a7a19fb_0_2 = 0;
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_Q(41, __VscopeHash, 16404544359114128102ull);
    }
    vlSelf->test__DOT__inst___05Fmemory_wreq_fifo__DOT__head = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5680751684404876722ull);
    vlSelf->test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9279066354681145005ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_Q(41, __VscopeHash, 8955154519699182667ull);
    }
    vlSelf->test__DOT__inst___05Fmemory_rreq_fifo__DOT__head = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11016265984461605535ull);
    vlSelf->test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4681800565931886534ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_Q(37, __VscopeHash, 6486099017280421554ull);
    }
    vlSelf->test__DOT__inst___05Fmemory_wdata_fifo__DOT__head = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5034991841327320603ull);
    vlSelf->test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 1670974229766147413ull);
    vlSelf->test__DOT__taketwo__DOT___RESETN_inv_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2863552635236751660ull);
    vlSelf->test__DOT__taketwo__DOT___RESETN_inv_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1091454895059160491ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_wdata_sb_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9615473640665786671ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_wstrb_sb_0 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9083005791225029341ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_wlast_sb_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8704441236233326061ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_wvalid_sb_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6158328486846556335ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3 = VL_SCOPED_RAND_RESET_Q(37, __VscopeHash, 1883566874148450011ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_writedata_data_6 = VL_SCOPED_RAND_RESET_Q(37, __VscopeHash, 911570947058840802ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16322757937627714267ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_data_9 = VL_SCOPED_RAND_RESET_Q(37, __VscopeHash, 3724625056584525744ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2715912838500998741ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_writedata_next_data_11 = VL_SCOPED_RAND_RESET_Q(37, __VscopeHash, 13346257955559043371ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_writedata_next_valid_12 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16461406322707282599ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11003701433582107433ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_readdata_data_21 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 16237914374329568126ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15885515994875689353ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_data_24 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8209979750406731404ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14602934812126991993ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_readdata_next_data_26 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10206841647337692951ull);
    vlSelf->test__DOT__taketwo__DOT___sb_maxi_readdata_next_valid_27 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10447375714495353283ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_outstanding_wcount = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 8486378546057068884ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14472810236617374287ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_op_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11449488355399042510ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_global_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8026230800563097378ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_global_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11754266725737354578ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5951544480959753774ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9471972382909357919ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11540062138357604601ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_blocksize = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9377576042308827151ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15723508811320459630ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_fifo_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4258786971440658983ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 298073907388269591ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8690246153655522957ull);
    VL_SCOPED_RAND_RESET_W(137, vlSelf->test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata, __VscopeHash, 13433825983150391807ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_fifo_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1726656302755788675ull);
    vlSelf->test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 6363618949230240989ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_op_sel_buf = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3443379574225822765ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_addr_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4776346872604121866ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8245632829778658829ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 3390014698483739354ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_local_blocksize_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16229709862145663747ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2967691178384867718ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_data_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14984919191458479919ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5798433084090472890ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 176682904632267472ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13132007084922065764ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_op_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4603124557313819254ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_global_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12301822147778940982ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_global_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4436878080721679868ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_local_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14723019793669997730ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_local_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6207627333381852228ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_local_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14409258367977317960ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_local_blocksize = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9408256082528163845ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5876693857948399151ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_fifo_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8578019796258115488ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15941199635033176544ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14391015502914466699ull);
    VL_SCOPED_RAND_RESET_W(137, vlSelf->test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata, __VscopeHash, 6099836251349270300ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_fifo_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16466927668909499946ull);
    vlSelf->test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 18384432747247531256ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_op_sel_buf = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10114934709303259544ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_local_addr_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15449346817211475296ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_local_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7359105144236901828ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6780629774611088804ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_local_blocksize_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 139543556977728515ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16803553851885124014ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_data_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2606107013294494376ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3765059156640233547ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18188324042002622970ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_global_base_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16304373440981261659ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2895622310143966975ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6695368143776683192ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16463961737867908382ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7520411390152543246ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10444266712412334728ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_5 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9159783752707153338ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_6 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2103152669581137677ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_7 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11775693541835906777ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_8 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9634210129513126732ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_9 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1014546718792486416ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_10 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13508711706133218361ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12899086101788701484ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4587423800363334841ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_13 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12608561555667428766ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_14 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13272392516554779817ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_15 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11824937145412292381ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_16 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2095558759742823559ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_17 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6695864542279562258ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_18 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13791668112686698868ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_19 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13202503993319527642ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_20 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1678479993966275858ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_21 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14554987552017926094ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_22 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11217718741999954716ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_23 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12229612534147712135ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_24 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12243620070181341187ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_25 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1837450461321402651ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_26 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12702541088683036842ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_27 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2382175878843439141ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_28 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16524506643120265150ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_29 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15077051271977837824ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_30 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6582014430544804768ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_31 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8670845302896986043ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_32 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12409223306165206283ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_33 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9245220592126000424ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_34 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14426257315530418492ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_35 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6512125907309583951ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_36 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9608313844730561081ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4967366903557143256ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10566388809305257167ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6080734484431927712ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11213981416654679994ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3674637567547853388ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6047336375589110782ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16225257997405125230ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12039185937147458104ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17890629740017400253ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_9 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14074845344393635480ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_10 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17771629791753077841ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_11 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16502965205818640571ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_12 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14241188709144741721ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_13 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2812371358944456483ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_14 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9221553932271665341ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_15 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8466938226598653874ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_16 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17526748207263694463ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_17 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14332926671903392380ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13067846029010982523ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_19 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9044252287691838259ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_20 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12962208127972237611ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_21 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 414435062376565800ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_22 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5942093630424485077ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_23 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12849372377487324231ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_24 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7855758267819882763ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_25 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 546294423809366421ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_26 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13687891689231192413ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_27 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12188600984067373503ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_28 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7815902780753534943ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_29 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7204411987959438541ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_30 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9661846373692745397ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_31 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1356443554217484677ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_32 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15619081815047909072ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_33 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17187616526240528468ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_34 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 113534726311439545ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_35 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12112463524802441440ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_flag_36 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4899193613741098927ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 717770015295249076ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8025954510009463479ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14046989239824172433ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 783463018919988210ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18438971105967888565ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_5 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6746640823955362968ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_6 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1417110668127862208ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_7 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8171524459824840767ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_8 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1614908906584535525ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_9 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13284204345359028454ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_10 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16594121810042194449ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7851492122986752728ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4768489403808741565ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_13 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11453829794703987838ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_14 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4521813950834678613ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_15 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8481627796481297390ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_16 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11142925618310785137ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_17 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 906493518516084920ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_18 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8170723620088002287ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_19 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17540737907586098700ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_20 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2158849108339685335ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_21 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15174984941262954719ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_22 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5761186780056837497ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_23 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3673239472024083041ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_24 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2788984781834106087ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_25 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14397652853329297486ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_26 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3362335295630847584ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_27 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5535099278028035628ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_28 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2011652693900489894ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_29 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7830538221722875269ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_30 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3279356629010500365ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_31 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9615754404568773615ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_32 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 484990531711469705ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_33 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15892552810727082933ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_34 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3257089074496370059ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_35 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6882802820986754710ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_resetval_36 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3506552651298375453ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_register_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18240223805571614567ull);
    vlSelf->test__DOT__taketwo__DOT__addr_40 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7031692037714209891ull);
    vlSelf->test__DOT__taketwo__DOT__writevalid_41 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12837059425836484668ull);
    vlSelf->test__DOT__taketwo__DOT__readvalid_42 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16587437973762981293ull);
    vlSelf->test__DOT__taketwo__DOT__prev_awvalid_43 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7558411171474671230ull);
    vlSelf->test__DOT__taketwo__DOT__prev_arvalid_44 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15064233864913530324ull);
    vlSelf->test__DOT__taketwo__DOT__axis_maskaddr_45 = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 12238275293279264648ull);
    vlSelf->test__DOT__taketwo__DOT__axislite_rdata_46 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15736380766663465905ull);
    vlSelf->test__DOT__taketwo__DOT__axislite_flag_47 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3254467891791167629ull);
    vlSelf->test__DOT__taketwo__DOT__axislite_resetval_48 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13703924129964532168ull);
    vlSelf->test__DOT__taketwo__DOT___saxi_rdata_cond_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5314255986175618060ull);
    vlSelf->test__DOT__taketwo__DOT__rst_logic = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17582064897815705279ull);
    vlSelf->test__DOT__taketwo__DOT__RST = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17496139232168291804ull);
    vlSelf->test__DOT__taketwo__DOT___rst_logic_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13954472149655399572ull);
    vlSelf->test__DOT__taketwo__DOT___rst_logic_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14964791831377679091ull);
    vlSelf->test__DOT__taketwo__DOT__irq_busy_edge_50 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4033324575843063833ull);
    vlSelf->test__DOT__taketwo__DOT__irq_busy_edge_51 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8749071216287681034ull);
    vlSelf->test__DOT__taketwo__DOT__irq_extern_edge_52 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15972757886660829554ull);
    vlSelf->test__DOT__taketwo__DOT__irq_extern_edge_53 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7364209855693304356ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7051430155358610813ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2278122865339882493ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4406873801511680409ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10082959508343094197ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3395350609464448877ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13518728145959284749ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14008348286333613859ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11365440485418566831ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8999470236687537106ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17980321645460117022ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7555247049400364342ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12955895241971668654ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6051804114804097638ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id1_1_1_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 15397185060766729319ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9246424922390106815ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3980317737494329937ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10022306700252204932ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5031363164837100307ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15299852704194985595ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w16_l512_id2_1_1_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11067010348065257892ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5401376185907719808ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id0_1_addr = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 18190729251760219637ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4876823518714658562ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9064770859572906509ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15557712948327169232ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 16692136068478314619ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2367724080455571022ull);
    vlSelf->test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6122565005732337147ull);
    vlSelf->test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 7484307805795352752ull);
    vlSelf->test__DOT__taketwo__DOT__cparam_matmul_11_max_och_count = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5378266314054490577ull);
    vlSelf->test__DOT__taketwo__DOT__cparam_matmul_11_act_row_step = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4960425444790346617ull);
    vlSelf->test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9650533545349958332ull);
    vlSelf->test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 10519278863556764683ull);
    vlSelf->test__DOT__taketwo__DOT__cparam_matmul_11_keep_filter = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5869000231755452829ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_control_param_index = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2464697822539319502ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_stream_ivalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13881331265464397325ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4645394780413309225ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_source_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6328728625665303324ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_source_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5370992478733581517ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_busy_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17991513877138441860ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2529427824455098077ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2863162705480811724ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 10227069229592032911ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6951484764916749879ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14333914945014218903ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4565455561314704861ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6739833407279354117ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5500034208741633341ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6171452200459873071ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10905370810915127380ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7461243421887081234ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17861920943214993042ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4125702929144108748ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_ram_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9429204236039904083ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10256731342929446339ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_fifo_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1883960316272434956ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_x_source_empty_data = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6627482466566632180ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4971213793823312937ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7791912354939682534ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8807765717441587915ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18157405740264768672ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15781297024188714666ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12918948424811679109ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3930443621405550390ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3359241334310261755ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2079287312946916650ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9363524957145024042ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8192707863437212411ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7346253111332692193ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5832203096904059289ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_ram_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16945353203557307863ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1022189990594862240ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18299644672772500223ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_rshift_source_empty_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9371934198110046748ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_size_next_parameter_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4973583961951328355ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14726784898740353634ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13530684857622755799ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10305785007687500287ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7842923601657398140ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11761979329607665706ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7311710162227992059ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6471118789534300081ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14369941083857592193ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10905084930353224296ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1154442411321994637ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 736959029690022400ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7284633858104563059ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 394459904296693594ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11929765459845173147ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_fifo_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16472462074195826212ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_sum_sink_immediate = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 114165785515375069ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14501135144452590485ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17001036443147219076ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3336313200589044570ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17059650332270686814ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 3247961314271721576ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6725484799820986899ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18039814862911851574ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12548792132062801602ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2165782314564274336ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5196838955306561780ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1424376725757721722ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 765440022440583118ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_wdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8685321050548927761ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7890741820875918773ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_fifo_wdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6971671452545888029ull);
    vlSelf->test__DOT__taketwo__DOT___acc_0_valid_sink_immediate = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12700008374543184767ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_stream_ivalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12975088596929126892ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14827778180551966396ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_source_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17687638581445509262ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_source_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13774715662733986673ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_busy_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8252862233302089115ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11189585639440529643ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1546661686906054248ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2617924494717011173ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5034216783475236998ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12883385322336402301ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1240106987964928157ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16434887661182540272ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13928872081262952612ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15903283485872812237ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9424099638520382957ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3276572512355224765ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13768469125616595209ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4546432144250894931ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_ram_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15771691872574057408ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10715467911964893644ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_fifo_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12393835367598482118ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_var0_source_empty_data = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12289093832368374423ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2350068285056066240ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8666452696550982847ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1031736626024306889ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17646926433510872406ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12233692504571600073ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4562573350303177357ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16985682356132215632ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12040807911086263144ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14098896895425120479ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2599080673095465810ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11323670573130276822ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17580794361274272916ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15794520533674068768ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3926141391049808771ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_fifo_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6618506436548293686ull);
    vlSelf->test__DOT__taketwo__DOT___add_tree_1_sum_sink_immediate = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4713651084589426834ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_stream_ivalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2837994176926001988ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10208388639477006127ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2225152589610654905ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11382098481151089105ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_busy_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15543766703410175981ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1458993031528626055ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6225523545069406358ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8970028571049730007ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18117365841837920911ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4124650056377645774ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14302349352491212440ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5991130143235376279ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10819910948391115868ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9412091259247453402ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5913185095114267485ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9623656850461628077ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14250108555542025532ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8394505948501453880ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_ram_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11014084418944877461ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12507686154377450040ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_fifo_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16683090704569764576ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_empty_data = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4478195454338783367ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4302543982931242440ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17447373833458185796ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9172166230546747061ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5161496493631022502ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15939839209623528638ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1932584201543555098ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10732561202180073911ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16918121959153419986ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7836612324753719499ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4062394230692821832ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1572347383537537687ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4302002053380387168ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9428948339904631314ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_ram_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2785398364944420896ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11743590690414004861ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16677207922512499188ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_empty_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17251068448179309062ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7403921930323940966ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6736094174659723938ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15200867170771763610ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13737750091235128652ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4492516549386720434ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11779492077359902842ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5238277020325916776ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1121779082081874101ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 18224956205438522940ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4406681608284100394ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7921265766267378781ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7662368674764556366ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15932288327930866444ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_ram_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7574508790378983492ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15363020388467060019ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10275524358162693130ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_empty_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12378522002390047516ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7729836455137712157ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6463038366111884825ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7353708706774212237ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12671841865766380951ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2580514462018633610ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12888917617500346034ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16508200213216144463ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14994865883012649630ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16979825678571178860ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14873219911656817543ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7526415520704012494ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14707560828764389475ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5461428936084817189ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5221784272617991165ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_fifo_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9366599916609558163ull);
    vlSelf->test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_immediate = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6766294047969063850ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_stream_ivalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4457672328898082961ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12226158620461031076ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_source_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2230971430988043113ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_source_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11978789924066764835ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_busy_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12755302916602852934ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1339694167636880463ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17685822727110344215ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15662909593479301195ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17360467416790510220ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3889862880250044192ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10327100243853435405ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1672783660837386860ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2297538059613453792ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10287998386696881799ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13909912393406125389ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7185808429460753531ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10404521261874938414ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15615696910705248907ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_ram_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 43753946174292526ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10983618225489420719ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7158687073532422487ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_x_source_empty_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7844984927063311830ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3817942328110959414ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14858456788281126221ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 10975590895984781378ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18051344135441218891ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11882444427724910604ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 374634005712653055ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9977567948182939336ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18066897546556103077ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6334170064578272797ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9163847188273326396ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9216616759496399074ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14643410888146043785ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2873829341190517136ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_ram_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16608975585592571931ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18431943296703420237ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10970828061608780506ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_y_source_empty_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17955163022621909535ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12865242123219746223ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 16935764280246904411ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6956492779305339636ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 15137080606608992523ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 309076834586917412ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 16338284704431451124ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16258307667877815363ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4595841429032953787ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15544293053730510798ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3680790535821275641ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11017973049330516643ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4518332654310715078ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5793606262955304625ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_ram_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1561908575413652870ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1504139016924128470ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5959584730454835384ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_rshift_source_empty_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18292809865827335952ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5570390279126782563ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15738010378957882483ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17360644170336444849ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12226694706176710472ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10451980729539692942ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16095677450294286118ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6862435435990085816ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 3591355475396269503ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6437845271780728464ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14446906687426638787ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5154309697156160229ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15472019254082401724ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1565347391902191846ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2001228081339529684ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_fifo_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9912222360591078157ull);
    vlSelf->test__DOT__taketwo__DOT___mul_3_z_sink_immediate = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12798138513269228323ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_stream_ivalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2789765461781536022ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 918938569318073473ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5269483715466380768ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17193186471844801046ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9722756921354937217ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3114825972870170296ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_busy_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3076628311314608205ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_0_next_parameter_data = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 3392609754473048505ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_1_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17620566890349542496ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_2_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 379118792460644134ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_3_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5911819328630299181ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_4_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9859523851256384206ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_6_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10047908728331339981ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14616535046681632224ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10793288367452393789ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13872955269269754149ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14039310484158255682ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 933744747971803739ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9671551333887821736ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1447304554980251614ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11330367306870749328ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 16069090739149555961ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5319429708449470501ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2332746985972256020ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8998160947254808375ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15340615823591224003ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5482508038249834365ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10384041871370004006ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_empty_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16617063715551220794ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_8_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8617006351975349188ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4215091309619134868ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 824324780256654628ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3544547353049546814ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 917428006526291964ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16364466655480666838ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 438352590268789896ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11101299005129822612ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18184941037317104337ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10277286114095902164ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13704144269997354331ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10043084525639067708ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10373189343925810150ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1055242095506423180ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2694524738500991403ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7712681297908330762ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_empty_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15670417905032398895ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_10_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14859638528858502893ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11443919917449239182ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6357384743852123139ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15592543885063069672ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 756965209677044832ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10250902980122131379ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10358767371239543759ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17207041053049022408ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14315500352020589424ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4165200072453860471ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15473193296758142782ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8200398056764558042ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7226011776022545902ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16957820306264780103ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_ram_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10380638982645145699ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16271087601064296278ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2021143392458689304ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_empty_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10600945941058159562ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_12_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9084112407599753470ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13597453838071119724ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12352646580311638808ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4229879792848718066ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14863905250244531965ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17100245637196962947ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11179061703079009369ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3881704629879390631ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 312923212103306356ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9178857697249030524ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11534044314005713909ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9615433021023572902ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6458121741151028337ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 166965134210287003ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_ram_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9770640110457916191ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2211433918529778031ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16552580289904381036ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_empty_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8663780811346740521ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_14_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7944120452197379082ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7733141501767167074ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8580115440843553275ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9072825403740404525ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18017452138906057021ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4176326640895322433ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11385928660767594417ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3191675566334769052ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 539025100264743843ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4820210313254533913ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8811489071425571279ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5460401063656785245ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9065206280001983301ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2916205569661394209ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_ram_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3653412401134194640ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 665230709834927264ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4372724810840695861ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_empty_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11251627711716095825ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_16_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3077382594219404001ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_17_next_parameter_data = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18241273707714237355ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_18_next_parameter_data = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1689091186295961236ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_parameter_19_next_parameter_data = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8833721879176172179ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16799954716467652271ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13857360150729818396ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15275584509516852862ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4080799281157796269ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12646788038367841972ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8857998259537168692ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 914544811701581221ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10638152774868876525ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8916567152122257756ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6287937686212568331ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9495862338386578175ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16864965203712540678ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14620651947203707773ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4635583480944062406ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14138928726987996489ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_empty_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14053380268618413838ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8770506117358022172ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 87276876527804850ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8367583629552207419ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8739367589856470698ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7176883272035168571ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13402233103690074752ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8159905637744542868ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15776756763949272703ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17972265130676188253ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1358923671462759036ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9825590249439531523ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1070580964800360255ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10792532964030813694ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_fifo_deq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16040474229296695496ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_fifo_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7281963020184283874ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_empty_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12838661639741433991ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5344556759808674757ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10106293045591351214ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3179054984560507454ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6101972653488502785ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6782736169660344710ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15902615123664901123ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7746727256421096330ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6954540726639236477ull);
    vlSelf->test__DOT__taketwo__DOT___greaterthan_data_61 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17248230093893410476ull);
    vlSelf->test__DOT__taketwo__DOT___minus_data_63 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12697526919143084112ull);
    vlSelf->test__DOT__taketwo__DOT___greatereq_data_74 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9692997760749253273ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_161___05Fvariable_58 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7743867686400317573ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_164___05Fvariable_59 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12809339031565247480ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_167___05Fvariable_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7496234609698584167ull);
    vlSelf->test__DOT__taketwo__DOT___sll_data_65 = VL_SCOPED_RAND_RESET_Q(34, __VscopeHash, 5241374168081790469ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_158_greaterthan_61 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1079197653136883067ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_159_greatereq_74 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7019238549074847841ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_162___05Fdelay_161___05Fvariable_58 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3239616197808861495ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_165___05Fdelay_164___05Fvariable_59 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 481656811841428251ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_168___05Fdelay_167___05Fvariable_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7663074292398245021ull);
    vlSelf->test__DOT__taketwo__DOT___cond_data_71 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15598330940148671850ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_160___05Fdelay_159_greatereq_74 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11807150830320781964ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_163___05Fdelay_162___05Fdelay_161___05Fvariable_58 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13002767713432447449ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_166___05Fdelay_165___05Fdelay_164___05Fvariable_59 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16265947209815995864ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_169___05Fdelay_168___05Fdelay_167___05Fvariable_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4422363858128785300ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmuladd_madd_odata_reg_77 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17852412837516670560ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_170___05Fdelay_169___05Fdelay_168___05Fdelay_167___05Fvariable_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6912061286055952620ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_171___05Fdelay_170___05Fdelay_169___05Fdelay_168___05F___05Fvariable_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6977329346874362201ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_172___05Fdelay_171___05Fdelay_170___05Fdelay_169___05F___05Fvariable_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6713582540056962829ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_173___05Fdelay_172___05Fdelay_171___05Fdelay_170___05F___05Fvariable_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2244749261747379882ull);
    vlSelf->test__DOT__taketwo__DOT___sra_data_78 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16356760539221158902ull);
    vlSelf->test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10784235995595041679ull);
    vlSelf->test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13549360130532864596ull);
    vlSelf->test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9591101655388667692ull);
    vlSelf->test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15453350879126517369ull);
    vlSelf->test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18218475014064331345ull);
    vlSelf->test__DOT__taketwo__DOT___greaterthan_data_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3628492080001265474ull);
    vlSelf->test__DOT__taketwo__DOT___minus_data_5 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 10796122748054860091ull);
    vlSelf->test__DOT__taketwo__DOT___reduceadd_data_16 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14064052965576451746ull);
    vlSelf->test__DOT__taketwo__DOT___reduceadd_count_16 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12679440583774905978ull);
    vlSelf->test__DOT__taketwo__DOT___reduceadd_prev_count_max_16 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6388159943406642458ull);
    vlSelf->test__DOT__taketwo__DOT___reduceadd_reset_cond_16 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17087713259925305913ull);
    vlSelf->test__DOT__taketwo__DOT___reduceadd_current_count_16 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17830945574232544007ull);
    vlSelf->test__DOT__taketwo__DOT___reduceadd_current_data_16 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9639511108842118192ull);
    vlSelf->test__DOT__taketwo__DOT___pulse_data_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16187105523498194397ull);
    vlSelf->test__DOT__taketwo__DOT___pulse_count_18 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 18274345100310208492ull);
    vlSelf->test__DOT__taketwo__DOT___pulse_prev_count_max_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1617880048047580560ull);
    vlSelf->test__DOT__taketwo__DOT___pulse_reset_cond_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3577827810014213684ull);
    vlSelf->test__DOT__taketwo__DOT___pulse_current_count_18 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7076250628011109187ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_182___05Fvariable_1 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 16101979968136734333ull);
    VL_SCOPED_RAND_RESET_W(130, vlSelf->test__DOT__taketwo__DOT___sll_data_7, __VscopeHash, 4652659944917847049ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_179_greaterthan_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4187119819802096301ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_180_reduceadd_16 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9509599080553719987ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_183___05Fdelay_182___05Fvariable_1 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 5180869971469024605ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_186_pulse_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12299919694328959716ull);
    vlSelf->test__DOT__taketwo__DOT___cond_data_13 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8857145059899690394ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_181___05Fdelay_180_reduceadd_16 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2723847612208374390ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_184___05Fdelay_183___05Fdelay_182___05Fvariable_1 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 14140840190673498884ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_187___05Fdelay_186_pulse_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15503464530007378952ull);
    vlSelf->test__DOT__taketwo__DOT___plus_data_20 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8089566333881444127ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_185___05Fdelay_184___05Fdelay_183___05Fdelay_182___05Fvariable_1 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 15761215626630463131ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_188___05Fdelay_187___05Fdelay_186_pulse_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5984342890582686557ull);
    vlSelf->test__DOT__taketwo__DOT___sra_data_21 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9681577167216314185ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_189___05Fdelay_188___05Fdelay_187___05Fdelay_186_pulse_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 825185304901481741ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2779893656220588437ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15586110794835769528ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9037110361477867748ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9636167601510320842ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2762255455725647653ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11304156725323820125ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11012374887344688075ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17382463977385809556ull);
    VL_SCOPED_RAND_RESET_W(96, vlSelf->test__DOT__taketwo__DOT___times_mul_odata_reg_27, __VscopeHash, 10444896508905606225ull);
    VL_SCOPED_RAND_RESET_W(130, vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33, __VscopeHash, 2805663594533737462ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_199___05Fvariable_26 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17441030094969684448ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_203_eq_45 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4044162984400317423ull);
    VL_SCOPED_RAND_RESET_W(130, vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33, __VscopeHash, 9519150318156584119ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_200___05Fdelay_199___05Fvariable_26 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4274927641536199772ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_204___05Fdelay_203_eq_45 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14919350491788671750ull);
    VL_SCOPED_RAND_RESET_W(130, vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33, __VscopeHash, 3977470483955576758ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_201___05Fdelay_200___05Fdelay_199___05Fvariable_26 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 15689663257166787902ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_205___05Fdelay_204___05Fdelay_203_eq_45 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14571271197040927885ull);
    VL_SCOPED_RAND_RESET_W(130, vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33, __VscopeHash, 6145734317759929967ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_202___05Fdelay_201___05Fdelay_200___05Fdelay_199___05Fvariable_26 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 5131352459390854845ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_206___05Fdelay_205___05Fdelay_204___05Fdelay_203_eq_45 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4533314211280406410ull);
    VL_SCOPED_RAND_RESET_W(96, vlSelf->test__DOT__taketwo__DOT___cond_data_46, __VscopeHash, 2265289700218699323ull);
    vlSelf->test__DOT__taketwo__DOT___greaterthan_data_47 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15953635990144874252ull);
    vlSelf->test__DOT__taketwo__DOT___lessthan_data_51 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16463601025242051759ull);
    vlSelf->test__DOT__taketwo__DOT___greatereq_data_55 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3488172727927375914ull);
    VL_SCOPED_RAND_RESET_W(96, vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46, __VscopeHash, 2408585909014732346ull);
    VL_SCOPED_RAND_RESET_W(96, vlSelf->test__DOT__taketwo__DOT___cond_data_49, __VscopeHash, 17632245714377689115ull);
    VL_SCOPED_RAND_RESET_W(96, vlSelf->test__DOT__taketwo__DOT___cond_data_53, __VscopeHash, 379163583597073202ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_208_greatereq_55 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15479162611090101984ull);
    vlSelf->test__DOT__taketwo__DOT___cond_data_57 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18331005517563066618ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4429918543147438491ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16362128794867390801ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17032726879773259720ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15101251075123211925ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13635513935012833231ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15668052519953662789ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13888639487135564386ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1860738869167329401ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13812732279359527052ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15653484144789578684ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6376537724494437862ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1737693323370228075ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7896922534796150590ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4380645517025653805ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fifo_wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4874406588782816528ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_immediate = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7625020517246451904ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_count = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9889570130391456806ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_mode = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1168409585083872607ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_generator_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1565998356312201089ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2261744253889344112ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9982117261184148632ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_stride = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1155975972514501345ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1196572711556153301ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_size_buf = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8795140359370655375ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_stride_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 61884978610632717ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_sel = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15691593962848301512ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16887064836801799102ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_wenable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14573981075964278325ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_wdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1829301583863034297ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_fifo_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5161213157579890788ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_fifo_wdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9887724905148710145ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_immediate = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17744602879353442905ull);
    vlSelf->test__DOT__taketwo__DOT__main_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14116706056347165895ull);
    vlSelf->test__DOT__taketwo__DOT__internal_state_counter = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14870451209181598737ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_objaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13147011897894783477ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10527715681896510223ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6877230226631294728ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10064590196767487573ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10547099048178910873ull);
    vlSelf->test__DOT__taketwo__DOT__control_matmul_11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3600719539940103710ull);
    vlSelf->test__DOT__taketwo__DOT___control_matmul_11_called = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13193505684606809098ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_act_base_offset_row = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6434056817623080696ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1131097059963592457ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_filter_base_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1583566276897590011ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4969336385659893351ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_base_offset_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9677131913024257296ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_base_offset_col = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11723906162404172807ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_base_offset_row = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5780369582819362085ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9467952081219109261ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_base_offset_och = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10263404608071544672ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_dma_flag_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14278720497746199819ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_sync_comp_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 543335697584030246ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_sync_out_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16498544354772062682ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_write_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16110911984286794468ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_next_out_write_size = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12946026139525095954ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_col_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8661800902684131713ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_row_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14767937619538472796ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_bat_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1061844475910589373ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_och_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12584864419662760482ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_col_select = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6676791168477143566ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_row_select = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13635909176991626845ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_col_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8534772750478627491ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_row_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3761039462444319080ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_ram_select = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8412133429084870172ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_prev_col_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14505341455342413013ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_prev_row_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15922856930957627019ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_prev_bat_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2498882699215464144ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_prev_och_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17619879408865682068ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_prev_row_select = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11021135132178617834ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 911892158787909281ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_stream_out_local_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4050466297806002863ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_stream_out_local_col = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18289887354580127717ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2328943760453918966ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15223098867977300488ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7547512068891002506ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1667373498279318999ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_page = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18393914950548146248ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11699717528238681695ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_page_dma_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18253981088240864247ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_laddr_offset = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1805549347678674562ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_skip_read_filter = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 614275033312383740ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_skip_read_act = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3678713736210939928ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_skip_comp = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 746749973116202453ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_skip_write_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16668300553037442341ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_req_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10755717961462340310ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_cur_global_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11504943339856408755ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_cont = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10735318742410602766ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_63_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10811482123245553215ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_raddr_cond_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6036619707616276572ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_read_data_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11556097311514848582ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_fsm_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3113780075369090334ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_addr_76 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17160366382781838659ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_stride_77 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 16575055313213316583ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_length_78 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 665755744521136032ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_done_79 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3979586312319091945ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_fsm_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12212420323822916279ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_addr_82 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 1074446649396188675ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_stride_83 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 11168594974336278801ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_length_84 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 18316453612334431069ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_done_85 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12787260577472997970ull);
    vlSelf->test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_88 = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 6496339255497420046ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_fsm_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10629552680484599659ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_addr_91 = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 15890232357303128943ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_stride_92 = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 16144564746668347061ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_length_93 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 733876461147473077ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_done_94 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15284536703440449473ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_mux_dma_pad_mask_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4045250715098017264ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_mux_dma_flag_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1069258301840812754ull);
    vlSelf->test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_101 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 6868154351433509597ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_fsm_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16317942733302065828ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_addr_104 = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 1866599230033552416ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_stride_105 = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 16607045717479104080ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_length_106 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5891719322862220693ull);
    vlSelf->test__DOT__taketwo__DOT__write_burst_packed_done_107 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16434031193480466444ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_comp_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6695881592373318616ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 707207631864402972ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_buf_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16767320233828555515ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7762883105068782500ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_row_count_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16235055483311994895ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_row_select_buf = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12829803307520691872ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_och_count_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9561579681017464140ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_stream_pad_mask_0_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2502815985801727785ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_stream_pad_masks = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16530663357530120543ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7561235617234008444ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8376593634501893256ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18141990344456134991ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17226948456893863023ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 663823935625400949ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17326632327188114054ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7681222350800737807ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1368983840185996892ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_9 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3588187629702505190ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_10 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4678129374979090782ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_11 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8197828551136554988ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_12 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15806768061217601401ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_13 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4680237942263704365ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_14 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8383163090184227802ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_15 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1275945551299017947ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_16 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 416520691894323109ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_17 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17460935888730938102ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14557076896062254902ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_19 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14686765723063972016ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_20 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10031423485422524180ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_21 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12573140332690181113ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_22 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5884683054520772851ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_23 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12586185339206691795ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_24 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11483887093155606423ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_25 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16404626281973444874ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_26 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4761435049246064679ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_27 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11513751898320768956ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_28 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5780660810994000693ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_29 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12169494188173104355ull);
    vlSelf->test__DOT__taketwo__DOT___eq_data_134 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4261723098473701368ull);
    vlSelf->test__DOT__taketwo__DOT___eq_data_138 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5727086007956189979ull);
    vlSelf->test__DOT__taketwo__DOT___plus_data_174 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16937822875570327256ull);
    vlSelf->test__DOT__taketwo__DOT___plus_data_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17224076337768561113ull);
    vlSelf->test__DOT__taketwo__DOT___plus_data_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7453467448590397629ull);
    vlSelf->test__DOT__taketwo__DOT___eq_data_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3493175884400339448ull);
    vlSelf->test__DOT__taketwo__DOT___eq_data_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9469645903672972178ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14198573101917786576ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_223_pointer_153 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1633896376573296404ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_224_reinterpretcast_152 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11264348803945593724ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_225___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13729990847130731167ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_246___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 3737482381474906020ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_257_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18208802078978054201ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_274_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18076344367952649590ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_58 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 981867673355406741ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_59 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6854981099527996115ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_60 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11314574613096843866ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_226___05Fdelay_225___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11747152934469462359ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_236_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6179715044938680219ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_247___05Fdelay_246___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 2388862017196547355ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_258___05Fdelay_257_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8488598594343484533ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_275___05Fdelay_274_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17873326944302401970ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_292_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10751691783658108704ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_310_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16956491166393629056ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_339_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6886838673150267458ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_227___05Fdelay_226___05Fdelay_225___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11438246245100337134ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_237___05Fdelay_236_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10572301456272137190ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_248___05Fdelay_247___05Fdelay_246___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4769363922913227351ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_259___05Fdelay_258___05Fdelay_257_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14885181476815680307ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_276___05Fdelay_275___05Fdelay_274_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12194639511946405478ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_293___05Fdelay_292_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2102302103566135972ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_311___05Fdelay_310_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11856965880074298091ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_340___05Fdelay_339_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4404892847366857855ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_228___05Fdelay_227___05Fdelay_226___05Fdelay_225___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6552003229508294426ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_238___05Fdelay_237___05Fdelay_236_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16387302399847792206ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_249___05Fdelay_248___05Fdelay_247___05Fdelay_246___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 12253566017896355437ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_260___05Fdelay_259___05Fdelay_258___05Fdelay_257_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7846225521299817232ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_277___05Fdelay_276___05Fdelay_275___05Fdelay_274_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13492306343461762161ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_294___05Fdelay_293___05Fdelay_292_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6412335443016031418ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_312___05Fdelay_311___05Fdelay_310_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11890958916272007290ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_341___05Fdelay_340___05Fdelay_339_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6411363228340950753ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_229___05Fdelay_228___05Fdelay_227___05Fdelay_226___05F___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11933544542273843745ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_239___05Fdelay_238___05Fdelay_237___05Fdelay_236_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16932749867734993263ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_250___05Fdelay_249___05Fdelay_248___05Fdelay_247___05F___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4951551954468010666ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_261___05Fdelay_260___05Fdelay_259___05Fdelay_258___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2895807459674699763ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_278___05Fdelay_277___05Fdelay_276___05Fdelay_275___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10667426708323594500ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_295___05Fdelay_294___05Fdelay_293___05Fdelay_292_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18127086789300242838ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_313___05Fdelay_312___05Fdelay_311___05Fdelay_310_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15165146365225346667ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_342___05Fdelay_341___05Fdelay_340___05Fdelay_339_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3918705358302415863ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_230___05Fdelay_229___05Fdelay_228___05Fdelay_227___05F___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14914967230051346386ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_240___05Fdelay_239___05Fdelay_238___05Fdelay_237___05F_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1303600242138456139ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_251___05Fdelay_250___05Fdelay_249___05Fdelay_248___05F___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 16633416964942809895ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_262___05Fdelay_261___05Fdelay_260___05Fdelay_259___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4910821079414939953ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_279___05Fdelay_278___05Fdelay_277___05Fdelay_276___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10340477700910043684ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_296___05Fdelay_295___05Fdelay_294___05Fdelay_293___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1605278539004730783ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_314___05Fdelay_313___05Fdelay_312___05Fdelay_311___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11887631427010984623ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_343___05Fdelay_342___05Fdelay_341___05Fdelay_340___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4367055135644296021ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_231___05Fdelay_230___05Fdelay_229___05Fdelay_228___05F___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14362615729107094208ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_241___05Fdelay_240___05Fdelay_239___05Fdelay_238___05F_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16258597918019971704ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_252___05Fdelay_251___05Fdelay_250___05Fdelay_249___05F___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 2976185677575742075ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_263___05Fdelay_262___05Fdelay_261___05Fdelay_260___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4182979251656353047ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_280___05Fdelay_279___05Fdelay_278___05Fdelay_277___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4755684545405493120ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_297___05Fdelay_296___05Fdelay_295___05Fdelay_294___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5557558727215833056ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_315___05Fdelay_314___05Fdelay_313___05Fdelay_312___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9600275289512580487ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_344___05Fdelay_343___05Fdelay_342___05Fdelay_341___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11790373848417163728ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_232___05Fdelay_231___05Fdelay_230___05Fdelay_229___05F___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10501072682214655738ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_242___05Fdelay_241___05Fdelay_240___05Fdelay_239___05F_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 15456407777919276338ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_253___05Fdelay_252___05Fdelay_251___05Fdelay_250___05F___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 1562232326752275830ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_264___05Fdelay_263___05Fdelay_262___05Fdelay_261___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10687402808188835792ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_281___05Fdelay_280___05Fdelay_279___05Fdelay_278___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17347746439397542139ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_298___05Fdelay_297___05Fdelay_296___05Fdelay_295___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9863899626268545219ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_316___05Fdelay_315___05Fdelay_314___05Fdelay_313___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8095200104119354737ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_345___05Fdelay_344___05Fdelay_343___05Fdelay_342___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10535356839096487921ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_233___05Fdelay_232___05Fdelay_231___05Fdelay_230___05F___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1264686513817565366ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_243___05Fdelay_242___05Fdelay_241___05Fdelay_240___05F_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3173869360918684803ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_254___05Fdelay_253___05Fdelay_252___05Fdelay_251___05F___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17644262256593540608ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_265___05Fdelay_264___05Fdelay_263___05Fdelay_262___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1837149793779467377ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_282___05Fdelay_281___05Fdelay_280___05Fdelay_279___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8660482747070278544ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_299___05Fdelay_298___05Fdelay_297___05Fdelay_296___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16786216410582068705ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_317___05Fdelay_316___05Fdelay_315___05Fdelay_314___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14244570297421210051ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_346___05Fdelay_345___05Fdelay_344___05Fdelay_343___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10438500719481756546ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_234___05Fdelay_233___05Fdelay_232___05Fdelay_231___05F___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5038606906036034653ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_244___05Fdelay_243___05Fdelay_242___05Fdelay_241___05F_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12747700268046096775ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_255___05Fdelay_254___05Fdelay_253___05Fdelay_252___05F___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 10505392391553419743ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_266___05Fdelay_265___05Fdelay_264___05Fdelay_263___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15430320791127974114ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_283___05Fdelay_282___05Fdelay_281___05Fdelay_280___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11116032002540627700ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_300___05Fdelay_299___05Fdelay_298___05Fdelay_297___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2563783915374183981ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_318___05Fdelay_317___05Fdelay_316___05Fdelay_315___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15921083411591456557ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_347___05Fdelay_346___05Fdelay_345___05Fdelay_344___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9449193793509727412ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_22 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13492613986042712818ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_235___05Fdelay_234___05Fdelay_233___05Fdelay_232___05F___05Fvariable_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10069932172680236631ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_245___05Fdelay_244___05Fdelay_243___05Fdelay_242___05F_plus_190 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1088472321958638818ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_256___05Fdelay_255___05Fdelay_254___05Fdelay_253___05F___05Fvariable_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 5406086547045709886ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_267___05Fdelay_266___05Fdelay_265___05Fdelay_264___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5678281941660156276ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_284___05Fdelay_283___05Fdelay_282___05Fdelay_281___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17005298178059805502ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_301___05Fdelay_300___05Fdelay_299___05Fdelay_298___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7009362496509714076ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_319___05Fdelay_318___05Fdelay_317___05Fdelay_316___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2967135115628316868ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_348___05Fdelay_347___05Fdelay_346___05Fdelay_345___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7971997227472082267ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_15 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2557187206353571985ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_0 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17825471380025170765ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_1 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 11479669766490085557ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17103723027424754673ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_268___05Fdelay_267___05Fdelay_266___05Fdelay_265___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8371062567143568217ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_285___05Fdelay_284___05Fdelay_283___05Fdelay_282___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 989158863749464149ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_302___05Fdelay_301___05Fdelay_300___05Fdelay_299___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5947588749062476910ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_320___05Fdelay_319___05Fdelay_318___05Fdelay_317___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15597702389390695984ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_349___05Fdelay_348___05Fdelay_347___05Fdelay_346___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18213790019256928402ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_269___05Fdelay_268___05Fdelay_267___05Fdelay_266___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 677921085696317145ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_286___05Fdelay_285___05Fdelay_284___05Fdelay_283___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1852722504336858653ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_303___05Fdelay_302___05Fdelay_301___05Fdelay_300___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16648294074015441493ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_321___05Fdelay_320___05Fdelay_319___05Fdelay_318___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7065289024502540442ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_350___05Fdelay_349___05Fdelay_348___05Fdelay_347___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7473868453243993886ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_270___05Fdelay_269___05Fdelay_268___05Fdelay_267___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10626371653564772726ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_287___05Fdelay_286___05Fdelay_285___05Fdelay_284___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7755218719854556298ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_304___05Fdelay_303___05Fdelay_302___05Fdelay_301___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 696621674231276630ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_322___05Fdelay_321___05Fdelay_320___05Fdelay_319___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17719699489412433019ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_351___05Fdelay_350___05Fdelay_349___05Fdelay_348___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12622389552342456408ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_271___05Fdelay_270___05Fdelay_269___05Fdelay_268___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12797523005786215601ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_288___05Fdelay_287___05Fdelay_286___05Fdelay_285___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2144853066589816849ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_305___05Fdelay_304___05Fdelay_303___05Fdelay_302___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6236893802538751479ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_323___05Fdelay_322___05Fdelay_321___05Fdelay_320___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2573446318435923505ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_352___05Fdelay_351___05Fdelay_350___05Fdelay_349___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10059202486292964001ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_272___05Fdelay_271___05Fdelay_270___05Fdelay_269___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6435095566914348558ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_289___05Fdelay_288___05Fdelay_287___05Fdelay_286___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4001138814761654163ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_306___05Fdelay_305___05Fdelay_304___05Fdelay_303___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7114857137919301885ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_324___05Fdelay_323___05Fdelay_322___05Fdelay_321___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10232991080860396993ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_353___05Fdelay_352___05Fdelay_351___05Fdelay_350___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8925039370749659894ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_273___05Fdelay_272___05Fdelay_271___05Fdelay_270___05F_cond_100 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13218696426446481899ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_290___05Fdelay_289___05Fdelay_288___05Fdelay_287___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5430458700688414933ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_307___05Fdelay_306___05Fdelay_305___05Fdelay_304___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8763047325706064587ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_325___05Fdelay_324___05Fdelay_323___05Fdelay_322___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2162898884275905977ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_354___05Fdelay_353___05Fdelay_352___05Fdelay_351___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11776038509638698271ull);
    vlSelf->test__DOT__taketwo__DOT___plus_data_193 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11071109158897893589ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_291___05Fdelay_290___05Fdelay_289___05Fdelay_288___05F_cond_107 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12926369502029157853ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_308___05Fdelay_307___05Fdelay_306___05Fdelay_305___05F_plus_209 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4414502435747943146ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_326___05Fdelay_325___05Fdelay_324___05Fdelay_323___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9132054914384479543ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_355___05Fdelay_354___05Fdelay_353___05Fdelay_352___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 972823320121921278ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_367___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1302328498346904070ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_24 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1707390104554917517ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_25 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12138305633386465059ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_26 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 15933883520993830013ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_327___05Fdelay_326___05Fdelay_325___05Fdelay_324___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11672611941821542266ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_356___05Fdelay_355___05Fdelay_354___05Fdelay_353___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16777455929132118975ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_368___05Fdelay_367___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14923913048246583203ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_328___05Fdelay_327___05Fdelay_326___05Fdelay_325___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2152069608099095496ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_357___05Fdelay_356___05Fdelay_355___05Fdelay_354___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13855516355263025733ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_369___05Fdelay_368___05Fdelay_367___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1127932006721071882ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_329___05Fdelay_328___05Fdelay_327___05Fdelay_326___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15588578540940069884ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_358___05Fdelay_357___05Fdelay_356___05Fdelay_355___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1115256020513702134ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_370___05Fdelay_369___05Fdelay_368___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4602524662093533548ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_330___05Fdelay_329___05Fdelay_328___05Fdelay_327___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14059980779155269545ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_359___05Fdelay_358___05Fdelay_357___05Fdelay_356___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9124002744406789694ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_371___05Fdelay_370___05Fdelay_369___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3594962642143349391ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_331___05Fdelay_330___05Fdelay_329___05Fdelay_328___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8956756255846443947ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_360___05Fdelay_359___05Fdelay_358___05Fdelay_357___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5137262019458708220ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_372___05Fdelay_371___05Fdelay_370___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4630378213935199774ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_332___05Fdelay_331___05Fdelay_330___05Fdelay_329___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3528087092328001731ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_361___05Fdelay_360___05Fdelay_359___05Fdelay_358___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2528635735221124175ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_373___05Fdelay_372___05Fdelay_371___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1687686324942676711ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_333___05Fdelay_332___05Fdelay_331___05Fdelay_330___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12812339991010986844ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_362___05Fdelay_361___05Fdelay_360___05Fdelay_359___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16290666612749005536ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_374___05Fdelay_373___05Fdelay_372___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13891430837307773800ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_334___05Fdelay_333___05Fdelay_332___05Fdelay_331___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17423613890923706052ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_363___05Fdelay_362___05Fdelay_361___05Fdelay_360___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16745066263466350276ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_375___05Fdelay_374___05Fdelay_373___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11983597256516902465ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_335___05Fdelay_334___05Fdelay_333___05Fdelay_332___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5108631412666643912ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_364___05Fdelay_363___05Fdelay_362___05Fdelay_361___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1333795655026612926ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_376___05Fdelay_375___05Fdelay_374___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12386027882312109565ull);
    vlSelf->test__DOT__taketwo__DOT___greaterthan_data_212 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 294214537973324461ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_309___05Fsubstreamoutput_210 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7852194782265325224ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_336___05Fdelay_335___05Fdelay_334___05Fdelay_333___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10024953451637206804ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_365___05Fdelay_364___05Fdelay_363___05Fdelay_362___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11180487091135774280ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_377___05Fdelay_376___05Fdelay_375___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15012865927928698679ull);
    vlSelf->test__DOT__taketwo__DOT___cond_data_214 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6146672054919630427ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_337___05Fdelay_336___05Fdelay_335___05Fdelay_334___05F_eq_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14256058416904220562ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16067966705725287372ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_366___05Fdelay_365___05Fdelay_364___05Fdelay_363___05F_eq_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17102874804770604130ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fdelay_data_378___05Fdelay_377___05Fdelay_376___05F___05Fsubstreamoutput_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6430885190616814505ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_79 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 5747672909140192746ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_80 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15588254099365148139ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_81 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1014939337416973195ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_82 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12995713301340293850ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_83 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12939131463890672677ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_94 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8449069044839254323ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17434897349575008640ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2065754367615573650ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14833527529425141312ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17514548401850833632ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4932470919908251740ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15173513291019245654ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 16781893183980789733ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9137277392031628769ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18214765862021806649ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9743925694791756546ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6203056952390389430ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16909535126892187327ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17573666458817609475ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9186579980025867160ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13059556660572249064ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15888744660749910956ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9785103957209651636ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13983119804107869339ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13160672473122493891ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14339914324261938412ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4282468652508710980ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10443470870724654395ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14133320575111644771ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9611887216193943946ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_120_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1369792543075293461ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_95 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5884093045606348338ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10035703524921763575ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_101 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3999785848594531368ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1503358498402660506ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16641734150020118708ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8336920563165718473ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3675542668123673370ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15332944010672710038ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6915629265052170828ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2270916172261663097ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13410749131765235331ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17689143514327090433ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9012662584900657596ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5634991767672410240ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7442726911273835494ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5424742205664951230ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5059801622343183898ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5542267665232124846ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12139215863304495451ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12702340769739871432ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1424189966649105724ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1397370382115076631ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15148093960539384354ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9902067171963426206ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15549373821946817102ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6684446528628193283ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 241390477562750661ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_124_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6256263353095570037ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_102 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1325000188964530453ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1676275890767539377ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_108 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13240560754948388977ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_109 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1225932949307542956ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_115 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15582833224557399298ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_116 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3782247832730159397ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_122 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10159297166095248198ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_123 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17742598824420919443ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_129 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9462744349394946928ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_130 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13779862362414438828ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_131 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15148953675329791818ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_132 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2838030032286032386ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10082135115833175649ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17875997375355669742ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11542237902927024674ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12476474837305387224ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13357604699898272937ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5673188108085703587ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12305320734179178689ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15081760775887630876ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13347274213753082131ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16672176493188342211ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5279998991579187225ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2557140117335093015ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2243339544650362642ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 16937931756049226811ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 16218336469591296177ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 3013953864082783858ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10332623387589847152ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10084982515590797090ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17429436988284180953ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14827688061560615896ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4528541065019034308ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16464037219121147611ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3823962137286325409ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14241992856321936779ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_137 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4638600439665313969ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_139_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3197249337263065390ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_141_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14429785801921060949ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_133 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12601039043224221258ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17622808021309040709ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4925478049201469499ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4726292656762034001ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8575424645898058156ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2566317870291919350ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7521877149105768250ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15587147879742442381ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5946355916395699898ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 10005218498218645701ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6289935819603892999ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2464624824326213464ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10835060690405750488ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6223268161362747249ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6344323465950193043ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4259196391713307845ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 3492964887783621869ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7130687254799123425ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7775552852394568240ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 17249324110539249356ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 18203757499342857530ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 11333557872724876819ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15123477312347826944ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15198509598794353567ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8055729837129756433ull);
    vlSelf->test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1118897425361988182ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_146 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10503036566865293641ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_148_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9521696144730065313ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_150_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11737657865299320634ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_147 = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4102112903252294160ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2496270830449081763ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_154 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9501821401480494210ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_155 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11084364550871082315ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_156 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3491902446565615435ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_157 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4845586605365796521ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_158 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12745181854550542545ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_159 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17004765541537260200ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_160 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1517624271239738287ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_161 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15614604611387808640ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_162 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12840229079116540878ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_163 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8490465345555123017ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_164 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8779780398762528293ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_165 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8183994283001761391ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_166 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11492083331968136965ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_167 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13074626481358720853ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_168 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9844811586680975092ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_169 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14501046382795747411ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_170 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8820239917972868311ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_171 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10173924076773069614ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_172 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2749254091005233742ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_173 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7182779117617042152ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_174 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14071858898881936751ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_175 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4921643013538365227ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_176 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8061939943966988198ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_177 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7633945946743855099ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_178 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6582460317217700992ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_179 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10342378277636471821ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_180 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6699003928347621929ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_181 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8107605738113088162ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_182 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2259538559117510517ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_183 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5116460778957088272ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_184 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7150170757474464862ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_187 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 18310923789431794253ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_188 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4516141978557669832ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_189 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9004584656134687512ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_190 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1258323393732853954ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_191 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15410221384846381482ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_192 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 3130181596330904695ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_193 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9568094548469062635ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_194 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8520479521255713390ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_195 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12280397481674443323ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_196 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8214008458702352775ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_197 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2137484220082810764ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_198 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13941214785353888662ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_199 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15578675585709728685ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_200 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 14462425825118279920ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_201 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 2453594703546910052ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_202 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 7338286559285490747ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_203 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5165897636752491140ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_204 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8981285771293168697ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_205 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13469728448870250046ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_206 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 5990140812137176996ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_207 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 18360360647227081168ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_208 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15130545752549520784ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_209 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1340036474954784249ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_210 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 9021745290503639654ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_211 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15459658242641670898ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_212 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15694055644883912305ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_213 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12468513283485677151ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_214 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8569916379051001402ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_215 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1597075304735705318ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_216 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 8263445316497644821ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_217 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 12919680112612359205ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_218 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3257892608415018331ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_219 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4840435757805655218ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_220 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11318478283544383608ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_221 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5241954044924935612ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_222 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13190336486142430428ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_223 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17449920173129075455ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_224 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6066197220309627037ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_225 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3893808297776548609ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_226 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5759726157756267254ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_227 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12197639109894442882ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_228 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1421631294779130972ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_229 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17924845436546026107ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_230 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3026815871708430532ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_231 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16448705007744491422ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_232 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 35670912552378835ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_233 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14187568903665840346ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_234 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12472496031346915256ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_235 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11196423944509813689ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_236 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7297827040075124637ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_237 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10889952881956454307ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_238 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12857241248189018912ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_239 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12484164901931090145ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_240 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5822016556883417779ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_241 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16181699245359652009ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_242 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16416096647601910831ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_243 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18053557447957717222ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_244 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10406177692686884640ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_245 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15062412488801714248ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_246 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3282038426854108905ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_247 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4690640236619583460ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_248 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5990470757746766494ull);
    vlSelf->test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13700306929501311478ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_251 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13978650635848987735ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_252 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5271968220625503143ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_253 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4898891874367689632ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_254 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4965497158072145805ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_255 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11403410110210353858ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_256 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9856129356429035348ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_257 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16294042308567124712ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_258 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 549790223132015616ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_259 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6932785524304880666ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_260 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14692840479499323802ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_261 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14151972014703713395ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_262 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10253375110269176007ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_263 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14909609906383809382ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_264 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7262230151113058600ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_265 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8899690951468872729ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_266 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5001094047034345592ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_267 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3057564115091558232ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_268 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2846523216172858014ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_269 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6210744521586789042ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_270 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9252159944884386928ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_271 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3175635706264971012ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_272 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3242240989969502425ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_273 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15612460825059654365ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_274 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3999878881649624101ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_275 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3626802535391775020ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_276 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3693407819096264970ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_277 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16063627654186304567ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_278 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5287619839071130309ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_279 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11502823021706336895ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_280 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13118148489176331648ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_281 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8768384755615046033ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_282 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2975235227584666883ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_283 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17072215567732947218ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_284 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12498527459186248600ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_285 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1337774427228833810ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_286 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12359848515170598633ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_287 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3209632629826862222ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_288 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13786268416607557824ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_289 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15368811565998205064ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_290 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9688005101175411943ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_291 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3327704221000242538ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_292 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6468001151428962927ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_293 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15764529339794743315ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_294 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4206865047350202148ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_295 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2208417464442221389ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_296 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1215720088194132465ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_297 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10512248276560111557ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_298 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18237902186119670521ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_299 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16239454603211677776ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_300 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13679525403743835992ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_301 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7603001165124222044ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_302 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11418389299664974367ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_303 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11045312953407218630ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_304 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8427244340509012668ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_305 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2121861111299123675ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_306 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14775455656978407953ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_307 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14558686230093663154ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_308 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9714985297930468836ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_309 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5420139215334317653ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_310 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5387862991907717845ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_311 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10044097788022419205ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_312 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2396718032751665475ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_313 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16548616023865094394ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_314 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10700548844869447996ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_315 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9424476758032348211ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_316 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15591181043226469013ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_317 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16999782852992040409ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_318 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11085294061711554436ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_319 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10712217715453800415ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_320 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15398581023923966686ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_321 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1440279627791464422ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_322 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 615374370081032060ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_323 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6330911826148353840ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_324 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13052199488875530389ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_325 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1891446456918248187ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_326 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5199535505884629864ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_327 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6782078655275141841ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_328 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3552263760597611422ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_329 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9990176712735628706ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_330 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14987211631681808345ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_331 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3881376250689663293ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_332 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14680740569128457203ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_333 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 890231291533606490ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_334 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7779311072798563027ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_335 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2762089494131610622ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_336 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1769392117883545788ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_337 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13855835311418100295ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_338 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15155665832545154430ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_339 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8682490484797607233ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_340 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 406456102264184393ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_341 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1815057912029666949ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_342 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12614422230468462839ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_343 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17270657026583062038ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_344 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5490282964635554948ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_345 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7127743764991404703ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_346 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7362141167233632537ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_347 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12018375963348429345ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_348 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1074576029695425567ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_349 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14504098524737986938ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_350 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7480212758406981495ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_351 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1403688519787498936ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_352 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1470293803492023710ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_353 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13840513638582187923ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_354 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6360926001848917300ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_355 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5987849655591097903ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_356 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1921460632618833634ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_357 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14291680467708865206ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_358 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7648666959270418132ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_359 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3131111107171373364ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_360 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12690478638640829949ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_361 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11414406551803769210ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_362 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9699333679484784411ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_363 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11107935489250405980ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_364 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17274639774444496353ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_365 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5265808652872999005ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_366 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4218193625659675399ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fvariable_wdata_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7810750737533393408ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_367 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16588413460749870108ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_368 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6926625956552311996ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_369 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3701083595154071001ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_370 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11382792410702827894ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_373 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 131599180811618269ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_376 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15653803579069655196ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_377 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15280727232811644266ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_378 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1485945421937576538ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_379 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13856165257027544413ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_380 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5183479765366106450ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_381 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10899017221433554473ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_382 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17788097002698363724ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_383 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14562554641300152681ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_384 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14796952043542352366ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_385 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10502105960946122813ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_386 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4654038781950558325ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_387 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13214408894151672174ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_388 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18095230147577411196ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_389 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1002170232668162726ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_390 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16786881837313783474ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_391 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12269325985214740505ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_392 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6643968575721973044ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_393 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4416662002223652461ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_394 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9356271508927474292ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_395 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5061425426331454931ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_396 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11228129711525500296ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_397 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2070280467175356262ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_398 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17455001764745007187ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_399 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8304785879401335135ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_400 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17976212804509384367ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_401 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15748906231011124960ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_402 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2241771664005474047ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_403 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5605992969419461219ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_404 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4113629866603488002ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_405 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18210610206751628049ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_406 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15436234674480327517ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_407 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9130851445270315646ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_408 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12212360122420873571ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_409 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3902588967684769560ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_410 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16668526576571420567ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_411 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12318762843010008972ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_412 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17426164468251738243ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_413 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4466098860019069243ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_414 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17119693405698389181ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_415 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12769929672136958628ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_416 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8196241563590218242ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_417 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9778784712980890201ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_418 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6771679587806102030ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_419 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8354222737196757585ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_420 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 518515495902776811ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_421 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7804506537654978525ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_422 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3960827284185663587ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_423 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16331047119275795127ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_424 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 969682325029579550ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_425 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13339902160119580185ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_426 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13406507443824200262ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_427 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1397676322252705931ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_428 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15000719463799006848ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_429 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18364940769212990900ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_430 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10673597157776377271ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_431 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4542155268191557562ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_432 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7682452198620229476ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_433 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11046673504034134280ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_434 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15986283010737966057ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_435 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1966914742552919767ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_436 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8133619027747031300ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_437 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3838772945150962212ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_438 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9560038929184123930ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_439 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9343269502299639730ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_440 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 725501661603315831ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_441 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13040803845728188925ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_442 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1483139553283481464ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_443 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14912662048326260121ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_444 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13919964672078037217ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_445 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13491970674854873108ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_446 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6067300689087075140ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_447 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7482051719939982717ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_448 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7493720590524201054ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_449 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3143956856962834327ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_450 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15909894465849452331ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_451 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4749141433892092321ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_452 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 175453325345468411ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_453 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1757996474736064018ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_454 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16361061294976371518ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_455 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14194821593530735293ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_456 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13369916335820171932ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_457 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9020152602258886882ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_458 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15855638897209990614ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_459 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14579566810372696333ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_460 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11395638160494417872ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_461 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14759859465908340069ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_462 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5385719205579353465ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_463 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11768714506752323475ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_464 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10776017130504079463ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_465 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5758795551837301320ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_466 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12647875333102126315ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_467 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12219881335878993072ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_468 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6360310195563940077ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_469 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7046536509258664208ull);
    vlSelf->test__DOT__taketwo__DOT___tmp_470 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 251509733517970681ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_dma_out_mask_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11356482714639160459ull);
    vlSelf->test__DOT__taketwo__DOT___dma_write_packed_local_packed_size_473 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10816036223844580485ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_req_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6046934712868710754ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_cur_global_size = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 6040249918312606749ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_cont = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2794728952195028976ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_483_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 379171000683107083ull);
    vlSelf->test__DOT__taketwo__DOT__mask_addr_masked_485 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13597906442165877138ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_503_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9420558062268210907ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_waddr_cond_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4774016495210489923ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_write_data_fsm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11670597169321388196ull);
    vlSelf->test__DOT__taketwo__DOT__read_burst_packed_fsm_4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12380534230955760893ull);
    vlSelf->test__DOT__taketwo__DOT__read_burst_packed_addr_504 = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 7622337894723360828ull);
    vlSelf->test__DOT__taketwo__DOT__read_burst_packed_stride_505 = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 3038822067177240366ull);
    vlSelf->test__DOT__taketwo__DOT__read_burst_packed_length_506 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 1445127826452056729ull);
    vlSelf->test__DOT__taketwo__DOT__read_burst_packed_rvalid_507 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4309408833835264852ull);
    vlSelf->test__DOT__taketwo__DOT__read_burst_packed_rlast_508 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9004636026741091557ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_511_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4692422664395674124ull);
    vlSelf->test__DOT__taketwo__DOT_____05Ftmp_515_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10903673887285542943ull);
    vlSelf->test__DOT__taketwo__DOT___maxi_wdata_cond_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11559640337791655171ull);
    vlSelf->test__DOT__taketwo__DOT__matmul_11_mux_next_dma_flag_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 334495964103977395ull);
    vlSelf->test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43 = 0;
    vlSelf->test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44 = 0;
    vlSelf->test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_45 = 0;
    vlSelf->test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51 = 0;
    vlSelf->test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52 = 0;
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(137, vlSelf->test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[__Vi0], __VscopeHash, 691263606837226362ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 3302748144865494959ull);
    vlSelf->test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 1003302376000221462ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(137, vlSelf->test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[__Vi0], __VscopeHash, 2587149404172794304ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 16559762616380821240ull);
    vlSelf->test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4994144654522218839ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_0_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 45337878481820979ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_1_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 15735621797228543593ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4022284756737929953ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_0_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4893678231664940667ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_1_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 251297701277326146ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8988583464411739368ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_0_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12926007084330466222ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_1_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7857974546651641329ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17862539396028856506ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_0_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11673296998052100047ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_1_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6888779225050760166ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16417771611073906275ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_0_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14498371269494980520ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_1_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11874995728507318571ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16394700839239119926ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_0_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9848838205871901620ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_1_rdata_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14032996778860870842ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6923413463913827173ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_0_rdata_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7068954504556365224ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_1_rdata_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3249808733420535707ull);
    for (int __Vi0 = 0; __Vi0 < 128; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11346524012441226420ull);
    }
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_0_rdata_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13428469534362256032ull);
    vlSelf->test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_1_rdata_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12706239852186399483ull);
    for (int __Vi0 = 0; __Vi0 < 128; ++__Vi0) {
        vlSelf->test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1799431159865654415ull);
    }
    vlSelf->test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___a = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14562642765136478022ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___b = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3621560337040098671ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___c = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5249832750666548537ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14683854896969416326ull);
    vlSelf->test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3495444635679744441ull);
    vlSelf->test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___a = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8740700889972818943ull);
    vlSelf->test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___b = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2889487627478094419ull);
    VL_SCOPED_RAND_RESET_W(96, vlSelf->test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul0, __VscopeHash, 12471389838947866667ull);
    VL_SCOPED_RAND_RESET_W(96, vlSelf->test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1, __VscopeHash, 18432297192260462577ull);
    vlSelf->__Vdly__test__DOT___saxi_awvalid = 0;
    vlSelf->__Vdly__test__DOT_____05Fsaxi_wvalid_sb_0 = 0;
    vlSelf->__Vdly__test__DOT___sb___05Fsaxi_writedata_valid_40 = 0;
    vlSelf->__Vdly__test__DOT___sb___05Fsaxi_writedata_tmp_valid_43 = 0;
    vlSelf->__Vdly__test__DOT___saxi_arvalid = 0;
    vlSelf->__Vdly__test__DOT___sb___05Fsaxi_readdata_tmp_valid_56 = 0;
    vlSelf->__Vdly__test__DOT_____05Fsaxi_outstanding_wcount = 0;
    vlSelf->__Vdly__test__DOT__th_ctrl = 0;
    vlSelf->__Vdly__test__DOT__maxi_awvalid = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___maxi_outstanding_wcount = 0;
    vlSelf->__Vdly__test__DOT__saxi_rvalid = 0;
    vlSelf->__Vdly__test__DOT__saxi_bvalid = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___saxi_register_fsm = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_fsm = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_start = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__main_fsm = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__control_matmul_11 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_base_offset = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_row = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_col = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_row = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_base_offset_och = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_page = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_laddr_offset = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_out_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_write_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_next_out_write_size = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_row_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_bat_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_och_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_row_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_bat_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_prev_och_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_col_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_row_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_out_ram_select = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_filter = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_read_act = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_skip_write_out = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_comp_fsm = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_act_local_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_stream_out_local_col = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_col_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_col_select = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT__matmul_11_sync_comp_count = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2 = 0;
    vlSelf->__Vdly__test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3 = 0;
    vlSelf->__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__mem__v0 = 0;
    vlSelf->__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__mem__v0 = 0;
    vlSelf->__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__mem__v0 = 0;
    vlSelf->__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__mem__v0 = 0;
    vlSelf->__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__mem__v0 = 0;
    vlSelf->__VdlyVal__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__mem__v0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__test__DOT__CLK__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
