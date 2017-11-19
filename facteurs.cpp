#include "facteurs.h"

Facteurs::Facteurs(int n){
        this->nbFactored = n;
        this->factorisation();
}

void Facteurs::factorisation(){
        int N = this->nbFactored;
        if(N<=2) {
                std::cerr << "Erreur : le nombre à vérifier est inférieur ou égal à 2." << std::endl;
                exit(EXIT_FAILURE);
        }
        else{
                for(int j = 2; j<= N; j++) {
                        while( N % j == 0) {
                                facteurs.push_back(j);
                                N = N / j;
                        }
                }
                this->nbFacteurs = facteurs.size();
        }

}

int Facteurs::getNbFactored(){
        return this->nbFactored;
}

int& Facteurs::operator[](int i){
        return facteurs[i];
}

int Facteurs::getNbFacteurs(){
        return this->nbFacteurs;
}

Facteurs::~Facteurs(){

}
