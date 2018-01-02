#ifndef eratosthene_hpp
#define eratosthene_hpp
#include <gmpxx.h>

void multiple(mpz_class i, mpz_class number, bool* prime);
bool* eratosthene(mpz_class number);

#endif
