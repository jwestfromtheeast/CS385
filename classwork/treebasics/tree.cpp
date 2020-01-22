// A tree is a directed acyclic graph
// A binary tree is one in which there are 2 children (possibly null)
// For every non-null node. A binary search tree is a binary tree
// where each node in the left subtree has a key < the value at the root
// and each node in the right subtree has a key > the value at the root
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
};

// root left right
void preorder(Node *n) {
    if (n) {
        cout << n->key;
        preorder(n->left);
        preorder(n->right);
    }
}

// left root right
void inorder(Node *n) {
    if (n) {
        inorder(n->left);
        cout << n->key;
        inorder(n->right);
    }
}

// left right root
void postorder(Node *n) {
    if (n) {
        postorder(n->left);
        postorder(n->right);
        cout << n->key;
    }
}

