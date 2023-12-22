#pragma once

#include "sudoku.h"

typedef struct NakedPair_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    int values[2];
} NakedPair;
bool cell_same_unit(Cell *cell1, Cell *cell2);
int find_naked_pair_values(Cell **p_cells, int *naked_pair_values);
void find_naked_pair(Cell **p_cells, NakedPair *naked_pairs, int *p_counter);
int naked_pairs(SudokuBoard *p_board);