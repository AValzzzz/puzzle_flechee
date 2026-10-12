#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include "hexagon.h"

bool loadBoard(const Hexagon *hex, bool board[], int argc, char *argv[]);

#endif
