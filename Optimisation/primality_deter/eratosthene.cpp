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

bool* eratosthene2(unsigned long int number){
    unsigned long int i, memory_size = number/2;
    bool* isPrime = new bool[memory_size]; //Tableau indiquant si un nombre i est premier ou non, true si premier, false sinon.

    // Initialisation du tableau
    for(i = 0; i <= memory_size; i++)
        isPrime[i] = true;

    for(i = 3; i*i <= number; i+=2){
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
    unsigned long int nb = 100, memory_size=nb/2;
    bool* isPrime = new bool[memory_size];
    isPrime = eratosthene(nb);
    printf("LALA\n");
    for(int i = 1; i <= memory_size; i++){
        if(isPrime[i]) printf("%d  ", i*2+1);
    }
    printf("\n");
    return 0;
}
*/
