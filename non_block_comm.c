#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char** argv){
    int rank, size;
    MPI_Status *status1;
    MPI_Status *status2;
    MPI_Status status[200] = {&status1, &status2};
    double start_time, end_time;
    MPI_Request *req1;
    MPI_Request *req2;
    MPI_Request req[200] = {&req1, &req2};

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char msg[200] = "read my message";

    if (rank==0){

        start_time = MPI_Wtime();
        MPI_Isend(msg, 200, MPI_CHAR, 1, 99, MPI_COMM_WORLD, &req1);
        MPI_Irecv(msg, 200, MPI_CHAR, 1, 99, MPI_COMM_WORLD, &status1);
        //MPI_Wait(req, status);

        end_time = MPI_Wtime();

        printf("0 = round trip took %f seconds \n", end_time-start_time);

    }else{
        MPI_Isend(msg, 200, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &req2);
        MPI_Irecv(msg, 200, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status2);
        //MPI_Wait(req, status);
    }
    MPI_Waitall(2, req, status); // blocked here
    MPI_Finalize();
}