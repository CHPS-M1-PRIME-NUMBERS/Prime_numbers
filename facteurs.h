#ifndef facteurs_h
#define facteurs_h
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
int getNbFactored();
int getNbFacteurs();
~Facteurs();

};

#endif
