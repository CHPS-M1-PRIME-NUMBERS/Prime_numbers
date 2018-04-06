#include "AKS_CONJECTURE.hpp"

NTL_CLIENT
// cette fonction vérifie que n est un "perfect power", si cette fonction
// renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power2(unsigned long int n) {
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
// Implementation de l'algorithme AKS qui retourne true si le nombre n est
// premier, false sinon.
bool conjecture(unsigned long int n) {
  unsigned long int r, i;
  if (is_perfect_power2(n)) {
    return false;
  } else {
    r = 2;
    i = n % r;
    for (r = 2; i * i % r == 1; r++) {
      if (i == 0)
        return false;
      i = n % r;
    }
    unsigned long int temp = n;
    ZZ x = conv<ZZ>(temp);
    ZZ_p::init(x); // mod n
    ZZ_pX f(r, 1);
    f -= 1; // f=x^r-1
    const ZZ_pXModulus pf(f);
    ZZ_pX p1(x % r, 1);
    p1 -= 1; // x^n-1
    ZZ_pX p2(1, 1);
    p2 -= 1;                 // x-1
    PowerMod(p2, p2, x, pf); //(x-1)^n
    if (p1 == p2) {
      return true;
    } else {
      return false;
    }
  }
}
/*
int main() {
  int a = 5;
  int elapsed_time;
  std::chrono::time_point<std::chrono::system_clock> start, end;

  start = std::chrono::system_clock::now();
  bool res = conjecture(a);
  end = std::chrono::system_clock::now();
  elapsed_time =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  printf("res de %d => %d\n", a, res);
  std::cout << "Time elapsed average: " << elapsed_time << " µs" << std::endl;
}
*/
