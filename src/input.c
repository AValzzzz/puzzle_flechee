#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "input.h"
#include "board.h"

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

static bool readBoard(const Hexagon *hex, bool board[])
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

static void generateBoard(const Hexagon *hex, bool board[], const char *seedArg)
{
    unsigned int seed = time(NULL);
    if (seedArg != NULL)
        seed = strtoul(seedArg, NULL, 10);
    srand(seed);

    randomBoard(hex, board);
    printf("Seed: %u\n", seed);
}

bool loadBoard(const Hexagon *hex, bool board[], int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--input") == 0)
    {
        if (!readBoard(hex, board))
        {
            printf("\nIncomplete board.\n");
            return false;
        }
    }
    else
        generateBoard(hex, board, argc > 1 ? argv[1] : NULL);
    return true;
}
