#include "euclide.hpp"

// Donne le plus grand diviseur commun de deux nombres
unsigned long int pgcd(unsigned long int a, unsigned long int b){
        int r = 1;
        while(a%b != 0) {
                r = a%b;
                a = b;
                b = r;
        }
        return r;
}

// Test la prmialité d'un nombre en vérifiant que le plus grand pgcd de celui ci est 1 avec tout les nombre inferieur à racine de celui ci
// Retourne true si premier, false sinon.
bool computation_bound_euclide(unsigned long int number){
        int i;
        for ( i = 2; i*i <= number; i++) {
                if (pgcd(i, number) != 1) return false;
        }
        return true;
}

// Test la primalité d'un nombre en verifiant que aucun nombre inferieur à sa racine ne le divise.
// Retourne true si premier, false sinon.
bool computation_bound_modulo(unsigned long int number){
        int i;
        for ( i = 2; i*i <= number; i++) {
                if (number%i == 0) return false;
        }
        return true;
}
