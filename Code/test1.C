#include "binary_search.h"
#include "linear_search.h"
#include <iostream>

int
main()
{
	int MAX = 100000000;
	int iArr[MAX];
	for (int i = 0; i != MAX; ++i) {
		iArr[i] = i;
	}

	int K = 92;
	binary(iArr, MAX, K);

	return 0;
}
