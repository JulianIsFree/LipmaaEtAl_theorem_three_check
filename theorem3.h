#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//#define VISUAL_DEBUG
#define MATRIX_EDGE 8
#define ARR_TYPE unsigned long

typedef struct _Matrix
{
	ARR_TYPE **arr;
	int r;
	int c;
} Matrix;

void init_matrix(Matrix &m);
void deinit_matrix(Matrix &m);
void copy_matrix(Matrix &source, Matrix &dest);

int read_matricies(FILE * fin, Matrix matricies[]);

void print_matrix(const Matrix & m);

void print_matricies(const Matrix matricies[], const int n);

int cmp(const Matrix & m1, const Matrix & m2);

int multiply(Matrix m1, Matrix m2, Matrix & result);

ARR_TYPE adp(const int N, const int a, const int b, const int c, Matrix matricies[]);

int check_theorem(FILE * fout, const int N, Matrix matricies[]);
