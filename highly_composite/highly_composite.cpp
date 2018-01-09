#include "highly_composite.hpp"


unsigned long int nb_dividers(unsigned long int number){ // calculates the number of divisors of an integer
    std::list<unsigned long int> prime; // List of prime number
    memory_bound(number, &prime);

    unsigned long int res = 1;
    int expo = 0;
    unsigned long int head = prime.front();

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

bool highly_composite_naive(unsigned long int number){ // Check if the number is highly composed (naive method)

    for (auto i = 0; i < number; i++){
        if (nb_dividers(i) >= nb_dividers(number)) return false;
    }
    return true;
}

/**
The prime factorization of a highly composite number, then:
    1. The primes 2, 3, ..., p form a string of consecutive primes,
    2. The exponents are nonincreasing, so a_2>=a_3>=...>=a_p, and
    3. The final exponent a_p is always 1, except for the two cases N=4=2^2 and N=36=2^2·3^2, where it is 2.
*/

bool highly_composite_def(unsigned long int number){ // definition that use the form of a highly composite
    std::list<unsigned long int> prime; // List of prime number
    memory_bound(number, &prime);

    unsigned long int nbr = number;
    unsigned long int tmp = 0;
    unsigned long int expo = number; // It's a defautl expo (everytime is wrong but after the first test will be true)
    unsigned long int head = prime.front();

    while ( (number >= head) && (number != 1) && (head != 0)){
        while ( (number%head == 0) && (number != 1)){
            number = number/head;
            tmp += 1;
        }
        if (expo < tmp) return false;
        expo = tmp;
        tmp = 0;
        prime.pop_front(); // delete the first element.
        head = prime.front();
    }
    if ((nbr != 4) && (nbr != 36) && (expo != 1))
        return false; // The final exponent a_p is always 1, except for the two cases N = 4 and N = 36.

    return true;
}
