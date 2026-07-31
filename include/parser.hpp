#pragma once

#include <cstdint>
#include <cstddef>

#include "ring_buffer.hpp"
#include "market_packet.hpp"
#include "market_handler.hpp"
#include "packet_pool.hpp"

class Parser {
    public:
        Parser(RingBuffer<MarketPacket*, 1024>& rb, MarketHandler& h, PacketPool<1024>& p);

        void process();
    
    private:
        RingBuffer<MarketPacket*, 1024>& ringBuffer;
        uint64_t expectedSequence = 1;
        MarketHandler& handler;
        PacketPool<1024>& pool;
};