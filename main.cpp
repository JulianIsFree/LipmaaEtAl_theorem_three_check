#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "theorem3.h"
#include "hypothesis.h"

#define WORD_LEN 8

int main()
{
	FILE * fin = fopen("matricies.txt", "r");
	if (fin == NULL)
		return -1;
	Matrix matricies[10];
	read_matricies(fin, matricies);
	fclose(fin);

	int words1[WORD_LEN];
	int words2[WORD_LEN];
	words1[0] = 3;
	words2[0] = 3;

	FILE * fout = fopen("is_sqnc_03_max_sum_bigger.txt", "w");
	for (int i = 0; i < WORD_LEN; ++i)
	{
		if (is_sqnc_03_sum_max_bigger(fout, words1, words2, i, 1, matricies))
			fprintf(fout, "all is good for word_len = %d.\n", i);
		else
			fprintf(fout, "results don't match with the hypothesis: word_len = %d.\n", i);
	}
	fclose(fout);

	return 0;
}
