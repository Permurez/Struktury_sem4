#include "DynamicArray.hpp"

DynamicArray::DynamicArray() {
    size = 0;
    capacity = 1;
    data = new int[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

// Podwaja rozmiar tablicy w momencie braku miejsca
void DynamicArray::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void DynamicArray::addFront(int value) {
    if (size == capacity) resize();
    for (int i = size; i > 0; i--) {
        data[i] = data[i - 1];
    }
    data[0] = value;
    size++;
}

void DynamicArray::addBack(int value) {
    if (size == capacity) resize();
    data[size] = value;
    size++;
}
void DynamicArray::addAtIndex(int value, int index) {
    if (index <= 0) { addFront(value); return; }
    if (index >= size) { addBack(value); return; }
    if (size == capacity) resize();
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void DynamicArray::removeFront() {
    if (size == 0) return;
    for (int i = 0; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

void DynamicArray::removeBack() {
    if (size == 0) return;
    size--;
}
void DynamicArray::removeAtIndex(int index) {
    if (size == 0) return;
    if (index <= 0) { removeFront(); return; }
    if (index >= size - 1) { removeBack(); return; }
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}


bool DynamicArray::find(int value) {
    for (int i = 0; i < size; i++) {
        if (data[i] == value) return true;
    }
    return false;
}