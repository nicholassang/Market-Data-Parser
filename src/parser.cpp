#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "parser.hpp"
#include "market_handler.hpp"
#include "decoder.hpp"
#include <immintrin.h>
#include <x86intrin.h>

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

            printHistogram();

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
    // We use __rdtscp which calculates internal clock speed
    unsigned int aux;
    uint64_t now = __rdtscp(&aux);
    uint64_t latencyCycles = now - header->timestamp;

    double cyclesPerNanosecond = 3.8; // Assume CPU is 3.8Ghtz
    uint64_t latencyNs = latencyCycles / cyclesPerNanosecond; // cycle / freq = seconds (latency) 

    packetCount++;
    totalLatency += latencyNs;
    maxLatency = std::max(maxLatency, latencyNs);

    recordLatency(latencyNs);

    // Log lost packets
    if (header->sequence != expectedSequence){
        uint64_t lost = header->sequence - expectedSequence;
        totalPacketLost += lost;
    }
    expectedSequence = header->sequence + 1;

    // Commented out for now to test latency, cout is computationally expensive for 1000000~ UDP packets
    // decoder.decode(packet, handler);

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
// Track latency in log(2^n) buckets
void Parser::recordLatency(uint64_t latency){
    // convert ns -> us
    uint64_t us = latency / 1000;

    int bucket = 0;
    uint64_t value = 1;
    while (value < us && bucket < HISTOGRAM_SIZE - 1){
        value *= 2;
        bucket++;
    }

    latencyBuckets[bucket]++;
}

// Function to get percentile, algorithm below
uint64_t Parser::getPercentile(double percentile){
    uint64_t target = static_cast<uint64_t>(packetCount * percentile);

    uint64_t cumulative = 0;
    uint64_t upper = 1;

    for (int i = 0; i < HISTOGRAM_SIZE; i++){
        cumulative += latencyBuckets[i];

        if (cumulative >= target){
            return upper * 1000; // convert us -> ns
        }

        upper *= 2;
    }

    return upper * 1000;
}

void Parser::printHistogram(){
    std::cout << "\nLatency Histogram\n";

    uint64_t lower = 0;
    uint64_t upper = 1;
    for (int i = 0; i < HISTOGRAM_SIZE; i++){
        std::cout << lower << "-" << upper << "us: " << latencyBuckets[i] << "\n";

        lower = upper;
        upper *= 2;
    }
}