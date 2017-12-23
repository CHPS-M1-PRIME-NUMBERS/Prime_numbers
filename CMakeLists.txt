cmake_minimum_required(VERSION 3.2.2)

project(TP1 VERSION 1.0 LANGUAGES CXX)

# compilation c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include(FindGMP)
find_library(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIR})
include_directories(${GMPXX_INCLUDE_DIR})


# executable
add_executable(prime_numbers main.cpp euclide.cpp millerRabin.cpp memory_bound.cpp eratosthene.cpp pocklington.cpp facteurs.cpp)
target_link_libraries(prime_numbers ${GMP_LIBRARIES} ${GMPXX_LIBRARIRES} gmp gmpxx)
