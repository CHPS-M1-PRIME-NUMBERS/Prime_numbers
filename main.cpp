#include <iostream>
#include <chrono>
#include <gmpxx.h>

#include "memory_bound.hpp"
#include "euclide.hpp"
#include "millerRabin.hpp"
#include "pocklington.hpp"


std::ostream& operator<<(std::ostream& out, mpz_class& chiffre){
        out << chiffre.get_str();
        return out;
}

int main(int argc, char** argv){

        unsigned int candidatPrime1 = 27457;
        unsigned int candidatPrime2 = 8353;
        unsigned int candidatPrime3 = 491;
        bool result;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        int elapsed_time;

        mpz_class a(10);
        a += a;

        /*
           std::cout << "==== Memory Bound || Eratosthene sieve ====" << std::endl;

           std::list<unsigned int> liste;
           unsigned int n = 500;
           start = std::chrono::system_clock::now();
           memory_bound(n, &liste);
           end = std::chrono::system_clock::now();
           std::cout << "Eratosthene sieve from 2 to " << n << ":" << std::endl;
           std::cout << liste << std::endl;
           elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
           std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;


         */
        std::cout << "==== Pocklington ====" << '\n';

        std::cout << "Is " << candidatPrime1 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = pocklington(candidatPrime1);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime2 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = pocklington(candidatPrime2);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime3 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = pocklington(candidatPrime3);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;

/*
        std::cout << "==== Miller Rabin ====" << '\n';

        unsigned int iterations = 50;

        std::cout << "Is " << candidatPrime1 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = millerRabin(candidatPrime1, iterations);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        std::cout << "It seems ";
        if(result) {
                std::cout << "True";
        }else{
                std::cout << "False";
        }
        std::cout << " after " << iterations << " iterations." << std::endl;
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime2 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = millerRabin(candidatPrime2, iterations);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        std::cout << "It seems ";
        if(result) {
                std::cout << "True";
        }else{
                std::cout << "False";
        }
        std::cout << " after " << iterations << " iterations." << std::endl;
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime3 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = millerRabin(candidatPrime3, iterations);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        std::cout << "It seems ";
        if(result) {
                std::cout << "True";
        }else{
                std::cout << "False";
        }
        std::cout << " after " << iterations << " iterations." << std::endl;
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;



        std::cout << "==== Computation Bound || Euclide ====" << '\n';

        std::cout << "Is " << candidatPrime1 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = computation_bound_euclide(283);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime2 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = computation_bound_euclide(candidatPrime2);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime3 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = computation_bound_euclide(candidatPrime3);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;



        std::cout << "==== Computation Bound || Modulo ====" << '\n';

        std::cout << "Is " << candidatPrime1 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = computation_bound_modulo(283);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime2 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = computation_bound_modulo(candidatPrime2);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
        std::cout << "-" << std::endl;
        std::cout << "Is " << candidatPrime3 << " a prime number?" << std::endl;
        start = std::chrono::system_clock::now();
        result = computation_bound_modulo(candidatPrime3);
        end = std::chrono::system_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
                               (end-start).count();
        if(result) {
                std::cout << "True" << std::endl;
        }else{
                std::cout << "False" << std::endl;
        }
        std::cout << "Time elapsed: " << elapsed_time << " ns" << std::endl;
 */
        return 0;
}
