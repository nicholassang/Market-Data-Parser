#include "decoder.hpp"

void Decoder::decode(MarketPacket* packet, MarketHandler& handler){
    auto* header = reinterpret_cast<PacketHeader*>(packet->data);
    switch(header->messageType){
        case 1:{
            auto* trade = reinterpret_cast<TradeMessage*>(packet->data + sizeof(PacketHeader));
            handler.onTrade(*trade);
            break;
        }
        case 2:{auto* quote = reinterpret_cast<QuoteMessage*>(packet->data + sizeof(PacketHeader));
            handler.onQuote(*quote);
            break;
        }
    }
}
