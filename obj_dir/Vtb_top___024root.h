// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_top.h for the primary calling header

#ifndef VERILATED_VTB_TOP___024ROOT_H_
#define VERILATED_VTB_TOP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_top___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_top__DOT__clk;
    CData/*0:0*/ tb_top__DOT__rst;
    CData/*0:0*/ tb_top__DOT__valid;
    CData/*0:0*/ tb_top__DOT__waiting;
    CData/*0:0*/ tb_top__DOT__dut__DOT__parser_valid;
    CData/*0:0*/ tb_top__DOT__dut__DOT__side;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_top__DOT__clk__0;
    CData/*0:0*/ __VactContinue;
    SData/*15:0*/ tb_top__DOT__best_bid;
    SData/*15:0*/ tb_top__DOT__best_ask;
    SData/*15:0*/ tb_top__DOT__dut__DOT__price;
    IData/*31:0*/ tb_top__DOT__cycles;
    IData/*31:0*/ tb_top__DOT__packets_processed;
    IData/*31:0*/ tb_top__DOT__latency;
    IData/*31:0*/ tb_top__DOT__latency_start;
    IData/*31:0*/ __VactIterCount;
    QData/*63:0*/ tb_top__DOT__packet;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_he3ce3317__0;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_top___024root(Vtb_top__Syms* symsp, const char* v__name);
    ~Vtb_top___024root();
    VL_UNCOPYABLE(Vtb_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
