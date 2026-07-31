#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "parser.hpp"
#include "market_handler.hpp"

#include <iostream>
#include <chrono>

Parser::Parser(RingBuffer<MarketPacket*,1024>& rb, MarketHandler& h, PacketPool<1024>& p): ringBuffer(rb), handler(h), pool(p){
    std::cout << "Parser created" << "\n";
}

void Parser::process() {
    MarketPacket* packet;

    uint64_t totalPacketLost = 0;

    uint64_t packetCount = 0;
    uint64_t totalLatency = 0;
    uint64_t maxLatency = 0;

    while (true) {
        if (!ringBuffer.pop(packet)){
            continue;
        }
        auto* header = reinterpret_cast<PacketHeader*>(packet->data);
        if (packet->length < sizeof(PacketHeader)){
            continue;
        }
        // Check latency
        auto now = std::chrono::steady_clock::now();
        auto nowNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
        auto latency = nowNs - header->timestamp;
        packetCount++;
        totalLatency += latency;
        maxLatency = std::max(maxLatency, latency);

        // Seqeunce validation
        if (header->sequence != expectedSequence){
            //std::cout << "Expected: " << expectedSequence << " but got " << header->sequence << "\n";
            uint64_t lost = header->sequence - expectedSequence;
            totalPacketLost += lost;
            //std::cout << "Lost " << lost << " packets" << "\n";
        }
        expectedSequence = header->sequence + 1;

        // Consume market packet from ring buffer
        switch (header->messageType) {
            case 1: {
                if (packet->length < sizeof(PacketHeader) + sizeof(TradeMessage)){
                    continue;
                }
                auto* trade = reinterpret_cast<TradeMessage*>(packet->data + sizeof(PacketHeader));
                //handler.onTrade(*trade);
                break;
            }
            case 2: {
                if (packet->length < sizeof(PacketHeader) + sizeof(QuoteMessage)){
                    continue;
                }
                auto* quote = reinterpret_cast<QuoteMessage*>(packet->data + sizeof(PacketHeader));
                //handler.onQuote(*quote);
                break;
            }
            default:
                std::cout << "Unknown message type " << int(header->messageType) << "\n";
            break;
        }

        pool.release(packet);

        // Print statistics in intervals 
        if (packetCount % 1000000 == 0) {
            std::cout << "Interval: " << (packetCount % 100000) + 1 << '\n';
            std::cout << "Packets: " << packetCount << '\n';
            std::cout << "Average latency: " << totalLatency / packetCount << " ns\n";
            std::cout << "Max latency: " << maxLatency << " ns\n";
            std::cout << "Lost packets: " << totalPacketLost << "\n\n";
            std::cout << "Ring drops: " << ringBuffer.getDrops() << "\n";
        }
    }
}