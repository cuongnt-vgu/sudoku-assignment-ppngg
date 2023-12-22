#include "naked_pairs.h"
#include <stdlib.h>

int find_naked_pair_values(Cell **p_cells, int *naked_pair_values)
{
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = i + 1; j < BOARD_SIZE; j++)
        {
            if (p_cells[i]->num_candidates == 2 && p_cells[j]->num_candidates == 2 && !p_cells[i]->processed && !p_cells[j]->processed)
            {
                int *candidates1 = get_candidates(p_cells[i]);
                int *candidates2 = get_candidates(p_cells[j]);
                if (candidates1[0] == candidates2[0] && candidates1[1] == candidates2[1])
                {
                    naked_pair_values[counter++] = candidates1[0];
                    naked_pair_values[counter++] = candidates1[1];
                    p_cells[i]->processed = true;
                    p_cells[j]->processed = true;
                }
                free(candidates1);
                free(candidates2);
            }
        }
    }
    return counter;
}
// Find naked pair cells and unset candidates for other cells
void find_naked_pair(Cell **p_cells, NakedPair *naked_pairs, int *p_counter)
{
    int naked_pair_values[BOARD_SIZE * 2];
    int num_pair = find_naked_pair_values(p_cells, naked_pair_values);
    for (int i = 0; i < num_pair; i += 2)
    {
        int value1 = naked_pair_values[i];
        int value2 = naked_pair_values[i + 1];
        // Find naked pair cells
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            for (int k = j + 1; k < BOARD_SIZE; k++)
            {
                if (p_cells[j]->num_candidates == 2 && p_cells[k]->num_candidates == 2)
                {
                    if (is_candidate(p_cells[j], value1) && is_candidate(p_cells[j], value2) && is_candidate(p_cells[k], value1) && is_candidate(p_cells[k], value2))
                    {
                        naked_pairs[*p_counter].p_cell1 = p_cells[j];
                        naked_pairs[*p_counter].p_cell2 = p_cells[k];
                        naked_pairs[*p_counter].values[0] = value1;
                        naked_pairs[*p_counter].values[1] = value2;
                        (*p_counter)++;
                    }
                }
            }
        }
    }
    // Check for non naked pair cells and unset candidates, set processed flag to avoid reevaluation
    for (int i = 0; i < *p_counter; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->num_candidates > 1)
            {
                // Skip naked pair cells
                if (p_cells[j] != naked_pairs[i].p_cell1 && p_cells[j] != naked_pairs[i].p_cell2)
                {
                    // Check if they are in the same row, same column or same box
                    if (cell_same_unit(p_cells[j], naked_pairs[i].p_cell1) &&
                        cell_same_unit(p_cells[j], naked_pairs[i].p_cell2) && !p_cells[j]->processed)
                    {
                        // Unset candidates
                        {
                            int *cnd = get_candidates(p_cells[j]);
                            int num = p_cells[j]->num_candidates;
                            for (int k = 0; k < num; k++)
                            {
                                if (cnd[k] == naked_pairs[i].values[0] && !p_cells[j]->processed)
                                {
                                    unset_candidate(p_cells[j], cnd[k]);
                                    p_cells[j]->processed = true;
                                }
                                if (cnd[k] == naked_pairs[i].values[1])
                                {
                                    unset_candidate(p_cells[j], cnd[k]);
                                    p_cells[j]->processed = true;
                                }
                            }
                            free(cnd);
                        }
                    }
                }
            }
        }
    }
}
int naked_pairs(SudokuBoard *p_board)
{
    NakedPair naked_pairs[BOARD_SIZE * 2];
    int count = 0;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pair(p_board->p_rows[i], naked_pairs, &count);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pair(p_board->p_cols[i], naked_pairs, &count);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pair(p_board->p_boxes[i], naked_pairs, &count);
    }
    return count;
}