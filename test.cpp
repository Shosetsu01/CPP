// 6. О чемпионате мира. На чемпионате мира по футболу используется электронный мяч. На поле 22 игрока.
// Каждый игрок бьет по мячу (сообщение MPI) со случайной силой (в ньютонах) по 1 разу. 
// Мяч получает удары и определяет, с какой силой его ударили, выводя сообщение на экран.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>     
#include <time.h>  
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {
    srand (time(NULL));

    int rank, size, tag = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        int myach;
		for(int i=1; i < size; i++){
			MPI_Recv(&myach,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
            // sleep(1);	
			cout << " Удар! " << myach << "н" <<endl;
			MPI_Send(&myach,1,MPI_INT,i,tag,MPI_COMM_WORLD);
		}
    } 
    if (rank != 0) {
        int silaUdara;
		silaUdara = rand() % 100 + 1;
        MPI_Send(&silaUdara,1,MPI_INT,0,tag,MPI_COMM_WORLD);
		MPI_Recv(&silaUdara,1,MPI_INT,0,tag,MPI_COMM_WORLD,&status);	 
    }
    
    // cout << rank << " ";

    MPI_Finalize();
	return 0;
}