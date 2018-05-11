// milad teimouri 95725127 Q4 part b
// sudo mpicc mpi_arrayProcess.c -o mpi_arrayProcess -lm
// mpirun -f hosts -n 7 ./mpi_arrayProcess
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>


int array[2000][2000];

int main(int argc, char** argv) {

    int N = 2000;
    double sum=0;
    double totalSum;
    int myRank;
    int NumProcess;
    int chunk,offset,remaining;
    MPI_Init(&argc, &argv);
    double start = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &NumProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    chunk = N / NumProcess;
    remaining = N % NumProcess;
    if (myRank == 0){
    	for (int i=0 ; i<N ; i++){
            for (int j=0 ; j<N ; j++){
                array[i][j] = i*j;
            }
        }
        offset = chunk + remaining;
        for (int process=1; process<NumProcess; process++){
            MPI_Send(&array[offset][0] , N*chunk , MPI_INT , process , 0 , MPI_COMM_WORLD);
            offset += chunk;
        }
        for (int row=0 ; row<(chunk+remaining) ; row++){
            for (int col=0 ; col<N ; col++){
                sum += (double) sqrt(array[row][col]);
            }
        }
        printf("calculated sum By process %d  =  %f \n",myRank,sum );
	}
    else {
        int recvArray[chunk][N]; 
        MPI_Recv(&recvArray[0][0], N*chunk, MPI_INT, 0, 0, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        for (int row=0 ; row<chunk ; row++){
            for (int col=0 ; col<N ; col++){
                sum += (double) sqrt(recvArray[row][col]);
            }
        }
        printf("calculated sum By process %d  =  %f \n",myRank,sum );

    }

    MPI_Reduce(&sum, &totalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myRank==0){
        double finish = MPI_Wtime();
        printf("calculated sum by all processes = %f \nin %fs wall time\n",totalSum , finish - start);
    }


    
    MPI_Finalize();
    return 0;
}