#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<mpi.h>
#include<malloc.h>




void main(int argc, char **argv){
    int nproc;
    int mytid;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &mytid);
    
    char *ids;

    char saludo[10] = "Hola";
            
    if(mytid == 0)
        ids = (char *) malloc (sizeof (saludo) * nproc);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(saludo, 4, MPI_CHAR, ids, 4, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    if(mytid == 0){
        strcat(ids,"\0");
        printf("Procesos dicen: %s\n", ids);
        free (ids);
    }
    MPI_Finalize();
}

