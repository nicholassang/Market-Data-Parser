#include "dpdk_receiver.hpp"

#include <rte_ethdev.h>
#include <rte_mbuf.h>

#include <iostream>
#include <cstring>


DPDKReceiver::DPDKReceiver(RingBuffer<MarketPacket*,65536>& rb, PacketPool<65536>& p, uint16_t port): ringBuffer(rb), pool(p), portId(port){
    std::cout << "DPDK Receiver created\n";
}

void DPDKReceiver::receive(){
    rte_mbuf* packets[BURST_SIZE];
    while(true){
        uint16_t received =
            rte_eth_rx_burst( // aspect of kernel-bypass
                portId,
                queueId,
                packets,
                BURST_SIZE
            );
        if(received == 0){
            continue;
        }
        for(uint16_t i = 0; i < received; i++){
            processPacket(
                packets[i]
            );
            rte_pktmbuf_free(
                packets[i]
            );
        }
    }
}

void DPDKReceiver::processPacket(rte_mbuf* mbuf){
    MarketPacket* packet = pool.acquire();

    if(packet == nullptr){
        return;
    }
    uint16_t length =
        rte_pktmbuf_pkt_len(
            mbuf
        );
    char* data =
        rte_pktmbuf_mtod(
            mbuf,
            char*
        );
    if(length > sizeof(packet->data)){
        pool.release(packet);
        return;
    }

    /*
       Temporary copy.

       Later:
       make MarketPacket point directly
       to mbuf memory for true zero-copy.
    */
    memcpy(
        packet->data,
        data,
        length
    );
    packet->length = length;
    if(!ringBuffer.push(packet)){
        pool.release(packet);
    }
}