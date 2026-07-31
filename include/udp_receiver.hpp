#pragma once

#include "ring_buffer.hpp"
#include "market_packet.hpp"
#include "packet_pool.hpp"

class UDPReceiver {
    public: 
        UDPReceiver(int port, RingBuffer<MarketPacket*, 1024>& rb, PacketPool<1024>& p);
        ~UDPReceiver();

        void receive();
    private:
        int sockfd;
        RingBuffer<MarketPacket*, 1024>& ringBuffer;
        PacketPool<1024>& pool;
};