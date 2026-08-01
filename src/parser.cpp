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

            std::cout << "\nLatency Histogram\n";
            std::cout << "<1us: " << latencyBuckets[0] << "\n";
            std::cout << "1-5us: " << latencyBuckets[1] << "\n";
            std::cout << "5-10us: " << latencyBuckets[2] << "\n";
            std::cout << "10-50us: " << latencyBuckets[3] << "\n";
            std::cout << "50-100us: " << latencyBuckets[4] << "\n";
            std::cout << "100-500us: " << latencyBuckets[5] << "\n";
            std::cout << "500us-1ms: " << latencyBuckets[6] << "\n";
            std::cout << "1-5ms: " << latencyBuckets[7] << "\n";
            std::cout << "5-10ms: " << latencyBuckets[8] << "\n";
            std::cout << ">10ms: " << latencyBuckets[9] << "\n";

            std::cout << "p50: " << getPercentile(0.50) << " ns\n";
            std::cout << "p99: " << getPercentile(0.99) << " ns\n";
            std::cout << "p99.9: " << getPercentile(0.999) << " ns\n";

            // Reset to get statistics per million packets
            latencyBuckets.fill(0);
            totalLatency = 0;
            maxLatency = 0;
            packetCount = 0;
        }
    }
}

void Parser::processPacket(MarketPacket* packet){
    if (packet->length < sizeof(PacketHeader)){
        pool.release(packet);
        return;
    }

    auto* header = reinterpret_cast<PacketHeader*>(packet->data);

    // Log latency
    auto now = std::chrono::steady_clock::now();
    auto nowNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    auto latency = nowNs - header->timestamp;
    packetCount++;
    totalLatency += latency;
    maxLatency = std::max(maxLatency, latency);
    recordLatency(latency);

    // Log lost packets
    if (header->sequence != expectedSequence){
        uint64_t lost = header->sequence - expectedSequence;
        totalPacketLost += lost;
    }
    expectedSequence = header->sequence + 1;

    // Commented out for now to test latency, cout is computationally expensive for 1000000~ UDP packets
    //decoder.decode(packet, handler);

    pool.release(packet);
}
/*
    Latency Buckets Ref
    bucket 0: <1us
    bucket 1: 1-5us
    bucket 2: 5-10us
    bucket 3: 10-50us
    bucket 4: 50-100us
    bucket 5: 100-500us
    bucket 6: 500us-1ms
    bucket 7: 1-5ms
    bucket 8: 5-10ms
    bucket 9: >10ms
*/
void Parser::recordLatency(uint64_t latency){
    uint64_t us = latency / 1000;

    if(us < 1) latencyBuckets[0]++;
    else if(us < 5) latencyBuckets[1]++;
    else if(us < 10) latencyBuckets[2]++; 
    else if(us < 50) latencyBuckets[3]++;
    else if(us < 100) latencyBuckets[4]++;
    else if(us < 500) latencyBuckets[5]++;
    else if(us < 1000) latencyBuckets[6]++;
    else if(us < 5000) latencyBuckets[7]++;
    else if(us < 10000) latencyBuckets[8]++;
    else latencyBuckets[9]++;
}

uint64_t Parser::getPercentile(double percentile){
    uint64_t target = static_cast<uint64_t>(packetCount * percentile);
    uint64_t cumulative = 0;
    uint64_t bucketUpperBounds[10] = {
        1000,        // <1us
        5000,        // <5us
        10000,       // <10us
        50000,       // <50us
        100000,      // <100us
        500000,      // <500us
        1000000,     // <1ms
        5000000,     // <5ms
        10000000,    // <10ms
        UINT64_MAX
    };

    for (int i = 0; i < 10; i++){
        cumulative += latencyBuckets[i];
        if(cumulative >= target)
        {
            return bucketUpperBounds[i];
        }
    }
    return UINT64_MAX;
}