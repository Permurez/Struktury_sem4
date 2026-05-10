#pragma once
#include <stdexcept>

struct ListNode {
    int value;
    int priority;
    ListNode* next;
};

class LinkedListPQ {
private:
    ListNode* head;
    int sz;

    ListNode* findMaxPrev() const;

public:
    LinkedListPQ();
    ~LinkedListPQ();

    void insert(int value, int priority);
    ListNode extractMax();
    ListNode peek() const;
    void modifyKey(int value, int newPriority);
    int  size()  const;
    bool empty() const;
};
