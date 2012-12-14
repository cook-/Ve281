#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <iostream>

using namespace std;

class Edge;

class Node {
    int index;              // The index of the node
    vector<Edge*> outEdges; // The outgoing edges
    vector<Edge*> inEdges;  // The incoming edges
    bool explored;
    int value;
    Node *prev; // The previous node on the shortest path

public:
    Node();
    Node(int ind);

    friend class Edge;
    friend class Graph;
    friend ostream& operator<<(ostream &os, const Node &v);
    //
};

#endif /* __NODE_H__ */
