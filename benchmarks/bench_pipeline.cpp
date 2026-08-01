#include <benchmark/benchmark.h>

#include "ring_buffer.hpp"

#include <thread>
#include <atomic>


static void BM_SPSCThroughput(
    benchmark::State& state)
{
    RingBuffer<int,65536> rb;

    std::atomic<bool> running=true;


    std::thread producer([&](){

        while(running)
        {
            rb.push(1);
        }

    });


    std::thread consumer([&](){

        int x;

        while(running)
        {
            rb.pop(x);
        }

    });


    for(auto _ : state)
    {
        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }


    running=false;

    state.counters["Throughput"] =
    benchmark::Counter(
        state.iterations(),
        benchmark::Counter::kIsRate
    );

    producer.join();
    consumer.join();
}


BENCHMARK(BM_SPSCThroughput);