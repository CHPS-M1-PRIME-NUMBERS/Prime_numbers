#include "memory_bound.hpp"

// #### MEMORY-BOUND #### //

// La liste l en paramètre contiendra une liste de nombre premier jusqu'à nbr selon le crible d'Eratosthene
void memory_bound(unsigned long int nbr, std::list<unsigned long int>* l){ // Retourne une liste de nombre premier entre 2 et nbr.

        bool* isPrime;
        unsigned long int i;
        isPrime = eratosthene(nbr); // Appel du crible d'Eratosthene

        for(i = 0; i <= nbr; i++) {
                if (isPrime[i]) {
                        l->push_back(i); // Ajout des nombres premiers dans la liste
                }
        }
        delete [] isPrime;
}

// Operator<< pour afficher le contenu de la liste.
std::ostream& operator<<(std::ostream& flux, std::list<unsigned long int>& l)
{
        while(!l.empty())
        {
                flux << l.front() << ' ';
                l.pop_front();
        }
        return flux;
}
