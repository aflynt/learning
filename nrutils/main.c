#include "linsolve.h"
#include "fft.h"

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
int main_LU(int argc, char *argv[])
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


int main(int argc, char *argv[])
{
  ///// SECTION FROM LU
  int i,j, n;
  float **a = NULL;
  float **y = NULL;
  float *b  = NULL;
  float d;
  int *indx = NULL;

  int ni = 3;
  int nj = 3;
  double **p = NULL;
  double *adata = NULL;

  FILE *fptri,*fptr_r;
  char ifile[60]="a.mat";
  char rfile[60]="b.mat";

  if((fptri = fopen( ifile, "r")) == NULL){ printf("Null file pointer\n"); exit(1);}
  if((fptr_r = fopen( rfile, "r")) == NULL){ printf("Null file pointer\n"); exit(1);}
  //
  // Count number of lines
  int nn = wc(fptri) - 1; rewind(fptri);
  ni = nn;
  nj = nn;
  n = nn;
  printf("n = %d\n", n);
  a    = matrix(1,n,1,n);
  y    = matrix(1,n,1,n);
  indx = ivector(1,n);
  b    = vector(1,n);

  // allocate p[n][n] as double matrix
  p = (double**) malloc(ni*sizeof(double*));
  adata = (double*) malloc(ni*nj*sizeof(double));
  for(i = 0; i < ni; i++) p[i] = adata + nj*i;
  //
  // read the rhs vector into p
  readCSV(fptr_r, ",", n, n, p);

  // copy p into b (float vector)
  for(i = 0; i < n; i++)
  {
    b[i+1] = p[i][0];
    printf("b[%d] = %f\n",i,b[i+1]);
  }

  // read a double matrix into p
  readCSV(fptri, ",", n, n, p);

  // copy p into a (float matrix)
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      a[i+1][j+1] = p[i][j];


  //b[1] =  1.0;
  //b[2] = -2.0;
  //b[3] =  0.0;

  printf("\n*======== before\n");
  printf("a\n");
  prnMat(a,n,n);

  // compute matrix inverse
  invert_matrix(a, y, n);
 
  // copy p back into a (float matrix)
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      a[i+1][j+1] = p[i][j];
 
  // compute solution to linear system
  ludcmp(a,n,indx,&d);
  lubksb(a,n,indx,b);
  // answer x is given back in b
  // original matrix a will be destroyed and turned into LU solution

  printf("\n*======== matrix inverse\n");
  printf("y\n");
  prnMat(y,n,n);

  printf("b, solution vector\n");
  for(i = 1; i <= n; i++)
    printf("b[%d] = %6.2f\n",i,b[i]);

  free_matrix(a,1,n,1,n);
  free_matrix(y,1,n,1,n);
  free_vector(b,1,n);
  free_ivector(indx,1,n);
  free(p);
  free(adata);
  fclose(fptri);
  fclose(fptr_r);

  return 0;
}
