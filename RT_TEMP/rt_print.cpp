#include <iostream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <sched.h>
#include <pthread.h>
#include <unistd.h>

#define INTERVAL_MS 100  // Interval in milliseconds

void set_realtime_priority() {
    struct sched_param param;
    param.sched_priority = 80;  // Set high priority (1-99)
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        std::cerr << "Failed to set real-time scheduler: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Real-time scheduler set with priority " << param.sched_priority << std::endl;
    }
}

void wait_interval(struct timespec *next_time) {
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, next_time, NULL);
    next_time->tv_nsec += INTERVAL_MS * 1000000;
    if (next_time->tv_nsec >= 1000000000) {
        next_time->tv_sec += 1;
        next_time->tv_nsec -= 1000000000;
    }
}

int main() {
    set_realtime_priority();

    struct timespec next_time;
    clock_gettime(CLOCK_MONOTONIC, &next_time);  // Get current time

    while (true) {
        std::cout << "Real-time task running..." << std::endl;
        wait_interval(&next_time);  // Wait for the next interval
    }

    return 0;
}
