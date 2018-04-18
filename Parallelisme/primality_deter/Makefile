CC = mpicxx
CFLAGS = -fPIC
LDTOOL = ar rcs
LDFLAGS = -lntl -lgmp
EXEC = libprimalitydeter.a
SRC =	AKS.cpp eratosthene.cpp euclide.cpp facteurs.cpp memory_bound.cpp pocklington.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LDTOOL) $@ $^

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm *.o $(EXEC)

.PHONY: clean
