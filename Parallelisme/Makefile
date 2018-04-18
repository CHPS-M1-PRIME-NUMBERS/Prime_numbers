CC = mpicxx
CFLAGS = -O3
LDFLAGS = -lntl -lgmp -lm
LIBDIR = -I./lib/ntl-11.0.0/include -I./lib/gmp-6.1.2
EXEC = prime_numbers
SRC =	main.cpp primality_deter/*.cpp primality_proba/*.cpp highly_composite/*.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

# lib:
# 	cd primality_deter && $(MAKE)
# 	cd primality_proba && $(MAKE)
# 	cd highly_composite && $(MAKE)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) ./primality_proba/*.a ./primality_deter/*.a ./highly_composite/*.a -L./lib/

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS) -I./primality_proba -I./primality_deter -I./highly_composite $(LIBDIR)

clean:
	rm *.o $(EXEC)

.PHONY: clean
