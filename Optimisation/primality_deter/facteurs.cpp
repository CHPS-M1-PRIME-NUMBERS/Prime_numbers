#include "facteurs.hpp"

// Classe permettant la decomposition d'un nombre en ses facteurs et de les stocker.
Facteurs::Facteurs(unsigned long int n){
        this->nbFactored = n;
        this->factorisation();
}

void Facteurs::factorisation(){
        unsigned long int N = this->nbFactored;
        if(N<0) {
                std::cerr << "Erreur : le nombre à vérifier est négatif." << std::endl;
                exit(EXIT_FAILURE);
        }
        else if(N == 1) {
                facteurs.push_back(1);
                this->nbFacteurs = facteurs.size();
        }
        else if(N == 2) {
                facteurs.push_back(2);
                this->nbFacteurs = facteurs.size();
        }
        else{
                for(unsigned long int j = 2; j<= N; j++) {
                        while( N % j == 0) {
                                facteurs.push_back(j);
                                N = N / j;
                        }
                }
                this->nbFacteurs = facteurs.size();
        }

}

unsigned long int Facteurs::getNbFactored(){
        return this->nbFactored;
}

unsigned long int& Facteurs::operator[](int i){
        return facteurs[i];
}

int Facteurs::getNbFacteurs(){
        return this->nbFacteurs;
}

Facteurs::~Facteurs(){

}

// Surcharge de l'operateur de flux sortant pour afficher les facteurs.
std::ostream& operator<<(std::ostream& os, Facteurs& facteur){
        for(int i = 0; i < facteur.getNbFacteurs(); i++) {
                os << facteur[i] << " ";
        }
        return os;
}
