#include <cmath>
#include <iostream>
#include <type_traits>

// cette fonction vérifie que n est un "perfect power", si cette fonction renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power(int n)
{
	int b;
	double a;
	int tmp;
	for (b=2;b <= log2(n);b++)
	{
        a = pow(n,1.0/b);
		std::cout<<"valeur de a pour b = "<< b <<" est égale a "<< a <<std::endl;
		if((a - (int)a) == 0)
		{
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
		
bool aks(unsigned int n)
{
	int r,i,gcd;
	if (is_perfect_power(n))
	{
		std::cout<<"composite"<<std::endl;
		return false;
	}else{
		r=find_r(n);
		std::cout<<" r est égale a "<< r <<std::endl;
		for(i=r;i > 1;i--)
		{
			if ((gcd=GCD(i,n)) > 1 && gcd < n)
			{
				std::cout<<"composite"<<std::endl;
				return false;
			}
		}
		if ( n <= r )
		{
			std::cout<<"prime"<<std::endl;
			return true;
		}
				
		
}
}

int main ()
{
	aks(31);
}
