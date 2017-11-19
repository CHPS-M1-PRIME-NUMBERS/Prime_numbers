#ifndef memory_bound_h
#define memory_bound_h

#include <iostream>
#include <list>
#include "eratosthene.h"

void memory_bound(unsigned int nbr, std::list<unsigned int>* l);
std::ostream& operator<<(std::ostream& flux, std::list<unsigned int>& l);

#endif
