CC = mpicxx
CFLAGS = -O3
LDFLAGS = -lntl -lgmp -lm
EXEC = prime_numbers
SRC =	main.cpp primality_deter/*.cpp primality_proba/*.cpp highly_composite/*.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

# lib:
# 	cd primality_deter && $(MAKE)
# 	cd primality_proba && $(MAKE)
# 	cd highly_composite && $(MAKE)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) ./primality_proba/*.a ./primality_deter/*.a ./highly_composite/*.a

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS) -I./primality_proba -I./primality_deter -I./highly_composite

clean:
	rm *.o $(EXEC)

.PHONY: clean
