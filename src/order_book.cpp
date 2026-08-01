#include "order_book.hpp"

void OrderBook::addTrade(uint64_t price, uint32_t quantity) {
    lastTradePrice = price;
    totalVolume += quantity;
}

void OrderBook::addBid(uint64_t price, uint32_t qty)
{
    // update existing level
    for(size_t i=0;i<bidCount;i++)
    {
        if(bids[i].price == price)
        {
            bids[i].quantity = qty;

            if(qty == 0)
                removeBid(price);

            return;
        }
    }

    if(qty == 0 || bidCount == MAX_LEVELS)
        return;

    size_t pos = bidCount;

    while(pos > 0 && bids[pos-1].price < price)
    {
        bids[pos] = bids[pos-1];
        pos--;
    }

    bids[pos] = {price, qty};
    bidCount++;
}

void OrderBook::addAsk(uint64_t price, uint32_t qty)
{
    for(size_t i=0;i<askCount;i++)
    {
        if(asks[i].price == price)
        {
            asks[i].quantity = qty;

            if(qty == 0)
                removeAsk(price);

            return;
        }
    }

    if(qty == 0 || askCount == MAX_LEVELS)
        return;

    size_t pos = askCount;

    while(pos > 0 && asks[pos-1].price > price)
    {
        asks[pos] = asks[pos-1];
        pos--;
    }

    asks[pos] = {price, qty};
    askCount++;
}

void OrderBook::removeBid(uint64_t price)
{
    for(size_t i=0;i<bidCount;i++)
    {
        if(bids[i].price == price)
        {
            for(size_t j=i+1;j<bidCount;j++)
                bids[j-1] = bids[j];

            bidCount--;
            return;
        }
    }
}

void OrderBook::removeAsk(uint64_t price)
{
    for(size_t i=0;i<askCount;i++)
    {
        if(asks[i].price == price)
        {
            for(size_t j=i+1;j<askCount;j++)
                asks[j-1] = asks[j];

            askCount--;
            return;
        }
    }
}

uint64_t OrderBook::bestBid() const
{
    if(bidCount == 0)
        return 0;

    return bids[0].price;
}

uint64_t OrderBook::bestAsk() const
{
    if(askCount == 0)
        return 0;

    return asks[0].price;
}