#ifndef HEAT_FUNCTIONS
#define HEAT_FUNCTIONS

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>

typedef std::vector<double> Vector;
typedef std::vector < Vector> doubleVector;

int heat_initialize(doubleVector &init, const int nx, const double dx);

int heat_solve( doubleVector &init, doubleVector &end, double k,
   double dx, double dt, int nx, int tsteps ) ;
  
int heat_step(const doubleVector &current, doubleVector &next , const double &k,
   const double &dx, const double &dt, const int  &nx); 

#endif // HEAT_FUNCTIONS
