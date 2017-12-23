#ifndef memory_bound_hpp
#define memory_bound_hpp

#include <iostream>
#include <list>
#include "eratosthene.hpp"

void memory_bound(mpz_class nbr, std::list<mpz_class>* l);
std::ostream& operator<<(std::ostream& flux, std::list<mpz_class>& l);

#endif
