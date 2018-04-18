CC = mpicxx
CFLAGS = -O3
LDFLAGS = -lntl -lgmp -lm
LIBDIR = -I./lib/ntl-11.0.0/include -I./lib/gmp-6.1.2
EXEC = prime_numbers
SRC =	main.cpp
OBJ = $(SRC:.cpp=.o)


all: lib $(EXEC)

lib:
	$(MAKE) -C highly_composite/
	$(MAKE) -C primality_proba/
	$(MAKE) -C primality_deter/

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) ./primality_proba/*.a ./primality_deter/*.a ./highly_composite/*.a -L./lib/

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS) -I./primality_proba -I./primality_deter -I./highly_composite $(LIBDIR)

clean:
	rm *.o $(EXEC)

.PHONY: clean lib
