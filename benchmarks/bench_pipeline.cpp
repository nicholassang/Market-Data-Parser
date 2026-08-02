#include <benchmark/benchmark.h>
#include "ring_buffer.hpp"

#include <thread>
#include <atomic>
#include <chrono>


static void BM_SPSCThroughput(benchmark::State& state){
    RingBuffer<int,65536> rb;

    std::atomic<bool> running{true};
    std::atomic<uint64_t> produced{0};
    std::atomic<uint64_t> consumed{0};

    std::thread producer([&](){
        while (running) {
            if (rb.push(1)) {
                produced.fetch_add(1, std::memory_order_relaxed);
            }
        }
    });

    std::thread consumer([&](){
        int x;
        while (running) {
            if (rb.pop(x)) {
                consumed.fetch_add(1, std::memory_order_relaxed);
            }
        }

    });

    for (auto _ : state) {
        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }

    running=false;

    producer.join();
    consumer.join();

    state.counters["Throughput"] = static_cast<double>(consumed.load());

    state.counters["Produced"] = static_cast<double>(produced.load());

    state.counters["Consumed"] = static_cast<double>(consumed.load());
}

BENCHMARK(BM_SPSCThroughput);