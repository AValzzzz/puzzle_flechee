# puzzle_flechee

## Rules :

A hexagon with 4 squares per side (37 spots total). 
Each spot can have two states, either 1 or 2.
Touching a square changes the state of its 6 neighbors + himself.

Objective: There are only 1s.

Start : a random generation with either spot having 1 or 2.

## Build & run

```sh
make
./puzzle
./puzzle {seed}
./puzzle --input
./puzzle_gui
./puzzle_gui {seed}
./puzzle_gui --input
```

With `--input`, type the board from the real game row by row, from top to bottom (13 rows of 1 to 4 cells, e.g. `1 2 2`).

The program prints the board, the list of cells to click (fewest clicks), then plays an animation in the terminal (the cell to click is highlighted)

`puzzle_gui` takes the same arguments and plays the animation in a window (needs raylib).
