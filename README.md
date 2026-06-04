# Data Structures

My C++ implementations of essential and most commonly used data structures, written from scratch for learning purposes.

## Implemented Structures

| Structure | Description |
|---|---|
| `LinkedList` | linked list with standard operations |
| `DynamicArray` | Resizable array (similar to `std::vector`) |
| `BinarySearchTree` | BST with insert, search and traversal |
| `BinaryHeap` | Min/max heap with heapify operations |
| `HashMap` | Hash table with collision handling |

## Getting Started

Each structure lives in its own folder and can be compiled independently.

```bash
# Clone the repo
git clone https://github.com/kubawn7/Data-Structures.git
cd Data-Structures

# Compile a chosen structure (example)
g++ -std=c++17 -o out LinkedList/LinkedList.cpp
./out
```

Requires a C++17-compatible compiler (GCC, Clang, MSVC).

## Project Structure

```
Data-Structures/
├── LinkedList/
├── DynamicArray/
├── BinarySearchTree/
├── BinaryHeap/
└── HashMap/
```

## Purpose

Educational project — each implementation focuses on clarity over optimization, making it easy to understand the underlying mechanics before reaching for STL containers.

