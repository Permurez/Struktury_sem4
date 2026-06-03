#pragma once
#include <vector>
#include <list>
#include <utility>
#include "hash_fn.h"

// Wariant 1: Tablica mieszająca z łańcuchowaniem (std::list w kubełkach)
// Kolizje rozwiązywane przez listy jednokierunkowe – metoda łańcuchowa
class HashChaining {
public:
    explicit HashChaining(int capacity) : capacity(capacity) {
        buckets.resize(capacity);
    }

    void insert(int key, int value) {
        int idx = hashFn(key, capacity);
        for (auto& [k, v] : buckets[idx]) {
            if (k == key) { v = value; return; } // aktualizacja istniejącego
        }
        buckets[idx].emplace_back(key, value);
    }

    bool remove(int key) {
        int idx = hashFn(key, capacity);
        auto& chain = buckets[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                return true;
            }
        }
        return false;
    }

    void clear() {
        for (auto& b : buckets) b.clear();
    }

private:
    int capacity;
    std::vector<std::list<std::pair<int, int>>> buckets;
};
