#pragma once

#include <climits>
#include <vector>

// Wariant 2: Tablica mieszająca z adresowaniem otwartym – liniowe próbkowanie
class HashOpenAddressing {
public:
    explicit HashOpenAddressing(int capacity);

    void insert(int key, int value);
    bool remove(int key);
    void clear();

private:
    static constexpr int EMPTY = INT_MIN;
    static constexpr int DELETED = INT_MIN + 1;
    static constexpr double MAX_LOAD_FACTOR = 0.7;

    int capacity;
    int size;
    std::vector<int> keys;
    std::vector<int> vals;

    void rehash();
};
