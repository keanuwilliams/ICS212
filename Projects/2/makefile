# Makefile for Homework

PROG  = database
DPROG = databaseDEBUG
SRC   = driver.cpp menu.cpp llist.cpp 

CC      = g++
CFLAGS  = -ansi -pedantic-errors -Wall -c
DFLAGS  = $(CFLAGS) -DDEBUG
LDFLAGS =

OBJ = $(SRC:.cpp=.o)

.PHONY: final

final:
	$(CC) $(CFLAGS) $(SRC)
	$(CC) -o $(PROG) $(OBJ)

.PHONY: debug

debug:
	$(CC) $(DFLAGS) $(SRC)
	$(CC) -o $(DPROG) $(OBJ)
	
.PHONY: clean

clean:
	rm -f $(OBJ) $(PROG) $(DPROG) 

proof:
	script proof_of_compilation.txt

test:
	script test_output.txt

run:
	./$(PROG)

run_debug:
	./$(DPROG)


