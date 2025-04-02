#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <ctime>
#include <cstring>

#define THREAD1_INTERVAL_MS 100  // 100 ms interval
#define THREAD2_INTERVAL_MS 200  // 200 ms interval

void wait_interval(struct timespec *next_time, int interval_ms) {
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, next_time, NULL);
    next_time->tv_nsec += interval_ms * 1000000;
    if (next_time->tv_nsec >= 1000000000) {
        next_time->tv_sec += 1;
        next_time->tv_nsec -= 1000000000;
    }
}

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    int interval_ms = (thread_id == 1) ? THREAD1_INTERVAL_MS : THREAD2_INTERVAL_MS;

    struct timespec next_time;
    clock_gettime(CLOCK_MONOTONIC, &next_time);

    while (true) {
        std::cout << "Thread " << thread_id << " running..." << std::endl;
        wait_interval(&next_time, interval_ms);
    }
    return NULL;
}

void set_thread_priority(pthread_t thread, int priority) {
    struct sched_param param;
    param.sched_priority = priority;
    if (pthread_setschedparam(thread, SCHED_FIFO, &param) != 0) {
        std::cerr << "Failed to set thread priority: " << strerror(errno) << std::endl;
    }
}

// int main() {
//     pthread_t thread1, thread2;
//     int id1 = 1, id2 = 2;

//     pthread_attr_t attr1, attr2;
//     pthread_attr_init(&attr1);
//     pthread_attr_init(&attr2);

//     pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
//     pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);

//     struct sched_param param1, param2;
//     param1.sched_priority = 80;  // High priority
//     param2.sched_priority = 70;  // Lower priority

//     pthread_attr_setschedparam(&attr1, &param1);
//     pthread_attr_setschedparam(&attr2, &param2);

//     pthread_create(&thread1, &attr1, thread_function, &id1);
//     pthread_create(&thread2, &attr2, thread_function, &id2);

//     set_thread_priority(thread1, 80);
//     set_thread_priority(thread2, 70);

//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     return 0;
// }


int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    struct sched_param main_param;
    main_param.sched_priority = 90; // Highest priority
    if (sched_setscheduler(0, SCHED_FIFO, &main_param) < 0) {
        std::cerr << "Failed to set main thread priority: " << strerror(errno) << std::endl;
    }

    pthread_create(&thread1, NULL, thread_function, &id1);
    pthread_create(&thread2, NULL, thread_function, &id2);

    set_thread_priority(thread1, 80);
    set_thread_priority(thread2, 70);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
