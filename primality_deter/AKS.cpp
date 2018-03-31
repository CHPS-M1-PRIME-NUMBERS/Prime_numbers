#include "AKS.hpp"
NTL_CLIENT
// cette fonction vérifie que n est un "perfect power", si cette fonction
// renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power(unsigned long int n) {
  unsigned long int b, a2;
  double a;
  unsigned long int tmp;
  for (b = 2; b <= log2(n); b++) {
    a = pow(n, 1.0 / b);
    if ((a - (unsigned long int)a) == 0) {
      return true;
    }
  }
  return false;
}

// Retourne le maximum entre deux nombres.
unsigned long int maximum(unsigned long int a, unsigned long int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

// Fonction permettant de resoudre R dans l'algorithme AKS
unsigned long int find_r(unsigned long int n) {
  unsigned long int maxk = floor(pow(log2(n), 2));
  unsigned long int maxr = maximum(ceil(pow(log2(n), 5)), 3);
  bool nextR = true;
  unsigned long int r, k;
  for (r = 2; nextR && (r < maxr); r++) {
    nextR = false;
    for (k = 1; (!nextR) && (k <= maxk); k++) {
      nextR = ((modpow(n, k, r) == 1) || (modpow(n, k, r) == 0));
    }
  }
  r--;
  return r;
}

// Fonction donnant le PGCD entre deux nombres
unsigned long int GCD(unsigned long int a, unsigned long int b) {
  unsigned long int r = 1;
  while (a % b != 0) {
    r = a % b;
    a = b;
    b = r;
  }
  return r;
}

unsigned long int EulerPhi(unsigned long int n) {
  float res = n;
  unsigned long int p;
  for (p = 2; (p * p) <= n; p++) {
    if (n % p == 0) {
      while (n % p == 0) {
        n /= p;
        res *= (1.0 - (1.0 / (float)p));
      }
    }
  }
  if (n > 1)
    res *= (1.0 - (1.0 / (float)n));
  return res;
}

// Fonction implementant l'étape 5 de l'agorithme AKS
bool step_5(unsigned long int n, unsigned long int r) {
  unsigned long int maxi = floor(sqrt(EulerPhi(r)) * log2(n));
  unsigned long int temp = n;
  ZZ x = conv<ZZ>(temp);
  ZZ_p::init(x); // mod n
  ZZ_pX f(r, 1);
  f -= 1; // f=x^r-1
  const ZZ_pXModulus pf(f);
  ZZ_pX p1(x % r, 1); // x^{n%r}=x^n mod(x^r-1)
  unsigned long int a;
  for (a = 1; a <= maxi; ++a) {
    ZZ_pX p2(1, 1);
    p2 -= a;                 // x-a
    PowerMod(p2, p2, x, pf); //(x-a)^n
    p2 += a;                 //(x-a)^n+a
    if (p1 != p2) {
      return false;
    }
  }
  return true;
}

// Implementation de l'algorithme AKS qui retourne true si le nombre n est
// premier, false sinon.
bool aks(unsigned long int n) {
  unsigned long int r, i, gcd;
  if (is_perfect_power(n)) {
    return false;
  } else {
    r = find_r(n);
    for (i = r; i > 1; i--) {
      if ((gcd = GCD(i, n)) > 1 && gcd < n) {
        return false;
      }
    }
    if (n <= r) {
      return true;
    }
    if (!step_5(n, r)) {
      return false;
    }
  }
  return true;
}
