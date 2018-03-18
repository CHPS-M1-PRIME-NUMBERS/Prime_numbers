#include "eratosthene.hpp"
#include <stdio.h>

bool* eratosthene(unsigned long int number){
        bool* isPrime = new bool[number+1]; //Tableau indiquant si un nombre i est premier ou non, true si premier, false sinon.
        unsigned long int i;

        // Initialisation du tableau
        for(i = 3; i <= number; i+= 2)
            isPrime[i] = true;
        isPrime[2] = true;

        for(i = 3; i*i <= number; i+=2){
            // On avance si la case actuel n'est pas à vraie.
            while( (i <= number) && !(isPrime[i]) )
                i += 2;
            // On commence à i pour ne pas visiter plusieurs fois la meme case
            for(int j = i; j*i <= number; j++)
                isPrime[j * i] = false;
        }
        return isPrime;
}
