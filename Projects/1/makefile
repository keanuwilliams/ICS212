# Makefile for Project 1

PROG = project
SRC  = ui.c driver.c dbfunctions.c

CC      = gcc
CFLAGS  = -ansi -pedantic-errors -Wall
LDFLAGS =

OBJ = $(SRC:.c=.o)

.PHONY: all

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJ) $(PROG)

real_clean:
	rm -f $(OBJ) $(PROG) file.txt proof_of_compilation.txt test_output.txt

proof:
	script proof_of_compilation.txt

test:
	script test_output.txt

run:
	./$(PROG)
debug:
	./$(PROG) debug
