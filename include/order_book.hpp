#pragma once

#include <map>

class OrderBook{
    public:
        void addTrade(uint64_t price, int quantity){
            trades[price] += quantity;
        }
        void addBid(uint64_t price, int size){
            bids[price]+=size;
        }

        void addAsk(uint64_t price, int size){
            asks[price]+=size;
        }

        uint64_t bestBid(){
            return bids.rbegin()->first;
        }

        uint64_t bestAsk(){
            return asks.begin()->first;
        }

    private:
        std::map<uint64_t,int> bids;
        std::map<uint64_t,int> asks;
        std::map<uint64_t,int> trades;
};