add_library(primality_proba millerRabin.cpp)

install (TARGETS primality_proba DESTINATION bin)
install (FILES millerRabin.hpp DESTINATION include)
