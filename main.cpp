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
        unsigned int n;
        bool all_test_flag = false;
        bool aks_flag = false;
        bool euclide_flag = false;
        bool mem_bound_flag = false;
        bool pock_flag = false;
        bool miller_flag = false;
        bool highly_composite_flag = false;

        //Check si il existe des arguments, si oui recupère le nombre n et le nombre d'iterations
        if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ) {
                cerr << "No argument provided!" << endl;
                return 1;
        }
        else {
                iter = atoi(argv[argc-2]);
                n = strtoul(argv[argc-1], NULL, 0);
        }

        // Empeche GetOpt d'afficher des erreurs:
        opterr = 0;

        // On récupère les options
        while ( (opt = getopt(argc, argv, "akeumpih")) != -1 ) {    // for each option...
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
                        highly_composite_flag = true;
                        break;
                case '?': // option inconnue
                        cerr << "Unknown option: '" << char(optopt) << "'!" << endl;
                        break;
                }
        }

        unsigned int avg = 0;
        bool result;
        int elapsed_time;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::ofstream file1("average.txt", std::ios::out | std::ios::trunc);
        std::ofstream file2("data.txt", std::ios::out | std::ios::app);
        std::ofstream file3("result.txt", std::ios::out | std::ios::trunc);

        {
                std::cout << "||||||||||||||  Test pour N = " << n << " ||||||||||||||" << std::endl;

                if(mem_bound_flag == true || all_test_flag == true) {
                        unsigned int n_temp = n;
                        if(n_temp>8000000000) {
                                n_temp = 8000000000;
                        }
                        std::cout << "==== Memory Bound || Eratosthene sieve ====" << std::endl;
                        std::list<unsigned int> liste;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                memory_bound(n_temp, &liste);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        avg /= iter;
                        file3 << "Eratosthene sieve from 2 to " << n_temp << ":" << std::endl << liste << std::endl;
                        std::cout << "Time elapsed average: " << avg << " ns" << std::endl;
                        std::cout << "Memory used: " << n_temp * sizeof(bool) << " bytes" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;
                }

                if(pock_flag == true || all_test_flag == true) {
                        std::cout << "==== Pocklington ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = pocklington(n);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        if(result) {
                                file3 << "Pocklington of " << n << ":" << std::endl << "True" << std::endl;
                        }else{
                                file3 << "Pocklington of " << n << ":" << std::endl << "False" << std::endl;
                        }
                        std::cout << "Time elapsed average: " << avg << " ns" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;
                }

                if(miller_flag == true || all_test_flag == true) {
                        std::cout << "==== Miller Rabin ====" << '\n';
                        unsigned int iterations = 50;
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = millerRabin(n, iterations);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        if(result) {
                                file3 << "Miller Rabin of " << n << ":" << std::endl << "True" << std::endl;
                        }else{
                                file3 << "Miller Rabin of " << n << ":" << std::endl << "False" << std::endl;
                        }
                        std::cout << "Time elapsed average: " << avg << " ns" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;
                }

                if(euclide_flag == true || all_test_flag == true) {
                        std::cout << "==== Computation Bound || Euclide ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = computation_bound_euclide(n);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        if(result) {
                                file3 << "Computation Bound || Euclide of " << n << ":" << std::endl << "True" << std::endl;
                        }else{
                                file3 << "Computation Bound || Euclide of " << n << ":" << std::endl << "False" << std::endl;
                        }
                        std::cout << "Time elapsed average: " << avg << " ns" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;
                }

                if(euclide_flag == true || all_test_flag == true) {
                        std::cout << "==== Computation Bound || Modulo ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = computation_bound_modulo(n);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        if(result) {
                                file3 << "Computation Bound || Modulo of " << n << ":" << std::endl << "True" << std::endl;
                        }else{
                                file3 << "Computation Bound || Modulo of " << n << ":" << std::endl << "False" << std::endl;
                        }
                        std::cout << "Time elapsed average: " << avg << " ns" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;
                }

                if(aks_flag == true || all_test_flag == true) {
                        std::cout << "==== AKS ====" << '\n';
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = aks(n);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        if(result) {
                                file3 << "AKS of " << n << ":" << std::endl << "True" << std::endl;
                        }else{
                                file3 << "AKS of " << n << ":" << std::endl << "False" << std::endl;
                        }
                        std::cout << "Time elapsed average: " << avg << " ns" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;
                }
        }

        {       // Nombre Hautement Composé
                if(highly_composite_flag == true || all_test_flag == true) {
                        std::cout << "==== highly_composite_naive ====" << std::endl;
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = highly_composite_naive(n);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        avg /= iter;
                        if(result) {
                                file3 << "highly_composite_naive of " << n << ":" << std::endl << "True" << std::endl;
                        }else{
                                file3 << "highly_composite_naive of " << n << ":" << std::endl << "False" << std::endl;
                        }
                        std::cout << "Time elapsed average:"  << avg << " ns" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;


                        std::cout << "==== highly_composite_def ====" << std::endl;
                        avg = 0;
                        for (int i = 0; i < iter; i++) {
                                start = std::chrono::system_clock::now();
                                result = highly_composite_def(n);
                                end = std::chrono::system_clock::now();
                                elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                                avg += elapsed_time;
                        }
                        avg /= iter;
                        if(result) {
                                file3 << "highly_composite_def of " << n << ":" << std::endl << "True" << std::endl;
                        }else{
                                file3 << "highly_composite_def of " << n << ":" << std::endl << "False" << std::endl;
                        }
                        std::cout << "Time elapsed average:"  << avg << " ns" << std::endl;
                        file1 << avg << std::endl;
                        file2 << avg << std::endl;
                }
        }
        file2 << std::endl;
        std::cout << std::endl;
        return 0;
}
