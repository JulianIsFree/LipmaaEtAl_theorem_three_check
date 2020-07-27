#include "theorem3.h"

ARR_TYPE adp(const int N, const int a, const int b, const int c, Matrix matricies[])
{
	Matrix result, prev_result;
	init_matrix(result);
	init_matrix(prev_result);
	copy_matrix(matricies[8], prev_result);
	
	for (int i = 0; i < N; ++i)
	{
		unsigned int word = 
			(((a >> (N - i - 1)) & 1) << 2) ^
			(((b >> (N - i - 1)) & 1) << 1) ^
			(((c >> (N - i - 1)) & 1));

		multiply(prev_result, matricies[word], result);
		copy_matrix(result, prev_result);
	}

	multiply(prev_result, matricies[9], result);

	int r = result.arr[0][0];
	deinit_matrix(result);
	deinit_matrix(prev_result);
	return r;
}
