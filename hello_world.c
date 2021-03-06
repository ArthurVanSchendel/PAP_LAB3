#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv){

    int rank, size;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank%2==0){
        printf("Hello, I'm an even rank process! %d/%d\n", rank, size);

    }else{
        printf("Hello, I'm an odd rank process! %d/%d\n", rank, size);

    }

    //printf("Hello, I'm Process %d/%d\n", rank, size);
    
    MPI_Finalize();
    return 0;
}
