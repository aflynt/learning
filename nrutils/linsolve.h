#include "nrutil.h"
#include <stdio.h>
#include <math.h>

#ifndef _GAUSSJ_H_
#define _GAUSSJ_H_

void gaussj(float **a, int n, float **b, int m);

// print a matrix A[n][m]
void prnMat(float **a, int n, int m);

#endif /* _GAUSSJ_H_ */
