#pragma once

#include "ring_buffer.hpp"
#include "market_packet.hpp"

class UDPReceiver {
    public: 
        UDPReceiver(
            int port,
            RingBuffer<MarketPacket, 1024>& rb
        );
        ~UDPReceiver();

        void receive();
    private:
        int sockfd;
        RingBuffer<MarketPacket, 1024>& ringBuffer;

};