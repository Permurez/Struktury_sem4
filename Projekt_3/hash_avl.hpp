#pragma once
#include <vector>

#include "avl_tree.hpp"

// Wariant 3: Tablica mieszająca z łańcuchowaniem – kubełki to drzewa AVL
class HashAVL {
public:
    explicit HashAVL(int capacity);

    void insert(int key, int value);
    bool remove(int key);
    void clear();

private:
    int capacity;
    std::vector<AVLTree> buckets;
};
