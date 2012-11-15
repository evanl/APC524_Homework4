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

int doubleArrayRemove(doubleArray &arr1, int nx){

  for (int i=0; i < nx; ++i ){
   delete [] arr1[i];
  }
  delete [] arr1; 

  return 0;
}

int heat_initialize(doubleArray &arr1, const int nx, const double dx){

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

int heat_solve( doubleArray &arr1, doubleArray &arr2, double k,
   double dx, double dt, int nx, int tsteps,  int nthreads  ) {

  for (int i = 0 ; i < tsteps; i++){
    if ( i % 2 == 0 ) {
      heat_step(arr1, arr2, k, dx, dt, nx, nthreads);
    }else {
      heat_step(arr2, arr1, k, dx, dt, nx, nthreads);
    }
  }
  return 0;
}


int heat_step(const doubleArray &current, doubleArray &next , const double &k,
   const double &dx, const double &dt, const int &nx,  int nthreads ) {


  for (int i = 0; i < nx; i++){
    for (int j = 0; j <nx; j++){
      double w, e, s, n, c;

      if ((j!=0) && (j != (nx-1))){

        if (i==0){
          w = current[nx-1][j];
        }else{
          w = current[i-1][j];
        }
        if (i == (nx-1)){
          e = current[0][j];
        }else{
          e = current[i+1][j];
        }
        n = current[i][j+1];
        s = current[i][j-1];
        c = current[i][j];

        next[i][j] = c + dt * k * ( w + e + n + s - 4 * c) / (dx * dx);
      }
    }
  }

  return 0;
}


double heat_average(const doubleArray &arr, int nx) {

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

int heat_write_contour( const doubleArray &arr2, double dx, int nx ){

  // writes files to be plotted 
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
  
  
  // forms a contour plot of the output data. 
  //FILE *in;
  //char buff[512];
  //if(!( in = popen("gnuplot heat_plot.gnu","r"))){
  //  exit(1);
  //}
  //while(fgets(buff,sizeof(buff),in)!=NULL){
  //  std::cout << buff;
  // }
  //pclose(in);
  return 0;
}
