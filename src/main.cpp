#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"

int main() {
    RingBuffer<MarketPacket, 1024> ringBuffer;
    UDPReceiver receiver(9000, ringBuffer);

    receiver.receive();

    return 0;
}