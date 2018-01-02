#include "memory_bound.hpp"

// #### MEMORY-BOUND #### //

void memory_bound(mpz_class nbr, std::list<mpz_class>* l){ // Return a list of prime numbers between 2 and nbr.

        bool* isPrime;
        unsigned int i;
        if (!l->empty()) l->clear(); // Clear the content
        isPrime = eratosthene(nbr); // Application of the eratosthene sieve to find the prime numbers

        for(mpz_class i(0); cmp(i, nbr) <= 0; i++) {
                if (isPrime[i.get_ui()]) {
                        l->push_back(i);
                }
        }
        delete [] isPrime;
}

// Operator<< to print the content of a list.
std::ostream& operator<<(std::ostream& flux, std::list<mpz_class>& l)
{
        while(!l.empty())
        {
                flux << l.front() << ' ';
                l.pop_front();
        }
        return flux;
}
