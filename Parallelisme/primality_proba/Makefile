CC = mpicxx
CFLAGS = -fPIC
LDTOOL = ar rcs
EXEC = libprimalityproba.a
SRC =	millerRabin.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	 $(LDTOOL) $@ $^

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm *.o $(EXEC)

.PHONY: clean
