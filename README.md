# Parallel Array Maximum in C (POSIX Threads)

## Overview

This project demonstrates parallel computation in C using POSIX threads (pthreads) to calculate the maximum value of a large integer array. The workload is evenly distributed across multiple threads, and synchronization is achieved using a mutex to safely update a shared global maximum variable.

The goal is to illustrate practical thread coordination, shared memory protection, and performance scaling behavior.

---

## Problem Statement

Given a large array of randomly generated integers, compute the maximum value using multiple threads while ensuring:

- Safe access to shared memory
- Proper synchronization
- Efficient workload partitioning
- Measurable performance comparison

---

## Key Concepts Demonstrated

- POSIX Threads (pthreads)
- Multithreading in C
- Workload partitioning
- Mutex-based synchronization
- Shared memory protection
- Thread-safe global state updates
- Performance benchmarking
- Scalability vs context-switching overhead

---

## How It Works

1. The program generates an array of random integers.
2. The array is divided evenly among `t` threads.
3. Each thread computes a local maximum for its assigned segment.
4. A mutex is used to safely compare and update the global maximum.
5. Execution time is measured to evaluate performance scaling.

---

## Compilation & Execution

```bash
gcc src/main.c -pthread -o parallel_max
./parallel_max

You will be prompted to enter:
	•	Array size (n)
	•	Number of threads (t)

The program outputs:
	•	Execution time
	•	Maximum value found

⸻

Performance Observations

Empirical testing shows:
	•	Significant performance improvement when increasing threads up to the number of available CPU cores.
	•	Diminishing returns or slight performance degradation when exceeding core count due to thread management overhead and context switching.

This highlights the trade-off between parallelism and synchronization cost.

⸻

Technical Skills Showcased
	•	Systems programming in C
	•	Concurrency design
	•	Mutex synchronization patterns
	•	Parallel workload design
	•	Performance analysis mindset

⸻

Build Environment

Tested on:
	•	macOS (clang)
	•	Linux (gcc)

⸻

Author

Panagiotis Zois
MSc ICT | Business-to-Technology Professional
Focused on bridging system-level engineering with real-world business applications.
