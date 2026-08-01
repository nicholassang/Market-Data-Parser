#pragma once

#include <cstdint>
#include <cstddef>

struct PriceLevel {
    uint64_t price;
    uint32_t quantity;
};

class OrderBook {
    public:
        void addTrade(uint64_t price, uint32_t quantity) {
            // Stub for now
        }

        void addBid(uint64_t price, uint32_t qty) {
            if (bidCount < MAX_LEVELS){
                bids[bidCount++] = {price, qty};
            }
        }

        void addAsk(uint64_t price, uint32_t qty) {
            if (askCount < MAX_LEVELS){
                asks[askCount++] = {price, qty};
            }
        }

        uint64_t bestBid() const {
            uint64_t best = 0;
            for (size_t i = 0; i < bidCount; i++) {
                if (bids[i].price > best){
                    best = bids[i].price;
                }
            }
            return best;
        }

        uint64_t bestAsk() const {
            if (askCount == 0){
                return 0;
            }
            uint64_t best = asks[0].price;
            for (size_t i = 1; i < askCount; i++) {
                if (asks[i].price < best){
                    best = asks[i].price;
                }
            }
            return best;
        }

    private:
        static constexpr size_t MAX_LEVELS = 1024;

        PriceLevel bids[MAX_LEVELS];
        PriceLevel asks[MAX_LEVELS];

        size_t bidCount = 0;
        size_t askCount = 0;
};