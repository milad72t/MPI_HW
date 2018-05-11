// milad teimouri 95725127 Q1
// mpi_hello.c -o mpi_hello
// mpirun -f hosts -n 22 ./mpi_hello
// part 1 
#include <stdio.h>
#include <mpi.h>

// int main(int argc, char** argv) {

//     int myRank;
//     int NumProcess;
//     MPI_Init(&argc, &argv);
//     MPI_Comm_size(MPI_COMM_WORLD, &NumProcess);
//     MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

//     printf("Hello world. I am processor %d of %d\n", myRank, NumProcess);
//     MPI_Finalize();
//     return 0;
// }


//part 2 


int main(int argc, char** argv) {

    int myRank;
    int NumProcess;
    int RecvRank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &NumProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    if (myRank == 0){
    	printf("Hello world. I am processor %d of %d\n", myRank, NumProcess);
    	for (int i = 1; i < NumProcess; ++i)
    	{
    		MPI_Recv(&RecvRank , 1 , MPI_INT , i , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
    		printf("Hello world. I am processor %d of %d\n", RecvRank, NumProcess);
    	}
    }

    else {
    	MPI_Send(&myRank , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
    }


    MPI_Finalize();
    return 0;
}
