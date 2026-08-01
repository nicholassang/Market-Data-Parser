#include <benchmark/benchmark.h>

#include "ring_buffer.hpp"


static void BM_RingBufferPushPop(benchmark::State& state)
{
    RingBuffer<int,65536> rb;

    int value = 0;   // initialize

    for(auto _ : state)
    {
        bool pushed = rb.push(123);

        benchmark::DoNotOptimize(pushed);

        bool popped = rb.pop(value);

        benchmark::DoNotOptimize(popped);
        benchmark::DoNotOptimize(value);
    }
}


BENCHMARK(BM_RingBufferPushPop);