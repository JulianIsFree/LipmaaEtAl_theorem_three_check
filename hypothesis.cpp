#include "hypothesis.h"

typedef struct _Max
{
	int first;
	int second;
} Max;

Max find_max(Matrix v, int matrix)
{
	int f = 0;
	int s = 0;
	for (int i = 0; i < 4; ++i)
	{
		int j = columns[matrix][i];
		int e = v.arr[j][0];

		if (e >= f)
		{
			s = f;
			f = e;
		}
		else if (e >= s)
			s = e;
	}

	return { f , s };
}



void multi_sqnc(int sqnc[], const int len, Matrix matricies[], Matrix &result)
{
	Matrix sub_result;
	init_identity_matrix(sub_result);

	for (int i = len - 1; i >= 0; --i)
	{
		multiply(sub_result, matricies[sqnc[i]], result);
		copy_matrix(result, sub_result);
	}

	multiply(sub_result, matricies[9], result);
	deinit_matrix(sub_result);
}

char is_sqnc_03_max_bigger(FILE * fout, int main_sqnc[], int morph_sqnc[], const int N, const int n, Matrix matricies[])
{
	if (n >= N)
		return 1;

	Matrix main, morph;
	
	init_matrix(main);
	init_matrix(morph);
	
	char result = 1;

	for (int i = 0; i < 8; ++i)
	{
		main_sqnc[n] = i;
		morph_sqnc[n] = i & 1 ? 3 : 0;

		if (!is_sqnc_03_max_bigger(fout, main_sqnc, morph_sqnc, N, n + 1, matricies))
			result = 0;

		multi_sqnc(main_sqnc, n + 1, matricies, main);
		multi_sqnc(morph_sqnc, n + 1, matricies, morph);

		Max main_max = find_max(main, i);
		Max morph_max = find_max(morph, i & 1 ? 3 : 0);

		if (main_max.first > morph_max.first || main_max.second > morph_max.second)
		{

			for (int j = n; j >= 0; --j)
				fprintf(fout, "%d ", main_sqnc[j]);
			fprintf(fout, "\n");
			for (int j = n; j >= 0 ; --j)
				fprintf(fout, "%d ", morph_sqnc[j]);
			fprintf(fout, "\n\n");
			result = 0;
		}
	}

	deinit_matrix(main);
	deinit_matrix(morph);
	return result;
}

int find_tail(int morph_sqnc[], int n)
{
	int curr = morph_sqnc[n];

	while (n >= 0 && morph_sqnc[n] == curr)
		--n;

	return n;
}

double get_main_sqnc_sum(Matrix main, int m, int n)
{
	double sum = main.arr[m][0];
	
	for (int i = 0; i < 4; ++i)
	{
		if (columns[m][i] == m)
			continue;

		sum += (double)main.arr[columns[m][i]][0] / 4;
	}

	Max max = find_max(main, m);
	sum -= (double)max.first / 4;

	return sum;
}

char check(int main_sqnc[], int morph_sqnc[], int n, Matrix matricies[])
{
	if (n <= 0)
		return 1;

	Matrix main, morph;

	init_matrix(main);
	init_matrix(morph);
	
	while (n >= 0)
	{
		while (n > 0 && 
			morph_sqnc[n] == morph_sqnc[n - 1])
			n--;

		int k = n - 1;
		while (k > 0 && 
			morph_sqnc[k] == morph_sqnc[k - 1])
			k--;

		if (k <= 0 || n <= 0)
		{
			deinit_matrix(main);
			deinit_matrix(morph);
			return 1;
		}

		multi_sqnc(main_sqnc, n, matricies, main);
		multi_sqnc(morph_sqnc, n, matricies, morph);
		
		Max morph_max = find_max(morph, morph_sqnc[n]);
		double main_sum = get_main_sqnc_sum(main, main_sqnc[n], n);
		if (morph_max.second >= main_sum)
			return 1;
		else 
			return 0;
	}
	
	deinit_matrix(main);
	deinit_matrix(morph);
	return 1;
}

char is_sqnc_03_sum_max_bigger(FILE * fout, int main_sqnc[], int morph_sqnc[], const int N, const int n, Matrix matricies[])
{ 
	// morph_sqnc[0] = 3
	if (n >= N)
		return 1;
	char result = 1;

	for (int i = 0; i < 8; ++i)
	{
		main_sqnc[n] = i;
		morph_sqnc[n] = i & 1 ? 3 : 0;

		if (morph_sqnc[n] != morph_sqnc[n - 1])
			if (!check(main_sqnc, morph_sqnc, n, matricies))
			{
				for (int j = n; j >= 0; --j)
					fprintf(fout, "%d ", main_sqnc[j]);
				fprintf(fout, "\n");
				for (int j = n; j >= 0; --j)
					fprintf(fout, "%d ", morph_sqnc[j]);
				fprintf(fout, "\n\n");
				result = 0;
			}

		if (!is_sqnc_03_sum_max_bigger(fout, main_sqnc, morph_sqnc, N, n + 1, matricies))
			result = 0;
	}

	return result;
}

double adp_sqnc(int words[], int len, Matrix matricies[])
{
	double result = 0;

	Matrix prev, curr;
	init_matrix(prev);
	init_matrix(curr);
	copy_matrix(matricies[8], prev);

	for (int i = len - 1; i >= 0; --i)
	{
		multiply(prev, matricies[words[i]], curr);
		copy_matrix(curr, prev);
	}
	
	result = curr.arr[0][0];
	result /= 1 << (2 * len);


	deinit_matrix(prev);
	deinit_matrix(curr);

	return result;
}
