# Hybrid FPGA + C++ Low-Latency Market Data Parser

This project consists of two complementary components:

1. **C++20 Zero-Copy Market Data Processing Engine**: A production-style software pipeline for low-latency market data processing.
2. **SystemVerilog FPGA Simulation Prototype**: A hardware exploration of market data processing concepts using Verilator.

The goal is to demonstrate low-latency software engineering concepts in C++ and explore how FPGA hardware acceleration could complement future high-frequency trading infrastructure.

---

# Features

## C++20 Market Data Processing Engine

The C++ implementation is a high-performance, production-style pipeline designed for low-latency market data processing. It includes:

- **Zero-Copy Architecture**: Efficient memory handling for high-throughput processing.
- **Lock-Free Communication**: SPSC ring buffer for inter-thread communication.
- **Order Book Reconstruction**: Level 2 order book with price-level aggregation.
- **Latency Measurement**: Tools for analyzing p50/p99/p99.9 latencies.

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

## FPGA Simulation Prototype

The FPGA simulation is a hardware exploration of market data processing concepts. It is implemented in SystemVerilog and simulated using Verilator. The FPGA prototype is **not integrated** into the C++ pipeline but serves as a proof-of-concept for potential hardware acceleration.

### FPGA Implementation

The FPGA simulation includes:

- **Packet Parsing**: Deterministic decoding of market data packets.
- **Bid/Ask Tracking**: Hardware-accelerated price-level aggregation.
- **Best Price Calculation**: Efficient computation of best bid/ask prices.

### Verilator Benchmark Results

- **Packets Processed**: 1002
- **Cycles**: 1012
- **Packets/Cycle**: 0.990119
- **Throughput**: 247.5 million packets/sec @ 250MHz
- **Processing Latency**: 1 cycle (4 ns)

### Purpose

The FPGA simulation explores how hardware acceleration could complement the software pipeline in future high-frequency trading systems. It demonstrates deterministic latency and high throughput for market data processing.

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
   C++ Market Data Parser
      |
      v
   CPU Trading Logic
```

### FPGA Simulation Flow

```
   Verilator Simulation
      |
      v
   Packet Parser
      |
      v
   Bid/Ask Tracking
      |
      v
   Best Price Calculation
```

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