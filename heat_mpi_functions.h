#ifndef HEAT_MPI_FUNCTIONS
#define HEAT_MPI_FUNCTIONS

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <stdio.h>

typedef double** doubleArray;

doubleArray doubleArrayCreate( const int nx, const int nxproc);

int doubleArrayRemove(doubleArray arr1, const int nx );

int heat_initialize(doubleArray arr1, const int nx, const int nxproc, const double proc_origin, const double dx);

int heat_step(const doubleArray current, doubleArray next , double k,
   const double dx, const double dt, const int nx , const int nxproc,
   double* lbuf, double* rbuf ); 

double heat_average(const doubleArray arr, const int nx, const int nxproc);

int heat_write( const doubleArray arr2, double dx, const int nx , const int nxproc, const int rank);

#endif // HEAT_MPI_FUNCTIONS
