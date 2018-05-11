// milad teimouri 95725127 Q3
// sudo mpicc mpi_sumId.c -o ./mpi_sumId
// mpirun -f hosts -n 16 ./mpi_sumId
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>


// Ring Topology

int main(int argc, char** argv) {

    int myRank;
    int NumProcess;
    
    MPI_Init(&argc, &argv);
   	double start = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &NumProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int sum = 0;
    int SumValue = 0;
    if (myRank != 0){
    	MPI_Recv(&SumValue, 1, MPI_INT, myRank-1, 0, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        printf("Process %d received SumValue %d from process %d\n", myRank, SumValue, myRank - 1);
	}
    SumValue = SumValue + myRank;
    MPI_Send(&SumValue, 1, MPI_INT, (myRank + 1) % NumProcess, 0, MPI_COMM_WORLD);

    if (myRank == 0) {
        MPI_Recv(&SumValue, 1, MPI_INT, NumProcess - 1, 0, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        printf("SumValue of processes rank = %d\n", SumValue);
        double finish = MPI_Wtime();
        printf("total time elapsed in process %d : %.8f \n",myRank , finish - start );
    }

    MPI_Finalize();
    return 0;
}





// with AllReduce Function
/*
int main(int argc, char** argv) {

    int myRank;
    int NumProcess;    
    MPI_Init(&argc, &argv);
    double start = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &NumProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int SumValue;

    MPI_Allreduce(&myRank, &SumValue, 1 , MPI_INT , MPI_SUM , MPI_COMM_WORLD);

    if (myRank == 0) {
        printf("SumValue of processes rank = %d\n", SumValue);
        double finish = MPI_Wtime();
        printf("total time elapsed in process %d : %.8f \n",myRank , finish - start );
    }

    MPI_Finalize();
    return 0;
}
*/