#include "hash_avl.hpp"
#include "hash_fn.hpp"

HashAVL::HashAVL(int capacity) : capacity(capacity) {
    buckets.resize(capacity);
}

void HashAVL::insert(int key, int value) {
    buckets[hashFn(key, capacity)].insert(key, value);
}

bool HashAVL::remove(int key) {
    return buckets[hashFn(key, capacity)].remove(key);
}

void HashAVL::clear() {
    for (auto& b : buckets) b.clear();
}
