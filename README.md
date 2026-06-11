# Warehouse Robot Navigation System

A C++ simulation of a multi-robot warehouse management system built as a group assignment for the Data Structures (DSTR) module at Asia Pacific University (APU).  
The system models a real warehouse workflow — from order intake to robot dispatch and shelf navigation — using five core data structures.

---

## System Architecture

The project is divided into five modules, each owned by a different team member:

| Module | Data Structure | Role |
|---|---|---|
| **WarehouseLayout** *(my contribution)* | Tree | Warehouse hierarchy & robot navigation |
| ItemSearch | Binary Search Tree (BST) | Item lookup by ID / name |
| OrderManagement | Queue | Order intake and processing |
| RobotAssignment | Circular Queue | Robot availability management |
| RobotNavigation | Stack | Step-by-step path execution |

---

## My Contribution — Warehouse Layout & Navigation (Task 5)

**Files:** `WarehouseLayout/WarehouseLayout.hpp`, `WarehouseLayout/WarehouseLayout.cpp`

I designed and implemented a **self-implemented hierarchical tree** (no STL) to model the physical structure of the warehouse and compute navigation routes between any two locations.

### Data Structure Design
- Each `LocationNode` stores a name, type, a **dynamic array of child pointers** 
  (doubles in capacity when full), and a **parent back-link** for upward traversal
- The tree is 4 levels deep: `Warehouse → Zone → Aisle → Shelf`
- No STL containers used — memory managed manually with `new` / `delete`

### Key Algorithms Implemented
- **`buildLayout()`** — constructs the full warehouse tree (2 zones × 2 aisles × 
  2 shelves each)
- **`findLocation()`** — pre-order recursive search by node name
- **`getPathToLocation()`** — traces parent links from a target shelf up to root, 
  then reverses to produce a root-to-shelf path
- **`getPathBetweenLocations()`** — finds the **Lowest Common Ancestor (LCA)** of 
  two nodes, then splices the upward path from source and downward path to 
  destination into a single route
- **`displayLayout()`** — indented tree display
- **`displayPreOrder()`** — pre-order traversal print
- **`displayRoute()`** — human-readable step-by-step route output

### Integration with Other Modules
The `WarehouseTree` is used by `main.cpp` to:
- Resolve item shelf locations (from `ItemSearch`) into navigable tree paths
- Feed step sequences into `RobotNavigation`'s path stack for execution
- Power the obstacle-handling backtrack demo (sibling node detection via parent links)

---

## How to Compile & Run

```bash
g++ -o warehouse main.cpp \
    WarehouseLayout/WarehouseLayout.cpp \
    ItemSearch/ItemSearch.cpp \
    OrderManagement/OrderManagement.cpp \
    RobotAssignment/RobotAssignment.cpp \
    RobotNavigation/RobotNavigation.cpp

./warehouse
```

The program runs an automated simulation then enters an **interactive menu** where you can process orders, view robot status, and browse the warehouse layout.

---

## Tech Stack
- **Language:** C++ (no STL containers — all data structures self-implemented)
- **Tools:** VS Code, GitHub

---

## Module: Data Structures (DSTR) — Year 2, Computer Science (AI), APU

> This fork highlights my personal contribution (Task 5 — Warehouse Layout & Navigation). Full group project available on request.
