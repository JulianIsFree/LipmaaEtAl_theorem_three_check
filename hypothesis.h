#pragma once
#include <map>
#include "theorem3.h"
#include "matrix.h"

static int s0[] = { 0, 3, 5, 6 };
static int s1[] = { 1, 2, 4, 7 };

static int a0[] = { 0, 3, 5, 6 };
static int a1[] = { 1, 2, 4, 7 };
static int a2[] = { 1, 2, 4, 7 };
static int a3[] = { 0, 3, 5, 6 };
static int a4[] = { 1, 2, 4, 7 };
static int a5[] = { 0, 3, 5, 6 };
static int a6[] = { 0, 3, 5, 6 };
static int a7[] = { 1, 2, 4, 7 };
static int * columns[] = { a0, a1, a2, a3, a4, a5, a6, a7 };

char is_sqnc_03_max_bigger(FILE * fout, int main_sqnc[], int morph_sqnc[], const int N, const int n, Matrix matricies[]);
char is_sqnc_03_sum_max_bigger(FILE * fout, int main_sqnc[], int morph_sqnc[], const int N, const int n, Matrix matricies[]);

double adp_sqnc(int words[], int len, Matrix matricies[]);
char check_size_of_set(FILE * fout, const size_t n, Matrix matricies[]);
