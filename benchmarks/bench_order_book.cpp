#include <benchmark/benchmark.h>

#include "order_book.hpp"


static void BM_OrderBookInsert(
    benchmark::State& state)
{
    OrderBook book;


    for(auto _ : state)
    {
        book.addBid(
            10000,
            10
        );


        benchmark::ClobberMemory();
    }
}


static void BM_OrderBookAsk(
    benchmark::State& state)
{
    OrderBook book;


    for(auto _ : state)
    {
        book.addAsk(
            10001,
            10
        );
    }
}


BENCHMARK(BM_OrderBookInsert);
BENCHMARK(BM_OrderBookAsk);