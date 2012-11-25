// Return the position of an element in sorted array "A" of
// size "n" with value "K". If "K" is not in "A", return
// the value "n".

int
linear(int A[], int n, int K)
{
	for (int i = 0; i != n; ++i) {
		if (A[i] == K)
			return i;
	}
	return n;
}
