#ifndef HEAT_FUNCTIONS
#define HEAT_FUNCTIONS

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <stdio.h>

typedef double** doubleArray;

doubleArray doubleArrayCreate(int nx);

int doubleArrayRemove(doubleArray arr1, int nx);

int heat_initialize(doubleArray arr1, const int nx, const double dx);

int heat_solve( doubleArray arr1, doubleArray arr2, double k,
   double dx, double dt, int nx, int tsteps ,  int nthreads  ) ;
  
int heat_step(const doubleArray current, doubleArray next , const double &k,
   const double &dx, const double &dt, const int  &nx,  int nthreads ); 

double heat_average(const doubleArray arr, int nx);

int heat_write( const doubleArray arr2, double dx, int nx );

#endif // HEAT_FUNCTIONS
