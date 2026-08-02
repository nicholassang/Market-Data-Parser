#include <benchmark/benchmark.h>

#include "dpdk_init.hpp"
#include "dpdk_port.hpp"
#include "dpdk_receiver.hpp"
#include "ring_buffer.hpp"
#include "packet_pool.hpp"
#include "market_packet.hpp"

#include <rte_mbuf.h>
#include <rte_mempool.h>

#include <stdexcept>
#include <cstring>
#include <memory>


static rte_mempool* createPool()
{
    rte_mempool* pool =
        rte_pktmbuf_pool_create(
            "BENCH_POOL_UNIQUE",
            8192,
            250,
            0,
            RTE_MBUF_DEFAULT_BUF_SIZE,
            rte_socket_id()
        );

    return pool;
}


static void BM_DPDKPacketProcess(
    benchmark::State& state
)
{
    /*
        Initialize DPDK EAL once.
        EAL sets up hugepages, memory zones,
        and DPDK runtime environment.
    */
    init_dpdk();

    auto rb = std::make_unique<RingBuffer<rte_mbuf*,65536>>(); // rte_mbuf* to call dpdk functions directly


    rte_mempool* mbufPool =
        createPool();


    if(mbufPool == nullptr){
        throw std::runtime_error(
            "Failed to create mbuf pool"
        );
    }



    for(auto _ : state){

        rte_mbuf* mbuf =
            rte_pktmbuf_alloc(mbufPool);
    
    
        if(!mbuf)
            continue;
    
    
        mbuf->pkt_len = 64;
        mbuf->data_len = 64;
    
    
        if(!rb->push(mbuf)) {
            rte_pktmbuf_free(mbuf);
            continue;
        }
    
    
        rte_mbuf* consumed=nullptr;
    
        if(rb->pop(consumed)){
    
            uint8_t* data =
            rte_pktmbuf_mtod(
                consumed,
                uint8_t*
            );
        
            uint64_t price =
                *reinterpret_cast<uint64_t*>(data);
            
            benchmark::DoNotOptimize(price);
    
    
            rte_pktmbuf_free(consumed);
        }
    }



    /*
        Cleanup remaining packets
    */
    rte_mbuf* remaining = nullptr;

    while(rb->pop(remaining)){
        rte_pktmbuf_free(remaining);
    }


    rte_mempool_free(
        mbufPool
    );
}



BENCHMARK(
    BM_DPDKPacketProcess
);