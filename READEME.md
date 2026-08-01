# Zero-Copy Market Data Parser

A high-performance market data ingestion engine built in modern C++20.

This project simulates a simplified low-latency trading infrastructure pipeline:

```
   UDP Market Data Feed
          |
          v
   Zero-Copy Decoder
          |
          v
   Lock-Free SPSC Queue
          |
          v
Order Book Engine
```

The goal is to explore performance-critical C++ concepts used in financial systems:

- zero-copy memory processing
- cache-friendly data structures
- lock-free communication
- memory pooling
- low-latency benchmarking


# Features

## Zero-Copy Packet Parser

Market packets are decoded directly from raw memory buffers without unnecessary copying.

Techniques used:

- packed memory layouts
- `reinterpret_cast`
- direct buffer parsing
- binary message decoding

Pipeline:

```
Raw UDP Buffer
       |
       v
 Packet Header
       |
       v
 Trade / Quote Message
```


## Packet Memory Pool

Custom packet allocator to avoid repeated heap allocations.

Features:

- preallocated packet storage
- reusable packet objects
- free-list ring buffer
- constant-time acquire/release

Example:

```cpp
auto* packet = pool.acquire();

process(packet);

pool.release(packet);
```

Benchmark:

```
BM_PacketPoolAcquireRelease

~1 ns per operation
```


## Lock-Free SPSC Ring Buffer

Single Producer Single Consumer queue for passing market events between pipeline stages.

Design:

- fixed-size circular buffer
- atomic synchronization
- no mutex locking
- cache-friendly memory layout

Benchmark:

```
BM_SPSCThroughput

Produced:
~80 million messages/sec

Consumed:
~80 million messages/sec
```


## Order Book Engine

Maintains bid and ask price levels.

Supported operations:

```cpp
addBid(price, quantity)
addAsk(price, quantity)

removeBid(price)
removeAsk(price)

bestBid()
bestAsk()
```

Implementation:

- contiguous memory using `std::array`
- sorted price levels
- binary search lookup using `std::lower_bound`
- cached best bid/ask prices


Example:

```
Bids

10100 x 50
10099 x 20
10098 x 10


Asks

10101 x 30
10102 x 40
10103 x 60
```


# Performance Benchmarks

Environment:

```
CPU:
18 cores @ 4.5GHz

Compiler:
GCC 13

Language:
C++20
```

Compiler optimizations:

```
-O3
-march=native
```


## Microbenchmarks

```
Benchmark                         Time
------------------------------------------------

RingBufferPushPop                 ~1 ns

PacketPoolAcquireRelease          ~1 ns

OrderBookAsk                      ~1.5 ns

OrderBookRandom                   ~7 ns

OrderBookDepth/10                 ~160 ns

OrderBookDepth/100                ~2.6 us

OrderBookDepth/1000               ~216 us
```


## Pipeline Throughput

```
SPSCThroughput

Produced:
~80M messages/sec

Consumed:
~80M messages/sec
```


# Testing

Unit tests are implemented using Catch2.

Run:

```bash
./build/unit_tests
```

Example output:

```
All tests passed
37 assertions in 8 test cases
```

Tests cover:

- packet decoding
- packet pool allocation
- ring buffer correctness
- order book operations


# Build Instructions

Requirements:

- C++20 compiler
- CMake >= 3.20
- Google Benchmark
- Catch2


Build:

```bash
mkdir build
cd build

cmake ..
cmake --build . -j
```


# Running

## Market Data Parser

```bash
./build/zero_copy_parser
```


## UDP Sender (Same UDP packet data for mainly latency/throughout testing)

```bash
./build/sender
```


## Unit Tests

```bash
./build/unit_tests
```


## Benchmarks

```bash
./build/benchmarks
```


# Project Structure (Main files)

```
.
├── include
│   ├── decoder.hpp
│   ├── packet_pool.hpp
│   ├── ring_buffer.hpp
│   ├── order_book.hpp
│   └── market_packet.hpp
│
├── src
│   ├── decoder.cpp
│   ├── parser.cpp
│   ├── udp_receiver.cpp
│   ├── order_book.cpp
│   └── main.cpp
│
├── benchmarks
│   ├── bench_ring_buffer.cpp
│   ├── bench_packet_pool.cpp
│   ├── bench_order_book.cpp
│   └── bench_pipeline.cpp
│
└── tests
    ├── test_decoder.cpp
    ├── test_packet_pool.cpp
    ├── test_ring_buffer.cpp
    └── test_order_book.cpp
```


# Future Improvements

Potential optimizations:

- price-indexed order book for O(1) lookup
- cache-line alignment improvements
- NUMA-aware memory allocation
- epoll-based networking
- DPDK kernel bypass networking
- latency percentile measurements (p50/p99/p99.9)
- hardware timestamping


# Learning Objectives

This project explores concepts used in:

- high-frequency trading systems
- exchange gateways
- market data feeds
- low-latency C++ infrastructure
- performance-critical applications