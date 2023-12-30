#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell *p_cell3;
    int values[3];
} NakedTriple;
bool isElementPresent(int element, int *array, int size);
void generateCombinations(int n, int ***combinations, int *combinationsCount);
void freeCombinations(int ***combinations, int combinationsCount);
int find_naked_triple_values(Cell **p_cells, int *naked_triple_values, int **combinations, int combinationsCount);
void find_naked_triple(Cell **p_cells, NakedTriple *naked_pairs, int *p_counter, int **combinations, int combinationsCount);
int naked_triples(SudokuBoard *p_board);
