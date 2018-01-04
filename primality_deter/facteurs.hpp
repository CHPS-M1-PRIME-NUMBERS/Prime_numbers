#ifndef facteurs_hpp
#define facteurs_hpp
#include "iostream"
#include <vector>

class Facteurs {
private:
std::vector<unsigned long int> facteurs;
int nbFacteurs;
unsigned long int nbFactored;
void factorisation();

public:
Facteurs(unsigned long int);
unsigned long int& operator[](int i);
friend std ::ostream& operator<<(std::ostream& os, Facteurs& facteur);
unsigned long int getNbFactored();
int getNbFacteurs();
~Facteurs();

};

#endif
