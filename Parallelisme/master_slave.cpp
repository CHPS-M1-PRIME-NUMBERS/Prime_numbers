#include <mpi.h>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <assert.h>
#include <list>
#include <chrono>

#include "memory_bound.hpp"
#include "euclide.hpp"
#include "millerRabin.hpp"
#include "pocklington.hpp"
#include "AKS.hpp"
#include "highly_composite.hpp"

#define MASTER_RANK 0
#define TAG_READY   1000
#define TAG_END     2000
#define TAG_DATA    3000
/*
void highly_composite_main(int iter, unsigned long int val, std::ofstream file1, std::ofstream file2, std::ofstream file3,
    bool highly_composite_def_flag, bool highly_composite_naive_flag)
{
    unsigned long int n, max, min;

    //Lance le test de Nombre hautement composé naive si l'option est choisie
    if(highly_composite_naive_flag == true || all_test_flag == true) {
        std::cout << "==== highly_composite_naive ====" << std::endl;
        avg = 0;
        for (int i = 0; i < iter; i++) {
            start = std::chrono::system_clock::now();
            result = highly_composite_naive(n);
            end = std::chrono::system_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
            if (!first_time) {
                first_time = true;
                max = elapsed_time;
                min = max;
            }
            if (max < elapsed_time) max = elapsed_time;
            if (min > elapsed_time) min = elapsed_time;
            avg += elapsed_time;
        }
        avg /= iter;
        if(result) {
            file3 << "highly_composite_naive " << n << " True" << std::endl;
        }else{
            file3 << "highly_composite_naive " << n << " False" << std::endl;
        }
        std::cout << "Time elapsed average: "  << avg << " µs" << std::endl;
        file2 << n << " " << avg << " " << min << " " << max << std::endl;
    }
    //Lance le test de Nombre hautement composé définition si l'option est choisie
    if(highly_composite_def_flag == true || all_test_flag == true) {
        std::cout << "==== highly_composite_def ====" << std::endl;
        avg = 0;
        for (int i = 0; i < iter; i++) {
            start = std::chrono::system_clock::now();
            result = highly_composite_def(n);
            end = std::chrono::system_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
            if (!first_time) {
                first_time = true;
                max = elapsed_time;
                min = max;
            }
            if (max < elapsed_time) max = elapsed_time;
            if (min > elapsed_time) min = elapsed_time;
            avg += elapsed_time;
        }
        avg /= iter;
        if(result) {
            file3 << "highly_composite_def " << n << " True" << std::endl;
        }else{
            file3 << "highly_composite_def " << n << " False" << std::endl;
        }
        std::cout << "Time elapsed average: "  << avg << " µs" << std::endl;
        file2 << n << " " << avg << " " << min << " " << max << std::endl;
    }

}
*/
void primality_test(int iter, unsigned long int val, std::ofstream& file1, std::ofstream& file2, std::ofstream& file3,
    bool first_time, bool all_test_flag, bool aks_flag, bool euclide_flag, bool modulo_flag, bool mem_bound_flag,
    bool pock_flag, bool miller_flag)
    {

        unsigned long int avg = 0, max, min;
        bool result;
        int elapsed_time;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        std::cout << "||||||||||||||  Test pour N = " << val << " ||||||||||||||" << std::endl;


        //Lance le crible d'Eratosthene si l'option est choisie
        if(mem_bound_flag == true || all_test_flag == true) {
            unsigned long int n_temp = val;
            if(n_temp>1000000000) {
                n_temp = 1000000000;
            }
            std::cout << "==== Memory Bound || Eratosthene sieve ====" << std::endl;
            std::list<unsigned long int> liste;
            for (int i = 0; i < iter; i++) {
                // Entoure la fonction des indications temporelles de début et de fin d'execution (de même pour les autres algorithmes)
                start = std::chrono::system_clock::now();
                memory_bound(n_temp, &liste);
                end = std::chrono::system_clock::now();
                elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
                if (!first_time) {
                    first_time = true;
                    max = elapsed_time;
                    min = max;
                }
                if (max < elapsed_time) max = elapsed_time;
                if (min > elapsed_time) min = elapsed_time;
                avg += elapsed_time;
            }
            avg /= iter;
            //Affichage et incription des résultats dans les fichiers (de même pour les autres algorithmes)
            file1 << "Eratosthene sieve from 2 to " << n_temp << ":" << std::endl << liste << std::endl;
            std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
            std::cout << "Memory used: " << n_temp * sizeof(bool) << " bytes" << std::endl;
            file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test de Pocklington si l'option est choisie
        if(pock_flag == true || all_test_flag == true) {
            std::cout << "==== Pocklington ====" << '\n';
            avg = 0;
            for (int i = 0; i < iter; i++) {
                start = std::chrono::system_clock::now();
                result = pocklington(val);
                end = std::chrono::system_clock::now();
                elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
                if (!first_time) {
                    first_time = true;
                    max = elapsed_time;
                    min = max;
                }
                if (max < elapsed_time) max = elapsed_time;
                if (min > elapsed_time) min = elapsed_time;
                avg += elapsed_time;
            }
            if(result) {
                file3 << "Pocklington " << val << " True" << std::endl;
            }else{
                file3 << "Pocklington " << val << " False" << std::endl;
            }
            avg /= iter;
            std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
            file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test de Miller-Rabin si l'option est choisie
        if(miller_flag == true || all_test_flag == true) {
            std::cout << "==== Miller Rabin ====" << '\n';
            unsigned long int iterations = 500;
            avg = 0;
            for (int i = 0; i < iter; i++) {
                start = std::chrono::system_clock::now();
                result = millerRabin(val, iterations);
                end = std::chrono::system_clock::now();
                elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
                if (!first_time) {
                    first_time = true;
                    max = elapsed_time;
                    min = max;
                }
                if (max < elapsed_time) max = elapsed_time;
                if (min > elapsed_time) min = elapsed_time;
                avg += elapsed_time;
            }
            if(result) {
                file3 << "Miller_Rabin " << val << " True" << std::endl;
            }else{
                file3 << "Miller_Rabin " << val << " False" << std::endl;
            }
            avg /= iter;
            std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
            file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test d'Euclide si l'option est choisie
        if(euclide_flag == true || all_test_flag == true) {
            std::cout << "==== Computation Bound || Euclide ====" << '\n';
            avg = 0;
            for (int i = 0; i < iter; i++) {
                start = std::chrono::system_clock::now();
                result = computation_bound_euclide(val);
                end = std::chrono::system_clock::now();
                elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
                if (!first_time) {
                    first_time = true;
                    max = elapsed_time;
                    min = max;
                }
                if (max < elapsed_time) max = elapsed_time;
                if (min > elapsed_time) min = elapsed_time;
                avg += elapsed_time;
            }
            if(result) {
                file3 << "Computation_Bound_Euclide " << val << " True" << std::endl;
            }else{
                file3 << "Computation_Bound_Euclide " << val << " False" << std::endl;
            }
            avg /= iter;
            std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
            file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test de Modulo si l'option est choisie
        if(modulo_flag == true || all_test_flag == true) {
            std::cout << "==== Computation Bound || Modulo ====" << '\n';
            avg = 0;
            for (int i = 0; i < iter; i++) {
                start = std::chrono::system_clock::now();
                result = computation_bound_modulo(val);
                end = std::chrono::system_clock::now();
                elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
                if (!first_time) {
                    first_time = true;
                    max = elapsed_time;
                    min = max;
                }
                if (max < elapsed_time) max = elapsed_time;
                if (min > elapsed_time) min = elapsed_time;
                avg += elapsed_time;
            }
            if(result) {
                file3 << "Computation_Bound_Modulo " << val << " True" << std::endl;
            }else{
                file3 << "Computation_Bound_Modulo " << val << " False" << std::endl;
            }
            avg /= iter;
            std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
            file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test d'AKS si l'option est choisie
        if(aks_flag == true || all_test_flag == true) {
            std::cout << "==== AKS ====" << '\n';
            avg = 0;
            for (int i = 0; i < iter; i++) {
                start = std::chrono::system_clock::now();
                result = aks(val);
                end = std::chrono::system_clock::now();
                elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
                if (!first_time) {
                    first_time = true;
                    max = elapsed_time;
                    min = max;
                }
                if (max < elapsed_time) max = elapsed_time;
                if (min > elapsed_time) min = elapsed_time;
                avg += elapsed_time;
            }
            if(result) {
                file3 << "AKS " << val << " True" << std::endl;
            }else{
                file3 << "AKS " << val << " False" << std::endl;
            }
            avg /= iter;
            std::cout << "AKS : " << val << " || Time elapsed average: " << avg << " µs" << std::endl;
            file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }
    }

void run_slave(int slave_rank, int iter, bool first_time, bool all_test_flag, bool aks_flag, bool euclide_flag,
    bool modulo_flag, bool mem_bound_flag, bool pock_flag, bool miller_flag, bool highly_composite_def_flag,
    bool highly_composite_naive_flag)
{
    MPI_Status sta;
    int over = 0;
    unsigned long int val;

    //On ouvre les flux des différents fichiers
    std::ofstream file1("memory.txt", std::ios::out | std::ios::trunc);
    std::ofstream file2("data.txt", std::ios::out | std::ios::app);
    std::ofstream file3("result.txt", std::ios::out | std::ios::app);

    do
    {
        // On envoit un message au "maitre" pour indiquer que je suis dispo
        MPI_Send(NULL, 0, MPI_BYTE, MASTER_RANK, TAG_READY, MPI_COMM_WORLD);
        // On attend l'arrivee d'un message de la part du maitre.
        MPI_Probe(MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &sta);

        if (sta.MPI_TAG >= TAG_DATA)
        {
            MPI_Recv(&val, 1, MPI_UNSIGNED_LONG, MASTER_RANK, sta.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            primality_test(iter, val, file1, file2, file3, first_time, all_test_flag, aks_flag, euclide_flag,
                modulo_flag, mem_bound_flag, pock_flag, miller_flag);
        }
        else
        {
            assert(sta.MPI_TAG == TAG_END);

            // L'etiquette TAG_END indique la fin du travail de l'esclave.
            MPI_Recv(NULL, 0, MPI_BYTE, MASTER_RANK, TAG_END, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            over = 1;
        }
    }
    while(!over);
}

// Fonctio utilisé par le maitre pour lire une donnée dans un tableau de données.
unsigned long int read_data(int *p_cptr, unsigned long int data[], int size)
{
    if (*p_cptr < size) {
        (*p_cptr)++;
        return data[*p_cptr-1];
    }
    else{
        return -1;
    }
}

void run_master(int nslaves, unsigned long int data[], int size)
{
    MPI_Status sta;
    int slave_rank = -1;
    int cptr = 0;
    unsigned long int val;

    // On lit la premiere donnee
    val = read_data(&cptr, data, size);

    while(val != -1){
        // Le maitre attend qu'un esclave soit disponible
        MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, TAG_READY, MPI_COMM_WORLD, &sta);
        slave_rank = sta.MPI_SOURCE;
        // Le maitre envoit les donnees a traiter a l'esclave avec l'etiquette TAG_DATA+cptr
        MPI_Send(&val, 1, MPI_UNSIGNED_LONG, slave_rank, TAG_DATA, MPI_COMM_WORLD);
        // On prepare la prochaine donnee
        val = read_data(&cptr, data, size);
    }

    /* Maintenant que toutes les donnees sont traitees
       il faut recevoir les messages TAG_READY en cours (autant que d'esclaves)
    */
    for(int i = 0 ; i < nslaves ; i++)
    {
        MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, TAG_READY, MPI_COMM_WORLD, &sta);
        slave_rank = sta.MPI_SOURCE;
        // Le maitre envoit le message de fin du travail a l'esclave
        MPI_Send(NULL, 0, MPI_BYTE, slave_rank, TAG_END, MPI_COMM_WORLD);
    }
}
/*
int main(int argc, char **argv)
{
    int rank, size;
    double t1, t2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == MASTER_RANK) t1 = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == MASTER_RANK)
    {
        unsigned long int data[8] = {3, 97, 1097, 50023, 9990887, 25003151, 33083221, 40003387};
        run_master(size-1, data, 8);
    }
    else
    {
        run_slave(rank);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == MASTER_RANK){
        t2 = MPI_Wtime();
        std::cout << "TEMPS TOTAL : " << t2 - t1 << "s\n";
    }
    MPI_Finalize();

    return 0;
}*/
