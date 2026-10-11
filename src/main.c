#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hexagon.h"
#include "board.h"
#include "input.h"
#include "solver.h"
#include "display.h"

static void generateBoard(const Hexagon *hex, bool board[], const char *seedArg)
{
    unsigned int seed = time(NULL);
    if (seedArg != NULL)
        seed = strtoul(seedArg, NULL, 10);
    srand(seed);

    randomBoard(hex, board);
    printf("Seed: %u\n", seed);
}

int main(int argc, char *argv[])
{
    Hexagon hex;
    initHexagon(&hex);

    bool board[NB_CELLS];
    if (argc > 1 && strcmp(argv[1], "--input") == 0)
    {
        if (!readBoard(&hex, board))
        {
            printf("\nIncomplete board.\n");
            return 1;
        }
    }
    else
        generateBoard(&hex, board, argc > 1 ? argv[1] : NULL);

    printf("\n");
    printBoard(&hex, board, NO_HIGHLIGHT);
    printf("\n");

    Solution solution;
    if (!solve(&hex, board, &solution)) {
        printf("This board has no solution. \n");
        return 1;
    }
    printSolution(&hex, &solution);

    printf("\nPress Enter to watch the animation...");
    getchar();
    animateSolution(&hex, board, &solution);

    return 0;
}
