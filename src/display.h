#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include "hexagon.h"
#include "solver.h"

void printBoard(const Hexagon *hex, const bool board[]);
void printSolution(const Hexagon *hex, const Solution *solution);

#endif