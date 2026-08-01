#pragma once

#include "market_packet.hpp"
#include <atomic>
#include <cassert>

template<size_t N>
class FreeRing {
public:

    FreeRing()
        : head(0),
          tail(0)
    {}

    bool push(size_t index)
    {
        size_t currentTail = tail.load(std::memory_order_relaxed);

        size_t nextTail = (currentTail + 1) % N;

        if(nextTail == head.load(std::memory_order_acquire))
            return false;

        buffer[currentTail] = index;

        tail.store(
            nextTail,
            std::memory_order_release
        );

        return true;
    }


    bool pop(size_t& index)
    {
        size_t currentHead = head.load(std::memory_order_relaxed);

        if(currentHead == tail.load(std::memory_order_acquire))
            return false;

        index = buffer[currentHead];

        head.store(
            (currentHead + 1) % N,
            std::memory_order_release
        );

        return true;
    }


private:

    size_t buffer[N];

    alignas(64)
    std::atomic<size_t> head;

    alignas(64)
    std::atomic<size_t> tail;
};


template<size_t N>
class PacketPool {

public:

    PacketPool()
    {
        for(size_t i = 0; i < N; i++)
            freeRing.push(i);
    }


    MarketPacket* acquire()
    {
        size_t index;

        if(!freeRing.pop(index))
            return nullptr;

        return &packets[index];
    }


    void release(MarketPacket* packet){
        if(packet == nullptr)
            return;
    
        size_t index = packet - packets;
    
        assert(index < N);
    
        freeRing.push(index);
    }


private:

    alignas(64)
    MarketPacket packets[N];

    FreeRing<N> freeRing;
};