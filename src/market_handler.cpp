#include "market_handler.hpp"
#include "market_packet.hpp"
#include <iostream>

MarketHandler::MarketHandler(OrderBook& book): orderBook(book){}

void MarketHandler::onTrade(const TradeMessage& trade) {
    orderBook.addTrade(trade.price, trade.quantity);
}

void MarketHandler::onQuote(const QuoteMessage& quote){
    orderBook.addBid(quote.bidPrice, quote.bidQuantity);
    orderBook.addAsk(quote.askPrice, quote.bidQuantity);
}