// Откомпилируйте последовательную программу с включением опций поддержки технологии OpenMP и запустите код с использованием нескольких нитей, задайте разное количество нитей. Сравните время выполнения необходимых вычислений для последовательной версии программы и для параллельной (с любым количеством потоков по вашему усмотрению).
// При помощи функций OpenMP определите время, необходимое для работы функции omp_get_wtick(). Хватает ли для этого точности системного таймера?
// 3. В массиве А(6,6) элементы каждого столбца расположить в порядке возрастания.


#include <iostream>
#include <time.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <omp.h>
#include <fstream>

using namespace std;

#define N 1000

int arr[N][N];

int main() {
    ofstream outf("lab3.txt");

    if (!outf)
	{
		// то выводим сообщение об ошибке и выполняем функцию exit()
		cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
		exit(1);
	}

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand()%100-100;
            outf << setw(4) << arr[i][j];
        }
        outf << endl; 
    }

    outf << endl; 
   

    #pragma omp parallel num_threads(2)
    { 
        double start_time, end_time, tick;
        start_time = omp_get_wtime();

        #pragma omp for 
        // сортировка элементов столбцов массива по возрастанию 
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                for (int k = 0, temp = 0; k < N; k++) {
                    if (arr[i][k] > arr[i + 1][k]) {
                        // меняем элементы местами
                        temp = arr[i][k];
                        arr[i][k] = arr[i + 1][k];
                        arr[i + 1][k] = temp;
                    }
                }
            }
        }

        end_time = omp_get_wtime();
        tick = omp_get_wtick();
    
        printf("Время на замер времени %lf\n", end_time-start_time);
        printf("Точность таймера %lf\n", tick);
        // outf << "Время на замер времени = " << end_time-start_time << endl;
        // outf << "Точность таймера = " << tick << endl;
    }

    for (int i = 0; i < N; i++) {
        outf << setw(4) << i+1 << " "; 
        for (int j = 0; j < N; j++) {
            outf << setw(4) << arr[i][j];
        }
        outf << endl; 
    }
    

    return 0;
}



