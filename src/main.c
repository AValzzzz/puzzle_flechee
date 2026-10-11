#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hexagon.h"
#include "board.h"
#include "solver.h"
#include "display.h"

int main(int argc, char *argv[])
{
    unsigned int seed = time(NULL);
    if (argc > 1)
        seed = strtoul(argv[1], NULL, 10);
    srand(seed);

    Hexagon hex;
    initHexagon(&hex);

    bool board[NB_CELLS];
    randomBoard(&hex, board);

    printf("Seed: %u\n\n",seed);
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
