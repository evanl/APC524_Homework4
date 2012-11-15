#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>
#include <omp.h>
#include "heat_functions.h"

using std::vector;

const double PI = 3.14159265359;

int main (int argc, const char *argv[] ){

  time_t beginTime; 
  beginTime = time(NULL);
  // process command line argument. 
  if (argc != 3){
    printf( "Invalid input, please specify nx \n ");
    return 1;
  }
  const int nx = atoi(argv[1]);
  const int nthreads = atoi(argv[2]);

  // initialize physical constants. 
  const double dx = PI / (nx - 1 );
  const double k = 0.25 ;//* pow(10.0,-6.0);
  const double dt = dx * dx / (4.0 * k);
  const double tmax = 0.5 * PI * PI / k;
  const int tsteps = ceil(tmax/dt);

  std::cout << "dx = " << dx << std::endl;
  std::cout << "k  = " << k << std::endl;
  std::cout << "tmax = " << tmax << std::endl;
  std::cout << "dt = " << dt << std::endl;
  std::cout << "tsteps = " << tsteps << std::endl;
  std::cout << "nthreads = " << nthreads << std::endl;

  doubleArray arr1, arr2;
  arr1 = doubleArrayCreate(nx);
  arr2 = doubleArrayCreate(nx);
 
  heat_initialize(arr1, nx, dx);
  heat_initialize(arr2, nx, dx); 

  omp_set_num_threads(nthreads);
  heat_solve(arr1, arr2, k, dx, dt, nx, tsteps, nthreads);

  double taverage;

  taverage = heat_average(arr2, nx); 

  std::cout << "t_average = " << taverage << std::endl;

  std::cout << "time to compute [seconds] = "; 
  std::cout << ((double)(time(NULL)-beginTime));
  std::cout << std::endl;

  
  // Write the file to output.dat
  heat_write( arr2, dx, nx );

  doubleArrayRemove(arr1 ,nx);
  doubleArrayRemove(arr2 ,nx );

  return 0;
}
