#include <benchmark/benchmark.h>

#include "ring_buffer.hpp"


static void BM_RingBufferPushPop(benchmark::State& state)
{
    RingBuffer<int,65536> rb;

    int value;

    for(auto _ : state)
    {
        benchmark::DoNotOptimize(rb.push(123));

        benchmark::DoNotOptimize(
            rb.pop(value)
        );
    }
}

BENCHMARK(BM_RingBufferPushPop);

BENCHMARK_MAIN();