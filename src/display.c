#include <stdio.h>
#include "display.h"

#define CELL_WIDTH 4
#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"

static void printIndent(int row)
{
    int missingCells = NB_ROWS - rowLength(row);
    int spaces = missingCells * CELL_WIDTH / 2;

    for (int i = 0; i < spaces; i++)
        printf(" ");
}

static void printCell(bool value)
{
    int number = value ? 1 : 2;

    if (value)
        printf(COLOR_GREEN " %d " COLOR_RESET " ", number);
    else
        printf(COLOR_RED " %d " COLOR_RESET " ", number);
}

void printBoard(const Hexagon *hex, const bool board[])
{
    for (int i = 0; i < NB_CELLS; i++)
    {
        bool newRow = (i == 0 || hex->row[i] != hex->row[i - 1]);

        if (newRow)
        {
            if (i > 0)
                printf("\n");
            printIndent(hex->row[i]);
        }
        printCell(board[i]);
    }
    printf("\n");
}

static void printCellName(const Hexagon *hex, int cell)
{
    printf("row %d, cell %d", hex->row[cell] + 1, hex->col[cell] + 1);
}

void printSolution(const Hexagon *hex, const Solution *solution)
{
    printf("Solution in %d clicks:\n", solution->nbClicks);

    for (int i = 0; i < solution->nbClicks; i++)
    {
        printf("  %2d. ", i + 1);
        printCellName(hex, solution->clicks[i]);
        printf("\n");
    }
}