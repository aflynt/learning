#include "linsolve.h"


int main(int argc, char *argv[])
{
  int i, j, k;

  float **a;
  float **b;
  int n = 3;
  int m = 1;
  a = matrix(1,n,1,n);
  b = matrix(1,n,1,m);

  a[1][1] = 2.0;
  a[1][2] = 1.0;
  a[1][3] =-1.0;

  a[2][1] =-3.0;
  a[2][2] =-1.0;
  a[2][3] = 2.0;

  a[3][1] =-2.0;
  a[3][2] = 1.0;
  a[3][3] = 2.0;

  b[1][1] =  8.0;
  b[2][1] =-11.0;
  b[3][1] = -3.0;


  printf("\n*======== before\n");
  printf("a\n");
  prnMat(a,n,n);

  printf("b\n");
  prnMat(b,n,m);

  // compute solution to linear system
  gaussj(a, n, b, m);

  printf("\n*======== after\n");
  printf("a\n");
  prnMat(a,n,n);

  printf("b\n");
  prnMat(b,n,m);

  free_matrix(a,1,n,1,n);
  free_matrix(b,1,n,1,m);

  return 0;
}

