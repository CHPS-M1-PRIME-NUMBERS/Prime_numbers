#include <math.h>
#include <iostream>
#include <type_traits>

// cette fonction vérifie que n est un "perfect power", si cette fonction renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power(unsigned int n)
{
	int b;
	double a;
	int tmp;
	for (b=2;b <= (log(n)/log(2));b++)
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
	
	
bool aks(unsigned int n)
{
	;
}

int main ()
{
	std::cout<<"pour n = 283 " << is_perfect_power(121) <<std::endl;
	std::cout<<"pour n = 284 " << is_perfect_power(125) <<std::endl;
}
