# Parallel Array Maximum in C (POSIX Threads)

## Overview

Parallel computation of the maximum value of a large integer array using POSIX threads (pthreads) and mutex synchronization.

The array is partitioned across multiple threads. Each thread computes a local maximum and updates a shared global maximum using a mutex to ensure thread safety.

---

## Core Concepts

- POSIX Threads (pthreads)
- Multithreading in C
- Workload partitioning
- Mutex-based synchronization
- Shared memory protection
- Performance measurement

---

## Execution Flow

1. Generate an array of random integers.
2. Divide the array into equal segments.
3. Each thread computes a local maximum.
4. A mutex protects updates to the global maximum.
5. Execution time is recorded for performance comparison.

---

## Build & Run

bash
gcc src/main.c -pthread -o parallel_max
./parallel_max

Inputs:
- Array size (n)
- Number of threads (t)

Outputs:
- Execution time
- Maximum value


## Notes on Performance

Performance improves as thread count approaches available CPU cores.
Beyond that point, thread management and context switching introduce overhead.


## Environment

Tested on:
- macOS (clang)
- Linux (gcc)


## Author

Panagiotis Zois
MSc ICT | Bridging Business & Technology
