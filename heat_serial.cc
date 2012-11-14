#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>
#include "heat_functions.h"

using std::vector;

const double PI = 3.14159265359;

int main (int argc, const char *argv[] ){

  clock_t beginTime = clock();
  // process command line argument. 
  if (argc != 2){
    printf( "Invalid input, please specify nx \n ");
    return 1;
  }
  const int nx = atoi(argv[1]);

  // initialize physical constants. 
  const double dx = PI / (nx - 1 );
  const double k = 0.15 ;//* pow(10.0,-6.0);
  const double dt = dx * dx / (4.0 * k);
  const double tmax = 0.5 * PI * PI / k;
  const int tsteps = ceil(tmax/dt);

  std::cout << "dx = " << dx << std::endl;
  std::cout << "k  = " << k << std::endl;
  std::cout << "tmax = " << tmax << std::endl;
  std::cout << "dt = " << dt << std::endl;
  std::cout << "tsteps = " << tsteps << std::endl;

  doubleArray arr1, arr2;
  arr1 = doubleArrayCreate(nx);
  arr2 = doubleArrayCreate(nx);
 
  heat_initialize(arr1, nx, dx);
  heat_initialize(arr2, nx, dx); 

  // solve equation. 
  heat_solve(arr1, arr2, k, dx, dt, nx, tsteps);

  double taverage;

  taverage = heat_average(arr2, nx); 

  std::cout << "t_average = " << taverage << std::endl;

  std::cout << "time to compute [seconds] = "; 
  std::cout << ((double)(clock()-beginTime))/CLOCKS_PER_SEC;
  std::cout << std::endl;

  
  // Write the file to output.dat, generate contour plot. 
  heat_write_contour( arr2, dx, nx );

  return 0;
}
