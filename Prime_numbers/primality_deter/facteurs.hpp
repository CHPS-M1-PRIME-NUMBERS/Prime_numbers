#ifndef facteurs_hpp
#define facteurs_hpp
#include "iostream"
#include <vector>

class Facteurs {
private:
std::vector<int> facteurs;
int nbFacteurs;
int nbFactored;
void factorisation();

public:
Facteurs(int);
int& operator[](int i);
friend std::ostream& operator<<(std::ostream& os, Facteurs& facteur);
int getNbFactored();
int getNbFacteurs();
~Facteurs();

};

#endif
