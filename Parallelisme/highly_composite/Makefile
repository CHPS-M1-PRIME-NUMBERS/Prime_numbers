CC = mpicxx
CFLAGS = -O3 -fPIC --std=c++14
LDTOOL = ar rcs
LIBDIR = -I../primality_deter -L../primality_deter -lprimalitydeter
EXEC = libhighlycomposite.a
SRC =	highly_composite.cpp
OBJ = $(SRC:.cpp=.o)
all: $(EXEC)

$(EXEC): $(OBJ)
	$(LDTOOL) $@ $^

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS) $(LIBDIR)

clean:
	rm *.o $(EXEC)

.PHONY: clean
