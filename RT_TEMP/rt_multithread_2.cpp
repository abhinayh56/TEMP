#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

#define PERIOD_NS 1000000  // 1 ms

void real_time_task() {
    struct timespec next, now;
    clock_gettime(CLOCK_MONOTONIC, &next);

    while (true) {
        // Wait until the next period
        clock_gettime(CLOCK_MONOTONIC, &now);
        long jitter_ns = (now.tv_sec - next.tv_sec) * 1e9 + (now.tv_nsec - next.tv_nsec);
        
        // Print time jitter
        std::cout << "Jitter: " << jitter_ns << " ns" << std::endl;

        // Update next wake-up time
        next.tv_nsec += PERIOD_NS;
        if (next.tv_nsec >= 1000000000) {
            next.tv_nsec -= 1000000000;
            next.tv_sec++;
        }

        // Sleep until the next period
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
    }
}

int main() {
    std::thread rt_thread(real_time_task);
    rt_thread.join();
    return 0;
}
