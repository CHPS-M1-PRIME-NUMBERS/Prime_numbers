#ifndef AKS_hpp
#define AKS_hpp
#include "NTL/ZZ_pX.h"
#include "NTL/ZZ.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <type_traits>

// cette fonction vérifie que n est un "perfect power", si cette fonction renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power(unsigned int n);

unsigned int maximum (unsigned int a, unsigned int b);

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

int find_r(int n);

unsigned int GCD(unsigned int a, unsigned int b);

unsigned int EulerPhi(unsigned int n);

bool step_5(unsigned int n, unsigned int r);

bool aks(unsigned int n);

#endif
