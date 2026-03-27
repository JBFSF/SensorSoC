// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vout.h for the primary calling header

#include "Vout__pch.h"

void Vout___024root___nba_sequent__TOP__0(Vout___024root* vlSelf);
void Vout___024root___nba_sequent__TOP__1(Vout___024root* vlSelf);

void Vout___024root___eval_nba(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_nba\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vout___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        Vout___024root___nba_sequent__TOP__1(vlSelf);
    }
}

void Vout___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

void Vout___024root___eval_triggers__act(Vout___024root* vlSelf);

bool Vout___024root___eval_phase__act(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_phase__act\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vout___024root___eval_triggers__act(vlSelf);
    Vout___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vout___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vout___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

bool Vout___024root___eval_phase__nba(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_phase__nba\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vout___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vout___024root___eval_nba(vlSelf);
        Vout___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
bool Vout___024root___eval_phase__ico(Vout___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vout___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vout___024root___eval(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vout___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("/home/jfriday/sensorsoc/ML/nngen_out/taketwo.out/out.v", 3, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (Vout___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vout___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/jfriday/sensorsoc/ML/nngen_out/taketwo.out/out.v", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vout___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/jfriday/sensorsoc/ML/nngen_out/taketwo.out/out.v", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vout___024root___eval_phase__act(vlSelf));
    } while (Vout___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vout___024root___eval_debug_assertions(Vout___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vout___024root___eval_debug_assertions\n"); );
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.io_CLK & 0xfeU)))) {
        Verilated::overWidthError("io_CLK");
    }
    if (VL_UNLIKELY(((vlSelfRef.io_RESETN & 0xfeU)))) {
        Verilated::overWidthError("io_RESETN");
    }
}
#endif  // VL_DEBUG
