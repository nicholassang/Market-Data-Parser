#pragma once

#include <atomic>
#include <cstddef>

// Prevent CPU false sharing differing cache lines
struct alignas(64) CacheAlignedAtomic{
    std::atomic<size_t> value{0};

    size_t load(std::memory_order order = std::memory_order_seq_cst) const {
        return value.load(order);
    }

    void store(size_t v, std::memory_order order = std::memory_order_seq_cst){
        value.store(v, order);
    }
};