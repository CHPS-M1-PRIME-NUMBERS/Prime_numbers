#ifndef miller_rabin_hpp
#define miller_rabin_hpp

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <gmpxx.h>

unsigned int expPower(unsigned int x, unsigned int y, unsigned int p);
bool millerTest(unsigned int d, unsigned int n);
bool millerRabin(unsigned int n, unsigned int k);

#endif
