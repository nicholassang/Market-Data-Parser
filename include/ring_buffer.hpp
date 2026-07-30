#include <cstddef>

#pragma once

template<typename T, size_t N>
class RingBuffer {
    public:
        bool push(const T&);
        bool pop(T&);
        bool empty() const;
        bool full() const;

    private:
        T buffer[N];
        size_t head = 0;
        size_t tail = 0;
};

template<typename T, size_t N>
bool RingBuffer<T, N>::push(const T& item){
    if (full()){
        return false;
    }
    buffer[head] = item;
    head = (head + 1) % N;
    return true;
} 

template<typename T, size_t N>
bool RingBuffer<T, N>::pop(T& item){
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