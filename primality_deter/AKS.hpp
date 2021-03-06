#ifndef AKS_hpp
#define AKS_hpp
#include "NTL/ZZ_pX.h"
#include "NTL/ZZ.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <type_traits>

// cette fonction vérifie que n est un "perfect power", si cette fonction renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power(unsigned long int n);

unsigned long int maximum (unsigned long int a, unsigned long int b);

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

unsigned long int find_r(unsigned long int n);

unsigned long int GCD(unsigned long int a, unsigned long int b);

unsigned long int EulerPhi(unsigned long int n);

bool step_5(unsigned long int n, unsigned long int r);

bool aks(unsigned long int n);

#endif
