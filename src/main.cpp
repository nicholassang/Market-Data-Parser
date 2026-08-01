#include <thread>
#include <csignal>

#include "runtime.hpp"
#include "parser.hpp"
#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "market_handler.hpp"
#include "packet_pool.hpp"
#include "decoder.hpp"
#include "cpu_affinity.hpp"
#include "order_book.hpp"

void signalHandler(int){
    Runtime::running = false;
}

int main() {
    // For graceful shutdown
    signal(SIGINT, signalHandler);

    // Ring Buffer
    RingBuffer<MarketPacket*, 65536> ringBuffer;
    // Packet Pool
        /*
            MarketPacket size ~1KB
            65536 * 1KB ≈64MB
        */
    auto pool = std::make_unique<PacketPool<65536>>();

    // Order Book
    OrderBook orderBook;

    // Handler for logging etc.
    MarketHandler handler(orderBook);
    // Decoder for datatype handling
    Decoder decoder;
    // Receiver
    UDPReceiver receiver(9000, ringBuffer, *pool);
    // Parser
    Parser parser(ringBuffer, handler, *pool, decoder);

    // 2 threads to share the same resource ringBuffer
    std::thread receiverThread([&]() {
        pinThread(0);
        receiver.receive();
    });
    std::thread parserThread([&]() {
        pinThread(1);
        parser.process();
    });
    receiverThread.join();
    parserThread.join();

    return 0;
}