#pragma once

#include "sudoku.h"
typedef struct HiddenPair_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    int values[2];
} HiddenPair;


int hidden_pairs(SudokuBoard *p_board);
