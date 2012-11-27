#ifndef TWO_THREE_TREE_C
#define TWO_THREE_TREE_C

#include <iostream>
using namespace std;

template <class Key, class Val>
Val* Tree::search(Key key) const {
    return search_help(root, key);
}


template <class Key, class Val>
bool Tree::insert(Key *key, Val *val) {
    if (!root) {
        root = new Node<Key, Val>;
        root->lkey = key;
        root->lval = val;
        root->rkey = NULL;
        root->rval = val;
        root->left = NULL;
        root->center = NULL;
        root->right = NULL;
        return true;
    }
    return insert_help(root, key, val, root);
}

template <class Key, class Val>
Val* Tree::remove(Key key) {

}

template <class Key, class Val>
void Tree::inOrderPrint(ostream &os) const {

}

template <class Key, class Val>
Tree::Tree() {

}

template <class Key, class Val>
Tree::Tree(const Tree &t) {

}

template <class Key, class Val>
Tree::Tree &operator=(const Tree &t) {

}

template <class Key, class Val>
Tree::~Tree() {

}

template <class Key, class Val>
static Val* search_help(Node<Key, Val> *node, Key key) {
    if (!node) return NULL;

    if (key < node->lkey)
        return search_help(node->left, key);
    else if (key == node->lkey)
        return lval;
    else {
        if (!rkey || key < node->rkey)
            return search_help(node->center, key);
        else if (key == node->rkey)
            return rval;
        else
            return search_help(node->right, key);
    }
}

template <class Key, class Val>
static bool insert_help(Node<Key, Val> *&node, Key *key, Val *val,
                                            Node<Key, Val> *root) {
    if (!(node->left)) {    // is a leaf
        if (!(node->rkey)) {    // is a 2-node
            node->rkey = key;
            node->rval = val;
        }
        else                    // is a 3-node
            split(node, key, val, root);
        return true;
    }

    if (*key < node->lkey)
        return insert_help(node->left, key, val);
    else if (*key == node->lkey)
        return false;
    else {
        if (!rkey || *key < node->rkey)
            return insert_help(node->center, key, val);
        else if (*key == node->rkey)
            return false;
        else
            return insert_help(node->right, key, val);
    }
}

template <class Key, class Val>
static split(Node<Key, Val> *&node, Key key, Val val, Node<Key, Val> *root) {
    Node<Key, Val> *parent = NULL;
    if (node == root)
        parent = new Node<Key, Val>;
    else
        parent = search_parent(node, root);

    
}

template <class Key, class Val>
static Node<Key, Val>* search_parent(Node<Key, Val> *node, Node<Key, Val> *root) {
    if 
}

#endif /* TWO_THREE_TREE_C */
