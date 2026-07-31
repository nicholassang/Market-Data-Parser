#pragma once

#include <cstdint>
#include <cstddef>

#include "ring_buffer.hpp"
#include "market_packet.hpp"
#include "market_handler.hpp"

class Parser {
    public:
        Parser(RingBuffer<MarketPacket, 1024>& rb, MarketHandler& h);

        void process();
    
    private:
        RingBuffer<MarketPacket, 1024>& ringBuffer;
        uint64_t expectedSequence = 1;
        MarketHandler& handler;
};