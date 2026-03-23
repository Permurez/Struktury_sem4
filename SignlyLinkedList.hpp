#pragma once

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    void addFront(int value);
    void addBack(int value);
    void addAtIndex(int value, int index);

    void removeFront();
    void removeBack();
    void removeAtIndex(int index);

    bool find(int value);
};