#pragma once

#include <cstdint>
#include <cstddef>

#include "ring_buffer.hpp"
#include "market_packet.hpp"

class Parser {
    public:
        Parser(RingBuffer<MarketPacket, 1024>& rb);

        void process();
    
    private:
        RingBuffer<MarketPacket, 1024>& ringBuffer;
        uint64_t expectedSequence = 1;
};