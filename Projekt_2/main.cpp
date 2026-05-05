#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include "HeapPQ.hpp"
#include "LinkedListPQ.hpp"

using namespace std;
using namespace std::chrono;

// Funkcja pomocnicza do generowania liczb losowych
int getRandom(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void runTests(int N) {
    cout << "======================================\n";
    cout << "Rozpoczynam badania dla N = " << N << "\n";
    cout << "======================================\n";

    // Zakres priorytetów kilkukrotnie większy niż N
    int maxPriority = N * 5; 

    LinkedListPQ listPQ;
    HeapPQ heapPQ(N + 100); // Inicjalizacja kopca z zapasem pojemności

    // Wektory do zapamiętania wstawionych wartości (aby móc testować modifyKey)
    vector<int> insertedValues;

    // ---------------------------------------------------------
    // 1. Badanie operacji INSERT
    // ---------------------------------------------------------
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        int val = getRandom(1, 1000000);
        int prio = getRandom(1, maxPriority);
        listPQ.insert(val, prio);
        insertedValues.push_back(val); // Zapisujemy wartość do późniejszych testów
    }
    auto stop = high_resolution_clock::now();
    auto durationListInsert = duration_cast<microseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        int val = insertedValues[i];
        int prio = getRandom(1, maxPriority);
        heapPQ.insert(val, prio);
    }
    stop = high_resolution_clock::now();
    auto durationHeapInsert = duration_cast<microseconds>(stop - start);

    cout << "[INSERT] Lista: " << durationListInsert.count() << " us | Kopiec: " << durationHeapInsert.count() << " us\n";

    // ---------------------------------------------------------
    // 2. Badanie operacji PEEK / FIND-MAX
    // ---------------------------------------------------------
    start = high_resolution_clock::now();
    listPQ.peek();
    stop = high_resolution_clock::now();
    auto durationListPeek = duration_cast<nanoseconds>(stop - start);

    start = high_resolution_clock::now();
    heapPQ.peek();
    stop = high_resolution_clock::now();
    auto durationHeapPeek = duration_cast<nanoseconds>(stop - start);

    cout << "[PEEK]   Lista: " << durationListPeek.count() << " ns | Kopiec: " << durationHeapPeek.count() << " ns\n";

    // ---------------------------------------------------------
    // 3. Badanie operacji RETURN-SIZE
    // ---------------------------------------------------------
    start = high_resolution_clock::now();
    listPQ.size();
    stop = high_resolution_clock::now();
    auto durationListSize = duration_cast<nanoseconds>(stop - start);

    start = high_resolution_clock::now();
    heapPQ.size();
    stop = high_resolution_clock::now();
    auto durationHeapSize = duration_cast<nanoseconds>(stop - start);

    cout << "[SIZE]   Lista: " << durationListSize.count() << " ns | Kopiec: " << durationHeapSize.count() << " ns\n";

    // ---------------------------------------------------------
    // 4. Badanie operacji MODIFY-KEY
    // Modyfikujemy 100 losowych, istniejących elementów
    // ---------------------------------------------------------
    int modifications = 100;
    start = high_resolution_clock::now();
    for (int i = 0; i < modifications; i++) {
        int randomIdx = getRandom(0, N - 1);
        int newPrio = getRandom(1, maxPriority);
        listPQ.modifyKey(insertedValues[randomIdx], newPrio);
    }
    stop = high_resolution_clock::now();
    auto durationListModify = duration_cast<microseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int i = 0; i < modifications; i++) {
        int randomIdx = getRandom(0, N - 1);
        int newPrio = getRandom(1, maxPriority);
        heapPQ.modifyKey(insertedValues[randomIdx], newPrio);
    }
    stop = high_resolution_clock::now();
    auto durationHeapModify = duration_cast<microseconds>(stop - start);

    cout << "[MODIFY] Lista: " << durationListModify.count() << " us | Kopiec: " << durationHeapModify.count() << " us (dla " << modifications << " prob)\n";

    // ---------------------------------------------------------
    // 5. Badanie operacji EXTRACT-MAX
    // Wyciągamy wszystko aż struktury będą puste
    // ---------------------------------------------------------
    start = high_resolution_clock::now();
    while (!listPQ.empty()) {
        listPQ.extractMax();
    }
    stop = high_resolution_clock::now();
    auto durationListExtract = duration_cast<microseconds>(stop - start);

    start = high_resolution_clock::now();
    while (!heapPQ.empty()) {
        heapPQ.extractMax();
    }
    stop = high_resolution_clock::now();
    auto durationHeapExtract = duration_cast<microseconds>(stop - start);

    cout << "[EXTRACT] Lista: " << durationListExtract.count() << " us | Kopiec: " << durationHeapExtract.count() << " us\n\n";
}

int main() {
    // Badamy dla kilku różnych rozmiarów, aby pokazać złożoność czasową
    vector<int> testSizes = {1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000, 5000000, 10000000};
    
    for (int size : testSizes) {
        runTests(size);
    }

    return 0;
}