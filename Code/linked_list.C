#include "linked_list.h"
using namespace std;

bool LinkedList::isEmpty() {
	return !first;
}

void LinkedList::insertFirst(int v) {
	node *np = new node;
	np->next = first;
	np->value = v;
	first = np;
}

int LinkedList::removeFirst() {
	if (isEmpty()) {
		listIsEmpty e;
		throw &e;
	}
	node *victim = first;
	first = victim->next;
	int result = victim->value;
	delete victim;
	return result;
}

int LinkedList::getSize() {
	int cnt = 0;
	node *curr = first->next;
	while (curr) {
		curr = curr->next;
		++cnt;
	}
	return cnt;
}

void LinkedList::appendNode(node *n) {
	if (isEmpty()) {
		first = n;
		return;
	}
	node *curr = first;
	while (curr->next) {
		curr = curr->next;
	}
	curr->next = n;
}

int LinkedList::removeNode(node *n) {
	int value;
	if (first == n) {
		value = removeFirst();
		return value;
	}
	node *curr = first;
	while (curr->next != n) {
		curr = curr->next;
	}
	curr->next = n->next;
	value = n->value;
	delete n;
	return value;
}

void LinkedList::reverse() {
	node *curr = first;
	node *prev = NULL;
	node *next = NULL;
	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	first = prev;
}

LinkedList(): first(0) {}

LinkedList(const LinkedList& l) {
	
	this->first = l.first;
}

~LinkedList() {}

LinkedList& operator=(const LinkedList& l) {
	this->first
}
