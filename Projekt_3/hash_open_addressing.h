#pragma once
#include <vector>
#include <climits>
#include "hash_fn.h"

// Wariant 2: Tablica mieszająca z adresowaniem otwartym – liniowe próbkowanie
// Kolizje rozwiązywane przez przeszukiwanie kolejnych slotów (linear probing)
// Usuwanie leniwe: zamiast kasować slot, oznaczamy go jako DELETED
class HashOpenAddressing {
public:
    explicit HashOpenAddressing(int capacity) : capacity(capacity), size(0) {
        keys.assign(capacity, EMPTY);
        vals.assign(capacity, 0);
    }

    void insert(int key, int value) {
        if (size >= capacity * MAX_LOAD_FACTOR)
            rehash();

        int idx = hashFn(key, capacity);
        while (keys[idx] != EMPTY && keys[idx] != DELETED && keys[idx] != key)
            idx = (idx + 1) % capacity;

        if (keys[idx] == EMPTY || keys[idx] == DELETED) size++;
        keys[idx] = key;
        vals[idx] = value;
    }

    bool remove(int key) {
        int idx = hashFn(key, capacity);
        for (int probed = 0; probed < capacity; probed++) {
            if (keys[idx] == EMPTY) return false; // klucz nie istnieje
            if (keys[idx] == key) {
                keys[idx] = DELETED; // leniwe usuwanie – nie psuje łańcucha próbkowania
                size--;
                return true;
            }
            idx = (idx + 1) % capacity;
        }
        return false;
    }

    void clear() {
        keys.assign(capacity, EMPTY);
        vals.assign(capacity, 0);
        size = 0;
    }

private:
    static constexpr int    EMPTY           = INT_MIN;
    static constexpr int    DELETED         = INT_MIN + 1;
    static constexpr double MAX_LOAD_FACTOR = 0.7;

    int capacity, size;
    std::vector<int> keys, vals;

    void rehash() {
        int newCap = capacity * 2;
        HashOpenAddressing tmp(newCap);
        for (int i = 0; i < capacity; i++)
            if (keys[i] != EMPTY && keys[i] != DELETED)
                tmp.insert(keys[i], vals[i]);
        *this = std::move(tmp);
    }
};
