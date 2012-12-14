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
    Node* source;
    Node* dest;

public:
    Graph();
    ~Graph();
    //
};

#endif /* __GRAPH_H__ */
