#include "order_book.hpp"

void OrderBook::addTrade(uint64_t price, uint32_t quantity) {
    lastTradePrice_ = price;
    totalVolume_ += quantity;
}

void OrderBook::addBid(uint64_t price, uint32_t qty) {
    updateBid(price, qty);
}

void OrderBook::addAsk(uint64_t price, uint32_t qty) {
    updateAsk(price, qty);
}

void OrderBook::updateBid(uint64_t price, uint32_t qty) {
    for (size_t i = 0; i < bidCount; i++) {
        if (bids[i].price == price) {
            bids[i].quantity = qty;
            if (qty == 0) removeBid(price);
            return;
        }
    }

    if (qty == 0 || bidCount == MAX_LEVELS) return;

    size_t pos = bidCount;
    while (pos > 0 && bids[pos - 1].price < price) {
        bids[pos] = bids[pos - 1];
        pos--;
    }

    bids[pos] = {price, qty};
    bidCount++;
}

void OrderBook::updateAsk(uint64_t price, uint32_t qty) {
    for (size_t i = 0; i < askCount; i++) {
        if (asks[i].price == price) {
            asks[i].quantity = qty;
            if (qty == 0) removeAsk(price);
            return;
        }
    }

    if (qty == 0 || askCount == MAX_LEVELS) return;

    size_t pos = askCount;
    while (pos > 0 && asks[pos - 1].price > price) {
        asks[pos] = asks[pos - 1];
        pos--;
    }

    asks[pos] = {price, qty};
    askCount++;
}

void OrderBook::removeBid(uint64_t price) {
    for (size_t i = 0; i < bidCount; i++) {
        if (bids[i].price == price) {
            for (size_t j = i + 1; j < bidCount; j++) {
                bids[j - 1] = bids[j];
            }
            bidCount--;
            return;
        }
    }
}

void OrderBook::removeAsk(uint64_t price) {
    for (size_t i = 0; i < askCount; i++) {
        if (asks[i].price == price) {
            for (size_t j = i + 1; j < askCount; j++) {
                asks[j - 1] = asks[j];
            }
            askCount--;
            return;
        }
    }
}

uint64_t OrderBook::bestBid() const {
    return bidCount > 0 ? bids[0].price : 0;
}

uint64_t OrderBook::bestAsk() const {
    return askCount > 0 ? asks[0].price : 0;
}

uint64_t OrderBook::spread() const {
    if (bidCount == 0 || askCount == 0) return 0;
    return bestAsk() - bestBid();
}

uint64_t OrderBook::midPrice() const {
    if (bidCount == 0 || askCount == 0) return 0;
    return (bestBid() + bestAsk()) / 2;
}

double OrderBook::vwap() const {
    uint64_t totalPriceQty = 0;
    uint64_t totalQty = 0;

    // Combine bids and asks into a single loop
    for (size_t i = 0; i < bidCount; i++) {
        totalPriceQty += bids[i].price * bids[i].quantity;
        totalQty += bids[i].quantity;
    }

    for (size_t i = 0; i < askCount; i++) {
        totalPriceQty += asks[i].price * asks[i].quantity;
        totalQty += asks[i].quantity;
    }

    // Return VWAP or 0.0 if no volume
    return totalQty > 0 ? static_cast<double>(totalPriceQty) / totalQty : 0.0;
}