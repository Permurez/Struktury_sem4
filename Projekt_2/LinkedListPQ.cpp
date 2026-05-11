#include "LinkedListPQ.hpp"

// Zwraca wskaznik na poprzednika wezla z maksymalnym priorytetem.
// Jezeli maksimum jest w glowie, zwraca nullptr.
ListNode* LinkedListPQ::findMaxPrev() const {
        ListNode* maxPrev = nullptr;
        ListNode* maxNode = head;
        ListNode* prev    = nullptr;
        ListNode* curr    = head;

        while (curr) {
            if (curr->priority > maxNode->priority) {
                maxNode = curr;
                maxPrev = prev;
            }
            prev = curr;
            curr = curr->next;
        }
        return maxPrev;
    }

LinkedListPQ::LinkedListPQ() : head(nullptr), sz(0) {}

LinkedListPQ::~LinkedListPQ() {
        while (head) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

// Wstawia element na poczatek listy
void LinkedListPQ::insert(int value, int priority) {
        ListNode* node = new ListNode{value, priority, head};
        head = node;
        sz++;
    }

// Usuwa i zwraca element o najwyzszym priorytecie
ListNode LinkedListPQ::extractMax() {
        if (!head) throw std::runtime_error("Kolejka jest pusta");

        ListNode* maxPrev = findMaxPrev();
        ListNode* maxNode;

        if (maxPrev == nullptr) {
            maxNode = head;
            head    = head->next;
        } else {
            maxNode        = maxPrev->next;
            maxPrev->next  = maxNode->next;
        }

        ListNode result = *maxNode;
        delete maxNode;
        sz--;
        return result;
    }

// Zwraca element o najwyzszym priorytecie bez usuwania 
ListNode LinkedListPQ::peek() const {
        if (!head) throw std::runtime_error("Kolejka jest pusta");

        ListNode* maxPrev = findMaxPrev();
        ListNode* maxNode = (maxPrev == nullptr) ? head : maxPrev->next;
        return *maxNode;
    }

// Zmienia priorytet elementu o podanej wartosci 
void LinkedListPQ::modifyKey(int value, int newPriority) {
        ListNode* curr = head;
        while (curr) {
            if (curr->value == value) {
                curr->priority = newPriority;
                return;
            }
            curr = curr->next;
        }
        throw std::runtime_error("Wartosc nie znaleziona");
    }

int LinkedListPQ::size() const { return sz; }
bool LinkedListPQ::empty() const { return sz == 0; }
