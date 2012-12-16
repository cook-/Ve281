#include "graph.h"
#include <iostream>
#include <vector>

using namespace std;

Graph::Graph()
: src(NULL), dest(NULL) { }

Graph::~Graph() {
    for (vector<Node*>::iterator iter = nodes.begin();
                                 iter != nodes.end(); ++ iter)
        delete *iter;

    for (vector<Edge*>::iterator iter = edges.begin();
                                 iter != edges.end(); ++iter)
        delete *iter;
}

bool Graph::isEmpty() {
    bool result = true;
    for (vector<Node*>::iterator iter = nodes.begin();
                                 iter != nodes.end(); ++iter)
        result = result && (*iter)->explored;
    return result;
}

void Graph::setSrc(int index) {
    src = nodes[index];
}

Node* Graph::getSrc() {
    return src;
}

void Graph::setDest(int index) {
    dest = nodes[index];
}

Node* Graph::getDest() {
    return dest;
}

void Graph::addNode(Node *np) {
    nodes.push_back(np);
}

Node* Graph::getNode(int index) {
    return nodes[index];
}

int Graph::getNodeVectorSize() {
    return nodes.size();
}

void Graph::addEdge(Edge *ep) {
    edges.push_back(ep);
}

Edge* Graph::getEdge(int index) {
    return edges[index];
}

int Graph::getEdgeVectorSize() {
    return edges.size();
}

void Graph::reInitialize() {
    for (vector<Node*>::const_iterator iter = nodes.begin();
                                       iter != nodes.end(); ++iter) {
        (*iter)->explored = false;
        (*iter)->value = -1;
        (*iter)->prev = NULL;
    }
}
