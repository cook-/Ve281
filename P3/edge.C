#include "edge.h"
#include <iostream>
#include <vector>

using namespace std;

Edge::Edge()
: start(NULL), end(NULL), weight(0) { }

Edge::Edge(Node* s, Node* d, int w)
: start(s), end(d), weight(w) { }

Node* Edge::getStart() {
    return start;
}

Node* Edge::getEnd() {
    return end;
}

int Edge::getWeight() {
    return weight;
}

ostream& operator<<(ostream &os, const Edge &e) {
    os << "edge: " << e.weight << endl;
    //os << e.start->index << " --> " << e.end->index << endl;

    return os;
}
