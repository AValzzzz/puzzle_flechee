#include <stdio.h>
#include "hexagon.h"
#include "input.h"
#include "solver.h"
#include "display.h"

int main(int argc, char *argv[])
{
    Hexagon hex;
    initHexagon(&hex);

    bool board[NB_CELLS];
    if (!loadBoard(&hex, board, argc, argv))
        return 1;

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
