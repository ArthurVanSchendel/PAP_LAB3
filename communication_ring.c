#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char** argv){
    uint64_t msg[20];
    int rank, size;
    MPI_Status status;
    double start_time, end_time;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //int n = 5;   // user choice for number of nodes in the ring

    char token[200] = "I have read the message - P0";
    //fgets(token, 50, "I have read the message - P0");

    if (rank==0){

        start_time = MPI_Wtime();
        MPI_Send(token, 200, MPI_CHAR, rank+1, 99, MPI_COMM_WORLD);
        printf("im here\n");

        MPI_Recv(token, 200, MPI_CHAR, size-1, 99, MPI_COMM_WORLD, &status);
        end_time = MPI_Wtime();

        printf("0 = round trip took %f seconds \n", end_time-start_time);

    }else{
        MPI_Recv(token, 200, MPI_CHAR, rank-1, 99, MPI_COMM_WORLD, &status);
        //strcat(token, ("P%d", rank));
        //strcat(token, "Read\n");
        printf("process %d\n", rank);

        if (!(rank+1 >= size)){
            MPI_Send(token, 200, MPI_CHAR, rank+1, 99, MPI_COMM_WORLD);
        }else{
            MPI_Send(token, 200, MPI_CHAR, 0, 99, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}