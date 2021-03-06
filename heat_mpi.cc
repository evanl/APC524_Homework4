#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>
#include "mpi.h"
#include "heat_mpi_functions.h"

using std::vector;

const double PI = 3.14159265359;

int main (int argc, char *argv[] ){

  time_t beginTime; 
  beginTime = time(NULL);

  // process command line argument. 
  if (argc != 3){
    printf( "Invalid input, please execute in the following way: \n  ./heat_mpi <number of grid points> <number of processes> ");
    return 1;
  }
  const int nx = atoi(argv[1]);
  const int num_processors = atoi(argv[2]);

  // initialize physical constants. 
  const double dx = PI / (nx - 1 );
  const double k = 0.25 ;
  const double dt = dx * dx / (4.0 * k);
  const double tmax = 0.5 * PI * PI / k;
  const int tsteps = ceil(tmax/dt);

  std::cout << "dx = " << dx << std::endl;
  std::cout << "k  = " << k << std::endl;
  std::cout << "tmax = " << tmax << std::endl;
  std::cout << "dt = " << dt << std::endl;
  std::cout << "tsteps = " << tsteps << std::endl;
  std::cout << "num_processors = " << num_processors << std::endl;

  
  /* initialize process in each thread.  */
  int numtasks, rank, next, prev, rc, nxproc;
  double proc_origin, taverage;
  MPI_Status stats ;

  double lbuf[nx], rbuf[nx];
  double lsend[nx], rsend[nx];
  nxproc = nx / num_processors;

  
  // parallel code 
  rc = MPI_Init( &argc, &argv);
  if (rc != MPI_SUCCESS){
    std::cout << "error starting MPI program" << std::endl;
    MPI_Abort(MPI_COMM_WORLD, rc);
  }
  //distribute array rank and number of total. 
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  prev = rank-1;
  next = rank+1;
  if( rank == 0  )
  {
    prev = numtasks - 1;
  }
  if( rank == (numtasks-1) )
  {
    next = 0;
  }

  // initialize arrays and buffers. 
  doubleArray arr1, arr2;
  arr1 = doubleArrayCreate(nx,nxproc);
  arr2 = doubleArrayCreate(nx,nxproc);
 
  proc_origin = rank * PI / numtasks;

  heat_initialize(arr1, nx, nxproc, proc_origin, dx);
  heat_initialize(arr2, nx, nxproc, proc_origin, dx); 

  std::cout << "for rank " << rank << " there are " <<  nxproc; 
  std::cout << " grid cells beginning at  " << proc_origin << std::endl;
  int token = 0;

   //solve routine. 
  for (int i = 0 ; i < tsteps; i++){
    if ( i % 2 == 0 ) {
      
      for( int i=0 ; i < nx ; i++ )
      {
        rsend[i] = arr1[0][i]; 
        lsend[i] = arr1[nxproc-1][i];
      }

      MPI_Send(&lsend, nx , MPI_DOUBLE, prev, token, MPI_COMM_WORLD );
      MPI_Recv(&rbuf, nx, MPI_DOUBLE, next, token, MPI_COMM_WORLD, &stats);
      
      MPI_Send(&rsend,        nx , MPI_DOUBLE, next, token, MPI_COMM_WORLD );
      MPI_Recv(&lbuf, nx, MPI_DOUBLE, prev, token, MPI_COMM_WORLD, &stats);
      
      heat_step(arr1, arr2, k, dx, dt, nx, nxproc, lbuf, rbuf);
    }else {
      
      for( int i=0 ; i < nx ; i++ )
      {
        rsend[i] = arr2[0][i]; 
        lsend[i] = arr2[nxproc-1][i];
      }

      MPI_Send(&lsend, nx , MPI_DOUBLE, prev, token, MPI_COMM_WORLD );
      MPI_Recv(&rbuf, nx, MPI_DOUBLE, next, token, MPI_COMM_WORLD, &stats);
      
      MPI_Send(&rsend,        nx , MPI_DOUBLE, next, token, MPI_COMM_WORLD );
      MPI_Recv(&lbuf, nx, MPI_DOUBLE, prev, token, MPI_COMM_WORLD, &stats);
  
      heat_step(arr2, arr1, k, dx, dt, nx, nxproc, lbuf, rbuf);
    }
  }

  // Write the file to output.dat
  heat_write( arr2, dx, nx, nxproc ,rank, proc_origin);
        
  /* get local averages and sum up to get total average */ 

  taverage = heat_average(arr2, nx, nxproc); 

  std::cout << "t_average = " << taverage << std::endl;

  MPI_Finalize();

  std::cout << "time to compute [seconds] = "; 
  std::cout << ((double)(time(NULL)-beginTime));
  std::cout << std::endl;
  
  doubleArrayRemove(arr1, nx, nxproc);
  doubleArrayRemove(arr2, nx, nxproc);

  return 0;
}
