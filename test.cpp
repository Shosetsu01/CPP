#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std;
#define row 10
#define column 10

int main()
{   
    int arr[row][column];
    int sum_of_row[row] {0};

    #pragma omp parallel num_threads(4)
    { 
    // задаем массив вручную
        double start_time, end_time, tick;
        start_time = omp_get_wtime();

        #pragma omp for
        for (int i = 0; i < row; i++){
            // cout << "Вводим " << i + 1 << " строку\n"<< std::endl;
            for (int j = 0; j < column; j++){
                // cout << "Введите целое число ";
                // cin >> arr[i][j];
                arr[i][j] = rand()%10;
                sum_of_row[i] += arr[i][j];
            }
            cout << endl;
        }

        end_time = omp_get_wtime();
        tick = omp_get_wtick();
        printf("Время на замер времени %lf\n", end_time-start_time);
        printf("Точность таймера %lf\n", tick);
    }
// выводим полученный массив
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            cout.width(7);
            cout << arr[i][j];
        }
        cout << " summ of this row = " << sum_of_row[i];
        cout << endl;
    }
    cout << endl;

// выводим массив, вычитая из элементов побочной диагонали сумму каждой строки
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            cout.width(7);
            if (i + j == row - 1){
                arr[i][j] -= sum_of_row[i];
            }
            cout << arr[i][j];
        }
        cout << endl;
    }
    return 0;
}
