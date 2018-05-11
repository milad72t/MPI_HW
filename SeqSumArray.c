// milad teimouri 95725127 Q4 part a
// sudo gcc SeqSumArray.c -o SeqSumArray -lm
// ./SeqSumArray
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>


// Sequential Array Sum

int array[2000][2000];

int main(int argc, char** argv) {

	int N =2000;
	clock_t begin = clock();    
	for (int i=0 ; i<N ; i++){
		for (int j=0 ; j<N ; j++){
			array[i][j] = i*j;
		}
	}
	double sum = 0;
	// for (int row=0 ; row<N ; row++){
	// 	for (int col=0 ; col<N ; col++){
	// 		sum += (double) sqrt(array[row][col]);
	// 	}
	// }
	for (int col=0 ; col<N ; col++){
		for (int row=0 ; row<N ; row++){
			sum += (double) sqrt(array[row][col]);
		}
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("sum of array : %f in %f second\n", sum, time_spent);
    return 0;
}