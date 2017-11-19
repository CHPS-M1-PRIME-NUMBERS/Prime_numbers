#include "eratosthene.h"

void multiple(unsigned int i, unsigned int number, bool* prime){ // Function that sets all premium multiples [i] to false.
        int j = 2;

        while ( j <= number/i) {
                prime[j * i] = false;
                j++;
        }
}

bool* eratosthene(unsigned int number){
        bool* isPrime = new bool[number+1]; //Boolean array indicating whether the index number i is prime or not.
        int i = 0, k;

        // Initialisation du tableau
        while(i <= number) {
                isPrime[i] = true;
                i++;
        }

        // 1 and 0 are not prime
        isPrime[0] = false; isPrime[1] = false;
        i = 2;
        while (i <= number) {
                multiple(i,number,isPrime); // Sets all premium multiples of i to false.
                i++;
                while( (i <= number) && !(isPrime[i]) ) {
                        i++;
                }
        }
        return isPrime;
}
