#include <stdio.h>
#include <stdint.h>
#include "mpi.h"

int main(int argc, char** argv){
    uint64_t msg[20];
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank==0){
        printf("Process %d is sending empty array !", rank);
        MPI_Send(msg, 20, MPI_LONG, 1, 99, MPI_COMM_WORLD);

        MPI_Recv(msg, 20, MPI_LONG, 1, 99, MPI_COMM_WORLD, &status);
        printf("Process %d received the array, printing it...\n", rank);
        for (int i =0; i < 20; i++){
            printf("Process %d received %lu !\n", rank, msg[i]);
            msg[i]=i;
        }
    }else{
        MPI_Recv(msg, 20, MPI_LONG, 0, 99, MPI_COMM_WORLD, &status);
        
        printf("Filling array...\n");
        for (int i=0; i < 20; i++){
            printf("Process %d received %lu !\n", rank, msg[i]);
            msg[i]=i;
        }
        MPI_Send(msg, 20, MPI_LONG, 0, 99, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}