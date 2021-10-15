#include <iostream>
#include <cstdlib>
#include <thread>
#include <ctime>
#include <vector>

using namespace std;
#define N 1000
#define M 4
vector <int> A(N), B(N), maxC(M);

void func (int k) {
    int q = 0;
    for (int i = N/M*k; i < N/M*(k+1); i++){
        if (A[i] > q) {
            q = A[i];
        }
    }
    maxC[k] = q;
}

int main() {
    thread thread[M];

    srand(time(0));

    for (int i = 0; i < N; i++){
        A[i] = rand() % 100001;
    }

    int maxA = A[0], maxATr = 0;

    //Однопоточное вычисление

    clock_t start_time_noTread = clock();
        for (int i = 0; i < N; i++){
            if (A[i] > maxA) {
                maxA = A[i];
            }
        }
    clock_t end_time_noTread = clock();
    double time_of_execution_noTread = double(end_time_noTread-start_time_noTread)/CLOCKS_PER_SEC;

    cout << maxA << endl;
    cout << time_of_execution_noTread << endl;


    //Многопоточное вычисление

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
            if (maxC[i] >= maxATr) {
                maxATr = maxC[i];
            }
        }
    //замер конца времени и вывод полученного результата и времени рассчета
    clock_t end_time = clock();
    double time_of_execution = double(end_time-start_time)/CLOCKS_PER_SEC;
    
    cout << maxATr << endl;
    cout << time_of_execution << endl;

    return 0;
}                                  