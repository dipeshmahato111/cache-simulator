# Cache Simulator (CS3339 - Homework 3)

## Team Members
- Dipesh Kumar Mahato

##  Description
This project implements a cache simulator in C++. The simulator models cache behavior based on user-defined parameters and a sequence of memory references. For each memory access, the program reports whether it results in a **HIT** or **MISS**.

##  Assumptions
- Cache starts empty (all entries invalid)
- Each cache block contains exactly one word
- Memory references are given as word addresses
- Number of entries is a power of two
- Associativity divides the number of entries evenly
 
##Cache Design
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

##  Known Limitations
- Uses a simple replacement policy 
- Only supports single-word blocks
- Does not classify misspellings

