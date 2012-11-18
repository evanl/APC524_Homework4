#include "heat_functions.h"

using std::ofstream;

doubleArray doubleArrayCreate(int nx){

  double **arr;

  arr = new double*[nx];
  for (int i=0; i < nx; ++i){
    arr[i] = new double[nx];
  }

  return arr;
}

int doubleArrayRemove(doubleArray arr1, int nx){

  for (int i=0; i < nx; ++i ){
   delete [] arr1[i];
  }
  delete [] arr1; 

  return 0;
}

int heat_initialize(doubleArray arr1, const int nx, const double dx){

  for (int i = 0 ; i < nx ; ++i ){
    for ( int j = 0 ; j < nx; ++j){
      // evaluates boundary conditions. 
      if ( j == 0 ){
        arr1[i][j] = cos(i * dx) * cos(i*dx);
      }else if ( j == (nx-1)) {
        arr1[i][j] = sin( i * dx) * sin(i *dx);
      } else{
      arr1[i][j] = 0.0;
      }
    }
  }

  return 0;
}

int heat_solve( doubleArray arr1, doubleArray arr2, double k,
   double dx, double dt, int nx, int tsteps) {

  for (int i = 0 ; i < tsteps; i++){
    if ( i % 2 == 0 ) {
      heat_step(arr1, arr2, k, dx, dt, nx);
    }else {
      heat_step(arr2, arr1, k, dx, dt, nx);
    }
  }
  return 0;
}


int heat_step(const doubleArray current, doubleArray next , const double &k,
   const double &dx, const double &dt, const int &nx) {

  for( int j=1 ; j < (nx-1) ; j++ )
  {

    next[0][j] = current[0][j] + dt * k * ( current[nx-1][j] + current[1][j] + current[0][j+1] + current[0][j-1] - 4 * current[0][j]) / ( dx * dx);

    next[nx-1][j] = current[nx-1][j] + dt * k * ( current[0][j] + current[1][j] + current[nx-1][j+1] + current[nx-1][j-1] - 4 * current[nx-1][j]) / ( dx * dx);
  }
  

  for (int i = 1; i < (nx-1); i++){
    for (int j = 1; j < (nx-1) ; j++){

      double t = 0.0; 

      t = t + current[i-1][j] + current[i+1][j] + current[i][j+1] + current[i][j-1];

      next[i][j] = current[i][j] + dt * k * ( t - 4 * current[i][j]) / (dx * dx);

    }
  }

  return 0;
}


double heat_average(const doubleArray arr, int nx) {

  double taverage;
  double sumT = 0.0;
  double N = nx * nx ;

  for( int i=0 ; i < nx ; i++ )
  {
    for( int j=0 ; j < nx  ; j++ )
    {
      sumT = sumT + arr[i][j];
    }
    
  }
  return taverage = sumT / N; 
}

int heat_write( const doubleArray arr2, double dx, int nx ){

  ofstream output;
  output.open("output.dat");
  for (int i = 0 ; i < nx ; ++i ){
    for ( int j = 0 ; j < nx; ++j){
      output <<  i * dx << " ";
      output <<  j * dx << " ";
      output << arr2[i][j] << std::endl;
      if( i == (nx-1) && j == (nx-1)){
        output << std::endl;
      }
    }
  }
  output.close();
  
  
  return 0;
}
