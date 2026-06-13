/*
 * Task 5 — Warehouse Layout & Navigation Module Implementation
 * Member: Lee Wei Kee
 * Student ID: TP076249
 * Data Structure: Tree (hierarchical, self-implemented)
 */

#include "WarehouseLayout.hpp"

using namespace std;

// ─────────────────────────────────────────────
// LocationNode Constructor
// Called automatically when a new node is created with 'new LocationNode(name, type)'
// Sets up the node's name, type, an empty children array (4 slots), and no parent yet
// ─────────────────────────────────────────────
LocationNode::LocationNode(std::string n, std::string t) {
    name = n;
    type = t;
    children = new LocationNode*[INITIAL_CAPACITY]; // allocate 4 empty slots for children on the heap
    childCount = 0;                                 // no children yet
    childCapacity = INITIAL_CAPACITY;               // array currently holds up to 4 children
    parent = nullptr;                               // no parent yet — will be set by addChild()
}

// ─────────────────────────────────────────────
// LocationNode Destructor
// Called automatically when 'delete node' is used
// Only frees the children pointer array — NOT the child nodes themselves
// Child nodes are deleted separately by destroyTree()
// ─────────────────────────────────────────────
LocationNode::~LocationNode() {
    delete[] children; // free the array of pointer slots only
}

// ─────────────────────────────────────────────
// addChild — attach one child node under this node
// Step 1: check if the children array is full
// Step 2: if full, double the array size, copy old pointers, delete old array
// Step 3: place the new child pointer into the next empty slot
// Step 4: set the child's parent pointer back to this node
// ─────────────────────────────────────────────
void LocationNode::addChild(LocationNode* child) {
    if (childCount == childCapacity) {              // array is full — need to grow
        int newCapacity = childCapacity * 2;        // double the capacity
        LocationNode** newArr = new LocationNode*[newCapacity]; // allocate bigger array
        for (int i = 0; i < childCount; i++) {
            newArr[i] = children[i];                // copy existing pointers to new array
        }
        delete[] children;                          // free the old array
        children = newArr;                          // point to the new bigger array
        childCapacity = newCapacity;                // update capacity
    }
    children[childCount++] = child;                 // place new child in next empty slot, then increment count
    child->parent = this;                           // tell the child: this node is your parent
}

// ─────────────────────────────────────────────
// WarehouseTree Constructor
// Called when a WarehouseTree object is created
// Tree starts empty — buildLayout() fills it later
// ─────────────────────────────────────────────
WarehouseTree::WarehouseTree() {
    root = nullptr; // empty tree, no nodes yet
}

// ─────────────────────────────────────────────
// WarehouseTree Destructor
// Called automatically when the WarehouseTree object is destroyed
// Calls destroyTree() to delete every node and free all heap memory
// ─────────────────────────────────────────────
WarehouseTree::~WarehouseTree() {
    destroyTree(root);
}

// ─────────────────────────────────────────────
// destroyTree — delete all nodes in the tree, starting from deepest level
// Step 1: if node is null, stop (base case)
// Step 2: recursively delete all children first (deepest nodes deleted first)
// Step 3: then delete this node (triggers ~LocationNode to free its children array)
// Must delete children before parent — deleting parent first loses all child pointers
// ─────────────────────────────────────────────
void WarehouseTree::destroyTree(LocationNode* node) {
    if (node == nullptr) return;                    // nothing to delete
    for (int i = 0; i < node->childCount; i++) {
        destroyTree(node->children[i]);             // delete this child and all nodes below it
    }
    delete node;                                    // all children gone — safe to delete this node now
}

// ─────────────────────────────────────────────
// depthOf — count how many levels down this node is from the root
// Root = depth 0, Zone = depth 1, Aisle = depth 2, Shelf = depth 3
// Walks up via parent pointers, counting each step until reaching the root
// Used by findLCA() to align two nodes to the same depth before searching
// ─────────────────────────────────────────────
int WarehouseTree::depthOf(LocationNode* node) const {
    int depth = 0;
    while (node->parent != nullptr) {   // keep going while there is a parent above
        node = node->parent;            // move up one level
        depth++;                        // count this step
    }
    return depth;
}

// ─────────────────────────────────────────────
// findLCA — find the Lowest Common Ancestor of two nodes
// The LCA is the deepest node that is above both locations
// It is the turning point in the route — go UP to LCA, then DOWN to destination
// Step 1: get the depth of both nodes
// Step 2: bring the deeper node up until both are at the same depth
// Step 3: walk both nodes up together until they point to the same node — that is the LCA
// ─────────────────────────────────────────────
LocationNode* WarehouseTree::findLCA(LocationNode* a, LocationNode* b) const {
    if (a == nullptr || b == nullptr) return nullptr; // safety check

    int da = depthOf(a);
    int db = depthOf(b);

    while (da > db) { a = a->parent; da--; }   // bring a up to match b's depth
    while (db > da) { b = b->parent; db--; }   // bring b up to match a's depth

    while (a != b) {        // walk both up together until they meet
        a = a->parent;
        b = b->parent;
    }
    return a;               // a and b now point to the same node — the LCA
}

// ─────────────────────────────────────────────
// getPathBetweenLocations — build the full route between two locations
// Step 1: find both nodes by name
// Step 2: safety check — stop if either location doesn't exist
// Step 3: find the LCA (turning point between going up and going down)
// Step 4: build root→from path and root→to path using buildPath()
// Step 5: find where the LCA appears in each path
// Step 6: read fromPath BACKWARDS (from→LCA) then toPath FORWARDS (LCA→to)
// Step 7: return total number of locations in the final route
// ─────────────────────────────────────────────
int WarehouseTree::getPathBetweenLocations(const string& fromName,
                                            const string& toName,
                                            string* pathArr, int maxLen) const {
    LocationNode* fromNode = findLocation(fromName); // search tree for starting node
    LocationNode* toNode   = findLocation(toName);   // search tree for destination node

    if (fromNode == nullptr) {
        cout << "[WarehouseLayout] Source location not found: " << fromName << endl;
        return 0;
    }
    if (toNode == nullptr) {
        cout << "[WarehouseLayout] Destination location not found: " << toName << endl;
        return 0;
    }

    LocationNode* lca = findLCA(fromNode, toNode); // find the turning point

    string fromPath[MAX_PATH_LEN]; // temp array: root → fromNode
    string toPath[MAX_PATH_LEN];   // temp array: root → toNode
    int fromLen = buildPath(fromNode, fromPath, MAX_PATH_LEN);
    int toLen   = buildPath(toNode,   toPath,   MAX_PATH_LEN);

    int lcaIdxFrom = -1, lcaIdxTo = -1; // index of LCA in each path (-1 = not found yet)
    for (int i = 0; i < fromLen; i++) {
        if (fromPath[i] == lca->name) { lcaIdxFrom = i; break; } // found LCA in fromPath
    }
    for (int i = 0; i < toLen; i++) {
        if (toPath[i] == lca->name) { lcaIdxTo = i; break; }     // found LCA in toPath
    }

    int idx = 0;
    // first half: read fromPath backwards — from starting node UP to LCA
    for (int i = fromLen - 1; i >= lcaIdxFrom && idx < maxLen; i--) {
        pathArr[idx++] = fromPath[i];
    }
    // second half: read toPath forwards — from just after LCA DOWN to destination
    // skip lcaIdxTo because LCA is already added in the first half
    for (int i = lcaIdxTo + 1; i < toLen && idx < maxLen; i++) {
        pathArr[idx++] = toPath[i];
    }
    return idx; // total number of locations in the route
}

// ─────────────────────────────────────────────
// displayRoute — print the route between two locations step by step
// Step 1: call getPathBetweenLocations() to fill the path array
// Step 2: if no path found, stop
// Step 3: print a header showing start and end
// Step 4: loop through each location — print step number, current location, and next location
// Step 5: print total number of movements (steps = locations - 1)
// ─────────────────────────────────────────────
void WarehouseTree::displayRoute(const string& fromName, const string& toName) const {
    string path[MAX_PATH_LEN];
    int len = getPathBetweenLocations(fromName, toName, path, MAX_PATH_LEN);

    if (len == 0) return; // no route found — stop

    cout << "\n=== Route: " << fromName << " --> " << toName << " ===" << endl;
    for (int i = 0; i < len; i++) {
        cout << "  Step " << (i + 1) << ": " << path[i];
        if (i < len - 1) cout << " -> " << path[i + 1]; // print arrow to next location (skip on last step)
        cout << endl;
    }
    cout << "Total steps: " << (len - 1) << endl; // movements = locations - 1
}

// ─────────────────────────────────────────────
// buildLayout — create all nodes and connect them into the warehouse tree
// Called once at startup
// Pattern for each level: create node → attach to parent → attach children
// Zones and aisles need pointer variables because addChild() is called on them later
// Shelves are created and attached in one line — they have no children
// ─────────────────────────────────────────────
void WarehouseTree::buildLayout() {
    root = new LocationNode("Warehouse", "warehouse"); // create the top-level root node

    // --- Zone A ---
    LocationNode* zoneA = new LocationNode("Zone-A", "zone");
    root->addChild(zoneA);                             // attach Zone-A under Warehouse

    LocationNode* aisle1 = new LocationNode("Aisle-1", "aisle");
    zoneA->addChild(aisle1);                           // attach Aisle-1 under Zone-A
    aisle1->addChild(new LocationNode("Shelf-1", "shelf")); // attach Shelf-1 under Aisle-1
    aisle1->addChild(new LocationNode("Shelf-2", "shelf")); // attach Shelf-2 under Aisle-1

    LocationNode* aisle2 = new LocationNode("Aisle-2", "aisle");
    zoneA->addChild(aisle2);                           // attach Aisle-2 under Zone-A
    aisle2->addChild(new LocationNode("Shelf-3", "shelf")); // attach Shelf-3 under Aisle-2
    aisle2->addChild(new LocationNode("Shelf-4", "shelf")); // attach Shelf-4 under Aisle-2

    // --- Zone B ---
    LocationNode* zoneB = new LocationNode("Zone-B", "zone");
    root->addChild(zoneB);                             // attach Zone-B under Warehouse

    LocationNode* aisle3 = new LocationNode("Aisle-3", "aisle");
    zoneB->addChild(aisle3);                           // attach Aisle-3 under Zone-B
    aisle3->addChild(new LocationNode("Shelf-5", "shelf")); // attach Shelf-5 under Aisle-3
    aisle3->addChild(new LocationNode("Shelf-6", "shelf")); // attach Shelf-6 under Aisle-3

    LocationNode* aisle4 = new LocationNode("Aisle-4", "aisle");
    zoneB->addChild(aisle4);                           // attach Aisle-4 under Zone-B
    aisle4->addChild(new LocationNode("Shelf-7", "shelf")); // attach Shelf-7 under Aisle-4
    aisle4->addChild(new LocationNode("Shelf-8", "shelf")); // attach Shelf-8 under Aisle-4
}

// ─────────────────────────────────────────────
// findNode — search the tree for a node with a matching name (pre-order DFS)
// Step 1: if node is null, stop — nothing to check (base case)
// Step 2: if this node's name matches, return it — found
// Step 3: search each child one by one — if any returns a match, pass it up immediately
// Step 4: if nothing found in this entire subtree, return nullptr
// ─────────────────────────────────────────────
LocationNode* WarehouseTree::findNode(LocationNode* node, const string& name) const {
    if (node == nullptr) return nullptr;        // nothing here
    if (node->name == name) return node;        // found it — return this node
    for (int i = 0; i < node->childCount; i++) {
        LocationNode* result = findNode(node->children[i], name); // search this child's subtree
        if (result != nullptr) return result;   // found in subtree — pass it up
    }
    return nullptr;                             // not found in this subtree
}

// ─────────────────────────────────────────────
// findLocation — public wrapper for findNode()
// Always starts the search from the root
// Caller only needs to pass the name — root is handled internally
// ─────────────────────────────────────────────
LocationNode* WarehouseTree::findLocation(const string& name) const {
    return findNode(root, name); // start searching from the top of the tree
}

// ─────────────────────────────────────────────
// buildPath — build a root→target path as an array of location names
// Step 1: walk UP from target to root using parent pointers, collect names into temp[]
//         result in temp is bottom→top (target first, root last) — wrong order
// Step 2: reverse temp[] into pathArr so order becomes root→target (correct order)
// Step 3: return how many locations are in the path
// Note: copyLen safety check prevents writing past the caller's array size limit
// ─────────────────────────────────────────────
int WarehouseTree::buildPath(LocationNode* target, std::string* pathArr, int maxLen) const {
    string temp[MAX_PATH_LEN]; // scratch array — stores names bottom→top while walking up
    int len = 0;
    LocationNode* current = target;
    while (current != nullptr && len < MAX_PATH_LEN) {
        temp[len++] = current->name; // collect this node's name, then move up
        current = current->parent;
    }
    // take whichever is smaller — actual path length or caller's array limit
    int copyLen = (len < maxLen) ? len : maxLen;
    for (int i = 0; i < copyLen; i++) {
        pathArr[i] = temp[len - 1 - i]; // reverse: read temp from last to first
    }
    return copyLen; // number of locations in the path
}

// ─────────────────────────────────────────────
// getPathToLocation — find a node by name and return the root→target path
// Step 1: find the target node using findLocation()
// Step 2: safety check — stop if name doesn't exist in the tree
// Step 3: call buildPath() to build and return the root→target path
// Returns path length (0 if not found)
// ─────────────────────────────────────────────
int WarehouseTree::getPathToLocation(const string& targetName, string* pathArr, int maxLen) const {
    LocationNode* target = findLocation(targetName); // search tree for the target node
    if (target == nullptr) {
        cout << "Location not found: " << targetName << endl;
        return 0;
    }
    return buildPath(target, pathArr, maxLen); // build and return the path
}

// ─────────────────────────────────────────────
// displayTree — print the warehouse layout as an indented hierarchy
// Step 1: if node is null, stop (base case)
// Step 2: print spaces based on depth (4 spaces per level) — creates visual indentation
// Step 3: print this node's name and type on the same line
// Step 4: recursively call displayTree on each child with depth+1
// ─────────────────────────────────────────────
void WarehouseTree::displayTree(LocationNode* node, int depth) const {
    if (node == nullptr) return;
    for (int i = 0; i < depth * 4; i++) cout << " "; // 4 spaces per level of depth
    cout << node->name << " (" << node->type << ")" << endl;
    for (int i = 0; i < node->childCount; i++) {
        displayTree(node->children[i], depth + 1); // print each child one level deeper
    }
}

// ─────────────────────────────────────────────
// displayLayout — public entry point for printing the tree
// Checks if the tree has been built, then calls displayTree() starting from root at depth 0
// ─────────────────────────────────────────────
void WarehouseTree::displayLayout() const {
    cout << "\n=== Warehouse Layout ===" << endl;
    if (root == nullptr) {
        cout << "Layout not built yet." << endl;
        return;
    }
    displayTree(root, 0); // start printing from root at depth 0
}

// ─────────────────────────────────────────────
// traversePreOrder — visit every node in pre-order (current node first, then children)
// Print current node's name, then recursively visit each child left to right
// ─────────────────────────────────────────────
void WarehouseTree::traversePreOrder(LocationNode* node) const {
    if (node == nullptr) return;
    cout << node->name << endl;                     // print this node first
    for (int i = 0; i < node->childCount; i++) {
        traversePreOrder(node->children[i]);        // then visit each child
    }
}

// ─────────────────────────────────────────────
// displayPreOrder — public entry point for pre-order traversal
// Calls traversePreOrder() starting from root
// ─────────────────────────────────────────────
void WarehouseTree::displayPreOrder() const {
    cout << "\n=== Pre-Order Traversal ===" << endl;
    traversePreOrder(root);
}
