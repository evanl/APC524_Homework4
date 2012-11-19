#include "heat_mpi_functions.h"

using std::ofstream;

doubleArray doubleArrayCreate(const int nx, const int nxproc){

  double **arr;

  arr = new double*[nxproc];
  for (int i=0; i < nxproc; ++i){
    arr[i] = new double[nx];
  }

  return arr;
}

int doubleArrayRemove(doubleArray arr1, const int nx){

  for (int i=0; i < nx; ++i ){
   delete [] arr1[i];
  }
  delete [] arr1; 

  return 0;
}

int heat_initialize(doubleArray arr1, const int nx, const int nxproc, const double proc_origin, const double dx){

  for (int i = 0 ; i < nxproc ; ++i ){
    for ( int j = 0 ; j < nx; ++j){
      // evaluates boundary conditions. 
      if ( j == 0 ){
        arr1[i][j] = cos(proc_origin + i * dx) * cos(proc_origin + i*dx);
      }else if ( j == (nx-1)) {
        arr1[i][j] = sin(proc_origin +  i * dx) * sin(proc_origin + i *dx);
      } else{
      arr1[i][j] = 0.0;
      }
    }
  }

  return 0;
}


int heat_step(const doubleArray current, doubleArray next , const double k,
   const double dx, const double dt, const int nx, const int nxproc, double* lbuf, double* rbuf ) {

  

  for( int j=1 ; j < (nx-1) ; j++ )
  {

    next[0][j] = current[0][j] + dt * k * ( lbuf[j] + current[1][j] + current[0][j+1] + current[0][j-1] - 4 * current[0][j]) / ( dx * dx);

    next[nxproc-1][j] = current[nxproc-1][j] + dt * k * ( rbuf[j] + current[nxproc-2][j] + current[nxproc-1][j+1] + current[nxproc-1][j-1] - 4 * current[nxproc-1][j]) / ( dx * dx);
  }
  

  for (int i = 1; i < (nxproc-1); i++){
    for (int j = 1; j < (nx-1) ; j++){

      double t = 0.0; 

      t = t + current[i-1][j] + current[i+1][j] + current[i][j+1] + current[i][j-1];

      next[i][j] = current[i][j] + dt * k * ( t - 4 * current[i][j]) / (dx * dx);

    }
  }

  return 0;
}


double heat_average(const doubleArray arr, const int nx, const int nxproc) {

  double taverage;
  double sumT = 0.0;
  double N = nxproc * nxproc ;

  for( int i=0 ; i < nxproc ; i++ )
  {
    for( int j=0 ; j < nx  ; j++ )
    {
      sumT = sumT + arr[i][j];
    }
    
  }
  return taverage = sumT / N; 
}

int heat_write( const doubleArray arr2, double dx, const int nx, const int nxproc, const int rank ){

  char outchar [50];
  sprintf(outchar,"output%d.dat",rank);

  ofstream output;
  output.open(outchar);
  for (int i = 0 ; i < nxproc ; ++i ){
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
