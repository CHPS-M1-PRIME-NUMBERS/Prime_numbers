#include <iostream>
#include <fstream>
#include <chrono>

#include "memory_bound.hpp"
#include "euclide.hpp"
#include "millerRabin.hpp"
#include "pocklington.hpp"
#include "AKS.hpp"
#include "highly_composite.hpp"

#include <unistd.h>

int main(int argc, char** argv){

        int opt;
        int iter;
        unsigned long int n, max, min;
        bool first_time = false;
        bool all_test_flag = false;
        bool aks_flag = false;
        bool euclide_flag = false;
        bool modulo_flag = false;
        bool mem_bound_flag = false;
        bool pock_flag = false;
        bool miller_flag = false;
        bool highly_composite_def_flag = false;
        bool highly_composite_naive_flag = false;

        //Check si il existe des arguments, si oui recupère le nombre n et le nombre d'iterations
        if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ) {
                std::cerr << "No argument provided!" << std::endl;
                return 1;
        }
        else {
                iter = atoi(argv[argc-2]);
                n = strtoul(argv[argc-1], NULL, 0);
        }

        // Empeche GetOpt d'afficher des erreurs:
        opterr = 0;

        // On récupère les options
        while ( (opt = getopt(argc, argv, "akeoumpihH")) != -1 ) {    // for each option...
                switch ( opt ) {
                case 'a':
                        all_test_flag = true;
                        break;
                case 'k':
                        aks_flag = true;
                        break;
                case 'e':
                        euclide_flag = true;
                        break;
                case 'o':
                        modulo_flag = true;
                        break;
                case 'm':
                        mem_bound_flag = true;
                        break;
                case 'p':
                        pock_flag = true;
                        break;
                case 'i':
                        miller_flag = true;
                        break;
                case 'h':
                        highly_composite_naive_flag = true;
                        break;
                case 'H':
                        highly_composite_def_flag = true;
                        break;
                case '?': // option inconnue
                        std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
                        break;
                }
        }

        unsigned long int avg = 0;
        bool result;
        int elapsed_time;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        //On ouvre les flux des différents fichiers
        std::ofstream file1("memory.txt", std::ios::out | std::ios::trunc);
        std::ofstream file2("data.txt", std::ios::out | std::ios::app);
        std::ofstream file3("result.txt", std::ios::out | std::ios::app);


        {
                std::cout << "||||||||||||||  Test pour N = " << n << " ||||||||||||||" << std::endl;


                //Lance le crible d'Eratosthene si l'option est choisie
                if(mem_bound_flag == true || all_test_flag == true) {
                        unsigned long int n_temp = n;
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
                        file2 << n << " " << avg << " " << min << " " << max << std::endl;
                }

                //Lance le test de Pocklington si l'option est choisie
                if(pock_flag == true || all_test_flag == true) {
                        std::cout << "==== Pocklington ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = pocklington(n);
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
                                file3 << "Pocklington " << n << " True" << std::endl;
                        }else{
                                file3 << "Pocklington " << n << " False" << std::endl;
                        }
                        avg /= iter;
                        std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
                        file2 << n << " " << avg << " " << min << " " << max << std::endl;
                }

                //Lance le test de Miller-Rabin si l'option est choisie
                if(miller_flag == true || all_test_flag == true) {
                        std::cout << "==== Miller Rabin ====" << '\n';
                        unsigned long int iterations = 500;
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = millerRabin(n, iterations);
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
                                file3 << "Miller_Rabin " << n << " True" << std::endl;
                        }else{
                                file3 << "Miller_Rabin " << n << " False" << std::endl;
                        }
                        avg /= iter;
                        std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
                        file2 << n << " " << avg << " " << min << " " << max << std::endl;
                }

                //Lance le test d'Euclide si l'option est choisie
                if(euclide_flag == true || all_test_flag == true) {
                        std::cout << "==== Computation Bound || Euclide ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = computation_bound_euclide(n);
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
                                file3 << "Computation_Bound_Euclide " << n << " True" << std::endl;
                        }else{
                                file3 << "Computation_Bound_Euclide " << n << " False" << std::endl;
                        }
                        avg /= iter;
                        std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
                        file2 << n << " " << avg << " " << min << " " << max << std::endl;
                }

                //Lance le test de Modulo si l'option est choisie
                if(modulo_flag == true || all_test_flag == true) {
                        std::cout << "==== Computation Bound || Modulo ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = computation_bound_modulo(n);
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
                                file3 << "Computation_Bound_Modulo " << n << " True" << std::endl;
                        }else{
                                file3 << "Computation_Bound_Modulo " << n << " False" << std::endl;
                        }
                        avg /= iter;
                        std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
                        file2 << n << " " << avg << " " << min << " " << max << std::endl;
                }

                //Lance le test d'AKS si l'option est choisie
                if(aks_flag == true || all_test_flag == true) {
                        std::cout << "==== AKS ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = aks(n);
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
                                file3 << "AKS " << n << " True" << std::endl;
                        }else{
                                file3 << "AKS " << n << " False" << std::endl;
                        }
                        avg /= iter;
                        std::cout << "Time elapsed average: " << avg << " µs" << std::endl;
                        file2 << n << " " << avg << " " << min << " " << max << std::endl;
                }
        }

        {       //Lance le test de Nombre hautement composé naive si l'option est choisie
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
        std::cout << std::endl;

        //Fin du programme
        return 0;
}
