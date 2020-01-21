#include "nrutil.h"
#include "linsolve.h"

#define SWAP(a,b) {temp=(a); (a)=(b); (b) = temp;}
#define TINY 1.0e-20;

// gauss jordan linear solver
void gaussj(float **a, int n, float **b, int m)
{
  int *indxc, *indxr, *ipiv;
  int i,icol,irow,j,k,l,ll;
  float big, dum, pivinv,temp;

  indxc=ivector(1,n);  //bookkeeping vectors for the pivoting
  indxr=ivector(1,n);
  ipiv =ivector(1,n);

  for(j=1;j<=n;j++) ipiv[j] = 0;

  // main loop over columns to be reduced.
  for(i=1;i<=n;i++){
    big = 0.0;
    for(j=1;j<=n;j++)   // outer loop of search for pivot elements
      if(ipiv[j] != 1)
        for(k=1;k<=n;k++){
          if(ipiv[k] == 0){
            if(fabs(a[j][k]) >= big){
              big = fabs(a[j][k]);
              irow=j;
              icol=k;
            }
          }
          else if (ipiv[k] > 1)
            nrerror("gaussj:Singular Matrix-1"); 
        }
    ++(ipiv[icol]);
    // We now have the pivot element, so we interchange rows, if
    // needed to put the pivot element on the diagonal.

    if (irow != icol){
      for(l=1;l<=n;l++) SWAP(a[irow][l],a[icol][l])
      for(l=1;l<=m;l++) SWAP(b[irow][l],b[icol][l])
    }

    indxr[i] = irow;
    indxc[i] = icol;
    if (a[icol][icol] == 0.0) nrerror("gaussj: Singular Matrix-2");
    pivinv = 1.0/a[icol][icol];
    a[icol][icol]=1.0;

    for(l=1;l<=n;l++) a[icol][l] *= pivinv;
    for(l=1;l<=m;l++) b[icol][l] *= pivinv;

    for(ll=1;ll<=n;ll++)
      if(ll != icol){
        dum=a[ll][icol];
        a[ll][icol]=0.0;
          for(l=1;l<=n;l++) a[ll][l] -= a[icol][l]*dum;
          for(l=1;l<=m;l++) b[ll][l] -= b[icol][l]*dum;
      }
  }

  //unscramble solution
  for(l=n; l >=1; l--){
    if(indxr[l] != indxc[l])
      for(k=1;k<=n;k++)
        SWAP(a[k][indxr[l]],a[k][indxc[l]]);
  }
  free_ivector(ipiv,1,n);
  free_ivector(indxr,1,n);
  free_ivector(indxc,1,n);

  // end of the function
}

// print a matrix A[n][m]
void prnMat(float **a, int n, int m)
{
  int i,j;
  for(i = 1; i <= n; i++){
    for(j = 1; j <= m; j++)
      printf("%6.2f",a[i][j]);
    putchar('\n');
  }
}

// LU Decomposition
void ludcmp(float **a, int n, int *indx, float *d)
{
  // replaces A[n][n] by LU decomposition
  // indx[n] == records row permutations from partial pivots
  // d is +/-1 to track even/odd number of row interchanges

  int i,imax,j,k;
  float big, dum,sum,temp;
  float *vv;                //vv stores implicit scaling of each row

  vv = vector(1,n);
  *d = 1.0;
  for(i = 1; i <= n; i++){  // loop ove rows to get implicit scaling info
    big = 0.0;
    for(j = 1; j <= n; j++)
      if((temp = fabs(a[i][j])) > big) big=temp;
    if (big == 0.0)
      nrerror("Singular matrix in routine ludcmp"); 
      //no nonzero largest elemnt
    // save the scaling
    vv[i] = 1.0/big;
  }
  for(j = 1; j <= n; j++){ // loop over columns of Crout's method
    for(i = 1; i < j; i++){
      sum = a[i][j];
      for(k = 1; k < i; k++) sum -= a[i][k] * a[k][j];
      a[i][j]=sum;
    }
    big=0.0;
    for(i = j; i <= n; i++){ // init search for largest pivot elem.
      sum = a[i][j];
      for(k = 1; k < j; k++)
        sum -= a[i][k]*a[k][j];
      a[i][j] = sum;
      if( (dum=vv[i]*fabs(sum)) >= big) {
        // is the figure of merit for pivot better than the best yet?
        big = dum;
        imax = i;
      }
    }
    if ( j != imax) {           // interchange rows if needed
      for(k = 1; k <= n; k++){
        dum = a[imax][k];
        a[imax][k] = a[j][k];
        a[j][k] = dum;
      }
      *d = -(*d);        // flip the sign
      vv[imax] = vv[j];  // chg scale factor
    }
    indx[j] = imax;
    if ( a[j][j] == 0.0)  // pivot elem cant be zero
      a[j][j]=TINY;
    if ( j != n){            // finally divide by pivot elem
      dum = 1.0 / (a[j][j]);
      for(i = j+1; i <= n; i++)
        a[i][j] *= dum;
    }
  }
  free_vector(vv,1,n);
}

// LU Backsubstitution linear solver
void lubksb(float **a, int n, int *indx, float *b)
{
  // solves set of n linear equations A*X = B.
  // a[n][n] is input as LU decomp. indx[n] is input as permutation vector
  // from ludcmp. b[n] is rhs vector B and returns as solution vector X
  // a, n, and indx are not modified by this routine.
  int i, ii=0, ip, j;
  float sum;

  // when ii is positive, it will become the index of the first nonvanishing
  // element of b. we now do the forward substitution. eq 2.3.6
  // just have to unscramble the permutation as we go
  for(i = 1; i <= n; i++){
    ip = indx[i];
    sum = b[ip];
    b[ip] = b[i];
    if(ii)
      for(j = ii; j <= i-1; j++)
        sum -= a[i][j]*b[j];
    else if (sum) ii=i;
    b[i] = sum;
  }
  // now we do the back substitution eq 2.3.7
  for(i = n; i >= 1; i--){
    sum=b[i];
    for(j = i+1; j <= n; j++)
      sum -= a[i][j]*b[j];

    // store a component of the solution vector x.
    b[i] = sum/a[i][i];
  }
}

// uses LU Decomposition to invert a matrix Y = A^(-1) ,A[n][n]
void invert_matrix(float **a, float **y, int n)
{
  // the matrix y will contain the inverse of the original matrix a, which
  // will have been destroyed.
  int i,j;
  int *indx;
  float *col;
  float d;

  indx = ivector(1,n);
  col  =  vector(1,n);

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

  free_vector(col,1,n);
  free_ivector(indx,1,n);
}
