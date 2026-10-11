#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>
#include "hexagon.h"

typedef struct {
    int clicks[NB_CELLS];
    int nbClicks;
} Solution;

bool solve (const Hexagon *hex, const bool board[], Solution *best);

#endif