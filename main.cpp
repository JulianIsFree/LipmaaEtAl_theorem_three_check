#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "theorem3.h"
#include "hypothesis.h"

#define WORD_LEN 20

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

	FILE * fout = fopen("check_size_of_set.txt", "w");
	for (int i = 0; i < WORD_LEN; ++i)
	{
		if (check_size_of_set(fout, i, matricies))
			fprintf(fout, "all is good for word_len = %d.\n", i);
		else
			fprintf(fout, "results don't match with the hypothesis: word_len = %d.\n", i);
	}
	fclose(fout);

	return 0;
}
