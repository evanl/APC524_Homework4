#include "heat_functions.h"

using std::ofstream;

int heat_initialize(doubleVector &vec1, const int nx, const double dx){

  vec1.resize(nx);
  for (int i = 0 ; i < nx ; ++i){
    vec1[i].resize(nx);
  }

  for (int i = 0 ; i < nx ; ++i ){
    for ( int j = 0 ; j < nx; ++j){
      // evaluates boundary conditions. 
      if ( j == 0 ){
        vec1[i][j] = cos(i * dx) * cos(i*dx);
      }else if ( j == (nx-1)) {
        vec1[i][j] = sin( i * dx) * sin(i *dx);
      } else{
      vec1[i][j] = 0.0;
      }
    }
  }

  return 0;
}

int heat_solve( doubleVector &vec1, doubleVector &vec2, double k,
   double dx, double dt, int nx, int tsteps ) {

  int count = 0;
  for (int i = 0 ; i < tsteps; i++){
    count++;
    if ( i % 2 == 0 ) {
      heat_step(vec1, vec2, k, dx, dt, nx);
    }else {
      heat_step(vec2, vec1, k, dx, dt, nx);
    }
    std::copy(vec2.begin(), vec2.end(), vec1.begin());
    if ((vec2[1][1] != vec2[1][1]) || (vec1[1][1] != vec1[1][1])){ 
      std::cout << "diverged after " << count << " iterations";
      std::cout << std::endl;
      exit(1);
    }
  }
  return 0;
}


int heat_step(const doubleVector &current, doubleVector &next , const double &k,
   const double &dx, const double &dt, const int &nx) {

  //std::cout << "iter" << std::endl;

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

        //std::cout << i << " " << j << std::endl;
        //std::cout << w << " " << e << " " << n << " ";
        //std::cout << s << " " << c << " " << std::endl;
        next[i][j] = c + dt * k * ( w + e + n + s - 4 * c) / (dx * dx);
      }
    }
  }

  return 0;
}

int heat_write_contour( const doubleVector &vec2, double dx, int nx ){

  // writes files to be plotted 
  ofstream output;
  output.open("output.dat");
  for (int i = 0 ; i < nx ; ++i ){
    for ( int j = 0 ; j < nx; ++j){
      output <<  i * dx << " ";
      output <<  j * dx << " ";
      output << vec2[i][j] << std::endl;
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
