// milad teimouri 95725127 Q2
// mpicc mpi_calcPi.c -o ./mpi_calcPi -lm
// mpirun -f hosts -n 16 ./mpi_calcPi {Count}
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>


int main(int argc, char** argv) {

    int myRank;
    int NumProcess;
    int count;
    if (argc==1) count=1000000; 
    else count = atoi(argv[1]);
    int inQuarter=0;
    MPI_Init(&argc, &argv);
   	double start = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &NumProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    if (myRank == 0){
    	for (int i = 1; i < NumProcess; ++i)
    	{
    		int RecvInQuarter = 0;
    		MPI_Recv(&RecvInQuarter , 1 , MPI_INT , i , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
    		inQuarter = inQuarter + RecvInQuarter;
    	}
    	int AllCount = count*(NumProcess-1);
    	printf("pi : %.10f\n", 4*((double)inQuarter/AllCount));  
	}
    else {
    	srand((int)time(0)+myRank*NumProcess);
    	double x;
    	double y;
    	double distance;
     	for (int i=0 ; i<count ;i++){
	      x = ((double) rand() / (RAND_MAX));
	      y =((double) rand() / (RAND_MAX));
	      distance = sqrt(pow(x,2) + pow(y,2));
	      if (distance <1) {
	        inQuarter++;
	      }
  		}

  		MPI_Send(&inQuarter , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
  		printf("in Quarter count: %d from : %d count By process %d \n",inQuarter , count,myRank);
    }

    double finish = MPI_Wtime();
    printf("total time elapsed in process %d : %.8f \n",myRank , finish - start );
    MPI_Finalize();
    return 0;
}