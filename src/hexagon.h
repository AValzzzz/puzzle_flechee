#ifndef HEXAGON_H
#define HEXAGON_H

#define SIDE 4
#define NB_ROWS (2 * SIDE - 1)
#define NB_CELLS 37
#define MAX_NEIGHBORS 6

typedef struct {
    int q[NB_CELLS];
    int r[NB_CELLS];
    int row[NB_CELLS];
    int col[NB_CELLS];
    int nbNeighbors[NB_CELLS];
    int neighbors[NB_CELLS][MAX_NEIGHBORS];
} Hexagon;

void initHexagon(Hexagon *hex);
int rowLength(int row);

#endif