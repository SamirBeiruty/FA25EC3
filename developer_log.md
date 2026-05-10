# Developer Log

## May 9, 2026

**Work Session:** Full implementation of `tree.h` and activation of `main.cpp` tree-building logic.

**Files Modified:**
- `tree.h`
- `main.cpp`

**What Was Done:**
- Implemented `Node<U>` constructor with id and data initialization.
- Implemented `Tree<T>` with an `unordered_map` to track all allocated nodes for O(1) lookup and safe memory management.
- Implemented `createRoot` to allocate the root node dynamically and register it in the map.
- Implemented `addNode` to find a parent by ID, reuse an existing child node if one with that ID already exists (supporting multiple parents pointing to the same child), or create a new child node otherwise.
- Implemented `findNode` using the internal map for O(1) lookup.
- Implemented `printAll` to print every node, its text, and its children IDs in the expected format.
- Implemented `playGame` to walk the tree interactively, prompting the user at each branching node until a leaf is reached.
- Implemented `~Tree` destructor to iterate the map and delete every dynamically allocated node, preventing memory leaks.
- Activated the commented-out tree construction loop in `main.cpp` to call `createRoot` and `addNode` for all parsed story nodes.
- Added `printAll()` and `playGame()` calls at the end of `main`.

**Issues Encountered:**
- Nodes shared across multiple parents (e.g., node 4 reachable from both node 2 and node 3) required checking the map before allocating, to avoid duplicate allocations and double-free errors in the destructor.

**Commit:** Initial implementation — tree class with multi-parent support, traversal, printing, and gameplay loop.
