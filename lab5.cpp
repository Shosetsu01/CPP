// 6. О чемпионате мира. На чемпионате мира по футболу используется электронный мяч. На поле 22 игрока.
// Каждый игрок бьет по мячу (сообщение MPI) со случайной силой (в ньютонах) по 1 разу. 
// Мяч получает удары и определяет, с какой силой его ударили, выводя сообщение на экран.
//  mpic++ -o lab5 lab5.cpp && mpirun -np 23 ./lab5

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
			MPI_Recv(&myach,1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
            // sleep(1);	
			cout << status.MPI_SOURCE << " " << " Удар! " << myach << "н" <<endl;
			MPI_Send(&myach,1,MPI_INT,status.MPI_SOURCE,tag,MPI_COMM_WORLD);
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


// #include "mpi.h"
// #include <stdio.h>
// #include <stdlib.h>     
// #include <time.h>  
// #include <iostream>
// #include <unistd.h>

// using namespace std;

// int main(int argc, char **argv) {
//     srand (time(NULL));

//     int rank, size, tag = 0;
//     MPI_Status status[23];
//     MPI_Request reqs[23];
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//     if (rank == 0) {
//         int myach[23];
// 		for(int i=1; i < size; i++){
// 			MPI_Irecv(&myach[i],1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&reqs[i]);
//             // sleep(1);	
// 			cout << i << " " << " Удар! " << myach[i] << "н" <<endl;
// 			MPI_Isend(&myach[i],1,MPI_INT,status.MPI_SOURCE,tag,MPI_COMM_WORLD,&reqs[i+2]);
// 		}
//     } 
//     if (rank != 0) {
//         int silaUdara;
// 		silaUdara = rand() % 100 + 1;
//         MPI_Isend(&silaUdara,1,MPI_INT,0,tag,MPI_COMM_WORLD,&reqs);
// 		MPI_Irecv(&silaUdara,1,MPI_INT,0,tag,MPI_COMM_WORLD,&reqs);	 
//     }
//     MPI_Waitall(rank, &reqs, &status);
    
//     // cout << rank << " ";

//     MPI_Finalize();
// 	return 0;
// }

