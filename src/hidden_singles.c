#include "hidden_singles.h"

// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
int find_hidden_single_values(Cell **p_cells, int *hidden_single_values)
{
    int count = 0;
    for (int value = 1; value <= BOARD_SIZE; value++)
    {
        int occurrence = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if(p_cells[i]->num_candidates > 1 && is_candidate(p_cells[i], value))
            {
                occurrence++;
            }
        }
        if(occurrence == 1)
        {
            hidden_single_values[count] = value;
            count++; 
        }
    }
    return count;
}

// find hidden single cells in a row, in a collumn or in a box
void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,
                        int *p_counter)
{
    int hidden_single_values[BOARD_SIZE];
    int count_hidden_single = find_hidden_single_values(p_cells, hidden_single_values);
    for (int i = 0; i < count_hidden_single; i++){
        int num = hidden_single_values[i];
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            // if(is_candidate(p_cells[j], num) && is_in_list((p_hidden_singles, *p_counter, p_cells[j]))
            if(is_candidate(p_cells[j], num) && !p_cells[j]->processed)
                {
                    p_hidden_singles[*p_counter].p_cell = p_cells[j];
                    p_hidden_singles[*p_counter].value = num;
                    (*p_counter)++;
                    p_cells[j]->processed = 1;
                }
        }
        }
}

// find hidden single cells in a board, return the number of hidden single cells
int hidden_singles(SudokuBoard *p_board)
{
    HiddenSingle hidden_singles[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        find_hidden_single(p_board->p_cols[j], hidden_singles, &counter);
    }

    // Check boxes
    for (int k = 0; k < BOARD_SIZE; k++) {
        find_hidden_single(p_board->p_boxes[k], hidden_singles, &counter);
    }

    // Apply hidden singles

    for (int i = 0; i < counter; i++)
    {
        Cell *cell = hidden_singles[i].p_cell;
        int value = hidden_singles[i].value;
        set_candidates(cell, &value, 1);
        cell->value = value;
        p_board->solved_cells[p_board->solved_counter++] = cell;
    }
    return counter;
}
