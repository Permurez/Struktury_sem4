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
    cout << "   Wyniki pomiarow dla N = " << N << "\n";
    cout << "======================================\n";

    // Zakres priorytetów kilkukrotnie większy niż N
    int maxPriority = N * 5; 

    LinkedListPQ listPQ;
    HeapPQ heapPQ(N + 100); // Inicjalizacja kopca z zapasem pojemności

    // Wektory do zapamiętania wstawionych wartości (aby móc testować modifyKey)
    vector<int> insertedValues(N);
    vector<int> priorities(N);
    for (int i = 0; i < N; i++) {
        insertedValues[i] = getRandom(1, 10000000);
        priorities[i] = getRandom(1, maxPriority);
    }

    // Badanie operacji INSERT
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        listPQ.insert(insertedValues[i], priorities[i]);
    }
    auto stop = high_resolution_clock::now();
    auto durationListInsert = (duration_cast<nanoseconds>(stop - start))/N; // Średni czas na operację

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        heapPQ.insert(insertedValues[i], priorities[i]);
    }
    stop = high_resolution_clock::now();
    auto durationHeapInsert = (duration_cast<nanoseconds>(stop - start))/N; // Średni czas na operację

    cout << "[INSERT] Lista: " << durationListInsert.count() << " ns | Kopiec: " << durationHeapInsert.count() << " ns\n";

    // Badanie operacji PEEK 
    start = high_resolution_clock::now();
    listPQ.peek();
    stop = high_resolution_clock::now();
    auto durationListPeek = duration_cast<microseconds>(stop - start);

    start = high_resolution_clock::now();
    heapPQ.peek();
    stop = high_resolution_clock::now();
    auto durationHeapPeek = duration_cast<microseconds>(stop - start);

    cout << "[PEEK]   Lista: " << durationListPeek.count() << " us | Kopiec: " << durationHeapPeek.count() << " us\n";

    // Badanie operacji RETURN-SIZE
    start = high_resolution_clock::now();
    listPQ.size();
    stop = high_resolution_clock::now();
    auto durationListSize = duration_cast<nanoseconds>(stop - start);

    start = high_resolution_clock::now();
    heapPQ.size();
    stop = high_resolution_clock::now();
    auto durationHeapSize = duration_cast<nanoseconds>(stop - start);

    cout << "[SIZE]   Lista: " << durationListSize.count() << " ns | Kopiec: " << durationHeapSize.count() << " ns\n";

    // Badanie operacji MODIFY-KEY
    // Modyfikujemy 100 losowych, istniejących elementów
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

    cout << "[MODIFY] Lista: " << durationListModify.count() << " us | Kopiec: " << durationHeapModify.count() << " us (dla " << modifications << " zmian)\n";

    // Badanie operacji EXTRACT-MAX
    // Wyciągamy wszystko aż struktury będą puste
    start = high_resolution_clock::now();
    while (!heapPQ.empty()) {
        heapPQ.extractMax();
    }
    stop = high_resolution_clock::now();
    auto durationHeapExtract = (duration_cast<nanoseconds>(stop - start))/N;//Średni czas zamiast całego

    if (N <= 100000) {
    start = high_resolution_clock::now();
        while (!listPQ.empty()) listPQ.extractMax();
        stop = high_resolution_clock::now();
        auto durationListExtract = duration_cast<nanoseconds>(stop - start);
        cout << "[EXTRACT] Lista: " << durationListExtract.count() << " us | ";
    } else {
        cout << "[EXTRACT] Lista: pomijam dla N > 100000 | ";
    }

    cout << "Kopiec: " << durationHeapExtract.count() << " us\n";
}

int main() {
    // Badamy dla kilku różnych rozmiarów, aby pokazać złożoność czasową
    vector<int> testSizes = {1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000, 5000000, 10000000};
    
    for (int size : testSizes) {
        runTests(size);
    }

    return 0;
}
