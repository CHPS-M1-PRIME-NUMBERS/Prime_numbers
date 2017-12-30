#ifndef miller_rabin_hpp
#define miller_rabin_hpp

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <gmpxx.h>
#include <iostream>

void expPower(mpz_t dest, mpz_t x, mpz_t y, mpz_t p);
bool millerTest(mpz_t d, mpz_t n);
bool millerRabin(mpz_t n, mpz_t k);

#endif
