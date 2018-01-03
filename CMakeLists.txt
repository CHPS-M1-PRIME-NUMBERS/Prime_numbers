cmake_minimum_required(VERSION 3.2.2)

project(Prime_numbers VERSION 1.0 LANGUAGES CXX)

# compilation c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_library(NTL_LIB ntl)
if(NOT NTL_LIB)
  message(FATAL_ERROR "ntl library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
endif()

#includes our libraries
include_directories ("${PROJECT_SOURCE_DIR}/primality_proba")
include_directories ("${PROJECT_SOURCE_DIR}/primality_deter")
include_directories ("${PROJECT_SOURCE_DIR}/highly_composite")
add_subdirectory (primality_proba)
add_subdirectory (primality_deter)
add_subdirectory (highly_composite)
set (EXTRA_LIBS ${EXTRA_LIBS} primality_proba primality_deter highly_composite)

add_executable(prime_numbers main.cpp)
target_link_libraries(prime_numbers ${NTL_LIB} ${M_LIB} ${GMP_LIBRARIES} ${GMPXX_LIBRARIRES} ${EXTRA_LIBS} ntl gmp gmpxx)
