#pragma once

#include <rte_mempool.h>
#include <cstdint>

class DPDKPort {
    public:
        DPDKPort( uint16_t portId = 0);
        ~DPDKPort();

        bool init();

        uint16_t getPortId() const {
            return portId;
        }

    private:
        uint16_t portId;

        rte_mempool* mbufPool = nullptr;

        static constexpr uint16_t RX_QUEUE = 0;
        static constexpr uint16_t RX_DESC = 1024;
};