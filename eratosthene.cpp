#include "eratosthene.h"

void multiple(int i, int number, bool* prime){ // Fonction qui met tout les multiple de prime[i] à false.
    int j = 2;

    while ( j <= number/i){
        prime[j * i] = false;
        j++;
    }
}

bool crible_eratosthene(int number){
    bool* isPrime = new bool[number+1]; // Tableau de booléen indiquant si la le nombre d'indice i est premie rou non.
    int i = 0, k;

    // Initialisation du tableau
    while(i <= number){
        isPrime[i] = true;
        i++;
    }

    // 1 et 0 non premier
    isPrime[0] = false; isPrime[1] = false;
    i = 2;
    while (i <= number){
        multiple(i,number,isPrime); // On met tout les multiples de i à false.
        i++;
        while( (i <= number) && !(isPrime[i]) ){
            i++;
        }
    }

    // On vérifie si number est bien un nombre premier.
    if (isPrime[number]){
        delete [] isPrime;
        return true;
    }
    else{
        delete [] isPrime;
        return false;
    }
}

int main(int argc, char** argv){

    // Test de la fonction
    int n1 = 1151, n2 = 993; bool res;
    res = crible_eratosthene(n1);
    std::cout << n1 << " est-il premier ? " << res << std::endl; // Doit afficher 1
    res = crible_eratosthene(n2);
    std::cout << n2 << " est-il premier ? " << res << std::endl; // Doit afficher 0

    return 0;
}
