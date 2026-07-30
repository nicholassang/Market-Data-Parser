#include <thread>
#include "parser.hpp"
#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"

int main() {
    RingBuffer<MarketPacket, 1024> ringBuffer;
    UDPReceiver receiver(9000,ringBuffer);
    Parser parser(ringBuffer);

    // 2 threads to share the same resource ringBuffer
    std::thread receiverThread([&]() {receiver.receive();});
    std::thread parserThread([&]() {parser.process();});
    receiverThread.join();
    parserThread.join();

    return 0;
}