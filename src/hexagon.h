#ifndef HEXAGON_H
#define HEXAGON_H

#define SIDE 4
#define NB_ROWS (4 * SIDE - 3)
#define NB_CELLS 37
#define MAX_NEIGHBORS 6

/*
 * The cells are numbered from 0 to 36, row by row, from top to bottom
 * and left to right:
 *
 *           0
 *        1     2
 *     3     4     5
 *  6     7     8     9
 *    10    11    12
 * 13    14    15    16
 *    17    18    19
 * 20    21    22    23
 *    24    25    26
 * 27    28    29    30
 *    31    32    33
 *       34    35
 *          36
 */

typedef struct {
    int q[NB_CELLS];
    int r[NB_CELLS];
    int row[NB_CELLS];
    int col[NB_CELLS];
    int nbNeighbors[NB_CELLS];
    int neighbors[NB_CELLS][MAX_NEIGHBORS];
} Hexagon;

void initHexagon(Hexagon *hex);

#endif