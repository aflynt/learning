#include "fft.h"


int main(int argc, char *argv[])
{

  int i, j, k;
  int np, nc, nt=0;
  FILE *fptri;
  FILE *fptrl;
  FILE *fptro;

  double *tdata;
  double *adata;

  char flog[60]="log.dat";
  char ifile[60]="inputdata.txt";
  char ofile[60]="results.dat";

  double ts=0.0;
  double *data;
  double *f;
  //double fmax = FS/2.0;         // max frequency captured is sample freq / 2.0
  double fmax = 150.0/2.0;         // max frequency captured
  int nn = 1024;          // length of fft / 2 (for complex #'s)


  // open files
  if((fptri = fopen( ifile, "r")) == NULL){ printf("Null file pointer\n"); exit(1);}
  if((fptrl = fopen(  flog, "w")) == NULL){ printf("Null file pointer\n"); exit(1);}
  if((fptro = fopen( ofile, "w")) == NULL){ printf("Null file pointer\n"); exit(1);}

  // Count number of lines
  nn = wc(fptri); rewind(fptri);

  // increase nn to next highest 2^x
  printf("reading from file = %s\n", ifile);
  printf("logging to   file = %s\n", flog);
  fprintf(fptrl,"nn from file = %2d\n", nn);
  int pownum = 0;
  for(i = 2; i < 16 && (pownum = pow(2,i)) < nn ; i++){
    //printf("nn = %2d, 2^[%2d] = %f\n", nn, i, pow(2.0,(double) i));
  }
  nn = pownum;
  //nn = 1024;
  fprintf(fptrl,"nn now equals = %2d\n", nn);


  // allocate input data arrays time[i], A[i]
  tdata = (double *) malloc(nn * sizeof(double));
  adata = (double *) malloc(nn * sizeof(double));

  // allocate vectors 1..2*nn
  data = dvector(1,2*nn);
  f = dvector(1,2*nn);

  // read adata from input file
  getXYdata(fptri, tdata, adata);

  // set data to zero
  for(i = 1; i <= 2*nn; i++)
    data[i] = 0.0;

  // cp adata into data
  for(i = 0; i <nn; i++){
    j=2*i+1;
    data[j] = adata[i];
    //printf("i,j, adata, data = %d, %d, %f, %f\n", i, j, adata[i], data[j]);
  }

  int pick = -1;

  if(argc > 1){
    fmax = atof(argv[1]);
    pick = 1;
    fprintf(fptrl,"pick: %d\n", pick);
    fprintf(fptrl,"fmax: %10.3f\n", fmax);
  }
  else{
    printf("pick: 1=calc FFT, 0=mk data\n");
    scanf("%d",&pick);
  }

  // make FFT data
  if(pick == 0){

    mkFFTdata(data, fptrl);
  }
  // compute FFT
  else {

    // compute FFT for complex data
    four1(data, nn, 1);

    // print DFT vs f
    printf("writing results to file: %s\n", ofile);
    for(i = 1; i <= nn+2; i+=2){
      f[i] = (double) (i-1) * fmax/ ((double) nn);
      fprintf(fptro, "%10.3f, %10.3f\n",f[i], fabs(data[i]));
    }
  }

  free_dvector(data, 1, 2*nn);
  free_dvector(f, 1, 2*nn);

  free(tdata);
  free(adata);
  fclose(fptri);
  fclose(fptrl);
  fclose(fptro);

  return 0;
}

