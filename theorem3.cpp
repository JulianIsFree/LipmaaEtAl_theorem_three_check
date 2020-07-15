#include "theorem3.h"

void init_matrix(Matrix & m)
{
	m.arr = new ARR_TYPE*[MATRIX_EDGE];
	for (int i = 0; i < MATRIX_EDGE; ++i)
		m.arr[i] = new ARR_TYPE[MATRIX_EDGE];
	m.c = 0;
	m.r = 0;
}

void deinit_matrix(Matrix & m)
{
	for (int i = 0; i < MATRIX_EDGE; ++i)
		delete(m.arr[i]);
	delete(m.arr);

}

void copy_matrix(Matrix & source, Matrix & dest)
{
	ARR_TYPE ** arr = new ARR_TYPE*[MATRIX_EDGE];
	for (int i = 0; i < MATRIX_EDGE; ++i)
	{
		arr[i] = new ARR_TYPE[MATRIX_EDGE];
		memcpy(arr[i], source.arr[i], sizeof(ARR_TYPE) * MATRIX_EDGE);
	}

	dest.c = source.c;
	dest.r = source.r;
	dest.arr = arr;
}

int read_matricies(FILE * fin, Matrix matricies[])
{
	for (int i = 0; i < 10; ++i)
		init_matrix(matricies[i]);

	for (int i = 0; i < MATRIX_EDGE; ++i)
	{
		matricies[i].c = MATRIX_EDGE;
		matricies[i].r = MATRIX_EDGE;
		ARR_TYPE **arr = matricies[i].arr;

		for (int j = 0; j < MATRIX_EDGE; ++j)
		{
			arr[j] = new ARR_TYPE[MATRIX_EDGE];
			if (fscanf(fin, "%d %d %d %d %d %d %d %d", &arr[j][0], &arr[j][1], &arr[j][2], &arr[j][3], &arr[j][4], &arr[j][5], &arr[j][6], &arr[j][7]) != 8)
				return 0;
		}
	}

	//L matrix
	matricies[8].c = 8;
	matricies[8].r = 1;

	if (fscanf(fin, "%d %d %d %d %d %d %d %d", &matricies[8].arr[0][0], &matricies[8].arr[0][1], &matricies[8].arr[0][2], &matricies[8].arr[0][3],
		&matricies[8].arr[0][4], &matricies[8].arr[0][5], &matricies[8].arr[0][6], &matricies[8].arr[0][7]) != 8)
		return 0;

	//C matrix
	matricies[9].arr = new ARR_TYPE*[8];
	matricies[9].arr[0] = new ARR_TYPE[1];
	matricies[9].arr[1] = new ARR_TYPE[1];
	matricies[9].arr[2] = new ARR_TYPE[1];
	matricies[9].arr[3] = new ARR_TYPE[1];
	matricies[9].arr[4] = new ARR_TYPE[1];
	matricies[9].arr[5] = new ARR_TYPE[1];
	matricies[9].arr[6] = new ARR_TYPE[1];
	matricies[9].arr[7] = new ARR_TYPE[1];
	matricies[9].c = 1;
	matricies[9].r = 8;
	if (fscanf(fin, "%d %d %d %d %d %d %d %d", &matricies[9].arr[0][0], &matricies[9].arr[1][0], &matricies[9].arr[2][0], &matricies[9].arr[3][0],
		&matricies[9].arr[4][0], &matricies[9].arr[5][0], &matricies[9].arr[6][0], &matricies[9].arr[7][0]) != 8)
		return 0;

	return 1;
}

void print_matrix(const Matrix &m)
{
	for (int i = 0; i < m.r; ++i)
	{
		for (int j = 0; j < m.c; ++j)
		{
			cout << m.arr[i][j] << " ";
		}
		cout << endl;
	}
}

void print_matricies(const Matrix  matricies[], const int n)
{
	for (int i = 0; i < n; ++i)
	{
		print_matrix(matricies[i]);
		cout << endl;
	}
}

int cmp(const Matrix &m1, const Matrix &m2)
{
	if (m1.c != m2.c || m1.r != m2.r)
		return 0;

	for (int i = 0; i < m1.r; ++i)
	{
		for (int j = 0; j < m1.c; ++j)
		{
			if (m1.arr[i][j] != m2.arr[i][j])
				return 0;
		}
	}

	return 1;
}

int multiply(Matrix m1, Matrix m2, Matrix &result)
{
	if (m1.c != m2.r)
		return 0;

	Matrix sub_result;
	init_matrix(sub_result);

	sub_result.r = m1.r;
	sub_result.c = m2.c;

	for (int i = 0; i < m1.r; i++)
	{
		for (int j = 0; j < m2.c; j++)
		{
			sub_result.arr[i][j] = 0;
			for (int k = 0; k < m1.c; k++)
				sub_result.arr[i][j] += m1.arr[i][k] * m2.arr[k][j];
		}
	}

	deinit_matrix(result);
	result = sub_result;
	return 1;
}

ARR_TYPE adp(const int N, const int a, const int b, const int c, Matrix matricies[])
{
	Matrix result;
	copy_matrix(matricies[8], result);
	
	for (int i = 0; i < N; ++i)
	{
		unsigned int word = 
			(((a >> (N - i - 1)) & 1) << 2) ^
			(((b >> (N - i - 1)) & 1) << 1) ^
			(((c >> (N - i - 1)) & 1));
#ifdef VISUAL_DEBUG
		print_matrix(result);
		cout << endl;
		print_matrix(matricies[word]);
		cout << endl;
#endif
		multiply(result, matricies[word], result);
#ifdef VISUAL_DEBUG
		print_matrix(result);
		cout << endl;
#endif
	}
	
#ifdef VISUAL_DEBUG
	print_matrix(result);
	cout << endl;
	print_matrix(matricies[9]);
	cout << endl;
#endif
	multiply(result, matricies[9], result);
#ifdef VISUAL_DEBUG
	print_matrix(result);
	cout << endl;
#endif

	int r = result.arr[0][0];
	deinit_matrix(result);
	return r;
}

int check_theorem(FILE * fout, const int N, Matrix matricies[])
{
	const int max_value = 1 << N;
	for (int c = 0; c < max_value; ++c)
	{
		const ARR_TYPE max_prob = adp(N, 0, c, c, matricies);
		fprintf(fout, "%d %d %d\n", N, c, max_prob);
		for (int a = 0; a < max_value; ++a)
		{
			for (int b = 0; b < max_value; ++b)
			{
				if (adp(N, a, b, c, matricies) > max_prob)
				{
					fprintf(fout, "Fail for N = %d, parameters: %d %d %d\n", N, a, b, c);
					fprintf(stdout, "Fail for N = %d, parameters: %d %d %d\n", N, a, b, c);
					return 0;
				}
			}
		}
	}

	fprintf(fout, "Success for N = %d\n", N);
	fprintf(stdout, "Success for N = %d\n", N);
	return 1;
}
