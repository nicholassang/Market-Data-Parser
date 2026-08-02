#include "dpdk_init.hpp"

#include <rte_eal.h>
#include <stdexcept>

int init_dpdk()
{
    static bool initialized = false;

    if (initialized)
        return 0;

    char* argv[] = {
        (char*)"app",
        (char*)"-l",
        (char*)"0",
        (char*)"--huge-dir=/dev/hugepages"
    };

    int argc = 4;

    int ret = rte_eal_init(argc, argv);

    if (ret < 0)
        throw std::runtime_error("DPDK EAL init failed");

    initialized = true;
    return ret;
}