#ifndef MASTER_SLAVE
#define MASTER_SLAVE
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
#include "AKS_CONJECTURE.hpp"
#include "highly_composite.hpp"

#define MASTER_RANK 0
#define TAG_READY   1000
#define TAG_END     2000
#define TAG_DATA    3000

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress (double percentage)
{
        int val = (int) (percentage * 100);
        int lpad = (int) (percentage * PBWIDTH);
        int rpad = PBWIDTH - lpad;
        printf ("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
        std::cout.flush();
}

void highly_composite_main(int iter, unsigned long int val, std::ofstream& file1, std::ofstream& file2, std::ofstream& file3,
                           bool first_time, bool all_test_flag, bool highly_composite_def_flag, bool highly_composite_naive_flag);

void primality_test(int iter, unsigned long int val, std::ofstream& file1, std::ofstream& file2, std::ofstream& file3,
                    bool first_time, bool all_test_flag, bool aks_flag, bool conjecture_flag, bool euclide_flag, bool modulo_flag, bool mem_bound_flag,
                    bool pock_flag, bool miller_flag);

void run_slave(int slave_rank, int iter, bool first_time, bool all_test_flag, bool aks_flag, bool conjecture_flag, bool 			euclide_flag,bool modulo_flag, bool mem_bound_flag, bool pock_flag, bool miller_flag, bool highly_composite_def_flag,
			bool highly_composite_naive_flag)
{
        MPI_Status sta;
        int over = 0;
        unsigned long int val;

        char mem[32], data[32], result[32]; // make sure it's big enough
        snprintf(mem, sizeof(mem), "memory%d.txt", slave_rank);
        snprintf(data, sizeof(data), "data%d.txt", slave_rank);
        snprintf(result, sizeof(result), "result%d.txt", slave_rank);
        //On ouvre les flux des différents fichiers
        std::ofstream file1("mem.txt", std::ios::out | std::ios::trunc);
        std::ofstream file2("data.txt", std::ios::out | std::ios::trunc);
        std::ofstream file3("result.txt", std::ios::out | std::ios::trunc);

        do
        {
                // On envoit un message au "maitre" pour indiquer que je suis dispo
                MPI_Send(NULL, 0, MPI_BYTE, MASTER_RANK, TAG_READY, MPI_COMM_WORLD);
                // On attend l'arrivee d'un message de la part du maitre.
                MPI_Probe(MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &sta);

                if (sta.MPI_TAG >= TAG_DATA)
                {
                        MPI_Recv(&val, 1, MPI_UNSIGNED_LONG, MASTER_RANK, sta.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        primality_test(iter, val, file1, file2, file3, first_time, all_test_flag, aks_flag, conjecture_flag, 											euclide_flag, modulo_flag, mem_bound_flag, pock_flag, miller_flag);
                        highly_composite_main(iter, val, file1, file2, file3, first_time, all_test_flag,
                                              highly_composite_def_flag, highly_composite_naive_flag);
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

void run_master(int nslaves, unsigned long int range_start, unsigned long int range_end)
{
        MPI_Status sta;
        int slave_rank = -1;
        int cptr = 0;
        unsigned long int val = ((range_end - range_start)/100);

        // On lit la premiere donnee
        //val = read_data(&cptr, data, size);
		
        for(unsigned long int i = range_start; i<=range_end; i++) {
                // Le maitre attend qu'un esclave soit disponible
                MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, TAG_READY, MPI_COMM_WORLD, &sta);
		        if (val != 0){
		            if(i%((range_end - range_start)/100) == 0) {
		                    printProgress((double)(i-range_start)/(double)(range_end-range_start));
		            }
		        }
                slave_rank = sta.MPI_SOURCE;
                // Le maitre envoit les donnees a traiter a l'esclave avec l'etiquette TAG_DATA+cptr
                MPI_Send(&i, 1, MPI_UNSIGNED_LONG, slave_rank, TAG_DATA, MPI_COMM_WORLD);
        }

        /* Maintenant que toutes les donnees sont traitees
           il faut recevoir les messages TAG_READY en cours (autant que d'esclaves)
         */
        for(int i = 0; i < nslaves; i++)
        {
                MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, TAG_READY, MPI_COMM_WORLD, &sta);
                slave_rank = sta.MPI_SOURCE;
                // Le maitre envoit le message de fin du travail a l'esclave
                MPI_Send(NULL, 0, MPI_BYTE, slave_rank, TAG_END, MPI_COMM_WORLD);
        }
}


void highly_composite_main(int iter, unsigned long int val, std::ofstream& file1, std::ofstream& file2, std::ofstream& file3,
                           bool first_time, bool all_test_flag, bool highly_composite_def_flag, bool highly_composite_naive_flag)
{
        unsigned long int max, min, avg = 0;
        bool result;
        int elapsed_time;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        //Lance le test de Nombre hautement composé naive si l'option est choisie
        if(highly_composite_naive_flag == true || all_test_flag == true) {
                //std::cout << "==== highly_composite_naive ====" << std::endl;
                avg = 0;
                for (int i = 0; i < iter; i++) {
                        start = std::chrono::system_clock::now();
                        result = highly_composite_naive(val);
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
                        file3 << "highly_composite_naive " << val << " True" << std::endl;
                }else{
                        file3 << "highly_composite_naive " << val << " False" << std::endl;
                }
                //std::cout << "highly_composite_naive " << val << " === Time elapsed average: "  << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }
        //Lance le test de Nombre hautement composé définition si l'option est choisie
        if(highly_composite_def_flag == true || all_test_flag == true) {
                //std::cout << "==== highly_composite_def ====" << std::endl;
                avg = 0;
                for (int i = 0; i < iter; i++) {
                        start = std::chrono::system_clock::now();
                        result = highly_composite_def(val);
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
                        file3 << "highly_composite_def " << val << " True" << std::endl;
                }else{
                        file3 << "highly_composite_def " << val << " False" << std::endl;
                }
                //std::cout << "highly_composite_def " << val << " === Time elapsed average: "  << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

}

void primality_test(int iter, unsigned long int val, std::ofstream& file1, std::ofstream& file2, std::ofstream& file3,
                    bool first_time, bool all_test_flag, bool aks_flag, bool conjecture_flag, bool euclide_flag, bool modulo_flag, bool mem_bound_flag,
                    bool pock_flag, bool miller_flag)
{

        unsigned long int avg = 0, max, min;
        bool result;
        int elapsed_time;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        //Lance le crible d'Eratosthene si l'option est choisie
        if(mem_bound_flag == true || all_test_flag == true) {
                unsigned long int n_temp = val;
                if(n_temp>1000000000) {
                        n_temp = 1000000000;
                }
                //std::cout << "==== Memory Bound || Eratosthene sieve pour N = " << val << " ====" << std::endl;
                std::list<unsigned long int> liste;
                for (int i = 0; i < iter; i++) {
                        // Entoure la fonction des indications temporelles de début et de fin d'execution (de même pour les autres algorithmes)		
                        liste.clear();
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
                //std::cout << "Eratosthene : " << val << " === Time elapsed average: " << avg << " µs"  << " and Memory used: " << n_temp * sizeof(bool)/2 << " bytes" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test de Pocklington si l'option est choisie
        if(pock_flag == true || all_test_flag == true) {
                //std::cout << "==== Pocklington  pour N = " << val << " ====" << '\n';
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
                //std::cout << "Pocklington : " << val << " === Time elapsed average: " << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test de Miller-Rabin si l'option est choisie
        if(miller_flag == true || all_test_flag == true) {
                //std::cout << "==== Miller Rabin pour N = " << val << " ====" << '\n';
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
                //std::cout << "Miller Rabin : " << val << " === Time elapsed average: " << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test d'Euclide si l'option est choisie
        if(euclide_flag == true || all_test_flag == true) {
                //std::cout << "==== Computation Bound || Euclide pour N = " << val << " ====" << '\n';
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
                //std::cout << "Computation_Bound_Euclide : " << val << " === Time elapsed average: " << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test de Modulo si l'option est choisie
        if(modulo_flag == true || all_test_flag == true) {
                //std::cout << "==== Computation Bound || Modulo pour N = " << val << " ====" << '\n';
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
                //std::cout << "Computation_Bound_Modulo : " << val << " === Time elapsed average: " << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }

        //Lance le test d'AKS si l'option est choisie
        if(aks_flag == true || all_test_flag == true) {
                //std::cout << "==== AKS pour N = " << val << " ====" << '\n';
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
                //std::cout << "AKS : " << val << " === Time elapsed average: " << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }
        
        if(conjecture_flag == true || all_test_flag == true) {
                //std::cout << "==== AKS Conjecture pour N = " << val << " ====" << '\n';
                avg = 0;
                for (int i = 0; i < iter; i++) {
                	if ( val < 3) break;
                        start = std::chrono::system_clock::now();
                        result = conjecture(val);
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
                        file3 << "AKS Conjecture" << val << " True" << std::endl;
                }else{
                        file3 << "AKS Conjecture" << val << " False" << std::endl;
                }
                avg /= iter;
                //std::cout << "AKS Conjecture : " << val << " === Time elapsed average: " << avg << " µs" << std::endl;
                file2 << val << " " << avg << " " << min << " " << max << std::endl;
        }
}

#endif
