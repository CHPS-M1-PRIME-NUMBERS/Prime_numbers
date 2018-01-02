add_library(primality_deter AKS.cpp eratosthene.cpp euclide.cpp facteurs.cpp memory_bound.cpp
    pocklington.cpp)

install (TARGETS primality_deter DESTINATION bin)
install (FILES AKS.hpp eratosthene.hpp CPolyMod.hpp euclide.hpp facteurs.hpp memory_bound.hpp
pocklington.hpp DESTINATION include)
