#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "parser.hpp"
#include "market_handler.hpp"

#include <iostream>

Parser::Parser(RingBuffer<MarketPacket,1024>& rb): ringBuffer(rb){
    std::cout << "Parser created" << "\n";
}

void Parser::process() {
    MarketPacket packet;
    MarketHandler handler;
    while (true) {
        if (!ringBuffer.pop(packet)){
            continue;
        }
        auto* header = reinterpret_cast<PacketHeader*>(packet.data);
        if (packet.length < sizeof(PacketHeader)){
            continue;
        }
        std::cout << "Sequence: " << header->sequence << "\n";
        if (header->sequence != lastSequence + 1){
            std::cout << "Packet Lost" << "\n";
        }
        lastSequence = header->sequence;

        // Consume market packet from ring buffer
        switch (header->messageType) {
            case 1: {
                if (packet.length < sizeof(PacketHeader) + sizeof(TradeMessage)){
                    continue;
                }
                auto* trade = reinterpret_cast<TradeMessage*>(packet.data + sizeof(PacketHeader));
                handler.onTrade(*trade);
                break;
            }
            case 2: {
                if (packet.length < sizeof(PacketHeader) + sizeof(QuoteMessage)){
                    continue;
                }
                auto* quote = reinterpret_cast<QuoteMessage*>(packet.data + sizeof(PacketHeader));
                handler.onQuote(*quote);
                break;
            }
        }
    }
}