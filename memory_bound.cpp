#include "memory_bound.h"

// #### MEMORY-BOUND #### //

void memory_bound(unsigned int nbr, std::list<unsigned int>* l){ // Return a list of prime numbers between 2 and nbr.

    bool* isPrime;
    unsigned int i;
    isPrime = eratosthene(nbr); // Application of the eratosthene sieve to find the prime numbers

    for(i = 0; i <= nbr; i++){
        if (isPrime[i]){
            l->push_back(i);
        }
    }
    delete [] isPrime;
}

// Operator<< to print the content of a list.
std::ostream& operator<<(std::ostream& flux, std::list<unsigned int>& l)
{
	while(!l.empty())
	{
		flux << l.front() << ' ';
		l.pop_front();
	}
	flux << std::endl;
	return flux;
}

int main(){

	std::list<unsigned int> l;
	memory_bound(1039, &l);
	std::cout << l;

    return 0;
}
