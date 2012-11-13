#include "heat_functions.h"


int heat_initialize(doubleVector &init, const int nx, const double dx){

  init.resize(nx);
  for (int i = 0 ; i < nx ; ++i){
    init[i].resize(nx);
  }

  for (int i = 0 ; i < nx ; ++i ){
    for ( int j = 0 ; j < nx; ++j){
      // evaluates boundary conditions. 
      if ( j == 0 ){
        init[i][j] = cos(i * dx) * cos(i*dx);
      }else if ( j == (nx-1)) {
        init[i][j] = sin( i * dx) * sin(i *dx);
      } else{
      init[i][j] = 0.0;
      }
    }
  }

  return 0;
}

int heat_solve( doubleVector &init, doubleVector &end, double k,
   double dx, double dt, int nx, int tsteps ) {

  int count = 0;
  for (int i = 0 ; i < tsteps; i++){
    heat_step(init, end, k, dx, dt, nx);
    //std::cout << end[1][1] << std::endl;
    if (end[1][1] != end[1][1]){ 
      std::cout << "diverged after " << count << " iterations";
      std::cout << std::endl;
      exit(1);
    }
    std::copy(end.begin(), end.end(), init.begin());
    count++;
  }
  return 0;
}


int heat_step(const doubleVector &current, doubleVector &next , const double &k,
   const double &dx, const double &dt, const int &nx) {

  std::cout << "iter" << std::endl;

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
        next[i][j] = c + dt * ( w + e + n + s - 4 * c) / (dx * dx);
      }
    }
  }

  return 0;

}
