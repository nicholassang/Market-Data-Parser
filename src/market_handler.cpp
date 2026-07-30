#include "market_handler.hpp"
#include "market_packet.hpp"

void MarketHandler::onTrade(const TradeMessage& trade){
    std::cout << "Trade\n";
    std::cout.write(trade->symbol, 8);
    std::cout << "\n"; // symbol is char array string, may not contain null terminator, use write safer
    std::cout << trade->price << "\n";
    std::cout << trade->quantity << "\n";
}

void MarketHandler::onQuote(const QuoteMessage& quote){
    std::cout << "Quote\n";
    std::cout<< "Symbol: "; 
    std::cout.write(quote->symbol, 8); 
    std::cout<<"\n"; // symbol is char array string, may not contain null terminator, use write safer
    std::cout << "BidPrice: " << quote->bidPrice << "\n";
    std::cout << "AskPrice: " << quote->askPrice << "\n";
}
