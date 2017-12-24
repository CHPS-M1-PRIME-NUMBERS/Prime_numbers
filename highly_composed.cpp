#include <cmath>
#include <cstdlib>
#include "memory_bound.hpp"

unsigned int nb_dividers(unsigned int number){ // calculates the number of divisors of an integer
    std::list<unsigned int> prime; // List of prime number
    memory_bound(number, &prime);

    unsigned int res = 1;
    int expo = 0;
    unsigned int head = prime.front();

    while ( (number >= head) && (number != 1) && (head != 0)){
        while ( (number%head == 0) && (number != 1)){
            number = number/head;
            expo += 1;
        }
        res *= (expo + 1);
        prime.pop_front(); // delete the first element.
        head = prime.front();
        expo = 0;
    }

    return res;
}

bool highly_composite_naive(unsigned int number){ // Check if the number is highly composed (naive method)

    for (auto i = 0; i < number; i++){
        if (nb_dividers(i) >= nb_dividers(number)) return false;
    }
    return true;
}

int main(){
    int a;
    std::cin >> a;
    std::cout << " Nombre de diviseur de " << a << " : " << nb_dividers(a) << std::endl;

    // Test de highly_composite
    std::cout << " Hautement composé ? " << highly_composite(a) << std::endl;
}
