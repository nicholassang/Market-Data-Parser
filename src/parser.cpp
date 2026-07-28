#include "packet.hpp"

void parse_packet(const char* buffer) {
    auto packet =
        reinterpret_cast<const MarketDataPacket*>(buffer);

    (void)packet;
}