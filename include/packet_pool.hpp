#pragma once

#include "market_packet.hpp"
#include <atomic>

template<size_t N>
class PacketPool {
    public:
        PacketPool() {
            for(size_t i=0;i<N;i++){
                freeList[i].store(true);
            }
        }
        MarketPacket* acquire(){
            for(size_t i=0;i<N;i++){
                bool expected=true;
                if(freeList[i].compare_exchange_strong(
                    expected,
                    false
                )){
                    return &packets[i];
                }
            }
            return nullptr;
        }

        void release(MarketPacket* packet){

            size_t index = packet - packets;

            freeList[index].store(true);

        }
    private:
        MarketPacket packets[N];
        std::atomic<bool> freeList[N];
};