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

  doubleVector vec1, vec2;
 
  heat_initialize(vec1, nx, dx);
  heat_initialize(vec2, nx, dx); 

  // solve equation. 
  heat_solve(vec1, vec2, k, dx, dt, nx, tsteps);

  int tcompute = clock();
  std::cout << "time to compute [seconds]" << ((double)tcompute)/CLOCKS_PER_SEC;
  std::cout << std::endl;

  
  // Write the file to output.dat, generate contour plot. 
  heat_write_contour( vec2, dx, nx );

  return 0;
}
