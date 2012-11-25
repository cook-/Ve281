#include <iostream>
using namespace std;

int removeKey(int a[], unsigned int size, int key) {
	for (int i = 0; i != size; ++i) {
		if (a[i] == key) {
			for (int j = i; j != size-1; ++j) {
				a[j] = a[j+1];
			}
			size--;
		}
	}
	return size;
}

void print(int a[], unsigned int size) {
	for (int i = 0; i != size; ++i) {
		cout << a[i] << ' ';
	}
	cout << endl;
}

int main()
{
	int a[5] = { 4, 2, -5, 2, 9 };
	print(a, 5);
	int new_size = removeKey(a, 5, 2);
	print(a, new_size);
	return 0;
}


