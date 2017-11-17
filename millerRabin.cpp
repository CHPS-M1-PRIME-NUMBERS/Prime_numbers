#include "millerRabin.h"

int expPower(int x, int y, int p){
	int res = 1;	 
	x = x % p; 		 					 
	while (y > 0){
		if ((y%2) ==  1){	
			res = (res*x)%p;
		}
		y = y/2;
		x = (x*x) % p;
	}
	return res;
}

bool millerTest(int d, int n){
	int a = 2 + rand() % (n - 4);
	int x = expPower(a, d, n);
	if (x == 1 || x == n-1){		
		return true;
	}
	while (d != n-1){
		x = (x * x) % n;
		d *= 2;
		if (x == 1)	 return false;
		if (x == n-1) return true;
	}
	return false;
}

bool isPrime(int n, int k)
{
	int d = n - 1;
	
	if (n <= 1 || n == 4) return false;
	if (n <= 3) return true;

	while (d % 2 == 0)
		d /= 2;
		
	for (int i = 0; i < k; i++)
		if (millerTest(d, n) == false){
			return false;
		}
	return true;
}

int main()
{
	int n, k = 4;
	std::cout << "Enter the number to check: ";
	std::cin >>n ;
	if (isPrime(n, k))
		std::cout << n << " is prime." << std::endl;
    else
        std::cout << n << " is not prime." << std::endl;

	return 0;
}
