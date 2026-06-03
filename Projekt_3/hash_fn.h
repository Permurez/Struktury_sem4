#pragma once

// Uniwersalna funkcja mieszająca – modularna, obsługuje ujemne klucze
inline int hashFn(int key, int capacity) {
    return ((key % capacity) + capacity) % capacity;
}
