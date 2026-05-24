/*
 * Task 3 — Robot Navigation & Path Tracking Implementation
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Stack (self-implemented, LIFO)
 */

#include "RobotNavigation.hpp"

// ---------------------------------------------------------------
// Step constructor
// ---------------------------------------------------------------
Step::Step(std::string dir, std::string loc) {
    // TODO: Initialize direction = dir, location = loc, next = nullptr
}

// ---------------------------------------------------------------
// PathStack constructor
// ---------------------------------------------------------------
PathStack::PathStack() {
    // TODO: Initialize top = nullptr, size = 0
}

// ---------------------------------------------------------------
// PathStack destructor — free all step nodes
// ---------------------------------------------------------------
PathStack::~PathStack() {
    // TODO: Pop and delete each remaining step until stack is empty
}

// ---------------------------------------------------------------
// push — record one movement step
// ---------------------------------------------------------------
void PathStack::push(std::string direction, std::string location) {
    // TODO: Create new Step node
    // TODO: new->next = current top
    // TODO: top = new node
    // TODO: Increment size
    // TODO: Print log: "Robot moved [direction] -> [location]"
}

// ---------------------------------------------------------------
// pop — remove and return top step
// ---------------------------------------------------------------
Step* PathStack::pop() {
    // TODO: If empty, print error and return nullptr
    // TODO: Save top, move top = top->next
    // TODO: Set saved->next = nullptr, decrement size
    // TODO: Return saved node (caller handles memory)
    return nullptr;
}

Step* PathStack::peek() const {
    // TODO: Return top (nullptr if empty)
    return nullptr;
}

bool PathStack::isEmpty() const {
    // TODO: Return true if top == nullptr
    return true;
}

int PathStack::getSize() const {
    // TODO: Return size
    return 0;
}

// ---------------------------------------------------------------
// displayForwardPath — print path in forward order (first step first)
// ---------------------------------------------------------------
void PathStack::displayForwardPath() const {
    // Stack top = last step; to print forward order, collect into a temp
    // array and print from index (size-1) down to 0.
    //
    // TODO: Print header "=== Forward Path ==="
    // TODO: If empty, print "No path recorded."
    // TODO: Traverse stack into temp array, print in reverse index order
}

// ---------------------------------------------------------------
// returnPath — simulate robot returning via reversed path
// ---------------------------------------------------------------
void PathStack::returnPath() {
    // TODO: Print header "=== Return Path (Reverse) ==="
    // TODO: If empty, print "No path to reverse."
    // TODO: While stack not empty:
    //         pop step, get reverseDirection()
    //         print: "Robot moves [reverse] <- [location]"
    //         delete popped step
}

// ---------------------------------------------------------------
// backtrack — undo last step (obstacle encountered)
// ---------------------------------------------------------------
void PathStack::backtrack() {
    // TODO: If empty, print "Cannot backtrack — no steps recorded."
    // TODO: Pop top step
    // TODO: Print: "Obstacle! Backtracking from [location]..."
    // TODO: Delete popped step
}

// ---------------------------------------------------------------
// reverseDirection
// ---------------------------------------------------------------
std::string PathStack::reverseDirection(std::string dir) const {
    // TODO: "forward" -> "backward"
    // TODO: "backward" -> "forward"
    // TODO: "left" -> "right"
    // TODO: "right" -> "left"
    // TODO: default: return "unknown"
    return "unknown";
}
