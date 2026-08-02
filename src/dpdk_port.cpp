#include "dpdk_port.hpp"

#include <rte_ethdev.h>
#include <rte_mbuf.h>

#include <iostream>

DPDKPort::DPDKPort(uint16_t id) : portId(id){}

bool DPDKPort::init(){
    uint16_t count = rte_eth_dev_count_avail();

    if(count == 0){
        std::cerr << "No DPDK NIC found\n";
        return false;
    }
    if (portId >= count){
        std::cerr << "Invalid port id\n";
        return false;
    }

    // Create packet buffer pool
    mbufPool = rte_pktmbuf_pool_create(
            "MBUF_POOL",
            8192,
            256,
            0,
            RTE_MBUF_DEFAULT_BUF_SIZE,
            rte_socket_id()
        );
    if (mbufPool == nullptr){
        std::cerr << "mbuf pool creation failed\n";
        return false;
    }

    rte_eth_conf portConfig{};

    int ret = rte_eth_dev_configure(
            portId,
            1,          // RX queues
            0,          // TX queues
            &portConfig
        );
    if (ret < 0){
        std::cerr << "Port configure failed\n";
        return false;
    }
    ret = rte_eth_rx_queue_setup(
            portId,
            RX_QUEUE,
            RX_DESC,
            rte_eth_dev_socket_id(portId),
            nullptr,
            mbufPool
        );
    if (ret < 0){
        std::cerr << "RX queue setup failed\n";
        return false;
    }
    ret = rte_eth_dev_start(portId);
    if (ret < 0){
        std::cerr
            << "Port start failed\n";

        return false;
    }
    rte_eth_promiscuous_enable(portId);
    std::cout << "DPDK port started: " << portId << "\n";

    return true;
}

DPDKPort::~DPDKPort(){
    if (rte_eth_dev_is_valid_port(portId)) {
        rte_eth_dev_stop(portId);
    }
    if (mbufPool) {
        rte_mempool_free(mbufPool);
    }
}