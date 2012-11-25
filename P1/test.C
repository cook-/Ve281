#include <iostream>
#include "queue.h"
#include "queue.C"
using namespace std;

int main(int argc, char *argv[])
{
    Queue<int> queue;
    int *ip;

	for (int i = 0; i != 100; ++i) {
		ip = new int(i);
	    queue.enqueue(ip);
	}


	Queue<int> another_queue = queue;
	while (!another_queue.isEmpty()) {
		ip = another_queue.dequeue();
		cout << *ip << ' ';
		delete ip;
	}
	cout << endl;

	return 0;
}
