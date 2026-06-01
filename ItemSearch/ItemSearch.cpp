/*
 * Task 4 — Item Search & Management Module Implementation
 * Member: Ng Wan Teng
 * Student ID: TP076289
 * Data Structure: Binary Search Tree (BST)
 */

#include "ItemSearch.hpp"

using namespace std;

ItemNode::ItemNode(int id, string name, string loc) {
    itemId = id;
    itemName = name;
    location = loc;
    left = nullptr;
    right = nullptr;
}

ItemBST::ItemBST() {
    root = nullptr;
}

ItemBST::~ItemBST() {
    destroyTree(root);
    root = nullptr;
}

void ItemBST::destroyTree(ItemNode* node) {
    if (node == nullptr) return;

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

ItemNode* ItemBST::insertHelper(ItemNode* node, int id, string name, string loc) {
    if (node == nullptr) {
        return new ItemNode(id, name, loc);
    }

    if (id < node->itemId) {
        node->left = insertHelper(node->left, id, name, loc);
    } 
    else if (id > node->itemId) {
        node->right = insertHelper(node->right, id, name, loc);
    } 
    else {
        node->itemName = name;
        node->location = loc;
    }

    return node;
}

void ItemBST::insert(int itemId, string itemName, string location) {
    bool existingItem = (searchById(itemId) != nullptr);

    root = insertHelper(root, itemId, itemName, location);

    if (existingItem) {
        cout << "[ItemSearch] Existing item updated: "
             << itemId << " | " << itemName << " | " << location << endl;
    } 
    else {
        cout << "[ItemSearch] Item inserted: "
             << itemId << " | " << itemName << " | " << location << endl;
    }
}

ItemNode* ItemBST::searchHelper(ItemNode* node, int id) const {
    if (node == nullptr || node->itemId == id) {
        return node;
    }

    if (id < node->itemId) {
        return searchHelper(node->left, id);
    }

    return searchHelper(node->right, id);
}

ItemNode* ItemBST::searchById(int itemId) const {
    return searchHelper(root, itemId);
}

ItemNode* ItemBST::searchByNameHelper(ItemNode* node, string name) const {
    if (node == nullptr) return nullptr;

    ItemNode* leftResult = searchByNameHelper(node->left, name);
    if (leftResult != nullptr) return leftResult;

    if (node->itemName == name) return node;

    return searchByNameHelper(node->right, name);
}

ItemNode* ItemBST::searchByName(string itemName) const {
    return searchByNameHelper(root, itemName);
}

ItemNode* ItemBST::findMin(ItemNode* node) const {
    if (node == nullptr) return nullptr;

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

ItemNode* ItemBST::deleteHelper(ItemNode* node, int id) {
    if (node == nullptr) return nullptr;

    if (id < node->itemId) {
        node->left = deleteHelper(node->left, id);
    } 
    else if (id > node->itemId) {
        node->right = deleteHelper(node->right, id);
    } 
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        if (node->left == nullptr) {
            ItemNode* temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == nullptr) {
            ItemNode* temp = node->left;
            delete node;
            return temp;
        }

        ItemNode* successor = findMin(node->right);

        node->itemId = successor->itemId;
        node->itemName = successor->itemName;
        node->location = successor->location;

        node->right = deleteHelper(node->right, successor->itemId);
    }

    return node;
}

void ItemBST::deleteItem(int itemId) {
    ItemNode* item = searchById(itemId);

    if (item == nullptr) {
        cout << "[ItemSearch] Item ID " << itemId
             << " not found. Delete cancelled." << endl;
        return;
    }

    cout << "[ItemSearch] Item deleted: "
         << item->itemId << " | "
         << item->itemName << " | "
         << item->location << endl;

    root = deleteHelper(root, itemId);
}

void ItemBST::updateLocation(int itemId, string newLocation) {
    ItemNode* item = searchById(itemId);

    if (item == nullptr) {
        cout << "[ItemSearch] Item ID " << itemId
             << " not found. Update cancelled." << endl;
        return;
    }

    string oldLocation = item->location;
    item->location = newLocation;

    cout << "[ItemSearch] Location updated for "
         << item->itemName << " from "
         << oldLocation << " to "
         << newLocation << endl;
}

void ItemBST::inOrderHelper(ItemNode* node) const {
    if (node == nullptr) return;

    inOrderHelper(node->left);

    cout << "  ID: " << node->itemId
         << " | Name: " << node->itemName
         << " | Location: " << node->location << endl;

    inOrderHelper(node->right);
}

void ItemBST::displayAll() const {
    cout << "\n=== Item Database (Sorted by Item ID) ===" << endl;

    if (root == nullptr) {
        cout << "No items in database." << endl;
        return;
    }

    inOrderHelper(root);
}