CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -O2

COMMON = src/hexagon.o src/board.o src/solver.o src/input.o
EXEC = puzzle
GUI = puzzle_gui

all: $(EXEC) $(GUI)

$(EXEC): $(COMMON) src/main.o src/display.o
	$(CC) $(CFLAGS) -o $@ $^

$(GUI): $(COMMON) src/gui.o
	$(CC) $(CFLAGS) -o $@ $^ -lraylib -lm

src/%.o: src/%.c src/*.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf src/*.o $(EXEC) $(GUI)

.PHONY: all clean
