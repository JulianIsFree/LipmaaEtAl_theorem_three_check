#include "hypothesis.h"

void print_bit(const int n, const int N)
{
	cout << setw((int)log2(N)) << n <<": ";
	for (int i = 0; i < N; ++i)
		cout << ((n >> (N - i - 1)) & 1);
	cout << endl;
}

int check_hypothesis(const int N, const int b, const int c, Matrix matricies[])
{
	const int mask = (1 << N) - 1;
	int dif = (b & c) ^ c;

#ifdef VISUAL_DEBUG
	print_bit(b, N);
	print_bit(c, N);
	print_bit(dif, N);
#endif

	for (int i = 0; i < N; ++i)
	{
		if ((dif >> (N - i - 1)) & 1)
		{
			int _b = b ^ (1 << i);
			cout << adp(N, 0, _b, c, matricies) << endl;
		}
	}

	return 1;
}
