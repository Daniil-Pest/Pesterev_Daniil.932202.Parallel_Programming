#include <mpi.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv); // инициализации MPI
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	srand(time(NULL)); // разный seed для псевдослучайных значений
	double y[5]; // создание массива с пятью компонентами
	double x = cos((rank + 1) * rand() / (RAND_MAX + 0.0)); // вычисление по формуле из условия
	for (int k = 0; k < 5; k++)
		y[k] = pow(cos(x), k + 1); // вычисление по формуле из условия
	
	double result[5 * size]; // создание объединённого массива
	MPI_Gather(y, 5, MPI_DOUBLE, result, 5, MPI_DOUBLE, 0, MPI_COMM_WORLD); // слияние в объединённый массив нулевого процесса
	
	if (rank == 0) // на нулевом процессе
	{
		double max = -INFINITY;
		for (int i = 0; i < size; i++) // поиск максимального произведения
		{
			double multiple = 1;
			for (int j = 0; j < 5; j++)
				multiple *= result[i + j]; // произведения из последовательностей по пять элементов
			if (multiple > max)
				max = multiple;
		}
		printf("The maximum element of the multiplications is %f.\n", max); // вывод
	}
	
	MPI_Finalize(); // очистка состояний MPI
	return 0;
}
