#pragma once
#include <vector>
#include "avl_tree.h"
#include "hash_fn.h"

// Wariant 3: Tablica mieszająca z łańcuchowaniem – kubełki to drzewa AVL
// Zamiast listy w kubełku używamy AVL → wyszukiwanie O(log k) zamiast O(k)
// Sensowne gdy współczynnik wypełnienia wysoki i kolizji jest dużo
class HashAVL {
public:
    explicit HashAVL(int capacity) : capacity(capacity) {
        buckets.resize(capacity);
    }

    void insert(int key, int value) {
        buckets[hashFn(key, capacity)].insert(key, value);
    }

    bool remove(int key) {
        return buckets[hashFn(key, capacity)].remove(key);
    }

    void clear() {
        for (auto& b : buckets) b.clear();
    }

private:
    int capacity;
    std::vector<AVLTree> buckets;
};
