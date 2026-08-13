high-throughput, low-latency in-memory key-value cache engine implemented in modern C++ (C++17). 

This project provides an extensible caching framework supporting runtime-swappable eviction strategies, specifically **Least Recently Used (LRU)** and **Least Frequently Used (LFU)**, achieving strict O(1) time complexity for both read and write operations.

## Key Features
- **Polymorphic Architecture:** Utilizes an abstract base interface (`Cache.h`) allowing seamless swapping between eviction policies.
- **O(1) Time Complexity:** Employs a hybrid data structure strategy combining `std::unordered_map` with a doubly linked list (`std::list`) for O(1) key lookups, updates, and node evictions.
- **Buffer Pool Engine Design:** Modeled after database storage layers and buffer managers (e.g., PostgreSQL / MySQL buffer pools) to manage constrained memory spaces efficiently.
- **Zero Heavy External Dependencies:** Built entirely with pure modern C++ standard library utilities.

## Project Structure

```text
in-memory-cache/
├── Cache.h          # Abstract base class / Cache interface
├── LRU_Cache.h       # LRU eviction policy implementation
├── LFU_Cache.h       # LFU eviction policy implementation
├── main.cpp         # Driver program and benchmark runner
├── README.md        # Documentation
└── .gitignore      # Git tracking exclusions
