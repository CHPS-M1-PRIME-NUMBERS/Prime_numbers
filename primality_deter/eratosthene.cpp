#include "eratosthene.hpp"
#include <iostream>

void multiple(mpz_class i, mpz_class number, bool* prime){ // Function that sets all premium multiples [i] to false.
        mpz_class j = 2;

        while ( cmp(j, number/i) <= 0) {
                prime[j.get_ui() * i.get_ui()] = false;
                j = j+1;
        }
}

bool* eratosthene(mpz_class number){
        bool* isPrime = new bool[number.get_ui()+1]; //Boolean array indicating whether the index number i is prime or not.
        mpz_class i = 0, k;

        // Initialisation du tableau
        while(cmp(i, number) <= 0) {
                isPrime[i.get_ui()] = true;
                i = i+1;
        }

        // 1 and 0 are not prime
        isPrime[0] = false; isPrime[1] = false;
        i = 2;
        while(cmp(i, number) <= 0) {
                multiple(i,number,isPrime); // Sets all premium multiples of i to false.
                i++;
                while( (cmp(i, number) <= 0) && !(isPrime[i.get_ui()]) ) {
                        i = i+1;
                }
        }
        return isPrime;
}
