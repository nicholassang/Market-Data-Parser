#pragma once

#include "market_packet.hpp"
#include "order_book.hpp"

class MarketHandler {
    public:
        MarketHandler(OrderBook& book);
        void onTrade(const TradeMessage& trade);
        void onQuote(const QuoteMessage& quote);
    private:
        OrderBook orderBook;
};