#pragma once
#include <algorithm>

// Węzeł drzewa AVL przechowujący parę klucz-wartość
struct AVLNode {
    int key, value, height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k, int v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

// Samobalansujące drzewo BST (AVL) – użyte jako kubełek w HashAVL
// Gwarantuje O(log k) dla insert/remove zamiast O(k) przy liście
class AVLTree {
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    void insert(int key, int value) { root = insert(root, key, value); }
    bool remove(int key)            { bool found = false; root = remove(root, key, found); return found; }
    void clear()                    { destroy(root); root = nullptr; }

private:
    AVLNode* root;

    // ── Pomocnicze ──────────────────────────────

    int height(AVLNode* n)  { return n ? n->height : 0; }
    int balance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }

    void updateHeight(AVLNode* n) {
        n->height = 1 + std::max(height(n->left), height(n->right));
    }

    // ── Rotacje ─────────────────────────────────

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x  = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left  = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y  = x->right;
        AVLNode* T2 = y->left;
        y->left  = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* rebalance(AVLNode* n) {
        updateHeight(n);
        int b = balance(n);
        if (b > 1) {
            if (balance(n->left) < 0) n->left = rotateLeft(n->left); // LR
            return rotateRight(n);                                     // LL
        }
        if (b < -1) {
            if (balance(n->right) > 0) n->right = rotateRight(n->right); // RL
            return rotateLeft(n);                                          // RR
        }
        return n;
    }

    // ── Operacje rekurencyjne ────────────────────

    AVLNode* insert(AVLNode* n, int key, int value) {
        if (!n) return new AVLNode(key, value);
        if      (key < n->key) n->left  = insert(n->left,  key, value);
        else if (key > n->key) n->right = insert(n->right, key, value);
        else                   { n->value = value; return n; } // aktualizacja
        return rebalance(n);
    }

    AVLNode* minNode(AVLNode* n) {
        return n->left ? minNode(n->left) : n;
    }

    AVLNode* remove(AVLNode* n, int key, bool& found) {
        if (!n) return nullptr;
        if      (key < n->key) n->left  = remove(n->left,  key, found);
        else if (key > n->key) n->right = remove(n->right, key, found);
        else {
            found = true;
            if (!n->left || !n->right) {
                AVLNode* child = n->left ? n->left : n->right;
                delete n;
                return child;
            }
            // Następnik in-order zastępuje usuwany węzeł
            AVLNode* succ = minNode(n->right);
            n->key   = succ->key;
            n->value = succ->value;
            n->right = remove(n->right, succ->key, found);
        }
        return rebalance(n);
    }

    void destroy(AVLNode* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
};
