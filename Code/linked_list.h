struct node {
	node *next;
	int value;
};

class listIsEmpty {};

class LinkedList {
	node *first;
public:
	bool isEmpty();
	void insertFirst(int v);
	int removeFirst();
	int getSize();
	void appendNode(node *n);
	int removeNode(node *n);
	void reverse();
	LinkedList();
	LinkedList(const LinkedList& l);
	~LinkedList();
	LinkedList& opeartor=(const LinkedList& l);
};
