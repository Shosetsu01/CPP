// 6. О чемпионате мира. На чемпионате мира по футболу используется электронный мяч. На поле 22 игрока.
// Каждый игрок бьет по мячу (сообщение MPI) со случайной силой (в ньютонах) по 1 разу. 
// Мяч получает удары и определяет, с какой силой его ударили, выводя сообщение на экран.

#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
	int rang, numfr, tag=0;
	int rc= MPI_Init(&argc, &argv);
	MPI_Status stat;
	MPI_Comm_size(MPI_COMM_WORLD,&numfr); 
	MPI_Comm_rank(MPI_COMM_WORLD,&rang); 
	
	if(rang ==0){
		int zak;
		for(int i=1; i < numfr; i++){
			rc = MPI_Recv(&zak,1,MPI_INT,i,tag,MPI_COMM_WORLD,&stat);	
			sleep(0.1);
			cout << " принял " << zak <<endl;
			rc = MPI_Send(&zak,1,MPI_INT,i,tag,MPI_COMM_WORLD);
		}
		
		for(int i=1; i < numfr; i++){
			rc = MPI_Recv(&zak,1,MPI_INT,i,tag,MPI_COMM_WORLD,&stat);	
			sleep(0.1);
			cout << " принял " << zak <<endl;
			rc = MPI_Send(&zak,1,MPI_INT,i,tag,MPI_COMM_WORLD);
		}
	}
	
	if(rang != 0){
		int blud;
		blud = rang;
		rc = MPI_Send(&blud,1,MPI_INT,0,tag,MPI_COMM_WORLD);
		rc = MPI_Recv(&blud,1,MPI_INT,0,tag,MPI_COMM_WORLD,&stat);	
		//cout << rang << " принял " << blud <<endl;
		
		blud = rang + 100;
		rc = MPI_Send(&blud,1,MPI_INT,0,tag,MPI_COMM_WORLD);
		rc = MPI_Recv(&blud,1,MPI_INT,0,tag,MPI_COMM_WORLD,&stat);
		//cout << rang << " принял " << blud <<endl;
	}
	
	MPI_Finalize();
	return 0;
}