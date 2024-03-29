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


    char saludo[20] = "Soy el proceso ";
    char id [4];
    //printf("-- %d --\n",mytid);
    sprintf(id, "%d", mytid); 
    //printf("## %s ##\n",id);
    strcat(saludo, id);

            
    if(mytid == 0)
        ids = (char *) malloc (sizeof (saludo) * nproc);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(saludo, 20, MPI_CHAR, ids, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    if(mytid == 0){
        strcat(ids,"\0");
        int tam = 0;
        printf("Procesos dicen:\n");
        for(int i=0;i < nproc; i++){
            printf("    -%s\n", (ids + tam));
            tam = tam + strlen(ids + tam) + 1;
        }
        free (ids);
    }
    MPI_Finalize();
}


