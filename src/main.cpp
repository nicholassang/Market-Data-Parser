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
#include "dpdk_init.hpp"
#include "dpdk_receiver.hpp"
#include "dpdk_port.hpp"

void signalHandler(int){
    Runtime::running = false;
}

int main() {
    // For graceful shutdown
    signal(SIGINT, signalHandler);

    // Initialize DPDK runtime
    if(init_dpdk() < 0){
        return 1;
    }

    // Initialize NIC
    DPDKPort port;
    if(!port.init()){
        return 1;
    }

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

    // A: UDP Receiver
    // UDPReceiver receiver(9000, ringBuffer, *pool);

    // B: DPDK Receiver
    DPDKReceiver receiver(ringBuffer, *pool, 0); // DPDK port id -> 0

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