#include "node.h"
#include <iostream>
#include <vector>

using namespace std;

Node::Node()
: index(-1), explored(false), value(-1), prev(NULL) { }

Node::Node(int ind)
: index(ind), explored(false), value(-1), prev(NULL) { }

vector<Edge*>& Node::getInEdgeVector() {
    return inEdges;
}

vector<Edge*>& Node::getOutEdgeVector() {
    return outEdges;
}

int Node::getIndex() {
    return index;
}

void Node::addOutEdge(Edge* ep) {
    outEdges.push_back(ep);
}

void Node::addInEdge(Edge* ep) {
    inEdges.push_back(ep);
}

int Node::getDistance() {
    return value;
}

void Node::setDistance(int dist) {
    value = dist;
}

Node* Node::getPrevNode() {
    return prev;
}

void Node::setPrevNode(Node* np) {
    prev = np;
}

bool Node::isExplored() {
    return explored;
}

void Node::markAsExplored() {
    explored = true;
}

ostream& operator<<(ostream &os, const Node &v) {
    os << "node " << v.index << endl;
    os << "    explored? ";
    if (!v.explored) os << "No!";
    else os << "Yes!";
    os << endl;

    return os;
}
