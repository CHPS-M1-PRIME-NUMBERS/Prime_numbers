cmake_minimum_required(VERSION 3.9.4)

project(Prime_numbers VERSION 1.0 LANGUAGES CXX)

# compilation c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_library(NTL_LIB ntl)
if(NOT NTL_LIB)
  message(FATAL_ERROR "ntl library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
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
