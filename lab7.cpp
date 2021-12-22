// Лаб7 Вар6. Напишите программу с использованием MPI, моделирующую ситуацию: есть 2
// бригады по 20 рабочих (процессы). Каждый рабочий отсылает 1 сообщение-вопрос
// каждому из рабочих другой бригады в строго заданном порядке, но может
// как получить, так и не получить ответ. Реализовать 5 кругов обмена
// сообщениями, то есть каждый рабочий должен отправить 95 сообщений-вопросов,
// программа не должна попадать в ситуацию “deadlock”.

#include "mpi.h"
#include <time.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));

    int rank;
    MPI_Status status;
    MPI_Request reqs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int brigada = 1; brigada <= 2; brigada++) {
        if (brigada == 1) {
            if (rank == 0)
            {
                for (int i = 0; i < 20; i++)
                {   
                    cout << endl;
                    for (int j = 0; j < 20; j++)
                    {
                        int otvet;
                        MPI_Irecv(&otvet, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs);
                        cout << brigada << " - " << i + 1 << " - " << j + 1 << " - otvet = " << otvet << endl;
                        MPI_Isend(&otvet, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs);
                    }
                }
            }
            else
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        int message;
                        message = rand() % 100 + 1;
                        MPI_Isend(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs);
                        MPI_Irecv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs);
                    }
                }
            }
        } else {
            if (rank == 1)
            {
                for (int i = 0; i < 20; i++)
                {   
                    cout << endl;
                    for (int j = 0; j < 20; j++)
                    {
                        int otvet;
                        MPI_Irecv(&otvet, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &reqs);
                        cout << brigada << " - " << i + 1 << " - " << j + 1 << " - otvet = " << otvet << endl;
                        MPI_Isend(&otvet, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &reqs);
                    }
                }
            }
            else
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        int message;
                        message = rand() % 100 + 1;
                        MPI_Isend(&message, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &reqs);
                        MPI_Irecv(&message, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &reqs);
                    }
                }
            }
        }
    }

    MPI_Waitall(size, reqs, status);

    MPI_Finalize();
    return 0;
}

// int rank;
// MPI_Status stats[2];
// MPI_Request reqs[2];
// MPI_Init(&argc, &argv);
// MPI_Comm_rank(MPI_COMM_WORLD, &rank);
// // MPI_Comm_size(MPI_COMM_WORLD, &size);

// int otvmes;
// MPI_Irecv(&otvmes, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs[0]);

// for (int i = 0; i < 20; i++)
// {
//     int message = rand() % 1000 + 100;
//     MPI_Isend(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs[1]);
//     MPI_Irecv(&message, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &reqs[1]);
// }

// int flag;

// for (int i = 0; i < 20; i++)
// {
//     // int received;
//     // MPI_Irecv(&received, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &reqs);
//     // cout << i + 1 << " message: " << received << endl;

//     if ((MPI_Test(&reqs[0], &flag, &stats[0]) == MPI_SUCCESS) && (stats[0].MPI_SOURCE = 0))
//     // && (status.MPI_SOURCE >= 0))
//     {
//         int otvet = rand() % 100 + 1;
//         // Если сообщение получено, то отвечаем ей (сообщение-ответ - тег 1)
//         MPI_Isend(&otvet, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &reqs[1]);
//     }
// }

// MPI_Barrier(MPI_COMM_WORLD);

// for (int i = 0; i < 20; i++)
// {

// 	// Если сообщение получено, выводим одно сообщение
// 	if ((MPI_Test(&reqs[1], &flag, &stats[1]) == MPI_SUCCESS) && (stats[1].MPI_SOURCE >= 0))
// 	{
// 		cout << "Fish number " << " thinks that fish number " << i << " - good fish!" << endl;
// 	}
// 	// Иначе - другое
// 	else
// 	{
// 		cout << "Fish number " << " thinks that fish number " << i << " - smels fishy..." << endl;
// 	}

// 	// Синхронизируем вывод
// 	MPI_Barrier(MPI_COMM_WORLD);
// }
