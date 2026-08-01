#pragma once

#include <pthread.h>
#include <sched.h>

inline void pinThread(int cpu){
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);
    CPU_SET(cpu,&cpuset);

    pthread_setaffinity_np(
        pthread_self(),
        sizeof(cpu_set_t),
        &cpuset
    );
}