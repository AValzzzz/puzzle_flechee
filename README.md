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
```

Thr program prints the board, the list of cells to click (fewest clicks), then plays an animation in the terminal (the cell to click is highlighted)