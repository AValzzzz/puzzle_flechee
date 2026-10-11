#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "hexagon.h"

void randomBoard(const Hexagon *hex, bool board[]);
void click(const Hexagon *hex, bool board[], int cell);
bool isSolved(const bool board[]);

#endif