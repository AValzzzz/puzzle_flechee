#include <stdlib.h>
#include <stdbool.h>
#include "hexagon.h"

static int distanceFromCenter(int q, int r)
{
    return (abs(q) + abs(r) + abs(q + r)) / 2;
}

static bool areNeighbors(const Hexagon *hex, int a, int b)
{
    int dq = hex->q[b] - hex->q[a];
    int dr = hex->r[b] - hex->r[a];

    return distanceFromCenter(dq, dr) == 1;
}

static void placeCells(Hexagon *hex)
{
    int radius = SIDE - 1;
    int i = 0;

    for (int row = 0; row < NB_ROWS; row++)
    {
        int col = 0;

        for (int q = -radius; q <= radius; q++)
        {
            int doubleR = row - 2 * radius - q;
            int r = doubleR / 2;

            if (doubleR % 2 != 0 || distanceFromCenter(q, r) > radius)
                continue;

            hex->q[i] = q;
            hex->r[i] = r;
            hex->row[i] = row;
            hex->col[i] = col;
            col++;
            i++;
        }
    }
}

static void findNeighbors(Hexagon *hex)
{
    for (int i = 0; i < NB_CELLS; i++)
    {
        hex->nbNeighbors[i] = 0;

        for (int j = 0; j < NB_CELLS; j++)
        {
            if (areNeighbors(hex, i, j))
            {
                hex->neighbors[i][hex->nbNeighbors[i]] = j;
                hex->nbNeighbors[i]++;
            }
        }
    }
}

void initHexagon(Hexagon *hex)
{
    placeCells(hex);
    findNeighbors(hex);
}
