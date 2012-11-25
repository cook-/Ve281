#ifndef __BST__
#define __BST__

struct node {
    Item item;
    node *left;
    node *right;
};

struct Item {
    Key key;
    Val value;
};

class BST {
public:
    node *search(node *root, Key k);
    void insert(node *&root, Item item);
    node *remove(node *&root, Key k);
private:
    node *root;
    node *findMax(node *&root)
};

#endif /* __BST__ */
