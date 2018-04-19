CC = mpicxx
CFLAGS = -fPIC --std=c++14
LDTOOL = ar rcs
LDFLAGS = -lntl -lgmp -lm
LIBDIR = -I../lib/usr/local/include -I../lib/gmp-6.1.2/
EXEC = libprimalitydeter.a
SRC =	AKS.cpp AKS_CONJECTURE.cpp eratosthene.cpp euclide.cpp facteurs.cpp memory_bound.cpp pocklington.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LDTOOL) $@ $^ ../lib/usr/local/lib/libntl.a

AKS.o: AKS.cpp
		$(CC) -c $^ -o $@ $(CFLAGS) $(LIBDIR) -L../lib/usr/local/lib $(LDFLAGS)

AKS_CONJECTURE.o: AKS_CONJECTURE.cpp
			$(CC) -c $^ -o $@ $(CFLAGS) $(LIBDIR) -L../lib/usr/local/lib $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)


clean:
	rm *.o $(EXEC)

.PHONY: clean
