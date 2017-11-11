#include "pocklington.h"

int* factorisation(int n){
        if(n<2) ;
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

bool pocklington(int candidatPrime){

        return false;
}
