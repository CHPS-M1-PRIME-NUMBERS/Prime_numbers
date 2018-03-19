#ifndef miller_rabin_hpp
#define miller_rabin_hpp

#include <cmath>
#include <cstdlib>
#include <ctime>

unsigned long int expPower(unsigned long int x, unsigned long int y, unsigned long int p);
bool millerTest(unsigned long int d, unsigned long int n);
bool millerRabin(unsigned long int n, unsigned long int k);

#endif
