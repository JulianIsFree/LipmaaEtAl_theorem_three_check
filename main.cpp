#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "theorem3.h"
#include "hypothesis.h"

int main()
{
	FILE * fin = fopen("matricies.txt", "r");
	if (fin == NULL)
		return -1;
	Matrix matricies[10];
	read_matricies(fin, matricies);
	fclose(fin);

	check_hypothesis(8, 153, 221);

	return 0;
}
