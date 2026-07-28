#pragma once

#include <cstdint>

#pragma pack(push, 1)
struct MarketDataPacket {
    uint32_t sequence;
    uint64_t price;
    uint32_t quantity;
};
#pragma pack(pop)