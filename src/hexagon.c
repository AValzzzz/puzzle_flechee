#include <stdlib.h>
#include <stdbool.h>
#include "hexagon.h"

static int max(int a, int b) { return a > b ? a : b; }
static int min(int a, int b) { return a < b ? a : b; }

int rowLength(int row)
{
    return NB_ROWS - abs(row - (SIDE - 1));
}

static bool areNeighbors(const Hexagon *hex, int a, int b)
{
    int dq = hex->q[b] - hex->q[a];
    int dr = hex->r[b] - hex->r[a];
    int distance = (abs(dq) + abs(dr) + abs(dq + dr)) / 2;

    return distance == 1;
}

static void placeCells(Hexagon *hex)
{
    int radius = SIDE - 1;
    int i = 0;

    for (int r = -radius; r <= radius; r++)
    {
        int qMin = max(-radius, -radius - r);
        int qMax = min(radius, radius - r);

        for (int q = qMin; q <= qMax; q++)
        {
            hex->q[i] = q;
            hex->r[i] = r;
            hex->row[i] = r + radius;
            hex->col[i] = q - qMin;
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