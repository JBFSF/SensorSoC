// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vout__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vout::Vout(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vout__Syms(contextp(), _vcname__, this)}
    , io_CLK{vlSymsp->TOP.io_CLK}
    , io_RESETN{vlSymsp->TOP.io_RESETN}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vout::Vout(const char* _vcname__)
    : Vout(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vout::~Vout() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vout___024root___eval_debug_assertions(Vout___024root* vlSelf);
#endif  // VL_DEBUG
void Vout___024root___eval_static(Vout___024root* vlSelf);
void Vout___024root___eval_initial(Vout___024root* vlSelf);
void Vout___024root___eval_settle(Vout___024root* vlSelf);
void Vout___024root___eval(Vout___024root* vlSelf);

void Vout::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vout::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vout___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vout___024root___eval_static(&(vlSymsp->TOP));
        Vout___024root___eval_initial(&(vlSymsp->TOP));
        Vout___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vout___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vout::eventsPending() { return false; }

uint64_t Vout::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vout::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vout___024root___eval_final(Vout___024root* vlSelf);

VL_ATTR_COLD void Vout::final() {
    Vout___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vout::hierName() const { return vlSymsp->name(); }
const char* Vout::modelName() const { return "Vout"; }
unsigned Vout::threads() const { return 1; }
void Vout::prepareClone() const { contextp()->prepareClone(); }
void Vout::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vout::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vout___024root__trace_decl_types(VerilatedVcd* tracep);

void Vout___024root__trace_init_top(Vout___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vout___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vout___024root*>(voidSelf);
    Vout__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vout___024root__trace_decl_types(tracep);
    Vout___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vout___024root__trace_register(Vout___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vout::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vout::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vout___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
