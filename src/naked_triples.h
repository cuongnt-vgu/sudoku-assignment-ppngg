#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cell1
    Cell *p_cell2
    Cell *p_cell3
    int values[3]
}
int find_naked_triple_values(Cell **p_cells, int *naked_triple_values);
void find_naked_triple(Cell **p_cells, naked *naked_pairs, int *p_counter)
int naked_triples(SudokuBoard *p_board);