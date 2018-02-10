#include <iostream>

#include <mpi.h>

#include "pocklington.hpp"

#define MASTER 0

#define CONTINUE 100
#define STOP 99
#define READY 98

#define MAX 1000

void master();
void slave(int rang);
int test(int nombre);
void read_data(int * donnees, int * taille);

int main(int argc, char ** argv){
        MPI_Init(&argc, &argv);
        int rang, nproc;

        MPI_Comm_rank(MPI_COMM_WORLD, &rang);
        MPI_Comm_size(MPI_COMM_WORLD, &nproc);

        if(rang == MASTER) {
                std::cout << nproc << " process." << std::endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);


        if(rang == MASTER) {
                master();
        }
        else{
                slave(rang);
        }

        MPI_Finalize();
}

void master(){
        std::cout << "P" << MASTER << " : ready." << std::endl;
        int rangEsclave;
        int * donnees = NULL;
        int taille;
        int i;

        int nproc;
        MPI_Comm_size(MPI_COMM_WORLD, &nproc);

        read_data(donnees, &taille);

        while(taille > 0) {
                MPI_Recv(&rangEsclave, 1, MPI_INT, MPI_ANY_SOURCE, READY, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(donnees, taille, MPI_INT, rangEsclave, CONTINUE, MPI_COMM_WORLD);
                read_data(donnees, &taille);
        }

        for(i = 1; i<nproc; i++) {
                MPI_Recv(&rangEsclave, 1, MPI_INT, MPI_ANY_SOURCE, READY, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(NULL, 0, MPI_INT, rangEsclave, STOP, MPI_COMM_WORLD);
        }
        delete[] donnees;
        std::cout << "Master (" << MASTER << ") : done." << std::endl;
}

void slave(int rang){
        std::cout << "P" << rang << " : ready." << std::endl;
        int tag = CONTINUE; int taille = 0; int * nombreAVerifier = NULL; int i;
        MPI_Status status;
        MPI_Send(&rang, 1, MPI_INT, MASTER, READY, MPI_COMM_WORLD);

        while(tag >= CONTINUE) {
                MPI_Probe(MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                tag = status.MPI_TAG;
                if(status.MPI_TAG >= CONTINUE) {
                        MPI_Get_count(&status, MPI_INT, &taille);
                        nombreAVerifier = new int[taille]();
                        MPI_Recv(nombreAVerifier, taille, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

                        for(i = 0; i < taille; i++) {
                                std::cout << nombreAVerifier[i] << " : " << pocklington(nombreAVerifier[i]) << "." << std::endl;
                        }
                        MPI_Ssend(&rang, 1, MPI_INT, MASTER, READY, MPI_COMM_WORLD);
                        tag = status.MPI_TAG;
                        delete[] nombreAVerifier;
                }
        }
        printf("P%d : done.\n", rang);
}

void read_data(int * donnees, int * taille){
        *taille = MAX;
        donnees = new int[*taille]();
        for(int i = 0; i < MAX; i++) {
                donnees[i] = i;
        }
}
