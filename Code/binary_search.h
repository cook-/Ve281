// Return the position of an element in sorted array "A" of
// size "n" with value "K". If "K" is not in "A", return
// the value "n".

int
binary(int A[], int n, int K)
{
	int l = -1;
	int r = n;
	while (l + 1 != r) {
		int m = (l + r)/2;
		if (K < A[m]) r = m;
		if (K == A[m]) return m;
		if (K > A[m]) l = m;
	}
	return n;
}
