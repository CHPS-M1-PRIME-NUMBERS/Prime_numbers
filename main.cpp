#include <iostream>
#include <fstream>
#include <chrono>
#include <gmpxx.h>

#include "memory_bound.hpp"
#include "euclide.hpp"
#include "millerRabin.hpp"
#include "pocklington.hpp"
#include "AKS.hpp"
#include "highly_composite.hpp"


std::ostream& operator<<(std::ostream& out, mpz_class& chiffre){
        out << chiffre.get_str();
        return out;
}

int main(int argc, char** argv){

    unsigned int iter, n, size, hc;
    // On récupère les arguments.
    if (argc == 1){ // Il n'y a pas d'arguments
        iter = 15;
        n = 7999993; //Valeur par défaut.
        size = 0;
    }
    else if (argc == 2){ // On connais seulement le nombre d'iérations
        iter = atoi(argv[1]);
        n = 7999993;
        size = 0;
    }
    else if (argc == 3 || argc == 4){ // Pas de tableau ou on connait sa taille mais pas de contenus.
        iter = atoi(argv[1]);
        n = atoi(argv[2]);
        size = 0;
    }
    else{
        iter = atoi(argv[1]);
        n = atoi(argv[2]);
        size = atoi(argv[3]);
        if (size != (argc-4-1)) size = argc-4-1; // Test fait dans le cas ou one n'utilise pas le script bash.
        hc = atoi(argv[argc-1]);
    }

    unsigned int tab[size];
    if (size != 0){
        for (int i = 0; i < size; i++){
            tab[i] = atoi(argv[i+4]);
        }
    }

    unsigned int avg = 0;
    bool result;
    int elapsed_time;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::ofstream file1("average.txt", std::ios::out | std::ios::trunc);
    std::ofstream file2("data.txt", std::ios::out | std::ios::trunc);
    std::ofstream file3("result.txt", std::ios::out | std::ios::trunc);

    {
        std::cout << "Test pour N = " << n << std::endl;

        std::cout << "==== Memory Bound || Eratosthene sieve ====" << std::endl;
        std::list<unsigned int> liste;
        for (int i = 0; i < iter; i ++){
		          start = std::chrono::system_clock::now();
		          memory_bound(n, &liste);
    		      end = std::chrono::system_clock::now();
	    	      elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
		          avg += elapsed_time;
	    }
	    avg /= iter;
        file3 << "Eratosthene sieve from 2 to " << n << ":" << std::endl << liste << std::endl;
	    std::cout << "Time elapsed average: " << avg << " ns" << std::endl;
        file1 << avg << " ";


        std::cout << "==== Pocklington ====" << '\n';
        avg = 0;
        for (int i = 0; i < iter; i ++){
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
        file1 << avg << " ";


        std::cout << "==== Miller Rabin ====" << '\n';
        unsigned int iterations = 50;
        avg = 0;
        for (int i = 0; i < iter; i ++){
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
        file1 << avg << " ";


        std::cout << "==== Computation Bound || Euclide ====" << '\n';
        avg = 0;
        for (int i = 0; i < iter; i ++){
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
        file1 << avg << " ";


        std::cout << "==== Computation Bound || Modulo ====" << '\n';
        avg = 0;
        for (int i = 0; i < iter; i ++){
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
        file1 << avg << " \n";

        std::cout << "==== AKS ====" << '\n';
        avg = 0;
        for (int i = 0; i < iter; i ++){
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
        file1 << avg << " \n";
    }

    if (size != 0){ // Le tableau n'est pas vide.
        std::cout << "\nTest pour un tableau de nombres premier :"<< std::endl;
        std::cout << "==== Memory Bound || Eratosthene sieve ====" << std::endl;
        std::list<unsigned int> liste;
        for (int i = 0; i < size; i++){
            tab[i] = atoi(argv[i+4]);
        }
        for (int i = 0; i < size; i ++){
    		start = std::chrono::system_clock::now();
    		memory_bound(tab[i], &liste);
    		end = std::chrono::system_clock::now();
    	    elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    		file2 << tab[i] << " " << elapsed_time << std::endl;
	    }file2 << std::endl;

       std::cout << "==== Pocklington ====" << '\n';
       for (int i = 0; i < size; i ++){
           start = std::chrono::system_clock::now();
           result = pocklington(tab[i]);
           end = std::chrono::system_clock::now();
           elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
           file2 << tab[i] << " " << elapsed_time << std::endl;
       }file2 << std::endl;

       std::cout << "==== Miller Rabin ====" << '\n';
       unsigned int iterations = 50;
       for (int i = 0; i < size; i ++){
           start = std::chrono::system_clock::now();
           result = millerRabin(tab[i], iterations);
           end = std::chrono::system_clock::now();
           elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
           file2 << tab[i] << " " << elapsed_time << std::endl;
       }file2 << std::endl;

       std::cout << "==== Computation Bound || Euclide ====" << '\n';
       for (int i = 0; i < size; i ++){
           start = std::chrono::system_clock::now();
           result = computation_bound_euclide(tab[i]);
           end = std::chrono::system_clock::now();
           elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
           file2 << tab[i] << " " << elapsed_time << std::endl;
       }file2 << std::endl;

       std::cout << "==== Computation Bound || Modulo ====" << '\n';
       for (int i = 0; i < size; i ++){
           start = std::chrono::system_clock::now();
           result = computation_bound_modulo(tab[i]);
           end = std::chrono::system_clock::now();
           elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
           file2 << tab[i] << " " << elapsed_time << std::endl;
       }file2 << std::endl;

       std::cout << "==== AKS ====" << '\n';
       for (int i = 0; i < size; i ++){
           start = std::chrono::system_clock::now();
           result = aks(tab[i]);
           end = std::chrono::system_clock::now();
           elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
           file2 << tab[i] << " " << elapsed_time << std::endl;
       }file2 << std::endl;
    }

    { // Nombre Hautement Composé
        std::cout << "\nTest Nombre Hautement Composé pour K = " << hc << std::endl;

        std::cout << "==== highly_composite_naive ====" << std::endl;
        avg = 0;
        for (int i = 0; i < iter; i ++){
		          start = std::chrono::system_clock::now();
		          result = highly_composite_naive(hc);
    		      end = std::chrono::system_clock::now();
	    	      elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
		          avg += elapsed_time;
	    }
	    avg /= iter;
        if(result) {
                file3 << "highly_composite_naive of " << hc << ":" << std::endl << "True" << std::endl;
        }else{
                file3 << "highly_composite_naive of " << hc << ":" << std::endl << "False" << std::endl;
        }
	    std::cout << "Time elapsed average:"  << avg << " ns" << std::endl;
        file1 << avg << " ";


        std::cout << "==== highly_composite_def ====" << std::endl;
        avg = 0;
        for (int i = 0; i < iter; i ++){
		          start = std::chrono::system_clock::now();
		          result = highly_composite_def(hc);
    		      end = std::chrono::system_clock::now();
	    	      elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
		          avg += elapsed_time;
	    }
	    avg /= iter;
        if(result) {
                file3 << "highly_composite_def of " << hc << ":" << std::endl << "True" << std::endl;
        }else{
                file3 << "highly_composite_def of " << hc << ":" << std::endl << "False" << std::endl;
        }
	    std::cout << "Time elapsed average:"  << avg << " ns" << std::endl;
        file1 << avg << " ";
    }
        return 0;
}
