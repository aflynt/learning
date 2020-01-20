#include "linsolve.h"

#if 0

//int main_gj(int argc, char *argv[])
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
#endif

// uses LU decomposition to solve linear equation set
//int main_LU(int argc, char *argv[])
int main(int argc, char *argv[])
{
  int i, j, k;

  float **a;
  float *b;
  float d;
  int n = 3;
  int m = 1;
  int *indx;
  indx = ivector(1,n);
  a = matrix(1,n,1,n);
  b = vector(1,n);

  a[1][1] = 2.0;
  a[1][2] = 1.0;
  a[1][3] =-1.0;

  a[2][1] =-3.0;
  a[2][2] =-1.0;
  a[2][3] = 2.0;

  a[3][1] =-2.0;
  a[3][2] = 1.0;
  a[3][3] = 2.0;

  b[1] =  8.0;
  b[2] =-11.0;
  b[3] = -3.0;


  printf("\n*======== before\n");
  printf("a\n");
  prnMat(a,n,n);

  printf("b\n");
  for(i = 1; i <= n; i++)
    printf("b[%d] = %6.2f\n",i,b[i]);

  // compute solution to linear system
  ludcmp(a,n,indx,&d);
  lubksb(a,n,indx,b);
  // answer x is given back in b
  // original matrix a will be destroyed and turned into LU solution

  printf("\n*======== after\n");
  printf("a\n");
  prnMat(a,n,n);

  printf("b\n");
  for(i = 1; i <= n; i++)
    printf("b[%d] = %6.2f\n",i,b[i]);

  free_matrix(a,1,n,1,n);
  free_vector(b,1,n);
  free_ivector(indx,1,n);

  return 0;
}

// uses LU Decomposition to invert a matrix
int main_inv(int argc, char *argv[])
{
  int i, j;
  int n = 3;
  int *indx;

  float **a;
  float **y;
  float *col;
  float d;

  indx = ivector(1,n);
  a    = matrix(1,n,1,n);
  y    = matrix(1,n,1,n);
  col  = vector(1,n);

  a[1][1] = 2.0;
  a[1][2] = 1.0;
  a[1][3] =-1.0;

  a[2][1] =-3.0;
  a[2][2] =-1.0;
  a[2][3] = 2.0;

  a[3][1] =-2.0;
  a[3][2] = 1.0;
  a[3][3] = 2.0;


  printf("\n*======== before\n");
  printf("a\n");
  prnMat(a,n,n);


  // LU decompose just once 
  ludcmp(a,n,indx,&d);

  // Invert the matrix by columnes
  for(j = 1; j <= n; j++){
    for(i = 1; i <= n; i++)
      col[i] = 0.0;
    col[j] = 1.0;
    lubksb(a,n,indx,col);
    for(i = 1; i <= n; i++)
      y[i][j] = col[i];
  }

  // the matrix y now contains the inverse of the original matrix a, which
  // will have been destroyed.


  printf("\n*======== after\n");
  printf("y\n");
  prnMat(y,n,n);


  free_matrix(a,1,n,1,n);
  free_matrix(y,1,n,1,n);
  free_vector(col,1,n);
  free_ivector(indx,1,n);

  return 0;
}
