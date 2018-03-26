#include "eratosthene.hpp"
#include "omp.h"

#include <iostream>
#include <fstream>
#include <chrono>

// Implemenation du crible d'Eratosthene. Retourne un tableau de booleen indiquant la primalité des nombres de 2 à N.
bool* eratosthene(unsigned long int number){
    unsigned long int i, memory_size = number/2;
    bool* isPrime = new bool[memory_size]; //Tableau indiquant si un nombre i est premier ou non, true si premier, false sinon.
    const long int NumberSqrt = (long int)sqrt((long double)number); // Cette variable est là car Open MP n'accepte pas i*i <= number

    // Initialisation du tableau
    #pragma omp parallel for
    for(i = 0; i <= memory_size; i++)
        isPrime[i] = true;

    #pragma omp parallel for schedule(dynamic)
    for(i = 3; i <= NumberSqrt; i+=2){
        // On avance si la case actuel n'est pas à vraie.
        while( (i <= number) && !(isPrime[i/2]) )
            i += 2;
        // On commence à i pour ne pas visiter plusieurs fois la meme case
        for(int j = i*i; j <= number; j+= 2*i)
            isPrime[j/2] = false;
    }
    return isPrime;
}
/*
int main(){
    unsigned long int nb = 9990887, memory_size=nb/2;
    bool* isPrime = new bool[memory_size];

    int elapsed_time;
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    isPrime = eratosthene(nb);
    end = std::chrono::system_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout << "Time elapsed average: " << elapsed_time << " µs" << std::endl;

    return 0;
}*/
