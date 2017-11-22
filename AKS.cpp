#include <cmath>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "CPolyMod.cpp"

// cette fonction vérifie que n est un "perfect power", si cette fonction renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power(int n)
{
	int b, a2;
	double a;
	int tmp;
	for (b=2;b <= log2(n);b++)
	{
        a = pow(n,1.0/b);
		if((a - (int)a) == 0) {
			return true;
		}
	}
	return false;
}

int max ( int a ,int b)
{
	if ( a > b )
	{
		return a;
	}
	else{
		return b;
	}
}

template <typename T>
T modpow(T base, T exp, T modulus){
        base %= modulus;
        T result = 1;
        while(exp > 0) {
                if(exp & 1) result =(result * base) % modulus;
                base = (base * base) % modulus;
                exp >>= 1;
        }
        return result;
}

int find_r(int n)
{
	int maxk = floor(pow(log2(n),2));
	int maxr = max(ceil(pow(log2(n),5)),3);
	bool nextR = true;
	int r,k;
	for (r=2; nextR && (r < maxr); r++)
	{
		nextR=false;
		for(k=1; (!nextR) && (k <= maxk); k++)
		{
			nextR=( (modpow(n,k,r) == 1) || (modpow(n,k,r) ==0));
		}
	}
	r--;
	return r;
}

int GCD(int a, int b){
        int r = 1;
        while(a%b != 0)
         {
                r = a%b;
                a = b;
                b = r;
        }
        return r;
}
int EulerPhi(int n)
{
	float res=n;
	int p;
	for ( p=2; (p*p) <= n; p++)
	{
		if(n%p ==0)
		{
			while(n%p == 0)
			{
				n/= p;
				res *= (1.0 - (1.0/(float)p));
			}
		}
	}
	if (n >1)
	res *= (1.0 - (1.0/(float)n));
	return res;
}

bool step_5(int n, int r){
	unsigned int max = floor(sqrt(EulerPhi(r))*log2(n));
	CPolyMod p1(r, n);	// x
	p1 = p1.Pow(n);		// x^n

	unsigned int a;
	for (a = 1; a <= max; ++a) {
		CPolyMod p2(r, n);		// x
		p2 -= a;				// x - a
		p2 = p2.Pow(n);			// (x - a)^n
		p2 += a;				// (x - a)^n + a
		if (p1 != p2) {
			return false;
		}
	}
	return true;
}

bool aks(int n)
{
	int r,i,gcd;
	if (is_perfect_power(n))
	{
		std::cout<<n<<" composite"<<std::endl;
		return false;
	}else{
		r=find_r(n);
		for(i=r;i > 1;i--)
		{
			if ((gcd=GCD(i,n)) > 1 && gcd < n)
			{
				std::cout<<n<<" composite"<<std::endl;
				return false;
			}
		}
		if ( n <= r )
		{
			std::cout<<n<<" prime"<<std::endl;
			return true;
		}
		if (!step_5(n,r)){
			std::cout<<n<<" composite"<<std::endl;
			return false;
		}
	}
	std::cout<<n<<" prime"<<std::endl;
	return true;
}

int main ()
{
	aks(31);
	aks(1039);
	aks(1001);
}
