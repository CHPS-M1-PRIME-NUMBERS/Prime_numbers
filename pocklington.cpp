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
        // std::cerr << facteurs << std::endl;

        if(facteurs.getNbFacteurs() < 1) {
                return false;
        }

        int A = facteurs[0]; int i = 1;
        std::vector<int> facteursA;
        facteursA.push_back(facteurs[0]);
        //On récupère un A depuis les facteurs premier de candidatPrime
        while(i<facteurs.getNbFacteurs() && A <= std::sqrt(candidatPrime)) { //A doit être plus grand que sqrt(N) donc A² doit être plus grand que N
                        A *= facteurs[i];
                        facteursA.push_back(facteurs[i++]);
        }

        // std::cout << "A : " << A << std::endl;

        //On calcule b
        int B = (candidatPrime-1)/A;
        // std::cerr << "PGCD(A, B) = " << pgcd(A, B) << std::endl;

        if(A > std::sqrt(candidatPrime) && A*B == candidatPrime-1 && pgcd(A, B) == 1) {
          for(int  a = 2; a<1000; a++){
                for(i = 0; i < facteursA.size(); i++) {
                    if(modpow(a, candidatPrime-1, candidatPrime) == 1 && pgcd(std::pow(a, (candidatPrime-1)/facteursA[i])-1, candidatPrime) == 1){
                      return true;
                    }
                  }
                }
        }
        return false;
}
