#include "DoubleLinkedList.hpp"
 
DoubleLinkedList::DoubleLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}
 
DoubleLinkedList::~DoubleLinkedList() {//iteracja po calej liscie od heada i wywalnie
    DNode* current = head;
    while (current != nullptr) {
        DNode* temp = current->next;
        delete current;
        current = temp;
    }
}
 
void DoubleLinkedList::addFront(int value) {
    DNode* newNode = new DNode(value);
    newNode->next = head; 
    if (head != nullptr) {
        head->previous = newNode; // Stary head wskazuje prev na nowy wezel
    }
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
    size++;
}
 
void DoubleLinkedList::addBack(int value) {
    DNode* newNode = new DNode(value);
    if (tail!= nullptr) {
        tail->next = newNode;
        newNode->previous = tail; 
    } else {
        head = newNode;
    }
    tail = newNode;
    size++;
}
 
void DoubleLinkedList::addAtIndex(int value, int index) {
    if (index <= 0) { 
        addFront(value); return; }
    if (index >= size) { 
        addBack(value); return; }
 
    DNode* newNode = new DNode(value);
    DNode* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    // Wpinamy newNode miedzy current a current->next
    DNode* next = current->next;
    newNode->next = next;
    newNode->previous = current;
    current->next = newNode;
    if (next != nullptr) {
        next->previous = newNode;
    }
    size++;
}
 
void DoubleLinkedList::removeFront() { // Odciecie sznura od glowy
    if (head == nullptr) return; 
    DNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->previous   = nullptr; 
    } else {
        tail = nullptr; 
    }
    delete temp;
    size--;
}
 
void DoubleLinkedList::removeBack() { // Zlozonosc O(1) dzieki wskaznikowi prev
    if (tail == nullptr) return;
    DNode* temp = tail;
    tail = tail->previous;
    if (tail != nullptr) {
        tail->next = nullptr; // Nowy tail nie ma nastepnika
    } else {
        head = nullptr; 
    }
    delete temp;
    size--;
}
 
void DoubleLinkedList::removeAtIndex(int index) {
    if (head == nullptr) return;
    if (index < 0) return;
    if (index == 0) { removeFront(); return; }
    if (index == size - 1) { removeBack(); return; }
 
    DNode* current = head;
    for (int i = 0; i < index; i++) {
        if (current == nullptr) return; 
        current = current->next;
    }
 
    // Odpinamy current z lancucha
    current->previous->next = current->next;
    if (current->next != nullptr) {
        current->next->previous = current->previous;
    }
    delete current;
    size--;
}
 
bool DoubleLinkedList::find(int value) {
    DNode* current = head;
    while (current != nullptr) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}