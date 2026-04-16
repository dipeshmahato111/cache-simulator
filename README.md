# Cache Simulator (CS3339 - Homework 3)

## Team Member
- Dipesh Kumar Mahato

##  Description
This project implements a cache simulator in C++. The simulator models cache behavior based on user-defined parameters and a sequence of memory references. For each memory access, the program reports whether it results in a **HIT** or **MISS**.

##  Assumptions
- Cache starts empty (all entries invalid)
- Each cache block contains exactly one word
- Memory references are given as word addresses
- Number of entries is a power of two
- Associativity divides the number of entries evenly
 
## Cache Design
- Number of sets:

num_sets = num_entries / associativity

- Address mapping:
- **Index** = address % num_sets
- **Tag** = address / num_sets

- Replacement Policy:
- Simple replacement (first available, otherwise replace first entry)

##  Input Format
The program is executed using:

./cache_sim num_entries associativity memory_reference_file


### Example:

./cache_sim 4 2 input.txt

The input file contains space-separated integers

1 3 5 1 3 1

---

##  Output Format
The output is written to a file named:

cache_sim_output

Each line follows this format:

ADDRESS: HIT/MISS


### Example Output:

1 : MISS
3 : MISS
5 : MISS
1 : MISS
3 : MISS
1 : HIT

##  Compilation & Execution

Compile:

g++ cache_sim.cpp -o cache_sim

### Run:

./cache_sim 4 2 input.txt


### 1. Multi-Word Blocks
In a multi-word block cache, each cache line stores multiple consecutive memory addresses instead of a single word. This would require:
- Adding a block size parameter
- Modifying index and tag calculations to include block offset bits
- Checking if an address falls within a block range

This improves spatial locality by allowing nearby memory accesses to result in cache hits.

---

### 2. Multi-Level Cache (L1 and L2)
A multi-level cache system includes multiple cache layers:
- L1 (small, fast cache)
- L2 (larger, slower cache)

On a memory access:
- Check L1 first
- If MISS → check L2
- If MISS in both → fetch from main memory

This reduces average memory access time and improves performance.

---

### 3. Miss Classification
Cache misses can be classified into three types:

- **Compulsory Miss**: First-time access to a memory block (cold start)
- **Capacity Miss**: Cache is too small to hold all needed data
- **Conflict Miss**: Multiple addresses map to the same cache set

To implement this, the simulator would need to:
- Track previously accessed addresses
- Simulate a fully associative cache for comparison
- Analyze replacement behavior

---
