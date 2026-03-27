// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vout__Syms.h"


void Vout___024root__trace_chg_0_sub_0(Vout___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vout___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root__trace_chg_0\n"); );
    // Body
    Vout___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vout___024root*>(voidSelf);
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vout___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vout___024root__trace_chg_0_sub_0(Vout___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root__trace_chg_0_sub_0\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<5>/*159:0*/ __Vtemp_5;
    VlWide<5>/*159:0*/ __Vtemp_14;
    VlWide<5>/*159:0*/ __Vtemp_16;
    VlWide<5>/*159:0*/ __Vtemp_17;
    VlWide<5>/*159:0*/ __Vtemp_18;
    VlWide<5>/*159:0*/ __Vtemp_21;
    VlWide<4>/*127:0*/ __Vtemp_23;
    VlWide<4>/*127:0*/ __Vtemp_24;
    VlWide<4>/*127:0*/ __Vtemp_25;
    VlWide<4>/*127:0*/ __Vtemp_26;
    VlWide<5>/*159:0*/ __Vtemp_29;
    VlWide<4>/*127:0*/ __Vtemp_31;
    VlWide<4>/*127:0*/ __Vtemp_32;
    VlWide<4>/*127:0*/ __Vtemp_33;
    VlWide<4>/*127:0*/ __Vtemp_34;
    VlWide<4>/*127:0*/ __Vtemp_35;
    VlWide<4>/*127:0*/ __Vtemp_36;
    VlWide<5>/*159:0*/ __Vtemp_40;
    VlWide<4>/*127:0*/ __Vtemp_42;
    VlWide<4>/*127:0*/ __Vtemp_43;
    VlWide<4>/*127:0*/ __Vtemp_44;
    VlWide<4>/*127:0*/ __Vtemp_45;
    VlWide<4>/*127:0*/ __Vtemp_46;
    VlWide<4>/*127:0*/ __Vtemp_47;
    VlWide<4>/*127:0*/ __Vtemp_48;
    VlWide<3>/*95:0*/ __Vtemp_50;
    VlWide<5>/*159:0*/ __Vtemp_53;
    VlWide<5>/*159:0*/ __Vtemp_56;
    VlWide<5>/*159:0*/ __Vtemp_59;
    VlWide<3>/*95:0*/ __Vtemp_60;
    VlWide<3>/*95:0*/ __Vtemp_61;
    VlWide<3>/*95:0*/ __Vtemp_62;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+0,(vlSelfRef.test__DOT__CLK));
        bufp->chgBit(oldp+1,(vlSelfRef.test__DOT__RESETN));
        bufp->chgBit(oldp+2,((1U & (~ (IData)(vlSelfRef.test__DOT__RESETN)))));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        bufp->chgBit(oldp+3,(vlSelfRef.test__DOT__irq));
        bufp->chgIData(oldp+4,(vlSelfRef.test__DOT__maxi_awaddr),32);
        bufp->chgCData(oldp+5,(vlSelfRef.test__DOT__maxi_awlen),8);
        bufp->chgBit(oldp+6,(vlSelfRef.test__DOT__maxi_awvalid));
        bufp->chgBit(oldp+7,(vlSelfRef.test__DOT__memory_awready));
        bufp->chgIData(oldp+8,((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6)),32);
        bufp->chgCData(oldp+9,((0x0000000fU & (IData)(
                                                      (vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6 
                                                       >> 0x00000020U)))),4);
        bufp->chgBit(oldp+10,((1U & (IData)((vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6 
                                             >> 0x00000024U)))));
        bufp->chgBit(oldp+11,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_valid_7));
        bufp->chgBit(oldp+12,((1U & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full)))));
        bufp->chgBit(oldp+13,(vlSelfRef.test__DOT__memory_bvalid));
        bufp->chgIData(oldp+14,(vlSelfRef.test__DOT__maxi_araddr),32);
        bufp->chgCData(oldp+15,(vlSelfRef.test__DOT__maxi_arlen),8);
        bufp->chgBit(oldp+16,(vlSelfRef.test__DOT__maxi_arvalid));
        bufp->chgBit(oldp+17,(vlSelfRef.test__DOT__memory_arready));
        bufp->chgIData(oldp+18,(vlSelfRef.test__DOT__memory_rdata),32);
        bufp->chgBit(oldp+19,(vlSelfRef.test__DOT__memory_rlast));
        bufp->chgBit(oldp+20,(vlSelfRef.test__DOT__memory_rvalid));
        bufp->chgBit(oldp+21,((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)))));
        bufp->chgIData(oldp+22,(vlSelfRef.test__DOT___saxi_awaddr),32);
        bufp->chgBit(oldp+23,(vlSelfRef.test__DOT___saxi_awvalid));
        bufp->chgBit(oldp+24,(vlSelfRef.test__DOT__saxi_awready));
        bufp->chgIData(oldp+25,((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39)),32);
        bufp->chgCData(oldp+26,((0x0000000fU & (IData)(
                                                       (vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39 
                                                        >> 0x00000020U)))),4);
        bufp->chgBit(oldp+27,(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_valid_40));
        bufp->chgBit(oldp+28,((3U == vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm)));
        bufp->chgBit(oldp+29,(vlSelfRef.test__DOT__saxi_bvalid));
        bufp->chgIData(oldp+30,(vlSelfRef.test__DOT___saxi_araddr),32);
        bufp->chgBit(oldp+31,(vlSelfRef.test__DOT___saxi_arvalid));
        bufp->chgBit(oldp+32,(vlSelfRef.test__DOT__saxi_arready));
        bufp->chgIData(oldp+33,(vlSelfRef.test__DOT__saxi_rdata),32);
        bufp->chgBit(oldp+34,(vlSelfRef.test__DOT__saxi_rvalid));
        bufp->chgBit(oldp+35,((1U & (~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)))));
        bufp->chgIData(oldp+36,(vlSelfRef.test__DOT___memory_waddr_fsm),32);
        bufp->chgIData(oldp+37,(vlSelfRef.test__DOT___memory_wdata_fsm),32);
        bufp->chgIData(oldp+38,(vlSelfRef.test__DOT___memory_raddr_fsm),32);
        bufp->chgIData(oldp+39,(vlSelfRef.test__DOT___memory_rdata_fsm),32);
        bufp->chgBit(oldp+40,(vlSelfRef.test__DOT___memory_wreq_fifo_enq));
        bufp->chgQData(oldp+41,(((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_1)
                                  ? (((QData)((IData)(vlSelfRef.test__DOT__maxi_awaddr)) 
                                      << 9U) | (QData)((IData)(
                                                               (0x000001ffU 
                                                                & ((IData)(1U) 
                                                                   + (IData)(vlSelfRef.test__DOT__maxi_awlen))))))
                                  : 0ULL)),41);
        bufp->chgBit(oldp+43,(vlSelfRef.test__DOT___memory_wreq_fifo_full));
        bufp->chgBit(oldp+44,(vlSelfRef.test__DOT___memory_wreq_fifo_almost_full));
        bufp->chgBit(oldp+45,(vlSelfRef.test__DOT___memory_wreq_fifo_deq));
        bufp->chgQData(oldp+46,(vlSelfRef.test__DOT___memory_wreq_fifo_rdata),41);
        bufp->chgBit(oldp+48,(vlSelfRef.test__DOT___memory_wreq_fifo_empty));
        bufp->chgBit(oldp+49,((((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head) 
                                == (7U & ((IData)(1U) 
                                          + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail)))) 
                               | (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_empty))));
        bufp->chgCData(oldp+50,(vlSelfRef.test__DOT__count___05Fmemory_wreq_fifo),4);
        bufp->chgBit(oldp+51,(vlSelfRef.test__DOT___memory_rreq_fifo_enq));
        bufp->chgQData(oldp+52,(((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_2)
                                  ? (((QData)((IData)(vlSelfRef.test__DOT__maxi_araddr)) 
                                      << 9U) | (QData)((IData)(
                                                               (0x000001ffU 
                                                                & ((IData)(1U) 
                                                                   + (IData)(vlSelfRef.test__DOT__maxi_arlen))))))
                                  : 0ULL)),41);
        bufp->chgBit(oldp+54,(vlSelfRef.test__DOT___memory_rreq_fifo_full));
        bufp->chgBit(oldp+55,(vlSelfRef.test__DOT___memory_rreq_fifo_almost_full));
        bufp->chgBit(oldp+56,(vlSelfRef.test__DOT___memory_rreq_fifo_deq));
        bufp->chgQData(oldp+57,(vlSelfRef.test__DOT___memory_rreq_fifo_rdata),41);
        bufp->chgBit(oldp+59,(vlSelfRef.test__DOT___memory_rreq_fifo_empty));
        bufp->chgBit(oldp+60,((((IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head) 
                                == (7U & ((IData)(1U) 
                                          + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail)))) 
                               | (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_empty))));
        bufp->chgCData(oldp+61,(vlSelfRef.test__DOT__count___05Fmemory_rreq_fifo),4);
        bufp->chgBit(oldp+62,(vlSelfRef.test__DOT___memory_wdata_fifo_enq));
        bufp->chgQData(oldp+63,(((IData)(vlSelfRef.test__DOT____VdfgRegularize_h0a7a19fb_0_0)
                                  ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6
                                  : 0ULL)),37);
        bufp->chgBit(oldp+65,(vlSelfRef.test__DOT___memory_wdata_fifo_full));
        bufp->chgBit(oldp+66,(vlSelfRef.test__DOT___memory_wdata_fifo_almost_full));
        bufp->chgBit(oldp+67,(vlSelfRef.test__DOT___memory_wdata_fifo_deq));
        bufp->chgQData(oldp+68,(vlSelfRef.test__DOT___memory_wdata_fifo_rdata),37);
        bufp->chgBit(oldp+70,(vlSelfRef.test__DOT___memory_wdata_fifo_empty));
        bufp->chgBit(oldp+71,((((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head) 
                                == (7U & ((IData)(1U) 
                                          + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail)))) 
                               | (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty))));
        bufp->chgCData(oldp+72,(vlSelfRef.test__DOT__count___05Fmemory_wdata_fifo),4);
        bufp->chgQData(oldp+73,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_data_6),37);
        bufp->chgBit(oldp+75,(vlSelfRef.test__DOT_____05Ftmp_5_1));
        bufp->chgQData(oldp+76,(vlSelfRef.test__DOT___write_count),33);
        bufp->chgIData(oldp+78,(vlSelfRef.test__DOT___write_addr),32);
        bufp->chgQData(oldp+79,(vlSelfRef.test__DOT___read_count),33);
        bufp->chgIData(oldp+81,(vlSelfRef.test__DOT___read_addr),32);
        bufp->chgQData(oldp+82,(vlSelfRef.test__DOT___sleep_interval_count),33);
        bufp->chgQData(oldp+84,(vlSelfRef.test__DOT___keep_sleep_count),33);
        bufp->chgSData(oldp+86,((0x000001ffU & ((IData)(1U) 
                                                + (IData)(vlSelfRef.test__DOT__maxi_awlen)))),9);
        bufp->chgQData(oldp+87,((((QData)((IData)(vlSelfRef.test__DOT__maxi_awaddr)) 
                                  << 9U) | (QData)((IData)(
                                                           (0x000001ffU 
                                                            & ((IData)(1U) 
                                                               + (IData)(vlSelfRef.test__DOT__maxi_awlen))))))),41);
        bufp->chgBit(oldp+89,((1U & (~ (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_almost_full)))));
        bufp->chgBit(oldp+90,(vlSelfRef.test__DOT_____05Ftmp_10_1));
        bufp->chgIData(oldp+91,((IData)((vlSelfRef.test__DOT___memory_wreq_fifo_rdata 
                                         >> 9U))),32);
        bufp->chgSData(oldp+92,((0x000001ffU & (IData)(vlSelfRef.test__DOT___memory_wreq_fifo_rdata))),9);
        bufp->chgIData(oldp+93,((IData)(vlSelfRef.test__DOT___memory_wdata_fifo_rdata)),32);
        bufp->chgCData(oldp+94,((0x0000000fU & (IData)(
                                                       (vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                                                        >> 0x00000020U)))),4);
        bufp->chgBit(oldp+95,((1U & (IData)((vlSelfRef.test__DOT___memory_wdata_fifo_rdata 
                                             >> 0x00000024U)))));
        bufp->chgBit(oldp+96,((1U & (~ (IData)(vlSelfRef.test__DOT___memory_wdata_fifo_empty)))));
        bufp->chgBit(oldp+97,(vlSelfRef.test__DOT__write_data_wready_17));
        bufp->chgSData(oldp+98,((0x000001ffU & ((IData)(1U) 
                                                + (IData)(vlSelfRef.test__DOT__maxi_arlen)))),9);
        bufp->chgQData(oldp+99,((((QData)((IData)(vlSelfRef.test__DOT__maxi_araddr)) 
                                  << 9U) | (QData)((IData)(
                                                           (0x000001ffU 
                                                            & ((IData)(1U) 
                                                               + (IData)(vlSelfRef.test__DOT__maxi_arlen))))))),41);
        bufp->chgBit(oldp+101,((1U & (~ (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_almost_full)))));
        bufp->chgBit(oldp+102,(vlSelfRef.test__DOT_____05Ftmp_22_1));
        bufp->chgIData(oldp+103,((IData)((vlSelfRef.test__DOT___memory_rreq_fifo_rdata 
                                          >> 9U))),32);
        bufp->chgSData(oldp+104,((0x000001ffU & (IData)(vlSelfRef.test__DOT___memory_rreq_fifo_rdata))),9);
        bufp->chgIData(oldp+105,(vlSelfRef.test__DOT___d1___05Fmemory_rdata_fsm),32);
        bufp->chgBit(oldp+106,(vlSelfRef.test__DOT_____05Fmemory_rdata_fsm_cond_11_0_1));
        bufp->chgIData(oldp+107,(vlSelfRef.test__DOT_____05Fsaxi_wdata_sb_0),32);
        bufp->chgCData(oldp+108,(vlSelfRef.test__DOT_____05Fsaxi_wstrb_sb_0),4);
        bufp->chgBit(oldp+109,(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0));
        bufp->chgBit(oldp+110,((1U & (~ (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)))));
        bufp->chgQData(oldp+111,(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_s_data_36),36);
        bufp->chgQData(oldp+113,(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_data_39),36);
        bufp->chgQData(oldp+115,(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_data_42),36);
        bufp->chgBit(oldp+117,(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43));
        bufp->chgQData(oldp+118,(((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43)
                                   ? vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_data_42
                                   : vlSelfRef.test__DOT___sb___05Fsaxi_writedata_s_data_36)),36);
        bufp->chgBit(oldp+120,(((IData)(vlSelfRef.test__DOT_____05Fsaxi_wvalid_sb_0) 
                                | (IData)(vlSelfRef.test__DOT___sb___05Fsaxi_writedata_tmp_valid_43))));
        bufp->chgIData(oldp+121,(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_data_52),32);
        bufp->chgBit(oldp+122,(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_valid_53));
        bufp->chgBit(oldp+123,(vlSelfRef.test__DOT_____05Fsaxi_rready_sb_0));
        bufp->chgIData(oldp+124,(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_data_55),32);
        bufp->chgBit(oldp+125,(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56));
        bufp->chgIData(oldp+126,(((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56)
                                   ? vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_data_55
                                   : vlSelfRef.test__DOT__saxi_rdata)),32);
        bufp->chgBit(oldp+127,(((IData)(vlSelfRef.test__DOT___sb___05Fsaxi_readdata_tmp_valid_56) 
                                | (IData)(vlSelfRef.test__DOT__saxi_rvalid))));
        bufp->chgCData(oldp+128,(vlSelfRef.test__DOT_____05Fsaxi_outstanding_wcount),3);
        bufp->chgBit(oldp+129,(vlSelfRef.test__DOT_____05Fsaxi_has_outstanding_write));
        bufp->chgIData(oldp+130,(vlSelfRef.test__DOT__time_counter),32);
        bufp->chgIData(oldp+131,(vlSelfRef.test__DOT__th_ctrl),32);
        bufp->chgIData(oldp+132,(vlSelfRef.test__DOT___th_ctrl___05F_0),32);
        bufp->chgBit(oldp+133,(vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_0_1));
        bufp->chgBit(oldp+134,(vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_0_1));
        bufp->chgIData(oldp+135,(vlSelfRef.test__DOT___th_ctrl_start_time_1),32);
        bufp->chgBit(oldp+136,(vlSelfRef.test__DOT_____05Fsaxi_waddr_cond_1_1));
        bufp->chgBit(oldp+137,(vlSelfRef.test__DOT_____05Fsaxi_wdata_cond_1_1));
        bufp->chgBit(oldp+138,(vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_0_1));
        bufp->chgIData(oldp+139,(vlSelfRef.test__DOT__axim_rdata_73),32);
        bufp->chgBit(oldp+140,(vlSelfRef.test__DOT_____05Fsaxi_raddr_cond_1_1));
        bufp->chgIData(oldp+141,(vlSelfRef.test__DOT__axim_rdata_74),32);
        bufp->chgIData(oldp+142,(vlSelfRef.test__DOT___th_ctrl_end_time_2),32);
        bufp->chgIData(oldp+143,(vlSelfRef.test__DOT___th_ctrl_ok_3),32);
        bufp->chgIData(oldp+144,(vlSelfRef.test__DOT___th_ctrl_bat_4),32);
        bufp->chgIData(oldp+145,(vlSelfRef.test__DOT___th_ctrl_i_5),32);
        bufp->chgSData(oldp+146,(vlSelfRef.test__DOT__rdata_75),16);
        bufp->chgIData(oldp+147,(vlSelfRef.test__DOT___th_ctrl_orig_6),32);
        bufp->chgSData(oldp+148,(vlSelfRef.test__DOT__rdata_76),16);
        bufp->chgIData(oldp+149,(vlSelfRef.test__DOT___th_ctrl_check_7),32);
        bufp->chgQData(oldp+150,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[0]),41);
        bufp->chgQData(oldp+152,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[1]),41);
        bufp->chgQData(oldp+154,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[2]),41);
        bufp->chgQData(oldp+156,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[3]),41);
        bufp->chgQData(oldp+158,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[4]),41);
        bufp->chgQData(oldp+160,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[5]),41);
        bufp->chgQData(oldp+162,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[6]),41);
        bufp->chgQData(oldp+164,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__mem[7]),41);
        bufp->chgCData(oldp+166,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head),3);
        bufp->chgCData(oldp+167,(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail),3);
        bufp->chgBit(oldp+168,(((IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head) 
                                == (7U & ((IData)(1U) 
                                          + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail))))));
        bufp->chgBit(oldp+169,(((7U & ((IData)(2U) 
                                       + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__head))) 
                                == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_rreq_fifo__DOT__tail))));
        bufp->chgQData(oldp+170,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[0]),37);
        bufp->chgQData(oldp+172,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[1]),37);
        bufp->chgQData(oldp+174,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[2]),37);
        bufp->chgQData(oldp+176,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[3]),37);
        bufp->chgQData(oldp+178,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[4]),37);
        bufp->chgQData(oldp+180,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[5]),37);
        bufp->chgQData(oldp+182,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[6]),37);
        bufp->chgQData(oldp+184,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__mem[7]),37);
        bufp->chgCData(oldp+186,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head),3);
        bufp->chgCData(oldp+187,(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail),3);
        bufp->chgBit(oldp+188,(((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head) 
                                == (7U & ((IData)(1U) 
                                          + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail))))));
        bufp->chgBit(oldp+189,(((7U & ((IData)(2U) 
                                       + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__head))) 
                                == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wdata_fifo__DOT__tail))));
        bufp->chgQData(oldp+190,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[0]),41);
        bufp->chgQData(oldp+192,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[1]),41);
        bufp->chgQData(oldp+194,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[2]),41);
        bufp->chgQData(oldp+196,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[3]),41);
        bufp->chgQData(oldp+198,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[4]),41);
        bufp->chgQData(oldp+200,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[5]),41);
        bufp->chgQData(oldp+202,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[6]),41);
        bufp->chgQData(oldp+204,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__mem[7]),41);
        bufp->chgCData(oldp+206,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head),3);
        bufp->chgCData(oldp+207,(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail),3);
        bufp->chgBit(oldp+208,(((IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head) 
                                == (7U & ((IData)(1U) 
                                          + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail))))));
        bufp->chgBit(oldp+209,(((7U & ((IData)(2U) 
                                       + (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__head))) 
                                == (IData)(vlSelfRef.test__DOT__inst___05Fmemory_wreq_fifo__DOT__tail))));
        bufp->chgBit(oldp+210,(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_2));
        bufp->chgBit(oldp+211,(vlSelfRef.test__DOT__taketwo__DOT___RESETN_inv_1));
        bufp->chgIData(oldp+212,(vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_sb_0),32);
        bufp->chgCData(oldp+213,(vlSelfRef.test__DOT__taketwo__DOT___maxi_wstrb_sb_0),4);
        bufp->chgBit(oldp+214,(vlSelfRef.test__DOT__taketwo__DOT___maxi_wlast_sb_0));
        bufp->chgBit(oldp+215,(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0));
        bufp->chgBit(oldp+216,((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)))));
        bufp->chgQData(oldp+217,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3),37);
        bufp->chgQData(oldp+219,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_data_9),37);
        bufp->chgBit(oldp+221,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10));
        bufp->chgQData(oldp+222,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10)
                                   ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_data_9
                                   : vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_s_data_3)),37);
        bufp->chgBit(oldp+224,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_wvalid_sb_0) 
                                | (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_writedata_tmp_valid_10))));
        bufp->chgIData(oldp+225,((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21)),32);
        bufp->chgBit(oldp+226,((1U & (IData)((vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21 
                                              >> 0x00000020U)))));
        bufp->chgBit(oldp+227,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_valid_22));
        bufp->chgBit(oldp+228,((2U == vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm)));
        bufp->chgQData(oldp+229,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18),33);
        bufp->chgQData(oldp+231,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21),33);
        bufp->chgQData(oldp+233,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_data_24),33);
        bufp->chgBit(oldp+235,(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25));
        bufp->chgQData(oldp+236,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25)
                                   ? vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_data_24
                                   : vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_s_data_18)),33);
        bufp->chgBit(oldp+238,(((IData)(vlSelfRef.test__DOT__memory_rvalid) 
                                | (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_tmp_valid_25))));
        bufp->chgCData(oldp+239,(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount),3);
        bufp->chgBit(oldp+240,(((0U < (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_outstanding_wcount)) 
                                | (IData)(vlSelfRef.test__DOT__maxi_awvalid))));
        bufp->chgBit(oldp+241,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_start));
        bufp->chgCData(oldp+242,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel),8);
        bufp->chgIData(oldp+243,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr),32);
        bufp->chgQData(oldp+244,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_size),33);
        bufp->chgIData(oldp+246,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr),32);
        bufp->chgIData(oldp+247,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride),32);
        bufp->chgQData(oldp+248,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size),33);
        bufp->chgIData(oldp+250,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize),32);
        bufp->chgBit(oldp+251,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_enq));
        if (vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_45) {
            __Vtemp_5[0U] = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize;
            __Vtemp_5[1U] = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size);
            __Vtemp_5[2U] = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride 
                              << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size 
                                                >> 0x00000020U)));
            __Vtemp_5[3U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                        << 0x00000020U) 
                                       | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr)))) 
                              << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride 
                                        >> 0x0000001fU));
            __Vtemp_5[4U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                        << 0x00000020U) 
                                       | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr)))) 
                              >> 0x0000001fU) | ((IData)(
                                                         ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                                            << 0x00000020U) 
                                                           | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr))) 
                                                          >> 0x00000020U)) 
                                                 << 1U));
        } else {
            __Vtemp_5[0U] = 0U;
            __Vtemp_5[1U] = 0U;
            __Vtemp_5[2U] = 0U;
            __Vtemp_5[3U] = 0U;
            __Vtemp_5[4U] = 0U;
        }
        bufp->chgWData(oldp+252,(__Vtemp_5),137);
        bufp->chgBit(oldp+257,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_full));
        bufp->chgBit(oldp+258,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full));
        bufp->chgBit(oldp+259,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_deq));
        bufp->chgWData(oldp+260,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata),137);
        bufp->chgBit(oldp+265,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty));
        bufp->chgBit(oldp+266,((((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head) 
                                 == (7U & ((IData)(1U) 
                                           + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail)))) 
                                | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))));
        bufp->chgCData(oldp+267,(vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_read_req_fifo),4);
        bufp->chgCData(oldp+268,((0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                                                 >> 1U))),8);
        bufp->chgIData(oldp+269,(((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[4U] 
                                   << 0x0000001fU) 
                                  | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                                     >> 1U))),32);
        bufp->chgIData(oldp+270,(((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[3U] 
                                   << 0x0000001fU) 
                                  | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U] 
                                     >> 1U))),32);
        bufp->chgQData(oldp+271,((0x00000001ffffffffULL 
                                  & (((QData)((IData)(
                                                      vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[2U])) 
                                      << 0x00000020U) 
                                     | (QData)((IData)(
                                                       vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[1U]))))),33);
        bufp->chgIData(oldp+273,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_rdata[0U]),32);
        bufp->chgCData(oldp+274,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel_buf),8);
        bufp->chgIData(oldp+275,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr_buf),32);
        bufp->chgIData(oldp+276,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride_buf),32);
        bufp->chgQData(oldp+277,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size_buf),33);
        bufp->chgIData(oldp+279,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize_buf),32);
        bufp->chgBit(oldp+280,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_busy));
        bufp->chgBit(oldp+281,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy));
        bufp->chgBit(oldp+282,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_idle));
        bufp->chgBit(oldp+283,(((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_busy)) 
                                & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_empty))));
        bufp->chgBit(oldp+284,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle));
        bufp->chgBit(oldp+285,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_start));
        bufp->chgCData(oldp+286,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel),8);
        bufp->chgIData(oldp+287,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr),32);
        bufp->chgQData(oldp+288,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_size),33);
        bufp->chgIData(oldp+290,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr),32);
        bufp->chgIData(oldp+291,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride),32);
        bufp->chgQData(oldp+292,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size),33);
        bufp->chgIData(oldp+294,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize),32);
        bufp->chgBit(oldp+295,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_enq));
        if (vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_44) {
            __Vtemp_14[0U] = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize;
            __Vtemp_14[1U] = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size);
            __Vtemp_14[2U] = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                               << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size 
                                                 >> 0x00000020U)));
            __Vtemp_14[3U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                         << 0x00000020U) 
                                        | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                               << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                                         >> 0x0000001fU));
            __Vtemp_14[4U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                         << 0x00000020U) 
                                        | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                               >> 0x0000001fU) | ((IData)(
                                                          ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                                             << 0x00000020U) 
                                                            | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr))) 
                                                           >> 0x00000020U)) 
                                                  << 1U));
        } else if (vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_43) {
            __Vtemp_14[0U] = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize;
            __Vtemp_14[1U] = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size);
            __Vtemp_14[2U] = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                               << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size 
                                                 >> 0x00000020U)));
            __Vtemp_14[3U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                         << 0x00000020U) 
                                        | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                               << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                                         >> 0x0000001fU));
            __Vtemp_14[4U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                         << 0x00000020U) 
                                        | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                               >> 0x0000001fU) | ((IData)(
                                                          ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                                             << 0x00000020U) 
                                                            | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr))) 
                                                           >> 0x00000020U)) 
                                                  << 1U));
        } else {
            __Vtemp_14[0U] = 0U;
            __Vtemp_14[1U] = 0U;
            __Vtemp_14[2U] = 0U;
            __Vtemp_14[3U] = 0U;
            __Vtemp_14[4U] = 0U;
        }
        bufp->chgWData(oldp+296,(__Vtemp_14),137);
        bufp->chgBit(oldp+301,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_full));
        bufp->chgBit(oldp+302,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full));
        bufp->chgBit(oldp+303,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_deq));
        bufp->chgWData(oldp+304,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata),137);
        bufp->chgBit(oldp+309,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty));
        bufp->chgBit(oldp+310,((((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head) 
                                 == (7U & ((IData)(1U) 
                                           + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail)))) 
                                | (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty))));
        bufp->chgCData(oldp+311,(vlSelfRef.test__DOT__taketwo__DOT__count___05Fmaxi_write_req_fifo),4);
        bufp->chgCData(oldp+312,((0x000000ffU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U] 
                                                 >> 1U))),8);
        bufp->chgIData(oldp+313,(((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[4U] 
                                   << 0x0000001fU) 
                                  | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[3U] 
                                     >> 1U))),32);
        bufp->chgIData(oldp+314,(((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[3U] 
                                   << 0x0000001fU) 
                                  | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[2U] 
                                     >> 1U))),32);
        bufp->chgQData(oldp+315,((0x00000001ffffffffULL 
                                  & (((QData)((IData)(
                                                      vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[2U])) 
                                      << 0x00000020U) 
                                     | (QData)((IData)(
                                                       vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[1U]))))),33);
        bufp->chgIData(oldp+317,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_rdata[0U]),32);
        bufp->chgCData(oldp+318,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel_buf),8);
        bufp->chgIData(oldp+319,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr_buf),32);
        bufp->chgIData(oldp+320,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride_buf),32);
        bufp->chgQData(oldp+321,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_size_buf),33);
        bufp->chgIData(oldp+323,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize_buf),32);
        bufp->chgBit(oldp+324,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_busy));
        bufp->chgBit(oldp+325,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy));
        bufp->chgBit(oldp+326,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_idle));
        bufp->chgBit(oldp+327,(((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_busy)) 
                                & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_empty))));
        bufp->chgBit(oldp+328,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle));
        bufp->chgIData(oldp+329,(vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr),32);
        bufp->chgIData(oldp+330,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_0),32);
        bufp->chgIData(oldp+331,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_1),32);
        bufp->chgIData(oldp+332,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_2),32);
        bufp->chgIData(oldp+333,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_3),32);
        bufp->chgIData(oldp+334,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_4),32);
        bufp->chgIData(oldp+335,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5),32);
        bufp->chgIData(oldp+336,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6),32);
        bufp->chgIData(oldp+337,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7),32);
        bufp->chgIData(oldp+338,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_8),32);
        bufp->chgIData(oldp+339,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9),32);
        bufp->chgIData(oldp+340,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_10),32);
        bufp->chgIData(oldp+341,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_11),32);
        bufp->chgIData(oldp+342,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_12),32);
        bufp->chgIData(oldp+343,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_13),32);
        bufp->chgIData(oldp+344,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_14),32);
        bufp->chgIData(oldp+345,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_15),32);
        bufp->chgIData(oldp+346,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_16),32);
        bufp->chgIData(oldp+347,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_17),32);
        bufp->chgIData(oldp+348,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_18),32);
        bufp->chgIData(oldp+349,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_19),32);
        bufp->chgIData(oldp+350,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_20),32);
        bufp->chgIData(oldp+351,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_21),32);
        bufp->chgIData(oldp+352,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_22),32);
        bufp->chgIData(oldp+353,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_23),32);
        bufp->chgIData(oldp+354,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_24),32);
        bufp->chgIData(oldp+355,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_25),32);
        bufp->chgIData(oldp+356,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_26),32);
        bufp->chgIData(oldp+357,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_27),32);
        bufp->chgIData(oldp+358,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_28),32);
        bufp->chgIData(oldp+359,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_29),32);
        bufp->chgIData(oldp+360,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_30),32);
        bufp->chgIData(oldp+361,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_31),32);
        bufp->chgIData(oldp+362,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_32),32);
        bufp->chgIData(oldp+363,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_33),32);
        bufp->chgIData(oldp+364,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_34),32);
        bufp->chgIData(oldp+365,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_35),32);
        bufp->chgIData(oldp+366,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_36),32);
        bufp->chgBit(oldp+367,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_0));
        bufp->chgBit(oldp+368,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_1));
        bufp->chgBit(oldp+369,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_2));
        bufp->chgBit(oldp+370,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_3));
        bufp->chgBit(oldp+371,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_4));
        bufp->chgBit(oldp+372,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_5));
        bufp->chgBit(oldp+373,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_6));
        bufp->chgBit(oldp+374,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_7));
        bufp->chgBit(oldp+375,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_8));
        bufp->chgBit(oldp+376,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_9));
        bufp->chgBit(oldp+377,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_10));
        bufp->chgBit(oldp+378,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_11));
        bufp->chgBit(oldp+379,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_12));
        bufp->chgBit(oldp+380,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_13));
        bufp->chgBit(oldp+381,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_14));
        bufp->chgBit(oldp+382,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_15));
        bufp->chgBit(oldp+383,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_16));
        bufp->chgBit(oldp+384,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_17));
        bufp->chgBit(oldp+385,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_18));
        bufp->chgBit(oldp+386,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_19));
        bufp->chgBit(oldp+387,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_20));
        bufp->chgBit(oldp+388,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_21));
        bufp->chgBit(oldp+389,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_22));
        bufp->chgBit(oldp+390,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_23));
        bufp->chgBit(oldp+391,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_24));
        bufp->chgBit(oldp+392,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_25));
        bufp->chgBit(oldp+393,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_26));
        bufp->chgBit(oldp+394,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_27));
        bufp->chgBit(oldp+395,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_28));
        bufp->chgBit(oldp+396,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_29));
        bufp->chgBit(oldp+397,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_30));
        bufp->chgBit(oldp+398,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_31));
        bufp->chgBit(oldp+399,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_32));
        bufp->chgBit(oldp+400,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_33));
        bufp->chgBit(oldp+401,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_34));
        bufp->chgBit(oldp+402,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_35));
        bufp->chgBit(oldp+403,(vlSelfRef.test__DOT__taketwo__DOT___saxi_flag_36));
        bufp->chgIData(oldp+404,(vlSelfRef.test__DOT__taketwo__DOT___saxi_register_fsm),32);
        bufp->chgIData(oldp+405,(vlSelfRef.test__DOT__taketwo__DOT__addr_40),32);
        bufp->chgBit(oldp+406,(vlSelfRef.test__DOT__taketwo__DOT__writevalid_41));
        bufp->chgBit(oldp+407,(vlSelfRef.test__DOT__taketwo__DOT__readvalid_42));
        bufp->chgBit(oldp+408,(vlSelfRef.test__DOT__taketwo__DOT__prev_awvalid_43));
        bufp->chgBit(oldp+409,(vlSelfRef.test__DOT__taketwo__DOT__prev_arvalid_44));
        bufp->chgCData(oldp+410,(vlSelfRef.test__DOT__taketwo__DOT__axis_maskaddr_45),6);
        bufp->chgIData(oldp+411,(vlSelfRef.test__DOT__taketwo__DOT__axislite_rdata_46),32);
        bufp->chgBit(oldp+412,(vlSelfRef.test__DOT__taketwo__DOT__axislite_flag_47));
        bufp->chgIData(oldp+413,(vlSelfRef.test__DOT__taketwo__DOT__axislite_resetval_48),32);
        bufp->chgBit(oldp+414,(vlSelfRef.test__DOT__taketwo__DOT___saxi_rdata_cond_0_1));
        bufp->chgBit(oldp+415,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle) 
                                & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle))));
        bufp->chgBit(oldp+416,((((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_idle) 
                                 & (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_idle)) 
                                & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_6)));
        bufp->chgBit(oldp+417,(vlSelfRef.test__DOT__taketwo__DOT__rst_logic));
        bufp->chgBit(oldp+418,(vlSelfRef.test__DOT__taketwo__DOT__RST));
        bufp->chgBit(oldp+419,(vlSelfRef.test__DOT__taketwo__DOT___rst_logic_1));
        bufp->chgBit(oldp+420,(vlSelfRef.test__DOT__taketwo__DOT___rst_logic_2));
        bufp->chgIData(oldp+421,((vlSelfRef.test__DOT__taketwo__DOT___saxi_register_10 
                                  & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_9)),32);
        bufp->chgBit(oldp+422,((1U & vlSelfRef.test__DOT__taketwo__DOT___saxi_register_5)));
        bufp->chgBit(oldp+423,(vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_50));
        bufp->chgBit(oldp+424,(vlSelfRef.test__DOT__taketwo__DOT__irq_busy_edge_51));
        bufp->chgBit(oldp+425,((0U != vlSelfRef.test__DOT__taketwo__DOT___saxi_register_7)));
        bufp->chgBit(oldp+426,(vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_52));
        bufp->chgBit(oldp+427,(vlSelfRef.test__DOT__taketwo__DOT__irq_extern_edge_53));
        bufp->chgCData(oldp+428,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_addr),8);
        bufp->chgSData(oldp+429,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_0_rdata_out),16);
        bufp->chgSData(oldp+430,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wdata),16);
        bufp->chgBit(oldp+431,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_0_wenable));
        bufp->chgCData(oldp+432,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_addr),8);
        bufp->chgSData(oldp+433,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_1_rdata_out),16);
        bufp->chgBit(oldp+434,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_0_1_enable));
        bufp->chgCData(oldp+435,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_addr),8);
        bufp->chgSData(oldp+436,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_0_rdata_out),16);
        bufp->chgSData(oldp+437,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wdata),16);
        bufp->chgBit(oldp+438,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id0_1_0_wenable));
        bufp->chgSData(oldp+439,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_1_rdata_out),16);
        bufp->chgCData(oldp+440,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_addr),8);
        bufp->chgSData(oldp+441,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_0_rdata_out),16);
        bufp->chgBit(oldp+442,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_0_enable));
        bufp->chgCData(oldp+443,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_addr),8);
        bufp->chgSData(oldp+444,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_1_rdata_out),16);
        bufp->chgSData(oldp+445,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wdata),16);
        bufp->chgBit(oldp+446,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_0_1_wenable));
        bufp->chgSData(oldp+447,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_0_rdata_out),16);
        bufp->chgSData(oldp+448,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_1_rdata_out),16);
        bufp->chgSData(oldp+449,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id1_1_1_wdata),16);
        bufp->chgCData(oldp+450,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_addr),8);
        bufp->chgSData(oldp+451,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_0_rdata_out),16);
        bufp->chgBit(oldp+452,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_0_enable));
        bufp->chgCData(oldp+453,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_addr),8);
        bufp->chgSData(oldp+454,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_1_rdata_out),16);
        bufp->chgSData(oldp+455,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wdata),16);
        bufp->chgBit(oldp+456,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_0_1_wenable));
        bufp->chgSData(oldp+457,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_0_rdata_out),16);
        bufp->chgSData(oldp+458,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_1_rdata_out),16);
        bufp->chgSData(oldp+459,(vlSelfRef.test__DOT__taketwo__DOT__ram_w16_l512_id2_1_1_wdata),16);
        bufp->chgCData(oldp+460,(((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable)
                                   ? (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_raddr)
                                   : 0U)),7);
        bufp->chgIData(oldp+461,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_0_rdata_out),32);
        bufp->chgBit(oldp+462,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_0_enable));
        bufp->chgCData(oldp+463,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_addr),7);
        bufp->chgIData(oldp+464,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_1_rdata_out),32);
        bufp->chgIData(oldp+465,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wdata),32);
        bufp->chgBit(oldp+466,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id0_1_wenable));
        bufp->chgCData(oldp+467,(((IData)(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable)
                                   ? (0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_raddr)
                                   : 0U)),7);
        bufp->chgIData(oldp+468,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_0_rdata_out),32);
        bufp->chgBit(oldp+469,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_0_enable));
        bufp->chgCData(oldp+470,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_addr),7);
        bufp->chgIData(oldp+471,(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_1_rdata_out),32);
        bufp->chgIData(oldp+472,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wdata),32);
        bufp->chgBit(oldp+473,(vlSelfRef.test__DOT__taketwo__DOT__ram_w32_l128_id1_1_wenable));
        bufp->chgCData(oldp+474,(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_filter_num_och),7);
        bufp->chgCData(oldp+475,(((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                   ? 0x1eU : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                               ? 0x1dU
                                               : 0x1eU))),5);
        bufp->chgBit(oldp+476,(((0U != (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index)) 
                                & (1U != (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index)))));
        bufp->chgCData(oldp+477,(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_max_och_count),5);
        bufp->chgCData(oldp+478,(((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                   ? 0x40U : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                               ? 4U
                                               : 8U))),7);
        bufp->chgCData(oldp+479,(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_act_row_step),8);
        bufp->chgCData(oldp+480,((0x0000007fU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)),7);
        bufp->chgSData(oldp+481,(((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                   ? 0x0200U : ((1U 
                                                 == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                                 ? 0x0200U
                                                 : 0x0080U))),10);
        bufp->chgSData(oldp+482,((0x000001ffU & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52)),9);
        bufp->chgCData(oldp+483,(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_col_step),8);
        bufp->chgCData(oldp+484,(((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                   ? 0x80U : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                               ? 8U
                                               : 4U))),8);
        bufp->chgCData(oldp+485,(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_out_write_size),7);
        bufp->chgCData(oldp+486,(((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                   ? 0x40U : ((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index))
                                               ? 0U
                                               : 2U))),7);
        bufp->chgBit(oldp+487,(vlSelfRef.test__DOT__taketwo__DOT__cparam_matmul_11_keep_filter));
        bufp->chgCData(oldp+488,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_control_param_index),2);
        bufp->chgBit(oldp+489,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_stream_ivalid));
        bufp->chgIData(oldp+490,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_fsm),32);
        bufp->chgBit(oldp+491,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_start));
        bufp->chgBit(oldp+492,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_busy));
        bufp->chgBit(oldp+493,(vlSelfRef.test__DOT__taketwo__DOT___tmp_311));
        bufp->chgBit(oldp+494,(vlSelfRef.test__DOT__taketwo__DOT___tmp_318));
        bufp->chgBit(oldp+495,(vlSelfRef.test__DOT__taketwo__DOT___tmp_325));
        bufp->chgBit(oldp+496,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_source_busy) 
                                | ((IData)(vlSelfRef.test__DOT__taketwo__DOT___acc_0_busy_reg) 
                                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_325)))));
        bufp->chgBit(oldp+497,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_busy_reg));
        bufp->chgBit(oldp+498,((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy)))));
        bufp->chgBit(oldp+499,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_x_idle));
        bufp->chgBit(oldp+500,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_x_source_ram_renable));
        bufp->chgBit(oldp+501,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_x_source_fifo_deq));
        bufp->chgBit(oldp+502,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_rshift_idle));
        bufp->chgBit(oldp+503,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_rshift_source_ram_renable));
        bufp->chgBit(oldp+504,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_rshift_source_fifo_deq));
        bufp->chgBit(oldp+505,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_sum_sink_wenable));
        bufp->chgBit(oldp+506,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_sum_sink_fifo_enq));
        bufp->chgBit(oldp+507,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_valid_sink_wenable));
        bufp->chgBit(oldp+508,(vlSelfRef.test__DOT__taketwo__DOT___acc_0_valid_sink_fifo_enq));
        bufp->chgBit(oldp+509,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_stream_ivalid));
        bufp->chgIData(oldp+510,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_fsm),32);
        bufp->chgBit(oldp+511,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_start));
        bufp->chgBit(oldp+512,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_busy));
        bufp->chgBit(oldp+513,(vlSelfRef.test__DOT__taketwo__DOT___tmp_289));
        bufp->chgBit(oldp+514,(vlSelfRef.test__DOT__taketwo__DOT___tmp_291));
        bufp->chgBit(oldp+515,(vlSelfRef.test__DOT__taketwo__DOT___tmp_293));
        bufp->chgBit(oldp+516,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_source_busy) 
                                | ((IData)(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_busy_reg) 
                                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_293)))));
        bufp->chgBit(oldp+517,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_busy_reg));
        bufp->chgBit(oldp+518,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_var0_idle));
        bufp->chgBit(oldp+519,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_var0_source_ram_renable));
        bufp->chgBit(oldp+520,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_var0_source_fifo_deq));
        bufp->chgBit(oldp+521,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_sum_sink_wenable));
        bufp->chgBit(oldp+522,(vlSelfRef.test__DOT__taketwo__DOT___add_tree_1_sum_sink_fifo_enq));
        bufp->chgBit(oldp+523,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_stream_ivalid));
        bufp->chgIData(oldp+524,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_fsm),32);
        bufp->chgBit(oldp+525,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_start));
        bufp->chgBit(oldp+526,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy));
        bufp->chgBit(oldp+527,(vlSelfRef.test__DOT__taketwo__DOT___tmp_339));
        bufp->chgBit(oldp+528,(vlSelfRef.test__DOT__taketwo__DOT___tmp_349));
        bufp->chgBit(oldp+529,(vlSelfRef.test__DOT__taketwo__DOT___tmp_359));
        bufp->chgBit(oldp+530,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_source_busy) 
                                | ((IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_busy_reg) 
                                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_359)))));
        bufp->chgBit(oldp+531,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_busy_reg));
        bufp->chgBit(oldp+532,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_idle));
        bufp->chgBit(oldp+533,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_ram_renable));
        bufp->chgBit(oldp+534,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_x_source_fifo_deq));
        bufp->chgBit(oldp+535,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_idle));
        bufp->chgBit(oldp+536,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_ram_renable));
        bufp->chgBit(oldp+537,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_y_source_fifo_deq));
        bufp->chgBit(oldp+538,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_idle));
        bufp->chgBit(oldp+539,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_ram_renable));
        bufp->chgBit(oldp+540,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_rshift_source_fifo_deq));
        bufp->chgBit(oldp+541,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_wenable));
        bufp->chgBit(oldp+542,(vlSelfRef.test__DOT__taketwo__DOT___mul_rshift_round_clip_2_z_sink_fifo_enq));
        bufp->chgBit(oldp+543,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_stream_ivalid));
        bufp->chgIData(oldp+544,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_fsm),32);
        bufp->chgBit(oldp+545,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_start));
        bufp->chgBit(oldp+546,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_busy));
        bufp->chgBit(oldp+547,(vlSelfRef.test__DOT__taketwo__DOT___tmp_263));
        bufp->chgBit(oldp+548,(vlSelfRef.test__DOT__taketwo__DOT___tmp_273));
        bufp->chgBit(oldp+549,(vlSelfRef.test__DOT__taketwo__DOT___tmp_283));
        bufp->chgBit(oldp+550,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_source_busy) 
                                | ((IData)(vlSelfRef.test__DOT__taketwo__DOT___mul_3_busy_reg) 
                                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_283)))));
        bufp->chgBit(oldp+551,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_busy_reg));
        bufp->chgBit(oldp+552,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_x_idle));
        bufp->chgBit(oldp+553,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_x_source_ram_renable));
        bufp->chgBit(oldp+554,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_x_source_fifo_deq));
        bufp->chgBit(oldp+555,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_y_idle));
        bufp->chgBit(oldp+556,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_y_source_ram_renable));
        bufp->chgBit(oldp+557,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_y_source_fifo_deq));
        bufp->chgBit(oldp+558,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_rshift_idle));
        bufp->chgBit(oldp+559,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_rshift_source_ram_renable));
        bufp->chgBit(oldp+560,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_rshift_source_fifo_deq));
        bufp->chgBit(oldp+561,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_z_sink_wenable));
        bufp->chgBit(oldp+562,(vlSelfRef.test__DOT__taketwo__DOT___mul_3_z_sink_fifo_enq));
        bufp->chgBit(oldp+563,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_stream_ivalid));
        bufp->chgIData(oldp+564,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_fsm),32);
        bufp->chgBit(oldp+565,((4U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)));
        bufp->chgBit(oldp+566,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_start));
        bufp->chgBit(oldp+567,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_stop));
        bufp->chgBit(oldp+568,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_busy));
        bufp->chgBit(oldp+569,(vlSelfRef.test__DOT__taketwo__DOT___tmp_407));
        bufp->chgBit(oldp+570,(vlSelfRef.test__DOT__taketwo__DOT___tmp_438));
        bufp->chgBit(oldp+571,(vlSelfRef.test__DOT__taketwo__DOT___tmp_469));
        bufp->chgBit(oldp+572,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy));
        bufp->chgBit(oldp+573,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_busy_reg));
        bufp->chgCData(oldp+574,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_0_next_parameter_data),7);
        bufp->chgBit(oldp+575,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_1_next_parameter_data));
        bufp->chgBit(oldp+576,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_2_next_parameter_data));
        bufp->chgBit(oldp+577,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_3_next_parameter_data));
        bufp->chgBit(oldp+578,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_4_next_parameter_data));
        bufp->chgBit(oldp+579,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_6_next_parameter_data));
        bufp->chgBit(oldp+580,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_idle));
        bufp->chgCData(oldp+581,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_mode),5);
        bufp->chgIData(oldp+582,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset),32);
        bufp->chgIData(oldp+583,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset_buf),32);
        bufp->chgCData(oldp+584,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel),8);
        bufp->chgIData(oldp+585,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_raddr),32);
        bufp->chgBit(oldp+586,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_ram_renable));
        bufp->chgIData(oldp+587,(((1U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_sel))
                                   ? vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id1__DOT__ram_w32_l128_id1_0_rdata_out
                                   : 0U)),32);
        bufp->chgBit(oldp+588,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_fifo_deq));
        bufp->chgBit(oldp+589,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_8_next_parameter_data));
        bufp->chgBit(oldp+590,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_idle));
        bufp->chgCData(oldp+591,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_mode),5);
        bufp->chgIData(oldp+592,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset),32);
        bufp->chgIData(oldp+593,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset_buf),32);
        bufp->chgCData(oldp+594,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel),8);
        bufp->chgIData(oldp+595,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_raddr),32);
        bufp->chgBit(oldp+596,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_ram_renable));
        bufp->chgIData(oldp+597,(((2U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_sel))
                                   ? vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w32_l128_id0__DOT__ram_w32_l128_id0_0_rdata_out
                                   : 0U)),32);
        bufp->chgBit(oldp+598,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_fifo_deq));
        bufp->chgBit(oldp+599,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_10_next_parameter_data));
        bufp->chgBit(oldp+600,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_idle));
        bufp->chgCData(oldp+601,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_mode),5);
        bufp->chgBit(oldp+602,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_ram_renable));
        bufp->chgBit(oldp+603,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_fifo_deq));
        bufp->chgSData(oldp+604,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_11_source_empty_data),16);
        bufp->chgBit(oldp+605,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_12_next_parameter_data));
        bufp->chgBit(oldp+606,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_idle));
        bufp->chgCData(oldp+607,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_mode),5);
        bufp->chgBit(oldp+608,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_ram_renable));
        bufp->chgBit(oldp+609,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_fifo_deq));
        bufp->chgSData(oldp+610,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_13_source_empty_data),16);
        bufp->chgBit(oldp+611,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_14_next_parameter_data));
        bufp->chgBit(oldp+612,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_idle));
        bufp->chgCData(oldp+613,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_mode),5);
        bufp->chgBit(oldp+614,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_ram_renable));
        bufp->chgBit(oldp+615,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_fifo_deq));
        bufp->chgSData(oldp+616,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_15_source_empty_data),16);
        bufp->chgBit(oldp+617,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_16_next_parameter_data));
        bufp->chgBit(oldp+618,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_17_next_parameter_data));
        bufp->chgCData(oldp+619,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_18_next_parameter_data),5);
        bufp->chgCData(oldp+620,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_parameter_19_next_parameter_data),2);
        bufp->chgBit(oldp+621,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_idle));
        bufp->chgCData(oldp+622,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_mode),5);
        bufp->chgIData(oldp+623,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset),32);
        bufp->chgIData(oldp+624,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset_buf),32);
        bufp->chgCData(oldp+625,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel),8);
        bufp->chgIData(oldp+626,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr),32);
        bufp->chgBit(oldp+627,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_renable));
        bufp->chgSData(oldp+628,(((3U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_sel))
                                   ? (0x0000ffffU & 
                                      ((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_137)
                                        ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_0_rdata_out)
                                        : (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_0_rdata_out)))
                                   : 0U)),16);
        bufp->chgBit(oldp+629,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_fifo_deq));
        bufp->chgBit(oldp+630,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_idle));
        bufp->chgCData(oldp+631,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_mode),5);
        bufp->chgIData(oldp+632,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset),32);
        bufp->chgIData(oldp+633,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset_buf),32);
        bufp->chgCData(oldp+634,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel),8);
        bufp->chgIData(oldp+635,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr),32);
        bufp->chgBit(oldp+636,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_renable));
        bufp->chgSData(oldp+637,(((4U == (IData)(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_sel))
                                   ? (0x0000ffffU & 
                                      ((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_146)
                                        ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_0_rdata_out)
                                        : (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_0_rdata_out)))
                                   : 0U)),16);
        bufp->chgBit(oldp+638,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_fifo_deq));
        bufp->chgSData(oldp+639,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_58),16);
        bufp->chgSData(oldp+640,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_59),16);
        bufp->chgCData(oldp+641,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_60),5);
        bufp->chgBit(oldp+642,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_1));
        bufp->chgBit(oldp+643,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_2));
        bufp->chgBit(oldp+644,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_3));
        bufp->chgBit(oldp+645,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_4));
        bufp->chgBit(oldp+646,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_5));
        bufp->chgBit(oldp+647,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_6));
        bufp->chgBit(oldp+648,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_7));
        bufp->chgBit(oldp+649,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_3_stream_ivalid_8));
        bufp->chgBit(oldp+650,(vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_61));
        bufp->chgCData(oldp+651,(vlSelfRef.test__DOT__taketwo__DOT___minus_data_63),5);
        bufp->chgBit(oldp+652,(vlSelfRef.test__DOT__taketwo__DOT___greatereq_data_74));
        bufp->chgSData(oldp+653,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_161___05Fvariable_58),16);
        bufp->chgSData(oldp+654,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_164___05Fvariable_59),16);
        bufp->chgCData(oldp+655,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_167___05Fvariable_60),5);
        bufp->chgQData(oldp+656,(vlSelfRef.test__DOT__taketwo__DOT___sll_data_65),34);
        bufp->chgBit(oldp+658,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_158_greaterthan_61));
        bufp->chgBit(oldp+659,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_159_greatereq_74));
        bufp->chgSData(oldp+660,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_162___05Fdelay_161___05Fvariable_58),16);
        bufp->chgSData(oldp+661,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_165___05Fdelay_164___05Fvariable_59),16);
        bufp->chgCData(oldp+662,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_168___05Fdelay_167___05Fvariable_60),5);
        bufp->chgIData(oldp+663,(vlSelfRef.test__DOT__taketwo__DOT___cond_data_71),32);
        bufp->chgBit(oldp+664,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_160___05Fdelay_159_greatereq_74));
        bufp->chgSData(oldp+665,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_163___05Fdelay_162___05Fdelay_161___05Fvariable_58),16);
        bufp->chgSData(oldp+666,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_166___05Fdelay_165___05Fdelay_164___05Fvariable_59),16);
        bufp->chgCData(oldp+667,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_169___05Fdelay_168___05Fdelay_167___05Fvariable_60),5);
        bufp->chgSData(oldp+668,((0x0000ffffU & (- vlSelfRef.test__DOT__taketwo__DOT___cond_data_71))),16);
        bufp->chgSData(oldp+669,((0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_160___05Fdelay_159_greatereq_74)
                                                  ? vlSelfRef.test__DOT__taketwo__DOT___cond_data_71
                                                  : 
                                                 VL_EXTENDS_II(32,16, 
                                                               (0x0000ffffU 
                                                                & (- vlSelfRef.test__DOT__taketwo__DOT___cond_data_71)))))),16);
        bufp->chgIData(oldp+670,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd1),32);
        bufp->chgIData(oldp+671,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_odata_reg_77),32);
        bufp->chgCData(oldp+672,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_170___05Fdelay_169___05Fdelay_168___05Fdelay_167___05Fvariable_60),5);
        bufp->chgCData(oldp+673,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_171___05Fdelay_170___05Fdelay_169___05Fdelay_168___05F___05Fvariable_60),5);
        bufp->chgCData(oldp+674,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_172___05Fdelay_171___05Fdelay_170___05Fdelay_169___05F___05Fvariable_60),5);
        bufp->chgCData(oldp+675,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_173___05Fdelay_172___05Fdelay_171___05Fdelay_170___05F___05Fvariable_60),5);
        bufp->chgIData(oldp+676,(vlSelfRef.test__DOT__taketwo__DOT___sra_data_78),32);
        bufp->chgQData(oldp+677,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_22),64);
        bufp->chgQData(oldp+679,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_0),64);
        bufp->chgCData(oldp+681,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_1),7);
        bufp->chgIData(oldp+682,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_2),32);
        bufp->chgBit(oldp+683,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_15));
        bufp->chgBit(oldp+684,(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_1));
        bufp->chgBit(oldp+685,(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_2));
        bufp->chgBit(oldp+686,(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_3));
        bufp->chgBit(oldp+687,(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_4));
        bufp->chgBit(oldp+688,(vlSelfRef.test__DOT__taketwo__DOT_____05Facc_0_stream_ivalid_5));
        bufp->chgBit(oldp+689,(vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_3));
        bufp->chgCData(oldp+690,(vlSelfRef.test__DOT__taketwo__DOT___minus_data_5),7);
        bufp->chgQData(oldp+691,(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16),64);
        bufp->chgQData(oldp+693,(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_count_16),33);
        bufp->chgBit(oldp+695,(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_prev_count_max_16));
        bufp->chgBit(oldp+696,(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_reset_cond_16));
        bufp->chgQData(oldp+697,(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_current_count_16),33);
        bufp->chgQData(oldp+699,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___reduceadd_reset_cond_16)
                                   ? 0ULL : vlSelfRef.test__DOT__taketwo__DOT___reduceadd_data_16)),64);
        bufp->chgBit(oldp+701,(vlSelfRef.test__DOT__taketwo__DOT___pulse_data_18));
        bufp->chgQData(oldp+702,(vlSelfRef.test__DOT__taketwo__DOT___pulse_count_18),33);
        bufp->chgBit(oldp+704,(vlSelfRef.test__DOT__taketwo__DOT___pulse_prev_count_max_18));
        bufp->chgBit(oldp+705,(vlSelfRef.test__DOT__taketwo__DOT___pulse_reset_cond_18));
        bufp->chgQData(oldp+706,(vlSelfRef.test__DOT__taketwo__DOT___pulse_current_count_18),33);
        bufp->chgBit(oldp+708,(((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_reset_cond_18)) 
                                & (IData)(vlSelfRef.test__DOT__taketwo__DOT___pulse_data_18))));
        bufp->chgCData(oldp+709,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_182___05Fvariable_1),7);
        bufp->chgWData(oldp+710,(vlSelfRef.test__DOT__taketwo__DOT___sll_data_7),130);
        bufp->chgBit(oldp+715,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_179_greaterthan_3));
        bufp->chgQData(oldp+716,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_180_reduceadd_16),64);
        bufp->chgCData(oldp+718,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_183___05Fdelay_182___05Fvariable_1),7);
        bufp->chgBit(oldp+719,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_186_pulse_18));
        bufp->chgQData(oldp+720,(vlSelfRef.test__DOT__taketwo__DOT___cond_data_13),64);
        bufp->chgQData(oldp+722,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_181___05Fdelay_180_reduceadd_16),64);
        bufp->chgCData(oldp+724,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_184___05Fdelay_183___05Fdelay_182___05Fvariable_1),7);
        bufp->chgBit(oldp+725,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_187___05Fdelay_186_pulse_18));
        bufp->chgQData(oldp+726,(vlSelfRef.test__DOT__taketwo__DOT___plus_data_20),64);
        bufp->chgCData(oldp+728,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_185___05Fdelay_184___05Fdelay_183___05Fdelay_182___05Fvariable_1),7);
        bufp->chgBit(oldp+729,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_188___05Fdelay_187___05Fdelay_186_pulse_18));
        bufp->chgQData(oldp+730,(vlSelfRef.test__DOT__taketwo__DOT___sra_data_21),64);
        bufp->chgBit(oldp+732,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_189___05Fdelay_188___05Fdelay_187___05Fdelay_186_pulse_18));
        bufp->chgQData(oldp+733,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_24),64);
        bufp->chgIData(oldp+735,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_25),32);
        bufp->chgCData(oldp+736,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26),7);
        bufp->chgBit(oldp+737,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_1));
        bufp->chgBit(oldp+738,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_2));
        bufp->chgBit(oldp+739,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_3));
        bufp->chgBit(oldp+740,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_4));
        bufp->chgBit(oldp+741,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_5));
        bufp->chgBit(oldp+742,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_6));
        bufp->chgBit(oldp+743,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_7));
        bufp->chgBit(oldp+744,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmul_rshift_round_clip_2_stream_ivalid_8));
        bufp->chgWData(oldp+745,(vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul1),96);
        bufp->chgWData(oldp+748,(vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27),96);
        bufp->chgCData(oldp+751,((0x0000007fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26) 
                                                 - (IData)(1U)))),7);
        __Vtemp_16[0U] = 1U;
        __Vtemp_16[1U] = 0U;
        __Vtemp_16[2U] = 0U;
        __Vtemp_16[3U] = 0U;
        __Vtemp_16[4U] = 0U;
        VL_SHIFTL_WWI(130,130,7, __Vtemp_17, __Vtemp_16, 
                      (0x0000007fU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26) 
                                      - (IData)(1U))));
        __Vtemp_18[0U] = __Vtemp_17[0U];
        __Vtemp_18[1U] = __Vtemp_17[1U];
        __Vtemp_18[2U] = __Vtemp_17[2U];
        __Vtemp_18[3U] = __Vtemp_17[3U];
        __Vtemp_18[4U] = (3U & __Vtemp_17[4U]);
        bufp->chgWData(oldp+752,(__Vtemp_18),130);
        bufp->chgBit(oldp+757,((0U == (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_26))));
        bufp->chgWData(oldp+758,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_195_sll_33),130);
        bufp->chgCData(oldp+763,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_199___05Fvariable_26),7);
        bufp->chgBit(oldp+764,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_203_eq_45));
        bufp->chgWData(oldp+765,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_196___05Fdelay_195_sll_33),130);
        bufp->chgCData(oldp+770,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_200___05Fdelay_199___05Fvariable_26),7);
        bufp->chgBit(oldp+771,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_204___05Fdelay_203_eq_45));
        bufp->chgWData(oldp+772,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_197___05Fdelay_196___05Fdelay_195_sll_33),130);
        bufp->chgCData(oldp+777,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_201___05Fdelay_200___05Fdelay_199___05Fvariable_26),7);
        bufp->chgBit(oldp+778,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_205___05Fdelay_204___05Fdelay_203_eq_45));
        bufp->chgWData(oldp+779,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33),130);
        bufp->chgCData(oldp+784,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_202___05Fdelay_201___05Fdelay_200___05Fdelay_199___05Fvariable_26),7);
        bufp->chgBit(oldp+785,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_206___05Fdelay_205___05Fdelay_204___05Fdelay_203_eq_45));
        bufp->chgBit(oldp+786,((vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U] 
                                >> 0x0000001fU)));
        bufp->chgCData(oldp+787,(((vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U] 
                                   >> 0x0000001fU) ? 3U
                                   : 0U)),2);
        VL_EXTENDS_WW(130,96, __Vtemp_21, vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27);
        __Vtemp_23[0U] = __Vtemp_21[0U];
        __Vtemp_23[1U] = __Vtemp_21[1U];
        __Vtemp_23[2U] = __Vtemp_21[2U];
        __Vtemp_23[3U] = __Vtemp_21[3U];
        __Vtemp_24[0U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[0U];
        __Vtemp_24[1U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[1U];
        __Vtemp_24[2U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[2U];
        __Vtemp_24[3U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[3U];
        VL_ADD_W(4, __Vtemp_25, __Vtemp_23, __Vtemp_24);
        __Vtemp_26[0U] = __Vtemp_25[0U];
        __Vtemp_26[1U] = __Vtemp_25[1U];
        __Vtemp_26[2U] = __Vtemp_25[2U];
        __Vtemp_26[3U] = (1U & __Vtemp_25[3U]);
        bufp->chgWData(oldp+788,(__Vtemp_26),97);
        VL_EXTENDS_WW(130,96, __Vtemp_29, vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27);
        __Vtemp_31[0U] = __Vtemp_29[0U];
        __Vtemp_31[1U] = __Vtemp_29[1U];
        __Vtemp_31[2U] = __Vtemp_29[2U];
        __Vtemp_31[3U] = __Vtemp_29[3U];
        __Vtemp_32[0U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[0U];
        __Vtemp_32[1U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[1U];
        __Vtemp_32[2U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[2U];
        __Vtemp_32[3U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[3U];
        VL_ADD_W(4, __Vtemp_33, __Vtemp_31, __Vtemp_32);
        VL_EXTENDS_WI(97,2, __Vtemp_34, ((vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U] 
                                          >> 0x0000001fU)
                                          ? 3U : 0U));
        VL_ADD_W(4, __Vtemp_35, __Vtemp_33, __Vtemp_34);
        __Vtemp_36[0U] = __Vtemp_35[0U];
        __Vtemp_36[1U] = __Vtemp_35[1U];
        __Vtemp_36[2U] = __Vtemp_35[2U];
        __Vtemp_36[3U] = (1U & __Vtemp_35[3U]);
        bufp->chgWData(oldp+792,(__Vtemp_36),97);
        VL_EXTENDS_WW(130,96, __Vtemp_40, vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27);
        __Vtemp_42[0U] = __Vtemp_40[0U];
        __Vtemp_42[1U] = __Vtemp_40[1U];
        __Vtemp_42[2U] = __Vtemp_40[2U];
        __Vtemp_42[3U] = __Vtemp_40[3U];
        __Vtemp_43[0U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[0U];
        __Vtemp_43[1U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[1U];
        __Vtemp_43[2U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[2U];
        __Vtemp_43[3U] = vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_198___05Fdelay_197___05Fdelay_196___05Fdelay_195_sll_33[3U];
        VL_ADD_W(4, __Vtemp_44, __Vtemp_42, __Vtemp_43);
        VL_EXTENDS_WI(97,2, __Vtemp_45, ((vlSelfRef.test__DOT__taketwo__DOT___times_mul_odata_reg_27[2U] 
                                          >> 0x0000001fU)
                                          ? 3U : 0U));
        VL_ADD_W(4, __Vtemp_46, __Vtemp_44, __Vtemp_45);
        __Vtemp_47[0U] = __Vtemp_46[0U];
        __Vtemp_47[1U] = __Vtemp_46[1U];
        __Vtemp_47[2U] = __Vtemp_46[2U];
        __Vtemp_47[3U] = (1U & __Vtemp_46[3U]);
        VL_SHIFTRS_WWI(97,97,7, __Vtemp_48, __Vtemp_47, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_202___05Fdelay_201___05Fdelay_200___05Fdelay_199___05Fvariable_26));
        __Vtemp_50[0U] = __Vtemp_48[0U];
        __Vtemp_50[1U] = __Vtemp_48[1U];
        __Vtemp_50[2U] = __Vtemp_48[2U];
        bufp->chgWData(oldp+796,(__Vtemp_50),96);
        bufp->chgWData(oldp+799,(vlSelfRef.test__DOT__taketwo__DOT___cond_data_46),96);
        bufp->chgBit(oldp+802,(vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_47));
        bufp->chgBit(oldp+803,(vlSelfRef.test__DOT__taketwo__DOT___lessthan_data_51));
        bufp->chgBit(oldp+804,(vlSelfRef.test__DOT__taketwo__DOT___greatereq_data_55));
        bufp->chgWData(oldp+805,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_207_cond_46),96);
        bufp->chgWData(oldp+808,(vlSelfRef.test__DOT__taketwo__DOT___cond_data_49),96);
        bufp->chgWData(oldp+811,(vlSelfRef.test__DOT__taketwo__DOT___cond_data_53),96);
        bufp->chgBit(oldp+814,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_208_greatereq_55));
        bufp->chgSData(oldp+815,(vlSelfRef.test__DOT__taketwo__DOT___cond_data_57),16);
        bufp->chgQData(oldp+816,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_count),33);
        bufp->chgCData(oldp+818,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_mode),5);
        bufp->chgIData(oldp+819,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset),32);
        bufp->chgQData(oldp+820,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size),33);
        bufp->chgIData(oldp+822,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride),32);
        bufp->chgIData(oldp+823,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_offset_buf),32);
        bufp->chgQData(oldp+824,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_size_buf),33);
        bufp->chgIData(oldp+826,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_stride_buf),32);
        bufp->chgCData(oldp+827,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_sel),8);
        bufp->chgIData(oldp+828,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr),32);
        bufp->chgBit(oldp+829,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wenable));
        bufp->chgSData(oldp+830,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_wdata),16);
        bufp->chgBit(oldp+831,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fifo_enq));
        bufp->chgBit(oldp+832,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_wenable));
        bufp->chgBit(oldp+833,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_27_sink_fifo_enq));
        bufp->chgIData(oldp+834,(vlSelfRef.test__DOT__taketwo__DOT__main_fsm),32);
        bufp->chgIData(oldp+835,(vlSelfRef.test__DOT__taketwo__DOT__internal_state_counter),32);
        bufp->chgIData(oldp+836,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr),32);
        bufp->chgIData(oldp+837,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0),32);
        bufp->chgIData(oldp+838,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1),32);
        bufp->chgIData(oldp+839,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2),32);
        bufp->chgIData(oldp+840,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3),32);
        bufp->chgIData(oldp+841,(vlSelfRef.test__DOT__taketwo__DOT__control_matmul_11),32);
        bufp->chgBit(oldp+842,(vlSelfRef.test__DOT__taketwo__DOT___control_matmul_11_called));
        bufp->chgIData(oldp+843,((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
                                  + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row)),32);
        bufp->chgIData(oldp+844,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row),32);
        bufp->chgIData(oldp+845,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat),32);
        bufp->chgIData(oldp+846,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_base_offset),32);
        bufp->chgIData(oldp+847,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_stream_num_ops),32);
        bufp->chgIData(oldp+848,((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_val 
                                  + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
                                     + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
                                        + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
                                           + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och))))),32);
        bufp->chgIData(oldp+849,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_val),32);
        bufp->chgIData(oldp+850,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col),32);
        bufp->chgIData(oldp+851,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row),32);
        bufp->chgIData(oldp+852,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat),32);
        bufp->chgIData(oldp+853,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och),32);
        bufp->chgBit(oldp+854,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0));
        bufp->chgIData(oldp+855,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_comp_count),32);
        bufp->chgIData(oldp+856,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_sync_out_count),32);
        bufp->chgIData(oldp+857,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_write_count),32);
        bufp->chgIData(oldp+858,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size),32);
        bufp->chgIData(oldp+859,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_count),32);
        bufp->chgIData(oldp+860,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count),32);
        bufp->chgIData(oldp+861,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_bat_count),32);
        bufp->chgIData(oldp+862,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count),32);
        bufp->chgBit(oldp+863,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_select));
        bufp->chgBit(oldp+864,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select));
        bufp->chgIData(oldp+865,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_col_count),32);
        bufp->chgIData(oldp+866,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_row_count),32);
        bufp->chgIData(oldp+867,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_ram_select),32);
        bufp->chgIData(oldp+868,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_count),32);
        bufp->chgIData(oldp+869,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_bat_count),32);
        bufp->chgIData(oldp+870,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_och_count),32);
        bufp->chgBit(oldp+871,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select));
        bufp->chgIData(oldp+872,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_act_local_0),32);
        bufp->chgIData(oldp+873,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_val),32);
        bufp->chgIData(oldp+874,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_col),32);
        bufp->chgIData(oldp+875,((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_col 
                                  + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_val)),32);
        bufp->chgIData(oldp+876,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_0),32);
        bufp->chgIData(oldp+877,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_dma_offset_0),32);
        bufp->chgIData(oldp+878,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset),32);
        bufp->chgIData(oldp+879,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_dma_offset),32);
        bufp->chgBit(oldp+880,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page));
        bufp->chgIData(oldp+881,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset),32);
        bufp->chgIData(oldp+882,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_dma_offset),32);
        bufp->chgIData(oldp+883,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_laddr_offset),32);
        bufp->chgBit(oldp+884,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_filter));
        bufp->chgBit(oldp+885,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_read_act));
        bufp->chgBit(oldp+886,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_comp));
        bufp->chgBit(oldp+887,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_skip_write_out));
        bufp->chgIData(oldp+888,(VL_SHIFTR_III(32,32,32, 
                                               (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                                + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2), 2U)),32);
        bufp->chgIData(oldp+889,((0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                                 + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_2))),32);
        bufp->chgIData(oldp+890,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fsm),32);
        bufp->chgQData(oldp+891,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cur_global_size),33);
        bufp->chgBit(oldp+893,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_cont));
        __Vtemp_53[0U] = vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_blocksize;
        __Vtemp_53[1U] = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size);
        __Vtemp_53[2U] = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride 
                           << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_size 
                                             >> 0x00000020U)));
        __Vtemp_53[3U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr)))) 
                           << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_stride 
                                     >> 0x0000001fU));
        __Vtemp_53[4U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr)))) 
                           >> 0x0000001fU) | ((IData)(
                                                      ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_op_sel)) 
                                                         << 0x00000020U) 
                                                        | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_local_addr))) 
                                                       >> 0x00000020U)) 
                                              << 1U));
        bufp->chgWData(oldp+894,(__Vtemp_53),137);
        bufp->chgBit(oldp+899,((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_req_fifo_almost_full)))));
        bufp->chgBit(oldp+900,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_63_1));
        bufp->chgIData(oldp+901,(VL_SHIFTR_III(32,32,32, vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr, 2U)),32);
        bufp->chgIData(oldp+902,((0xfffffffcU & vlSelfRef.test__DOT__taketwo__DOT___maxi_read_global_addr)),32);
        bufp->chgBit(oldp+903,(vlSelfRef.test__DOT__taketwo__DOT___maxi_raddr_cond_0_1));
        bufp->chgIData(oldp+904,(vlSelfRef.test__DOT__taketwo__DOT___maxi_read_data_fsm),32);
        bufp->chgIData(oldp+905,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_0),32);
        bufp->chgCData(oldp+906,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_76),7);
        bufp->chgCData(oldp+907,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_77),7);
        bufp->chgQData(oldp+908,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_78),33);
        bufp->chgBit(oldp+910,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_79));
        bufp->chgIData(oldp+911,(VL_SHIFTR_III(32,32,32, 
                                               (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                                + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3), 2U)),32);
        bufp->chgIData(oldp+912,((0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                                 + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_3))),32);
        bufp->chgIData(oldp+913,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_fsm_1),32);
        bufp->chgCData(oldp+914,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_addr_82),7);
        bufp->chgCData(oldp+915,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_stride_83),7);
        bufp->chgQData(oldp+916,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_length_84),33);
        bufp->chgBit(oldp+918,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_done_85));
        bufp->chgSData(oldp+919,((0x000001ffU & VL_SHIFTR_III(9,9,32, 
                                                              (0x000001ffU 
                                                               & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52), 1U))),9);
        bufp->chgBit(oldp+920,((1U & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_52)));
        bufp->chgSData(oldp+921,(vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_88),9);
        bufp->chgIData(oldp+922,(VL_SHIFTR_III(32,32,32, 
                                               (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 
                                                + (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                                   + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_base_offset)), 2U)),32);
        bufp->chgIData(oldp+923,((0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_1 
                                                 + 
                                                 (vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr 
                                                  + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_base_offset)))),32);
        bufp->chgIData(oldp+924,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_2),32);
        bufp->chgSData(oldp+925,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_91),9);
        bufp->chgSData(oldp+926,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_92),9);
        bufp->chgQData(oldp+927,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_93),33);
        bufp->chgBit(oldp+929,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_94));
        bufp->chgCData(oldp+930,((0x000000ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_91) 
                                                 >> 1U))),8);
        bufp->chgSData(oldp+931,((0x0000ffffU & (IData)(vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21))),16);
        bufp->chgSData(oldp+932,((0x0000ffffU & (IData)(
                                                        (vlSelfRef.test__DOT__taketwo__DOT___sb_maxi_readdata_data_21 
                                                         >> 0x00000010U)))),16);
        bufp->chgIData(oldp+933,(((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)
                                   ? 0U : (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 
                                           + (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
                                              + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row)))),32);
        bufp->chgBit(oldp+934,((1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count)));
        bufp->chgBit(oldp+935,(((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)) 
                                & (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count))));
        bufp->chgBit(oldp+936,(((~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_prev_row_select)) 
                                & (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_dma_flag_0))));
        bufp->chgCData(oldp+937,((0x0000007fU & VL_SHIFTR_III(7,7,32, 
                                                              (0x0000007fU 
                                                               & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51), 1U))),7);
        bufp->chgBit(oldp+938,((1U & vlSelfRef.test__DOT__taketwo__DOT____VdfgRegularize_h1c6c32d7_0_51)));
        bufp->chgCData(oldp+939,(vlSelfRef.test__DOT__taketwo__DOT___dma_read_packed_local_packed_size_101),7);
        bufp->chgIData(oldp+940,(VL_SHIFTR_III(32,32,32, 
                                               (((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)
                                                  ? 0U
                                                  : 
                                                 (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 
                                                  + 
                                                  (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
                                                   + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row))) 
                                                + vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr), 2U)),32);
        bufp->chgIData(oldp+941,((0xfffffffcU & (((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)
                                                   ? 0U
                                                   : 
                                                  (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_arg_objaddr_0 
                                                   + 
                                                   (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_bat 
                                                    + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_base_offset_row))) 
                                                 + vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr))),32);
        bufp->chgIData(oldp+942,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_fsm_3),32);
        bufp->chgSData(oldp+943,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_104),9);
        bufp->chgSData(oldp+944,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_stride_105),9);
        bufp->chgQData(oldp+945,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_length_106),33);
        bufp->chgBit(oldp+947,(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_done_107));
        bufp->chgCData(oldp+948,((0x000000ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__write_burst_packed_addr_104) 
                                                 >> 1U))),8);
        bufp->chgIData(oldp+949,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm),32);
        bufp->chgIData(oldp+950,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_filter_page_comp_offset_buf),32);
        bufp->chgIData(oldp+951,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_act_page_comp_offset_buf_0),32);
        bufp->chgIData(oldp+952,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset_buf),32);
        bufp->chgIData(oldp+953,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count_buf),32);
        bufp->chgBit(oldp+954,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select_buf));
        bufp->chgIData(oldp+955,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_och_count_buf),32);
        bufp->chgBit(oldp+956,(((1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_col_count) 
                                | (1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_count_buf))));
        bufp->chgBit(oldp+957,(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_pad_masks));
        bufp->chgCData(oldp+958,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_79),7);
        bufp->chgBit(oldp+959,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_80));
        bufp->chgBit(oldp+960,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_81));
        bufp->chgBit(oldp+961,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_82));
        bufp->chgBit(oldp+962,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_83));
        bufp->chgBit(oldp+963,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_84));
        bufp->chgBit(oldp+964,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_94));
        bufp->chgIData(oldp+965,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_95),32);
        bufp->chgBit(oldp+966,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_101));
        bufp->chgIData(oldp+967,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_102),32);
        bufp->chgBit(oldp+968,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_108));
        bufp->chgSData(oldp+969,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_109),16);
        bufp->chgBit(oldp+970,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_115));
        bufp->chgSData(oldp+971,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_116),16);
        bufp->chgBit(oldp+972,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_122));
        bufp->chgSData(oldp+973,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_123),16);
        bufp->chgBit(oldp+974,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_129));
        bufp->chgBit(oldp+975,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_130));
        bufp->chgCData(oldp+976,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_131),5);
        bufp->chgCData(oldp+977,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_132),2);
        bufp->chgSData(oldp+978,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_133),16);
        bufp->chgSData(oldp+979,(vlSelfRef.test__DOT__taketwo__DOT_____05Fvariable_wdata_147),16);
        bufp->chgBit(oldp+980,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_1));
        bufp->chgBit(oldp+981,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_2));
        bufp->chgBit(oldp+982,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_3));
        bufp->chgBit(oldp+983,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_4));
        bufp->chgBit(oldp+984,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_5));
        bufp->chgBit(oldp+985,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_6));
        bufp->chgBit(oldp+986,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_7));
        bufp->chgBit(oldp+987,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_8));
        bufp->chgBit(oldp+988,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_9));
        bufp->chgBit(oldp+989,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_10));
        bufp->chgBit(oldp+990,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_11));
        bufp->chgBit(oldp+991,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_12));
        bufp->chgBit(oldp+992,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_13));
        bufp->chgBit(oldp+993,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_14));
        bufp->chgBit(oldp+994,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_15));
        bufp->chgBit(oldp+995,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_16));
        bufp->chgBit(oldp+996,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_17));
        bufp->chgBit(oldp+997,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_18));
        bufp->chgBit(oldp+998,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_19));
        bufp->chgBit(oldp+999,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_20));
        bufp->chgBit(oldp+1000,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_21));
        bufp->chgBit(oldp+1001,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_22));
        bufp->chgBit(oldp+1002,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_23));
        bufp->chgBit(oldp+1003,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_24));
        bufp->chgBit(oldp+1004,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_25));
        bufp->chgBit(oldp+1005,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_26));
        bufp->chgBit(oldp+1006,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_27));
        bufp->chgBit(oldp+1007,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_28));
        bufp->chgBit(oldp+1008,(vlSelfRef.test__DOT__taketwo__DOT_____05Fstream_matmul_11_stream_ivalid_29));
        bufp->chgBit(oldp+1009,(vlSelfRef.test__DOT__taketwo__DOT___eq_data_134));
        bufp->chgBit(oldp+1010,(vlSelfRef.test__DOT__taketwo__DOT___eq_data_138));
        bufp->chgSData(oldp+1011,(vlSelfRef.test__DOT__taketwo__DOT___plus_data_174),16);
        bufp->chgSData(oldp+1012,(vlSelfRef.test__DOT__taketwo__DOT___plus_data_190),16);
        bufp->chgSData(oldp+1013,(vlSelfRef.test__DOT__taketwo__DOT___plus_data_209),16);
        bufp->chgBit(oldp+1014,(vlSelfRef.test__DOT__taketwo__DOT___eq_data_215));
        bufp->chgBit(oldp+1015,(vlSelfRef.test__DOT__taketwo__DOT___eq_data_218));
        bufp->chgSData(oldp+1016,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133),16);
        bufp->chgBit(oldp+1017,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_223_pointer_153));
        bufp->chgSData(oldp+1018,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_224_reinterpretcast_152),16);
        bufp->chgBit(oldp+1019,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_225___05Fvariable_84));
        bufp->chgCData(oldp+1020,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_246___05Fvariable_79),7);
        bufp->chgIData(oldp+1021,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_257_cond_100),32);
        bufp->chgIData(oldp+1022,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_274_cond_107),32);
        bufp->chgSData(oldp+1023,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_134)
                                    ? (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133)
                                    : 0U)),16);
        bufp->chgSData(oldp+1024,(((IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_138)
                                    ? ((IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_134)
                                        ? (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133)
                                        : 0U) : 0U)),16);
        bufp->chgSData(oldp+1025,(((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_223_pointer_153)
                                    ? 0U : ((IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_138)
                                             ? ((IData)(vlSelfRef.test__DOT__taketwo__DOT___eq_data_134)
                                                 ? (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_222___05Fvariable_133)
                                                 : 0U)
                                             : 0U))),16);
        bufp->chgBit(oldp+1026,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_226___05Fdelay_225___05Fvariable_84));
        bufp->chgSData(oldp+1027,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_236_plus_190),16);
        bufp->chgCData(oldp+1028,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_247___05Fdelay_246___05Fvariable_79),7);
        bufp->chgIData(oldp+1029,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_258___05Fdelay_257_cond_100),32);
        bufp->chgIData(oldp+1030,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_275___05Fdelay_274_cond_107),32);
        bufp->chgSData(oldp+1031,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_292_plus_209),16);
        bufp->chgBit(oldp+1032,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_310_eq_215));
        bufp->chgBit(oldp+1033,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_339_eq_218));
        bufp->chgBit(oldp+1034,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_227___05Fdelay_226___05Fdelay_225___05Fvariable_84));
        bufp->chgSData(oldp+1035,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_237___05Fdelay_236_plus_190),16);
        bufp->chgCData(oldp+1036,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_248___05Fdelay_247___05Fdelay_246___05Fvariable_79),7);
        bufp->chgIData(oldp+1037,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_259___05Fdelay_258___05Fdelay_257_cond_100),32);
        bufp->chgIData(oldp+1038,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_276___05Fdelay_275___05Fdelay_274_cond_107),32);
        bufp->chgSData(oldp+1039,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_293___05Fdelay_292_plus_209),16);
        bufp->chgBit(oldp+1040,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_311___05Fdelay_310_eq_215));
        bufp->chgBit(oldp+1041,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_340___05Fdelay_339_eq_218));
        bufp->chgBit(oldp+1042,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_228___05Fdelay_227___05Fdelay_226___05Fdelay_225___05Fvariable_84));
        bufp->chgSData(oldp+1043,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_238___05Fdelay_237___05Fdelay_236_plus_190),16);
        bufp->chgCData(oldp+1044,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_249___05Fdelay_248___05Fdelay_247___05Fdelay_246___05Fvariable_79),7);
        bufp->chgIData(oldp+1045,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_260___05Fdelay_259___05Fdelay_258___05Fdelay_257_cond_100),32);
        bufp->chgIData(oldp+1046,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_277___05Fdelay_276___05Fdelay_275___05Fdelay_274_cond_107),32);
        bufp->chgSData(oldp+1047,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_294___05Fdelay_293___05Fdelay_292_plus_209),16);
        bufp->chgBit(oldp+1048,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_312___05Fdelay_311___05Fdelay_310_eq_215));
        bufp->chgBit(oldp+1049,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_341___05Fdelay_340___05Fdelay_339_eq_218));
        bufp->chgBit(oldp+1050,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_229___05Fdelay_228___05Fdelay_227___05Fdelay_226___05F___05Fvariable_84));
        bufp->chgSData(oldp+1051,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_239___05Fdelay_238___05Fdelay_237___05Fdelay_236_plus_190),16);
        bufp->chgCData(oldp+1052,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_250___05Fdelay_249___05Fdelay_248___05Fdelay_247___05F___05Fvariable_79),7);
        bufp->chgIData(oldp+1053,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_261___05Fdelay_260___05Fdelay_259___05Fdelay_258___05F_cond_100),32);
        bufp->chgIData(oldp+1054,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_278___05Fdelay_277___05Fdelay_276___05Fdelay_275___05F_cond_107),32);
        bufp->chgSData(oldp+1055,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_295___05Fdelay_294___05Fdelay_293___05Fdelay_292_plus_209),16);
        bufp->chgBit(oldp+1056,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_313___05Fdelay_312___05Fdelay_311___05Fdelay_310_eq_215));
        bufp->chgBit(oldp+1057,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_342___05Fdelay_341___05Fdelay_340___05Fdelay_339_eq_218));
        bufp->chgBit(oldp+1058,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_230___05Fdelay_229___05Fdelay_228___05Fdelay_227___05F___05Fvariable_84));
        bufp->chgSData(oldp+1059,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_240___05Fdelay_239___05Fdelay_238___05Fdelay_237___05F_plus_190),16);
        bufp->chgCData(oldp+1060,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_251___05Fdelay_250___05Fdelay_249___05Fdelay_248___05F___05Fvariable_79),7);
        bufp->chgIData(oldp+1061,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_262___05Fdelay_261___05Fdelay_260___05Fdelay_259___05F_cond_100),32);
        bufp->chgIData(oldp+1062,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_279___05Fdelay_278___05Fdelay_277___05Fdelay_276___05F_cond_107),32);
        bufp->chgSData(oldp+1063,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_296___05Fdelay_295___05Fdelay_294___05Fdelay_293___05F_plus_209),16);
        bufp->chgBit(oldp+1064,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_314___05Fdelay_313___05Fdelay_312___05Fdelay_311___05F_eq_215));
        bufp->chgBit(oldp+1065,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_343___05Fdelay_342___05Fdelay_341___05Fdelay_340___05F_eq_218));
        bufp->chgBit(oldp+1066,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_231___05Fdelay_230___05Fdelay_229___05Fdelay_228___05F___05Fvariable_84));
        bufp->chgSData(oldp+1067,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_241___05Fdelay_240___05Fdelay_239___05Fdelay_238___05F_plus_190),16);
        bufp->chgCData(oldp+1068,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_252___05Fdelay_251___05Fdelay_250___05Fdelay_249___05F___05Fvariable_79),7);
        bufp->chgIData(oldp+1069,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_263___05Fdelay_262___05Fdelay_261___05Fdelay_260___05F_cond_100),32);
        bufp->chgIData(oldp+1070,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_280___05Fdelay_279___05Fdelay_278___05Fdelay_277___05F_cond_107),32);
        bufp->chgSData(oldp+1071,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_297___05Fdelay_296___05Fdelay_295___05Fdelay_294___05F_plus_209),16);
        bufp->chgBit(oldp+1072,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_315___05Fdelay_314___05Fdelay_313___05Fdelay_312___05F_eq_215));
        bufp->chgBit(oldp+1073,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_344___05Fdelay_343___05Fdelay_342___05Fdelay_341___05F_eq_218));
        bufp->chgBit(oldp+1074,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_232___05Fdelay_231___05Fdelay_230___05Fdelay_229___05F___05Fvariable_84));
        bufp->chgSData(oldp+1075,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_242___05Fdelay_241___05Fdelay_240___05Fdelay_239___05F_plus_190),16);
        bufp->chgCData(oldp+1076,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_253___05Fdelay_252___05Fdelay_251___05Fdelay_250___05F___05Fvariable_79),7);
        bufp->chgIData(oldp+1077,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_264___05Fdelay_263___05Fdelay_262___05Fdelay_261___05F_cond_100),32);
        bufp->chgIData(oldp+1078,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_281___05Fdelay_280___05Fdelay_279___05Fdelay_278___05F_cond_107),32);
        bufp->chgSData(oldp+1079,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_298___05Fdelay_297___05Fdelay_296___05Fdelay_295___05F_plus_209),16);
        bufp->chgBit(oldp+1080,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_316___05Fdelay_315___05Fdelay_314___05Fdelay_313___05F_eq_215));
        bufp->chgBit(oldp+1081,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_345___05Fdelay_344___05Fdelay_343___05Fdelay_342___05F_eq_218));
        bufp->chgBit(oldp+1082,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_233___05Fdelay_232___05Fdelay_231___05Fdelay_230___05F___05Fvariable_84));
        bufp->chgSData(oldp+1083,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_243___05Fdelay_242___05Fdelay_241___05Fdelay_240___05F_plus_190),16);
        bufp->chgCData(oldp+1084,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_254___05Fdelay_253___05Fdelay_252___05Fdelay_251___05F___05Fvariable_79),7);
        bufp->chgIData(oldp+1085,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_265___05Fdelay_264___05Fdelay_263___05Fdelay_262___05F_cond_100),32);
        bufp->chgIData(oldp+1086,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_282___05Fdelay_281___05Fdelay_280___05Fdelay_279___05F_cond_107),32);
        bufp->chgSData(oldp+1087,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_299___05Fdelay_298___05Fdelay_297___05Fdelay_296___05F_plus_209),16);
        bufp->chgBit(oldp+1088,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_317___05Fdelay_316___05Fdelay_315___05Fdelay_314___05F_eq_215));
        bufp->chgBit(oldp+1089,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_346___05Fdelay_345___05Fdelay_344___05Fdelay_343___05F_eq_218));
        bufp->chgBit(oldp+1090,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_234___05Fdelay_233___05Fdelay_232___05Fdelay_231___05F___05Fvariable_84));
        bufp->chgSData(oldp+1091,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_244___05Fdelay_243___05Fdelay_242___05Fdelay_241___05F_plus_190),16);
        bufp->chgCData(oldp+1092,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_255___05Fdelay_254___05Fdelay_253___05Fdelay_252___05F___05Fvariable_79),7);
        bufp->chgIData(oldp+1093,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_266___05Fdelay_265___05Fdelay_264___05Fdelay_263___05F_cond_100),32);
        bufp->chgIData(oldp+1094,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_283___05Fdelay_282___05Fdelay_281___05Fdelay_280___05F_cond_107),32);
        bufp->chgSData(oldp+1095,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_300___05Fdelay_299___05Fdelay_298___05Fdelay_297___05F_plus_209),16);
        bufp->chgBit(oldp+1096,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_318___05Fdelay_317___05Fdelay_316___05Fdelay_315___05F_eq_215));
        bufp->chgBit(oldp+1097,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_347___05Fdelay_346___05Fdelay_345___05Fdelay_344___05F_eq_218));
        bufp->chgBit(oldp+1098,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_235___05Fdelay_234___05Fdelay_233___05Fdelay_232___05F___05Fvariable_84));
        bufp->chgSData(oldp+1099,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_245___05Fdelay_244___05Fdelay_243___05Fdelay_242___05F_plus_190),16);
        bufp->chgCData(oldp+1100,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_256___05Fdelay_255___05Fdelay_254___05Fdelay_253___05F___05Fvariable_79),7);
        bufp->chgIData(oldp+1101,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_267___05Fdelay_266___05Fdelay_265___05Fdelay_264___05F_cond_100),32);
        bufp->chgIData(oldp+1102,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_284___05Fdelay_283___05Fdelay_282___05Fdelay_281___05F_cond_107),32);
        bufp->chgSData(oldp+1103,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_301___05Fdelay_300___05Fdelay_299___05Fdelay_298___05F_plus_209),16);
        bufp->chgBit(oldp+1104,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_319___05Fdelay_318___05Fdelay_317___05Fdelay_316___05F_eq_215));
        bufp->chgBit(oldp+1105,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_348___05Fdelay_347___05Fdelay_346___05Fdelay_345___05F_eq_218));
        bufp->chgIData(oldp+1106,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_268___05Fdelay_267___05Fdelay_266___05Fdelay_265___05F_cond_100),32);
        bufp->chgIData(oldp+1107,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_285___05Fdelay_284___05Fdelay_283___05Fdelay_282___05F_cond_107),32);
        bufp->chgSData(oldp+1108,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_302___05Fdelay_301___05Fdelay_300___05Fdelay_299___05F_plus_209),16);
        bufp->chgBit(oldp+1109,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_320___05Fdelay_319___05Fdelay_318___05Fdelay_317___05F_eq_215));
        bufp->chgBit(oldp+1110,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_349___05Fdelay_348___05Fdelay_347___05Fdelay_346___05F_eq_218));
        bufp->chgIData(oldp+1111,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_269___05Fdelay_268___05Fdelay_267___05Fdelay_266___05F_cond_100),32);
        bufp->chgIData(oldp+1112,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_286___05Fdelay_285___05Fdelay_284___05Fdelay_283___05F_cond_107),32);
        bufp->chgSData(oldp+1113,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_303___05Fdelay_302___05Fdelay_301___05Fdelay_300___05F_plus_209),16);
        bufp->chgBit(oldp+1114,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_321___05Fdelay_320___05Fdelay_319___05Fdelay_318___05F_eq_215));
        bufp->chgBit(oldp+1115,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_350___05Fdelay_349___05Fdelay_348___05Fdelay_347___05F_eq_218));
        bufp->chgIData(oldp+1116,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_270___05Fdelay_269___05Fdelay_268___05Fdelay_267___05F_cond_100),32);
        bufp->chgIData(oldp+1117,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_287___05Fdelay_286___05Fdelay_285___05Fdelay_284___05F_cond_107),32);
        bufp->chgSData(oldp+1118,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_304___05Fdelay_303___05Fdelay_302___05Fdelay_301___05F_plus_209),16);
        bufp->chgBit(oldp+1119,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_322___05Fdelay_321___05Fdelay_320___05Fdelay_319___05F_eq_215));
        bufp->chgBit(oldp+1120,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_351___05Fdelay_350___05Fdelay_349___05Fdelay_348___05F_eq_218));
        bufp->chgIData(oldp+1121,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_271___05Fdelay_270___05Fdelay_269___05Fdelay_268___05F_cond_100),32);
        bufp->chgIData(oldp+1122,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_288___05Fdelay_287___05Fdelay_286___05Fdelay_285___05F_cond_107),32);
        bufp->chgSData(oldp+1123,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_305___05Fdelay_304___05Fdelay_303___05Fdelay_302___05F_plus_209),16);
        bufp->chgBit(oldp+1124,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_323___05Fdelay_322___05Fdelay_321___05Fdelay_320___05F_eq_215));
        bufp->chgBit(oldp+1125,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_352___05Fdelay_351___05Fdelay_350___05Fdelay_349___05F_eq_218));
        bufp->chgIData(oldp+1126,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_272___05Fdelay_271___05Fdelay_270___05Fdelay_269___05F_cond_100),32);
        bufp->chgIData(oldp+1127,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_289___05Fdelay_288___05Fdelay_287___05Fdelay_286___05F_cond_107),32);
        bufp->chgSData(oldp+1128,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_306___05Fdelay_305___05Fdelay_304___05Fdelay_303___05F_plus_209),16);
        bufp->chgBit(oldp+1129,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_324___05Fdelay_323___05Fdelay_322___05Fdelay_321___05F_eq_215));
        bufp->chgBit(oldp+1130,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_353___05Fdelay_352___05Fdelay_351___05Fdelay_350___05F_eq_218));
        bufp->chgIData(oldp+1131,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_273___05Fdelay_272___05Fdelay_271___05Fdelay_270___05F_cond_100),32);
        bufp->chgIData(oldp+1132,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_290___05Fdelay_289___05Fdelay_288___05Fdelay_287___05F_cond_107),32);
        bufp->chgSData(oldp+1133,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_307___05Fdelay_306___05Fdelay_305___05Fdelay_304___05F_plus_209),16);
        bufp->chgBit(oldp+1134,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_325___05Fdelay_324___05Fdelay_323___05Fdelay_322___05F_eq_215));
        bufp->chgBit(oldp+1135,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_354___05Fdelay_353___05Fdelay_352___05Fdelay_351___05F_eq_218));
        bufp->chgQData(oldp+1136,(vlSelfRef.test__DOT__taketwo__DOT___plus_data_193),64);
        bufp->chgIData(oldp+1138,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_291___05Fdelay_290___05Fdelay_289___05Fdelay_288___05F_cond_107),32);
        bufp->chgSData(oldp+1139,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_308___05Fdelay_307___05Fdelay_306___05Fdelay_305___05F_plus_209),16);
        bufp->chgBit(oldp+1140,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_326___05Fdelay_325___05Fdelay_324___05Fdelay_323___05F_eq_215));
        bufp->chgBit(oldp+1141,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_355___05Fdelay_354___05Fdelay_353___05Fdelay_352___05F_eq_218));
        bufp->chgBit(oldp+1142,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_367___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1143,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_327___05Fdelay_326___05Fdelay_325___05Fdelay_324___05F_eq_215));
        bufp->chgBit(oldp+1144,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_356___05Fdelay_355___05Fdelay_354___05Fdelay_353___05F_eq_218));
        bufp->chgBit(oldp+1145,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_368___05Fdelay_367___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1146,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_328___05Fdelay_327___05Fdelay_326___05Fdelay_325___05F_eq_215));
        bufp->chgBit(oldp+1147,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_357___05Fdelay_356___05Fdelay_355___05Fdelay_354___05F_eq_218));
        bufp->chgBit(oldp+1148,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_369___05Fdelay_368___05Fdelay_367___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1149,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_329___05Fdelay_328___05Fdelay_327___05Fdelay_326___05F_eq_215));
        bufp->chgBit(oldp+1150,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_358___05Fdelay_357___05Fdelay_356___05Fdelay_355___05F_eq_218));
        bufp->chgBit(oldp+1151,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_370___05Fdelay_369___05Fdelay_368___05F___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1152,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_330___05Fdelay_329___05Fdelay_328___05Fdelay_327___05F_eq_215));
        bufp->chgBit(oldp+1153,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_359___05Fdelay_358___05Fdelay_357___05Fdelay_356___05F_eq_218));
        bufp->chgBit(oldp+1154,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_371___05Fdelay_370___05Fdelay_369___05F___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1155,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_331___05Fdelay_330___05Fdelay_329___05Fdelay_328___05F_eq_215));
        bufp->chgBit(oldp+1156,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_360___05Fdelay_359___05Fdelay_358___05Fdelay_357___05F_eq_218));
        bufp->chgBit(oldp+1157,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_372___05Fdelay_371___05Fdelay_370___05F___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1158,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_332___05Fdelay_331___05Fdelay_330___05Fdelay_329___05F_eq_215));
        bufp->chgBit(oldp+1159,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_361___05Fdelay_360___05Fdelay_359___05Fdelay_358___05F_eq_218));
        bufp->chgBit(oldp+1160,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_373___05Fdelay_372___05Fdelay_371___05F___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1161,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_333___05Fdelay_332___05Fdelay_331___05Fdelay_330___05F_eq_215));
        bufp->chgBit(oldp+1162,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_362___05Fdelay_361___05Fdelay_360___05Fdelay_359___05F_eq_218));
        bufp->chgBit(oldp+1163,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_374___05Fdelay_373___05Fdelay_372___05F___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1164,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_334___05Fdelay_333___05Fdelay_332___05Fdelay_331___05F_eq_215));
        bufp->chgBit(oldp+1165,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_363___05Fdelay_362___05Fdelay_361___05Fdelay_360___05F_eq_218));
        bufp->chgBit(oldp+1166,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_375___05Fdelay_374___05Fdelay_373___05F___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1167,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_335___05Fdelay_334___05Fdelay_333___05Fdelay_332___05F_eq_215));
        bufp->chgBit(oldp+1168,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_364___05Fdelay_363___05Fdelay_362___05Fdelay_361___05F_eq_218));
        bufp->chgBit(oldp+1169,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_376___05Fdelay_375___05Fdelay_374___05F___05Fsubstreamoutput_192));
        bufp->chgBit(oldp+1170,(vlSelfRef.test__DOT__taketwo__DOT___greaterthan_data_212));
        bufp->chgSData(oldp+1171,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_309___05Fsubstreamoutput_210),16);
        bufp->chgBit(oldp+1172,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_336___05Fdelay_335___05Fdelay_334___05Fdelay_333___05F_eq_215));
        bufp->chgBit(oldp+1173,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_365___05Fdelay_364___05Fdelay_363___05Fdelay_362___05F_eq_218));
        bufp->chgBit(oldp+1174,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_377___05Fdelay_376___05Fdelay_375___05F___05Fsubstreamoutput_192));
        bufp->chgSData(oldp+1175,(vlSelfRef.test__DOT__taketwo__DOT___cond_data_214),16);
        bufp->chgBit(oldp+1176,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_337___05Fdelay_336___05Fdelay_335___05Fdelay_334___05F_eq_215));
        bufp->chgSData(oldp+1177,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210),16);
        bufp->chgBit(oldp+1178,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_366___05Fdelay_365___05Fdelay_364___05Fdelay_363___05F_eq_218));
        bufp->chgBit(oldp+1179,(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_378___05Fdelay_377___05Fdelay_376___05F___05Fsubstreamoutput_192));
        bufp->chgSData(oldp+1180,(((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_337___05Fdelay_336___05Fdelay_335___05Fdelay_334___05F_eq_215)
                                    ? (IData)(vlSelfRef.test__DOT__taketwo__DOT___cond_data_214)
                                    : (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210))),16);
        bufp->chgSData(oldp+1181,(((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_366___05Fdelay_365___05Fdelay_364___05Fdelay_363___05F_eq_218)
                                    ? (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210)
                                    : ((IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_337___05Fdelay_336___05Fdelay_335___05Fdelay_334___05F_eq_215)
                                        ? (IData)(vlSelfRef.test__DOT__taketwo__DOT___cond_data_214)
                                        : (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fdelay_data_338___05Fdelay_309___05Fsubstreamoutput_210)))),16);
        bufp->chgBit(oldp+1182,((3U == vlSelfRef.test__DOT__taketwo__DOT__matmul_11_comp_fsm)));
        bufp->chgIData(oldp+1183,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0),32);
        bufp->chgIData(oldp+1184,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1),32);
        bufp->chgIData(oldp+1185,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2),32);
        bufp->chgIData(oldp+1186,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3),32);
        bufp->chgQData(oldp+1187,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_0),33);
        bufp->chgQData(oldp+1189,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_1),33);
        bufp->chgQData(oldp+1191,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_2),33);
        bufp->chgQData(oldp+1193,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_3),33);
        bufp->chgIData(oldp+1195,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_0),32);
        bufp->chgIData(oldp+1196,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_1),32);
        bufp->chgIData(oldp+1197,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_2),32);
        bufp->chgIData(oldp+1198,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_3),32);
        bufp->chgQData(oldp+1199,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_0),33);
        bufp->chgQData(oldp+1201,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_1),33);
        bufp->chgQData(oldp+1203,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_2),33);
        bufp->chgQData(oldp+1205,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_count_3),33);
        bufp->chgQData(oldp+1207,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_0),33);
        bufp->chgQData(oldp+1209,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_1),33);
        bufp->chgQData(oldp+1211,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_2),33);
        bufp->chgQData(oldp+1213,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_size_buf_3),33);
        bufp->chgIData(oldp+1215,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_0),32);
        bufp->chgIData(oldp+1216,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_1),32);
        bufp->chgIData(oldp+1217,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_2),32);
        bufp->chgIData(oldp+1218,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_stride_buf_3),32);
        bufp->chgBit(oldp+1219,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_120_1));
        bufp->chgIData(oldp+1220,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_pat_fsm_0),32);
        bufp->chgIData(oldp+1221,((vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_7_source_offset_buf 
                                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_0 
                                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_1 
                                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_2 
                                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_7_pat_cur_offset_3))))),32);
        bufp->chgIData(oldp+1222,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0),32);
        bufp->chgIData(oldp+1223,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1),32);
        bufp->chgIData(oldp+1224,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2),32);
        bufp->chgIData(oldp+1225,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3),32);
        bufp->chgQData(oldp+1226,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_0),33);
        bufp->chgQData(oldp+1228,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_1),33);
        bufp->chgQData(oldp+1230,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_2),33);
        bufp->chgQData(oldp+1232,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_3),33);
        bufp->chgIData(oldp+1234,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_0),32);
        bufp->chgIData(oldp+1235,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_1),32);
        bufp->chgIData(oldp+1236,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_2),32);
        bufp->chgIData(oldp+1237,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_3),32);
        bufp->chgQData(oldp+1238,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_0),33);
        bufp->chgQData(oldp+1240,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_1),33);
        bufp->chgQData(oldp+1242,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_2),33);
        bufp->chgQData(oldp+1244,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_count_3),33);
        bufp->chgQData(oldp+1246,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_0),33);
        bufp->chgQData(oldp+1248,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_1),33);
        bufp->chgQData(oldp+1250,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_2),33);
        bufp->chgQData(oldp+1252,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_size_buf_3),33);
        bufp->chgIData(oldp+1254,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_0),32);
        bufp->chgIData(oldp+1255,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_1),32);
        bufp->chgIData(oldp+1256,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_2),32);
        bufp->chgIData(oldp+1257,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_stride_buf_3),32);
        bufp->chgBit(oldp+1258,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_124_1));
        bufp->chgIData(oldp+1259,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_pat_fsm_1),32);
        bufp->chgIData(oldp+1260,((vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_9_source_offset_buf 
                                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_0 
                                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_1 
                                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_2 
                                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_9_pat_cur_offset_3))))),32);
        bufp->chgIData(oldp+1261,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0),32);
        bufp->chgIData(oldp+1262,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1),32);
        bufp->chgIData(oldp+1263,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2),32);
        bufp->chgIData(oldp+1264,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3),32);
        bufp->chgQData(oldp+1265,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_0),33);
        bufp->chgQData(oldp+1267,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_1),33);
        bufp->chgQData(oldp+1269,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_2),33);
        bufp->chgQData(oldp+1271,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_3),33);
        bufp->chgIData(oldp+1273,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_0),32);
        bufp->chgIData(oldp+1274,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_1),32);
        bufp->chgIData(oldp+1275,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_2),32);
        bufp->chgIData(oldp+1276,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_3),32);
        bufp->chgQData(oldp+1277,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_0),33);
        bufp->chgQData(oldp+1279,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_1),33);
        bufp->chgQData(oldp+1281,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_2),33);
        bufp->chgQData(oldp+1283,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_count_3),33);
        bufp->chgQData(oldp+1285,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_0),33);
        bufp->chgQData(oldp+1287,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_1),33);
        bufp->chgQData(oldp+1289,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_2),33);
        bufp->chgQData(oldp+1291,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_size_buf_3),33);
        bufp->chgIData(oldp+1293,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_0),32);
        bufp->chgIData(oldp+1294,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_1),32);
        bufp->chgIData(oldp+1295,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_2),32);
        bufp->chgIData(oldp+1296,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_stride_buf_3),32);
        bufp->chgBit(oldp+1297,((1U & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_ram_raddr)));
        bufp->chgBit(oldp+1298,(vlSelfRef.test__DOT__taketwo__DOT___tmp_137));
        bufp->chgBit(oldp+1299,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_139_1));
        bufp->chgBit(oldp+1300,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_141_1));
        bufp->chgSData(oldp+1301,((0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_137)
                                                   ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_1__DOT__ram_w16_l512_id1_1_0_rdata_out)
                                                   : (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id1_0__DOT__ram_w16_l512_id1_0_0_rdata_out)))),16);
        bufp->chgIData(oldp+1302,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_pat_fsm_2),32);
        bufp->chgIData(oldp+1303,((vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_20_source_offset_buf 
                                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_0 
                                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_1 
                                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_2 
                                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_20_pat_cur_offset_3))))),32);
        bufp->chgIData(oldp+1304,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0),32);
        bufp->chgIData(oldp+1305,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1),32);
        bufp->chgIData(oldp+1306,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2),32);
        bufp->chgIData(oldp+1307,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3),32);
        bufp->chgQData(oldp+1308,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_0),33);
        bufp->chgQData(oldp+1310,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_1),33);
        bufp->chgQData(oldp+1312,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_2),33);
        bufp->chgQData(oldp+1314,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_3),33);
        bufp->chgIData(oldp+1316,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_0),32);
        bufp->chgIData(oldp+1317,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_1),32);
        bufp->chgIData(oldp+1318,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_2),32);
        bufp->chgIData(oldp+1319,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_3),32);
        bufp->chgQData(oldp+1320,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_0),33);
        bufp->chgQData(oldp+1322,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_1),33);
        bufp->chgQData(oldp+1324,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_2),33);
        bufp->chgQData(oldp+1326,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_count_3),33);
        bufp->chgQData(oldp+1328,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_0),33);
        bufp->chgQData(oldp+1330,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_1),33);
        bufp->chgQData(oldp+1332,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_2),33);
        bufp->chgQData(oldp+1334,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_size_buf_3),33);
        bufp->chgIData(oldp+1336,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_0),32);
        bufp->chgIData(oldp+1337,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_1),32);
        bufp->chgIData(oldp+1338,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_2),32);
        bufp->chgIData(oldp+1339,(vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_stride_buf_3),32);
        bufp->chgBit(oldp+1340,((1U & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_ram_raddr)));
        bufp->chgBit(oldp+1341,(vlSelfRef.test__DOT__taketwo__DOT___tmp_146));
        bufp->chgBit(oldp+1342,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_148_1));
        bufp->chgBit(oldp+1343,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_150_1));
        bufp->chgSData(oldp+1344,((0x0000ffffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT___tmp_146)
                                                   ? (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_1__DOT__ram_w16_l512_id2_1_0_rdata_out)
                                                   : (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id2_0__DOT__ram_w16_l512_id2_0_0_rdata_out)))),16);
        bufp->chgIData(oldp+1345,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_pat_fsm_3),32);
        bufp->chgIData(oldp+1346,((vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_source_21_source_offset_buf 
                                   + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_0 
                                      + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_1 
                                         + (vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_2 
                                            + vlSelfRef.test__DOT__taketwo__DOT___source_stream_matmul_11_source_21_pat_cur_offset_3))))),32);
        bufp->chgBit(oldp+1347,(vlSelfRef.test__DOT__taketwo__DOT___tmp_154));
        bufp->chgBit(oldp+1348,(vlSelfRef.test__DOT__taketwo__DOT___tmp_155));
        bufp->chgBit(oldp+1349,(vlSelfRef.test__DOT__taketwo__DOT___tmp_156));
        bufp->chgBit(oldp+1350,(vlSelfRef.test__DOT__taketwo__DOT___tmp_157));
        bufp->chgBit(oldp+1351,(vlSelfRef.test__DOT__taketwo__DOT___tmp_158));
        bufp->chgBit(oldp+1352,(vlSelfRef.test__DOT__taketwo__DOT___tmp_159));
        bufp->chgBit(oldp+1353,(vlSelfRef.test__DOT__taketwo__DOT___tmp_160));
        bufp->chgBit(oldp+1354,(vlSelfRef.test__DOT__taketwo__DOT___tmp_161));
        bufp->chgBit(oldp+1355,(vlSelfRef.test__DOT__taketwo__DOT___tmp_162));
        bufp->chgBit(oldp+1356,(vlSelfRef.test__DOT__taketwo__DOT___tmp_163));
        bufp->chgBit(oldp+1357,(vlSelfRef.test__DOT__taketwo__DOT___tmp_164));
        bufp->chgBit(oldp+1358,(vlSelfRef.test__DOT__taketwo__DOT___tmp_165));
        bufp->chgBit(oldp+1359,(vlSelfRef.test__DOT__taketwo__DOT___tmp_166));
        bufp->chgBit(oldp+1360,(vlSelfRef.test__DOT__taketwo__DOT___tmp_167));
        bufp->chgBit(oldp+1361,(vlSelfRef.test__DOT__taketwo__DOT___tmp_168));
        bufp->chgBit(oldp+1362,(vlSelfRef.test__DOT__taketwo__DOT___tmp_169));
        bufp->chgBit(oldp+1363,(vlSelfRef.test__DOT__taketwo__DOT___tmp_170));
        bufp->chgBit(oldp+1364,(vlSelfRef.test__DOT__taketwo__DOT___tmp_171));
        bufp->chgBit(oldp+1365,(vlSelfRef.test__DOT__taketwo__DOT___tmp_172));
        bufp->chgBit(oldp+1366,(vlSelfRef.test__DOT__taketwo__DOT___tmp_173));
        bufp->chgBit(oldp+1367,(vlSelfRef.test__DOT__taketwo__DOT___tmp_174));
        bufp->chgBit(oldp+1368,(vlSelfRef.test__DOT__taketwo__DOT___tmp_175));
        bufp->chgBit(oldp+1369,(vlSelfRef.test__DOT__taketwo__DOT___tmp_176));
        bufp->chgBit(oldp+1370,(vlSelfRef.test__DOT__taketwo__DOT___tmp_177));
        bufp->chgBit(oldp+1371,(vlSelfRef.test__DOT__taketwo__DOT___tmp_178));
        bufp->chgBit(oldp+1372,(vlSelfRef.test__DOT__taketwo__DOT___tmp_179));
        bufp->chgBit(oldp+1373,(vlSelfRef.test__DOT__taketwo__DOT___tmp_180));
        bufp->chgBit(oldp+1374,(vlSelfRef.test__DOT__taketwo__DOT___tmp_181));
        bufp->chgBit(oldp+1375,(vlSelfRef.test__DOT__taketwo__DOT___tmp_182));
        bufp->chgBit(oldp+1376,(vlSelfRef.test__DOT__taketwo__DOT___tmp_183));
        bufp->chgBit(oldp+1377,(vlSelfRef.test__DOT__taketwo__DOT___tmp_184));
        bufp->chgQData(oldp+1378,((0x00000001ffffffffULL 
                                   & ((QData)((IData)(
                                                      (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_col 
                                                       + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_stream_out_local_val))) 
                                      + (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_page_comp_offset_buf))))),33);
        bufp->chgQData(oldp+1380,(vlSelfRef.test__DOT__taketwo__DOT___tmp_187),33);
        bufp->chgQData(oldp+1382,(vlSelfRef.test__DOT__taketwo__DOT___tmp_188),33);
        bufp->chgQData(oldp+1384,(vlSelfRef.test__DOT__taketwo__DOT___tmp_189),33);
        bufp->chgQData(oldp+1386,(vlSelfRef.test__DOT__taketwo__DOT___tmp_190),33);
        bufp->chgQData(oldp+1388,(vlSelfRef.test__DOT__taketwo__DOT___tmp_191),33);
        bufp->chgQData(oldp+1390,(vlSelfRef.test__DOT__taketwo__DOT___tmp_192),33);
        bufp->chgQData(oldp+1392,(vlSelfRef.test__DOT__taketwo__DOT___tmp_193),33);
        bufp->chgQData(oldp+1394,(vlSelfRef.test__DOT__taketwo__DOT___tmp_194),33);
        bufp->chgQData(oldp+1396,(vlSelfRef.test__DOT__taketwo__DOT___tmp_195),33);
        bufp->chgQData(oldp+1398,(vlSelfRef.test__DOT__taketwo__DOT___tmp_196),33);
        bufp->chgQData(oldp+1400,(vlSelfRef.test__DOT__taketwo__DOT___tmp_197),33);
        bufp->chgQData(oldp+1402,(vlSelfRef.test__DOT__taketwo__DOT___tmp_198),33);
        bufp->chgQData(oldp+1404,(vlSelfRef.test__DOT__taketwo__DOT___tmp_199),33);
        bufp->chgQData(oldp+1406,(vlSelfRef.test__DOT__taketwo__DOT___tmp_200),33);
        bufp->chgQData(oldp+1408,(vlSelfRef.test__DOT__taketwo__DOT___tmp_201),33);
        bufp->chgQData(oldp+1410,(vlSelfRef.test__DOT__taketwo__DOT___tmp_202),33);
        bufp->chgQData(oldp+1412,(vlSelfRef.test__DOT__taketwo__DOT___tmp_203),33);
        bufp->chgQData(oldp+1414,(vlSelfRef.test__DOT__taketwo__DOT___tmp_204),33);
        bufp->chgQData(oldp+1416,(vlSelfRef.test__DOT__taketwo__DOT___tmp_205),33);
        bufp->chgQData(oldp+1418,(vlSelfRef.test__DOT__taketwo__DOT___tmp_206),33);
        bufp->chgQData(oldp+1420,(vlSelfRef.test__DOT__taketwo__DOT___tmp_207),33);
        bufp->chgQData(oldp+1422,(vlSelfRef.test__DOT__taketwo__DOT___tmp_208),33);
        bufp->chgQData(oldp+1424,(vlSelfRef.test__DOT__taketwo__DOT___tmp_209),33);
        bufp->chgQData(oldp+1426,(vlSelfRef.test__DOT__taketwo__DOT___tmp_210),33);
        bufp->chgQData(oldp+1428,(vlSelfRef.test__DOT__taketwo__DOT___tmp_211),33);
        bufp->chgQData(oldp+1430,(vlSelfRef.test__DOT__taketwo__DOT___tmp_212),33);
        bufp->chgQData(oldp+1432,(vlSelfRef.test__DOT__taketwo__DOT___tmp_213),33);
        bufp->chgQData(oldp+1434,(vlSelfRef.test__DOT__taketwo__DOT___tmp_214),33);
        bufp->chgQData(oldp+1436,(vlSelfRef.test__DOT__taketwo__DOT___tmp_215),33);
        bufp->chgQData(oldp+1438,(vlSelfRef.test__DOT__taketwo__DOT___tmp_216),33);
        bufp->chgQData(oldp+1440,(vlSelfRef.test__DOT__taketwo__DOT___tmp_217),33);
        bufp->chgIData(oldp+1442,(vlSelfRef.test__DOT__taketwo__DOT___tmp_218),32);
        bufp->chgIData(oldp+1443,(vlSelfRef.test__DOT__taketwo__DOT___tmp_219),32);
        bufp->chgIData(oldp+1444,(vlSelfRef.test__DOT__taketwo__DOT___tmp_220),32);
        bufp->chgIData(oldp+1445,(vlSelfRef.test__DOT__taketwo__DOT___tmp_221),32);
        bufp->chgIData(oldp+1446,(vlSelfRef.test__DOT__taketwo__DOT___tmp_222),32);
        bufp->chgIData(oldp+1447,(vlSelfRef.test__DOT__taketwo__DOT___tmp_223),32);
        bufp->chgIData(oldp+1448,(vlSelfRef.test__DOT__taketwo__DOT___tmp_224),32);
        bufp->chgIData(oldp+1449,(vlSelfRef.test__DOT__taketwo__DOT___tmp_225),32);
        bufp->chgIData(oldp+1450,(vlSelfRef.test__DOT__taketwo__DOT___tmp_226),32);
        bufp->chgIData(oldp+1451,(vlSelfRef.test__DOT__taketwo__DOT___tmp_227),32);
        bufp->chgIData(oldp+1452,(vlSelfRef.test__DOT__taketwo__DOT___tmp_228),32);
        bufp->chgIData(oldp+1453,(vlSelfRef.test__DOT__taketwo__DOT___tmp_229),32);
        bufp->chgIData(oldp+1454,(vlSelfRef.test__DOT__taketwo__DOT___tmp_230),32);
        bufp->chgIData(oldp+1455,(vlSelfRef.test__DOT__taketwo__DOT___tmp_231),32);
        bufp->chgIData(oldp+1456,(vlSelfRef.test__DOT__taketwo__DOT___tmp_232),32);
        bufp->chgIData(oldp+1457,(vlSelfRef.test__DOT__taketwo__DOT___tmp_233),32);
        bufp->chgIData(oldp+1458,(vlSelfRef.test__DOT__taketwo__DOT___tmp_234),32);
        bufp->chgIData(oldp+1459,(vlSelfRef.test__DOT__taketwo__DOT___tmp_235),32);
        bufp->chgIData(oldp+1460,(vlSelfRef.test__DOT__taketwo__DOT___tmp_236),32);
        bufp->chgIData(oldp+1461,(vlSelfRef.test__DOT__taketwo__DOT___tmp_237),32);
        bufp->chgIData(oldp+1462,(vlSelfRef.test__DOT__taketwo__DOT___tmp_238),32);
        bufp->chgIData(oldp+1463,(vlSelfRef.test__DOT__taketwo__DOT___tmp_239),32);
        bufp->chgIData(oldp+1464,(vlSelfRef.test__DOT__taketwo__DOT___tmp_240),32);
        bufp->chgIData(oldp+1465,(vlSelfRef.test__DOT__taketwo__DOT___tmp_241),32);
        bufp->chgIData(oldp+1466,(vlSelfRef.test__DOT__taketwo__DOT___tmp_242),32);
        bufp->chgIData(oldp+1467,(vlSelfRef.test__DOT__taketwo__DOT___tmp_243),32);
        bufp->chgIData(oldp+1468,(vlSelfRef.test__DOT__taketwo__DOT___tmp_244),32);
        bufp->chgIData(oldp+1469,(vlSelfRef.test__DOT__taketwo__DOT___tmp_245),32);
        bufp->chgIData(oldp+1470,(vlSelfRef.test__DOT__taketwo__DOT___tmp_246),32);
        bufp->chgIData(oldp+1471,(vlSelfRef.test__DOT__taketwo__DOT___tmp_247),32);
        bufp->chgIData(oldp+1472,(vlSelfRef.test__DOT__taketwo__DOT___tmp_248),32);
        bufp->chgBit(oldp+1473,((1U & vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_waddr)));
        bufp->chgIData(oldp+1474,(vlSelfRef.test__DOT__taketwo__DOT___stream_matmul_11_sink_26_sink_fsm_4),32);
        bufp->chgBit(oldp+1475,(vlSelfRef.test__DOT__taketwo__DOT___tmp_251));
        bufp->chgBit(oldp+1476,(vlSelfRef.test__DOT__taketwo__DOT___tmp_252));
        bufp->chgBit(oldp+1477,(vlSelfRef.test__DOT__taketwo__DOT___tmp_253));
        bufp->chgBit(oldp+1478,(vlSelfRef.test__DOT__taketwo__DOT___tmp_254));
        bufp->chgBit(oldp+1479,(vlSelfRef.test__DOT__taketwo__DOT___tmp_255));
        bufp->chgBit(oldp+1480,(vlSelfRef.test__DOT__taketwo__DOT___tmp_256));
        bufp->chgBit(oldp+1481,(vlSelfRef.test__DOT__taketwo__DOT___tmp_257));
        bufp->chgBit(oldp+1482,(vlSelfRef.test__DOT__taketwo__DOT___tmp_258));
        bufp->chgBit(oldp+1483,(vlSelfRef.test__DOT__taketwo__DOT___tmp_259));
        bufp->chgBit(oldp+1484,(vlSelfRef.test__DOT__taketwo__DOT___tmp_260));
        bufp->chgBit(oldp+1485,(vlSelfRef.test__DOT__taketwo__DOT___tmp_261));
        bufp->chgBit(oldp+1486,(vlSelfRef.test__DOT__taketwo__DOT___tmp_262));
        bufp->chgBit(oldp+1487,(vlSelfRef.test__DOT__taketwo__DOT___tmp_264));
        bufp->chgBit(oldp+1488,(vlSelfRef.test__DOT__taketwo__DOT___tmp_265));
        bufp->chgBit(oldp+1489,(vlSelfRef.test__DOT__taketwo__DOT___tmp_266));
        bufp->chgBit(oldp+1490,(vlSelfRef.test__DOT__taketwo__DOT___tmp_267));
        bufp->chgBit(oldp+1491,(vlSelfRef.test__DOT__taketwo__DOT___tmp_268));
        bufp->chgBit(oldp+1492,(vlSelfRef.test__DOT__taketwo__DOT___tmp_269));
        bufp->chgBit(oldp+1493,(vlSelfRef.test__DOT__taketwo__DOT___tmp_270));
        bufp->chgBit(oldp+1494,(vlSelfRef.test__DOT__taketwo__DOT___tmp_271));
        bufp->chgBit(oldp+1495,(vlSelfRef.test__DOT__taketwo__DOT___tmp_272));
        bufp->chgBit(oldp+1496,(vlSelfRef.test__DOT__taketwo__DOT___tmp_274));
        bufp->chgBit(oldp+1497,(vlSelfRef.test__DOT__taketwo__DOT___tmp_275));
        bufp->chgBit(oldp+1498,(vlSelfRef.test__DOT__taketwo__DOT___tmp_276));
        bufp->chgBit(oldp+1499,(vlSelfRef.test__DOT__taketwo__DOT___tmp_277));
        bufp->chgBit(oldp+1500,(vlSelfRef.test__DOT__taketwo__DOT___tmp_278));
        bufp->chgBit(oldp+1501,(vlSelfRef.test__DOT__taketwo__DOT___tmp_279));
        bufp->chgBit(oldp+1502,(vlSelfRef.test__DOT__taketwo__DOT___tmp_280));
        bufp->chgBit(oldp+1503,(vlSelfRef.test__DOT__taketwo__DOT___tmp_281));
        bufp->chgBit(oldp+1504,(vlSelfRef.test__DOT__taketwo__DOT___tmp_282));
        bufp->chgBit(oldp+1505,(vlSelfRef.test__DOT__taketwo__DOT___tmp_284));
        bufp->chgBit(oldp+1506,(vlSelfRef.test__DOT__taketwo__DOT___tmp_285));
        bufp->chgBit(oldp+1507,(vlSelfRef.test__DOT__taketwo__DOT___tmp_286));
        bufp->chgBit(oldp+1508,(vlSelfRef.test__DOT__taketwo__DOT___tmp_287));
        bufp->chgBit(oldp+1509,(vlSelfRef.test__DOT__taketwo__DOT___tmp_288));
        bufp->chgBit(oldp+1510,(vlSelfRef.test__DOT__taketwo__DOT___tmp_290));
        bufp->chgBit(oldp+1511,(vlSelfRef.test__DOT__taketwo__DOT___tmp_292));
        bufp->chgBit(oldp+1512,(vlSelfRef.test__DOT__taketwo__DOT___tmp_294));
        bufp->chgBit(oldp+1513,(vlSelfRef.test__DOT__taketwo__DOT___tmp_295));
        bufp->chgBit(oldp+1514,(vlSelfRef.test__DOT__taketwo__DOT___tmp_296));
        bufp->chgBit(oldp+1515,(vlSelfRef.test__DOT__taketwo__DOT___tmp_297));
        bufp->chgBit(oldp+1516,(vlSelfRef.test__DOT__taketwo__DOT___tmp_298));
        bufp->chgBit(oldp+1517,(vlSelfRef.test__DOT__taketwo__DOT___tmp_299));
        bufp->chgBit(oldp+1518,(vlSelfRef.test__DOT__taketwo__DOT___tmp_300));
        bufp->chgBit(oldp+1519,(vlSelfRef.test__DOT__taketwo__DOT___tmp_301));
        bufp->chgBit(oldp+1520,(vlSelfRef.test__DOT__taketwo__DOT___tmp_302));
        bufp->chgBit(oldp+1521,(vlSelfRef.test__DOT__taketwo__DOT___tmp_303));
        bufp->chgBit(oldp+1522,(vlSelfRef.test__DOT__taketwo__DOT___tmp_304));
        bufp->chgBit(oldp+1523,(vlSelfRef.test__DOT__taketwo__DOT___tmp_305));
        bufp->chgBit(oldp+1524,(vlSelfRef.test__DOT__taketwo__DOT___tmp_306));
        bufp->chgBit(oldp+1525,(vlSelfRef.test__DOT__taketwo__DOT___tmp_307));
        bufp->chgBit(oldp+1526,(vlSelfRef.test__DOT__taketwo__DOT___tmp_308));
        bufp->chgBit(oldp+1527,(vlSelfRef.test__DOT__taketwo__DOT___tmp_309));
        bufp->chgBit(oldp+1528,(vlSelfRef.test__DOT__taketwo__DOT___tmp_310));
        bufp->chgBit(oldp+1529,(vlSelfRef.test__DOT__taketwo__DOT___tmp_312));
        bufp->chgBit(oldp+1530,(vlSelfRef.test__DOT__taketwo__DOT___tmp_313));
        bufp->chgBit(oldp+1531,(vlSelfRef.test__DOT__taketwo__DOT___tmp_314));
        bufp->chgBit(oldp+1532,(vlSelfRef.test__DOT__taketwo__DOT___tmp_315));
        bufp->chgBit(oldp+1533,(vlSelfRef.test__DOT__taketwo__DOT___tmp_316));
        bufp->chgBit(oldp+1534,(vlSelfRef.test__DOT__taketwo__DOT___tmp_317));
        bufp->chgBit(oldp+1535,(vlSelfRef.test__DOT__taketwo__DOT___tmp_319));
        bufp->chgBit(oldp+1536,(vlSelfRef.test__DOT__taketwo__DOT___tmp_320));
        bufp->chgBit(oldp+1537,(vlSelfRef.test__DOT__taketwo__DOT___tmp_321));
        bufp->chgBit(oldp+1538,(vlSelfRef.test__DOT__taketwo__DOT___tmp_322));
        bufp->chgBit(oldp+1539,(vlSelfRef.test__DOT__taketwo__DOT___tmp_323));
        bufp->chgBit(oldp+1540,(vlSelfRef.test__DOT__taketwo__DOT___tmp_324));
        bufp->chgBit(oldp+1541,(vlSelfRef.test__DOT__taketwo__DOT___tmp_326));
        bufp->chgBit(oldp+1542,(vlSelfRef.test__DOT__taketwo__DOT___tmp_327));
        bufp->chgBit(oldp+1543,(vlSelfRef.test__DOT__taketwo__DOT___tmp_328));
        bufp->chgBit(oldp+1544,(vlSelfRef.test__DOT__taketwo__DOT___tmp_329));
        bufp->chgBit(oldp+1545,(vlSelfRef.test__DOT__taketwo__DOT___tmp_330));
        bufp->chgBit(oldp+1546,(vlSelfRef.test__DOT__taketwo__DOT___tmp_331));
        bufp->chgBit(oldp+1547,(vlSelfRef.test__DOT__taketwo__DOT___tmp_332));
        bufp->chgBit(oldp+1548,(vlSelfRef.test__DOT__taketwo__DOT___tmp_333));
        bufp->chgBit(oldp+1549,(vlSelfRef.test__DOT__taketwo__DOT___tmp_334));
        bufp->chgBit(oldp+1550,(vlSelfRef.test__DOT__taketwo__DOT___tmp_335));
        bufp->chgBit(oldp+1551,(vlSelfRef.test__DOT__taketwo__DOT___tmp_336));
        bufp->chgBit(oldp+1552,(vlSelfRef.test__DOT__taketwo__DOT___tmp_337));
        bufp->chgBit(oldp+1553,(vlSelfRef.test__DOT__taketwo__DOT___tmp_338));
        bufp->chgBit(oldp+1554,(vlSelfRef.test__DOT__taketwo__DOT___tmp_340));
        bufp->chgBit(oldp+1555,(vlSelfRef.test__DOT__taketwo__DOT___tmp_341));
        bufp->chgBit(oldp+1556,(vlSelfRef.test__DOT__taketwo__DOT___tmp_342));
        bufp->chgBit(oldp+1557,(vlSelfRef.test__DOT__taketwo__DOT___tmp_343));
        bufp->chgBit(oldp+1558,(vlSelfRef.test__DOT__taketwo__DOT___tmp_344));
        bufp->chgBit(oldp+1559,(vlSelfRef.test__DOT__taketwo__DOT___tmp_345));
        bufp->chgBit(oldp+1560,(vlSelfRef.test__DOT__taketwo__DOT___tmp_346));
        bufp->chgBit(oldp+1561,(vlSelfRef.test__DOT__taketwo__DOT___tmp_347));
        bufp->chgBit(oldp+1562,(vlSelfRef.test__DOT__taketwo__DOT___tmp_348));
        bufp->chgBit(oldp+1563,(vlSelfRef.test__DOT__taketwo__DOT___tmp_350));
        bufp->chgBit(oldp+1564,(vlSelfRef.test__DOT__taketwo__DOT___tmp_351));
        bufp->chgBit(oldp+1565,(vlSelfRef.test__DOT__taketwo__DOT___tmp_352));
        bufp->chgBit(oldp+1566,(vlSelfRef.test__DOT__taketwo__DOT___tmp_353));
        bufp->chgBit(oldp+1567,(vlSelfRef.test__DOT__taketwo__DOT___tmp_354));
        bufp->chgBit(oldp+1568,(vlSelfRef.test__DOT__taketwo__DOT___tmp_355));
        bufp->chgBit(oldp+1569,(vlSelfRef.test__DOT__taketwo__DOT___tmp_356));
        bufp->chgBit(oldp+1570,(vlSelfRef.test__DOT__taketwo__DOT___tmp_357));
        bufp->chgBit(oldp+1571,(vlSelfRef.test__DOT__taketwo__DOT___tmp_358));
        bufp->chgBit(oldp+1572,(vlSelfRef.test__DOT__taketwo__DOT___tmp_360));
        bufp->chgBit(oldp+1573,(vlSelfRef.test__DOT__taketwo__DOT___tmp_361));
        bufp->chgBit(oldp+1574,(vlSelfRef.test__DOT__taketwo__DOT___tmp_362));
        bufp->chgBit(oldp+1575,(vlSelfRef.test__DOT__taketwo__DOT___tmp_363));
        bufp->chgBit(oldp+1576,(vlSelfRef.test__DOT__taketwo__DOT___tmp_364));
        bufp->chgBit(oldp+1577,(vlSelfRef.test__DOT__taketwo__DOT___tmp_365));
        bufp->chgBit(oldp+1578,(vlSelfRef.test__DOT__taketwo__DOT___tmp_366));
        bufp->chgBit(oldp+1579,(vlSelfRef.test__DOT__taketwo__DOT___tmp_367));
        bufp->chgBit(oldp+1580,(vlSelfRef.test__DOT__taketwo__DOT___tmp_368));
        bufp->chgBit(oldp+1581,(vlSelfRef.test__DOT__taketwo__DOT___tmp_369));
        bufp->chgBit(oldp+1582,(vlSelfRef.test__DOT__taketwo__DOT___tmp_370));
        bufp->chgBit(oldp+1583,(vlSelfRef.test__DOT__taketwo__DOT___tmp_373));
        bufp->chgBit(oldp+1584,(vlSelfRef.test__DOT__taketwo__DOT___tmp_376));
        bufp->chgBit(oldp+1585,(vlSelfRef.test__DOT__taketwo__DOT___tmp_377));
        bufp->chgBit(oldp+1586,(vlSelfRef.test__DOT__taketwo__DOT___tmp_378));
        bufp->chgBit(oldp+1587,(vlSelfRef.test__DOT__taketwo__DOT___tmp_379));
        bufp->chgBit(oldp+1588,(vlSelfRef.test__DOT__taketwo__DOT___tmp_380));
        bufp->chgBit(oldp+1589,(vlSelfRef.test__DOT__taketwo__DOT___tmp_381));
        bufp->chgBit(oldp+1590,(vlSelfRef.test__DOT__taketwo__DOT___tmp_382));
        bufp->chgBit(oldp+1591,(vlSelfRef.test__DOT__taketwo__DOT___tmp_383));
        bufp->chgBit(oldp+1592,(vlSelfRef.test__DOT__taketwo__DOT___tmp_384));
        bufp->chgBit(oldp+1593,(vlSelfRef.test__DOT__taketwo__DOT___tmp_385));
        bufp->chgBit(oldp+1594,(vlSelfRef.test__DOT__taketwo__DOT___tmp_386));
        bufp->chgBit(oldp+1595,(vlSelfRef.test__DOT__taketwo__DOT___tmp_387));
        bufp->chgBit(oldp+1596,(vlSelfRef.test__DOT__taketwo__DOT___tmp_388));
        bufp->chgBit(oldp+1597,(vlSelfRef.test__DOT__taketwo__DOT___tmp_389));
        bufp->chgBit(oldp+1598,(vlSelfRef.test__DOT__taketwo__DOT___tmp_390));
        bufp->chgBit(oldp+1599,(vlSelfRef.test__DOT__taketwo__DOT___tmp_391));
        bufp->chgBit(oldp+1600,(vlSelfRef.test__DOT__taketwo__DOT___tmp_392));
        bufp->chgBit(oldp+1601,(vlSelfRef.test__DOT__taketwo__DOT___tmp_393));
        bufp->chgBit(oldp+1602,(vlSelfRef.test__DOT__taketwo__DOT___tmp_394));
        bufp->chgBit(oldp+1603,(vlSelfRef.test__DOT__taketwo__DOT___tmp_395));
        bufp->chgBit(oldp+1604,(vlSelfRef.test__DOT__taketwo__DOT___tmp_396));
        bufp->chgBit(oldp+1605,(vlSelfRef.test__DOT__taketwo__DOT___tmp_397));
        bufp->chgBit(oldp+1606,(vlSelfRef.test__DOT__taketwo__DOT___tmp_398));
        bufp->chgBit(oldp+1607,(vlSelfRef.test__DOT__taketwo__DOT___tmp_399));
        bufp->chgBit(oldp+1608,(vlSelfRef.test__DOT__taketwo__DOT___tmp_400));
        bufp->chgBit(oldp+1609,(vlSelfRef.test__DOT__taketwo__DOT___tmp_401));
        bufp->chgBit(oldp+1610,(vlSelfRef.test__DOT__taketwo__DOT___tmp_402));
        bufp->chgBit(oldp+1611,(vlSelfRef.test__DOT__taketwo__DOT___tmp_403));
        bufp->chgBit(oldp+1612,(vlSelfRef.test__DOT__taketwo__DOT___tmp_404));
        bufp->chgBit(oldp+1613,(vlSelfRef.test__DOT__taketwo__DOT___tmp_405));
        bufp->chgBit(oldp+1614,(vlSelfRef.test__DOT__taketwo__DOT___tmp_406));
        bufp->chgBit(oldp+1615,(vlSelfRef.test__DOT__taketwo__DOT___tmp_408));
        bufp->chgBit(oldp+1616,(vlSelfRef.test__DOT__taketwo__DOT___tmp_409));
        bufp->chgBit(oldp+1617,(vlSelfRef.test__DOT__taketwo__DOT___tmp_410));
        bufp->chgBit(oldp+1618,(vlSelfRef.test__DOT__taketwo__DOT___tmp_411));
        bufp->chgBit(oldp+1619,(vlSelfRef.test__DOT__taketwo__DOT___tmp_412));
        bufp->chgBit(oldp+1620,(vlSelfRef.test__DOT__taketwo__DOT___tmp_413));
        bufp->chgBit(oldp+1621,(vlSelfRef.test__DOT__taketwo__DOT___tmp_414));
        bufp->chgBit(oldp+1622,(vlSelfRef.test__DOT__taketwo__DOT___tmp_415));
        bufp->chgBit(oldp+1623,(vlSelfRef.test__DOT__taketwo__DOT___tmp_416));
        bufp->chgBit(oldp+1624,(vlSelfRef.test__DOT__taketwo__DOT___tmp_417));
        bufp->chgBit(oldp+1625,(vlSelfRef.test__DOT__taketwo__DOT___tmp_418));
        bufp->chgBit(oldp+1626,(vlSelfRef.test__DOT__taketwo__DOT___tmp_419));
        bufp->chgBit(oldp+1627,(vlSelfRef.test__DOT__taketwo__DOT___tmp_420));
        bufp->chgBit(oldp+1628,(vlSelfRef.test__DOT__taketwo__DOT___tmp_421));
        bufp->chgBit(oldp+1629,(vlSelfRef.test__DOT__taketwo__DOT___tmp_422));
        bufp->chgBit(oldp+1630,(vlSelfRef.test__DOT__taketwo__DOT___tmp_423));
        bufp->chgBit(oldp+1631,(vlSelfRef.test__DOT__taketwo__DOT___tmp_424));
        bufp->chgBit(oldp+1632,(vlSelfRef.test__DOT__taketwo__DOT___tmp_425));
        bufp->chgBit(oldp+1633,(vlSelfRef.test__DOT__taketwo__DOT___tmp_426));
        bufp->chgBit(oldp+1634,(vlSelfRef.test__DOT__taketwo__DOT___tmp_427));
        bufp->chgBit(oldp+1635,(vlSelfRef.test__DOT__taketwo__DOT___tmp_428));
        bufp->chgBit(oldp+1636,(vlSelfRef.test__DOT__taketwo__DOT___tmp_429));
        bufp->chgBit(oldp+1637,(vlSelfRef.test__DOT__taketwo__DOT___tmp_430));
        bufp->chgBit(oldp+1638,(vlSelfRef.test__DOT__taketwo__DOT___tmp_431));
        bufp->chgBit(oldp+1639,(vlSelfRef.test__DOT__taketwo__DOT___tmp_432));
        bufp->chgBit(oldp+1640,(vlSelfRef.test__DOT__taketwo__DOT___tmp_433));
        bufp->chgBit(oldp+1641,(vlSelfRef.test__DOT__taketwo__DOT___tmp_434));
        bufp->chgBit(oldp+1642,(vlSelfRef.test__DOT__taketwo__DOT___tmp_435));
        bufp->chgBit(oldp+1643,(vlSelfRef.test__DOT__taketwo__DOT___tmp_436));
        bufp->chgBit(oldp+1644,(vlSelfRef.test__DOT__taketwo__DOT___tmp_437));
        bufp->chgBit(oldp+1645,(vlSelfRef.test__DOT__taketwo__DOT___tmp_439));
        bufp->chgBit(oldp+1646,(vlSelfRef.test__DOT__taketwo__DOT___tmp_440));
        bufp->chgBit(oldp+1647,(vlSelfRef.test__DOT__taketwo__DOT___tmp_441));
        bufp->chgBit(oldp+1648,(vlSelfRef.test__DOT__taketwo__DOT___tmp_442));
        bufp->chgBit(oldp+1649,(vlSelfRef.test__DOT__taketwo__DOT___tmp_443));
        bufp->chgBit(oldp+1650,(vlSelfRef.test__DOT__taketwo__DOT___tmp_444));
        bufp->chgBit(oldp+1651,(vlSelfRef.test__DOT__taketwo__DOT___tmp_445));
        bufp->chgBit(oldp+1652,(vlSelfRef.test__DOT__taketwo__DOT___tmp_446));
        bufp->chgBit(oldp+1653,(vlSelfRef.test__DOT__taketwo__DOT___tmp_447));
        bufp->chgBit(oldp+1654,(vlSelfRef.test__DOT__taketwo__DOT___tmp_448));
        bufp->chgBit(oldp+1655,(vlSelfRef.test__DOT__taketwo__DOT___tmp_449));
        bufp->chgBit(oldp+1656,(vlSelfRef.test__DOT__taketwo__DOT___tmp_450));
        bufp->chgBit(oldp+1657,(vlSelfRef.test__DOT__taketwo__DOT___tmp_451));
        bufp->chgBit(oldp+1658,(vlSelfRef.test__DOT__taketwo__DOT___tmp_452));
        bufp->chgBit(oldp+1659,(vlSelfRef.test__DOT__taketwo__DOT___tmp_453));
        bufp->chgBit(oldp+1660,(vlSelfRef.test__DOT__taketwo__DOT___tmp_454));
        bufp->chgBit(oldp+1661,(vlSelfRef.test__DOT__taketwo__DOT___tmp_455));
        bufp->chgBit(oldp+1662,(vlSelfRef.test__DOT__taketwo__DOT___tmp_456));
        bufp->chgBit(oldp+1663,(vlSelfRef.test__DOT__taketwo__DOT___tmp_457));
        bufp->chgBit(oldp+1664,(vlSelfRef.test__DOT__taketwo__DOT___tmp_458));
        bufp->chgBit(oldp+1665,(vlSelfRef.test__DOT__taketwo__DOT___tmp_459));
        bufp->chgBit(oldp+1666,(vlSelfRef.test__DOT__taketwo__DOT___tmp_460));
        bufp->chgBit(oldp+1667,(vlSelfRef.test__DOT__taketwo__DOT___tmp_461));
        bufp->chgBit(oldp+1668,(vlSelfRef.test__DOT__taketwo__DOT___tmp_462));
        bufp->chgBit(oldp+1669,(vlSelfRef.test__DOT__taketwo__DOT___tmp_463));
        bufp->chgBit(oldp+1670,(vlSelfRef.test__DOT__taketwo__DOT___tmp_464));
        bufp->chgBit(oldp+1671,(vlSelfRef.test__DOT__taketwo__DOT___tmp_465));
        bufp->chgBit(oldp+1672,(vlSelfRef.test__DOT__taketwo__DOT___tmp_466));
        bufp->chgBit(oldp+1673,(vlSelfRef.test__DOT__taketwo__DOT___tmp_467));
        bufp->chgBit(oldp+1674,(vlSelfRef.test__DOT__taketwo__DOT___tmp_468));
        bufp->chgBit(oldp+1675,(vlSelfRef.test__DOT__taketwo__DOT___tmp_470));
        bufp->chgBit(oldp+1676,((1U <= vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_row_count)));
        bufp->chgIData(oldp+1677,(VL_SHIFTR_III(32,32,32, vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size, 1U)),32);
        bufp->chgBit(oldp+1678,((1U & vlSelfRef.test__DOT__taketwo__DOT__matmul_11_next_out_write_size)));
        bufp->chgIData(oldp+1679,(vlSelfRef.test__DOT__taketwo__DOT___dma_write_packed_local_packed_size_473),32);
        bufp->chgIData(oldp+1680,(VL_SHIFTR_III(32,32,32, 
                                                (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr 
                                                 + 
                                                 ((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_val 
                                                   + 
                                                   (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
                                                    + 
                                                    (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
                                                     + 
                                                     (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
                                                      + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och)))) 
                                                  + vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr)), 2U)),32);
        bufp->chgIData(oldp+1681,((0xfffffffcU & (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_objaddr 
                                                  + 
                                                  ((vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_val 
                                                    + 
                                                    (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_col 
                                                     + 
                                                     (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_row 
                                                      + 
                                                      (vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_bat 
                                                       + vlSelfRef.test__DOT__taketwo__DOT__matmul_11_out_base_offset_och)))) 
                                                   + vlSelfRef.test__DOT__taketwo__DOT___maxi_global_base_addr)))),32);
        bufp->chgIData(oldp+1682,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fsm),32);
        bufp->chgQData(oldp+1683,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size),33);
        bufp->chgBit(oldp+1685,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cont));
        __Vtemp_56[0U] = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize;
        __Vtemp_56[1U] = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size);
        __Vtemp_56[2U] = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                           << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_size 
                                             >> 0x00000020U)));
        __Vtemp_56[3U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                           << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                                     >> 0x0000001fU));
        __Vtemp_56[4U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                           >> 0x0000001fU) | ((IData)(
                                                      ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                                         << 0x00000020U) 
                                                        | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr))) 
                                                       >> 0x00000020U)) 
                                              << 1U));
        bufp->chgWData(oldp+1686,(__Vtemp_56),137);
        bufp->chgBit(oldp+1691,((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_req_fifo_almost_full)))));
        bufp->chgBit(oldp+1692,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_483_1));
        bufp->chgIData(oldp+1693,(VL_SHIFTR_III(32,32,32, vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr, 2U)),32);
        bufp->chgIData(oldp+1694,((0xfffffffcU & vlSelfRef.test__DOT__taketwo__DOT___maxi_write_global_addr)),32);
        __Vtemp_59[0U] = vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_blocksize;
        __Vtemp_59[1U] = (IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size);
        __Vtemp_59[2U] = ((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                           << 1U) | (IData)((vlSelfRef.test__DOT__taketwo__DOT___maxi_write_cur_global_size 
                                             >> 0x00000020U)));
        __Vtemp_59[3U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                           << 1U) | (vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_stride 
                                     >> 0x0000001fU));
        __Vtemp_59[4U] = (((IData)((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr)))) 
                           >> 0x0000001fU) | ((IData)(
                                                      ((((QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_op_sel)) 
                                                         << 0x00000020U) 
                                                        | (QData)((IData)(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_local_addr))) 
                                                       >> 0x00000020U)) 
                                              << 1U));
        bufp->chgWData(oldp+1695,(__Vtemp_59),137);
        bufp->chgBit(oldp+1700,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_503_1));
        bufp->chgBit(oldp+1701,(vlSelfRef.test__DOT__taketwo__DOT___maxi_waddr_cond_0_1));
        bufp->chgIData(oldp+1702,(vlSelfRef.test__DOT__taketwo__DOT___maxi_write_data_fsm),32);
        bufp->chgIData(oldp+1703,(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_fsm_4),32);
        bufp->chgSData(oldp+1704,(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_addr_504),9);
        bufp->chgSData(oldp+1705,(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_stride_505),9);
        bufp->chgQData(oldp+1706,(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_length_506),33);
        bufp->chgBit(oldp+1708,(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rvalid_507));
        bufp->chgBit(oldp+1709,(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_rlast_508));
        bufp->chgCData(oldp+1710,((0x000000ffU & ((IData)(vlSelfRef.test__DOT__taketwo__DOT__read_burst_packed_addr_504) 
                                                  >> 1U))),8);
        bufp->chgBit(oldp+1711,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_511_1));
        bufp->chgBit(oldp+1712,(vlSelfRef.test__DOT__taketwo__DOT_____05Ftmp_515_1));
        bufp->chgIData(oldp+1713,((((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_1__DOT__ram_w16_l512_id0_1_1_rdata_out) 
                                    << 0x00000010U) 
                                   | (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst_ram_w16_l512_id0_0__DOT__ram_w16_l512_id0_0_1_rdata_out))),32);
        bufp->chgBit(oldp+1714,(vlSelfRef.test__DOT__taketwo__DOT___maxi_wdata_cond_0_1));
        bufp->chgBit(oldp+1715,((1U & (~ (IData)(vlSelfRef.test__DOT__taketwo__DOT__matmul_11_row_select)))));
        bufp->chgSData(oldp+1716,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___a),16);
        bufp->chgSData(oldp+1717,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___b),16);
        bufp->chgSData(oldp+1718,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___c),16);
        bufp->chgIData(oldp+1719,(VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___a)), 
                                              VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___b)))),32);
        bufp->chgIData(oldp+1720,((VL_MULS_III(32, 
                                               VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___a)), 
                                               VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___b))) 
                                   + VL_EXTENDS_II(32,16, (IData)(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___c)))),32);
        bufp->chgIData(oldp+1721,(vlSelfRef.test__DOT__taketwo__DOT_____05Fmuladd_madd_77__DOT__madd__DOT___pipe_madd0),32);
        bufp->chgQData(oldp+1722,(vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___a),64);
        bufp->chgIData(oldp+1724,(vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___b),32);
        VL_EXTENDS_WQ(96,64, __Vtemp_60, vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___a);
        VL_EXTENDS_WI(96,32, __Vtemp_61, vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___b);
        VL_MULS_WWW(96, __Vtemp_62, __Vtemp_60, __Vtemp_61);
        bufp->chgWData(oldp+1725,(__Vtemp_62),96);
        bufp->chgWData(oldp+1728,(vlSelfRef.test__DOT__taketwo__DOT___times_mul_27__DOT__mult__DOT___pipe_mul0),96);
        bufp->chgWData(oldp+1731,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[0]),137);
        bufp->chgWData(oldp+1736,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[1]),137);
        bufp->chgWData(oldp+1741,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[2]),137);
        bufp->chgWData(oldp+1746,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[3]),137);
        bufp->chgWData(oldp+1751,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[4]),137);
        bufp->chgWData(oldp+1756,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[5]),137);
        bufp->chgWData(oldp+1761,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[6]),137);
        bufp->chgWData(oldp+1766,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__mem[7]),137);
        bufp->chgCData(oldp+1771,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head),3);
        bufp->chgCData(oldp+1772,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail),3);
        bufp->chgBit(oldp+1773,(((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head) 
                                 == (7U & ((IData)(1U) 
                                           + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail))))));
        bufp->chgBit(oldp+1774,(((7U & ((IData)(2U) 
                                        + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__head))) 
                                 == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_read_req_fifo__DOT__tail))));
        bufp->chgWData(oldp+1775,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[0]),137);
        bufp->chgWData(oldp+1780,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[1]),137);
        bufp->chgWData(oldp+1785,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[2]),137);
        bufp->chgWData(oldp+1790,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[3]),137);
        bufp->chgWData(oldp+1795,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[4]),137);
        bufp->chgWData(oldp+1800,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[5]),137);
        bufp->chgWData(oldp+1805,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[6]),137);
        bufp->chgWData(oldp+1810,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__mem[7]),137);
        bufp->chgCData(oldp+1815,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head),3);
        bufp->chgCData(oldp+1816,(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail),3);
        bufp->chgBit(oldp+1817,(((IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head) 
                                 == (7U & ((IData)(1U) 
                                           + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail))))));
        bufp->chgBit(oldp+1818,(((7U & ((IData)(2U) 
                                        + (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__head))) 
                                 == (IData)(vlSelfRef.test__DOT__taketwo__DOT__inst___05Fmaxi_write_req_fifo__DOT__tail))));
    }
    bufp->chgBit(oldp+1819,(vlSelfRef.io_CLK));
    bufp->chgBit(oldp+1820,(vlSelfRef.io_RESETN));
}

void Vout___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root__trace_cleanup\n"); );
    // Body
    Vout___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vout___024root*>(voidSelf);
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
