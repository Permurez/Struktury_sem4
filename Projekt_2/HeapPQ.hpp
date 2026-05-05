#pragma once
#include <stdexcept>
 
struct HeapNode {
    int value;
    int priority;
};
 
class HeapPQ {
private:
    HeapNode* data;
    int capacity;
    int sz;
 
    void resize();
    void heapifyUp(int i);
    void heapifyDown(int i);
 
public:
    HeapPQ(int cap = 16);
    ~HeapPQ();
 
    void insert(int value, int priority);
    HeapNode extractMax();
    HeapNode peek() const;
    void modifyKey(int value, int newPriority);
    int size() const;
    bool empty() const;
};