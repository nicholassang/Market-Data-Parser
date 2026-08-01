#pragma once
#include <cstdint>
#include <cstddef>

#pragma pack(push, 1)

enum MessageType{
    TRADE = 1,
    QUOTE = 2,
};

struct alignas(64) MarketPacket {
    char data[1024];
    size_t length;
};

struct PacketHeader {
    uint16_t length;
    uint8_t messageType;
    uint64_t sequence;
    uint64_t timestamp;
};

// We consider messageType = 1
struct TradeMessage {
    char symbol[8];
    uint64_t price;
    uint32_t quantity;
};

// We consider messageType = 2
struct QuoteMessage {
    char symbol[8];
    uint64_t bidPrice;
    uint64_t askPrice;
};

#pragma pack(pop)