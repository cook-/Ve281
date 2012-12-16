#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "node.h"
#include "edge.h"
#include <vector>
#include <iostream>

using namespace std;

class Graph {
    vector<Node*> nodes;
    vector<Edge*> edges;
    Node* src;
    Node* dest;

public:
    Graph();
    ~Graph();
    
    bool isEmpty();

    void setSrc(int index);
    Node* getSrc();
    void setDest(int index);
    Node* getDest();

    void addNode(Node *np);
    Node* getNode(int index);
    int getNodeVectorSize();

    void addEdge(Edge *ep);
    Edge* getEdge(int index);
    int getEdgeVectorSize();

    void reInitialize();
};

#endif /* __GRAPH_H__ */
