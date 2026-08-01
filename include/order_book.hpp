#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

struct PriceLevel {
    uint64_t price = 0;
    uint32_t quantity = 0;
};

class OrderBook {
public:
    void addTrade(uint64_t price, uint32_t quantity);

    void addBid(uint64_t price, uint32_t qty);
    void addAsk(uint64_t price, uint32_t qty);

    void removeBid(uint64_t price);
    void removeAsk(uint64_t price);

    uint64_t bestBid() const;
    uint64_t bestAsk() const;

    const PriceLevel* getBids() const { return bids.data(); }
    const PriceLevel* getAsks() const { return asks.data(); }

    size_t bidLevels() const { return bidCount; }
    size_t askLevels() const { return askCount; }

private:
    static constexpr size_t MAX_LEVELS = 1024;

    std::array<PriceLevel, MAX_LEVELS> bids{};
    std::array<PriceLevel, MAX_LEVELS> asks{};

    size_t bidCount = 0;
    size_t askCount = 0;

    uint64_t lastTradePrice = 0;
    uint64_t totalVolume = 0;

};