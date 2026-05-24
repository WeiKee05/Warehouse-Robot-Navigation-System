/*
 * DSTR Lab Evaluation Work #2 — Warehouse Robot Navigation System
 * CT077-3-2-DSTR | Asia Pacific University | 2026
 *
 * Full system entry point — integrates all 5 modules:
 *   1. OrderManagement    (Queue)          — Task 1
 *   2. RobotAssignment    (Circular Queue) — Task 2
 *   3. RobotNavigation    (Stack)          — Task 3
 *   4. ItemSearch         (BST)            — Task 4 (Optional)
 *   5. WarehouseLayout    (Tree)           — Task 5 (Optional)
 *
 * All team members contribute to this single prototype.
 */

#include <iostream>
#include "OrderManagement/OrderManagement.hpp"
#include "RobotAssignment/RobotAssignment.hpp"
#include "RobotNavigation/RobotNavigation.hpp"
#include "ItemSearch/ItemSearch.hpp"
#include "WarehouseLayout/WarehouseLayout.hpp"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Warehouse Robot Navigation System     " << std::endl;
    std::cout << "========================================" << std::endl;

    // ----------------------------------------------------------
    // STEP 1: Initialize warehouse layout (Task 5)
    // ----------------------------------------------------------
    // TODO: Create WarehouseTree, call buildLayout()
    // TODO: Display the layout with displayLayout()

    // ----------------------------------------------------------
    // STEP 2: Load item database (Task 4)
    // ----------------------------------------------------------
    // TODO: Create ItemBST, insert sample items with ID, name, location
    // TODO: Display all items with displayAll()

    // ----------------------------------------------------------
    // STEP 3: Receive and queue incoming orders (Task 1)
    // ----------------------------------------------------------
    // TODO: Create OrderQueue, enqueue several sample orders
    // TODO: Display pending orders with displayPending()

    // ----------------------------------------------------------
    // STEP 4: Register robots and assign the first order (Task 2)
    // ----------------------------------------------------------
    // TODO: Create RobotCircularQueue, add robots (e.g., Robot 1–5)
    // TODO: Dequeue first order from OrderQueue
    // TODO: Call assignNext() to get robot for the order
    // TODO: Display robot status with displayStatus()

    // ----------------------------------------------------------
    // STEP 5: Search for item location (Task 4)
    // ----------------------------------------------------------
    // TODO: Use ItemBST::searchById() or searchByName() to find item
    // TODO: Print item location (e.g., "Zone-A/Aisle-2/Shelf-3")

    // ----------------------------------------------------------
    // STEP 6: Generate route to item via warehouse layout (Task 5)
    // ----------------------------------------------------------
    // TODO: Use WarehouseTree::getPathToLocation() to get path array
    // TODO: Print the generated route

    // ----------------------------------------------------------
    // STEP 7: Navigate robot — push each step onto stack (Task 3)
    // ----------------------------------------------------------
    // TODO: Create PathStack
    // TODO: Push movement steps matching the generated route
    //       e.g., push("forward", "Zone-A"), push("left", "Aisle-2"), ...
    // TODO: Display forward path with displayForwardPath()

    // ----------------------------------------------------------
    // STEP 8: Robot completes task — return via reverse path (Task 3)
    // ----------------------------------------------------------
    // TODO: Call PathStack::returnPath() to simulate return journey
    // TODO: Mark assigned robot as available: markAvailable(robotId)

    // ----------------------------------------------------------
    // STEP 9: Mark order as completed (Task 1)
    // ----------------------------------------------------------
    // TODO: Display completed order history with displayCompleted()

    std::cout << "\n========================================" << std::endl;
    std::cout << "  System simulation complete.           " << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
