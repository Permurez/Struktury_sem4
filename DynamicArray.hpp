#pragma once

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;

    void resize();

public:
    DynamicArray();
    ~DynamicArray();

    void addFront(int value);
    void addBack(int value);
    void addAtIndex(int value, int index);

    void removeFront();
    void removeBack();
    void removeAtIndex(int index);

    bool find(int value);
};