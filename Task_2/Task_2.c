// переделать всё
// оформл
// переделать вывод?
// суммы (переменные)

#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	srand(time(NULL));
	double x_k = 0.0;	   //.0?
	double sum = 0.0;	   //.0?
	double sum_temp = 0.0; //.0?
	double min = INFINITY; // тип?
	printf("Process %d:\t", rank);
	for (int k = 1; k <= 5; k++)
	{
		double x_k = sin(k * (rank + 1) * rand() / (RAND_MAX + 0.0)); //.0 (моё)?
		printf("%f\t", x_k);
		if (rank == 1)
			sum_temp += x_k;
		if ((rank == 2) && (min > x_k))
			min = x_k;
	}
	printf("\n");
	
	MPI_Reduce(&sum_temp, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0)
		printf("\nThe sum of the first process numbers is %f.\n", sum);
	
	MPI_Finalize();
	return 0;
}
