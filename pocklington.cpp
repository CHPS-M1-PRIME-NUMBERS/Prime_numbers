#include "pocklington.h"

int* factorisation(int n){
        if(n<2) return nullptr;
        else{
                int *facteursObtenus = new int[10000](); int i = 0;

                for(int j = 0; j<10000; j++) {
                        facteursObtenus[j] = 0;
                }

                for(int j = 2; j<= n; j++) {
                        while( n % j == 0) {
                                facteursObtenus[i++] = j;
                                n = n / j;
                        }
                }
                return facteursObtenus;
        }
        return nullptr;
}

int pgcd(int a, int b){
        //Algoritme d'Euclide
        int r = 1;
        while(a%b != 0) { //Tant que le reste n'est pas 0
                r = a%b;
                a = b;
                b = r;
        }
        return r;
}

bool pocklington(int candidatPrime){
        //Trouver un a, on a f un facteur de a et on a n - 1 = f * r
        //Et PGDC(f, r) = 1

        return false;
}
