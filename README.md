# Warehouse Robot Navigation System

A C++ simulation of an autonomous warehouse management system, built as a group assignment for the Data Structures module. 

The system models a real warehouse workflow — from receiving a customer order, assigning a robot, navigating to the item's shelf, and returning to the starting point — all using self-implemented data structures with no STL containers allowed.

---

## How the System Works

1. A customer order arrives and is added to the queue
2. A robot is assigned to handle the order
3. The system locates the item's shelf in the warehouse
4. A route is generated from the robot's position to the shelf
5. The robot follows the route step by step
6. After picking up the item, the robot retraces its path back

---

## System Modules

The project is split into five modules, each owned by a different team member:

| Module | Data Structure | What It Does |
|---|---|---|
| **WarehouseLayout** *(my contribution)* | Tree | Models the warehouse layout and generates navigation routes |
| OrderManagement | Queue | Receives and processes customer orders in order of arrival |
| RobotAssignment | Circular Queue | Assigns tasks to robots fairly in rotation |
| RobotNavigation | Stack | Records each movement step and retraces the path in reverse |
| ItemSearch | Binary Search Tree (BST) | Stores all items and looks them up quickly by ID or name |

---

## My Contribution — Warehouse Layout & Navigation (Task 5)

**Files:** `WarehouseLayout/WarehouseLayout.hpp` · `WarehouseLayout/WarehouseLayout.cpp`

Built a **self-implemented tree** to represent the physical structure of the warehouse and generate step-by-step navigation routes between any two locations.

### The Warehouse Structure

The tree has 4 levels:

```
Warehouse
├── Zone-A
│   ├── Aisle-1
│   │   ├── Shelf-1
│   │   └── Shelf-2
│   └── Aisle-2
│       ├── Shelf-3
│       └── Shelf-4
└── Zone-B
    ├── Aisle-3
    │   ├── Shelf-5
    │   └── Shelf-6
    └── Aisle-4
        ├── Shelf-7
        └── Shelf-8
```

### How the Tree Node Works

Each location in the warehouse is stored as a `LocationNode` containing:
- `name` — the location name e.g. `"Shelf-3"`
- `type` — the level it sits at e.g. `"zone"`, `"aisle"`, `"shelf"`
- `children` — a dynamic array of pointers to child nodes (starts at 4 slots, doubles when full)
- `parent` — a pointer back up to the parent node, used for path tracing

No STL containers were used — all memory is managed manually using `new` and `delete`.

### Key Functions

| Function | What It Does |
|---|---|
| `buildLayout()` | Creates all nodes and connects them into the full warehouse tree |
| `findLocation()` | Searches the tree by name using pre-order depth-first search |
| `buildPath()` | Walks up from a node to the root via parent pointers, then reverses the result to get root → node order |
| `getPathBetweenLocations()` | Finds the **Lowest Common Ancestor (LCA)** of two locations, then combines the upward path from the start and the downward path to the destination into one complete route |
| `displayLayout()` | Prints the full warehouse tree in an indented format |
| `displayRoute()` | Prints the route between two locations step by step |

### Why Does LCA Matter?

To find the shortest route between two shelves, the system finds their **Lowest Common Ancestor** — the deepest node in the tree that is above both locations. This is the turning point in the route.

```
Example: Shelf-1 to Shelf-5

Shelf-1 → Aisle-1 → Zone-A → Warehouse → Zone-B → Aisle-3 → Shelf-5
          (going UP to LCA)              (going DOWN to destination)

LCA = Warehouse (because Shelf-1 and Shelf-5 are in different zones)
```

If two shelves are in the same zone, the LCA would be that zone — meaning the robot does not need to travel all the way up to the root.

### How My Module Connects to the Rest of the System

- `ItemSearch` finds which shelf an item is stored on
- `WarehouseLayout` takes that shelf name and generates the route to reach it
- `RobotNavigation` receives the route and records each step on a stack, allowing the robot to retrace its path in reverse after completing the task

---

## How to Compile and Run

```bash
g++ -o warehouse main.cpp \
    WarehouseLayout/WarehouseLayout.cpp \
    ItemSearch/ItemSearch.cpp \
    OrderManagement/OrderManagement.cpp \
    RobotAssignment/RobotAssignment.cpp \
    RobotNavigation/RobotNavigation.cpp

./warehouse
```

The program runs an automated demo first, then opens an interactive menu where you can process orders, check robot status, and explore the warehouse layout.

---

## Tech Stack

- **Language:** C++17
- **Data structures:** All self-implemented — no STL containers (`<vector>`, `<list>`, etc.)
- **Tools:** VS Code, GitHub


> This fork highlights my personal contribution — Task 5: Warehouse Layout & Navigation. The full group project is available on request.
