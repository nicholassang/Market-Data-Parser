// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VL_ATTR_COLD void Vtb_top___024root___eval_static(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtb_top___024root___eval_final(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vtb_top___024root___eval_settle(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge tb_top.clk)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge tb_top.clk)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_top___024root___ctor_var_reset(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->tb_top__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__rst = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__packet = VL_RAND_RESET_Q(64);
    vlSelf->tb_top__DOT__valid = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__best_bid = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__best_ask = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__cycles = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__packets_processed = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__latency = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__latency_start = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__waiting = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__dut__DOT__parser_valid = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__dut__DOT__price = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__dut__DOT__side = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__tb_top__DOT__clk__0 = VL_RAND_RESET_I(1);
}
