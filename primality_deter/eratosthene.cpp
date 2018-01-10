#include "eratosthene.hpp"

void multiple(unsigned long int i, unsigned long int number, bool* prime){ // Fonction qui met tout les nombres multiples de i à faux.
        int j = 2;

        while ( j <= number/i) {
                prime[j * i] = false;
                j++;
        }
}

// Implemenation du crible d'Eratosthene. Retourne un tableau de booleen indiquant la primalité des nombres de 2 à N.
bool* eratosthene(unsigned long int number){
        bool* isPrime = new bool[number+1]; //Tableau indiquant si un nombre i est premier ou non, true si premier, false sinon.
        unsigned long int i = 0, k;

        // Initialisation du tableau
        while(i <= number) {
                isPrime[i] = true;
                i++;
        }

        // 1 et 0 ne sont pas premiers
        isPrime[0] = false; isPrime[1] = false;
        i = 2;
        while (i <= number) {
                multiple(i,number,isPrime); // Appel de la fonction multiple qui met tout les multiples de i à false.
                i++;
                while( (i <= number) && !(isPrime[i]) ) {
                        i++;
                }
        }
        return isPrime;
}
