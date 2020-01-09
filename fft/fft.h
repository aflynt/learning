#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nrutil.h"
#include <math.h>
#define PI 3.14159265359

#define CHECKPT {printf("Checkpoint: %s, line %d\n", __FILE__, __LINE__);\
  fflush(stdout);}

//FILE * openFile(int argc, char *argv[], FILE *fptr);
FILE * openFile( char fname[]);
int getPdata(FILE *fptr, double *time, double **pt);
int getRTZdata(FILE *fptr, double *r, double *theta, double *z);
int getXYdata(FILE *fptr, double *r, double *z);
void print1D(int len, double *x, char *name);
void print2D(double **pt, int ni, int nj);
void print3(int len, double *x, double *y, double *z, char *name);
int wc(FILE *fptr);
int findPt(int len, double *r, double *theta, double *z, int *flag, double rt, double tt, double zt);

int findTopPt(int len, double *z);
int calcGeom(int imax, double *T, double *s, double *As, double *zmid, double *R, double *Z);
int printForceData(int tmax, int kmax, double *zmid, double **Fx,double **Fy,double **Fz);
int nColsCSV(FILE *fptr, const char s[2]);
int readCSV(FILE *fptr, const char s[2], int ni, int nj, double **p);

FILE * openFile(char fname[]);
int getPdata(FILE *fptr, double *time, double **pt);
void printArray(double *time, double **pt, int numLines);
void printVector(int ni, double *x, double *y, double *z);
void sort(int ni, double *x, double *y, double *z);
int compare_doubles( const void *a, const void *b);
void swap(double *p, double *q);
//void swap2D(int nc, double *p, double *q);
void swap2D(int nc, double **p, double **q);
void sort2D(double **pt, int ni, int nc);

void four1(double data[], unsigned long nn, int isign);
int  write2log(FILE *fptr, double val, char *s);
int mkFFTdata(double * data, FILE *fptro);
