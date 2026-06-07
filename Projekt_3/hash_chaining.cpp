#include "hash_chaining.hpp"

#include "hash_fn.hpp"

HashChaining::HashChaining(int capacity) : capacity(capacity) {
    buckets.resize(capacity);
}

void HashChaining::insert(int key, int value) {
    int idx = hashFn(key, capacity);
    for (auto& [k, v] : buckets[idx]) {
        if (k == key) {
            v = value;
            return;
        }
    }
    buckets[idx].emplace_back(key, value);
}

bool HashChaining::remove(int key) {
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

void HashChaining::clear() {
    for (auto& b : buckets) b.clear();
}
