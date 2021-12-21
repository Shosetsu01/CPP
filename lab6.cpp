// 6. МПИ Составить программу, решающую систему линейных 
// алгебраических уравнений методом простых итераций. 
// Для распараллеливания использовать MPI и коллективные операции.
// 
// Распределение данных - горизонтальными полосами. (Запуск программы на 4 процессах).  
// Для запуска mpic++ test.cpp && mpiexec -n 4 ./a.out


#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h> 
#include <string.h>

// Каждая ветвь задает размеры своих полос матрицы MA и вектора правой части. 
#define M 16
#define N 4
#define EL(x) (sizeof(x) / sizeof(x[0]))
#define ABS(X) ((X) < 0 ? -(X) : (X))
// Задаем необходимую точность приближенных корней  
#define E 0.0001
// Задаем шаг итерации  
#define T 0.1
// Описываем массивы для полос исходной матрицы - MA, вектора правой части - F, значения приближений на предыдущей итерации - Y и текущей - Y1, результата умножения матрицы коэффициентов на вектор - S и всего вектора значения приближений на предыдущей итерации - V.  
static double MA[N][M], F[N], Y[N], Y1[N], S[N], V[M];

int main(int argc, char **argv) {
	int i, j, z, H, MyP, size, v;
	int *index, *edges;
	MPI_Comm comm_gr; 
	int reord = 1; 
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	// Выделяем память под массивы для описания вершин и ребер в топологии полный граф  
	index = (int *)malloc(size * sizeof(int));
	edges = (int *)malloc(size * (size - 1) * sizeof(int));
	// Заполняем массивы для описания вершин и ребер для топологии полный граф и задаем топологию "полный граф".  
	for (i = 0; i < size; i++) {
		index[i] = (size - 1) * (i + 1);
		v = 0;
		for (j = 0; j < size; j++)
		{
			if (i != j)
				edges[i * (size - 1) + v++] = j;
		}
	}
	MPI_Graph_create(MPI_COMM_WORLD, size, index, edges, reord, &comm_gr);
	// каждая ветвь определяет свой номер (ранг)  
	MPI_Comm_rank(comm_gr, &MyP);
	// Каждая ветвь генерирует свои полосы матрицы A и свой отрезок вектора правой части. (По диагонали исходной матрицы - числа = 2, остальные числа = 1).  
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if ((N * MyP + i) == j)
				MA[i][j] = 2.0;
			else
				MA[i][j] = 1.0;
		}
		F[i] = M + 1;
	}
	// Каждая ветвь задает начальное приближение корней.  
	for (i = 0; i < N; i++)
		Y1[i] = 0.3;
	// Начало вычислений  
	do
	{
		for (i = 0; i < N; i++)
		{
			S[i] = 0.0;
			Y[i] = Y1[i];
		}
		// В каждой ветви формируем весь вектор предыдущей итерации и умножаем матрицу коэффициентов на этот вектор  
		MPI_Allgather(Y, EL(Y), MPI_DOUBLE, V, EL(Y), MPI_DOUBLE, comm_gr);
		for (j = 0; j < N; j++)
			for (i = 0; i < M; i++)
				S[j] += MA[j][i] * V[i];
		z = 0; // Флаг завершения вычислений всеми ветвями  
		for (i = 0; i < N; i++)
		{
			Y1[i] = Y[i] - T * (S[i] - F[i]);
			if (ABS(Y1[i] - Y[i]) > E)
				z = 1;
		}
		// Суммируем все флаги (по всем ветвям) и результат записываем в H в каждой ветви  
		MPI_Allreduce(&z, &H, 1, MPI_INT, MPI_SUM, comm_gr);
	} while (H > 0);
	printf("MyP = %d\n", MyP);
	// Все ветви для контроля печатают свои первые четыре значения корня  
	printf("Rez MyP = %d Y0=%f Y1=%f Y2=%f Y3=%f\n", MyP, Y[0], Y[1], Y[2], Y[3]);
	// Все ветви завершают выполнение  
	MPI_Comm_free(&comm_gr);
	MPI_Finalize();
	return (0);
}