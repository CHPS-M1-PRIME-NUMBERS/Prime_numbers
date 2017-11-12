#include "pocklington.h"

int* factorisation(int n){
        const int taille = 100000;
        if(n<2) return nullptr;
        else{
                int *facteursObtenus = new int[taille](); int i = 0;

                for(int j = 0; j<taille; j++) {
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
        int * facteurs = factorisation(candidatPrime-1);
        int a = facteurs[0] * facteurs[1]; int i = 2;
        //On récupère un a depuis les facteurs premier de candidatPrime
        while(a*a <= candidatPrime) { //A doit être plus grand que sqrt(N) donc A² doit être plus grand que N
                a *= facteurs[i++];
        }

        //On calcule b
        int b = (candidatPrime-1)/a;
        std::cout << "A : "<<a<<", B : "<<b<<std::endl;
        // std::cout << "A*B = "<< a*b << " "; if(a*b == candidatPrime-1) std::cout<<"True"<<std::endl; else std::cout<<"False"<<std::endl;
        if(a*a > candidatPrime) {
                std::cout<<"A² > N : True"<<std::endl;
                if(pgcd(a, b) == 1) {
                        int * facteursA = factorisation(a); int j = 0;
                        if(facteursA != NULL) {
                                while(facteursA[j] != 0) {
                                        if((int) std::pow(facteursA[j], candidatPrime-1) % candidatPrime == 1) {
                                                if(pgcd((std::pow(facteursA[j], (candidatPrime-1)/(j+1)))-1, candidatPrime) == 1) {
                                                        return true;
                                                }
                                        }
                                        j++;
                                }
                        }

                }
        }
        else { std::cout<<"A² > N : False"<<std::endl; }

        std::cout << "PGCD(" << a << ", " << b << ") =  " << pgcd(a, b) << std::endl;

        //Affichage de la factorisation de N-1
        /* unsigned int i = 0;
           if(facteurs != NULL) {
                while(facteurs[i] != 0) {
                        std::cout<<facteurs[i]<<" ";
                        i++;
                }
                std::cout<<std::endl;

                delete[](facteurs);
           } */

        return false;
}
