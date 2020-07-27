#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>

#define MATRIX_EDGE 8
#define ARR_TYPE unsigned long

//#define VISUAL_DEBUG_MULTI

using namespace std;

typedef struct _Matrix
{
	ARR_TYPE **arr;
	int r;
	int c;
} Matrix;

void init_matrix(Matrix &m);

void init_identity_matrix(Matrix &m);

void deinit_matrix(Matrix &m);

void copy_matrix(Matrix & source, Matrix & dest);

void copy_matrix_and_allocate(Matrix &source, Matrix &dest);

int read_matricies(FILE * fin, Matrix matricies[]);

void print_matrix(const Matrix & m);

void print_matricies(const Matrix matricies[], const int n);

void print_bit(FILE * fout, const int n, const int N);

int cmp(const Matrix & m1, const Matrix & m2);

int multiply(Matrix m1, Matrix m2, Matrix & result);