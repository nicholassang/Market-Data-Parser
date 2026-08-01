#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "parser.hpp"
#include "market_handler.hpp"
#include "decoder.hpp"
#include <immintrin.h>

#include <iostream>
#include <chrono>

Parser::Parser(RingBuffer<MarketPacket*,1024>& rb, MarketHandler& h, PacketPool<1024>& p, Decoder& d): ringBuffer(rb), handler(h), pool(p), decoder(d){
    std::cout << "Parser created" << "\n";
}

void Parser::process() {
    MarketPacket* packet;

    while (true) {
        int processed = 0;
        while(processed < 64 && ringBuffer.pop(packet)){
            processPacket(packet);
            processed++;
        }
        if (processed == 0){
            _mm_pause();
        }

        // Print statistics in intervals 
        if (packetCount > 0 && packetCount % 1000000 == 0) {
            std::cout << "Interval: " << (packetCount % 100000) + 1 << '\n';
            std::cout << "Packets: " << packetCount << '\n';
            std::cout << "Average latency: " << totalLatency / packetCount << " ns\n";
            std::cout << "Max latency: " << maxLatency << " ns\n";
            std::cout << "Lost packets: " << totalPacketLost << "\n\n";
            std::cout << "Ring drops: " << ringBuffer.getDrops() << "\n";
        }
    }
}

void Parser::processPacket(MarketPacket* packet){
    if (packet->length < sizeof(PacketHeader)){
        pool.release(packet);
        return;
    }

    auto* header = reinterpret_cast<PacketHeader*>(packet->data);

    auto now = std::chrono::steady_clock::now();
    auto nowNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    auto latency = nowNs - header->timestamp;

    packetCount++;
    totalLatency += latency;
    maxLatency = std::max(maxLatency, latency);

    if (header->sequence != expectedSequence){
        uint64_t lost = header->sequence - expectedSequence;
        totalPacketLost += lost;
    }

    expectedSequence = header->sequence + 1;

    // Commented out for now to test latency, cout is computationally expensive for 1000000~ UDP packets
    //decoder.decode(packet, handler);

    pool.release(packet);
}