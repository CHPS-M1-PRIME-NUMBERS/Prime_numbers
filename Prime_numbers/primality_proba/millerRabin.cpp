#include "millerRabin.hpp"

// Modular exponentiation (x^y) % p
unsigned int expPower(unsigned int x, unsigned int y, unsigned int p){
								unsigned int res = 1;
								x = x % p;
								while (y > 0) {
																if ((y%2) ==  1) {
																								res = (res*x)%p;
																}
																y = y/2;
																x = (x*x) % p;
								}
								return res;
}

// Returns false if n is composite or
// true if n is probably prime.
bool millerTest(unsigned int d, unsigned int n){
								unsigned int a = 2 + rand() % (n - 4);
								unsigned int x = expPower(a, d, n);
								if (x == 1 || x == n-1) {
																return true;
								}
								// Square and multiply
								while (d != n-1) {
																x = (x * x) % n;
																d *= 2;
																if (x == 1) return false;
																if (x == n-1) return true;
								}
								return false;
}

// Returns false if n is composite or true if n
// is probably prime
bool millerRabin(unsigned int n, unsigned int k)
{
								srand (time(NULL));
								unsigned int d = n - 1;

								if (n <= 1 || n == 4) return false;
								if (n <= 3) return true;

								while (d % 2 == 0)
																d /= 2;

								for (unsigned int i = 0; i < k; i++)
																if (millerTest(d, n) == false) {
																								return false;
																}
								return true;
}
