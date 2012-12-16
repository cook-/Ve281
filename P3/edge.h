#ifndef __EDGE_H__
#define __EDGE_H__

#include <vector>
#include <iostream>

using namespace std;

class Node;

class Edge {
    Node *start;    // The start node of the edge
    Node *end;      // The end node of the edge
    int weight;     // The weight of the edge

public:
    Edge();
    Edge(Node *s, Node *d, int w);
    Node* getStart();
    Node* getEnd();
    int getWeight();

    friend class Node;
    friend class Graph;
    friend ostream& operator<<(ostream &os, const Edge &e);
    //
};

#endif /* __EDGE_H__ */
