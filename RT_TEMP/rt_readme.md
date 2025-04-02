# rt_print.cpp

Compile
```
g++ -o rt_print rt_print.cpp -pthread
```

Execute
```
sudo ./rt_print
```

# rt_multithread.cpp

Compile
```
g++ -o rt_multithread rt_multithread.cpp -pthread
```

Execute
```
sudo ./rt_multithread
```

Check thread priority with:
```
ps -eo pid,comm,pri,policy | grep rt_multithread
```

Observe real-time execution using
```
chrt -p $(pgrep rt_multithread)
```

The cyclictest tool is used to measure the latency of real-time threads.
Install rt-tests

sudo apt install rt-tests

Run cyclictest

sudo cyclictest -m -n -a 1 -q -p 90 -i 1000

📌 Explanation:

    -m: Lock memory (avoid page faults).

    -n: Use high-precision clock_nanosleep().

    -a 1: Bind to CPU core 1.

    -q: Quiet mode.

    -p 90: Priority 90.

    -i 1000: Interval 1000 µs (1 ms).

👉 Expected Output:

# Min Latency: 5 µs
# Avg Latency: 7 µs
# Max Latency: 15 µs