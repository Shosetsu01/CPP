// ShishkoLab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 
// Напишите программу с использованием MPI, моделирующую ситуацию: есть 4
// бригады по 20 рабочих (процессы). Каждый рабочий отсылает по одному 100
// сообщений-вопросов случайным рабочим из других бригад. Те должны ответит
// на вопрос. Программа не должна попадать в ситуацию “deadlock”.

#include <iostream>
#include "mpi.h"

#define WORKER_COUNT 20

//mpiexec -n 4 ShiskoLab7

using namespace std;

void Helper(int mainRank, int process_Rank, int worker[WORKER_COUNT])
{
    int flagExit = 1;
    int randomIndexWorker;
    int randomIndexBrigade;
    int requestRank;
    int message;
    int index;
    int responce;

    if (process_Rank == mainRank)
    {
        for (int i = 0; i < WORKER_COUNT; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                while ((randomIndexBrigade = 1 + rand() % 3) == process_Rank) // brigade[1 .. 3]
                { }
                MPI_Bcast(&randomIndexBrigade, 1, MPI_INT, mainRank, MPI_COMM_WORLD); //сообщаем всем процессам, норме бригады, куда отправляем
                randomIndexWorker = rand() % WORKER_COUNT; // [0 .. 19]
                MPI_Send(&randomIndexWorker, 1, MPI_INT, randomIndexBrigade, 0, MPI_COMM_WORLD); //отправляем конкретному рабочему
                MPI_Send(&worker[i], 1, MPI_INT, randomIndexBrigade, 1, MPI_COMM_WORLD); //отправляем само сообщение

                MPI_Recv(&responce, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //получаем ответ от рабочего, кому слали
                if (i == WORKER_COUNT - 1 && j == 99)
                    flagExit = 0;
                MPI_Bcast(&flagExit, 1, MPI_INT, mainRank, MPI_COMM_WORLD); //можно ли другим процессам выходить из цикла?
            }
        }
    }
    else
    {
        while (flagExit)
        {
            MPI_Bcast(&requestRank, 1, MPI_INT, mainRank, MPI_COMM_WORLD); //слушаем какой бригаде придет сообщение
            if (requestRank == process_Rank)
            {
                MPI_Recv(&index, 1, MPI_INT, mainRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //получаем индекс, какому рабочему адресована отправка
                MPI_Recv(&message, 1, MPI_INT, mainRank, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //получаем само сообщение

                MPI_Send(&worker[index], 1, MPI_INT, mainRank, 2, MPI_COMM_WORLD); //отправляем ответ конкретного рабочего
            }

            MPI_Bcast(&flagExit, 1, MPI_INT, mainRank, MPI_COMM_WORLD); //слушаем, можно ли выходить из циклов while
        }
    }
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    int process_Rank, size_Of_Cluster;
    double result = 0;
    int worker[WORKER_COUNT];

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    for (int i = 0; i < WORKER_COUNT; i++)
        worker[i] = rand() % 20; //сообщения которые будет рассылать рабочий

    Helper(0, process_Rank, worker);
    Helper(1, process_Rank, worker);
    Helper(2, process_Rank, worker);
    Helper(3, process_Rank, worker);

    MPI_Finalize();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
