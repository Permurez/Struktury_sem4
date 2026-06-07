#include "avl_tree.hpp"

#include <algorithm>

AVLNode::AVLNode(int k, int v)
    : key(k), value(v), height(1), left(nullptr), right(nullptr) {}

namespace {
int height(AVLNode* n) { return n ? n->height : 0; }
int balance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }

void updateHeight(AVLNode* n) {
    n->height = 1 + std::max(height(n->left), height(n->right));
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* rebalance(AVLNode* n) {
    updateHeight(n);
    int b = balance(n);
    if (b > 1) {
        if (balance(n->left) < 0) n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (b < -1) {
        if (balance(n->right) > 0) n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

AVLNode* insertNode(AVLNode* n, int key, int value) {
    if (!n) return new AVLNode(key, value);
    if (key < n->key) n->left = insertNode(n->left, key, value);
    else if (key > n->key) n->right = insertNode(n->right, key, value);
    else {
        n->value = value;
        return n;
    }
    return rebalance(n);
}

AVLNode* minNode(AVLNode* n) {
    return n->left ? minNode(n->left) : n;
}

AVLNode* removeNode(AVLNode* n, int key, bool& found) {
    if (!n) return nullptr;
    if (key < n->key) n->left = removeNode(n->left, key, found);
    else if (key > n->key) n->right = removeNode(n->right, key, found);
    else {
        found = true;
        if (!n->left || !n->right) {
            AVLNode* child = n->left ? n->left : n->right;
            delete n;
            return child;
        }
        AVLNode* succ = minNode(n->right);
        n->key = succ->key;
        n->value = succ->value;
        n->right = removeNode(n->right, succ->key, found);
    }
    return rebalance(n);
}

void destroyTree(AVLNode* n) {
    if (!n) return;
    destroyTree(n->left);
    destroyTree(n->right);
    delete n;
}
} // namespace

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::insert(int key, int value) {
    root = insertNode(root, key, value);
}

bool AVLTree::remove(int key) {
    bool found = false;
    root = removeNode(root, key, found);
    return found;
}

void AVLTree::clear() {
    destroyTree(root);
    root = nullptr;
}
