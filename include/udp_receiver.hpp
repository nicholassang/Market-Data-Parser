#pragma once

#include "ring_buffer.hpp"
#include "market_packet.hpp"
#include "packet_pool.hpp"

class UDPReceiver {
    public: 
        UDPReceiver(int port, RingBuffer<MarketPacket*, 65536>& rb, PacketPool<65536>& p);
        ~UDPReceiver();

        void receive();
    private:
        int sockfd;
        RingBuffer<MarketPacket*, 65536>& ringBuffer;
        PacketPool<65536>& pool;
};