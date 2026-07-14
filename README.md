# Intelligent Search Engine with Autocomplete & Fuzzy Query Processing

A modular C++ search engine implementing **Trie-based indexing**, **Top-K autocomplete**, and **fuzzy query processing** using **Levenshtein distance**. The project focuses on efficient search, algorithmic optimization, and performance benchmarking over a **370K+ word English dictionary**.

---

## Features

- Exact word search using a Trie
- Prefix-based autocomplete
- Dynamic frequency-based ranking
- Top-K autocomplete using a bounded min-heap
- Fuzzy query processing using Levenshtein distance
- Candidate filtering for efficient spell correction
- Benchmarking framework for performance evaluation
- Modular object-oriented C++ design

---

## Project Structure

```
Intelligent-Search-Engine/
│
├── benchmark/
├── data/
│   ├── sample_words.txt
│   └── words_alpha.txt
├── docs/
├── include/
│   ├── Trie.h
│   ├── DictionaryLoader.h
│   ├── SearchEngine.h
│   └── SpellCorrector.h
├── src/
│   ├── Trie.cpp
│   ├── DictionaryLoader.cpp
│   ├── SearchEngine.cpp
│   ├── SpellCorrector.cpp
│   ├── benchmark.cpp
│   └── main.cpp
├── tests/
└── README.md
```

---

# Architecture

```
                    +------------------+
                    |      main.cpp    |
                    +--------+---------+
                             |
                             |
                    +--------v---------+
                    |   SearchEngine   |
                    +----+--------+----+
                         |        |
              +----------+        +--------------+
              |                                |
      +-------v-------+                +--------v---------+
      |     Trie      |                | SpellCorrector   |
      +-------+-------+                +--------+---------+
              |                                 |
              |                                 |
      Prefix Search                     Levenshtein Distance
      Exact Search                      Candidate Filtering
      Top-K Autocomplete
```

---

# Components

### Trie

- Exact word search
- Prefix search
- Frequency tracking
- DFS-based autocomplete
- Heap-based Top-K autocomplete

---

### SpellCorrector

- Levenshtein edit distance
- Two-row dynamic programming optimization
- Prefix and length-based candidate filtering
- Partial sorting for Top-K suggestions

---

### DictionaryLoader

- Loads words into the Trie
- Builds spell correction dictionary

---

### SearchEngine

Acts as the interface between the application and the underlying modules.

---

# Algorithms Used

| Feature | Algorithm |
|----------|-----------|
| Exact Search | Trie |
| Prefix Search | Trie |
| Autocomplete | DFS |
| Top-K Ranking | Bounded Min-Heap |
| Spell Correction | Levenshtein Distance |
| Candidate Selection | Prefix & Length Filtering |

---

# Time Complexity

| Operation | Complexity |
|------------|-----------|
| Insert | O(L) |
| Exact Search | O(L) |
| Prefix Search | O(L) |
| Autocomplete (DFS + Sort) | O(M log M) |
| Heap Autocomplete | O(M log K) |
| Spell Correction | O(C × L²) (after candidate filtering) |

Where

- **L** = word length
- **M** = number of words matching the prefix
- **K** = requested number of suggestions
- **C** = filtered candidate set size

---

# Performance Benchmarks

## Exact Search

Dictionary Size: **370,105 words**

| Queries | Trie (µs) | Linear (µs) | Speedup |
|----------|----------:|------------:|---------:|
| 100 | 0.0 | 45,725 | ∞ |
| 1,000 | 0.0 | 425,477 | ∞ |
| 5,000 | 400 | 2,186,689 | 5466× |
| 10,000 | 802 | 6,020,814 | 7511× |
| 20,000 | 1600 | 11,763,855 | 7352× |

---

## Top-K Autocomplete

| K | DFS + Sort (µs) | Heap (µs) | Speedup |
|---|---------------:|----------:|---------:|
| 5 | 18,337,586 | 11,333,517 | 1.62× |
| 10 | 25,664,702 | 13,393,213 | 1.92× |
| 20 | 31,132,229 | 14,255,625 | 2.18× |
| 50 | 31,084,400 | 13,943,332 | 2.23× |

---

# Optimizations

### Candidate Filtering

Spell correction filters dictionary words by

- first character
- word length

before computing edit distance, significantly reducing the number of Levenshtein computations.

---

### Heap-Based Top-K Ranking

The initial implementation

```
DFS
↓

Collect all matches
↓

Sort entire vector
```

was optimized to

```
DFS
↓

Bounded Min-Heap (size = K)
↓

Top-K Suggestions
```

reducing ranking complexity from

```
O(M log M)

↓

O(M log K)
```

---

# Building

Compile the application

```bash
g++ src/main.cpp src/Trie.cpp src/DictionaryLoader.cpp src/SearchEngine.cpp src/SpellCorrector.cpp -Iinclude -std=c++17 -O2 -o search_engine
```

Run

```bash
./search_engine
```

Compile benchmark

```bash
g++ src/benchmark.cpp src/Trie.cpp -Iinclude -std=c++17 -O2 -o benchmark
```

Run

```bash
./benchmark
```

---

# Future Improvements

- Dictionary sanitization
- Unit testing
- Benchmark visualization
- Memory profiling
- Configurable ranking strategies
- Additional search ranking heuristics

---

# Technologies

- C++17
- STL
- Trie
- Priority Queue
- Dynamic Programming
- Levenshtein Distance

---

# License

This project is intended for educational and learning purposes.
