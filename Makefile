CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -O2

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = puzzle

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c src/*.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(EXEC)

.PHONY: all clean