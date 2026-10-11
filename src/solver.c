#include "solver.h"
#include "board.h"

typedef struct
{
    const Hexagon *hex;
    bool board[NB_CELLS];
    int lastTouch[NB_CELLS];
    Solution current;
    Solution *best;
    bool found;
} Search;

static void computeLastTouch(const Hexagon *hex, int lastTouch[])
{
    for (int i = 0; i < NB_CELLS; i++)
    {
        lastTouch[i] = i;

        for (int j = 0; j < hex->nbNeighbors[i]; j++)
        {
            int neighbor = hex->neighbors[i][j];
            if (neighbor > lastTouch[i])
                lastTouch[i] = neighbor;
        }
    }
}

static bool lockedCellsAreOk(const Search *s, int decided)
{
    for (int i = 0; i < NB_CELLS; i++)
        if (s->lastTouch[i] == decided && !s->board[i])
            return false;
    return true;
}

static void search(Search *s, int cell)
{
    if (s->found && s->current.nbClicks >= s->best->nbClicks)
        return;

    if (cell == NB_CELLS)
    {
        *s->best = s->current;
        s->found = true;
        return;
    }

    if (lockedCellsAreOk(s, cell))
        search(s, cell + 1);

    click(s->hex, s->board, cell);
    s->current.clicks[s->current.nbClicks] = cell;
    s->current.nbClicks++;

    if (lockedCellsAreOk(s, cell))
        search(s, cell + 1);

    s->current.nbClicks--;
    click(s->hex, s->board, cell);
}

bool solve(const Hexagon *hex, const bool board[], Solution *best)
{
    Search s;

    s.hex = hex;
    for (int i = 0; i < NB_CELLS; i++)
        s.board[i] = board[i];

    computeLastTouch(hex, s.lastTouch);
    s.current.nbClicks = 0;
    s.best = best;
    s.found = false;

    search(&s, 0);
    return s.found;
}