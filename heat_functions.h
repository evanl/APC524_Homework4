#ifndef HEAT_FUNCTIONS
#define HEAT_FUNCTIONS

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <stdio.h>

typedef std::vector<double> Vector;
typedef std::vector < Vector> doubleVector;

int heat_initialize(doubleVector &vec1, const int nx, const double dx);

int heat_solve( doubleVector &vec1, doubleVector &vec2, double k,
   double dx, double dt, int nx, int tsteps ) ;
  
int heat_step(const doubleVector &current, doubleVector &next , const double &k,
   const double &dx, const double &dt, const int  &nx); 

int heat_write_contour( const doubleVector &vec2, double dx, int nx );

#endif // HEAT_FUNCTIONS
