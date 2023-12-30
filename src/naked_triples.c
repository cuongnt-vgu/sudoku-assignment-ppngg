#include "naked_triples.h"
#include <stdlib.h>
#include <stdio.h>
bool isElementPresent(int element, int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == element)
        {
            return true;
        }
    }
    return false;
}

int find_naked_triple_values(Cell **p_cells, int *naked_triple_values)
{
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {

        if (p_cells[i]->num_candidates > 1 && p_cells[i]->num_candidates < 4)
        {
            for (int j = i + 1; j < BOARD_SIZE; j++)
            {
                if (p_cells[j]->num_candidates > 1 && p_cells[j]->num_candidates < 4)
                {
                    for (int k = j + 1; k < BOARD_SIZE; k++)
                    {
                        int combo[BOARD_SIZE] = {0};
                        int index = 0;
                        if (p_cells[k]->num_candidates > 1 && p_cells[k]->num_candidates < 4 && !p_cells[i]->processed && !p_cells[j]->processed && !p_cells[k]->processed)
                        {
                            int *candidates = get_candidates(p_cells[i]);
                            for (int c1 = 0, len1 = p_cells[i]->num_candidates; c1 < len1; c1++)
                            {
                                if (!isElementPresent(candidates[c1], combo, BOARD_SIZE))
                                {
                                    combo[index++] = candidates[c1];
                                }
                            }
                            candidates = get_candidates(p_cells[j]);
                            for (int c2 = 0, len2 = p_cells[j]->num_candidates; c2 < len2; c2++)
                            {
                                if (!isElementPresent(candidates[c2], combo, BOARD_SIZE))
                                {
                                    combo[index++] = candidates[c2];
                                }
                            }
                            candidates = get_candidates(p_cells[k]);
                            for (int c3 = 0, len3 = p_cells[k]->num_candidates; c3 < len3; c3++)
                            {
                                if (!isElementPresent(candidates[c3], combo, BOARD_SIZE))
                                {
                                    combo[index++] = candidates[c3];
                                }
                            }
                            
                            free(candidates);
                            //free(candidates1);
                            //free(candidates2);
                            if (index == 3)
                            {
                                for (int t = 0; t < index; t++)
                                {
                                    p_cells[i]->processed = true;
                                    p_cells[j]->processed = true;
                                    p_cells[k]->processed = true;
                                    naked_triple_values[counter++] = combo[t];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return counter;
}

void find_naked_triple(Cell **p_cells, NakedTriple *naked_triples, int *p_counter)
{
    int naked_triple_values[BOARD_SIZE*BOARD_SIZE];
    int naked_triple_count = find_naked_triple_values(p_cells, naked_triple_values);
    for (int i = 0; i < naked_triple_count; i += 3)
    {
        int value1 = naked_triple_values[i];
        int value2 = naked_triple_values[i + 1];
        int value3 = naked_triple_values[i + 2];
        // Find naked triple cells
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->num_candidates > 1 && p_cells[j]->num_candidates < 4)
            {
                for (int k = j + 1; k < BOARD_SIZE; k++)
                {
                    if (p_cells[k]->num_candidates > 1 && p_cells[k]->num_candidates < 4)
                    {
                        for (int l = k + 1; l < BOARD_SIZE; l++)
                        {
                            if (p_cells[l]->num_candidates > 1 && p_cells[l]->num_candidates < 4 && !p_cells[j]->processed && !p_cells[k]->processed && !p_cells[l]->processed)
                            {
                                // Check if 3 cells has 2/3 candidates that match with value1, value2 or value3
                                int c, len, match;
                                bool flag1 = false;
                                bool flag2 = false;
                                bool flag3 = false;
                                for (c = 0, len = p_cells[j]->num_candidates, match = 0; c < len; c++)
                                {
                                    if (is_candidate(p_cells[j], value1) || is_candidate(p_cells[j], value2) || is_candidate(p_cells[j], value3))
                                    {
                                        match++;
                                    }
                                }
                                if (match >= 2)
                                {
                                    flag1 = true;
                                }
                                else
                                {
                                    flag1 = false;
                                }
                                for (c = 0, len = p_cells[k]->num_candidates, match = 0; c < len; c++)
                                {
                                    if (is_candidate(p_cells[k], value1) || is_candidate(p_cells[k], value2) || is_candidate(p_cells[k], value3))
                                    {
                                        match++;
                                    }
                                }
                                if (match >= 2)
                                {
                                    flag2 = true;
                                }
                                else
                                {
                                    flag2 = false;
                                }
                                for (c = 0, len = p_cells[k]->num_candidates, match = 0; c < len; c++)
                                {
                                    if (is_candidate(p_cells[l], value1) || is_candidate(p_cells[l], value2) || is_candidate(p_cells[l], value3))
                                    {
                                        match++;
                                    }
                                }
                                if (match >= 2)
                                {
                                    flag3 = true;
                                }
                                else
                                {
                                    flag3 = false;
                                }
                                if (flag1 == true && flag2 == true && flag3 == true)
                                {
                                    p_cells[j]->processed = true;
                                    p_cells[k]->processed = true;
                                    p_cells[l]->processed = true;
                                    naked_triples[*p_counter].p_cell1 = p_cells[j];
                                    naked_triples[*p_counter].p_cell2 = p_cells[k];
                                    naked_triples[*p_counter].p_cell3 = p_cells[l];
                                    naked_triples[*p_counter].values[0] = value1;
                                    naked_triples[*p_counter].values[1] = value2;
                                    naked_triples[*p_counter].values[2] = value3;
                                    (*p_counter)++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Check for non naked triple cells then remove
    for (int i = 0; i < *p_counter; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->num_candidates > 1 && p_cells[j]->num_candidates < 4)
            {
                // Skip naked triple cells
                if (p_cells[j] != naked_triples[i].p_cell1 && p_cells[j] != naked_triples[i].p_cell2 && p_cells[j] != naked_triples[i].p_cell3)
                {
                    // Check if they are in the same row, same column or same box
                    if (cell_same_unit(p_cells[j], naked_triples[i].p_cell1) &&
                        cell_same_unit(p_cells[j], naked_triples[i].p_cell2) && cell_same_unit(p_cells[j], naked_triples[i].p_cell3) && !p_cells[j]->processed)
                    {
                        // Unset candidates
                        if (is_candidate(p_cells[j], naked_triple_values[0]))
                        {
                            unset_candidate(p_cells[j], naked_triples[i].values[0]);
                            p_cells[j]->processed = true;
                        }
                        if (is_candidate(p_cells[j], naked_triple_values[1]))
                        {
                            unset_candidate(p_cells[j], naked_triple_values[1]);
                            p_cells[j]->processed = true;
                        }
                        if (is_candidate(p_cells[j], naked_triple_values[2]))
                        {
                            unset_candidate(p_cells[j], naked_triple_values[2]);
                            p_cells[j]->processed = true;
                        }
                    }
                }
            }
        }
    }
}
int naked_triples(SudokuBoard *p_board)
{
    NakedTriple naked_triples[BOARD_SIZE * BOARD_SIZE];
    int total_naked_triples = 0;

    // Check rows for naked triples
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_triple(p_board->p_rows[i], naked_triples, &total_naked_triples);
    }

    // Check columns for naked triples
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        find_naked_triple(p_board->p_cols[j], naked_triples, &total_naked_triples);
    }

    // Check boxes for naked triples
    for (int k = 0; k < BOARD_SIZE; k++)
    {
        find_naked_triple(p_board->p_boxes[k], naked_triples, &total_naked_triples);
    }

    return total_naked_triples;
}