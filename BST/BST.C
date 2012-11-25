#include "BST.h"

node * BST::search(node *root, Key k) {
    if (root == NULL)
        return NULL;
    if (k == root->item.key)
        return root;
    else if (k < root->item.key)
        return search(root->left, k);
    else (k > root->item.key)
        return search(root->right, k);
}

void BST::insert(node *&root, Item item) {
    if (root == NULL)
        return new node(item);
    if (k < root->item.key)
        return insert(root->left, item);
    else if (k > root->item.key)
        return insert(root->right, item);
}

void BST::remove(node *&root, Key k) {
    if (root == NULL)
        return;
    if (k < root->item.key)
        return remove(root->left, k);
    else if (k > root->item.key)
        return remove(root->right, k);
    else {
        if (root->left == NULL && root->right == NULL) {    // leaf
            delete root;
            root = NULL;
        }
        else if (root->right == NULL) {  // one-degree node
            node *tmp = root;
            root = root->left;
            delete tmp;
        else if (root->left == NULL) {  // one-degree node
            node *tmp = root;
            root = root->right;
            delete tmp;
        }
        else {  // two-degree node
            node *&replace = findMax(root->left);
            root->item = replace->item;
            node *tmp = replace;
            replace = replace->left;    // the largest key must be in
                                        // a leaf node or one-degree node
            delete tmp;
        }
        return;
    }
}

node * BST::findMax(node *&root) {
    if (root == NULL)
        return NULL;
    if (root->right == NULL)
        return root;
    else
        return findMax(root->right);
}
