#include <stdio.h>
#include <ctype.h>
#include "input.h"

#define LINE_SIZE 256

static int countCellsInRow(const Hexagon *hex, int row)
{
    int count = 0;

    for (int i = 0; i < NB_CELLS; i++)
        if (hex->row[i] == row)
            count++;
    return count;
}

static bool parseRow(const char *line, bool cells[], int length)
{
    int count = 0;

    for (const char *c = line; *c != '\0'; c++)
    {
        if (isspace((unsigned char)*c))
            continue;
        if ((*c != '1' && *c != '2') || count == length)
            return false;
        cells[count] = (*c == '1');
        count++;
    }
    return count == length;
}

static bool readRow(bool cells[], int row, int length)
{
    char line[LINE_SIZE];

    printf("Row %2d (%d cells): ", row + 1, length);
    while (fgets(line, sizeof line, stdin) != NULL)
    {
        if (parseRow(line, cells, length))
            return true;
        printf("Expected %d values, each 1 or 2. Row %2d: ", length, row + 1);
    }
    return false;
}

bool readBoard(const Hexagon *hex, bool board[])
{
    int cell = 0;

    printf("Enter each row from top to bottom, using 1 and 2:\n");

    for (int row = 0; row < NB_ROWS; row++)
    {
        int length = countCellsInRow(hex, row);

        if (!readRow(board + cell, row, length))
            return false;
        cell += length;
    }
    return true;
}
