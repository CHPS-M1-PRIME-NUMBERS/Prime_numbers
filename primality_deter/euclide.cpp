#include "euclide.hpp"

unsigned long int pgcd(unsigned long int a, unsigned long int b){
        int r = 1;
        while(a%b != 0) {
                r = a%b;
                a = b;
                b = r;
        }
        return r;
}

bool computation_bound_euclide(unsigned long int number){
        int i;
        for ( i = 2; i*i <= number; i++) {
                if (pgcd(i, number) != 1) return false;
        }
        return true;
}

bool computation_bound_modulo(unsigned long int number){
        int i;
        for ( i = 2; i*i <= number; i++) {
                if (number%i == 0) return false;
        }
        return true;
}
