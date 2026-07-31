#include <thread>
#include "parser.hpp"
#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "market_handler.hpp"

int main() {
    // Ring Buffer
    RingBuffer<MarketPacket, 1024> ringBuffer;
    // Handler for logging etc.
    MarketHandler handler;
    // Receiver
    UDPReceiver receiver(9000,ringBuffer);
    // Parser
    Parser parser(ringBuffer, handler);

    // 2 threads to share the same resource ringBuffer
    std::thread receiverThread([&]() {receiver.receive();});
    std::thread parserThread([&]() {parser.process();});
    receiverThread.join();
    parserThread.join();

    return 0;
}