#pragma once

#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "packet_pool.hpp"

#include <rte_mbuf.h>
#include <cstdint>

class DPDKReceiver {
    public:
        DPDKReceiver(
            RingBuffer<MarketPacket*, 65536>& rb,
            PacketPool<65536>& pool,
            uint16_t port

        );

        void receive();


    private:
        RingBuffer<MarketPacket*, 65536>& ringBuffer;
        PacketPool<65536>& pool;

        uint16_t portId;
        uint16_t queueId = 0;

        static constexpr uint16_t BURST_SIZE = 32;

        void processPacket(
            rte_mbuf* mbuf
        );
};