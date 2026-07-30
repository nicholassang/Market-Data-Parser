#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "parser.hpp"

#include <iostream>

Parser::Parser(RingBuffer<MarketPacket,1024>& rb): ringBuffer(rb){
    std::cout << "Parser created" << "\n";
}

void Parser::process() {
    MarketPacket packet;
    while (true) {
        if (!ringBuffer.pop(packet)){
            continue;
        }
        auto* header = reinterpret_cast<PacketHeader*>(packet.data);
        std::cout << "Sequence: " << header->sequence << "\n";
        switch (header->messageType) {
            case 1: {
                auto* trade =
                    reinterpret_cast<TradeMessage*>(
                        packet.data + sizeof(PacketHeader)
                    );
                std::cout << "Trade\n";
                std::cout.write(trade->symbol, 8);
                std::cout << "\n"; // symbol is char array string, may not contain null terminator, use write safer
                std::cout << trade->price << "\n";
                std::cout << trade->quantity << "\n";
                break;
            }
            case 2: {
                auto* quote =
                    reinterpret_cast<QuoteMessage*>(
                        packet.data + sizeof(PacketHeader)
                    );
                std::cout << "Quote\n";
                std::cout<< "Symbol: "; 
                std::cout.write(quote->symbol, 8); 
                std::cout<<"\n"; // symbol is char array string, may not contain null terminator, use write safer
                std::cout << "BidPrice: " << quote->bidPrice << "\n";
                std::cout << "AskPrice: " << quote->askPrice << "\n";
                break;
            }
        }
    }
}