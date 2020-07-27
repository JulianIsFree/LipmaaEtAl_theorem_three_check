#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>

#include "matrix.h"
using namespace std;

ARR_TYPE adp(const int N, const int a, const int b, const int c, Matrix matricies[]);

int check_theorem(FILE * fout, const int N, Matrix matricies[]);

void get_theorem3_statistic(FILE * fout, const int N, Matrix matricies[]);

void check_hypothesis_one(FILE * fout, const int N, Matrix matricies[]);
