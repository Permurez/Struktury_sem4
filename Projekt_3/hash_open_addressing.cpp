#include "hash_open_addressing.hpp"

#include <utility>

#include "hash_fn.hpp"

HashOpenAddressing::HashOpenAddressing(int capacity) : capacity(capacity), size(0) {
    keys.assign(capacity, EMPTY);
    vals.assign(capacity, 0);
}

void HashOpenAddressing::insert(int key, int value) {
    if (size >= capacity * MAX_LOAD_FACTOR)
        rehash();

    int idx = hashFn(key, capacity);
    while (keys[idx] != EMPTY && keys[idx] != DELETED && keys[idx] != key)
        idx = (idx + 1) % capacity;

    if (keys[idx] == EMPTY || keys[idx] == DELETED) ++size;
    keys[idx] = key;
    vals[idx] = value;
}

bool HashOpenAddressing::remove(int key) {
    int idx = hashFn(key, capacity);
    for (int probed = 0; probed < capacity; ++probed) {
        if (keys[idx] == EMPTY) return false;
        if (keys[idx] == key) {
            keys[idx] = DELETED;
            --size;
            return true;
        }
        idx = (idx + 1) % capacity;
    }
    return false;
}

void HashOpenAddressing::clear() {
    keys.assign(capacity, EMPTY);
    vals.assign(capacity, 0);
    size = 0;
}

void HashOpenAddressing::rehash() {
    int newCap = capacity * 2;
    HashOpenAddressing tmp(newCap);
    for (int i = 0; i < capacity; ++i) {
        if (keys[i] != EMPTY && keys[i] != DELETED)
            tmp.insert(keys[i], vals[i]);
    }
    *this = std::move(tmp);
}
