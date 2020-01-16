#include "fft.h"

int compare_doubles( const void *a, const void *b)
{
  const double *da = (const double *) a;
  const double *db = (const double *) b;

  return (*da > *db) - (*da < *db);
}

void swap(double *p, double *q)
{
  double tmp;
  tmp =*p;
  *p = *q;
  *q = tmp;
}

void swap2D(int nc, double **p, double **q)
{
  int k;
  double tmp;

  for(k=0; k<nc; k++){ // swap values
    tmp = (*p)[k];
    (*p)[k] = (*q)[k];
    (*q)[k] = tmp;
  }
}

// open a file
FILE * openFile(char fname[])
{
  FILE * fptr;

  if((fptr = fopen(fname, "r")) == NULL){
    printf("Null file pointer\n");
    exit(1);
  }

  return fptr;
}

int getPdata(FILE *fptr, double *time, double **pt)
{
  int i=0;
  int t=0;
  int num;
  char str[1800];
  char *ret;
  char *token;
  const char mych = 't';
  const char s[2] = ",";


  // get a line from fptr and put it into str
  while ( fgets(str, 1800, fptr) != NULL)
  {

    // skip header containing ch
    // searches for ch in str and does something if didnt find ch
    if ((ret = strchr(str, mych)) == NULL)
    {
      i = 0;

      // get first token
      token = strtok(str, s);

      time[t] = atof(token); //first value is time

      //printf("LINE = %d, time[%d] = %f\n", t, time[t]);
      //scanf("%d",&num);

      // jump to next value
      token = strtok(NULL, s);

      // walk thru other tokens
      while (token != NULL) {
        //printf(" %s\n", token );
        pt[t][i] = atof(token);

        //sscanf(token, "%lf", &pt[t][i++]);
        //printf("pt[%3d][%2d]= %8.4f\n", t, i, pt[t][i]);

        token = strtok(NULL, s);
        i++;
      }
    }
    //printf("|%3d| String after |%c| is |%s|\n",t, mych, ret);
    t++;
  }

  return t;
}

int getRTZdata(FILE *fptr, double *r, double *theta, double *z)
{
  int i=0;
  int t=0;
  int num;
  char str[1800];
  char *ret;
  char *token;
  const char mych = 't';
  const char s[2] = ",";


  // get a line from fptr and put it into str
  while ( fgets(str, 1800, fptr) != NULL)
  {

    // skip header containing ch
    // searches for ch in str and does something if didnt find ch
    if ((ret = strchr(str, mych)) == NULL)
    {
      i = 0;

      // get first token
      token = strtok(str, s);

      r[t] = atof(token); //first value

      // jump to next value
      token = strtok(NULL, s);

      theta[t] = atof(token);

      // jump to next value
      token = strtok(NULL, s);
      z[t] = atof(token);


      //// walk thru other tokens
      //while (token != NULL) {
      //  //printf(" %s\n", token );
      //  pt[t][i] = atof(token);

      //  //sscanf(token, "%lf", &pt[t][i++]);
      //  //printf("pt[%3d][%2d]= %8.4f\n", t, i, pt[t][i]);

      //  token = strtok(NULL, s);
      //  i++;
      //}
      t++;
    }
    //printf("|%3d| String after |%c| is |%s|\n",t, mych, ret);
  }

  return t;
}

int  write2log(FILE *fptr, double val, char *s){
  fprintf(fptr, "%s\t=\t%10.3f\n", s, val);
}

int getXYdata(FILE *fptr, double *r, double *z)
{
  int t=0;
  char str[1800];
  char *ret;
  char *token;
  const char mych = '#';
  const char s[2] = ",";

  // get a line from fptr and put it into str
  while ( fgets(str, 1800, fptr) != NULL){
    // skip header containing ch
    // searches for ch in str and does something if didnt find ch
    if ((ret = strchr(str, mych)) == NULL){
      // get first token
      token = strtok(str, s);

      r[t] = atof(token); //first value

      // jump to next value
      token = strtok(NULL, s);
      z[t] = atof(token);

      t++;
    }
  }

  return t;
}

int nColsCSV(FILE *fptr, const char s[2])
{
  char str[800];
  char *token;
  int maxa=0;
  int maxc=0;

  while ( fgets(str, 800, fptr) != NULL){
    // get 1st token
    token = strtok(str, s);
    maxc = 0;

    while( token != NULL){
      maxc++;
      //printf("maxa =|%2d| maxc =|%2d| token=|%s|\n", maxa, maxc, token);

      token = strtok(NULL, s);
    }
    if(maxc > maxa)
      maxa = maxc;

  }
  return maxa;
}

int readCSV(FILE *fptr, const char s[2], int ni, int nj, double **p)
{
  char str[800];
  char *token;
  int i=0;
  int j=0;
  int firstTime=1;

  //  for (i = 0; i < ni; i++)
  //    for (j = 0; j < nc; j++)
  //      point[i][j] = 0.0;

  while ( fgets(str, 800, fptr) != NULL){
    if(firstTime==1){ // skip 1st line header
      firstTime=0;
      continue;
    }
    // get 1st token
    token = strtok(str, s);
    j = 0;

    while( token != NULL){
      p[i][j] = atof(token);
      //printf("i =|%2d| j =|%2d| token=|%10.3f|\n", i, j, p[i][j]);
      j++;

      token = strtok(NULL, s);
    }
    i++;
  }
  return i;
}

void print1D(int len, double *x, char *name)
{
  int i;

  for (i = 0; i< len; i++)
    printf("%s[%2d] = %5.2f\n", name, i, x[i]);
}

void print3(int len, double *x, double *y, double *z, char *name)
{
  int i;

  for (i = 0; i< len; i++)
    printf("%s[%2d] = | %6.3f\t%3.0f\t%6.3f |\n", name, i, x[i], y[i], z[i]);
}


// Print the array pt[ni][nj]
void print2D(double **pt, int ni, int nj)
{
  int i,j;

  printf("       ");
  for (j = 0; j< nj; j++)
    printf("%10s ", " ");
  printf("\n");

  for (i = 0; i< ni; i++){
    printf("i=[%2d] ",i);
    for (j = 0; j< nj; j++){
      if (j == 1)
        printf("%12.5E ", pt[i][j]);
      else
        printf("%10.3f ", pt[i][j]);
    }
    putchar('\n');
  }
}

int wc(FILE *fptr)
{
  int c;  // character
  int cp; // prev char
  int n;  // num lines

  n = 0;
  c = 0;
  while(1)
  {
    cp = c;
    c = getc(fptr);
    if(c == '\n')
    {
      n++;
      continue;
    }
    if (c == EOF && cp == '\n') break;
    if (c == EOF)
    {
      n++;
      break;
    }
  }

  return n;
}

int findPt(int len, double *r, double *theta, double *z, int *flag, double rt, double tt, double zt)
{
  int i;
  double eps = 1.0E-6;
  int gotr = 0;
  int gott = 0;
  int gotz = 0;
  int nfound = 0;

  //reset flag array
  for (i = 0; i < len; i++)
    flag[i]=0;

  // look for correct theta and z above ztarget
  for (i = 0; i < len; i++)
  {
    if (theta[i] < tt + eps && theta[i] > tt - eps)
      gott = 1;
    if (z[i] > zt+ eps && z[i] < 5.53 - eps)
      gotz = 1;

    if(gott && gotz)
    {
      flag[i] = 1;
      nfound++;
    }
    //printf("LINE %2d: %f \t %f \t %f \t r t z = | %d %d %d | flag = %d\n", i,  r[i], theta[i], z[i], gotr, gott, gotz, flag[i]);
    gotr = 0;
    gott = 0;
    gotz = 0;
  }

  return nfound;
}

int findTopPt(int len, double *z)
{
  int i;
  double zmax, zmaxt;
  int ntop = -1;

  zmax = zmaxt = z[0];

  for (i = 0; i < len; i++){
    if((zmaxt = z[i]) > zmax){
      zmax = zmaxt;
      ntop = i;
    }
  }

  return ntop;
}

int calcGeom(int imax, double *T, double *s, double *As, double *zmid, double *R, double *Z)
{
  int i;
  double zbase = -4.7316;
  double rbase = 0.43815;

  for (i = 0; i < imax; i++){
    if(i == 0){
      T[i] = 0.0;
      s[i]  = sqrt((R[i] - rbase)*(R[i] - rbase)+
                   (Z[i] - zbase)*(Z[i] - zbase));
      As[i]  =  PI*(R[i] + rbase) * s[i] / 8.0;
      zmid[i] = 0.5*(Z[i] + zbase);
    }
    else{
      T[i] = atan((R[i] - R[i-1])/(Z[i] - Z[i-1]));
      s[i] = sqrt((R[i] - R[i-1])*(R[i] - R[i-1])+
                  (Z[i] - Z[i-1])*(Z[i] - Z[i-1]));
      As[i] =  PI*(R[i] + R[i-1]) * s[i] / 8.0;
      zmid[i] = 0.5*(Z[i] + Z[i-1]);
    }
    //printf("i=%d T=%10.3f  S=%10.3f  A=%10.3f  Z=%10.3f\n",i,T[i],s[i],As[i],zmid[i]);
  }

  return 0;
}

int printForceData(int tmax, int kmax, double *zmid, double **Fx,double **Fy,double **Fz)
{
  int t, k;
  for (t=1; t<tmax;t++){
    if(t ==1){
      printf("Header  ,");
      for (k=0; k<kmax;k++) printf("%10s ,", "Fz");
      for (k=0; k<kmax;k++) printf("%10s ,", "Fx");
      for (k=0; k<kmax;k++) printf("%10s ,", "Fy");
      printf("\n");
      printf("z(m)=   ,");
      for (k=0; k<kmax;k++) printf("%10.3E ,", zmid[k]);
      for (k=0; k<kmax;k++) printf("%10.3E ,", zmid[k]);
      for (k=0; k<kmax;k++) printf("%10.3E ,", zmid[k]);
      printf("\n");
    }
    printf("t=|%3d| ,", t);
    for (k=0; k<kmax;k++) printf("%10.3E ,", Fz[t][k]);
    for (k=0; k<kmax;k++) printf("%10.3E ,", Fx[t][k]);
    for (k=0; k<kmax;k++) printf("%10.3E ,", Fy[t][k]);
    printf("\n");
  }
  return 0;
}

void printVector(int ni, double *x, double *y, double *z)
{
  int i;
  printf("  ");
  for (i = 0; i < ni; i++)
     printf("%6d ", i);
  printf("\n");

  printf("x=");
  for (i = 0; i < ni; i++)
     printf("%6.1f ", x[i]);
  printf("\n");


  printf("y=");
  for (i = 0; i < ni; i++)
     printf("%6.1f ", y[i]);
  printf("\n");

  printf("z=");
  for (i = 0; i < ni; i++)
     printf("%6.1f ", z[i]);
  printf("\n");
}

void sort(int ni, double *x, double *y, double *z)
{
  int i,j;
  double xtmp, ytmp, ztmp;

  //bubble sort method

  for(i=0; i<ni -1; ++i){
    for(j = ni-1; i<j; --j){
      if (y[j-1] > y[j]){
        swap(&x[j-1], &x[j]);
        swap(&y[j-1], &y[j]);
        swap(&z[j-1], &z[j]);
      }
      else if (y[j-1] == y[j]){
        if (z[j-1] > z[j]){
          swap(&x[j-1], &x[j]);
          swap(&y[j-1], &y[j]);
          swap(&z[j-1], &z[j]);
        }
      }
    }
  }
  //qsort(y, ni, sizeof(double), compare_doubles);

}

void sort2D(double **pt, int ni, int nc)
{
  int i,j;

  //bubble sort method
  for(i=0; i<ni -1; ++i){
    for(j = ni-1; i<j; --j){
      if (pt[j-1][3] > pt[j][3])          // Yj less
          swap2D(nc, &(&pt[j-1])[0], &(&pt[j])[0]);
      else if (pt[j-1][3] == pt[j][3]){   // Yj equal
        if (pt[j-1][4] > pt[j][4])        // Zj less
            swap2D(nc, &(&pt[j-1])[0], &(&pt[j])[0]);
        else if (pt[j-1][4] == pt[j][4]){ // Zj equal
          if (pt[j-1][2] > pt[j][2])      // xj less
            swap2D(nc, &(&pt[j-1])[0], &(&pt[j])[0]);
        }
      }
    }
  }
}

#if 0
  // check poly coefficients
  double *x0;
  double *y0;
  double *cof;
  x0=vector(0,nfound-1);
  y0=vector(0,nfound-1);
  cof=vector(0,nfound-1);

  for (i = 0; i < nfound; i++)
  {
    x0[i] = (double) mpz[i];
    y0[i] = (double)  point[1][mpn[i]];

      printf("i:%2d, x0 = |%6.3f| y0 = |%6.3f|\n",i , x0[i], y0[i]);
  }


  polcof(x0, y0, nfound-1, &cof[0]);

  for (i = 0; i < nfound; i++)
  {
    printf("i:%2d, cof = |%10.3E|\n", i, cof[i]);
  }

  free_vector(x0,0,nfound);
  free_vector(y0,0,nfound);
  free_vector(xa,1,nfound);
  free_vector(ya,1,nfound);
#endif
//CHECKPT;

int mkFFTdata(double * data, FILE *fptro)
{
  FILE *fptr;
  char fname[60]="fftdata.dat";
  char flog[60]="log.dat";
  int i;
  double ts;
  double freq = 10;           // target frequency
  double omega = 2*PI*freq;  // w = 2 pi f
  double FS = 150;   // sampling rate
  double dt = 1.0 / FS;      // time step size
  double ncycles = 5;           // number of cycles to capture
  double ttot = ncycles / freq; // total time
  double fmax = FS/2.0;         // max frequency captured
  double nnf = ttot / dt;      // number of samp
  int nn = (int) nnf;          // length of fft / 2 (for complex #'s)

  if((fptr = fopen(fname, "w")) == NULL){
    printf("Null file pointer\n");
    exit(1);
  }

  // calc FFT data
  printf("writing to file: %s\n", fname);
  for(i = 0; i < nn; i++){
    ts = (double) i * dt;
    data[i] = (double) cos(omega * ts);
    //printf("%10.3f, %10.3f\n",ts , data[i]);
    fprintf(fptr,"%10.3f, %10.3f\n",ts , data[i]);
  }

  // write parameters to log file
  write2log(fptro, freq,  "freq");
  write2log(fptro, omega, "omega");
  write2log(fptro, FS,    "FS");
  write2log(fptro, dt,    "dt");
  write2log(fptro, (double) nn,    "nn");
  write2log(fptro, fmax,  "fmax");

  fclose(fptr);

  return nn;
}
