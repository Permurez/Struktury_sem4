#pragma once

// Węzeł drzewa AVL przechowujący parę klucz-wartość
struct AVLNode {
    int key, value, height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k, int v);
};

// Samobalansujące drzewo BST (AVL) – użyte jako kubełek w HashAVL
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(int key, int value);
    bool remove(int key);
    void clear();

private:
    AVLNode* root;
};
