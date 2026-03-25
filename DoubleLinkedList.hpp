#pragma once
 
struct DNode { //bo Node jest juz w SinglyLinkedList
    int data;
    DNode* next;
    DNode* previous;
 
    DNode(int val) : data(val), next(nullptr), previous (nullptr) {}
};
 
class DoubleLinkedList {
private:
    DNode* head;
    DNode* tail;
    int size;
 
public:
    DoubleLinkedList();
    ~DoubleLinkedList();
 
    void addFront(int value);
    void addBack(int value);
    void addAtIndex(int value, int index);
 
    void removeFront();
    void removeBack();
    void removeAtIndex(int index);
 
    bool find(int value);
};
 