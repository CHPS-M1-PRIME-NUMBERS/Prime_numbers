#include "millerRabin.hpp"

// Exponentiation modulaire (x^y) % p
unsigned long int expPower(unsigned long int x, unsigned long int y, unsigned long int p){
								unsigned long int res = 1;
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

// Retourne faux si n est composé ou
// vrai si n est probablement premier
bool millerTest(unsigned long int d, unsigned long int n){
								unsigned long int a = 2 + rand() % (n - 4);
								unsigned long int x = expPower(a, d, n);
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

// Retourne faux si n est composé ou
// vrai si n est probablement premier
bool millerRabin(unsigned long int n, unsigned long int k)
{
								// Initialisation du générateur des nombres aléatoires
								srand (time(NULL));
								unsigned long int d = n - 1;

								if (n <= 1 || n == 4) return false;
								if (n <= 3) return true;

								while (d % 2 == 0)
																d /= 2;

								for (unsigned long int i = 0; i < k; i++)
																if (millerTest(d, n) == false) {
																								return false;
																}
								return true;
}
