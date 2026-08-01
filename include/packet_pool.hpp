#pragma once

#include "market_packet.hpp"
#include <atomic>

template<size_t N>
class FreeRing {
    public:
        bool push(size_t index){
            size_t currentTail = tail.load(std::memory_order_relaxed);
            size_t nextTail = (currentTail + 1) % N;
            if(nextTail == head.load(std::memory_order_acquire)){
                return false; // full
            }
            buffer[currentTail] = index;
            tail.store(nextTail, std::memory_order_release);
            return true;
        }

        bool pop(size_t& index){
            size_t currentHead = head.load(std::memory_order_relaxed);
            if(currentHead == tail.load(std::memory_order_acquire)){
                return false; // empty
            }
            index = buffer[currentHead];
            head.store(
                (currentHead + 1) % N,
                std::memory_order_release
            );
            return true;
        }

    private:
        size_t buffer[N];
        std::atomic<size_t> head{0};
        std::atomic<size_t> tail{0};
};

template<size_t N>
class PacketPool {
    public:
        PacketPool() {
            for (size_t i = 0; i < N; i++){
                freeRing.push(i);
            }
        }
        MarketPacket* acquire(){
            size_t index;
            if (!freeRing.pop(index)){
                return nullptr;
            }
            return &packets[index];
        }

        void release(MarketPacket* packet){
            size_t index = packet - packets;
            freeRing.push(index);
        }
    private:
        MarketPacket packets[N];
        FreeRing<N> freeRing;
};