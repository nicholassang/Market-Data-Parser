#pragma once
#include <cstdint>

struct MarketDataPacket {
    uint32_t sequence;
    uint32_t price;
    uint32_t quantity;
};