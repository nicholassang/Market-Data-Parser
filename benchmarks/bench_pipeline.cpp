#include <benchmark/benchmark.h>
#include "ring_buffer.hpp"

#include <thread>
#include <atomic>


static void BM_SPSCThroughput(
    benchmark::State& state)
{
    RingBuffer<int,65536> rb;

    std::atomic<bool> running{true};
    std::atomic<uint64_t> produced{0};
    std::atomic<uint64_t> consumed{0};


    std::thread producer([&](){

        while(running)
        {
            if(rb.push(1))
            {
                produced++;
            }
        }

    });


    std::thread consumer([&](){

        int x;

        while(running)
        {
            if(rb.pop(x))
            {
                consumed++;
            }
        }

    });


    for(auto _ : state)
    {
        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }


    running=false;


    producer.join();
    consumer.join();


    state.counters["Produced"] =
        benchmark::Counter(
            produced.load(),
            benchmark::Counter::kIsRate
        );


    state.counters["Consumed"] =
        benchmark::Counter(
            consumed.load(),
            benchmark::Counter::kIsRate
        );
}


BENCHMARK(BM_SPSCThroughput);