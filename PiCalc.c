
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main (int argc, char** argv)
{
	
		int count;
		if (argc==1) count=1000000; 
		else count = atoi(argv[1]);
		srand((int)time(0));
		int inQuarter=0;
		int outQuarter=0;
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
			else {
				outQuarter++;
			}
		}
		printf("pi : %.10f\n", 4*((double)inQuarter/count));

		return 0;	
}