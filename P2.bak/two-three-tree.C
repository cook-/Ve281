#ifndef TWO_THREE_TREE_C
#define TWO_THREE_TREE_C

#include <iostream>
using namespace std;

template <class Key, class Val>
Val* Tree<Key, Val>::search(Key key) const {
    return search_help(root, key);
}

template <class Key, class Val>
static Val* search_help(Node<Key, Val> *node, Key key) {
    if (node == NULL)
        return NULL;

    if (key < *(node->lkey))
        return search_help(node->left, key);
    else if (key == *(node->lkey))
        return node->lval;
    else {
        if (node->rkey == NULL)
            return search_help(node->center, key);
        else {
            if (key == *(node->rkey))
                return node->rval;
            else
                return search_help(node->right, key);
        }
    }
}

template <class Key, class Val>
bool Tree<Key, Val>::insert(Key *key, Val *val) {
    if (isEmpty()) {   // if tree is empty
        root = new Node<Key, Val>;
        root->lkey = key;
        root->lval = val;
        root->rkey = NULL;
        root->rval = NULL;
        root->left = NULL;
        root->center = NULL;
        root->right = NULL;
        return true;
    }
    
    if (search(*key) != NULL)
        return false;

    Node<Key, Val>* pN1 = NULL; 
    Node<Key, Val>* pN2 = NULL;

    if (insert_help(root, key, val, &pN1, &pN2)) {
        root = new Node<Key, Val>;
        root->lkey = key;
        root->lval = val;
        root->left = pN1;
        root->center = pN2;
    }

    return true;
}

template <class Key, class Val>
static bool insert_help(Node<Key, Val>* pNode, Key *&key, Val *&val,
                        Node<Key, Val>** ppN1, Node<Key, Val>** ppN2) {
    Node<Key, Val>* pN1 = NULL;
    Node<Key, Val>* pN2 = NULL;
    Node<Key, Val>* pNew = NULL;

    Key* keys[3];
    Val* vals[3];
    Node<Key, Val>* pC[4];  // a placeholder when rearranging the four nodes

    // *pNode is an internal node
    if (pNode->left != NULL) {

        // recurse down the first child
        if (*key < *(pNode->lkey)) {
            if (!insert_help(pNode->left, key, val, &pN1, &pN2))
                return false;
            if (pNode->rkey == NULL) {  // *pNode is a 2-node
                pNode->rkey = pNode->lkey;
                pNode->rval = pNode->lval;
                pNode->lkey = key;
                pNode->lval = val;
                pNode->right = pNode->center;
                pNode->center = pN2;
                pNode->left = pN1;
                return false;
            }
            else {  // *pNode is a 3-node
                keys[0] = key;
                keys[1] = pNode->lkey;
                keys[2] = pNode->rkey;
                vals[0] = val;
                vals[1] = pNode->lval;
                vals[2] = pNode->rval;
                pC[0] = pN1;
                pC[1] = pN2;
                pC[2] = pNode->center;
                pC[3] = pNode->right;
            }
        }
    
        // *pNode is a 3-node, recurse down the center or right child?
        else if (pNode->rkey != NULL) {

            // recurse down the center child
            if (*key < *(pNode->rkey)) {
                if (!insert_help(pNode->center, key, val, &pN1, &pN2))
                    return false;

                // split this node
                keys[0] = pNode->lkey;
                keys[1] = key;
                keys[2] = pNode->rkey;
                vals[0] = pNode->lval;
                vals[1] = val;
                vals[2] = pNode->rval;
                pC[0] = pNode->left;
                pC[1] = pN1;
                pC[2] = pN2;
                pC[3] = pNode->right;
            }

            // recurse down the right child
            else if (*key > *(pNode->rkey)) {
                if (!insert_help(pNode->right, key, val, &pN1, &pN2))
                    return false;
                keys[0] = pNode->lkey;
                keys[1] = pNode->rkey;
                keys[2] = key;
                vals[0] = pNode->lval;
                vals[1] = pNode->rval;
                vals[2] = val;
                pC[0] = pNode->left;
                pC[1] = pNode->center;
                pC[2] = pN1;
                pC[3] = pN2;
            }

            else {
                pNode->rkey = key;
                pNode->rval = val;
                return false;
            }
        }

        else if (*key > *(pNode->lkey)) {
            if (!insert_help(pNode->center, key, val, &pN1, &pN2))
                return false;
            pNode->rkey = key;
            pNode->rval = val;
            pNode->center = pN1;
            pNode->right = pN2;
            return false;
        }

        else {
            pNode->lkey = key;
            pNode->lval = val;
            return false;
        }
    }

    // recursive base case, hit a leaf node
    else {

        // 2-node leaf
        if (pNode->rkey == NULL) {
            if (*key > *(pNode->lkey)) { // new key bigger than *lkey
                pNode->rkey = key;
                pNode->rval = val;
            }
            else if (*key < *(pNode->lkey)) { // new key smaller than *lkey
                pNode->rkey = pNode->lkey;
                pNode->rval = pNode->lval;
                pNode->lkey = key;
                pNode->lval = val;
            }
            else // existing key
                pNode->lval = val;

            // no fix-up operations required back out of recursion
            return false;
        }

        // 3-node leaf
        if (*key < *(pNode->lkey)) { // new key smaller than *lkey
            keys[0] = key;
            keys[1] = pNode->lkey;
            keys[2] = pNode->rkey;
            vals[0] = val;
            vals[1] = pNode->lval;
            vals[2] = pNode->rval;
        }
        else if (*key == *(pNode->lkey)) { // existing key
            pNode->lval = val;
            return false;
        }
        else if (*key < *(pNode->rkey)) { // new key smaller than *rkey
            keys[0] = pNode->lkey;
            keys[1] = key;
            keys[2] = pNode->rkey;
            vals[0] = pNode->lval;
            vals[1] = val;
            vals[2] = pNode->rval;
        }
        else if (*key == *(pNode->rkey)) { // existing key
            pNode->rval = val;
            return false;
        }
        else { // new key bigger than *rkey
            keys[0] = pNode->lkey;
            keys[1] = pNode->rkey;
            keys[2] = key;
            vals[0] = pNode->lval;
            vals[1] = pNode->rval;
            vals[2] = val;
        }

        // leave all children pointer NULL
        pC[0] = NULL;
        pC[1] = NULL;
        pC[2] = NULL;
        pC[3] = NULL;
    }

    // replace the contents of pNode to contain the first two child nodes
    pNode->lkey = keys[0];
    pNode->lval = vals[0];
    pNode->rkey = NULL;
    pNode->rval = NULL;
    pNode->left = pC[0];
    pNode->center = pC[1];
    pNode->right = NULL;

    // create a new node to contain the last two nodes
    pNew = new Node<Key, Val>;
    pNew->lkey = keys[2];
    pNew->lval = vals[2];
    pNew->rkey = NULL;
    pNew->rval = NULL;
    pNew->left = pC[2];
    pNew->center = pC[3];
    pNew->right = NULL;

    // return information about pNode & pNew to caller
    key = keys[1];
    val = vals[1];
    *ppN1 = pNode;
    *ppN2 = pNew;

    return true;
}

template <class Key, class Val>
Val* Tree<Key, Val>::remove(Key key) {
    if (remove_help(root, key)) {
        Node<Key, Val>* victim = root;
        root = root->left;
        victim->left = NULL;
        delete victim;
    }
    return search(key);
}

template <class Key, class Val>
static bool remove_help(Node<Key, Val>* pNode, Key &key) {
    if (pNode->left != NULL) {
        if (key < *(pNode->lkey)) {
            if (remove_help(pNode->left, key))
                return fixFirst(pNode);
        }

        else if (key == *(pNode->lkey)) {
            Key *succKey;
            Val *succVal;
            if (inOrderSuccessor(pNode->center, succKey, succVal)) {
                pNode->lkey = succKey;
                pNode->lval = succVal;
                if (fixInOrderSuccessor(pNode->center))
                    return fixSecond(pNode);
            }
            else {
                pNode->lkey = succKey;
                pNode->lval = succVal;
            }
        }

        else if (pNode->rkey != NULL) {
            if (key < *(pNode->rkey)) {
                if (remove_help(pNode->center, key))
                    return fixSecond(pNode);
            }
            else if (key > *(pNode->rkey)) {
                if (remove_help(pNode->right, key)) {
                    fixThird(pNode);
                    return false;
                }
            }
            else {
                Key *succKey;
                Val *succVal;
                if (inOrderSuccessor(pNode->right, succKey, succVal)) {
                    pNode->rkey = succKey;
                    pNode->rval = succVal;
                    if (fixInOrderSuccessor(pNode->right)) {
                        fixThird(pNode);
                        return false;
                    }
                }
                else {
                    pNode->rkey = succKey;
                    pNode->rval = succVal;
                }
            }
        }

        else {
            if (remove_help(pNode->center, key))
                return fixSecond(pNode);
        }
    }

    // hit a leaf node
    else {
        if (key == *(pNode->lkey)) {
            pNode->lkey = pNode->rkey;
            pNode->lval = pNode->rval;
            pNode->rkey = NULL;
            pNode->rval = NULL;
            return (pNode->rkey == NULL);
        }
        else if (pNode->rkey != NULL && key == *(pNode->rkey)) {
            pNode->rkey = NULL;
            pNode->rval = NULL;
        }
    }

    return false;
}

template <class Key, class Val>
static bool inOrderSuccessor(Node<Key, Val>* &pNode, Key *&key, Val *&val) {
    while (pNode->left != NULL)
        pNode = pNode->left;

    key = pNode->lkey;
    val = pNode->lval;
    pNode->lkey = pNode->rkey;
    pNode->lval = pNode->rval;
    pNode->rkey = NULL;
    pNode->rval = NULL;

    return (pNode->lval == NULL);
}

template <class Key, class Val>
static bool fixInOrderSuccessor(Node<Key, Val>* pNode) {
    if (pNode->left == NULL)
        return true;

    if (fixInOrderSuccessor(pNode->left))
        return fixFirst(pNode);

    return false;
}

template <class Key, class Val>
static bool fixFirst(Node<Key, Val>* pNode) {
    Node<Key, Val> *pC1 = pNode->left;
    Node<Key, Val> *pC2 = pNode->center;

    if (pC2->rkey != NULL) { // *pC2 is a 3-node
        pC1->lkey = pNode->lkey;
        pC1->lval = pNode->lval;
        pNode->lkey = pC2->lkey;
        pNode->lval = pC2->lval;
        pC2->lkey = pC2->rkey;
        pC2->lval = pC2->rval;
        pC2->rkey = NULL;
        pC2->rval = NULL;

        pC1->center = pC2->left;
        pC2->left = pC2->center;
        pC2->center = pC2->right;
        pC2->right = NULL;

        return false;
    }

    pC1->lkey = pNode->lkey;
    pC1->lval = pNode->lval;
    pC1->rkey = pC2->lkey;
    pC1->rval = pC2->lval;
    pC2->lkey = NULL;
    pC2->lval = NULL;

    pC1->center = pC2->left;
    pC1->right = pC2->center;

    pC2->left = NULL;
    pC2->center = NULL;
    pC2->right = NULL;

    pNode->lkey = pNode->rkey;
    pNode->lval = pNode->rval;
    pNode->rkey = NULL;
    pNode->rkey = NULL;
    pNode->center = pNode->right;
    pNode->right = NULL;

    delete pC2;

    return (pNode->lval == NULL);
}

template <class Key, class Val>
static bool fixSecond(Node<Key,Val> *pNode)
{
    Node<Key,Val> *pC1 = pNode->left;
    Node<Key,Val> *pC2 = pNode->center;
    
    if (pC1->rkey !=NULL) {
        pC2->lkey = pNode->lkey;
    	pC2->lval = pNode->lval;
        pNode->lkey = pC1->rkey;
    	pNode->lval = pC1->rval;
        pC1->rkey = NULL;
        pC1->rkey = NULL;

        pC2->center = pC2->left;
        pC2->left = pC1->right;
        pC1->right = NULL;

        return false;
    }
    
    if (pNode->rkey !=NULL) {
        pC1->rkey = pNode->lkey;
	    pC1->rval = pNode->lval;
        pNode->lkey = pNode->rkey;
    	pNode->lval = pNode->rval;
        pNode->rval =NULL;
        pNode->rkey = NULL;
        pC2->lkey = NULL;
        pC2->lval = NULL;

        pC1->center = pC2->left;
        pC1->right = pC2->center;
        pC2->left = NULL;
        pC2->center = NULL;

	    pNode->center=pNode->right;
        pNode->right= NULL;

        delete pC2;

        return false;
    }

    pC1->rkey = pNode->lkey;
	pC1->rval = pNode->lval;
    pNode->lkey=NULL;
    pNode->lval=NULL;

	pC1->right = pC2->left;
	pC2->left = NULL;
	pNode->center = NULL;

	delete pC2;

	return true;
}

template <class Key, class Val>
static void fixThird(Node<Key, Val>* pNode) {
    Node<Key, Val>* pC2 = pNode->center;
    Node<Key, Val>* pC3 = pNode->right;

    if (pC2->rkey != NULL) {
        pC3->lkey = pNode->rkey;
        pC3->lval = pNode->rval;
        pNode->rkey = pC2->rkey;
        pNode->rval = pC2->rval;
        pC2->rkey = NULL;
        pC2->rval = NULL;

        pC3->center = pC3->left;
        pC3->left = pC2->right;
        pC2->right = NULL;
    }

    else {
        pC2->rkey = pNode->rkey;
        pC2->rval = pNode->rval;
        pNode->rkey = NULL;
        pNode->rval = NULL;

        pC2->right = pC3->left;
        pC3->left = NULL;
        pNode->right = NULL;

        delete pC3;
    }
}

template <class Key, class Val>
void Tree<Key, Val>::inOrderPrint(ostream &os) const {
    inOrderPrint_help(os, root);
}

template <class Key, class Val>
static void inOrderPrint_help(ostream &os, Node<Key, Val>* pNode) {
    static int level = -1;
    level++;
    if (pNode == NULL) {
        level--;
        return;
    }

    inOrderPrint_help(os, pNode->left);

    for (int i = 0; i != 4*level; ++i)
        os << ' ';
    os << *(pNode->lval) << endl;
    if (pNode->left == NULL && pNode->rkey != NULL) {
        for (int i = 0; i != 4*level; ++i)
            os << ' ';
        os << *(pNode->rval) << endl;
    }
    
    inOrderPrint_help(os, pNode->center);

    if (pNode->right != NULL) {
        for (int i = 0; i != 4*level; ++i)
            os << ' ';
        os << *(pNode->rval) << endl;

        inOrderPrint_help(os, pNode->right);
    }
    level--;
    return;
}

template <class Key, class Val>
Tree<Key, Val>::Tree(): root(NULL) {
}

template <class Key, class Val>
Tree<Key, Val>::Tree(const Tree &t) {

}

template <class Key, class Val>
Tree<Key, Val>& Tree<Key, Val>::operator=(const Tree &t) {

}

template <class Key, class Val>
Tree<Key, Val>::~Tree() {
    removeAll(root);
}

template <class Key, class Val>
static void removeAll(Node<Key, Val>* pNode) {
    if (pNode == NULL)
        return;
    else {
        removeAll(pNode->left);
        removeAll(pNode->center);
        removeAll(pNode->right);
        delete pNode;
    }
}

#endif /* TWO_THREE_TREE_C */
