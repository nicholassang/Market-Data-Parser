#pragma once

#include "market_handler.hpp"

class Decoder{
    public:
        void decode(MarketPacket* packet, MarketHandler& handler);
};