#include <stdio.h>
#include <stdint.h>
#include "mpi.h"

int main(int argc, char** argv){
    uint64_t msg[20];
    int rank, size;
    MPI_Status status;
    double start_time, end_time;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank==0){

        printf("0 = Process %d is filling array...\n", rank);
        for (int i=0; i < 20; i++){
            msg[i]=i;
        }

        start_time = MPI_Wtime();

        printf("0 = sending array from process 0 to process 1\n");

        MPI_Send(msg, 20, MPI_LONG, 1, 99, MPI_COMM_WORLD);

        printf("0 = received array from process 1\n");

        MPI_Recv(msg, 20, MPI_LONG, 1, 99, MPI_COMM_WORLD, &status);
        end_time = MPI_Wtime();
        printf("0 = round trip took %f seconds \n", end_time-start_time);

        //printf("Process %d received the array, printing it...\n", rank);
    }else{
        MPI_Recv(msg, 20, MPI_LONG, 0, 99, MPI_COMM_WORLD, &status);
        printf("1 = received from process 0, send back to process 1\n");

        MPI_Send(msg, 20, MPI_LONG, 0, 99, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}