#include "HeapPQ.hpp"
#include <algorithm>  // std::swap



HeapPQ::HeapPQ(int cap) : capacity(cap), sz(0) {
    data = new HeapNode[capacity];
}

HeapPQ::~HeapPQ() {
    delete[] data;
}

// Podwaja rozmiar tablicy gdy jest pelna
void HeapPQ::resize() {
    capacity *= 2;
    HeapNode* newData = new HeapNode[capacity];
    for (int i = 0; i < sz; i++)
        newData[i] = data[i];
    delete[] data;
    data = newData;
}

// "Przesiewa" element w gore dopoki ma wiekszy priorytet niz rodzic
void HeapPQ::heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (data[i].priority > data[parent].priority) {
            std::swap(data[i], data[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

// "Przesiewa" element w dol dopoki ma mniejszy priorytet niz dziecko
void HeapPQ::heapifyDown(int i) {
    while (true) {
        int largest = i;
        int left    = 2 * i + 1;
        int right   = 2 * i + 2;

        if (left  < sz && data[left].priority  > data[largest].priority) largest = left;
        if (right < sz && data[right].priority > data[largest].priority) largest = right;

        if (largest != i) {
            std::swap(data[i], data[largest]);
            i = largest;
        } else {
            break;
        }
    }
}

void HeapPQ::insert(int value, int priority) {
    if (sz == capacity) resize();
    data[sz] = {value, priority};
    heapifyUp(sz);
    sz++;
}

HeapNode HeapPQ::extractMax() {
    if (sz == 0) throw std::runtime_error("Kopiec jest pusty");
    HeapNode maxNode = data[0];
    data[0] = data[sz - 1];
    sz--;
    heapifyDown(0);
    return maxNode;
}

HeapNode HeapPQ::peek() const {
    if (sz == 0) throw std::runtime_error("Kopiec jest pusty");
    return data[0];
}

// Wyszukanie liniowe po wartosci, potem naprawa wlasnosci kopca
void HeapPQ::modifyKey(int value, int newPriority) {
    for (int i = 0; i < sz; i++) {
        if (data[i].value == value) {
            int oldPriority    = data[i].priority;
            data[i].priority   = newPriority;
            if (newPriority > oldPriority)
                heapifyUp(i);
            else
                heapifyDown(i);
            return;
        }
    }
    throw std::runtime_error("Wartosc nie znaleziona");
}

int  HeapPQ::size()  const { return sz; }
bool HeapPQ::empty() const { return sz == 0; }