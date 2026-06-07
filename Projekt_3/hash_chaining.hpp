#pragma once

#include <list>
#include <utility>
#include <vector>

// Wariant 1: Tablica mieszająca z łańcuchowaniem (std::list w kubełkach)
class HashChaining {
public:
    explicit HashChaining(int capacity);

    void insert(int key, int value);
    bool remove(int key);
    void clear();

private:
    int capacity;
    std::vector<std::list<std::pair<int, int>>> buckets;
};
