#pragma once
#include <atomic>

struct Runtime {
    static inline std::atomic<bool> running{true};
};