#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>
#include "heat_functions.h"

using std::vector;
using std::ofstream;

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
  const double dt = dx * dx / (8.0 * k);
  const double tmax = 0.5 * PI * PI / k;
  const int tsteps = ceil(tmax/dt);

  std::cout << "dx = " << dx << std::endl;
  std::cout << "k  = " << k << std::endl;
  std::cout << "tmax = " << tmax << std::endl;
  std::cout << "dt = " << dt << std::endl;

  doubleVector init, end;
 
  heat_initialize(init, nx, dx);
  heat_initialize(end, nx, dx); 

  /* 
   * solve function goes here
   */

  heat_solve(init, end, k, dx, dt, nx, tsteps);

  // print computation time
  int tcompute = clock();
  std::cout << "time to compute [seconds]" << ((double)tcompute)/CLOCKS_PER_SEC;
  std::cout << std::endl;


  // writes files to be plotted 
  ofstream output;
  output.open("output.dat");
  for (int i = 0 ; i < nx ; ++i ){
    for ( int j = 0 ; j < nx; ++j){
      output <<  i * dx << " ";
      output <<  j * dx << " ";
      output << end[i][j] << std::endl;
      if( i == (nx-1) && j == (nx-1)){
        output << std::endl;
      }
    }
  }
  output.close();
  
  // prints writing time. 
  int t = clock();
  std::cout << "time to write [seconds] " << ((double)t)/CLOCKS_PER_SEC; 
  std::cout << std::endl;
  
  // forms a contour plot of the output data. 
  FILE *in;
  char buff[512];
  if(!( in = popen("gnuplot heat_plot.gnu","r"))){
    exit(1);
  }
  while(fgets(buff,sizeof(buff),in)!=NULL){
    std::cout << buff;
  }
  pclose(in);
  
  
  int t1 = clock();
  std::cout << "time to plot [seconds] " << ((double)t1)/CLOCKS_PER_SEC << std::endl;
  
  return 0;
}
