#include "millerRabin.hpp"

// Modular exponentiation (x^y) % p
void expPower(mpz_t dest, mpz_t x, mpz_t y, mpz_t p){
	mpz_set_ui(dest, 1); //dest = 1;
	mpz_mod(x, x, p); //x = x % p;
	while (mpz_cmp(y, 0) > 0) //y > 0
	{
		if (mpz_odd_p(y) !=  0) // (y%2) == 1
		{
			mpz_mul(dest, dest, x);
			mpz_mod(dest, dest, p); //res = (res*x)%p;
		}
		mpz_fdiv_q_ui(y, y, 2);//y = y/2;
		mpz_mul(x, x, x);
		mpz_mod(x, x, p);//x = (x*x) % p;
	}
}

// Returns false if n is composite or
// true if n is probably prime.
bool millerTest(mpz_t d, mpz_t n){
	//////valeur aléatoire//////
	mpz_t a, n_1, n_2, x;
	mpz_inits(a, n_1, n_2, x);
	mpz_sub_ui(n_2,n,2);
	mpz_sub_ui(n_1,n,1);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(NULL));
	mpz_urandomm(a, state, n_2);//a in range 0 to n-2
	//////////////////////////////
	expPower(x, a, d, n);//unsigned int x = expPower(a, d, n);
	if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_1) == 0){
		return true;
	}
	// Square and multiply
	while (mpz_cmp(d, n_1) != 0){
		mpz_mul(x, x, x);
		mpz_mod(x, x, n);//x = (x * x) % n;
		mpz_mul_ui(d, d, 2);//d *= 2;
		if (mpz_cmp_ui(x, 1) == 0) return false;
		if (mpz_cmp(x, n_1) == 0) return true;
	}
	mpz_clear(a);mpz_clear(n_1);mpz_clear(n_2);mpz_clear(x);
return false;
}


// Returns false if n is composite or true if n
// is probably prime
bool millerRabin(mpz_t n, mpz_t k)
{
	mpz_t d, i;
	mpz_inits(d, i);
	mpz_sub_ui(d,n,1);//unsigned int d = n - 1;

	if (mpz_cmp_ui(n, 2) < 0 || mpz_cmp_ui(n, 4) == 0){
		mpz_clears(d, i);
		return false;
	}
	if (mpz_cmp_ui(n, 4) < 0){
		mpz_clears(d, i);
		return true;
	}

	while (mpz_even_p(d) != 0) mpz_fdiv_q_ui(d, d, 2);

	for (mpz_set_ui(i, 0); mpz_cmp(i, k) < 0; mpz_add_ui(i, i, 1))
		if (millerTest(d, n) == false) {
			mpz_clears(d, i);
			return false;
		}
		mpz_clears(d, i);
		return true;
}
