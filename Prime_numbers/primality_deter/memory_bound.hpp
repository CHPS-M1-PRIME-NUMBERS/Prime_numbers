#ifndef memory_bound_hpp
#define memory_bound_hpp

#include <iostream>
#include <list>
#include "eratosthene.hpp"

void memory_bound(unsigned int nbr, std::list<unsigned int>* l);
std::ostream& operator<<(std::ostream& flux, std::list<unsigned int>& l);

#endif
