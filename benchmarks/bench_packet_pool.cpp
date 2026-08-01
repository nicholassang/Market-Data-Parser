#include <benchmark/benchmark.h>
#include <memory>

#include "packet_pool.hpp"


static void BM_PacketPoolAcquireRelease(
    benchmark::State& state)
{
    auto pool = std::make_unique<PacketPool<65536>>();

    for(auto _ : state)
    {
        auto* packet = pool->acquire();

        benchmark::DoNotOptimize(packet);

        if(packet)
            pool->release(packet);
    }
}

BENCHMARK(BM_PacketPoolAcquireRelease);