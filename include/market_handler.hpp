#pragma once

#include "market_packet.hpp"

class MarketHandler {

public:
    void onTrade(const TradeMessage& trade);
    void onQuote(const QuoteMessage& quote);
};