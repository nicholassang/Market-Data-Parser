#pragma once

#include <cstdint>
#include <cstddef>
#include <array>

#include "ring_buffer.hpp"
#include "market_packet.hpp"
#include "market_handler.hpp"
#include "packet_pool.hpp"
#include "decoder.hpp"

class Parser {
    public:
        Parser(RingBuffer<MarketPacket*, 1024>& rb, MarketHandler& h, PacketPool<1024>& p, Decoder& d);

        void process();
    
    private:
        RingBuffer<MarketPacket*, 1024>& ringBuffer;
        MarketHandler& handler;
        PacketPool<1024>& pool;
        Decoder& decoder;

        std::array<uint64_t, 10> latencyBuckets{};

        void recordLatency(uint64_t latency);
        void processPacket(MarketPacket* packet);
        uint64_t getPercentile(double percentile);

        uint64_t expectedSequence = 1;
        uint64_t totalPacketLost = 0;
        uint64_t packetCount = 0;
        uint64_t totalLatency = 0;
        uint64_t maxLatency = 0;
};