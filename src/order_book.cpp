#include "order_book.hpp"

void OrderBook::addTrade(uint64_t price, uint32_t quantity){
    lastTradePrice = price;
    totalVolume += quantity;
}


void OrderBook::addBid(uint64_t price, uint32_t qty){
    auto it = std::lower_bound(bids.begin(), bids.begin() + bidCount,
        price,
        [](const PriceLevel& level, uint64_t p)
        {
            return level.price > p; // descending
        }
    );

    size_t pos = it - bids.begin();


    // existing level
    if(pos < bidCount && bids[pos].price == price)
    {
        bids[pos].quantity = qty;

        if(qty == 0)
            removeBid(price);

        return;
    }


    if(qty == 0 || bidCount == MAX_LEVELS)
        return;


    // shift right
    for(size_t i = bidCount; i > pos; i--)
        bids[i] = bids[i-1];


    bids[pos] = {price, qty};
    bidCount++;


    if(price > bestBidPrice)
        bestBidPrice = price;
}

void OrderBook::addAsk(uint64_t price, uint32_t qty){
    auto it = std::lower_bound(
        asks.begin(),
        asks.begin() + askCount,
        price,
        [](const PriceLevel& level, uint64_t p)
        {
            return level.price < p; // ascending
        }
    );

    size_t pos = it - asks.begin();


    // existing level
    if(pos < askCount && asks[pos].price == price)
    {
        asks[pos].quantity = qty;

        if(qty == 0)
            removeAsk(price);

        return;
    }


    if(qty == 0 || askCount == MAX_LEVELS)
        return;


    // shift right
    for(size_t i = askCount; i > pos; i--)
        asks[i] = asks[i-1];


    asks[pos] = {price, qty};
    askCount++;


    if(bestAskPrice == 0 || price < bestAskPrice)
        bestAskPrice = price;
}

void OrderBook::removeBid(uint64_t price){
    auto it = std::lower_bound(
        bids.begin(),
        bids.begin() + bidCount,
        price,
        [](const PriceLevel& level, uint64_t p)
        {
            return level.price > p;
        }
    );

    size_t pos = it - bids.begin();


    if(pos >= bidCount || bids[pos].price != price)
        return;


    for(size_t i = pos + 1; i < bidCount; i++)
        bids[i-1] = bids[i];


    bidCount--;


    if(bidCount > 0)
        bestBidPrice = bids[0].price;
    else
        bestBidPrice = 0;
}

void OrderBook::removeAsk(uint64_t price){
    auto it = std::lower_bound(
        asks.begin(),
        asks.begin() + askCount,
        price,
        [](const PriceLevel& level, uint64_t p)
        {
            return level.price < p;
        }
    );

    size_t pos = it - asks.begin();

    if(pos >= askCount || asks[pos].price != price)
        return;

    for(size_t i = pos + 1; i < askCount; i++)
        asks[i-1] = asks[i];

    askCount--;

    if(askCount > 0)
        bestAskPrice = asks[0].price;
    else
        bestAskPrice = 0;
}

uint64_t OrderBook::bestBid() const{
    return bestBidPrice;
}


uint64_t OrderBook::bestAsk() const{
    return bestAskPrice;
}