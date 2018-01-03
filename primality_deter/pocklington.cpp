#include "pocklington.hpp"

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

int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
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
        Facteurs facteurs(candidatPrime - 1); // Factorisation de N-1

        // std::vector<int> facteurs; // Factorisation de N-1

        if(facteurs.getNbFacteurs() < 2) {
                if(candidatPrime == 1) {
                        return false;
                }
                else if(candidatPrime == 2) {
                        return true;
                }
                else if(candidatPrime == 3) {
                        return true;
                }
        }



        int A = facteurs[0]; int i = 1;
        int B;
        std::vector<int> facteursA;
        facteursA.push_back(facteurs[0]);
        //On récupère un A depuis les facteurs premier de candidatPrime
        //Optimisation possible si on factorise en même temps qu'on cherche un A répondant aux besoins et qu'on arrête quand on a trouver.
        while(A <= std::sqrt(candidatPrime) || gcd(A, B) != 1) { //A doit être plus grand que sqrt(N) donc A² doit être plus grand que N
                A *= facteurs[i];
                facteursA.push_back(facteurs[i++]);
                B = (candidatPrime-1)/A;
        }

        if(A > std::sqrt(candidatPrime) && A*B == candidatPrime-1 && gcd(A, B) == 1) {
                for(int a = 2; a<candidatPrime-1; a++) {
                        for(i = 0; i < facteursA.size(); i++) {
                                int w = modpow(a, (candidatPrime-1)/facteursA[i], candidatPrime)-1;

                                if(modpow(a, candidatPrime-1, candidatPrime) == 1 && gcd(w, candidatPrime) == 1) {
                                        return true;
                                }
                        }
                }
        }

        return false;
}
