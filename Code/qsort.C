#include <cstdio>

int d[100];

void qsort(int l, int r)
{
	int mid = d[(r +l) >> 1], i = l, j = r, temp;
	if (l >= r)
		return;
	while (i < j)
	{	
		while (d[i] < mid)
			i++;
		while (d[j] > mid)
			j--;
		if (i <= j)
		{
			temp = d[i];
			d[i] = d[j];
			d[j] = temp;
			i++;
			j--;
		}
	}
		qsort(l, j);
		qsort(i, r);
}


int main()
{
	int n;
	qsort(0, n - 1);
	return 0;
}
