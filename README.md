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

# Key Design Concepts

The software pipeline was built around a set of low-latency engineering principles rather than algorithmic tricks alone. These concepts are what separate the microbenchmark numbers above from a naive implementation.

### Cache Efficiency

Memory access, not raw compute, is usually the bottleneck on modern CPUs. The pipeline favors:

- Contiguous memory layouts
- Minimizing allocations on the hot path
- Reducing unnecessary copies
- Cache-friendly data structures for the order book

### False Sharing

False sharing occurs when independent variables modified by different cores happen to sit on the same cache line, forcing unnecessary cache-coherence traffic. This was mitigated by:

- Careful memory layout of shared structures
- Separating frequently-modified variables (e.g. producer/consumer indices) onto distinct cache lines
- Explicit cache-line alignment where contention was measured

### CPU Affinity and Thread Scheduling

To reduce latency variance, pipeline threads are pinned to dedicated cores. This:

- Avoids unnecessary context switches
- Improves cache/TLB reuse
- Reduces jitter caused by OS scheduling

### Memory Management

General-purpose `new`/`delete` introduces unpredictable latency from allocator overhead and fragmentation. Instead, the pipeline uses a custom memory pool with:

- Preallocated packet storage
- Object reuse instead of repeated allocation
- Constant-time acquire/release (~1 ns, see benchmarks)

### Kernel-Bypass Networking (DPDK)

Traditional UDP receive paths go through the Linux kernel network stack, incurring overhead from interrupts, system calls, packet copying, and context switching. DPDK avoids this by giving the application direct, polled access to the NIC from user space via huge pages and preallocated packet buffers. This project's zero-copy decoder, packet pool, and lock-free queue design were built around the same principles, even where DPDK integration is still a work in progress (see Build Instructions).

---

# Design Comparisons

Rather than assuming each optimization would help, the impact of each design decision was measured against a simpler baseline:

| Decision | Baseline | Optimized | Result |
|---|---|---|---|
| Packet parsing | Copy into application buffers | Zero-copy, parse directly from raw buffer | Removed a memcpy and reduced cache pollution |
| Memory allocation | `new`/`delete` per packet | Preallocated memory pool | Constant-time (~1 ns) acquire/release, no fragmentation |
| Inter-thread communication | Mutex-guarded queue | Lock-free SPSC ring buffer | ~80M messages/sec, no lock contention |
| Networking | Kernel socket recv path | DPDK-style kernel bypass (planned) | Avoids syscall/interrupt overhead (see Future Improvements) |
| Processing model | Software-only pipeline | FPGA simulation prototype | Deterministic 1-cycle (4 ns) latency vs. variable software latency |

Individually, each change looks small. Together, removing copies, avoiding dynamic allocation, eliminating locks, and improving cache locality compound into materially better throughput and latency consistency - the same philosophy used in production HFT infrastructure.

---

# Design Choices

This section expands on the comparisons above, walking through each major decision, why it was chosen, and why the alternatives were rejected.

### Zero-Copy Packet Parsing

**Chosen:** Direct parsing from raw packet buffers using packed structures and memory reinterpretation.

**Why:**
- Avoids unnecessary `memcpy` operations and reduces memory bandwidth usage.
- Minimizes cache pollution by avoiding duplicate packet data.
- Provides lower and more predictable latency, which matters for market data systems.

**Why not traditional parsing with copies:**
- Copying every incoming packet introduces additional CPU work.
- Multiple copies between network buffers, application buffers, and processing layers increase latency.
- Less suitable for high-frequency message rates.

### Preallocated Packet Memory Pool

**Chosen:** Custom memory pool with reusable packet storage.

**Why:**
- Provides constant-time allocation and release.
- Avoids unpredictable heap allocator latency.
- Reduces memory fragmentation during continuous market data processing.

**Why not `new`/`delete` or heap allocation:**
- Dynamic allocation introduces allocator overhead.
- Latency can vary depending on heap state.
- Millions of market events per second make repeated allocations expensive.

### Lock-Free SPSC Ring Buffer

**Chosen:** Single Producer Single Consumer lock-free queue.

**Why:**
- Provides fast communication between pipeline stages without mutex contention.
- Uses atomic operations instead of blocking synchronization.
- Cache-friendly circular buffer design improves throughput.

**Why not mutex-based queues:**
- Locks introduce contention between producer and consumer threads.
- Thread scheduling and context switching create unpredictable latency.
- Lower throughput under high-frequency workloads.

**Why not multi-producer/multi-consumer queues:**
- Adds unnecessary synchronization complexity.
- The pipeline architecture naturally follows a single-producer, single-consumer model.
- A simpler design provides better performance for this use case.

### Array-Based Order Book Storage

**Chosen:** Array-based price-level storage for the order book (used in both the FPGA simulation and the C++ implementation).

**Why:**
- Provides direct O(1) access to price levels through indexing.
- Eliminates pointer chasing and hashing overhead.
- Uses contiguous memory, improving CPU cache locality.
- Gives predictable latency, which is important for high-frequency trading systems.
- Works well in markets with bounded and known price ranges.

A price update can access its level directly, with no search required:

```cpp
bids[price] = quantity;
asks[price] = quantity;
```

**Why not `std::map`:**

`std::map<uint32_t, uint64_t> bids;` provides O(log n) insertion, lookup, and deletion, but introduces overhead that an array avoids:

- Each node is separately allocated on the heap.
- Traversal requires following pointers between nodes.
- Poor cache locality due to scattered memory access.
- The tree structure performs unnecessary comparisons when the price can already be represented as an index.

A `std::map` lookup requires tree traversal:

```
Root
 |
 v
Node
 |
 v
Node
 |
 v
Price Level
```

while an array provides direct indexed access:

```
Price
 |
 v
Array Index
 |
 v
Price Level
```

For latency-sensitive systems processing millions of updates, avoiding pointer traversal provides a significant performance improvement.

**Why not `unordered_map`:**
- Average O(1) lookup, but worse cache behavior than a flat array.
- Hashing introduces additional computation.
- Performance can vary due to collisions and resizing.

**Trade-off:**
- Arrays require a known price range and may waste memory if the possible price space is very large.
- Maps are more flexible and suitable for markets with sparse or unpredictable price levels.

The array approach was chosen here because the goal was to explore low-latency, hardware-friendly designs - this mirrors techniques used in some exchange systems, where price levels are represented using indexed structures to achieve deterministic access times.

### Cache-Aware Data Layout

**Chosen:** Careful struct layout, compact memory representation, and awareness of cache-line behavior.

**Why:**
- Modern CPUs are heavily affected by memory access patterns.
- Keeping frequently accessed data together improves cache hits.
- Reduces unnecessary memory fetches.

**Why not ignore memory layout:**
- Two algorithms with identical Big-O complexity can have very different real-world performance.
- Cache misses can dominate execution time in low-latency systems.

### Avoiding False Sharing

**Chosen:** Consideration of cache-line alignment and independent memory regions for concurrently-accessed data.

**Why:**
- Prevents unnecessary cache invalidation between CPU cores.
- Improves throughput consistency when multiple threads operate concurrently.

**Why not rely only on atomic operations:**
- Atomics guarantee correctness but do not eliminate cache-coherence overhead.
- Poor memory placement can still significantly reduce throughput even when correctness is guaranteed.

### Benchmark-Driven Optimization

**Chosen:** Measure every major architectural decision instead of relying only on theoretical complexity.

**Why:**
- Real performance depends on CPU architecture, cache behavior, and workload patterns.
- Benchmarking reveals unexpected bottlenecks that Big-O analysis can't predict.

**Why not optimize purely based on Big-O analysis:**
- Constant factors dominate in high-performance systems.
- Memory access patterns and hardware behavior often matter more than asymptotic complexity.

### FPGA Hardware Pipeline Simulation

**Chosen:** SystemVerilog simulation using Verilator.

**Why:**
- Allows exploration of hardware acceleration concepts.
- Provides deterministic latency measurements.
- Demonstrates how packet processing can be implemented as a pipeline.

**Why not directly integrate FPGA hardware:**
- Requires physical FPGA hardware and networking interfaces.
- The project goal was to explore architecture and latency characteristics first.
- Simulation provides a controlled environment for evaluating design decisions.

### DPDK-Inspired Architecture

**Chosen:** Adopt principles similar to DPDK without direct integration.

**Why:**
- DPDK demonstrates how low-latency trading systems bypass traditional networking overhead.
- Concepts such as zero-copy buffers, memory pools, polling, and user-space packet processing align with this project's goals.

**Why not directly use DPDK:**
- The project focuses on understanding the underlying performance concepts rather than building a production network driver.
- Full DPDK integration requires specialized NIC configuration and hardware access.
- The current implementation isolates packet-processing performance without introducing networking complexity.

---

# Testing

The test suite is intended to validate correctness independently of the performance benchmarks. Coverage includes:

- Packet decoding correctness
- Packet memory pool allocation/reuse
- SPSC queue push/pop correctness and ordering
- Order book updates (`addBid`, `removeBid`, `bestBid`)
- Bid/ask price-level aggregation
- FPGA packet processing (via Verilator testbenches)

Run with:

```bash
./build/unit_tests
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
- Full DPDK integration for the UDP receive path, benchmarked against the current kernel-socket implementation

---

# Lessons Learned

- Data structures affect cache behavior as much as they affect algorithmic complexity
- Memory allocation strategy affects latency *consistency*, not just average latency
- Synchronization choice (locks vs. lock-free) has a direct throughput cost
- CPU architecture and scheduling matter as much as code-level optimization
- Benchmarking beats intuition - several assumed optimizations were only validated (or disproven) by measurement

---

# Learning Objectives

This project explores concepts used in:

- High-frequency trading systems
- Exchange gateways
- Market data feeds
- Low-latency C++ infrastructure
- Deterministic FPGA acceleration
- Performance-critical applications