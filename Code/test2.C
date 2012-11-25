#include "binary_search.h"
#include "linear_search.h"
#include <iostream>

int
main()
{
	int MAX = 1000000000;
	int iArr[MAX];
	for (int i = 0; i != MAX; ++i) {
		iArr[i] = i;
	}

	int K = 92;
	linear(iArr, MAX, K);

	return 0;
}
