#include <stdlib.h>
#include "board.h"

void randomBoard(const Hexagon *hex, bool board[])
{
    for (int i = 0; i < NB_CELLS; i++)
        board[i] = true;
    for (int i = 0; i < NB_CELLS; i++)
        if (rand() % 2 == 0)
            click(hex, board, i);
}

void click(const Hexagon *hex, bool board[], int cell)
{
    board[cell] = !board[cell];

    for (int i = 0; i < hex->nbNeighbors[cell]; i++)
    {
        int neighbor = hex->neighbors[cell][i];
        board[neighbor] = !board[neighbor];
    }
}

bool isSolved(const bool board[])
{
    for (int i = 0; i < NB_CELLS; i++)
        if (!board[i])
            return false;
    return true;
}