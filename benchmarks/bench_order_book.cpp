#include <benchmark/benchmark.h>

#include "order_book.hpp"

static void BM_OrderBookInsert(
    benchmark::State& state)
{
    for(auto _ : state)
    {
        OrderBook book;

        for(int i = 0; i < 1000; i++)
        {
            book.addBid(
                10000 + i,
                10
            );
        }

        benchmark::DoNotOptimize(book);
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
        benchmark::DoNotOptimize(book);
        benchmark::ClobberMemory();
    }
}

static void BM_OrderBookRandom(
    benchmark::State& state)
{
    OrderBook book;

    uint64_t price = 10000;

    for(auto _ : state)
    {
        price++;

        book.addBid(
            price,
            10
        );

        benchmark::DoNotOptimize(price);
        benchmark::DoNotOptimize(book);
    }
}

static void BM_OrderBookDepth(
    benchmark::State& state)
{
    int depth = state.range(0);

    for(auto _ : state)
    {
        OrderBook book;

        for(int i=0;i<depth;i++)
        {
            book.addBid(
                10000+i,
                10
            );
        }

        benchmark::DoNotOptimize(book);
    }
}

BENCHMARK(BM_OrderBookInsert);
BENCHMARK(BM_OrderBookAsk);
BENCHMARK(BM_OrderBookRandom);
BENCHMARK(BM_OrderBookDepth)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000);