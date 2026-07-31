#pragma once

#include <atomic>
#include <cstddef>

template<typename T, size_t N>
class RingBuffer {
    public:
        bool push(const T& item) {
            size_t currentHead = head.load(std::memory_order_relaxed);
            size_t nextHead = (currentHead + 1) % N;
            if (nextHead == tail.load(std::memory_order_acquire)) {
                drops++;
                return false;
            }
            buffer[currentHead] = item;
            head.store(nextHead,std::memory_order_release);
            return true;
        }

        bool pop(T& item) {
            size_t currentTail = tail.load(std::memory_order_relaxed);
            if (currentTail == head.load(std::memory_order_acquire)) {
                return false;
            }
            item = buffer[currentTail];
            tail.store((currentTail + 1) % N,std::memory_order_release);

            return true;
        }

        bool empty() const {
            return head.load() == tail.load();
        }

        size_t getDrops() const {
            return drops.load();
        }

    private:
        T buffer[N];
        alignas(64)
        std::atomic<size_t> head{0};
        alignas(64)
        std::atomic<size_t> tail{0};
        std::atomic<size_t> drops{0};
};