#pragma once

#include <mutex>
#include <cstddef>

template<typename T, size_t N>
class RingBuffer {
    public:
        bool push(const T&);
        bool pop(T&);
        bool empty() const;
        bool full() const;
        uint64_t dropped = 0;

    private:
        T buffer[N];
        size_t head = 0;
        size_t tail = 0;
        std::mutex mutex;
};

template<typename T, size_t N>
bool RingBuffer<T, N>::push(const T& item){
    // Prevent data race between receiver and parser
    std::lock_guard<std::mutex> lock(mutex);
    if (full()){
        dropped++;
        return false;
    }
    buffer[head] = item;
    head = (head + 1) % N;
    return true;
} 

template<typename T, size_t N>
bool RingBuffer<T, N>::pop(T& item){
    // Prevent data race between receiver and parser
    std::lock_guard<std::mutex> lock(mutex);
    if (empty()){
        return false;
    }

    item = buffer[tail];
    tail = (tail + 1) % N;
    return true;
} 

template<typename T, size_t N>
bool RingBuffer<T, N>::empty() const{
    return head == tail;
} 

template<typename T, size_t N>
bool RingBuffer<T, N>::full() const{
    return (head + 1) % N == tail;
} 