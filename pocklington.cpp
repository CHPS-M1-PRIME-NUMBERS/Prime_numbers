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
        Facteurs facteurs(candidatPrime - 1);
        if(facteurs.getNbFacteurs() < 2) {
                return false;
        }
        int A = facteurs[0] * facteurs[1]; int i = 2;
        std::vector<int> facteursA;
        //On récupère un a depuis les facteurs premier de candidatPrime
        while(A*A <= candidatPrime) { //A doit être plus grand que sqrt(N) donc A² doit être plus grand que N
                if(i < facteurs.getNbFacteurs()) {
                        A *= facteurs[i];
                        facteursA.push_back(facteurs[i++]);
                }
        }

        //On calcule b
        int B = (candidatPrime-1)/A;
        //std::cout << "A : "<<A<<", B : "<<B<<std::endl;
        if(A*A > candidatPrime) {
                // std::cout<<"A² > N : True"<<std::endl;
                int a = 0;
                for(i = 0; i < facteursA.size(); i++) {
                        a = rechercherCandidat(facteursA[i]);
                        if(pgcd(std::pow(a, (candidatPrime-1)/facteursA[i]), candidatPrime) != 1) {
                                return false;
                        }
                }
        }
        return true;
}
