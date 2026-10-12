#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include "hexagon.h"
#include "solver.h"

void printBoard(const Hexagon *hex, const bool board[], int highlighted);
void printSolution(const Hexagon *hex, const Solution *solution);
void animateSolution(const Hexagon *hex, bool board[], const Solution *solution);

#endif