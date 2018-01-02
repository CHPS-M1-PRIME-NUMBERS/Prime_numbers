add_library(highly_composite highly_composite.cpp)

install (TARGETS highly_composite DESTINATION bin)
install (FILES highly_composite.hpp DESTINATION include)
