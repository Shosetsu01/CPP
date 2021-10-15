#include <iostream>
#include <cstdlib>
#include <thread>
#include <ctime>
#include <vector>

/*. Найти скалярное произведение векторов A и B, заполненных случайными целыми числами от 0 до 100.
Длина векторов 100000 элементов.
Число потоков выбирается из множества {4; 10; 20; 40}.
Измерить время работы программы в каждом случае, построить график зависимости времени выполнения от числа потоков*/
using namespace std;
#define N 100000
#define M 4

vector <double> A(N), B(N), C(4);
double scalarmult, scalarmult1;

void func (int k) {
    for (int i = N/M*k; i < N/M*(k+1); i++){
        C[k] += A[i] * B[i];
    }
}

int main() {
    thread thread[M];

    srand(time(0));

    int mult = 0;

    clock_t start_time_noTread = clock();
        for (int i = 0; i < N; i++){
            A[i] = rand() % 101;
            B[i] = rand() % 101;
        }
        for (int i = 0; i < N; i++){
            mult += A[i] * B[i];
        }
    clock_t end_time_noTread = clock();
    double time_of_execution_noTread = double(end_time_noTread-start_time_noTread)/CLOCKS_PER_SEC;

    cout << mult << endl;
    cout << time_of_execution_noTread << endl;

    //замер времени начала
    clock_t start_time = clock();
        //запуск расчета с помощью потоков
        for (int i = 0; i < M; i++)
            thread[i] = std::thread(func, i);
        //завершение потоков
        for (int i = 0; i < M; i++)
            thread[i].join();
        //сложение полученных частей для получения общего скалярного произведения векторов
        for (int i = 0; i < M; i++){
        //cout « scalarmult3[i] « endl;
            scalarmult += C[i];
        }
    //замер конца времени и вывод полученного результата и времени рассчета
    clock_t end_time = clock();
    double time_of_execution = double(end_time-start_time)/CLOCKS_PER_SEC;
    cout << scalarmult << endl;
    cout << time_of_execution << endl;

return 0;
}