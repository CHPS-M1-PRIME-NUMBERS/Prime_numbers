#include "highly_composite.hpp"


unsigned long int nb_dividers(unsigned long int number){ // Calcul le nombre de diviseurs d'un entier.
        std::list<unsigned long int> prime; // Une liste de nombre premiers.
        memory_bound(number, &prime); // Appel à Eratosthene pour trouver une liste assez grande de nombres premiers.

        unsigned long int res = 1;
        int expo = 0;
        unsigned long int head = prime.front();

        while ( (number >= head) && (number != 1) && (head != 0)) {
                while ( (number%head == 0) && (number != 1)) {
                        number = number/head;
                        expo += 1;
                }
                res *= (expo + 1);
                prime.pop_front(); // Supprime le 1er élément
                head = prime.front();
                expo = 0;
        }

        return res;
}

bool highly_composite_naive(unsigned long int number){ // Renvoie true si un nombre est hautement composé (methode naive), false sinon.

        for (auto i = 0; i < number; i++) {
                if (nb_dividers(i) >= nb_dividers(number)) return false;
        }
        return true;
}

/**
   Un nombre hautement composé suit les règles suivantes:
    1. Les nombres premiers 2, 3, ..., p forment une suite qui composent n,
    2. Les exposants n'augmentent, so a_2>=a_3>=...>=a_p, et
    3. L'exposant final p_a est toujours 1, sauf pour deux cas N=4=2^2 et N=36=2^2·3^2, où c'est 2.
 */

bool highly_composite_def(unsigned long int number){ // Renvoie true si un nombre est hautement composé (methode utilisant sa définition), false sinon.
        std::list<unsigned long int> prime; // Liste de nombres premiers
        memory_bound(number, &prime);

        unsigned long int nbr = number;
        unsigned long int tmp = 0;
        unsigned long int expo = number;
        unsigned long int head = prime.front();

        while ( (number >= head) && (number != 1) && (head != 0)) {
                while ( (number%head == 0) && (number != 1)) {
                        number = number/head;
                        tmp += 1;
                }
                if (expo < tmp) return false;
                expo = tmp;
                tmp = 0;
                prime.pop_front();
                head = prime.front();
        }
        if ((nbr != 4) && (nbr != 36) && (expo != 1))
                return false; L'exposant final p_a est toujours 1, sauf pour deux cas N=4=2^2 et N=36=2^2·3^2, où c'est 2.

        return true;
}
