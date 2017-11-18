#include "pocklington.h"

template <typename T>
T modpow(T base, T exp, T modulus){
        base %= modulus;
        T result = 1;
        while(exp > 0) {
                if(exp & 1) result =(result * base) % modulus;
                base = (base * base) % modulus;
                exp >>= 1;
        }
        return result;
}

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

int rechercherCandidat(int N){
        int a = 2;
        while(modpow(a, N-1, N) != 1) {
                a += 1;
        }

        return a;
}

bool pocklington(int candidatPrime){
        //Trouver un a, on a f un facteur de a et on a n - 1 = f * r
        //Et PGDC(f, r) = 1
        int * facteurs = factorisation(candidatPrime-1);
        int A = facteurs[0] * facteurs[1]; int i = 2;
        //On récupère un a depuis les facteurs premier de candidatPrime
        if(facteurs == nullptr) { exit(EXIT_FAILURE); }
        while(A*A <= candidatPrime) { //A doit être plus grand que sqrt(N) donc A² doit être plus grand que N
                A *= facteurs[i++];
        }
        delete[] facteurs;

        //On calcule b
        int B = (candidatPrime-1)/A;
        std::cout << "A : "<<A<<", B : "<<B<<std::endl;
        // std::cout << "A*B = "<< a*b << " "; if(a*b == candidatPrime-1) std::cout<<"True"<<std::endl; else std::cout<<"False"<<std::endl;
        if(A*A > candidatPrime) {
                std::cout<<"A² > N : True"<<std::endl;
                int * facteursA = factorisation(A);
                int a = 0; i = 0;
                if(facteursA != NULL) {
                        while(facteursA[i] != 0) {
                                a = rechercherCandidat(facteursA[i]);
                                if(pgcd(std::pow(a, (candidatPrime-1)/facteursA[i]), candidatPrime) != 1) {
                                        return false;
                                }
                                i++;
                        }

                        delete[](facteursA);
                }
        }


        return true;
}
