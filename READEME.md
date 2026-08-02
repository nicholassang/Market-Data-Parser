# Hybrid FPGA + C++ Low-Latency Market Data Parser

A high-performance market data ingestion engine built with modern C++20 and FPGA acceleration.

This project simulates a hybrid low-latency trading infrastructure pipeline:

```
   UDP Market Data Feed
          |
          v
   DPDK Kernel-Bypass Networking
          |
          v
   FPGA Packet Parser + Order Book
          |
          v
   Lock-Free SPSC Queue
          |
          v
   CPU Trading Logic
```

The goal is to explore performance-critical C++ and FPGA concepts used in financial systems:

- zero-copy memory processing
- cache-friendly data structures
- lock-free communication
- memory pooling
- deterministic hardware acceleration
- low-latency benchmarking

---

# Features

## Hybrid Architecture

The system combines FPGA acceleration with C++ software to achieve ultra-low latency:

- **FPGA**: Deterministic packet parsing and order book acceleration.
- **DPDK**: High-throughput kernel-bypass networking and NIC data movement.
- **CPU**: Trading strategies and higher-level application logic.

---

## FPGA Implementation

The FPGA implementation accelerates packet parsing and order book operations:

- **Packet Parsing**: Deterministic decoding of market data packets.
- **Order Book**: Hardware-accelerated price-level aggregation and updates.

### Verilator Benchmark Results

- **Packets Processed**: 1002
- **Cycles**: 1012
- **Packets/Cycle**: 0.990119
- **Throughput**: 247.5 million packets/sec @ 250MHz
- **Processing Latency**: 1 cycle (4 ns)

---

## C++ Implementation

The C++ pipeline handles trading logic and integrates with the FPGA for hardware acceleration.

### Benchmarks (Software)

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

#### Microbenchmarks

```
Benchmark                         Time
------------------------------------------------

PacketPoolAcquireRelease          ~1 ns

RingBufferPushPop                 ~1 ns

OrderBookAsk                      ~1.5 ns

OrderBookRandom                   ~7 ns

OrderBookDepth/10                 ~160 ns

OrderBookDepth/100                ~2.6 μs

OrderBookDepth/1000               ~216 μs
```

#### Pipeline Throughput

```
SPSCThroughput

Produced:
~80M messages/sec

Consumed:
~80M messages/sec
```

---

# Hardware/Software Architecture

### Overview

```
   UDP Feed
      |
      v
   DPDK RX
      |
      v
   FPGA Parser
      |
      v
   FPGA Order Book
      |
      v
   CPU Trading Logic
```

### FPGA Modules

1. **Packet Parser**:
   - Decodes market data packets.
   - Outputs structured messages to the order book.

2. **Order Book**:
   - Hardware-accelerated price-level aggregation.
   - Deterministic latency for updates and lookups.

3. **Simulation Flow**:
   - Verilator used for RTL simulation and benchmarking.
   - Deterministic latency verified with cycle-accurate results.

---

# Build Instructions

## Requirements

- **C++20 Compiler**: GCC 13 or Clang 16
- **CMake**: Version >= 3.20
- **Google Benchmark**: For performance testing
- **Catch2**: For unit testing
- **Verilator**: For FPGA simulation
- **DPDK**: For kernel-bypass networking

---

## Build

### Software

```bash
mkdir build
cd build

cmake ..
cmake --build . -j
```

### FPGA Simulation

```bash
cd fpga
make verilator
./simulator
```

---

# Running

## Market Data Parser

```bash
./build/zero_copy_parser
```

## UDP Sender

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

---

# Future Improvements

### Hardware

- PCIe FPGA deployment
- DMA streaming for high-throughput data movement
- FPGA-enabled NICs for direct packet processing
- Hardware timestamping for precise latency measurement
- Deeper order book acceleration for multi-level aggregation

### Software

- p50/p99/p99.9 latency analysis
- NUMA-aware memory allocation
- Optimized cache-line alignment
- Epoll-based networking for improved scalability

---

# Learning Objectives

This project explores concepts used in:

- High-frequency trading systems
- Exchange gateways
- Market data feeds
- Low-latency C++ infrastructure
- Deterministic FPGA acceleration
- Performance-critical applications