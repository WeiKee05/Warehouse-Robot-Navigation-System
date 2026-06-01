#ifndef ITEM_SEARCH_HPP
#define ITEM_SEARCH_HPP

#include <iostream>
#include <string>

using namespace std;

struct ItemNode {
    int itemId;
    string itemName;
    string location;
    ItemNode* left;
    ItemNode* right;

    ItemNode(int id, string name, string loc);
};

class ItemBST {
private:
    ItemNode* root;

    ItemNode* insertHelper(ItemNode* node, int id, string name, string loc);
    ItemNode* searchHelper(ItemNode* node, int id) const;
    ItemNode* searchByNameHelper(ItemNode* node, string name) const;
    ItemNode* deleteHelper(ItemNode* node, int id);
    ItemNode* findMin(ItemNode* node) const;

    void inOrderHelper(ItemNode* node) const;
    void destroyTree(ItemNode* node);

public:
    ItemBST();
    ~ItemBST();

    void insert(int itemId, string itemName, string location);
    ItemNode* searchById(int itemId) const;
    ItemNode* searchByName(string itemName) const;
    void updateLocation(int itemId, string newLocation);
    void deleteItem(int itemId);
    void displayAll() const;
};

#endif