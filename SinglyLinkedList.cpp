#include "SignlyLinkedList.hpp"
SinglyLinkedList::SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}


SinglyLinkedList::~SinglyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
}

void SinglyLinkedList::addFront(int value) {
    Node* newNode = new Node(value);
    newNode->next = head; // Nowy wezel wskazuje na obecny head
    head = newNode;
    if (tail == nullptr) { 
        tail = newNode;
    }
    size++;
}

void SinglyLinkedList::addBack(int value) {
    Node* newNode = new Node(value);
    if (tail) {  
    tail->next = newNode;} else
    {head = newNode;}
    tail = newNode; 
    size++;
}

void SinglyLinkedList::addAtIndex(int value, int index) {
    if (index <= 0) { addFront(value); return; }
    if (index >= size) { addBack(value); return; }
    Node* newNode = new Node(value);
    Node* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    size++;
}
void SinglyLinkedList::removeFront() {//odciecie sznura od glowy
if (head == nullptr) return; // Lista jest pusta
    Node* temp = head;
    head = head->next; 
    delete temp; 
    size--;
    if(size == 0) {
        tail = nullptr;
    }

}

void SinglyLinkedList::removeBack() { //zlozonosc o(n) bo trzeba przejsc cala liste
    if (head == nullptr) return;

    if (head == tail) {
        delete head;
        head = tail = nullptr;
        size = 0;
        return;
    }

    Node* current = head;
    while (current->next != tail)//kiedy nastepny nie jest ognonem ide dalej
        current = current->next;

    delete tail;
    tail = current;
    tail->next = nullptr;
    size--;
}

void SinglyLinkedList::removeAtIndex(int index) {
if (head == nullptr) return;
else if (index < 0) return;
else if (index == 0) {removeFront();return;}
Node* current = head;
for (int i = 0; i < index - 1; i++) {
    current = current->next;
}
Node* toDelete = current->next;
current->next = toDelete->next;
if(toDelete == tail) {tail = current;}
delete toDelete;
size--;
}

bool SinglyLinkedList::find(int value) {//szukanie po petli O(n)
    Node* current = head;
    while (current!= nullptr) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}