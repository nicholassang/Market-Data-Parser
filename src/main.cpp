#include <thread>

#include "parser.hpp"
#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "market_handler.hpp"
#include "packet_pool.hpp"
#include "decoder.hpp"

int main() {
    // Ring Buffer
    RingBuffer<MarketPacket*, 65536> ringBuffer;
    // Packet Pool
        /*
            MarketPacket size ~1KB
            65536 * 1KB ≈64MB
        */
    auto pool = std::make_unique<PacketPool<65536>>();

    // Handler for logging etc.
    MarketHandler handler;
    // Decoder for datatype handling
    Decoder decoder;
    // Receiver
    UDPReceiver receiver(9000, ringBuffer, *pool);
    // Parser
    Parser parser(ringBuffer, handler, *pool, decoder);

    // 2 threads to share the same resource ringBuffer
    std::thread receiverThread([&]() {receiver.receive();});
    std::thread parserThread([&]() {parser.process();});
    receiverThread.join();
    parserThread.join();

    return 0;
}