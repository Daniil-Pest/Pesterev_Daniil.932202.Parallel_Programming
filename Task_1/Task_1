#include <mpi.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	srand(time(NULL));
	double y[5];
	double x = cos((rank + 1) * rand() / (RAND_MAX + 0.0));
	for (int k = 0; k < 5; k++)
		y[k] = pow(cos(x), k + 1);
	
	double result[5 * size];
	MPI_Gather(y, 5, MPI_DOUBLE, result, 5, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	if (rank == 0)
	{
		double max = -INFINITY;
		for (int i = 0; i < size; i++)
		{
			double multiple = 1;
			for (int j = 0; j < 5; j++)
				multiple *= result[i + j];
			if (multiple > max)
				max = multiple;
		}
		printf("The maximum element of the multiplications is %f.\n", max);
	}
	
	MPI_Finalize();
	return 0;
}
