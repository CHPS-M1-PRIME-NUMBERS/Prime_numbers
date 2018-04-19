CC = mpicxx
CFLAGS = -O3 --std=c++14
LDFLAGS = -lntl -lgmp -lm
LIBDIR = -I./lib/usr/local/include/ -I./lib/gmp-6.1.2/
EXEC = prime_numbers
SRC =	main.cpp
OBJ = $(SRC:.cpp=.o)


all: lib $(EXEC)

lib:
	$(MAKE) -C highly_composite/
	$(MAKE) -C primality_proba/
	$(MAKE) -C primality_deter/

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LIBDIR) -L./lib/usr/local/lib/ -L./lib/gmp-6.1.2/ ./primality_proba/*.a ./primality_deter/*.a ./highly_composite/*.a $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS) -I./primality_proba -I./primality_deter -I./highly_composite $(LIBDIR) $(LDFLAGS)

clean:
	rm *.o $(EXEC)

.PHONY: clean lib
