// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__0(Vtb_top___024root* vlSelf);
VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1(Vtb_top___024root* vlSelf);

void Vtb_top___024root___eval_initial(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial\n"); );
    // Body
    Vtb_top___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_top___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__tb_top__DOT__clk__0 
        = vlSelf->tb_top__DOT__clk;
}

VL_INLINE_OPT VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__0(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Init
    IData/*31:0*/ tb_top__DOT__unnamedblk1__DOT__i;
    tb_top__DOT__unnamedblk1__DOT__i = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__0__price;
    __Vtask_tb_top__DOT__send_packet__0__price = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__0__quantity;
    __Vtask_tb_top__DOT__send_packet__0__quantity = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__send_packet__0__side;
    __Vtask_tb_top__DOT__send_packet__0__side = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__1__price;
    __Vtask_tb_top__DOT__send_packet__1__price = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__1__quantity;
    __Vtask_tb_top__DOT__send_packet__1__quantity = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__send_packet__1__side;
    __Vtask_tb_top__DOT__send_packet__1__side = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__2__price;
    __Vtask_tb_top__DOT__send_packet__2__price = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__2__quantity;
    __Vtask_tb_top__DOT__send_packet__2__quantity = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__send_packet__2__side;
    __Vtask_tb_top__DOT__send_packet__2__side = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__3__price;
    __Vtask_tb_top__DOT__send_packet__3__price = 0;
    SData/*15:0*/ __Vtask_tb_top__DOT__send_packet__3__quantity;
    __Vtask_tb_top__DOT__send_packet__3__quantity = 0;
    CData/*0:0*/ __Vtask_tb_top__DOT__send_packet__3__side;
    __Vtask_tb_top__DOT__send_packet__3__side = 0;
    // Body
    vlSelf->tb_top__DOT__clk = 0U;
    vlSelf->tb_top__DOT__rst = 1U;
    vlSelf->tb_top__DOT__valid = 0U;
    vlSelf->tb_top__DOT__packet = 0ULL;
    vlSelf->tb_top__DOT__cycles = 0U;
    vlSelf->tb_top__DOT__packets_processed = 0U;
    vlSelf->tb_top__DOT__waiting = 0U;
    co_await vlSelf->__VdlySched.delay(0x4e20ULL, nullptr, 
                                       "fpga/sim/tb_top.sv", 
                                       166);
    vlSelf->tb_top__DOT__rst = 0U;
    __Vtask_tb_top__DOT__send_packet__0__side = 0U;
    __Vtask_tb_top__DOT__send_packet__0__quantity = 0x32U;
    __Vtask_tb_top__DOT__send_packet__0__price = 0x64U;
    vlSelf->tb_top__DOT__packet = (((QData)((IData)(
                                                    (((IData)(__Vtask_tb_top__DOT__send_packet__0__quantity) 
                                                      << 0x10U) 
                                                     | (IData)(__Vtask_tb_top__DOT__send_packet__0__price)))) 
                                    << 0x20U) | (QData)((IData)(
                                                                ((IData)(__Vtask_tb_top__DOT__send_packet__0__side) 
                                                                 << 0x1fU))));
    vlSelf->tb_top__DOT__valid = 1U;
    co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_top.clk)", 
                                                       "fpga/sim/tb_top.sv", 
                                                       128);
    vlSelf->tb_top__DOT__valid = 0U;
    __Vtask_tb_top__DOT__send_packet__1__side = 0U;
    __Vtask_tb_top__DOT__send_packet__1__quantity = 0x14U;
    __Vtask_tb_top__DOT__send_packet__1__price = 0x69U;
    vlSelf->tb_top__DOT__packet = (((QData)((IData)(
                                                    (((IData)(__Vtask_tb_top__DOT__send_packet__1__quantity) 
                                                      << 0x10U) 
                                                     | (IData)(__Vtask_tb_top__DOT__send_packet__1__price)))) 
                                    << 0x20U) | (QData)((IData)(
                                                                ((IData)(__Vtask_tb_top__DOT__send_packet__1__side) 
                                                                 << 0x1fU))));
    vlSelf->tb_top__DOT__valid = 1U;
    co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_top.clk)", 
                                                       "fpga/sim/tb_top.sv", 
                                                       128);
    vlSelf->tb_top__DOT__valid = 0U;
    __Vtask_tb_top__DOT__send_packet__2__side = 1U;
    __Vtask_tb_top__DOT__send_packet__2__quantity = 0x1eU;
    __Vtask_tb_top__DOT__send_packet__2__price = 0x6eU;
    vlSelf->tb_top__DOT__packet = (((QData)((IData)(
                                                    (((IData)(__Vtask_tb_top__DOT__send_packet__2__quantity) 
                                                      << 0x10U) 
                                                     | (IData)(__Vtask_tb_top__DOT__send_packet__2__price)))) 
                                    << 0x20U) | (QData)((IData)(
                                                                ((IData)(__Vtask_tb_top__DOT__send_packet__2__side) 
                                                                 << 0x1fU))));
    vlSelf->tb_top__DOT__valid = 1U;
    co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge tb_top.clk)", 
                                                       "fpga/sim/tb_top.sv", 
                                                       128);
    vlSelf->tb_top__DOT__valid = 0U;
    tb_top__DOT__unnamedblk1__DOT__i = 0U;
    while (VL_GTS_III(32, 0x3e8U, tb_top__DOT__unnamedblk1__DOT__i)) {
        __Vtask_tb_top__DOT__send_packet__3__side = 
            (1U & tb_top__DOT__unnamedblk1__DOT__i);
        __Vtask_tb_top__DOT__send_packet__3__quantity = 0xaU;
        __Vtask_tb_top__DOT__send_packet__3__price 
            = (0xffffU & ((IData)(0x64U) + tb_top__DOT__unnamedblk1__DOT__i));
        vlSelf->tb_top__DOT__packet = (((QData)((IData)(
                                                        (((IData)(__Vtask_tb_top__DOT__send_packet__3__quantity) 
                                                          << 0x10U) 
                                                         | (IData)(__Vtask_tb_top__DOT__send_packet__3__price)))) 
                                        << 0x20U) | (QData)((IData)(
                                                                    ((IData)(__Vtask_tb_top__DOT__send_packet__3__side) 
                                                                     << 0x1fU))));
        vlSelf->tb_top__DOT__valid = 1U;
        co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_top.clk)", 
                                                           "fpga/sim/tb_top.sv", 
                                                           128);
        vlSelf->tb_top__DOT__valid = 0U;
        tb_top__DOT__unnamedblk1__DOT__i = ((IData)(1U) 
                                            + tb_top__DOT__unnamedblk1__DOT__i);
    }
    co_await vlSelf->__VdlySched.delay(0x4e20ULL, nullptr, 
                                       "fpga/sim/tb_top.sv", 
                                       225);
    VL_WRITEF("======================\n FPGA BENCHMARK \n======================\nPackets processed = %0d\nCycles = %0d\nPackets/cycle = %f\nThroughput @250MHz = %f Mpps\nLatency = %0d cycles\nLatency = %0f ns\nBest Bid = %5#\nBest Ask = %5#\n",
              32,vlSelf->tb_top__DOT__packets_processed,
              32,vlSelf->tb_top__DOT__cycles,64,(VL_ISTOR_D_I(32, vlSelf->tb_top__DOT__packets_processed) 
                                                 / 
                                                 VL_ISTOR_D_I(32, vlSelf->tb_top__DOT__cycles)),
              64,((250.0 * VL_ISTOR_D_I(32, vlSelf->tb_top__DOT__packets_processed)) 
                  / VL_ISTOR_D_I(32, vlSelf->tb_top__DOT__cycles)),
              32,vlSelf->tb_top__DOT__latency,64,(4.0 
                                                  * 
                                                  VL_ISTOR_D_I(32, vlSelf->tb_top__DOT__latency)),
              16,(IData)(vlSelf->tb_top__DOT__best_bid),
              16,vlSelf->tb_top__DOT__best_ask);
    VL_FINISH_MT("fpga/sim/tb_top.sv", 295, "");
}

VL_INLINE_OPT VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x7d0ULL, 
                                           nullptr, 
                                           "fpga/sim/tb_top.sv", 
                                           44);
        vlSelf->tb_top__DOT__clk = (1U & (~ (IData)(vlSelf->tb_top__DOT__clk)));
    }
}

void Vtb_top___024root___eval_act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtb_top___024root___nba_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vdly__tb_top__DOT__cycles;
    __Vdly__tb_top__DOT__cycles = 0;
    IData/*31:0*/ __Vdly__tb_top__DOT__latency_start;
    __Vdly__tb_top__DOT__latency_start = 0;
    CData/*0:0*/ __Vdly__tb_top__DOT__waiting;
    __Vdly__tb_top__DOT__waiting = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__best_bid;
    __Vdly__tb_top__DOT__best_bid = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__best_ask;
    __Vdly__tb_top__DOT__best_ask = 0;
    // Body
    __Vdly__tb_top__DOT__waiting = vlSelf->tb_top__DOT__waiting;
    __Vdly__tb_top__DOT__latency_start = vlSelf->tb_top__DOT__latency_start;
    __Vdly__tb_top__DOT__cycles = vlSelf->tb_top__DOT__cycles;
    __Vdly__tb_top__DOT__best_ask = vlSelf->tb_top__DOT__best_ask;
    __Vdly__tb_top__DOT__best_bid = vlSelf->tb_top__DOT__best_bid;
    if (vlSelf->tb_top__DOT__valid) {
        vlSelf->tb_top__DOT__packets_processed = ((IData)(1U) 
                                                  + vlSelf->tb_top__DOT__packets_processed);
        __Vdly__tb_top__DOT__latency_start = vlSelf->tb_top__DOT__cycles;
        __Vdly__tb_top__DOT__waiting = 1U;
    }
    if (vlSelf->tb_top__DOT__rst) {
        __Vdly__tb_top__DOT__best_ask = 0xffffU;
        __Vdly__tb_top__DOT__best_bid = 0U;
        vlSelf->tb_top__DOT__dut__DOT__parser_valid = 0U;
        vlSelf->tb_top__DOT__dut__DOT__side = 0U;
        vlSelf->tb_top__DOT__dut__DOT__price = 0U;
    } else {
        if (vlSelf->tb_top__DOT__dut__DOT__parser_valid) {
            if (vlSelf->tb_top__DOT__dut__DOT__side) {
                if (((IData)(vlSelf->tb_top__DOT__dut__DOT__price) 
                     < (IData)(vlSelf->tb_top__DOT__best_ask))) {
                    __Vdly__tb_top__DOT__best_ask = vlSelf->tb_top__DOT__dut__DOT__price;
                }
            }
            if ((1U & (~ (IData)(vlSelf->tb_top__DOT__dut__DOT__side)))) {
                if (((IData)(vlSelf->tb_top__DOT__dut__DOT__price) 
                     > (IData)(vlSelf->tb_top__DOT__best_bid))) {
                    __Vdly__tb_top__DOT__best_bid = vlSelf->tb_top__DOT__dut__DOT__price;
                }
            }
        }
        vlSelf->tb_top__DOT__dut__DOT__parser_valid = 0U;
        if (vlSelf->tb_top__DOT__valid) {
            vlSelf->tb_top__DOT__dut__DOT__parser_valid = 1U;
            vlSelf->tb_top__DOT__dut__DOT__side = (1U 
                                                   & (IData)(
                                                             (vlSelf->tb_top__DOT__packet 
                                                              >> 0x1fU)));
            vlSelf->tb_top__DOT__dut__DOT__price = 
                (0xffffU & (IData)((vlSelf->tb_top__DOT__packet 
                                    >> 0x20U)));
        }
    }
    __Vdly__tb_top__DOT__cycles = ((IData)(1U) + vlSelf->tb_top__DOT__cycles);
    if (vlSelf->tb_top__DOT__waiting) {
        if (((0U != (IData)(vlSelf->tb_top__DOT__best_bid)) 
             | (0xffffU != (IData)(vlSelf->tb_top__DOT__best_ask)))) {
            vlSelf->tb_top__DOT__latency = (vlSelf->tb_top__DOT__cycles 
                                            - vlSelf->tb_top__DOT__latency_start);
            __Vdly__tb_top__DOT__waiting = 0U;
        }
    }
    vlSelf->tb_top__DOT__cycles = __Vdly__tb_top__DOT__cycles;
    vlSelf->tb_top__DOT__latency_start = __Vdly__tb_top__DOT__latency_start;
    vlSelf->tb_top__DOT__waiting = __Vdly__tb_top__DOT__waiting;
    vlSelf->tb_top__DOT__best_bid = __Vdly__tb_top__DOT__best_bid;
    vlSelf->tb_top__DOT__best_ask = __Vdly__tb_top__DOT__best_ask;
}

void Vtb_top___024root___eval_nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtb_top___024root___timing_resume(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___timing_resume\n"); );
    // Body
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_he3ce3317__0.resume("@(posedge tb_top.clk)");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vtb_top___024root___timing_commit(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___timing_commit\n"); );
    // Body
    if ((! (1ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_he3ce3317__0.commit("@(posedge tb_top.clk)");
    }
}

void Vtb_top___024root___eval_triggers__act(Vtb_top___024root* vlSelf);

bool Vtb_top___024root___eval_phase__act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_top___024root___eval_triggers__act(vlSelf);
    Vtb_top___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtb_top___024root___timing_resume(vlSelf);
        Vtb_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_top___024root___eval_phase__nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb_top___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__nba(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_top___024root___eval(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtb_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("fpga/sim/tb_top.sv", 4, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("fpga/sim/tb_top.sv", 4, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtb_top___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtb_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtb_top___024root___eval_debug_assertions(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
