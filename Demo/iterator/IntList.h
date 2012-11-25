#ifndef INTLIST_H
#define INTLIST_H

#include <cstdlib>

class listIsEmpty {}; // An exception class

class ListIter;

struct node
{
    node *next;
    int   value;
};

class IntList
{
    node *first;
    void removeAll();
    void copyList(node *list);

public:
    bool isEmpty();
    // EFFECTS: returns true if list is empty, false otherwise
    void insert(int v);
    // MODIFIES: this
    // EFFECTS: inserts v into the front of the list
    int remove();
    // MODIFIES: this
    // EFFECTS: if list is empty, throw listIsEmpty.
    //          Otherwise, remove and return the first 
    //          element of the list

    ListIter begin();
    ListIter end();

    void print();
    // MODIFIES: cout
    // EFFECTS: print the int list

    IntList();
    // default constructor
    IntList(const IntList& l);
    // copy constructor
    ~IntList();
    // destructor
    IntList &operator=(const IntList &l); 
    // assignment operator
};

class ListIter
{
    node *ptr;

public:
    ListIter(node *n = NULL):ptr(n){}

    bool operator!=(const ListIter &iter)
    { return ptr != iter.ptr; }

    // allows data dereferencing using *
    int& operator* ()
    { return ptr->value; }

    void operator++(int) // itr++
    { ptr = ptr->next; }

    void operator++() // ++itr
    { ptr = ptr->next; }

};

#endif
