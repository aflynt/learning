#include "nrutil.h"
#include <stdio.h>
#include <math.h>

#ifndef _GAUSSJ_H_
#define _GAUSSJ_H_

// solve A x = b using gauss-jordan method
// A [n][n],  b[n][m] contains m rhs vectors 
void gaussj(float **a, int n, float **b, int m);

// print a matrix A[n][m]
void prnMat(float **a, int n, int m);

// LU Decomposition
void ludcmp(float **a, int n, int *indx, float *d);

// LU back-substitution linear solver
void lubksb(float **a, int n, int *indx, float b[]);
//
// uses LU Decomposition to invert a matrix Y = A^(-1) ,A[n][n]
void invert_matrix(float **a, float **y, int n);

#endif /* _GAUSSJ_H_ */
